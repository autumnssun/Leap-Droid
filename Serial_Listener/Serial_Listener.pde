import org.json.*;
import com.onformative.leap.LeapMotionP5;
import com.leapmotion.leap.*;
import processing.serial.*;
import saito.objloader.*;


OBJModel model;

LeapMotionP5 leap;
Serial port;// Serial port of the xbee object.

int commaPosition;
String blah;
public void setup() {
  size(1400, 700,P3D);// set up the window with P3D mode
  port = new Serial(this,"/dev/tty.usbmodem1a12411", 115200);
  port.bufferUntil('\n');
  
  model = new OBJModel(this, "object1.obj", "absolute");
  
  model.scale(5);
  model.translateToCenter();
  background(255);
}

public void draw() { 
  background(255);
  rx();
}

void serialEvent(Serial p){
  blah=p.readString();
}

void rx(){
  if(blah.length()>3){
    print(blah);
    if (blah.charAt(0)=='{'&&blah.charAt(blah.length()-3)=='}'){
      JSON json=JSON.parse(blah);
      drawQuadcopter(json.getFloat("pitch"),json.getFloat("roll"),json.getFloat("yaw"));
    }else{
      //print("wrong format");
    }
  }
}

public void drawQuadcopter(float pitch,float roll,float yaw){
  lights();
  pushMatrix();
  translate(width/2,height/2);
  rotateX(radians(roll*180.0)); 
  rotateY(radians(pitch*180.0));
  rotateZ(radians(yaw*180.0));
  model.draw();
  popMatrix();
}
