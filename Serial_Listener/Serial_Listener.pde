import org.json.*;
import com.onformative.leap.LeapMotionP5;
import com.leapmotion.leap.*;
import processing.serial.*;
import saito.objloader.*;


OBJModel model;

LeapMotionP5 leap;
Serial port;// Serial port of the xbee object.

int commaPosition;
String blah=" ";
Float p,y,r;
public void setup() {
  size(1400, 700,P3D);// set up the window with P3D mode
  port = new Serial(this,"/dev/tty.usbmodem1a12411", 115200); //wire mode
  //port = new Serial(this,"/dev/tty.usbserial-A101LY3X", 115200); //wireless mode
  port.bufferUntil('\n');
  
  model = new OBJModel(this, "object.obj", "absolute",  QUADS);
  
  model.scale(1);
  model.translateToCenter();
  background(255);
}

public void draw() { 
  
  rx();
  
}

void serialEvent(Serial p){
  blah=p.readString();
}

void rx(){
  print(blah);
  if(blah.length()>3){
    if (blah.charAt(0)=='{'&&blah.charAt(blah.length()-3)=='}'){
      JSON json=JSON.parse(blah);
      drawQuadcopter(json.getFloat("pitch"),json.getFloat("roll"));
    }else{
      //print("wrong format");
    }
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
