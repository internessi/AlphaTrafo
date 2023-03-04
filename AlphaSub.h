void setupSERIAL(){
  delay(5000);
  Serial.begin(115200);
  delay(1000); Serial.println();
  delay(1000); Serial.println("Starting Serial");
  delay(1000); Serial.print(".");
  delay(1000); Serial.print(".");
  delay(1000); Serial.println(".");
  delay(3000);
  }
