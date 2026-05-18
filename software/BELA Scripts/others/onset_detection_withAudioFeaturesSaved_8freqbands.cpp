/**
 * Audio onset detection using energy and spectral features
 * ---------------------------------------------------------
 * Optimized version with logging every second.
 * No real-time I/O in render(). Underruns avoided.
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
#include <fftw3.h>  // Required for FFT

// Create a scope object with 2 channels to visualize the audio signal
Scope scope;

// Define the configuration file name
const std::string configFilename = "config.txt"; 

// Define the configuration parameters
int bufferSize = 512;                           // Number of samples stored in buffer for energy calculation
int hopSize = 256;                              // Interval at which buffer is processed
float refractoryPeriod = 0.5;                  // Refractory period (sec) - time between onset detections
float activationDuration = 0.05;               // Duration to activate the digital output pin after onset detection (sec)
float inputGain = 30;                          // Input gain for the microphones    
float energyThreshold = 0.05;                  // Threshold for detecting an onset
float toneFreq = 200.0;                        // Frequency of the tone to be generated

// Define state variables to keep track of the audio processing
std::vector<float> audioBuffer(bufferSize, 0.0f); // Buffer to store audio samples
int bufferIndex = 0;                           // Current position in audioBuffer
int hopCounter = 0;                            // Counter to track samples processed since last energy calculation 
int refractoryPeriodSamples;                   // Refractory period in samples
int refractoryCounter = 0;                     // Counter to track refractory period
int timeSinceLastOnset = 0;                    // Counter to track samples since last onset
int activationDurationSamples;                 // Activation duration in samples
int activationCounter = 0;                     // Counter to track how long digital output is activated
const int digitalPin = 0;                      // Digital pin number to activate

// Define variables for recording audio
std::vector<std::vector<float>> audioRecorder;  // Buffer to save audio
std::string audioFilename;                     // Filename to save audio
std::vector<int> digitalPinRecorder;           // Buffer to save digital pin states
std::string markerFilename;                    // Filename to save markers
double recordAudio = 0;                        // Flag to enable or disable audio recording
double recordDuration = 20;                    // Recording duration in seconds
unsigned int recordingFrames = 0;              // Counter to track frames recorded
const int RECORD_BUFFER_SIZE = 512;           // Define the buffer size for audio recording

// Define the record buffer
std::vector<float> recordBuffer;
int recordBufferIndex = 0;

// Define variables for CSV logging
std::string csvFilename;
std::ofstream csvFile;
bool csvFileOpen = false;
unsigned int totalFrames = 0;

// Define a struct to store onset events
struct OnsetEvent {
    double timestamp;          // Timestamp of the onset event
    float energy;              // Energy of the onset event
    float rms;                 // RMS value of the onset event
    float freqContent;         // Frequency content of the onset event
    std::vector<float> bandEnergies;
};

// Define a vector to store onset events
std::vector<OnsetEvent> onsetBuffer;
const int MAX_ONSET_EVENTS = 1000;             // Maximum number of onset events to store

// Define variables for logging every second
double lastLogTime = 0.0;                      // Last time we logged (in seconds)
const double logInterval = 1.0;                // Log every 1 second

// Define variables for FFT calculations
fftwf_plan fftPlan;                            // FFT plan (real-to-complex)
std::vector<float> fftBuffer;                  // Complex buffer: real + imag (size = 2 * bufferSize)

// Frequency bands (in Hz) in 1/3-octave bands
std::vector<std::pair<float, float>> frequencyBands = {
    {20, 40},    	// Band 1: Sub bass (for music impact)
    {40, 80},   	// Band 2: Bass
    {80, 160},  	// Band 3: Low mid
    {160, 320},  	// Band 4: Lower mid
    {320, 640}, 	// Band 5: Mid
    {640, 1280}  	// Band 6: Upper Mid
    {1280, 2560}	// Band 7: High
    {2560, 8000}	// Band 8: Treble
};

// Buffer to store band energies
std::vector<float> bandEnergies(8, 0.0f);

// Function to generate a unique filename (adds the current timestamp)
std::string generateFilename(const std::string& baseFilename) {
    // Get the current time
    std::time_t now = std::time(nullptr);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", std::localtime(&now));
    // Return the base filename with the timestamp appended
    return baseFilename + "_" + timestamp;
}

// Function to read from config file 
bool readConfig(const std::string& filename) {
    // Open the config file
    std::ifstream configFile(filename);
    if (!configFile.is_open()) {
        // If the file cannot be opened, print an error message and return false
        rt_printf("Cannot open the config file\n");
        return false;
    }

    // Read the config file line by line
    std::string line;
    while (std::getline(configFile, line)) {
        // Parse the line into key-value pairs
        std::istringstream iss(line);
        std::string key;
        if (iss >> key) {
            // Check the key and update the corresponding variable
            if (key == "energyThreshold") {
                if (!(iss >> energyThreshold)) {
                    // If the value cannot be parsed, print an error message and return false
                    rt_printf("Error reading energy threshold value\n");
                    return false;
                }
            } else if (key == "recordAudio") {
                if (!(iss >> recordAudio)) {
                    // If the value cannot be parsed, print an error message and return false
                    rt_printf("Error reading recording on/off value\n");
                    return false;
                }
            } else if (key == "recordDuration") {
                if (!(iss >> recordDuration)) {
                    // If the value cannot be parsed, print an error message and return false
                    rt_printf("Error reading recording duration value\n");
                    return false;
                }
            } else if (key == "inputGain") {
                if (!(iss >> inputGain)) {
                    // If the value cannot be parsed, print an error message and return false
                    rt_printf("Error reading input gain value\n");
                    return false;
                }
            }
        }
    }
    // Close the config file
    configFile.close();
    // Return true if the config file was read successfully
    return true;
}

// Function to calculate energy of a buffer
float calculateEnergy(const std::vector<float>& buffer) {
    // Initialize the energy to 0
    float energy = 0.0f;
    // Calculate the energy by summing the squares of the samples
    for (const auto& sample : buffer) {
        energy += sample * sample;
    }
    // Return the energy divided by the number of samples
    return energy / buffer.size();
}

// Modified function to compute spectral centroid and band energies
void computeSpectralFeatures(const std::vector<float>& buffer, int sampleRate,
                            float& spectralCentroid, std::vector<float>& bandEnergies) {
    const int N = buffer.size();

    // Copy the real data to the FFT buffer
    for (int i = 0; i < N; ++i) {
        fftBuffer[i] = buffer[i];
    }

    // Zero out the imaginary part of the FFT buffer
    for (int i = 0; i < N; ++i) {
        fftBuffer[N + i] = 0.0f;
    }

    // Execute the FFT
    fftwf_execute(fftPlan);

    // Compute the magnitude spectrum
    std::vector<float> magnitude(N/2, 0.0f);
    for (int i = 0; i < N/2; ++i) {
        float real = fftBuffer[i * 2];
        float imag = fftBuffer[i * 2 + 1];
        magnitude[i] = std::sqrt(real * real + imag * imag);
    }

    // Compute the spectral centroid
    float sum = 0.0f;
    float weightedSum = 0.0f;
    for (int i = 0; i < N/2; ++i) {
        float freq = (float)i * sampleRate / N;
        sum += magnitude[i];
        weightedSum += freq * magnitude[i];
    }
    spectralCentroid = (sum == 0.0f) ? 0.0f : weightedSum / sum;

    // Compute band energies
    for (int band = 0; band < 6; ++band) {
        bandEnergies[band] = 0.0f;
        float lowFreq = frequencyBands[band].first;
        float highFreq = frequencyBands[band].second;

        // Find the FFT bins corresponding to this frequency range
        int lowBin = std::max(1, (int)(lowFreq * N / sampleRate));
        int highBin = std::min(N/2 - 1, (int)(highFreq * N / sampleRate));

        // Sum the energy in this band
        for (int i = lowBin; i <= highBin; ++i) {
            bandEnergies[band] += magnitude[i] * magnitude[i];
        }

        // Normalize by the number of bins
        bandEnergies[band] /= (highBin - lowBin + 1);
    }
}

// Function to log onset events to CSV every second
void logEvents(BelaContext *context) {
    // Check if there are any onset events to log
    if (onsetBuffer.empty()) return;

    // Get the current time
    // double currentTime = (double)context->audioFrames / context->audioSampleRate;
	double currentTime = (double)totalFrames / context->audioSampleRate;
    // Check if it's time to log (every second)
    if (currentTime - lastLogTime < logInterval) return;

    // Write all onset events to the CSV file
    for (const auto& event : onsetBuffer) {
        csvFile << std::fixed << std::setprecision(6)
                << event.timestamp << ","
                << 1 << ","  // detection flag
                << event.rms << ","
                << event.freqContent;
	for (int i = 0; i < 8; ++i) {
        	csvFile << "," << event.bandEnergies[i];
   	}
    csvFile << "\n";
    }

    // Flush the CSV file to disk
    csvFile.flush();
    // Update the last log time
    lastLogTime = currentTime;

    // Print a message to indicate that onset events have been logged
    rt_printf("Logged %zu onset events to CSV at %.2f seconds\n", onsetBuffer.size(), currentTime);

    // Clear the onset buffer after logging
    onsetBuffer.clear();
}

// Function to setup the audio processing
bool setup(BelaContext *context, void *userData) {
    // Setup the scope object
    scope.setup(2, context->audioSampleRate);

    // Set the audio input gain
    Bela_setAudioInputGain(0, inputGain);
    Bela_setAudioInputGain(1, inputGain);

    // Calculate the refractory period in samples
    refractoryPeriodSamples = context->audioSampleRate * refractoryPeriod;
    // Calculate the activation duration in samples
    activationDurationSamples = context->audioSampleRate * activationDuration;

    // Set the digital pin mode to output
    pinMode(context, 0, digitalPin, OUTPUT);

    // Read the config file
    if (!readConfig(configFilename)) {
        // If the config file cannot be read, use default values
        rt_printf("Using default energy threshold: %f\n", energyThreshold);
        rt_printf("Using default recording duration: %f\n", recordDuration);
        rt_printf("Using default input gain: %f\n", inputGain);
    } else {
        // If the config file can be read, use the values from the file
        rt_printf("Using energy threshold from config: %f\n", energyThreshold);
        rt_printf("Using recording duration from config: %f\n", recordDuration);
        rt_printf("Using input gain from config: %f\n", inputGain);
    }

    // Initialize the FFT buffer and plan
    fftBuffer.resize(2 * bufferSize);
    fftPlan = fftwf_plan_dft_r2c_1d(bufferSize, fftBuffer.data(), (fftwf_complex*)fftBuffer.data(), FFTW_ESTIMATE);

	// CSV File to save Audio Featues
	// Generate a unique filename for the CSV file
	csvFilename = generateFilename("audio_features") + ".csv";
	// Open the CSV file for writing
	csvFile.open(csvFilename);
	if (csvFile.is_open()) {
		// Write the header to the CSV file
		csvFile << "timestamp,detection,RMS,frequency_content, band1, band2, band3, band4, band5, band6, band7, band8\n";
		csvFile.flush();
		csvFileOpen = true;
		rt_printf("CSV file created: %s\n", csvFilename.c_str());
	} else {
		// If the CSV file cannot be opened, print an error message
		rt_printf("Warning: Could not open CSV file for writing.\n");
	}

    // Setup audio recording
    if (recordAudio == 1) {
        // Generate a unique filename for the audio file
        audioFilename = generateFilename("audiofile") + ".wav";
        rt_printf("Audio recording is ON. Recording to file: %s\n", audioFilename.c_str());

        // Initialize the record buffer
        recordBuffer.resize(RECORD_BUFFER_SIZE * context->audioInChannels, 0.0f);
		
        // Generate a unique filename for the marker file
        markerFilename = generateFilename("markerfile") + ".txt";
        rt_printf("Marker file: %s\n", markerFilename.c_str());

        // Calculate the number of frames to record
        unsigned int numFrames = context->audioSampleRate * recordDuration;
        // Initialize the audio recorder buffer
        audioRecorder.resize(context->audioInChannels);
        digitalPinRecorder.resize(numFrames);
        try {
            // Resize the audio recorder buffer to the correct size
            for (auto& c : audioRecorder)
                c.resize(numFrames);
        } catch (std::exception& e) {
            // If an error occurs, print an error message and return false
            fprintf(stderr, "Error while allocating memory.\n");
            return false;
        }
    } else {
        // If audio recording is not enabled, print a message
        rt_printf("Audio recording is OFF\n");
    }

    // Reserve space for the onset buffer
    onsetBuffer.reserve(MAX_ONSET_EVENTS);
    for (auto& event : onsetBuffer) {
        event.bandEnergies.resize(8, 0.0f);
    }
    // Initialize the last log time
    lastLogTime = 0.0;

    // Return true to indicate that setup was successful
    return true;
}

// Function to render new audio samples
void render(BelaContext *context, void *userData) {
    // Initialize the phase and phase increment for the tone generator
    static float phase = 0.0f;
    float phaseIncrement = 2.0f * M_PI * toneFreq / context->audioSampleRate;
    // Initialize the total frames counter
    //static unsigned int totalFrames = 0;

    // Process each audio frame
    for (unsigned int n = 0; n < context->audioFrames; ++n) {
        // Read the audio input
        float micInputL = audioRead(context, n, 0);
        float micInputR = audioRead(context, n, 1);
        // Log the audio input to the scope
        scope.log(micInputL, micInputR);

        // Read the current audio sample
        float currentSample = audioRead(context, n, 0);
        // Store the current sample in the audio buffer
        audioBuffer[bufferIndex] = currentSample;
        // Increment the buffer index
        bufferIndex = (bufferIndex + 1) % bufferSize;

        // Increment the hop counter
        hopCounter++;
        // Check if it's time to process the audio buffer
        if (hopCounter >= hopSize) {
            // Reset the hop counter
            hopCounter = 0;

            // Calculate the energy of the audio buffer
            float energy = calculateEnergy(audioBuffer);
            // Calculate the RMS value of the audio buffer
            float rms = std::sqrt(energy);
            // Calculate the spectral centroid of the audio buffer
            float freqContent;
            computeSpectralFeatures(audioBuffer, context->audioSampleRate, freqContent, bandEnergies);
            // Calculate the timestamp of the onset event
            double timestamp = (double)(totalFrames + n) / context->audioSampleRate;

            // Check if an onset has been detected
            int detection = (energy >= energyThreshold && refractoryCounter <= 0) ? 1 : 0;

            // If an onset has been detected, add it to the onset buffer
            if (detection) {
		rt_printf("Onset detected! Energy: %f\n", energy);
                OnsetEvent event;
   		event.timestamp = timestamp;
		event.energy = energy;
		event.rms = rms;
 		event.freqContent = freqContent;
		event.bandEnergies = bandEnergies;
		onsetBuffer.push_back(event);

                // If the onset buffer is full, remove the oldest onset event
                if (onsetBuffer.size() > MAX_ONSET_EVENTS) {
                    onsetBuffer.erase(onsetBuffer.begin());
                }

                // Set the refractory counter
                refractoryCounter = refractoryPeriodSamples;
                // Set the activation counter
                activationCounter = activationDurationSamples;
                // Activate the digital output pin
                digitalWrite(context, n, digitalPin, HIGH);
            }

            // Decrement the refractory counter
            if (refractoryCounter > 0) {
                refractoryCounter -= hopSize;
                // If the refractory counter is negative, set it to 0
                if (refractoryCounter < 0) refractoryCounter = 0;
            }
            // Decrement the activation counter
            if (activationCounter > 0) {
                activationCounter--;
                // If the activation counter is 0, deactivate the digital output pin
                if (activationCounter == 0) digitalWrite(context, n, digitalPin, LOW);
            }
        }

        // Generate the tone output
        float out = sinf(phase);
        phase += phaseIncrement;
        // If the phase exceeds 2*pi, reset it to 0
        if (phase >= 2.0f * M_PI) phase -= 2.0f * M_PI;
        // Write the tone output to the audio output
        audioWrite(context, n, 0, out);
        audioWrite(context, n, 1, out);

        // Record the audio and digital pin state
         if (recordAudio == 1) {
	        // Read the audio input
	        float micInputL = audioRead(context, n, 0);
	        float micInputR = audioRead(context, n, 1);
	
	        // Store the audio data in the record buffer
	        recordBuffer[recordBufferIndex * context->audioInChannels] = micInputL;
	        recordBuffer[recordBufferIndex * context->audioInChannels + 1] = micInputR;
	        recordBufferIndex++;
	
	        // If the record buffer is full, write it to the file
	        if (recordBufferIndex >= RECORD_BUFFER_SIZE) {
	            // Write the record buffer to the file
	            // For now, we'll just print the buffer to the console
	            // In a real application, you'd use a library like AudioFileUtilities to write the buffer to a file
	            for (int i = 0; i < RECORD_BUFFER_SIZE * context->audioInChannels; i++) {
	                rt_printf("%f ", recordBuffer[i]);
	            }
	            rt_printf("\n");
	
	            // Reset the record buffer index
	            recordBufferIndex = 0;
	        }
	    }
    }

    // Increment the total frames counter
    totalFrames += context->audioFrames;

    // Log the onset events to the CSV file every second
    logEvents(context);
}

// Function to cleanup the audio processing
void cleanup(BelaContext *context, void *userData) {
    // Resize the audio recorder buffer to the correct size
    for (auto& i : audioRecorder) i.resize(recordingFrames);
    // Resize the digital pin recorder buffer to the correct size
    digitalPinRecorder.resize(recordingFrames);

    // If audio recording is enabled, save the recorded audio to a file
    if (recordAudio == 1) {
        // Save the recorded audio to a file
        AudioFileUtilities::write(audioFilename, audioRecorder, context->audioSampleRate);
        rt_printf("Audio recording saved\n");

        // Save the digital pin states to a file
        std::ofstream markerFile(markerFilename);
        if (markerFile.is_open()) {
            // Write the digital pin states to the file
            for (const auto& state : digitalPinRecorder) {
                markerFile << state << "\n";
            }
            markerFile.close();
        }
    }

    // If there are any remaining onset events, log them to the CSV file
    if (csvFileOpen && !onsetBuffer.empty()) {
        // Write the remaining onset events to the CSV file
        for (const auto& event : onsetBuffer) {
            csvFile << std::fixed << std::setprecision(6)
                    << event.timestamp << ","
                    << 1 << ","
                    << event.rms << ","
                    << event.freqContent 
	for (int i = 0; i < 8; ++i) {
            csvFile << "," << event.bandEnergies[i];
        }
        csvFile << "\n";
        }
        csvFile.flush();
        rt_printf("Final %zu onset events logged to CSV\n", onsetBuffer.size());
    }

    // If the CSV file is open, close it
    if (csvFileOpen) {
        csvFile.close();
        rt_printf("CSV file saved: %s\n", csvFilename.c_str());
    }

    // If the FFT plan is not null, destroy it
    if (fftPlan) {
        fftwf_destroy_plan(fftPlan);
    }
}