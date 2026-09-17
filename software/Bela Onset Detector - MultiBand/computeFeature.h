#ifndef COMPUTE_FEATURES_H
#define COMPUTE_FEATURES_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <cstddef>

#include <fftw3.h>


class FeatureCalculator
{
public:
    explicit FeatureCalculator(int fftSize = 512)
		: fftSize_(fftSize),
          sampleRate_(44100.0f),
          fftInput_(nullptr),
          fftOutput_(nullptr),
          fftPlan_(nullptr),
          fftReady_(false)
    {
    }

    ~FeatureCalculator()
    {
        cleanup();
    }


    bool setup(float sampleRate)
    {
        sampleRate_ = sampleRate;
        cleanup();

        if (fftSize_ <= 0)
            return false;

        fftInput_ = static_cast<float*>(fftwf_malloc(sizeof(float) * fftSize_));
        fftOutput_ = static_cast<fftwf_complex*>(fftwf_malloc(sizeof(fftwf_complex) * (fftSize_ / 2 + 1)));
        if (!fftInput_ || !fftOutput_)
        {
            cleanup();
            return false;
        }

        fftPlan_ = fftwf_plan_dft_r2c_1d(fftSize_, fftInput_, fftOutput_, FFTW_ESTIMATE);
        if (!fftPlan_)
        {
            cleanup();
            return false;
        }

        fftReady_ = true;
        return true;
    }

	

    // RMS calculation
    float computeRMS(const std::vector<float>& buffer) const
    {
        if (buffer.empty())
            return 0.0f;
		
        double sumSquares = 0.0;

        for (std::size_t i = 0; i < buffer.size(); ++i)
        {
            const double sample = static_cast<double>(buffer[i]);
            sumSquares += sample * sample;
        }

        return static_cast<float>(std::sqrt(sumSquares / static_cast<double>(buffer.size())));
    }

	
	
    // RMS in dB
    float computeRMSdB(
        const std::vector<float>& buffer) const
    {
        const float rms = computeRMS(buffer);
        const float minRMS = 1.0e-12f;
        return 20.0f * std::log10(std::max(rms, minRMS));
    }

	

    // FFT calculation
    bool computeFFT(const std::vector<float>& buffer)
    {
        if (!fftReady_)
            return false;

        if (buffer.size() < static_cast<std::size_t>(fftSize_))
        {
            return false;
        }

        constexpr float PI = 3.14159265358979323846f;
        for (int i = 0; i < fftSize_; ++i)
        {
            const float window = 0.5f * (1.0f - std::cos((2.0f * PI * static_cast<float>(i)) / static_cast<float>(fftSize_ - 1)));
            fftInput_[i] = buffer[i] * window;
        }

        fftwf_execute(fftPlan_);
        return true;
    }


    // FFT magnitude
    float getMagnitude(int bin) const
    {
        if (!fftReady_)
            return 0.0f;

        const int maxBin = fftSize_ / 2;

        if (bin < 0 || bin > maxBin)
            return 0.0f;

        const float real = fftOutput_[bin][0];
        const float imag = fftOutput_[bin][1];
        return std::sqrt(real * real + imag * imag);
    }


    float getBinFrequency(int bin) const
    {
        return static_cast<float>(bin) * sampleRate_ / static_cast<float>(fftSize_);
    }



	// dominant frequency
    float computeDominantFrequency() const
    {
        if (!fftReady_)
            return 0.0f;

        const int numberOfBins = fftSize_ / 2 + 1;
        if (numberOfBins <= 1)
            return 0.0f;

        int maxBin = 1;
        float maxMagnitude = getMagnitude(1);

        for (int bin = 2; bin < numberOfBins; ++bin)
        {
            const float magnitude = getMagnitude(bin);

            if (magnitude > maxMagnitude)
            {
                maxMagnitude = magnitude;
                maxBin = bin;
            }
        }

        return getBinFrequency(maxBin);
    }


	
    // spectral centroid
    float computeSpectralCentroid() const
    {
        if (!fftReady_)
            return 0.0f;

        const int numberOfBins = fftSize_ / 2 + 1;
        double weightedSum = 0.0;
        double magnitudeSum = 0.0;

        for (int bin = 1;
             bin < numberOfBins;
             ++bin)
        {
            const float magnitude = getMagnitude(bin);
            const float frequency = getBinFrequency(bin);

            weightedSum += static_cast<double>(frequency) * static_cast<double>(magnitude);
            magnitudeSum += static_cast<double>(magnitude);
        }

        if (magnitudeSum <= 0.0)
            return 0.0f;

        return static_cast<float>(weightedSum / magnitudeSum);
    }



    // spectral energy
    float computeSpectralEnergy() const
    {
        if (!fftReady_)
            return 0.0f;

        const int numberOfBins = fftSize_ / 2 + 1;
        double energy = 0.0;

        for (int bin = 1; bin < numberOfBins; ++bin)
        {
            const float magnitude = getMagnitude(bin);

            energy += static_cast<double>(magnitude) * static_cast<double>(magnitude);
        }
        return static_cast<float>(energy);
    }


    // energy within frequency band
    float computeBandEnergy(float lowFrequency, float highFrequency) const
    {
        if (!fftReady_)
            return 0.0f;
        if (highFrequency <= lowFrequency)
            return 0.0f;

        const int numberOfBins = fftSize_ / 2 + 1;
        double energy = 0.0;
        for (int bin = 1; bin < numberOfBins; ++bin)
        {
            const float frequency = getBinFrequency(bin);
            if (frequency >= lowFrequency && frequency < highFrequency)
            {
                const float magnitude = getMagnitude(bin);
                energy += static_cast<double>(magnitude) * static_cast<double>(magnitude);
            }
        }

        return static_cast<float>(energy);
    }


    // low band
    float computeLowBandEnergy() const
    {
        return computeBandEnergy(20.0f, 250.0f);
    }

    // mid band
    float computeMidBandEnergy() const
    {
        return computeBandEnergy(250.0f, 2000.0f);
    }

    // high band
    float computeHighBandEnergy() const
    {
        return computeBandEnergy(2000.0f, 10000.0f);
    }


    // getters
    int getFFTSize() const
    {
        return fftSize_;
    }

    float getSampleRate() const
    {
        return sampleRate_;
    }


    // cleanup
    void cleanup()
    {
        if (fftPlan_)
        {
            fftwf_destroy_plan(fftPlan_);
            fftPlan_ = nullptr;
        }

        if (fftInput_)
        {
            fftwf_free(fftInput_);
            fftInput_ = nullptr;
        }

        if (fftOutput_)
        {
            fftwf_free(fftOutput_);
            fftOutput_ = nullptr;
        }
        fftReady_ = false;
    }


private:
    int fftSize_;
    float sampleRate_;
    float* fftInput_;
    fftwf_complex* fftOutput_;
    fftwf_plan fftPlan_;
    bool fftReady_;
};

#endif 
