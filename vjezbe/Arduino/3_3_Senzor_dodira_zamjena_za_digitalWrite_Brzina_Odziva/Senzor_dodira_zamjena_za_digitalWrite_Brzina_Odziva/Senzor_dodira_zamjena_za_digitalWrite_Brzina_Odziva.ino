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
 lcd.clear();
              if(digitalRead(TOUCH_PIN)==HIGH)
              {
                PORTB &= ~_BV(PB2);
                pinMode(LIGHT_PIN, OUTPUT);
              }
              if(digitalRead(TOUCH_PIN)==LOW)
              {
               testBrzineOdziva();
              } 
delay(500);
}

void testBrzineOdziva()
{
 int initial = 0;
 int final = 0;
 initial = micros();
 for(int i = 0; i < 500; i++)
 {
    digitalWrite(10,LOW);
    digitalWrite(10,HIGH);
 }
 final = micros();
 lcd.setCursor(0,0);
 lcd.print("dig.W.[ms]: ");
 lcd.print(final-initial);
 
 initial = micros();
 for(int i = 0; i < 500; i++)
 {
    PORTB &= ~_BV(PB2);  
    PORTB |= _BV(PB2);
  }
 final = micros();
 lcd.setCursor(0,1);
 lcd.print("c cmd[ms]: ");
 lcd.print(final-initial);
 pinMode(LCD_PIN, OUTPUT);
 
}
 

