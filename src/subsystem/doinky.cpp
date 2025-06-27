#include "doinky.h"
#include "main.h"
#include "pros/misc.h"

pros::adi::Pneumatics doinky(PORT_ADI_DOINKY, false);
pros::adi::Pneumatics claw(PORT_ADI_CLAW, false);

void runDoinkyToggle() {
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    engageDoinky();
  else
    disengageDoinky();

  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
    claw.toggle();
  }
}
void disengageDoinky() { doinky.retract(); }

void engageDoinky() { doinky.extend(); }

void disengageClaw() { claw.retract(); }

void engageClaw() { claw.extend(); }

bool isDoinked() { return doinky.is_extended(); }
