#include "intake.h"
#include "latch.h"
#include "main.h"
#include "pros/misc.h"

pros::MotorGroup intake({PORT_INTAKE_LEFT, PORT_INTAKE_RIGHT});
IntakeState intakeState = STOPPED;

void intakeIn(){
    if (!isLatched()) {
        engageLatch();
        pros::c::controller_rumble(pros::E_CONTROLLER_MASTER, ".");
    }
    intakeState = IN;
    intake.move(IN);
}

void intakeOut(){
    intakeState = OUT;
    intake.move(OUT);
}

void intakeStop(){
    intakeState = STOPPED;
    intake.move(STOPPED);
}

void runIntake() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && intakeState != BLOCKED) intakeIn();
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) intakeOut();
    else if (intakeState != BLOCKED) intakeStop();
}

IntakeState getIntakeState() {
    return intakeState;
}

void setIntakeState(IntakeState state) {
    intakeState = state;
    intake.move(state);
}

double getIntakeRotations() {
    return intake.get_position();
}