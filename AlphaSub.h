// AlphaTrafo by Frank Wolf - 06/2023 
// the code is documentation enough !

#include <Arduino.h>                                /* Start ESP32 */
#include <EEPROM.h>
#include <math.h>
#include <WiFi.h>       // standard library

int BSZ = 0;
int BSZM = 0;
float dp = 0;

int RELAIS = 4;
int LED1 = 14;
int LED2 = 12;

void LEDredgreenfast(){
  digitalWrite(LED1, HIGH);
  delay(75);
  digitalWrite(LED1, LOW); 
  digitalWrite(LED2, HIGH);
  delay(75);
  digitalWrite(LED2, LOW); 
}

String arbitraryBase( unsigned long value, int base) {
    static char baseChars[] = "ZWAFBCDEFGHIJKLMNZPFRSTUV71234WXYZABCDEF7123456789GHIJKLM6789NZPHRSTUVWXYZPB";
    String result = "";
    do {
         result = String(baseChars[value % base]) + result;  // Add on the left
         value /= base;
         } while (value != 0);
    return result;
}

void MacSerial() {
  uint8_t baseMac[7];
  esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
  mac_adr = (baseMac[2]) + (baseMac[3] * 213) + (baseMac[4] * 231 * 253) + (baseMac[5] * 237 * 219 * 251);
  mac_adr = mac_adr + 1321754191;
  sn = arbitraryBase(mac_adr, 68);
  if (sn.length() > 5) {
    sn = sn.substring(0, 5);
  }
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
// long BMZ                 0, 1, 2, 3  
// int heatMinute           6, 7
// int regenerateMinutes    10, 11
// int tempLimit            14, 15
  EEPROM.get(0, BMZ);                               // load BMZ 
  if(BMZ<0){                                        // no BMZ?
    BMZ = 0;                 
    EEPROM.put(0, BMZ);                             // write 0
    EEPROM.commit();
    delay(10);
    EEPROM.get(0, BMZ);                             // load BMZ 
    Serial.println("BMZ -> initialized");  
  } // if(BMZ<1)
  Serial.println("BMZ: " + String(BMZ)); 
   
  EEPROM.get(6, heatMinutes);                        // load 
  if(heatMinutes<1){                                 // nothing?
    heatMinutes = 2;          
    EEPROM.put(6, heatMinutes);                      // write 
    EEPROM.commit();
    delay(10);
    EEPROM.get(6, heatMinutes);                      // load  
    Serial.println("heatMinutes -> initialized");  
  } // if(heatMinutes<1)
  Serial.println("heatMinutes: " + String(heatMinutes));  
  
  EEPROM.get(10, regenerateMinutes);                 // load  
  if(regenerateMinutes<1){                          // nothing?
    regenerateMinutes = 1;          
    EEPROM.put(10, regenerateMinutes);               // write 
    EEPROM.commit();
    delay(10);
    EEPROM.get(10, regenerateMinutes);               // load BMZ 
    Serial.println("regenerateMinutes -> initialized");  
  } // if(regenerateMinutes<1)
  Serial.println("regenerateMinutes: " + String(regenerateMinutes));  
  
  EEPROM.get(14, tempLimit);                         // load 
  if(tempLimit <1){                                 // nothing?
    tempLimit = 12;  
    EEPROM.put(14, tempLimit);                       // write 
    EEPROM.commit();
    delay(10);
    EEPROM.get(14, tempLimit);                       // load 
    Serial.println("tempLimit  -> initialized");  
  } // if(tempLimit<1)
  Serial.println("tempLimit: " + String(tempLimit));  
    
} // setupEEPROM

void setupBlink(){
  delay(1000); LEDredgreenfast();  
  delay(1000); LEDredgreenfast();  Serial.println(); 
  delay(1000); LEDredgreenfast();  Serial.println("AlphaTrafo");
  delay(1000); LEDredgreenfast();
}

void LEDred1000(){
  digitalWrite(LED2, LOW); 
  digitalWrite(LED1, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW); 
}

void LEDgreen1000(){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(1000);
  digitalWrite(LED2, LOW); 
}

void LEDredgreen(){
  digitalWrite(LED2, LOW); 
  digitalWrite(LED1, HIGH);
  delay(300);
  digitalWrite(LED1, LOW); 
  digitalWrite(LED2, HIGH);
  delay(300);
  digitalWrite(LED2, LOW); 
}

void LEDredred(){
  digitalWrite(LED2, LOW); 
  digitalWrite(LED1, HIGH);
  delay(300);
  digitalWrite(LED1, LOW); 
  delay(300);
  digitalWrite(LED1, HIGH);
  delay(300);
  digitalWrite(LED1, LOW); 
}


void LEDgreengreen(){
  digitalWrite(LED2, HIGH);
  delay(300);
  digitalWrite(LED2, LOW); 
  delay(300);
  digitalWrite(LED2, HIGH);
  delay(300);
  digitalWrite(LED2, LOW); 
}

void LEDredredred(){
  digitalWrite(LED2, LOW); 
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
