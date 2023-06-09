// AlphaTrafo by Frank Wolf - 06/2023 
// the code is documentation enough !

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

void print_wakeup_reason(){
  wakeup_reason = esp_sleep_get_wakeup_cause();
  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

void espSleep(){
  if(GOSLEEP){
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    //Serial.println("Sleep for " + String(TIME_TO_SLEEP) + " Seconds");
    delay(100); Serial.flush(); delay(100); 
    //esp_deep_sleep_start();
    esp_light_sleep_start();
  }
}

void setupEEPROM() { 
    EEPROM.get(adrBMZ, BMZ);                         // load BMZ 
  if(BMZ<0){                                        // no BMZ?
    EEPROM.put(adrBMZ, BMZ);                        // write 0
    EEPROM.commit();
    delay(10);
    EEPROM.get(adrBMZ, BMZ);                        // load BMZ 
    Serial.println("BMZ -> initialized");  
  } // if(BMZ<0)
  Serial.println("BMZ: " + String(BMZ));   
} // setupEEPROM

void setupBlink(){
  delay(1000); LEDredgreenfast();  
  delay(1000); LEDredgreenfast();  Serial.println(); 
  delay(1000); LEDredgreenfast();  Serial.println("AlphaTrafo");
  delay(1000); LEDredgreenfast();
}

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

void setModemSleep() {
    WiFi.setSleep(true);
    setCpuFrequencyMhz(80);
}
 
void wakeModemSleep() {
    setCpuFrequencyMhz(240);
}
 
void relaisOFF(){
digitalWrite(RELAIS, LOW);
}
