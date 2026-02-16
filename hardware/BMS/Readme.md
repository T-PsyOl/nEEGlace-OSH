**nEEGlace – Battery Management System (BMS)**

**Overview**

This project presents a custom Battery Management System (BMS) designed for the nEEGlace wearable EEG platform. The system provides battery charging, power regulation, and voltage distribution for embedded computing and EEG acquisition hardware using a dedicated PCB.

**System Description**

The BMS is built around a Hailege charging and discharging board and a 3.7 V 6000 mAh Li-ion battery. The Hailege board manages both battery charging and discharging and acts as the primary power interface for the system. Power is distributed to multiple subsystems through regulated outputs to ensure electrical safety and operational stability.

**Power Architecture**

_Battery:_

1. 3.7 V, 6000 mAh rechargeable Li-ion battery( Selected to support long recording sessions and wearable operation)

_Charging & Discharging:_

1. Managed entirely by the Hailege USB-C / USB-A board
2. Supports USB-C power input
3. Provides charging, discharging, and protection functionality
4. Includes an onboard power indicator LED

**Power Flow**

1. USB-C Input to Hailege Board:
   a. Supplies external power
   b. Charges the 3.7 V 6000 mAh battery
   c. Regulates and outputs 5 V

2. 5 V Distribution
   a. Directly powers the BELA board
   b. Routed through dedicated PCB holes connected to the Hailege board
   c. Includes a decoupling capacitor across the 5 V line for voltage stability

3. Voltage Regulation
   a. MCP1700-330E LDO steps down 5 V to 3.3 V
   b. Supplies stable power to the OpenBCI board

4. Grounding
   a. Common ground shared across all subsystems
   b. Implemented using a solid bottom-layer copper ground plane
   c.Multiple ground vias connect top-layer ground nodes to the plane

**Hardware Components**

1. [3.7 V 6000 mAh Li-ion battery](https://www.reichelt.de/de/de/shop/produkt/li-ion_akku_soldered_333289_6000_mah_3_7_v-373553?PROVID=2788&gad_source=1&gad_campaignid=183379230&gbraid=0AAAAADwnxta8x0yYWdivk4HIYVx2_J6NZ&gclid=CjwKCAiA3L_JBhAlEiwAlcWO51JmLiWQyC8HWgx-cUKDrKQgi5Q3NVtTysLjH48ZbLqRPE6nEGL0sRoC1l8QAvD_BwE)
2. [HiLetGo USB-C / USB-A charging and discharging board](https://www.amazon.de/HiLetgo-Discharging-Integrated-Interface-Compatible/dp/B0CDWT9295)
3. [MCP1700-330E low-dropout regulator (3.3 V)](https://www.mouser.de/ProductDetail/Microchip-Technology/MCP1700T-3302E-MB?qs=WWgnj3qycfnlJJhwyn%2Fifw%3D%3D)
4. Decoupling capacitor on 5 V rail- 10u and 100uF.
5. Custom two-layer PCB
6. Ground vias for noise reduction
7. Through-hole pads for power connections (no pin headers)
8. [Slider switch](https://www.reichelt.com/de/en/shop/product/slide_switch_straight_pitch_2_54_1_x_on_off_on-105710)
9. [Cables](https://www.reichelt.com/de/en/shop/product/copper_wire_0_5mm_10m_black-404600)



**PCB Design**

The BMS PCB was designed using EasyEDA and optimized for wearable electronics:
<img width="461" height="324" alt="Screenshot 2026-01-31 at 1 59 58 PM" src="https://github.com/user-attachments/assets/00a4f526-55b7-4dbc-b651-99a9f5e79cac" />

1. Two-layer PCB
2. Top layer: power routing and component placement
3. Bottom layer: continuous copper ground plane
4. Thick ground traces and copper pours
5. Ground vias are placed at all ground nodes

_Through-holes for:_
1. 5 V output to BELA
2. Power connections from the Hailege board

Green solder mask with silkscreen labeling


**Functionality**

1. USB-C powered battery charging
2. Safe battery discharging for system operation
3. Visual power status indication
4. 5 V regulated output for BELA board
5. 3.3 V low-noise output for OpenBCI
6. Compact and integration-ready PCB for wearable use

**Design Rationale**

1. The Hailege board simplifies charging and discharging while reducing PCB complexity.
2. A 6000 mAh battery enables extended usage suitable for long EEG recordings.
3. The MCP1700-330E LDO provides low-noise regulation critical for biosignal acquisition.
4. A solid ground plane minimizes electromagnetic interference and improves system reliability.
5. Through-hole connections offer mechanical robustness inside a wearable enclosure.

