void serialSetup() {
  Serial.begin(115200);
}

//Is called, when Data is available
void serialEvent() {
  byte data[5];
  while(Serial.available() > 0)
    //Check for start byte
    if(Serial.read() == B11111111) {
      Serial.readBytes(data, 5);
      Serial.flush();

        //Check if packet is complete
        if(data[4] == (data[1]^data[2]^data[3])) {
          //Now switch between different modes
          switch(data[0]) {
            case B00000001: setColor(data[1], data[2], data[3]); Serial.write(0); break;
          }
        } else {
          //return 1 as error code when check failed
          Serial.write(1);
        }
      }
  }
}
