/**
 * @file    RO_UART.c
 * @brief	UART接口 : Uart1&Uart2
 *
 * \n
 * @details uart用户可直接调用Ro_Init_uart初始化进行使用,默认参数为无校验位,字宽为8,1个停止位,波特率为115200
 * 小端传输,具体应用可参考module_Uart.c的所有测试用例
 *
 * \n
 * @version 
 * @author  vinolee
 * @date    2020-10-20
 *
 * @history
 *
 */
#include "config.h"

#ifdef RO_UART_MODULE_ENABLED


#include "robei_Uart.h"
#include "robei_SYSCLK.h"

UART_HandleTypeDef huart0;
UART_HandleTypeDef huart1;
/**
 * 
 * @brief	通过串口0直接发送一个是数据
 * \n
 *
 * @param	data		
 * @retval	None
 * \n
 */
 

void uart0_putchar(uint8_t data)
{
	while(!(READ_BIT(UART0_REG(UART_STATUS),UART_u1DTR(1))));
	WRITE_REG(UART0_REG(UART_TX_DATA),UART_TXDATA(data));

}
 
/**
 * 
 * @brief	通过串口1直接发送一个是数据
 * \n
 *
 * @param	data		
 * @retval	None
 * \n
 */
void uart1_putchar(uint8_t data)
{
    while(!(READ_BIT(UART1_REG(UART_STATUS),UART_u1DTR(1))));
	WRITE_REG(UART1_REG(UART_TX_DATA),UART_TXDATA(data));

}


/**
 * 
 * @brief	初始化Uart的时钟
 * \n
 * @param	huart		Uart的handle 指针	
 * @param	u8Uart_CLK	需要查找时钟树来确定当前的频率	
 * @retval	None
 * \n
 */
void Ro_Uart_CLK(UART_HandleTypeDef *huart,uint8_t u8UartCLK)
{
	MODIFY_REG(POWER_CLK_REG(CLOCK_WWDG),CLOCK_UARTEN(0x1),CLOCK_UARTEN(1));
	if(huart->Instance==UART0)
	{
		MODIFY_REG(POWER_CLK_REG(CLOCK_04),CLOCK_UART(0xf),CLOCK_UART(u8UartCLK));
	}
	else
	{
		MODIFY_REG(POWER_CLK_REG(CLOCK_04),CLOCK_UART1(0xf),CLOCK_UART1(u8UartCLK));
	}
}

void Ro_Uart_ResetFIFO(UART_HandleTypeDef *huart)
{
    SET_BIT(huart->Instance->FCR,UART_RFRST(1));
    CLEAR_BIT(huart->Instance->FCR,UART_RFRST(1));
}
/**
 * 
 * @brief	清空当前Uart的缓冲
 * \n
 *
 * @param	huart		Uart的handle 指针	
 * @retval	None
 * \n
 */
void Ro_Uart_Reset(UART_HandleTypeDef *huart)
{
	if(huart->Instance==UART0)
    	WRITE_REG(POWER_CLK_REG(CLOCK_RST),CLOCK_UART0_RST(0x1)); 
	else	
	 	WRITE_REG(POWER_CLK_REG(CLOCK_RST),CLOCK_UART1_RST(0x1)); 
}
void Ro_Uart_Clear(UART_HandleTypeDef *huart)
{
	WRITE_REG(POWER_CLK_REG(CLOCK_RST),UART_RX_CLEAR(0x1)|UART_TX_CLEAR(0x1)); 
}

/**
 * 
 * @brief	使能串口
 * \n
 *
 * @param	huart		Uart的handle 指针	
 * @param	enRx	接收使能	
 * 		@arg ENABLE:使能接收功能	
 * 		@arg DISABLE:关掉接收功能
 *
 * @param	enTx	发送使能
 * 		@arg ENABLE:使能发送功能	
 * 		@arg DISABLE:关掉发送功能
 *
 * @note	当前串口为单工，不能够双工或半双工使用
 * @retval	None
 * \n
 */

void Ro_Uart_Enable(UART_HandleTypeDef *huart,uint8_t enRx ,uint8_t enTx)
{
	if(enTx)
	{
		SET_BIT(huart->Instance->LCR,UART_TXEN(1));
	}
	else
	{
		CLEAR_BIT(huart->Instance->LCR,UART_TXEN(1));
	}
	
	if(enRx)
	{
		SET_BIT(huart->Instance->LCR,UART_RXEN(1));
	}
	else
	{
		CLEAR_BIT(huart->Instance->LCR,UART_RXEN(1));
	}
	
	SET_BIT(huart->Instance->IER,UART_TBEIE(1));//usart1 独有
	SET_BIT(huart->Instance->LCR,UART_UEN(1));
    SET_BIT(huart->Instance->FCR,UART_DMAT(1));//20210224 for uart test
}

/**
 * 
 * @brief	使能Uart1发送中断
 * \n
 *
 * @param	huart		Uart的handle 指针	
 * @param	bEnable		@arg ENABLE 使能发送中断
 * 						@arg DISABLE 关掉发送中断 
 * @retval	None
 * \n
 */

void Ro_Uart_ITEnable(UART_HandleTypeDef *huart,uint8_t bRxEnable,uint8_t bTxEnable)
{
	if(huart->Instance==UART0)
	{
		if(bRxEnable||bTxEnable)
		{
			SET_BIT(PLIC_REG(IT_MASK),IT_IRQ24) ;
			MODIFY_REG(PLIC_REG(IT_REQA24),EX(0xf),EX(0xe));	
		}
		else
		{
			CLEAR_BIT(PLIC_REG(IT_MASK),IT_IRQ24) ;
			MODIFY_REG(PLIC_REG(IT_REQA24),EX(0xf),EX(0xf));	
		}
	}
	else if(huart->Instance==UART1)
	{
		if(bRxEnable||bTxEnable)
		{
			SET_BIT(PLIC_REG(IT_MASK),IT_IRQ25) ;
			MODIFY_REG(PLIC_REG(IT_REQA25),EX(0xf),EX(0xe));	
		}
		else
		{
			CLEAR_BIT(PLIC_REG(IT_MASK),IT_IRQ25) ;
			MODIFY_REG(PLIC_REG(IT_REQA25),EX(0xf),EX(0xf));	
		}
	}
	if(bRxEnable)
	{		
		SET_BIT(huart->Instance->LCR,UART_RBFIE(0x1));	
	}
	else
	{		
		CLEAR_BIT(huart->Instance->LCR,UART_RBFIE(0x1));	
	}
	if(bTxEnable)
	{		
		SET_BIT(huart->Instance->LCR,UART_TBEIE(0x1));	
	}
	else
	{		
		CLEAR_BIT(huart->Instance->LCR,UART_TBEIE(0x1));	
	}
}

/**
 * 
 * @brief	奇偶校验功能选择
 * \n
 *
 * @param	huart		Uart的handle 指针	
 * @param	parity	
 *					@arg 	PARITY_NONE 无奇偶校验
 *					@arg 	PARITY_ODD 	奇校验
 *					@arg 	PARITY_EVEN 偶校验
 * @retval	None
 * \n
 */

void Ro_Uart_Parity(UART_HandleTypeDef *huart,uint8_t parity)
{
	MODIFY_REG(huart->Instance->LCR,UART_EPS(0x1),UART_EPS(parity));	
}

/**
 * 
 * @brief	等待接收一个字符,CPU接收方式
 * \n
 *
 * @param	huart		Uart的handle 指针	
 * @retval	uint8_t
 * \n
 */

uint8_t Ro_Uart_Receive(UART_HandleTypeDef *huart)
{
	uint8_t temp; 
	temp=huart->Instance->RDR;
	
	while(READ_BIT(huart->Instance->ICR,UART_RBusy(1)));//rbusy
//关rxenable
	CLEAR_BIT(huart->Instance->LCR,UART_RXEN(1));
	
//读取数据
	temp=huart->Instance->RDR;
//打开rxenable
	SET_BIT(huart->Instance->LCR,UART_RXEN(1));
	return temp;
}

/**
 * 
 * @brief	字长选择   {URM1,URM0}:0:0_8bit   0:1_9bit	 1:0_7bit	1:1_6bit
 * \n
 *
 * @retval	None
 * @param	huart		Uart的handle 指针	
 * @param	wls	@arg	UART_WORDLENGTH_6B:6bit	
 * @arg	UART_WORDLENGTH_7B:7bit	
 * @arg	UART_WORDLENGTH_8B:8bit	
 * @arg	UART_WORDLENGTH_9B:9bit	
 * \n
 */

void Ro_Uart_WLS(UART_HandleTypeDef *huart,uint32_t wls)
{
	if(wls&UART_WLSURM1(0x1))
		SET_BIT(huart->Instance->LCR, UART_WLSURM1(0x1));
	if(wls&UART_WLSURM0(0x1))
		SET_BIT(huart->Instance->LCR, UART_WLSURM0(0x1));
}

/**
 * 
 * @brief	过采样
 * \n
 *
 * @param	huart		Uart的handle 指针	
 * @param	ovs		
 * 				@arg UART_OVERSAMPLING_16: Over sample 16
 * 				@arg UART_OVERSAMPLING_8 : Over sample 8
 * @retval	None
 * \n
 */
void Ro_Uart_OVS(UART_HandleTypeDef *huart,uint8_t ovs)
{
	MODIFY_REG(huart->Instance->LCR,UART_OVS(0x1),UART_OVS(ovs));	
}
/**
 * 
 * @brief	设置波特率
 * \n
 *
 * @param	huart		Uart的handle 指针	
 * @param	baudrate	波特率需要查找时钟树然后计算可得
 *	baudrate=(GCLK/Uart_ClK)*1000000/baud-1
 * @retval	None
 * \n
 */

void Ro_Uart_BaudRate(UART_HandleTypeDef *huart,uint16_t baudrate)
{
	//(u8Uart1_CLK/9600)-1=0x1a

//0x30: dlm register[15:4]
	huart->Instance->DMR=baudrate&0xfff0;

//0x2c: dll register[3:0]
	huart->Instance->DLR=baudrate&0x000f;

//prescaler
	huart->Instance->PCR=0;
}

/**
 * 
 * @brief	设置停止位
 * \n
 *
 * @param	huart		Uart的handle 指针	
 * @param	stopbit 	
 *			@arg STOP_ONE		1bit 
 *			@arg STOP_HALF		0.5bit 
 *			@arg STOP_TWO		2bit 
 *			@arg STOP_ONEHALF	1.5bit 
 * @retval	None
 * \n
 */
void Ro_Uart_Stopbit(UART_HandleTypeDef *huart,uint8_t stopbit)
{
	MODIFY_REG(huart->Instance->MR,UART_STOP(0x3),UART_STOP(stopbit));	
}

/**
 * 
 * @brief	大小端发送顺序
 * \n
 *
 * @param	huart		Uart的handle 指针	
 * @param	msbfst
 * 	@arg UART_MSB	先发送数据高位
 * 	@arg UART_LSB	先发送数据地位
 * @retval	None
 * \n
 */

void Ro_Uart_MSBFST(UART_HandleTypeDef *huart,uint8_t msbfst)
{
	//设置Rx为输入
	MODIFY_REG(huart->Instance->MR,UART_MSBFST(0x1),UART_MSBFST(msbfst));	
}

void Ro_Uart_SCKEN(UART_HandleTypeDef *huart,uint8_t scken)
{
	//设置Rx为输入
	MODIFY_REG(huart->Instance->MR,UART_SCKEN(0x1),UART_SCKEN(scken));	
}


/*
100	0
010	10 		//Tx 发生的中断
001	100		//Rx 发生的中断
Default	1
*/
/**
 * 
 * @brief	获取Uart1的中断状态
 * \n
 *
 * @param	huart		Uart的handle 指针	
 * @retval	None
 * \n
 */

uint8_t Ro_Uart_IRQStatus(UART_HandleTypeDef *huart)
{
	//低四位有效
	
	return (uint8_t)(huart->Instance->ICR&0xf);
}


/**
 * 
 * @brief	设置Uart1的GPIO
 * \n
 *
 * @param	huart		Uart的handle 指针	
 * @retval	None
 * \n
 */
void Ro_Uart_GPIO(UART_HandleTypeDef *huart)
{
	if(huart->Instance==UART0)
	{
		//SET_BIT(GPIOA->GPIO_OE,GPIO_PIN_2);	
		
		//Tx B3
			SET_BIT(GPIOA->GPIO_A,GPIO_PIN_0);
			SET_BIT(GPIOA->GPIO_F,GPIO_PIN_0);
			SET_BIT(GPIOA->GPIO_OE,GPIO_PIN_0);
			//RX B2
			SET_BIT(GPIOA->GPIO_A,GPIO_PIN_1);
			SET_BIT(GPIOA->GPIO_F,GPIO_PIN_1);
			CLEAR_BIT(GPIOA->GPIO_OE,GPIO_PIN_1);
	}
	else
	{
		SET_BIT(GPIOA->GPIO_A,GPIO_PIN_3);
		SET_BIT(GPIOA->GPIO_F,GPIO_PIN_3);
		SET_BIT(GPIOA->GPIO_OE,GPIO_PIN_3);
	}
}

/**
 * 
 * @brief	使能Uart1的RxDMA
 * \n
 *
 * @param	huart		Uart的handle 指针	
 * @param	bEnable		
 * @retval	None
 * \n
 */
void Ro_Uart_RxDMA_Enable(UART_HandleTypeDef *huart,uint8_t bEnable)
{
	if(bEnable)
	{
		SET_BIT(huart->Instance->DCR,UART_RDMAE(1));
	}
	else
	{
		CLEAR_BIT(huart->Instance->DCR,UART_RDMAE(1));
	}
}


/**
 * 
 * @brief	使能Uart1的DMA发送
 * \n
 *
 * @param	huart		Uart的handle 指针	
 * @param	bEnable		
 * @arg		ENABLE   :使能Tx DMA功能
 * @arg		DISENABLE:关掉Tx DMA功能
 * @retval	None
 * \n
 */
void Ro_Uart_TxDMA_Enable(UART_HandleTypeDef *huart,uint8_t bEnable)
{
	if(bEnable)
	{
	
		SET_BIT(huart->Instance->DCR,UART_TDMAE(0x01));
	}
	else
	{
		CLEAR_BIT(huart->Instance->DCR,UART_TDMAE(0x01));
	}
}
/**
 * 
 * @brief	设置DMA的接收的超时时间
 * \n
 *
 * @param	huart		Uart的handle 指针	
 * @param	u32Time		
 * @retval	None
 * \n
 */
void Ro_Uart_DMA_TimeOut(UART_HandleTypeDef *huart,uint32_t u32Time)
{
	if(u32Time>0xffffff)
		u32Time=0xffffff;
	WRITE_REG(huart->Instance->FLR,(huart->Instance->FLR&0xff000000)|u32Time);
}

/**
 * 
 * @brief	初始化Uart1
 * \n
 *
 * @param	huart		Uart的handle 指针	
 * @retval	None
 * \n
 */
void Ro_Init_Uart(UART_HandleTypeDef *huart)
{
//重置一下

	Ro_Uart_Reset(huart);

//设置时钟
	Ro_Uart_CLK(huart,9);//Uart时钟设置 100MHZ


//设置波特率
	//Ro_Uart_BaudRate(huart,0x08);//fpga小板
	Ro_Uart_BaudRate(huart,0x1a);//100MHz 1a=115200

//设置GPIO，其中tx管脚固定
	Ro_Uart_GPIO(huart);

//设置停止位，默认为1个停止位
	Ro_Uart_Stopbit(huart,STOP_ONE);

//设置高低位发送顺序
	Ro_Uart_MSBFST(huart,UART_LSB);
    Ro_Uart_SCKEN(huart,1);

//设置过采样率
	Ro_Uart_OVS(huart,UART_OVERSAMPLING_16);

//字节位宽选择,选择每次传递数据的位宽
	Ro_Uart_WLS(huart,UART_WORDLENGTH_8B);

//开关中断
	Ro_Uart_RxDMA_Enable(huart,DISABLE);

	Ro_Uart_DMA_TimeOut(huart,400);//3.84s=10000
    SET_BIT( POWER_CLK_REG(0),CLOCK_UART0_RRmp(1));//20210222 新添加测试Rx

//使能串口
	Ro_Uart_Enable(huart,ENABLE,ENABLE);

	Ro_Uart_ITEnable(huart,DISABLE,DISABLE);
}


#endif
