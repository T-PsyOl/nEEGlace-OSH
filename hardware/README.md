# nEEGlace Hardware
This directory documents the complete hardware setup of the nEEGlace system.

The hardware integrates EEG acquisition, high-quality audio recording,
real-time processing, and battery-powered operation into a single wearable
device.

## System Overview

The nEEGlace hardware is built around the following core components:

- [Bela GEM Stereo](https://eu.shop.bela.io/products/bela-gem-stereo) for real-time audio and control
   - We originally used the Bela Mini. However this is discontinued and we are moving to the Bela GEM Stereo  
- [OpenBCI Cyton (8-channel)](https://shop.openbci.com/products/cyton-biosensing-board-8-channel) or [Cyton + Daisy (16-channel)](https://shop.openbci.com/products/cyton-daisy-biosensing-boards-16-channel) for (ear)-EEG
- [**Roland CS-10EM binaural microphones**](https://proav.roland.com/de/products/proav_cs-10em/) for stereo audio
- **Battery Management System (BMS)** and rechargeable battery
- **Custom Bela Cape** for electrical integration
- **Wearable casing** and internal wiring

## Directory Structure

hardware/
├── BMS/
│   └── README.md
├── cape/
│   └── README.md
├── casing/
│   └── README.md
├── wiring/
│   └── README.md
└── README.md  ← you are here

Each subfolder documents one hardware module and its role in the overall system.

## Required Hardware Components

### 1. Processing and Control
- **Bela Mini**
  - Executes real-time audio and data acquisition code
  - Acts as the central control unit

- **Custom Bela Cape**
  - Interfaces Bela Mini with:
    - OpenBCI EEG amplifier
    - Roland CS-10EM microphones
    - Power system
  - Provides signal routing and mechanical mounting

### 2. EEG Acquisition
- **OpenBCI Cyton Biosensing Board (8-channel)**  
  *or*  
- **OpenBCI Cyton + Daisy Biosensing Boards (16-channel)**

- **EEG electrodes**
  - EEG electrodes
  - OpenBCI-compatible connectors and cables

### 3. Audio Acquisition
- **Roland CS-10EM binaural microphones**
  - In-ear stereo microphones
  - Connected to Bela Mini audio inputs

- **Audio cabling**
  - Stereo microphone cables

### 4. Power System
- **Rechargeable battery**
  - LiPo

- **Battery Management System (BMS)**
  - Battery charging
  - Electrical protection
  - Power distribution to Bela and peripherals

### 5. Wiring and Interconnection


### 6. Mechanical Components
- **nEEGlace casing**
  - Houses all electronic components
  - Designed for wearable, everyday use
- Fasteners and mounting elements

## Design Principles

The nEEGlace hardware follows these principles:

- **Open hardware**: all designs are shared and documented
- **Modularity**: individual components can be replaced or extended
- **Low-noise design**: separation of EEG and audio signal paths
- **Wearability**: suitable for long-term, real-world recordings

## Status

This documentation reflects the current nEEGlace prototype.
Hardware components and interfaces may evolve as the project progresses.
Each submodule README documents its current state and known limitations.
