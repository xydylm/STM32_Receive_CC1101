// bsp borad support package

#include  "./led/bsp_led.h"

void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//��ʱ��
	RCC_APB2PeriphClockCmd(IOCFG0_GPIO_CLK|IOCFG2_GPIO_CLK,ENABLE);
	
	//���ýṹ��GDIO0
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;		//��ʱ����Ϊ����
	GPIO_InitStruct.GPIO_Pin = IOCFG0_GPIO_PIN;
	GPIO_Init(IOCFG0_GPIO_PORT, &GPIO_InitStruct);
}

void Led_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//��ʱ��
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);
	
	//��ʼ���ṹ��
	GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN + LED2_GPIO_PIN + LED3_GPIO_PIN;
	GPIO_InitStruct.GPIO_Speed =GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;

	/*���ó�ʼ�������������úõĽṹ���Աд���Ĵ�����*/
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
	
	/* ��ʼ��ʱ�ر�LED1��LED2 */
	GPIO_SetBits(LED_GPIO_PORT, LED1_GPIO_PIN |LED2_GPIO_PIN);
	//��ʼ������LED3ΪϨ��״̬(�͵�ƽϨ��)
	GPIO_ResetBits(LED_GPIO_PORT, LED3_GPIO_PIN);
}

/*
 *	˵	��: LED��������
 *	��	��: flag,ֵΪ����֮һ:
 *	    		 0: �͵�ƽ,LEDϨ��
 *				 1: �ߵ�ƽ,LED����
 *	����ֵ: ��
**/
void LED1(uint8_t flag)
{
	if(flag == 0)
	{
		GPIO_SetBits(LED_GPIO_PORT, LED1_GPIO_PIN);
	}
	else if(flag == 1)
	{
		GPIO_ResetBits(LED_GPIO_PORT, LED1_GPIO_PIN);
	}	
}

/*
 *	˵	��: LED��������
 *	��	��: flag,ֵΪ����֮һ:
 *	    		 0: �͵�ƽ,LEDϨ��
 *				 1: �ߵ�ƽ,LED����
 *	����ֵ: ��
**/
void LED2(uint8_t flag)
{
	if(flag == 0)
	{
		GPIO_SetBits(LED_GPIO_PORT, LED2_GPIO_PIN);
	}
	else if(flag == 1)
	{
		GPIO_ResetBits(LED_GPIO_PORT, LED2_GPIO_PIN);
	}	
}


void LED3(uint8_t flag)
{
	if(flag == 1)
	{
		GPIO_SetBits(LED_GPIO_PORT, LED3_GPIO_PIN);
	}
	else if(flag == 0)
	{
		GPIO_ResetBits(LED_GPIO_PORT, LED3_GPIO_PIN);
	}	
}
