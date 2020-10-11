#include "lora-receiver.h"


bool onReceive(int packetSize) {
  char LoRaData[255];
  char content[255];
  StaticJsonDocument<800> doc;

  // received a packet
  ardprintf("Received packet with length %d", packetSize);

  // read packet
  for (int i = 0; i < packetSize; i++) {
    LoRaData[i] = LoRa.read();
  }
  LoRaData[packetSize] = '\0';
  //ardprintf("%s", LoRaData);

  // print RSSI of packet
  ardprintf("with RSSI %d", LoRa.packetRssi());

  /* packet will be in JSON format:
    {
      "url": "http://test.com",
      "auth": "authorization",
      "data": {...}
    }
  */
  deserializeJson(doc, LoRaData);

  JsonObject documentRoot = doc.as<JsonObject>();

  const char * authorization = documentRoot.getMember("auth").as<char *>();
  ardprintf("Get auth %s", authorization);

  JsonObject jsonContent = documentRoot.getMember("data").as<JsonObject>();

  const char * url = documentRoot.getMember("url").as<char *>();
  ardprintf("Get url %s", url);

  // reuse buffer
  serializeJson(jsonContent, content);
  //ardprintf(content);

  return makeSecureNetworkRequest(url, authorization, content);
}

bool setupLoRa() {
  // SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);

  LoRa.setSPIFrequency(1E5);

  // setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {
    return false;
  }

  ardprintf("LoRa initialized");

  return true;
}
