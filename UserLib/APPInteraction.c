/**********************************************************************************************************************
 * 文件     ：APPInteraction.c
 * 简介     ：通过USMART调试组件实现在线调参，主要用于PID的在线调参，需要结合XCOM V2.0串口调试助手使用。
 * 使用方法 ：开启USART1的中断，波特率为115200，同时要开通一个定时器，设置频率为10hz，100ms中断一次，用于执行usmart扫描。
 *            因为USMART调试组件是不支持小数的在线调参，所以在用串口调试助手在线调参时应将参数乘以1000，然后要在相应的函
 *            数得到参数后再除以1000。
 *
**********************************************************************************************************************/

#include "APPInteraction.h"
#include "usmart.h"
#include "usart.h"
#include "tim.h"
#include "stdio.h"


//u8 Urxbuf[2],rxbuf[2],Usart_Flag;

u8  USART_RX_BUF[USART_REC_LEN];  //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
u16 USART_RX_STA = 0;  //接收状态标记	
u8 aRxBuffer[RXBUFFERSIZE];//HAL库USART接收Buffer

/*用于openmv的数据接收，USART2*/
u8 aRxBuffer2[1], usart2_rxbuffer[2];
int Position_X,Position_Y;  //目标位置的坐标


/**********************************************************************************************************************
 * @brief  USMART调试组件初始化，主要是对用到的串口和定时器初始化和USMART初始化
 * @param  None
 * @retval None
 * @others 用到的串口和定时器的中断优先级要设置成一样，CAN通信的中断优先级最好也一样，不一样有时好像会数据出错
**********************************************************************************************************************/
void APPInteractionInit(void)
{
    
    HAL_UART_Receive_IT(&huart1, (u8 *)aRxBuffer, RXBUFFERSIZE);//该函数会开启串口1接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
    HAL_TIM_Base_Start_IT(&htim4);  //频率为10hz，100ms中断一次
    
    usmart_dev.init(); 		//初始化USMART

}    


/**********************************************************************************************************************
 * @brief   串口中断函数，不用自己定义，用于数据的接收
 * @param   UART_HandleTypeDef *huart     UART handle Structure
 * @retval  None
**********************************************************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
   
	if(huart->Instance==USART1)//如果是串口1
	{
		if((USART_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART_RX_STA&0x4000)//接收到了0x0d
			{
				if(aRxBuffer[0]!=0x0a)USART_RX_STA=0;//接收错误,重新开始
				else USART_RX_STA|=0x8000;	//接收完成了 
			}
			else //还没收到0X0D
			{	
				if(aRxBuffer[0]==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=aRxBuffer[0] ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
				}		
                
			}
            
		}

	}
    if(huart->Instance==USART2)
    {
        OpenmvDataReceive();  /*Openmv数据接收*/
    }
    
}



/**********************************************************************************************************************
 * @brief   超时处理，重启串口1接收中断，在USART1_IRQHandler()中被调用
 * @param   None
 * @retval  None
 * @others  USART1的中断优先级和定时器4的中断优先级最好设置成一样
**********************************************************************************************************************/
void Reset_Usart1_Receive_IT(void)
{
    u32 timeout=0;
    timeout=0;
    while (HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY)//等待就绪
    {
         timeout++;//超时处理
         if(timeout>HAL_MAX_DELAY) break;		
    }
     
    timeout=0;
    while(HAL_UART_Receive_IT(&huart1, (u8 *)aRxBuffer, RXBUFFERSIZE) != HAL_OK)//一次处理完成之后，重新开启中断并设置RxXferCount为1
    {
         timeout++; //超时处理
         if(timeout>HAL_MAX_DELAY) break;	
    }
    
}


/**********************************************************************************************************************
 * @brief    USMART扫描，100ms执行一次，在TIM4_IRQHandler()中被调用
 * @param    None
 * @retval   None
 * @others   可以换成其它的定时器，但定时器的频率为10Hz，即100ms中断一次，开启中断后再
 *           将此函数放入相应的定时器中断函数就行了
**********************************************************************************************************************/
void UsmartScan(void)
{
    if(__HAL_TIM_GET_IT_SOURCE(&htim4,TIM_IT_UPDATE)==SET)//溢出中断
    {
        usmart_dev.scan();	//执行usmart扫描
        __HAL_TIM_SET_COUNTER(&htim4,0);    //清空定时器的CNT
        __HAL_TIM_SET_AUTORELOAD(&htim4,100);//恢复原来的设置
    }
    __HAL_TIM_CLEAR_IT(&htim4, TIM_IT_UPDATE);//清除中断标志位
  
}



void OpenmvDataReceive(void)
{
    
    static uint8_t count=0,Usart_Flag_1,Usart_Flag_2;
    if(Usart_Flag_2 == 1)
    {
        usart2_rxbuffer[count] = aRxBuffer2[0];
        count++;
        if(count == 2)
        {

            Position_X = usart2_rxbuffer[0];
            Position_Y = usart2_rxbuffer[1];
            printf("\n\rPosition_X is:%d,Position_Y is:%d\n\r",Position_X,Position_Y);
            
            count = 0;
            Usart_Flag_1 = 0;
            Usart_Flag_2 = 0;
        }
        
    }
    if(aRxBuffer2[0] == 0xff)
    {
        Usart_Flag_1 = 1;
    }
    if((Usart_Flag_1 == 1)&&(aRxBuffer2[0] == 0xfe))
    {
        Usart_Flag_2 = 1;  
    }
    HAL_UART_Receive_IT(&huart2,(uint8_t *)aRxBuffer2,1);
    
}
