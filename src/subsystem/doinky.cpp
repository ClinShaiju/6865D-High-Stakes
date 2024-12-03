#include "doinky.h"
#include "main.h"

pros::adi::Pneumatics doinky(PORT_ADI_DOINKY, true);

void runDoinkyToggle() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) engageDoinky();
    else disengageDoinky();
}
void disengageDoinky() {
    doinky.extend();
}

void engageDoinky() {
    doinky.retract();
}

bool isDoinked() {
     return doinky.is_extended();
  }

