#ifndef _RO_UART_H_
#define _RO_UART_H_
#include "config.h"
#include "platform.h"
#ifdef RO_UART_MODULE_ENABLED
/** 
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */
 
typedef struct
{
	volatile uint32_t TDR;		/*!< USART Tx Data register,			Address offset: 0x00 */
	volatile uint32_t IER;		/*!< USART Int Enable register,			Address offset: 0x04 */
	volatile uint32_t ITR;		/*!< USART Interrupt register,			Address offset: 0x08 */
	volatile uint32_t LCR;		/*!< USART Line Control  register,		Address offset: 0x0C */
	volatile uint32_t MR;		/*!< USART Modem register,				Address offset: 0x10 */
	volatile uint32_t FLR;		/*!< USART Frame Length register,		Address offset: 0x14 */
	volatile uint32_t ICR;		/*!< USART int clear register,			Address offset: 0x18 */
	volatile uint32_t DCR;		/*!< USART DMA control register,		Address offset: 0x1C */
	volatile uint32_t PCR;		/*!< USART Prescaler control register,	Address offset: 0x20 */
	volatile uint32_t FCR;		/*!< USART Fifo control register,		Address offset: 0x24 */
	volatile uint32_t RDR;		/*!< USART Rx data register,			Address offset: 0x28 */
	volatile uint32_t DLR;		/*!< USART Dll register,				Address offset: 0x2C */
	volatile uint32_t DMR;		/*!< USART Dlm register,				Address offset: 0x30 */
} USART_TypeDef;
/**
  * @brief UART Init Structure definition
  */
typedef struct
{
  uint32_t BaudRate;                  /*!< This member configures the UART communication baud rate.
                                           The baud rate is computed using the following formula:
                                           - IntegerDivider = ((PCLKx) / (16 * (huart->Init.BaudRate)))
                                           - FractionalDivider = ((IntegerDivider - ((uint32_t) IntegerDivider)) * 16) + 0.5 */

  uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref UART_Word_Length */

  uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref UART_Stop_Bits */

  uint32_t Parity;                    /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref UART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */

  uint32_t Mode;                      /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref UART_Mode */

  uint32_t HwFlowCtl;                 /*!< Specifies whether the hardware flow control mode is enabled or disabled.
                                           This parameter can be a value of @ref UART_Hardware_Flow_Control */

  uint32_t OverSampling;              /*!< Specifies whether the Over sampling 8 is enabled or disabled, to achieve higher speed (up to fPCLK/8).
                                           This parameter can be a value of @ref UART_Over_Sampling. This feature is only available 
                                           on STM32F100xx family, so OverSampling parameter should always be set to 16. */
} UART_InitTypeDef;

/**
  * @brief  UART handle Structure definition
  */
typedef struct __UART_HandleTypeDef
{
  USART_TypeDef                 *Instance;        /*!< UART registers base address        */

  UART_InitTypeDef              Init;             /*!< UART communication parameters      */

} UART_HandleTypeDef;


#define  USART0_BASE 	    	0xfffe9000	
#define  USART1_BASE 	    	0xfffea000
	
#define UART0 ((USART_TypeDef *)USART0_BASE)
#define UART1 ((USART_TypeDef *)USART1_BASE)


	
#define	UART_FLAG_TC		(0x00020000)	
#define	UART_FLAG_BRKIF		(0x00000100)	
#define	UART_FLAG_TFE		(0x00000080)	
#define	Power_CLKSB0		0xfffe0c20
#define	Power_UART_CLKSB 	0xfffe0c30
#define	UART_Clock_Sel		0x0440499a
#define	TEST_DATA0 		 		0x01	
#define	TEST_DATA1 		  		0x02	
#define	TEST_DATA2 		  		0x03
#define	TEST_DATA3 		  		0x31	
	
#define  Clock_Select0u		0x1c94999c 
#define  Clock_Select0     0x0a12188c

#define UART_TX_DATA		(0x0000)
#define UART_STATUS		(0x0018)

#if 0
/* Register offsets */
#define UART_TX_DATA		(0x0000)
#define UART_IT_ENABLE		(0x0004)
#define UART_IT			(0x0008)
#define UART_LINECONTROL	(0x000c)
#define UART_MODEM			(0x0010)
#define UART_FRAME_LEN		(0x0014)
#define UART_IT_CLEAR		(0x0018)
#define UART_STATUS		(0x0018)
#define UART_DMA			(0x001c)
#define UART_PRESCALER		(0x0020)
#define UART_FIFO_CTRL		(0x0024)
#define UART_RX_DATA		(0x0028)
#define UART_DLL			(0x002c)
#define UART_DLM			(0x0030)
#endif

typedef enum
{
  PARITY_NONE       = 0x00U,   
  PARITY_ODD      	= 0x01U,    
  PARITY_EVEN    	= 0x02U,        
    
}RO_Uart_ParityTypeDef;
 
typedef enum
{
	STOP_ONE 	  	= 0x00U,	//1bit 
	STOP_HALF		= 0x01U,	  
	STOP_TWO 	  	= 0x02U,		  
	STOP_ONEHALF	= 0x03U,		  
  
}RO_Uart_StopBitTypeDef;


/** @defgroup UART_Word_Length UART Word Length
  * @{
  */
#define UART_WORDLENGTH_6B                  ( 0x1 << 28| 0x1 << 12) 
#define UART_WORDLENGTH_7B                  ( 0x1 << 28) 
#define UART_WORDLENGTH_8B                  0 
#define UART_WORDLENGTH_9B                  ( 0x1 << 12) 
/**
  * @}
  */
	
/** @defgroup UART_Over_Sampling UART Over Sampling
  * @{
  */
#define UART_OVERSAMPLING_16                    0x00000000U
#define UART_OVERSAMPLING_8                     0x00000001U
/**
  * @}
  */
/** @defgroup UART_Stop_Bits UART Number of Stop Bits
  * @{
  */
#define UART_STOPBITS_0_5				0x00000001U
#define UART_STOPBITS_1					0x00000000U
#define UART_STOPBITS_1_5				0x00000011U
#define UART_STOPBITS_2					0x00000010U
/**
  * @}
  */

/**
  * @}
  */
/** @defgroup UART_Stop_Bits UART MSBFirst/LSBFirst
  * @{
  */
#define UART_LSB				0x00000000U
#define UART_MSB				0x00000001U
/**
  * @}
  */


/* Fields */
#define UART_TXDATA(x)    (((x) & 0xffffffff) << 0)

#define UART_RSIE(x)    	(((x) & 0x1) << 3) 
#define UART_RBFIE(x)		(((x) & 0x1) << 5) 
#define UART_TCIE(x)    	(((x) & 0x1) << 6) 
#define UART_TBEIE(x)		(((x) & 0x1) << 7) 

#define UART_MINI(x)    	(((x) & 0xf) << 0) 


#define UART_UEN(x)		(((x) & 0x1) << 0) 
#define UART_SBC(x)    	(((x) & 0x1) << 1)
#define UART_RXEN(x)    	(((x) & 0x1) << 2)
#define UART_TXEN(x)    	(((x) & 0x1) << 3) 
#define UART_EPS(x)		(((x) & 0x1) << 9) 
#define UART_PEN(x)		(((x) & 0x1) << 10) 
#define UART_WLSURM0(x)	(((x) & 0x1) << 12) 
#define UART_WLSURM1(x)	(((x) & 0x1) << 28) 

#define UART_LBM(x)		(((x) & 0x1) << 3) 
#define UART_LBDIE(x)    	(((x) & 0x1) << 6) 
//#define UART_STOP0(x)    	(((x) & 0x1) << 12) 
//#define UART_STOP1(x)    	(((x) & 0x1) << 13) 
#define UART_STOP(x)    (((x) & 0x3) << 12) 
//#define uSTOP1(x)    (((x) & 0x1) << 13) 

#define UART_MSBFST(x)    	(((x) & 0x1) << 19)
#define UART_SCKEN(x)    	(((x) & 0x1) << 11)

#define UART_TMOV(x)    	(((x) & 0xffffff) << 0) 
#define UART_FLEN(x)    	(((x) & 0xff) << 24) 

#define UART_TXC(x)    	(((x) & 0x1) << 1)
#define UART_RSTART(x)    	(((x) & 0x1) << 2)
#define UART_TFE(x)    	(((x) & 0x1) << 3)
#define UART_RFF(x)    	(((x) & 0x1) << 4)
#define UART_u1DTR(x)        (((x) & 0x1) << 6)
#define UART_RBusy(x)    	(((x) & 0x1) << 5)
#define UART_BREAKF(x)    	(((x) & 0x1) << 6)
#define UART_TSTART(x)    	(((x) & 0x1) << 7)
#define UART_BreakIF(x)    (((x) & 0x1) << 8)

#define UART_RDMAE(x)    	(((x) & 0x1) << 5) 
#define UART_TDMAE(x)    	(((x) & 0x1) << 7) 

#define UART_DIV(x)    		(((x) & 0xf) << 5) 
#define UART_MUL(x)    		(((x) & 0xf) << 9)
#define UART_OVS(x)    		(((x) & 0x1) << 15) 

#define UART_RFRST(x)    	(((x) & 0x1) << 1) 
#define UART_TFRSRT(x)    	(((x) & 0x1) << 3) 
#define UART_DMAT(x)    	(((x) & 0x1) << 4) 
#define UART_RCVR(x)    	(((x) & 0x3) << 6)

#define UART_RXDATA(x)    (((x) & 0xffffffff) << 0)

#define UART_DLL(x)    (((x) & 0xf) << 0)
#define UART_DLM(x)    (((x) & 0xfff) << 4)

extern UART_HandleTypeDef huart0;
extern UART_HandleTypeDef huart1;

void Ro_Init_Uart(UART_HandleTypeDef *huart);
void uart0_putchar(uint8_t data);
void uart1_putchar(uint8_t data);
void Ro_Uart_Enable(UART_HandleTypeDef *huart,uint8_t enRx ,uint8_t enTx);
void Ro_Uart_Reset(UART_HandleTypeDef *huart);
void Ro_Uart_ResetFIFO(UART_HandleTypeDef *huart);
void Ro_Uart_RxDMA_Enable(UART_HandleTypeDef *huart,uint8_t bEnable);
void Ro_Uart_TxDMA_Enable(UART_HandleTypeDef *huart,uint8_t bEnable);

#endif
#endif