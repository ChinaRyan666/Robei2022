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
void Ro_fuwei_send(void)//复位指令
{
    uart0_putchar('$');
    uart0_putchar('D');
    uart0_putchar('K');
    uart0_putchar('T');
    uart0_putchar(':');
    uart0_putchar('1');
    uart0_putchar(',');
    uart0_putchar('1');
   
}

void Ro_dongzuo_send(void)//动作指令
{
    uart0_putchar('$');
    uart0_putchar('D');
    uart0_putchar('K');
    uart0_putchar('T');
    uart0_putchar('：');
    uart0_putchar('4');
    uart0_putchar('1');
    uart0_putchar(',');
    uart0_putchar('1');
    uart0_putchar('!');
   
}
/*------------------当接收到八角板传来的高低电平，通过F组对应引脚进行读取，做出相应判断，再通过A0向六足机器人控制板发送信息指令-----------------------------------------*/
int main( void )
{
	uint32_t   i=0;
    uint32_t   j=0;
	uint32_t   z=0;//0x03;
    uint32_t   x=0;
    uint32_t   y=0;
    uint32_t   t=0;
    huart0.Instance=UART0;
    Ro_Init_Uart(&huart0);
    huart1.Instance=UART1;
    Ro_Init_Uart(&huart1); 	//初始化uart0和uart1
    GPIO_InitTypeDef TestGPIO;
    TestGPIO.Pin=GPIO_PIN_0;
    TestGPIO.Mode=GPIO_MODE_INPUT;
    Ro_GPIO_Init(GPIOF,&TestGPIO);//初始化F组引脚，设置为输入
    
    TestGPIO.Pin=GPIO_PIN_0;
    TestGPIO.Mode=GPIO_MODE_OUTPUT;
    Ro_GPIO_Init(GPIOC,&TestGPIO); //初始化C组引脚，设置为输出 
  


        
       while(1)
       {
           if(i==1000000)
           {
               i=0;
               
               z=Ro_GPIO_ReadPin(GPIOF, GPIO_PIN_0);
             
               if(z==1)
               {
                printf(ZZFW);
                 printf(ZMSQJ);  
                   x=Ro_GPIO_ReadPin(GPIOF, GPIO_PIN_1);//读取F1引脚，是否进行转弯判断
                   if(x==1)
                   {
                     printf(ZMSZZ); 
                      for( j=0;j<3000000;j++){}
                    }
                    y=Ro_GPIO_ReadPin(GPIOF, GPIO_PIN_2);//读取F2引脚，是否进行后退
                     if(y==1)
                     {
                         printf(ZMSHT); 
                      for( j=0;j<2000000;j++){}
                    }
                }
               else if(z==1)
                    printf(ZZFW);
               
           }
      
   i++;
	
	}

}
