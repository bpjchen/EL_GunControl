/**********************************************************************************************************************	 
 * 备注                 ：移植正点原子的USMART调试组件，在此声明！
 * 作者                 ：正点原子@ALIENTEK
 * 正点原子官方论坛     ：www.openedv.com 
 * 正点原子技术交流群   ：932714459
 * 版本                 ：V3.3
 * Copyright(C) 正点原子 2011-2021
 * All rights reserved
**********************************************************************************************************************/
#include "usmart.h"
#include "usmart_str.h"
#include "APPInteraction.h"
#include "stdio.h"

/*********************************************************用户配置区********************************************************/
//这下面要包含所用到的函数所申明的头文件(用户自己添加) 
#include "Control.h"
#include "pid.h"
								 

//函数名列表初始化(用户自己添加)
//用户直接在这里输入要执行的函数名及其查找串，按照相应的格式添加即可
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//如果使能了读写操作
	(void*)read_addr,"u32 read_addr(u32 addr)",
	(void*)write_addr,"void write_addr(u32 addr,u32 val)",	 
#endif		    
		
//   (void*)set_moto_current1,"void set_moto_current1(CAN_HandleTypeDef *hcan,s16 iq1, s16 iq2, s16 iq3, s16 iq4)", 
   (void*)LED_Test,"void LED_Test(int flag)",
//   (void*)pid_reset,"void pid_reset(uint32_t kp, uint32_t ki, uint32_t kd)",
   
        
       
};			

/*********************************************************END***************************************************************/

//函数控制管理器初始化
//得到各个受控函数的名字
//得到函数总数量
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//函数数量
	0,	  	//参数数量
	0,	 	//函数ID
	1,		//参数显示类型,0,10进制;1,16进制
	0,		//参数类型.bitx:,0,数字;1,字符串	    
	0,	  	//每个参数的长度暂存表,需要MAX_PARM个0初始化
	0,		//函数的参数,需要PARM_LEN个0初始化
};   



















