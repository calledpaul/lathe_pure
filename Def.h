#ifndef DEF_H
#define DEF_H

#include "Def_const.h"
#include "Def_pins.h"

	#define SHAFT_ENCODER_FULL_TICKS 2048
	#define SHAFT_ROTATION_TICKS 512
	
	#define X_STEPPER_MAX_SPEED 920 * 3
	#define X_STEPS_TO_MM 920
	#define X_AXIS_PLAY_MM 0.35

	#define Y_STEPPER_MAX_SPEED 920 * 3
	#define Y_STEPS_TO_MM 920
	#define Y_AXIS_PLAY_MM 0.12

	#define SHAFT_RATIO(x) (x * 0.00598828125)

#endif
