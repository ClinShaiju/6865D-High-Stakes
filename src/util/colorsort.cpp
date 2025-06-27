  #include "auton/selector.h"
  #include "main.h"
  #include "subsystem/doinky.h"
  #include "subsystem/intake.h"
  #include "subsystem/latch.h"

  pros::Optical optical(PORT_OPTICAL);
  pros::Distance sortSensor(PORT_DISTANCE);

  #define WAIT_TIME 50
  #define STOP_TIME 200

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
    optical.set_integration_time(20);
    while (true) {
      IntakeState prevIntakeState = getIntakeState();
      IntakeState prevHookState = getHookState();
      Alliance seenColor = getColor(optical.get_hue());

      if (seenColor != currentAlliance && seenColor != OTHER) {
        bool resetSort = false;

        while (sortSensor.get_distance() > 20) {

          if (getColor(optical.get_hue()) == currentAlliance &&
              seenColor != OTHER) {
            resetSort = true;
            break;
          }
          pros::delay(20);
        }
        if (!resetSort) {
          pros::delay(WAIT_TIME);

          setIntakeState(STOPPED, STOPPED);
          setIntakeState(BLOCKED, BLOCKED);
          pros::delay(STOP_TIME);

          setIntakeState(prevIntakeState, prevHookState);
        }

      }
      pros::delay(20);
    }
  }
