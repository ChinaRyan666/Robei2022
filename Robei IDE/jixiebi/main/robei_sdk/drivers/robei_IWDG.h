#ifndef _HAMSTER_IWDG_H_
#define _HAMSTER_IWDG_H_
#include <stdio.h>
#include "platform.h"
#include "config.h"
#ifdef RO_IWDG_MODULE_ENABLED
/*

Base Address	:0xfffe_0000

Offset Address	:0xC24
Register Name	:IWDG windows
value 			:window:[11:00]
reset value		:0xfff
note			:窗口寄存器，打开此寄存器必须喂狗要精确，写入0xfff关闭此寄存器

Offset Address	:0xC28
Register Name	:IWDG count
value 			:count:[11:00]
reset value		:0xfff
note			:读取当前的计数�?

Offset Address	:0xC34
Register Name	:IWDG KEY
value 			:window:[15:00]
reset value		:0x0000
note			:必须每个一段时间写�?xAAAA，否则当计数器数�?时，看门狗会产生复位
				写入键�?x5555可使能对IWDG PR寄存器的访问
				写入键�?xcccc可启动看门狗

Offset Address	:0xC38
Register Name	:IWDG Prescale counter
value 			:IPC:[02:00]
reset value		:0x0
note			:预分频，占用三位
				000：DIV4
				001：DIV8
				010: DIV16
				011: DIV32
				100：DIV64
				101：DIV128
				110: DIV256
				111: DIV256

Offset Address	:0xC3C
Register Name	:IWDG Reload
value 			:Reload:[15:00]
reset value		:0xfff
note			:

FLOW�?		
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
	volatile uint32_t KR;
	volatile uint32_t PR;
	volatile uint32_t RLR;
}IWDG_Typedef;

typedef struct
{
	uint32_t Prescaler;	
	uint32_t Reload;	
	uint32_t Window;
}IWDG_InitTypeDef;

typedef struct
{
	IWDG_Typedef  *Instance;
	IWDG_InitTypeDef Init;
}IWDG_HandleTypeDef;


#define IWDG ((IWDG_Typedef *)(IWDG_ADDR+0xc54))
#define WWDG_WR 		0xc54//0xc04
#define WWDG_WCOUNT 	0xc58//0xc08
#define WWDG_WIE	 	0xc5c//0xc2c

#define IWDG_PREV 		0xc08//0xc28
#define IWDG_RELOAD1 	0xc04//0xc28

#define IWDG_WR 		0xc60//0xc24
#define IWDG_COUNT 		0xc64//0xc28
#define IWDG_KEY 		0xc68//0xc34
#define IWDG_IPC 		0xc6c//0xc38
#define IWDG_RELOAD 	0xc70//0xc3c

/* Fields */
#define WINDOW(x)		(((x) & 0xfff) << 0) 
#define WDGCOUNT(x)		(((x) & 0xfff) << 0) 
#define KEY(x)    (((x) & 0xffff) << 0) 
#define IPC(x)    		(((x) & 0x7) << 0) 
#define CLKEN(x)    		(((x) & 0x1) << 16) 

void Hamster_IWDG_Init(void);
void Hamster_IWDG_Refresh(void);




#endif
#endif
