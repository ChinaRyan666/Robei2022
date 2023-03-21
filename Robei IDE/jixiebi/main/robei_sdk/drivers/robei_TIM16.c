 /**
 * @file    hamster_TIM16.c
 * @brief	16bit timer接口
 *
 * \n
 * @details 
 *
 * \n
 * @version 
 * @author  vinolee
 * @date    2020-7-3
 *
 * @history
 *
 */

#include "robei_TIM16.h"
#include "robei_SYSCLK.h"
#include "robei_IT.h"
#ifdef RO_TIM16_MODULE_ENABLED
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

/**
 * @brief 配置 timer16 时钟
 * @param u8TIM16CLK: 时钟配置参数
 *
 *
 * @retval None
 */
void Ro_Init_TM16_CLK(uint8_t u8TIM16CLK)
{
	MODIFY_REG(POWER_CLK_REG(CLOCK_WWDG),CLOCK_TMEN(0x1),CLOCK_TMEN(1));
	WRITE_REG(POWER_CLK_REG(CLOCK_RST),CLOCK_TIM_RST(0x1));	
	MODIFY_REG(POWER_CLK_REG(CLOCK_04),CLOCK_TM16(0xf),CLOCK_TM16(u8TIM16CLK));
}

/**
 * @brief 初始化 timer16
 *
 * @retval None
 */
 #if 0
 htim1.Instance=TIM1;
 htim1_Instance TIM2;
 htim1_Instance TIM3;
 htim1_Instance TIM4;
 #endif
void Ro_TIM_Init(TIM_HandleTypeDef *htim)
{
    //WRITE_REG(POWER_CLK_REG(0x0c),0x100000);
	// 初始化时钟
	Ro_Init_TM16_CLK(0);
	MODIFY_REG(POWER_CLK_REG(CLOCK_WWDG),CLOCK_GPEN(0x1),CLOCK_GPEN(1));

if(htim->Instance==TIM1)
{
    GPIOB->GPIO_A=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
	GPIOB->GPIO_F=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIOB->GPIO_OE=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
}
else if(htim->Instance==TIM2)
{
	// 配置复用的 GPIO 端口
	GPIOF->GPIO_A=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_7;
	GPIOF->GPIO_F=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_7;
	GPIOF->GPIO_OE=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_7;
	
    GPIOH->GPIO_A=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
	GPIOH->GPIO_F=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
	GPIOH->GPIO_OE=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;

}
else if(htim->Instance==TIM3)
{
	// 配置复用的 GPIO 端口
    GPIOH->GPIO_A=GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIOH->GPIO_F=GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIOH->GPIO_OE=GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    
	GPIOI->GPIO_A=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
	GPIOI->GPIO_F=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
	GPIOI->GPIO_OE=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
}
else if(htim->Instance==TIM4)
{
	// 配置复用的 GPIO 端口
    GPIOI->GPIO_A=GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIOI->GPIO_F=GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIOI->GPIO_OE=GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    
	GPIOJ->GPIO_A=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
	GPIOJ->GPIO_F=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
	GPIOJ->GPIO_OE=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
}
else return ;
	
	// 初始化分频器， cntr_clk = TIM16_CLK/(TM_PData+1)
	// 配置 timer16 计数器的默认初始值、结束值。
	WRITE_REG(htim->Instance->PSC,TM16_PDATA(0x0f));
	WRITE_REG(htim->Instance->CNT,TM16_COUNTER(0));
	WRITE_REG(htim->Instance->ARR,TM16_LDATA(0x0f));
	WRITE_REG(htim->Instance->BDTR,TM16_BRKOSSI(0)|TM16_BRKEN(0)|TM16_DDATA(0x0));
}

/**
 * @brief 配置 timer16的工作状态为计时器或pwm
 * @param u8TMMode: @arg TIM_MODE_PWM:PWM 
 * @arg TIM_MODE_TIMING:timer
 * @arg TIM_MODE_CAPTURE:capture
 *
 * @retval None
 */

void Ro_TIM_Mode(TIM_HandleTypeDef *htim,uint8_t u8TMMode)
{
 if(u8TMMode==TIM_MODE_TIMING)
 {
  WRITE_REG(htim->Instance->CCMR2,TM16_ITUEN(1));
  Ro_IT_Enable_TM16();// 使能 timer16 的中断
 }
 else
 {
  WRITE_REG(htim->Instance->CCMR2,TM16_ITUEN(0));
  Ro_IT_Disable_TM16();// 使 timer16 的中断
 }
 WRITE_REG(htim->Instance->CR1,TM16_CMS(0)|TM16_DIR(0)|TM16_OPM(0)|TM16_URS(0)|TM16_UDIS(0)|TM16_CEN(0));  //count_clk=TM16/(TM_PData+1)
}

/**
 * @brief 使能 timer16
 *
 * @retval None
 */
void Ro_TIM_Enable(TIM_HandleTypeDef *htim)
{
	//MODIFY_REG(htim->Instance->CCMR2,0, ITUEN(1));		
    MODIFY_REG(htim->Instance->CR1,TM16_CEN(1), TM16_CEN(1));	
}
/**
 * @brief 使能 timer16 capture
 *
 * @retval None
 */
void Ro_TIM_CaptureTest(TIM_HandleTypeDef *htim)
{
	//MODIFY_REG(htim->Instance->CCMR2,0, ITUEN(1));	
	
    MODIFY_REG(htim->Instance->SMCR,TM16_CAP(1)|TM16_TS(1)|TM16_ETPS(3)|TM16_ECE(1), TM16_CAP(1)|TM16_TS(1)|TM16_ETPS(0)|TM16_ECE(1));	
}


/**
 * @brief 关闭 timer16
 *
 * @retval None
 */
void Ro_TIM_Disable(TIM_HandleTypeDef *htim)
{
	MODIFY_REG(htim->Instance->CR1,TM16_CEN(1), TM16_CEN(0));	
    //WRITE_REG(htim->Instance->CCMR4,TM16_TM16_PWM0EN(1)|TM16_TM16_PWM1EN(1)|TM16_PWM2EN(1));
}

/**
 * @brief 清除 timer16中 timer1 中断
 *
 * @retval None
 */
void Ro_TIM_ClearIT(TIM_HandleTypeDef *htim)
{
	WRITE_REG(htim->Instance->CSR,TM16_IRQB(1)|TM16_IRQU(1)) ;
}
/**
 * @brief 使能timer的刹车功能
 *
 * @retval None
 */
void Ro_TIM_BreakEnable(TIM_HandleTypeDef *htim,uint8_t enable)
{
	if(enable)
	{
		SET_BIT(htim->Instance->BDTR,TM16_BRKOSSI(1)|TM16_BRKEN(1));
		
		WRITE_REG(htim->Instance->SMCR,TM16_OIS0(1)|TM16_nOIS0(1)|TM16_OIS1(1)|TM16_nOIS1(1)|TM16_OIS2(1)|TM16_nOIS2(1)\
					|TM16_OIS3(1)|TM16_nOIS3(1));	//DeadTime
	}
	else
		CLEAR_BIT(htim->Instance->BDTR,TM16_BRKOSSI(1)|TM16_BRKEN(1));
}

/**
 * @brief 使能或禁用 timer16 的某通道的pwm
 * @param pwm_n: 要配置的pwm通道序号
 * @param status: 要把pwm通道配置为状态，0 禁用，非0 使能
 * 
 * @retval None
 */
void Ro_TIM_ConfigPWMSettable(TIM_HandleTypeDef *htim,uint8_t pwm_n, uint8_t status)
{
	uint8_t status_b = status == 0?0:1;

	switch(pwm_n){
	case 0:	
		MODIFY_REG(htim->Instance->CCMR4, TM16_PWM0EN(1)*(!status_b), TM16_PWM0EN(1)*status_b);
		break;
	case 1:
		MODIFY_REG(htim->Instance->CCMR4, TM16_PWM1EN(1)*(!status_b), TM16_PWM1EN(1)*status_b);
		break;
	case 2:
		MODIFY_REG(htim->Instance->CCMR4, TM16_PWM2EN(1)*(!status_b), TM16_PWM2EN(1)*status_b);
		break;
	case 3:
		MODIFY_REG(htim->Instance->CCMR4, TM16_PWM3EN(1)*(!status_b), TM16_PWM3EN(1)*status_b);
		break;
	default:
		break;
	}
	WRITE_REG(htim->Instance->CR1,TM16_CMS(1)|TM16_DIR(0)|TM16_OPM(0)|TM16_URS(0)|TM16_UDIS(0)|TM16_CEN(1));
}
/** 
 * @brief 配置死区时间
 * @param DeadTime: 时间范围 0x00-0xff
 *
 *
 * @retval None
 */
 
void Ro_TIM_ConfigBreakDeadTime(TIM_HandleTypeDef *htim,uint8_t DeadTime)
{
	MODIFY_REG(htim->Instance->BDTR,TM16_DDATA(0xff),TM16_DDATA(DeadTime));	//DeadTime
}

/** 
 * @brief 配置 timer16 时钟 (todo)
 * @param div: 时钟配置参数
 *
 *
 * @retval None
 */
void Ro_TIM_ConfigClockDivision(TIM_HandleTypeDef *htim,uint8_t div)
{
	Ro_Init_TM16_CLK(div);
}

/** 
 * @brief 配置 timer16 的分频系数
 * @param psc: 分频系数的值
 *
 * @retval None
 */
void Ro_TIM_ConfigPrescaler(TIM_HandleTypeDef *htim,uint16_t psc)
{
	WRITE_REG(htim->Instance->PSC,TM16_PDATA(psc));
}

/** 
 * @brief 配置 timer16 的计数器初始值和结束值 (todo)  cnt 为总的计数个数
 * @param cnt: 分频系数的值
 *
 * @retval None
 */
void Ro_TIM_ConfigPeriod(TIM_HandleTypeDef *htim,uint32_t cnt)
{
	WRITE_REG(htim->Instance->CNT,TM16_COUNTER(0));
	WRITE_REG(htim->Instance->ARR,TM16_LDATA(cnt));
}

/** 
 * @brief 配置 timer16 的分频系数
 * @param pwm_n: 要配置的pwm通道序号
 * @param acc: 调节占空比的值 ,从初始值到acc 为高电平
 *
 * @retval None
 */
void Ro_TIM_RepetitionCounter(TIM_HandleTypeDef *htim,int pwm_n, uint32_t acc)
{
	switch(pwm_n) {
	case 0:	
		WRITE_REG(htim->Instance->CCR0,TM16_LDATA(acc));
		break;
	case 1:
		WRITE_REG(htim->Instance->CCR1,TM16_LDATA(acc));
		break;
	case 2:
		WRITE_REG(htim->Instance->CCR2,TM16_LDATA(acc));
		break;
	case 3:
		WRITE_REG(htim->Instance->CCR3,TM16_LDATA(acc));
		break;
	default:
		break;
	}
	WRITE_REG(htim->Instance->CR1,TM16_CMS(1)|TM16_DIR(0)|TM16_OPM(0)|TM16_URS(0)|TM16_UDIS(0)|TM16_CEN(1));
	//WRITE_REG(htim->Instance->CR1,CMS(1)|DIR(0)|OPM(0)|URS(0)|UDIS(0)|TR(1));
}


/** 
 * @brief 配置 timer16 pwm模式时某通道的占空比
 * @param pwm_n: 要配置的pwm通道序号 pwm_n = 0 1 2
 * @param dr: 要配置成的pwm 占空比，例如，要配置成80%，则dr为80.
 *
 * @retval None
 */
void Ro_TIM_ConfigDutyRatio(TIM_HandleTypeDef *htim,int pwm_n, uint32_t dr)
{
	uint32_t val;
	val = READ_REG(htim->Instance->ARR);
	val = val * dr/100;
	Ro_TIM_RepetitionCounter(htim,pwm_n, val);
}

#endif
