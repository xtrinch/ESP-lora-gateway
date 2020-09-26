#include "station.h"

bool setupWiFi() {
  int wifiRetriesLeft = WIFI_CONNECT_RETRIES;

  WiFi.begin(CFG_WIFI_SSID, CFG_WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED && wifiRetriesLeft > 0) {
    delay(500);
    ardprintf("Station: Connecting with SSID %s", CFG_WIFI_SSID);
    ardprintf("Station: Connecting with password %s", CFG_WIFI_PASSWORD);

    wifiRetriesLeft -= 1;
  }

  if (wifiRetriesLeft <= 0 || WiFi.status() != WL_CONNECTED) {
    ardprintf("Station: Could not connect to WiFi.");
    return false;
  }
  
  ardprintf("Station: Connected to WiFi");

  return true;
}

bool makeNetworkRequest(const char * url, const char * authorization, const char * content) {
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Accept", "application/json");
  http.addHeader("Authorization", authorization);
  int httpResponseCode = http.POST(content);

  if (httpResponseCode > 0) {
    ardprintf("Station: HTTP Response code: %d", httpResponseCode);
    const char * payload = http.getString().c_str();
    ardprintf("%s", payload);
    http.end();
    return true;
  }
  else {
    http.end();
    ardprintf("Station: Error code: %d", httpResponseCode);
    return false;
  }

  return false;
}