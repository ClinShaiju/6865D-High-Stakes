#pragma once
#include "ladybrown.h"
#include "main.h"

enum LadybrownState {
  REST = 0,
 CATCH = 390,
  // CATCH = 470,
  LADDER = 600,
  NEUTRAL = 1650, //1250 is with no slop
  ALLIANCE = 2150,
  MANUAL 
};

// enum LadybrownState {
//   REST = 0,
//   CATCH = 340,
//   NEUTRAL = 1650, //1250 is with no slop
//   ALLIANCE = 2150,
//   MANUAL 
// };

extern double kP;
extern double kD;
extern double currentRotation;

void ladybrownInit();
void runLadybrown();
void ladybrownPID();
void PIDtuner();
void ladybrownTap();
LadybrownState returnState();
void setLadybrownRotation(double);
void cycleLadybrown(LadybrownState);
void setLadybrown(LadybrownState);
