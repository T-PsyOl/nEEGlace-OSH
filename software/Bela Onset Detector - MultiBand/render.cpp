#include <Bela.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

#include <libraries/AudioFile/AudioFile.h>
#include <libraries/Scope/Scope.h>

#include "onsetdetector.h"
#include "startupLogger.h"
#include "computeFeatures.h"

Scope scope;

const std::string configFilename = "Config.txt";
const std::string logFile = "bela_startup_log.txt";

// configuration
float inputGain           = 43.0f;
float activationDuration  = 0.05f;
float refractoryPeriod    = 0.5f;
float toneFreq            = 200.0f;
double recordAudio        = 1;
double recordDuration     = 20.0;

// onset detector
OnsetDetectorParams detectorParams;
OnsetDetector detector;

// digital pin activation
const int digitalPin = 0;
int activationDurSamples = 0;
int activationCounter = 0;
int refractoryPeriodSamples = 0;
int refractoryCounter = 0;
int timeSinceLastOnset = 0;

// audio recording
std::vector<std::vector<float>> audioRecorder;
std::vector<int> digitalPinRecorder;
std::string audioFilename;
std::string markerFilename;
unsigned int recordingFrames = 0;

// feature extraction
const int FFT_SIZE = 512;
FeatureCalculator features(FFT_SIZE);
std::vector<float> audioBuffer(FFT_SIZE, 0.0f);
int audioBufferIndex = 0;
unsigned int audioBufferFilled = 0;
std::vector<float> featureWindow(FFT_SIZE, 0.0f);


// onset event logging
std::string csvFilename;
std::ofstream csvFile;
bool csvFileOpen = false;
unsigned int totalFrames = 0;
unsigned int onset_index = 0;

// event struct
struct OnsetEvent
{
    unsigned int onset_index;
    double onset_time;
    float rms;
    //float levelDb;
    //float dominantFrequency;
    float spectralCentroid;
    //float spectralEnergy;
    //float lowEnergy;
    //float midEnergy;
    //float highEnergy;
};


// event buffer
std::vector<OnsetEvent> onsetBuffer;
const int MAX_ONSET_EVENTS = 1000;

// CSV logging
double lastLogTime = 0.0;
const double logInterval = 1.0;

// function to generate filename
std::string generateFilename(const std::string& logFile)
{
    std::ifstream file(logFile);
    if (!file.is_open())
    {
        std::cout << "Cannot open: " << logFile << std::endl;
        return "";
    }

    std::string line;
    std::string featureFilename;

    while (std::getline(file, line))
    {
        if (line.rfind("Feature File:", 0) == 0)
        {
            featureFilename =
                line.substr(std::string("Feature File:").length());

            // remove leading whitespace
            featureFilename.erase(0, featureFilename.find_first_not_of(" \t"));
            // remove trailing whitespace
            featureFilename.erase(featureFilename.find_last_not_of(" \t\r\n") + 1);
        }
    }

    std::cout<< "Feature filename found: ["<< featureFilename<< "]"<< std::endl;
    return featureFilename;
}


// read configuration file
bool readConfig(const std::string& filename)
{
    std::ifstream f(filename);

    if (!f.is_open())
    {
        rt_printf("Cannot open config file — using defaults.\n");
        return false;
    }

    std::string line;

    while (std::getline(f, line))
    {
        std::istringstream iss(line);
        std::string key;
		
        if (!(iss >> key))
            continue;

        if (key == "inputGain")
        {
            iss >> inputGain;
        }

        else if (key == "activationDuration")
        {
            iss >> activationDuration;
        }

        else if (key == "refractoryPeriod")
        {
            iss >> refractoryPeriod;
        }

        else if (key == "toneFreq")
        {
            iss >> toneFreq;
        }

        else if (key == "recordAudio")
        {
            iss >> recordAudio;
        }

        else if (key == "recordDuration")
        {
            iss >> recordDuration;
        }

        else if (key == "svf_cutoff_Hz")
        {
            iss >> detectorParams.svf_cutoff_Hz;
        }

        else if (key == "svf_Q")
        {
            iss >> detectorParams.svf_Q;
        }

        else if (key == "threshBase")
        {
            for (int i = 0; i < 4; ++i)
                iss >> detectorParams.threshBase[i];
        }

        else if (key == "jumpFactor")
        {
            for (int i = 0; i < 4; ++i)
                iss >> detectorParams.jumpFactor[i];
        }

        else if (key == "decayConst")
        {
            for (int i = 0; i < 4; ++i)
                iss >> detectorParams.decayConst[i];
        }

        else if (key == "tauFast_ms")
        {
            for (int i = 0; i < 4; ++i)
                iss >> detectorParams.tauFast_ms[i];
        }

        else if (key == "tauSlow_ms")
        {
            for (int i = 0; i < 4; ++i)
                iss >> detectorParams.tauSlow_ms[i];
        }
    }

    f.close();

    return true;
}


void getFeatureWindow()
{
    if (audioBufferFilled < FFT_SIZE)
    {
        const int missing =
            FFT_SIZE - audioBufferFilled;

        // zero-pad the beginning
        for (int i = 0; i < missing; ++i)
            featureWindow[i] = 0.0f;

        // copy available samples
        for (unsigned int i = 0; i < audioBufferFilled; ++i)
        {
            int index = (audioBufferIndex - static_cast<int>(audioBufferFilled) + static_cast<int>(i)) % FFT_SIZE;
            if (index < 0)
                index += FFT_SIZE;
			
            featureWindow[missing + i] = audioBuffer[index];
        }
    }

    else
    {
        // buffer is full.
        for (int i = 0; i < FFT_SIZE; ++i)
        {
            int index = (audioBufferIndex + i) % FFT_SIZE;
            featureWindow[i] = audioBuffer[index];
        }
    }
}


// log onset events to CSV

void logEvents(BelaContext* context)
{
    if (!csvFileOpen)
        return;
    if (onsetBuffer.empty())
        return;

    double currentTime = static_cast<double>(totalFrames) / context->audioSampleRate;
    if (currentTime - lastLogTime < logInterval)
        return;

    for (const auto& event : onsetBuffer)
    {
        csvFile
            << std::fixed
            << std::setprecision(4)

            << event.onset_index << ","
            << event.onset_time << ","

            << std::setprecision(8)
            << event.rms << ","

            //<< std::setprecision(4)
            //<< event.levelDb << ","

            //<< event.dominantFrequency << ","
            << event.spectralCentroid << ","

            << std::setprecision(8)
            //<< event.spectralEnergy << ","
            //<< event.lowEnergy << ","
            //<< event.midEnergy << ","
            //<< event.highEnergy

            << "\n";
    }


    // Flush to disk
    csvFile.flush();
    lastLogTime = currentTime;
    //rt_printf("Logged %zu onset events to CSV at %.2f seconds\n", onsetBuffer.size(), currentTime);

    onsetBuffer.clear();
}


// setup function
bool setup(BelaContext* context, void* /*userData*/)
{
	// read config file
    readConfig(configFilename);
	
	// startup logger 
    appendStartupModeToFile();

	
    scope.setup(2, context->audioSampleRate);

    Bela_setAudioInputGain(0,inputGain);
    Bela_setAudioInputGain(1,inputGain);

    pinMode(context, 0, digitalPin, OUTPUT);

    activationDurSamples = static_cast<int>(context->audioSampleRate * activationDuration);
    refractoryPeriodSamples = static_cast<int>(context->audioSampleRate * refractoryPeriod);

	// initialise onset detector
    detector.setup(context->audioSampleRate, detectorParams);

	// check feature extraction call
    if (!features.setup(context->audioSampleRate))
    {
        rt_printf("Failed to initialize feature calculator\n");
        return false;
    }


    audioBuffer.assign(FFT_SIZE,0.0f);
    featureWindow.assign(FFT_SIZE,0.0f);
    audioBufferIndex = 0;
    audioBufferFilled = 0;

    // CSV file
    csvFilename =generateFilename(logFile) + ".csv";
    csvFile.open(csvFilename);

    if (csvFile.is_open())
    {
        csvFile
            << "onset_index,"
            << "onset_time,"
            << "rms,"
            //<< "level_dB,"
            //<< "dominant_frequency_Hz,"
            << "spectral_centroid_Hz\n";
            //<< "spectral_energy,"
            //<< "low_band_energy,"
            //<< "mid_band_energy,"
            //<< "high_band_energy\n";

        csvFile.flush();
        csvFileOpen = true;
        rt_printf("CSV file created: %s\n", csvFilename.c_str());
    }

    else
    {
        rt_printf("Warning: Could not open CSV file for writing.\n");
    }

    // Aadio recording setup
    if (recordAudio == 1)
    {
        audioFilename = generateFilename("audiofile") + ".wav";
        markerFilename = generateFilename("markerfile") + ".txt";

        rt_printf("Recording ON → %s\n",audioFilename.c_str());
    }

    else
    {
        rt_printf("Recording OFF\n");
    }


    // allocate recording buffers
    unsigned int numFrames = static_cast<unsigned int>(context->audioSampleRate * recordDuration);
    if (recordAudio == 1)
    {
        audioRecorder.resize(context->audioInChannels);
        digitalPinRecorder.resize(numFrames, 0);

        for (auto& ch : audioRecorder)
        {
            try
            {
                ch.resize(numFrames, 0.0f);
            }

            catch (std::exception& e)
            {
                fprintf(stderr, "Memory allocation error: %s\n", e.what());
                return false;
            }
        }
    }

    onsetBuffer.reserve(MAX_ONSET_EVENTS);
    lastLogTime = 0.0;
    return true;
}


// render function
void render(BelaContext* context, void* /*userData*/)
{
    static float phase = 0.0f;
    const float phaseInc = 2.0f * 3.14159265358979323846f * toneFreq / context->audioSampleRate;

    // process audio frame
    for (unsigned int n = 0; n < context->audioFrames;++n)
    {
        float micL = audioRead(context, n, 0);
        float micR = audioRead(context, n, 1);

        scope.log(micL, micR);

        // add current sample to circular audio buffer
        audioBuffer[audioBufferIndex] = micL;
        audioBufferIndex++;

        if (audioBufferIndex >= FFT_SIZE)
            audioBufferIndex = 0;

        if (audioBufferFilled < FFT_SIZE)
            ++audioBufferFilled;

        // Onset detection
        bool onset = detector.processSample(micL);
        double onset_time = static_cast<double>(totalFrames + n) / context->audioSampleRate;
        
		if (onset && refractoryCounter <= 0)
        {
            const double timeSinceOnsetSeconds = static_cast<double>(timeSinceLastOnset) / context->audioSampleRate;

            rt_printf("Onset Detected at %.4f s | " 
					  "threshold: %.4f | "
					  "time since last onset: %.4f s\n",
					  onset_time,
					  detector.getThreshold(0),
					  timeSinceOnsetSeconds
					 );

			// digital output activation
            activationCounter = activationDurSamples;
            digitalWrite(context, n, digitalPin, HIGH);

            ++onset_index;

			// get event features 
            getFeatureWindow();
            // calculate RMS
			const float rms = features.computeRMS(featureWindow);
            // calculate FFT
            const bool fftOK = features.computeFFT(featureWindow);
            // float dominantFrequency = 0.0f;
            float spectralCentroid = 0.0f;
            // float spectralEnergy = 0.0f;
            // float lowEnergy = 0.0f;
            // float midEnergy = 0.0f;
            // float highEnergy = 0.0f;
            if (fftOK)
            {
                //dominantFrequency = features.computeDominantFrequency();
                spectralCentroid = features.computeSpectralCentroid();
                //spectralEnergy = features.computeSpectralEnergy();
                // lowEnergy = features.computeLowBandEnergy();
                // midEnergy = features.computeMidBandEnergy();
                // highEnergy = features.computeHighBandEnergy();
            }

            // store event + features
            OnsetEvent event;
            event.onset_index = onset_index;
            event.onset_time = onset_time;
            event.rms = rms;
            // event.levelDb = levelDb;
            // event.dominantFrequency = dominantFrequency;
            event.spectralCentroid = spectralCentroid;
            // event.spectralEnergy = spectralEnergy;
            // event.lowEnergy = lowEnergy;
            // event.midEnergy = midEnergy;
            // event.highEnergy = highEnergy;

            onsetBuffer.push_back(event);
            if (onsetBuffer.size() >MAX_ONSET_EVENTS)
            {
                onsetBuffer.erase(onsetBuffer.begin());
            }

            // refractory period
            refractoryCounter = refractoryPeriodSamples;
            timeSinceLastOnset = 0;
        }


        // ----------------------------------------------------
        // Refractory and timing counters
        // ----------------------------------------------------

        if (refractoryCounter > 0) --refractoryCounter;
        ++timeSinceLastOnset;

		// feedback tone 
        float audioOut = 0.0f;
        if (activationCounter > 0)
        {
            --activationCounter;
            if (activationCounter == 0)
            {
                digitalWrite(context, n, digitalPin, LOW);
            }

            audioOut = std::sin(phase);
            phase += phaseInc;


            if (phase >= 2.0f * 3.14159265358979323846f)
            {
                phase -= 2.0f * 3.14159265358979323846f;
            }
        }

        else
        {
            phase = 0.0f;
        }

        audioWrite(context, n, 0, audioOut);
        audioWrite(context, n, 1, audioOut);


        // audio recording
        if (recordAudio == 1)
        {
            audioRecorder[0][recordingFrames] = micL;
			audioRecorder[1][recordingFrames] = micR;

            digitalPinRecorder[recordingFrames] = digitalRead(context, n, digitalPin);
            ++recordingFrames;
			
            // stop when buffer is full
            if (recordingFrames >= audioRecorder[0].size())
            {
                Bela_requestStop();
                return;
            }
        }
    }

    totalFrames += context->audioFrames;
    logEvents(context);
}


// cleanup
void cleanup(BelaContext* context, void* /*userData*/)
{

    if (recordAudio == 1)
    {
        for (auto& ch : audioRecorder) 
			ch.resize(recordingFrames);

        digitalPinRecorder.resize(recordingFrames);
    }


    // save audio
    if (recordAudio == 1)
    {
        AudioFileUtilities::write(audioFilename, audioRecorder, context->audioSampleRate);
        rt_printf("Audio saved → %s\n", audioFilename.c_str());
        std::ofstream mf(markerFilename);

        if (mf.is_open())
        {
            for (const auto& s : digitalPinRecorder)
            {
                mf << s << "\n";
            }
        }
        rt_printf("Markers saved → %s\n",markerFilename.c_str());
    }


    if (csvFileOpen && !onsetBuffer.empty())
    {
        for (const auto& event : onsetBuffer)
        {
            csvFile
                << std::fixed
                << std::setprecision(4)

                << event.onset_index << ","
                << event.onset_time << ","
				
                << std::setprecision(8)
                << event.rms << ","

                << event.spectralCentroid << ","
                << "\n";
        }

        csvFile.flush();
        rt_printf("Final %zu onset events logged to CSV\n",onsetBuffer.size());
    }

    // close CSV
    if (csvFileOpen)
    {
        csvFile.close();
        csvFileOpen = false;
        rt_printf("CSV file saved: %s\n", csvFilename.c_str());
    }

    features.cleanup();
}
