#ifndef DEF_PIN_H
#define DEF_PIN_H

#include "Board.h"

  //switches
  #define PIN_MODE_1 BOARD::D25
  #define PIN_MODE_2 BOARD::D26
  #define PIN_MODE_3 BOARD::D27
  #define PIN_MODE_4 BOARD::D28


  // #define MODE_1 25
// #define MODE_2 26
// #define MODE_3 27
// #define MODE_4 28

  #define PIN_LEFT BOARD::D29
  #define PIN_RIGHT BOARD::D30

  #define PIN_RED BOARD::D31
  #define PIN_STOP BOARD::D10

  //stepper X
  #define PIN_X_AXIS_STEPPER_POWER BOARD::D6
  #define PIN_X_AXIS_STEPPER_A BOARD::D5
  #define PIN_X_AXIS_STEPPER_B BOARD::D4

  //stepper Y
  #define PIN_Y_AXIS_STEPPER_POWER BOARD::D9
  #define PIN_Y_AXIS_STEPPER_A BOARD::D8
  #define PIN_Y_AXIS_STEPPER_B BOARD::D7

  // manual encoder
  #define PIN_MANUAL_ENCODER_A BOARD::D22
  #define PIN_MANUAL_ENCODER_B BOARD::D23
  #define PIN_MANUAL_ENCODER_BUTTON BOARD::D24

  //shaft encoder
  #define PIN_SHAFT_ENCODER_A BOARD::D2
  #define PIN_SHAFT_ENCODER_B BOARD::D3
  #define PIN_SHAFT_ENCODER_ZERO BOARD::D18 //19

  // Interrupts
  #define INTERRUPT_SHAFT_ENCODER_A 0
  #define INTERRUPT_SHAFT_ENCODER_B 1
  #define INTERRUPT_SHAFT_ENCODER_ZERO 4

#endif