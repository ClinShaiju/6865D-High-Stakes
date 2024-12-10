#include "main.h"

void redRingAuton() {
	chassis.setPose(-53.374, 15.5, 180);
	chassis.moveToPose(-54, -9, 180, 1000); // Push out starting ring
	chassis.waitUntilDone();
	chassis.moveToPose(-61.75, -1, 90, 1500, {.forwards=false}); // score alliance stake
	chassis.waitUntilDone();
	intakeIn();
	chassis.waitUntilDone();
	pros::delay(500);
	intakeStop();
	chassis.moveToPose(-24, 43, 56, 2000); // first ring
	intakeIn();
	chassis.waitUntil(70);
	intakeStop();
	chassis.waitUntilDone();
	chassis.moveToPose(-21.5, 26, 0, 1200, {.forwards=false, .lead=0.5}); // goal
	chassis.waitUntil(3);
	disengageLatch();
	chassis.waitUntil(20);
	engageLatch();
	chassis.waitUntilDone();
	chassis.moveToPose(-10, 36.387, 62, 2000); // second ring
	intakeIn();
	chassis.waitUntilDone();
	chassis.moveToPose(-3, 55, 0, 1000); // third ring
	chassis.waitUntilDone();
	chassis.turnToHeading(-45, 500);
	chassis.waitUntilDone();
	chassis.moveToPoint(-22, 0, 5000, {.maxSpeed=50}); // ladder
	pros::delay(500);
	intakeStop();
	engageDoinky();
	chassis.waitUntilDone();
}