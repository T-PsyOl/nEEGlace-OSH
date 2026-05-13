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

nEEGlace-OpenHardware builds on several stages of previous work on mobile,
neck-worn EEG systems for studying brain activity beyond the laboratory.

An early precursor was used in a long-term mobile ear-EEG study on auditory
attention in everyday life. In that study, a mobile EEG amplifier was attached
to headphones worn around the neck, which were also used for sound presentation.
Participants wore the setup for several hours while performing auditory oddball
tasks in the laboratory and during normal office routines. This work showed that
long-term mobile EEG recordings can be used to study auditory processing in
everyday settings.
The study can be found here:

[Hölle, D., Meekes, J., & Bleichner, M. G. (2021). Mobile ear-EEG to study
auditory attention in everyday life. *Behavior Research Methods*, 53,
2025–2036.](https://doi.org/10.3758/s13428-021-01538-0)

Based on this experience, the original nEEGlace system was developed as a more
integrated neck-worn platform. It combined a commercial, research-grade EEG
amplifier with a commercial neck speaker, creating a compact system for mobile
EEG recordings with integrated sound presentation and contextual audio
recording.

The original nEEGlace project is documented in the previous repository:

[https://github.com/T-PsyOl/neeglace](https://github.com/T-PsyOl/neeglace)

The associated hardware metapaper was published in the *Journal of Open
Hardware*:

[Bleichner, M. G., & Emkes, R. (2020). Building an Ear-EEG System by Hacking a
Commercial Neck Speaker and a Commercial EEG Amplifier to Record Brain Activity
Beyond the Lab. *Journal of Open Hardware*, 4(1).](https://doi.org/10.5334/joh.25)

This nEEGlace version was subsequently used in a study on smartphone-based
ear-EEG for investigating sound processing in everyday life. In that work,
participants were equipped with the nEEGlace, a smartphone-based recording setup, and microphones for recording
the acoustic environment. The study demonstrated how mobile EEG recordings can
be combined with contextual sound information to investigate neural responses
to sounds in more naturalistic conditions.

The study is described here:

[Hölle, D., & Bleichner, M. G. (2023). Smartphone-based
ear-electroencephalography to study sound processing in everyday life.
*European Journal of Neuroscience*, 58(7), 3671–3685.](https://doi.org/10.1111/ejn.16124)

The current nEEGlace-OpenHardware platform continues this line of work. Whereas
the earlier systems relied on adapting and integrating commercial components,
nEEGlace-OpenHardware is designed as a reproducible, modular, and extensible
open-hardware platform. It retains the central scientific aim of recording
neural activity together with contextual information in everyday environments,
while making the system easier to document, reproduce, modify, and further
develop.

## System Overview

## System Overview
nEEGlace is designed around a modular, 3D-printable casing that can be worn around
the neck. The casing houses the core components required for mobile EEG and
contextual audio recording and provides a reproducible mechanical platform for
integrating different hardware configurations.

The system includes:

- **A neck-worn casing** that can be 3D printed and adapted to house different
  hardware components and configurations.
- **Electrode connectors** for connecting ear-EEG electrodes, such as cEEGrids,
  or other EEG electrode arrangements.
- **An EEG acquisition system** for recording neural activity during mobile
  measurements.
- **An audio processing board** for real-time audio processing, event
  extraction, and event injection into the EEG data stream.
- **Binaural microphones** for recording the acoustic environment from the
  wearer’s perspective.
- **A battery unit** that powers all components for several hours of mobile
  operation.

The system is modular by design. Components such as the EEG system, audio board,
microphones, battery unit, connectors, and casing parts can be modified,
replaced, or reconfigured without redesigning the full platform. This allows
nEEGlace to serve as a general neck-worn hardware platform for mobile
neurophysiology and context-aware sensing, rather than as a fixed device tied to
one specific hardware setup.

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
