// AlphaTrafo by Frank Wolf - 05/2023 

bool DS18B20 = true;
bool CAPTIVE = false;
bool SHT11 = true;
bool MEASURE = true;
bool actionSetup = false;
bool actionHeat = false;
bool actionReg = false;
bool activeHeat = false;
bool activeReg = false;

float tmpSHT11 = 0;                         // SHT11 - global float tmpSHT11
float humSHT11 = 0;                         // SHT11 - global float humSHT11
float tmpDS18B20 = 0;                       // DS18B20 - global float tmpDS18B20

int tempLimit = 10;
int heatMinutes = 40;
int heatMillis = 0;
int regenerateMinutes = 20;
int regenerateMillis = 0;
int drewPointOffset = 0;

double measurementTimer = millis();

#include "AlphaSub.h"                       // #include <EEPROM.h>, <math.h>
#include "AlphaWifi.h"                      // #include <DNSServer.h>, <WiFi.h>, <AsyncTCP.h>, <ESPAsyncWebSrv.h>
#include "AlphaSHT11.h"                     // #include <SHT1x-ESP.h>
#include "AlphaDS18B20.h"                   // #include <OneWire.h>, <DallasTemperature.h>

void setup(){
  relaisOFF();
  setupSERIAL();                            // SUB - setup serial at 115200 
  setupEEPROM();                            // SUB - setup EEPROM, BMZ init
  setupGPIO();                              // SUB - setup LED, RLY
  setupSHT11();                             // SHT11 - setup SHT11
  Serial.println("SHT11 TMP: " + String(tmpSHT11) + "ºC");
  Serial.println("SHT11 HUM: " + String(humSHT11) + "%");  
  setupDS18B20();                           // DS18B20 - setup DS18B20
  Serial.println("DS18B20: " + String(tmpDS18B20) + "ºC");
  calcDP();                                   // calculate drew point
  Serial.println("TP: " + String(dp) + "ºC"); 
  setupCAPTIVE();                           // WIFI - setup captive
  Serial.println("- - - - -");              // exit setup
  measurementTimer = millis();
}

void loop(){
  loopCAPTIVE();             // active captive                            

  // make measurement, calculate drew point, take action
  if (((millis() - measurementTimer) > 10000) && (MEASURE)) { 
    LEDredgreen();
    readSHT11();                                // read SHT11
    Serial.println("SHT11 TMP: " + String(tmpSHT11) + "ºC");
    Serial.println("SHT11 HUM: " + String(humSHT11) + "%");   
    readDS18B20();                              // read DS18B20
    Serial.println("DS18B20: " + String(tmpDS18B20) + "ºC");
    calcDP();                                   // calculate drew point
    Serial.println("TP: " + String(dp) + "ºC"); 
    Serial.println();
    measurementTimer = millis();
    MEASURE = false;
    actionHeat = true;
  } // exit make measurement

  if (actionHeat) {                             // action heat
    if (!activeHeat) {                          // setup heat      
      Serial.println("ACTION - heizen");   
      heatMillis = millis() + (heatMinutes * 300);
      relaisON();
      activeHeat = true; }
    if (heatMillis < millis()) {                // active heat 
      Serial.println("STOPP - heizen"); 
      relaisOFF();
      activeHeat = false;
      actionHeat = false;
      actionReg = true; }
  } // exit action heat

  if (actionReg) {                              // action recovery
    if (!activeReg) {                           // setup recovery             
      Serial.println("ACTION - regenerieren");   
      regenerateMillis = millis() + (regenerateMinutes * 600);
      activeReg = true; }
    if (regenerateMillis < millis()) {          // active recovery 
      Serial.println("STOPP - regenerieren"); 
      Serial.println(" ");
      activeReg = false;
      actionReg = false;
      MEASURE = true;
      measurementTimer= millis(); }
  } // exit action heat

} // exit loop



  





 
