#include "main.h"
#include "lemlib/asset.hpp"
#include "lemlib/pose.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "subsystem/doinky.h"
#include "subsystem/drivetrain.h"
#include "subsystem/intake.h"
#include "subsystem/latch.h"

float driveVturn = .5;

float formatHeading(float heading) {
    int signum = sgn(heading);
    float output = std::abs(heading);

    while (output > 360) output -= 360;
    if (signum == -1) return 360 - output;
    return output;
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void updateLED() {

	while (true) {
		lemlib::Pose pose = chassis.getPose();

		pros::lcd::print(1,   "x: %f", pose.x);
		pros::lcd::print(2,   "y: %f", pose.y);
		pros::lcd::print(3,   "head: %f", formatHeading(pose.theta));

		// if (isLatched()) {

		// pros::c::controller_print(pros::E_CONTROLLER_MASTER, 1, 1, "%s", "Closed");
		// } else {

		// pros::c::controller_print(pros::E_CONTROLLER_MASTER, 1, 1, "%s", "Open");
		// }
		pros::c::controller_print(pros::E_CONTROLLER_MASTER, 1, 1, "%.2f", (pose.y));


		pros::delay(20);
	}
}

void initialize() {
	pros::lcd::initialize();
	chassis.calibrate();
	pros::Task task(updateLED);

}

void disabled() {
}

ASSET(firstgoal_txt);
ASSET(secondgoal_txt);
ASSET(thirdgoal_txt);
ASSET(fourthgoal_txt);

void competition_initialize() {
}

void skillsAuton() {
	chassis.setPose(-60, 1.5, 90);
	intakeIn();
	pros::delay(500);
	chassis.follow(firstgoal_txt, 15, 15000);
	chassis.follow(secondgoal_txt, 15, 15000);
	chassis.follow(thirdgoal_txt, 15, 15000);
	chassis.follow(fourthgoal_txt, 15, 15000);
	
}

void redBetterAuton() {
	chassis.setPose(-53.374, 15.5, 180);
	chassis.moveToPose(-54, -9, 180, 1000); // Push out starting ring
	chassis.waitUntilDone();
	chassis.moveToPose(-60, 1.5, 90, 1500, {.forwards=false}); // score alliance stake
	chassis.waitUntilDone();
	intakeIn();
	chassis.waitUntilDone();
	pros::delay(500);
	intakeStop();
	chassis.moveToPose(-28.322, 46, 56, 2000); // first ring
	intakeIn();
	chassis.waitUntil(70);
	intakeStop();
	chassis.waitUntilDone();
	chassis.moveToPose(-29, 27, 0, 1200, {.forwards=false, .lead=0.3}); // goal
	chassis.waitUntil(3);
	disengageLatch();
	chassis.waitUntil(15);
	engageLatch();
	chassis.waitUntilDone();
	chassis.moveToPose(-15, 43.387, 62, 2000); // second ring
	intakeIn();
	chassis.waitUntilDone();
	chassis.moveToPose(-20, 45, 50, 500, {.forwards=false}); // reverse
	chassis.waitUntilDone();
	chassis.moveToPoint(-20, 52.921, 1000); // third ring
	chassis.waitUntilDone();
	chassis.turnToHeading(-45, 500);
	chassis.waitUntilDone();
	chassis.moveToPoint(-26, 0, 5000, {.maxSpeed=50}); // ladder
	pros::delay(500);
	intakeStop();
	engageDoinky();
	chassis.waitUntilDone();
}

void blueBetterAuton() {
	chassis.setPose(53.374, 16.5, -180);
	chassis.moveToPose(53, -9, -180, 1000); // Push out starting ring
	chassis.waitUntilDone();
	chassis.moveToPose(61, 0, -90, 1500, {.forwards=false}); // score alliance stake
	chassis.waitUntilDone();
	intakeIn();
	chassis.waitUntilDone();
	pros::delay(500);
	intakeStop();
	chassis.moveToPose(20.322, 46, -56, 2000); // first ring
	intakeIn();
	chassis.waitUntil(60);
	intakeStop();
	chassis.waitUntilDone();
	chassis.moveToPose(20, 30, 0, 1200, {.forwards=false, .lead=0.3, .maxSpeed=80}); // goal
	chassis.waitUntil(3);
	disengageLatch();
	chassis.waitUntil(15);
	engageLatch();
	chassis.waitUntilDone();
	chassis.moveToPose(6, 42.387, -62, 2000); // second ring
	pros::delay(100);
	intakeIn();
	chassis.waitUntilDone();
	chassis.moveToPose(11, 44, -50, 500, {.forwards=false}); // reverse
	chassis.waitUntilDone();
	chassis.moveToPoint(11, 51.921, 1000); // third ring
	chassis.waitUntilDone();
	chassis.turnToHeading(45, 500);
	chassis.waitUntilDone();
	chassis.moveToPoint(23, 0, 5000, {.maxSpeed=50}); // ladder
	pros::delay(500);
	intakeStop();
	engageDoinky();
	chassis.waitUntilDone();
}

void autonomous() {
    skillsAuton();
	

}


void opcontrol() {

	while (true) {
		lemlib::Pose pose = chassis.getPose();

		pros::lcd::print(1,   "x: %f", pose.x);
		pros::lcd::print(2,   "y: %f", pose.y);
		pros::lcd::print(3,   "head: %f", formatHeading(pose.y));

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) autonomous();
		else {
			runLatchToggle();
			runIntake();
			runDoinkyToggle();
			int yAxis = returnExponential(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), 1, 10);
			int xAxis = returnExponential(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), 2, 6);
			chassis.arcade(yAxis, xAxis);
			pros::delay(20);
		}
	}
}


//hawk tuah SPIT ON THAT THANG!!!!