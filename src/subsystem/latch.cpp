#include "main.h"

pros::adi::Pneumatics latchLeft(PORT_ADI_LATCH_LEFT, false);
pros::adi::Pneumatics latchRight(PORT_ADI_LATCH_RIGHT, false);

void runLatchToggle() {
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        latchLeft.toggle();
        latchRight.toggle();
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

bool isLatched() {
     return latchLeft.is_extended();
}





