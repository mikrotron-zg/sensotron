#include <LiquidCrystal.h>
#define LCD_PIN 9

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

static int thresholdvalueSnd;

void setup()
{
    Serial.begin(9600);  
    lcd.begin(16,2);
    pinMode(LCD_PIN, OUTPUT);

    thresholdvalueSnd = analogRead(A1);
}

void loop()
{
 int sensorValue = analogRead(A1);
 lcd.setCursor(0,0);
 lcd.clear();
              if(sensorValue<thresholdvalueSnd)
              {
                 lcd.print("Sound");
              }
              if(sensorValue>=thresholdvalueSnd)
              {
                 lcd.print("NoSound");
              } 
              Serial.println(sensorValue);
delay(500);
}
