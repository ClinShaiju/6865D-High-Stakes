#include "neutral_mech.h"
#include "drivetrain.h"
#include "globals.h"
#include "intake.h"
#include "latch.h"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"

pros::adi::Pneumatics liftLeft(PORT_ADI_LIFT_LEFT, false);
pros::adi::Pneumatics liftRight(PORT_ADI_LIFT_RIGHT, false);

pros::adi::Pneumatics flipout(PORT_ADI_FLIPOUT, false);

pros::adi::DigitalIn limitSwitch(PORT_ADI_LIMIT);
bool redirecting = false;

bool collapsing = false;

int collapseWait = 500;

void engageLift() {
  liftLeft.extend();
  liftRight.extend();
}

void disengageLift() {
  liftLeft.retract();
  liftRight.retract();
} 

void engageFlipout () {
  flipout.extend();
}

void disengageFlipout () {
  flipout.retract();
}

void setRedirect(bool redirect) {
  redirecting = redirect;
}

void setCollapse(int milli) {
  collapsing = true;
  collapseWait = milli;
}

void toggleLift() {
  liftLeft.toggle();
  liftRight.toggle();
}

void toggleFlipout() { flipout.toggle(); }

void macro_redirect() {
  while (true) {
    if (redirecting) {
      engageLatch();
      flipout.extend();
      setIntakeState(BLOCKED);
      intake.move(40);
      while (limitSwitch.get_value()) {
        if (getIntakeState() != BLOCKED) {
          redirecting = false;
          break;
        }
        pros::delay(20);
      }
      while (!limitSwitch.get_value()) {
        if (getIntakeState() != BLOCKED) {
          redirecting = false;
          break;
        }
        pros::delay(20);
      }
      intake.move(-127);
      pros::delay(1000);
      intakeStop();
      redirecting = false;
    }
    pros::delay(20);
  }
}
void macro_collapse() {
  while (true) {
    if (collapsing) {
      liftLeft.retract();
      liftRight.retract();
      pros::delay(1000);
      flipout.retract();
      collapsing = false;
      collapseWait = 500;
    }
    pros::delay(20);
  }
}

void runNeutralMech() {
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
    toggleLift();
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
    toggleFlipout();
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
    redirecting = true;
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
    collapsing = true;
}
