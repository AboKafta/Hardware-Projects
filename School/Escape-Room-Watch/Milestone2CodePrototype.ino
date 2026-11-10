//Georgy Rached 

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buzzer = 11;

const int buttonPin = 2; 

volatile bool paused = false;

//Notes

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
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
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

/* ================= OLED TEXT ================= */

void oledText(const __FlashStringHelper *line1, const __FlashStringHelper *line2) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(line1);
  display.println(line2);
  display.display();
}

/* ================= BUTTON HELPERS ================= */

// Toggle pause if pressed. Debounced + waits for release.
void checkPauseToggle() {
  if (digitalRead(buttonPin) == LOW) {
    delay(25); // debounce
    if (digitalRead(buttonPin) == LOW) {
      while (digitalRead(buttonPin) == LOW) delay(5); // wait release

      paused = !paused;
      if (paused) {
        noTone(buzzer);
        oledText(F("PAUSED"), F("Press to resume"));
      } else {
        oledText(F("RESUMING"), F(""));
      }
    }
  }
}

void waitWhilePaused() {
  while (paused) {
    checkPauseToggle();
    delay(10);
  }
}

// Returns true if a press is detected (for "replay" prompt at the end)
bool waitForButtonPress() {
  // wait for a clean press + release
  while (digitalRead(buttonPin) == HIGH) {
    delay(10);
  }
  delay(25);
  if (digitalRead(buttonPin) == LOW) {
    while (digitalRead(buttonPin) == LOW) delay(5);
    return true;
  }
  return false;
}

/* ================= PLAYER ================= */

void playSong(const int16_t *melody, int notes, int tempo) {
  long wholenote = (60000L * 4) / tempo;

  for (int i = 0; i < notes * 2; i += 2) {
    checkPauseToggle();
    waitWhilePaused();

    int16_t pitch   = (int16_t)pgm_read_word_near(melody + i);
    int16_t divider = (int16_t)pgm_read_word_near(melody + i + 1);

    long noteDuration;
    if (divider > 0) {
      noteDuration = wholenote / divider;
    } else {
      noteDuration = wholenote / labs(divider);
      noteDuration = (noteDuration * 3) / 2; // dotted notes
    }

    if (pitch != 0) tone(buzzer, pitch);

    long playTime = (noteDuration * 9) / 10;
    for (long t = 0; t < playTime; t += 10) {
      checkPauseToggle();
      waitWhilePaused();
      delay(10);
    }

    noTone(buzzer);

    long gap = noteDuration / 10;
    for (long t = 0; t < gap; t += 10) {
      checkPauseToggle();
      waitWhilePaused();
      delay(10);
    }
  }
}

// Take on Me

const int tempoTakeOnMe = 140;

const int16_t takeOnMeMelody[] PROGMEM = {
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8,
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8,
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8,

  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8,
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8,
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
};

const int takeOnMeNotes = sizeof(takeOnMeMelody) / sizeof(takeOnMeMelody[0]) / 2;

// Star Wars

const int tempoStarWars = 140;

const int16_t starWarsMelody[] PROGMEM = {
  NOTE_AS4,8, NOTE_AS4,8, NOTE_AS4,8,
  NOTE_F5,2, NOTE_C6,2,
  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,
  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,
  NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2, NOTE_C5,8, NOTE_C5,8, NOTE_C5,8,
  NOTE_F5,2, NOTE_C6,2,
  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,

  NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,
  NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2, NOTE_C5,-8, NOTE_C5,16,
  NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
  NOTE_F5,8, NOTE_G5,8, NOTE_A5,8, NOTE_G5,4, NOTE_D5,8, NOTE_E5,4, NOTE_C5,-8, NOTE_C5,16,
  NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
};

const int starWarsNotes = sizeof(starWarsMelody) / sizeof(starWarsMelody[0]) / 2;

// Rickroll

const int tempoRick = 140;

const int16_t rickMelody[] PROGMEM = {
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //repeat from 1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  REST,4, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_D5,8, NOTE_E5,8, NOTE_CS5,-8,
  NOTE_B4,16, NOTE_A4,2, REST,4,

  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,4, NOTE_A4,8, //7
  NOTE_A5,8, REST,8, NOTE_A5,8, NOTE_E5,-4, REST,4,
  NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,8, REST,8,
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, REST,4,
};

const int rickNotes = sizeof(rickMelody) / sizeof(rickMelody[0]) / 2;

//loop

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for (;;);
  }

  oledText(F("3-song buzzer"), F("D2 Pause/Replay"));
}

void loop() {
  //play songs
  paused = false;

  oledText(F("Song 1: Take On Me"), F("BUtton Pause/Resume"));
  playSong(takeOnMeMelody, takeOnMeNotes, tempoTakeOnMe);
  delay(1500);

  oledText(F("Song 2: Star Wars"), F("Button Pause/Resume"));
  playSong(starWarsMelody, starWarsNotes, tempoStarWars);
  delay(1500);

  oledText(F("Song 3: Rickroll"), F("Button Pause/Resume"));
  playSong(rickMelody, rickNotes, tempoRick);

  //finished
  noTone(buzzer);
  paused = false; // make sure we're not stuck paused
  oledText(F("Finished!"), F("Press button to replay"));

  waitForButtonPress();  // blocks here until you press the button

  // delay so it doesn't retrigger
  delay(200);

}