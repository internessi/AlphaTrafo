// AlphaTrafo by Frank Wolf - 06/2023 
// the code is documentation enough !

#include <WebServer.h>  // standard library
#include "AlphaHtml.h"                       // .h file that stores your html page code

// here you post web pages to your homes intranet which will make page debugging easier
// as you just need to refresh the browser as opposed to reconnection to the web server
// #define USE_INTRANET

// replace this with your homes intranet connect parameters
#define LOCAL_SSID "ALARM4U"
#define LOCAL_PASS "Wolf1212"

uint32_t SensorUpdate = 0;

// the XML array size needs to be bigger that your maximum expected size. 2048 is way too big for this example
char XML[256];

// just some buffer holder for char operations
char buf[32];

// variable for the IP reported when you connect to your homes intranet (during debug mode)
IPAddress Actual_IP;

// definitions of your desired intranet created by the ESP32
IPAddress PageIP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip;

// gotta create a server
WebServer server(80);

void Bsz_Reset() { BMZ = 0;   // set BMZ to 0, save in eeprom
  EEPROM.put(0, BMZ); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }
  
void ProcessHeat_5() {heatMinutes = 5; 
  EEPROM.put(6, heatMinutes); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessHeat_10() {heatMinutes = 10; 
  EEPROM.put(6, heatMinutes); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessHeat_20() {heatMinutes = 20; 
  EEPROM.put(6, heatMinutes); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessHeat_30() {heatMinutes = 30; 
  EEPROM.put(6, heatMinutes); EEPROM.commit(); delay(10); 
  LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessHeat_40() {heatMinutes = 40;  
  EEPROM.put(6, heatMinutes); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessHeat_50() {heatMinutes = 50;  
  EEPROM.put(6, heatMinutes); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }  
  
void ProcessReg_5() {regenerateMinutes = 5;   
  EEPROM.put(10, regenerateMinutes); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessReg_10() {regenerateMinutes = 10;   
  EEPROM.put(10, regenerateMinutes); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessReg_20() {regenerateMinutes = 20;   
  EEPROM.put(10, regenerateMinutes); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessReg_30() {regenerateMinutes = 30;   
  EEPROM.put(10, regenerateMinutes); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessReg_40() {regenerateMinutes = 40;   
  EEPROM.put(10, regenerateMinutes); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessReg_50() {regenerateMinutes = 50;   
  EEPROM.put(10, regenerateMinutes); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }  

  
void ProcessTmp_6() {tempLimit = 6;   
  EEPROM.put(14, tempLimit); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessTmp_8() {tempLimit = 8;   
  EEPROM.put(14, tempLimit); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessTmp_10() {tempLimit = 10;   
  EEPROM.put(14, tempLimit); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessTmp_12() {tempLimit = 12;   
  EEPROM.put(14, tempLimit); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessTmp_14() {tempLimit = 14;   
  EEPROM.put(14, tempLimit); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessTmp_16() {tempLimit = 16;   
  EEPROM.put(14, tempLimit); EEPROM.commit(); delay(10);
  LEDgreengreen(); server.send(200, "text/plain", ""); }

// code to send the main web page
// PAGE_MAIN is a large char defined in SuperMon.h
void SendWebsite() {
  Serial.println("sending web page");
  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/html", PAGE_MAIN);
}

// code to send the main web page
// I avoid string data types at all cost hence all the char mainipulation code
void SendXML() {

  wifiAvailable = millis() + 60000;     // keep wifi online for 60 more secounds

  float i;
  i = (float)BMZ / 60.00000;     
  BSZ = int(i);
  BSZM = (i - BSZ) * 60;

  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");
  sprintf(buf, "<A0>%s</A0>\n", sn.c_str());
  strcat(XML, buf);   
  sprintf(buf, "<S0>%d.%d</S0>\n", (int) (tmpSHT11), abs((int) (tmpSHT11 * 10)  - ((int) (tmpSHT11) * 10)));
  strcat(XML, buf);
  sprintf(buf, "<S1>%d.%d</S1>\n", (int) (humSHT11), abs((int) (humSHT11 * 10)  - ((int) (humSHT11) * 10)));
  strcat(XML, buf);
  sprintf(buf, "<S2>%d.%d</S2>\n", (int) (tmpDS18B20), abs((int) (tmpDS18B20 * 10)  - ((int) (tmpDS18B20) * 10)));
  strcat(XML, buf);
  sprintf(buf, "<H0>%d</H0>\n", (int) (heatMinutes));
  strcat(XML, buf);
  sprintf(buf, "<R0>%d</R0>\n", (int) (regenerateMinutes));
  strcat(XML, buf);
  sprintf(buf, "<B0>%d</B0>\n", (int) (BSZ));
  strcat(XML, buf);
  sprintf(buf, "<B1>%d</B1>\n", (int) (BSZM));
  strcat(XML, buf);
  sprintf(buf, "<T0>%d</T0>\n", (int) (tempLimit));
  strcat(XML, buf);
  strcat(XML, "</Data>\n");
  // wanna see what the XML code looks like?
  // actually print it to the serial monitor and use some text editor to get the size
  // then pad and adjust char XML[2048]; above
  Serial.println("XML: " + String(tmpSHT11) + "ºC - " + String(humSHT11) + "% - " + String(tmpDS18B20) + "ºC - L: " + String(tempLimit) + "ºC - H" 
    + String(heatMinutes) + " - R" + String(regenerateMinutes) + " - " + String(BSZ) + "h " + String(BSZM) + "m");
  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/xml", XML);
  
}

// I think I got this code from the wifi example
void printWifiStatus() {

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("Open http://");
  Serial.println(ip);
}

// end of code

void wifi_main(){
    // WIFI - WIFI - WIFI - WIFI - WIFI 
    // if your web page or XML are large, you may not get a call back from the web page
    // and the ESP will think something has locked up and reboot the ESP
    // not sure I like this feature, actually I kinda hate it
    // disable watch dog timer 0
    disableCore0WDT();
    // maybe disable watch dog timer 1 if needed
    //  disableCore1WDT();
    // just an update to progress
    Serial.println("starting server");

//   WiFi.begin(LOCAL_SSID, LOCAL_PASS);
//    while (WiFi.status() != WL_CONNECTED) {
//      delay(500);
//      Serial.print(".");
//    }
//    Serial.print("IP address: "); Serial.println(WiFi.localIP());
//    Actual_IP = WiFi.localIP();

    String APSSID = "Trafosteuerung " + sn;
    const char *ssid = APSSID.c_str();
    const char *password = "12345678";

    WiFi.softAP(ssid, password);
    delay(100);
    WiFi.softAPConfig(PageIP, gateway, subnet);
    delay(100);
    Actual_IP = WiFi.softAPIP();
    Serial.print("IP address: "); Serial.println(Actual_IP);

    // printWifiStatus();
    // these calls will handle data coming back from your web page
    // this one is a page request, upon ESP getting / string the web page will be sent
    server.on("/", SendWebsite);
    // upon esp getting /XML string, ESP will build and send the XML, this is how we refresh
    // just parts of the web page
    server.on("/xml", SendXML);
    server.on("/BSZ_RESET", Bsz_Reset);
    server.on("/HEAT_5", ProcessHeat_5);
    server.on("/HEAT_10", ProcessHeat_10);
    server.on("/HEAT_20", ProcessHeat_20);
    server.on("/HEAT_30", ProcessHeat_30);
    server.on("/HEAT_40", ProcessHeat_40);
    server.on("/HEAT_50", ProcessHeat_50);
    server.on("/REG_5", ProcessReg_5);
    server.on("/REG_10", ProcessReg_10);
    server.on("/REG_20", ProcessReg_20);
    server.on("/REG_30", ProcessReg_30);
    server.on("/REG_40", ProcessReg_40);
    server.on("/REG_50", ProcessReg_50);  
    server.on("/TMP_6", ProcessTmp_6);
    server.on("/TMP_8", ProcessTmp_8);
    server.on("/TMP_10", ProcessTmp_10);
    server.on("/TMP_12", ProcessTmp_12);
    server.on("/TMP_14", ProcessTmp_14);
    server.on("/TMP_16", ProcessTmp_16);  
    // finally begin the server
    server.begin();
  // END WIFI - END WIFI - END WIFI - END WIFI
}
