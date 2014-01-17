import processing.serial.*;
Serial port;// Serial port of the xbee object.

public void setup() {
  size(1400, 700,P3D);// set up the window with P3D mode
  port = new Serial(this,"/dev/tty.usbserial-A101LY3X", 115200);
}

public void draw() {
  background(255);
  while (port.available() >0) {
    String inBuffer = port.readString();   
    if (inBuffer != null) {
      println(inBuffer);
    }
  }
}
