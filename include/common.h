#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <string.h>
#include <stdarg.h>
#include <Arduino.h>
#include <Arduino.h>
#ifdef ESP32
  #include <HTTPClient.h>
  #include <WiFi.h>
#elif ESP8266
  #include <ESP8266HTTPClient.h>
  #include <ESP8266WiFi.h>
#endif

#define ARDBUFFER 32

// macro to string expansion for env variables
#define xstr(s) strs(s)
#define strs(s) #s

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define mS_TO_S_FACTOR 1000  /* Conversion factor for mili seconds to seconds */

void ardprintf(const char *str, ...);
void append(char* s, char c);

#define CFG_ACCESS_TOKEN xstr(ACCESS_TOKEN)
#define CFG_SENSOR_DASHBOARD_URL xstr(SENSOR_DASHBOARD_URL)

#endif