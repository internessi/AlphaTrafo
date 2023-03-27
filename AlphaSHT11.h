#include <SHT1x-ESP.h>

// Specify data and clock connections and instantiate SHT1x object
#define dataPin  26
#define clockPin 27
SHT1x sht1x(dataPin, clockPin);

void readSHT11(){
  if(SHT11){
    tmpSHT11 = (round((sht1x.readTemperatureC()*10))/10);
    humSHT11 = (round((sht1x.readHumidity()*10))/10);
    while((tmpSHT11<-25) or (humSHT11>90)){
      digitalWrite(LED1, HIGH);
      delay(420);
      digitalWrite(LED1, LOW); 
      delay(420);
      digitalWrite(LED1, HIGH);
      delay(420);
      digitalWrite(LED1, LOW); 
      delay(1740);
      tmpSHT11 = (round((sht1x.readTemperatureC()*10))/10);
      humSHT11 = (round((sht1x.readHumidity()*10))/10);
    }// while DS18B20 not connected    
    }
  }

void setupSHT11(){
  if(SHT11){
    readSHT11();
    Serial.println("SHT11 -> initialized");     
  }
}
