/**
Audio onset detection using energy features
-------------------------------------------
The script reads audio samples (from one input), calculates energy,
and logs onset events to a CSV file with timestamp, detection flag, and RMS.
*/

#include <Bela.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <libraries/AudioFile/AudioFile.h>
#include <libraries/Biquad/Biquad.h>
#include <algorithm>
#include <ctime>
#include <libraries/Scope/Scope.h>

// Create a scope object with 2 channels
Scope scope;

// config file
const std::string configFilename = "config.txt";

// configuration parameters
int bufferSize = 512;                           // num of samples stored in buffer for energy calculation
int hopSize = 256;                              // interval at which buffer is processed
float refractoryPeriod = 0.5;                  // refractory period (sec)
float activationDuration = 0.05;               // duration to activate the digital output pin after onset detection (sec)
float inputGain = 30;                          // input gain for the microphones
float energyThreshold = 0.05;                  // threshold for detecting an onset
float toneFreq = 200.0;

// state variables
std::vector<float> audioBuffer(bufferSize, 0.0f);
int bufferIndex = 0;                           // current position in audioBuffer
int hopCounter = 0;                            // to track samples processed since last energy calculation
int refractoryPeriodSamples;
int refractoryCounter = 0;                     // to track refractory period
int timeSinceLastOnset = 0;                    // to track samples since last onset
int activationDurationSamples;
int activationCounter = 0;                     // to track how long digital output is activated
const int digitalPin = 0;                      // digital pin number to activate

// recording audio variables
std::vector<std::vector<float>> audioRecorder;  // variable to save audio
std::string audioFilename;                     // filename to save audio
std::vector<int> digitalPinRecorder;           // variable to save digital pin states for the marker events
std::string markerFilename;                    // filename to save markers from the digital pin
double recordAudio = 0;                        // recording on/off
double recordDuration = 20;                    // recording duration in sec
unsigned int recordingFrames = 0;              // to track the frames recorded

// CSV logging variables
std::string csvFilename;                       // filename to save the CSV data
std::ofstream csvFile;                         // output file stream to write to the CSV file 
bool csvFileOpen = false;                      // flag to indicate whether the CSV file is open

// function to generate a unique filename (adds the current timestamp)
std::string generateFilename(const std::string& baseFilename){
    std::time_t now = std::time(nullptr);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", std::localtime(&now));
    return baseFilename + "_" + timestamp;
}

// function to read from config file
bool readConfig(const std::string& filename){
    std::ifstream configFile(filename);
    if(!configFile.is_open()){
        rt_printf("Cannot open the config file\n");
        return false;
    }

    std::string line;
    while(std::getline(configFile, line)){
        std::istringstream iss(line);
        std::string key;
        if(iss >> key){
            if(key == "energyThreshold"){
                if(!(iss >> energyThreshold)){
                    rt_printf("Error reading energy threshold value\n");
                    return false;
                }
            } else if(key == "recordAudio"){
                if(!(iss >> recordAudio)){
                    rt_printf("Error reading recording on/off value\n");
                    return false;
                }
            } else if(key == "recordDuration"){
                if(!(iss >> recordDuration)){
                    rt_printf("Error reading recording duration value\n");
                    return false;
                }
            } else if(key == "inputGain"){
                if(!(iss >> inputGain)){
                    rt_printf("Error reading input gain value\n");
                    return false;
                }
            }
        }
    }
    configFile.close();
    return true;
}

// function to calculate energy of a buffer
float calculateEnergy(const std::vector<float>& buffer) {
    float energy = 0.0f;
    for (const auto& sample : buffer) {
        energy += sample * sample;
    }
    return energy / buffer.size();
}

// function to setup
bool setup(BelaContext *context, void *userData) {
    // Initialize scope with 2 channels at the audio sample rate
    scope.setup(2, context->audioSampleRate);

    // Set input gain
    Bela_setAudioInputGain(0, inputGain);
    Bela_setAudioInputGain(1, inputGain);

    // Convert time to samples
    refractoryPeriodSamples = context->audioSampleRate * refractoryPeriod;
    activationDurationSamples = context->audioSampleRate * activationDuration;

    // Set digital pin as output
    pinMode(context, 0, digitalPin, OUTPUT);

    // Read config file
    if (!readConfig(configFilename)) {
        rt_printf("Using default energy threshold: %f\n", energyThreshold);
        rt_printf("Using default recording duration: %f\n", recordDuration);
        rt_printf("Using default input gain: %f\n", inputGain);
    } else {
        rt_printf("Using energy threshold from config: %f\n", energyThreshold);
        rt_printf("Using recording duration from config: %f\n", recordDuration);
        rt_printf("Using input gain from config: %f\n", inputGain);
    }

    // Audio recording setup
    if (recordAudio == 1) {
        audioFilename = generateFilename("audiofile") + ".wav";
        rt_printf("Audio recording is ON. Recording to file: %s\n", audioFilename.c_str());

        markerFilename = generateFilename("markerfile") + ".txt";
        rt_printf("Marker file: %s\n", markerFilename.c_str());

        // CSV file setup
        csvFilename = generateFilename("onset_detection") + ".csv";               // generating filename for the CSV file
        csvFile.open(csvFilename);                                                // opening the CSV file
        if (csvFile.is_open()) {                                                  // Check if its successfully open
            csvFile << "timestamp,detection,RMS\n";                               // writes the header row to the CSV file
            csvFile.flush();                                                      // flushes the output buffer so its written immediately to the disk 
            csvFileOpen = true;                                                   // sets csvFileOpe true to indicate its open and ready for writing
            rt_printf("CSV file created: %s\n", csvFilename.c_str());             // message that the CSV file was successfully created
        } else {
            rt_printf("Warning: Could not open CSV file for writing.\n");         // message when it couldnt open the CSV file
        }
    } else {
        rt_printf("Audio recording is OFF\n");
    }

    // Allocate memory for audio recording
    unsigned int numFrames = context->audioSampleRate * recordDuration;
    audioRecorder.resize(context->audioInChannels);
    digitalPinRecorder.resize(numFrames);
    try {
        for (auto& c : audioRecorder)
            c.resize(numFrames);
    } catch (std::exception& e) {
        fprintf(stderr, "Error while allocating memory.\n");
        return false;
    }

    return true;
}

// function to render new audio samples
void render(BelaContext *context, void *userData) {
    static float phase = 0.0f;
    float phaseIncrement = 2.0f * M_PI * toneFreq / context->audioSampleRate;

    for (unsigned int n = 0; n < context->audioFrames; ++n) {
        float micInputL = audioRead(context, n, 0);
        float micInputR = audioRead(context, n, 1);

        // Send to scope
        scope.log(micInputL, micInputR);

        // Read current sample
        float currentSample = audioRead(context, n, 0);

        // Update buffer
        audioBuffer[bufferIndex] = currentSample;
        bufferIndex = (bufferIndex + 1) % bufferSize;

        // Increment hop counter
        hopCounter++;
        if (hopCounter >= hopSize) {
            hopCounter = 0;

            // Calculate energy and RMS
            float energy = calculateEnergy(audioBuffer);
            float rms = std::sqrt(energy);

            // Get timestamp (in seconds) 
            double timestamp = (double)context->audioFramesElapsed / context->audioSampleRate;

            // Check for onset detection -> so we can store it inside the CSV file
            int detection = (energy >= energyThreshold && refractoryCounter <= 0) ? 1 : 0;

            // Log to CSV if open
            if (csvFileOpen) {                                                   // checks if csvFileOpen is true, so it is ready for writing
                csvFile << std::fixed << std::setprecision(6)                    // starts writing: "fixed" for fixed-point notation and "setprecision(6)" for 6 decimal places 
                        << timestamp << ","                                      // writes timestamp, detection and rms into the CSV file
                        << detection << ","
                        << rms << "\n";
                csvFile.flush();                                                 // flushes the output buffer of the CSV file, so its written immediately to disk
            }

            // Handle onset detection
            if (detection) {                                                     // changed condition to variable
                rt_printf("Onset detected! Energy: %f, RMS: %f\n", energy, rms);
                rt_printf("Time since last onset: %f seconds\n", timeSinceLastOnset / context->audioSampleRate);

                refractoryCounter = refractoryPeriodSamples;
                timeSinceLastOnset = 0;
                activationCounter = activationDurationSamples;
                digitalWrite(context, n, digitalPin, HIGH);
                rt_printf("Pin On\n");
            }

            // Handle refractory period
            if (refractoryCounter > 0) {
                refractoryCounter--;
            }

            // Increment time since last onset
            timeSinceLastOnset++;

            // Handle activation duration
            if (activationCounter > 0) {
                activationCounter--;
                if (activationCounter == 0) {
                    digitalWrite(context, n, digitalPin, LOW);
                    rt_printf("Pin Off\n");
                }
            }
        }

        // Audio output (tone)
        float out = sinf(phase);
        phase += phaseIncrement;
        if (phase >= 2.0f * M_PI) {
            phase -= 2.0f * M_PI;
        }

        audioWrite(context, n, 0, out);
        audioWrite(context, n, 1, out);

        // Record audio and digital pin state
        if (recordAudio == 1) {
            audioRecorder[0][recordingFrames] = currentSample;
            digitalPinRecorder[recordingFrames] = digitalRead(context, n, digitalPin);
            ++recordingFrames;
            if (recordingFrames >= audioRecorder[0].size()) {
                Bela_requestStop();
                return;
            }
        }
    }
}

// function to cleanup
void cleanup(BelaContext *context, void *userData) {
    // Resize recorded data
    for (auto& i : audioRecorder)
        i.resize(recordingFrames);
    digitalPinRecorder.resize(recordingFrames);

    // Save audio and markers
    if (recordAudio == 1) {
        AudioFileUtilities::write(audioFilename, audioRecorder, context->audioSampleRate);
        rt_printf("Audio recording saved\n");

        std::ofstream markerFile(markerFilename);
        if (markerFile.is_open()) {
            for (const auto& state : digitalPinRecorder) {
                markerFile << state << "\n";
            }
            markerFile.close();
        }
    }

    // Close CSV file
    if (csvFileOpen) {                                                             // Checks if the csvFileOpen is true
        csvFile.close();                                                           // if true close the CSV file
        rt_printf("CSV file saved: %s\n", csvFilename.c_str());                    // writes that the output is saved and gibes out the filename
    }
}