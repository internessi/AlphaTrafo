// AlphaTrafo by Frank Wolf - 06/2023 
// the code is documentation enough !

#include <WebServer.h>  // standard library
#include "AlphaHtml.h"                       // .h file that stores your html page code

// here you post web pages to your homes intranet which will make page debugging easier
// as you just need to refresh the browser as opposed to reconnection to the web server
#define USE_INTRANET

// replace this with your homes intranet connect parameters
#define LOCAL_SSID "ALARM4U"
#define LOCAL_PASS "Wolf1212"

// once  you are read to go live these settings are what you client will connect to
#define AP_SSID "TestWebSite"
#define AP_PASS "023456789"


uint32_t SensorUpdate = 0;


// the XML array size needs to be bigger that your maximum expected size. 2048 is way too big for this example
char XML[1024];

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

void Bsz_Reset() {
  BMZ = 0; LEDgreengreen(); server.send(200, "text/plain", ""); }
  
void ProcessHeat_5() {
  heatMinutes = 5; LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessHeat_10() {
  heatMinutes = 10; LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessHeat_20() {
  heatMinutes = 20; LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessHeat_30() {
  heatMinutes = 30; LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessHeat_40() {
  heatMinutes = 40; LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessHeat_50() {
  heatMinutes = 50; LEDgreengreen(); server.send(200, "text/plain", ""); }  
  
void ProcessReg_5() {
  regenerateMinutes = 5; LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessReg_10() {
  regenerateMinutes = 10; LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessReg_20() {
  regenerateMinutes = 20; LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessReg_30() {
  regenerateMinutes = 30; LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessReg_40() {
  regenerateMinutes = 40; LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessReg_50() {
  regenerateMinutes = 50; LEDgreengreen(); server.send(200, "text/plain", ""); }  

  
void ProcessTmp_6() {
  tempLimit = 6; LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessTmp_8() {
  tempLimit = 8; LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessTmp_10() {
  tempLimit = 10; LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessTmp_12() {
  tempLimit = 12; LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessTmp_14() {
  tempLimit = 14; LEDgreengreen(); server.send(200, "text/plain", ""); }
void ProcessTmp_16() {
  tempLimit = 16; LEDgreengreen(); server.send(200, "text/plain", ""); }  

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

  float i;
  i = (float)BMZ / 60.00000; 
  Serial.println(i);    
  BSZ = int(i);
  BSZM = (i - BSZ) * 60;

  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

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
  Serial.println(XML);

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
