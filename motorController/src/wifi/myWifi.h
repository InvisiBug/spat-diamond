#ifndef MYWIFI_h
#define MYWIFI_h
#include <WiFi.h>

class MyWiFi {
 public:
  MyWiFi(const char* ssid, const char* password, int wifiLED);
  void handleWifi();
  void start();

 private:
  const char* ssid;
  const char* password;
  int wifiLED;

  bool connected = false;
  long lastConnectionAttempt = 0;
  long connectionTimeout = (2 * 1000);
};

#endif
