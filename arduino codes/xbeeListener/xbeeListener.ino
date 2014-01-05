int ledPin=13;
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
}

void loop()
{
  while (Serial.available()==0);
  byte val=Serial.read();  
  Serial.println(val);
  //Serial.println(val,HEX);
}
