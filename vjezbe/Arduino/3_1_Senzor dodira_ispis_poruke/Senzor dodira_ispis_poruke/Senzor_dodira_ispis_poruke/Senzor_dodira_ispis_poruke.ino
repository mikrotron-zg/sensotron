#include <LiquidCrystal.h>
#define TOUCH_PIN 2
#define LCD_PIN 9
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup()
{
    Serial.begin(9600);  
    lcd.begin(16,2);
    pinMode(LCD_PIN, OUTPUT);

}

void loop()
{
 
 lcd.clear();
 lcd.setCursor(0,0);

              if(digitalRead(TOUCH_PIN)==HIGH)
              {
                lcd.print("NoTouch");
              }
              if(digitalRead(TOUCH_PIN)==LOW)
              {
                lcd.print("Touch");
              } 
delay(500);
} 
