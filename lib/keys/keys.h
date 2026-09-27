#pragma once

#include <Arduino.h>

#include "key_event.h"
#include "keyboard_config.h"
#include "keymap.h"

class Keys {

public:
  Keys(const KeyboardConfig &config);

  void begin();
  void loop();

  bool getEvent(KeyEvent &event);
  bool isFnHeld() const { return _fnPressed; }

private:
  const KeyboardConfig &_config;

  bool _state[KeyboardConfig::rows][KeyboardConfig::cols] = {};
  bool _lastState[KeyboardConfig::rows][KeyboardConfig::cols] = {};
  unsigned long _lastChange[KeyboardConfig::rows][KeyboardConfig::cols] = {};

  static constexpr unsigned long DEBOUNCE_TIME = 10;

  KeyCode _keymap[KeyboardConfig::rows][KeyboardConfig::cols] = {

      // Row 0
      {KEY_ESC, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O,
       KEY_P, KEY_NONE, KEY_BKSP},

      // Row 1
      {KEY_TB, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L,
       KEY_SEMICOLON, KEY_SINGLE_QUOTE, KEY_ENTER},

      // Row 2
      {KEY_NONE, KEY_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M,
       KEY_LESS_THAN, KEY_GREATER_THAN, KEY_FORWARD_SLASH, KEY_SHIFT},

      // Row 3
      {
          KEY_NONE,
          KEY_CTRL,
          KEY_ALT,
          KEY_SPACE,
          KEY_SPACE,
          KEY_NONE,
          KEY_NONE,
          KEY_NONE,
          KEY_NONE,
          KEY_NONE,
          KEY_SPACE,
          KEY_FN,
          KEY_CTRL,
      }};

  KeyCode _fnKeymap[KeyboardConfig::rows][KeyboardConfig::cols] = {
      {KEY_HELLO, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
       KEY_0, KEY_NONE, KEY_BKSP},

      {KEY_TB, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L,
       KEY_SEMICOLON, KEY_SINGLE_QUOTE, KEY_ENTER},

      {KEY_NONE, KEY_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M,
       KEY_LESS_THAN, KEY_GREATER_THAN, KEY_FORWARD_SLASH, KEY_SHIFT},

      {KEY_NONE, KEY_CTRL, KEY_ALT, KEY_SPACE, KEY_SPACE, KEY_NONE, KEY_NONE,
       KEY_NONE, KEY_NONE, KEY_NONE, KEY_SPACE, KEY_FN, KEY_CTRL}};

  bool _fnPressed = false;

  KeyEvent _event;
  bool _eventAvailable = false;
};