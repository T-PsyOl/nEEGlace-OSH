**nEEGlace – Battery Management System (BMS)**

**Overview**
This project presents a custom Battery Management System (BMS) designed for the nEEGlace wearable EEG platform. The system provides battery charging, power regulation, and safe voltage distribution for embedded computing, EEG acquisition hardware, and microphone peripherals. It is specifically designed with participant safety and data integrity in mind for neuroscience research.

**System Description**
The BMS is built around a HiLetgo charging and discharging board and a high-capacity 3.7 V 6000 mAh Li-ion battery. The HiLetgo board acts as the primary power interface. To ensure maximum safety for the wearer and protect the battery, the board features a custom smart-switching circuit utilizing a Schottky diode and a MOSFET. This ensures the device can be charged easily while strictly preventing the system from operating while plugged into a wall outlet.

**Power Architecture & Safety Features**

1. _Battery & Primary Power:_
a) 3.7 V, 6000 mAh Li-ion battery: Selected to support multi-hour recording sessions, allowing for long-term ambulatory EEG paradigms. 
b) HiLetgo USB-C Board: Manages USB-C power input, battery charging, and provides an onboard power indicator LED.

2. _Smart Switching & Participant Safety:_
a) To ensure the system is both safe for human use and highly reliable, the power flow is controlled by two key components:
The "One-Way" Charging Valve (Schottky Diode): A Schottky diode is placed between the HiLetgo board and the battery's positive terminal. Think of this as a one-way gate. It allows USB power to flow *into* the battery, charging it at any time (even when the device is turned off). However, when the device is switched off and disconnected from USB, it prevents the battery from draining its power back into the HiLetgo board. 
b) The Automatic Safety Switch (MOSFET): In wearable EEG, a participant must never be electrically connected to wall power. The MOSFET acts as a smart safety gate. When the HiLetgo board is actively charging the battery via USB, the MOSFET automatically cuts off power to the rest of the nEEGlace system. It acts as an automatic switch ensuring that the system can *only* run on isolated battery power, and never while tethered to a charging cable.

3. _Power Distribution & Regulation:_
a) 5 V Distribution: Directly powers the BELA computing board. Dual decoupling capacitors (10 µF and 100 µF) are used to smooth the voltage, preventing power spikes from interrupting the computer.
b) 3.3 V Distribution: A Low-Dropout Regulator (LDO) steps the 5 V down to a highly stable, low-noise 3.3 V line. This clean power is critical for supplying the OpenBCI (OBCI) board to ensure high-fidelity, noise-free EEG signal acquisition. It also powers the 3.3 V Microphone (Mic) module.

**Hardware Components**
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

**PCB Design**
<img width="586" height="454" alt="Screenshot 2026-04-15 at 8 44 06 AM" src="https://github.com/user-attachments/assets/4640775b-47fc-4426-aa75-cca3b2e4273e" />

The BMS PCB was designed using EasyEDA, tailored specifically for integration into a wearable electronics enclosure:
1) _Two-Layer Architecture:_ The top layer handles power routing, while the bottom layer is a continuous copper "ground plane." This solid ground plane acts as a shield, minimizing electromagnetic interference (EMI) that could corrupt sensitive EEG data.
2) _Robust Connections:_ Uses through-holes for all power outputs (BELA, OBCI, Mic) rather than bulky pin headers, ensuring mechanical stability even when the participant is moving.
3) _Clear Labeling:_Green solder mask with a highly legible silkscreen to prevent wiring errors during assembly.

**Design Rationale & Benefits for Research**
1) _Participant Safety First:_ The MOSFET circuit guarantees "charge-and-play" prevention. The system physically cannot be powered on while connected to mains power, eliminating the risk of electrical faults reaching the participant.
2) _Always-Ready Charging:_ The Schottky diode ensures that simply plugging the device into a USB-C cable will charge the battery, regardless of what position the physical power switch is in.
3) _Clean Biosignals:_ The combination of a dedicated 3.3V LDO for the OpenBCI board and a continuous ground plane ensures that the power supplied to the EEG amplifiers is extremely quiet, leading to a higher Signal-to-Noise Ratio (SNR) in your recordings.
4) _Extended Paradigms:_ The 6000 mAh battery capacity natively supports extended, day-long recording sessions without needing to swap batteries or interrupt the experiment.
