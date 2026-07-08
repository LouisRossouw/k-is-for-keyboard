#include "keyboard.h"

#include "esp_bt.h"

Keyboard::Keyboard(const KeyboardConfig &cfg)
    : config(cfg), lighting(state, config.led0),
      display(config.oledSda, config.oledScl, config.textSize),
      keys(config.rows, config.cols) {}

void Keyboard::begin() {
  Serial.begin(115200);
  Serial.println("Keyboard starting..");

  // Disable Bluetooth
  if (esp_bt_controller_get_status() == ESP_BT_CONTROLLER_STATUS_ENABLED) {
    esp_bt_controller_disable();
    esp_bt_controller_deinit();
  }

  keys.begin();
  lighting.begin();
  lighting.testStrip(); // TODO: remove once strip is confirmed working
  display.begin();
}

void Keyboard::loop() {
  keys.loop();
  lighting.loop();
  display.loop();
}