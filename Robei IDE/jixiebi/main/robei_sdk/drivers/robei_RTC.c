#include "config.h"

#ifdef RO_RTC_MODULE_ENABLED
DMA_HandleTypeDef DMA_iic_rtc;

void Ro_RTC_Init(void)
{
	DMA_iic_rtc.Instance=DMA0_Channel0;
	DMA_iic_rtc.Init.Priority=DMA_PRIORITY_VERY_HIGH;
	DMA_iic_rtc.Init.SrcType=DMA_DEFAULT;
	DMA_iic_rtc.Init.DstType=DMA_IIC;
	DMA_iic_rtc.Init.Mode=DMA_MODE_BYTE;
	Ro_Init_DMA(&DMA_iic_rtc);
	Ro_IIC_Init();
}
void Ro_RTC_Stop(void)
{
	uint8_t rtc_buf[5];

	//0 内部寄存器：0c关掉计数；1-4：写80关掉计数，写00打开计数
	rtc_buf[0]=0x0c;
	rtc_buf[1]=0x00;
	rtc_buf[2]=0x00;
	rtc_buf[3]=0x00;
	rtc_buf[4]=0x80;
	Ro_IIC_Setup(0x80,5,0);
	Ro_DMA_Start(&DMA_iic_rtc,(uint32_t)rtc_buf,IIC_BASE_ADDR+IIC_TX_DATA0,5);
}
void Ro_RTC_Start(void)
{
	uint8_t rtc_buf[5];
	rtc_buf[0]=0x0c;
	rtc_buf[1]=0x00;
	rtc_buf[2]=0x00;
	rtc_buf[3]=0x00;
	rtc_buf[4]=0x00;
	Ro_IIC_Setup(0x80,5,0);
	Ro_DMA_Start(&DMA_iic_rtc,(uint32_t)rtc_buf,IIC_BASE_ADDR+IIC_TX_DATA0,5);
}
void Ro_RTC_SetupTime(void)
{
	
}
void Ro_RTC_SetupDate(void)
{
	
}
void Ro_RTC_SetupAlarm(void)
{
	
}
void Ro_RTC_StartAlarm(void)
{
	
}

#endif

