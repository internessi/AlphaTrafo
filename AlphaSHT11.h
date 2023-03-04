
#include "SHT1x-ESP.h"

void setupSHT11(){
    if(SHT11){
      
    }
}

// Specify data and clock connections and instantiate SHT1x object
#define dataPin  27
#define clockPin 26
SHT1x sht1x(dataPin, clockPin);

void readSHT11(){
  if(SHT11){
    float temp_c;
    float temp_f;
    float humidity;
   
    // Read values from the sensor
    temp_c = sht1x.readTemperatureC();
    temp_f = sht1x.readTemperatureF();
    humidity = sht1x.readHumidity();
   
    // Print the values to the serial port
    Serial.print("Temperature: ");
    Serial.print(temp_c, DEC);
    Serial.print("C / ");
    Serial.print(temp_f, DEC);
    Serial.print("F. Humidity: ");
    Serial.print(humidity);
    Serial.println("%"); 
    }
  }
