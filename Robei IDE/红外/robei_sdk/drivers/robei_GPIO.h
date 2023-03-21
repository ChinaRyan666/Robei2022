#ifndef _HAMSTER_GPIO_H_
#define _HAMSTER_GPIO_H_
#include "config.h"
#include "platform.h"
#ifdef RO_GPIO_MODULE_ENABLED

#define GPIO_MODE_INPUT				(0x01)
#define GPIO_MODE_OUTPUT			(0x02)
#define GPIO_MODE_IT_RISING			(0x04)
#define GPIO_MODE_IT_FALLING		(0x08)
#define GPIO_MODE_IT_RISING_FALLING	(0x0c)

#define GPIO_BASE	0xfffe8000
//#define GPIOA_BASE	(GPIO_BASE+0x00)	 
#define GPIOA_BASE	(GPIO_BASE+0x04)
#define GPIOB_BASE	(GPIO_BASE+0x18)
#define GPIOC_BASE	(GPIO_BASE+0x2c) 
#define GPIOD_BASE	(GPIO_BASE+0x40)
#define GPIOE_BASE	(GPIO_BASE+0x54)
#define GPIOF_BASE	(GPIO_BASE+0x68)
#define GPIOG_BASE	(GPIO_BASE+0x7c)
#define GPIOH_BASE	(GPIO_BASE+0x90)
#define GPIOI_BASE	(GPIO_BASE+0xa4)
#define GPIOJ_BASE	(GPIO_BASE+0xb8)
#define GPIOK_BASE	(GPIO_BASE+0xcc)


typedef struct
{
	volatile uint32_t GPIO_W;	
	volatile uint32_t GPIO_OE;
	volatile uint32_t GPIO_F;
	volatile uint32_t GPIO_A;
	volatile uint32_t GPIO_R;
}GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef *)GPIOE_BASE)
#define GPIOF ((GPIO_TypeDef *)GPIOF_BASE)
#define GPIOG ((GPIO_TypeDef *)GPIOG_BASE)
#define GPIOH ((GPIO_TypeDef *)GPIOH_BASE)
#define GPIOI ((GPIO_TypeDef *)GPIOI_BASE)
#define GPIOJ ((GPIO_TypeDef *)GPIOJ_BASE)
#define GPIOK ((GPIO_TypeDef *)GPIOK_BASE)
#define GPIOL ((GPIO_TypeDef *)GPIOL_BASE)
//#define GPIOM ((GPIO_TypeDef *)GPIOM_BASE)

#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_All               ((uint16_t)0x00FF)  /* All pins selected */

//hamster GPIO 设置输出输入
#define GPIO_TEST_SET_DERICTION		(GPIOK->GPIO_OE)
#define GPIO_TEST_SET_GET_VAL		(GPIOK->GPIO_W)
//hamster GPIO 设置输出输入
#define GPIO_TEST_DISPLAY_OUR 		(GPIOK->GPIO_R)
#define GPIO_TEST_FUNCTION_REMAP	(GPIOK->GPIO_F)
#define GPIO_TEST_FUNCTION_SPI		(0x58)

#define GPIO_REMAP0		0xF4
#define GPIO_REMAP1		0xF8
#define GPB		0x00			
#define GPC		0x01	
#define GPD		0x02	
#define GPE		0x03	
#define GPF		0x04	
#define GPG		0x05	
#define GPH		0x06	
#define GPI		0x07	
#define GPJ		0x08
#define GPK		0x09	
#define GPL		0x0A	
#define GPM		0x0B

#define SET_B(x)			(((x) & 0xf) << 20)
#define SET_D(x)			(((x) & 0xf) << 16)
#define SET_F(x)			(((x) & 0xf) << 12)
#define SET_H(x)			(((x) & 0xf) << 8)
#define SET_J(x)			(((x) & 0xf) << 4)
#define SET_L(x)			(((x) & 0xf) << 0)

#define SET_C(x)			(((x) & 0xf) << 20)
#define SET_E(x)			(((x) & 0xf) << 16)
#define SET_G(x)			(((x) & 0xf) << 12)
#define SET_I(x)			(((x) & 0xf) << 8)
#define SET_K(x)			(((x) & 0xf) << 4)
#define SET_M(x)			(((x) & 0xf) << 0)

#define GPIO_M(x)			(((x) & 0xff) << 0)


#if 1
#define REMAP_B(x)			MODIFY_REG(GPIO_REG(GPIO_REMAP0),SET_B(0xf),(((x) & 0xf) << 20))
#define REMAP_D(x)			MODIFY_REG(GPIO_REG(GPIO_REMAP0),SET_D(0xf),(((x) & 0xf) << 16))
#define REMAP_F(x)			MODIFY_REG(GPIO_REG(GPIO_REMAP0),SET_F(0xf),(((x) & 0xf) << 12))
#define REMAP_H(x)			MODIFY_REG(GPIO_REG(GPIO_REMAP0),SET_H(0xf),(((x) & 0xf) << 8))
#define REMAP_J(x)			MODIFY_REG(GPIO_REG(GPIO_REMAP0),SET_J(0xf),(((x) & 0xf) << 4))
#define REMAP_L(x)			MODIFY_REG(GPIO_REG(GPIO_REMAP0),SET_L(0xf),(((x) & 0xf) << 0))

#define REMAP_C(x)			MODIFY_REG(GPIO_REG(GPIO_REMAP1),SET_C(0xf),(((x) & 0xf) << 20))
#define REMAP_E(x)			MODIFY_REG(GPIO_REG(GPIO_REMAP1),SET_E(0xf),(((x) & 0xf) << 16))
#define REMAP_G(x)			MODIFY_REG(GPIO_REG(GPIO_REMAP1),SET_G(0xf),(((x) & 0xf) << 12))
#define REMAP_I(x)			MODIFY_REG(GPIO_REG(GPIO_REMAP1),SET_I(0xf),(((x) & 0xf) << 8))
#define REMAP_K(x)			MODIFY_REG(GPIO_REG(GPIO_REMAP1),SET_K(0xf),(((x) & 0xf) << 4))
#define REMAP_M(x)			MODIFY_REG(GPIO_REG(GPIO_REMAP1),SET_M(0xf),(((x) & 0xf) << 0))

#endif

#define GPIOC_W_BASE			0x2C	
#define GPIOC_OE_BASE			0x30
#define GPIOC_FUNCTION_REMAP	(0x34)
#define GPIOC_ADATA_REMAP		(0x38)
#define GPIOC_R_BASE			0x3C
#define GPIOC_SET_DERICTION	(GPIOC_OE_BASE)
#define GPIOC_SET_GET_VAL	(GPIOC_W_BASE)
#define GPIOC_DISPLAY_OUT 	(GPIOC_R_BASE)
//#define GPIOC_FUNCTION_REMAP	(GPIOC_FUNCTION_REMAP)

#define GPIOD_W_BASE			0x40	
#define GPIOD_OE_BASE			0x44
#define GPIOD_FUNCTION_REMAP	0x48
#define GPIOD_ADATA_REMAP		0x4c
#define GPIOD_R_BASE			0x50
#define GPIOD_SET_DERICTION		(GPIOD_OE_BASE)
#define GPIOD_SET_GET_VAL		(GPIOD_W_BASE)
#define GPIOD_DISPLAY_OUR		(GPIOD_R_BASE)
//#define GPIOD_FUNCTION_REMAP	(GPIOD_FUNCTION_REMAP)

#define GPIOE_W_BASE			0x54	
#define GPIOE_OE_BASE			0x58
#define GPIOE_FUNCTION_REMAP	(0x5c)
#define GPIOE_ADATA_REMAP		(0x60)
#define GPIOE_SET_DERICTION	(GPIOE_OE_BASE)
#define GPIOE_FUNCTION_SPI	(0x58)


#define GPIOA_W_BASE			0x4	
#define GPIOA_OE_BASE			0x08
#define GPIOA_FUNCTION_REMAP	0x0c
#define GPIOA_ADATA_REMAP		0x10
#define GPIOA_R_BASE			0x14
#define GPIOA_SET_DERICTION		(GPIOA_OE_BASE)
#define GPIOA_SET_GET_VAL		(GPIOA_W_BASE)
#define GPIOA_DISPLAY_OUR		(GPIOA_R_BASE)


#define GPIOB_W_BASE			0x18	
#define GPIOB_OE_BASE			0x1c
#define GPIOB_FUNCTION_REMAP	0x20
#define GPIOB_ADATA_REMAP		0x24
#define GPIOB_R_BASE			0x28
#define GPIOB_SET_DERICTION		(GPIOB_OE_BASE)
#define GPIOB_SET_VAL		(GPIOB_W_BASE)
#define GPIOB_GET_VAL		(GPIOB_R_BASE)

#define GPIOF_W_BASE			0x68	
#define GPIOF_OE_BASE			0x6c
#define GPIOF_FUNCTION_REMAP	0x70
#define GPIOF_ADATA_REMAP		0x74
#define GPIOF_R_BASE			0x78
#define GPIOF_SET_DERICTION		(GPIOF_OE_BASE)
#define GPIOF_SET_GET_VAL		(GPIOF_W_BASE)
#define GPIOF_DISPLAY_OUR		(GPIOF_R_BASE)

/**
  * @brief GPIO Init structure definition
  */
typedef struct
{
  uint32_t Pin;       /*!< Specifies the GPIO pins to be configured.
                           This parameter can be any value of @ref GPIO_pins_define */

  uint32_t Mode;      /*!< Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref GPIO_mode_define */
} GPIO_InitTypeDef;

typedef enum
{
	GPIO_PIN_RESET=0U,
	GPIO_PIN_SET
}GPIO_PinState;
typedef enum
{
	GPIO_PIN_IN=0U,
	GPIO_PIN_OUT
}GPIO_PinDirection;

void Ro_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
GPIO_PinState Ro_GPIO_ReadGroup(GPIO_TypeDef *GPIOx);
GPIO_PinState Ro_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Ro_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void Ro_GPIO_Remap(uint8_t src,uint8_t dest);
void Ro_GPIO_SetDirection(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,GPIO_PinDirection GPIO_InOut);


#endif
#endif
