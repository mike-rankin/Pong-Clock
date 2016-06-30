#ifndef BALL_H
#define BALL_H

class Adafruit_GFX;
#include "Paddle.h"

struct Ball {
  Ball(int16_t x, int16_t y, int8_t dx, int8_t dy);
  
  bool update(const Paddle& lpaddle, const Paddle& rpaddle);
  void calcTarget();
  void draw(Adafruit_GFX* display) const;

  int16_t x, y;
  uint8_t w, h;
  int8_t dx, dy;
  uint8_t target_y;
};

#endif
