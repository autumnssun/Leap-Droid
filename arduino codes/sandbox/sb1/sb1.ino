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
  /*int val=Serial.read()-"0";  
  if(val==1){
     Serial.println("The LED in ON");
     digitalWrite(ledPin,HIGH);
  }
  else if(val==0){
    Serial.println("The LED in OFF");
    digitalWrite(ledPin,LOW);
  }else{
    Serial.println("Invalid");
  }
  */
  //while (Serial.available()>0);
  Serial.println(Serial.read(),HEX);
  
  //Serial.println(val,HEX);
}
