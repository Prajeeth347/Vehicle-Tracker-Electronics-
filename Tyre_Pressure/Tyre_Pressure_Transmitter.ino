#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <RH_ASK.h>
#include <SPI.h> 

Adafruit_BMP085 bmp180;
RH_ASK rf_driver;

void setup() {
  Serial.begin(9600);
  bmp180.begin();
  rf_driver.init();
}

void loop() {
          float pressure = ((bmp180.readPressure())*0.000145037738);
          String pressurestring = String(pressure);
          char pressurechar[5];
          for(int i = 0; i<5; i++){
              pressurechar[i] = pressurestring[i];
            }
          rf_driver.send((uint8_t *)pressurechar, 5);
          rf_driver.waitPacketSent();  
          delay(1000);
    }
