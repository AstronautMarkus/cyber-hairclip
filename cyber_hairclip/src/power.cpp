#include "power.h"
#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

void powerSave() {
  WiFi.mode(WIFI_OFF);  // the radio is unused and is the biggest battery drain
#if defined(ESP8266)
  WiFi.forceSleepBegin();  // on core 2.x WIFI_OFF alone can leave the modem powered
  delay(1);
#elif defined(ESP32)
  setCpuFrequencyMhz(80);  // 240 -> 80 MHz: much lower draw; I2C is unaffected (APB stays at 80 MHz)
#endif
}
