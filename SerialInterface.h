void serialSetup() {
  Serial.begin(115200);
}

//Is called, when Data is available
void serialEvent() {
  byte data[5];
  while(Serial.available() > 0) {
    //Check for start byte
    if(Serial.read() == B11111111) {
      Serial.readBytes(data, 6);
        //Check if packet is complete
        if(data[5] == (data[1]^data[2]^data[3])) {
          //Now switch between different modes
          switch(data[0]) {
            case B00000001: setColor(data[1], data[2], data[3]); Serial.write(0); break;
            case B00000010: fadeTo(data[1], data[2], data[3], data[401]); Serial.write(0); break;
          }
        } else {
          //return 1 as error code when check failed
          Serial.write(1);
        }
      while(Serial.available() > 0) {
        Serial.read();
        //Clear the buffer
      }
    }
  }
}
