/**
 * @file    hamster_SPI.c
 * @brief	SPI0/SPI1基本操作接口
 *
 * \n
 * @details SPI0/SPI1 的API接口包括初始化,读数据,写数据,发送命令,读状态,设置长度
 *
 * \n
 * @version 
 * @author  vinolee
 * @date    2020-10-20
 *
 * @history
 *
 */
#include "config.h"

#ifdef RO_SPI_MODULE_ENABLED
#include "robei_IT.h"
SPI_HandleTypeDef hspi0;
SPI_HandleTypeDef hspi1;
/**
 * 
 * @brief 初始化SPI的GPIO
 * \n
 *
 * @retval None
 * \n
 * @see
 */
void Ro_SPI_GPIO_Init(SPI_HandleTypeDef *hspi)
{

	if(hspi->Instance==SPI0)
	{
    MODIFY_REG(GPIO_REG(GPIOC_ADATA_REMAP),GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6\
						,GPIO_PIN_3);
	MODIFY_REG(GPIO_REG(GPIOC_FUNCTION_REMAP),GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6\
						,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
	MODIFY_REG(GPIO_REG(GPIOC_SET_DERICTION),GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_1\
								,GPIO_PIN_6|GPIO_PIN_5);
    
	}
	else if(hspi->Instance==SPI1)
	{
    MODIFY_REG(GPIO_REG(GPIOE_ADATA_REMAP),GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7\
							,GPIO_PIN_0);
	MODIFY_REG(GPIO_REG(GPIOE_FUNCTION_REMAP),GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7\
							,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7);
	MODIFY_REG(GPIO_REG(GPIOE_SET_DERICTION),GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7\
							,GPIO_PIN_6|GPIO_PIN_7);
	}
}

/**
 * 
 * @brief 初始化Handle SPI:初始化时钟,GPIO
 * \n
 *
 * @retval None
 * \n
 * @see
 */

void Ro_SPI_Init(SPI_HandleTypeDef *hspi)
{
 	Ro_Init_SPI_CLK(6);//default clock define  PCLKD8        4'd6 // pclk=hclk/8
  
	Ro_SPI_GPIO_Init(hspi);
    
    hspi->Instance->CR1=BIDIM(0)|BIDIO(0)|CRCE(0)|CRCN(0)|CRCL(0)|RXONLY(0)|SSME(0)|SSICS(0)|\
			LSBF(0)|TFR(1)|RFR(1)|SDOD(0)|SFE(hspi->Init.Mode)|SSPM(0)|SSPEN(1)|LBM(0) ;
	hspi->Instance->CR0=FRF(0)|SPH(hspi->Init.CLKPhase)|SPO(hspi->Init.CLKPolarity) ;
    hspi->Instance->CPR=CPSR(0x0);
    
}

/**
 * 
 * @brief SPI0 读数据
 * \n
 *
 * @param 	addr 		读取地址
 * @retval 	uint32_t	返回读取到的数据
 * \n
 * @see
 */
uint32_t Ro_SPI_ReadData(SPI_HandleTypeDef *hspi,uint32_t addr)
{
	if(hspi->Instance==SPI0)
		return (uint32_t)(READ_REG(SPI0_RW_REG(addr))) ;
	else
		return (uint32_t)(READ_REG(SPI1_RW_REG(addr))) ;
}
/**
 * 
 * @brief SPI0写数据
 * \n
 *
 * @param 	addr	写数据的地址
 * @param 	data	写入的数据
 * @retval None
 * \n
 * @see
 */
void Ro_SPI_WriteData(SPI_HandleTypeDef *hspi,uint32_t addr,uint32_t data)
{
	if(hspi->Instance==SPI0)
		WRITE_REG(SPI0_RW_REG(addr),data) ;
	else
		WRITE_REG(SPI1_RW_REG(addr),data) ;
}

/**
 * 
 * @brief SPI0写入命令
 * \n
 *
 * @param cmd	命令	
 * @param	mode	@arg SPI_DATASIZE_8BIT
 * @arg SPI_DATASIZE_16BIT
 
 * @retval None
 * \n
 * @see
 */
void Ro_SPI_Cmd(SPI_HandleTypeDef *hspi,uint8_t mode,uint32_t cmd)
{
 	hspi->Instance->CR=DEMO(mode)|CMD(cmd);
	MODIFY_REG(hspi->Instance->CR1,tempSPI0(0xff),tempSPI0(0)) ;//DMA 用新加测试用
}
void Ro_SPI_QuadEN(SPI_HandleTypeDef *hspi,uint8_t FlashType,uint8_t isEn)
{
    MODIFY_REG(hspi->Instance->CR0,DSS(0x1f),DSS(7));
	if(hspi->Instance==SPI0)
	{
    	MODIFY_REG(GPIO_REG(GPIOC_FUNCTION_REMAP),GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6\
						,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6);
		MODIFY_REG(GPIO_REG(GPIOC_FUNCTION_REMAP),GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6\
						,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_6);
    	SET_BIT(GPIOC->GPIO_W,GPIO_PIN_4);  
	}
	else
	{
		MODIFY_REG(GPIO_REG(GPIOE_FUNCTION_REMAP),GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7\
								,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_6|GPIO_PIN_7);
		MODIFY_REG(GPIO_REG(GPIOE_FUNCTION_REMAP),GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7\
							,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6|GPIO_PIN_7);
		SET_BIT(GPIOE->GPIO_W,GPIO_PIN_3);
	}
   // WRITE_REG(hspi->Instance->CR0,SPH(1)|DSS(7));
    if(FlashType==MXIC_FLASH_QE)
    {
		WRITE_REG(hspi->Instance->CR,DEMO(0)|CMD(FlashType)) ;//0x18=0x106
		MODIFY_REG(hspi->Instance->CR1,tempSPI0(0xff),tempSPI0(0)) ;//DMA 用新加测试用
		//WRITE_REG(SPI0_RW_REG(0x00),isEn) ;//0x08=0x06 
    }   
    else if((FlashType==WINBOND_FLASH_QE)||(FlashType==GD_FLASH_QE))
    {
		WRITE_REG(hspi->Instance->CR,DEMO(0)|CMD(FlashType)) ;//0x18=0x106
		MODIFY_REG(hspi->Instance->CR1,tempSPI0(0xff),tempSPI0(0)) ;//DMA 用新加测试用
		//WRITE_REG(SPI0_RW_REG(0x00),isEn) ;//0x08=0x06 
    }   
	if(hspi->Instance==SPI0)
		WRITE_REG(SPI0_RW_REG(0x00),isEn) ;//0x08=0x06 
	else
		WRITE_REG(SPI1_RW_REG(0x00),isEn) ;//0x08=0x06 
    while(!(READ_REG(hspi->Instance->SR)&READY(1)));
    MODIFY_REG(hspi->Instance->CR0,DSS(0x1f),DSS(31)) ;
   // WRITE_REG(hspi->Instance->CR0,SPH(1)|DSS(31));
}
/**
 * 
 * @brief	SPI0读状态
 * \n
 *
 * @retval uint32_t
 * \n
 * @see
 */
uint32_t Ro_SPI_ReadStatus(SPI_HandleTypeDef *hspi)
{
	 return (uint32_t)READ_REG(hspi->Instance->DR);
}
/**
 * 
 * @brief	SPI0等待完成
 * \n
 *
 * @retval uint32_t
 * \n
 * @see
 */
Ro_StatusTypeDef Ro_SPI_WaitForReady(SPI_HandleTypeDef *hspi)
{
	uint32_t timeout;
	while(!(READ_REG(hspi->Instance->SR)&READY(1)))
	{
		timeout++;
		if(timeout==0xffff)
			return RO_BUSY;
	}
	return RO_OK;
}
/**
 * 
 * @brief	SPI0数据长度选择.可自定义每次接收和发送数据的长度。默认为1个word 32bit
 * \n
 * @param	 len	 命令
 *	 This parameter can be one of the following values:
 *	   @arg SPI_SINGLE_WORD:		4 byte in single mode
 *	   @arg SPI_SINGLE_HALFWORD:	2 byte in single mode
 *	   @arg SPI_SINGLE_BYTE:		1 byte in single mode
 *	   @arg SPI_QUAD_WORD:			4 byte in quad mode
 *	   @arg SPI_QUAD_HALFWORD:		2 byte in quad mode
 *	   @arg SPI_QUAD_BYTE:			1 byte in quad mode
 *
 * @retval 
 * \n
 * @see
 */

void Ro_SPI_SetupLen(SPI_HandleTypeDef *hspi,SPI_DataLen len)
{
    MODIFY_REG(hspi->Instance->CR0,DSS(0x1f),DSS(len)) ;//0=0x0a
}





#endif
