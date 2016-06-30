#ifndef CLOCKFACE_DIGITAL_H
#define CLOCKFACE_DIGITAL_H

#include <Adafruit_GFX.h>
#include "Clockface.h"

class ClockfaceDigital : public Clockface {
public:
  void draw(Adafruit_GFX* display) const;
};

#endif
