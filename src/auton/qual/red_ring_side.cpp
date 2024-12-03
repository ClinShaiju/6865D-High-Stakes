#include "main.h"

void redRingAuton() {
	chassis.setPose(-53.374, 15.5, 180);
	chassis.moveToPose(-54, -9, 180, 1000); // Push out starting ring
	chassis.waitUntilDone();
	chassis.moveToPose(-60, 1.5, 90, 1500, {.forwards=false}); // score alliance stake
	chassis.waitUntilDone();
	intakeIn();
	chassis.waitUntilDone();
	pros::delay(500);
	intakeStop();
	chassis.moveToPose(-28.322, 46, 56, 2000); // first ring
	intakeIn();
	chassis.waitUntil(70);
	intakeStop();
	chassis.waitUntilDone();
	chassis.moveToPose(-29, 27, 0, 1200, {.forwards=false, .lead=0.3}); // goal
	chassis.waitUntil(3);
	disengageLatch();
	chassis.waitUntil(15);
	engageLatch();
	chassis.waitUntilDone();
	chassis.moveToPose(-15, 43.387, 62, 2000); // second ring
	intakeIn();
	chassis.waitUntilDone();
	chassis.moveToPose(-20, 45, 50, 500, {.forwards=false}); // reverse
	chassis.waitUntilDone();
	chassis.moveToPoint(-20, 52.921, 1000); // third ring
	chassis.waitUntilDone();
	chassis.turnToHeading(-45, 500);
	chassis.waitUntilDone();
	chassis.moveToPoint(-26, 0, 5000, {.maxSpeed=50}); // ladder
	pros::delay(500);
	intakeStop();
	engageDoinky();
	chassis.waitUntilDone();
}