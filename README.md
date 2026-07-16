Georgy Rached

GE 1502

4/14/2026

Milestone 4 – Escape Room

**Our Puzzle:**

Our puzzle consisted of a 3D-printed transmitter, and a space watch. The transmitter has 2 pieces: the main body and the antenna. The antenna is hidden in the vending machine and contains a hint to unlock a code, which is hidden in the front of the transmitter's base. The code obtained from the antenna is the final code to escape the room. The base of the transmitter was hidden in the final starbox of the starboxxes puzzle.

The Spacewatch is an electronic circuit that plays/buzzes 3 space-themed songs. The electronics were fitted into the fabricated object which looked like a watch. If all three songs are guessed correctly, then a code is displayed at the end which is a code for one of the locks in the escape room. The components performed well during the trials, with nothing breaking or malfunctioning.

**Committee:**

I was on the marketing committee. Our responsibilities were making a sign-up website, generating a QR code, designing an eye-catching poster and distributing them across campus. There were around 7 members. The workload felt well-balanced and achievable, with everything being achieved in time.

**My Specific Contributions:**

For my small group, I volunteered to make the electronics part of the project. The first prototype was a basic LED screen, a passive buzzer, and a pause/resume button. For the final version, I included three buttons for guessing, a passive buzzer and an OLED screen. I used an Arduino Nano for my microcontroller and coded it all in C++ on Arduino IDE. This was then fitted into the fabricated object.

For the committee, I contributed to initial discussion and created the initial google docs that included all the plans. Additionally, I helped build part of the sign-up website, including the layout format for all the game sections. I wrote the small description of our escape room for the website after setting up the layout for the other sections. I also distributed one of the posters that were given and put it up on the second floor of Snell Library

**Design Process and Pitfalls of the Electronics Section:**

For the prototype, my original idea included a speaker with an SD card module to play the songs. However, I didn't have a speaker and none of the team wanted to spend money, so I pivoted to using a passive buzzer to generate frequencies. I found a repository on GitHub that had a library of popular songs arranged for passive buzzers. Using the base code that the GitHub had, I had a working prototype. Then, I implemented a button that could pause and resume the song and an OLED screen to show some text/output if the guess was correct or not.

After milestone two, some improvements had to be made. For the final design, I removed the pause/resume button since it was unreliable and not essential. I also added an incorrect and correct sound that plays when a button is pressed. Then, I added three buttons to the circuit for the inputs. However, this is where I encountered my first main pitfall. The buttons were super sensitive, and the lightest touch would trigger an input. I first thought I had faulty buttons, so I substituted them. It turned out that wasn't the problem, so I tested some code that would stop the electrical interference, but that also didn't work. After some hours of troubleshooting, I changed the circuitry of the buttons. This proved successful as the buttons worked normally now. However, the OLED stopped working. I created a function that split the text across 3 separate lines at fixed positions on the OLED screen, since the long string overflowed the OLED. With the shorter chunks being passed instead of one big chunk, the OLED started to work again.

**How It Went:**

From hearing classmates who were there and the in-class discussion, the escape room went pretty well. Compared to other years, our room was difficult and took around 40 minutes to solve each escape room. There were minimal malfunctions during the escape room. I was there for setup, and we thought we setup everything, but apparently the vending machine and car weren't setup well. Cleanup was fast and resetting the problems didn't take a lot of time between each session. For improving the place next time, maybe we can add space themed décor that could elevate the atmosphere. Also, I think it should be mandated to have at least 1 person from each group for setup next time since the setup crew was very confused on the setup of some projects.

The game also went somewhat differently than what we expected. Instead of everyone going to one puzzle, the groups spread out to a lot of puzzles. They were also gentle with the puzzles instead of being brute like we thought they'd be. For the watch, everyone thought it was too easy, but I didn't really want the puzzle to be too hard and be a good beginner puzzle. Overall, the escape room was a big success.

I would like to thank Gavin Cox, Mateo Borrero, and Hrishikesh Reddy for doing the 3D printed object and the fabricated object. Without them, this all wouldn't have been possible.

**Appendix:**

<img width="199" height="264" alt="image" src="https://github.com/user-attachments/assets/c2de5712-0390-4d25-ba21-1c3bb87cdf97" />
