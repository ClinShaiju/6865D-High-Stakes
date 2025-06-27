#include "main.h"
#include "auton/auton.h"
#include "auton/selector.h"
#include "pros/misc.h"
#include "subsystem/drivetrain.h"
#include "subsystem/intake.h"
#include "subsystem/ladybrown.h"
#include "subsystem/latch.h"
#include "util/colorsort.h"
#include "util/util.h"

void printScreen() {
  controller.clear();
  while (true) {

    // controller.print(0, 0, "X:%.2f Y: %.2f", chassis.getPose().x,
    // chassis.getPose().y);
    controller.print(0, 0, "P:%.2f D: %.2f\nr: %,2f", kP, kD, currentRotation);
    controller.print(1, 1, "S: %d ", returnState());

    pros::delay(20);
  }
}

void initialize() {
  pros::Task colorSortTask(colorSort);
  pros::Task printTask(printScreen);
  pros::Task ladybrownTask(ladybrownPID);
  ladybrownInit();
  gui();
  chassis.calibrate();
}

void disabled() {}

void competition_initialize() {}

void autonomous() { autonSelector(); }

void opcontrol() {

  while (true) {
    // replayRecorder();

    runLatchToggle();
    // PIDtuner();
    runIntake();
    runDoinkyToggle();
    runLadybrown();
    int yAxis = returnExponential(
        controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), 1, 10);
    int xAxis = returnExponential(
        controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), 2, 6);
    chassis.arcade(yAxis, xAxis);
    pros::delay(20);
  }
}