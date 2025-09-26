////////////////////////////////////////////////////////////////////////
//
//  ###
//   #  #    #  ####  #      #    # #####  ######  ####
//   #  ##   # #    # #      #    # #    # #      #
//   #  # #  # #      #      #    # #    # #####   ####
//   #  #  # # #      #      #    # #    # #           #
//   #  #   ## #    # #      #    # #    # #      #    #
//  ### #    #  ####  ######  ####  #####  ######  ####
// boop
////////////////////////////////////////////////////////////////////////
#include <AccelStepper.h>
#include <Arduino.h>
#include <FastLED.h>
#include <MultiStepper.h>
#include <PubSubClient.h>  // MQTT
#include <Streaming.h>

#include "myMQTT/myMQTT.h"
#include "stepper/MyStepper.h"
#include "wifi/myWifi.h"

////////////////////////////////////////////////////////////////////////
//
//  ######
//  #     # ###### ###### # #    # # ##### #  ####  #    #  ####
//  #     # #      #      # ##   # #   #   # #    # ##   # #
//  #     # #####  #####  # # #  # #   #   # #    # # #  #  ####
//  #     # #      #      # #  # # #   #   # #    # #  # #      #
//  #     # #      #      # #   ## #   #   # #    # #   ## #    #
//  ######  ###### #      # #    # #   #   #  ####  #    #  ####
//
////////////////////////////////////////////////////////////////////////
#define stepsPerRevolution 2048
#define connectionLED 21

struct DiamondConfig {
  int pin1;
  int pin2;
  int pin3;
  int pin4;
};

////////////////////////////////////////////////////////////////////////
//
//  #     #
//  #     #   ##   #####  #####  #    #   ##   #####  ######
//  #     #  #  #  #    # #    # #    #  #  #  #    # #
//  ####### #    # #    # #    # #    # #    # #    # #####
//  #     # ###### #####  #    # # ## # ###### #####  #
//  #     # #    # #   #  #    # ##  ## #    # #   #  #
//  #     # #    # #    # #####  #    # #    # #    # ######
//
////////////////////////////////////////////////////////////////////////
// * Processor Core tasks
TaskHandle_t Task1;
TaskHandle_t Task2;

DiamondConfig largeTestDiamond = {19, 5, 18, 17};
DiamondConfig smallTestDiamond = {33, 25, 26, 27};

MyStepper large(stepsPerRevolution, 25, 120, largeTestDiamond.pin1, largeTestDiamond.pin2, largeTestDiamond.pin3, largeTestDiamond.pin4);
MyStepper small(stepsPerRevolution, 25, 120, smallTestDiamond.pin1, smallTestDiamond.pin2, smallTestDiamond.pin3, smallTestDiamond.pin4);

MyWiFi myWifi("I Don't Mind", "Have2Biscuits", connectionLED);

MyMQTT myMQTT("192.168.1.2", connectionLED);

////////////////////////////////////////////////////////////////////////
//
//  #     #
//  #     #   ##   #####  #   ##   #####  #      ######  ####
//  #     #  #  #  #    # #  #  #  #    # #      #      #
//  #     # #    # #    # # #    # #####  #      #####   ####
//   #   #  ###### #####  # ###### #    # #      #           #
//    # #   #    # #   #  # #    # #    # #      #      #    #
//     #    #    # #    # # #    # #####  ###### ######  ####
//
////////////////////////////////////////////////////////////////////////
int incomingByte = 0;  // for incoming serial data
int state = 0;

bool startup = true;

////////////////////////////////////////////////////////////////////////
//
//  ######                                                #####
//  #     # #####   ####   ####  #####    ##   #    #    #     # #####   ##   #####  ##### #    # #####
//  #     # #    # #    # #    # #    #  #  #  ##  ##    #         #    #  #  #    #   #   #    # #    #
//  ######  #    # #    # #      #    # #    # # ## #     #####    #   #    # #    #   #   #    # #    #
//  #       #####  #    # #  ### #####  ###### #    #          #   #   ###### #####    #   #    # #####
//  #       #   #  #    # #    # #   #  #    # #    #    #     #   #   #    # #   #    #   #    # #
//  #       #    #  ####   ####  #    # #    # #    #     #####    #   #    # #    #   #    ####  #
//
////////////////////////////////////////////////////////////////////////
// Forward declarations for FreeRTOS task functions
void core1Loop(void* pvParameters);
void core2Loop(void* pvParameters);
void messageReceived(char* topic, byte* payload, unsigned int length);

void setup() {
  //* System architecture, dual core stuff
  xTaskCreatePinnedToCore(core1Loop, "Task1", 10000, NULL, 1, &Task1, 0);
  delay(500);

  xTaskCreatePinnedToCore(core2Loop, "Task2", 10000, NULL, 1, &Task2, 1);
  delay(500);

  disableCore0WDT();  // This prevents the WDT taking out an idle core
  disableCore1WDT();  // the wifi code was triggering the WDT

  Serial.begin(115200);

  // Start diamonds
  small.begin();
  large.begin();

  // start comms
  myWifi.start();
  myMQTT.start(messageReceived);

  pinMode(connectionLED, OUTPUT);
}

///////////////////////////////////////////////////////////////////////
//
//  #     #                    ######
//  ##   ##   ##   # #    #    #     # #####   ####   ####  #####    ##   #    #
//  # # # #  #  #  # ##   #    #     # #    # #    # #    # #    #  #  #  ##  ##
//  #  #  # #    # # # #  #    ######  #    # #    # #      #    # #    # # ## #
//  #     # ###### # #  # #    #       #####  #    # #  ### #####  ###### #    #
//  #     # #    # # #   ##    #       #   #  #    # #    # #   #  #    # #    #
//  #     # #    # # #    #    #       #    #  ####   ####  #    # #    # #    #
//
///////////////////////////////////////////////////////////////////////
void core1Loop(void* pvParameters) {
  for (;;) {
    if (startup) {
      delay(500);  // * Add this back if WDT issues come back
      startup = false;
    }

    if (Serial.available() > 0) {
      incomingByte = Serial.read();

      Serial << "incomingByte: " << incomingByte - 48 << endl;
      state = incomingByte - 48;  // Convert ASCII to integer
    }

    myWifi.handleWifi();
  }
}

void core2Loop(void* pvParameters) {
  for (;;) {
    myMQTT.run();
    switch (state) {
      case 1: {
        //! MQTT messages enabeled for state 1 below :portal_door: @see messageReceived() have a look at comment anchors extension
        // int speed = 10;

        // uint32_t smallDiamond = millis() * speed;
        // int smallPercentage = map(inoise16(smallDiamond, 0), 0, 65535, 0, 100);
        // small.goToPercentage(smallPercentage);

        // uint32_t largeDiamond = 2 * millis() * speed;  // This value of 2 needs to be played with
        // int largePercentage = map(inoise16(largeDiamond, 0), 0, 65535, 0, 100);
        // large.goToPercentage(largePercentage);

      } break;

      case 2:
        large.home();
        small.home();
        state = 0;
        break;

      case 3:
        large.disengageMotors();
        small.disengageMotors();
        break;

      case 4:
        large.resetHome();
        small.resetHome();
        state = 0;
        break;

      case 5:
        large.rotateOnce(false);
        small.rotateOnce(false);
        state = 0;
        break;

      case 6:
        large.goToPercentage(0);
        small.goToPercentage(0);
        state = 0;
        break;

      case 7:
        large.goToPercentage(50);
        small.goToPercentage(50);
        state = 0;
        break;

      case 8:
        large.goToPercentage(100);
        small.goToPercentage(100);
        state = 0;
        break;

      case 9:
        float largeAngleDeg = millis() / 100;                // angle in degrees over time
        float largeAngleRad = largeAngleDeg * 1000 / 57296;  // convert to radians
        float largeValue = sin(largeAngleRad);               // grab the sine of the angle, -1 to +1
        float largeDistance = (largeValue + 1) / 2 * 100;    // convert to percentage with 0 being at the 50% mark
        large.goToPercentage(largeDistance);                 // move the large diamond

        // Serial << "Large angle deg: " << largeAngleDeg << "\t Large: " << largeDistance << endl;

        float smallAngle = 180 + millis() / 100.0;         // time in seconds angle
        float smallAngleRad = smallAngle * 1000 / 57296;   // convert to radians
        float smallValue = sin(smallAngleRad);             // -1 to +1
        float smallDistance = (smallValue + 1) / 2 * 100;  // 0 to 1

        small.goToPercentage(smallDistance);

        // Serial << millis() / 1000.0 << '\t' << 180 + millis() / 1000.0 << endl;
        // Serial << "Large: " << largeDistance << '\t' << "Small: " << smallDistance << endl;
        // Serial << sin(4) << endl;
        break;
    }

    large.run();
    small.run();
  }
}

void loop() {
}

void printMessage(byte* payload, int length) {
  for (int i = 0; i < length; i++) {
    Serial << (char)payload[i];  // Dont put an endl here
  }
  Serial << endl;
}

void messageReceived(char* topic, byte* payload, unsigned int length) {
  // Serial << "Message Received" << endl;
  // state = payload[0] - 48;
  // printMessage(payload, length);

  if (payload[0] == 'a') {
    state = payload[2] - 48;  // Convert ASCII to integer

  } else {
    // Make a String or local char buffer
    String s;
    s.reserve(length);
    for (unsigned i = 0; i < length; ++i) s += (char)payload[i];

    // Split on commas
    int last = 0;
    int idx;
    int values[5];  // adjust size
    int count = 0;

    while ((idx = s.indexOf(',', last)) != -1 && count < 5) {
      values[count++] = s.substring(last, idx).toInt();
      last = idx + 1;
    }
    if (count < 5 && last < s.length()) {
      values[count++] = s.substring(last).toInt();
    }

    // Serial << "Recieved % values" << endl;
    // Serial << "Small: " << values[0] << "%\tLarge: " << values[1] << "%" << endl;

    if (state == 1) {
      small.goToPercentage(values[0]);
      large.goToPercentage(values[1]);
    }
  }
}