#ifndef _HAMSTER_IT_H_
#define _HAMSTER_IT_H_


#include "config.h"
#ifdef RO_IT_MODULE_ENABLED

/* Register offsets */

#define IT_FLAG				0x00
#define IT_MASK				0x04
#define IT_LEVER			0x08
#define IT_EVENT			0x0c			
#define IT_EXTIRQ_SEL		0x10
#define IT_SW_INT0			0x14
#define IT_PENDING			0x18
#define IT_FIQ				0x1c
#define IT_BASE_VECTOR		0x20
#define IT_RISING_TRIG		0x24
#define IT_FALLING_TRIG		0x28
#define IT_REQA0			0x30
#define IT_REQA1			0x34
#define IT_REQA2			0x38
#define IT_REQA3			0x3c
#define IT_REQA4			0x40
#define IT_REQA5			0x44
#define IT_REQA6			0x48
#define IT_REQA7			0x4c
#define IT_REQA8			0x50
#define IT_REQA9			0x54
#define IT_REQA10			0x58
#define IT_REQA11			0x5c
#define IT_REQA12			0x60
#define IT_REQA13			0x64
#define IT_REQA14			0x68
#define IT_REQA15			0x6c
#define IT_REQA16			0x70
#define IT_REQA17			0x74
#define IT_REQA18			0x78
#define IT_REQA19			0x7c
#define IT_REQA20			0x80
#define IT_REQA21			0x84
#define IT_REQA22			0x88
#define IT_REQA23			0x8c
#define IT_REQA24			0x90
#define IT_REQA25			0x94
#define IT_REQA26			0x98
#define IT_REQA27			0x9c
#define IT_REQA28			0xa0
#define IT_REQA29			0xa4
#define IT_REQA30			0xa8
#define IT_REQA31			0xac

/* Fields */

#define ACK(x)		(((x) & 0x1) << 0) 
#define IRQM(x)		(((x) & 0xffffffff) ) 
#define LM(x)		(((x) & 0xf) << 0) 
#define EVENTM(x)	(((x) & 0xffffffff)) 
#define EXTIC(x)	(((x) & 0xffff) << 0) 
#define SIR(x)		(((x) & 0xffffffff) ) 
#define PACK(x)		(((x) & 0x7fffff) ) 
#define SFIQ(x)		(((x) & 0x1) ) 
#define TB(x)		(((x) & 0xffffff)<< 6 ) 
#define RTSR(x)		(((x) & 0xfffff) ) //<<4 不需要，因为irq4-11已经做了这个动作
#define FTSR(x)		(((x) & 0xfffff) )  //<<4
#define EX(x)		(((x) & 0xf) ) 

#define IT_IRQ0			(0x0001<<0)  
#define IT_IRQ1			(0x0001<<1)  
#define IT_IRQ2			(0x0001<<2)  
#define IT_IRQ3			(0x0001<<3)  
#define IT_IRQ4			(0x0001<<4)  
#define IT_IRQ5			(0x0001<<5)  
#define IT_IRQ6			(0x0001<<6)  
#define IT_IRQ7			(0x0001<<7)  
#define IT_IRQ8			(0x0001<<8)  
#define IT_IRQ9			(0x0001<<9)  
#define IT_IRQ10		(0x0001<<10)  
#define IT_IRQ11		(0x0001<<11)  
#define IT_IRQ12		(0x0001<<12)  
#define IT_IRQ13		(0x0001<<13)  
#define IT_IRQ14		(0x0001<<14)  
#define IT_IRQ15		(0x0001<<15)  
#define IT_IRQ16		(0x0001<<16)  
#define IT_IRQ17		(0x0001<<17)  
#define IT_IRQ18		(0x0001<<18)  
#define IT_IRQ19		(0x0001<<19)  
#define IT_IRQ20		(0x0001<<20)  
#define IT_IRQ21		(0x0001<<21)  
#define IT_IRQ22		(0x0001<<22)  
#define IT_IRQ23		(0x0001<<23)  
#define IT_IRQ24		(0x0001<<24)  
#define IT_IRQ25		(0x0001<<25)  
#define IT_IRQ26		(0x0001<<26)  
#define IT_IRQ27		(0x0001<<27)  
#define IT_IRQ28		(0x0001<<28)  
#define IT_IRQ29		(0x0001<<29)  
#define IT_IRQ30		(0x0001<<30)  
#define IT_IRQ31		(0x0001<<31)


#define IT_GPIOA		0x00
#define IT_GPIOB		0x01
#define IT_GPIOC		0x02
#define IT_GPIOD		0x03

void Ro_IT_Init(void);
void Ro_IT_Enable_DMA_SPI(void);
void Ro_IT_Enable_ADP(void);
void Ro_IT_Enable_TM32(void);
void Ro_IT_Enable_TM16(void);
void Ro_Adptive_IRQHandle(void);
void Ro_IT_Disable_TM16(void);
void Ro_IT_Enable_RTOS(void);
void Ro_IT_Enable_DMA01_CH4(void);
void Ro_IT_Enable_WDG(void);
void Ro_IT_Enable_DMA01_CH5(void);
void Ro_IT_Disable_TM32(void);

#endif
#endif

