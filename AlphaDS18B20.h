#include <OneWire.h>
#include <DallasTemperature.h>

const int oneWireBus = 13;            // GPIO where the DS18B20  
OneWire oneWire(oneWireBus);          // Setup a oneWire instance
DallasTemperature sensors(&oneWire);  // Pass our oneWire reference

void readDS18B20(){
  if(DS18B20){
    sensors.begin();
    sensors.requestTemperatures(); 
    tmpDS18B20 = (round((sensors.getTempCByIndex(0)*10))/10);
    while(tmpDS18B20<-25){
      digitalWrite(LED1, HIGH);
      delay(250);
      digitalWrite(LED1, LOW); 
      delay(250);
      digitalWrite(LED1, HIGH);
      delay(250);
      digitalWrite(LED1, LOW); 
      delay(250);
      digitalWrite(LED1, HIGH);
      delay(250);
      digitalWrite(LED1, LOW); 
      delay(1750);
      sensors.begin();
      sensors.requestTemperatures(); 
      tmpDS18B20 = (round((sensors.getTempCByIndex(0)*10))/10);
    }// while DS18B20 not connected
    }// end DS18B20
}

void setupDS18B20(){
  if(DS18B20){
    readDS18B20();
    Serial.println("DS18B20 -> initialized");
    }// end DS18B20
}
