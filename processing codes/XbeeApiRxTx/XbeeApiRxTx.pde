/*//////////////     NOTES   ////////////////
+ Coodinator serial port: /dev/tty.usbserial-A101LY3X 
+ Coodinator MAC ADDRESS: 0013A2004089E9C8
+ Coodinator 16 bit MAC: --

+ Rourter serial port:  /dev/tty.usbserial-A901J1S5
+ Router MAC ADDRESS: 0013A2004089E9D0
+ Router 16 bit MAC: FF52
///////////////END OF NOTES///////////////*/
import processing.serial.*;
import xbee.*;

Serial port;
XBeeReader xbee;

void setup()
{
  size(200, 200);

  // println("Available serial ports:");
  // println(Serial.list());
  port = new Serial(this,"/dev/tty.usbserial-A101LY3X", 9600);
  xbee = new XBeeReader(this,port);

  xbee.startXBee();
  println("XBee Library version " + xbee.getVersion());
}

void draw()
{
}

void xBeeEvent(XBeeReader xbee) {
  XBeeDataFrame data = xbee.getXBeeReading();

  if (data.getApiID() == xbee.SERIES1_RX16PACKET) {
    int addr = data.getAddress16();
    int[] bytes = data.getBytes();
    
    print(millis() + "\t[" + addr + "]:");
    
    for (int n = 0; n < bytes.length; n++) {
      print(" " + bytes[n]);
      
    }
    
    println();
    
    // echo data back to the xbee.
    xbee.sendDataString16(addr, bytes);
  } 
}


