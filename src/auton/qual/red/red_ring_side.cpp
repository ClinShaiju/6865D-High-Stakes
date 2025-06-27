#include "main.h"
#include "pros/rtos.hpp"
#include "subsystem/doinky.h"
#include "subsystem/drivetrain.h"
#include "subsystem/intake.h"
#include "subsystem/latch.h"

void redRingAuton() {
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
  chassis.moveToPose(-10, 55, 90, 2500); // 3rd ring
  chassis.waitUntilDone();
  chassis.moveToPose(-27, 50.5, 90, 1000, {.forwards = false, .minSpeed = 90});
  chassis.waitUntilDone();
  chassis.moveToPose(-10, 46, 90, 3000, {.lead = 0.4}); // 4th ring
  chassis.waitUntilDone();
  chassis.moveToPose(-23, 40.5, 90, 1000, {.forwards = false, .minSpeed = 90});
  chassis.waitUntilDone();
  chassis.moveToPose(-24, 0, -180, 3000);
  chassis.waitUntilDone();

}