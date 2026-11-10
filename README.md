# Hardware Projects

My engineering work, split into personal projects and school projects, each in its own folder.

## Personal Projects

### PCB

| Project | Tool | Description |
|---|---|---|
| [RP2350 Dev Board](Personal/PCB/RP2350-Dev-Board) | KiCad | Custom development board for the RP2350 microcontroller, with bring-up and GPIO test firmware |
| [Room Temperature Monitor](Personal/PCB/Room-Temperature-Monitor) | Altium | Temperature monitor circuit from an Arduino beginner's guidebook, redesigned as a custom PCB with an Arduino Nano in place of the Uno |
| [Piano](Personal/PCB/Piano) | KiCad | Arduino Nano-based piano board with a piezo speaker |
| [Blinking Heart](Personal/PCB/BlinkingHeart) | KiCad | Battery-powered blinking LED heart board |

### Embedded

| Project | Tool | Description |
|---|---|---|
| [MP3 Player](Personal/Embedded/MP3-Player) | Arduino | MP3 player firmware with a wiring diagram |
| [Prosthetic Hand](Personal/Embedded/ProstheticHand) (unfinished) | Arduino | Prototype firmware driving motors from sensor input |

### Websites

| Project | Tools | Description |
|---|---|---|
| [Personal Website](Personal/Websites/Personal-Website) | | Coming soon |
| [One Year Anniversary](Personal/Websites/One-Year-Anniversary) | HTML | Single-page website |

## School Projects

| Project | Course | Tools | Description |
|---|---|---|---|
| [Escape Room Watch](School/Escape-Room-Watch) | Cornerstone of Engineering 2 | Arduino, SolidWorks | Team project: a space-themed escape room puzzle. An Arduino Nano plays three songs on a buzzer, and guessing all three with the buttons shows a lock code on an OLED. I built the electronics and wrote the firmware; my teammates designed and 3D-printed the watch and transmitter (models in `CAD`) |
| [Frog Launcher](School/Frog-Launcher) | Cornerstone of Engineering 1 | MicroPython | Team project: an arcade machine where players launch frogs onto lily pads worth 1 to 3 points and avoid alligators worth -1. I wrote all the code for the Raspberry Pi Pico, built the LCD scoreboard, and rewired the circuit |
| [Chessboard](School/Chessboard) | Cornerstone of Engineering 2 | SolidWorks | Kingdom Hearts-themed chess set: the board and every piece modeled as parts and an assembly, with a final report |
| [Secrets of the Phoenicians](School/Secrets-of-the-Phoenicians) | Cornerstone of Engineering 2 | MATLAB App Designer | Puzzle adventure game set in ancient Phoenicia, using switches, a dropdown, and buttons, with three endings |
| [RPG Fighting Game](School/RPG-Fighting-Game) | Cornerstone of Engineering 1 | Python | Turn-based boss fight with attack, capture, and befriend options, built around a class |
| [Classic Circuit Calculator](https://github.com/brodienewhouse/Classic-Circuit-Calculator) (in progress) | Computing Fundamentals for Engineers | C++ | Team project: calculates current, resistance, voltage, and power for simple series and parallel resistor circuits, with a touch-display frontend. Hosted in a teammate's repo |

## Opening the files

- **KiCad:** open the `.kicad_pro` file in the project folder.
- **Altium:** open `TempMonitor.PrjPcb` in Altium Designer.
- **SolidWorks:** open the `.SLDASM` assembly file, keeping its part files in the same folder. Chessboard has a PDF report for viewing without SolidWorks.
- **Arduino:** open the `.ino` files in the Arduino IDE.
- **MicroPython:** open the `.py` files in Thonny and run them on a Raspberry Pi Pico.
- **Python:** run `RPGFightingGame.py` with Python 3.
- **MATLAB:** open `ML3FINAL.mlapp` in App Designer.
- **Websites:** open `index.html` in a browser.

Where included, Gerber files for fabrication are in a `.zip` inside the project folder.

## AI assistance

Most of the firmware in this repo was developed with coding assistance from Claude, Anthropic's AI assistant.
