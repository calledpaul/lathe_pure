#ifndef ShaftEncoder_h
#define ShaftEncoder_h 1

#include "Utils.h"


class ShaftEncoder {
private:
  long shaftEncoderTicks = 0, prevShaftEncoderTicks = 0;
  int realShaftEncoderTicksCount = SHAFT_ENCODER_FULL_TICKS, oneRotationShaftEncoderTicks = 0;
  unsigned int shaftSpeed = 0;
  callbackFn _tickCallback, _zeroPointTickCallback;
  GPIO<PIN_SHAFT_ENCODER_A> encoderA;
  GPIO<PIN_SHAFT_ENCODER_B> encoderB;
  GPIO<PIN_SHAFT_ENCODER_ZERO> encoderZero;
  Timer timer = Timer(250); // 4 times per second
  bool tickCallbackEnabled = false;
  bool enableOnZero = false;
public:
  
  init() {
    encoderA.pullup();
    encoderB.pullup();
    encoderZero.pullup();
  }

  void disable() {
    tickCallbackEnabled = false;
    enableOnZero = false;
  }

  void enable(bool immediate = true) {
    if (immediate) tickCallbackEnabled = true;
    else enableOnZero = true;
    p(tickCallbackEnabled);
  }

  void configureCallback(callbackFn tickCallback) {
    disable();
    _tickCallback = tickCallback;
  }

  void isr() {
    oneRotationShaftEncoderTicks++;
    if (_tickCallback && tickCallbackEnabled) {
      _tickCallback();
    }
  }

  void zeroPointISR() {
    if (abs(oneRotationShaftEncoderTicks) > realShaftEncoderTicksCount-40 
        && abs(oneRotationShaftEncoderTicks) <= realShaftEncoderTicksCount 
        && realShaftEncoderTicksCount != abs(oneRotationShaftEncoderTicks)) 
    {
        shaftEncoderTicks += (oneRotationShaftEncoderTicks > 0 ? 1 : -1)*(realShaftEncoderTicksCount - abs(oneRotationShaftEncoderTicks));
    }
    oneRotationShaftEncoderTicks = 0;
    if (enableOnZero) {
      tickCallbackEnabled = true;
    }
    if (_zeroPointTickCallback) _zeroPointTickCallback();
  }

  int speed() {
    return shaftSpeed;
  }

  int getShaftAngle() {      
    return oneRotationShaftEncoderTicks;
  }

  void tick() {
    if (!timer.tick()) return;
    int delta = shaftEncoderTicks - prevShaftEncoderTicks;    
    shaftSpeed = delta > 0 ? abs((delta >> 2) * 1.875) : 0; // delta / 32 * 15
    prevShaftEncoderTicks = shaftEncoderTicks;
  }

  long ticks() {
    return shaftEncoderTicks;
  }

  void setZeroPointTickCallback(callbackFn shaftZeroPointTick) {
    _zeroPointTickCallback = shaftZeroPointTick;
  }
};

ShaftEncoder shaftEncoder;

void shaftEncoderISR() {
  shaftEncoder.isr(); 
}
void shaftEncoderZeroISR() {
  p("zero");
  shaftEncoder.zeroPointISR();
}

void shaftEncoderInit() {
  shaftEncoder.init();
  attachInterrupt(INTERRUPT_SHAFT_ENCODER_A, shaftEncoderISR, CHANGE); //or rising
  attachInterrupt(INTERRUPT_SHAFT_ENCODER_ZERO, shaftEncoderZeroISR, RISING);
}


#endif




