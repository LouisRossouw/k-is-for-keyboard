#ifndef LIGHTS_H
#define LIGHTS_H

#include "Arduino.h"
#include "keyboard_state.h"
#include <Adafruit_NeoPixel.h>

#define STRIP_PIN 10
#define STRIP_COUNT 16 // Change to your actual LED count

class Lighting {

public:
  Lighting(KeyboardState &state, int pin0);

  void begin();
  void connected(int delayMs);

  void lightupPull(int delayMs);
  void lightupPush(int delayMs);

  void blink(int times, int delayMs);
  void builtInblink(int times, int highDelayMs, int lowDelayMs);
  void disconnected(int times, int delayMs);

  void reconnectAttempt(int times, int delayMs);
  void error(int times, int delayMs);
  void builtInLedOff();
  void off();
  void testStrip(); // Lights all LEDs red to verify strip is working

  void loop();

private:
  KeyboardState &state;

  int _pin0; // Data
  Adafruit_NeoPixel _strip;

  uint32_t wheel(uint8_t pos); // Maps 0-255 to a rainbow colour
};

#endif