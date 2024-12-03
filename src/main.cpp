#include "main.h"
#include "auton/selector.h"
#include "subsystem/latch.h"
#include "subsystem/neutral_mech.h"

void initialize() {
	chassis.calibrate();
	pros::Task colorSortTask(colorSort);
	pros::Task redirectTask(macro_redirect);
	pros::Task collapseTask(macro_collapse);
	engageLatch();
	gui();

}

void disabled() {
}


void competition_initialize() {
}


void autonomous() {
    autonSelector();
}

void opcontrol() {
	autonomous();

	while (true) {
			runLatchToggle();
			runIntake();
			runDoinkyToggle();
			runNeutralMech();
			int yAxis = returnExponential(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), 1, 10);
			int xAxis = returnExponential(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), 2, 6);
			chassis.arcade(yAxis, xAxis);
			pros::delay(20);

	}
}


