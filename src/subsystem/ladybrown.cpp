#include "ladybrown.h"
#include "intake.h"
#include "lemlib/pid.hpp"
#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"

pros::Motor ladybrown(PORT_LADYBROWN);
pros::Rotation rotationTracker(PORT_ROTATION_LADYBROWN);

double desiredRotation = 0.0;
double currentRotation = 0.0;
double error = 0.0;
double prevError = 0.0;
double derivative = 0.0;
double kP = 0.4; // proportional constant
double kD = 0.0; // derivative constant
LadybrownState state = REST;

void ladybrownInit() {
  ladybrown.set_brake_mode(pros::MotorBrake::hold);
  rotationTracker.reset_position();
}

void setLadybrownRotation(double rot) { ladybrown.set_zero_position(rot); }

LadybrownState returnState() { return state; }

void cycleLadybrown(LadybrownState st) {

  if (st == REST)
    state = CATCH;
  else if (st == CATCH)
    state = NEUTRAL;
  else if (st == NEUTRAL)
    state = ALLIANCE;
  else
    state = REST;
}

void ladybrownTap() {
  for (int i = 0; i < 2; i++) {
    setIntakeState(IN, IN);
    pros::delay(100);
    setIntakeState(STOPPED, STOPPED);
  }
}

void setLadybrown(LadybrownState st) { state = st; }

void runLadybrown() {
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
    state = MANUAL;
    ladybrown.move(127);
  } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
    state = MANUAL;

    ladybrown.move(-127);
  } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
    cycleLadybrown(state);
  else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
    state = REST;
  else
    ladybrown.brake();
}

void ladybrownPID() {
  while (true) {
    currentRotation = ladybrown.get_position();
    error = (double)state - currentRotation;
    derivative = error - prevError;
    prevError = error;
    if (state != MANUAL) {
      ladybrown.move(error * kP + derivative * kD);
    }
    pros::delay(20);
  }
}

// void PIDtuner() {
//   if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
//     kP += .05;
//   else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
//     kP -= .05;
//   else if
//   (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
//     kD += .05;
//   else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
//     kD -= .05;
// }