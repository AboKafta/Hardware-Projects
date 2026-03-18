// Georgy Rached – Space Jukebox
// Pin 3 = Btn1 | Pin 4 = Btn2 | Pin 5 = Btn3

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT  64
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buzzer = 11;
const int PIN_B1 = 3;
const int PIN_B2 = 4;
const int PIN_B3 = 5;

/* ═══════════════════════════════════════
   DEBOUNCED BUTTONS
   ═══════════════════════════════════════ */
struct Btn {
  int           pin;
  bool          raw, stable, pressed;
  unsigned long lastChange;
};

Btn b1 = {PIN_B1, false, false, false, 0};
Btn b2 = {PIN_B2, false, false, false, 0};
Btn b3 = {PIN_B3, false, false, false, 0};

void pollBtn(Btn &b) {
  b.pressed = false;
  bool r = digitalRead(b.pin) == HIGH;
  unsigned long now = millis();
  if (r != b.raw) { b.raw = r; b.lastChange = now; }
  if (now - b.lastChange >= 25 && r != b.stable) {
    b.stable = r;
    if (r) b.pressed = true;
  }
}

void pollAll() {
  pollBtn(b1);
  pollBtn(b2);
  pollBtn(b3);
}

/* ═══════════════════════════════════════
   OLED
   ═══════════════════════════════════════ */
void oledShow(const __FlashStringHelper *l1,
              const __FlashStringHelper *l2 = nullptr,
              const __FlashStringHelper *l3 = nullptr,
              const __FlashStringHelper *l4 = nullptr) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(l1);
  if (l2) display.println(l2);
  if (l3) display.println(l3);
  if (l4) display.println(l4);
  display.display();
}

void showSongScreen(int n) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Song ")); display.print(n); display.println(F(" / 3"));
  display.display();
}

/* ═══════════════════════════════════════
   NOTE DEFINES
   ═══════════════════════════════════════ */
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

/* ═══════════════════════════════════════
   MELODIES
   ═══════════════════════════════════════ */

// Song 1 – Star Wars Main Theme (~15s @ 120bpm)
const int tempoS1 = 120;
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

// Song 2 – Fly Me to the Moon (~15s @ 120bpm)
const int tempoS2 = 120;
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

// Song 3 – Imperial March (~15s @ 100bpm)
const int tempoS3 = 100;
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

/* ═══════════════════════════════════════
   NON-BLOCKING PLAYER
   ═══════════════════════════════════════ */
int           noteIdx   = 0;
bool          noteReady = false;
unsigned long noteBegin = 0;
long          noteDur   = 0;
bool          inGap     = false;

void resetPlayer() {
  noteIdx = 0; noteReady = false; noteDur = 0; inGap = false;
}

bool tickSong(const int16_t *mel, int nNotes, int tempo) {
  if (noteIdx >= nNotes) return true;

  unsigned long now = millis();

  if (!noteReady) {
    int16_t pitch = (int16_t)pgm_read_word_near(mel + noteIdx * 2);
    int16_t div   = (int16_t)pgm_read_word_near(mel + noteIdx * 2 + 1);
    long whole    = (60000L * 4) / tempo;
    noteDur       = (div > 0) ? whole / div : (whole / -div * 3) / 2;
    if (pitch != REST) tone(buzzer, pitch); else noTone(buzzer);
    noteBegin = now;
    noteReady = true;
    inGap     = false;
  }

  long elapsed = (long)(now - noteBegin);

  if (!inGap) {
    if (elapsed >= (noteDur * 9) / 10) {
      noTone(buzzer);
      noteBegin = now;
      inGap     = true;
    }
  } else {
    if (elapsed >= noteDur / 10) {
      noteReady = false;
      noteIdx++;
      if (noteIdx >= nNotes) { noTone(buzzer); return true; }
    }
  }
  return false;
}

/* ═══════════════════════════════════════
   APP STATE MACHINE
   ═══════════════════════════════════════ */
enum State { STARTUP, PLAYING, ANSWER, ALLDONE };
State appState = STARTUP;
int   curSong  = 1;

const int16_t *curMel;
int            curNotes, curTempo;

void loadSong(int n) {
  switch (n) {
    case 1: curMel = song1; curNotes = notes1; curTempo = tempoS1; break;
    case 2: curMel = song2; curNotes = notes2; curTempo = tempoS2; break;
    case 3: curMel = song3; curNotes = notes3; curTempo = tempoS3; break;
  }
}

void startSong(int n) {
  curSong = n;
  loadSong(n);
  resetPlayer();
  appState = PLAYING;
  showSongScreen(n);
}

/* ═══════════════════════════════════════
   SETUP
   ═══════════════════════════════════════ */
void setup() {
  pinMode(PIN_B1, INPUT);
  pinMode(PIN_B2, INPUT);
  pinMode(PIN_B3, INPUT);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) for (;;);
  oledShow(F("= Space Jukebox ="), F(""), F("Press any button"), F("to start!"));
}

/* ═══════════════════════════════════════
   MAIN LOOP
   ═══════════════════════════════════════ */
void loop() {
  pollAll();

  switch (appState) {

    case STARTUP:
      if (b1.pressed || b2.pressed || b3.pressed)
        startSong(1);
      break;

    case PLAYING:
      if (tickSong(curMel, curNotes, curTempo)) {
        appState = ANSWER;
        oledShow(F("Which song was it?"),
                 F("Press its button:"),
                 F(""),
                 F("Btn 1  /  2  /  3"));
      }
      break;

    case ANSWER: {
      int ans = b1.pressed ? 1 : b2.pressed ? 2 : b3.pressed ? 3 : 0;
      if (ans) {
        if (ans == curSong) {
          if (curSong == 3) {
            oledShow(F("Correct!"), F(""), F("All done!"), F("Great job!"));
            delay(1500);
            appState = ALLDONE;
            oledShow(F("Press any button"), F("to replay!"));
          } else {
            oledShow(F("Correct!"), F(""), F("Get ready..."));
            delay(1000);
            startSong(curSong + 1);
          }
        } else {
          oledShow(F("Wrong!"), F(""), F("Replaying..."));
          delay(1000);
          startSong(curSong);
        }
      }
      break;
    }

    case ALLDONE:
      if (b1.pressed || b2.pressed || b3.pressed)
        startSong(1);
      break;
  }
}