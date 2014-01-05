#include <Servo.h>

// Variables declaration.
//
Servo myServo;
byte val;

void setup() {                
  Serial.begin(9600);
  myServo.attach(9);
  myArm();
}

// the loop routine runs over and over again forever:
void loop() {
  if(Serial.available()>0){
    val=int(Serial.read());
    Serial.println(val);    
  }
}



void myArm(){
  int speed;
  for(speed = 0; speed <= 100; speed+= 1){
    setSpeed(speed);
    delay(100);
  }
  delay(1000);  
  for(speed = 100; speed >0; speed -=1){
    setSpeed(speed);
    delay(100); 
  }

}

void setSpeed(int speed)
{
  // speed is from 0 to 100 where 0 is off and 100 is max speed
  // the following maps speed values of 0-100 to angles from 0-180
  int angle = map(speed, 0, 100, 0, 180);
  Serial.write("speed=");
  Serial.println(angle);
  myServo.write(angle);
  
}

