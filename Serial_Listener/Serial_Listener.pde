import org.json.*;
import com.onformative.leap.LeapMotionP5;
import com.leapmotion.leap.*;
import processing.serial.*;
import saito.objloader.*;


OBJModel model;

LeapMotionP5 leap;
Serial port;// Serial port of the xbee object.
String dataString;
int commaPosition;
Float p,y,r;

int myWidth=1400;
int myHeight=700;
int timechunk=7;
JSON[] stackData= new JSON[200];

public void setup() {
  size(myWidth, myHeight,P3D);// set up the window with P3D mode
  port = new Serial(this,"/dev/tty.usbmodem1421", 115200); //wire mode
  //port = new Serial(this,"/dev/tty.usbserial-A101LY3X", 115200); //wireless mode
  port.bufferUntil('\n');
  //model = new OBJModel(this, "object.obj", "absolute",  QUADS);
  
  //model.scale(1);
  //model.translateToCenter();
  background(0);
  
  for (int i=0;i<stackData.length;i++){
    JSON json=JSON.parse("{gx:1,gy:1,gz:1,ax:1,ay:1,az:1}");
    stackData[i]=json;
  }
}

public void draw() { 
  stringProcess();  
  
}

void serialEvent(Serial _port){
  //print("ja");
  dataString=_port.readString();
}

void stringProcess(){
  if(dataString.length()>0){
    print(dataString);
    if (dataString.charAt(0)=='{'&&dataString.charAt(dataString.length()-3)=='}'){
      JSON json=JSON.parse(dataString);
      for (int i=0; i<stackData.length-1;i++){
        stackData[i]=stackData[i+1];
      }
      stackData[stackData.length-1]=json;
      
      background(0);
      drawGraph();
  
    }else{
    }
  }
}
public void drawGraph(){
  int center=myHeight/2;
  int quater=myHeight/4;
  for (int i=0; i<stackData.length-1;i++){
    smooth();
    stroke(127,255,255);
    line(30,30,130,30);
    line(i*timechunk,stackData[i].getFloat("gx")+center+quater,  timechunk*(i+1), stackData[i+1].getFloat("gx")+center+quater);
    stroke(255,127,255);
    line(30,60,130,60);
    line(i*timechunk,stackData[i].getFloat("gy")+center+quater,  timechunk*(i+1), stackData[i+1].getFloat("gy")+center+quater);
    stroke(255,255,127);
    line(30,90,130,90);
    line(i*timechunk,stackData[i].getFloat("gz")+center+quater,  timechunk*(i+1), stackData[i+1].getFloat("gz")+center+quater);
    
    
    stroke(0,127,255);
    line(200,30,300,30);
    line(i*timechunk,stackData[i].getFloat("ax")*100+center-quater,  timechunk*(i+1), stackData[i+1].getFloat("ax")*100+center-quater);
    stroke(127,0,255);
    line(200,60,300,60);
    line(i*timechunk,stackData[i].getFloat("ay")*100+center-quater,  timechunk*(i+1), stackData[i+1].getFloat("ay")*100+center-quater);
    stroke(255,127,0);
    line(200,90,300,90);
    line(i*timechunk,stackData[i].getFloat("az")*100+center-quater,  timechunk*(i+1), stackData[i+1].getFloat("az")*100+center-quater);
    
  }
}
public void drawQuadcopter(float pitch, float roll){
  background(255);
  lights();
  pushMatrix();
  translate(width/2,height/2);
  rotateZ(radians(roll)); 
  rotateX(radians(pitch));
  model.draw();
  popMatrix();
}
