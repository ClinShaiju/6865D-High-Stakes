#pragma once
#include "main.h"
#include "pros/adi.hpp"

void runNeutralMech();
void macro_redirect();
void macro_collapse();

extern pros::adi::DigitalIn limitSwitch;