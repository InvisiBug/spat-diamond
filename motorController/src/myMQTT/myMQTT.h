#ifndef MYMQTT_H
#define MYMQTT_H
#include <PubSubClient.h>  // MQTT
#include <WiFiClient.h>    // Wifi

class MyMQTT {
 public:
  MyMQTT();

  void start(void (*fn)(char*, uint8_t*, unsigned int));
  void run();
  void subscribeToTopics();
 bool connect();

 private:
  const char* nodeName = "Diamonds";
  void messageReceived(char* topic, byte* payload, unsigned int length);
  void printMessage(byte* payload, int length);

  const char* disconnectMsg = "Diamonds Disconnected";
  const char* controlTopic = "Diamonds Control";
  const char* mqttServerIP = "192.168.1.63";

  int connectionLED = 2;  // Built in LED on most boards

  bool ON = 0;
  bool OFF = 1;

  long connectionTimeout = (2 * 1000);
  long lastConnectionAttempt = 0;

  WiFiClient espClient;
  PubSubClient mqtt = PubSubClient(espClient);  // Needs to be initialized here for some reason, crashes if not
};

#endif
