#ifndef Stepper_h
#define Stepper_h

#include <Utils.h>
#include "AccelStepper.h"

class AStepper : public AccelStepper {
  protected:
    int signedDir[2] = {-1, 1};
  public:
    float play = 0.0;    
    long referencePoint = 0;
    long stepsToMM = 0;
    long safeSpeed = 0;
    callbackFnRetBool emergencyFunc;

    AStepper(float playVal, long stepsToMMVal, long maxSpeed) : play(playVal), stepsToMM(stepsToMMVal), AccelStepper(AccelStepper::DRIVER, 0, 0) {
      setMaxSpeed(maxSpeed);
      safeSpeed = maxSpeed >> 1;
    }
    
    // virtual void enableOutputs() {}

    void setDir(int dir) {
      setSpeed(1 * signedDir[dir]);
    }

    void stepMMremovePlay(float mm, int direction) {
      removePlay(direction);      
      setCurrentPosition(0);
      moveTo(mm * stepsToMM);
      setMaxSafeSpeed(direction);
      stepContinuousToDestination();
    }

    void returnToZero() {
      removePlay(RIGHT);
      moveTo(0);
      setMaxSafeSpeed(RIGHT);
      stepContinuousToDestination();
    }

    void setMaxSafeSpeed(int direction) {
      setSpeed(safeSpeed * signedDir[direction]);
    }

    void removePlay(int direction) {
      unsigned long currentPos = currentPosition(), spd = speed(), target = targetPosition();
      setCurrentPosition(0);
      setMaxSafeSpeed(direction);
      
      long finalPos = round(play * stepsToMM * signedDir[direction]);
      while (currentPosition() != finalPos) runSpeed();

      // set original logical values
      setCurrentPosition(currentPos);
      moveTo(target);
      setSpeed(spd);
    }

    void stepContinuousToDestination() {
      while (distanceToGo()) {
        if (emergencyFunc && emergencyFunc()) break;
        runSpeedToPosition();
      }
    }

    //  void setSpeedRemovePlay(float newSpeed) {
    //   // validate direction change
    //   if ((speed() < 0 && newSpeed > 0) || (speed() > 0 && newSpeed < 0)){
    //     removePlay(newSpeed > 0 ? 1 : 0);
    //   }
    //   setSpeed(newSpeed);
    // }    

    // void stepMMOld(float mm) {
    //   stepContinuous(round(mm * stepsToMM));
    // }

    // void stepContinuous(long steps, bool toPosition = true) {
    //   long snapshot = currentPosition();
    //   while (abs(snapshot - currentPosition()) < steps) {
    //     if (emergencyFunc && emergencyFunc()) break;
    //     if(toPosition)
    //       runSpeedToPosition();
    //     else
    //       runSpeed();
    //   }
    // }

};


class XStepper : public AStepper {
  public:
    XStepper() : AStepper(X_AXIS_PLAY_MM, X_STEPS_TO_MM, X_STEPPER_MAX_SPEED) {}
    GPIO<PIN_X_AXIS_STEPPER_POWER> powerMode;
    GPIO<PIN_X_AXIS_STEPPER_A> stepA;
    GPIO<PIN_X_AXIS_STEPPER_B> stepB;
    void init() {
      powerMode.output();
      stepA.output();
      stepB.output();
    }
    void on() {
      powerMode.write(true);
    }
    void off() {
      powerMode.write(false);
    }

  protected:  
  	virtual void setOutputPins(uint8_t mask) {
      stepA.write((mask & (1 << 0)) ? (HIGH ^ _pinInverted[0]) : (LOW ^ _pinInverted[0]));
      stepB.write((mask & (1 << 1)) ? (HIGH ^ _pinInverted[1]) : (LOW ^ _pinInverted[1]));
  	}
};


class YStepper : public AStepper {
  public:
    YStepper() : AStepper(Y_AXIS_PLAY_MM, Y_STEPS_TO_MM, Y_STEPPER_MAX_SPEED) {}
    GPIO<PIN_Y_AXIS_STEPPER_POWER> powerMode;
    GPIO<PIN_Y_AXIS_STEPPER_A> stepA;
    GPIO<PIN_Y_AXIS_STEPPER_B> stepB;
    void init() {
      powerMode.output();
      stepA.output();
      stepB.output();
    }
    void on() {
      powerMode.write(true);
    }
    void off() {
      powerMode.write(false);
    }
  protected:
  	virtual void setOutputPins(uint8_t mask) {
      stepA = (mask & (1 << 0)) ? (HIGH ^ _pinInverted[0]) : (LOW ^ _pinInverted[0]);
      stepB = (mask & (1 << 1)) ? (HIGH ^ _pinInverted[1]) : (LOW ^ _pinInverted[1]);
  	}
};


#endif