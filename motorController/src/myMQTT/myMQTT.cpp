#include "myMQTT.h"

#include <PubSubClient.h>  // MQTT

#include "Arduino.h"
#include "Streaming.h"
#include "WiFi.h"
#include "WiFiClient.h"  // Wifi

using namespace std;
//? All distances in mm

MyMQTT::MyMQTT() {
  espClient = WiFiClient();
}

void MyMQTT::start(void (*fn)(char*, uint8_t*, unsigned int)) {
  mqtt.setServer(mqttServerIP, 1883);
  mqtt.setCallback(fn);


}

void MyMQTT::messageReceived(char* topic, byte* payload, unsigned int length) {
  // Serial << "Message Received" << endl;
  printMessage(payload, length);
}

void MyMQTT::printMessage(byte* payload, int length) {
  for (int i = 0; i < length; i++) {
    Serial << (char)payload[i];  // Dont put an endl here
  }
  Serial << endl;
}

void MyMQTT::run() {
  if (WiFi.status() == WL_CONNECTED) {
    // Serial << "Checking MQTT connection..." << endl;

    if (!mqtt.connected()) {
      Serial << "MQTT not connected" << endl;

      long now = millis();

      if (mqtt.connect(nodeName, nodeName, 1, 0, disconnectMsg)) {  // Attempt to connect using a login
        Serial << "| MQTT connection established |" << endl;        // Dont publish here, causes crashes
        subscribeToTopics();

        // digitalWrite(connectionLED, OFF);
      } else {  // Not connected
        Serial << "| MQTT connection failed, rc=" << mqtt.state() << " Trying again |" << endl;
        // digitalWrite(connectionLED, ON);
        delay(250);
        // digitalWrite(connectionLED, OFF);
      }
    } else {  // Connected
      // Serial << "| MQTT connected |" << endl;
      mqtt.loop();
    }
  }
}

void MyMQTT::subscribeToTopics() {
  mqtt.subscribe(controlTopic);
}

bool MyMQTT::connect() {
  if (mqtt.connect(nodeName)) {  // doesomething
    Serial << "| MQTT connection established |" << endl;
  }

  return mqtt.connected();
}
