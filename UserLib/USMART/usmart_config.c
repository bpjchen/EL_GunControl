/**********************************************************************************************************************	 
 * ��ע                 ����ֲ����ԭ�ӵ�USMART����������ڴ�������
 * ����                 ������ԭ��@ALIENTEK
 * ����ԭ�ӹٷ���̳     ��www.openedv.com 
 * ����ԭ�Ӽ�������Ⱥ   ��932714459
 * �汾                 ��V3.3
 * Copyright(C) ����ԭ�� 2011-2021
 * All rights reserved
**********************************************************************************************************************/
#include "usmart.h"
#include "usmart_str.h"
#include "APPInteraction.h"
#include "stdio.h"

/*********************************************************�û�������********************************************************/
//������Ҫ�������õ��ĺ�����������ͷ�ļ�(�û��Լ����) 
#include "Control.h"
//#include "pid.h"
								 

//�������б��ʼ��(�û��Լ����)
//�û�ֱ������������Ҫִ�еĺ�����������Ҵ���������Ӧ�ĸ�ʽ��Ӽ���
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//���ʹ���˶�д����
	(void*)read_addr,"u32 read_addr(u32 addr)",
	(void*)write_addr,"void write_addr(u32 addr,u32 val)",	 
#endif		    
		
//   (void*)set_moto_current1,"void set_moto_current1(CAN_HandleTypeDef *hcan,s16 iq1, s16 iq2, s16 iq3, s16 iq4)", 
//   (void*)LED_Test,"void LED_Test(int flag)",
//   (void*)pid_reset,"void pid_reset(uint32_t kp, uint32_t ki, uint32_t kd)",
   
        
       
};			

/*********************************************************END***************************************************************/

//�������ƹ�������ʼ��
//�õ������ܿغ���������
//�õ�����������
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//��������
	0,	  	//��������
	0,	 	//����ID
	1,		//������ʾ����,0,10����;1,16����
	0,		//��������.bitx:,0,����;1,�ַ���	    
	0,	  	//ÿ�������ĳ����ݴ��,��ҪMAX_PARM��0��ʼ��
	0,		//�����Ĳ���,��ҪPARM_LEN��0��ʼ��
};   



















