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

int tempLimit = 12;
int heatMinutes = 2;
int heatCycles = 0;
int regenerateMinutes = 1;
int regenerateCycles = 0;
int drewPointOffset = 2;

#define uS_TO_S_FACTOR 1000000              // conversion micro to seconds 
#define TIME_TO_SLEEP  10                   // 30 secounds at release
RTC_DATA_ATTR int bootCount = 0;
esp_sleep_wakeup_cause_t wakeup_reason;

#include "AlphaWifi.h"                      // #include <DNSServer.h>, <WiFi.h>, <AsyncTCP.h>, <ESPAsyncWebSrv.h>
#include "AlphaSub.h"                       // #include <EEPROM.h>, <math.h>
#include "AlphaSHT11.h"                     // #include <SHT1x-ESP.h>
#include "AlphaDS18B20.h"                   // #include <OneWire.h>, <DallasTemperature.h>


void setup(){
                    
  relaisOFF();                              // SUB - better be safe than sorry
  setupGPIO();                              // SUB - setup LED, RLY  
  Serial.begin(115200);                     // setup serial at 115200 

  // if your web page or XML are large, you may not get a call back from the web page
  // and the ESP will think something has locked up and reboot the ESP
  // not sure I like this feature, actually I kinda hate it
  // disable watch dog timer 0
  disableCore0WDT();

  // maybe disable watch dog timer 1 if needed
  //  disableCore1WDT();

  // just an update to progress
  Serial.println("starting server");

  // if you have this #define USE_INTRANET,  you will connect to your home intranet, again makes debugging easier
#ifdef USE_INTRANET
  WiFi.begin(LOCAL_SSID, LOCAL_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
  Actual_IP = WiFi.localIP();
#endif

  // if you don't have #define USE_INTRANET, here's where you will creat and access point
  // an intranet with no internet connection. But Clients can connect to your intranet and see
  // the web page you are about to serve up
#ifndef USE_INTRANET
  WiFi.softAP(AP_SSID, AP_PASS);
  delay(100);
  WiFi.softAPConfig(PageIP, gateway, subnet);
  delay(100);
  Actual_IP = WiFi.softAPIP();
  Serial.print("IP address: "); Serial.println(Actual_IP);
#endif

  printWifiStatus();


  // these calls will handle data coming back from your web page
  // this one is a page request, upon ESP getting / string the web page will be sent
  server.on("/", SendWebsite);

  // upon esp getting /XML string, ESP will build and send the XML, this is how we refresh
  // just parts of the web page
  server.on("/xml", SendXML);

  // upon ESP getting /UPDATE_SLIDER string, ESP will execute the UpdateSlider function
  // same notion for the following .on calls
  // add as many as you need to process incoming strings from your web page
  // as you can imagine you will need to code some javascript in your web page to send such strings
  // this process will be documented in the SuperMon.h web page code
  server.on("/UPDATE_SLIDER", UpdateSlider);
  server.on("/BUTTON_0", ProcessButton_0);
  server.on("/BUTTON_1", ProcessButton_1);

  // finally begin the server
  server.begin();


  delay(1000); LEDredgreenfast();  
  Serial.println("- - - - -");              // enter setup
  
  // setModemSleep();                          // SUB - turn off WIFI/BT set CPU to 40 Mhz
  EEPROM.begin(32);
  wakeup_reason = esp_sleep_get_wakeup_cause(); // preperation for deep sleep
  if (wakeup_reason != ESP_SLEEP_WAKEUP_TIMER)  // skipping init of sensors
  {
    setupBlink();                           // SUB - setup blink 3x, write AlphaTrafo
    setupEEPROM();                          // SUB - setup EEPROM, BMZ init
    readSHT11();                            // SHT11 - setup SHT11
    delay(1000); LEDredgreenfast(); 
    readSHT11();                            // read SHT11 
    Serial.println("HUM Luft : " + String(humSHT11) + "%"); 
    Serial.println("TMP Luft : " + String(tmpSHT11) + "ºC");
    readDS18B20();                          // read DS18B20
    Serial.println("TMP Wand: " + String(tmpDS18B20) + "ºC");
    calcDP();                               // calculate drew point
    delay(1000); LEDredgreenfast(); 
    Serial.println("TP: " + String(dp) + "ºC"); 
 //   setupCAPTIVE();                         // WIFI - setup captive
    delay(1000); LEDredgreenfast(); 
    Serial.println("- - - - -");            // exit setup
  }
}

void loop(){

  if (WEBSERVER) {
    if ((millis() - SensorUpdate) >= 10000) {
      //Serial.println("Reading Sensors");
      SensorUpdate = millis();
      LEDredgreen();
      readSHT11();                            // read SHT11
      Serial.println("HUM Luft : " + String(humSHT11) + "%"); 
      Serial.println("TMP Luft : " + String(tmpSHT11) + "ºC");
      readDS18B20();                          // read DS18B20
      Serial.println("TMP Wand: " + String(tmpDS18B20) + "ºC");
      calcDP();                               // calculate drew point
      Serial.println("TP: " + String(dp) + "ºC"); 
    }
  }
  // no matter what you must call this handleClient repeatidly--otherwise the web page
  // will not get instructions to do something
  server.handleClient();


  
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
      EEPROM.get(adrBMZ, BMZ);                  // get BMZ
      BMZ = BMZ + heatMinutes;                  // add BMZ
      EEPROM.put(adrBMZ, BMZ);                  // store BMZ                        
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







 
