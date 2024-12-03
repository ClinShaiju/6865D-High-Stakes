#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "subsystem/drivetrain.h"
#include "subsystem/intake.h"
#include "subsystem/latch.h"

ASSET(cornerone_tworings_txt);

void skillsAuton() {
	intakeIn();
	pros::delay(1000);
	intakeStop(); //1st ring
	chassis.setPose(-59,0,90);
	chassis.moveToPose(-40, -5, 125, 1000);
	chassis.waitUntilDone();
	intakeStop();
	disengageLatch();
	chassis.moveToPose(-46, 24, 180, 1500, {.forwards=false});
	chassis.waitUntilDone();
	engageLatch(); //1st goal
	chassis.follow(cornerone_tworings_txt, 15, 3500); //2 rings
	chassis.waitUntil(12);
	intakeIn();
	chassis.waitUntil(90);
	chassis.cancelAllMotions();
	intakeIn();
	chassis.moveToPose(-23, -50, -90, 1000); //ring w/ straight line
	chassis.waitUntilDone();
	chassis.moveToPose(-52, -50, -90, 1000);  //MORE rings
	chassis.waitUntilDone();
	chassis.moveToPose(-52, -50, -90, 1000); //face other ring
	chassis.waitUntilDone();
	chassis.turnToHeading(125, 500); 
	chassis.moveToPoint(-33, -72, 750); //get last ring
	chassis.waitUntilDone();
	chassis.swingToHeading(45, lemlib::DriveSide::RIGHT, 1000);
	chassis.waitUntilDone();
	chassis.turnToHeading(45, 1000);
	chassis.waitUntilDone();
	chassis.moveToPoint(-58, -72, 1500, {.forwards=false}); //back into corner
	disengageLatch();
	chassis.waitUntilDone();
	chassis.moveToPoint(-42, -40, 2000); //go get other stake
	chassis.waitUntilDone();
	chassis.turnToHeading(180, 1000);
	chassis.waitUntilDone();
	chassis.moveToPoint(-42, 36, 1500, {.forwards=false}); //get second goal
	chassis.waitUntilDone();
	engageLatch();
	
	
}