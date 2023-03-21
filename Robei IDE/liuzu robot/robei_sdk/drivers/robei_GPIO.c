/**
 * @file	hamster_GPIO.c
 * @brief	GPIO接口
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
#include "config.h"

#ifdef RO_GPIO_MODULE_ENABLED
/*
Hamster GPIO 操作流程
1、设置方向，输入 输出
2、设置复用功能
3、操作
 toConfirm:如何使用GPIO的中断
*/
#include "robei_GPIO.h"



/**
 * 
 * @brief	GPIO 初始化
 * \n
 *
 * @param	GPIOx		GPIO对应的组	
 *		@arg GPIOA-GPIOM
 * @param	GPIO_Init	GPIO对应的管脚	
 *		@arg GPIO_Init:Pin: GPIO_PIN_0-GPIO_PIN_7
 *		@arg GPIO_Init:Mode:GPIO_MODE_INPUT;GPIO_MODE_OUTPUT;GPIO_MODE_IT_RISING;GPIO_MODE_IT_FALLING;GPIO_MODE_IT_RISING_FALLING
 * @retval	None
 * \n
 */
void Ro_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
	uint32_t position = 0x00u;
	uint32_t ioposition;
	uint32_t iocurrent;
	uint32_t itstate=0;
	MODIFY_REG(POWER_CLK_REG(CLOCK_WWDG),CLOCK_GPEN(0x1),CLOCK_GPEN(1));


	/* Configure the port pins */
	while (((GPIO_Init->Pin) >> position) != 0x00u)
	{
	/* Get the IO position */
	ioposition = (0x01uL << position);

	/* Get the current IO position */
	iocurrent = (uint32_t)(GPIO_Init->Pin) & ioposition;

	if (iocurrent == ioposition)
	{

	  //GPIO A F 可以都设置成0
		CLEAR_BIT(GPIOx->GPIO_A,ioposition);
		CLEAR_BIT(GPIOx->GPIO_F,ioposition);

		if(ioposition<0x10)
            itstate=1<<(8+position);
        else
            itstate=1<<position;
		/* Configure the interrupt mask */
		 if ((GPIO_Init->Mode & GPIO_MODE_OUTPUT) == GPIO_MODE_OUTPUT)
		{
		  SET_BIT(GPIOx->GPIO_OE,ioposition);
		}
		else 
		{
		  CLEAR_BIT(GPIOx->GPIO_OE,ioposition);
        }
	/* Enable or disable the rising trigger */
        if ((GPIO_Init->Mode & GPIO_MODE_IT_RISING) == GPIO_MODE_IT_RISING)
        {
            //SET_BIT(PLIC_REG(IT_RISING_TRIG),(itstate));	
            WRITE_REG(PLIC_REG(IT_RISING_TRIG),(PLIC_REG(IT_RISING_TRIG))|itstate);
        }
        /* Enable or disable the falling trigger */
        if ((GPIO_Init->Mode & GPIO_MODE_IT_FALLING) == GPIO_MODE_IT_FALLING)
        {
            //SET_BIT(PLIC_REG(IT_FALLING_TRIG),(itstate));	
            WRITE_REG(PLIC_REG(IT_FALLING_TRIG),(PLIC_REG(IT_FALLING_TRIG))|itstate);    
        }	  
	}

	position++;
	}
}
/**
  * @brief  写入输入GPIO当前组的管脚的状态
  * @param  GPIOx:		GPIO需要读取的组
  *         @arg GPIOA-GPIOM
  * @retval 当前组8个GIPO管脚的状态.
  */
void Ro_GPIO_WriteGroup(GPIO_TypeDef*GPIOx, uint8_t PinState)
{
	WRITE_REG(GPIOx->GPIO_W,PinState);
}

/**
  * @brief  读取输入GPIO当前组的管脚的状态
  * @param  GPIOx:		GPIO需要读取的组
  *         @arg GPIOA-GPIOM
  * @retval 当前组8个GIPO管脚的状态.
  */
GPIO_PinState Ro_GPIO_ReadGroup(GPIO_TypeDef *GPIOx)
{
  return GPIOx->GPIO_R&0xff;
}

/**
* @brief	更改当前GPIO组输入输出方向
  * @param	GPIOx:			GPIO需要切换方向的组GPIOA-GPIOM
  * @param	PinState:		GPIO管脚的状态
  * @param	PinDerection:	GPIO为输入还是输出
  *			@arg			GPIO_PIN_IN 输入方向
  *			@arg			GPIO_PIN_OUT 输出方向
  *         
  * @retval 
  */

void Ro_GPIO_SetupGroup_Direction(GPIO_TypeDef *GPIOx, uint8_t PinState,GPIO_PinDirection GPIO_InOut)
{
	if(GPIO_InOut==GPIO_PIN_IN)
	{
		CLEAR_BIT(GPIOx->GPIO_OE,0xff);
		}
	else
	{
		SET_BIT(GPIOx->GPIO_OE,0xff);
	}
}

/**
  * @brief  更改当前GPIO输入输出方向
  * @param  GPIOx:		GPIO需要切换方向的组GPIOA-GPIOM
  * @param  GPIO_Pin:	GPIO需要切换方向的管脚
  * @param  GPIO_InOut:	GPIO需要切换的方向
  *			@arg		GPIO_PIN_IN 输入方向
  *			@arg		GPIO_PIN_OUT 输出方向
  *         
  * @retval 
  */
void Ro_GPIO_SetDirection(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,GPIO_PinDirection GPIO_InOut)
{
    if(GPIO_InOut==GPIO_PIN_IN)
    {
        CLEAR_BIT(GPIOx->GPIO_OE,GPIO_Pin);
    }
    else
    {
        SET_BIT(GPIOx->GPIO_OE,GPIO_Pin);
    }
}

/**
  * @brief  读取输入GPIO的管脚的状态
  * @param  GPIOx:		GPIO隶属的组GPIOA-GPIOM
  * @param  GPIO_Pin:	要读取的GPIO的管脚
  *         
  * @retval The input port pin value.
  * 	@arg GPIO_PIN_SET,GPIO_PIN_RESET
  */
GPIO_PinState Ro_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  GPIO_PinState bitstatus;

  /* Check the parameters */
 
  if ((GPIOx->GPIO_R & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
  {
    bitstatus = GPIO_PIN_SET;
  }
  else
  {
    bitstatus = GPIO_PIN_RESET;
  }
  return bitstatus;
}

/**
  * @brief  写入输出GPIO的管脚的状态
  *
  *
  * @param  GPIOx: where x can be (B-M depending on device used) to select the GPIO peripheral
  * @param  GPIO_Pin: specifies the port bit to be written.
  *          This parameter can be one of GPIO_PIN_x where x can be (0..7).
  * @param  PinState: specifies the value to be written to the selected bit.
  *          This parameter can be one of the GPIO_PinState enum values:
  *            @arg GPIO_PIN_RESET: to clear the port pin
  *            @arg GPIO_PIN_SET: to set the port pin
  * @retval None
  */
void Ro_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
	/* Check the parameters */

	if (PinState != GPIO_PIN_RESET)
	{
		SET_BIT(GPIOx->GPIO_W,GPIO_Pin);
	}
	else
	{
		CLEAR_BIT(GPIOx->GPIO_W,GPIO_Pin);
	}
}

/**
  * @brief  重新映射GPIO组
  * @param  src:	需要映射的GPIO组GPB-GPL
  * @param  dest:	映射到的目标GPIO组GPB-GPL
  *         
  * @retval 
  */

void Ro_GPIO_Remap(uint8_t src,uint8_t dest)
{
	switch(src)
	{
		case GPB:
			REMAP_B(dest);
			break;
		case GPC:
			REMAP_C(dest);
			break;
		case GPD:
			REMAP_D(dest);
			break;
		case GPE:
			REMAP_E(dest);
			break;
		case GPF:
			REMAP_F(dest);
			break;
		case GPG:
			REMAP_G(dest);
			break;
		case GPH:
			REMAP_H(dest);
			break;
		case GPI:
			REMAP_I(dest);
			break;
		case GPJ:
			REMAP_J(dest);
			break;
		case GPK:
			REMAP_K(dest);
			break;
		case GPL:
			REMAP_L(dest);
			break;
		default:
			break;
	}
}



#endif
