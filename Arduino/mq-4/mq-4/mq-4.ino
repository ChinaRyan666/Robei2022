const int ledRedPin = 13;
const int ledGreenPin = 12;
const int analogPin = A0;
const int digitalPin = 7;
const int sound = 11;
int Astate = 0;
boolean  Dstate = 0;
void setup()
{
  pinMode (digitalPin, INPUT);
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(sound, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  Astate = analogRead(analogPin);
  Serial.println(Astate);
  Dstate = digitalRead(digitalPin);
  Serial.println(Dstate);
  if ( Dstate == HIGH )
  {
    digitalWrite(ledRedPin, LOW);
    digitalWrite(ledGreenPin, HIGH);
    //停止发声
    noTone(sound);
  }
  if ( Dstate == LOW)
  {

    digitalWrite(ledGreenPin, LOW);
    digitalWrite(ledRedPin, HIGH);
    for (int i = 200; i <= 800; i++)
    {
      tone(sound, i);
      delay(5);
    }
  }
  delay(200);
}
