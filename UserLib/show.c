#include "show.h"
#include "APPInteraction.h"
#include "Control.h"
#include "key.h"


u8  Flag_Stop=1;
uint8_t Show;


/*OLED��ʾ*/
void oled_show(void)
{                         
    /*��ʾ�����趨ֵ*/
    OLED_ShowString(00,10,"Value: ");
    OLED_ShowNumber(100,10, value,3,12);
    
    /*��ʾyaw����趨�Ƕ�ֵ*/
    OLED_ShowString(00,20,"Yaw angle: ");
    OLED_ShowNumber(100,20, yaw_value,3,12);
    
    /*��ʾpitch����趨�Ƕ�ֵ*/
    OLED_ShowString(00,30,"Pitch angle: ");
    OLED_ShowNumber(100,30, pitch_value,3,12);
    
   /*ˢ��OLED��Ļ*/
	OLED_Refresh_Gram();	
    
}

