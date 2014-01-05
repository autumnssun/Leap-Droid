import processing.serial.*;

// The serial port:
Serial myPort;
String jsonString="{123,333,121,111}";
void setup(){
// Open the port you are using at the rate you want:
   myPort = new Serial(this,"/dev/tty.usbserial-A101LY3X", 9600);
// myPort = new Serial(this,'/dev/tty.usbmodem1411' , 11);
   
}
void draw() {
  myPort.write(jsonString);
  while (myPort.available() > 0) {
    String inBuffer = myPort.readString();   
    if (inBuffer != null) {
      println(inBuffer);
    }
  }
  delay(1000);
}
