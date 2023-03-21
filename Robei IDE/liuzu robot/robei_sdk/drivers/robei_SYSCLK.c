/**
 * @file    hamster_SYSCLK.c
 * @brief	系统时钟的测试
 *
 * \n
 * @details 
 *
 * \n
 * @version 
 * @author  vinolee
 * @date    2020-7-3
 *
 * @history
 *
 */
#include "config.h"
#include "robei_SYSCLK.h"


//defaut:Ro_Init_Systick(3,1,3);

/**
 * 
 * @brief	初始化系统时钟
 * \n
 *
 * @param	hclksel		
 * @param	hclksel1		
 * @param	pclksel		
 * @retval	None
 * \n
 */
void Ro_Init_SysCLK(uint32_t hclksel,uint32_t hclksel1,uint32_t pclksel)
{

	//assume freq=8;
	uint32_t temp=POWER_CLK_REG(CLOCK_03);
	/*
		PCLKSEL[18:15]
		HCLKSEL1[10:7]
		HCLKSEL[6:3]
	*/
	temp=(temp&0xfff87807)|((pclksel<<15)|(hclksel1<<7)|(hclksel<<3));
	POWER_CLK_REG(CLOCK_03)= temp ;
}
/**
 * 
 * @brief	初始化系统嘀嗒
 * \n
 *
 * @param	u8TickPreScal	系统滴答的时钟	
 * @param	u32Tick 		系统滴答的时间间隔		
 * @retval	None
 * \n
 */
void Ro_Init_SysTick(uint8_t u8TickPreScal,uint32_t u32Tick)//频率default 3,tick default 3599
{
	//SYSTICK[30:27]
	MODIFY_REG(POWER_CLK_REG(CLOCK_03),CLOCK_TICKPRESCALER(0xf),CLOCK_TICKPRESCALER(u8TickPreScal));
	MODIFY_REG(POWER_CLK_REG(CLOCK_TICK),CLOCK_SYSTICK(0xffffff),CLOCK_SYSTICK(u32Tick));
}
/**
 * 
 * @brief	初始化SPI时钟
 * \n
 *
 * @param	u8SPICLK		
 * @retval	None
 * \n
 */
void Ro_Init_SPI_CLK(uint8_t u8SPICLK)
{
	MODIFY_REG(POWER_CLK_REG(CLOCK_WWDG),CLOCK_SPIEN(0x1),CLOCK_SPIEN(1));

	//SPI CLK[26:23]
	MODIFY_REG(POWER_CLK_REG(CLOCK_03),CLOCK_SSPCLK(0xf),CLOCK_SSPCLK(u8SPICLK));
}

/**
 * 
 * @brief	初始化IIC 时钟
 * \n
 *
 * @param	u8IICCLK		
 * @retval	None
 * \n
 */
void Ro_Init_IIC_CLK(uint8_t u8IICCLK)
{
	MODIFY_REG(POWER_CLK_REG(CLOCK_WWDG),CLOCK_I2CEN(0x1),CLOCK_I2CEN(1));

	//IIC CLK[27:24]
	MODIFY_REG(POWER_CLK_REG(CLOCK_04),CLOCK_I2C(0xf),CLOCK_I2C(u8IICCLK));
}
/**
 * 
 * @brief	初始化窗口看门狗时钟
 * \n
 *
 * @param	u8WWDGCLK		
 * @retval	None
 * \n
 */
void Ro_Init_WWG_CLK(uint8_t u8WWDGCLK)
{
	//IIC CLK[27:24]
	MODIFY_REG(POWER_CLK_REG(CLOCK_WWDG),CLOCK_WDG(0xf),CLOCK_WDG(u8WWDGCLK));
}
/**
 * 
 * @brief	使能Adaptive的时钟
 * \n
 *
 * @param	isenable		
 			@arg 1 使能adaptive
 			@arg 0 关掉adaptive
 * @retval	None
 * \n
 */
void Ro_Adaptive_Enable(uint8_t isenable)
{
	//IIC CLK[27:24]
	MODIFY_REG(POWER_CLK_REG(CLOCK_01),CLOCK_ADPEN(0x1),CLOCK_ADPEN(isenable));
}

/**
 * 
 * @brief	初始化timer16时钟
 * \n
 *
 * @param	u8Timer_CLK		
 * @retval	None
 * \n
 */
void Ro_Init_Timer_CLK(uint8_t u8Timer_CLK)
{
	MODIFY_REG(POWER_CLK_REG(CLOCK_WWDG),CLOCK_TMEN(0x1),CLOCK_TMEN(1));

	//Timer clk[7:4]
	uint32_t temp=POWER_CLK_REG(0xc30);
	POWER_CLK_REG(0xc30)= (temp&0xffffff0f)|(u8Timer_CLK<<4) ;

}
/**
 * 
 * @brief	初始化timer32的时钟
 * \n
 *
 * @param	u8Timer_CLK32		
 * @retval	None
 * \n
 */
void Ro_Init_Timer32_CLK(uint8_t u8Timer_CLK32)
{
	MODIFY_REG(POWER_CLK_REG(CLOCK_WWDG),CLOCK_TMEN(0x1),CLOCK_TMEN(1));
	//SYSTICK[3:0]
	uint32_t temp=POWER_CLK_REG(0xc30);
	POWER_CLK_REG(0xc30)= (temp&0xfffffff0)|(u8Timer_CLK32) ;
}




