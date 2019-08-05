#include  "./spi/bsp_spi.h"

/* ���裺��һ����������GPIO
 *       �ڶ���������SPI��ʼ��
 */
 
uint32_t  timeout;

//�����ʱ

void delay(uint32_t count)
{
	for(;count!=0;count--)
	{
	}
}

//SPI��ʼ������
void SPI_Config(void)
{
	/*�������IO����*/
	GPIO_InitTypeDef   GPIO_InitSturct;
	SPI_InitTypeDef    SPI_InitSturct;
	/*��һ�����á���ʼ��GPIO*/
	//ʹ��IOʱ��
	SPI_GPIO_APBxCmd(SPI_GPIO_CLK, ENABLE);
	
	//ʹ��SPIʱ��
	SPI_APBxCmd(SPI_CLK,ENABLE);
	
	//����CS���ţ��͵�ƽ��Ч��
	GPIO_InitSturct.GPIO_Pin=SPI_CS_PIN;
	GPIO_InitSturct.GPIO_Mode=GPIO_Mode_Out_PP;//ͨ���������ģʽ
	GPIO_InitSturct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO_PORT, &GPIO_InitSturct);
	
	//����SCK����
	GPIO_InitSturct.GPIO_Pin=SPI_SCK_PIN;
	GPIO_InitSturct.GPIO_Mode=GPIO_Mode_AF_PP;   //�����������ģʽ
	GPIO_Init(SPI_GPIO_PORT, &GPIO_InitSturct);
	
	//����MISO����
	GPIO_InitSturct.GPIO_Pin=SPI_MISO_PIN;
	GPIO_InitSturct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(SPI_GPIO_PORT, &GPIO_InitSturct);
	
	//����MOSI����
	GPIO_InitSturct.GPIO_Pin=SPI_MOSI_PIN;
	GPIO_InitSturct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(SPI_GPIO_PORT, &GPIO_InitSturct);
	
	/* �ڶ������á���ʼ��SPI*/
	 
	
	//4��Ƶ9MHz,
	SPI_InitSturct.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_8;
	
	//ģʽ0,����SCLK�͵�ƽ���������ز���
	SPI_InitSturct.SPI_CPHA=SPI_CPHA_1Edge;
	SPI_InitSturct.SPI_CPOL=SPI_CPOL_Low;
	
	//SPI_InitSturct.SPI_CRCPolynomial=7;
	SPI_InitSturct.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitSturct.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitSturct.SPI_FirstBit=SPI_FirstBit_MSB;
	SPI_InitSturct.SPI_Mode=SPI_Mode_Master;   //��ģʽ
	SPI_InitSturct.SPI_NSS=SPI_NSS_Soft;
	SPI_Init(SPIx, &SPI_InitSturct);
	
  /* ��������ʹ��SPI*/	
	SPI_Cmd(SPIx, ENABLE);
}

/**********************END OF FIEL1*********************************/

//�ص�����,�ص��������
void  SPI_FLASH_TimeOut_CallBack(uint8_t data)
{
	if(data == 1)
	{
		printf("\r\n SPI��⵽TXE���ִ��󣬴�������ǣ�%d",data);
	}
	else
	{
		printf("\r\n SPI��⵽RXNE���ִ��󣬴�������ǣ�%d",data);
	}
}

/*����һ���ֽں���*/
uint8_t SPI_Send(uint8_t data)
{
	uint8_t read_temp = 0x00;
	
	timeout=1000;
	
	//��շ��ͻ�����.TXEΪ1ʱ,��ʾ��ʾ���ͻ�����Ϊ��,TXEΪ0ʱ,��ʾ���ͻ�������Ϊ��
	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE)==RESET)
	{
		if(timeout -- ==0)
		{
				SPI_FLASH_TimeOut_CallBack(1);
		}
	}	
	//ֻ�з��ͻ�����Ϊ��ʱ,���ܿ�ʼ�������ݵ����ͻ�����
	  SPI_I2S_SendData(SPIx, data);
	  
	 //��������
	  timeout=1000;
	
	  //�ж����ջ����������Ƿ�Ϊ��,������ջ�����Ϊ��,�ȴ�.RXNEΪ0ʱ,��ʾ��ʾ���ͻ�����Ϊ��,RXNEΪ1ʱ,��ʾ���ͻ�������Ϊ��
	 while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE)==RESET)
	 {
		 if(timeout-- ==0)
		 {
			 SPI_FLASH_TimeOut_CallBack(2);
		 }
	 }
	 //������ջ�������Ϊ��,��ȡ������������
	 read_temp = SPI_I2S_ReceiveData(SPIx);  
	 
	 //ֱ�ӽ���ַ�����ݻ������������ֽ�֮�����ʱ��ӵ�����,�����Ͳ�����ʱ
	 Delay_us(10);						//�ֲ���Ҫ����ʱ200ns,������ʱ1us.
	 
//	 printf("\n�����ǡ�������������������������%x\n",read_temp);
	 return read_temp;
}

/***********************************************************/


