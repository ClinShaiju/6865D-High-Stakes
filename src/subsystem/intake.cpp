#include "latch.h"
#include "main.h"
#include "pros/misc.h"

pros::MotorGroup intake({PORT_INTAKE_LEFT, PORT_INTAKE_RIGHT});

void intakeIn(){
    if (!isLatched()) {
        engageLatch();
        pros::c::controller_rumble(pros::E_CONTROLLER_MASTER, ".");
    }
    intake.move(127);
}

void intakeOut(){
    intake.move(-127);
}

void intakeStop(){
    intake.move(0);
}

void runIntake() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) intakeIn();
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) intakeOut();
    else intakeStop();
}
