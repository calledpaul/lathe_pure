#ifndef UTILS_H
#define UTILS_H
#include <Arduino.h>
#include "Def.h"
#include <math.h>
#include "TimedAction.h"
#include "GPIO.h"

extern "C" {
  typedef void (*callbackFn)(void);
  typedef void (*callbackFnInt)(int);
  typedef void (*callbackFnIntInt)(int, int);
  typedef void (*callbackFnIntBool)(int, bool);
  typedef bool (*callbackFnRetBool)(void);
}

class Tickable {
public:
  virtual void init();
  virtual void tick();
};

#define pp(a, b, c) Serial.print(a); Serial.print(b); Serial.println(c);  
#define p(a) Serial.println(a);

#endif

