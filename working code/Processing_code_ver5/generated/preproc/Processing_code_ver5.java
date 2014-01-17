import processing.core.*; 
import processing.xml.*; 

import com.onformative.leap.LeapMotionP5; 
import com.leapmotion.leap.*; 
import processing.serial.*; 

import java.applet.*; 
import java.awt.Dimension; 
import java.awt.Frame; 
import java.awt.event.MouseEvent; 
import java.awt.event.KeyEvent; 
import java.awt.event.FocusEvent; 
import java.awt.Image; 
import java.io.*; 
import java.net.*; 
import java.text.*; 
import java.util.*; 
import java.util.zip.*; 
import java.util.regex.*; 

public class Processing_code_ver5 extends PApplet {

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
 *Listen to confirmation data, 
 *change all 4 rotors speed base on the heigh of the hand.
*/

/*PROPOSE INTERACTION PLAN
 *There are two mode to operate the droid:
 *ONE HAND MODE.
 *The high of the hand will control the hight of the 
 *droid, that mean it will control the speed of 4 rotors
*/








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




public void handListener(){
  if(leap.getHandList().size()>0){
    if (!handPresented){
      //save the intial coordinatel
      print("New hand position");
    }
    handPresented=true;
    
    Hand hand=leap.getHand(0);
    PVector handPosition = leap.getPosition(hand);
    int mapPosY=(int)map(handPosition.y, -40, 450,100,0);
    mapPosY=constrain(mapPosY,20,99);
    r1=r2=r3=r4=mapPosY;
//    print(handPosition.y);
//    println(" -> "+mapPosY+"...sending...");   
//    port.write("{"+r1+","+r2+","+r3+","+r4+"}");
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
  for (Hand hand : leap.getHandList()) {
      pushMatrix();
      PVector handPosition = leap.getPosition(hand);
      translate(handPosition.x, handPosition.y);
      float pitch = leap.getPitch(hand);
      float roll = leap.getRoll(hand);
      float yaw = leap.getYaw(hand);
      
      rotateX(radians(map(pitch, -30, 30, 45, -45)));
      rotateY(radians(map(yaw, -12, 18, 45, -45)));
      rotateZ(radians(map(roll, -40, 40, 45, -45)));
      sphere(100);
      popMatrix();
   }
}


public void stop() {
  leap.stop();
}


    static public void main(String args[]) {
        PApplet.main(new String[] { "--bgcolor=#ECE9D8", "Processing_code_ver5" });
    }
}
