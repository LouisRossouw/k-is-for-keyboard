#include "keyboard.h"
#include "USB.h"
#include "USBHIDKeyboard.h"
#include "esp_bt.h"

USBHIDKeyboard hidKeyboard;

Keyboard::Keyboard(const KeyboardConfig &cfg)
    : config(cfg), lighting(state, config.led0),
      display(config.oledSda, config.oledScl, config.textSize), keys(config) {}

void Keyboard::begin() {
  Serial.begin(115200);

  Serial.println("=== SETUP START ===");
  Serial.println("Keyboard starting..");

  hidKeyboard.begin();
  USB.begin();

  // Disable Bluetooth
  if (esp_bt_controller_get_status() == ESP_BT_CONTROLLER_STATUS_ENABLED) {
    esp_bt_controller_disable();
    esp_bt_controller_deinit();
  }

  display.begin();
  keys.begin();
  lighting.begin();
  lighting.testStrip(); // TODO: remove once strip is confirmed working

  Serial.println("=== SETUP END ===");
}

void Keyboard::loop() {
  keys.loop();

  // Keys consumes KEY_FN internally — read its state directly
  state.fnHeld = keys.isFnHeld();

  KeyEvent event;

  if (keys.getEvent(event)) {

    uint8_t hidKey = keyToHID(event.key);

    if (hidKey != 0) {
      if (event.pressed) {
        hidKeyboard.press(hidKey);
      } else {
        hidKeyboard.release(hidKey);
      }
    }

    if (event.pressed) {
      char msg[32];

      snprintf(msg, sizeof(msg), "%s %02X %02X", keyName(event.key), event.key,
               hidKey);

      display.showMessage(msg, 2);
      lighting.flashColumn(event.col);
    } else {
      display.showMessage("", 2);
    }
  }

  lighting.loop();
  display.loop();
}

uint8_t keyToHID(KeyCode key) {
  switch (key) {

  case KEY_A:
    return 'a';
  case KEY_B:
    return 'b';
  case KEY_C:
    return 'c';
  case KEY_D:
    return 'd';
  case KEY_E:
    return 'e';
  case KEY_F:
    return 'f';
  case KEY_G:
    return 'g';
  case KEY_H:
    return 'h';
  case KEY_I:
    return 'i';
  case KEY_J:
    return 'j';
  case KEY_K:
    return 'k';
  case KEY_L:
    return 'l';
  case KEY_M:
    return 'm';
  case KEY_N:
    return 'n';
  case KEY_O:
    return 'o';
  case KEY_P:
    return 'p';
  case KEY_Q:
    return 'q';
  case KEY_R:
    return 'r';
  case KEY_S:
    return 's';
  case KEY_T:
    return 't';
  case KEY_U:
    return 'u';
  case KEY_V:
    return 'v';
  case KEY_W:
    return 'w';
  case KEY_X:
    return 'x';
  case KEY_Y:
    return 'y';
  case KEY_Z:
    return 'z';

  case KEY_1:
    return '1';
  case KEY_2:
    return '2';
  case KEY_3:
    return '3';
  case KEY_4:
    return '4';
  case KEY_5:
    return '5';
  case KEY_6:
    return '6';
  case KEY_7:
    return '7';
  case KEY_8:
    return '8';
  case KEY_9:
    return '9';
  case KEY_0:
    return '0';

  case KEY_BKSP:
    return 0x08; // _asciimap → HID 0x2A

  case KEY_TB:
    return 0x09; // _asciimap → HID 0x2B

  case KEY_ENTER:
    return 0x0A; // _asciimap → HID 0x28

  case KEY_SPACE:
    return 0x20; // _asciimap → HID 0x2C

  case KEY_ESC:
    return 0xB1; // special key → HID 0x29

  // Modifier keys (0x80–0x87 range sets modifier bits)
  case KEY_SHIFT:
    return 0x81;
  case KEY_CTRL:
    return 0x80;
  case KEY_ALT:
    return 0x82;

  default:
    return 0;
  }
}