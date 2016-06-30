#ifndef MENU_SETTINGS_BRIGHTNESS_H
#define MENU_SETTINGS_BRIGHTNESS_H

#include <Arduino.h>
#include "Menu.h"

class SettingsBrightnessMenu : public Menu {
public:
  SettingsBrightnessMenu();
  bool update();
  void button1();
  void button2();
  void draw(Adafruit_GFX* display) const;
private:
  uint8_t selection;
};

#endif
