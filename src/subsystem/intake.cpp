#include "intake.h"
#include "globals.h"
#include "latch.h"
#include "main.h"
#include "pros/misc.h"

pros::Motor intake(PORT_INTAKE);
pros::Motor hooks(PORT_HOOKS);
IntakeState intakeState = STOPPED;

void intakeIn(){
    if (!isLatched()) {
        engageLatch();
        pros::c::controller_rumble(pros::E_CONTROLLER_MASTER, ".");
    }
    intakeState = IN;
    intake.move(IN);
    hooks.move(IN);
}

void intakeOut(){
    intakeState = OUT;
    intake.move(OUT);
    hooks.move(OUT);

}

void intakeStop(){
    intakeState = STOPPED;
    intake.move(STOPPED);
    hooks.move(STOPPED);

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
    hooks.move(state);
}

double getIntakeRotations() {
    return hooks.get_position();
}