#include "MyStepper.h"

#include "Arduino.h"
#include "Stepper.h"
#include "Streaming.h"

using namespace std;
//? All distances in mm

MyStepper::MyStepper(int stepsPerRev, float drumDiameter, float hangingDistance, int in1, int in2, int in3, int in4) : thisStepper(stepsPerRev, in1, in2, in3, in4) {
  this->in1 = in1;
  this->in2 = in2;
  this->in3 = in3;
  this->in4 = in4;

  this->stepsPerRev = stepsPerRev;
  this->drumDiameter = drumDiameter;
  this->hangingDistance = hangingDistance;
  this->distancePerRev = drumDiameter * PI;

  this->currentPosition = 0;
  this->targetPosition = 0;
  this->speed = 15;
}

void MyStepper::begin() {
  thisStepper.setSpeed(speed);
}

//////////////////////////////////////////////////////////////////////////////
//
//  ######
//  #     # #    # #    #
//  #     # #    # ##   #
//  ######  #    # # #  #
//  #   #   #    # #  # #
//  #    #  #    # #   ##
//  #     #  ####  #    #
//
//////////////////////////////////////////////////////////////////////////////
void MyStepper::run() {
  if (targetPosition > currentPosition) {
    stepAndUpdatePos(1);
  } else if (targetPosition < currentPosition) {
    stepAndUpdatePos(-1);
  }
}

void MyStepper::rotateOnce(bool clockwise = true) {
  setTarget(currentPosition + stepsPerRev * (clockwise ? 1 : -1));
}

bool MyStepper::atTarget() {
  return currentPosition == targetPosition;
}

void MyStepper::setTarget(int target) {
  targetPosition = target;
}

void MyStepper::stepAndUpdatePos(int stepAmount) {
  thisStepper.step(stepAmount);
  currentPosition += stepAmount;
}

void MyStepper::home() {
  setTarget(0);
}

void MyStepper::resetHome() {
  currentPosition = 0;
  targetPosition = 0;
}

void MyStepper::rotateDegrees(float degrees, bool clockwise = true) {
  float rotationsToRotate = degrees / 360.0;
  float stepsToStep = rotationsToRotate * stepsPerRev;
  setTarget(currentPosition + (clockwise ? stepsToStep : -stepsToStep));
}

void MyStepper::goToPercentage(float percentage) {
  float distanceToMove = (percentage / 100.0) * hangingDistance;
  float rotationsToRotate = distanceToMove / distancePerRev;
  float stepsToStep = rotationsToRotate * stepsPerRev;

  setTarget(stepsToStep);
}

void MyStepper::disengageMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}