
bool DS18B20 = true;
bool CAPTIVE = false;
bool SHT11 = true;

#include "AlphaSub.h"
#include "AlphaWifi.h"
#include "AlphaSHT11.h"
#include "AlphaDS18B20.h"

int RELAIS = 4;
int LED1 = 14;
int LED2 = 12;

void setup(){
  setupSERIAL();
  setupDS18B20();
  setupCAPTIVE();
  Serial.println("exit setup()");

pinMode (LED1, OUTPUT);  
digitalWrite(LED1, LOW);
pinMode (LED2, OUTPUT);  
digitalWrite(LED2, LOW);
pinMode (RELAIS, OUTPUT);
digitalWrite(RELAIS, LOW);

}

void loop(){
loopCAPTIVE();
readSHT11();
readDS18B20();

       
}




 
