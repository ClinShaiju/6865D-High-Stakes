#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/rtos.hpp"
#include "subsystem/drivetrain.h"
#include "subsystem/intake.h"
#include "subsystem/ladybrown.h"
#include "subsystem/latch.h"

void redAWP() {
  setLadybrownRotation(360);
  chassis.setPose(-52.5, 12.75, -116);
  chassis.moveToPose(-56, 9.25, -120, 2000,
                     {.minSpeed = 50}); // Score on alliance
  setLadybrown(ALLIANCE);
  chassis.waitUntilDone();
  chassis.moveToPose(-24, 24, -135, 3000,
                     {.forwards = false, .lead = .1}); // Move to goal
  chassis.waitUntil(5);
  setLadybrown(REST);
  chassis.waitUntil(10);
  chassis.cancelAllMotions();
  chassis.moveToPose(
      -24, 25.5, -135, 3000,
      {.forwards = false, .lead = .1, .maxSpeed = 50}); // Move to goal slower
  chassis.waitUntil(18);
  engageLatch();
  chassis.cancelAllMotions();
  chassis.turnToHeading(0, 600);       // Face first ring stack
  chassis.moveToPose(-28, 48, 0, 2000); // Get first ring stack
  setIntakeState(IN, IN);
  chassis.waitUntil(24);
  chassis.cancelAllMotions();
  chassis.swingToHeading(-135, lemlib::DriveSide::RIGHT,
                         1000); // Swing for 2nd ring stack
  chassis.waitUntilDone();
  chassis.moveToPose(-53, 0, -170, 3000, {.lead=.3, .minSpeed=50}); // Go to second ring stack
  chassis.waitUntilDone();
  chassis.moveToPose(-53, -12, -180, 3000); // Go to second ring stack
  chassis.waitUntilDone();
  chassis.swingToHeading(-90, lemlib::DriveSide::RIGHT, 1000); // Swing to face 2nd goal
  disengageLatch();
  chassis.waitUntilDone();
  chassis.moveToPose(-24, -28, -90, 3000, {.forwards = false, .lead=.2}); // Move to 2nd goal
  chassis.waitUntil(10);
  chassis.cancelAllMotions();
  chassis.moveToPose(-24, -28, -90, 500, {.forwards = false, .maxSpeed=50}); // Move to 2nd goal slower
  chassis.waitUntilDone();
  engageLatch();
  chassis.moveToPose(-28 , -52, -170, 2000);
  chassis.waitUntilDone();
  chassis.moveToPose(-12, -10, -135, 2000, {.forwards=false, .minSpeed=100});
  chassis.waitUntil(12);
  setIntakeState(STOPPED, STOPPED);
  setLadybrown(LADDER);
  chassis.waitUntilDone();
}