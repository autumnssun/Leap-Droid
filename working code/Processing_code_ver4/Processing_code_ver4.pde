/*
 *PROJECT: LEAPDROID 
 *PLATFORM PROCESSING
 *STATE: PROTOTYPING
 *--------------------------------------
 *PROCESSING code version 3
 *Description:
 *Capturing leapmotion sensor then compute
 *speed for each rotor then send it over the Xbee
 *the speed should be between 0 and 180. 
 *data format: {180,100,50,0}
 *each individual number in the object should be between 0 and 180
 *Listen to confirmation data, and greenlight signal
*/

/*PROPOSE INTERACTION PLAN
 *There are two mode to operate the droid:
 *ONE HAND MODE.
 *The high of the hand will control the hight of the 
 *droid, that mean it will control the speed of 4 rotors
*/


import com.onformative.leap.LeapMotionP5;
import com.leapmotion.leap.*;
import processing.serial.*;

LeapMotionP5 leap;
Serial port;// Serial port of the xbee object.

//Status variables
boolean droidReady;
int r1,r2,r3,r4;
int sensitivity=2;
boolean handPresented=false;

public void setup() {
  size(1000, 500,P3D);// set up the window with P3D mode
  //Set up the droid and the control interface here
  leap = new LeapMotionP5(this);
  port = new Serial(this,"/dev/tty.usbserial-A101LY3X", 9600);
}

public void draw() {  
  background(0);
  fill(255);
  handListener();
  renderHand();
}



public void stop() {
  leap.stop();
}


public void handListener(){
  if(leap.getHandList().size()>0){
    if (!handPresented){
      //save the intial coordinatel
      print("New hand position");
    }
    handPresented=true;
    
    Hand hand=leap.getHand(0);
    PVector handPosition = leap.getPosition(hand);
    //print(handPosition.y);
    int mapPosY=(int)map(handPosition.y, -40, 450,100,0);
    mapPosY=constrain(mapPosY,20,99);
    //println(" -> "+mapPosY+"...sending...");
    r1=r2=r3=r4=mapPosY;
    //port.write("{"+r1+","+r2+","+r3+","+r4+"}");
//    print("{"+r1+","+r2+","+r3+","+r4+"}");
    
    float pitch = leap.getPitch(hand);
    float roll = leap.getRoll(hand);
    float yaw = leap.getYaw(hand);
//    print(" | Pitch "+pitch);
//    print(" | Roll "+roll);
//    print(" | Yaw "+yaw);
    
  }
  else{
    if (!handPresented){
      handPresented=false;
      print("hand removed");
    }
    r1=r2=r3=r4=40;
  }
  println();
}

public void remoteListener(){
  while (port.available() >0) {
    String inBuffer = port.readString();   
    if (inBuffer != null) {
      println(inBuffer);
    }
  }
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
