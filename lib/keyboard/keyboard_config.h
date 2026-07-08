#pragma once

struct KeyboardConfig {
  // OLED Display
  int oledSda = 0; // SDA
  int oledScl = 1; // Scl
  int textSize = 1;

  // Addressable leds; We only need the data pin,
  // TODO; find the correct pin
  int led0 = 10;

  // TODO; set the correct rows & cols with the new keyboard!
  int rows = 3;
  int cols = 3;
};