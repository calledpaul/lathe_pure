#ifndef MANUALENCODER_H
#define MANUALENCODER_H

#include "Utils.h"
#include "RotaryEncoder.h"
#include "OneButton.h"

class ManualEncoder : public Tickable {
private:  
  int _counter=-999, c=0, _min=0, _max=10;
  callbackFnInt _changeFn;
  RotaryEncoder _encoder;
  GPIO<PIN_MANUAL_ENCODER_BUTTON> manualEncoderButton;
  OneButton button = OneButton(1);
  bool _progressiveCounter = false;
public:
  bool enabled = true;
  
  ManualEncoder() = default; 
  virtual void init() {
    manualEncoderButton.pullup();
    _encoder.init();
  };
  void configureCallback(callbackFnInt changeFn) { 
    _changeFn = changeFn;
  }
  void configureCallback(callbackFnInt changeFn, callbackFunction clickFn) { 
    _changeFn = changeFn;
    if(clickFn) button.attachClick(clickFn);
  }
  void configureDefaults(int min, int max, int def, bool progressiveCounter = false) { 
    _counter = def;
    _min = min;
    _max = max;
    _progressiveCounter = progressiveCounter;
    bool enabled = true;
    if (_changeFn) _changeFn(_counter);
  }
  virtual void tick() {
    if (!enabled) return;
    button.tick(manualEncoderButton);
    _encoder.poll();
    c = _encoder.getChange(_progressiveCounter);
    if (!c) return;
    //slow mode
    if(isLongPressed()) c = c > 0 ? 1 : -1;
    int oldCounter = _counter;
    _counter += c;
    if (_counter < _min) _counter = _min;
    else if (_counter > _max) _counter = _max;
    if (_changeFn && oldCounter != _counter) _changeFn(_counter);
  }
  int val() {
    return _counter;
  }
  bool isLongPressed() {
    return button.isLongPressed();
  }
};

/*
void change(int c) {}
void click() {}
ManualEncoder manualEncoder;
manualEncoder.init();
manualEncoder.configureDefaults(2, 20, 10);
manualEncoder.configureCallback(change, click);
*/
#endif