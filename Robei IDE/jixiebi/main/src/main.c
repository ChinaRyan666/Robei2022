/*
 * Copyright (C) 2022 Robei.com, Inc. or its affiliates.  All Rights Reserved.
 */

#include "platform.h"
#include <stdio.h>
#include "config.h"





#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#include "platform.h"
#include <stdio.h>
#include "robei_GPIO.h"
#include "robei_IT.h"

/*-----------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
extern void Ro_TIM_Init(TIM_HandleTypeDef *htim);

void delay_us(uint32_t us)//延时(us)
{
    for(uint32_t i = 0;i<=us;i++);
}

void DM_ch_speed_Position(int i,int data,int angle)//x选择通道(i),舵机转动速度(data),舵机转动角度(angle)
{
    short Data,dataL,dataH,DataL,DataH,y=1,z=255,w=2,b=100;//b为角度校正偏移量
    Data=500+10*angle+b;//转动角度(0-180)转换为舵机对应的时间(500-2000)
    printf("%x",z);
    printf("%x",y);
    switch(i)
    {
        case 0:printf("%x",i); break;
        case 1:printf("%x",i); break;
        case 2:printf("%x",i); break;
        case 3:printf("%x",i); break;
        case 4:printf("%x",i); break;
        case 5:printf("%x",i); break;
        case 6:printf("%x",i); break;
        case 7:printf("%x",i); break;
        case 8:printf("%x",i); break;
        case 9:printf("%x",i); break;
        case 10:printf("%x",i); break;
        case 11:printf("%x",i); break;
        case 12:printf("%x",i); break;
        case 13:printf("%x",i); break;
        case 14:printf("%x",i); break;
        case 15:printf("%x",i); break;
    }
    dataL=data&0xff;//取转动速度data转化为十六进制的低位输出
    dataH=data>>8;//取转动速度转化为十六进制的高位输出
    printf("%x",dataL);
    printf("%x",dataH);
    //选择通道设置速度
    
    
    printf("%x",z);
    printf("%x",w);
    switch(i)
    {
        case 0:printf("%x",i); break;
        case 1:printf("%x",i); break;
        case 2:printf("%x",i); break;
        case 3:printf("%x",i); break;
        case 4:printf("%x",i); break;
        case 5:printf("%x",i); break;
        case 6:printf("%x",i); break;
        case 7:printf("%x",i); break;
        case 8:printf("%x",i); break;
        case 9:printf("%x",i); break;
        case 10:printf("%x",i); break;
        case 11:printf("%x",i); break;
        case 12:printf("%x",i); break;
        case 13:printf("%x",i); break;
        case 14:printf("%x",i); break;
        case 15:printf("%x",i); break;
    }
    DataL=Data&0xff;//取转动速度data转化为十六进制的低位输出
    DataH=Data>>8;//取转动速度转化为十六进制的高位输出
    printf("%x",DataL);
    printf("%x",DataH);
    //选择通道设置转动角度
}
void DM_Action(short Data)//启动动作组(1-10)
{
    short DataL,DataH,x=0,z=255,b=9;//输出0xff,0x09,0x00启动动作组
    printf("%x",z);
    printf("%x",b);
    printf("%x",x);
    DataL=Data&0xff;
    DataH=Data>>8;
    printf("%x",DataL);
    printf("%x",DataH);    
}
void DM_stop()//机械臂停止代码
{
    short x=0,y=1,z=255,b=11;
    printf("%x",z);
    printf("%x",b);
    printf("%x",x);
    printf("%x",y);
    printf("%x",x);
}
int main()
{

    huart0.Instance=UART0;
    Ro_Init_Uart(&huart0);
    huart1.Instance=UART1;
    Ro_Init_Uart(&huart1); //启用uart串口
    GPIO_InitTypeDef TestGPIO; 
    TestGPIO.Mode=GPIO_MODE_INPUT; //设置 C 组的 GPIO 为输入
    TestGPIO.Pin=GPIO_PIN_0;
    TestGPIO.Mode= GPIO_MODE_IT_RISING;//c0上升沿触发中断
    Ro_GPIO_Init(GPIOC,&TestGPIO); //初始化 IO
    TestGPIO.Mode=GPIO_MODE_INPUT; //设置 F 组为输入
    Ro_GPIO_Init(GPIOF,&TestGPIO);//初始化 IO
    TestGPIO.Pin=GPIO_PIN_1;
    TestGPIO.Mode= GPIO_MODE_IT_RISING;//f1上升沿触发中断
        while(1)
    {

        uint32_t i,j=0;
        for(i=0;i<16;i++)
        {
            DM_ch_speed_Position(i,i,0);
        }//控制舵机转到0度
        
        DM_Action(1);//启用动作组1
        if(Ro_GPIO_ReadGroup(GPIOC))//读取C0状态，如果为高电平做出以下动作
        {
            DM_ch_speed_Position(0,5,135);//控制机械臂垂下
            delay_us(10000);
            DM_ch_speed_Position(7,8,90);//控制机械臂右摆
            delay_us(10000);
            DM_ch_speed_Position(0,5,90);
            delay_us(10000);
            DM_ch_speed_Position(7,8,0);
            delay_us(10000); 
            //机械臂归位
        }//控制机械臂做出摆动动作
        if(Ro_GPIO_ReadGroup(GPIOF))
        {
            DM_ch_speed_Position(0,5,135);//控制机械臂垂下
            delay_us(10000);
            DM_ch_speed_Position(4,9,45);
            delay_us(10000);
            DM_ch_speed_Position(9,9,45);
            delay_us(10000);//调整姿态
            DM_ch_speed_Position(10,7,0);//机械臂夹子夹取
            delay_us(10000);
            DM_ch_speed_Position(10,9,180);//机械臂夹子松开
            delay_us(10000);
            DM_ch_speed_Position(9,9,0);
            delay_us(10000);
            DM_ch_speed_Position(4,9,0);
            delay_us(10000);
            DM_ch_speed_Position(0,9,90);
            delay_us(10000);
            //机械臂归位
        }
        //机械表夹取物品
    }
} 



/*

unsigned char DM0_Speed1_Position_90[15]    =    { 0xff, 0x01, 0x00, 0x01, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=1，位置90度
unsigned char DM0_Speed2_Position_90[15]    =    { 0xff, 0x01, 0x00, 0x02, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=2，位置90度
unsigned char DM0_Speed3_Position_90[15]    =    { 0xff, 0x01, 0x00, 0x03, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=3，位置90度
unsigned char DM0_Speed4_Position_90[15]    =    { 0xff, 0x01, 0x00, 0x04, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=4，位置90度
unsigned char DM0_Speed5_Position_90[15]    =    { 0xff, 0x01, 0x00, 0x05, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=5，位置90度
unsigned char DM0_Speed6_Position_90[15]    =    { 0xff, 0x01, 0x00, 0x06, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=6，位置90度
unsigned char DM0_Speed7_Position_90[15]    =    { 0xff, 0x01, 0x00, 0x07, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=7，位置90度
unsigned char DM0_Speed8_Position_90[15]    =    { 0xff, 0x01, 0x00, 0x08, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=8，位置90度
unsigned char DM0_Speed9_Position_90[15]    =    { 0xff, 0x01, 0x00, 0x09, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=9，位置90度
unsigned char DM0_Speed10_Position_90[15]   =    { 0xff, 0x01, 0x00, 0x0a, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=10，位置90度
unsigned char DM0_Speed11_Position_90[15]   =    { 0xff, 0x01, 0x00, 0x0b, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=11，位置90度
unsigned char DM0_Speed12_Position_90[15]   =    { 0xff, 0x01, 0x00, 0x0c, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=12，位置90度
unsigned char DM0_Speed13_Position_90[15]   =    { 0xff, 0x01, 0x00, 0x0d, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=13，位置90度
unsigned char DM0_Speed14_Position_90[15]   =    { 0xff, 0x01, 0x00, 0x0e, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=14，位置90度
unsigned char DM0_Speed15_Position_90[15]   =    { 0xff, 0x01, 0x00, 0x0f, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=15，位置90度
unsigned char DM0_Speed16_Position_90[15]   =    { 0xff, 0x01, 0x00, 0x10, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=16，位置90度
unsigned char DM0_Speed17_Position_90[15]   =    { 0xff, 0x01, 0x00, 0x11, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=17，位置90度
unsigned char DM0_Speed18_Position_90[15]   =    { 0xff, 0x01, 0x00, 0x12, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=18，位置90度
unsigned char DM0_Speed19_Position_90[15]   =    { 0xff, 0x01, 0x00, 0x13, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=19，位置90度
unsigned char DM0_Speed20_Position_90[15]   =    { 0xff, 0x01, 0x00, 0x14, 0x00, 0xff, 0x02, 0x00, 0xdc, 0x05 };  //通道0，速度=20，位置90度
    

unsigned char DM0_Speed1_Position_0[15]     =    { 0xff, 0x01, 0x00, 0x01, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=1，位置0度
unsigned char DM0_Speed2_Position_0[15]     =    { 0xff, 0x01, 0x00, 0x02, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=2，位置0度
unsigned char DM0_Speed3_Position_0[15]     =    { 0xff, 0x01, 0x00, 0x03, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=3，位置0度
unsigned char DM0_Speed4_Position_0[15]     =    { 0xff, 0x01, 0x00, 0x04, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=4，位置0度
unsigned char DM0_Speed5_Position_0[15]     =    { 0xff, 0x01, 0x00, 0x05, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=5，位置0度
unsigned char DM0_Speed6_Position_0[15]     =    { 0xff, 0x01, 0x00, 0x06, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=6，位置0度
unsigned char DM0_Speed7_Position_0[15]     =    { 0xff, 0x01, 0x00, 0x07, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=7，位置0度
unsigned char DM0_Speed8_Position_0[15]     =    { 0xff, 0x01, 0x00, 0x08, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=8，位置0度
unsigned char DM0_Speed9_Position_0[15]     =    { 0xff, 0x01, 0x00, 0x09, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=9，位置0度
unsigned char DM0_Speed10_Position_0[15]    =    { 0xff, 0x01, 0x00, 0x0a, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=10，位置0度
unsigned char DM0_Speed11_Position_0[15]    =    { 0xff, 0x01, 0x00, 0x0b, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=11，位置0度
unsigned char DM0_Speed12_Position_0[15]    =    { 0xff, 0x01, 0x00, 0x0c, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=12，位置0度
unsigned char DM0_Speed13_Position_0[15]    =    { 0xff, 0x01, 0x00, 0x0d, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=13，位置0度
unsigned char DM0_Speed14_Position_0[15]    =    { 0xff, 0x01, 0x00, 0x0e, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=14，位置0度
unsigned char DM0_Speed15_Position_0[15]    =    { 0xff, 0x01, 0x00, 0x0f, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=15，位置0度
unsigned char DM0_Speed16_Position_0[15]    =    { 0xff, 0x01, 0x00, 0x10, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=16，位置0度
unsigned char DM0_Speed17_Position_0[15]    =    { 0xff, 0x01, 0x00, 0x11, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=17，位置0度
unsigned char DM0_Speed18_Position_0[15]    =    { 0xff, 0x01, 0x00, 0x12, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=18，位置0度
unsigned char DM0_Speed19_Position_0[15]    =    { 0xff, 0x01, 0x00, 0x13, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=19，位置0度
unsigned char DM0_Speed20_Position_0[15]    =    { 0xff, 0x01, 0x00, 0x14, 0x00, 0xff, 0x02, 0x00, 0xf4, 0x01 };  //通道0，速度=20，位置0度
                                                                                                  
                                            
unsigned char DM1_Speed1_Position_90[15]    =    { 0xff, 0x01, 0x01, 0x01, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=1，位置90度
unsigned char DM1_Speed2_Position_90[15]    =    { 0xff, 0x01, 0x01, 0x02, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=2，位置90度
unsigned char DM1_Speed3_Position_90[15]    =    { 0xff, 0x01, 0x01, 0x03, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=3，位置90度
unsigned char DM1_Speed4_Position_90[15]    =    { 0xff, 0x01, 0x01, 0x04, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=4，位置90度
unsigned char DM1_Speed5_Position_90[15]    =    { 0xff, 0x01, 0x01, 0x05, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=5，位置90度
unsigned char DM1_Speed6_Position_90[15]    =    { 0xff, 0x01, 0x01, 0x06, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=6，位置90度
unsigned char DM1_Speed7_Position_90[15]    =    { 0xff, 0x01, 0x01, 0x07, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=7，位置90度
unsigned char DM1_Speed8_Position_90[15]    =    { 0xff, 0x01, 0x01, 0x08, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=8，位置90度
unsigned char DM1_Speed9_Position_90[15]    =    { 0xff, 0x01, 0x01, 0x09, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=9，位置90度
unsigned char DM1_Speed10_Position_90[15]   =    { 0xff, 0x01, 0x01, 0x0a, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=10，位置90度
unsigned char DM1_Speed11_Position_90[15]   =    { 0xff, 0x01, 0x01, 0x0b, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=11，位置90度
unsigned char DM1_Speed12_Position_90[15]   =    { 0xff, 0x01, 0x01, 0x0c, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=12，位置90度
unsigned char DM1_Speed13_Position_90[15]   =    { 0xff, 0x01, 0x01, 0x0d, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=13，位置90度
unsigned char DM1_Speed14_Position_90[15]   =    { 0xff, 0x01, 0x01, 0x0e, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=14，位置90度
unsigned char DM1_Speed15_Position_90[15]   =    { 0xff, 0x01, 0x01, 0x0f, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=15，位置90度
unsigned char DM1_Speed16_Position_90[15]   =    { 0xff, 0x01, 0x01, 0x10, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=16，位置90度
unsigned char DM1_Speed17_Position_90[15]   =    { 0xff, 0x01, 0x01, 0x11, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=17，位置90度
unsigned char DM1_Speed18_Position_90[15]   =    { 0xff, 0x01, 0x01, 0x12, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=18，位置90度
unsigned char DM1_Speed19_Position_90[15]   =    { 0xff, 0x01, 0x01, 0x13, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=19，位置90度
unsigned char DM1_Speed20_Position_90[15]   =    { 0xff, 0x01, 0x01, 0x14, 0x00, 0xff, 0x02, 0x01, 0xdc, 0x05 };  //通道1，速度=20，位置90度
       

unsigned char DM1_Speed1_Position_0[15]     =    { 0xff, 0x01, 0x01, 0x01, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=1，位置0度
unsigned char DM1_Speed2_Position_0[15]     =    { 0xff, 0x01, 0x01, 0x02, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=2，位置0度
unsigned char DM1_Speed3_Position_0[15]     =    { 0xff, 0x01, 0x01, 0x03, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=3，位置0度
unsigned char DM1_Speed4_Position_0[15]     =    { 0xff, 0x01, 0x01, 0x04, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=4，位置0度
unsigned char DM1_Speed5_Position_0[15]     =    { 0xff, 0x01, 0x01, 0x05, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=5，位置0度
unsigned char DM1_Speed6_Position_0[15]     =    { 0xff, 0x01, 0x01, 0x06, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=6，位置0度
unsigned char DM1_Speed7_Position_0[15]     =    { 0xff, 0x01, 0x01, 0x07, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=7，位置0度
unsigned char DM1_Speed8_Position_0[15]     =    { 0xff, 0x01, 0x01, 0x08, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=8，位置0度
unsigned char DM1_Speed9_Position_0[15]     =    { 0xff, 0x01, 0x01, 0x09, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=9，位置0度
unsigned char DM1_Speed10_Position_0[15]    =    { 0xff, 0x01, 0x01, 0x0a, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=10，位置0度
unsigned char DM1_Speed11_Position_0[15]    =    { 0xff, 0x01, 0x01, 0x0b, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=11，位置0度
unsigned char DM1_Speed12_Position_0[15]    =    { 0xff, 0x01, 0x01, 0x0c, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=12，位置0度
unsigned char DM1_Speed13_Position_0[15]    =    { 0xff, 0x01, 0x01, 0x0d, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=13，位置0度
unsigned char DM1_Speed14_Position_0[15]    =    { 0xff, 0x01, 0x01, 0x0e, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=14，位置0度
unsigned char DM1_Speed15_Position_0[15]    =    { 0xff, 0x01, 0x01, 0x0f, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=15，位置0度
unsigned char DM1_Speed16_Position_0[15]    =    { 0xff, 0x01, 0x01, 0x10, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=16，位置0度
unsigned char DM1_Speed17_Position_0[15]    =    { 0xff, 0x01, 0x01, 0x11, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=17，位置0度
unsigned char DM1_Speed18_Position_0[15]    =    { 0xff, 0x01, 0x01, 0x12, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=18，位置0度
unsigned char DM1_Speed19_Position_0[15]    =    { 0xff, 0x01, 0x01, 0x13, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=19，位置0度
unsigned char DM1_Speed20_Position_0[15]    =    { 0xff, 0x01, 0x01, 0x14, 0x00, 0xff, 0x02, 0x01, 0xf4, 0x01 };  //通道1，速度=20，位置0度
                                            
                                            
unsigned char DM2_Speed1_Position_90[15]    =    { 0xff, 0x01, 0x02, 0x01, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=1，位置90度
unsigned char DM2_Speed2_Position_90[15]    =    { 0xff, 0x01, 0x02, 0x02, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=2，位置90度
unsigned char DM2_Speed3_Position_90[15]    =    { 0xff, 0x01, 0x02, 0x03, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=3，位置90度
unsigned char DM2_Speed4_Position_90[15]    =    { 0xff, 0x01, 0x02, 0x04, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=4，位置90度
unsigned char DM2_Speed5_Position_90[15]    =    { 0xff, 0x01, 0x02, 0x05, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=5，位置90度
unsigned char DM2_Speed6_Position_90[15]    =    { 0xff, 0x01, 0x02, 0x06, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=6，位置90度
unsigned char DM2_Speed7_Position_90[15]    =    { 0xff, 0x01, 0x02, 0x07, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=7，位置90度
unsigned char DM2_Speed8_Position_90[15]    =    { 0xff, 0x01, 0x02, 0x08, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=8，位置90度
unsigned char DM2_Speed9_Position_90[15]    =    { 0xff, 0x01, 0x02, 0x09, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=9，位置90度
unsigned char DM2_Speed10_Position_90[15]   =    { 0xff, 0x01, 0x02, 0x0a, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=10，位置90度
unsigned char DM2_Speed11_Position_90[15]   =    { 0xff, 0x01, 0x02, 0x0b, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=11，位置90度
unsigned char DM2_Speed12_Position_90[15]   =    { 0xff, 0x01, 0x02, 0x0c, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=12，位置90度
unsigned char DM2_Speed13_Position_90[15]   =    { 0xff, 0x01, 0x02, 0x0d, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=13，位置90度
unsigned char DM2_Speed14_Position_90[15]   =    { 0xff, 0x01, 0x02, 0x0e, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=14，位置90度
unsigned char DM2_Speed15_Position_90[15]   =    { 0xff, 0x01, 0x02, 0x0f, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=15，位置90度
unsigned char DM2_Speed16_Position_90[15]   =    { 0xff, 0x01, 0x02, 0x10, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=16，位置90度
unsigned char DM2_Speed17_Position_90[15]   =    { 0xff, 0x01, 0x02, 0x11, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=17，位置90度
unsigned char DM2_Speed18_Position_90[15]   =    { 0xff, 0x01, 0x02, 0x12, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=18，位置90度
unsigned char DM2_Speed19_Position_90[15]   =    { 0xff, 0x01, 0x02, 0x13, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=19，位置90度
unsigned char DM2_Speed20_Position_90[15]   =    { 0xff, 0x01, 0x02, 0x14, 0x00, 0xff, 0x02, 0x02, 0xdc, 0x05 };  //通道2，速度=20，位置90度
 

unsigned char DM2_Speed1_Position_0[15]     =    { 0xff, 0x01, 0x02, 0x01, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=1，位置0度
unsigned char DM2_Speed2_Position_0[15]     =    { 0xff, 0x01, 0x02, 0x02, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=2，位置0度
unsigned char DM2_Speed3_Position_0[15]     =    { 0xff, 0x01, 0x02, 0x03, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=3，位置0度
unsigned char DM2_Speed4_Position_0[15]     =    { 0xff, 0x01, 0x02, 0x04, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=4，位置0度
unsigned char DM2_Speed5_Position_0[15]     =    { 0xff, 0x01, 0x02, 0x05, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=5，位置0度
unsigned char DM2_Speed6_Position_0[15]     =    { 0xff, 0x01, 0x02, 0x06, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=6，位置0度
unsigned char DM2_Speed7_Position_0[15]     =    { 0xff, 0x01, 0x02, 0x07, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=7，位置0度
unsigned char DM2_Speed8_Position_0[15]     =    { 0xff, 0x01, 0x02, 0x08, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=8，位置0度
unsigned char DM2_Speed9_Position_0[15]     =    { 0xff, 0x01, 0x02, 0x09, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=9，位置0度
unsigned char DM2_Speed10_Position_0[15]    =    { 0xff, 0x01, 0x02, 0x0a, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=10，位置0度
unsigned char DM2_Speed11_Position_0[15]    =    { 0xff, 0x01, 0x02, 0x0b, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=11，位置0度
unsigned char DM2_Speed12_Position_0[15]    =    { 0xff, 0x01, 0x02, 0x0c, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=12，位置0度
unsigned char DM2_Speed13_Position_0[15]    =    { 0xff, 0x01, 0x02, 0x0d, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=13，位置0度
unsigned char DM2_Speed14_Position_0[15]    =    { 0xff, 0x01, 0x02, 0x0e, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=14，位置0度
unsigned char DM2_Speed15_Position_0[15]    =    { 0xff, 0x01, 0x02, 0x0f, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=15，位置0度
unsigned char DM2_Speed16_Position_0[15]    =    { 0xff, 0x01, 0x02, 0x10, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=16，位置0度
unsigned char DM2_Speed17_Position_0[15]    =    { 0xff, 0x01, 0x02, 0x11, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=17，位置0度
unsigned char DM2_Speed18_Position_0[15]    =    { 0xff, 0x01, 0x02, 0x12, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=18，位置0度
unsigned char DM2_Speed19_Position_0[15]    =    { 0xff, 0x01, 0x02, 0x13, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=19，位置0度
unsigned char DM2_Speed20_Position_0[15]    =    { 0xff, 0x01, 0x02, 0x14, 0x00, 0xff, 0x02, 0x02, 0xf4, 0x01 };  //通道2，速度=20，位置0度
                                            
                                            
unsigned char DM3_Speed10_Position_90[15]   =    { 0xff, 0x01, 0x03, 0x0a, 0x00, 0xff, 0x02, 0x03, 0xdc, 0x05 };  //通道3，速度=10，位置90度
unsigned char DM3_Speed20_Position_90[15]   =    { 0xff, 0x01, 0x03, 0x14, 0x00, 0xff, 0x02, 0x03, 0xdc, 0x05 };  //通道3，速度=20，位置90度
                                            
unsigned char DM3_Speed10_Position_0[15]    =    { 0xff, 0x01, 0x03, 0x0a, 0x00, 0xff, 0x02, 0x03, 0xf4, 0x01 };  //通道3，速度=10，位置0度
unsigned char DM3_Speed20_Position_0[15]    =    { 0xff, 0x01, 0x03, 0x14, 0x00, 0xff, 0x02, 0x03, 0xf4, 0x01 };  //通道3，速度=20，位置0度
                                            
                                            
unsigned char DM4_Speed10_Position_90[15]   =    { 0xff, 0x01, 0x04, 0x0a, 0x00, 0xff, 0x02, 0x04, 0xdc, 0x05 };  //通道4，速度=10，位置90度
unsigned char DM4_Speed20_Position_90[15]   =    { 0xff, 0x01, 0x04, 0x14, 0x00, 0xff, 0x02, 0x04, 0xdc, 0x05 };  //通道4，速度=20，位置90度
                                                                                                                          
unsigned char DM4_Speed10_Position_0[15]    =    { 0xff, 0x01, 0x04, 0x0a, 0x00, 0xff, 0x02, 0x04, 0xf4, 0x01 };  //通道4，速度=10，位置0度
unsigned char DM4_Speed20_Position_0[15]    =    { 0xff, 0x01, 0x04, 0x14, 0x00, 0xff, 0x02, 0x04, 0xf4, 0x01 };  //通道4，速度=20，位置0度
                                            
                                            
unsigned char DM5_Speed10_Position_90[15]   =    { 0xff, 0x01, 0x05, 0x0a, 0x00, 0xff, 0x02, 0x05, 0xdc, 0x05 };  //通道5，速度=10，位置90度
unsigned char DM5_Speed20_Position_90[15]   =    { 0xff, 0x01, 0x05, 0x14, 0x00, 0xff, 0x02, 0x05, 0xdc, 0x05 };  //通道5，速度=20，位置90度
                                                                                                                           
unsigned char DM5_Speed10_Position_0[15]    =    { 0xff, 0x01, 0x05, 0x0a, 0x00, 0xff, 0x02, 0x05, 0xf4, 0x01 };  //通道5，速度=10，位置0度
unsigned char DM5_Speed20_Position_0[15]    =    { 0xff, 0x01, 0x05, 0x14, 0x00, 0xff, 0x02, 0x05, 0xf4, 0x01 };  //通道5，速度=20，位置0度
                                            
                                            
unsigned char DM6_Speed10_Position_90[15]   =    { 0xff, 0x01, 0x06, 0x0a, 0x00, 0xff, 0x02, 0x06, 0xdc, 0x05 };  //通道6，速度=10，位置90度
unsigned char DM6_Speed20_Position_90[15]   =    { 0xff, 0x01, 0x06, 0x14, 0x00, 0xff, 0x02, 0x06, 0xdc, 0x05 };  //通道6，速度=20，位置90度
                                                                                                                           
unsigned char DM6_Speed10_Position_0[15]    =    { 0xff, 0x01, 0x06, 0x0a, 0x00, 0xff, 0x02, 0x06, 0xf4, 0x01 };  //通道6，速度=10，位置0度
unsigned char DM6_Speed20_Position_0[15]    =    { 0xff, 0x01, 0x06, 0x14, 0x00, 0xff, 0x02, 0x06, 0xf4, 0x01 };  //通道6，速度=20，位置0度
                                            
                                            
unsigned char DM7_Speed10_Position_90[15]   =    { 0xff, 0x01, 0x07, 0x0a, 0x00, 0xff, 0x02, 0x07, 0xdc, 0x05 };  //通道7，速度=10，位置90度
unsigned char DM7_Speed20_Position_90[15]   =    { 0xff, 0x01, 0x07, 0x14, 0x00, 0xff, 0x02, 0x07, 0xdc, 0x05 };  //通道7，速度=20，位置90度
                                                                                                                           
unsigned char DM7_Speed10_Position_0[15]    =    { 0xff, 0x01, 0x07, 0x0a, 0x00, 0xff, 0x02, 0x07, 0xf4, 0x01 };  //通道7，速度=10，位置0度
unsigned char DM7_Speed20_Position_0[15]    =    { 0xff, 0x01, 0x07, 0x14, 0x00, 0xff, 0x02, 0x07, 0xf4, 0x01 };  //通道7，速度=20，位置0度
                                            
                                            
unsigned char DM8_Speed10_Position_90[15]   =    { 0xff, 0x01, 0x08, 0x0a, 0x00, 0xff, 0x02, 0x08, 0xdc, 0x05 };  //通道8，速度=10，位置90度
unsigned char DM8_Speed20_Position_90[15]   =    { 0xff, 0x01, 0x08, 0x14, 0x00, 0xff, 0x02, 0x08, 0xdc, 0x05 };  //通道8，速度=20，位置90度
                                                                                                                           
unsigned char DM8_Speed10_Position_0[15]    =    { 0xff, 0x01, 0x08, 0x0a, 0x00, 0xff, 0x02, 0x08, 0xf4, 0x01 };  //通道8，速度=10，位置0度
unsigned char DM8_Speed20_Position_0[15]    =    { 0xff, 0x01, 0x08, 0x14, 0x00, 0xff, 0x02, 0x08, 0xf4, 0x01 };  //通道8，速度=20，位置0度
                                            
                                            
unsigned char DM9_Speed10_Position_90[15]   =    { 0xff, 0x01, 0x09, 0x0a, 0x00, 0xff, 0x02, 0x09, 0xdc, 0x05 };  //通道9，速度=10，位置90度
unsigned char DM9_Speed20_Position_90[15]   =    { 0xff, 0x01, 0x09, 0x14, 0x00, 0xff, 0x02, 0x09, 0xdc, 0x05 };  //通道9，速度=20，位置90度
                                                                                                                           
unsigned char DM9_Speed10_Position_0[15]    =    { 0xff, 0x01, 0x09, 0x0a, 0x00, 0xff, 0x02, 0x09, 0xf4, 0x01 };  //通道9，速度=10，位置0度
unsigned char DM9_Speed20_Position_0[15]    =    { 0xff, 0x01, 0x09, 0x14, 0x00, 0xff, 0x02, 0x09, 0xf4, 0x01 };  //通道9，速度=20，位置0度


unsigned char DM10_Speed10_Position_90[15]  =    { 0xff, 0x01, 0x0a, 0x0a, 0x00, 0xff, 0x02, 0x0a, 0xdc, 0x05 };  //通道10，速度=10，位置90度
unsigned char DM10_Speed20_Position_90[15]  =    { 0xff, 0x01, 0x0a, 0x14, 0x00, 0xff, 0x02, 0x0a, 0xdc, 0x05 };  //通道10，速度=20，位置90度
                                                                                                                           
unsigned char DM10_Speed10_Position_0[15]   =    { 0xff, 0x01, 0x0a, 0x0a, 0x00, 0xff, 0x02, 0x0a, 0xf4, 0x01 };  //通道10，速度=10，位置0度
unsigned char DM10_Speed20_Position_0[15]   =    { 0xff, 0x01, 0x0a, 0x14, 0x00, 0xff, 0x02, 0x0a, 0xf4, 0x01 };  //通道10，速度=20，位置0度


unsigned char DM11_Speed10_Position_90[15]  =    { 0xff, 0x01, 0x0b, 0x0a, 0x00, 0xff, 0x02, 0x0b, 0xdc, 0x05 };  //通道11，速度=10，位置90度
unsigned char DM11_Speed20_Position_90[15]  =    { 0xff, 0x01, 0x0b, 0x14, 0x00, 0xff, 0x02, 0x0b, 0xdc, 0x05 };  //通道11，速度=20，位置90度
                                                                                                                           
unsigned char DM11_Speed10_Position_0[15]   =    { 0xff, 0x01, 0x0b, 0x0a, 0x00, 0xff, 0x02, 0x0b, 0xf4, 0x01 };  //通道11，速度=10，位置0度
unsigned char DM11_Speed20_Position_0[15]   =    { 0xff, 0x01, 0x0b, 0x14, 0x00, 0xff, 0x02, 0x0b, 0xf4, 0x01 };  //通道11，速度=20，位置0度


unsigned char DM12_Speed10_Position_90[15]  =    { 0xff, 0x01, 0x0c, 0x0a, 0x00, 0xff, 0x02, 0x0c, 0xdc, 0x05 };  //通道12，速度=10，位置90度
unsigned char DM12_Speed20_Position_90[15]  =    { 0xff, 0x01, 0x0c, 0x14, 0x00, 0xff, 0x02, 0x0c, 0xdc, 0x05 };  //通道12，速度=20，位置90度
                                                                                                                           
unsigned char DM12_Speed10_Position_0[15]   =    { 0xff, 0x01, 0x0c, 0x0a, 0x00, 0xff, 0x02, 0x0c, 0xf4, 0x01 };  //通道12，速度=10，位置0度
unsigned char DM12_Speed20_Position_0[15]   =    { 0xff, 0x01, 0x0c, 0x14, 0x00, 0xff, 0x02, 0x0c, 0xf4, 0x01 };  //通道12，速度=20，位置0度


unsigned char DM13_Speed10_Position_90[15]  =    { 0xff, 0x01, 0x0d, 0x0a, 0x00, 0xff, 0x02, 0x0d, 0xdc, 0x05 };  //通道13，速度=10，位置90度
unsigned char DM13_Speed20_Position_90[15]  =    { 0xff, 0x01, 0x0d, 0x14, 0x00, 0xff, 0x02, 0x0d, 0xdc, 0x05 };  //通道13，速度=20，位置90度
                                                                                                                           
unsigned char DM13_Speed10_Position_0[15]   =    { 0xff, 0x01, 0x0d, 0x0a, 0x00, 0xff, 0x02, 0x0d, 0xf4, 0x01 };  //通道13，速度=10，位置0度
unsigned char DM13_Speed20_Position_0[15]   =    { 0xff, 0x01, 0x0d, 0x14, 0x00, 0xff, 0x02, 0x0d, 0xf4, 0x01 };  //通道13，速度=20，位置0度


unsigned char DM14_Speed10_Position_90[15]  =    { 0xff, 0x01, 0x0e, 0x0a, 0x00, 0xff, 0x02, 0x0e, 0xdc, 0x05 };  //通道14，速度=10，位置90度
unsigned char DM14_Speed20_Position_90[15]  =    { 0xff, 0x01, 0x0e, 0x14, 0x00, 0xff, 0x02, 0x0e, 0xdc, 0x05 };  //通道14，速度=20，位置90度
                                                                                                                           
unsigned char DM14_Speed10_Position_0[15]   =    { 0xff, 0x01, 0x0e, 0x0a, 0x00, 0xff, 0x02, 0x0e, 0xf4, 0x01 };  //通道14，速度=10，位置0度
unsigned char DM14_Speed20_Position_0[15]   =    { 0xff, 0x01, 0x0e, 0x14, 0x00, 0xff, 0x02, 0x0e, 0xf4, 0x01 };  //通道14，速度=20，位置0度


unsigned char DM15_Speed10_Position_90[15]  =    { 0xff, 0x01, 0x0f, 0x0a, 0x00, 0xff, 0x02, 0x0f, 0xdc, 0x05 };  //通道15，速度=10，位置90度
unsigned char DM15_Speed20_Position_90[15]  =    { 0xff, 0x01, 0x0f, 0x14, 0x00, 0xff, 0x02, 0x0f, 0xdc, 0x05 };  //通道15，速度=20，位置90度
                                                                                                                           
unsigned char DM15_Speed10_Position_0[15]   =    { 0xff, 0x01, 0x0f, 0x0a, 0x00, 0xff, 0x02, 0x0f, 0xf4, 0x01 };  //通道15，速度=10，位置0度
unsigned char DM15_Speed20_Position_0[15]   =    { 0xff, 0x01, 0x0f, 0x14, 0x00, 0xff, 0x02, 0x0f, 0xf4, 0x01 };  //通道15，速度=20，位置0度



动作组
unsigned char DM_Action0[5]   = { 0xff, 0x09, 0x00, 0x00, 0x00 };               //动作组0
unsigned char DM_Action1[5]   = { 0xff, 0x09, 0x00, 0x01, 0x00 };               //动作组1
unsigned char DM_Action2[5]   = { 0xff, 0x09, 0x00, 0x02, 0x00 };               //动作组2
unsigned char DM_Action3[5]   = { 0xff, 0x09, 0x00, 0x03, 0x00 };               //动作组3
unsigned char DM_Action4[5]   = { 0xff, 0x09, 0x00, 0x04, 0x00 };               //动作组4
unsigned char DM_Action5[5]   = { 0xff, 0x09, 0x00, 0x05, 0x00 };               //动作组5
unsigned char DM_Action6[5]   = { 0xff, 0x09, 0x00, 0x06, 0x00 };               //动作组6
unsigned char DM_Action7[5]   = { 0xff, 0x09, 0x00, 0x07, 0x00 };               //动作组7
unsigned char DM_Action8[5]   = { 0xff, 0x09, 0x00, 0x08, 0x00 };               //动作组8
unsigned char DM_Action9[5]   = { 0xff, 0x09, 0x00, 0x09, 0x00 };               //动作组9
unsigned char DM_Action10[5]  = { 0xff, 0x09, 0x00, 0x0a, 0x00 };               //动作组a
unsigned char DM_Action11[5]  = { 0xff, 0x09, 0x00, 0x0b, 0x00 };               //动作组b
unsigned char DM_Action12[5]  = { 0xff, 0x09, 0x00, 0x0c, 0x00 };               //动作组c
unsigned char DM_Action13[5]  = { 0xff, 0x09, 0x00, 0x0d, 0x00 };               //动作组d
unsigned char DM_Action14[5]  = { 0xff, 0x09, 0x00, 0x0e, 0x00 };               //动作组e
unsigned char DM_Action15[5]  = { 0xff, 0x09, 0x00, 0x0f, 0x00 };               //动作组f
*/