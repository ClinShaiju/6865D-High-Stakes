#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "subsystem/drivetrain.h"
#include "subsystem/intake.h"
#include "subsystem/latch.h"
#include "subsystem/neutral_mech.h"
#include "util/colorsort.h"

ASSET(cornerone_tworings_txt);
ASSET(top_right_goal_txt);
ASSET(bottom_right_goal_txt);

void skillsAuton() {
	intakeIn();
	pros::delay(1000);
	intakeStop(); //1st ring
	chassis.setPose(-59,0,90);
	chassis.moveToPose(-32, -5, 125, 1000);
	chassis.waitUntilDone();
	disengageLatch();
	chassis.moveToPose(-43, 20, 180, 1500, {.forwards=false}); //1st goal
	chassis.waitUntil(26);
	engageLatch(); //1st goal
	chassis.waitUntilDone();
	intakeIn();
	chassis.moveToPoint(-20, -25, 1500); //intake one ring
	chassis.waitUntilDone();
	chassis.moveToPose(31, -52, 90,5000, {.lead=.3}); //hold far ring
	chassis.waitUntil(53);
	setRedirect(true);
	chassis.turnToHeading(-135, 5000);
	chassis.moveToPose(0, -55, 180, 5000);
	chassis.waitUntilDone();
	setRedirect(false);
	intakeIn();
	engageLift();
	pros::delay(2000);
	engageFlipout();
	pros::delay(2000);
	chassis.moveToPose(0, -59, 180, 2500);
	chassis.waitUntilDone();
	disengageLift();
	pros::delay(2000);
	disengageFlipout();
	pros::delay(2000);
	chassis.turnToHeading(-90, 1500);
	chassis.waitUntilDone();
	chassis.moveToPose(-31, -45, -90, 2000, {.lead=.25, .maxSpeed=75}); //ring w/ straight line
	chassis.waitUntilDone();
	chassis.moveToPose(-59, -48, -90, 2000, {.maxSpeed=50});  //MORE rings
	chassis.waitUntilDone();
	chassis.turnToHeading(155, 500); //face other ring
	chassis.waitUntilDone();
	chassis.moveToPoint(-46, -63, 1000); //get last ring
	chassis.waitUntilDone();
	chassis.turnToHeading(60, 1000);
	chassis.waitUntilDone();
	chassis.moveToPose(-61, -62, 45, 3500, {.forwards=false}); //back into corner
	chassis.waitUntil(2);
	intakeStop();
	chassis.waitUntilDone();
	disengageLatch();
	chassis.waitUntilDone();
	chassis.moveToPose(-44, -48, 45, 2000); 
	chassis.waitUntilDone();
	chassis.turnToHeading(180, 1000); //face other stake
	chassis.waitUntilDone();
	chassis.moveToPose(-46, -27, 180, 3500, {.forwards=false}); //grab second goal
	chassis.waitUntil(15);
	engageLatch();
	chassis.waitUntilDone();
	chassis.turnToHeading(67, 1000);
	intakeIn();
	chassis.waitUntilDone();
	chassis.moveToPose(5, 3, 45,2500); //go in center to get ring
	chassis.waitUntilDone();
	chassis.turnToHeading(-45, 1000); 
	chassis.moveToPoint(-22, 27, 2500); //one ring
	chassis.waitUntilDone();
	chassis.moveToPose(-22, 53, 0, 3500); //1st ring in line
	chassis.waitUntilDone();
	chassis.turnToHeading(-90, 1000);
	chassis.moveToPose(-47, 48, -90, 1000); //2nd ring in line
	chassis.waitUntilDone();
	chassis.moveToPose(-58, 48, -90,1000); //3rd  ring in line
	chassis.waitUntilDone();
	chassis.turnToHeading(-45, 1000);
	chassis.moveToPoint(-43, 60, 3500); //get last ring
	chassis.waitUntilDone();
	chassis.turnToHeading(90, 1000);
	chassis.moveToPoint(-60, 68, 1000, {.forwards=false}); //2nd goal in corner
	chassis.waitUntilDone();
	intakeStop();
	disengageLatch();
	chassis.moveToPoint(27, 32, 5000); // travel to other side
	chassis.waitUntil(15);
	intakeIn();
	setIntakeHold(true);
	chassis.waitUntilDone(); 
	setIntakeHold(false);	
	chassis.moveToPoint(23, 23, 5000); // pick up ring
	chassis.waitUntilDone();
	chassis.moveToPoint(37, 7, 5000); // facing stake
	chassis.waitUntilDone();
	chassis.turnToHeading(-45, 1000); //back facec to stake
	chassis.moveToPoint(44, 3, 5000, {.forwards=false});
	chassis.waitUntilDone();
	engageLatch();
	chassis.moveToPose(26, 50, 90, 2000);
	chassis.waitUntil(15);
	intakeIn();
	chassis.waitUntilDone();
	chassis.turnToHeading(45, 1000);
	chassis.moveToPoint(3, 60, 5000); // get topmost ring
	chassis.waitUntilDone();


	
 }
//chassis.waitUntilDone();
// 	chassis.turnToHeading(25, 500); //turn to face top right stake
// 	chassis.moveToPose(64, 60, 25,2000); //put top right stake in corner
// 	chassis.waitUntilDone();
// 	chassis.moveToPose(49, -10, 25, 1500, {.forwards=false}); //move to middle: clin this is probably stupid line of code to add but wtv lolsies
// 	chassis.waitUntilDone();
// 	chassis.turnToHeading(325, 750);
// 	chassis.waitUntilDone();
// 	chassis.moveToPose(64, -64, -15, 2000, {.forwards=false}); //bottom right stake in corner
// 	chassis.waitUntilDone();