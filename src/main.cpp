#include "main.h"

void setup() { 
  Serial.begin(115200);
  while (!Serial);
  
  while (!setupWiFi());

  while (!setupLoRa());
}

void loop() {
    // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    onReceive(packetSize);
  }
  
  checkIfShouldPing();
}