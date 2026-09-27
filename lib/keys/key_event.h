#pragma once

#include "keymap.h"

struct KeyEvent {
  KeyCode key;

  uint8_t row;
  uint8_t col;

  bool pressed;
};