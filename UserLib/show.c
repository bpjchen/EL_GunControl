#include "show.h"
#include "APPInteraction.h"
#include "Control.h"
#include "key.h"


u8  Flag_Stop=1;
uint8_t Show;


/*OLED显示*/
void oled_show(void)
{                         
    /*显示按键设定值*/
    OLED_ShowString(00,10,"Value: ");
    OLED_ShowNumber(100,10, value,3,12);
    
    /*显示yaw轴的设定角度值*/
    OLED_ShowString(00,20,"Yaw angle: ");
    OLED_ShowNumber(100,20, yaw_value,3,12);
    
    /*显示pitch轴的设定角度值*/
    OLED_ShowString(00,30,"Pitch angle: ");
    OLED_ShowNumber(100,30, pitch_value,3,12);
    
   /*刷新OLED屏幕*/
	OLED_Refresh_Gram();	
    
}

