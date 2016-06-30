#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Paddle.h"
#include "Ball.h"

// Some graphics constants
#define BLACK 0
#define WHITE 1
#define WIDTH 128
#define HEIGHT 64

Ball::Ball(int16_t x, int16_t y, int8_t dx, int8_t dy)
: x(x), y(y), w(3), h(3), dx(dx), dy(dy)
{}

bool Ball::update(const Paddle& lpaddle, const Paddle& rpaddle) {
  x = x + dx;
  y = y + dy;
  bool hit = false;

  if (dx < 0 && x <= lpaddle.w && y >= lpaddle.y && y <= lpaddle.y + lpaddle.h) {
    dx = dx * -1;
    calcTarget();
  } else if (dx > 0 && x + w >= WIDTH - rpaddle.w && y + h >= rpaddle.y && y <= rpaddle.y + rpaddle.h) {
    dx = dx * -1;
    calcTarget();
  } else if ((dx > 0 && x >= WIDTH) || (dx < 0 && x + w < 0)) {
    hit = true;
  }

  if (y > HEIGHT - w || y < 0) {
    dy = dy * -1;
  }
  return hit;
}

void Ball::calcTarget() {
  int16_t target_x;
  uint8_t reflections;
  int16_t calc_y;

  if (dx > 0) {
    target_x = WIDTH - w;
  } 
  else {
    target_x = -1 * (WIDTH - w);
  }

  calc_y = abs(target_x * (dy / dx) + y);

  reflections = floor(calc_y / HEIGHT);

  if (reflections % 2 == 0) {
    target_y = calc_y % HEIGHT;
  } 
  else {
    target_y = HEIGHT - (calc_y % HEIGHT);
  }
}

void Ball::draw(Adafruit_GFX* display) const {
  display->fillRect(x, y, w, h, WHITE);
}

