/*
 *PROJECT: LEAPDROID 
 *PLATFORM PROCESSING
 *STATE: PROTOTYPING
 *--------------------------------------
 *PROCESSING code version 2
 *Description:
 *Capturing leapmotion sensor then compute
 *speed for each rotor then send it over the Xbee
 *the speed should be between 0 and 180. 
 *data format: {180,100,50,0}
 *each individual number in the object should be between 0 and 180
 *TODO:Listen to confirmation data.
*/

/*PROPOSE INTERACTION PLAN
 *There are two mode to operate the droid:
 *TWO HAND MODE. 
 *ONE HAND MODE.
*/

import com.onformative.leap.LeapMotionP5;
import com.leapmotion.leap.*;
import processing.serial.*;
import java.util.Date;
LeapMotionP5 leap;
Serial port;// Serial port of the xbee object.

//Status variables
boolean inSync;

public void setup() {
  //size(1000, 500,P3D);// set up the window with P3D mode
  //leap = new LeapMotionP5(this);
  //port = new Serial(this,"/dev/tty.usbserial-A101LY3X", 9600);
  
  sync();
}


public void draw() {  
  background(0);
  fill(255);
}

public void stop() {
  leap.stop();
}

public void sync(){
  Date d = new Date();
  long current = d.getTime()/1000;
  Serial.print("{nock,nock}");
}

public void renderFinger(){
  for (Finger f : leap.getFingerList()) {
    PVector position = leap.getTip(f);
    PVector velocity = leap.getVelocity(f);
    ellipse(position.x, position.y, 10, 10);
    line(position.x, position.y, position.x + velocity.x, position.y + velocity.y);
  }
}

public void renderHand(){
  //println(leap.getHandList().length());
  for (Hand hand : leap.getHandList()) {
      pushMatrix();
      PVector handPosition = leap.getPosition(hand);
      translate(handPosition.x, handPosition.y,handPosition.z);
      //println("PosX"+handPosition.x);
      //println("PosY"+handPosition.y);
      //println("PosZ"+handPosition.z);
      float pitch = leap.getPitch(hand);
      float roll = leap.getRoll(hand);
      float yaw = leap.getYaw(hand);
      
      rotateX(radians(map(pitch, -30, 30, 45, -45)));
      rotateY(radians(map(yaw, -12, 18, 45, -45)));
      rotateZ(radians(map(roll, -40, 40, 45, -45)));
      //float handSize = leap.getSphereRadius(hand);
      sphere(100);
      popMatrix();
       //myPort.write("{"+(int)handPosition.x+","+(int)handPosition.y+","+(int)handPosition.z+","+(int)yaw+"}");
   }
}
