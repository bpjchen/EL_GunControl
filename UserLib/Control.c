/*********************************************************************************************************************
 * ע��1����ʱ��3��ͨ��3���ڿ�������Ķ������ʱ��3��ͨ��4���ڿ�������Ķ��
 *     2�����0.5ms�ߵ�ƽ�����壬�����Ӧ0��
 *     3�����1.5ms�ߵ�ƽ�����壬�����Ӧ90��
 *     4�����2.5ms�ߵ�ƽ�����壬�����Ӧ180��
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
        /*�����ʼλ��*/
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,480);/*���0.5ms�ߵ�ƽ�����壬pitch������Ӧ0��*/
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,1500);/*���1.5ms�ߵ�ƽ�����壬yaw������Ӧ90��*/
        
    }
    if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)
    {
//        HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_SET);
         __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,900);/*���1.5ms�ߵ�ƽ�����壬pitch�������Ƕ�*/
        
        
    }
    if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)
    {
//        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,500);/*���0.5ms�ߵ�ƽ�����壬�����Ӧ0��*/
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,834);/*���0.5ms�ߵ�ƽ�����壬�����Ӧ30��*/
        
        Steering_Engine_Set_Value(10,-32);
        
    }
    if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET)
    {
//        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,2500);/*���2.5ms�ߵ�ƽ�����壬�����Ӧ180��*/
//        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,2166);/*���2.5ms�ߵ�ƽ�����壬�����Ӧ150��*/
        
        Steering_Engine_Set_Value(20,-30);
        
    }
    if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==GPIO_PIN_RESET)
    {
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,1500);/*���1.5ms�ߵ�ƽ�����壬�����Ӧ90��*/
        
    }

    
}

//pitch:pitch��Ƕ�ֵ��Ϊ��������ΧΪ��0 ~ 37;
//yaw:yaw��Ƕ�ֵ�����������ԣ���Χ��-60 ~ 60;
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
