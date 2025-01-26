#include "latch.h"
#include "drivetrain.h"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/misc.h"

pros::adi::Pneumatics latchLeft(PORT_ADI_LATCH_LEFT, false);
pros::adi::Pneumatics latchRight(PORT_ADI_LATCH_RIGHT, false);

pros::Distance clampSensor(PORT_DISTANCE);
bool autoClamping = false;
bool holding = false;
int prevClampingDistance = 0;
#define CLAMPING_DISTANCE 20

void runLatchToggle() {
  autoClamp();
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
    autoClamping = false;
    latchLeft.toggle();
    latchRight.toggle();
  }
}
void autoClamp() {
  holding = (clampSensor.get_distance() < CLAMPING_DISTANCE &&
             (latchLeft.is_extended() || holding));

  if (latchLeft.is_extended())
    holding = true;

  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2) &&
      !autoClamping) {
    disengageLatch();
    autoClamping = true;
  } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) &&
             autoClamping) {

    if (clampSensor.get_distance() < CLAMPING_DISTANCE && !holding) {
        engageLatch();
      autoClamping = false;
    }
  } else {
    holding = false;
    autoClamping = false;
  }
}

void engageLatch() {
  latchLeft.extend();
  latchRight.extend();
}

void disengageLatch() {
  latchLeft.retract();
  latchRight.retract();
}

bool isLatched() { return latchLeft.is_extended(); }
