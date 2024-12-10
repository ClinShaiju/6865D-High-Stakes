#include "doinky.h"
#include "main.h"

pros::adi::Pneumatics doinky(PORT_ADI_DOINKY, false);

void runDoinkyToggle() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) engageDoinky();
    else disengageDoinky();
}
void disengageDoinky() {
    doinky.retract();
}

void engageDoinky() {
    doinky.extend();
}

bool isDoinked() {
     return doinky.is_extended();
  }

