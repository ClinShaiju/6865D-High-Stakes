#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/rtos.hpp"
#include "subsystem/drivetrain.h"
#include "subsystem/intake.h"
#include "subsystem/ladybrown.h"
#include "subsystem/latch.h"

void blueAWP() {
	setLadybrownRotation(360);
  chassis.setPose(52.5, 12.75, 116);
  chassis.moveToPose(56, 9.25, 120, 2000,
                     {.minSpeed = 50}); // Score on alliance
  setLadybrown(ALLIANCE);
  chassis.waitUntilDone();
  chassis.moveToPose(24, 24, 135, 3000,
                     {.forwards = false, .lead = .1}); // Move to goal
  chassis.waitUntil(5);
  setLadybrown(REST);
  chassis.waitUntil(10);
  chassis.cancelAllMotions();
  chassis.moveToPose(
      24, 25.5, 135, 3000,
      {.forwards = false, .lead = .1, .maxSpeed = 50}); // Move to goal slower
  chassis.waitUntil(18);
  engageLatch();
  chassis.cancelAllMotions();
  chassis.turnToHeading(0, 600);       // Face first ring stack
  chassis.moveToPose(24, 48, 0, 2000); // Get first ring stack
  setIntakeState(IN, IN);
  chassis.waitUntil(24);
  chassis.cancelAllMotions();
  chassis.swingToHeading(135, lemlib::DriveSide::LEFT,
                         1000); // Swing for 2nd ring stack
  chassis.waitUntilDone();
  chassis.moveToPose(48, 0, 180, 3000, {.minSpeed=50}); // Go to second ring stack
  chassis.waitUntilDone();
  chassis.moveToPose(48, -8, 180, 3000); // Go to second ring stack
  chassis.waitUntilDone();
  chassis.swingToHeading(90, lemlib::DriveSide::LEFT, 1000); // Swing to face 2nd goal
  disengageLatch();
  chassis.waitUntilDone();
  chassis.moveToPose(24, -19, 110, 3000, {.forwards = false, .lead=.8}); // Move to 2nd goal
  chassis.waitUntil(20);
  chassis.cancelAllMotions();
  chassis.moveToPose(21, -18, 110, 500, {.forwards = false,.lead=.8, .maxSpeed=50}); // Move to 2nd goal slower
  chassis.waitUntilDone();
  engageLatch();
  pros::delay(250);
  chassis.moveToPose(26, -43, -170, 2000);
  chassis.waitUntilDone();
  chassis.moveToPose(12, -10, 135, 2000, {.forwards=false, .minSpeed=100});
  chassis.waitUntil(12);
  setLadybrown(LADDER);
  chassis.waitUntilDone();
}