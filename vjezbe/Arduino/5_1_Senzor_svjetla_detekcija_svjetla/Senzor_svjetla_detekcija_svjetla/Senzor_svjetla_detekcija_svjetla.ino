#include <LiquidCrystal.h>
#define LCD_PIN 9

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

static int thresholdvalueLight;

void setup()
{
    Serial.begin(9600);  
    lcd.begin(16,2);
    pinMode(LCD_PIN, OUTPUT);

    thresholdvalueLight = analogRead(A2);
}

void loop()
{
 int sensorValue = analogRead(A2);
 lcd.setCursor(0,0);
 lcd.clear();
              if(sensorValue>thresholdvalueLight)
              {
                 lcd.print("Descending light");

              }
              if(sensorValue<=thresholdvalueLight)
              {
                 lcd.print("Light is ok");
              } 
delay(500);
}

