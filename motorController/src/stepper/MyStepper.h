#ifndef MYSTEPPER_H
#define MYSTEPPER_H
#include "Stepper.h"

class MyStepper {
 public:
  MyStepper(int stepsPerRev, float drumDiameter, float hangingDistance, int in1, int in2, int in3, int in4);
  void begin();

  // Getters
  bool atTarget();

  // Setters
  void rotateOnce(bool clockwise);
  void rotateDegrees(float degrees, bool clockwise);
  void stepAndUpdatePos(int stepAmount);
  void setTarget(int target);
  void goToPercentage(float percentage);  // 0-100%

  // Utilities
  void run();
  void disengageMotors();
  void home();
  void resetHome();

 private:
  int stepsPerRev;
  float drumDiameter;
  float distancePerRev;
  float hangingDistance;  // in mm

  int currentPosition;  // In steps
  int targetPosition;   // In steps

  int speed;
  int in1, in2, in3, in4;

  Stepper thisStepper;
};

#endif
