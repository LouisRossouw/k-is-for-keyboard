#include "keys.h"

Keys::Keys(const KeyboardConfig &config) : _config(config) {}

void Keys::begin() {

  for (uint8_t row = 0; row < _config.rows; row++) {
    pinMode(_config.rowPins[row], OUTPUT);
    digitalWrite(_config.rowPins[row], HIGH);
  }

  for (uint8_t col = 0; col < _config.cols; col++) {
    pinMode(_config.colPins[col], INPUT_PULLUP);
  }
}

void Keys::loop() {

  // Don't overwrite an event that hasn't been consumed yet.
  if (_eventAvailable) {
    return;
  }

  for (uint8_t row = 0; row < _config.rows; row++) {

    digitalWrite(_config.rowPins[row], LOW);

    for (uint8_t col = 0; col < _config.cols; col++) {

      bool pressed = digitalRead(_config.colPins[col]) == LOW;

      // Raw state changed
      if (pressed != _lastState[row][col]) {
        _lastState[row][col] = pressed;
        _lastChange[row][col] = millis();
      }

      // State has been stable long enough
      if ((millis() - _lastChange[row][col]) >= DEBOUNCE_TIME) {

        if (_state[row][col] != pressed) {

          _state[row][col] = pressed;

          KeyCode key = _keymap[row][col];

          if (key == KEY_FN) {

            _fnPressed = pressed;

          } else if (key != KEY_NONE) {

            if (_fnPressed) {
              key = _fnKeymap[row][col];
            }

            if (key != KEY_NONE) {

              _event.key = key;
              _event.row = row;
              _event.col = col;
              _event.pressed = pressed;

              _eventAvailable = true;
            }
          }
        }
      }
    }

    digitalWrite(_config.rowPins[row], HIGH);

    if (_eventAvailable) {
      return;
    }
  }
}

bool Keys::getEvent(KeyEvent &event) {

  if (!_eventAvailable) {
    return false;
  }

  event = _event;

  _eventAvailable = false;

  return true;
}