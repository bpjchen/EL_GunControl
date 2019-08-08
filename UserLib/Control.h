#ifndef __CONTROL_
#define __CONTROL_

#include "mytype.h"


#define PITCH_MIN_ANGLE  480;
#define PITCH_MAX_ANGLE  800;
#define YAW_MIN_ANGLE  1180;
#define YAW_MAX_ANGLE  1820;

extern uint8_t Ctrl;

int16_t Value_limit(int16_t input, int16_t max, int16_t min);
void SteeringEngineControl(void);
void Steering_Engine_Set_Value(int16_t yaw, int16_t pitch);
void Patrol_pattern_yaw(void);
void Patrol_pattern_pitch(void);

#endif



