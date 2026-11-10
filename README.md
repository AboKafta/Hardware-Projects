# Hardware Projects

PCB designs, CAD models, embedded firmware, and websites from my engineering projects, each in its own folder.

## PCB

| Project | Tool | Description |
|---|---|---|
| [RP2350 Dev Board](PCB/RP2350-Dev-Board) | KiCad | Custom development board for the RP2350 microcontroller, with bring-up and GPIO test firmware |
| [Room Temperature Monitor](PCB/Room-Temperature-Monitor) | Altium | Temperature monitor circuit from an Arduino beginner's guidebook, redesigned as a custom PCB with an Arduino Nano in place of the Uno |
| [Piano](PCB/Piano) | KiCad | Arduino Nano-based piano board with a piezo speaker |
| [Blinking Heart](PCB/BlinkingHeart) | KiCad | Battery-powered blinking LED heart board |

## CAD

| Project | Tool | Description |
|---|---|---|
| [Chessboard](CAD/Chessboard) | SolidWorks | Chess board and full set of pieces modeled as parts and an assembly, with a final report |
| [Flywheel](CAD/Flywheel) | SolidWorks | Flywheel assembly with a bracket, axle, bushing, collar, and set screw, plus an engineering drawing with a bill of materials |

## Embedded

| Project | Tool | Description |
|---|---|---|
| [Escape Room Watch](Embedded/Escape-Room-Watch) | Arduino, SolidWorks | Team project: a space-themed escape room puzzle. An Arduino Nano plays three songs on a buzzer, and guessing all three with the buttons shows a lock code on an OLED. I built the electronics and wrote the firmware; my teammates designed and 3D-printed the watch and transmitter (models in `CAD`) |
| [Frog Launcher](Embedded/Frog-Launcher) | MicroPython | Team project: an arcade machine where players launch frogs onto lily pads worth 1 to 3 points and avoid alligators worth -1. I wrote all the code for the Raspberry Pi Pico, built the LCD scoreboard, and rewired the circuit |
| [Pico Spooky Project](Embedded/Pico-Spooky-Project) | MicroPython | Halloween prop on a Raspberry Pi Pico: an ultrasonic sensor detects someone within 10 cm, then a servo turns and two LEDs start blinking |
| [MP3 Player](Embedded/MP3-Player) | Arduino | MP3 player firmware with a wiring diagram |
| [Prosthetic Hand](Embedded/ProstheticHand) (unfinished) | Arduino | Prototype firmware driving motors from sensor input |

## Websites

| Project | Tools | Description |
|---|---|---|
| [Personal Website](Websites/Personal-Website) | | Coming soon |
| [One Year Anniversary](Websites/One-Year-Anniversary) | HTML | Single-page website |

## Opening the files

- **KiCad:** open the `.kicad_pro` file in the project folder.
- **Altium:** open `TempMonitor.PrjPcb` in Altium Designer.
- **SolidWorks:** open the `.SLDASM` assembly file, keeping its part files in the same folder. Chessboard has a PDF report and Flywheel has screenshots, for viewing without SolidWorks.
- **Arduino:** open the `.ino` files in the Arduino IDE.
- **MicroPython:** open the `.py` files in Thonny and run them on a Raspberry Pi Pico.
- **Websites:** open `index.html` in a browser.

Where included, Gerber files for fabrication are in a `.zip` inside the project folder.

## AI assistance

Most of the firmware in this repo was developed with coding assistance from Claude, Anthropic's AI assistant.
