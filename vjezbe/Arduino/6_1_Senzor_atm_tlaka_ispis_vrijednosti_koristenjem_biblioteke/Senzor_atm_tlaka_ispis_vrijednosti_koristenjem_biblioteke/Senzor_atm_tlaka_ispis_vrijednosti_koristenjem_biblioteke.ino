#include <Adafruit_MPL115A2.h>
#include <LiquidCrystal.h>
#define LCD_PIN 9

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
Adafruit_MPL115A2 mpl115a2;
void setup() 
{

    Serial.begin(9600);  
    lcd.begin(16,2);
    mpl115a2.begin();
    pinMode(LCD_PIN, OUTPUT);
}

void loop() 
{
 static char pressureC[10];  

                 dtostrf(mpl115a2.getPressure(), 4, 2, pressureC);
                 lcd.setCursor(0,0);
                 lcd.print("Tlak[kPa]: ");
                 lcd.print(pressureC);
                 delay(500);
}

