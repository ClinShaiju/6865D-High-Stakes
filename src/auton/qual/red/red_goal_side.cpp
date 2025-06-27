#include "main.h"
#include "pros/rtos.hpp"
#include "subsystem/doinky.h"
#include "subsystem/drivetrain.h"
#include "subsystem/intake.h"
#include "subsystem/latch.h"

void redGoalAuton() {
  chassis.setPose(-52, -67.125, 71.5);
  setIntakeState(IN, STOPPED);
  chassis.moveToPose(10, -52.5, 90, 3000, {.lead=.1, .minSpeed = 127}); // Rush Goal
  engageDoinky();
  chassis.waitUntil(27);
  engageClaw();
  chassis.cancelAllMotions();
  pros::delay(250);
  chassis.moveToPose(-36, -53.5, 90, 3000,
                     {.forwards = false, .minSpeed = 127}); // Move back
  chassis.waitUntil(20); // Release claw while coming back
  disengageClaw();
  chassis.waitUntilDone();
  disengageDoinky();
  chassis.turnToHeading(-45, 1000); // Face latch toward rushed goal
  chassis.waitUntilDone();
  chassis.moveToPose(-23, -65, -45, 2000,
                     {.forwards = false}); // Turn ot grab rushed goal
  chassis.waitUntil(18);
  engageLatch();
  setIntakeState(IN, IN);
  chassis.waitUntilDone();
  pros::delay(500);
  chassis.turnToHeading(-45, 1500);
  chassis.waitUntilDone();
  chassis.moveToPose(-57, -57, 90, 3000, {.forwards=false});
  chassis.waitUntilDone();
  disengageLatch();
  chassis.turnToHeading(135, 2000); // Face 2nd goal
  chassis.waitUntilDone();
  chassis.moveToPose(-26, -24, -180, 3000, {.forwards = false}); // Go to 2nd goal
  chassis.waitUntilDone();
  engageLatch();
  chassis.moveToPose(-48, -24, -90, 3000); // Preload
  chassis.waitUntilDone();
  chassis.moveToPose(-57, -57, 45, 3000, {.forwards=false}); 
  pros::delay(2000);
}

// Grab goal, score preload and on field, drop near corner and set up for 2nd goal

// chassis.setPose(53, 41.5, 55);
// chassis.moveToPose(25, 22.5, 53, 1200,
//                    {.forwards = false, .minSpeed = 70}); // 1st ring
// chassis.waitUntilDone();
// //chassis.waitUntil(39.5);
// engageLatch(); // grab stake
// pros::delay(100);
// setIntakeState(IN, IN);
// chassis.moveToPose(23.5, 43, 0, 2500); // 2nd
// // ring
// chassis.waitUntilDone();
// chassis.moveToPose(47, 47, 90, 2500); //go to corner // HEADING WAS GONE SO I PUT 90!
// chassis.waitUntilDone();
// chassis.turnToHeading(-135, 850);
// chassis.waitUntilDone();
// disengageLatch();
// chassis.turnToHeading(-90, 850);
// chassis.moveToPoint(18, 46, 2500, { .forwards=false}); //go to corner
// chassis.waitUntilDone();