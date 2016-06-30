#ifndef MENU_SETTINGS_H
#define MENU_SETTINGS_H

#include <Arduino.h>
#include "Menu.h"

class SettingsMenu : public Menu {
public:
  SettingsMenu();
  bool update();
  void button1();
  void button2();
  void draw(Adafruit_GFX* display) const;
protected:
  uint8_t selection;
};

#endif
