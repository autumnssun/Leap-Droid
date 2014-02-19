#include "Wire.h"
#include "HMC5883.h"

HMC5883 gyro;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  gyro.enableDefault();
}
void loop() {
  gyro.read();

  Serial.print("G ");
  Serial.print("X: ");
  Serial.print(gyro.g.x);
  Serial.print(" Y: ");
  Serial.print(gyro.g.y);
  Serial.print(" Z: ");
  Serial.println(gyro.g.z);

  delay(100);
}
