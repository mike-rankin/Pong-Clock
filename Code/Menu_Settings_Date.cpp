#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Menu_Settings_Date.h"
#include "State.h"

// Grab RTC instance from .ino
extern RTC_DS1307 RTC;

// Some graphics constants
#define BLACK 0
#define WHITE 1
#define WIDTH 128
#define HEIGHT 64

SettingsDateMenu::SettingsDateMenu()
: Menu(MENU_SETTINGS_DATE)
, selection(0)
{}

bool SettingsDateMenu::update() {
  return state.timeMinuteUpdated;
}

void SettingsDateMenu::button1() {
  selection = (selection + 1) % 7;
}

void SettingsDateMenu::button2() {
  if (selection == 6) {
    switchMenu(MENU_SETTINGS);
  } else {
    uint16_t year = state.now.year();
    uint8_t month = state.now.month();
    uint8_t day = state.now.day();
    if (selection == 2) {
      year += 1;
    } else if (selection == 5) {
      year -= 1;
    } else if (selection == 1) {
      month = (month % 12) + 1;
    } else if (selection == 4) {
      month = month == 1 ? 12 : (month - 1);
    } else if (selection == 0) {
      day = (day % 31) + 1;
    } else if (selection == 3) {
      day = day == 1 ? 31 : (day - 1);
    }
    state.now = DateTime(year, month, day, state.now.hour(), state.now.minute(), state.now.second());
    state.timeUpdated = true;
    state.timeMinuteUpdated = true;
    RTC.adjust(state.now);
  }
}

void SettingsDateMenu::draw(Adafruit_GFX* display) const {
  drawLayout(display, F("Set Date"));

  // Date text
  display->setTextSize(2);
  display->setTextColor(WHITE);
  display->setCursor(20, 23);
  display->print(state.now.day());
  display->setCursor(50, 23);
  display->print(state.getMonthStr(state.now.month()));
  display->setCursor(90, 30);
  display->setTextSize(1);
  display->print(state.now.year());

  // Triangle selectors
  if (selection < 3) {
    display->fillTriangle(
      30 + (selection * 35), 15,
      35 + (selection * 35), 20,
      25 + (selection * 35), 20,
      WHITE);
  } else if (selection < 6) {
    display->fillTriangle(
      30 + ((selection - 3) * 35), 45,
      35 + ((selection - 3) * 35), 40,
      25 + ((selection - 3) * 35), 40,
      WHITE);
  }

  // Back item
  if (selection == 6) {
    display->fillRect(0, 53, WIDTH, 10, WHITE);
    display->setTextColor(BLACK, WHITE);
  } else {
    display->setTextColor(WHITE);
  }
  display->setTextSize(1);
  display->setCursor(5, 54);
  display->print(F("Back"));
}

