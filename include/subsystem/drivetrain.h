#pragma once
#include "main.h"

extern pros::Controller controller;
extern lemlib::Chassis chassis;


void arcadeDrive(double leftAxis, double rightAxis);
void tankDrive(double leftAxis, double rightAxis);
