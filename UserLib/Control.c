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


uint8_t Ctrl;



void SteeringEngineControl(void)
{
    
    if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==GPIO_PIN_RESET)
    {
//        HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_RESET);
        /*舵机初始位置*/
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,480);/*输出0.5ms高电平的脉冲，pitch轴舵机对应0度*/
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,1500);/*输出1.5ms高电平的脉冲，yaw轴舵机对应90度*/
        
    }
    if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)
    {
//        HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_SET);
         __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,800);/*输出1.5ms高电平的脉冲，pitch轴舵机最大角度*/
        
        
    }
    if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)
    {
//        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,500);/*输出0.5ms高电平的脉冲，舵机对应0度*/
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,1180);/*输出0.5ms高电平的脉冲，舵机对应30度*/
        
        Steering_Engine_Set_Value(10,-25);
        
    }
    if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET)
    {
//        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,2500);/*输出2.5ms高电平的脉冲，舵机对应180度*/
//        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,1820);/*输出2.5ms高电平的脉冲，舵机对应150度*/
        
        Patrol_pattern_yaw();

        
    }
    if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==GPIO_PIN_RESET)
    {
//        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,1500);/*输出1.5ms高电平的脉冲，舵机对应90度*/
        
        Patrol_pattern_pitch();
        
    }

}

//pitch:pitch轴角度值，为正数，范围为：0 ~ 30;
//yaw:yaw轴角度值，正负都可以，范围为：-30 ~ 30;
void Steering_Engine_Set_Value(int16_t pitch, int16_t yaw)
{
    
    int16_t pitch_t_1,pitch_t_2,yaw_t_1,yaw_t_2;
    pitch_t_1 = (int16_t)(480+11.1*pitch);
    yaw_t_1 = (int16_t)(1500+11.1*yaw);
    
    pitch_t_2 = Value_limit(pitch_t_1,480,800);
    yaw_t_2 = Value_limit(yaw_t_1,1180,1820);
    
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,pitch_t_2);
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,yaw_t_2);
    
}


/*yaw轴上下运动*/
void Patrol_pattern_yaw(void)
{
    
    static int16_t yaw_t = 0,flag,yaw_t_1,yaw_t_2;
    
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
    yaw_t_1 = (int16_t)(1500+11.1*yaw_t);
    yaw_t_2 = Value_limit(yaw_t_1,1180,1820);
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,yaw_t_2);
    
    HAL_Delay(20);
    
}


/*pitch轴左右运动*/
void Patrol_pattern_pitch(void)
{
    
    static int16_t pitch_t = 0,flag,pitch_t_1,pitch_t_2;
    
     if(pitch_t == 29)
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
    pitch_t_2 = Value_limit(pitch_t_1,480,800);
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,pitch_t_2);
    HAL_Delay(30);
    
}


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
