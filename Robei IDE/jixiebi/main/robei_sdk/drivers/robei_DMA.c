/**
 * @file	hamster_DMA.c
 * @brief	DMA基本操作接口
 *
 * \n
 * @details	
 *
 * \n
 * @version	
 * @author		vinolee
 * @date		2020-7-6
 *
 * @history	
 *
 */
#include "robei_SYSCLK.h"
#include "robei_DMA.h"

#ifdef RO_DMA_MODULE_ENABLED



/**
 * 
 * @brief	使能DMA Clock
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_Init_DMA_CLK(void)
{	 
	WRITE_REG(POWER_CLK_REG(CLOCK_01),CLOCK_ADPEN(1)|CLOCK_INTM_EN(1)|CLOCK_DMAEN(1)|CLOCK_DMA1EN(1));
}

/**
 * 
 * @brief	初始化DMA
 * \n
 * @note	通过Power Control Register打开DMA Clock enable;
 * 			打开DMA overal config Register的CReq，使能DMA;
 * 			配置 ch config b Register；
 * 			定义source addr；
 * 			定义destination addr；
 * 配置overal ch sel选择DMA触发条件，参考DMA Req.xlsx或者DMA1.Req.xlsx
 * （如果DMA作为master那么此寄存器可以不进行配置，只需执行下一步骤即可。
 * 如果DMA作为slave，则需要根据每个channel支持的外围器件进行选择。）
 * 配置ch config a，设置当前channel的PL优先级，设置传输类型（single 
 * 4字还是8字），根据传输情况设置BC和TC。设置ST，开始传输。
 *
 * @retval	None
 * \n
 */
void Ro_Init_DMA(DMA_HandleTypeDef *hdma)
{
	
	Ro_Init_DMA_CLK();
	if(IS_DMA0_ALL_INSTANCE(hdma->Instance))
	{
		*DMA0_Overal=CREQ(1)|DH(0x0);
	}
	else if(IS_DMA1_ALL_INSTANCE(hdma->Instance))
	{
		*DMA1_Overal=CREQ(1)|DH(0x0);
	}
	else
		return;
}
/**
 * 
 * @brief	DMA 启动
 * \n
 *
 * @param	hdma			dma通道的handle
 * @param	SrcAddress		源地址
 * @param	DstAddress		目的地址
 * @param	DataLength		数据长度
 *
 * @retval	None
 * \n
 */
void Ro_DMA_Start_8World(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
	uint32_t temp;
	uint16_t u16Counter;

	hdma->Instance->ADDR_SOURCE=SrcAddress;
	hdma->Instance->ADDR_DEST=DstAddress;
	if(hdma->Init.SrcType==DMA_IIC||hdma->Init.SrcType==DMA_UART)
		temp=(CHB_TW0(0x02)|CHB_FS0(1)|CHB_CIE0(0));
	else
		temp=(CHB_TW0(0x02)|CHB_FS0(0)|CHB_CIE0(0));

	if(hdma->Init.DstType==DMA_IIC||hdma->Init.DstType==DMA_UART)
		temp=temp|CHB_FD0(1);
	else
		temp=temp|CHB_FD0(0);
	hdma->Instance->CONF_CHB=temp;
	
	temp=(CHA_PB0(0)|CHA_ST0(0)|CHA_PL0(hdma->Init.Priority)|CHA_BT0(0x4)|CHA_BC0(0x0)|CHA_TC0(0)|CHA_CE0(0x1));
		
	hdma->Instance->CONF_CHA=temp;

	hdma->Instance->CONF_CHA=temp|CHA_ST0(1);
	do
	{
		u16Counter=READ_BIT(DMA0_REG(DMA_OVERALCONFIG),0xffff)+1;
	}
	while(u16Counter!=0);

}
void Ro_DMA_Start_4World(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
	uint32_t temp;
	uint16_t u16Counter;

	hdma->Instance->ADDR_SOURCE=SrcAddress;
	hdma->Instance->ADDR_DEST=DstAddress;
	if(hdma->Init.SrcType==DMA_IIC||hdma->Init.SrcType==DMA_UART)
		temp=(CHB_TW0(0x02)|CHB_FS0(1)|CHB_CIE0(0));
	else
		temp=(CHB_TW0(0x02)|CHB_FS0(0)|CHB_CIE0(0));

	if(hdma->Init.DstType==DMA_IIC||hdma->Init.DstType==DMA_UART)
		temp=temp|CHB_FD0(1);
	else
		temp=temp|CHB_FD0(0);
	hdma->Instance->CONF_CHB=temp;
	
	temp=(CHA_PB0(0)|CHA_ST0(0)|CHA_PL0(hdma->Init.Priority)|CHA_BT0(0x2)|CHA_BC0(0x0)|CHA_TC0(0)|CHA_CE0(0x1));
		
	hdma->Instance->CONF_CHA=temp;

	hdma->Instance->CONF_CHA=temp|CHA_ST0(1);
	do
	{
		u16Counter=READ_BIT(DMA0_REG(DMA_OVERALCONFIG),0xffff)+1;
	}
	while(u16Counter!=0);

}

/**
 * 
 * @brief	DMA 启动
 * \n
 *
 * @param	hdma			dma通道的handle
 * @param	SrcAddress		源地址
 * @param	DstAddress		目的地址
 * @param	DataLength		数据长度
 *
 * @retval	None
 * \n
 */
void Ro_DMA_Start(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
	uint32_t temp;
	uint32_t u32Counter;
//temp clear start
	

	
	if(hdma->Instance==DMA1_Channel0)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK0(1));
	else if(hdma->Instance==DMA1_Channel1)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK1(1));
	else if(hdma->Instance==DMA1_Channel2)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK2(1));
	else if(hdma->Instance==DMA1_Channel3)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK3(1));
	else if(hdma->Instance==DMA1_Channel4)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK4(1));
	else if(hdma->Instance==DMA1_Channel5)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK5(1));
	else if(hdma->Instance==DMA1_Channel6)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK6(1));
	else if(hdma->Instance==DMA1_Channel7)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK7(1));
	else if(hdma->Instance==DMA0_Channel0)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK0(1));
	else if(hdma->Instance==DMA0_Channel1)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK1(1));
	else if(hdma->Instance==DMA0_Channel2)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK2(1));
	else if(hdma->Instance==DMA0_Channel3)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK3(1));
	else if(hdma->Instance==DMA0_Channel4)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK4(1));
	else if(hdma->Instance==DMA0_Channel5)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK5(1));
	else if(hdma->Instance==DMA0_Channel6)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK6(1));
	else if(hdma->Instance==DMA0_Channel7)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK7(1));		
	

	
	//temp clear start



	hdma->Instance->ADDR_SOURCE=SrcAddress;
	hdma->Instance->ADDR_DEST=DstAddress;
	if(hdma->Init.SrcType==DMA_IIC||hdma->Init.SrcType==DMA_UART)
		temp=(CHB_TW0(0)|CHB_FS0(1)|CHB_CIE0(0));
	else
		temp=(CHB_TW0(0)|CHB_FS0(0)|CHB_CIE0(0));

	if(hdma->Init.DstType==DMA_IIC||hdma->Init.DstType==DMA_UART)
		temp=temp|CHB_FD0(1);
	else
		temp=temp|CHB_FD0(0);
	hdma->Instance->CONF_CHB=temp;
	
	temp=(CHA_PB0(0)|CHA_ST0(0)|CHA_PL0(hdma->Init.Priority)|CHA_BT0(0x0)|CHA_BC0(0x0)|CHA_TC0(DataLength-1)|CHA_CE0(0x1));
		
	hdma->Instance->CONF_CHA=temp;

	hdma->Instance->CONF_CHA=temp|CHA_ST0(1);
	do
	{
		//u16Counter=READ_BIT(DMA0_REG(DMA_OVERALCONFIG),0xffff)+1;
	
	
		if(hdma->Instance==DMA1_Channel0)
			u32Counter=READ_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK0(1));
		else if(hdma->Instance==DMA1_Channel1)
			u32Counter=READ_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK1(1));
		else if(hdma->Instance==DMA1_Channel2)
			u32Counter=READ_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK2(1));
		else if(hdma->Instance==DMA1_Channel3)
			u32Counter=READ_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK3(1));
		else if(hdma->Instance==DMA1_Channel4)
			u32Counter=READ_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK4(1));
		else if(hdma->Instance==DMA1_Channel5)
			u32Counter=READ_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK5(1));
		else if(hdma->Instance==DMA1_Channel6)
			u32Counter=READ_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK6(1));
		else if(hdma->Instance==DMA1_Channel7)
			u32Counter=READ_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK7(1));
		else if(hdma->Instance==DMA0_Channel0)
			u32Counter=READ_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK0(1));
		else if(hdma->Instance==DMA0_Channel1)
			u32Counter=READ_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK1(1));
		else if(hdma->Instance==DMA0_Channel2)
			u32Counter=READ_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK2(1));
		else if(hdma->Instance==DMA0_Channel3)
			u32Counter=READ_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK3(1));
		else if(hdma->Instance==DMA0_Channel4)
			u32Counter=READ_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK4(1));
		else if(hdma->Instance==DMA0_Channel5)
			u32Counter=READ_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK5(1));
		else if(hdma->Instance==DMA0_Channel6)
			u32Counter=READ_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK6(1));
		else if(hdma->Instance==DMA0_Channel7)
			u32Counter=READ_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK7(1));		
		//if(hdma->Instance==DMA1_Channel0)
		//	u32Counter=READ_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK0(1));
		//else
		//	u32Counter=READ_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK0(1));
	}
	while(u32Counter==0);

}
/**
 * 
 * @brief	DMA 启动中断
 * \n
 *
 * @param	hdma			dma通道的handle
 * @param	SrcAddress		源地址
 * @param	DstAddress		目的地址
 * @param	DataLength		数据长度
 *
 * @retval	None
 * \n
 */
void Ro_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
	uint32_t temp;
	//uint16_t u16Counter;
	if(hdma->Instance==DMA1_Channel0)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK0(1));
	else if(hdma->Instance==DMA1_Channel1)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK1(1));
	else if(hdma->Instance==DMA1_Channel2)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK2(1));
	else if(hdma->Instance==DMA1_Channel3)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK3(1));
	else if(hdma->Instance==DMA1_Channel4)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK4(1));
	else if(hdma->Instance==DMA1_Channel5)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK5(1));
	else if(hdma->Instance==DMA1_Channel6)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK6(1));
	else if(hdma->Instance==DMA1_Channel7)
		CLEAR_BIT(DMA1_REG(DMA_OVERALCONFIG),ACK7(1));
	else if(hdma->Instance==DMA0_Channel0)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK0(1));
	else if(hdma->Instance==DMA0_Channel1)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK1(1));
	else if(hdma->Instance==DMA0_Channel2)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK2(1));
	else if(hdma->Instance==DMA0_Channel3)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK3(1));
	else if(hdma->Instance==DMA0_Channel4)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK4(1));
	else if(hdma->Instance==DMA0_Channel5)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK5(1));
	else if(hdma->Instance==DMA0_Channel6)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK6(1));
	else if(hdma->Instance==DMA0_Channel7)
		CLEAR_BIT(DMA0_REG(DMA_OVERALCONFIG),ACK7(1));		

	hdma->Instance->ADDR_SOURCE=SrcAddress;
	hdma->Instance->ADDR_DEST=DstAddress;
	if(hdma->Init.SrcType==DMA_IIC||hdma->Init.SrcType==DMA_UART)
		temp=(CHB_TW0(0)|CHB_FS0(1)|CHB_CIE0(1));
	else
		temp=(CHB_TW0(0)|CHB_FS0(0)|CHB_CIE0(1));

	if(hdma->Init.DstType==DMA_IIC||hdma->Init.DstType==DMA_UART)
		temp=temp|CHB_FD0(1);
	else
		temp=temp|CHB_FD0(0);
	hdma->Instance->CONF_CHB=temp;
	
	temp=(CHA_PB0(0)|CHA_ST0(0)|CHA_PL0(hdma->Init.Priority)|CHA_BT0(0x0)|CHA_BC0(0x0)|CHA_TC0(DataLength-1)|CHA_CE0(0x1));
		
	hdma->Instance->CONF_CHA=temp;

	hdma->Instance->CONF_CHA=temp|CHA_ST0(1);
#if 0//等待DMA操作完成
	do
	{
		u16Counter=READ_BIT(DMA0_REG(DMA_OVERALCONFIG),0xffff)+1;
	}
	while(u16Counter!=0);
#endif

}


#endif
