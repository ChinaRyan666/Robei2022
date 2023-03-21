#define Sensor_AO A0
#define Sensor_DO 8
unsigned int sensorValue = 0;

void setup()
{
  pinMode(Sensor_DO, INPUT);
  Serial.begin(9600);
}
void loop()
{
    sensorValue = analogRead(Sensor_AO);
    Serial.print("Sensor AD Value = ");
    Serial.println(sensorValue);  //输出气体浓度模拟值
  if (digitalRead(Sensor_DO) == LOW)
  {
    Serial.println("Alarm!"); //低电平警报
  }
  delay(1000);
}
