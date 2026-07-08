#include "lights.h"

#define LED_BUILTIN 8

Lighting::Lighting(KeyboardState &state, int pin0)
    : state(state), _pin0(pin0),
      _strip(STRIP_COUNT, STRIP_PIN, NEO_GRB + NEO_KHZ800) {}

void Lighting::begin() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  _strip.begin();
  _strip.setBrightness(50); // Start at 20% brightness
  _strip.clear();
  _strip.show();
}

void Lighting::builtInblink(int times, int highDelayMs, int lowDelayMs) {
  for (int i = 0; i < times; i++) {
    Serial.println("LED OFF");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(highDelayMs);
    Serial.println("LED ON");
    digitalWrite(LED_BUILTIN, LOW);
    delay(lowDelayMs);
  }
}

void Lighting::builtInLedOff() { digitalWrite(LED_BUILTIN, HIGH); }

// Direct port of the Python wheel() helper.
// Maps 0-255 to a position on the colour wheel (R->G->B->R).
uint32_t Lighting::wheel(uint8_t pos) {
  pos = 255 - pos;
  if (pos < 85)  return _strip.Color(255 - pos * 3, 0,           pos * 3);
  if (pos < 170) return _strip.Color(0,           (pos - 85) * 3, 255 - (pos - 85) * 3);
                 return _strip.Color((pos - 170) * 3, 255 - (pos - 170) * 3, 0);
}

// Non-blocking rainbow cycle — advances one step per loop() call.
// static j persists between calls so animation is continuous and smooth.
void Lighting::testStrip() {
  static int j = 0;
  for (int i = 0; i < _strip.numPixels(); i++) {
    int pixel_index = (i * 256 / _strip.numPixels()) + j;
    _strip.setPixelColor(i, wheel(pixel_index & 255));
  }
  _strip.show();
  j = (j + 1) & 255;
}

void Lighting::loop() {
  this->testStrip(); // TODO: remove once strip is confirmed working
}
