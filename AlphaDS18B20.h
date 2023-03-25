#include <OneWire.h>
#include <DallasTemperature.h>

const int oneWireBus = 13;            // GPIO where the DS18B20  
OneWire oneWire(oneWireBus);          // Setup a oneWire instance
DallasTemperature sensors(&oneWire);  // Pass our oneWire reference

float tmpDS18B20 = 0;

void readDS18B20(){
  if(DS18B20){
    sensors.begin();
    sensors.requestTemperatures(); 
    tmpDS18B20 = (round((sensors.getTempCByIndex(0)*10))/10);
    Serial.println("DS18B20: " + String(tmpDS18B20) + "ºC");
    }// end DS18B20
}

void setupDS18B20(){
  if(DS18B20){
    readDS18B20();
    Serial.println("DS18B20 -> initialized");
    }// end DS18B20
}
