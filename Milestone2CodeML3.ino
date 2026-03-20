//Georgy Rached. Assisted with AI and some songs from Robsoncouto GitHub
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>

#define BUZZER_PIN  9
#define BTN1_PIN    2
#define BTN2_PIN    3
#define BTN3_PIN    4

#define SCREEN_W 128
#define SCREEN_H 64
Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, -1);

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

const int   NUM_SONGS             = 3;
const int   correctBtn[NUM_SONGS] = { 1, 2, 3 };
const char* songTitles[NUM_SONGS] = { "Song  1", "Song  2", "Song  3" };

const int16_t* songData[NUM_SONGS]  = { song1,  song2,  song3  };
const int      songNotes[NUM_SONGS] = { notes1, notes2, notes3 };
const int      songTempo[NUM_SONGS] = { tempoS1,tempoS2,tempoS3};

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

void jingle(bool success) {
  if (success) {
    tone(BUZZER_PIN, 523, 120); delay(140);
    tone(BUZZER_PIN, 659, 120); delay(140);
    tone(BUZZER_PIN, 784, 280); delay(320);
  } else {
    tone(BUZZER_PIN, 330, 200); delay(230);
    tone(BUZZER_PIN, 262, 400); delay(450);
  }
  noTone(BUZZER_PIN);
}

int readBtn() {
  if (digitalRead(BTN1_PIN) == LOW) return 1;
  if (digitalRead(BTN2_PIN) == LOW) return 2;
  if (digitalRead(BTN3_PIN) == LOW) return 3;
  return 0;
}

int waitBtn() {
  while (readBtn() == 0) { }
  delay(60);
  int b = readBtn();
  while (readBtn() != 0) { }
  delay(60);
  return b;
}

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
  pinMode(BTN1_PIN, INPUT_PULLUP);
  pinMode(BTN2_PIN, INPUT_PULLUP);
  pinMode(BTN3_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  // ── CHANGE 1: story intro before instructions ──
  oledShow("* SPACE WATCH *",
           "The watch of an",
           "old spaceman has",
           "been collected.");
  delay(3000);
  oledShow("Inside is the code",
           "to the next lock.",
           "To keep it secure",
           "he stored 3 songs.");
  delay(3000);
  oledShow("Guess his top 3",
           "favorite songs",
           "to get through!",
           "");
  delay(3000);

  // original welcome / instructions — unchanged
  oledShow("Listen to each song",
           "then press the right",
           "button!",
           "Press any to start!");
  waitBtn();
  delay(200);
}

void loop() {
  for (int s = 0; s < NUM_SONGS; s++) {
    bool passed = false;
    while (!passed) {
      char header[24];
      snprintf(header, sizeof(header), ">> %s <<", songTitles[s]);
      oledShow(header, "Listen carefully...", "", "");
      delay(1200);

      playSong(s);
      noTone(BUZZER_PIN);

      oledShow("Which song was it?",
               "-------------------",
               "BTN1  BTN2  BTN3",
               "  1     2     3  ");
      delay(300);

      int answer = waitBtn();

      if (answer == correctBtn[s]) {
        passed = true;
        // ── CHANGE 2: show song name after correct answer ──
        oledShow("CORRECT!", songTitles[s], ":D  Nice one!", "");
        jingle(true);
        delay(1500);
      } else {
        char wrongLine[28];
        snprintf(wrongLine, sizeof(wrongLine), "You pressed BTN%d...", answer);
        oledShow("WRONG!", wrongLine, "Let's try again!", "");
        jingle(false);
        delay(1800);
      }
    }

    if (s < NUM_SONGS - 1) {
      oledShow("Nice work!",
               "Get ready for",
               "the next song...",
               "");
      delay(2000);
    }
  }

  oledShow("YOU WIN!  \\o/",
           "All songs cleared!",
           "The code is XXXX",  // PUT LOCK CODE HERE
           "Press to play again");

  int fanfare[][2] = {
    {523,100},{523,100},{523,100},{523,350},
    {415,350},{466,350},{523,700}
  };
  for (auto& n : fanfare) {
    tone(BUZZER_PIN, n[0], n[1]);
    delay(n[1] + 30);
  }
  noTone(BUZZER_PIN);

  waitBtn();
  delay(300);
}
