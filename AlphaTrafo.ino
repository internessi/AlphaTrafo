// AlphaTrafo by Frank Wolf - 03/2023 

bool DS18B20 = true;
bool CAPTIVE = false;
bool SHT11 = true;

float tmpSHT11 = 0;                         // SHT11 - global float tmpSHT11
float humSHT11 = 0;                         // SHT11 - global float humSHT11
float tmpDS18B20 = 0;                       // DS18B20 - global float tmpDS18B20

int templimit = 10;
int heat = 40;
int regenerate = 20;

double measurementTIMER= millis();

#include "AlphaSub.h"                       // #include <EEPROM.h>, <math.h>
#include "AlphaWifi.h"                      // #include <DNSServer.h>, <WiFi.h>, <AsyncTCP.h>, <ESPAsyncWebSrv.h>
#include "AlphaSHT11.h"                     // #include <SHT1x-ESP.h>
#include "AlphaDS18B20.h"                   // #include <OneWire.h>, <DallasTemperature.h>

void setup(){
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
}

void loop(){
  loopCAPTIVE();                              // active captive

  if ((millis() - measurementTIMER) > 10000) { 
    LEDredgreen();
    readSHT11();                                // read SHT11
    Serial.println("SHT11 TMP: " + String(tmpSHT11) + "ºC");
    Serial.println("SHT11 HUM: " + String(humSHT11) + "%");   
    readDS18B20();                              // read DS18B20
    Serial.println("DS18B20: " + String(tmpDS18B20) + "ºC");
    calcDP();                                   // calculate drew point
    Serial.println("TP: " + String(dp) + "ºC"); 
    Serial.println();
    measurementTIMER = millis();
  } // looptimer 

}



  





 
