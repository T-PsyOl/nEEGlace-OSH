# nEEGlace-OpenHardware

![nEEGlace open hardware](https://github.com/T-PsyOl/nEEGlace-OpenHardware/blob/main/assets/neeglace%202.2.png)
nEEGlace is an open hardware platform for studying neural activity in everyday
environments. It is designed to enable long-term, wearable EEG recordings
combined with rich contextual data, such as binaural audio, while remaining
compact, reproducible, and extensible.

The project is developed at the Translational Psychology Lab,
at the Department of Psychology at the Carl von Ossietzky Universität Oldenburg.

## Motivation

Understanding brain activity outside the laboratory is essential for studying
natural cognition, perception, and behavior. However, conventional EEG systems
are typically bulky, restrictive, and optimized for short, controlled
experiments. As a result, they are poorly suited for long-term or
ecologically valid recordings and often lack information about the sensory and
environmental context in which neural signals are recorded.

nEEGlace addresses these limitations by integrating ear-EEG with additional
contextual sensors into a neck-worn, wearable system that can be used in
real-world settings.

## Scientific Background

The current nEEGlace open-hardware platform builds on an earlier version of
nEEGlace, which was developed as a mounting system for mobile EEG recordings
beyond the laboratory. The original system combined a commercial,
research-grade EEG amplifier with a commercial neck speaker, creating a
neck-worn platform that allowed EEG to be recorded over extended periods while
also enabling sound playback and audio recording.

The original nEEGlace project is documented in the previous repository:
[https://github.com/T-PsyOl/neeglace](https://github.com/T-PsyOl/neeglace).

The associated hardware metapaper was published in the *Journal of Open
Hardware*:

[Bleichner, M. G., & Emkes, R. (2020). Building an Ear-EEG System by Hacking a
Commercial Neck Speaker and a Commercial EEG Amplifier to Record Brain Activity
Beyond the Lab. *Journal of Open Hardware*, 4(1).](https://doi.org/10.5334/joh.25)

Using this earlier nEEGlace model, we conducted studies on mobile and
naturalistic EEG recordings, particularly in the context of auditory
neuroscience. These studies showed that a neck-worn system can support EEG
recordings outside conventional laboratory settings and can be used to relate
brain activity to sound presentation and the acoustic environment.

The current open-hardware version continues this line of work but shifts the
focus from adapting commercial components toward a reproducible, extensible, and
documented hardware platform. It retains the central scientific motivation of
recording neural activity together with contextual information in everyday
environments, while making the system easier to reproduce, modify, and further
develop.

## System Overview

nEEGlace combines the following core elements:

- **(Ear)-EEG acquisition** 
- **Binaural audio recording** 
- **Real-time processing and control** 
- **Battery-powered operation** 
- **Wearable form factor**

The system is modular by design, allowing individual components (e.g., EEG
amplifier, microphones, casing) to be modified or replaced without redesigning
the entire platform.

## Repository Structure

This repository contains all components required to build, program, and use the
nEEGlace system:
- assets/ Media files, figures, and illustrations
- docs/ Background documentation and design rationale
- firmware/ Low-level firmware for embedded components
- hardware/ Hardware documentation (electronics, BMS, casing, wiring)
- manufacturing/ Manufacturing files and production-related information
- software/ User-facing software, analysis tools, and utilities
- test/ Hardware and software tests and validation scripts

Each folder contains its own README with more detailed documentation.

## Design Principles

nEEGlace follows a small set of guiding principles:

- **Open hardware**: schematics, layouts, and designs are shared
- **Modularity**: hardware and software components are loosely coupled
- **Wearability**: suitable for long-term use in everyday environments
- **Context awareness**: neural data is recorded together with relevant
  environmental information

## Project Status

nEEGlace is an active research and development project.
The hardware and software described here reflect the current prototype and may
evolve over time. Contributions, feedback, and replication efforts are welcome.

For details on specific components, please start with the corresponding
subfolder.
