#ifndef DEF_MODES_H
#define DEF_MODES_H

#include "Utils.h"

class Modes : public Tickable {
private:
  GPIO<PIN_MODE_1> mode_1;
  GPIO<PIN_MODE_2> mode_2;
  GPIO<PIN_MODE_3> mode_3;
  GPIO<PIN_MODE_4> mode_4;
  int currentMode = -1, mode;
  callbackFnIntInt _modeChangeFn;
  Timer timer = Timer(250);

public:
  void configureCallback(callbackFnIntInt modeChangeFn) {
    _modeChangeFn = modeChangeFn;
  }
  unsigned int val() {
    return currentMode;
  }

  virtual void init() {
    mode_1.pullup();
    mode_2.pullup();
    mode_3.pullup();
    mode_4.pullup();
  }

  virtual void tick(){
    if (!timer.tick()) return;
    if (!mode_1) {
      mode = MODE_CUT_X;
    } else if (!mode_2) {
      mode = MODE_CUT_Y;
    } else if (!mode_3) {
      mode = MODE_THREAD_EXTERNAL;
    } else if (!mode_4) {
      mode = MODE_THREAD_INTERNAL;
    } else {
      mode = MODE_CUSTOM;
    }
    if (currentMode != mode) {
      int old = currentMode;
      currentMode = mode;
      if (_modeChangeFn) _modeChangeFn(old, currentMode);      
    }
  }
  
};

/*void modeChange(int old, int current) {}
Modes m;
m.init(modeChange);
m.tick();
*/
#endif