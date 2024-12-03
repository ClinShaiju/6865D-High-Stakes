#pragma once
#include "main.h"
#include "selector.h"

enum Alliance {
    RED,
    BLUE,
    OTHER
};

enum Side {
    GOAL,
    RING
};

extern Alliance currentAlliance;
extern Side currentSide;
extern bool isElims;
extern bool isSkills;

void gui();
void autonSelector();