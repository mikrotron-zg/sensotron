#include <LiquidCrystal.h>
#define LCD_PIN 9
#define  LIGHT_PIN 10

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
 

              if(sensorValue>=thresholdvalueSnd)
              {
                digitalWrite(LIGHT_PIN,HIGH);
                pinMode(LCD_PIN,OUTPUT);
              }
              else 
              { 
        digitalWrite(LIGHT_PIN,LOW);
                pinMode(LCD_PIN,OUTPUT);
       }
delay(500);
}
