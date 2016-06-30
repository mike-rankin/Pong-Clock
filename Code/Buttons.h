#ifndef BUTTONS_H
#define BUTTONS_H

struct Button {
  Button(uint8_t pin);
  bool update();
  void interrupt();
  bool read() const;

  struct State {
    bool stable : 1;
    bool interrupt : 1;
  };
  volatile State state;
  uint16_t timer;
  uint8_t pin;
};

#endif
