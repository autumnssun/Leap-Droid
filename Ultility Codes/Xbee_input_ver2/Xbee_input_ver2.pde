import processing.serial.*;
Serial port;// Serial port of the xbee object.

String typedText;
PFont normal,light;
int comma,val;

void setup() {
  size(400, 400);
  port = new Serial(this,"/dev/tty.usbserial-A101LY3X", 115200);
  normal = createFont("Helvetica",200); 
  val=70;
}
 
void draw() {
  background(70,200,255);
  fill(255);
  textFont(normal,30);
  textAlign(CENTER,CENTER);
  text("Current Speed",200,100);
  textAlign(CENTER,CENTER);
  textFont(normal,200);
  
  
  fill(100);
  text(val,199,199);
  fill(230);
  text(val,201,201);
  
  fill(70,158,200);
  text(val,200,200);
  
}

void keyPressed() {
  if (key == CODED) {
    switch(keyCode){
      case UP:
        if(val==140){
        }else{
          val++;
        }
        break;
      case DOWN:
        if (val==55){
        }else{
          val--;
        }
        break;
      default:
        break;
      } 
    }
  typedText="";
  typedText="{"+val+","+val+","+val+","+val+"}";
  senddata(typedText);
  
}

void senddata(String srt){
  port.write(srt);
  port.clear();
}
