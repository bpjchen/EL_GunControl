/**********************************************************************************************************************
 * �ļ�     ��APPInteraction.c
 * ���     ��ͨ��USMART�������ʵ�����ߵ��Σ���Ҫ����PID�����ߵ��Σ���Ҫ���XCOM V2.0���ڵ�������ʹ�á�
 * ʹ�÷��� ������USART1���жϣ�������Ϊ115200��ͬʱҪ��ͨһ����ʱ��������Ƶ��Ϊ10hz��100ms�ж�һ�Σ�����ִ��usmartɨ�衣
 *            ��ΪUSMART��������ǲ�֧��С�������ߵ��Σ��������ô��ڵ����������ߵ���ʱӦ����������1000��Ȼ��Ҫ����Ӧ�ĺ�
 *            ���õ��������ٳ���1000��
 *
**********************************************************************************************************************/

#include "APPInteraction.h"
#include "usmart.h"
#include "usart.h"
#include "tim.h"
#include "stdio.h"


//u8 Urxbuf[2],rxbuf[2],Usart_Flag;

u8  USART_RX_BUF[USART_REC_LEN];  //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
u16 USART_RX_STA = 0;  //����״̬���	
u8 aRxBuffer[RXBUFFERSIZE];//HAL��USART����Buffer

/*����openmv�����ݽ��գ�USART2*/
u8 aRxBuffer2[1], usart2_rxbuffer[2];
int Position_X,Position_Y;  //Ŀ��λ�õ�����


/**********************************************************************************************************************
 * @brief  USMART���������ʼ������Ҫ�Ƕ��õ��Ĵ��ںͶ�ʱ����ʼ����USMART��ʼ��
 * @param  None
 * @retval None
 * @others �õ��Ĵ��ںͶ�ʱ�����ж����ȼ�Ҫ���ó�һ����CANͨ�ŵ��ж����ȼ����Ҳһ������һ����ʱ��������ݳ���
**********************************************************************************************************************/
void APPInteractionInit(void)
{
    
    HAL_UART_Receive_IT(&huart1, (u8 *)aRxBuffer, RXBUFFERSIZE);//�ú����Ὺ������1�����жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
    HAL_TIM_Base_Start_IT(&htim4);  //Ƶ��Ϊ10hz��100ms�ж�һ��
    
    usmart_dev.init(); 		//��ʼ��USMART

}    


/**********************************************************************************************************************
 * @brief   �����жϺ����������Լ����壬�������ݵĽ���
 * @param   UART_HandleTypeDef *huart     UART handle Structure
 * @retval  None
**********************************************************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
   
	if(huart->Instance==USART1)//����Ǵ���1
	{
		if((USART_RX_STA&0x8000)==0)//����δ���
		{
			if(USART_RX_STA&0x4000)//���յ���0x0d
			{
				if(aRxBuffer[0]!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else USART_RX_STA|=0x8000;	//��������� 
			}
			else //��û�յ�0X0D
			{	
				if(aRxBuffer[0]==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=aRxBuffer[0] ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		
                
			}
            
		}

	}
    if(huart->Instance==USART2)
    {
        OpenmvDataReceive();  /*Openmv���ݽ���*/
    }
    
}



/**********************************************************************************************************************
 * @brief   ��ʱ������������1�����жϣ���USART1_IRQHandler()�б�����
 * @param   None
 * @retval  None
 * @others  USART1���ж����ȼ��Ͷ�ʱ��4���ж����ȼ�������ó�һ��
**********************************************************************************************************************/
void Reset_Usart1_Receive_IT(void)
{
    u32 timeout=0;
    timeout=0;
    while (HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY)//�ȴ�����
    {
         timeout++;//��ʱ����
         if(timeout>HAL_MAX_DELAY) break;		
    }
     
    timeout=0;
    while(HAL_UART_Receive_IT(&huart1, (u8 *)aRxBuffer, RXBUFFERSIZE) != HAL_OK)//һ�δ������֮�����¿����жϲ�����RxXferCountΪ1
    {
         timeout++; //��ʱ����
         if(timeout>HAL_MAX_DELAY) break;	
    }
    
}


/**********************************************************************************************************************
 * @brief    USMARTɨ�裬100msִ��һ�Σ���TIM4_IRQHandler()�б�����
 * @param    None
 * @retval   None
 * @others   ���Ի��������Ķ�ʱ��������ʱ����Ƶ��Ϊ10Hz����100ms�ж�һ�Σ������жϺ���
 *           ���˺���������Ӧ�Ķ�ʱ���жϺ���������
**********************************************************************************************************************/
void UsmartScan(void)
{
    if(__HAL_TIM_GET_IT_SOURCE(&htim4,TIM_IT_UPDATE)==SET)//����ж�
    {
        usmart_dev.scan();	//ִ��usmartɨ��
        __HAL_TIM_SET_COUNTER(&htim4,0);    //��ն�ʱ����CNT
        __HAL_TIM_SET_AUTORELOAD(&htim4,100);//�ָ�ԭ��������
    }
    __HAL_TIM_CLEAR_IT(&htim4, TIM_IT_UPDATE);//����жϱ�־λ
  
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
