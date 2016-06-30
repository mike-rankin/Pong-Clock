#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Menu.h"
#include "Menu_Settings.h"
#include "Menu_Settings_24.h"
#include "Menu_Settings_Time.h"
#include "Menu_Settings_Date.h"
#include "Menu_Settings_Brightness.h"
#include "Menu_Settings_Clockface.h"
#include "Menu_Clockface.h"
#include "State.h"

// Grab RTC instance from .ino
extern RTC_DS1307 RTC;
extern Menu* menu;

// Where should I change to on next update.
// Check switchMenu() and updateMenu().
Menu_selection nextMenu;

// Some graphics constants
#define BLACK 0
#define WHITE 1
#define WIDTH 128
#define HEIGHT 64


// Unfortunately I couldnt use virtual methods in here
// because it was taking up way to much RAM.
// So here I do manual virtual methods...
bool Menu::update() {
  switch(type) {
    case MENU_SETTINGS:
      return ((SettingsMenu*)this)->update();
    case MENU_SETTINGS_24H:
      return ((Settings24hMenu*)this)->update();
    case MENU_SETTINGS_TIME:
      return ((SettingsTimeMenu*)this)->update();
    case MENU_SETTINGS_DATE:
      return ((SettingsDateMenu*)this)->update();
    case MENU_SETTINGS_BRIGHTNESS:
      return ((SettingsBrightnessMenu*)this)->update();
    case MENU_SETTINGS_CLOCKFACE:
      return ((SettingsClockfaceMenu*)this)->update();
    case MENU_CLOCK:
      return ((ClockfaceMenu*)this)->update();
  }
}

void Menu::draw(Adafruit_GFX* display) const {
  switch(type) {
    case MENU_SETTINGS:
      ((SettingsMenu*)this)->draw(display);
      return;
    case MENU_SETTINGS_24H:
      ((Settings24hMenu*)this)->draw(display);
      return;
    case MENU_SETTINGS_TIME:
      ((SettingsTimeMenu*)this)->draw(display);
      return;
    case MENU_SETTINGS_DATE:
      ((SettingsDateMenu*)this)->draw(display);
      return;
    case MENU_SETTINGS_BRIGHTNESS:
      ((SettingsBrightnessMenu*)this)->draw(display);
      return;
    case MENU_SETTINGS_CLOCKFACE:
      ((SettingsClockfaceMenu*)this)->draw(display);
      return;
    case MENU_CLOCK:
      ((ClockfaceMenu*)this)->draw(display);
      return;
  }
}

void Menu::button1() {
  switch(type) {
    case MENU_SETTINGS:
      return ((SettingsMenu*)this)->button1();
    case MENU_SETTINGS_24H:
      return ((Settings24hMenu*)this)->button1();
    case MENU_SETTINGS_TIME:
      return ((SettingsTimeMenu*)this)->button1();
    case MENU_SETTINGS_DATE:
      return ((SettingsDateMenu*)this)->button1();
    case MENU_SETTINGS_BRIGHTNESS:
      return ((SettingsBrightnessMenu*)this)->button1();
    case MENU_SETTINGS_CLOCKFACE:
      return ((SettingsClockfaceMenu*)this)->button1();
    case MENU_CLOCK:
      return ((ClockfaceMenu*)this)->button1();
  }
}

void Menu::button2() {
  switch(type) {
    case MENU_SETTINGS:
      return ((SettingsMenu*)this)->button2();
    case MENU_SETTINGS_24H:
      return ((Settings24hMenu*)this)->button2();
    case MENU_SETTINGS_TIME:
      return ((SettingsTimeMenu*)this)->button2();
    case MENU_SETTINGS_DATE:
      return ((SettingsDateMenu*)this)->button2();
    case MENU_SETTINGS_BRIGHTNESS:
      return ((SettingsBrightnessMenu*)this)->button2();
    case MENU_SETTINGS_CLOCKFACE:
      return ((SettingsClockfaceMenu*)this)->button2();
    case MENU_CLOCK:
      return ((ClockfaceMenu*)this)->button2();
  }
}

// Function called to indicate that we want to change the menu
// It does not actually change it now, we do that later so that
// we dont delete the class that is calling this function from
// underneath it.
void switchMenu(Menu_selection s) {
  nextMenu = s;
}

void updateMenuSelection() {
  if (nextMenu >= MENU_MAX) return;
  if (menu && menu->getType() == nextMenu) return;

  // Okay we need to change. delete the old one.
  if (menu) {
    // If the menu needs a destructor, you need to do this.
    if (menu->getType() == MENU_CLOCK) {
      delete (ClockfaceMenu*)menu;
    } else {
      delete menu;
    }
    menu = NULL;
  }

  // Make the new one.
  switch(nextMenu) {
    case MENU_SETTINGS:
      menu = new SettingsMenu();
      break;
    case MENU_SETTINGS_24H:
      menu = new Settings24hMenu();
      break;
    case MENU_SETTINGS_TIME:
      menu = new SettingsTimeMenu();
      break;
    case MENU_SETTINGS_DATE:
      menu = new SettingsDateMenu();
      break;
    case MENU_SETTINGS_BRIGHTNESS:
      menu = new SettingsBrightnessMenu();
      break;
    case MENU_SETTINGS_CLOCKFACE:
      menu = new SettingsClockfaceMenu();
      break;
    case MENU_CLOCK:
      menu = new ClockfaceMenu();
      break;
  }
}

void Menu::drawLayout(Adafruit_GFX* display, const __FlashStringHelper* title) const {
  char buff[8];
  // Border
  display->drawRect(0, 0, WIDTH, HEIGHT, WHITE);

  // Title
  display->setTextColor(WHITE);
  display->setTextSize(1);
  display->setCursor(2, 2);
  uint16_t title_width = display->print(title);
  display->drawFastHLine(0, 10, title_width * 6 + 2, WHITE);
  display->drawFastVLine(title_width * 6 + 2, 0, 10, WHITE);

  // Clock
  uint8_t w = state.mode24h ? 31 : 37;
  display->fillRect(
    WIDTH - (w + 2), 0,
    (w + 2), 10,
    WHITE);
  display->drawFastHLine(WIDTH - (w + 1), 10, (w + 1), WHITE);
  display->setTextColor(BLACK, WHITE);
  if (state.mode24h) {
    display->setCursor(WIDTH - w, 2);
    snprintf_P(buff, 7, PSTR("%02d:%02d"), state.now.hour(), state.now.minute());
  } else {
    display->setCursor(WIDTH - w, 2);
    uint8_t hour = state.now.hour() % 12;
    if (hour == 0) hour = 12;
    snprintf_P(buff, 7, PSTR("%02d:%02d%c"),
      hour,
      state.now.minute(),
      state.now.hour() > 11 ? 'P' : 'A'
      );
  }
  display->print(buff);
}

