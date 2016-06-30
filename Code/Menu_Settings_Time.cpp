#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Menu_Settings_Time.h"
#include "State.h"

// Grab RTC instance from .ino
extern RTC_DS1307 RTC;

// Some graphics constants
#define BLACK 0
#define WHITE 1
#define WIDTH 128
#define HEIGHT 64


SettingsTimeMenu::SettingsTimeMenu()
: Menu(MENU_SETTINGS_TIME)
, selection(0)
{}

bool SettingsTimeMenu::update() {
  return state.timeMinuteUpdated;
}

void SettingsTimeMenu::button1() {
  selection = (selection + 1) % 5;
}

void SettingsTimeMenu::button2() {
  if (selection == 4) {
    switchMenu(MENU_SETTINGS);
  } else {
    uint8_t hour = state.now.hour();
    uint8_t minute = state.now.minute();
    if (selection == 0) {
      hour = (hour + 1) % 24;
    } else if (selection == 1) {
      minute = (minute + 1) % 60;
    } else if (selection == 2) {
      hour = hour == 0 ? 23 : (hour - 1);
    } else if (selection == 3) {
      minute = minute == 0 ? 59 : (minute - 1);
    }
    state.now = DateTime(state.now.year(), state.now.month(), state.now.day(), hour, minute, 0);
    state.timeUpdated = true;
    state.timeMinuteUpdated = true;
    RTC.adjust(state.now);
  }
}

void SettingsTimeMenu::draw(Adafruit_GFX* display) const {
  drawLayout(display, F("Set Time"));

  // Time
  char buff[9];
  display->setTextSize(2);
  display->setTextColor(WHITE);
  display->setCursor(20, 23);
  snprintf_P(buff, 9, PSTR("%02d:%02d"), state.now.hour(), state.now.minute());
  display->print(buff);

  if (selection < 2) {
    display->fillTriangle(
      30 + (selection * 35), 15,
      35 + (selection * 35), 20,
      25 + (selection * 35), 20,
      WHITE);
  } else if (selection < 4) {
    display->fillTriangle(
      30 + ((selection - 2) * 35), 45,
      35 + ((selection - 2) * 35), 40,
      25 + ((selection - 2) * 35), 40,
      WHITE);
  }
  if (selection == 4) {
    display->fillRect(0, 53, WIDTH, 10, WHITE);
    display->setTextColor(BLACK, WHITE);
  } else {
    display->setTextColor(WHITE);
  }
  display->setTextSize(1);
  display->setCursor(5, 54);
  display->print(F("Back"));
}

