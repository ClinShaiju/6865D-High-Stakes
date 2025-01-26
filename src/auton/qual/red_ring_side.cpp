#include "main.h"
#include "pros/rtos.hpp"

void redRingAuton() {
		chassis.setPose(53, 47.5, -90);
	intake.move(IN);
	chassis.moveToPose(24, 48, -90, 3000);
	chassis.waitUntilDone();
	chassis.turnToHeading(180, 3000);
	chassis.waitUntilDone();
	chassis.moveToPose(24, 72, 180, 1000 ,{.forwards=false});
	chassis.waitUntilDone();

	engageLatch();
	intakeIn();
	// pros::delay(1000);
	// chassis.moveToPose(0, 38, -75, 5000);
}