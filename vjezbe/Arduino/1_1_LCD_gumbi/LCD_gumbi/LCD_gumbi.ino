#include <LiquidCrystal.h>
#define LCD_PIN 9

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

static int thresholdvalueSnd;
int btn;

void setup()
{
    Serial.begin(9600);  
    lcd.begin(16,2);
    pinMode(LCD_PIN, OUTPUT);

    thresholdvalueSnd = analogRead(A0);
}

void loop()
{
 int sensorValue = analogRead(A0);
 btn = analogRead(A1);
 lcd.setCursor(0,0);

              if(sensorValue<=thresholdvalueSnd)
              {
      if(btn > 0 && btn < 1024)
                 lcd.print("Sound");
              } 
delay(500);
}
