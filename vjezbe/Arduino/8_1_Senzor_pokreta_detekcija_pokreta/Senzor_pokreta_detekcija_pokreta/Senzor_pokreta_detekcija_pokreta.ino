#include <LiquidCrystal.h>
#define PIR_PIN 3
#define LCD_PIN 9
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int motionDetect = 0;
void setup()
{
    Serial.begin(9600);  
    lcd.begin(16,2);
    pinMode(LCD_PIN, OUTPUT);
  motionDetect = digitalRead(PIR_PIN);
}

void loop()
{
 lcd.setCursor(0,0);

 lcd.clear();
              if (motionDetect == HIGH)
              {
                 lcd.print("Motion");
              }
              if (motionDetect == LOW)
              {
                 lcd.print("No motion");
              }
delay(500);
}
