#include "bsp_test.h"

void Print_data(uint8_t *data,uint8_t n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("\n ��ӡ���ݣ�%x",*data);
	}
}