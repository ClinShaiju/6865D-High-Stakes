#include "main.h"

void blueRingAuton() {
	chassis.setPose(53.374, 15.5, 180);
	chassis.moveToPose(54, -9, 180, 1000); // Push out starting ring
	chassis.waitUntilDone();
	chassis.moveToPose(62, 0, -90, 1500, {.forwards=false}); // score alliance stake
	chassis.waitUntilDone();
	intakeIn();
	chassis.waitUntilDone();
	pros::delay(500);
	intakeStop();
	chassis.moveToPose(24, 45, -56, 2000); // first ring
	intakeIn();
	chassis.waitUntil(70);
	intakeStop();
	chassis.waitUntilDone();
	chassis.moveToPose(23, 26, 0, 1200, {.forwards=false, .lead=0.5}); // goal
	chassis.waitUntil(3);
	disengageLatch();
	chassis.waitUntil(20);
	engageLatch();
	chassis.waitUntilDone();
	chassis.moveToPose(12, 39, -62, 2000); // second ring
	intakeIn();
	chassis.waitUntilDone();
	chassis.moveToPose(12, 55, 0, 1000); // third ring
	chassis.waitUntilDone();
	chassis.turnToHeading(45, 500);
	chassis.waitUntilDone();
	chassis.moveToPose(22, 0, 180, 5000, {.maxSpeed=50}); // ladder
	pros::delay(500);
	intakeStop();
	engageDoinky();
	chassis.waitUntilDone();
}