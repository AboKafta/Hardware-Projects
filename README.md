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

## Embedded

| Project | Tool | Description |
|---|---|---|
| [MP3 Player](Embedded/MP3-Player) | Arduino | MP3 player firmware with a wiring diagram |
| [Escape Room Watch](Embedded/Escape-Room-Watch) | Arduino | Prototype and milestone firmware for an escape room watch |
| [Prosthetic Hand](Embedded/ProstheticHand) (unfinished) | Arduino | Prototype firmware driving motors from sensor input |
| [Frog Launcher](Embedded/Frog-Launcher) | Python | Arcade game where you launch frogs onto lily pads to reach a target score |


## Websites

| Project | Tools | Description |
|---|---|---|
| [Personal Website](Websites/Personal-Website) | | Coming soon |
| [One Year Anniversary](Websites/One-Year-Anniversary) | HTML | Single-page website |

## Opening the files

- **KiCad:** open the `.kicad_pro` file in the project folder.
- **Altium:** open `TempMonitor.PrjPcb` in Altium Designer.
- **SolidWorks:** open `Rached_Assembly1.SLDASM`, keeping all part files in the same folder.
- **Firmware:** open the `.ino` files in the Arduino IDE.
- **Python:** run `FrogLauncher.py` with Python.
- **Websites:** open `index.html` in a browser.

Where included, Gerber files for fabrication are in a `.zip` inside the project folder.
