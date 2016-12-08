#include <Adafruit_MPL115A2.h>
#include <LiquidCrystal.h>
#include "Arduino.h"
#include <Wire.h>
#define LCD_PIN 9
#define ADRESA              (0x60)    // 1100000
#define TLAK_MSB            (0x00)
#define TLAK_LSB            (0x01)
#define TEMP_MSB            (0x02)
#define TEMP_LSB            (0x03)
#define A0_KOEF_MSB         (0x04)
#define A0_KOEF_LSB         (0x05)
#define B1_KOEF_MSB         (0x06)
#define B1_KOEF_LSB         (0x07)
#define B2_KOEF_MSB         (0x08)
#define B2_KOEF_LSB         (0x09)
#define C12_KOEF_MSB        (0x0A)
#define C12_KOEF_LSB        (0x0B)
#define STARTCONVERSION     (0x12)

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

float a0 = 0.0F;
float b1 = 0.0F;
float b2 = 0.0F;
float c12 = 0.0F;
  
void setup() 
{

    Serial.begin(9600);  
    lcd.begin(16,2);
    Wire.begin();
    getKoeficijente();
    pinMode(LCD_PIN, OUTPUT);
}

void loop() 
{
 static char tlakC[10];  
 float tlak=getTlak();
                 dtostrf(tlak, 4, 2, tlakC);
                 lcd.setCursor(0,0);
                 lcd.print("Tlak[kPa]: ");
                 lcd.print(tlakC);
                 delay(500);
}

void getKoeficijente()
{
  int16_t a0koef;
  int16_t b1koef;
  int16_t b2koef;
  int16_t c12koef;

  Wire.beginTransmission(ADRESA);
  Wire.write((uint8_t)A0_KOEF_MSB);
  Wire.endTransmission();

  Wire.requestFrom(ADRESA, 8);
  a0koef = (( (uint16_t) Wire.read() << 8) | Wire.read());
  b1koef = (( (uint16_t) Wire.read() << 8) | Wire.read());
  b2koef = (( (uint16_t) Wire.read() << 8) | Wire.read());
  c12koef = (( (uint16_t) (Wire.read() << 8) | Wire.read())) >> 2;


  a0 = (float)a0koef / 8;
  b1 = (float)b1koef / 8192;
  b2 = (float)b2koef / 16384;
  c12 = (float)c12koef;
  c12 /= 4194304.0;

}

float getTlak()
{
  uint16_t  tlak,temp;
  float     tlakComp;
  float     P;
 
  Wire.beginTransmission(ADRESA);
  Wire.write((uint8_t)STARTCONVERSION);
  Wire.write((uint8_t)0x00);
  Wire.endTransmission();

  delay(5);

  Wire.beginTransmission(ADRESA);
  Wire.write((uint8_t)TLAK_MSB);  // REGISTAR
  Wire.endTransmission();

  Wire.requestFrom(ADRESA, 4);
  tlak = (( (uint16_t) Wire.read() << 8) | Wire.read()) >> 6;
  temp = (( (uint16_t) Wire.read() << 8) | Wire.read()) >> 6;

  tlakComp = a0 + (b1 + c12 * temp ) * tlak + b2 * temp;

  
  P = ((65.0F / 1023.0F) * tlakComp) + 50.0F;        // kPa
 
  return P;
}


