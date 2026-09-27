
#pragma once

enum class KeyboardMode { Normal, Media, Macro, Settings };

struct KeyboardState {
  KeyboardMode mode = KeyboardMode::Normal;

  uint8_t brightness = 50;
  bool bluetoothEnabled = false;
  bool needsDisplayUpdate = true;
  bool fnHeld = false;
};
