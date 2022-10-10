//#########################################
//########## OpenRemoteEmpfanger ##########
//#########################################

//########## librarys ##########
#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include <Servo.h>

//########## objects, arrays, variabeles ##########
bool blink = LOW;

//RF24
RF24 radio(7, 8);
uint8_t address[][6] = {"00001"};

//Struktur für Servowerte
struct ServoData {
  byte sD0=0;
  byte sD1=0;
  byte sD2=0;
  byte sD3=0;
  byte sD4=0;
  byte sD5=0;
  byte sD6=0;
  byte sD7=0;
  byte sD8=0;
  byte sD9=0;
  byte sD10=0;
  byte sD11=0;
  byte sD12=0;
  byte sD13=0;
  byte sD14=0;
  byte sD15=0;
};

ServoData servoData;

Servo servo0;
Servo servo1;

//########## methods ##########

//########## setup code ##########
void setup() {
  pinMode(25, OUTPUT);
  Serial.begin(115200);
  delay(1000);
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {
      }
  }
  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(sizeof(servoData));
  radio.openReadingPipe(1, address[0]);
  radio.startListening();

  servo0.attach(21);
  servo1.attach(22);
}

//########## loop code ##########
void loop() {
  digitalWrite(25, blink);
  blink = !blink;
  
  uint8_t pipe;
  if (radio.available(&pipe)) {              // is there a payload? get the pipe number that recieved it
    uint8_t bytes = radio.getPayloadSize();  // get the size of the payload
    radio.read(&servoData, bytes);
    Serial.print("sD0: ");
    Serial.print(servoData.sD0);
    Serial.print(" sD1: ");
    Serial.println(servoData.sD1);             // fetch payload from FIFO
    servo0.write(servoData.sD0);
    servo1.write(servoData.sD1);
    delay(20);
  }else{
    Serial.println(F("radio is not available"));
    servo0.write(90);
    servo1.write(90);
  }
}
