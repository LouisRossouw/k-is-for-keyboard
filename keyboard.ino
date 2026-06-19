#include "esp_bt.h"
#include "secrets.h"

const char *deviceName = "esp32 keyboard";

void setup() {

  Serial.begin(115200);
  Serial.println(deviceName);

  // Disable Bluetooth
  if (esp_bt_controller_get_status() == ESP_BT_CONTROLLER_STATUS_ENABLED) {
    esp_bt_controller_disable();
    esp_bt_controller_deinit();
  }

};

void loop() {
  // loops here
}
