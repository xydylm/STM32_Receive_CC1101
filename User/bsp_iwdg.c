#include "bsp_iwdg.h"

/*
 * ˵	��: ���Ź���ʼ������,ÿ����IWDG_KR�Ĵ���д��0xAAAA,��װ�ص�ֵ��д�뵽��������,��ϸ��ο��ֲ�
 * ��	��: prv:Ԥ��Ƶϵ��,ֵ�ӹ̼��⺯������
 *			rlv:����������װ��ֵ
 *  ����ֵ: ��
 */
void IWDG_Config(uint8_t prv ,uint16_t rlv)
{
	//ʹ��Ԥ��Ƶ����װ�ؼĴ���(д��0x5555)
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	//����Ԥ��Ƶ
	IWDG_SetPrescaler(prv);
	
	//������װ�ؼĴ���ֵ
	IWDG_SetReload(rlv);
	
	//����װ�ؼĴ�����ֵд���������.����KR�Ĵ���д��0xAAAA
	IWDG_ReloadCounter();			//��������д���ֵ��ʼ�ݼ�
	
	
}

void IWDG_Start(void)
{
	//����Ϊ64��Ƶ,���Ź����¼���ʱ��Ϊ3s
	IWDG_Config(IWDG_Prescaler_64,1875);
	
	// ʹ��IWDG,�������Ź�����.��д��0xCCCC
	IWDG_Enable();
}

// ι��
void IWDG_Feed(void)
{
	/* ����װ�ؼĴ�����ֵ�ŵ��������У�ι������ֹIWDG��λ, ����������ֵ����0��ʱ������ϵͳ��λ
	   ��ν��ι������˼�ǣ����ÿ��Ź�������λ
	   ���ÿ��Ź���λ������: ��һ���ļ��ʱ��д��0xAAAA
	*/
	IWDG_ReloadCounter();
}
