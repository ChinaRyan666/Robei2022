#ifndef _HAMSTER_TIM16_H_
#define _HAMSTER_TIM16_H_


#include "config.h"
#ifdef RO_TIM16_MODULE_ENABLED
/* Register offsets */
#define TM16_TCON			(0x0000)
#define TM16_TCON_EVENT		(0x0004)
#define TM16_TM0			(0x0008)
#define TM16_TM_CATCH0		(0x000c)
#define TM16_TM_CATCH1		(0x0010)
#define TM16_TM_CATCH2		(0x0014)
#define TM16_PRESCALER		(0x0018)
#define TM16_TCON_SLAVE		(0x001c)
#define TM16_IT_STATUS		(0x0020)
#define TM16_IT_CLEAR		(0x0024)
#define TM16_DEADTIME		(0x0028)

#define TM16_IT_RELOAD		(0x002c)
#define TM16_IT_REPETITION	(0x0030)
#define TM16_TCON0			(0x0034)
#define TM16_TCON1			(0x0038)
#define TM16_TCON2			(0x003c)
#define TM16_TCON3			(0x0040)
#define TM16_TCON_OPTION0	(0x0044)
#define TM16_TCON_OPTION1	(0x0048)
#define TM16_TCON_OPTION2	(0x004c)
#define TM16_TM_CATCH3		(0x0050)

/* Fields */
#define TM16_CEN(x)			(((x) & 0x1) << 0) 
#define TM16_UDIS(x)		(((x) & 0x1) << 1) 
#define TM16_URS(x)			(((x) & 0x1) << 2)  
#define TM16_OPM(x)			(((x) & 0x1) << 3)  
#define TM16_DIR(x)			(((x) & 0x1) << 4)  
#define TM16_CMS(x)			(((x) & 0x3) << 5)  

#define TM16_TMMS(x)		(((x) & 0x7) << 0)  
#define TM16_STOP0EN(x)		(((x) & 0x1) << 3)  
#define TM16_STOP1EN(x)		(((x) & 0x1) << 4)  
#define TM16_STOP2EN(x)		(((x) & 0x1) << 5)  
#define TM16_STOP3EN(x)		(((x) & 0x1) << 6)  
#define TM16_UG(x)    		(((x) & 0x1) << 7)  
#define TM16_RST0EN(x)		(((x) & 0x1) << 9) 
#define TM16_RST1EN(x)		(((x) & 0x1) << 11)  
#define TM16_RST2EN(x)		(((x) & 0x1) << 13)   
#define TM16_RST3EN(x)		(((x) & 0x1) << 15)  

#define TM16_COUNTER(x)		(((x) & 0xffff) << 0)  

#define TM16_EDATA(x)		(((x) & 0xffff) << 0)  
#define TM16_EDATA1(x)		(((x) & 0xffff) << 0)  
#define TM16_EDATA2(x)		(((x) & 0xffff) << 0)  
#define TM16_PDATA(x)		(((x) & 0xffff) << 0)  

#define TM16_OIS0(x)		(((x) & 0x1) << 0)  
#define TM16_nOIS0(x)		(((x) & 0x1) << 1)  
#define TM16_OIS1(x)		(((x) & 0x1) << 2)  
#define TM16_nOIS1(x)		(((x) & 0x1) << 3)  
#define TM16_OIS2(x)		(((x) & 0x1) << 4)  
#define TM16_nOIS2(x)		(((x) & 0x1) << 5)  
#define TM16_OIS3(x)		(((x) & 0x1) << 6)  
#define TM16_nOIS3(x)		(((x) & 0x1) << 7)  

#define TM16_TS(x)    (((x) & 0x1) << 8)  
#define TM16_ETPS(x)    (((x) & 0x3) << 12)  
#define TM16_ECE(x)    (((x) & 0x1) << 14)  
#define TM16_CAP(x)    (((x) & 0x1) << 15)  

#define TM16_IRQU(x)    (((x) & 0x1) << 0)  
#define TM16_IRQ0(x)    (((x) & 0x1) << 1)  
#define TM16_IRQ1(x)    (((x) & 0x1) << 2)  
#define TM16_IRQ2(x)    (((x) & 0x1) << 3)  
#define TM16_IRQT(x)    (((x) & 0x1) << 6)  
#define TM16_IRQB(x)    (((x) & 0x1) << 7)  

#define TM16_LDATA(x)    (((x) & 0xffff) << 0)  
#define TM16_DDATA(x)    (((x) & 0xff) << 0)
#define TM16_BRKOSSI(x)    (((x) & 0x1) << 10)  
#define TM16_BRKEN(x)    (((x) & 0x1) << 12)  
#define TM16_BRKMODE(x)    (((x) & 0x1) << 13)  

#define TM16_ITUEN(x)    (((x) & 0x1) << 0)  
#define TM16_IT0EN(x)    (((x) & 0x1) << 1)  
#define TM16_IT1EN(x)    (((x) & 0x1) << 2)  
#define TM16_IT2EN(x)    (((x) & 0x1) << 3)  
#define TM16_ITTEN(x)    (((x) & 0x1) << 6)  
 
#define TM16_PWM0EN(x)    (((x) & 0x1) << 0)  
#define TM16_PWM1EN(x)    (((x) & 0x1) << 4) 
#define TM16_PWM2EN(x)    (((x) & 0x1) << 8)   
#define TM16_PWM3EN(x)    (((x) & 0x1) << 12)   
/** @defgroup TIM_Output_Compare_and_PWM_modes TIM Output Compare and PWM Modes
  * @{
  */
#define TIM_MODE_PWM                     0x00000000U                     /*!< PWM mode 1                             */
#define TIM_MODE_TIMING                  0x00000001U                                              /*!< Frozen                                 */
#define TIM_MODE_CAPTURE                 0x00000002U                                         /*!< Set channel to active level on match   */
/**
  * @}
  */

/**
  * @brief TIM Timers
  */




typedef struct
{
  __IO uint32_t CR1;       /*!< TIM control register 1,               Address offset: 0x00 */
  __IO uint32_t EGR;       /*!< TIM event generation register,        Address offset: 0x04 */
  __IO uint32_t CNT;       /*!< TIM counter register,                 Address offset: 0x08 */
  __IO uint32_t CCR0;      /*!< TIM capture/compare register 0,       Address offset: 0x0c */
  __IO uint32_t CCR1;      /*!< TIM capture/compare register 1,       Address offset: 0x10 */

  __IO uint32_t CCR2;      /*!< TIM capture/compare register 2,       Address offset: 0x14 */
  __IO uint32_t PSC;       /*!< TIM prescaler register,               Address offset: 0x18 */
  __IO uint32_t SMCR;      /*!< TIM slave Mode Control register,      Address offset: 0x1c */
  __IO uint32_t SR;        /*!< TIM status register,                  Address offset: 0x20 */
  __IO uint32_t CSR;       /*!< TIM control register 2,               Address offset: 0x24 */

  __IO uint32_t BDTR;      /*!< TIM break and dead-time register,     Address offset: 0x28 */
  __IO uint32_t ARR;       /*!< TIM auto-reload register,             Address offset: 0x2C */
  __IO uint32_t RCR;       /*!< TIM  repetition counter register,     Address offset: 0x30 */
  __IO uint32_t CCMR1;     /*!< TIM  capture/compare mode register 1, Address offset: 0x34 */
  __IO uint32_t CCMR2;     /*!< TIM  capture/compare mode register 2, Address offset: 0x38 */

  __IO uint32_t CCMR3;     /*!< TIM  capture/compare mode register 3, Address offset: 0x3c */
  __IO uint32_t CCMR4;     /*!< TIM  capture/compare mode register 4, Address offset: 0x40 */
  __IO uint32_t OR0;       /*!< TIM option register 0,                Address offset: 0x44 */
  __IO uint32_t OR1;       /*!< TIM option register 0,                Address offset: 0x48 */
  __IO uint32_t OR2;       /*!< TIM option register 0,                Address offset: 0x4c */

  __IO uint32_t CCR3;            /*!< TIM capture/compare register 3,       Address offset: 0x50 */
}TIM_TypeDef;

#define TIM1                ((TIM_TypeDef *)TIM1_BASE_ADDR)
#define TIM2                ((TIM_TypeDef *)TIM2_BASE_ADDR)
#define TIM3                ((TIM_TypeDef *)TIM3_BASE_ADDR)
#define TIM4                ((TIM_TypeDef *)TIM4_BASE_ADDR)
/**
  * @brief  TIM Time base Configuration Structure definition
  */
typedef struct
{
  uint32_t Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock.
                                   This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */

  uint32_t CounterMode;       /*!< Specifies the counter mode.
                                   This parameter can be a value of @ref TIM_Counter_Mode */

  uint32_t Period;            /*!< Specifies the period value to be loaded into the active
                                   Auto-Reload Register at the next update event.
                                   This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF.  */

  uint32_t ClockDivision;     /*!< Specifies the clock division.
                                   This parameter can be a value of @ref TIM_ClockDivision */

  uint32_t RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                    reaches zero, an update event is generated and counting restarts
                                    from the RCR value (N).
                                    This means in PWM mode that (N+1) corresponds to:
                                        - the number of PWM periods in edge-aligned mode
                                        - the number of half PWM period in center-aligned mode
                                     GP timers: this parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF.
                                     Advanced timers: this parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */

  uint32_t AutoReloadPreload;  /*!< Specifies the auto-reload preload.
                                   This parameter can be a value of @ref TIM_AutoReloadPreload */
} TIM_Base_InitTypeDef;

typedef struct __TIM_HandleTypeDef
{
  TIM_TypeDef                        *Instance;         /*!< Register base address                             */
  TIM_Base_InitTypeDef               Init;              /*!< TIM Time Base required parameters                 */
} TIM_HandleTypeDef;


void Ro_Init_TM16_CLK(uint8_t u8TIM16CLK);
void Ro_TIM_Init(TIM_HandleTypeDef *htim);
void Ro_TIM_Mode(TIM_HandleTypeDef *htim,uint8_t u8TMMode);
void Ro_TIM_Enable(TIM_HandleTypeDef *htim);
void Ro_TIM_Disable(TIM_HandleTypeDef *htim);
void Ro_TIM_ClearIT(TIM_HandleTypeDef *htim);
void Ro_TIM_BreakEnable(TIM_HandleTypeDef *htim,uint8_t enable);
void Ro_TIM_ConfigPWMSettable(TIM_HandleTypeDef *htim,uint8_t pwm_n, uint8_t status);
void Ro_TIM_ConfigBreakDeadTime(TIM_HandleTypeDef *htim,uint8_t DeadTime);
void Ro_TIM_ConfigClockDivision(TIM_HandleTypeDef *htim,uint8_t div);
void Ro_TIM_ConfigPrescaler(TIM_HandleTypeDef *htim,uint16_t psc);
void Ro_TIM_ConfigPeriod(TIM_HandleTypeDef *htim,uint32_t cnt);
void Ro_TIM_RepetitionCounter(TIM_HandleTypeDef *htim,int pwm_n, uint32_t acc);
void Ro_TIM_ConfigDutyRatio(TIM_HandleTypeDef *htim,int pwm_n, uint32_t dr);
#endif
#endif

