#ifndef CLOCKFACE_H
#define CLOCKFACE_H

#include <Adafruit_GFX.h>

/*
 * The abstract interface for clock faces.
 * The only nessicary method is the draw() function, the others are
 * there only for if it helps you (like for the Pong face).
 */
class Clockface {
public:
  virtual void begin(uint8_t hour, uint8_t minute) {}
  virtual void update(uint8_t hour, uint8_t minute) {}
  virtual void draw(Adafruit_GFX* display) const = 0;
};

#endif
