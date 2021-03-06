#ifndef  __BSP_UART_H
#define  __BSP_UART_H

#include  "stm32f10x.h"
#include "bsp_systick.h"


//串口1
#define   DEBUG_USARTx                 USART1  
#define   DEBUG_USART_CLK              RCC_APB2Periph_USART1
#define   DEBUG_USART_APBxCLKCmd       RCC_APB2PeriphClockCmd
#define   DEBUG_USART_BAUDRATE         115200

// USART_GPIO引脚宏定义
#define   DEBUG_USART_GPIO_CLK         RCC_APB2Periph_GPIOA
#define   DEBUG_USART_GPIO_APBxCLKCmd  RCC_APB2PeriphClockCmd
#define   DEBUG_USART_GPIO_PORT        GPIOA
#define   DEBUG_USART_TX_GPIO_PIN      GPIO_Pin_9
#define   DEBUG_USART_RX_GPIO_PIN      GPIO_Pin_10

//定义中断
#define   DEBUG_USART_IRQ              USART1_IRQn
#define   DEBUG_USART_IRQHandler       USART1_IRQHandler

void UART_Init(void);


#endif   /*__BSP_UART_H*/
