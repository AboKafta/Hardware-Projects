/* ===========================================================================
   RP2350 Custom Board - GPIO Sweep Test
   ---------------------------------------------------------------------------
   Drives one GPIO high at a time and announces it over serial, so you can
   probe the matching header pin and confirm it goes to 3.3 V.

   This catches three separate faults:
     - open joint        : pin never goes high
     - solder bridge     : a NEIGHBOURING pin also goes high
     - swapped net       : the wrong header pin lights up

   The third one is why the serial print matters. A pin that toggles proves
   the joint is good; only cross-checking against your pin map proves the
   net goes where the schematic says.

   HOW TO MEASURE (cheapest first)
     - LED + ~330R resistor on a jumper: cathode to GND, touch anode to each
       header pin. Lights = high. Fastest way to sweep the whole header.
     - Multimeter on DC volts, ground clipped: 3.3 V active, 0 V idle.
     - Logic analyser clipped across a run of pins, if you have one.

   BOARD: Tools > Board > Generic RP2350 (Earle Philhower arduino-pico core)
   =========================================================================== */

#include <Arduino.h>

// ---------------------------------------------------------------- pin sets --
// FREE pins: not connected to anything on the board, safe to drive at will.
const uint8_t FREE_GPIO[] = {
  0, 1, 4, 5, 9, 10, 11, 12, 13, 14, 15, 23, 24, 26, 27, 28, 29
};

// COMMITTED pins: wired to buttons, display or LED. Driving them is still a
// valid continuity test, but the display will glitch and the button lines
// will fight their pull-ups. Enable deliberately, not by accident.
const uint8_t COMMITTED_GPIO[] = {
  2, 3, 6, 7,        // buttons SW3-SW6
  8,                 // display backlight
  16, 17, 18, 19,    // SPI: MISO, TFT_CS, SCK, MOSI
  20, 21, 22,        // SD_CS, D/C, RST
  25                 // status LED
};

const uint8_t N_FREE      = sizeof(FREE_GPIO) / sizeof(FREE_GPIO[0]);
const uint8_t N_COMMITTED = sizeof(COMMITTED_GPIO) / sizeof(COMMITTED_GPIO[0]);

// ----------------------------------------------------------------- config --
// Long enough to find the pin on the header and get a probe on it. Drop to
// ~400 ms once you know your way around the board.
const unsigned long DWELL_MS = 1500;

// Set true to also sweep the committed pins. Expect the screen to flicker,
// the LED to blink out of sequence and the backlight to jump.
const bool SWEEP_COMMITTED = false;

// Set true to hold each pin high until you send a character over serial,
// instead of advancing on a timer. Useful when probing alone.
const bool STEP_ON_SERIAL = false;

// ------------------------------------------------------------------ setup --
void setup() {
  Serial.begin(115200);
  unsigned long t0 = millis();
  while (!Serial && millis() - t0 < 2000) { /* brief wait, don't hang */ }

  // Park everything low first. Starting from a known state means a pin
  // reading high later is the pin under test, not a leftover.
  for (uint8_t i = 0; i < N_FREE; i++) {
    pinMode(FREE_GPIO[i], OUTPUT);
    digitalWrite(FREE_GPIO[i], LOW);
  }
  if (SWEEP_COMMITTED) {
    for (uint8_t i = 0; i < N_COMMITTED; i++) {
      pinMode(COMMITTED_GPIO[i], OUTPUT);
      digitalWrite(COMMITTED_GPIO[i], LOW);
    }
  }

  Serial.println(F("\n=== RP2350 GPIO sweep ==="));
  Serial.print(F("Free pins      : "));   Serial.println(N_FREE);
  Serial.print(F("Committed pins : "));
  Serial.println(SWEEP_COMMITTED ? N_COMMITTED : 0);
  Serial.println(F("Each pin goes HIGH in turn. Probe the matching header pin."));
  Serial.println(F("Watch for neighbours going high too - that is a bridge.\n"));
  delay(1000);
}

// ------------------------------------------------------------------- loop --
void loop() {
  Serial.println(F("--- free pins ---"));
  for (uint8_t i = 0; i < N_FREE; i++) pulsePin(FREE_GPIO[i]);

  if (SWEEP_COMMITTED) {
    Serial.println(F("--- committed pins (display/buttons/LED will react) ---"));
    for (uint8_t i = 0; i < N_COMMITTED; i++) pulsePin(COMMITTED_GPIO[i]);
  }

  Serial.println(F("\nSweep complete. Restarting in 3 s.\n"));
  delay(3000);
}

// ------------------------------------------------------------------ helper --
void pulsePin(uint8_t pin) {
  Serial.print(F("GPIO "));
  if (pin < 10) Serial.print(' ');     // keeps the column aligned
  Serial.print(pin);
  Serial.println(F("  -> HIGH"));

  digitalWrite(pin, HIGH);

  if (STEP_ON_SERIAL) {
    while (!Serial.available()) { /* hold until you send anything */ }
    while (Serial.available()) Serial.read();
  } else {
    delay(DWELL_MS);
  }

  digitalWrite(pin, LOW);
}
