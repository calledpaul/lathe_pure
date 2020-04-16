#include "Controls.h"
#include "ModeCut.h"
#include "ModeThread.h"


void modeChange(int old, int current) {
  switch(current) {
    case MODE_CUT_X:
    case MODE_CUT_Y:
    Cut::init(current);
    break;
    case MODE_THREAD_EXTERNAL:
    case MODE_THREAD_INTERNAL:
    Thread::init(current);
    break;
    case MODE_CUSTOM:
    break;
  }
  controls.display.mode(current);
}


void setup() { 
  Serial.begin(9600);
  controls.mode.configureCallback(modeChange);
  controls.init();

/*
  pinMode (29, INPUT_PULLUP);
  pinMode (30, INPUT_PULLUP);
  controls.yStepper.init();
  controls.yStepper.on();
  controls.yStepper.setMaxSpeed(3000);
  controls.yStepper.setSpeed(1000);
*/
}

void loop() {
  controls.tick();

  /*bool left = !digitalRead(29);
  bool right = !digitalRead(30);
  if (left) {
    // controls.yStepper.on();    
    // digitalWrite(6, 1);
    controls.yStepper.setSpeed(-500);
  } else if (right) {
    // digitalWrite(6, 0);
    // controls.yStepper.off();
    controls.yStepper.setSpeed(500);
  }
  if (left || right){
    controls.yStepper.runSpeed();
  }*/
}



// #include "RotaryEncoder.h"
// #include <LiquidCrystal_I2C.h>
// #include "Utils.h"

// #include "AccelStepper.h"
// #include "ShaftEncoder.h"

// #define manualEncoderButton 24

// #define MODE_1 25
// #define MODE_2 26
// #define MODE_3 27
// #define MODE_4 28


// LiquidCrystal_I2C lcd(0x27, 20, 4);
// AccelStepper xstepper(AccelStepper::DRIVER, PIN_X_AXIS_STEPPER_A, PIN_X_AXIS_STEPPER_B);
// RotaryEncoder manualEncoder(new GPIO<PIN_MANUAL_ENCODER_A>(), new GPIO<PIN_MANUAL_ENCODER_B>());

// long counter = 0;
// long c = 0;
// bool redraw = true;

// void bu() {
//   Serial.println("Zeroo");
// }


// long z = 920; 
// long maxspeed = z*4;

// void setup()
// {
//   Serial.begin(9600);
//   pinMode (manualEncoderButton, INPUT_PULLUP);
//   manualEncoder.init();
//   lcd.init();
//   lcd.backlight();

  
//   xstepper.setMaxSpeed(maxspeed);
 

//   pinMode (MODE_1, INPUT_PULLUP);
//   pinMode (MODE_2, INPUT_PULLUP);
//   pinMode (MODE_3, INPUT_PULLUP);
//   pinMode (MODE_4, INPUT_PULLUP);

//   pinMode (10, INPUT_PULLUP);

//   pinMode (29, INPUT_PULLUP);
//   pinMode (30, INPUT_PULLUP);
//   pinMode (31, INPUT_PULLUP);
//   digitalWrite(29, HIGH);
//   digitalWrite(30, HIGH);
//   digitalWrite(31, HIGH);

//   // pinMode (9, OUTPUT);
//   // digitalWrite(9, LOW);

//   // pinMode(19, INPUT_PULLUP);
//   // pinMode(18, INPUT_PULLUP);
  
//   // attachInterrupt(0, a, CHANGE);
//   //attachInterrupt(1, a, CHANGE);
//   initShaftEncoder();
//   //xstepper.setAcceleration(maxspeed/2);
//   //xstepper.setSpeed(-maxspeed);
  

//   // long z = 1840/2;
  
//   // xstepper.setMaxSpeed(z);
//   // xstepper.setAcceleration(z/2);
//   xstepper.setSpeed(100);
//   // xstepper.moveTo(z*3);
  
// }

// int prevMode = -1;
// int mode = -1;

// String buff[32];

// void writeLCD(int x, int y, String* info) {
//   int pos = y*16+x;
//   if (buff[pos] != *info) {
//     buff[pos] = *info;
//     lcd.setCursor(x, y);
//     lcd.print(*info);
//   }
// }
// int t = 0;
// void loop()
// {

//   /*writeLCD(15, 1, &String(!digitalRead(10) ? "!" : " "));
//   writeLCD(3, 1, &String(!digitalRead(29) ? "<" : " "));
//   writeLCD(4, 1, &String(!digitalRead(30) ? ">" : " "));
//   writeLCD(5, 1, &String(!digitalRead(31) ? "RUN" : "   "));
//   */
//   // if (!digitalRead(31)) {
//   //   Serial.println("bu");
//   // }
//   /*if (!digitalRead(MODE_1)) {
//     mode = 1;
//   } else if (!digitalRead(MODE_2)) {
//     mode = 2;
//   } else if (!digitalRead(MODE_3)) {
//     mode = 3;
//   } else if (!digitalRead(MODE_4)) {
//     mode = 4;
//   } else {
//      mode = 5;
//   }
//   writeLCD(0, 0, &String(mode));
  
//   if (!digitalRead(manualEncoderButton)) {
//      counter = 0;
//   }*/
//   manualEncoder.poll();
//   c = manualEncoder.getChange();
//   bool left = !digitalRead(29);
//   bool right = !digitalRead(30);
//   if (c != 0) {
//     counter += c;
//     if (counter < 1) counter = 0;
//     Serial.println((counter*10*1.0)/z);
//     if (left) {
//       xstepper.setSpeed(counter*10*-1);
//     } else if (right) {
//       xstepper.setSpeed(counter*10);
//     }
//   }
//   if (left || right){
//     xstepper.runSpeed();
//   } else {
//     // writeLCD(2, 0, &String(xstepper.speed()));
//   }

//   // if (xstepper.distanceToGo() == 0)
//   //   xstepper.moveTo(-xstepper.currentPosition());
//   // xstepper.run();

 
 
// //  if (t != shaftEncoder.speed()) {
// //    t = shaftEncoder.speed();
// //    p(t);
// //  }

// }

// ////endddddddddddddddddddd---------------------------


// /*
//  #include "ShaftEncoder.h"
//  //#include "Stepper.h"

//  void setup() {
   
//    Serial.begin(9600);
//   // xAxisStepper.setMaxSpeed(maxspeedSteps);
//   // Serial.println(maxspeedSteps);
//   // updateXAxisSpeed(maxspeedSteps/2);
//   // moveXAxisTo(50000);
// }

// int t = 0;
//  void loop() {
//   // xAxisStepper.runSpeed();
//  delay(100);
//  if (t != shaftEncoder.getShaftAngle()) {
//    t = shaftEncoder.getShaftAngle();
//    p(float(t)*62/2048);
//  }
  
//  }


// */


// /*
// #include "AccelStepper.h"

// AccelStepper xstepper(AccelStepper::DRIVER, PIN_X_AXIS_STEPPER_A, PIN_X_AXIS_STEPPER_B);

// AccelStepper ystepper(AccelStepper::DRIVER, PIN_Y_AXIS_STEPPER_A, PIN_Y_AXIS_STEPPER_B);
// void setup()
// {  
//   // pinMode(6, OUTPUT);
//   // digitalWrite(6, HIGH);

//   long z = 1600;
  
//   xstepper.setMaxSpeed(z*2);
//   xstepper.setAcceleration(z/4);
//   xstepper.moveTo(z*10);

//   ystepper.setMaxSpeed(z*2);
//   ystepper.setAcceleration(z/4);
//   ystepper.moveTo(z*10);
// }
// void loop()
// {
//     if (xstepper.distanceToGo() == 0)
//       xstepper.moveTo(-xstepper.currentPosition());
//     xstepper.run();
//     if (ystepper.distanceToGo() == 0)
//       ystepper.moveTo(-ystepper.currentPosition());
//     ystepper.run();
// }

// */
// /*
// int old = 1;
// void setup()
// {  
//   pinMode(10, INPUT_PULLUP);
//   Serial.begin(9600);
//   // digitalWrite(6, HIGH);
// }
// void loop()
// {
//     // If at the end of travel go to the other end
//     int z = digitalRead(10);
//     if (z != old) {
//       old = z;
//       Serial.println(z);
//     }
// }*/