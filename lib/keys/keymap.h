#pragma once

#include <stdint.h>

enum KeyCode : uint8_t {
  KEY_NONE,
  KEY_HELLO,

  KEY_ESC,

  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,
  KEY_0,

  KEY_Q,
  KEY_W,
  KEY_E,
  KEY_R,
  KEY_T,
  KEY_Y,
  KEY_U,
  KEY_I,
  KEY_O,
  KEY_P,

  KEY_A,
  KEY_S,
  KEY_D,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_J,
  KEY_K,
  KEY_L,

  KEY_Z,
  KEY_X,
  KEY_C,
  KEY_V,
  KEY_B,
  KEY_N,
  KEY_M,

  KEY_SEMICOLON,
  KEY_SINGLE_QUOTE,

  KEY_LESS_THAN,
  KEY_GREATER_THAN,
  KEY_FORWARD_SLASH,

  KEY_SPACE,
  KEY_ENTER,
  KEY_BKSP,
  KEY_TB,
  KEY_SHIFT,
  KEY_CTRL,
  KEY_ALT,
  KEY_FN
};

inline const char *keyName(KeyCode key) {

  switch (key) {
  case KEY_ESC:
    return "ESC";

  case KEY_HELLO:
    return "HELLO";

  case KEY_1:
    return "1";
  case KEY_2:
    return "2";
  case KEY_3:
    return "3";
  case KEY_4:
    return "4";
  case KEY_5:
    return "5";
  case KEY_6:
    return "6";
  case KEY_7:
    return "7";
  case KEY_8:
    return "8";
  case KEY_9:
    return "9";
  case KEY_0:
    return "0";

  case KEY_Q:
    return "Q";
  case KEY_W:
    return "W";
  case KEY_E:
    return "E";
  case KEY_R:
    return "R";
  case KEY_T:
    return "T";
  case KEY_Y:
    return "Y";
  case KEY_U:
    return "U";
  case KEY_I:
    return "I";
  case KEY_O:
    return "O";
  case KEY_P:
    return "P";

  case KEY_A:
    return "A";
  case KEY_S:
    return "S";
  case KEY_D:
    return "D";
  case KEY_F:
    return "F";
  case KEY_G:
    return "G";
  case KEY_H:
    return "H";
  case KEY_J:
    return "J";
  case KEY_K:
    return "K";
  case KEY_L:
    return "L";

  case KEY_Z:
    return "Z";
  case KEY_X:
    return "X";
  case KEY_C:
    return "C";
  case KEY_V:
    return "V";
  case KEY_B:
    return "B";
  case KEY_N:
    return "N";
  case KEY_M:
    return "M";

  case KEY_SEMICOLON:
    return ";";
  case KEY_SINGLE_QUOTE:
    return "'";

  case KEY_LESS_THAN:
    return "<";
  case KEY_GREATER_THAN:
    return ">";
  case KEY_FORWARD_SLASH:
    return "/";

  case KEY_SPACE:
    return "SPACE";
  case KEY_ENTER:
    return "ENTER";
  case KEY_BKSP:
    return "BACKSPACE";
  case KEY_TB:
    return "TAB";
  case KEY_SHIFT:
    return "SHIFT";
  case KEY_CTRL:
    return "CTRL";
  case KEY_ALT:
    return "ALT";
  case KEY_FN:
    return "FN";

  default:
    return "NONE";
  }
}