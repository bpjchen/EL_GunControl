#ifndef __CONTROL_
#define __CONTROL_

#include "mytype.h"


extern uint8_t Ctrl;
extern int16_t yaw_t;
extern int16_t pitch_t;

void LED_Test(int flag);

int16_t Value_limit(int16_t input, int16_t max, int16_t min);
void SteeringEngineControl(void);
void Steering_Engine_Set_Value(int16_t yaw, int16_t pitch);
void Patrol_pattern_yaw(void);
void Patrol_pattern_pitch(void);
void Fire(void);
void ScanFireStatus(void);

#endif



