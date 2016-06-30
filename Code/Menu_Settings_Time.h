#ifndef MENU_SETTINGS_TIME_H
#define MENU_SETTINGS_TIME_H

#include <Arduino.h>
#include "Menu.h"

class SettingsTimeMenu : public Menu {
public:
  SettingsTimeMenu();
  bool update();
  void button1();
  void button2();
  void draw(Adafruit_GFX* display) const;
private:
  uint8_t selection;
};

#endif
