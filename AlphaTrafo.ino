// AlphaTrafo by Frank Wolf - 03/2023 

bool DS18B20 = true;
bool CAPTIVE = false;
bool SHT11 = true;

#include "AlphaWifi.h"                      // #include <DNSServer.h>, <WiFi.h>, <AsyncTCP.h>, <ESPAsyncWebSrv.h>
#include "AlphaSHT11.h"                     // #include <SHT1x-ESP.h>
#include "AlphaDS18B20.h"                   // #include <OneWire.h>, <DallasTemperature.h>
#include "AlphaSub.h"                       // #include <EEPROM.h>, <math.h>

void setup(){
  setupSERIAL();                            // SUB - setup serial at 115200 
  setupEEPROM();                            // SUB - setup EEPROM, BSZ init
  setupGPIO();                              // SUB - setup LED, RLY
  setupSHT11();                             // SHT11 - setup SHT11
  setupDS18B20();                           // DS18B20 - setup DS18B20
  setupCAPTIVE();                           // WIFI - setup captive
  Serial.println("- - - - -");              // exit setup
}

void loop(){

  delay(10000);   
  LEDred1000();
  Serial.println();
  
  loopCAPTIVE();                              // active captive
  readSHT11();                                // read SHT11
  readDS18B20();                              // read DS18B20
  calcDP();                                   // calculate drew point
  Serial.println("TP: " + String(dp) + "ºC"); 
  Serial.println(" "); 

  
}



  





 
