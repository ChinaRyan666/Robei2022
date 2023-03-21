/**
 * @file	hamster_IIC.c
 * @brief	IIC接口
 *
 * \n
 * @details
 *
 * \n
 * @version 
 * @author 	vinolee
 * @date    2020-7-6
 *
 * @history
 *
 */

#include "platform.h"
#include "robei_IIC.h"
#include "robei_GPIO.h"
#include "robei_DMA.h"

#include "config.h"
#include "robei_SYSCLK.h"



#ifdef RO_IIC_MODULE_ENABLED

/**
 * 
 * @brief	IIC 接口初始化
 * \n
 *
 * @retval	None
 * \n
 * @see
 */
void Ro_IIC_Init(void)
{
//设置clock
	Ro_Init_IIC_CLK(3);//PCLKD4        4'd3 // pclk=hclk/4
	
//设置GPIO

	SET_BIT(GPIO_REG(GPIOA_FUNCTION_REMAP),GPIO_PIN_4|GPIO_PIN_5);
	SET_BIT(GPIO_REG(GPIOA_ADATA_REMAP),GPIO_PIN_4|GPIO_PIN_5);
	SET_BIT(GPIO_REG(GPIOA_SET_DERICTION),GPIO_PIN_5);


//设置频率
	//bit_clk（SCL的clock） = i2c_clk/16/(tpcr+1)，

//设置相位差
//SELDEL 16*(tpcr+1)/2保证SDA在SCL低电平的一半时进行反转（相位设置）

	WRITE_REG(IIC_REG(IIC_PRESCALER),TCPR(0)|SELDEL(0x08)) ;

//设置control register  使能ACKEN， 可以选择是否选择使能此寄存器其他中断
	WRITE_REG(IIC_REG(IIC_CTL),RDMAE(0)|RDMAE(0)|TDMAE(0)|ACKEN(1)|TCIE(0)|STOIE(0)|NACKIE(0)|RXIE(0)|TXIE(0)) ;

//使能OE 打开output enable
	WRITE_REG(IIC_REG(IIC_IT_STATE),OE(1)) ;

}
/**
 * 
 * @brief	IIC多字节读写数据命令
 * \n
 *
 * @param	addr	写入地址
 * @param	len		要读写的长度
  * @param	isRead	读写方向设置
 * @retval	None
 * \n
 * @see
 */

void Ro_IIC_Setup(uint8_t addr,uint8_t len,uint8_t isRead)
{
	SET_BIT(IIC_REG(IIC_CTL),ACKEN(1)) ;
	WRITE_REG(IIC_REG(IIC_ADDR),NBYTE(len-1)|STOP(1)|START(1)|ADD10(0)|RDWRN(isRead)|ADDR(addr)) ;

}
/**
 * 
 * @brief	IIC写数据
 * \n
 *
 * @param	addr	写入地址
 * @param	data	写入数据
 * @retval	None
 * \n
 * @see
 */
void Ro_IIC_Write(uint8_t addr,uint8_t data,uint8_t len)
{
	//写地址，设置地址为10，设置数据字节数为1字节，设置start_en=1.stop_en=1
	SET_BIT(IIC_REG(IIC_CTL),ACKEN(1)) ;
	WRITE_REG(IIC_REG(IIC_ADDR),NBYTE(len-1)|STOP(1)|START(1)|ADD10(0)|RDWRN(0)|ADDR(addr)) ;
	WRITE_REG(IIC_REG(IIC_TX_DATA0),data) ;
	while(READ_REG(IIC_REG(IIC_IT_STATE))&0x200); //等待busy为0
}
/**
 * 
 * @brief	IIC写数据，使能传输完成中断（transfer complete interrupt enable）
 * \n
 *
 * @param	addr	写入地址	
 * @param	data	写入数据
 * @retval	None
 * \n
 * @see
 */
void Ro_IIC_Write_IT(uint8_t addr,uint8_t data)
{
	SET_BIT(IIC_REG(IIC_CTL),ACKEN(1)|TCIE(1)) ;
	WRITE_REG(IIC_REG(IIC_ADDR),NBYTE(0)|STOP(1)|START(1)|ADD10(0)|RDWRN(0)|ADDR(addr)) ;
	WRITE_REG(IIC_REG(IIC_TX_DATA0),data) ;
	while(READ_REG(IIC_REG(IIC_IT_STATE))&0x200); //等待busy为0
}

/**                                                                          
 * 
 * @brief	IIC读数据
 * \n
 *
 * @param	addr		读取地址
 * @param	len			数据长度
 * @retval	uint32_t
 * \n
 * @see
 */
uint32_t Ro_IIC_Read(uint8_t addr,uint8_t len)
{
	SET_BIT(IIC_REG(IIC_CTL),ACKEN(1));
	WRITE_REG(IIC_REG(IIC_ADDR),NBYTE(len-1)|STOP(1)|START(1)|ADD10(0)|RDWRN(1)|ADDR(addr)) ;//NBYTE(1)表示读1+1个
	return (uint32_t)(READ_REG(IIC_REG(IIC_RX_DATA0)));
}

#endif
