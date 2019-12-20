/*********************************************************************************************************************
 * ע��1����ʱ��3��ͨ��3���ڿ���pitch��������ʱ��3��ͨ��4���ڿ���yaw����
 *     2�����0.5ms�ߵ�ƽ�����壬�����Ӧ0��
 *     3�����1.5ms�ߵ�ƽ�����壬�����Ӧ90��
 *     4�����2.5ms�ߵ�ƽ�����壬�����Ӧ180��
 *
*********************************************************************************************************************/
#include "Control.h"
#include "main.h"
#include "tim.h"


uint8_t Ctrl;
int16_t yaw_t; //yaw��Ƕȣ���λ����
int16_t pitch_t;  //pitch��Ƕȣ���λ����

uint8_t fire_t = 1;


void SteeringEngineControl(void)
{
    
    if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==GPIO_PIN_RESET)
    {
//        HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_RESET);
        
                       
        /*�����ʼλ��*/
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,480);/*���0.5ms�ߵ�ƽ�����壬pitch������Ӧ0��*/
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,1540);/*���1.5ms�ߵ�ƽ�����壬yaw������Ӧ90��*/
        
        yaw_t = 0;
        pitch_t = 0;
        
    }
    else if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)
    {
//        HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_SET);
//         __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,800);/*���1.5ms�ߵ�ƽ�����壬pitch�������Ƕ�*/
        
//        HAL_GPIO_WritePin(CO_1_GPIO_Port,CO_1_Pin,GPIO_PIN_SET);//�򿪼̵���1
        
//        fire_t = 1;
        Steering_Engine_Set_Value(30,0);
        
    }
    else if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)
    {
//        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,500);/*���0.5ms�ߵ�ƽ�����壬�����Ӧ0��*/
//        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,1180);/*���0.5ms�ߵ�ƽ�����壬�����Ӧ30��*/
        
//        Steering_Engine_Set_Value(10,-25);
        
//        HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_RESET);
//        HAL_GPIO_WritePin(CO_2_GPIO_Port,CO_2_Pin,GPIO_PIN_SET);//�򿪼̵���2
        
        Fire();
        
    }
    else if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET)
    {
//        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,2500);/*���2.5ms�ߵ�ƽ�����壬�����Ӧ180��*/
//        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,1820);/*���2.5ms�ߵ�ƽ�����壬�����Ӧ150��*/
        
        Patrol_pattern_yaw();  /*yaw�������˶�*/

        
    }
    else if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==GPIO_PIN_RESET)
    {
//        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,1500);/*���1.5ms�ߵ�ƽ�����壬�����Ӧ90��*/
        
        Patrol_pattern_pitch();   /*pitch�������˶�*/
        
    }
//    else
//    {
//        HAL_GPIO_WritePin(CO_1_GPIO_Port,CO_1_Pin,GPIO_PIN_RESET);//�رռ̵���1
//        HAL_GPIO_WritePin(CO_2_GPIO_Port,CO_2_Pin,GPIO_PIN_RESET);//�رռ̵���2
////        HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_SET);
//    }

    ScanFireStatus();
}

//pitch:pitch��Ƕ�ֵ��Ϊ��������ΧΪ��0 ~ 45;
//yaw:yaw��Ƕ�ֵ�����������ԣ���ΧΪ��-30 ~ 30;
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


/*yaw�������˶�*/
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


/*pitch�������˶�*/
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



void Fire(void)
{
    
//    static uint8_t fire_t = 1;
    if(fire_t == 1)
    {
        HAL_GPIO_WritePin(CO_1_GPIO_Port,CO_1_Pin,GPIO_PIN_SET);//�򿪼̵���1�������ݳ��
        HAL_Delay(4000);
        HAL_GPIO_WritePin(CO_1_GPIO_Port,CO_1_Pin,GPIO_PIN_RESET);//�رռ̵���1
        HAL_Delay(10);
        HAL_GPIO_WritePin(CO_2_GPIO_Port,CO_2_Pin,GPIO_PIN_SET);//�򿪼̵���2�����ݷŵ�
        HAL_Delay(10);
        HAL_GPIO_WritePin(CO_2_GPIO_Port,CO_2_Pin,GPIO_PIN_RESET);//�رռ̵���2
        
        fire_t = 0;
    }
    
}



void ScanFireStatus(void)
{
    if(  fire_t == 0)
    {
         fire_t = 1;
    }
}

