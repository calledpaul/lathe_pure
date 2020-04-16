#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include "Utils.h"

class RotaryEncoder {
  unsigned int state, t;
  long change = 0, timestmp = 0;
  GPIO<PIN_MANUAL_ENCODER_A> mask0;
  GPIO<PIN_MANUAL_ENCODER_B> mask1;
  int ppc = 4, movement, tbl[16] = {
    0, +1, -1, 0,
    -1, 0, -2, +1,
    +1, +2, 0, -1,
    0, -1, +1, 0
  };
  unsigned int readState() {
    return (mask0 ? 0u : 1u) | (mask1 ? 0u : 2u);
  };
public:

  RotaryEncoder() : change(0), state(0) {}

  void init() {
    mask0.pullup();
    mask1.pullup();
    state = readState();
  };
  void poll() {
    t = readState();
    movement = tbl[(state << 2) | t];
    if (movement != 0) {
      change += movement;
      state = t;
    }
  };
  long getChange(bool timeDependant = false) {
    long r = 0;
    //noInterrupts();
    if (change >= ppc - 1)
      r = (change + 1) / ppc;
    else if (change <= 1 - ppc)
      r = -((1 - change) / ppc);
    change -= (r * ppc);
    //interrupts();
    if (r && timeDependant) {
      long m = millis();
      //Serial.println((m - timestmp));
      r = ((m - timestmp) > 200 ? 5 : (m - timestmp) > 50 ? 10 : 20) * r;
      timestmp = m;
    }
    return r;
  };
};

#endif




