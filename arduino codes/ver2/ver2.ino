
#include <Servo.h>

Servo myservo;
byte val;
int armspeed =30;

void myArm(){
  int speed;
  
  for(speed = 0; speed <= 100; speed+= 1)
  {
    setSpeed(speed);
    delay(100);
    
  }
  setSpeed(30);
  delay(1000);
  
  for(speed = 100; speed >0; speed -=1)
  {
    setSpeed(speed);    
    delay(100);
  }
  
  //Serial.println("30 halting...");
  setSpeed(30);
}

void setSpeed(int speed)
{
  // speed is from 0 to 100 where 0 is off and 100 is max speed
  // the following maps speed values of 0-100 to angles from 0-180
  int angle = map(speed, 0, 100, 0, 180);
  //Serial.println();
  //Serial.write("Speed changed to =");
  Serial.println(angle);
  Serial.println();
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
    val=int(Serial.read());
    //Serial.println(val);
    setSpeed(val);
  }
}
