int gas_din=2;
int gas_ain=A0;
int ad_value;
void setup()
{
  pinMode(gas_din,INPUT);
  pinMode(gas_ain,INPUT);
  Serial.begin(9600);
}
void loop()
{
  ad_value=analogRead(gas_ain);
  if(digitalRead(gas_din)==LOW)
  {
    Serial.println("Gas leakage");
    Serial.println(ad_value);
  }
  else
  {
    Serial.println("Gas not leak");
  }
  delay(500);
}
