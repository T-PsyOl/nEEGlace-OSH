# <ins>nEEGlace – Battery Management System (BMS)</ins>

---

## Table of Contents

- [Overview](#overview)
- [Repository Structure & File Guide](#repository-structure--file-guide)
- [Hardware Overview](#hardware-overview)
- [Component Reference](#component-reference)
  - [Battery Connector](#battery-connector)
  - [HiLetgo Module Connectors](#hiletgo-module-connectors)
  - [Power Switch (S)](#power-switch-s)
  - [Charge-Detect MOSFET (SSI2301CDS-T1-E3)](#charge-detect-mosfet-ssi2301cds-t1-e3)
  - [LDO Regulator (MCP1700T-3302)](#ldo-regulator-mcp1700t-3302)
  - [Bela 5V Output Connector](#bela-5v-output-connector)
  - [3.3V OBCI Output Connector](#33v-obci-output-connector)
  - [Mic 3.3V Output Connector](#mic-33v-output-connector)
- [Power Architecture](#power-architecture)
- [Charge-Safety Logic — Why the MOSFET Matters](#charge-safety-logic--why-the-mosfet-matters)
- [Signal Routing & Design Rationale](#signal-routing--design-rationale)
- [Connector Pinouts](#connector-pinouts)
- [Layer Stack](#layer-stack)
- [Use Cases](#use-cases)
---

## Overview

The **nEEGlace BMS** is a single-layer-routed, two-layer PCB that sits between a single-cell Li-ion/Li-Po battery, a **HiLetgo** charge/boost breakout module, and the downstream **Bela** + **OpenBCI** electronics on the nEEGlace headset. It provides:

- **Battery input** with a physical power switch
- **Charge-state detection** that automatically disconnects the downstream system while the battery is charging (prevents brown-outs, ground loops, and noisy USB power from reaching sensitive analog inputs)
- **Regulated 5V output** to power the Bela cape directly from the HiLetgo module
- **Regulated 3.3V output** (via onboard LDO) for the OpenBCI board and the microphone bias input on the Bela Cape

This board is designed for:
- Portable / wearable EEG data acquisition (nEEGlace headset)
- Powering a Bela Cape + Bela embedded audio platform from battery
-  Safe co-operation with OpenBCI boards on a shared battery rail
-  Automatic charge-safe shutdown — no manual power cycling required when charging

---

## Repository Structure & File Guide

```
nEEGlace BMS/
│
├── Assembly files/                    # Production-ready fabrication package
│   └── PickAndPlace_PCB_nEEGlace_BMS_* #   Centroid/pick-and-place file for PCBA
│
├── Datasheets/                        # Component datasheets (LDO, MOSFET, HiLetgo, etc.)
│
├── BMS_PCB_Connections.pdf            # Wiring / interconnection reference
│                                      #   → How the BMS connects to Battery,
│                                      #     HiLetgo, Bela, and OpenBCI
│
├── Gerber_nEEGlace_BMS_PCB.zip         # Gerber + Excellon drill files
│                                      #   → Send to any PCB fab to order boards
│
├── OBJ_PCB_nEEGlace_BMS.zip            # 3D mechanical model (OBJ format)
│                                      #   → Use for enclosure design and
│                                      #     mechanical clearance verification
│
├── PCB_nEEGlace_BMS.json              # KiCad PCB layout (machine-readable)
│
├── PCB_nEEGlace_BMS.pdf               # Printable PCB layout (all layers)
│
├── nEEGlace_BMS_PCB.png               # Rendered 3D top-view image of the PCB
│
├── Schematic_nEEGlace_BMS.pdf          # Complete circuit schematic
│                                      #   → Primary reference for signal tracing,
│                                      #     net names, and component values
│
├── odb++_pcb_BMS.tgz                  # ODB++ manufacturing data (alternative to Gerbers)
│
└── Readme.md                          # This file
```

### Quick-Reference: Which File Do I Need?

| Goal | File to Use |
|------|-------------|
| Order bare PCBs | `Gerber_nEEGlace_BMS_PCB.zip` or `odb++_pcb_BMS.tgz` |
| Order fully assembled PCBs (PCBA) | `Assembly files/` folder |
| Understand the circuit | `Schematic_nEEGlace_BMS.pdf` |
| Wire the board into the nEEGlace system | `BMS_PCB_Connections.pdf` |
| Design an enclosure | `OBJ_PCB_nEEGlace_BMS.zip` |
| Visual reference during assembly | `nEEGlace_BMS_PCB.png` / `PCB_nEEGlace_BMS.pdf` |
| Source replacement parts | `Datasheets/` folder |

---

## Hardware Overview
<img width="647" height="459" alt="Screenshot 2026-06-23 at 10 32 29 PM" src="https://github.com/user-attachments/assets/9d7c4f61-89f9-4ae3-a562-01f3899493d3" />


**Board form factor:** Small wearable-friendly form factor for the nEEGlace headset
**Layer count:** 2 (signal + ground plane)
**Key active components:** 1× LDO regulator, 1× N-channel MOSFET, 1× SPDT/SPST power switch

---

## Component Reference

## <ins>Hardware Components</ins>

1. [3.7 V 6000 mAh Li-ion battery](https://www.reichelt.de/de/de/shop/produkt/li-ion_akku_soldered_333289_6000_mah_3_7_v-373553?PROVID=2788&gad_source=1&gad_campaignid=183379230&gbraid=0AAAAADwnxta8x0yYWdivk4HIYVx2_J6NZ&gclid=CjwKCAiA3L_JBhAlEiwAlcWO51JmLiWQyC8HWgx-cUKDrKQgi5Q3NVtTysLjH48ZbLqRPE6nEGL0sRoC1l8QAvD_BwE)
2. [HiLetGo USB-C / USB-A charging and discharging board](https://www.amazon.de/HiLetgo-Discharging-Integrated-Interface-Compatible/dp/B0CDWT9295)
3. [MCP1700-330E low-dropout regulator (3.3 V)](https://www.mouser.de/ProductDetail/Microchip-Technology/MCP1700T-3302E-MB?qs=WWgnj3qycfnlJJhwyn%2Fifw%3D%3D)
4. [Schottky Diode(for unidirectional charge routing)](https://www.mouser.de/ProductDetail/Rectron/SR340-T?qs=2Exw0Z2g%252BZB953JkMkBZbA%3D%3D&mgh=1&vip=1&utm_id=20979042631&utm_source=google&utm_medium=cpc&utm_marketing_tactic=emeacorp&gad_source=1&gad_campaignid=20975737652&gbraid=0AAAAADn_wf0w41oU7Wab0nVdvJgo4DlKu&gclid=CjwKCAiA3L_JBhAlEiwAlcWO5z4tOhBydDzV852ASn-9xmEuQRKEQAsSAIz2j41eMdDuO-YCp13g2hoCTvcQAvD_BwE)
5. [MOSFET(for safety load-switching)](https://www.mouser.de/ProductDetail/Vishay-Semiconductors/SI2301CDS-T1-E3?qs=45wPT2wjtGkQH%252ByrbRpz4Q%3D%3D&utm_id=22433149193&utm_source=google&utm_medium=cpc&utm_marketing_tactic=emeacorp&gad_source=1&gad_campaignid=22426719006&gbraid=0AAAAADn_wf09UgNR-R2CLlcM_vOvQDQnU&gclid=CjwKCAjwyMnNBhBNEiwA-Kcgu9j7y7uiJBoyNoxLyqbDPPBvmXoioG-sIvvJfj0rHu6TZKW7d9wGAhoC2ucQAvD_BwE)
6. 100 kΩ and 10 kΩ resistors (supporting the MOSFET circuit)
7. Decoupling capacitor on 5 V rail- 10u and 100uF.
8. Custom two-layer PCB
9. Ground vias for noise reduction
10. Through-hole pads for power connections (no pin headers)
11. [Slider switch](https://www.reichelt.com/de/en/shop/product/slide_switch_straight_pitch_2_54_1_x_on_off_on-105710)
12. [Cables](https://www.reichelt.com/de/en/shop/product/copper_wire_0_5mm_10m_black-404600)

> A compact battery management and power-distribution board for the **nEEGlace** wearable EEG system, providing charge-safe power switching, 5V regulation via a HiLetgo boost/charge module, and 3.3V LDO regulation for OpenBCI and Bela Cape microphone inputs.

### Battery Connector

- **Location:** Bottom-left of the board, labelled `Battery`
- **Type:** 2-pin connector (JST-style)
- **Signals:** Battery (+), Battery (−) / GND
- **Function:** Main single-cell Li-ion/Li-Po input to the system

The battery feeds the **HiLetgo** module through the power switch, and is also the source that gets recharged when the HiLetgo module is connected to USB-C.

---

### HiLetgo Module Connectors

There are **two connectors** dedicated to the HiLetgo charge/boost breakout module:

| Connector | Location | Function |
|-----------|----------|----------|
| `HiLetgo` | Right edge, lower | Carries raw battery (+/−) to the HiLetgo module's battery terminal |
| `HiLetgo 5V` | Right edge, middle | Returns the HiLetgo module's regulated **5V output** back onto the BMS board |

**Design rationale:** The HiLetgo module performs two jobs depending on its USB-C state:
- **Battery present, no USB-C:** boosts/regulates the battery voltage to a constant 5V output
- **USB-C connected:** charges the battery, while still passing 5V through if powered

Because the same 5V output pin is active in both states, the BMS must distinguish *which* state is active before letting that 5V propagate downstream — this is the job of the MOSFET (see below).

---

### Power Switch (S)

- **Location:** Centre of the board, labelled `Switch`
- **Type:** Through-hole 6-pin (likely SPDT slide or tactile latching) switch
- **Function:** Main system on/off control

When closed, the switch connects the battery to the HiLetgo module's battery input, enabling the boost/regulation path. When open, the entire downstream system (Bela, OpenBCI, mic bias) is unpowered regardless of charge state.

---

### Charge-Detect MOSFET (SSI2301CDS-T1-E3)

- **Location:** Centre-left, labelled `MOSFET`, package SOT-23-3P
- **Part:** SSI2301CDS-T1-E3 — N-channel logic-level MOSFET
- **Function:** Automatic charge-state power gating

```
HiLetgo 5V ──┬── [10kΩ] ──┐
             │            ├──► Gate (charge-detect node)
             └── [100kΩ] ─┘
                            │
                          MOSFET (G-D-S)
                            │
                  Drain ──► to LDO input / downstream 5V rail
                  Source ─► GND (when conducting to ground, system is held OFF)
```

- **Battery discharging (not charging):** the gate-bias network is referenced through the **10 kΩ** path, the MOSFET is **off** (or its drain path is held high), and 5V/3.3V flow normally to Bela, OpenBCI, and the mic bias.
- **Battery charging (USB-C connected to HiLetgo):** the gate-bias network switches to the **100 kΩ** path, pulling the MOSFET's gate to a state where its drain is shorted to **GND**, which collapses the downstream 5V rail and **forcibly powers down the entire system**.

**Design rationale:** Charging a Li-ion cell injects noisy, switching-regulator ripple onto the battery rail, and most USB power bricks are not clean enough for sensitive EEG/biosignal analog front-ends. Rather than relying on the user to remember to power off the headset before charging, this MOSFET network makes shutdown-while-charging **automatic and unconditional**.

---

### LDO Regulator (MCP1700T-3302)

- **Location:** Top-centre, labelled `LDO`, package SOT-89-3
- **Part:** MCP1700T-3302 — fixed 3.3V output, low quiescent current (~1.6 µA), low-dropout linear regulator
- **Input:** Regulated 5V from the HiLetgo module (gated through the MOSFET)
- **Output:** Clean 3.3V rail, distributed to:
  - `3.3V OBCI` connector — powers the OpenBCI board
  - `Mic 3.3V` connector — supplies microphone bias voltage to the Bela Cape's mic input

**Design rationale:** The MCP1700 was chosen for its very low quiescent current (critical for battery life in a wearable) and low dropout voltage, ensuring a stable 3.3V rail even as the upstream 5V sags slightly under load.

---

### Bela 5V Output Connector

- **Location:** Top-left, labelled `Bela 5V`
- **Type:** 2-pin connector
- **Signals:** 5V (+), GND
- **Function:** Delivers the gated 5V rail directly to the Bela embedded audio platform's `5V Input` connector (see the companion [Bela Cape](#) repository)

---

### 3.3V OBCI Output Connector

- **Location:** Top-right, labelled `3.3V OBCI`
- **Type:** 2-pin connector
- **Signals:** 3.3V (+), GND
- **Function:** Powers the OpenBCI biosignal acquisition board from the onboard LDO output

---

### Mic 3.3V Output Connector

- **Location:** Top-left, labelled `Mic 3.3V`
- **Type:** 2-pin connector
- **Signals:** 3.3V (+), GND
- **Function:** Supplies microphone bias voltage to the Bela Cape's L-Mic/R-Mic electret bias network (replacing or supplementing the Bela Cape's own VD2 rail, depending on system configuration)

---

## Power Architecture

```
Battery ──[Switch S]──► HiLetgo (battery terminal)
                              │
                              │  (boost/regulate when discharging,
                              │   charge battery when USB-C present)
                              ▼
                        HiLetgo 5V output
                              │
                              ▼
                 ┌── Charge-detect MOSFET gate network ──┐
                 │     10kΩ (discharging) / 100kΩ (charging)
                 ▼
        MOSFET drain-source gate
                 │
        ┌────────┴─────────┐
        │ Charging?         │
        │  YES → MOSFET pulls rail to GND → system OFF
        │  NO  → rail passes through → system ON
        └────────┬─────────┘
                  ▼
            Gated 5V rail
                  │
        ┌─────────┼─────────┐
        ▼                   ▼
   Bela 5V connector    LDO (MCP1700T-3302)
   (powers Bela cape)         │
                               ▼
                         Gated 3.3V rail
                               │
                  ┌────────────┴────────────┐
                  ▼                         ▼
           3.3V OBCI connector       Mic 3.3V connector
           (powers OpenBCI)          (Bela Cape mic bias)
```

**Ground plane:** A solid ground pour provides a common return path for the battery, HiLetgo, switch, MOSFET, LDO, and all downstream connectors, minimising ground bounce between the digital switch logic and the analog 3.3V mic-bias rail.

---

## Charge-Safety Logic — Why the MOSFET Matters

| HiLetgo State | Gate Bias Path | MOSFET State | Downstream 5V/3.3V | System Behaviour |
|----------------|----------------|---------------|----------------------|-------------------|
| Battery only (discharging) | 10 kΩ | Off / non-conducting to GND | Passes through normally | Bela, OpenBCI, and mic bias powered — **system ON** |
| USB-C connected (battery charging) | 100 kΩ | Drain pulled to GND | Collapsed to ~0V | All downstream rails de-energised — **system OFF** |

This means the nEEGlace headset **cannot be operated while its battery is charging** — a deliberate safety/noise-isolation choice rather than a limitation, since charging current and switching noise from most USB power sources would otherwise contaminate EEG and audio signal acquisition.

>  Confirm the exact gate-bias resistor values and MOSFET orientation against `Schematic_nEEGlace_BMS.pdf` before reproducing this board — the description above reflects the intended design behaviour.

---

## Signal Routing & Design Rationale

### Why Route 5V to Bela *Before* the LDO?

Bela's onboard audio codec has its own internal regulation and is designed to accept 5V directly, so routing the gated 5V rail straight to the `Bela 5V` connector avoids an unnecessary regulation stage and the associated efficiency loss.

### Why a Separate 3.3V Rail for OBCI and Mic Bias?

OpenBCI boards and electret microphone bias circuits are both sensitive to supply noise. Deriving both from the same clean MCP1700T LDO output — rather than tapping raw, less-regulated 5V — keeps both subsystems on a quiet, low-noise rail.

### Why Gate the Rail at the MOSFET Instead of at the Switch?

Using the manual switch alone cannot distinguish "battery discharging" from "battery charging" — both look like "switch closed" to the user. Placing the cutoff at the MOSFET, driven by the charge-state-dependent resistor network, makes the protection **automatic and independent of user action**.

---

## Connector Pinouts

> The table below is derived from the PCB silkscreen and 3D render inspection. **Always cross-reference with `Schematic_nEEGlace_BMS.pdf`** and `BMS_PCB_Connections.pdf` for confirmed pin assignments before wiring external hardware.

| Connector | Pin 1 | Pin 2 | Notes |
|-----------|-------|-------|-------|
| Battery | Battery (+) | GND | Single-cell Li-ion/Li-Po input |
| HiLetgo | Battery (+) passthrough | GND | To HiLetgo module battery terminal |
| HiLetgo 5V | 5V (+) | GND | Return from HiLetgo regulated output |
| Bela 5V | 5V (+) gated | GND | To Bela `5V Input` connector |
| 3.3V OBCI | 3.3V (+) gated | GND | To OpenBCI power input |
| Mic 3.3V | 3.3V (+) gated | GND | To Bela Cape mic bias / VD2 domain |
| Switch (S) | Battery (+) in | Switched (+) out | Main power switch, see schematic for full 6-pin map |

---

## Layer Stack

| Layer | Colour in PCB Viewer | Role |
|-------|----------------------|------|
| F.Cu (Top) | Red | Power routing (battery, HiLetgo, switch, regulated rails) |
| B.Cu (Bottom) | Blue / dark blue | Ground plane + secondary routing |
| F.SilkS | White text | Component references, net labels |
| F.Courtyard | Outlines | Component keep-out boundaries |
| Edge.Cuts | Board outline | PCB boundary definition |

---

## Use Cases

### Wearable EEG + Audio Acquisition (nEEGlace)

Powers the full nEEGlace stack — Bela (audio/triggering), OpenBCI (EEG acquisition), and the Bela Cape's microphone front-end — from a single rechargeable battery, with automatic protection against operating the system while charging.

### Charge-Safe Battery Power for Bela Projects

Can be reused as a general-purpose charge-safe 5V/3.3V battery power supply for any Bela-based project that should never run while its battery is on charge.

### Combined Bio-signal + Audio Synchronisation

Pairs naturally with the companion **Bela Cape (Bela Gem Stereo)** board's D0/D1 trigger lines, enabling synchronised EEG and audio event marking from a single battery-powered, wearable platform.

---

