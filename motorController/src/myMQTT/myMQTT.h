#ifndef MYMQTT_H
#define MYMQTT_H
#include <PubSubClient.h>  // MQTT
#include <WiFiClient.h>    // Wifi

class MyMQTT {
 public:
  MyMQTT(const char* mqttServerIP, int connectionLED);

  void start(void (*fn)(char*, uint8_t*, unsigned int));
  void run();
  void subscribeToTopics();

 private:
  const char* nodeName = "Diamonds";

  const char* disconnectMsg = "Diamonds Disconnected";
  const char* controlTopic = "Diamonds Control";
  const char* mqttServerIP;

  int connectionLED;

  bool ON = 0;
  bool OFF = 1;

  long connectionTimeout = (2 * 1000);
  long lastConnectionAttempt = 0;

  WiFiClient espClient;
  PubSubClient mqtt;
};

#endif
