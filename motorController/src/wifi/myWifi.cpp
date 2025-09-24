#include "myWifi.h"

#include "Arduino.h"
#include "Streaming.h"
#include "WiFi.h"

using namespace std;
//? All distances in mm

MyWiFi::MyWiFi(const char* ssid, const char* password, int wifiLED) {
  this->ssid = ssid;
  this->password = password;
  this->wifiLED = wifiLED;
}

void MyWiFi::start() {
  WiFi.mode(WIFI_OFF);         // Clears the last wifi credentials
  WiFi.mode(WIFI_STA);         // Wifi Modes (WIFI_OFF, WIFI_STA, WIFI_AP, WIFI_AP_STA)
  WiFi.begin(ssid, password);  // Dont put give the ESP a host name, it screws up the wifi causing disconnects
}

void MyWiFi::handleWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    connected = false;
    // digitalWrite(connectionLED, invertConnectionLED ? OFF : ON);
    // digitalWrite(connectionLED, ON);

    long now = millis();
    if (now - lastConnectionAttempt > connectionTimeout) {
      lastConnectionAttempt = now;
      Serial << ".";
    }
  }

  if ((WiFi.status() == WL_CONNECTED) && (!connected)) {
    connected = true;
    // digitalWrite(connectionLED, invertConnectionLED ? ON : OFF);  // Turn off onboard led when connected
    // digitalWrite(connectionLED, OFF);
    Serial << endl;
    Serial << "| Connected to " << ssid << " |" << endl;
    Serial << "| IP address : " << WiFi.localIP() << " |" << endl;
  }
}