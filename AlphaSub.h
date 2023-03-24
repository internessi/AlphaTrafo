void setupSERIAL(){
  delay(3000);
  Serial.begin(115200);
  delay(1000); Serial.println();
  delay(1000); Serial.println("Starting Serial");
  delay(1000); Serial.print(".");
  delay(1000); Serial.print(".");
  delay(1000); Serial.println(".");
  delay(3000);
  }


void LEDred1000(){
  digitalWrite(LED1, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW); 
}

void LEDgreen1000(){
  digitalWrite(LED2, HIGH);
  delay(1000);
  digitalWrite(LED2, LOW); 
}

void relaisON(){
digitalWrite(RELAIS, HIGH); 
}

void relaisOFF(){
digitalWrite(RELAIS, LOW);
}
