#include <OneWire.h>
#include <DallasTemperature.h>

const int oneWireBus = 13;            // GPIO where the DS18B20  
OneWire oneWire(oneWireBus);          // Setup a oneWire instance
DallasTemperature sensors(&oneWire);  // Pass our oneWire reference

void setupDS18B20(){
  if(DS18B20){
    sensors.begin();
    Serial.println("Starting DS18B20 sensor");
    delay(1000);
    sensors.requestTemperatures(); 
    float temperatureC = sensors.getTempCByIndex(0);
    float temperatureF = sensors.getTempFByIndex(0);
    Serial.print(temperatureC);
    Serial.println("ºC");
    Serial.print(temperatureF);
    Serial.println("ºF");
    }// end DS18B20
}


void readDS18B20(){
  if(DS18B20){
    sensors.begin();
    sensors.requestTemperatures(); 
    float temperatureC = sensors.getTempCByIndex(0);
    float temperatureF = sensors.getTempFByIndex(0);
    Serial.print(temperatureC);
    Serial.println("ºC");
    Serial.print(temperatureF);
    Serial.println("ºF");
    }// end DS18B20
}
