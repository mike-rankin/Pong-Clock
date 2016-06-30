#include <Arduino.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include "Menu_Clockface.h"
#include "Menu.h"
#include "State.h"
#include "Clockface_Pong.h"
#include "Clockface_Digital.h"
//#include "Clockface_Pacman.h"
#include "Clockface_Tetris.h"


ClockfaceMenu::ClockfaceMenu()
: Menu(MENU_CLOCK)
, faceType(FACE_PONG)
, face(NULL)
{
  faceType = state.current_face;
  if (faceType >= FACE_MAX) faceType = 0;
  changeMenu();
  uint8_t hour = state.now.hour();
  if (!state.mode24h && hour > 12) {
    hour = hour - 12;
  }
  face->begin(hour, state.now.minute());
}

ClockfaceMenu::~ClockfaceMenu() {
  delete face;
}

bool ClockfaceMenu::update() {
  uint8_t hour = state.now.hour();
  if (!state.mode24h && hour > 12) {
    hour = hour - 12;
  }
  face->update(hour, state.now.minute());
  // Always render
  return true;
}

void ClockfaceMenu::draw(Adafruit_GFX* display) const {
  face->draw(display);
}

void ClockfaceMenu::button1() {
  do {
  faceType = (faceType + 1) % FACE_MAX;
  } while (!(state.enabled_faces & _BV(faceType)));
  changeMenu();
}

void ClockfaceMenu::changeMenu() {
  // Switch object
  if (face) {
    delete face;
    face = NULL;
  }
  switch(faceType) {
  case FACE_PONG:
    face = new ClockfacePong();
    break;
  case FACE_DIGITAL:
    face = new ClockfaceDigital();
    break;
//  case FACE_PACMAN:
//    face = new ClockfacePacman();
//    break;
  case FACE_TETRIS:
    face = new ClockfaceTetris();
    break;
  }

  // Call begin
  uint8_t hour = state.now.hour();
  if (!state.mode24h && hour > 12) {
    hour = hour - 12;
  }
  face->begin(hour, state.now.minute());

  state.current_face = faceType;
  state.save();
}

void ClockfaceMenu::button2() {
  switchMenu(MENU_SETTINGS);
}

