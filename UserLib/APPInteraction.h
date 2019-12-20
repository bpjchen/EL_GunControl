#ifndef __APPINERACTION_
#define __APPINERACTION_

#include "mytype.h"
#include "usmart.h"


#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define RXBUFFERSIZE   1 //�����С
	  	       

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;      //����״̬���	
extern u8 aRxBuffer[RXBUFFERSIZE];  //HAL��USART����Buffer

/*����openmv�����ݽ��գ�USART2*/
extern u8 aRxBuffer2[1], usart2_rxbuffer[2];
extern int Position_X,Position_Y; 


/*USMART���������ʼ��*/
void APPInteractionInit(void);
/*��ʱ������������1�����ж�*/
void Reset_Usart1_Receive_IT(void);
/*USMARTɨ�裬100msִ��һ�Σ���TIM4_IRQHandler�б�����*/
void UsmartScan(void);
/*Openmv���ݽ���*/
void OpenmvDataReceive(void);

#endif

