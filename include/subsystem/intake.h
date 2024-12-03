#pragma once
#include "main.h"
#include "pros/motor_group.hpp"

enum IntakeState {
    IN = 127,
    OUT = -127,
    STOPPED = 0,
    BLOCKED
};

extern pros::MotorGroup intake;

void intakeIn();
void intakeOut();
void intakeStop();
void runIntake();

IntakeState getIntakeState();
void setIntakeState(IntakeState state);

double getIntakeRotations();