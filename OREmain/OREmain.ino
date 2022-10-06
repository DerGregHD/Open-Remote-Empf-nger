#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include <Servo.h>

//RF24
RF24 radio(7, 8);
uint8_t address[][6] = {"00001"};

int PWMValue = 90;

Servo servo1;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {
      }
  }
  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(sizeof(PWMValue));
  radio.openReadingPipe(1, address[0]);
  radio.startListening();

  servo1.attach(21);
}

void loop() {
  Serial.println(F("Start the loop!"));
  
  uint8_t pipe;
  if (radio.available(&pipe)) {              // is there a payload? get the pipe number that recieved it
    uint8_t bytes = radio.getPayloadSize();  // get the size of the payload
    radio.read(&PWMValue, bytes);             // fetch payload from FIFO
    servo1.write(PWMValue);
    Serial.println(PWMValue);
    delay(10);
  }else{
    Serial.println(F("radio is not available"));
  }
}
