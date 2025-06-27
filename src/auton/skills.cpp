#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "subsystem/drivetrain.h"
#include "subsystem/intake.h"
#include "subsystem/ladybrown.h"
#include "subsystem/latch.h"
#include "util/colorsort.h"

void skillsAuton() {
  setLadybrownRotation(360);
  setIntakeState(STOPPED, STOPPED); // 1st ring
  chassis.setPose(-53.5, 1, -90);
  setLadybrown(ALLIANCE);
  pros::delay(1000);
  chassis.moveToPoint(-48, 1, 1500, {.forwards = false});
  chassis.waitUntilDone();
  chassis.turnToHeading(170, 350);
  chassis.waitUntilDone();
  setLadybrown(REST);
  disengageLatch();
  chassis.moveToPose(-45, 20, 180, 1500, {.forwards = false});
  chassis.waitUntilDone();
  engageLatch(); // 1st goal
  setIntakeState(IN, IN);
  chassis.moveToPose(-23, -23, 135, 2000, {.lead = .1}); // intake one ring
  chassis.waitUntilDone();
  chassis.moveToPose(0, -37, 90, 5000); // prepare for catch
  chassis.waitUntilDone();
  setLadybrown(CATCH);
  chassis.waitUntilDone();
  chassis.moveToPose(28, -51, 90, 5000); // get lb ring
  chassis.waitUntilDone();
  setIntakeState(STOPPED, STOPPED);
  chassis.moveToPose(1, -55, 180, 3000); // line up for wall
  chassis.waitUntilDone();
  setIntakeState(IN, STOPPED);
  chassis.moveToPose(1, -60, 180, 1000); // go to wall
  chassis.waitUntilDone();
  chassis.setPose(0, -56, 180);
  chassis.waitUntilDone();
  ladybrownTap();
  pros::delay(400);
  chassis.moveToPose(-1, -50, 180, 1000, {.forwards = false}); // away from wall
  chassis.waitUntilDone();
  setLadybrown(NEUTRAL);
  pros::delay(2000);
  setLadybrown(REST);
  pros::delay(1000);
  setIntakeState(IN, IN);
  chassis.moveToPose(-31, -45, -90, 2000,
                     {.lead = .25, .maxSpeed = 75}); // 1st ring
  chassis.waitUntilDone();
  chassis.moveToPose(-54, -45, -90, 2000, {.maxSpeed = 50}); // 2nd and 3rd ring
  chassis.waitUntilDone();
  chassis.moveToPose(-49, -45, -90, 2000,
                     {.forwards = false, .maxSpeed = 50}); // back up
  chassis.waitUntilDone();
  chassis.turnToHeading(170, 500); // face other ring
  chassis.waitUntilDone();
  chassis.moveToPoint(-50, -56, 1000); // get last ring
  chassis.waitUntilDone();
  chassis.turnToHeading(60, 1000); // turn to drop goal
  chassis.waitUntilDone();
  chassis.moveToPose(-62, -59, 45, 1000, {.forwards = false}); // goal in corner
  chassis.waitUntilDone();
  setIntakeState(STOPPED, STOPPED);
  disengageLatch();
  chassis.moveToPose(-44, -55, 45, 2000);
  chassis.waitUntilDone();
  chassis.turnToHeading(180, 1000); // face other stake
  chassis.waitUntilDone();
  chassis.moveToPose(-44, -23, 180, 3500,
                     {.forwards = false}); // grab second goal
  chassis.waitUntilDone();
  engageLatch();
  chassis.waitUntilDone();
  chassis.turnToHeading(67, 1000);
  chassis.waitUntilDone();
  setIntakeState(IN, STOPPED);
  chassis.moveToPose(5, 3, 45, 2500, {.lead = .6}); // go in center to get ring
  chassis.waitUntilDone();
  setIntakeState(IN, IN);
  pros::delay(500);
  setIntakeState(IN, STOPPED);
  chassis.turnToHeading(-45, 1000);
  chassis.waitUntilDone();
  chassis.moveToPoint(-18, 27, 2500); // one ring
  chassis.waitUntilDone();
  setIntakeState(IN, IN);
  pros::delay(500);
  chassis.moveToPose(-22, 53, 0, 3500); // 1st ring in line
  chassis.waitUntilDone();
  chassis.turnToHeading(-90, 1000);
  chassis.moveToPose(-47, 53, -90, 1000); // 2nd ring in line
  chassis.waitUntilDone();
  chassis.moveToPose(-55, 53, -90, 1000); // 3rd  ring in line
  chassis.waitUntilDone();
  chassis.moveToPose(-44, 53, -90, 1000, {.forwards = false}); // back up
  chassis.waitUntilDone();
  chassis.turnToHeading(-45, 1000);
  chassis.moveToPose(-43, 60, 0, 1000); // get last ring
  chassis.waitUntilDone();
  chassis.turnToHeading(135, 1000);
  chassis.waitUntilDone();
  chassis.moveToPose(-46, 68, 90, 1000,
                     {.forwards = false}); // 2nd goal in corner
  chassis.waitUntilDone();
  disengageLatch();

  // test
  chassis.moveToPose(0, 55, 90, 5000, {.maxSpeed = 50}); // prepare for wall

  // 2nd ladybrown
  //    setIntakeState(IN, STOPPED);
  //    chassis.moveToPose(0, 60, 0, 5000, {.maxSpeed=50}); // prepare for wall
  //    chassis.waitUntilDone();
  //    setLadybrown(CATCH);
  //    chassis.moveToPose(0, 54, 0, 5000); // get 1st ring
  //    setIntakeState(STOPPED, STOPPED);
  //    chassis.waitUntilDone();
  //    ladybrownTap();
  //    chassis.moveToPose(0, 55, 0, 3000); // line up for wall
  //    chassis.waitUntilDone();
  //    setIntakeState(IN, STOPPED);
  //    chassis.moveToPose(0, 68, 0, 3000); // go to wall
  //    chassis.waitUntilDone();
  //    chassis.setPose(0, 58.5, 0);
  //    chassis.waitUntilDone();
  //    setIntakeState(STOPPED, STOPPED);
  //    setLadybrown(NEUTRAL);
  //    chassis.waitUntilDone();
  //    pros::delay(2000);
  //    setLadybrown(REST);
  //    pros::delay(1000);
  //    setIntakeState(IN, STOPPED);
  //    chassis.waitUntilDone();
  // setIntakeState(IN, IN);

  // setIntakeState(IN, STOPPED);
  chassis.moveToPose(24, 24, 90, 2500); // 1st ring
  chassis.waitUntilDone();
  //   ladybrownTap();
  //   chassis.moveToPoint(36, 11, 2500);
  //   chassis.waitUntilDone();
  //   chassis.turnToHeading(-45, 850);
  //   chassis.waitUntilDone();
  //   chassis.moveToPose(40, 5, -45, 2500, {.forwards = false}); // grab stake
  //   chassis.waitUntilDone();
  //   engageLatch();

  setIntakeState(IN, STOPPED);
  chassis.moveToPose(57, 10, 5, 2500); // prepare for goal push
  chassis.waitUntilDone();
  chassis.moveToPose(60, 60, 25, 5000, {.minSpeed = 100}); // goal push
  chassis.waitUntilDone();
  setIntakeState(OUT, STOPPED);
  chassis.moveToPose(
      56, 40, 225, 5000,
      {.forwards = false, .maxSpeed = 50}); // back up after goal push
  chassis.waitUntilDone();

  // this code grabs stake

  chassis.moveToPose(46, 15, 0, 5000,
                     {.forwards = false}); // back up after goal push
  chassis.waitUntilDone();
  chassis.moveToPose(46, 8, 0, 5000,
                     {.forwards = false}); // back up after goal push
  chassis.waitUntilDone();
  engageLatch();
  chassis.turnToHeading(180, 500);
  chassis.waitUntilDone();
  chassis.moveToPoint(22, -25, 1500);
  chassis.waitUntilDone();
  chassis.moveToPose(22, -47, 180, 1500);
  chassis.waitUntilDone();
  chassis.turnToHeading(90, 500);
  chassis.waitUntilDone();
  chassis.moveToPose(60, -45, 90, 1500);
  chassis.waitUntilDone();
  chassis.moveToPose(35, -47, 180, 1500, {.forwards = false});
  chassis.waitUntilDone();
  chassis.moveToPoint(48, -60, 1500);
  chassis.waitUntilDone();
  chassis.turnToHeading(180, 500);
  chassis.waitUntilDone();
  chassis.turnToHeading(-90, 500);
  chassis.waitUntilDone();
  chassis.moveToPoint(52, -60, 1500, {.forwards = false});
  chassis.waitUntilDone();
  disengageLatch();

  //   setIntakeState(IN, IN);
  //   chassis.moveToPose(20, 48, -90, 2500, {.maxSpeed = 50}); // 2nd ring
  //   chassis.waitUntilDone();
  //   chassis.moveToPose(48, 0, 180, 2500);
  //   chassis.waitUntilDone();
  //   chassis.moveToPoint(19, -25, 2500); // 3rd ring
  //   chassis.waitUntilDone();
  //   chassis.turnToHeading(180, 750);
  //   chassis.waitUntilDone();
  //   chassis.moveToPose(24, -48, 180, 2500); // 4th ring
  //   chassis.waitUntilDone();
  //   chassis.moveToPose(64, -48, 90, 2500); // 5th and 6th ring
  //   chassis.waitUntilDone();
  //   chassis.moveToPose(48, -48, 180, 2500, {.forwards = false});
  //   chassis.waitUntilDone();
  //   chassis.moveToPose(48, -61, 180, 2500);
  //   chassis.turnToHeading(295, 750);
  //   chassis.waitUntilDone();
  //   chassis.moveToPose(58, -58, -45, 2500);
  //   chassis.waitUntilDone();
  //   engageLatch();
}
