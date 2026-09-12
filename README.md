# Room-Temperature-Monitor
Temperature Monitor circuit from an Arduino beginners guidebook translated into a custom Altium PCB room temperature monitor, and swapping the Arduino Uno for an Arduino Nano

I wanted to do a project on Altium to be more proficient in Altium since I’ve done all my PCBs on KiCad. I first opened and created the project files. I will use MPN search for all my components since that is a new useful tool that KiCad doesn’t have. This is the reference schematic

<img width="215" height="214" alt="image (17)" src="https://github.com/user-attachments/assets/e9503e35-a10c-4f57-81fd-69f6dfdc93ec" />

<img width="395" height="316" alt="image (16)" src="https://github.com/user-attachments/assets/f21c6b53-f02d-495e-8ee9-524e6e40e971" />

A lot of errors popped up when I thought it was fine. Most of the errors went away when I changed some names and double checked label connections. The only warning left was a pin type error on pin 2 of the sensor. I changed the pin type to passive since that is how it is wired in the schematic and that fixed the issue.

<img width="626" height="417" alt="image (18)" src="https://github.com/user-attachments/assets/d421bb40-ee40-4f96-974c-2451185bee93" />

I then moved onto layout and wiring. First of all, I got the JLCPCB rules set from a github repo and imported them onto Altium. After that, I changed the board shape. One of the LEDs was bigger than the other so I went back and changed the LED models for them to be the same width.

 The imported footprints were acting weird, with 2 LEDs being really off board. After some useful shortcuts, they were all back together.

I did 2 ground pours total, one on the rectangular body and one on the circular part. There were no pours on the neck of the build though so the heat from the nano and other components don’t transfer down to the temperature sensor. This increases the accuracies of our readings. One trace needs to connect across the grounds together from the temperature sensor.

After wiring, I validated it and got no errors. Gerber files were also generated and put into the GitHub. I decided not to continue to fabricate with JLCPCB due to money and time issues.

<img width="255" height="377" alt="image (20)" src="https://github.com/user-attachments/assets/a7f2236c-ff5a-4a62-a295-d32cf8c5a1b9" />

<img width="195" height="458" alt="image (19)" src="https://github.com/user-attachments/assets/2b19c5c8-e8f0-482c-b5be-8c0149939f1e" />


