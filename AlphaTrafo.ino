bool DS18B20 = false;
bool CAPTIVE = false;
bool SHT11 = false;

#include "AlphaWifi.h"
#include "AlphaSHT11.h"
#include "AlphaDS18B20.h"


void setup(){
  setupSERIAL();

  setupDS18B20();
  
  setupCAPTIVE();
 
  Serial.println("exit setup()");
}

void loop(){

loopCAPTIVE();
       
}
