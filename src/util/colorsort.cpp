#include "auton/selector.h"
#include "main.h"
#include "subsystem/intake.h"

pros::Optical optical(PORT_OPTICAL);

#define STOP_DISTANCE 320
#define WAIT_TIME 500

bool holdRing = false;

Alliance getColor(double hue) {
  if (hue > 190 && hue < 230)
    return BLUE;
  else if (hue > 0 && hue < 25)
    return RED;
  return OTHER;
}

void colorSort() {
  optical.set_led_pwm(100);
  while (true) {
    IntakeState prevIntakeState = getIntakeState();
    Alliance seenColor = getColor(optical.get_hue());
    int startingIntakeRot = getIntakeRotations();

    // if (seenColor != currentAlliance && seenColor != OTHER) {
    // 	while ((std::abs(getIntakeRotations() - startingIntakeRot)) <
    // STOP_DISTANCE) {} 	setIntakeState(BLOCKED);

    // 	startingIntakeRot = getIntakeRotations();

    // 	pros::delay(WAIT_TIME);
    // 	setIntakeState(prevIntakeState);
    // }

    if (seenColor != currentAlliance && seenColor != OTHER) {
      while (limitSwitch.get_value()) {
        pros::delay(20);
      }
      setIntakeState(BLOCKED);

      pros::delay(WAIT_TIME);
      setIntakeState(prevIntakeState);
    }
    else if (holdRing && seenColor == currentAlliance && seenColor != OTHER) {
      setIntakeState(STOPPED);
    }
    pros::delay(20);
  }
}

// double getOpticalColor()
// {
//   return optical.get_hue();
// }

void setIntakeHold (bool hold)
{
    holdRing = hold;
}

