#include "drivetrain.h"
#include "lemlib/chassis/trackingWheel.hpp"
#include "main.h"
#include "pros/rotation.hpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

/*
################
-  DRIVETRAIN  -
################
 */

pros::MotorGroup driveLeft({PORT_DRIVE_LEFT_FRONT, PORT_DRIVE_LEFT_TOP, PORT_DRIVE_LEFT_BOTTOM}, pros::MotorGearset::blue);
pros::MotorGroup driveRight({PORT_DRIVE_RIGHT_FRONT, PORT_DRIVE_RIGHT_TOP, PORT_DRIVE_RIGHT_BOTTOM}, pros::MotorGearset::blue);

// drivetrain settings
lemlib::Drivetrain drivetrain(&driveLeft, // left motor group
                              &driveRight, // right motor group
                              13, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 300
                              2 // chase power is 2. If we had traction wheels, it would have been 8
);

/*
###############
-  DRIVE PID  -
###############
*/ 

// lateral motion controller
lemlib::ControllerSettings linearController(15, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              75, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

/*
##############
-  ODOMETRY  -
##############
*/

//pros::ADIEncoder xEncoder = pros::ADIEncoder(PORT_ADI_XENCODER_TOP, PORT_ADI_XENCODER_BOTTOM, true);
//pros::ADIEncoder yEncoder = pros::ADIEncoder(PORT_ADI_YENCODER_TOP, PORT_ADI_YENCODER_BOTTOM, false);

//lemlib::TrackingWheel xTracker(&xEncoder, 2.75, -1.00393701, 1);
//lemlib::TrackingWheel yTracker(&yEncoder, 2.75, -0.0196850394, 1);

pros::Imu imu = pros::Imu(PORT_INERTIAL); 
pros::Rotation horizontalTracker(PORT_ROTATION_HORIZONTAL);
pros::Rotation verticalTracker(PORT_ROTATION_VERTICAL);
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontalTracker, lemlib::Omniwheel::NEW_2, -2.25);
lemlib::TrackingWheel vertical_tracking_wheel(&verticalTracker, lemlib::Omniwheel::NEW_2, 0.875);

lemlib::OdomSensors odomSensors(nullptr, // vertical tracking wheel 1, set to null
                                nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                                &horizontal_tracking_wheel, // horizontal tracking wheel 1
                                nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                                &imu // inertial sensor
);

lemlib::Chassis chassis = lemlib::Chassis(drivetrain, linearController, angularController, odomSensors);

void arcadeDrive(double leftAxis, double rightAxis) {
    driveLeft.move(leftAxis);
    driveRight.move(rightAxis);
}