#ifndef DEF_INPUTS_H
#define DEF_INPUTS_H

#include "Utils.h"

class Inputs : public Tickable {
private:
  GPIO<PIN_LEFT> pinLeft;
  GPIO<PIN_RIGHT> pinRight;
  GPIO<PIN_RED> pinRed;
  GPIO<PIN_STOP> pinStop;

  int switchState = -1, state;
  callbackFnIntInt _switchChangeFn;
  callbackFunction _stopFn;
  OneButton button = OneButton(1);
  Timer timer = Timer(200);

public:
  
  void configureCallback (callbackFnIntInt switchChangeFn, callbackFunction redFn, callbackFunction stopFn) {
    _switchChangeFn = switchChangeFn;
    _stopFn = stopFn;
    if (_switchChangeFn) _switchChangeFn(switchState, switchState);
    button.attachClick(redFn);
  }
  
  unsigned int swithState() {
    return switchState;
  }

  virtual void init() {
    pinLeft.pullup();
    pinRight.pullup();
    pinRed.pullup();
    pinStop.pullup();
  }

  virtual void tick(){
    if (!pinStop && _stopFn) _stopFn();
    button.tick(pinRed);
    if (!timer.tick()) return;
    state = OFF;
    if (!pinLeft) {
      state = LEFT;
    } else if (!pinRight) {
      state = RIGHT;
    }
    if (switchState != state) {
      int old = switchState;
      switchState = state;
      if (_switchChangeFn) _switchChangeFn(old, switchState);
    }
  }
  
};

/*void switchChange(int old, int current) {}
void trigger(){}
Inputs inputs;
inputs.configureCallback(switchChange, trigger);
inputs.init();
inputs.tick();
*/
#endif