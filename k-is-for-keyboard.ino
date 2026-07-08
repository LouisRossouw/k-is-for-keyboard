#include "keyboard.h"
#include "keyboard_config.h"

// TODO; We can pass different configs for different hardware!
KeyboardConfig config;
Keyboard keyboard(config);

void setup() { keyboard.begin(); }
void loop() { keyboard.loop(); }