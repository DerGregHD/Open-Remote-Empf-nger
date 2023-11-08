#include <SPI.h>
#include "printf.h"
#include <LoRa.h>
#include <Servo.h>

//########## objects, arrays, variabeles ##########
bool blink = LOW;

//RFM95W
#define rfm95w_mosi 19
#define rfm95w_miso 16
#define rfm95w_sck 18
#define rfm95w_cs 17
#define rfm95w_reset 20

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

Servo servo1;

void setup() {
  //Serial.begin(9600);
  //while (!Serial);
  
  //Serial.println("LoRa Receiver");
  
  LoRa.setPins(rfm95w_cs, rfm95w_reset, 15);
  
  if (!LoRa.begin(915E6)) {
    //Serial.println("Starting LoRa failed!");
    while (1);
  }else {
    //Serial.println("Starting LoRa successfull!");
  }

  servo1.attach(21);
}

void loop() {
  //Serial.println("Loop the loop!");
  //blink the onboard led
  digitalWrite(25, blink);
  blink = !blink;
  
  //uint8_t pipe;
  
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    //Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      for (int i = 0; i < packetSize; i++) {
        ((byte *) &servoData)[i] = LoRa.read();
      //Serial.print(PWMValue1);
      }
    }

    // print RSSI of packet
    //Serial.print("' with RSSI ");
    //Serial.println(LoRa.packetRssi());

    /*Serial.println("##########");
    Serial.print("sD0: ");
    Serial.print(servoData.sD0);
    Serial.print(" sD1: ");
    Serial.print(servoData.sD1);
    Serial.print(" sD2: ");
    Serial.print(servoData.sD2);
    Serial.print(" sD3: ");
    Serial.print(servoData.sD3);
    Serial.print(" sD4: ");
    Serial.print(servoData.sD4);
    Serial.print(" sD5: ");
    Serial.print(servoData.sD5);
    Serial.print(" sD6: ");
    Serial.print(servoData.sD6);
    Serial.print(" sD7: ");
    Serial.print(servoData.sD7);
    Serial.print(" sD8: ");
    Serial.print(servoData.sD8);
    Serial.print(" sD9: ");
    Serial.print(servoData.sD9);
    Serial.print(" sD10: ");
    Serial.print(servoData.sD10);
    Serial.print(" sD11: ");
    Serial.print(servoData.sD11);
    Serial.print(" sD12: ");
    Serial.print(servoData.sD12);
    Serial.print(" sD13: ");
    Serial.print(servoData.sD13);
    Serial.print(" sD14: ");
    Serial.print(servoData.sD14);
    Serial.print(" sD15: ");
    Serial.println(servoData.sD15);*/
  }else {
    //Serial.println("radio is not available");
  }
  
  delay(10);
}
