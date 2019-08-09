#ifndef __SHOW_H
#define __SHOW_H

#include "oled.h"

extern u8  Flag_Stop;   //停止标志位和 显示标志位 默认停止 显示打开
extern uint8_t Show;

void oled_show(void);



#endif

