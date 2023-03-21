#ifndef _HAMSTER_TIM32_H_
#define _HAMSTER_TIM32_H_
#include "config.h"
#ifdef RO_TIM32_MODULE_ENABLED
/* Register offsets */
#define TIM0_TCON			(0x0000)
#define TIM0_TCON_EVENT		(0x0004)
#define TIM0_TM0			(0x0008)
#define TIM0_CM0			(0x000c)
#define TIM0_CM1			(0x0010)
#define TIM0_CM2			(0x0014)
#define TIM0_PRESCALER		(0x0018)
#define TIM0_TCON_SLAVE		(0x001c)
#define TIM0_IT_STATUS		(0x0020)

#define TIM0_IT_CLEAR		(0x0024)
#define TIM0_DEADTIME		(0x0028)

#define TIM0_IT_RELOAD		(0x002c)

#define TIM0_TCON0			(0x0034)
#define TIM0_TCON1			(0x0038)
#define TIM0_TCON2			(0x003c)
#define TIM0_TCON3			(0x0040)
#define TIM0_TCON_OPTION0	(0x0048)
#define TIM0_TCON_OPTION1	(0x004c)
#define TIM0_CM3			(0x0050)


/* Fields */
#define TR(x)			(((x) & 0x1) << 0) 
#define UDIS(x)		(((x) & 0x1) << 1) 
#define URS(x)			(((x) & 0x1) << 2)  
#define OPM(x)			(((x) & 0x1) << 3)  
#define DIR(x)			(((x) & 0x1) << 4)  
#define CMS(x)			(((x) & 0x3) << 5)  
#define CKD(x)			(((x) & 0x3) << 8)  

#define TMMS(x)		(((x) & 0x7) << 0)  
#define TI1S(x)		(((x) & 0x1) << 7)

#define STOP0EN(x)		(((x) & 0x1) << 8)  
#define STOP1EN(x)		(((x) & 0x1) << 9)  
#define STOP2EN(x)		(((x) & 0x1) << 10)  
#define STOP3EN(x)		(((x) & 0x1) << 11) 

#define RST0EN(x)		(((x) & 0x1) << 12)  
#define RST1EN(x)		(((x) & 0x1) << 13)  
#define RST2EN(x)		(((x) & 0x1) << 14)  
#define RST3EN(x)		(((x) & 0x1) << 15)  

#define TIM32COUNT(x)		(((x) & 0xffffffff) << 0)  
#define EDATA(x)		(((x) & 0xffffffff) << 0)  
#define EDATA1(x)		(((x) & 0xffffffff) << 0)  
#define EDATA2(x)		(((x) & 0xffffffff) << 0)  
#define EDATA3(x)		(((x) & 0xffffffff) << 0)  

#define PDATA(x)		(((x) & 0xffff) << 0)  

#define TS(x)			(((x) & 0x1) << 6)  
#define ETPS(x)		(((x) & 0x3) << 12)  
#define ECE(x)			(((x) & 0x1) << 14)  
#define CAPEN(x)		(((x) & 0x1) << 15)

#define IRQU(x)		(((x) & 0x1) << 0)  
#define IRQ0(x)		(((x) & 0x1) << 1)  
#define IRQ1(x)		(((x) & 0x1) << 2)  
#define IRQ2(x)		(((x) & 0x1) << 3)  
#define IRQ3(x)		(((x) & 0x1) << 4) 

#define IRQT(x)		(((x) & 0x1) << 6)

#define BREQU(x)		(((x) & 0x1) << 8)  
#define BREQ0(x)		(((x) & 0x1) << 9)  
#define BREQ1(x)		(((x) & 0x1) << 10)  
#define BREQ2(x)		(((x) & 0x1) << 11)  
#define BREQ3(x)		(((x) & 0x1) << 12)  
#define BREQT(x)		(((x) & 0x1) << 14)

#define LDATA(x)		(((x) & 0xffffffff) << 0)  
 
#define DDATA(x)    (((x) & 0xff) << 0)  

#define CC0S(x)		(((x) & 0x3) << 0)  
#define CC0M(x)		(((x) & 0x7) << 2)  
#define CC1S(x)		(((x) & 0x3) << 8)  
#define CC1M(x)		(((x) & 0x7) << 10)  
#define CC2S(x)		(((x) & 0x3) << 0)  
#define CC2M(x)		(((x) & 0x7) << 2)  
#define CC3S(x)		(((x) & 0x3) << 8)  
#define CC3M(x)		(((x) & 0x7) << 10)  

 
#define PWM0EN(x)		(((x) & 0x1) << 0)  
#define CAP0EN0(x)		(((x) & 0x1) << 1)  
#define CAP0EN1(x)		(((x) & 0x1) << 3)  
#define PWM1EN(x)		(((x) & 0x1) << 4)  
#define CAP1EN0(x)		(((x) & 0x1) << 5)  
#define CAP1EN1(x)		(((x) & 0x1) << 7)  
#define PWM2EN(x)		(((x) & 0x1) << 8)  
#define CAP2EN0(x)		(((x) & 0x1) << 9)  
#define CAP2EN1(x)		(((x) & 0x1) << 11) 
#define PWM3EN(x)		(((x) & 0x1) << 12)  
#define CAP3EN0(x)		(((x) & 0x1) << 13)  
#define CAP3EN1(x)		(((x) & 0x1) << 15)  


#define ITUEN(x)		(((x) & 0x1) << 0)  
#define IT0EN(x)		(((x) & 0x1) << 1)  
#define IT1EN(x)		(((x) & 0x1) << 2)  
#define IT2EN(x)		(((x) & 0x1) << 3)
#define IT3EN(x)		(((x) & 0x1) << 4)
#define ITTEN(x)		(((x) & 0x1) << 6)
#define ITBEN(x)		(((x) & 0x1) << 7)  
#define DMAUEN(x)		(((x) & 0x1) << 8)  
#define DMA0EN(x)		(((x) & 0x1) << 9)  
#define DMA1EN(x)		(((x) & 0x1) << 10)  
#define DMA2EN(x)		(((x) & 0x1) << 11)  
#define DMA3EN(x)		(((x) & 0x1) << 12) 


#define DCR(x)    (((x) & 0x1fff) << 0)  
#define DMAR(x)    (((x) & 0xffff) << 0) 

void Ro_Init_TIM0_CLK(uint8_t u8TIM16CLK);
void Ro_TIM0_Init(void);
void Ro_TIM0_Mode(uint8_t u8TMMode);
void Ro_TIM0_Enable(void);
void Ro_TIM0_Disable(void);
void Ro_TIM0_Clear_IT(void);

void Ro_TIM0_ConfigPWMSettable(uint8_t pwm_n, uint8_t status);
void Ro_TIM0_ConfigBreakDeadTime(uint8_t DeadTime);

void Ro_TIM0_ConfigClockDivision(uint8_t div);
void Ro_TIM0_ConfigPrescaler(uint16_t psc);
void Ro_TIM0_ConfigPeriod(uint32_t cnt);
void Ro_TIM0_RepetitionCounter(int pwm_n, uint32_t acc);
void Ro_TIM0_ConfigDutyRatio(int pwm_n, uint32_t dr);
void Ro_TIM0_ClearIT(void);


#endif
#endif
