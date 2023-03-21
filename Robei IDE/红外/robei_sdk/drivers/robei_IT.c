/**
 * @file	hamster_IT.c
 * @brief	中断操作接口
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

#include "platform.h"
#include "config.h"
#include "encoding.h"

#ifdef RO_IT_MODULE_ENABLED
#include "robei_IT.h"


/**
 * 
 * @brief	使能SPI的DMA中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_DMA_SPI(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ12) ;
	MODIFY_REG(PLIC_REG(IT_REQA12),EX(0xf),EX(0xe));	
}
/**
 * 
 * @brief	使能DMA0和1的channel2的中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_DMA01_CH2(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ14) ;
	MODIFY_REG(PLIC_REG(IT_REQA14),EX(0xf),EX(0xe));	
}
/**
 * 
 * @brief	使能DMA0和1的channel3的中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_DMA01_CH3(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ15) ;
	MODIFY_REG(PLIC_REG(IT_REQA15),EX(0xf),EX(0xe));	
}
/**
 * 
 * @brief	使能DMA0和1的channel4的中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_DMA01_CH4(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ16) ;
	MODIFY_REG(PLIC_REG(IT_REQA16),EX(0xf),EX(0xe));
}
/**
 * 
 * @brief	使能DMA0和1的channel5的中断
 * \n
 *
 * @retval	None
 * \n
 */    
void Ro_IT_Enable_DMA01_CH5(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ17) ;
	MODIFY_REG(PLIC_REG(IT_REQA17),EX(0xf),EX(0xe));	
}
/**
 * 
 * @brief	使能DMA0和1的channel6的中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_DMA01_CH6(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ18) ;
	MODIFY_REG(PLIC_REG(IT_REQA18),EX(0xf),EX(0xe));	
}
/**
 * 
 * @brief	使能DMA0和1的channel7的中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_DMA01_CH7(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ21) ;
	MODIFY_REG(PLIC_REG(IT_REQA21),EX(0xf),EX(0xe));	
}

/**
 * 
 * @brief	使能IIC中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_IIC(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ28) ;
	MODIFY_REG(PLIC_REG(IT_REQA28),EX(0xf),EX(0xe));	
}
/**
 * 
 * @brief	使能WDG(看门狗)中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_WDG(void)
{
	
	swap_csr(mie, 0x1f);//20200603 move here form stack.s
	SET_BIT(IWDG_REG(WWDG_WIE),WIE(1)|CLKEN(1)) ;
}
/**
 * 
 * @brief	使能自适应(Adaptive)功能中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_ADP(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ22) ;
	MODIFY_REG(PLIC_REG(IT_REQA22),EX(0xf),EX(0xe));	
}

/**
 * 
 * @brief	使能16位 Timer 的中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_TM16(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ19) ;
	MODIFY_REG(PLIC_REG(IT_REQA19),EX(0xf),EX(0xe));	
}

/**
 * 
 * @brief 关掉16位 Timer 的中断
 * \n
 *
 * @retval None
 * \n
 */

void Ro_IT_Disable_TM16(void)
{
	CLEAR_BIT(PLIC_REG(IT_MASK),IT_IRQ19) ;
	MODIFY_REG(PLIC_REG(IT_REQA19),EX(0xf),EX(0xf)); 
}

/**
 * 
 * @brief	使能32位 Timer 的中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_TM32(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ20) ;
	MODIFY_REG(PLIC_REG(IT_REQA20),EX(0xf),EX(0xe));	
}

/**
 * 
 * @brief 关掉32位 Timer 的中断
 * \n
 *
 * @retval None
 * \n
 */

void Ro_IT_Disable_TM32(void)
{
	CLEAR_BIT(PLIC_REG(IT_MASK),IT_IRQ20) ;
	MODIFY_REG(PLIC_REG(IT_REQA20),EX(0xf),EX(0xf)); 
}

/**
 * 
 * @brief	使能SysTick
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_RTOS(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ0) ;
	MODIFY_REG(PLIC_REG(IT_REQA0),EX(0xf),EX(0xe));	
}
/**
 * 
 * @brief	使能GPIO0中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_GPIO0(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ8) ;
	MODIFY_REG(PLIC_REG(IT_REQA8),EX(0xf),EX(0xe));	
}
/**
 * 
 * @brief	使能GPIO1中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_GPIO1(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ9) ;
	MODIFY_REG(PLIC_REG(IT_REQA9),EX(0xf),EX(0xe));	
}
/**
 * 
 * @brief	使能GPIO2中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_GPIO2(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ10) ;
	MODIFY_REG(PLIC_REG(IT_REQA10),EX(0xf),EX(0xe));	
}
/**
 * 
 * @brief	使能GPIO3中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_GPIO3(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ11) ;
	MODIFY_REG(PLIC_REG(IT_REQA11),EX(0xf),EX(0xe));	

}
/**
 * 
 * @brief	使能GPIO4中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_GPIO4(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ4) ;
	MODIFY_REG(PLIC_REG(IT_REQA4),EX(0xf),EX(0xe));	
}
/**
 * 
 * @brief	使能GPIO5中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_GPIO5(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ5) ;
	MODIFY_REG(PLIC_REG(IT_REQA5),EX(0xf),EX(0xe));	
}
/**
 * 
 * @brief	使能GPIO6中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_GPIO6(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ6) ;
	MODIFY_REG(PLIC_REG(IT_REQA6),EX(0xf),EX(0xe));	
}
/**
 * 
 * @brief	使能GPIO7中断
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Enable_GPIO7(void)
{
	SET_BIT(PLIC_REG(IT_MASK),IT_IRQ7) ;
	MODIFY_REG(PLIC_REG(IT_REQA7),EX(0xf),EX(0xe));	
}
/**
 * 
 * @brief	使能GPIO B组中断选择
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Sel_GPIOA(void)
{
	GPIOA->GPIO_A=0;
	GPIOA->GPIO_F=0;
	GPIOA->GPIO_OE=0;
	WRITE_REG(PLIC_REG(IT_EXTIRQ_SEL),EXTIC(IT_GPIOA<<14|IT_GPIOA<<12|IT_GPIOA<<10|IT_GPIOA<<8|IT_GPIOA<<6|IT_GPIOA<<4|IT_GPIOA<<2|IT_GPIOA<<0));	
}

/**
 * 
 * @brief	使能GPIO C组中断选择
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Sel_GPIOB(void)
{
	GPIOB->GPIO_A=0;
	GPIOB->GPIO_F=0;
	GPIOB->GPIO_OE=0;
	WRITE_REG(PLIC_REG(IT_EXTIRQ_SEL),EXTIC(IT_GPIOB<<14|IT_GPIOB<<12|IT_GPIOB<<10|IT_GPIOB<<8|IT_GPIOB<<6|IT_GPIOB<<4|IT_GPIOB<<2|IT_GPIOB<<0));	
}
/**
 * 
 * @brief	使能GPIO D组中断选择
 * \n
 *
 * @retval	None
 * \n
 */
void Ro_IT_Sel_GPIOC(void)
{
	GPIOC->GPIO_A=0;
	GPIOC->GPIO_F=0;
	GPIOC->GPIO_OE=0;
	WRITE_REG(PLIC_REG(IT_EXTIRQ_SEL),EXTIC(IT_GPIOC<<14|IT_GPIOC<<12|IT_GPIOC<<10|IT_GPIOC<<8|IT_GPIOC<<6|IT_GPIOC<<4|IT_GPIOC<<2|IT_GPIOC<<0));	
}
/**
 * 
 * @brief	使能GPIO E组中断选择
 * \n
 * @note 此款CPU只支持GPIO B C D E四组进行GPIO中断，其他组不支持
 * @retval	None
 * \n
 */
void Ro_IT_Sel_GPIOD(void)
{
	GPIOD->GPIO_A=0;
	GPIOD->GPIO_F=0;
	GPIOD->GPIO_OE=0;
	WRITE_REG(PLIC_REG(IT_EXTIRQ_SEL),EXTIC(IT_GPIOD<<14|IT_GPIOD<<12|IT_GPIOD<<10|IT_GPIOD<<8|IT_GPIOD<<6|IT_GPIOD<<4|IT_GPIOD<<2|IT_GPIOD<<0));	
}
/**
 * 
 * @brief	GPIO 4/5触发中断，两个管脚共用一个中断处理函数
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_GPIO45_IRQHandle(void)
{
}
/**
 * 
 * @brief	GPIO 6 触发中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_GPIO6_IRQHandle(void)
{
}
/**
 * 
 * @brief	GPIO 7 触发中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_GPIO7_IRQHandle(void)
{
}
/**
 * 
 * @brief	GPIO 0 触发中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_GPIO0_IRQHandle(void)
{
}
/**
 * 
 * @brief	GPIO 1 触发中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_GPIO1_IRQHandle(void)
{
}

/**
 * 
 * @brief	GPIO 2 触发中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_GPIO2_IRQHandle(void)
{
}
/**
 * 
 * @brief	GPIO 3 触发中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_GPIO3_IRQHandle(void)
{
}

/**
 * 
 * @brief	窗口看门狗触发中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_WWDG_IRQHandle(void)
{
	Ro_WWDG_Refresh_IT(0x1FF);
}

/**
 * 
 * @brief	DMA0的 channel 0 和channel 1共用此中断
 * \n
 * @note	此中断会被bootloader调用，然后设置remap之后进入主程序才会被用户使用
 * @retval	None
 * \n
 */
void Ro_DMA0_CH01_IRQHandle(void)
{
	//if(!READ_BIT(POWER_CLK_REG(CLOCK_00),0x02))
	//{
    //    SET_BIT(POWER_CLK_REG(CLOCK_05),0x02);
	//}
   // CLEAR_BIT(POWER_CLK_REG(CLOCK_02), 0x02);
	//CLEAR_BIT(POWER_CLK_REG(CLOCK_05), 0x02);
}

/**
 * 
 * @brief	DMA1的 channel 0 和channel 1共用此中断
 * \n
 * @note	此中断会被bootloader调用，然后设置remap之后进入主程序才会被用户使用
 * @retval	None
 * \n
 */
void Ro_DMA1_CH01_IRQHandle(void)
{
    //WRITE_REG(POWER_CLK_REG(CLOCK_02),CLOCK_REBASE1(1)|CLOCK_RELOCK1(1));
}
/**
 * 
 * @brief	DMA0 和DMA1的 channel 2共用此中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_DMA01_CH2_IRQHandle(void)
{
}
/**
 * 
 * @brief	DMA0 和DMA1的 channel 3共用此中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_DMA01_CH3_IRQHandle(void)
{
}
/**
 * 
 * @brief	DMA0 和DMA1的 channel 4共用此中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_DMA01_CH4_IRQHandle(void)
{
}
/**
 * 
 * @brief	DMA0 和DMA1的 channel 5共用此中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_DMA01_CH5_IRQHandle(void)
{
}
/**
 * 
 * @brief	DMA0 和DMA1的 channel 6共用此中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_DMA01_CH6_IRQHandle(void)
{
}

/**
 * 
 * @brief	TIM1 TIM2 和TIM3共用一个中断向量，通过读取IRQ的状态来判断timer来自于谁
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_TIM16_IRQHandle(void)
{

}
/**
 * 
 * @brief	TIM0 和TIM4共用一个中断向量，通过读取IRQ的状态来判断timer来自于谁
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_TIM32_IRQHandle(void)
{

}
/**
 * 
 * @brief	DMA0 和DMA1的 channel 5共用此中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_DMA01_CH7_IRQHandle(void)
{
}
/**
 * 
 * @brief	SPI0触发中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_SSP0_IRQHandle(void)
{
}
/**
 * 
 * @brief	SPI1触发中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_SSP1_IRQHandle(void)
{
}
/**
 * 
 * @brief	SPI2触发中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_SSP2_IRQHandle(void)
{
}

/**
 * 
 * @brief	Adaptive 触发的中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_Adptive_IRQHandle()
{
	 

}
/**
 * 
 * @brief	UART0触发中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_UART0_IRQHandle(void)
{
   
}
/**
 * 
 * @brief	UART1触发中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_UART1_IRQHandle(void)
{

}

/**
 * 
 * @brief	IIC触发的中断
 * \n
 *
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_IIC_IRQHandle(void)
{
}

/**
 * 
 * @brief	系统崩溃的中断
 * \n
 *
 * @param	temp		
 * @retval	None
 * \n
 */
void __attribute__((weak)) Ro_Crash_IRQHandle(void)
{
	while(1)
		uart0_putchar('C');
}


#endif
