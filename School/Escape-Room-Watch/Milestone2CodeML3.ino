//Georgy Rached. Assisted with AI and some songs from Robsoncouto GitHub
//including Libraries neccesary to the OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>

//assigning buttons and buzzer to GPIOs
#define BUZZER_PIN  10
#define BTN1_PIN    2
#define BTN2_PIN    3
#define BTN3_PIN    4

//oled Pixels
#define SCREEN_W 128
#define SCREEN_H 64
Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, -1);

//notes for music
#define REST     0
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_C6  1047
#define NOTE_F6  1397

//song 1
const int tempoS1 = 120; //BPM
const int16_t song1[] PROGMEM = {
  NOTE_AS4,8, NOTE_AS4,8, NOTE_AS4,8,
  NOTE_F5,2,  NOTE_C6,2,
  NOTE_AS5,8, NOTE_A5,8,  NOTE_G5,8, NOTE_F6,2,  NOTE_C6,4,
  NOTE_AS5,8, NOTE_A5,8,  NOTE_G5,8, NOTE_F6,2,  NOTE_C6,4,
  NOTE_AS5,8, NOTE_A5,8,  NOTE_AS5,8,NOTE_G5,2,
  NOTE_C5,8,  NOTE_C5,8,  NOTE_C5,8,
  NOTE_F5,2,  NOTE_C6,2,
  NOTE_AS5,8, NOTE_A5,8,  NOTE_G5,8, NOTE_F6,2,
};
const int notes1 = sizeof(song1) / sizeof(song1[0]) / 2;

//song 2
const int tempoS2 = 120; //BPM
const int16_t song2[] PROGMEM = {
  NOTE_E5,8,  NOTE_D5,8, NOTE_C5,8, NOTE_B4,4, NOTE_A4,8, REST,8,
  NOTE_A4,8,  NOTE_B4,8, NOTE_C5,8, NOTE_B4,8, NOTE_A4,4, NOTE_G4,4,
  NOTE_A4,8,  NOTE_B4,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,4, NOTE_E5,4,
  NOTE_C5,8,  NOTE_B4,8, NOTE_A4,8, NOTE_G4,4, NOTE_E4,2,
  REST,4,     NOTE_E5,8, NOTE_D5,8, NOTE_C5,8, NOTE_B4,4,
  NOTE_C5,4,  NOTE_A4,2, REST,4,
  NOTE_A4,8,  NOTE_B4,8, NOTE_C5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,8,
  NOTE_G4,4,  NOTE_E4,2,
};
const int notes2 = sizeof(song2) / sizeof(song2[0]) / 2;

//song 3
const int tempoS3 = 100; //BPM
const int16_t song3[] PROGMEM = {
  NOTE_G4,4,  NOTE_G4,4,   NOTE_G4,4,
  NOTE_DS4,-8,NOTE_AS4,16,
  NOTE_G4,4,  NOTE_DS4,-8, NOTE_AS4,16, NOTE_G4,2,
  NOTE_D5,4,  NOTE_D5,4,   NOTE_D5,4,
  NOTE_DS5,-8,NOTE_AS4,16,
  NOTE_G4,4,  NOTE_DS4,-8, NOTE_AS4,16, NOTE_G4,2,
  NOTE_G5,4,  NOTE_G4,-8,  NOTE_G4,16,
  NOTE_G5,4,  NOTE_FS5,-8, NOTE_F5,16,
  NOTE_E5,8,  NOTE_DS5,8,  NOTE_E5,8,  REST,8,
  NOTE_GS4,8, NOTE_CS5,4,
};
const int notes3 = sizeof(song3) / sizeof(song3[0]) / 2;

const int NUM_SONGS = 3;
const int correctBtn[NUM_SONGS] = { 1, 2, 3 }; //button1 is song 1 , button 2 is song 2 ... can change around
const char* songTitles[NUM_SONGS] = { "Song  1", "Song  2", "Song  3" }; //name of song to display on LCD


const int16_t* songData[NUM_SONGS]  = { song1,   song2,   song3   };
const int      songNotes[NUM_SONGS] = { notes1,  notes2,  notes3  };
const int      songTempo[NUM_SONGS] = { tempoS1, tempoS2, tempoS3 };

//function write stuff on screen, basically print but for the OLED
void oledShow(const char* l1,
              const char* l2 = "",
              const char* l3 = "",
              const char* l4 = "") {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  if (l2[0] == '\0') {
    display.setTextSize(2);
    display.setCursor(0, 24);
    display.println(l1);
  } else {
    display.setTextSize(1);
    int16_t y = 4;
    const char* lines[] = {l1, l2, l3, l4};
    for (int i = 0; i < 4; i++) {
      if (lines[i][0] != '\0') {
        display.setCursor(0, y);
        display.println(lines[i]);
        y += 14;
      }
    }
  }
  display.display();
}

//function to play a short jingle sound
void jingle(bool success) {
  if (success) {
    // Rising three-note success fanfare
    tone(BUZZER_PIN, 523, 120); delay(140);
    tone(BUZZER_PIN, 659, 120); delay(140);
    tone(BUZZER_PIN, 784, 280); delay(320);
  } else {
    // Descending two-note fail sound
    tone(BUZZER_PIN, 330, 200); delay(230);
    tone(BUZZER_PIN, 262, 400); delay(450);
  }
  noTone(BUZZER_PIN);
}

//reading the button state
int readBtn() {
  if (digitalRead(BTN1_PIN) == LOW) return 1; //if button pressed, return 1
  if (digitalRead(BTN2_PIN) == LOW) return 2;
  if (digitalRead(BTN3_PIN) == LOW) return 3;
  return 0;  // No button pressed
}

//this function blocks the program from contuining unless a button is pressed
int waitBtn() {
  while (readBtn() == 0) {  } //do nothing
  delay(60);
  int b = readBtn();  //sees which button is pressed and stores it as variable b
  while (readBtn() != 0) { } // waits for release
  delay(60);
  return b; //send button number back to caller
}

// plays the intro story screens
void showIntro() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 24);
  display.println(F("SpaceWatch"));
  display.display();
  delay(1800);

  auto storyScreen = [](const __FlashStringHelper* a,
                        const __FlashStringHelper* b,
                        const __FlashStringHelper* c) {
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0,  4); display.println(a);
    display.setCursor(0, 18); display.println(b);
    display.setCursor(0, 32); display.println(c);
    display.display();
  };

  storyScreen(F("The watch of an"), F("old spaceman is"), F("collected."));
  delay(5000); //how long text stays on screen
  storyScreen(F("In this watch is"), F("the code to the"), F("next lock."));
  delay(5000);
  storyScreen(F("To keep it secure"), F("he has songs"), F("downloaded."));
  delay(5000);
  storyScreen(F("Guess his top 3"), F("favorite songs"), F("to get through!"));
  delay(5000);

  oledShow("Listen to each song",
           "Press the Correct",
           "Button!!",
           "Press any to start!");
  waitBtn();
  delay(200);
}

//function that plays the songs
void playSong(int idx) {
  const int16_t* melody = songData[idx];
  int   n      = songNotes[idx];
  int   tempo  = songTempo[idx];
  int   whole  = (60000L * 4) / tempo;
  for (int i = 0; i < n * 2; i += 2) {
    int freq = (int)pgm_read_word(&melody[i]);
    int dur  = (int)pgm_read_word(&melody[i + 1]);
    int ms;
    if (dur > 0) {
      ms = whole / dur;
    } else {
      ms = (whole / -dur) * 3 / 2;
    }
    int playMs = ms * 9 / 10;
    if (freq == REST) {
      delay(ms);
    } else {
      tone(BUZZER_PIN, freq, playMs);
      delay(ms);
      noTone(BUZZER_PIN);
    }
  }
}

void setup() {
  //arduino reads high as the normal and low when the button is pressed
  pinMode(BTN1_PIN, INPUT_PULLUP);
  pinMode(BTN2_PIN, INPUT_PULLUP);
  pinMode(BTN3_PIN, INPUT_PULLUP);
  //set as output to configure tone
  pinMode(BUZZER_PIN, OUTPUT);

  //initilaizing OLED Screen
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

//Main loop
void loop() {
  showIntro(); //show story and wait for button press

  //going through all the songs
  for (int s = 0; s < NUM_SONGS; s++) {
    bool passed = false; //sees if the right song was selected

    //while loop that keeps on replaying a song until they get the correct one
    while (!passed) {
      char header[24];
      snprintf(header, sizeof(header), ">> %s <<", songTitles[s]);
      oledShow(header,
               "Listen carefully...",
               "",
               "");
      delay(1200);  //lets the player read the screen before the song starts

      //play song
      playSong(s);
      noTone(BUZZER_PIN);  // Safety stop after song finishes

      //answer screen
      oledShow("Which song was it?",
               "-------------------",
               "BTN1  BTN2  BTN3",
               "  1     2     3  ");
      delay(300);

      //wait for player to enter answer
      int answer = waitBtn();

      //checking if answer is within the right order based off the correctBtn array
      if (answer == correctBtn[s]) {
        //Correct
        passed = true;
        oledShow("CORRECT!", songTitles[s], "Nice", "");
        jingle(true); //make sound
        delay(1500);  //show the result screen for 1.5 seconds
      } else {
        //wrong
        char wrongLine[28];
        snprintf(wrongLine, sizeof(wrongLine),
                 "You pressed BTN%d...", answer); //tells which wrong button they pressed
        oledShow("WRONG!", wrongLine, "Try again :)", "");
        jingle(false);
        delay(1800);  //show the fail screen for 1.8 seconds before replaying
      }
    } // end while(!passed)

    //transition to next song
    if (s < NUM_SONGS - 1) {
      oledShow("Nice work.",
               "Get ready for",
               "the next song...",
               "");
      delay(2000);  //2 second pause between songs
    }
  }

  //If all songs were pressed in the right order
  oledShow("You Passed!",
           "All songs cleared!",
           "The code is 204",  // PUT LOCK CODE HERE
           "Press to play again");

  //victory sound
  int fanfare[][2] = {
    {523,100},{523,100},{523,100},{523,350},
    {415,350},{466,350},{523,700}
  };
  for (auto& n : fanfare) {
    tone(BUZZER_PIN, n[0], n[1]);
    delay(n[1] + 30);
  }
  noTone(BUZZER_PIN);

  //press any button to replay
  waitBtn();
  delay(300);
}
