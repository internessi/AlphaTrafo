#include <EEPROM.h>
#include <math.h>

int RELAIS = 4;
int LED1 = 14;
int LED2 = 12;
int adrBMZ= 0;
long BMZ = 0;
float dp = 0;

void LEDredgreenfast(){
  digitalWrite(LED1, HIGH);
  delay(75);
  digitalWrite(LED1, LOW); 
  digitalWrite(LED2, HIGH);
  delay(75);
  digitalWrite(LED2, LOW); 
}

void setupSERIAL(){ 
  delay(1000); LEDredgreenfast();  Serial.begin(115200);
  delay(1000); LEDredgreenfast();  Serial.println(); 
  delay(1000); LEDredgreenfast();  Serial.println("AlphaTrafo");
  delay(1000); LEDredgreenfast();
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
  EEPROM.get(adrBMZ, BMZ);                          // load BMZ 
  if(BMZ<0){                                        // no BMZ?
    EEPROM.put(adrBMZ, BMZ);                        // write 0
    EEPROM.commit();
    delay(10);
    EEPROM.get(adrBMZ, BMZ);                        // load BMZ 
    Serial.println("BMZ -> initialized");  
  } // if(BMZ<0)
  Serial.println("BMZ: " + String(BMZ));   
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

void LEDredgreen(){
  digitalWrite(LED1, HIGH);
  delay(300);
  digitalWrite(LED1, LOW); 
  digitalWrite(LED2, HIGH);
  delay(300);
  digitalWrite(LED2, LOW); 
}

void LEDredred(){
  digitalWrite(LED1, HIGH);
  delay(300);
  digitalWrite(LED1, LOW); 
  delay(300);
  digitalWrite(LED1, HIGH);
  delay(300);
  digitalWrite(LED1, LOW); 
}

void LEDredredred(){
  digitalWrite(LED1, HIGH);
  delay(200);
  digitalWrite(LED1, LOW); 
  delay(200);
  digitalWrite(LED1, HIGH);
  delay(200);
  digitalWrite(LED1, LOW); 
  delay(200);
  digitalWrite(LED1, HIGH);
  delay(200);
  digitalWrite(LED1, LOW); 
}
void relaisON(){
digitalWrite(RELAIS, HIGH); 
}

void relaisOFF(){
digitalWrite(RELAIS, LOW);
}
