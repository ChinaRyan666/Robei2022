#include "platform.h"
#include <stdio.h>
#include "config.h"

/*-----------------------------------------------------------*/
#define	ZZFW	"$DKT:2,1!\r\n"	//	中姿复位
#define	ZMSQJ	"$DKT:17,0!\r\n"	//	中慢速前进
#define	ZMSHT	"$DKT:18,5!\r\n"	//	中慢速后退
#define	ZMSZZ	"$DKT:19,0!\r\n"	//	中慢速左转
#define	ZMSYZ	"$DKT:20,5!\r\n"	//	中慢速右转
#define	STOP "$DST!\r\n"	//	中慢速右转

/*------------------当接收到八角板传来的高低电平，通过F组对应引脚进行读取，做出相应判断，再通过A0向六足机器人控制板发送信息指令-----------------------------------------*/
int main( void )
{
	uint32_t   i=0;
    uint32_t   j=0;
	uint32_t   z=0;//0x03;
  
    huart0.Instance=UART0;
    Ro_Init_Uart(&huart0);
    huart1.Instance=UART1;
    Ro_Init_Uart(&huart1); 	//初始化uart0和uart1
    GPIO_InitTypeDef TestGPIO;
    TestGPIO.Pin=GPIO_PIN_0;
    TestGPIO.Mode=GPIO_MODE_INPUT;
    Ro_GPIO_Init(GPIOF,&TestGPIO);//初始化F组引脚，设置为输入
    
   


        
       while(1)
       {
           if(i==1000000)
           {
               i=0;
               
               z=Ro_GPIO_ReadPin(GPIOF, GPIO_PIN_0);
             
               
                printf("%ld\r\n",z);
                 
                 
                
               
               
           }
      
   i++;
	
	}

}