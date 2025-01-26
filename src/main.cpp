#include "main.h"
#include "auton/selector.h"
#include "pros/misc.h"
#include "subsystem/drivetrain.h"
#include "subsystem/intake.h"
#include "subsystem/latch.h"
#include "subsystem/neutral_mech.h"
#include "util/colorsort.h"

void printScreen() {
	while (true) {
	
	controller.print(0, 0, "X:%.2f Y: %.2f", chassis.getPose().x, chassis.getPose().y);
	pros::delay(20);
	}
}

void initialize() {
	pros::Task colorSortTask(colorSort);
	// pros::Task redirectTask(macro_redirect);
	// pros::Task collapseTask(macro_collapse);
	pros::Task printTask(printScreen);
	disengageLatch();
	gui();
	chassis.calibrate();

}

void disabled() {
}


void competition_initialize() {
}


void autonomous() {
	autonSelector();
}

void opcontrol() {

	// autonomous();	

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


