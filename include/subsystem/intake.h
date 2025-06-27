#pragma once
#include "main.h"
#include "pros/motor_group.hpp"

enum IntakeState {
    IN = 127,
    OUT = -127,
    STOPPED = 0,
    BLOCKED
};

extern pros::Motor intake;
extern pros::Motor hooks;

void runIntake();

IntakeState getIntakeState();
IntakeState getHookState();
/**
* @brief hello
*
* @param intakeSt sets state for intake
* @param hooksSt sets state for hooks
*/
void setIntakeState(IntakeState intakeSt, IntakeState hooksSt);