/*********************************************************************************************************************
 * 注：1、定时器3的通道3用于控制pitch轴舵机，定时器3的通道4用于控制yaw轴舵机
 *     2、输出0.5ms高电平的脉冲，舵机对应0度
 *     3、输出1.5ms高电平的脉冲，舵机对应90度
 *     4、输出2.5ms高电平的脉冲，舵机对应180度
 *
*********************************************************************************************************************/
#include "Control.h"
#include "main.h"
#include "tim.h"
#include "key.h"


uint8_t Ctrl;  //主循环的控制标志位
int16_t yaw_t; //yaw轴角度，单位：度
int16_t pitch_t;  //pitch轴角度，单位：度
int16_t yaw_value_end;
uint8_t left_right_flag;
uint8_t fire_status_t = 1;  //用于开炮控制的标志位


/*舵机控制*/
void SteeringEngineControl(void)
{
    
    if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==GPIO_PIN_RESET)
    {
                       
        /*舵机初始位置*/
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,480);/*输出0.5ms高电平的脉冲，pitch轴舵机对应0度*/
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,1540);/*输出1.5ms高电平的脉冲，yaw轴舵机对应90度*/
        
        yaw_t = 0;
        pitch_t = 0;
        
    }
    else if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)  /*yaw轴负值按键*/
    {
        left_right_flag = 1;
        yaw_value_end = -yaw_value;  /*取反，得到负的角度值*/
        
    }
    else if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)
    {
        
        Steering_Engine_Set_Value(pitch_value,yaw_value_end);  /*舵机移动目标位置*/
        Fire();  /*开炮*/
        set_status = 0; /*赋值标志位置零*/
        left_right_flag = 0;
        
    }
    else if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET)
    {
        
        Patrol_pattern_yaw();  /*yaw轴舵机左右运动*/

    }
    else if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==GPIO_PIN_RESET)
    {
        
        Patrol_pattern_pitch();   /*pitch轴舵机上下运动*/
        
    }
    else if(left_right_flag != 1) /*如果没有设置负值，则取原来的数值，默认是正数*/
    {
        
        yaw_value_end = yaw_value;
    }

    ScanFireStatus(); /*开炮状态检测，发完炮后重新置位*/
}


//pitch:pitch轴角度值，为正数，范围为：0 ~ 45;
//yaw:yaw轴角度值，正负都可以，范围为：-30 ~ 30;
void Steering_Engine_Set_Value(int16_t pitch, int16_t yaw)
{
    
    int16_t pitch_t_1,pitch_t_2,yaw_t_1,yaw_t_2;
    pitch_t_1 = (int16_t)(480+11.1*pitch);
    yaw_t_1 = (int16_t)(1540+11.1*yaw);
    
    pitch_t_2 = Value_limit(pitch_t_1,480,980);
    yaw_t_2 = Value_limit(yaw_t_1,1218,1860);
    
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,pitch_t_2);
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,yaw_t_2);
    
}


/*yaw轴左右运动*/
void Patrol_pattern_yaw(void)
{
    
    static int16_t flag,yaw_t_1,yaw_t_2;
    
    if(yaw_t == 29)
    {  
        flag = 1;
    }
    if(yaw_t == -29)
    {
        flag = 0;
    }
    if(flag == 1)
    {
        yaw_t--;
    }
    else
    {
        yaw_t++;
    }
    yaw_t_1 = (int16_t)(1540+11.1*yaw_t);
    yaw_t_2 = Value_limit(yaw_t_1,1218,1860);
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,yaw_t_2);
    HAL_Delay(30);
    
}


/*pitch轴上下运动*/
void Patrol_pattern_pitch(void)
{
    
    static int16_t flag,pitch_t_1,pitch_t_2;
    
     if(pitch_t == 45)
    {  
        flag = 1;
    }
    if(pitch_t == 0)
    {
        flag = 0;
    }
    if(flag == 1)
    {
        pitch_t--;
    }
    else
    {
        pitch_t++;
    }
    pitch_t_1 = (int16_t)(480+11.1*pitch_t);
    pitch_t_2 = Value_limit(pitch_t_1,480,980);
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,pitch_t_2);
    HAL_Delay(50);
    
}


/*数值大小限制*/
int16_t Value_limit(int16_t input, int16_t min, int16_t max)
{ 
    
    int16_t output;
    if(input < min)
    {
        output = min;
    }
    if(input > max)
    {
        output = max;
    }
    return output;
}



void LED_Test(int flag)
{
    
    if(flag == 1)
    {
        HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_RESET);
    }
    if(flag == 0)
    {
        HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_SET);
    }
   
}


/*一键开炮流程*/
void Fire(void)
{
    
    if(fire_status_t == 1)
    {
        HAL_GPIO_WritePin(CO_1_GPIO_Port,CO_1_Pin,GPIO_PIN_SET); /*打开继电器1，给电容充电*/
        HAL_Delay(4000);
        HAL_GPIO_WritePin(CO_1_GPIO_Port,CO_1_Pin,GPIO_PIN_RESET); /*关闭继电器1*/
        HAL_Delay(10);
        HAL_GPIO_WritePin(CO_2_GPIO_Port,CO_2_Pin,GPIO_PIN_SET); /*打开继电器2，电容放电*/
        HAL_Delay(10);
        HAL_GPIO_WritePin(CO_2_GPIO_Port,CO_2_Pin,GPIO_PIN_RESET); /*关闭继电器2*/
        
        fire_status_t = 0;
    }
    
}


/*开炮状态标志位设置，实现通过按键触发一键开炮*/
void ScanFireStatus(void)
{
    if(  fire_status_t == 0)
    {
         fire_status_t = 1;
    }
}

