#include "main.h"

void setup() { 
  Serial.begin(115200);
  while (!Serial);
  
  if (!setupWiFi()) {
    ardprintf("Setting up WiFi failed");
    while (1);
  }

  if (!setupLoRa()) {
    ardprintf("Setup LoRa failed");
    while(1);
  }
}

void loop() {
  checkIfShouldPing();
}