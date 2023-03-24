
#include "SHT1x-ESP.h"


// Specify data and clock connections and instantiate SHT1x object
#define dataPin  26
#define clockPin 27
SHT1x sht1x(dataPin, clockPin);

void setupSHT11(){
    if(SHT11){
      
    }
}


void readSHT11(){
  if(SHT11){
    float temp_c;
    float temp_f;
    float humidity;
    pinMode(dataPin, INPUT_PULLUP);
   
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
