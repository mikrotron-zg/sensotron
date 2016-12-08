
#include <LiquidCrystal.h>
#define TOUCH_PIN 2
#define LCD_PIN 9
#define LIGHT_PIN 10
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup()
{
    Serial.begin(9600);  
    lcd.begin(16,2);
  
}

void loop()
{
 
              if(digitalRead(TOUCH_PIN)==HIGH)
              {
                digitalWrite(LIGHT_PIN, LOW);
                pinMode(LIGHT_PIN, OUTPUT);
              }
              if(digitalRead(TOUCH_PIN)==LOW)
              {
                digitalWrite(LIGHT_PIN,HIGH);
                pinMode(LCD_PIN, OUTPUT);
              } 
delay(500);
} 
