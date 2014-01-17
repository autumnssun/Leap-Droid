import processing.serial.*;

// The serial port:
Serial myPort;
String jsonString;
void setup(){
// Open the port you are using at the rate you want:
   myPort = new Serial(this,"/dev/tty.usbserial-A101LY3X", 115200);
// myPort = new Serial(this,'/dev/tty.usbmodem1411' , 11);
   
}
void draw() {
  long unixTime = System.currentTimeMillis();
  //println(unixTime);
  myPort.write("{219,231,323,312}");
//  while (myPort.available() > 0) {
//    String inBuffer = myPort.readString();   
//    if (inBuffer != null) {
//      println(inBuffer);
//    }
//  }
  delay(5000);
}
