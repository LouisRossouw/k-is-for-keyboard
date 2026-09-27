#include "lights.h"

// #define LED_BUILTIN 8
#define LED_BUILTIN 48

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
  if (pos < 85)
    return _strip.Color(255 - pos * 3, 0, pos * 3);
  if (pos < 170)
    return _strip.Color(0, (pos - 85) * 3, 255 - (pos - 85) * 3);
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

// Non-blocking ambient base glow.
// Lights up the entire base in a single synchronized color that slowly cycles
// and breathes.
void Lighting::ambientBaseGlow() {
  static uint8_t colorPos = 0;
  static uint32_t lastColorUpdate = 0;
  static uint32_t lastBreatheUpdate = 0;
  static float breatheAngle = 0.0f;
  static float breathingFactor = 0.5f;

  uint32_t now = millis();

  // Slow down the color shifting: update color position every 30 milliseconds
  if (now - lastColorUpdate > 30) {
    colorPos++;
    lastColorUpdate = now;
  }

  // Update breathing factor every 15 milliseconds
  if (now - lastBreatheUpdate > 15) {
    // Breathing factor oscillates smoothly between 0.35 and 0.95 using a sine
    // wave
    breathingFactor = 0.65f + 0.30f * sin(breatheAngle);
    breatheAngle += 0.02f;
    if (breatheAngle >= 2.0f * 3.14159265f) {
      breatheAngle -= 2.0f * 3.14159265f;
    }
    lastBreatheUpdate = now;
  }

  // Get current base color from color wheel
  uint32_t baseColor = wheel(colorPos);

  // Apply the breathing factor to RGB components
  uint8_t r = (uint8_t)(((baseColor >> 16) & 0xFF) * breathingFactor);
  uint8_t g = (uint8_t)(((baseColor >> 8) & 0xFF) * breathingFactor);
  uint8_t b = (uint8_t)((baseColor & 0xFF) * breathingFactor);

  uint32_t finalColor = _strip.Color(r, g, b);

  // Set all pixels on the base to the same color
  for (int i = 0; i < _strip.numPixels(); i++) {
    _strip.setPixelColor(i, finalColor);
  }
  if (_flashColumn < _strip.numPixels() && millis() < _flashUntil) {

    _strip.setPixelColor(_flashColumn, _strip.Color(255, 255, 255));
  } else {
    _flashColumn = 255;
  }

  _strip.show();
}

void Lighting::flashColumn(uint8_t column) {

  if (column >= _strip.numPixels()) {
    return;
  }

  _flashColumn = column;
  _flashUntil = millis() + 100;
}

void Lighting::rainbow() {
  static uint8_t j = 0;
  static uint32_t lastUpdate = 0;

  uint32_t now = millis();
  if (now - lastUpdate > 10) { // advance hue every 10 ms
    j++;
    lastUpdate = now;
  }

  for (int i = 0; i < _strip.numPixels(); i++) {
    uint8_t pos = ((uint32_t)i * 256 / _strip.numPixels() + j) & 255;
    _strip.setPixelColor(i, wheel(pos));
  }
  _strip.show();
}

void Lighting::loop() {
  if (state.fnHeld) {
    rainbow();
  } else {
    ambientBaseGlow();
  }
}
