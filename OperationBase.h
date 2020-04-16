#ifndef DEF_OPERATIONBASE_H
#define DEF_OPERATIONBASE_H

#include "Controls.h"
#include "State.h"

class OperationBase {
public:

    static void encoderChange(int c) {
        state.ratio(c);
        state.stepOut = float(c) / 100;
        controls.display.speed(c);
    }

    static void followShaft() {
        float togo = state.shaftAgg + state.increment();
        int togoInt = int(togo);  
        state.shaftAgg = togo - togoInt;
        togoInt = abs(togoInt);
        while (togoInt--) {
            if (state.mainStepper != NULL) {
                state.mainStepper->runStep(togo > 0);
            }
            delayMicroseconds(10);
        }
    }
};

#endif