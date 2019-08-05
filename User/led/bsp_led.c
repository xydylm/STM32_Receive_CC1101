// bsp borad support package

#include  "./led/bsp_led.h"

void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//打开时钟
	RCC_APB2PeriphClockCmd(IOCFG0_GPIO_CLK|IOCFG2_GPIO_CLK,ENABLE);
	
	//配置结构体GDIO0
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;		//暂时配置为下拉
	GPIO_InitStruct.GPIO_Pin = IOCFG0_GPIO_PIN;
	GPIO_Init(IOCFG0_GPIO_PORT, &GPIO_InitStruct);
}

void Led_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//打开时钟
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);
	
	//初始化结构体
	GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN + LED2_GPIO_PIN + LED3_GPIO_PIN;
	GPIO_InitStruct.GPIO_Speed =GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;

	/*调用初始化函数，把配置好的结构体成员写到寄存器里*/
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
	
	/* 初始化时关闭LED1和LED2 */
	GPIO_SetBits(LED_GPIO_PORT, LED1_GPIO_PIN |LED2_GPIO_PIN);
	//初始化设置LED3为熄灭状态(低电平熄灭)
	GPIO_ResetBits(LED_GPIO_PORT, LED3_GPIO_PIN);
}

/*
 *	说	明: LED灯亮灭函数
 *	参	数: flag,值为下列之一:
 *	    		 0: 低电平,LED熄灭
 *				 1: 高电平,LED点亮
 *	返回值: 无
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
 *	说	明: LED灯亮灭函数
 *	参	数: flag,值为下列之一:
 *	    		 0: 低电平,LED熄灭
 *				 1: 高电平,LED点亮
 *	返回值: 无
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
