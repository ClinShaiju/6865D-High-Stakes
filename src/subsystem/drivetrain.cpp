#include "drivetrain.h"
#include "main.h"

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
                              11.875, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 4" omnis
                              300, // drivetrain rpm is 300
                              8 // chase power is 2. If we had traction wheels, it would have been 8
);

/*
###############
-  DRIVE PID  -
###############
*/ 

// lateral motion controller
lemlib::ControllerSettings linearController(40, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              250, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in pp inches
                                              0, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(4, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             35, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
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

lemlib::OdomSensors odomSensors(nullptr, // vertical tracking wheel 1, set to null
                                nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                                nullptr, // horizontal tracking wheel 1
                                nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                                &imu // inertial sensor
);

lemlib::Chassis chassis = lemlib::Chassis(drivetrain, linearController, angularController, odomSensors);

void arcadeDrive(double leftAxis, double rightAxis) {
    driveLeft.move(leftAxis);
    driveRight.move(rightAxis);
}