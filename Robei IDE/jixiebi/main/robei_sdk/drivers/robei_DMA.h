#ifndef _HAMSTER_DMA_H_
#define _HAMSTER_DMA_H_
#include "config.h"
#ifdef RO_DMA_MODULE_ENABLED
	/* Register offsets */
typedef struct
{
  __IO uint32_t CONF_CHA;
  __IO uint32_t CONF_CHB;
  __IO uint32_t ADDR_SOURCE;
  __IO uint32_t ADDR_DEST;
} DMA_Channel_TypeDef;
typedef struct
{
  __IO uint32_t OVERAL_CHSEL;
  __IO uint32_t INT_STATUS;
  __IO uint32_t INT_CLEAR;
} DMA_Overal_TypeDef;

/**
  * @brief  DMA Configuration Structure definition
  */
typedef struct
{
  uint32_t SrcType;                 /*!< Specifies if the data will be transferred from memory to peripheral, 
                                           from memory to memory or from peripheral to memory.
                                           This parameter can be a value of @ref DMA_Data_transfer_direction */
  uint32_t DstType;				 /*!< Specifies if the data will be transferred from memory to peripheral, 
											from memory to memory or from peripheral to memory.
											This parameter can be a value of @ref DMA_Data_transfer_direction */
  uint32_t Mode;                      /*!< Specifies the operation mode of the DMAy Channelx.
                                           This parameter can be a value of @ref DMA_mode
                                           @note The circular buffer mode cannot be used if the memory-to-memory
                                                 data transfer is configured on the selected Channel */

  uint32_t Priority;                  /*!< Specifies the software priority for the DMAy Channelx.
                                           This parameter can be a value of @ref DMA_Priority_level */
} DMA_InitTypeDef;

/** 
  * @brief  DMA handle Structure definition
  */
typedef struct __DMA_HandleTypeDef
{
  DMA_Channel_TypeDef   *Instance;                       /*!< Register base address                  */
  
  DMA_InitTypeDef       Init;                            /*!< DMA communication parameters           */ 
} DMA_HandleTypeDef;  
/** 
  * @brief  HAL DMA Callback ID structure definition
  */
typedef enum
{
  DMA_IIC       = 0x00U,    /*!< Full transfer     */
  DMA_UART      = 0x01U,    /*!< Half transfer     */
  DMA_DEFAULT    = 0x02U,        
    
}HAL_DMA_DeviceTypeDef;


#define DMA0_BASE             (DMA0_CTRL_ADDR + 0x00000000UL)
#define DMA1_BASE             (DMA1_CTRL_ADDR + 0x00000000UL)
#define DMA0_Channel0_BASE    (DMA0_BASE + 0x00000004UL)
#define DMA0_Channel1_BASE    (DMA0_BASE + 0x00000014UL)
#define DMA0_Channel2_BASE    (DMA0_BASE + 0x00000024UL)
#define DMA0_Channel3_BASE    (DMA0_BASE + 0x00000034UL)
#define DMA0_Channel4_BASE    (DMA0_BASE + 0x00000044UL)
#define DMA0_Channel5_BASE    (DMA0_BASE + 0x00000054UL)
#define DMA0_Channel6_BASE    (DMA0_BASE + 0x00000064UL)
#define DMA0_Channel7_BASE    (DMA0_BASE + 0x00000074UL)

#define DMA1_Channel0_BASE    (DMA1_BASE + 0x00000004UL)
#define DMA1_Channel1_BASE    (DMA1_BASE + 0x00000014UL)
#define DMA1_Channel2_BASE    (DMA1_BASE + 0x00000024UL)
#define DMA1_Channel3_BASE    (DMA1_BASE + 0x00000034UL)
#define DMA1_Channel4_BASE    (DMA1_BASE + 0x00000044UL)
#define DMA1_Channel5_BASE    (DMA1_BASE + 0x00000054UL)
#define DMA1_Channel6_BASE    (DMA1_BASE + 0x00000064UL)
#define DMA1_Channel7_BASE    (DMA1_BASE + 0x00000074UL)

#define DMA0_Channel0       ((DMA_Channel_TypeDef *)DMA0_Channel0_BASE)
#define DMA0_Channel1       ((DMA_Channel_TypeDef *)DMA0_Channel1_BASE)
#define DMA0_Channel2       ((DMA_Channel_TypeDef *)DMA0_Channel2_BASE)
#define DMA0_Channel3       ((DMA_Channel_TypeDef *)DMA0_Channel3_BASE)
#define DMA0_Channel4       ((DMA_Channel_TypeDef *)DMA0_Channel4_BASE)
#define DMA0_Channel5       ((DMA_Channel_TypeDef *)DMA0_Channel5_BASE)
#define DMA0_Channel6       ((DMA_Channel_TypeDef *)DMA0_Channel6_BASE)
#define DMA0_Channel7       ((DMA_Channel_TypeDef *)DMA0_Channel7_BASE)

#define DMA1_Channel0       ((DMA_Channel_TypeDef *)DMA1_Channel0_BASE)
#define DMA1_Channel1       ((DMA_Channel_TypeDef *)DMA1_Channel1_BASE)
#define DMA1_Channel2       ((DMA_Channel_TypeDef *)DMA1_Channel2_BASE)
#define DMA1_Channel3       ((DMA_Channel_TypeDef *)DMA1_Channel3_BASE)
#define DMA1_Channel4       ((DMA_Channel_TypeDef *)DMA1_Channel4_BASE)
#define DMA1_Channel5       ((DMA_Channel_TypeDef *)DMA1_Channel5_BASE)
#define DMA1_Channel6       ((DMA_Channel_TypeDef *)DMA1_Channel6_BASE)
#define DMA1_Channel7       ((DMA_Channel_TypeDef *)DMA1_Channel7_BASE)

#define DMA0_Overal       ((uint32_t *)DMA0_BASE)
#define DMA1_Overal       ((uint32_t *)DMA1_BASE)
#define DMA0_OveralCH_BASE    (DMA0_BASE + 0x00000084UL)
#define DMA1_OveralCH_BASE    (DMA1_BASE + 0x00000084UL)

#define DMA0_Overal_CH    ((DMA_Overal_TypeDef *)DMA0_OveralCH_BASE)
#define DMA1_Overal_CH    ((DMA_Overal_TypeDef *)DMA1_OveralCH_BASE)

/** @defgroup DMA_Priority_level DMA Priority level
  * @{
  */
#define DMA_PRIORITY_LOW             0x00000000U               /*!< Priority level : Low       */
#define DMA_PRIORITY_MEDIUM          0x00000001U  /*!< Priority level : Medium    */
#define DMA_PRIORITY_HIGH            0x00000002U  /*!< Priority level : High      */
#define DMA_PRIORITY_VERY_HIGH       0x00000003U   /*!< Priority level : Very_High */

/** @defgroup DMA_Priority_level DMA Priority level
  * @{
  */
#define DMA_MODE_BYTE           0x00000000U               /*!< Priority level : Low       */
#define DMA_MODE_HALFWORD       0x00000001U  /*!< Priority level : Medium    */
#define DMA_MODE_WORD           0x00000002U  /*!< Priority level : High      */


/****************************** DMA Instances *********************************/
#define IS_DMA0_ALL_INSTANCE(INSTANCE) (((INSTANCE) == DMA0_Channel1) || \
                                       ((INSTANCE) == DMA0_Channel2) || \
                                       ((INSTANCE) == DMA0_Channel3) || \
                                       ((INSTANCE) == DMA0_Channel4) || \
                                       ((INSTANCE) == DMA0_Channel5) || \
                                       ((INSTANCE) == DMA0_Channel6) || \
                                       ((INSTANCE) == DMA0_Channel7))
#define IS_DMA1_ALL_INSTANCE(INSTANCE) (((INSTANCE) == DMA1_Channel1) || \
									   ((INSTANCE) == DMA1_Channel2) || \
									   ((INSTANCE) == DMA1_Channel3) || \
									   ((INSTANCE) == DMA1_Channel4) || \
								       ((INSTANCE) == DMA1_Channel5) || \
										((INSTANCE) == DMA1_Channel6) || \
										((INSTANCE) == DMA1_Channel7))




//-------------------------------------------------------------------------------
#define DMA_OVERALCONFIG		(0x0000)

#define DMA_CH0_CONFIG_CHA		(0x0004)
#define DMA_CH0_CONFIG_CHB		(0x0008)
#define DMA_CH0_ADDR_SOURCE		(0x000c)
#define DMA_CH0_ADDR_DEST		(0x0010)

#define DMA_CH1_CONFIG_CHA		(0x0014)
#define DMA_CH1_CONFIG_CHB		(0x0018)
#define DMA_CH1_ADDR_SOURCE		(0x001c)
#define DMA_CH1_ADDR_DEST		(0x0020)

#define DMA_CH2_CONFIG_CHA		(0x0024)
#define DMA_CH2_CONFIG_CHB		(0x0028)
#define DMA_CH2_ADDR_SOURCE		(0x002c)
#define DMA_CH2_ADDR_DEST		(0x0030)

#define DMA_CH3_CONFIG_CHA		(0x0034)
#define DMA_CH3_CONFIG_CHB		(0x0038)
#define DMA_CH3_ADDR_SOURCE		(0x003c)
#define DMA_CH3_ADDR_DEST		(0x0040)

#define DMA_CH4_CONFIG_CHA		(0x0044)
#define DMA_CH4_CONFIG_CHB		(0x0048)
#define DMA_CH4_ADDR_SOURCE		(0x004c)
#define DMA_CH4_ADDR_DEST		(0x0050)

#define DMA_CH5_CONFIG_CHA		(0x0054)
#define DMA_CH5_CONFIG_CHB		(0x0058)
#define DMA_CH5_ADDR_SOURCE		(0x005c)
#define DMA_CH5_ADDR_DEST		(0x0060)

#define DMA_CH6_CONFIG_CHA		(0x0064)
#define DMA_CH6_CONFIG_CHB		(0x0068)
#define DMA_CH6_ADDR_SOURCE		(0x006c)
#define DMA_CH6_ADDR_DEST		(0x0070)

#define DMA_CH7_CONFIG_CHA		(0x0074)
#define DMA_CH7_CONFIG_CHB		(0x0078)
#define DMA_CH7_ADDR_SOURCE		(0x007c)
#define DMA_CH7_ADDR_DEST		(0x0080)

#define DMA_OVERAL_CH_SELECT	(0x0084)
#define DMA_INT_STATUS			(0x0088)
#define DMA_INT_CLEAR			(0x008c)

/* Fields */
#define ACK0(x)    (((x) & 0x1) << 16) 
#define ACK1(x)    (((x) & 0x1) << 17) 
#define ACK2(x)    (((x) & 0x1) << 18) 
#define ACK3(x)    (((x) & 0x1) << 19) 
#define ACK4(x)    (((x) & 0x1) << 20) 
#define ACK5(x)    (((x) & 0x1) << 21) 
#define ACK6(x)    (((x) & 0x1) << 22) 
#define ACK7(x)    (((x) & 0x1) << 23) 

#define DH(x)    (((x) & 0xF) << 24) 
#define CREQ(x)    (((x) & 0x1) << 31) 


#define CHA_CE0(x)   (((x) & 0x1) << 0)
#define CHA_TC0(x)   (((x) & 0xffff) << 1)//counter
#define CHA_BC0(x)   (((x) & 0xf) << 17)
#define CHA_BT0(x)   (((x) & 0xf) << 21)
#define CHA_PL0(x)   (((x) & 0x3) << 25)
#define CHA_ST0(x)   (((x) & 0x1) << 30)
#define CHA_PB0(x)   (((x) & 0x1) << 31)

#define CHB_CIE0(x)   (((x) & 0x1) << 19)
//#define CHB_EIE0(x)   (((x) & 0x1) << 20)
#define CHB_FD0(x)   (((x) & 0x1) << 24)
#define CHB_FS0(x)   (((x) & 0x1) << 25)
#define CHB_TW0(x)   (((x) & 0x3) << 26)
#define CHB_MS0(x)   (((x) & 0x3) << 28)


#define OVERAL_CHSEL_CS0(x)   (((x) & 0x3) << 0)
#define OVERAL_CHSEL_CS1(x)   (((x) & 0x3) << 4)
#define OVERAL_CHSEL_CS2(x)   (((x) & 0x3) << 8)
#define OVERAL_CHSEL_CS3(x)   (((x) & 0x3) << 12)
#define OVERAL_CHSEL_CS4(x)   (((x) & 0x3) << 16)
#define OVERAL_CHSEL_CS5(x)   (((x) & 0x3) << 20)
#define OVERAL_CHSEL_CS6(x)   (((x) & 0x3) << 24)
#define OVERAL_CHSEL_CS7(x)   (((x) & 0x3) << 28)

#define INT_CLEAR_DGIE0(x)   (((x) & 0x1) << 0)
#define INT_CLEAR_DTCIE0(x)   (((x) & 0x1) << 1)
#define INT_CLEAR_DTEIE0(x)   (((x) & 0x1) << 3)

#define INT_CLEAR_DGIE1(x)   (((x) & 0x1) << 4)
#define INT_CLEAR_DTCIE1(x)   (((x) & 0x1) << 5)
#define INT_CLEAR_DTEIE1(x)   (((x) & 0x1) << 7)

#define INT_CLEAR_DGIE2(x)   (((x) & 0x1) << 8)
#define INT_CLEAR_DTCIE2(x)   (((x) & 0x1) << 9)
#define INT_CLEAR_DTEIE2(x)   (((x) & 0x1) << 11)

#define INT_CLEAR_DGIE3(x)   (((x) & 0x1) << 12)
#define INT_CLEAR_DTCIE3(x)   (((x) & 0x1) << 13)
#define INT_CLEAR_DTEIE3(x)   (((x) & 0x1) << 15)

#define INT_CLEAR_DGIE4(x)   (((x) & 0x1) << 16)
#define INT_CLEAR_DTCIE4(x)   (((x) & 0x1) <<17)
#define INT_CLEAR_DTEIE4(x)   (((x) & 0x1) <<19)

#define INT_CLEAR_DGIE5(x)   (((x) & 0x1) << 20)
#define INT_CLEAR_DTCIE5(x)   (((x) & 0x1) <<21)
#define INT_CLEAR_DTEIE5(x)   (((x) & 0x1) <<23)

#define INT_CLEAR_DGIE6(x)   (((x) & 0x1) << 24)
#define INT_CLEAR_DTCIE6(x)   (((x) & 0x1) << 1)
#define INT_CLEAR_DTEIE6(x)   (((x) & 0x1) << 3)

#define INT_CLEAR_DGIE7(x)   (((x) & 0x1) << 0)
#define INT_CLEAR_DTCIE7(x)   (((x) & 0x1) << 1)
#define INT_CLEAR_DTEIE7(x)   (((x) & 0x1) << 3)


void Ro_Init_DMA_CLK(void);
void Ro_Init_DMA(DMA_HandleTypeDef *hdma);
void Ro_DMA_Start(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
void Ro_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
void Ro_DMA_Start(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
void Ro_DMA_Start_8World(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
void Ro_DMA_Start_4World(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);

#endif
#endif
