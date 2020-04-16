#ifndef DEF_CUT_H
#define DEF_CUT_H

#include "OperationBase.h"

class Cut : OperationBase {
public:
    static void init(int mode) {
        state.flush();
        //this should be automatically triggered
        // state.ratio(10);
        if (mode == MODE_CUT_X) {
            state.mainStepper = &controls.xStepper;
        } else {
            state.mainStepper = &controls.yStepper;
        }
        controls.shaftEncoder->configureCallback(Cut::followShaft);
        controls.inputs.configureCallback(Cut::switchChange, Cut::trigger, Cut::stop);
        controls.manualEncoder.configureCallback(Cut::encoderChange);
        controls.manualEncoder.configureDefaults(1, 30, 10);
    }

    static void switchChange(int old, int current) {
        if (state.autoInProgress) return;
        if (current == OFF) {
            controls.shaftEncoder->disable();
            // controls.display.refresh();
        } else {
            // controls.display.suspend();
            state.mainStepper->setDir(current);
            controls.shaftEncoder->enable(true);
        }
    }

    static void trigger(){
        p("red");
        if (state.autoInProgress) {
            controls.shaftEncoder->disable();
            controls.display.refresh();
            state.mainStepper->returnToZero();
            state.autoInProgress = false;
        } else {
            state.mainStepper->setDir(LEFT);
            state.mainStepper->setCurrentPosition(0);
            state.autoInProgress = true;
            controls.display.suspend();
            controls.shaftEncoder->enable(true); //immediate
        }
    }

    static void stop() {
        p("stop");
        if (state.autoInProgress) {
            trigger();
        } else {
            controls.shaftEncoder->disable();
        }
    }
};

#endif