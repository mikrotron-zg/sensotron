#include "DHT.h" 
#include <LiquidCrystal.h>
#include <stdlib.h>
#define DHTPIN 4 
#define DHTTYPE DHT11
#define LCD_PIN 9

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() 
{
    Serial.begin(9600);  
    dht.begin();
    pinMode(LCD_PIN, OUTPUT);
    
   
}

void loop()
{
    
     static char temp[10]; 
     static char hum[10];
     dtostrf(float(dht.readTemperature()), 3, 1, temp);
     dtostrf(float(dht.readHumidity()), 3, 1, hum);
     lcd.begin(16,2);
    
     lcd.clear();
     lcd.setCursor(0,0);
     
     lcd.print("Temp=");
     lcd.print(temp);
     lcd.print(" C");
     
     lcd.setCursor(0,1);
     
     lcd.print("Vlaga=");
     lcd.print(hum);
     lcd.print(" %");
     delay(500);
}
