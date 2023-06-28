// AlphaTrafo by Frank Wolf - 06/2023 
// the code is documentation enough !

bool DS18B20 = true;
bool WEBSERVER = true;
bool SHT11 = true;
bool MEASURE = false;
bool GOSLEEP = false;
bool actionSetup = false;
bool actionHeat = false;
bool actionReg = false;
bool activeHeat = false;
bool activeReg = false;

float tmpSHT11 = 0;                         // SHT11 - global float tmpSHT11
float humSHT11 = 0;                         // SHT11 - global float humSHT11
float tmpDS18B20 = 0;                       // DS18B20 - global float tmpDS18B20

long BMZ = 1;                 
int heatMinutes = 2;          
int regenerateMinutes = 1;     
int tempLimit = 12;         
int heatCycles = 0;
int regenerateCycles = 0;
int drewPointOffset = 2;

unsigned long wifiAvailable = 70000;
unsigned long ms = millis();
unsigned long mac_adr;
String sn;

#define uS_TO_S_FACTOR 1000000              // conversion micro to seconds 
#define TIME_TO_SLEEP  10                   // 30 secounds at release
RTC_DATA_ATTR int bootCount = 0;
esp_sleep_wakeup_cause_t wakeup_reason;

#include "AlphaSub.h"                       // #include <EEPROM.h>, <math.h>
#include "AlphaWifi.h"                      // #include <DNSServer.h>, <WiFi.h>, <AsyncTCP.h>, <ESPAsyncWebSrv.h>
#include "AlphaSHT11.h"                     // #include <SHT1x-ESP.h>
#include "AlphaDS18B20.h"                   // #include <OneWire.h>, <DallasTemperature.h>

void setup(){
  delay(50);                    
  relaisOFF();                              // SUB - better be safe than sorry
  delay(500);
  setupGPIO();                              // SUB - setup LED, RLY  
  delay(500);
  Serial.begin(115200);                     // setup serial at 115200 
  delay(500);
  
  MacSerial();
  Serial.println("SN: " + sn);              // enter setup
 
  wifi_main();                              // Start Wifi, enable hooks

  delay(1000); LEDredgreenfast();  
  Serial.println("- - - - -");              // enter setup

   
  // setModemSleep();                       // SUB - turn off WIFI/BT set CPU to 40 Mhz
  EEPROM.begin(32);
  wakeup_reason = esp_sleep_get_wakeup_cause(); // preperation for deep sleep
  if (wakeup_reason != ESP_SLEEP_WAKEUP_TIMER)  // skipping init of sensors
  {
    setupBlink();                           // SUB - setup blink 3x, write AlphaTrafo
    setupEEPROM();                          // SUB - setup EEPROM, BMZ init
    readSHT11();                            // SHT11 - setup SHT11
    //delay(1000); LEDredgreenfast(); 
   // readSHT11();                            // read SHT11 
   // Serial.println("HUM Luft : " + String(humSHT11) + "%"); 
    //Serial.println("TMP Luft : " + String(tmpSHT11) + "ºC");
   // readDS18B20();                          // read DS18B20
   // Serial.println("TMP Wand: " + String(tmpDS18B20) + "ºC");
   // calcDP();                               // calculate drew point
   // delay(1000); LEDredgreenfast(); 
   // Serial.println("TP: " + String(dp) + "ºC"); 
    //delay(1000); LEDredgreenfast(); 
    Serial.println("- - - - -");              // exit setup
  }
}

void loop(){
  
  if (WEBSERVER) {
    if (millis() > wifiAvailable) {
      WiFi.disconnect();
      WEBSERVER = false;
      Serial.println("WiFi disconnect"); 
      MEASURE = true;
      GOSLEEP = true;
    }
    if ((millis() - SensorUpdate) >= 5000) {
      SensorUpdate = millis();
      LEDredgreen();
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, LOW);
      readSHT11();                            // read SHT1
      readDS18B20();                          // read DS18B20
      calcDP();                               // calculate drew point
      int numClients = WiFi.softAPgetStationNum();
      if (numClients > 0) {
        wifiAvailable = millis() + 60000;     // keep wifi online for 60 more secounds
      }
      // Serial.println("Number of clients connected: " + String(numClients));
    }
    
    server.handleClient();                  // you must call this handleClient repeatidly
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, LOW);
  }

    
 // loopCAPTIVE();                            // active captive        
  if (MEASURE) {
    LEDredgreen();
    readSHT11();                            // read SHT11
    Serial.println("HUM Luft : " + String(humSHT11) + "%"); 
    Serial.println("TMP Luft : " + String(tmpSHT11) + "ºC");
    readDS18B20();                          // read DS18B20
    Serial.println("TMP Wand: " + String(tmpDS18B20) + "ºC");
    calcDP();                               // calculate drew point
    Serial.println("TP: " + String(dp) + "ºC"); 
    if (tmpDS18B20 < (dp + drewPointOffset)) {
      MEASURE = false; actionHeat = true; 
      Serial.println("Auslösung: Wand " + String(tmpDS18B20) + " < Taupunkt " + String(dp) + " + Anpassung " + String(drewPointOffset)); 
    } else if (tmpDS18B20 < tempLimit) {
      MEASURE = false; actionHeat = true;
      Serial.println("Auslösung: Wand " + String(tmpDS18B20) + " < Temperaturlimit " + String(tempLimit)); 
    }
    Serial.println();
  }
  if (actionHeat) {
    LEDredredred();
  }
  if (actionReg) {
    LEDredred();
  }

  if (actionHeat) {                             // action heat
    if (!activeHeat) {                          // setup heat      
      heatCycles = heatMinutes * 2;
      Serial.println("ACTION - heizen " + String(heatMinutes) + " Minuten (" + String(heatCycles) + " Zyklen)");
      relaisON();
      activeHeat = true; }
    if (heatCycles < 1) {                       // active heat 
      Serial.println("STOPP - heizen"); 
      relaisOFF();
      EEPROM.get(0, BMZ);                  // get BMZ
      BMZ = BMZ + heatMinutes;                  // add BMZ
      EEPROM.put(0, BMZ);                  // store BMZ                        
      EEPROM.commit(); delay(10);               // commit store  
      activeHeat = false;
      actionHeat = false;
      actionReg = true; }
      --heatCycles;  
  } // exit action heat

  if (actionReg) {                              // action recovery
    if (!activeReg) {                           // setup recovery    
      regenerateCycles = regenerateMinutes * 2;         
      Serial.println("ACTION - regenerieren " + String(regenerateMinutes) + " Minuten (" + String(regenerateCycles) + " Zyklen)"); 
      activeReg = true; }
    if (regenerateCycles < 1) {          // active recovery 
      Serial.println("STOPP - regenerieren"); 
      Serial.println(" ");
      activeReg = false;
      actionReg = false;
      MEASURE = true; }
    --regenerateCycles;
  } // exit action heat

  espSleep();

} // exit loop











 
