#include <EEPROM.h>
#include <math.h>

int RELAIS = 4;
int LED1 = 14;
int LED2 = 12;
int adrBSZ= 0;
long BSZ = 0;
float dp = 0;

void setupSERIAL(){
  delay(1000);
  Serial.begin(115200);
  delay(1000); Serial.println();
  delay(1000); Serial.println("AlphaTrafo");
  delay(1000);
  }

void setupGPIO(){
  pinMode (LED1, OUTPUT);  
  digitalWrite(LED1, LOW);
  pinMode (LED2, OUTPUT);  
  digitalWrite(LED2, LOW);
  pinMode (RELAIS, OUTPUT);
  digitalWrite(RELAIS, LOW);  
  }

void calcDP(){
  float a = 17.271, b = 240.7;
  if (tmpSHT11 >= 0) {b = 237.3;}
  dp = (a * tmpSHT11) / (b + tmpSHT11) + log(humSHT11*0.01);
  dp = (b * dp) / (a - dp);                         // fast drew point
  dp = (round((dp*10))/10);                         // round x.x
  }



void setupEEPROM() { 
  EEPROM.begin(32);
  EEPROM.get(adrBSZ, BSZ);                          // load BSZ 
  if(BSZ<0){                                        // no BSZ?
    EEPROM.put(adrBSZ, BSZ);                        // write 0
    EEPROM.commit();
    delay(10);
    EEPROM.get(adrBSZ, BSZ);                        // load BSZ 
    Serial.println("BSZ -> initialized");  
  } // if(BSZ<0)
  Serial.println("BSZ: " + String(BSZ));   
} // setupEEPROM

void LEDred1000(){
  digitalWrite(LED1, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW); 
}

void LEDgreen1000(){
  digitalWrite(LED2, HIGH);
  delay(1000);
  digitalWrite(LED2, LOW); 
}

void relaisON(){
digitalWrite(RELAIS, HIGH); 
}

void relaisOFF(){
digitalWrite(RELAIS, LOW);
}
