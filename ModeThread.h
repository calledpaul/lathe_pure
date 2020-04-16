#ifndef DEF_THREAD_H
#define DEF_THREAD_H

#include "OperationBase.h"

class Thread : OperationBase {
public:
    static void init(int mode) {
        state.flush();
        //this should be automatically triggered        
        //state.ratio(100);
        state.mainStepper = &controls.xStepper;
        state.dir = mode == MODE_THREAD_EXTERNAL ? OUTSIDE : INSIDE;
        
        controls.shaftEncoder->configureCallback(Thread::followShaft);
        controls.inputs.configureCallback(Thread::switchChange, Thread::trigger, Thread::stop);
        controls.manualEncoder.configureCallback(Thread::encoderChange);
        controls.manualEncoder.configureDefaults(30, 400, 100, true);
    }

    // no function in thread mode
    static void switchChange(int old, int current) {}

    static void trigger(){
        if (state.autoInProgress) {
            controls.shaftEncoder->disable();

            controls.yStepper.stepMMremovePlay(state.stepOut, state.dir);
            state.mainStepper->returnToZero();
            controls.yStepper.stepMMremovePlay(state.stepOut, !state.dir);

            state.autoInProgress = false;
            controls.manualEncoder.enabled = true;
        } else {
            state.mainStepper->setDir(LEFT);
            state.mainStepper->setCurrentPosition(0);
            state.autoInProgress = true;
            controls.display.suspend();
            controls.manualEncoder.enabled = false;
            controls.shaftEncoder->enable(false); //sync with Zero tick    
        }
    }

    static void stop() {
        if (state.autoInProgress) trigger();
    }
};

#endif