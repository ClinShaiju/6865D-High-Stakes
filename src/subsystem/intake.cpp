#include "intake.h"
#include "globals.h"
#include "latch.h"
#include "main.h"
#include "pros/misc.h"

pros::Motor intake(PORT_INTAKE);
pros::Motor hooks(PORT_HOOKS);
IntakeState intakeState = STOPPED;
IntakeState hooksState = STOPPED;

void runIntake() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && intakeState != BLOCKED) {
        setIntakeState(IN, STOPPED);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && intakeState != BLOCKED) setIntakeState(IN, IN);
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) setIntakeState(OUT, OUT);
    else if (intakeState != BLOCKED) setIntakeState(STOPPED, STOPPED);
}

IntakeState getIntakeState() {
    return intakeState;
}

IntakeState getHookState() {
    return hooksState;
}

void setIntakeState(IntakeState intakeSt, IntakeState hooksSt) {
    intakeState = intakeSt;
    hooksState = hooksSt;
    intake.move(intakeSt);
    hooks.move(hooksSt);
}