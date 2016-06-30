#ifndef PADDLE_H
#define PADDLE_H

class Adafriut_GFX;

struct Paddle {
  Paddle(int16_t x, int16_t y);
  void update(uint8_t target_y, int8_t ball_dx, bool should_miss);
  void draw(Adafruit_GFX* display) const;

  int16_t x, y;
  uint8_t w, h;
  int8_t d;
};

#endif
