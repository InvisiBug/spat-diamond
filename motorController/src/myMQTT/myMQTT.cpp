#include "myMQTT.h"

#include <PubSubClient.h>  // MQTT

#include "Arduino.h"
#include "Streaming.h"
#include "WiFi.h"
#include "WiFiClient.h"  // Wifi

using namespace std;

MyMQTT::MyMQTT(const char* mqttServerIP, int connectionLED) : mqtt(espClient) {
  espClient = WiFiClient();
  this->mqttServerIP = mqttServerIP;
  this->connectionLED = connectionLED;
}

void MyMQTT::start(void (*fn)(char*, uint8_t*, unsigned int)) {
  mqtt.setServer(mqttServerIP, 1883);
  mqtt.setCallback(fn);
}

void MyMQTT::run() {
  if (WiFi.status() == WL_CONNECTED) {
    if (!mqtt.connected()) {
      long now = millis();

      if (mqtt.connect(nodeName, nodeName, 1, 0, disconnectMsg)) {  // Attempt to connect using a login
        Serial << "| MQTT connection established |" << endl;        // Dont publish here, causes crashes
        subscribeToTopics();

        digitalWrite(connectionLED, OFF);
      } else {  // Not connected
        Serial << "| MQTT connection failed, rc=" << mqtt.state() << " Trying again |" << endl;
        digitalWrite(connectionLED, ON);
        delay(250);
        digitalWrite(connectionLED, OFF);
      }
    } else {  // Connected

      mqtt.loop();
    }
  }
}

void MyMQTT::subscribeToTopics() {
  mqtt.subscribe(controlTopic);
}
