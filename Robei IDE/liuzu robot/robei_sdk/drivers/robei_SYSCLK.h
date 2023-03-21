#ifndef _HAMSTER_SYSCLK_H_
#define _HAMSTER_SYSCLK_H_

/* Register offsets */
#include "platform.h"
#include "config.h"


#define CLOCK_REMAP		(0x0000)

#define CLOCK_00		(0x0004)
#define CLOCK_01		(0x0008)
#define CLOCK_02		(0x0010)
#define CLOCK_05		(0x0014)
#define CLOCK_03		(0x0c20)
#define CLOCK_04		(0x0c30)
#define CLOCK_RST		(0x000c)

#define CLOCK_WWDG		(0x0c40)
#define CLOCK_TICK		(0x0c4c)
#define CLOCK_PAD		(0x0c00)


/* Fields */

//Reset 
#define CLOCK_VInith(x)   		(((x) & 0x1) << 5)
#define CLOCK_UART0_TRmp(x)   (((x) & 0x1) << 7)
#define CLOCK_UART0_RRmp(x)   (((x) & 0x1) << 8)



#define CLOCK_TIM_RST(x)   (((x) & 0x1) << 20)
#define CLOCK_SYSRST(x)   (((x) & 0x1) << 24)



#define CLOCK_RMP(x)   (((x) & 0x1) << 0)
#define CLOCK_REBASE(x)   (((x) & 0x7ff) << 11)
#define CLOCK_REBASE1(x)   (((x) & 0x1ff) << 13)

#define CLOCK_ADPEN(x)   (((x) & 0x1) << 14)
#define CLOCK_INTM_EN(x)   (((x) & 0x1) << 16)
//#define CLOCK_HDMIEN(x)   (((x) & 0x3) << 17)


#define CLOCK_DMAEN(x)   (((x) & 0x1) << 19)
#define CLOCK_DMA1EN(x)   (((x) & 0x1) << 20)
//================================
#define UART_RX_CLEAR(x)   (((x) & 0x1) << 1)
#define UART_TX_CLEAR(x)   (((x) & 0x1) << 3)

#define CLOCK_CAN_RST(x)   (((x) & 0x1) << 8)
#define CLOCK_I2C1_RST(x)   (((x) & 0x1) << 9)
#define CLOCK_I2C_RST(x)   (((x) & 0x1) << 10)
#define CLOCK_SPI1_RST(x)   (((x) & 0x1) << 11)
#define CLOCK_SPI0_RST(x)   (((x) & 0x1) << 12)
#define CLOCK_UART1_RST(x)   (((x) & 0x1) << 14)
#define CLOCK_UART0_RST(x)   (((x) & 0x1) << 15)
#define CLOCK_WWDG_RST(x)   (((x) & 0x1) << 16)

#define CLOCK_TM16_0_RST(x)   (((x) & 0x1) << 17)
#define CLOCK_TM16_1_RST(x)   (((x) & 0x1) << 18)
#define CLOCK_TM16_2_RST(x)   (((x) & 0x1) << 19)
#define CLOCK_TM16_3_RST(x)   (((x) & 0x1) << 20)
#define CLOCK_TM32_RST(x)   (((x) & 0x1) << 21)
#define CLOCK_ADP_RST(x)   (((x) & 0x1) << 22)
#define CLOCK_SW_RST(x)   (((x) & 0x1) << 14)


//================================
#define CLOCK_RMP1(x)   (((x) & 0x1) << 0)
#define CLOCK_RELOCK1(x)   (((x) & 0x1) << 1)

#define CLOCK_HCLKSEL(x)   (((x) & 0xf) << 3)
#define CLOCK_HCLK1SEL(x)   (((x) & 0xf) << 7)
#define CLOCK_HDMISEL2(x)   (((x) & 0xf) << 11)

#define CLOCK_PCLKSEL(x)   (((x) & 0xf) << 15)
#define CLOCK_SSPCLK(x)   (((x) & 0xf) << 23)
#define CLOCK_TICKPRESCALER(x)   (((x) & 0xf) << 27)
#define CLOCK_SYSTICK(x)   (((x) & 0xffffff) << 0)

#define CLOCK_TIM0(x)   (((x) & 0xf) << 0)
#define CLOCK_TM16(x)   (((x) & 0xf) << 4)
#define CLOCK_UART(x)   (((x) & 0xf) << 8)
#define CLOCK_UART1(x)   (((x) & 0xf) << 12)
#define CLOCK_I2C(x)   (((x) & 0xf) << 24)
#define CLOCK_WDG(x)   (((x) & 0xf) << 0)
#define CLOCK_LCD(x)   (((x) & 0xf) << 4)

#define CLOCK_PAD_PREV(x)   (((x) & 0x2f) << 9)
//20210219 fangxu added for CLOCK_EN start +++
//#define CLOCK_WWDG		(0x0c40)

#define CLOCK_TMEN(x)   (((x) & 0x1) << 24)
#define CLOCK_GPEN(x)   (((x) & 0x1) << 26)
#define CLOCK_UARTEN(x)   (((x) & 0x1) << 27)
#define CLOCK_SPIEN(x)   (((x) & 0x1) << 28)
#define CLOCK_I2CEN(x)   (((x) & 0x1) << 30)
#define CLOCK_CANEN(x)   (((x) & 0x1) << 31)

//20210219 fangxu added for CLOCK_EN end   ---


//==============================================================
/*


#define  HCLKD1        4'd0 // hclk=sysclk
#define  HCLKD2        4'd1 // hclk=sysclk/2
#define  HCLKD3        4'd2 // hclk=sysclk/3
#define  HCLKD4        4'd3 // hclk=sysclk/4
#define  HCLKD5        4'd4 // hclk=sysclk/5
#define  HCLKD6        4'd5 // hclk=sysclk/6
#define  HCLKD8        4'd6 // hclk=sysclk/8
#define  HCLKD10       4'd7 // hclk=sysclk/10
#define  HCLKD12       4'd8 // hclk=sysclk/12
#define  HCLKD16       4'd9 // hclk=sysclk/16
#define  HCLKD32       4'd10 // hclk=sysclk/32
#define  HCLKD64       4'd11 // hclk=sysclk/64
#define  HCLKD128      4'd12 // hclk=sysclk/128
#define  HCLKD256      4'd13 // hclk=sysclk/256
#define  HCLKD512      4'd14 // hclk=sysclk/512

#define  PCLKD1        4'd0 // pclk=hclk/2
#define  PCLKD2        4'd1 // pclk=hclk/2
#define  PCLKD3        4'd2 // pclk=hclk/3
#define  PCLKD4        4'd3 // pclk=hclk/4
#define  PCLKD5        4'd4 // pclk=hclk/5
#define  PCLKD6        4'd5 // pclk=hclk/6
#define  PCLKD8        4'd6 // pclk=hclk/8
#define  PCLKD10       4'd7 // pclk=hclk/10
#define  PCLKD12       4'd8 // pclk=hclk/12
#define  PCLKD16       4'd9 // pclk=hclk/16
*/
//==============================================================

void Ro_Init_IIC_CLK(uint8_t u8IICCLK);
void Ro_Init_SPI_CLK(uint8_t u8SPICLK);
void Ro_Init_WWG_CLK(uint8_t u8WWDGCLK);
void Ro_Init_SysCLK(uint32_t hclksel,uint32_t hclksel1,uint32_t pclksel);
void Ro_Adaptive_Enable(uint8_t isenable);


#endif

