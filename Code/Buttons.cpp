
#include <Arduino.h>
#include "Buttons.h"

#define LOCKOUT_TIME 30

Button::Button(uint8_t pin)
: timer(0)
, pin(pin)
{
  state.stable = false;
  state.interrupt = false;
}

void Button::interrupt() {
  state.interrupt = true;
}

bool Button::update() {
  bool changed = false;
  noInterrupts();
  uint16_t now = millis();
  if (state.stable == false && state.interrupt && now - timer > LOCKOUT_TIME) {
    changed = true;
    state.stable = true;
    timer = now;
  }
  state.interrupt = false;
  if (state.stable && now - timer > LOCKOUT_TIME) {
    if (digitalRead(pin) == false) {
      state.stable = false;
      changed = true;
      timer = now;
    }
  }
  interrupts();
  return changed;
}

bool Button::read() const {
  return state.stable;
}

