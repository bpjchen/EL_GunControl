#include "key.h"
#include "main.h"
#include "Control.h"


uint8_t value_1,value_2,value_3;
uint8_t value_status_t_1 = 1,value_status_t_2 = 1,value_status_t_3 = 1;
uint16_t value_one,value_ten,value_hundred,value;
uint16_t pitch_value,yaw_value;
uint8_t set_status;

/*个位数的数字变化，通过按键实现数字从0到9再从9到0的周期性变化*/
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

/*十位数的数字变化，通过按键实现数字从0到9再从9到0的周期性变化*/
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

/*百位数的数字变化，通过按键实现数字从0到9再从9到0的周期性变化*/
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


/*通过不同按键对三位数进行赋值*/
uint16_t SetValue(void)
{
    if(HAL_GPIO_ReadPin(SET_DATA_4_GPIO_Port,SET_DATA_4_Pin)==GPIO_PIN_RESET)
    {
        HAL_Delay(200);
        value_one = CycleValue_1();  /*得到个位数的值*/
    }
    else if(HAL_GPIO_ReadPin(SET_DATA_3_GPIO_Port,SET_DATA_3_Pin)==GPIO_PIN_RESET)
    {
        HAL_Delay(200);
        value_ten = CycleValue_2();  /*得到十位数的值*/
    }
    else if(HAL_GPIO_ReadPin(SET_DATA_2_GPIO_Port,SET_DATA_2_Pin)==GPIO_PIN_RESET)
    {
        HAL_Delay(200);
        value_hundred = CycleValue_3();  /*得到百位数的值*/
    }
    value = value_hundred*100 + value_ten*10 + value_one;  /*得到输入值*/
    
    ScanValueStatus();  /*各位数值循环状态检测*/
    
    return value;
    
}


/*通过按键依次对yaw轴和pitch轴的舵机赋值*/
void set_pitch_yaw_value(void)
{

    if(HAL_GPIO_ReadPin(SET_DATA_1_GPIO_Port,SET_DATA_1_Pin)==GPIO_PIN_RESET)
    {
        if(set_status == 0)  /*第一次按下对yaw轴赋值*/
        {
            set_status++;
            yaw_value = SetValue();  /*赋值yaw轴角度值*/
        }
        if(set_status == 1)  /*第二次按下对pitch轴赋值*/
        {
            pitch_value = SetValue();  /*赋值pitch轴角度值*/
        }
        
    }
    
    
}


/*改变数字循环变化的标志位*/
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

