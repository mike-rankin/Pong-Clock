#ifndef CLOCKFACE_PACMAN_H
#define CLOCKFACE_PACMAN_H

#include <Adafruit_GFX.h>
#include "Clockface.h"

class ClockfacePacman : public Clockface {
public:
  ClockfacePacman();
  void update(uint8_t hour, uint8_t minute);
  void draw(Adafruit_GFX* display) const;
private:
  uint8_t dots_x, blinky_x, die_timer;
};

#endif
