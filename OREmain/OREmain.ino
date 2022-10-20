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
RF24 radio(20, 17);
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
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;

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

  servo0.attach(0);
  servo1.attach(1);
  servo2.attach(2);
  servo3.attach(3);
  servo4.attach(4);
  servo5.attach(5);
  servo6.attach(6);
  servo7.attach(7);
  servo8.attach(8);
  servo9.attach(9);
}

//########## loop code ##########
void loop() {
  digitalWrite(25, blink);
  blink = !blink;
  
  uint8_t pipe;
  //if (radio.available(&pipe)) {              // is there a payload? get the pipe number that recieved it
    uint8_t bytes = radio.getPayloadSize();  // get the size of the payload
    radio.read(&servoData, bytes);
    Serial.print("sD0: ");
    Serial.print(servoData.sD0);
    Serial.print(" sD1: ");
    Serial.println(servoData.sD1);             // fetch payload from FIFO
    servo0.write(servoData.sD0);
    servo1.write(servoData.sD1);
    servo2.write(servoData.sD2);
    servo3.write(servoData.sD3);
    servo4.write(servoData.sD4);
    servo5.write(servoData.sD5);
    servo6.write(servoData.sD6);
    servo7.write(servoData.sD7);
    servo8.write(servoData.sD8);
    servo9.write(servoData.sD9);
    delay(50);
  //}else{
    //Serial.println(F("radio is not available"));
    //servo0.write(90);
    //servo1.write(90);
    //servo2.write(90);
    //servo3.write(90);
    //servo4.write(90);
    //servo5.write(90);
    //servo6.write(90);
    //servo7.write(90);
    //servo8.write(90);
    //servo9.write(90);
  //}
}
