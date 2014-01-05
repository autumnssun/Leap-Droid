
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  //pinMode(led, OUTPUT);  
  Serial.begin(9600);  
}

// the loop routine runs over and over again forever:
void loop() {
  setRemoteState(0x5);
  
  delay(1000);   // wait for a second
  
  
  setRemoteState(0x4);
  delay(1000);               // wait for a second
}

void setRemoteState(char value){
  // Remote XBee: AT, Base XBee: API
  Serial.write(0x7E); // Sync up the start byte
  Serial.write((byte)0x0); // Length MSB (always 0)  
  Serial.write(0x10); // Length LSB 
  Serial.write(0x17); // 0x17 is the frame ID for sending an AT command
  Serial.write((byte)0x0); // Frame ID (no reply needed)
  Serial.write((byte)0x0); // Send the 64 bit destination address 
 
  // (Sending 0x000000000000FFFF (broadcast))
  //Serial.write((byte)0x0); 
  //Serial.write((byte)0x0); 
  //Serial.write((byte)0x0); 
  //Serial.write((byte)0x0); 
  //Serial.write((byte)0x0);   
  //Serial.write(0xFF); 
  //Serial.write(0xFF); 
  
  // Destination Network (Set to 0xFFFE if unknown)
  //Serial.write(0xFF); 
  //Serial.write(0xFE);  
  
  //Serial.write(0x02); // Set to 0x02 to apply these changes
  
 // Serial.write('D'); // AT Command: D1
  //Serial.write('3'); 
  
  //Serial.write(value); // Set D1 to be 5 (Digital Out HIGH)
  
  long chexsum = 0x17 + 0xFF + 0xFF +0xFF + 0xFE + 0x02 + 'D' + '3' + value;
  
  Serial.write( 0xFF - (chexsum & 0xFF)); 
}
