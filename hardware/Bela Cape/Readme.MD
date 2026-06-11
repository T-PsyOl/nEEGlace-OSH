# Bela Gem Stereo Hardware Cape

## Overview

This project presents a custom, high-precision audio expansion cape designed for the **Bela Gem Stereo** embedded computing platform (powered by the PocketBeagle 2). The system provides ultra-low latency audio processing, low-noise microphone biasing, and precision voltage scaling for stereo acoustic peripherals. It is specifically engineered with signal integrity, absolute phase-coherence, and high signal-to-noise ratios (SNR) in mind for scientific acoustic research, spatial audio capturing, and digital musical instrument (DMI) design.

| 3D Digital Prototype (Top View) | 2D Copper Trace & Routing Topology |
| --- | --- |
|  |  |

---

## System Description

The Bela Gem Stereo Cape acts as a hardware-optimized analog front-end shield that mounts directly onto the host processor's expansion headers. To bypass complex external breadboard circuits, this custom board consolidates dedicated microphone biasing networks, dual-channel voltage dividers, and flexible physical interconnects into a single, compact, noise-shielded PCB. It translates fragile analog acoustic signals into a clean, level-matched format perfectly tailored for the system's onboard Analog-to-Digital Converters (ADCs).

---

## Power Architecture & Signal Routing

Interfacing small-signal acoustic transducers with high-speed digital processing units introduces significant risk of high-frequency noise coupling. This design mitigates these bottlenecks through three core architectures:

### 1. Low-Noise Bias Voltage Distribution

Electret condenser microphone (ECM) capsules require an external DC bias voltage to power their internal JFET impedance converters.

* **The "Constant-Current" Pull-Up (`MIC RESISTORS`):** Symmetrical $2.2\,\text{k}\Omega$ pull-up resistors are tied directly to the filtered analog power rail. This specific resistance matches the native output impedance of standard acoustic capsules, maximizing power transfer and linearity while keeping the bias ripple-free.

### 2. Input Signal Attenuation & Scaling (`VD1` & `VD2`)

To prevent clipping the Bela Gem’s sensitive ADC inputs, the hardware integrates active attenuation networks:

* **The Precision Voltage Dividers:** Built using a $10\,\text{k}\Omega$ and $1\,\text{M}\Omega$ resistor topology, these networks scale incoming signal amplitudes to utilize the full dynamic range of the ADC without saturation. This layout preserves a high input impedance, preventing the hardware from loading down and degrading the microphone stage.

### 3. Power Isolation & Decoupling

* **5V External Rail Integration:** A dedicated $5\,\text{V}$ power entry path is broken out via terminal blocks. When deploying high-gain microphone setups, users can inject an isolated, linear-regulated external DC source.
* **Transient Shunting:** Dual inline surface-mount decoupling capacitors are positioned strategically near the center traces to filter out power supply ripple and digital switching transients before they reach the analog signal path.

---

## Hardware Components

* **P1 Host Interconnect:** Dual-row female pass-through headers ($2 \times 22$ pin configuration) for direct mounting onto the Bela Gem Stereo stack.
* **MIC RESISTORS:** 2x $2.2\,\text{k}\Omega$ (0805 SMD package) pull-up biasing resistors.
* **VD1 RESISTORS:** $10\,\text{k}\Omega$ and $1\,\text{M}\Omega$ (0805 SMD package) voltage divider pair for Left-channel attenuation.
* **VD2 RESISTORS:** Matched tolerance (0805 SMD package) resistor pair for Right-channel balancing.
* **Audio Jack:** 3.5mm Right-angle through-hole stereo TRS connector.
* **U3 Connector Array:** Right-angle modular terminal blocks for raw wire integration.
* **Decoupling Capacitors:** Onboard MLCC ceramic filtering capacitors.
* **Custom Two-Layer PCB:** Form-factor optimized for compact audio enclosures.
* **Solid Copper Ground Pour:** Continuous ground plane for EMI suppression.

---

## PCB Design

The cape was engineered with strict adherence to high-fidelity audio layout principles, visible across its design layers:

* **Two-Layer Shielding Architecture:** As seen in the layout file `33792.jpg`, the top layer handles dedicated signal and power routing, while the bottom layer is a continuous copper **ground plane**. This solid ground plane acts as an electromagnetic shield, isolating the sensitive analog traces from the digital clock noise of the underlying CPU.
* **Symmetrical Trace Geometry:** The Left (`L Mic`) and Right (`R Mic`) analog traces run parallel, isolated paths along the right half of the board. This structural symmetry ensures identical propagation delays and phase-coherence, minimizing crosstalk and maintaining true stereo separation.
* **Dual Interconnect Footprints:** Combines a consumer-facing 3.5mm **Audio Jack** (visible in `33791.jpg`) for plug-and-play gear with a heavy-duty right-angle terminal block array (**U3**) for secure, bare-wire instrument or custom chassis embedding.

---

## Design Rationale & Benefits for Research

* **Phase-Coherent Stereophonic Imaging:** Symmetrical trace matching guarantees negligible phase discrepancy between the Left and Right channels across the human audible spectrum ($20\,\text{Hz} - 20\,\text{kHz}$), a strict requirement for phase-sensitive acoustic measurements and spatial audio research.
* **Enhanced Signal-to-Noise Ratio (SNR):** By shifting the microphone biasing and attenuation networks from a loose breadboard to an aggressively grounded, decoupled PCB, the noise floor is radically minimized, resulting in pristine biosignal and acoustic capture.
* **Power Rail Isolation:** The dedicated external $5\,\text{V}$ input allows researchers to bypass noisy USB bus power entirely, preventing computer switching noise from bleeding into high-gain field probes or sensor arrays.
* **Deployable Field Stability:** Replacing fragile jumper wires with a rock-solid, direct-mounting cape form factor ensures structural and mechanical integrity during mobile field experiments or ambulatory tracking.
