#pragma once

#define WIFI_OFF 0
struct MockWiFi {
  void mode(int) {}
  void forceSleepBegin() {}
};
inline MockWiFi WiFi;
