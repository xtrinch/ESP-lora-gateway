#ifndef __LORA_H
#define __LORA_H

#include "common.h"
#include <SPI.h>
#include <LoRa.h>
#include <ArduinoJson.h>
#include "station.h"

// TTGO Lora32 pins for LoRa
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

// LoRa frequency band
#define BAND 866E6


bool onReceive();
bool setupLoRa();

#endif