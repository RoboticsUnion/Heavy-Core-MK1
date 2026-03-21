//ESP32 Encoder Test (AS5600)
//
//- SDA: GPIO21
//- SCL: GPIO22
//- Baudrate: 115200


#include <Arduino.h>
#include <Wire.h>
#include <AS5600.h>

AS5600 encoder;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  Wire.setClock(100000);

  if(!encoder.begin()){
    Serial.println("AS5600 not detected. Check connenctions.");
    while(1);
  }

  Serial.println("AS5600 initialized.");

}

void loop() {

  float angle = encoder.rawAngle();
  
  Serial.print("Angle: ");
  Serial.print(angle * AS5600_RAW_TO_DEGREES);
  Serial.println(" degrees");

  delay(100);

}