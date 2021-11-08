#include <LiquidCrystal_I2C.h>
#include <RH_ASK.h>
#include <SPI.h> 
int red_light_pin=3;
int green_light_pin =4;
int blue_light_pin = 5;
LiquidCrystal_I2C lcd(0x27,16,2);
RH_ASK rf_driver;

void setup() {
  rf_driver.init();
  lcd.init();
  lcd.clear();         
  lcd.backlight();      
  Serial.begin(9600);
}

void loop() {
  uint8_t buf[5];
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen))
    {
      lcd.setCursor(2,0);   
      lcd.print("Tyre Pressure");
      
      String pressurestring = (char*)buf;

      int pressurearray[5];
      float pressure = pressurestring.toFloat();

      lcd.setCursor(4,1);
      lcd.println(pressure);   
      
      lcd.setCursor(9,1);   
      lcd.print("Psi");    
      
      if(pressure<=14.45){
        RGB_color(255, 0, 0); 
        }
      else if(pressure >= 14.75){RGB_color(0, 255, 0);}
      else{RGB_color(0, 255, 255);}
    } 
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
