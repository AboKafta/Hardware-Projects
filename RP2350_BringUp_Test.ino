/* ===========================================================================
   RP2350 Custom Board - Hardware Bring-Up Test
   ---------------------------------------------------------------------------
   Tests, in order of increasing dependency:
     1. LED heartbeat   - proves the core is running (no peripherals needed)
     2. Serial output   - proves USB enumerated and the crystal is working
     3. Backlight       - proves GPIO8 and the display's power rail
     4. Display (SPI)   - proves SPI0, the TFT, and your wiring
     5. Buttons         - proves the 4 input GPIO

   If the display stays dark, watch the LED and serial monitor: they narrow
   the fault down to the SPI section rather than the whole board.

   BOARD: Tools > Board > Raspberry Pi Pico/RP2040/RP2350 > Generic RP2350
          (install Earle Philhower's arduino-pico core first)
   LIBS:  Adafruit GFX Library, Adafruit ST7735 and ST7789 Library
   =========================================================================== */

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// ---------------------------------------------------------------- pin map --
// Display (Adafruit 3533, ST7735S, 160x80) on SPI0
const uint8_t TFT_SCK_PIN   = 18;   // SPI0 SCK
const uint8_t TFT_MOSI_PIN  = 19;   // SPI0 TX
const uint8_t TFT_MISO_PIN  = 16;   // SPI0 RX (microSD only)
const uint8_t TFT_CS_PIN    = 17;
const uint8_t TFT_DC_PIN    = 21;
const uint8_t TFT_RST_PIN   = 22;
const uint8_t SDCARD_CS_PIN = 20;   // held high so the card ignores the bus
const uint8_t BACKLIGHT_PIN =  8;   // backlight, PWM-capable

// Inputs and status
const uint8_t BTN_PINS[4]     = { 2, 3, 6, 7 };
const uint8_t STATUS_LED_PIN  = 25;

// -------------------------------------------------------------- constants --
const int16_t SCREEN_W = 160;
const int16_t SCREEN_H = 80;
const uint8_t BALL_R   = 5;

const uint16_t BALL_COLORS[] = {
  ST77XX_RED, ST77XX_GREEN, ST77XX_BLUE,
  ST77XX_YELLOW, ST77XX_CYAN, ST77XX_MAGENTA
};
const uint8_t N_COLORS = sizeof(BALL_COLORS) / sizeof(BALL_COLORS[0]);

// Debounce window. Mechanical switches bounce for a few ms; 25 ms is a safe
// margin that still feels instant to a human.
const unsigned long DEBOUNCE_MS = 25;

// ------------------------------------------------------------------ state --
Adafruit_ST7735 tft = Adafruit_ST7735(&SPI, TFT_CS_PIN, TFT_DC_PIN, TFT_RST_PIN);

struct Button {
  bool          stable;      // debounced level (true = pressed)
  bool          lastRaw;
  bool          justPressed; // one-shot edge flag
  unsigned long lastChange;
  uint32_t      pressCount;
};
Button btn[4];

float    ballX = SCREEN_W / 2.0f, ballY = SCREEN_H / 2.0f;
float    velX  = 1.8f,            velY  = 1.1f;
int16_t  prevX = -99,             prevY = -99;   // for erasing the old frame
uint8_t  colorIdx = 0;
float    speedMul = 1.0f;
bool     paused   = false;
uint8_t  backlight = 255;

unsigned long lastFrame = 0;
unsigned long lastBeat  = 0;
bool          ledOn     = false;

// ------------------------------------------------------------------ setup --
void setup() {
  // --- 1. LED first. If this blinks, the core booted. ---
  pinMode(STATUS_LED_PIN, OUTPUT);
  digitalWrite(STATUS_LED_PIN, HIGH);

  // --- 2. Serial. If this prints, USB enumerated and the crystal is good. ---
  Serial.begin(115200);
  unsigned long t0 = millis();
  while (!Serial && millis() - t0 < 2000) { /* wait briefly, don't hang */ }
  Serial.println(F("\n=== RP2350 board bring-up ==="));

  // --- 3. Buttons. INPUT_PULLUP works whether or not R11-R14 are fitted;
  //        an internal pull-up in parallel with an external one is harmless. ---
  for (uint8_t i = 0; i < 4; i++) {
    pinMode(BTN_PINS[i], INPUT_PULLUP);
    btn[i] = { false, false, false, 0, 0 };
  }
  Serial.println(F("Buttons  : GPIO 2, 3, 6, 7 (internal pull-ups on)"));

  // --- 4. Park the microSD chip-select high so the card stays off the bus. ---
  pinMode(SDCARD_CS_PIN, OUTPUT);
  digitalWrite(SDCARD_CS_PIN, HIGH);

  // --- 5. Backlight. If the panel glows white, power and GPIO8 are good
  //        even if SPI is broken - a useful split in the fault tree. ---
  pinMode(BACKLIGHT_PIN, OUTPUT);
  analogWrite(BACKLIGHT_PIN, backlight);
  Serial.println(F("Backlight: on (GPIO8)"));

  // --- 6. SPI0 on our pins, then the panel. ---
  SPI.setSCK(TFT_SCK_PIN);
  SPI.setTX(TFT_MOSI_PIN);
  SPI.setRX(TFT_MISO_PIN);
  SPI.begin();

  // Revision note: boards made before Jan 2023 use INITR_MINI160x80 instead.
  // If the image is offset or colour-inverted, swap to the other constant.
  tft.initR(INITR_MINI160x80_PLUGIN);
  tft.setRotation(3);              // landscape, 160x80
  tft.fillScreen(ST77XX_BLACK);
  Serial.println(F("Display  : ST7735S initialised, 160x80"));

  splashScreen();
  drawStaticUI();
  lastFrame = millis();

  Serial.println(F("Ready. Press the buttons.\n"));
}

// ------------------------------------------------------------------- loop --
void loop() {
  heartbeat();
  readButtons();
  handleButtonActions();

  // ~50 fps. Fixed timestep keeps the motion speed independent of how long
  // the drawing actually takes.
  if (millis() - lastFrame >= 20) {
    lastFrame = millis();
    if (!paused) updateBall();
    drawBall();
    drawButtonStates();
  }
}

// -------------------------------------------------------------- heartbeat --
// Blinks the LED once a second. Runs regardless of display state, so a dark
// screen with a blinking LED means "core alive, SPI section suspect".
void heartbeat() {
  if (millis() - lastBeat >= 500) {
    lastBeat = millis();
    ledOn = !ledOn;
    digitalWrite(STATUS_LED_PIN, ledOn);
  }
}

// ---------------------------------------------------------------- buttons --
void readButtons() {
  for (uint8_t i = 0; i < 4; i++) {
    bool raw = (digitalRead(BTN_PINS[i]) == LOW);   // active low

    if (raw != btn[i].lastRaw) {
      btn[i].lastChange = millis();                // bounce started
      btn[i].lastRaw    = raw;
    }

    if (millis() - btn[i].lastChange > DEBOUNCE_MS && raw != btn[i].stable) {
      btn[i].stable = raw;
      if (raw) {
        btn[i].justPressed = true;
        btn[i].pressCount++;
        Serial.print(F("BTN"));  Serial.print(i + 1);
        Serial.print(F(" (GPIO")); Serial.print(BTN_PINS[i]);
        Serial.print(F(") pressed - count "));
        Serial.println(btn[i].pressCount);
      }
    }
  }
}

void handleButtonActions() {
  if (btn[0].justPressed) {                       // BTN1: cycle colour
    btn[0].justPressed = false;
    colorIdx = (colorIdx + 1) % N_COLORS;
  }
  if (btn[1].justPressed) {                       // BTN2: faster
    btn[1].justPressed = false;
    speedMul = min(speedMul * 1.5f, 6.0f);
  }
  if (btn[2].justPressed) {                       // BTN3: slower
    btn[2].justPressed = false;
    speedMul = max(speedMul / 1.5f, 0.2f);
  }
  if (btn[3].justPressed) {                       // BTN4: pause + dim
    btn[3].justPressed = false;
    paused = !paused;
    backlight = paused ? 40 : 255;                // visible proof GPIO8 PWMs
    analogWrite(BACKLIGHT_PIN, backlight);
  }
}

// --------------------------------------------------------------- graphics --
void splashScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(14, 16);
  tft.print(F("RP2350"));
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.setCursor(14, 40);
  tft.print(F("board bring-up OK"));
  tft.setTextColor(ST77XX_CYAN);
  tft.setCursor(14, 54);
  tft.print(F("press any button"));

  // Colour bars confirm the panel isn't stuck in a mono or inverted mode.
  const uint16_t bars[] = { ST77XX_RED, ST77XX_GREEN, ST77XX_BLUE, ST77XX_WHITE };
  for (uint8_t i = 0; i < 4; i++) tft.fillRect(120 + i * 8, 16, 6, 48, bars[i]);

  delay(2000);
  tft.fillScreen(ST77XX_BLACK);
}

void drawStaticUI() {
  tft.drawRect(0, 0, SCREEN_W, SCREEN_H - 14, ST77XX_WHITE);   // play area
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  for (uint8_t i = 0; i < 4; i++) {
    tft.setCursor(8 + i * 38, SCREEN_H - 11);
    tft.print(F("B"));
    tft.print(i + 1);
  }
}

void updateBall() {
  ballX += velX * speedMul;
  ballY += velY * speedMul;

  if (ballX - BALL_R <= 1)             { ballX = 1 + BALL_R;             velX = -velX; }
  if (ballX + BALL_R >= SCREEN_W - 2)  { ballX = SCREEN_W - 2 - BALL_R;  velX = -velX; }
  if (ballY - BALL_R <= 1)             { ballY = 1 + BALL_R;             velY = -velY; }
  if (ballY + BALL_R >= SCREEN_H - 16) { ballY = SCREEN_H - 16 - BALL_R; velY = -velY; }
}

// Erase-then-draw rather than clearing the whole screen: a full fillScreen()
// every frame is slow over SPI and shows as visible flicker.
void drawBall() {
  int16_t x = (int16_t)ballX, y = (int16_t)ballY;
  if (x == prevX && y == prevY) return;

  if (prevX > -99) tft.fillCircle(prevX, prevY, BALL_R, ST77XX_BLACK);
  tft.fillCircle(x, y, BALL_R, BALL_COLORS[colorIdx]);
  tft.drawRect(0, 0, SCREEN_W, SCREEN_H - 14, ST77XX_WHITE);  // repair border
  prevX = x; prevY = y;
}

void drawButtonStates() {
  static bool shown[4] = { false, false, false, false };
  for (uint8_t i = 0; i < 4; i++) {
    if (btn[i].stable != shown[i]) {
      shown[i] = btn[i].stable;
      uint16_t c = btn[i].stable ? ST77XX_GREEN : ST77XX_BLACK;
      tft.fillRect(20 + i * 38, SCREEN_H - 12, 10, 9, c);
      tft.drawRect(20 + i * 38, SCREEN_H - 12, 10, 9, ST77XX_WHITE);
    }
  }
}