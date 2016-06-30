#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Menu_Settings_Clockface.h"
#include "Menu_Clockface.h"
#include "State.h"

// Some graphics constants
#define BLACK 0
#define WHITE 1
#define WIDTH 128
#define HEIGHT 64

SettingsClockfaceMenu::SettingsClockfaceMenu()
: Menu(MENU_SETTINGS_CLOCKFACE)
, selection(0)
{}

bool SettingsClockfaceMenu::update() {
  return state.timeMinuteUpdated;
}

void SettingsClockfaceMenu::button1() {
  selection = (selection + 1) % (FACE_MAX+1);
}

void SettingsClockfaceMenu::button2() {
  if (selection == FACE_MAX) {
    switchMenu(MENU_SETTINGS);
  } else {
    state.enabled_faces ^= _BV(selection);
    state.save();
  }
}

void SettingsClockfaceMenu::draw(Adafruit_GFX* display) const {
  drawLayout(display, F("Clockfaces"));

  // Menu Items
  for (uint8_t i = 0; i < FACE_MAX+1; ++i) {
    display->setCursor(5, 13 + (i * 10));
    if (selection == i) {
      display->setTextColor(BLACK, WHITE);
      display->fillRect(
        0    , 12 + (i * 10),
        WIDTH, 9,
        WHITE);
    } else {
      display->setTextColor(WHITE);
    }
    if (i == FACE_MAX) {
      display->print(F("Back"));
    } else {
      if (state.enabled_faces & _BV(i)) {
        display->print('*');
      } else {
        display->print(' ');
      }
      switch (i) {
      case FACE_PONG:
        display->print(F(" Pong"));
        break;
      case FACE_DIGITAL:
        display->print(F(" Digital"));
        break;
//      case FACE_PACMAN:
//        display->print(F(" Pacman"));
//        break;
      case FACE_TETRIS:
        display->print(F(" Tetris"));
        break;
      }
    }
  }
}

