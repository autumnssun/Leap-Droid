import processing.serial.*;
Serial port;// Serial port of the xbee object.

String typedText = "{";
String [] stack= new String[10];
PFont font;
int comma;


void setup() {
  size(400, 400);
  port = new Serial(this,"/dev/tty.usbserial-A101LY3X", 115200);
  font = createFont("Helvetica", 18);  
  for(int i=0; i<stack.length;i++){
     stack[i]="";
  }
}
 
void draw() {
  background(255);
  
  stroke(125);
  strokeWeight(2);
  fill(255);
  line(0,height-40,width,height-40);
  
  fill(128,128,128);
  textFont(font,18);
  
  for(int i=0; i<stack.length;i++){
    if (stack[i]!=null){
      text(stack[i],10,350-30*i);
    }
  }
  
  text(typedText+(frameCount/10 % 2 == 0 ? "_" : ""), 10, 385);
}
 
void keyPressed(){
   if (key != CODED) {
     switch(key) {
      case BACKSPACE:
        typedText = typedText.substring(0,max(0,typedText.length()-1));
        break;
      default:
     }
   }
}

void keyReleased() {
  if(typedText.length()==16){
    typedText+="}";
    senddata(typedText);
  }
    
  if (key != CODED&&typedText.length()<17) {
    switch(key) {
    case BACKSPACE:
      typedText = typedText.substring(0,max(0,typedText.length()-1));
      break;
    case ENTER:
    case RETURN:
      senddata(typedText);
      break;
    case ESC:
    case DELETE:
      break;
    default:
      typedText += key;
    }
  }
}

void senddata(String srt){
  for(int i=stack.length-1; i>0;i--){
      stack[i]=stack[i-1];
      println(stack[i]);
  }
  stack[0]=typedText;
  port.write(typedText);
  typedText="{";
  println(srt);  
}
