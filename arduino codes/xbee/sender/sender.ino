int incomingByte = 0;   // for incoming serial data

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {
    if(Serial.available() > 0)
    {
        int b=Serial.read();
        Serial.println(b,DEC);
    }
}
