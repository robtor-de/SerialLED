void serialSetup() {
  Serial.begin(115200);
}

//Is called, when Data is available

void serialEvent() {
  byte data[5];
  while(Serial.available() > 0) {
    if(Serial.read() == B11111111) {
      Serial.write(1);
      Serial.readBytes(data, 5);
      }
  }
}
