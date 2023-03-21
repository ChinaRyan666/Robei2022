/**
 * @file    hamster_WWDG.c
 * @brief	看门狗接口
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

//-------------------------------------

//#include <FreeRTOS.h>

//-------------------------------------

#ifdef RO_WWDG_MODULE_ENABLED

#include "robei_WWDG.h"
/**
 * 
 * @brief	
 * \n
 * @param	WCOUNT	 窗口计数器，必须大于0x40，最大值0x3fff
 * @param	WR		喂狗范围，在0x40-WR之间可喂狗，WR<=WCOUNT
 *
 * @retval	None
 * \n
 */
void Ro_WWDG_Init(uint16_t WCOUNT,uint16_t WR)
{

	Ro_Init_WWG_CLK(9);

	//param setup
	IWDG_REG(WWDG_WCOUNT)=WCOUNT;//要先写counter，不然会重启，触发cpu的规则，最小更新到WWDG_WR
	IWDG_REG(WWDG_WR)=WR;
	IWDG_REG(IWDG_PREV)=0xff;
	//IWDG_REG(IWDG_RELOAD1)=3;
	
	IWDG_REG(WWDG_WW)=0xc000;
	IWDG_REG(WWDG_WIE)=CLKEN(1);//20201016 added clken

}
/**
 * 
 * @brief	喂狗 窗口计数器，必须大于0x40，最大值0x3fff
 * \n
 *
 * @param	WCOUNT	 窗口计数器，必须大于0x40，最大值0x3fff
 * @param	WR		喂狗范围，在0x40-WR之间可喂狗，WR<=WCOUNT
 * @retval	None
 * \n
 */
void Ro_WWDG_Refresh(uint16_t WCOUNT,uint16_t WR)
{
	if(IWDG_REG(WWDG_WCOUNT)<=WR)
		IWDG_REG(WWDG_WCOUNT)=WCOUNT;
		
	//Handle_IWDG.Instance->KR=IWDG_KEY_RELOAD;
}
/**
 * @brief  运行后立即喂狗
 * @param  WCOUNT	 窗口计数器，必须大于0x40，最大值0x3fff
 *
 * @retval None
 */
void Ro_WWDG_Wrongrefresh(uint16_t WWCOUNT)
{
    IWDG_REG(WWDG_WCOUNT)=WWCOUNT;
}
/**
 * 
 * @brief	中断喂狗
 * \n
 * @param	WCOUNT	 窗口计数器，必须大于0x40，最大值0x3fff
 *
 * @retval	None
 * \n
 */
void Ro_WWDG_Refresh_IT(uint16_t WCOUNT)
{
	IWDG_REG(WWDG_WCOUNT)=WCOUNT;
	CLEAR_BIT(IWDG_REG(WWDG_WIE),WIRQ(1)|CLKEN(1)) ;
}


#endif

