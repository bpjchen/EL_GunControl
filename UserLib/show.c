#include "show.h"
#include "APPInteraction.h"


u8  Flag_Stop=1;
uint8_t Show;

void oled_show(void)
{                         
//      if(Flag_Stop==0)OLED_ShowString(00,00,"Servo O-N");
//      else            OLED_ShowString(00,00,"Servo OFF");
    OLED_ShowString(00,20,"Position_X: ");
    OLED_ShowNumber(80,20, Position_X,3,12);
    
    OLED_ShowString(00,30,"Position_Y: ");
    OLED_ShowNumber(80,30, Position_Y,3,12);
//			OLED_ShowNumber(100,00, PS2_KEY,3,12);  //PS2的数据
// 		//=============显示PS2的状态=======================//	
//			OLED_ShowString(00,10,"LY");
//			OLED_ShowNumber(15,10, PS2_LY,3,12);  //PS2的数据
//			OLED_ShowString(60,10,"LX");
//			OLED_ShowNumber(75,10, PS2_LX,3,12);
//			
//			OLED_ShowString(00,20,"RY");
//			OLED_ShowNumber(15,20, PS2_RY,3,12);  //PS2的数据
//			OLED_ShowString(60,20,"RX");
//			OLED_ShowNumber(75,20, PS2_RX,3,12);
//			//=============显示PID参数=======================//	
//													OLED_ShowString(00,30,"KP");
//													OLED_ShowNumber(20,30, Balance_Kp,3,12);  //PS2的数据
//													OLED_ShowString(60,30,"KD");
//													OLED_ShowNumber(80,30, Balance_Kd,3,12);
//		//=============显示目标值的状态=======================//	
//		                     	OLED_ShowString(0,40,"T-");
//		  if( Zero_X<0)	    	OLED_ShowString(30,40,"-"),
//		                      OLED_ShowNumber(45,40,-Zero_X,3,12);
//		else                 	OLED_ShowString(30,40,"+"),
//                          OLED_ShowNumber(45,40, Zero_X,3,12); 
////		
//		if( Position_X<0)		  OLED_ShowString(80,40,"-"),
//		                      OLED_ShowNumber(95,40,-Position_X,3,12);
//		else                 	OLED_ShowString(80,40,"+"),
//		                      OLED_ShowNumber(95,40, Position_X,3,12);
//			//=============显示电机D的状态=======================//	
//													OLED_ShowString(0,50,"P-");
//    if( Zero_Y<0)	    	  OLED_ShowString(30,50,"-"),
//		                      OLED_ShowNumber(45,50,-Zero_Y,3,12);
//		else                 	OLED_ShowString(30,50,"+"),
//		                      OLED_ShowNumber(45,50, Zero_Y,3,12); 
////		
//		if( Position_Y<0)		  OLED_ShowString(80,50,"-"),
//		                      OLED_ShowNumber(95,50,-Position_Y,3,12);
//		else                 	OLED_ShowString(80,50,"+"),
//		                      OLED_ShowNumber(95,50, Position_Y,3,12);
		//=============刷新=======================//
		OLED_Refresh_Gram();	
}

