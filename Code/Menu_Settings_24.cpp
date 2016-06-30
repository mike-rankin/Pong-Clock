#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Menu_Settings_24.h"
#include "State.h"

// Some graphics constants
#define BLACK 0
#define WHITE 1
#define WIDTH 128
#define HEIGHT 64

Settings24hMenu::Settings24hMenu()
: Menu(MENU_SETTINGS_24H)
{}

bool Settings24hMenu::update()  {
  return state.timeMinuteUpdated;
}

void Settings24hMenu::button1() {
  state.mode24h = !state.mode24h;
  state.save();
}

void Settings24hMenu::button2() {
  switchMenu(MENU_SETTINGS);
}

void Settings24hMenu::draw(Adafruit_GFX* display) const {
  drawLayout(display, F("12/24hr mode"));

  // Selector
  display->setTextColor(WHITE);
  display->setTextSize(2);
  display->setCursor(40, 23);
  if (state.mode24h) {
    display->print(F("24hr"));
  } else {
    display->print(F("12hr"));
  }
  display->fillTriangle(
    (WIDTH / 2)    , 15,
    (WIDTH / 2) + 5, 20,
    (WIDTH / 2) - 5, 20,
    WHITE);
  display->fillTriangle(
    (WIDTH / 2)    , 45,
    (WIDTH / 2) + 5, 40,
    (WIDTH / 2) - 5, 40,
    WHITE);
}

