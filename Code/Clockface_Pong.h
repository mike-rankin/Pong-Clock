#ifndef CLOCKFACE_PONG_H
#define CLOCKFACE_PONG_H

#include <Adafruit_GFX.h>
#include "Clockface.h"
#include "Paddle.h"
#include "Ball.h"

class ClockfacePong : public Clockface {
public:
  ClockfacePong();

  void begin(uint8_t hour, uint8_t minute);
  void update(uint8_t hour, uint8_t minute);
  void draw(Adafruit_GFX* display) const;
  void drawScore(Adafruit_GFX* display) const;
private:
  Paddle lpaddle, rpaddle;
  Ball ball;
  uint8_t lscore, rscore;
  uint8_t pause;
};

#endif
