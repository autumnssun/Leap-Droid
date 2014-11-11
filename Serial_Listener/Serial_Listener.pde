import org.json.*;
import com.onformative.leap.LeapMotionP5;
import com.leapmotion.leap.*;
import processing.serial.*;
//import saito.objloader.*;


//OBJModel model;

LeapMotionP5 leap;
Serial port;// Serial port of the xbee object.
String dataString;
int commaPosition;
Float p,y,r;

int myWidth=1400;
int myHeight=700;
int timechunk=7;
int scale=300;
JSON[] stackData= new JSON[200];

public void setup() {
  size(myWidth, myHeight,P3D);// set up the window with P3D mode
  
  port = new Serial(this,"/dev/tty.usbmodem1411", 115200); //wire mode
  port.bufferUntil('\n');
  //model = new OBJModel(this, "object.obj", "absolute",  QUADS);
  //model.scale(1);
  //model.translateToCenter();
  
  for (int i=0;i<stackData.length;i++){
    //popuplate the stack with all 1 
    //JSON json=JSON.parse("{p:1,r:1}");
    //JSON json=JSON.parse("{gx:1,gy:1,gz:1,ax:1,ay:1,az:1}");
    //JSON json=JSON.parse("{gx:1,gy:1,gz:1}");
    JSON json=JSON.parse("{ax:1,ay:1,az:1}");

    //JSON json=JSON.parse("{gx:1,gy:1,gz:1,mx:1,my:1,mz:1}");
    //JSON json=JSON.parse("{gx:1,gy:1,gz:1,ax:1,ay:1,az:1,mx:1,my:1,mz:1}");
    stackData[i]=json;
  }
}

public void draw() { // default loop
  background(0);
  stringProcess();  
}

void serialEvent(Serial _port){
  dataString=_port.readString();
}

void stringProcess(){
  if(dataString.length()>0){
    print(dataString);
    if (dataString.charAt(0)=='{' && dataString.charAt(dataString.length()-3)=='}'){
      
      JSON json=JSON.parse(dataString);
      for (int i=0; i<stackData.length-1;i++){
        stackData[i]=stackData[i+1];
      }
      stackData[stackData.length-1]=json;
      drawGraph();
    }else{
      
    }
  }
}
public void drawGraph(){
  int hcenter=myHeight/2;
  int hquater=myHeight/4;
  for (int i=0; i<stackData.length-1;i++){
    smooth();
//    stroke(0,0,255);
//    line(30,30,130,30);
//    line(i*timechunk,stackData[i].getFloat("r")*100+hquater,  timechunk*(i+1), stackData[i+1].getFloat("r")*100+hquater);
//    stroke(0,255,0);
//    line(30,60,130,60);
//    line(i*timechunk,stackData[i].getFloat("p")*100+hquater,  timechunk*(i+1), stackData[i+1].getFloat("p")*100+hquater);
//    
//    stroke(0,0,255);
//    line(30,30,130,30);
//    line(i*timechunk,stackData[i].getFloat("gx")+hcenter+hquater,  timechunk*(i+1), stackData[i+1].getFloat("gx")+hcenter+hquater);
//    stroke(0,255,0);
//    line(30,60,130,60);
//    line(i*timechunk,stackData[i].getFloat("gy")+hcenter+hquater,  timechunk*(i+1), stackData[i+1].getFloat("gy")+hcenter+hquater);
//    stroke(255,0,0);
//    line(30,90,130,90);
//    line(i*timechunk,stackData[i].getFloat("gz")+hcenter+hquater,  timechunk*(i+1), stackData[i+1].getFloat("gz")+hcenter+hquater);
//    
    stroke(0,255,255);
    line(200,30,300,30);
    line(i*timechunk,stackData[i].getFloat("ax")+hcenter-hquater,  timechunk*(i+1), stackData[i+1].getFloat("ax")+hcenter-hquater);
    stroke(255,0,255);
    line(200,60,300,60);
    line(i*timechunk,stackData[i].getFloat("ay")+hcenter-hquater,  timechunk*(i+1), stackData[i+1].getFloat("ay")+hcenter-hquater);
    stroke(255,255,0);
    line(200,90,300,90);
    line(i*timechunk,stackData[i].getFloat("az")+hcenter-hquater,  timechunk*(i+1), stackData[i+1].getFloat("az")+hcenter-hquater);
//    
//    stroke(0,127,255);
//    line(200,30,300,30);
//    line(i*timechunk,stackData[i].getFloat("mx")+hcenter-hquater,  timechunk*(i+1), stackData[i+1].getFloat("mx")+hcenter-hquater);
//    stroke(127,0,255);
//    line(200,60,300,60);
//    line(i*timechunk,stackData[i].getFloat("my")+hcenter-hquater,  timechunk*(i+1), stackData[i+1].getFloat("my")+hcenter-hquater);
//    stroke(255,127,0);
//    line(200,90,300,90);
//    line(i*timechunk,stackData[i].getFloat("mz")+hcenter-hquater,  timechunk*(i+1), stackData[i+1].getFloat("mz")+hcenter-hquater);
//    
  }
}
public void drawQuadcopter(float pitch, float roll){
  
  lights();
  pushMatrix();
  translate(width/2,height/2);
  rotateX(radians(roll)); 
  rotateZ(radians(pitch));
  //model.draw();
  popMatrix();
}
