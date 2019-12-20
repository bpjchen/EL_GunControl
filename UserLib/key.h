#ifndef __KEY_
#define __KEY_

#include "mytype.h"

extern uint8_t value_1,value_2,value_3;
extern uint16_t value_one,value_ten,value_hundred,value;
extern uint16_t pitch_value,yaw_value;
extern uint8_t set_status;

uint8_t CycleValue_1(void);
uint8_t CycleValue_2(void);
uint8_t CycleValue_3(void);
uint16_t SetValue(void);
void ScanValueStatus(void);
void set_pitch_yaw_value(void);

#endif
