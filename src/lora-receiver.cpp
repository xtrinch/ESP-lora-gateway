#include "lora-receiver.h"

char LoRaData[600];

void onReceive(int packetSize) {
  // received a packet
  ardprintf("Received packet '");

  // read packet
  for (int i = 0; i < packetSize; i++) {
    LoRaData[i] = LoRa.read();
    ardprintf("%c", (char)LoRa.read());
  }
  LoRaData[packetSize] = '\0';

  // print RSSI of packet
  ardprintf("' with RSSI %s", LoRa.packetRssi());

  /* packet will be in JSON format:
    {
      "url": "http://test.com",
      "authorization": "authorization",
      "content": {...}
    }
  */
  StaticJsonDocument<800> doc;
  deserializeJson(doc, LoRaData);
  JsonObject documentRoot = doc.as<JsonObject>();
  const char * authorization = documentRoot.getMember("authorization").as<char *>();
  const char * content = documentRoot.getMember("content").as<char *>();
  const char * url = documentRoot.getMember("url").as<char *>();

  makeNetworkRequest(url, authorization, content);
}

bool setupLoRa() {
  // SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);

  // setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {
    return false;
  }

  ardprintf("LoRa initialized");

  // register the receive callback
  LoRa.onReceive(onReceive);

  // put the radio into receive mode
  LoRa.receive();

  return true;
}
