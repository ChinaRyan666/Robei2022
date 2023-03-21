#include "config.h"

#ifdef HAMSTER_IWDG_MODULE_ENABLED
#include "hamster_IWDG.h"
IWDG_HandleTypeDef Handle_IWDG;

void Hamster_IWDG_Init(void)
{
#if 1

//param setup
IWDG_REG(IWDG_KEY)=0x1CCCC;
IWDG_REG(IWDG_KEY)=0x1AAAA;
IWDG_REG(IWDG_WR)=0xfff;
IWDG_REG(IWDG_RELOAD)=0xfff;//0xf;
IWDG_REG(IWDG_IPC)=0x0;
IWDG_REG(IWDG_KEY)=0x1CCCC;
#else

/*-------------------------------------

IWDG_WR锛?volatile uint32_t WINR;
IWDG_COUNT锛?volatile uint32_t COUNT;
	volatile uint32_t KR;
	volatile uint32_t PR;
	volatile uint32_t RLR;

--------------------------------------*/
	uart_putchar('A');

	Handle_IWDG.Instance=IWDG;
	Handle_IWDG.Init.Prescaler=IWDG_PRESCALER_4;
	Handle_IWDG.Init.Window=4095;
	Handle_IWDG.Init.Reload=0xff;
	Handle_IWDG.Instance->KR=IWDG_KEY_ENABLE;
	
	Handle_IWDG.Instance->KR=IWDG_KEY_WRITE_ACCESS_ENABLE;
	Handle_IWDG.Instance->PR=Handle_IWDG.Init.Prescaler;
	Handle_IWDG.Instance->WINR=Handle_IWDG.Init.Window;
	Handle_IWDG.Instance->RLR=Handle_IWDG.Init.Reload;
	Hamster_IWDG_Refresh();
#endif
	
}

void Hamster_IWDG_Refresh(void)
{
	//Handle_IWDG.Instance->KR=IWDG_KEY_RELOAD;
	IWDG_REG(IWDG_KEY)=0x1AAAA;//这个是操作reload
	IWDG_REG(IWDG_KEY)=0x1cccc;//此为启动，如果不添加此动作，无法开启看门狗，此处与st不一致
}

void Hamster_IWDG_WWDG_Init(void)
{
//param setup
IWDG_REG(IWDG_KEY)=0x1AAAA;
IWDG_REG(IWDG_WR)=0x1ff;//c24->
IWDG_REG(IWDG_RELOAD)=0x1ff;//0x203;
IWDG_REG(IWDG_IPC)=0x0;
//IWDG_REG(IWDG_KEY)=0x1cccc;//c34->c68
//IWDG_REG(IWDG_KEY)=0x1AAAA;
IWDG_REG(IWDG_KEY)=0x1cccc;

#if 0
	uart_test('A');
	Handle_IWDG.Instance=IWDG;
	Handle_IWDG.Init.Prescaler=IWDG_PRESCALER_4;
	Handle_IWDG.Init.Window=4095;
	Handle_IWDG.Init.Reload=0xff;
	uart_test('B');
	Handle_IWDG.Instance->KR=IWDG_KEY_ENABLE;
	uart_test('C');
	
	Handle_IWDG.Instance->KR=IWDG_KEY_WRITE_ACCESS_ENABLE;
	uart_test('D');
	Handle_IWDG.Instance->PR=Handle_IWDG.Init.Prescaler;
	uart_test('E');
	Handle_IWDG.Instance->WINR=Handle_IWDG.Init.Window;
	uart_test('F');
	Handle_IWDG.Instance->RLR=Handle_IWDG.Init.Reload;
	uart_test('G');
#endif
	
}

void Hamster_IWDG_WWDG_Refresh(void)
{
	//Handle_IWDG.Instance->KR=IWDG_KEY_RELOAD;
	if(IWDG_REG(IWDG_COUNT)<0x1ff)
	{
		//IWDG_REG(IWDG_KEY)=0x1AAAA;
		IWDG_REG(IWDG_WR)=0x1ff;
		//IWDG_REG(IWDG_KEY)=0x1cccc;
	}
}

//不喂狗，直接等待重启


void Hamster_IWDG_Test_Reset(void)//ok
{
	Hamster_IWDG_Init();
	while(1);
}

//喂狗，不重启

void Hamster_IWDG_Test_nReset(void)
{
	Hamster_IWDG_Init();
	while(1)
	{
	
		IWDG_REG(IWDG_KEY)=0x1AAAA;//这个是操作reload
		IWDG_REG(IWDG_KEY)=0x1cccc;//此为启动，如果不添加此动作，无法开启看门狗，此处与st不一致
		//Hamster_IWDG_Refresh();
	}
}

//独立喂狗中的窗口喂狗，等待重启

void Hamster_IWDG_Test_WWDG_Reset(void)
{
	Hamster_IWDG_WWDG_Init();
	while(1);
}

//独立喂狗中的窗口喂狗，不重启

void Hamster_IWDG_Test_WWDG_nReset(void)
{
	Hamster_IWDG_WWDG_Init();
	while(1)
	{
		Hamster_IWDG_WWDG_Refresh();
	}
}

//独立喂狗中的窗口喂狗，错误时间喂狗重启

void Hamster_IWDG_Test_WWDG_Count_Reset(void)
{
	Hamster_IWDG_WWDG_Init();
	while(1)
	{
		if(IWDG_REG(IWDG_COUNT)>=0x1ff)
		{
			//IWDG_REG(IWDG_KEY)=0x1AAAA;
			IWDG_REG(IWDG_WR)=0x1ff;
			//IWDG_REG(IWDG_KEY)=0x1cccc;
		}
	}
}
void Hamster_IWDG_Test_nReset_DIV(uint16_t prescale)
{
	IWDG_REG(IWDG_KEY)=0x1cccc;
	IWDG_REG(IWDG_KEY)=0x1AAAA;
	IWDG_REG(IWDG_WR)=0xfff;
	IWDG_REG(IWDG_RELOAD)=0xf;
	IWDG_REG(IWDG_IPC)=prescale;
	IWDG_REG(IWDG_KEY)=0x1cccc;
	while(1)
	{
		Hamster_IWDG_Refresh();
	}

}
void Hamster_IWDG_Test_nReset_DIV_8(void)
{
	Hamster_IWDG_Test_nReset_DIV(IWDG_PRESCALER_8);
}
void Hamster_IWDG_Test_nReset_DIV_16(void)
{
	Hamster_IWDG_Test_nReset_DIV(IWDG_PRESCALER_16);
}

void Hamster_IWDG_Test_nReset_DIV_32(void)
{
	Hamster_IWDG_Test_nReset_DIV(IWDG_PRESCALER_32);
}

void Hamster_IWDG_Test_nReset_DIV_64(void)
{
	Hamster_IWDG_Test_nReset_DIV(IWDG_PRESCALER_64);
}

void Hamster_IWDG_Test_nReset_DIV_128(void)
{
	Hamster_IWDG_Test_nReset_DIV(IWDG_PRESCALER_128);
}


void Hamster_IWDG_Test_nReset_DIV_256(void)
{
	Hamster_IWDG_Test_nReset_DIV(IWDG_PRESCALER_256);
}

#endif


