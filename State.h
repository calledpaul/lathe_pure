#ifndef DEF_STATE_H
#define DEF_STATE_H

#include "Stepper.h"

class State {
private:
    float precomputedIncrement = 0;
public:
    bool autoInProgress;
    float shaftAgg;
    AStepper *mainStepper;
    int dir;
    float stepOut;

    State() {
        flush();
    }

    void flush() {
        autoInProgress = false;
        shaftAgg = 0;
        precomputedIncrement = 0;
        mainStepper = NULL;
        dir = -1;
        stepOut = 0;
    }
    void ratio(int r) {
        precomputedIncrement = SHAFT_RATIO(r);
        p(precomputedIncrement);
    }
    float increment() {
        return precomputedIncrement;
    }
};

State state;

#endif