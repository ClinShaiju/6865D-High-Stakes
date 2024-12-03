#include "main.h"

void blueRingAuton() {
	chassis.setPose(53.374, 16.5, -180);
	chassis.moveToPose(53, -9, -180, 1000); // Push out starting ring
	chassis.waitUntilDone();
	chassis.moveToPose(61, 0, -90, 1500, {.forwards=false}); // score alliance stake
	chassis.waitUntilDone();
	intakeIn();
	chassis.waitUntilDone();
	pros::delay(500);
	intakeStop();
	chassis.moveToPose(20.322, 46, -56, 2000); // first ring
	intakeIn();
	chassis.waitUntil(60);
	intakeStop();
	chassis.waitUntilDone();
	chassis.moveToPose(20, 30, 0, 1200, {.forwards=false, .lead=0.3, .maxSpeed=80}); // goal
	chassis.waitUntil(3);
	disengageLatch();
	chassis.waitUntil(15);
	engageLatch();
	chassis.waitUntilDone();
	chassis.moveToPose(6, 42.387, -62, 2000); // second ring
	pros::delay(100);
	intakeIn();
	chassis.waitUntilDone();
	chassis.moveToPose(11, 44, -50, 500, {.forwards=false}); // reverse
	chassis.waitUntilDone();
	chassis.moveToPoint(11, 51.921, 1000); // third ring
	chassis.waitUntilDone();
	chassis.turnToHeading(45, 500);
	chassis.waitUntilDone();
	chassis.moveToPoint(23, 0, 5000, {.maxSpeed=50}); // ladder
	pros::delay(500);
	intakeStop();
	engageDoinky();
	chassis.waitUntilDone();
}

