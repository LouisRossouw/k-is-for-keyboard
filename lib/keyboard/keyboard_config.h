#pragma once

#include <stdint.h>

struct KeyboardConfig {

  // =========================
  // OLED
  // =========================

  uint8_t oledSda = 9;
  uint8_t oledScl = 10;
  uint8_t textSize = 1;

  // =========================
  // LEDs
  // =========================

  uint8_t led0 = 7;

  // =========================
  // Keyboard matrix
  // =========================

  static constexpr uint8_t rows = 4;
  static constexpr uint8_t cols = 13;

  uint8_t rowPins[rows] = {40, 41, 42, 45};
  uint8_t colPins[cols] = {14, 15, 16, 17, 18, 21, 33, 34, 35, 36, 37, 38, 39};
};