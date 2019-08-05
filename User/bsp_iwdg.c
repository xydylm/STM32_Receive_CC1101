#include "bsp_iwdg.h"

/*
 * 说	明: 看门狗初始化配置,每当向IWDG_KR寄存器写入0xAAAA,重装载的值会写入到计数器中,详细请参考手册
 * 参	数: prv:预分频系数,值从固件库函数中找
 *			rlv:计数器的重装载值
 *  返回值: 无
 */
void IWDG_Config(uint8_t prv ,uint16_t rlv)
{
	//使能预分频和重装载寄存器(写入0x5555)
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	//设置预分频
	IWDG_SetPrescaler(prv);
	
	//设置重装载寄存器值
	IWDG_SetReload(rlv);
	
	//将重装载寄存器的值写入计数器中.即向KR寄存器写入0xAAAA
	IWDG_ReloadCounter();			//计数器从写入的值开始递减
	
	
}

void IWDG_Start(void)
{
	//设置为64分频,看门狗向下计数时间为3s
	IWDG_Config(IWDG_Prescaler_64,1875);
	
	// 使能IWDG,启动看门狗工作.即写入0xCCCC
	IWDG_Enable();
}

// 喂狗
void IWDG_Feed(void)
{
	/* 把重装载寄存器的值放到计数器中，喂狗，防止IWDG复位, 当计数器的值减到0的时候会产生系统复位
	   所谓的喂狗的意思是：不让看门狗产生复位
	   不让看门狗复位方法是: 以一定的间隔时间写入0xAAAA
	*/
	IWDG_ReloadCounter();
}
