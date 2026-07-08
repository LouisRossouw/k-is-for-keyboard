#pragma once

#include "display.h"
#include "keyboard_config.h"
#include "keyboard_state.h"
#include "keys.h"
#include "lights.h"

class Keyboard {
public:
  Keyboard(const KeyboardConfig &config);

  void begin();
  void loop();

private:
  KeyboardConfig config;
  KeyboardState state;

  Lighting lighting;
  Display display;
  Keys keys;
};