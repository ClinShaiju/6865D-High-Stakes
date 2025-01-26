#include "main.h"
#include "pros/rtos.hpp"
#include "subsystem/drivetrain.h"
#include "subsystem/intake.h"
#include "subsystem/latch.h"

void blueRingAuton() {
	// pros::delay(5000);

	chassis.setPose(53, 47.5, -90);
	intake.move(IN);
	chassis.moveToPose(24, 48, -90, 3000);
	chassis.waitUntilDone();
	chassis.turnToHeading(0, 3000);
	chassis.waitUntilDone();
	chassis.moveToPose(20, 24, 0, 1000 ,{.forwards=false});
	chassis.waitUntilDone();

	engageLatch();
	intakeIn();
	// pros::delay(1000);
	// chassis.moveToPose(0, 38, -75, 5000);


	
}