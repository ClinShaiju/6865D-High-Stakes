#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "subsystem/drivetrain.h"
#include "subsystem/intake.h"
#include "subsystem/latch.h"

ASSET(cornerone_tworings_txt);
ASSET(center_to_leftcorner_3rings_txt);

void skillsAuton() {
	intakeIn();
	pros::delay(1000);
	intakeStop(); //1st ring
	chassis.setPose(-59,0,90);
	chassis.moveToPose(-32, -5, 125, 1000);
	chassis.waitUntilDone();
	disengageLatch();
	chassis.moveToPose(-45, 18, 180, 1500, {.forwards=false});
	chassis.waitUntilDone();
	engageLatch(); //1st goal
	chassis.follow(cornerone_tworings_txt, 15, 5000); //2 rings
	chassis.waitUntil(30);
	intakeIn();
	chassis.waitUntil(90);
	chassis.cancelAllMotions();
	intakeIn();
	chassis.turnToHeading(-90, 1500);
	chassis.waitUntilDone();
	chassis.moveToPose(-23, -51, -90, 2000); //ring w/ straight line
	chassis.waitUntilDone();
	chassis.moveToPose(-55, -51, -90, 2000);  //MORE rings
	chassis.waitUntilDone();
	chassis.turnToHeading(155, 500); //face other ring
	chassis.waitUntilDone();
	chassis.moveToPoint(-46, -66, 3000); //get last ring
	chassis.waitUntilDone();
	chassis.turnToHeading(60, 1000);
	chassis.waitUntilDone();
	chassis.moveToPoint(-58, -72, 3500, {.forwards=false}); //back into corner
	disengageLatch();
	chassis.waitUntilDone();
	chassis.moveToPose(-48, -55, 0, 2000); //face other stake
	chassis.waitUntilDone();
	chassis.turnToHeading(180, 1000);
	chassis.waitUntilDone();
	chassis.moveToPoint(-48, -30, 3500, {.forwards=false}); //get second goal
	chassis.waitUntilDone();
	engageLatch();
	chassis.turnToHeading(67, 1000);
	chassis.moveToPose(0, 0, 0,3500, {.lead=.2}); //go in center to get ring
	chassis.waitUntilDone();
	chassis.follow(cornerone_tworings_txt, 15, 3500);
	chassis.waitUntilDone();
	intakeStop();
}