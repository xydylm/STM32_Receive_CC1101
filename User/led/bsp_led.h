#ifndef  __BSP_LED_H
#define  __BSP_LED_H

#include "stm32f10x.h"

//IOCFG0
#define   IOCFG0_GPIO_CLK           RCC_APB2Periph_GPIOA
#define   IOCFG0_GPIO_PORT          GPIOA
#define   IOCFG0_GPIO_PIN           GPIO_Pin_2

//IOCFG2
#define   IOCFG2_GPIO_CLK           RCC_APB2Periph_GPIOA
#define   IOCFG2_GPIO_PORT          GPIOA
#define   IOCFG2_GPIO_PIN           GPIO_Pin_3

//LED1
#define   LED_GPIO_CLK              RCC_APB2Periph_GPIOC
#define   LED_GPIO_PORT             GPIOC
#define   LED1_GPIO_PIN             GPIO_Pin_2
#define   LED2_GPIO_PIN             GPIO_Pin_3
#define   LED3_GPIO_PIN             GPIO_Pin_0
//LED3(∑«∞Â‘ÿLEDµ∆)






void GPIO_Config(void);
void Led_GPIO_Config(void);
void LED1(uint8_t flag);
void LED2(uint8_t flag);
void LED3(uint8_t flag);

#endif  /*__BSP_LED_H*/
