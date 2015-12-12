#include <avr/pgmspace.h>
#include <stdlib.h>
#include <Adafruit_MPL115A2.h>
#include <Wire.h>
#include "DHT.h"
#include <LiquidCrystal.h>
#define DHT_PIN 4    
#define TOUCH_PIN 2
#define BUZZER_PIN 1
#define PIR_PIN 3
#define LCD_PIN 9
#define DHTTYPE DHT11
#define FUNCT_NUM 8
#define MSG_NUM 12
#define MAX_UP 6
#define MAX_DOWN 7
#define RIGHT 50
#define UP 195
#define DOWN 380
#define LEFT 555
#define SELECT 790
#define NONE 1000


DHT dht(DHT_PIN, DHTTYPE);


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
    
   
unsigned short int cntDown = 0;
unsigned short int cntUp = 0;
short int state = -1;

static int thresholdvalueSnd;
static int thresholdvalueGas;
static int thresholdvalueLight;


void (*sensorFunctions[FUNCT_NUM])(); 

Adafruit_MPL115A2 mpl115a2;

    const char msgList0[] PROGMEM = "Menu: press down";
    const char msgList1[] PROGMEM = "Can't read DHT";
    const char msgList2[] PROGMEM = "Touch me";
    const char msgList3[] PROGMEM = "Thank you";
    const char msgList4[] PROGMEM = "I hear you";
    const char msgList5[] PROGMEM = "Talk to me";
    const char msgList6[] PROGMEM = "Light is ok";
    const char msgList7[] PROGMEM = "Descending light";
    const char msgList8[] PROGMEM = "Gas detection";
    const char msgList9[] PROGMEM = "No gas";
    const char msgList10[] PROGMEM = "Motion";
    const char msgList11[] PROGMEM = "No Motion";
    const char msgList12[] PROGMEM = "Temp[*C]=";
    const char msgList13[] PROGMEM = "Humidity[%]=";
    const char msgList14[] PROGMEM = "Pressure[kPa]: ";
    const char msgList15[] PROGMEM = " ";
    
    
    
const char* const msgList[] PROGMEM = {msgList0, msgList1, msgList2, msgList3, msgList4, msgList5, msgList6, msgList7, msgList8, msgList9, msgList10, msgList11, msgList12, msgList13, msgList14, msgList15};

    const char sensorList0[] PROGMEM = "1.HumdTemp Brick";
    const char sensorList1[] PROGMEM = "2.Touch Brick";
    const char sensorList2[] PROGMEM = "3.Sound Brick";
    const char sensorList3[] PROGMEM = "4.Light Brick";
    const char sensorList4[] PROGMEM = "5.Barom Sensor";
    const char sensorList5[] PROGMEM = "6.PIR Sensor";
    const char sensorList6[] PROGMEM = "7.Gas Brick";
    
const char* const sensorList[] PROGMEM = {sensorList0, sensorList1,sensorList2, sensorList3, sensorList4, sensorList5, sensorList6};



char buffer[130];

void setup() 
{
 
    Serial.begin(9600);  
    lcd.begin(16,2);
    
    displayAndDelay(0, 0,(const char*) &msgList[0], 500, "");
    
    dht.begin();
    mpl115a2.begin();
    pinMode(LCD_PIN, OUTPUT);
 
    sensorFunctions[0] = tempHumidSensor; 
    sensorFunctions[1] = touchSensor;
    sensorFunctions[2] = soundSensor ;
    sensorFunctions[3] = lightSensor;
    sensorFunctions[4] = barometricSensor;
    sensorFunctions[5] = pirSensor;
    sensorFunctions[6] = gasSensor;
    
    thresholdvalueSnd = analogRead(A1);
    thresholdvalueGas = analogRead(A3);
    thresholdvalueLight = analogRead(A2);
}

void loop() 
{
    if(cntUp > MAX_UP) cntUp=0;
    if(cntDown > MAX_DOWN) cntDown=0;
    
    pressButtons();
}

int readButtons() 
{
  
  int pressed = analogRead(A0); 
  static unsigned long debounce; 
  
  if(millis() - debounce < 200)
  { 
    return NONE; 
  } 
  else 
  {
    debounce = millis(); 
  }
  
  /**** http://www.ganssle.com/debouncing-pt2.htm ****/
 
  if (pressed < RIGHT)        pressed = RIGHT;
  else if (pressed < UP)      pressed = UP;
  else if (pressed < DOWN)    pressed = DOWN;
  else if (pressed < LEFT)    pressed = LEFT;
  else if (pressed < SELECT)  pressed = SELECT;
  else                        pressed = NONE;
  
  return pressed;
  
}

void pressButtons() 
{
  
    int button = readButtons();
  
  
    switch(button)
    {
      case RIGHT: 
              displayAndDelay(0, 0, (const char*) &sensorList[state], 500, "");
              break;
      case UP:
              cntUp=cntDown-1;
              cntDown--;
                  if(cntDown == -1) state = 0;
                  else  state = cntUp;
              displayAndDelay(0, 0, (const char*) &sensorList[state], 500, "");
              break;
      case DOWN:
              cntDown=cntUp;
              cntUp++;
              state = cntDown;
              displayAndDelay(0, 0, (const char*) &sensorList[state], 500, "");
              Serial.println("D");
              break;
      case SELECT:
              lcd.clear();
              do
              { 
                  
                  (*sensorFunctions[state]) ();
                   button = readButtons();
              } 
              while((button > RIGHT && button == SELECT) || (button == NONE));
              break;
      
    }

}


void displayAndDelay(int c1, int c2, const char* const list, int del, const char* readings)
{
                char buffer[100];
                if(c1 == c2) lcd.clear();
                lcd.setCursor(c1,c2);
                strcpy_P(buffer,(char*) pgm_read_word(list));
                strcat(buffer,readings);
                lcd.print(buffer);
                delay(del);  
}

void tempHumidSensor()
{
    static char humid[10]; 
    static char temp[10];  
    
                dtostrf(float(dht.readHumidity()), 3, 1, humid);
                dtostrf(float(dht.readTemperature()), 3, 1, temp);

              if (isnan(dht.readTemperature()) || isnan(dht.readHumidity())) 
              {
        
                displayAndDelay(0, 0, (const char*) &msgList[1], 500, "");
              }
              else 
              {
                displayAndDelay(0, 0, (const char*) &msgList[12],NULL,temp);
                displayAndDelay(0, 1, (const char*) &msgList[13], 500, humid);
              }
}

void touchSensor()
{
    
              if(digitalRead(TOUCH_PIN)==HIGH)   
              {
                 displayAndDelay(0, 0, (const char*) &msgList[2], 500, "");
              }
   
              if(digitalRead(TOUCH_PIN)==LOW)  
              {
                displayAndDelay(0, 0, (const char*) &msgList[3], 500, "");
              }
}


void soundSensor(){
   
    int sensorValue = analogRead(A1); 
    
              if(sensorValue>thresholdvalueSnd)
              {
                displayAndDelay(0, 0, (const char*) &msgList[5], 500, "");
              }
              if(sensorValue<=thresholdvalueSnd)
              {
                 displayAndDelay(0, 0, (const char*) &msgList[4], 500, "");
              }
}

void lightSensor()
{
   
    int sensorValue = analogRead(A2); 
    
              if(sensorValue<=thresholdvalueLight)
              {
                 displayAndDelay(0, 0, (const char*) &msgList[6], 500, "");
              }
              if(sensorValue>thresholdvalueLight)
              {
                 displayAndDelay(0, 0, (const char*) &msgList[7], 500, "");
              } 
}

void barometricSensor() 
{    
  static char pressureC[10];  
  
                 dtostrf(mpl115a2.getPressure(), 4, 2, pressureC);
                 displayAndDelay(0, 0, (const char*) &msgList[14], NULL, "");
                 displayAndDelay(0, 1, (const char*) &msgList[15], 500, pressureC);
  
}

void gasSensor()
{
 int sensorValue = analogRead(A3);

              if(sensorValue>thresholdvalueGas)
              {
                 displayAndDelay(0, 0, (const char*) &msgList[8], 500, "");
              }
              if(sensorValue<=thresholdvalueGas)
              {
                 displayAndDelay(0, 0, (const char*) &msgList[9], 500, "");
              } 
}

void pirSensor()
{
  int motionDetect = digitalRead(PIR_PIN);
 
              if (motionDetect == HIGH)
              {
                 displayAndDelay(0, 0, (const char*) &msgList[10], 10, "");
              }
              if (motionDetect == LOW)
              {
                displayAndDelay(0, 0, (const char*) &msgList[11], 10, "");
              }
  
}



 

