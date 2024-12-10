#pragma once
#include "main.h"
#include "pros/adi.hpp"

void engageLift();
void disengageLift();
void engageFlipout();
void disengageFlipout();
void setRedirect(bool);
void setCollapse(int);
void runNeutralMech();
void macro_redirect();
void macro_collapse();

extern pros::adi::DigitalIn limitSwitch;