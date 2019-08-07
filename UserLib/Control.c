/*********************************************************************************************************************
 * 注：1、定时器3的通道3用于控制上面的舵机，定时器3的通道4用于控制下面的舵机
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
         __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,900);/*输出1.5ms高电平的脉冲，pitch轴舵机最大角度*/
        
        
    }
    if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)
    {
//        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,500);/*输出0.5ms高电平的脉冲，舵机对应0度*/
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,834);/*输出0.5ms高电平的脉冲，舵机对应30度*/
        
        Steering_Engine_Set_Value(10,-32);
        
    }
    if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET)
    {
//        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,2500);/*输出2.5ms高电平的脉冲，舵机对应180度*/
//        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,2166);/*输出2.5ms高电平的脉冲，舵机对应150度*/
        
        Steering_Engine_Set_Value(20,-30);
        
    }
    if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==GPIO_PIN_RESET)
    {
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,1500);/*输出1.5ms高电平的脉冲，舵机对应90度*/
        
    }

    
}

//pitch:pitch轴角度值，为正数，范围为：0 ~ 37;
//yaw:yaw轴角度值，正负都可以，范围：-60 ~ 60;
void Steering_Engine_Set_Value(int16_t pitch, int16_t yaw)
{
    int16_t pitch_t_1,pitch_t_2,yaw_t_1,yaw_t_2;
    pitch_t_1 = (int16_t)(480+11.1*pitch);
    yaw_t_1 = (int16_t)(1500+11.1*yaw);
    
    pitch_t_2 = Value_limit(pitch_t_1,480,900);
    yaw_t_2 = Value_limit(yaw_t_1,834,2166);
    
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,pitch_t_2);
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,yaw_t_2);
    
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
