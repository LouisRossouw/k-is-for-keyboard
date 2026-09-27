#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Wire.h>

class Display {
public:
  Display(int pinSDA, int pinSCL, int textSize = 1);

  void begin();
  void showMessage(const String &msg, int textSize = -1);
  void loop();

private:
  int _pinSDA;
  int _pinSCL;
  int _textSize;

  Adafruit_SSD1306 _display;
};

#endif
