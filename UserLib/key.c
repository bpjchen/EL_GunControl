#include "key.h"
#include "main.h"
#include "Control.h"


uint8_t value_1,value_2,value_3;
uint8_t value_status_t_1 = 1,value_status_t_2 = 1,value_status_t_3 = 1;
uint16_t value_one,value_ten,value_hundred,value;
uint16_t pitch_value,yaw_value;
uint8_t set_status;

/*��λ�������ֱ仯��ͨ������ʵ�����ִ�0��9�ٴ�9��0�������Ա仯*/
uint8_t CycleValue_1(void)
{
    static int16_t flag;
    
    if(value_status_t_1 == 1)
    {
        if(value_1 == 9)
        {
            flag = 1;
        }
        if(value_1 == 0)
        {
            flag = 0;
        }
        if(flag == 1)
        {
            value_1--;
        }
        else
        {
            value_1++;
        }
        value_status_t_1 = 0;
    }
    return value_1;
}

/*ʮλ�������ֱ仯��ͨ������ʵ�����ִ�0��9�ٴ�9��0�������Ա仯*/
uint8_t CycleValue_2(void)
{
    static int16_t flag;
    
    if(value_status_t_2 == 1)
    {
        if(value_2 == 9)
        {
            flag = 1;
        }
        if(value_2 == 0)
        {
            flag = 0;
        }
        if(flag == 1)
        {
            value_2--;
        }
        else
        {
            value_2++;
        }
        value_status_t_2 = 0;
    }
    return value_2;
    
}

/*��λ�������ֱ仯��ͨ������ʵ�����ִ�0��9�ٴ�9��0�������Ա仯*/
uint8_t CycleValue_3(void)
{
    static int16_t flag;
    
    if(value_status_t_3 == 1)
    {
        if(value_3 == 9)
        {
            flag = 1;
        }
        if(value_3 == 0)
        {
            flag = 0;
        }
        if(flag == 1)
        {
            value_3--;
        }
        else
        {
            value_3++;
        }
        value_status_t_3 = 0;
    }
    return value_3;
    
}


/*ͨ����ͬ��������λ�����и�ֵ*/
uint16_t SetValue(void)
{
    if(HAL_GPIO_ReadPin(SET_DATA_4_GPIO_Port,SET_DATA_4_Pin)==GPIO_PIN_RESET)
    {
        HAL_Delay(200);
        value_one = CycleValue_1();  /*�õ���λ����ֵ*/
    }
    else if(HAL_GPIO_ReadPin(SET_DATA_3_GPIO_Port,SET_DATA_3_Pin)==GPIO_PIN_RESET)
    {
        HAL_Delay(200);
        value_ten = CycleValue_2();  /*�õ�ʮλ����ֵ*/
    }
    else if(HAL_GPIO_ReadPin(SET_DATA_2_GPIO_Port,SET_DATA_2_Pin)==GPIO_PIN_RESET)
    {
        HAL_Delay(200);
        value_hundred = CycleValue_3();  /*�õ���λ����ֵ*/
    }
    value = value_hundred*100 + value_ten*10 + value_one;  /*�õ�����ֵ*/
    
    ScanValueStatus();  /*��λ��ֵѭ��״̬���*/
    
    return value;
    
}


/*ͨ���������ζ�yaw���pitch��Ķ����ֵ*/
void set_pitch_yaw_value(void)
{

    if(HAL_GPIO_ReadPin(SET_DATA_1_GPIO_Port,SET_DATA_1_Pin)==GPIO_PIN_RESET)
    {
        if(set_status == 0)  /*��һ�ΰ��¶�yaw�ḳֵ*/
        {
            set_status++;
            yaw_value = SetValue();  /*��ֵyaw��Ƕ�ֵ*/
        }
        if(set_status == 1)  /*�ڶ��ΰ��¶�pitch�ḳֵ*/
        {
            pitch_value = SetValue();  /*��ֵpitch��Ƕ�ֵ*/
        }
        
    }
    
    
}


/*�ı�����ѭ���仯�ı�־λ*/
void ScanValueStatus(void)
{
    if(value_status_t_1 == 0)
    {
        value_status_t_1 = 1;
    }
    if(value_status_t_2 == 0)
    {
        value_status_t_2 = 1;
    }
    if(value_status_t_3 == 0)
    {
        value_status_t_3 = 1;
    }
    
}

