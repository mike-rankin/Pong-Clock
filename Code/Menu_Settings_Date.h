#ifndef MENU_SETTINGS_DATE_H
#define MENU_SETTINGS_DATE_H

#include <Arduino.h>
#include "Menu.h"

class SettingsDateMenu : public Menu {
public:
  SettingsDateMenu();
  bool update();
  void button1();
  void button2();
  void draw(Adafruit_GFX* display) const;
private:
  uint8_t selection;
};

#endif
