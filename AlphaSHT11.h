#include <SHT1x-ESP.h>

// Specify data and clock connections and instantiate SHT1x object
#define dataPin  26
#define clockPin 27
SHT1x sht1x(dataPin, clockPin);

float tmpSHT11 = 0;
float humSHT11 = 0;

void readSHT11(){
  if(SHT11){
    tmpSHT11 = (round((sht1x.readTemperatureC()*10))/10);
    humSHT11 = (round((sht1x.readHumidity()*10))/10);
    Serial.println("SHT11 TMP: " + String(tmpSHT11) + "ºC");
    Serial.println("SHT11 HUM: " + String(humSHT11) + "%");   
    }
  }

void setupSHT11(){
  if(SHT11){
    readSHT11();
    Serial.println("SHT11 -> initialized");     
  }
}
