#ifndef DEF_CONTROLS_H
#define DEF_CONTROLS_H

#include "ManualEncoder.h"
#include "Modes.h"
#include "Inputs.h"
#include "ShaftEncoder.h"
#include "Stepper.h"
#include "Display.h"

class Controls {
  public:
    Inputs inputs;
    ManualEncoder manualEncoder;
    Modes mode;
    ShaftEncoder *shaftEncoder;    
    XStepper xStepper;
    YStepper yStepper;
    Display display;

    Controls(ShaftEncoder *enc) : shaftEncoder(enc) {}

    void init() {
        display.init();
        inputs.init();
        manualEncoder.init();
        mode.init();
        xStepper.init();
        xStepper.on();
        yStepper.init();
        yStepper.on();
        shaftEncoderInit();
    }
    void tick() {
        inputs.tick();
        manualEncoder.tick();
        mode.tick();
        shaftEncoder->tick();
    }
};

Controls controls(&shaftEncoder);

#endif