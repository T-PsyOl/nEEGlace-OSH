#pragma once
/**
 * OnsetDetector.h
 * ---------------

 * Algorithm:
 *   1. SVF (State-Variable Filter, TPT form) splits each sample into LP / BP / HP
 *   2. Four detection channels: Wideband (WB), LP, BP, HP
 *   3. Each channel runs a fast and a slow one-pole IIR on the squared signal
 *      → energy ratio = fast_env / slow_env  (transient emphasis)
 *   4. Per-sample threshold across all 4 channels:
 *      → onset fires if ANY channel's ratio exceeds (threshBase + raise)
 *      → on detection: raise term jumps by jumpFactor × current threshold
 *      → every sample: raise term decays by decay_mul  (= decayConst^(-1/Fs))
 *
 * Usage in Bela:
 *
 *   In setup():
 *   OnsetDetectorParams p;   // edit fields to tune, or use defaults
 *   detector.setup(context->audioSampleRate, p);
 *
 *   In render():
 *   float sample = audioRead(context, n, 0);
 *   if (detector.processSample(sample)) {
 *   }
 *
 * No heap allocation after setup(). All state is in-class value types.
 * Safe to call reset() between recordings without re-running setup().
 */

#include <cmath>

//  parameters  
struct OnsetDetectorParams {
    float svf_cutoff_Hz   = 800.0f;
    float svf_Q           = 0.70710678f;   // 1/sqrt(2)
    // index: 0 = Wideband, 1 = LP, 2 = BP, 3 = HP
  // Main user parameter:
    // 1 = sensitive
    // 2 = less sensitive
    // 3 = much less sensitive
    float sensitivity = 1.0f;//added by martin 
	 float minEnergy   = 1e-7f; //changed by martin 

    float threshBase[4]   = {16.0f,   8.0f,   4.0f,    4.0f};

    float jumpFactor[4]   = { 4.0f,   6.0f,  32.0f,    8.0f};
    float decayConst[4]   = {8000.0f, 100.0f, 100.0f, 2000.0f}; 
    float tauFast_ms[4]   = { 2.0f,   2.0f,   2.0f,    4.0f};
    float tauSlow_ms[4]   = {20.0f,  10.0f,   5.0f,  160.0f};
};



//  OnsetDetector class
class OnsetDetector {
public:

    void setup(float sampleRate, const OnsetDetectorParams& p = OnsetDetectorParams{})
    {
        Fs     = sampleRate;
        params = p;

        // SVF coefficients 
        float wd = params.svf_cutoff_Hz * 6.28318530f;
        float T  = 1.0f / Fs;
        float wa = (2.0f / T) * std::tan(wd * T * 0.5f);
        svf_g    = wa * T * 0.5f;                          // cached for render
        float R  = 1.0f / (2.0f * params.svf_Q);

        svf_mul_state1 = 2.0f * R + svf_g;
        svf_mul_in     = 1.0f / (1.0f + 2.0f * R * svf_g + svf_g * svf_g);

        // one-pole IIR alphas and per-sample decay multipliers
        for (int c = 0; c < 4; ++c) {
            alpha_fast[c] = std::exp(-1.0f / (params.tauFast_ms[c] * 1e-3f * Fs));
            alpha_slow[c] = std::exp(-1.0f / (params.tauSlow_ms[c] * 1e-3f * Fs));
            decay_mul[c]  = std::pow(params.decayConst[c], -1.0f / Fs);
        }

        reset();
    }

    
    void reset()
    {
        svf_state1 = 0.0f;
        svf_state2 = 0.0f;
        for (int c = 0; c < 4; ++c) {
            iir_fast[c]     = 0.0f;
            iir_slow[c]     = 0.0f;
            thresh_raise[c] = 0.0f;
        }
    }

    
    // returns true when onset detected at present sample
    bool processSample(float x)
    {
        // SVF bandsplit (TPT form, sample-by-sample) 
        float yhp = (x - svf_mul_state1 * svf_state1 - svf_state2) * svf_mul_in;

        float g_yhp = svf_g * yhp;
        float ybp   = svf_state1 + g_yhp;
        svf_state1  = ybp + g_yhp;

        float g_ybp = svf_g * ybp;
        float ylp   = svf_state2 + g_ybp;
        svf_state2  = ylp + g_ybp;

        // channel signals: WB, LP, BP, HP
        float sig[4] = {x, ylp, ybp, yhp};

        // fast/slow energy ratio per channel
        float er[4];
        for (int c = 0; c < 4; ++c) {
            float x2    = sig[c] * sig[c];
            iir_fast[c] = (1.0f - alpha_fast[c]) * x2 + alpha_fast[c] * iir_fast[c];
            iir_slow[c] = (1.0f - alpha_slow[c]) * x2 + alpha_slow[c] * iir_slow[c];

            float denom = iir_slow[c] < 1e-10f ? 1e-10f : iir_slow[c]; 
            er[c]       = iir_fast[c] / denom;
        }

        // per-sample threshold check
        bool onset = false;
        float thr[4];
        for (int c = 0; c < 4; ++c) {
            //thr[c] = params.threshBase[c] + thresh_raise[c]; //original 
			thr[c] = params.sensitivity * params.threshBase[c] 
       + thresh_raise[c]; //added by martin
           // if (er[c] > thr[c]) { //original
          //      onset = true; //original
         //   } //original
        //} //original
		if (iir_slow[c] > params.minEnergy &&//added by martin
	    er[c] > thr[c]) {//added by martin
	    onset = true;//added by martin
			}//added by martin
		}//added by martin
		
        // update raise term 
        if (onset) {
            for (int c = 0; c < 4; ++c) {
                thresh_raise[c] = params.jumpFactor[c] * thr[c];   
            }
        }
        for (int c = 0; c < 4; ++c) {
            thresh_raise[c] *= decay_mul[c]; 
        }

        return onset;
    }

    // diagnostics 
    float getEnergyRatio(int ch) const {
        if (ch < 0 || ch > 3) return 0.0f;
        float d = iir_slow[ch] < 1e-10f ? 1e-10f : iir_slow[ch];
        return iir_fast[ch] / d;
    }
    float getThreshold(int ch) const {
        if (ch < 0 || ch > 3) return 0.0f;
        return params.threshBase[ch] + thresh_raise[ch];
    }
    float getSampleRate() const { return Fs; }

private:
    // coefficients 
    float Fs              = 44100.0f;
    float svf_g           = 0.0f;
    float svf_mul_state1  = 0.0f;
    float svf_mul_in      = 1.0f;
    float alpha_fast[4]   = {};
    float alpha_slow[4]   = {};
    float decay_mul[4]    = {};

    // runtime state
    float svf_state1      = 0.0f;
    float svf_state2      = 0.0f;
    float iir_fast[4]     = {};
    float iir_slow[4]     = {};
    float thresh_raise[4] = {};

    OnsetDetectorParams params;
};
