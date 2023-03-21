#include <TimerOne.h>
#include <string.h>
#define Success 1U
#define Failure 0U

const unsigned int bufferLength=600;
char RxBuffer[bufferLength];
unsigned int ii=0;
int L = 13;

const char datastreams_id[]="GPS_Data";//-------------------------设置转发名称
const char device_id[]="510498";//----------------------------------修改此处为"设备ID"
const char api_key[] ="7S0gNWc43T=5wvGJxgbPJVYthPY=";//--修改此处为"设备APIKey"
struct
{
unsigned char CMD;
unsigned int LengthA;
char fixed[20];
unsigned char id_length;
char id[20];
unsigned char LengthB1;
unsigned char LengthB2;
char api_key[50];
}login;

struct
{
unsigned char CMD;
unsigned char LengthA;
unsigned char mark;
unsigned char type;
unsigned char LengthB1;
unsigned char LengthB2;
char streamA[24];
char id[20];
char streamB[27];
char GPS_Buffer[150];
char streamC[7];
}Save_Data;

unsigned char mystrstr(char *s,char *t,unsigned int Length_s,unsigned int Length_t)
{        char x=0;char *p;p=t;
int i=0,j=0;
for(;i < Length_s; s++,i++)
            {  
          while(*t == *s)
              {  s++;t++;i++;j++;   
                 if (j>= Length_t) return 1;
              }
              s-=j;
              t=p;j=0;
                }
        return NULL;
}
void clrRxBuffer(void)
{
  memset(RxBuffer,0,bufferLength);
  ii=0;
}

void SIM808_ERROR(void)
{
  while(1)
  {
  digitalWrite(L, HIGH);
  delay(300);
  digitalWrite(L, LOW);
  delay(300);
  }
}

unsigned long  Time_Cont=0;
void Timer1_handler(void)
{
Time_Cont++;
}

unsigned int Send_Command(char *Command,char *Response,unsigned int Res_Length,unsigned long Timeout,unsigned char Retry)
{
  clrRxBuffer();
  for(unsigned char n=0;n<Retry;n++)
  {
  Serial.write(Command);
  Serial.write("\r\n");
  Time_Cont=0;
  while(Time_Cont<Timeout)
  {
    readBuffer();
    if((mystrstr(RxBuffer,Response,ii,Res_Length))!=NULL)
    {
      clrRxBuffer();
      return Success;
    }
   }
  Time_Cont=0;
  }
  clrRxBuffer();
  return Failure;
}

char EER_GPS_Buffer[24]={"$GPRMC,,V,,,,,,,,,,N*7F"};
int GET_GPS(void)
{ char *GPS_BufferHead,*GPS_BufferTail;

clrRxBuffer();
  if(Send_Command("AT+CGNSTST=1","OK",2,3000,5)==Success);
   Time_Cont=0;
  while(Time_Cont<5000)
  {
    readBuffer();

   if((GPS_BufferHead = strstr(RxBuffer, "$GPRMC,")) != NULL)
  {
    if(((GPS_BufferTail = strstr(GPS_BufferHead,"\r\n")) != NULL)&&(GPS_BufferTail >GPS_BufferHead)){
      memcpy(Save_Data.GPS_Buffer,GPS_BufferHead,GPS_BufferTail-GPS_BufferHead);
    clrRxBuffer();
    break;
    }
  }
  memcpy(Save_Data.GPS_Buffer,EER_GPS_Buffer,24);
  }
   Time_Cont=0;
    clrRxBuffer();
     if(Send_Command("AT+CGNSTST=0","OK",2,5000,10)==Success) ;
}

void SIM808_Initialization()
{
   if(Send_Command("AT","OK",2,3000,10)==Success);
   else SIM808_ERROR();

if(Send_Command("ATE0","OK",2,3000,10)==Success);
else SIM808_ERROR();

if(Send_Command("AT+CREG?","+CREG: 0,1",10,2000,20)==Success);
else SIM808_ERROR();

if(Send_Command("AT+CGREG?","+CGREG: 0,1",11,2000,20)==Success);
else SIM808_ERROR();
}


void SIM808_BOOT()
{
   if(Send_Command("AT","OK",2,100,5)==Success) return;
else
{
   digitalWrite(12, HIGH);
if(Send_Command("AT","OK",2,1000,20)==Success) {digitalWrite(12, LOW);return;}
else
{
   digitalWrite(12, LOW);
   SIM808_ERROR();
}
}
}

void Process_Save_Data()
{
}

void setup()
{
  Serial.begin(115200);
  pinMode(L, OUTPUT);
  pinMode(12, OUTPUT);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(Timer1_handler); // blinkLED to run every 1ms
  delay(5000);
digitalWrite(L, HIGH);


  SIM808_BOOT();

SIM808_Initialization();
if(Send_Command("AT+CGNSPWR=1","OK",2,3000,2)==Success) ;
else SIM808_ERROR();
}

const char data[]={0x00,0x03,0x45,0x44,0x50,0x01,0x40,0x01,0x00,0x00};
char response[]={0x20,0x02,0x00,0x00};
char responseX[]={0x0D,0x0A,0x20,0x02,0x00,0x00,0x0D,0x0A,0x3E,0x20};

void loop()
{
GET_GPS();

if(Send_Command("AT+CIPSTART=\"TCP\",\"183.230.40.39\",\"876\"","CONNECT",7,10000,2)==Success);//Serial.write("BinGo......AT+CIPSTART=\"TCP\"\r\n");

if(Send_Command("AT+CIPSEND",">",1,3000,2)==Success);// Serial.write("BinGo......AT+CIPSEND\r\n");

login.CMD=0x10;
login.id_length=strlen(device_id);

for(unsigned char i=0;i<10;i++)
{
strcpy(login.fixed , data);
}
strcpy(login.id,device_id);


login.LengthB1=0x00;
login.LengthB2=strlen(api_key);
strcpy(login.api_key,api_key);
login.LengthA=login.LengthB2+login.id_length+13;

Serial.write(login.CMD);
Serial.write(login.LengthA);
for(unsigned char i=0;i<10;i++)
{
Serial.write(login.fixed);
}
Serial.write(login.id_length);
Serial.write(login.id);
Serial.write(login.LengthB1);
Serial.write(login.LengthB2);
Serial.write(login.api_key);
if(Send_Command("32",response,sizeof(response)/sizeof(char),3000,1)==Success);
if(Send_Command("AT+CIPSEND",">",1,2000,1)==Success);


Save_Data.CMD=0X80;
Save_Data.mark=0x00;
Save_Data.type=0x01;
Save_Data.LengthB1=0x00;
strcpy(Save_Data.streamA,"{\"datastreams\":[{\"id\":\"");
strcpy(Save_Data.id,datastreams_id);
strcpy(Save_Data.streamB,"\",\"datapoints\":[{\"value\":\"");
strcpy(Save_Data.streamC,"\"}]}]}");

Save_Data.LengthB2=strlen((const char *)Save_Data.streamA)+strlen(datastreams_id)+strlen((const char *)Save_Data.streamB)+strlen((const char *)Save_Data.GPS_Buffer)+strlen((const char *)Save_Data.streamC);
Save_Data.LengthA=Save_Data.LengthB2+4;

Serial.write(Save_Data.CMD);
Serial.write(Save_Data.LengthA);
if(Save_Data.LengthA>127)Serial.write(0x01);
Serial.write(Save_Data.mark);
Serial.write(Save_Data.type);
Serial.write(Save_Data.LengthB1);
Serial.write(Save_Data.LengthB2);
Serial.write(Save_Data.streamA);
Serial.write(Save_Data.id);
Serial.write(Save_Data.streamB);
Serial.write(Save_Data.GPS_Buffer);
Serial.write(Save_Data.streamC);
if(Send_Command("32","SEND OK",7,3000,1)==Success);

memset(Save_Data.GPS_Buffer, 0, sizeof Save_Data.GPS_Buffer);
clrRxBuffer();

if(Send_Command("AT+CIPCLOSE","CLOSE OK",8,1000,1)==Success);
clrRxBuffer();

  digitalWrite(L, HIGH);
  delay(300);
  digitalWrite(L, LOW);
}
void readBuffer()
{
  while(Serial.available())
        {
         RxBuffer[ii++]=Serial.read();
         if(ii==bufferLength)clrRxBuffer();
         }
}
