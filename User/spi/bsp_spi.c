#include  "./spi/bsp_spi.h"

/* 步骤：第一步：先配置GPIO
 *       第二步：配置SPI初始化
 */
 
uint32_t  timeout;

//软件延时

void delay(uint32_t count)
{
	for(;count!=0;count--)
	{
	}
}

//SPI初始化配置
void SPI_Config(void)
{
	/*配置相关IO引脚*/
	GPIO_InitTypeDef   GPIO_InitSturct;
	SPI_InitTypeDef    SPI_InitSturct;
	/*第一步配置、初始化GPIO*/
	//使能IO时钟
	SPI_GPIO_APBxCmd(SPI_GPIO_CLK, ENABLE);
	
	//使能SPI时钟
	SPI_APBxCmd(SPI_CLK,ENABLE);
	
	//配置CS引脚（低电平有效）
	GPIO_InitSturct.GPIO_Pin=SPI_CS_PIN;
	GPIO_InitSturct.GPIO_Mode=GPIO_Mode_Out_PP;//通用推挽输出模式
	GPIO_InitSturct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO_PORT, &GPIO_InitSturct);
	
	//配置SCK引脚
	GPIO_InitSturct.GPIO_Pin=SPI_SCK_PIN;
	GPIO_InitSturct.GPIO_Mode=GPIO_Mode_AF_PP;   //复用推挽输出模式
	GPIO_Init(SPI_GPIO_PORT, &GPIO_InitSturct);
	
	//配置MISO引脚
	GPIO_InitSturct.GPIO_Pin=SPI_MISO_PIN;
	GPIO_InitSturct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(SPI_GPIO_PORT, &GPIO_InitSturct);
	
	//配置MOSI引脚
	GPIO_InitSturct.GPIO_Pin=SPI_MOSI_PIN;
	GPIO_InitSturct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(SPI_GPIO_PORT, &GPIO_InitSturct);
	
	/* 第二步配置、初始化SPI*/
	 
	
	//4分频9MHz,
	SPI_InitSturct.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_8;
	
	//模式0,空闲SCLK低电平，奇数边沿采样
	SPI_InitSturct.SPI_CPHA=SPI_CPHA_1Edge;
	SPI_InitSturct.SPI_CPOL=SPI_CPOL_Low;
	
	//SPI_InitSturct.SPI_CRCPolynomial=7;
	SPI_InitSturct.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitSturct.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitSturct.SPI_FirstBit=SPI_FirstBit_MSB;
	SPI_InitSturct.SPI_Mode=SPI_Mode_Master;   //主模式
	SPI_InitSturct.SPI_NSS=SPI_NSS_Soft;
	SPI_Init(SPIx, &SPI_InitSturct);
	
  /* 第三步：使能SPI*/	
	SPI_Cmd(SPIx, ENABLE);
}

/**********************END OF FIEL1*********************************/

//回调函数,回调错误代码
void  SPI_FLASH_TimeOut_CallBack(uint8_t data)
{
	if(data == 1)
	{
		printf("\r\n SPI检测到TXE出现错误，错误代码是：%d",data);
	}
	else
	{
		printf("\r\n SPI检测到RXNE出现错误，错误代码是：%d",data);
	}
}

/*发送一个字节函数*/
uint8_t SPI_Send(uint8_t data)
{
	uint8_t read_temp = 0x00;
	
	timeout=1000;
	
	//清空发送缓存区.TXE为1时,表示表示发送缓冲区为空,TXE为0时,表示发送缓冲区不为空
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE)==RESET)
	{
		if(timeout -- ==0)
		{
				SPI_FLASH_TimeOut_CallBack(1);
		}
	}	
	//只有发送缓冲区为空时,才能开始发送数据到发送缓存区
	  SPI_I2S_SendData(SPIx, data);
	  
	 //接收数据
	  timeout=1000;
	
	  //判定接收缓冲区数据是否为空,如果接收缓冲区为空,等待.RXNE为0时,表示表示发送缓冲区为空,RXNE为1时,表示发送缓冲区不为空
	 while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE)==RESET)
	 {
		 if(timeout-- ==0)
		 {
			 SPI_FLASH_TimeOut_CallBack(2);
		 }
	 }
	 //如果接收缓冲区不为空,读取接收区的数据
	 read_temp = SPI_I2S_ReceiveData(SPIx);  
	 
	 //直接将地址与数据或数据与数据字节之间的延时添加到这里,后续就不用延时
	 Delay_us(10);						//手册上要求延时200ns,这里延时1us.
	 
//	 printf("\n数据是。。。。。。。。。。。。：%x\n",read_temp);
	 return read_temp;
}

/***********************************************************/


