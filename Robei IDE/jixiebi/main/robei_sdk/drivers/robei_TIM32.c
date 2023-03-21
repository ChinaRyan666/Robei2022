/**
 * @file    Ro_TIM32.c
 * @brief	32bit timer接口
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
#include "config.h"

#ifdef RO_TIM32_MODULE_ENABLED
#include "robei_SYSCLK.h"
#include "robei_TIM32.h"
/**
 * @brief 配置 timer32 时钟
 * @param u8TIM16CLK: 时钟配置参数
 *
 *
 * @retval None
 */
void Ro_Init_TIM0_CLK(uint8_t TIM0CLK)
{
	//IIC CLK[27:24]
	MODIFY_REG(POWER_CLK_REG(CLOCK_04),CLOCK_TIM0(0xf),CLOCK_TIM0(TIM0CLK));
	MODIFY_REG(POWER_CLK_REG(CLOCK_WWDG),CLOCK_TMEN(0x1),CLOCK_TMEN(1));
}

/**
 * @brief 初始化 timer32
 *
 * @retval None
 */
void Ro_TIM0_Init(void)
{
	MODIFY_REG(POWER_CLK_REG(CLOCK_WWDG),CLOCK_GPEN(0x1),CLOCK_GPEN(1));
    GPIOD->GPIO_A=GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_6;
	GPIOD->GPIO_F=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIOD->GPIO_OE=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;

	//初始化clock
	Ro_Init_TIM0_CLK(0);    //TIM0clk = sysclk *a;
	
	//初始化Prescaler
	WRITE_REG(PWM0_REG(TIM0_PRESCALER),PDATA(0xff));		//count_clk=TIM0_clk/(TM_PData+1)
	WRITE_REG(PWM0_REG(TIM0_TM0),TIM32COUNT(0));				//初始值
	WRITE_REG(PWM0_REG(TIM0_IT_RELOAD),LDATA(0xffff));	//结束值
    WRITE_REG(PWM0_REG(TIM0_DEADTIME),DDATA(0x0));
}

/**
 * @brief 配置 timer32的工作状态为计时器或pwm
 * @param u8TMMode: 0:PWM 1:timer
 *
 * @retval None
 */
void Ro_TIM0_Mode(uint8_t u8TMMode)
{
	if(u8TMMode)
	{
		WRITE_REG(PWM0_REG(TIM0_TCON2),ITUEN(1));//使能
		Ro_IT_Enable_TM32();
	}
	
	WRITE_REG(PWM0_REG(TIM0_TCON),CMS(1)|DIR(0)|OPM(0)|URS(0)|UDIS(0)|TR(1));		//count_clk=TM16/(TM_PData+1)
}

/**
 * @brief 使能 timer32
 *
 * @retval None
 */
void Ro_TIM0_Enable(void)
{
	MODIFY_REG(PWM0_REG(TIM0_TCON2),ITUEN(1),ITUEN(1) );		//count_clk=TM16/(TM_PData+1)
}

/**
 * @brief 关闭 timer32
 *
 * @retval None
 */
void Ro_TIM0_Disable(void)
{
	MODIFY_REG(PWM0_REG(TIM0_TCON2),ITUEN(1),ITUEN(0));		//count_clk=TM16/(TM_PData+1)
}

/**
 * @brief 清除 timer32 中断
 *
 * @retval None
 */
void Ro_TIM0_ClearIT(void)
{
	SET_BIT(PWM0_REG(TIM0_IT_CLEAR),IRQU(0)) ;
}

/**
 * @brief 使能或禁用 timer32 的某通道的pwm
 * @param pwm_n: 要配置的pwm通道序号
 * @param status: 要把pwm通道配置为状态，0 禁用，非0 使能
 * 
 * @retval None
 */
void Ro_TIM0_ConfigPWMSettable(uint8_t pwm_n, uint8_t status)
{
	uint8_t status_b = status == 0?0:1;

	switch(pwm_n){
	case 0:
		MODIFY_REG(PWM0_REG(TIM0_TCON3), PWM0EN(1)*(!status_b), PWM0EN(1)*status_b);
		break;
	case 1:
		MODIFY_REG(PWM0_REG(TIM0_TCON3), PWM1EN(1)*(!status_b), PWM1EN(1)*status_b);
		break;
	case 2:
		MODIFY_REG(PWM0_REG(TIM0_TCON3), PWM2EN(1)*(!status_b), PWM2EN(1)*status_b);
		break;
	case 3:
		MODIFY_REG(PWM0_REG(TIM0_TCON3), PWM3EN(1)*(!status_b), PWM3EN(1)*status_b);
		break;
	default:
		break;
	}
	WRITE_REG(PWM0_REG(TIM0_TCON),CMS(1)|DIR(0)|OPM(0)|URS(0)|UDIS(0)|TR(1));
}
/** 
 * @brief 配置死区时间
 * @param DeadTime: 时间范围 0x00-0xff
 *
 *
 * @retval None
 */
 
void Ro_TIM0_ConfigBreakDeadTime(uint8_t DeadTime)
{
	WRITE_REG(PWM0_REG(TIM0_DEADTIME),DDATA(DeadTime));	//DeadTime
}

/** 
 * @brief 配置 timer32 时钟 (todo)
 * @param div: 时钟配置参数
 *
 *
 * @retval None
 */
void Ro_TIM0_ConfigClockDivision(uint8_t div)
{
	Ro_Init_TIM0_CLK(div);
}

/** 
 * @brief 配置 timer32 的分频系数
 * @param psc: 分频系数的值
 *
 * @retval None
 */
void Ro_TIM0_ConfigPrescaler(uint16_t psc)
{
	WRITE_REG(PWM0_REG(TIM0_PRESCALER),PDATA(psc));
}

/** 
 * @brief 配置 timer16 的计数器初始值和结束值 (todo)
 * @param cnt: 分频系数的值
 *
 * @retval None
 */
void Ro_TIM0_ConfigPeriod(uint32_t cnt)
{
    
	WRITE_REG(PWM0_REG(TIM0_TM0),TIM32COUNT(0));
	WRITE_REG(PWM0_REG(TIM0_IT_RELOAD),LDATA(cnt-1));
}
/** 
 * @brief 配置 timer32 的分频系数
 * @param pwm_n: 要配置的pwm通道序号
 * @param acc: 
 *
 * @retval None
 */
void Ro_TIM0_RepetitionCounter(int pwm_n, uint32_t acc)
{
	switch(pwm_n) {
	case 0:
		WRITE_REG(PWM0_REG(TIM0_CM0),LDATA(acc));
		break;
	case 1:
		WRITE_REG(PWM0_REG(TIM0_CM1),LDATA(acc));
		break;
	case 2:
		WRITE_REG(PWM0_REG(TIM0_CM2),LDATA(acc));
		break;
	case 3:
		WRITE_REG(PWM0_REG(TIM0_CM3),LDATA(acc));
		break;
	default:
		break;
	}
	WRITE_REG(PWM0_REG(TIM0_TCON),CMS(0)|DIR(0)|OPM(0)|URS(0)|UDIS(0)|TR(1));
}

/** 
 * @brief 配置 timer32 pwm模式时某通道的占空比
 * @param pwm_n: 要配置的pwm通道序号
 * @param dr: 要配置成的pwm 占空比，例如，要配置成80%，则dr为80.
 *
 * @retval None
 */
void Ro_TIM0_ConfigDutyRatio(int pwm_n, uint32_t dr)
{
	uint32_t val;
    if(dr==0)
    {
        val = 0;
    }
    else if(dr==100)
    {
        val = 0xffff;
    }
    else
    {
		val = READ_REG(PWM0_REG(TIM0_IT_RELOAD));
		val = ((val+1) * dr/100)-1;
    }
	Ro_TIM0_RepetitionCounter(pwm_n, val);
}


#endif
