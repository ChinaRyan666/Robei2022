#include "XFS.h"          //封装好的命令库
#include "TextTab.h"      //中文需要放在该记事本中（因为编码不兼容）
#include "ASR.h"
#define  ZZFW  "$DKT:2,1!" //  中姿复位 W
#define  ZKSQJ  "$DKT:13,5!"
#define ZMSQJ "$DKT:17,0!"  //  中慢速前进
#define ZMSHT "$DKT:18,5!"  //  中慢速后退
#define ZMSZZ "$DKT:19,0!"  //  中慢速左转
#define ZMSYZ "$DKT:20,5!"  //  中慢速右转
#define STOP "$DST!"  //  中慢
#define  DZFW  "$DKT:1,1!" //  低姿复位
#define HNBS  "$DKT:41,1!"
const int TrigPin=5;       //设置发射脚位
const int EchoPin=3; 
float cm; 
/*实例化语音合成对象*/
XFS5152CE xfs;


/*超时设置，示例为30S*/
static uint32_t LastSpeakTime = 0;
#define SpeakTimeOut 10000
static const char *music[] = {"[x1]sound213","[x1]sound224","[x1]sound225","[x1]sound328","[x1]sound325"};

/**
    @brief  初始化语音合成
    @param  无
    @retval 无
*/

uint8_t n = 1;
static void XFS_Init()
{

  xfs.Begin(0x30);//设备i2c地址，地址为新版地址为0x30,旧版地址为0x50
  delay(n);
  xfs.SetReader(XFS5152CE::Reader_XiaoYan);        //设置发音人
  delay(n);
  xfs.SetEncodingFormat(XFS5152CE::GB2312);           //文本的编码格式
  delay(n);
    xfs.SetLanguage(xfs.Language_Auto);                 //语种判断
    delay(n);
    xfs.SetStyle(XFS5152CE::Style_Continue);            //合成风格设置
    delay(n);
    xfs.SetArticulation(XFS5152CE::Articulation_Letter);  //设置单词的发音方式
    delay(n);
    xfs.SetSpeed(5);                         //设置语速1~10
    delay(n);
    xfs.SetIntonation(5);                    //设置语调1~10
    delay(n);
    xfs.SetVolume(2);                        //设置音量1~10
    delay(n);
}

unsigned char result = 0xFF;
void setup()
{
 unsigned char cleck = 0xff;
  Serial.begin(115200);  //串口波特率设置，打印数据时串口需要选择和这里一样的波特率
  XFS_Init();

#if 1
    I2CWrite(ASR_CLEAR_ADDR,0x40);//清除掉电保存区,录入前需要清除掉电保存区
    BusyWait();
    I2CWrite(ASR_MODE_ADDR,1);//设置检测模式 
    BusyWait();
    AsrAddWords(0,"yi zhou");
    BusyWait();             
    AsrAddWords(1,"hong deng");
    BusyWait();   
    AsrAddWords(2,"lv deng");
    BusyWait();
    AsrAddWords(3,"lan deng");
    BusyWait();
    AsrAddWords(4,"guan deng");
    BusyWait();
    AsrAddWords(5,"bo fang yi hao ti shi yin");
    BusyWait();
    AsrAddWords(6,"bo fang er hao ti shi yin");
    BusyWait();
    AsrAddWords(7,"bo fang san hao ti shi yin");
    BusyWait();
    AsrAddWords(8,"bo fang si hao ti shi yin");
    BusyWait();
    AsrAddWords(9,"bo fang wu hao ti shi yin");
    BusyWait();
    AsrAddWords(10,"kai shi");
    BusyWait();
    AsrAddWords(11,"jie shu");//进行测距
    BusyWait();
    AsrAddWords(12,"qie huan bo yin ren xu duo");
    BusyWait();
    AsrAddWords(13,"qie huan bo yin ren xiao pin");
    BusyWait();
    AsrAddWords(14,"qie huan bo yin ren tan lao ya");
    BusyWait();
    AsrAddWords(15,"qie huan bo yin ren xu xiao bao");
    BusyWait();
    while(cleck != 16)
    {
      WireReadData(ASR_NUM_CLECK,&cleck,1);
      Serial.println(cleck);
      delay(100);
      } 
   
#endif
    I2CWrite(ASR_REC_GAIN,0x55);  //识别的灵敏度，建议0x40-0x55
    I2CWrite(ASR_VOICE_FLAG,1);  //识别结果提示音开关设置
    I2CWrite(ASR_BUZZER,1);  //开启蜂鸣器
    RGB_Set(255,255,255);//设置模块的RGB灯为白色
    delay(500);
    I2CWrite(ASR_BUZZER,0);  //关闭蜂鸣器
    RGB_Set(0,0,0);//关闭RGB灯 


    xfs.StartSynthesis(TextTab2[0]);
    while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
    {
       delay(30);
    }

}
void loop()
{
        unsigned char result;
        WireReadData(ASR_RESULT,&result,1);//读取识别序号值，并赋值给result，默认是0xff
        delay(100);
        Serial.println(result);

        if(result == 0)//沂舟
        {
            xfs.StartSynthesis(TextTab1[0]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {

               delay(30);
            }
        }
        else if(result == 1)//红灯
        {    Serial.println(result);

            xfs.StartSynthesis(TextTab1[1]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
               delay(30);
            }
        }
        else if(result == 2)//绿灯
        {
            xfs.StartSynthesis(TextTab1[2]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
               delay(30);
            }
        }
        else if(result == 3)//蓝灯
        {
            xfs.StartSynthesis(TextTab1[3]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
               delay(30);
            }
        }
        else if(result == 4)//关灯
        {
            xfs.StartSynthesis(TextTab1[4]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
               delay(30);
            }
        }
        else if(result == 5)//1号
        {
            xfs.StartSynthesis(music[0]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
             delay(30);
             }
          
            xfs.StartSynthesis(TextTab1[5]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
               delay(30);
            }
        }       
        else if(result == 6)//2号
        {
            xfs.StartSynthesis(music[1]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
             delay(30);
             }
             
            xfs.StartSynthesis(TextTab1[6]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
               delay(30);
            }
        }
        else if(result == 7)//3号
        {
            xfs.StartSynthesis(music[2]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
             delay(30);
             }
             
            xfs.StartSynthesis(TextTab1[7]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
               delay(30);
            }
        }
        else if(result == 8)//4号
        {
            xfs.StartSynthesis(music[3]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
             delay(30);
             }
             
            xfs.StartSynthesis(TextTab1[8]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
               delay(30);
            }
        }
        else if(result == 9)//5号
        {
            xfs.StartSynthesis(music[4]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
             delay(30);
             }
             
            xfs.StartSynthesis(TextTab1[9]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
               delay(30);
            }
        }
        else if(result == 10)
        {
             xfs.StartSynthesis(TextTab1[0]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {

               delay(30);
            }
       
           
          while(1)
          {  
      unsigned char result;
        WireReadData(ASR_RESULT,&result,1);//读取识别序号值，并赋值给result，默认是0xff
        delay(100);
        Serial.println(result); 
if(result==0)
        break;  
             while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {

               delay(30);
            } 
            digitalWrite(TrigPin,LOW);        //用低高低电平发送脉冲给Trigpin引脚$
           delayMicroseconds(2);             //微秒级延时
           digitalWrite(TrigPin,HIGH);
           delayMicroseconds(10);
           digitalWrite(TrigPin,LOW);
           cm=pulseIn(EchoPin,HIGH)/58.0;   
                         //float checkdistance_0_0();
              if(cm<40)
                {
                  unsigned char result;
        WireReadData(ASR_RESULT,&result,1);//读取识别序号值，并赋值给result，默认是0xff
        delay(100);
         
if(result==0)
        break;  
                  Serial.println(cm);
                   Serial.println(ZMSZZ);//"$DKT:19,0!"  //  中慢速左转
                    delay(3000); 
          
                }
Serial.println(cm);
  Serial.println(ZKSQJ);//"$DKT:13,5!"  //  中快速前进
         delay(1000);
         
          }
        }
        else if(result == 111)//许久
        {
         
          xfs.SetReader(XFS5152CE::Reader_XuJiu);        //设置发音人
          delay(n);
            xfs.StartSynthesis(TextTab1[11]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
               delay(30);
            }
        }  
        else if(result == 12)//许多
        {
          xfs.SetReader(XFS5152CE::Reader_XuDuo);        //设置发音人
          delay(n);
            xfs.StartSynthesis(TextTab1[12]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
               delay(30);
            }
        }             
        else if(result == 13)//小萍
        {
          xfs.SetReader(XFS5152CE::Reader_XiaoPing);        //设置发音人
          delay(n);
            xfs.StartSynthesis(TextTab1[13]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
               delay(30);
            }
        }   
        else if(result == 14)//唐老鸭
        {
          xfs.SetReader(XFS5152CE::Reader_DonaldDuck);        //设置发音人
          delay(n);
            xfs.StartSynthesis(TextTab1[14]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
               delay(30);
            }
        }  
        else if(result == 15)//许小宝
        {
          xfs.SetReader(XFS5152CE::Reader_XuXiaoBao);        //设置发音人
          delay(n);
            xfs.StartSynthesis(TextTab1[15]);
            while(xfs.GetChipStatus() != xfs.ChipStatus_Idle)
            {
               delay(30);
            }
        }  

}
