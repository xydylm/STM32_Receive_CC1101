#include "bsp_systick.h"


/*
**   Author: xuzhi Liu
**	 Date  : 2018.11.15
**	
**	 ˵��:	systick���Ƽ�״̬�Ĵ���(��ʱ��,ֻ�����¼���,˵����cort_M3����ֲ���ex)
**			----------------------------------------------------------------------
**			--																 	--
**			--	λ��		����				����							--
**			----------------------------------------------------------------------
**			--  16			COUNTFLAG			�����ʱ����ʱ����0����λΪ1 	--
**   		----------------------------------------------------------------------
**			--	2			CLOCKSOURCE			ʱ��Դѡ��λ					--
**			----------------------------------------------------------------------
**			--	1			TICKINT				1=systick������0ʱ����systick	--
**			--									�쳣�ж�����,0= ������0ʱ�޶��� --
**			----------------------------------------------------------------------
**			--	0			ENABLE				systick��ʱ����ʹ��λ			--
**			--																	--
**			----------------------------------------------------------------------
*/
/* ������δ��벻�ܱ���,�����������Ϊ0,������core_cm3.h�����ж���,���Ƶ�������Ϊ�����systick�Ķ�ʱ */
#if		0

static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
	/* reload �Ĵ���Ϊ24λ,���ֵΪ2^24 */
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            
   
  /* ��ʼ��reload�Ĵ�����ֵ  */	
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      

  /* ����systick���ж����ȼ� */
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1); 

  /* ������ֵ���� */	
  SysTick->VAL   = 0;                                          
  
  /* ����systick��ʱ��
	 ʹ���ж�
	 ʹ��systick  */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |   //systickʱ��Դ,����AHB,f1Ĭ����72MHz
                   SysTick_CTRL_TICKINT_Msk   | 
                   SysTick_CTRL_ENABLE_Msk;                    
  return (0);                                                  
}

#endif

/*
**	��	��: Delay_ms(),ͨ�����ò�ѯCOUNTFLAGλ�Ƿ�Ϊ1����ʱ�ķ�ʽ
**	��	��: ������ʱ
**	��	��: ��ʱ��ʱ��
**	����ֵ: ��
**  ע:      ���㷽ʽ: Clk = 72Mʱ��t = (72) *(1/ 72 M )= 1US, Clk = 72Mʱ��t = (72000) *(1/ 72 M )= 1MS
*/
void Delay_ms(uint32_t ms)
{
	uint32_t i = 0;
	
	for(; i< ms;i++)
	{
		SysTick_Config(72000);
		while(!(SysTick->CTRL & (1<<16)));			//����CTRL16λ��ΪCOUNTFLAGλ	
	}
	/* ʧ��systick */
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk; 		//�رն�ʱ��
}

/*
**	��	��: Delay_us(),ͨ�����ò�ѯCOUNTFLAGλ�Ƿ�Ϊ1����ʱ�ķ�ʽ
**	��	��: ΢����ʱ
**	��	��: ��ʱ��ʱ��
**	����ֵ: ��
**  ע:      ���㷽ʽ: Clk = 72Mʱ��t = (72) *(1/ 72 M )= 1US, Clk = 72Mʱ��t = (72000) *(1/ 72 M )= 1MS
*/
void Delay_us(uint32_t us)
{
	uint32_t i = 0;
	
	for(; i< us;i++)
	{
		SysTick_Config(72);
		while(!(SysTick->CTRL & (1<<16)));			//����CTRL16λ��ΪCOUNTFLAGλ	
	}
	/* ʧ��systick */
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;		//�رն�ʱ��
}
