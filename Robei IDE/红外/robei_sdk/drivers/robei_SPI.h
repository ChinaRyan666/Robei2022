#ifndef _HAMSTER_SPI_H_
#define _HAMSTER_SPI_H_
#include "config.h"
#ifdef RO_SPI_MODULE_ENABLED
#define SPI0_BASE	0xfffec000
#define SPI1_BASE	0xfffdf000

#define WINBOND_FLASH_QE	0x31
#define WINBOND_QUAD_EN		0x02
#define WINBOND_QUAD_DISEN	0x00

#define MXIC_QUAD_EN		0x40
#define MXIC_FLASH_QE		0x01
#define MXIC_QUAD_DISEN		0x00

#define GD_FLASH_QE			0x31
#define GD_QUAD_EN			0x02
#define GD_QUAD_DISEN		0x00

typedef struct
{
	volatile uint32_t CR0;	/*!< SPI registers base address               */
	volatile uint32_t CR1;
	volatile uint32_t DR;
	volatile uint32_t SR;
	volatile uint32_t CPR;
	volatile uint32_t IMR;
	volatile uint32_t CR;
	volatile uint32_t MISR;
	volatile uint32_t ICR;
	volatile uint32_t DER;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
}SPI_TypeDef;

/**
  * @brief  SPI Configuration Structure definition
  */
typedef struct
{
  uint32_t Mode;                /*!< Specifies the SPI operating mode.
                                     This parameter can be a value of @ref SPI_Mode */

  uint32_t Direction;           /*!< Specifies the SPI bidirectional mode state.
                                     This parameter can be a value of @ref SPI_Direction */

  uint32_t DataSize;            /*!< Specifies the SPI data size.
                                     This parameter can be a value of @ref SPI_Data_Size */

  uint32_t CLKPolarity;         /*!< Specifies the serial clock steady state.
                                     This parameter can be a value of @ref SPI_Clock_Polarity */

  uint32_t CLKPhase;            /*!< Specifies the clock active edge for the bit capture.
                                     This parameter can be a value of @ref SPI_Clock_Phase */

  uint32_t NSS;                 /*!< Specifies whether the NSS signal is managed by
                                     hardware (NSS pin) or by software using the SSI bit.
                                     This parameter can be a value of @ref SPI_Slave_Select_management */

  uint32_t BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                     used to configure the transmit and receive SCK clock.
                                     This parameter can be a value of @ref SPI_BaudRate_Prescaler
                                     @note The communication clock is derived from the master
                                     clock. The slave clock does not need to be set. */

  uint32_t FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                     This parameter can be a value of @ref SPI_MSB_LSB_transmission */

  uint32_t TIMode;              /*!< Specifies if the TI mode is enabled or not.
                                     This parameter can be a value of @ref SPI_TI_mode */

  uint32_t CRCCalculation;      /*!< Specifies if the CRC calculation is enabled or not.
                                     This parameter can be a value of @ref SPI_CRC_Calculation */

  uint32_t CRCPolynomial;       /*!< Specifies the polynomial used for the CRC calculation.
                                     This parameter must be an odd number between Min_Data = 1 and Max_Data = 65535 */
} SPI_InitTypeDef;

typedef struct __SPI_HandleTypeDef
{
  SPI_TypeDef                *Instance;      /*!< SPI registers base address               */

  SPI_InitTypeDef            Init;           /*!< SPI communication parameters             */
}SPI_HandleTypeDef;
typedef enum
{
	SPI_SINGLE_WORD			= 31,
	SPI_SINGLE_HALFWORD		= 15,
	SPI_SINGLE_BYTE			= 7,
	SPI_QUAD_WORD			= 7,
	SPI_QUAD_HALFWORD		= 3,
	SPI_QUAD_BYTE			= 1,
}SPI_DataLen;

#define SPI0 ((SPI_TypeDef *)SPI0_BASE)
#define SPI1 ((SPI_TypeDef *)SPI1_BASE)

#define SPI_CTL0			(0x0000)
#define SPI_CTL1			(0x0004)
#define SPI_DATA			(0x0008)
#define SPI_STATUS			(0x000c)
#define SPI_CLOCK_PREC		(0x0010)
#define SPI_IT_MSK			(0x0014)
#define SPI_CMD_REG			(0x0018)
#define SPI_MSK_IT			(0x001c)
#define SPI_IT_CLR			(0x0020)
#define SPI_DMA_EN			(0x0024)
#define SPI_RX_CRC			(0x0028)
#define SPI_TX_CRC			(0x0020)

/* Fields */
#define LBM(x)				(((x) & 0x1) << 0) 
#define SSPEN(x)			(((x) & 0x1) << 1) 
#define SSPM(x)				(((x) & 0x1) << 2) 
#define SFE(x)				(((x) & 0x1) << 3) 
#define SDOD(x)				(((x) & 0x1) << 4) 
#define RFR(x)				(((x) & 0x1) << 5) 
#define TFR(x)				(((x) & 0x1) << 6) 
#define LSBF(x)				(((x) & 0x1) << 7) 
#define SSICS(x)    		(((x) & 0x1) << 8) 
#define SSME(x)				(((x) & 0x1) << 9) 
#define RXONLY(x)			(((x) & 0x1) << 10) 
#define CRCL(x)				(((x) & 0x1) << 11) 
#define CRCN(x)				(((x) & 0x1) << 12) 
#define CRCE(x)				(((x) & 0x1) << 13) 
#define BIDIO(x)    		(((x) & 0x1) << 14) 
#define BIDIM(x)    		(((x) & 0x1) << 15) 
#define tempSPI0(x)			(((x) & 0xff) << 24) 
#define tempClockSPI1(x)	(((x) &0x1ffff) << 15) 

#define DSS(x)    			(((x) & 0x1f) << 0) 
#define FRF(x)    			(((x) & 0x1) << 5) 
#define SPO(x)    			(((x) & 0x1) << 6) 
#define SPH(x)   			(((x) & 0x1) << 7) 
#define SCR(x)    			(((x) & 0xff) << 8) 

#define TEMPTY(x)    		(((x) & 0x1) << 0) 
#define nTFULL(x)    		(((x) & 0x1) << 1) 
#define nREMPTY(x)    		(((x) & 0x1) << 2) 
#define RFULL(x)    		(((x) & 0x1) << 3) 
#define READY(x)    		(((x) & 0x1) << 4) 

#define CPSR(x)    			(((x) & 0x7f) << 1) 

#define EXIM(x)    			(((x) & 0x1) << 1) 
#define RXIM(x)    			(((x) & 0x1) << 2) 
#define TXIM(x)    			(((x) & 0x1) << 3) 

#define CMD(x)    			(((x) & 0xff) << 0) 
#define DEMO(x)    			(((x) & 0x1) << 8) 
#define RXMIS(x)    		(((x) & 0x1) << 2) 
#define TXMIS(x)    		(((x) & 0x1) << 3) 
#define CIMIS(x)    		(((x) & 0x1) << 4) 

#define SPI_RDMAE(x)    	(((x) & 0x1) << 0) 
#define SPI_TDMAE(x)    	(((x) & 0x1) << 1) 

#define RX_CRC(x)    		(((x) & 0xffff) << 0) 
#define TX_CRC(x)    		(((x) & 0xffff) << 0) 

/** @defgroup SPI_Data_Size SPI Data Size
  * @{
  */
#define SPI_DATASIZE_8BIT               0x00000000U
#define SPI_DATASIZE_16BIT              0x00000001U
/**
  * @}
  */


/** @defgroup SPI_Mode SPI Mode
  * @{
  */
#define SPI_MODE_DATA                  (0x0U)
#define SPI_MODE_FLASH                 (0x1U)
/**
  * @}
  */
	/** @defgroup SPI_Clock_Polarity SPI Clock Polarity
	  * @{
	  */
#define SPI_POLARITY_LOW                (0x00000000U)
#define SPI_POLARITY_HIGH               (0x00000001U)
	/**
	  * @}
	  */
	
	/** @defgroup SPI_Clock_Phase SPI Clock Phase
	  * @{
	  */
#define SPI_PHASE_1EDGE                 (0x00000000U)
#define SPI_PHASE_2EDGE                 (0x00000001U)
	/**
	  * @}
	  */


void Ro_SPI_Init(SPI_HandleTypeDef *hspi);
uint32_t Ro_SPI_ReadData(SPI_HandleTypeDef *hspi,uint32_t addr);
void Ro_SPI_WriteData(SPI_HandleTypeDef *hspi,uint32_t addr,uint32_t data);
void Ro_SPI_Cmd(SPI_HandleTypeDef *hspi,uint8_t mode,uint32_t cmd);
void Ro_SPI_SetupLen(SPI_HandleTypeDef *hspi,SPI_DataLen len);
uint32_t Ro_SPI_ReadStatus(SPI_HandleTypeDef *hspi);
Ro_StatusTypeDef Ro_SPI_WaitForReady(SPI_HandleTypeDef *hspi);
void Ro_SPI_QuadEN(SPI_HandleTypeDef *hspi,uint8_t FlashType,uint8_t isEn);


#endif
#endif
