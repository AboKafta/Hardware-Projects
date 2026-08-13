# BlinkingHeartPCB
## Initial Prototype (Summer 2025)

A simple prototype was first made during the summer of 2025 as a gift for my girlfriend. After looking up some tutorials and many hours, I got a simple prototype. I tumbled into some problems such as putting footprints, design errors, and generating a BoM. After using JLCPCB, this is how it was supposed to look. However, after seeing how much it would cost and if it would even work, I didn't continue to manufacture it. A lot of steps were missed in the process (correct factory specifications, wrong gerber file, etc…) and contained a variety of through-hole and SMD parts.

<img width="1033" height="730" alt="image" src="https://github.com/user-attachments/assets/7198c52f-d427-4494-9620-6d3f028972a1" />

## Second Iteration (2026)

The goal is to make around the same but this time using a 555 timer to make it blink, use only through-hole components to make it easily solderable, and make it smaller and more appeasing. 

# Prototype

Using a guide from https://www.instructables.com/Flashing-LED-using-555-Timer/, a prototype on TinkerCAD was built. Modifications were:

- potentiometer which acts as a rheostat to change blinking speed instead of 1 set blinking speed
- 13 additional LEDs with 100ohm corresponding resistor
- 9V battery to 3V battery cell for convenience, with switch added

A prototype was made in TinkerCAD to check if everything works well before going on to making a schematic: https://www.tinkercad.com/things/8CvfxhTKkNE-blinking-led

<img width="670" height="678" alt="image" src="https://github.com/user-attachments/assets/26885a53-53f4-481e-b2b7-17ce7f0a9393" />

# Schematic

Helpful KiCad tutorial: https://www.youtube.com/watch v=HAlTS3Bm8C4&list=PLUOaI24LpvQPls1Ru_qECJrENwzD7XImd&index=3

In KiCad, the base schematic was transformed from:

<img width="1044" height="653" alt="image" src="https://github.com/user-attachments/assets/b7af0bac-1b84-4ee0-b32f-4917d4bc08e7" />

To:

<img width="1270" height="897" alt="image" src="https://github.com/user-attachments/assets/4d643067-cf89-429b-8685-ff681a2a0425" />

Notes:

- Resistor values on LEDs can be made higher to change duration of cell battery but LEDs won’t be as bright.
- If LED colors wants to be swapped, make sure the forward voltage is around 2V. Anything above 3V will ensure dim lights and low battery run time.
- The battery cell itself was bought off amazon rather than Digikey.
- 50ohm resistors to LEDs were kept to keep the current at a safe level and not rely on the cell battery’s internal resistance which is prone to spikes.
- Make sure the chosen 555 timer takes 3V, some take 4.5V and above only.

Parts Selected:

All items were found off Digikey and contain all the necessary symbols and footprints except the yellow LEDs, but that can be assigned to a basic 5mm LED footprint found on KiCad:

- Switch: https://www.digikey.com/en/products/detail/e-switch/100SP1T1B4M2QE/378824
- 555 Timer: https://www.digikey.com/en/products/detail/renesas-electronics-corporation/ICM7555IPAZ/821488
- 1k Ohm Resistor: https://www.digikey.com/en/products/detail/stackpole-electronics-inc/CF14JT1K00/1741314
- 1 uF Capacitor: https://www.digikey.com/en/products/detail/tdk/FG28X7R1E105KRT06/5803197
- Yellow LEDs: https://www.digikey.com/en/products/detail/kingbright/WP7113SYC/1747679
- 50ohm Resistors: https://www.digikey.com/en/products/detail/yageo/MFR25SFBE52-50R/9142201
- 1Mohm Potentiometer: https://www.digikey.com/en/products/detail/bourns-inc/PDB12-H4301-105BF/3780665

After that, run DRC. If no errors put up, it is safe to continue. Make sure to put limitations of PCB making factory that is chosen before continuing to PCB layout.

# PCB Layout

To get heart-shape, use the basic tools given. Make 2 semi-circles and have their 2 parallel lines from the endpoints intersect. After that, I updated PCB from schematic and laid out all the components. I placed the resistors and LCDs next to the each other so vias weren’t necessary for my case. After that, I refilled and rechecked the DRC, giving 0 warnings and error. I then added some finishing touches with the silk layer. Below are all the pictures:

<img width="1296" height="811" alt="image" src="https://github.com/user-attachments/assets/45b3ca15-39c8-4812-b3b1-56c564884525" />

<img width="1062" height="793" alt="image" src="https://github.com/user-attachments/assets/1fcf75b7-2ee8-4e7f-b641-f08e3438b374" />

<img width="891" height="711" alt="image" src="https://github.com/user-attachments/assets/d9f945b0-7fd4-4cb8-903c-cc95643e7fe6" />

<img width="991" height="690" alt="image" src="https://github.com/user-attachments/assets/22ffef90-2cb2-4fee-8afd-9c5ba2818b20" />

<img width="1003" height="688" alt="image" src="https://github.com/user-attachments/assets/90a1a547-5232-4270-81b3-d40319428165" />

Total Costs —> 46$ ($13 for PCB, $33 for parts)

# Soldering:

Below are results of the outcome. The LEDs were working while soldering, but stopped working. At first, I thought the LEDs were taking too much amps so I removed some LEDs, but it still wasn’t working. I put my multimeter to measure amps and the lights were lighting up when I was testing leads. However, 2 lights weren’t lighting up. This was because their legs were touching together. After fixing that, all the lights started lighting up and it was all working. I then reordered LEDs but burnt one pad off while reinstalling 



https://github.com/user-attachments/assets/f94614ca-ea78-433b-8afd-7a24a165e5f3

<img width="768" height="1024" alt="WhatsApp Image 2026-08-13 at 12 36 59 PM" src="https://github.com/user-attachments/assets/2624e316-6ef2-4524-898f-2dc1758f98d4" />
