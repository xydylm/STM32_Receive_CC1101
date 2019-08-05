#include "bsp_systick.h"


/*
**   Author: xuzhi Liu
**	 Date  : 2018.11.15
**	
**	 说明:	systick控制及状态寄存器(定时器,只能向下计数,说明在cort_M3编程手册里ex)
**			----------------------------------------------------------------------
**			--																 	--
**			--	位段		名称				描述							--
**			----------------------------------------------------------------------
**			--  16			COUNTFLAG			如果计时器及时到了0，该位为1 	--
**   		----------------------------------------------------------------------
**			--	2			CLOCKSOURCE			时钟源选择位					--
**			----------------------------------------------------------------------
**			--	1			TICKINT				1=systick计数到0时产生systick	--
**			--									异常中断请求,0= 计数到0时无动作 --
**			----------------------------------------------------------------------
**			--	0			ENABLE				systick定时器的使能位			--
**			--																	--
**			----------------------------------------------------------------------
*/
/* 下面这段代码不能编译,条件编译必须为0,函数在core_cm3.h中已有定义,复制到这里是为了理解systick的定时 */
#if		0

static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
	/* reload 寄存器为24位,最大值为2^24 */
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            
   
  /* 初始化reload寄存器的值  */	
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      

  /* 配置systick的中断优先级 */
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1); 

  /* 计数器值清零 */	
  SysTick->VAL   = 0;                                          
  
  /* 配置systick的时钟
	 使能中断
	 使能systick  */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |   //systick时钟源,来自AHB,f1默认是72MHz
                   SysTick_CTRL_TICKINT_Msk   | 
                   SysTick_CTRL_ENABLE_Msk;                    
  return (0);                                                  
}

#endif

/*
**	函	数: Delay_ms(),通过采用查询COUNTFLAG位是否为1来计时的方式
**	描	述: 毫秒延时
**	参	数: 延时的时间
**	返回值: 无
**  注:      计算方式: Clk = 72M时，t = (72) *(1/ 72 M )= 1US, Clk = 72M时，t = (72000) *(1/ 72 M )= 1MS
*/
void Delay_ms(uint32_t ms)
{
	uint32_t i = 0;
	
	for(; i< ms;i++)
	{
		SysTick_Config(72000);
		while(!(SysTick->CTRL & (1<<16)));			//左移CTRL16位即为COUNTFLAG位	
	}
	/* 失能systick */
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk; 		//关闭定时器
}

/*
**	函	数: Delay_us(),通过采用查询COUNTFLAG位是否为1来计时的方式
**	描	述: 微秒延时
**	参	数: 延时的时间
**	返回值: 无
**  注:      计算方式: Clk = 72M时，t = (72) *(1/ 72 M )= 1US, Clk = 72M时，t = (72000) *(1/ 72 M )= 1MS
*/
void Delay_us(uint32_t us)
{
	uint32_t i = 0;
	
	for(; i< us;i++)
	{
		SysTick_Config(72);
		while(!(SysTick->CTRL & (1<<16)));			//左移CTRL16位即为COUNTFLAG位	
	}
	/* 失能systick */
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;		//关闭定时器
}
