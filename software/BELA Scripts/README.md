# Audio Event Detection for nEEGlace

This folder contains the current audio event detection code for the nEEGlace prototype.

The general goal is to use microphone input to detect acoustic events in real time and generate markers that can be synchronized with EEG or other physiological recordings. 
In the current implementation, stereo microphone input is acquired by the Bela board. The audio signal is processed online, and an event marker is generated when the signal energy exceeds a predefined threshold.

At this stage, the implementation should be understood as a simple baseline detector. It demonstrates the basic processing pipeline from microphone input to event marker output, but it is not yet a full audio event classifier.

## Concept

The intended processing chain is:

```text
Stereo microphone input
        ↓
Bela audio acquisition
        ↓
Buffer-based audio processing
        ↓
Event detection
        ↓
Digital trigger output
        ↓
Synchronization with EEG / physiological data
```

The broader motivation is to add acoustic context to nEEGlace recordings. In real-world EEG recordings, it is often important to know when relevant sounds occurred in the environment. 
Detecting such events can help annotate recordings, identify time points of interest, and relate neural activity to events in the acoustic scene.

## Current implementation

The current script implements a simple energy-based onset detector.

Audio is read from the Bela audio inputs. Although both left and right microphone channels are acquired and visualized, the current detection logic uses one input channel for event detection. 
Samples are stored in a circular buffer. After a defined hop size, the energy of the current buffer is calculated as the mean squared amplitude of the samples.

If the energy exceeds a predefined threshold and the detector is not in its refractory period, an onset is detected. 
The script then activates a digital output pin for a short duration. This digital pulse can be used as an event marker.

The basic logic is:

```text
Read audio sample
        ↓
Store sample in buffer
        ↓
Every hopSize samples:
    compute buffer energy
        ↓
If energy > threshold and refractory period has passed:
    detect onset
    activate digital output pin
    optionally generate audio pulse
    optionally record audio and marker trace
```

## Parameters

The current detector uses the following main parameters:

| Parameter            | Description                                                   |
| -------------------- | ------------------------------------------------------------- |
| `bufferSize`         | Number of samples stored in the buffer for energy calculation |
| `hopSize`            | Number of samples between consecutive energy calculations     |
| `energyThreshold`    | Threshold used for detecting an onset                         |
| `refractoryPeriod`   | Minimum time between two detected events                      |
| `activationDuration` | Duration for which the digital output pin is activated        |
| `inputGain`          | Input gain for the microphones                                |
| `recordAudio`        | Enables or disables audio and marker recording                |
| `recordDuration`     | Duration of the recording in seconds                          |

Some parameters can be set through a `config.txt` file.

Example:

```text
energyThreshold 0.001
recordAudio 1
recordDuration 20
inputGain 55
```

If the configuration file cannot be read, the script uses the default values defined in the source code.

## Outputs

The script can produce three types of output.

### 1. Digital trigger

When an onset is detected, a digital output pin is set to `HIGH` for a short period. This can be used as an event marker for synchronization with EEG or other recording systems.

### 2. Audio pulse

During trigger activation, the script can write a short sine tone to the audio output. This is mainly useful for testing and debugging the timing of detected events.

### 3. Optional recording

If recording is enabled, the script stores the audio signal and the marker trace. At the end of the recording, the audio is saved as a `.wav` file and the marker trace is saved as a `.txt` file.

## Current status

The current implementation is an **audio event detector**, not yet an **audio event classifier**.

It detects whether an acoustic event has occurred, but it does not yet assign semantic labels to events. For example, it does not distinguish between speech, impact sounds, mechanical noise, movement artefacts, or other environmental sounds.

The current detector is useful as a first prototype because it establishes the basic real-time pipeline:

```text
microphone input → detection → trigger output → optional recording
```

## Limitations

The current implementation has several limitations:

* Detection is based only on broadband signal energy.
* The threshold is fixed and may need manual tuning for each environment.
* The detector currently uses one audio channel for event detection, although stereo input is available.
* The detector does not classify event types.
* Loud background noise may cause false detections.
* Quiet but relevant events may be missed.
* Slow changes in overall loudness may affect detection reliability.
* No spectral, temporal, or spatial features are currently used.
* The detector has not yet been systematically evaluated against manually annotated events.

## Possible future improvements

Several extensions could improve the robustness and usefulness of the system.

### Adaptive thresholding
### Stereo-based detection
### Spectral features
### Event classification
### Offline evaluation
