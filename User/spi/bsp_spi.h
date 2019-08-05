#ifndef  __BSP_SPI
#define  __BSP_SPI

#include  "stm32f10x.h"
#include  "stdio.h"
#include "./uart/bsp_uart.h"


/****************************条件编译宏定义*************************/
#define   Y		1
#define   N		0

/*****************************SPI相关GPIO口定义*********************/
#define   SPI_GPIO_APBxCmd        RCC_APB2PeriphClockCmd
#define   SPI_GPIO_CLK            RCC_APB2Periph_GPIOB
#define   SPI_GPIO_PORT           GPIOB

#define   SPI_CS_PIN              GPIO_Pin_12
#define   SPI_SCK_PIN             GPIO_Pin_13
#define   SPI_MISO_PIN            GPIO_Pin_14
#define   SPI_MOSI_PIN            GPIO_Pin_15

/********************************************************************/

/************************SPI相关定义***********************/

//SPI口选择
#define   SPIx                    SPI2
//SPI时钟控制
#define   SPI_APBxCmd             RCC_APB1PeriphClockCmd
//SPI时钟配置
#define   SPI_CLK                 RCC_APB1Periph_SPI2

/**********************************************************************/

//片选配置
#define   SPI_CS_HIGH()           GPIO_SetBits(SPI_GPIO_PORT, SPI_CS_PIN);
#define   SPI_CS_LOW()            GPIO_ResetBits(SPI_GPIO_PORT, SPI_CS_PIN);



void SPI_Config(void);
uint8_t SPI_Send(uint8_t data);

void delay(uint32_t count);

#endif   /*__BSP_SPI*/
