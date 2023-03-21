#ifndef _HAMSTER_WWDG_H_
#define _HAMSTER_WWDG_H_
#include <stdio.h>
#include "platform.h"
#include "config.h"
#ifdef RO_WWDG_MODULE_ENABLED
/*

Base Address	:0xfffe_0000

Offset Address		:0xC04
	Register Name	:WWDG Window 
	value 			:WPC:[01:00]
	reset value		:0x00
				00：DIV1
				01：DIV2
				10: DIV4
				11: DIV8
	note			:

	value 			:count:[13:00]
	reset value		:0x3ff
	note			:


Offset Address		:0xC08
	Register Name	:WWDG Count
	value 			:window:[15:00]
	reset value		:0x3ff
	note			:

Offset Address		:0xC2C
	Register Name	:WWDG key
	value 			:WIE:[09:09]
	reset value		:0x0
	note			:
	value 			:WDIS:[08:08]
	reset value		:0x1
	note			:
	value 			:WIRQ:[00:00]
	reset value		:0x1
	note			:


Offset Address		:0xC3C
Register Name	:IWDG Reload
value 			:Reload:[15:00]
reset value		:0xfff
note			:

FLOW��?		
TODO:独立看门狗中的窗口喂狗理论不清晰
*/


#define IWDG_KEY_RELOAD							0x0000AAAAU
#define IWDG_KEY_ENABLE							0x0000CCCCU
#define IWDG_KEY_WRITE_ACCESS_ENABLE			0x00005555U
#define IWDG_KEY_WRITE_ACCESS_DISABLE			0x00000000U

#define IWDG_PRESCALER_4						0x00000000
#define IWDG_PRESCALER_8						0x00000001
#define IWDG_PRESCALER_16						0x00000010
#define IWDG_PRESCALER_32						0x00000011
#define IWDG_PRESCALER_64						0x00000100
#define IWDG_PRESCALER_128						0x00000101
#define IWDG_PRESCALER_256						0x00000110


typedef struct
{
	volatile uint32_t WINR;
	volatile uint32_t COUNT;
}WWDG_Typedef;

#define WWDG_WW 		0xc54//0xc04
#define WWDG_WCOUNT 	0xc58//0xc08
#define WWDG_WIE	 	0xc5c//0xc2c


/* Fields */
#define WWINDOW(x)		(((x) & 0x3fff) << 0) 
#define WWPC(x)			(((x) & 0x3) << 14) 
#define WCOUNTER(x)		(((x) & 0x3fff) << 0) 
#define WIRQ(x)			(((x) & 0x1) << 0) 
#define WDIS(x)			(((x) & 0x1) << 8) 
#define WIE(x)			(((x) & 0x1) << 9) 

#define CLKEN(x)      (((x) & 0x1) << 16) 
#define WWDG ((IWDG_Typedef *)(IWDG_ADDR+0xc24))


void Ro_WWDG_Init(uint16_t WCOUNT,uint16_t WR);
void Ro_WWDG_Refresh(uint16_t WCOUNT,uint16_t WR);
void Ro_WWDG_Refresh_IT(uint16_t WCOUNT);


#endif
#endif

