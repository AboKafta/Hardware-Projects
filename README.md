# piano

The main goal of this project is to enhance and reinforce the basics of PCB designing.

With this in knowledge, I opened my Arduino beginners guidebook and chose the Piano project. This comes with an image of the breadboard prototype, a schematic drawing and the code.

After reading about the project, I opened up KiCad and began making a schematic. Instead of connecting everything with wires and copying the reference exactly as it was, I decided to use labels for the time. The other differences from the reference schematic is changing the Arduino Uno to an Arduino Nano, and selecting a buzzer drawing for the piezo.

The footprint, symbol, and 3d model for the piezo were gotten from: https://www.digikey.com/en/products/detail/murata-electronics/PKM22EPPH4001-B0/1219323
The rest of the footprints/symbols/3d models were obtained from the pre-installed KiCad library

I made my first drawing and it had issues such as duplicate labels and mismatched labels. Additionally, I got a power output error after running ERC. I had to put a power flag on the ground pin of the Nano to specify it was outputting power. 

With the errors cleaned, the schematic was done:
<img width="1152" height="355" alt="image" src="https://github.com/user-attachments/assets/b5e7416f-29b4-4745-a16e-ff8fe773739c" />

There weren’t any issues that came up while placing and routing components. This is the final product:
<img width="997" height="742" alt="image" src="https://github.com/user-attachments/assets/0c43d6e9-c2b9-46d7-aa94-816f8515a077" />
<img width="933" height="703" alt="image" src="https://github.com/user-attachments/assets/93f8a59d-8000-48ec-99c2-530247546b1f" />
<img width="802" height="601" alt="image" src="https://github.com/user-attachments/assets/4005faa9-8231-475a-a153-04f45857387e" />

<img width="768" height="1024" alt="WhatsApp Image 2026-08-13 at 12 46 29 PM" src="https://github.com/user-attachments/assets/7e61e4e0-bae4-49ab-b17c-738980929ea6" />

https://github.com/user-attachments/assets/582eb45c-a093-4306-8a8f-120d23ab803b


