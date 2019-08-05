#ifndef  __BSP_SPI
#define  __BSP_SPI

#include  "stm32f10x.h"
#include  "stdio.h"
#include "./uart/bsp_uart.h"


/****************************��������궨��*************************/
#define   Y		1
#define   N		0

/*****************************SPI���GPIO�ڶ���*********************/
#define   SPI_GPIO_APBxCmd        RCC_APB2PeriphClockCmd
#define   SPI_GPIO_CLK            RCC_APB2Periph_GPIOB
#define   SPI_GPIO_PORT           GPIOB

#define   SPI_CS_PIN              GPIO_Pin_12
#define   SPI_SCK_PIN             GPIO_Pin_13
#define   SPI_MISO_PIN            GPIO_Pin_14
#define   SPI_MOSI_PIN            GPIO_Pin_15

/********************************************************************/

/************************SPI��ض���***********************/

//SPI��ѡ��
#define   SPIx                    SPI2
//SPIʱ�ӿ���
#define   SPI_APBxCmd             RCC_APB1PeriphClockCmd
//SPIʱ������
#define   SPI_CLK                 RCC_APB1Periph_SPI2

/**********************************************************************/

//Ƭѡ����
#define   SPI_CS_HIGH()           GPIO_SetBits(SPI_GPIO_PORT, SPI_CS_PIN);
#define   SPI_CS_LOW()            GPIO_ResetBits(SPI_GPIO_PORT, SPI_CS_PIN);



void SPI_Config(void);
uint8_t SPI_Send(uint8_t data);

void delay(uint32_t count);

#endif   /*__BSP_SPI*/
