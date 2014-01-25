/*
 *PROJECT: LEAPDROID 
 *PLATFORM PROCESSING
 *STATE: PROTOTYPING
 *--------------------------------------
 *PROCESSING code version 5
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

import com.onformative.leap.LeapMotionP5;
import com.leapmotion.leap.*;
import processing.serial.*;
import saito.objloader.*;

OBJModel model;

LeapMotionP5 leap;
Serial port;// Serial port of the xbee object.

boolean handInitiated=false;
int [] speeds= new int[4];
float orgPitch, orgYaw, orgRoll;
PVector originalHandPosition;
int startTime=millis();
final int radius = 10;
final int lowSpeed=40,   //Lowest speed for the rotor
          highSpeed=180, //Highest speed for the rotor
          lowAlt=40,    //Lowest position of the hand in mm
          highAlt=350;   //Highest positionof the hand in mm
final float axisSensitivity=5; 
final int waitTime=2000;
final boolean relativeToLeap=true;

final  PVector pitchEffectiveRange=new PVector(0,0),
               rollEffectiveRange=new PVector(0,0);
float rotX, rotY;
               
public void setup() {
  size(1400, 700,P3D);// set up the window with P3D mode
  leap = new LeapMotionP5(this);
  port = new Serial(this,"/dev/tty.usbserial-A101LY3X", 115200);
  background(255);
  
  model = new OBJModel(this, "object.obj", "absolute", QUADS);
  
  model.scale(1);
  model.translateToCenter();
  model.disableTexture();
  noStroke();
}


void mouseDragged(){
    rotX += (mouseX - pmouseX) * 0.01;
    rotY -= (mouseY - pmouseY) * 0.01;
}

public void draw() {
  background(255);
  rx();  
  
  if(leap.getHandList().size()>0 && leap.getFingerList().size()>3){
    if (handInitiated){
        if (timeup()>0){
          float [] arr=sandBox(leap.getHand(0));
          prt(arr);          
          //drawQuadcopter(arr);
          //draw3d();
          tx(arr);
        }else{
          saveOriginalHand(leap.getHand(0));
          fill(0,200,0);
          textSize(20);
          port.write("{A}");
          text("Gain control in " +(-timeup()+1000)/1000  + " seconds",10,30);
        }
    }else{
      //port.write("{LeapReady}");
      startTime=millis();
      handInitiated=true;
    }
  }else{
    if (handInitiated){
      println("HAND RELEASE");
    }
    port.write("{A}");
    handInitiated=false;
  }
}



public float[] sandBox(Hand h){
  float []returnArray=new float[7];
  PVector handPos;
  float pitch, roll, yaw, r1,r2,r3,r4;

  handPos=leap.getPosition(h);
  pitch=leap.getPitch(h);
  roll =leap.getRoll(h);
  yaw = leap.getYaw(h);
  
  if (!relativeToLeap){
     handPos=PVector.sub(handPos,originalHandPosition);
     pitch=(pitch-orgPitch);
     roll =(roll-orgRoll);
     yaw = (yaw-orgYaw);
  }
  float handHeight=handPos.y;
  float pivot=handHeight;
  
  if(pitchEffectiveRange.x<pitch||pitch<pitchEffectiveRange.y){
    r1=pivot+sin(pitch*PI/180)*radius*axisSensitivity;
    r3=pivot-sin(pitch*PI/180)*radius*axisSensitivity;
  }else{
    r1=r3=pivot;
  }
  
  if(rollEffectiveRange.x<roll||roll<rollEffectiveRange.y){
    r2=pivot+sin(roll*PI/180)*radius*axisSensitivity;
    r4=pivot-sin(roll*PI/180)*radius*axisSensitivity;
  }else{
    r2=r4=pivot;
  }
  
  lights();
  pushMatrix();
  translate(width/2,height/2);
  rotateX(radians(map(pitch, -30, 30, 45, -45)));
  rotateY(radians(map(yaw, -12, 18, 45, -45)));
  rotateZ(radians(map(roll, -40, 40, 45, -45)));
  model.draw();
  popMatrix();
  
  returnArray[0]=r1;
  returnArray[1]=r2;
  returnArray[2]=r3;
  returnArray[3]=r4;
  
  returnArray[4]=pitch;
  returnArray[5]=roll;
  returnArray[6]=yaw;
  
  for (int i=0; i<4;i++){
    float cache=map(returnArray[i],highAlt,lowAlt,lowSpeed,highSpeed);
  }
  
  return returnArray;
}

public void saveOriginalHand(Hand h){
  originalHandPosition=leap.getPosition(h);
  orgPitch=leap.getPitch(h);
  orgRoll=leap.getRoll(h);
  orgYaw=leap.getYaw(h);
}


public void rx(){
  while (port.available() >0) {
    String inBuffer = port.readString();   
    if (inBuffer != null) {
      println(inBuffer);
    }
  }
}



public void drawQuadcopter(float []ar){
  fill(0);
  float x=leap.getPosition(leap.getHand(0)).x;
  ellipse(x-80,ar[2],20,20);
  ellipse(x+80,ar[0],60,60);
  ellipse(x-150,ar[1],40,40);
  ellipse(x+150,ar[3],40,40);
  stroke(0);
  line(x-80,ar[2],x+80,ar[0]);
  line(x-150,ar[1],x+150,ar[3]);
  
  
  
  
}

public void prt(float []ar){
  fill(0, 102, 153);
  for (int i=0; i<4;i++){
    text("Rotor " +(i+1)+" value: "+ (int)ar[i], 10, 30*(i+1));
  }
  fill(0, 0, 200);
  text("Yawn (angle): "+ar[4]*PI/180,10,300);
  fill(0, 200, 0);
  text("Ptich (angle): "+ar[5]*PI/180,10,360);
  fill(200, 0, 0);
  text("Roll (angle): "+ar[6]*PI/180,10,420);
  
}

public void tx(float []ar ){
  String sending=("{"+(int)ar[0]+","+(int)ar[1]+","+(int)ar[2]+","+(int)ar[3]+"}");
  port.write(sending);
}

public void stop() {
  port.write("{A}");
  leap.stop();
}

public int timeup(){
  return millis()-startTime-waitTime;
}

