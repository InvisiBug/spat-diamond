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
#include <MultiStepper.h>
#include <Stepper.h>

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
// #define stepsPerRevolution 2048
#define stepsPerRevolution 2048
struct {
  int in1 = 33;
  int in2 = 25;
  int in3 = 26;
  int in4 = 27;
} smallDiamondPins;

struct {
  int in1 = 19;
  int in2 = 5;
  int in3 = 18;
  int in4 = 17;
} largeDiamondPins;

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
Stepper largeDiamond(stepsPerRevolution, largeDiamondPins.in1, largeDiamondPins.in2, largeDiamondPins.in3, largeDiamondPins.in4);  // Large Diamond
Stepper smallDiamond(stepsPerRevolution, smallDiamondPins.in1, smallDiamondPins.in2, smallDiamondPins.in3, smallDiamondPins.in4);  // Small Diamond

AccelStepper largeDiamond2(AccelStepper::FULL4WIRE, largeDiamondPins.in1, largeDiamondPins.in2, largeDiamondPins.in3, largeDiamondPins.in4);
AccelStepper smallDiamond2(AccelStepper::FULL4WIRE, smallDiamondPins.in1, smallDiamondPins.in3, smallDiamondPins.in2, smallDiamondPins.in4);  // ! Swapped 2 and 3

MultiStepper steppers;
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

int steps = 1;
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
void setup() {
  // set the speed at 60 rpm:

  largeDiamond.setSpeed(10);

  largeDiamond2.setMaxSpeed(1000);
  largeDiamond2.setAcceleration(1000.0);
  largeDiamond2.setSpeed(1000);
  // largeDiamond2.moveTo(-1000);

  smallDiamond2.setMaxSpeed(1000);
  smallDiamond2.setAcceleration(1000.0);
  smallDiamond2.setSpeed(1000);
  // smallDiamond2.moveTo(-1000);

  // smallDiamond2.setMaxSpeed(500.0);
  // smallDiamond2.setAcceleration(500.0);
  // smallDiamond2.moveTo(stepsPerRevolution);

  // initialize the serial port:

  steppers.addStepper(largeDiamond2);
  steppers.addStepper(smallDiamond2);
  Serial.begin(115200);
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
void loop() {
  Serial.println("clockwise");
  largeDiamond.step(stepsPerRevolution);
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  largeDiamond.step(-stepsPerRevolution);
  delay(500);

  // long positions[2];  // Array of desired stepper positions
  // positions[0] = 1000;
  // positions[1] = 1000;

  // steppers.moveTo(positions);
  // steppers.run();  // Blocks until all are in position

  // if(stepper1)

  // Move to a different coordinate
  // positions[0] = -1000;
  // positions[1] = -500;
  // steppers.moveTo(positions);
  // steppers.run();  // Blocks until all are in position

  // if (largeDiamond2.distanceToGo() == 0) {
  //   largeDiamond2.moveTo(-largeDiamond2.currentPosition());
  // }

  // if (smallDiamond2.distanceToGo() == 0) {
  //   smallDiamond2.moveTo(-smallDiamond2.currentPosition());
  // }

  // largeDiamond2.run();
  // smallDiamond2.run();

  // for (int i = 0; i < stepsPerRevolution; i++) {
  //   largeDiamond.step(steps);
  //   smallDiamond.step(steps);
  // }

  // // largeDiamond.step(stepsPerRevolution);
  // // smallDiamond.step(stepsPerRevolution);
  // delay(500);

  // // step one revolution in the other direction:

  // // largeDiamond.step(-stepsPerRevolution);
  // // smallDiamond.step(-stepsPerRevolution);

  // for (int i = 0; i < stepsPerRevolution; i++) {
  //   largeDiamond.step(-steps);
  //   smallDiamond.step(-steps);
  // }

  // delay(500);
}
