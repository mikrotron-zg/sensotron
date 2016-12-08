#include <LiquidCrystal.h>
#define LCD_PIN 9

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

static int thresholdvalueGas;

void setup()
{
    Serial.begin(9600);  
    lcd.begin(16,2);
    pinMode(LCD_PIN, OUTPUT);

    thresholdvalueGas = analogRead(A3);
}

void loop()
{
 int sensorValue = analogRead(A3);
 lcd.setCursor(0,0);
 lcd.clear();
              if(sensorValue>thresholdvalueGas)
              {
                 lcd.print("Gas");
              }
              if(sensorValue<=thresholdvalueGas)
              {
                 lcd.print("No gas");
              } 
delay(500);
}

