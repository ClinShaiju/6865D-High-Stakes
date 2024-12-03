//
// Created by shaijcli000 on 9/25/2024.
//
#include "main.h"

double returnExponential(int axisValue, int type, float t) {
    double percentage = axisValue;
    if (type == 1) {
        if (percentage > 0) {
            percentage = 1.2 * pow(1.035664, percentage) - 1.2 + 0.2 * percentage;
        } else {
            percentage = -percentage;

            percentage = 1.2 * pow(1.035664, percentage) - 1.2 + 0.2 * percentage;

            percentage = -percentage;
        }
        return percentage;
    }
    else if (type == 2) {
        return (exp(-(t/10)) + exp((std::abs(percentage)-127)/10) * (1-exp(-(t/10))))*percentage;
    }
    else if (type == 3) {
        return (exp((std::abs(percentage)-127)/1000))*percentage;
    }
    return 0;
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

float formatHeading(float heading) {
    int signum = sgn(heading);
    float output = std::abs(heading);

    while (output > 360) output -= 360;
    if (signum == -1) return 360 - output;
    return output;
}
