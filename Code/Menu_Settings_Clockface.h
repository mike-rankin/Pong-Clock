#ifndef MENU_SETTINGS_CLOCKFACE_H
#define MENU_SETTINGS_CLOCKFACE_H

#include <Arduino.h>
#include "Menu.h"

class SettingsClockfaceMenu : public Menu {
public:
  SettingsClockfaceMenu();
  bool update();
  void button1();
  void button2();
  void draw(Adafruit_GFX* display) const;
private:
  uint8_t selection;
};

#endif
