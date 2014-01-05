
#include <Servo.h>

Servo myservo;
byte val;
int armspeed =30;

void myArm(){
  int speed;
  
  for(speed = 37; speed <= 100; speed+= 1)
  {
    
    setSpeed(speed);
    Serial.println(speed);
    delay(100);
    
  }
  
  setSpeed(30);
  delay(1000);
  
  for(speed = 90; speed >37; speed -=1)
  {
    
    setSpeed(speed);
    
    Serial.println(speed);
    delay(100);
    
  }
  
  Serial.println("30 halting...");
  setSpeed(30);
  delay(5000);
}

void setSpeed(int speed)
{
  // speed is from 0 to 100 where 0 is off and 100 is max speed
  // the following maps speed values of 0-100 to angles from 0-180
  int angle = map(speed, 0, 100, 0, 360);
  Serial.write("speed=");
  Serial.println(angle);
  myservo.write(angle);
  
}

void setup()
{
  Serial.begin(9600);
  myservo.attach(9);
  myArm();
}

void loop()
{
  
  if(Serial.available()>0){
    val=Serial.read();
    
    
    setSpeed((val));
    Serial.println(val);
  }
  /*
  int speed;
  
  Serial.println("Sweeping up");
  for(speed = 37; speed <= 100; speed+= 1)
  {
    
    setSpeed(speed);
    Serial.println(speed);
    delay(100);
    
  }
  
  setSpeed(30);
  delay(1000);
  
  Serial.println("Sweeping down");
  for(speed = 90; speed >37; speed -=1)
  {
    
    setSpeed(speed);
    Serial.println(speed);
    delay(100);
    
  }
  
  Serial.println("30 halting...");
  setSpeed(30);
  delay(5000);
  */
}
