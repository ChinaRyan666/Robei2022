#include "platform.h"
#include "hamster_GPIO.h"
#include "config.h"

void Ro_MT_Uart0_1(void)
{
	uint32_t cont=0;
	uint8_t i=0;
	i='0';
	while(1)
	{
		cont++;
		if(cont%1000==0)
		{
			uart1_putchar(i);
			//uart0_putchar(i);
			printf("%c\n",i);
			i++;
			if(i==127)
				i='0';
		}
	}
}
void Ro_MT_GPIO_TopBroadOutput(void)
{
	uint32_t cont=0;
	uint8_t i;
	uint8_t u8LastGPIO;
	printf("%s %s\r\n",__FUNCTION__,__TIME__);
	GPIOB->GPIO_A=0;
	GPIOB->GPIO_F=0;
	GPIOB->GPIO_OE=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	GPIOB->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

	GPIOC->GPIO_A=0;
	GPIOC->GPIO_F=0;
	GPIOC->GPIO_OE=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	GPIOC->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

	GPIOD->GPIO_A=0;
	GPIOD->GPIO_F=0;
	GPIOD->GPIO_OE=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	GPIOD->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

	GPIOE->GPIO_A=0;
	GPIOE->GPIO_F=0;
	GPIOE->GPIO_OE=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	GPIOE->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

	GPIOF->GPIO_A=0;
	GPIOF->GPIO_F=0;
	GPIOF->GPIO_OE=0;
	//GPIOF->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	//进入循环，如果GPIO与上一次不一致，打印
	while(1)
	{
		cont++;
		if(cont%4000==0)
		{
			GPIOB->GPIO_W=0;
			GPIOC->GPIO_W=0;
			GPIOD->GPIO_W=0;
			GPIOE->GPIO_W=0;
			//GPIOF->GPIO_W=0;
			printf("All low\n");
		}
		else if(cont%2000==0)
		{
			GPIOB->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			GPIOC->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			GPIOD->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			GPIOE->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			//GPIOF->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			printf("All High\n");
		}
	}
	//A组输出高低
	//B组输入，如果检测到数值变化则打印出来
}

void Ro_MT_GPIO_TopBroadInput(void)
{
	uint32_t cont=0;
	uint8_t i;
	uint8_t u8LastGPIOB,u8LastGPIOC,u8LastGPIOD,u8LastGPIOE;
	
	printf("%s %s\r\n",__FUNCTION__,__TIME__);
	GPIOB->GPIO_A=0;
	GPIOB->GPIO_F=0;
	GPIOB->GPIO_OE=0;

	GPIOC->GPIO_A=0;
	GPIOC->GPIO_F=0;
	GPIOC->GPIO_OE=0;

	GPIOD->GPIO_A=0;
	GPIOD->GPIO_F=0;
	GPIOD->GPIO_OE=0;

	GPIOE->GPIO_A=0;
	GPIOE->GPIO_F=0;
	GPIOE->GPIO_OE=0;
	
	//进入循环，如果GPIO与上一次不一致，打印
	while(1)
	{
	
		if(u8LastGPIOB!=GPIOB->GPIO_R)
		{
			u8LastGPIOB=GPIOB->GPIO_R;
			printf("Read GPIOB %02x\r\n",u8LastGPIOB);
		}
		if(u8LastGPIOC!=GPIOC->GPIO_R)
		{
			u8LastGPIOC=GPIOC->GPIO_R;
			printf("Read GPIOC %02x\r\n",u8LastGPIOC);
		}
		if(u8LastGPIOD!=GPIOD->GPIO_R)
		{
			u8LastGPIOD=GPIOD->GPIO_R;
			printf("Read GPIOD %02x\r\n",u8LastGPIOD);
		}
		if(u8LastGPIOE!=GPIOE->GPIO_R)
		{
			u8LastGPIOE=GPIOE->GPIO_R;
			printf("Read GPIOE %02x\r\n",u8LastGPIOE);
		}
		//if(u8LastGPIOM!=GPIOM->GPIO_R)
		{
		//	u8LastGPIOM=GPIOM->GPIO_R;
		//	printf("Read GPIOM %02x\r\n",u8LastGPIOM);
		}
	}
	//A组输出高低
	//B组输入，如果检测到数值变化则打印出来
}

void Ro_MT_GPIO_BotBroadInput(void)
{
	uint32_t cont=0;
	uint8_t i;
	uint8_t u8LastGPIOI,u8LastGPIOJ,u8LastGPIOK,u8LastGPIOL,u8LastGPIOM;
	
	printf("%s %s\r\n",__FUNCTION__,__TIME__);
	GPIOI->GPIO_A=0;
	GPIOI->GPIO_F=0;
	GPIOI->GPIO_OE=0;

	GPIOJ->GPIO_A=0;
	GPIOJ->GPIO_F=0;
	GPIOJ->GPIO_OE=0;

	GPIOK->GPIO_A=0;
	GPIOK->GPIO_F=0;
	GPIOK->GPIO_OE=0;

	GPIOL->GPIO_A=0;
	GPIOL->GPIO_F=0;
	GPIOL->GPIO_OE=0;

	//GPIOM->GPIO_A=0;
	//GPIOM->GPIO_F=0;
	//GPIOM->GPIO_OE=0;

	//进入循环，如果GPIO与上一次不一致，打印
	while(1)
	{
	
		if(u8LastGPIOI!=GPIOI->GPIO_R)
		{
			u8LastGPIOI=GPIOI->GPIO_R;
			printf("Read GPIOI %02x\r\n",u8LastGPIOI);
		}
		if(u8LastGPIOJ!=GPIOJ->GPIO_R)
		{
			u8LastGPIOJ=GPIOJ->GPIO_R;
			printf("Read GPIOJ %02x\r\n",u8LastGPIOJ);
		}
		if(u8LastGPIOK!=GPIOK->GPIO_R)
		{
			u8LastGPIOK=GPIOK->GPIO_R;
			printf("Read GPIOK %02x\r\n",u8LastGPIOK);
		}
		if(u8LastGPIOL!=GPIOL->GPIO_R)
		{
			u8LastGPIOL=GPIOL->GPIO_R;
			printf("Read GPIOL %02x\r\n",u8LastGPIOL);
		}
		//if(u8LastGPIOM!=GPIOM->GPIO_R)
		{
		//	u8LastGPIOM=GPIOM->GPIO_R;
		//	printf("Read GPIOM %02x\r\n",u8LastGPIOM);
		}
	}
	//A组输出高低
	//B组输入，如果检测到数值变化则打印出来
}
void Ro_MT_GPIO_BotBroadOutput(void)
{
	uint32_t cont=0;
	uint8_t i;
	uint8_t u8LastGPIO;
	printf("%s %s\r\n",__FUNCTION__,__TIME__);
	GPIOI->GPIO_A=0;
	GPIOI->GPIO_F=0;
	GPIOI->GPIO_OE=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

	GPIOJ->GPIO_A=0;
	GPIOJ->GPIO_F=0;
	GPIOJ->GPIO_OE=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);


	GPIOK->GPIO_A=0;
	GPIOK->GPIO_F=0;
	GPIOK->GPIO_OE=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

	GPIOL->GPIO_A=0;
	GPIOL->GPIO_F=0;
	GPIOL->GPIO_OE=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	//进入循环，如果GPIO与上一次不一致，打印
	while(1)
	{
		cont++;
		if(cont%4000==0)
		{
			GPIOI->GPIO_W=0;
			GPIOJ->GPIO_W=0;
			GPIOK->GPIO_W=0;
			GPIOL->GPIO_W=0;
			//GPIOF->GPIO_W=0;
			printf("All low\n");
		}
		else if(cont%2000==0)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			//GPIOF->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			printf("All High\n");
		}
	}
	//A组输出高低
	//B组输入，如果检测到数值变化则打印出来
}
void Ro_MT_TopGPIOA_IT(void)
{
	printf("%s %s\r\n",__FUNCTION__,__TIME__);
	Ro_GPIOA_test_IT();
}

void Ro_MT_TopGPIOB_IT(void)
{
	printf("%s %s\r\n",__FUNCTION__,__TIME__);
	Ro_GPIOB_test_IT();
}
void Ro_MT_TopGPIOC_IT(void)
{
	printf("%s %s\r\n",__FUNCTION__,__TIME__);
	Ro_GPIOC_test_IT();
}
void Ro_MT_TopGPIOD_IT(void)
{
	printf("%s %s\r\n",__FUNCTION__,__TIME__);
	Ro_GPIOD_test_IT();
}


void Ro_MT_BotGPIOH_trigerGPIOA_IT(void)
{
	uint32_t cont=0;
	printf("%s %s\r\n",__FUNCTION__,__TIME__);

	GPIOH->GPIO_A=0;
	GPIOH->GPIO_F=0;
	GPIOH->GPIO_OE=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	GPIOH->GPIO_W=0;

	while(1)
	{
		cont++;
		if(cont==1000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0);
			printf("GPIOH 0 raising\r\n");
		}
		else if(cont==2000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1);
			printf("GPIOH 1 raising\r\n");
		}
		else if(cont==3000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
			printf("GPIOH 2 raising\r\n");
		}
		else if(cont==4000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
			printf("GPIOH 3 raising\r\n");
		}
		else if(cont==5000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
			printf("GPIOH 4 raising\r\n");
		}
		else if(cont==6000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
			printf("GPIOH 5 raising\r\n");
		}
		else if(cont==7000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
			printf("GPIOH 6 raising\r\n");
		}
		else if(cont==8000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			printf("GPIOH 7 raising\r\n");
		}
		else if(cont==9000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
		}
		else if(cont==10000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
			printf("GPIOH 7 falling\r\n");
		}
		else if(cont==12000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
			printf("GPIOH 6 falling\r\n");
		}
		else if(cont==13000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
			printf("GPIOH 5 falling\r\n");
		}
		else if(cont==14000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
			printf("GPIOH 4 falling\r\n");
		}
		else if(cont==15000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
			printf("GPIOH 3 falling\r\n");
		}
		else if(cont==16000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1);
			printf("GPIOH 2 falling\r\n");
		}
		else if(cont==17000)
		{
			GPIOH->GPIO_W=(GPIO_PIN_0);
			printf("GPIOH 1 falling\r\n");
		}
		else if(cont==18000)
		{
			GPIOH->GPIO_W=0;
			printf("GPIOH 0 falling\r\n");
			cont=0;
		}
	}
}

void Ro_MT_BotGPIOI_trigerGPIOB_IT(void)
{
	uint32_t cont=0;
	printf("%s %s\r\n",__FUNCTION__,__TIME__);

	GPIOI->GPIO_A=0;
	GPIOI->GPIO_F=0;
	GPIOI->GPIO_OE=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	GPIOI->GPIO_W=0;

	while(1)
	{
		cont++;
		if(cont==1000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0);
			printf("GPIOI 0 raising\r\n");
		}
		else if(cont==2000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1);
			printf("GPIOI 1 raising\r\n");
		}
		else if(cont==3000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
			printf("GPIOI 2 raising\r\n");
		}
		else if(cont==4000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
			printf("GPIOI 3 raising\r\n");
		}
		else if(cont==5000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
			printf("GPIOI 4 raising\r\n");
		}
		else if(cont==6000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
			printf("GPIOI 5 raising\r\n");
		}
		else if(cont==7000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
			printf("GPIOI 6 raising\r\n");
		}
		else if(cont==8000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			printf("GPIOI 7 raising\r\n");
		}
		else if(cont==9000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);	
		}
		else if(cont==10000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
			printf("GPIOI 7 falling\r\n");
		}
		else if(cont==12000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
			printf("GPIOI 6 falling\r\n");
		}
		else if(cont==13000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
			printf("GPIOI 5 falling\r\n");
		}
		else if(cont==14000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
			printf("GPIOI 4 falling\r\n");
		}
		else if(cont==15000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
			printf("GPIOI 3 falling\r\n");
		}
		else if(cont==16000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1);
			printf("GPIOI 2 falling\r\n");
		}
		else if(cont==17000)
		{
			GPIOI->GPIO_W=(GPIO_PIN_0);
			printf("GPIOI 1 falling\r\n");
		}
		else if(cont==18000)
		{
			GPIOI->GPIO_W=0;
			printf("GPIOI 0 falling\r\n");
			cont=0;
		}
	}
}
void Ro_MT_BotGPIOJ_trigerGPIOC_IT(void)
{
	uint32_t cont=0;
	printf("%s %s\r\n",__FUNCTION__,__TIME__);

	GPIOJ->GPIO_A=0;
	GPIOJ->GPIO_F=0;
	GPIOJ->GPIO_OE=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	GPIOJ->GPIO_W=0;

	while(1)
	{
		cont++;
		if(cont==1000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0);
			printf("GPIOJ 0 raising\r\n");
		}
		else if(cont==2000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1);
			printf("GPIOJ 1 raising\r\n");
		}
		else if(cont==3000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
			printf("GPIOJ 2 raising\r\n");
		}
		else if(cont==4000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
			printf("GPIOJ 3 raising\r\n");
		}
		else if(cont==5000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
			printf("GPIOJ 4 raising\r\n");
		}
		else if(cont==6000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
			printf("GPIOJ 5 raising\r\n");
		}
		else if(cont==7000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
			printf("GPIOJ 6 raising\r\n");
		}
		else if(cont==8000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			printf("GPIOJ 7 raising\r\n");
		}
		else if(cont==9000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
		}
		else if(cont==10000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
			printf("GPIOJ 7 falling\r\n");
		}
		else if(cont==12000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
			printf("GPIOJ 6 falling\r\n");
		}
		else if(cont==13000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
			printf("GPIOJ 5 falling\r\n");
		}
		else if(cont==14000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
			printf("GPIOJ 4 falling\r\n");
		}
		else if(cont==15000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
			printf("GPIOJ 3 falling\r\n");
		}
		else if(cont==16000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1);
			printf("GPIOJ 2 falling\r\n");
		}
		else if(cont==17000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0);
			printf("GPIOJ 1 falling\r\n");
		}
		else if(cont==18000)
		{
			GPIOJ->GPIO_W=0;
			printf("GPIOJ 0 falling\r\n");
			cont=0;
		}
	}
}
void Ro_MT_BotGPIOK_trigerGPIOD_IT(void)
{
	uint32_t cont=0;
	printf("%s %s\r\n",__FUNCTION__,__TIME__);

	GPIOK->GPIO_A=0;
	GPIOK->GPIO_F=0;
	GPIOK->GPIO_OE=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	GPIOK->GPIO_W=0;
	while(1)
	{
		cont++;
		if(cont==3000)
		{
			GPIOK->GPIO_OE=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			printf("GPIOK all raising\r\n");
		}
		else if(cont==6000)
		{
			GPIOK->GPIO_OE=0;
			printf("GPIOK all falling\r\n");
			cont=0;

		}

	}
	while(1)
	{
		cont++;
		if(cont==1000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0);
			printf("GPIOK 0 raising\r\n");
		}
		else if(cont==2000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1);
			printf("GPIOK 1 raising\r\n");
		}
		else if(cont==3000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
			printf("GPIOK 2 raising\r\n");
		}
		else if(cont==4000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
			printf("GPIOK 3 raising\r\n");
		}
		else if(cont==5000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
			printf("GPIOK 4 raising\r\n");
		}
		else if(cont==6000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
			printf("GPIOK 5 raising\r\n");
		}
		else if(cont==7000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
			printf("GPIOK 6 raising\r\n");
		}
		else if(cont==8000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			printf("GPIOK 7 raising\r\n");
		}
		else if(cont==9000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
		}
		else if(cont==10000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
			printf("GPIOK 7 falling\r\n");
		}
		else if(cont==12000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
			printf("GPIOK 6 falling\r\n");
		}
		else if(cont==13000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
			printf("GPIOK 5 falling\r\n");
		}
		else if(cont==14000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
			printf("GPIOK 4 falling\r\n");
		}
		else if(cont==15000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
			printf("GPIOK 3 falling\r\n");
		}
		else if(cont==16000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1);
			printf("GPIOK 2 falling\r\n");
		}
		else if(cont==17000)
		{
			GPIOK->GPIO_W=(GPIO_PIN_0);
			printf("GPIOK 1 falling\r\n");
		}
		else if(cont==18000)
		{
			GPIOK->GPIO_W=0;
			printf("GPIOK 0 falling\r\n");
			cont=0;
		}
	}



}

void Ro_MT_BotGPIOJremapI_trigerGPIOB_IT(void)
{
	uint32_t cont=0;
	printf("%s %s\r\n",__FUNCTION__,__TIME__);

	MODIFY_REG(GPIO_REG(GPIO_REMAP1),SET_I(0xf),SET_I(GPJ));
	MODIFY_REG(GPIO_REG(GPIO_REMAP0),SET_J(0xf),SET_J(GPI));
	GPIOJ->GPIO_A=0;
	GPIOJ->GPIO_F=0;
	GPIOJ->GPIO_OE=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	GPIOJ->GPIO_W=0;

	while(1)
	{
		cont++;
		if(cont==1000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0);
			printf("GPIOJ 0 raising\r\n");
		}
		else if(cont==2000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1);
			printf("GPIOJ 1 raising\r\n");
		}
		else if(cont==3000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
			printf("GPIOJ 2 raising\r\n");
		}
		else if(cont==4000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
			printf("GPIOJ 3 raising\r\n");
		}
		else if(cont==5000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
			printf("GPIOJ 4 raising\r\n");
		}
		else if(cont==6000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
			printf("GPIOJ 5 raising\r\n");
		}
		else if(cont==7000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
			printf("GPIOJ 6 raising\r\n");
		}
		else if(cont==8000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			printf("GPIOJ 7 raising\r\n");
		}
		else if(cont==9000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			
		}
		else if(cont==10000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
			printf("GPIOJ 7 falling\r\n");
		}
		else if(cont==12000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
			printf("GPIOJ 6 falling\r\n");
		}
		else if(cont==13000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
			printf("GPIOJ 5 falling\r\n");
		}
		else if(cont==14000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
			printf("GPIOJ 4 falling\r\n");
		}
		else if(cont==15000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
			printf("GPIOJ 3 falling\r\n");
		}
		else if(cont==16000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1);
			printf("GPIOJ 2 falling\r\n");
		}
		else if(cont==17000)
		{
			GPIOJ->GPIO_W=(GPIO_PIN_0);
			printf("GPIOJ 1 falling\r\n");
		}
		else if(cont==18000)
		{
			GPIOJ->GPIO_W=0;
			printf("GPIOJ 0 falling\r\n");
			cont=0;
		}
	}



}
void Ro_MT_BotGPIOLremapJ_trigerGPIOC_IT(void)
{
	uint32_t cont=0;
	printf("%s %s\r\n",__FUNCTION__,__TIME__);

	MODIFY_REG(GPIO_REG(GPIO_REMAP0),SET_J(0xf),SET_J(GPL));
	MODIFY_REG(GPIO_REG(GPIO_REMAP0),SET_L(0xf),SET_L(GPJ));
	GPIOL->GPIO_A=0;
	GPIOL->GPIO_F=0;
	GPIOL->GPIO_OE=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	GPIOL->GPIO_W=0;

	while(1)
	{
		cont++;
		if(cont==1000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0);
			printf("GPIOL 0 raising\r\n");
		}
		else if(cont==2000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1);
			printf("GPIOL 1 raising\r\n");
		}
		else if(cont==3000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
			printf("GPIOL 2 raising\r\n");
		}
		else if(cont==4000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
			printf("GPIOL 3 raising\r\n");
		}
		else if(cont==5000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
			printf("GPIOL 4 raising\r\n");
		}
		else if(cont==6000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
			printf("GPIOL 5 raising\r\n");
		}
		else if(cont==7000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
			printf("GPIOL 6 raising\r\n");
		}
		else if(cont==8000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			printf("GPIOL 7 raising\r\n");
		}
		else if(cont==9000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
			
		}
		else if(cont==10000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
			printf("GPIOL 7 falling\r\n");
		}
		else if(cont==12000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
			printf("GPIOL 6 falling\r\n");
		}
		else if(cont==13000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
			printf("GPIOL 5 falling\r\n");
		}
		else if(cont==14000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
			printf("GPIOL 4 falling\r\n");
		}
		else if(cont==15000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
			printf("GPIOL 3 falling\r\n");
		}
		else if(cont==16000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0|GPIO_PIN_1);
			printf("GPIOL 2 falling\r\n");
		}
		else if(cont==17000)
		{
			GPIOL->GPIO_W=(GPIO_PIN_0);
			printf("GPIOL 1 falling\r\n");
		}
		else if(cont==18000)
		{
			GPIOL->GPIO_W=0;
			printf("GPIOL 0 falling\r\n");
			cont=0;
		}
	}



}



