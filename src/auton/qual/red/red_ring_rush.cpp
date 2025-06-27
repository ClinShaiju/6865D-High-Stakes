#include "main.h"
#include "pros/rtos.hpp"
#include "subsystem/doinky.h"
#include "subsystem/drivetrain.h"
#include "subsystem/intake.h"
#include "subsystem/ladybrown.h"
#include "subsystem/latch.h"

void redRingRushAuton() {
  setLadybrown(REST);
  chassis.setPose(-52.5, 22.75, 40);
  chassis.moveToPose(-9, 40, 50, 2000, {.minSpeed = 100}); // prep for 1st ring
  chassis.waitUntil(46.795432469419-2); 
  setIntakeState(IN, IN);
  pros::delay(650);
  setIntakeState(STOPPED, IN);
  chassis.turnToHeading(0, 500);
  chassis.waitUntilDone();
  chassis.moveToPose(-4, 49.25, 0, 2000, {.minSpeed = 100}); // get 1st ring

  

  chassis.waitUntilDone();
  chassis.moveToPoint(-4, 49, 700);
  chassis.waitUntilDone();
}