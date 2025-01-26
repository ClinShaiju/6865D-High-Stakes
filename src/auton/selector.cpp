#include "selector.h"
#include "auton.h"
#include "main.h"
#include "subsystem/drivetrain.h"
#include <charconv>
#include <cstdio>
#include <cstring>
#include <exception>
#include <string>

Alliance currentAlliance = RED;
Side currentSide = RING;
bool isElim = false;
bool isSkills = false;

static lv_obj_t* allianceSwitch;
static lv_obj_t* sideSwitch;
static lv_obj_t* skillsSwitch;
static lv_obj_t* elimSwitch;

static lv_obj_t* poseXLabel;
static lv_obj_t* poseYLabel;
static lv_obj_t* poseThetaLabel;

void odomUpdateTimer(lv_timer_t* timer) {
    char buffer[100];
    sprintf(buffer, "X: %.2f", chassis.getPose().x);
    lv_label_set_text(poseXLabel, buffer);
    sprintf(buffer, "Y: %.2f", chassis.getPose().y);
    lv_label_set_text(poseYLabel, buffer);
    sprintf(buffer, "Theta: %.2f", formatHeading(chassis.getPose().theta));
    lv_label_set_text(poseThetaLabel, buffer);

}

static void allianceSwitchCb(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    if (lv_obj_has_state(obj, LV_STATE_CHECKED)) currentAlliance = BLUE;
    else currentAlliance = RED;

}

static void sideSwitchCb(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    if (lv_obj_has_state(obj, LV_STATE_CHECKED)) currentSide = GOAL;
    else currentSide = RING;

}

static void skillsSwitchCb(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    if (lv_obj_has_state(obj, LV_STATE_CHECKED)) {
        isSkills = true;

        lv_obj_add_state(allianceSwitch, LV_STATE_DISABLED);
        lv_obj_add_state(sideSwitch, LV_STATE_DISABLED);
        lv_obj_add_state(elimSwitch, LV_STATE_DISABLED);

        currentAlliance = RED;
        lv_obj_clear_state(allianceSwitch, LV_STATE_CHECKED);

    }
    else {
        isSkills = false;

        lv_obj_clear_state(allianceSwitch, LV_STATE_DISABLED);
        lv_obj_clear_state(sideSwitch, LV_STATE_DISABLED);
        lv_obj_clear_state(elimSwitch, LV_STATE_DISABLED);

    }

}
static void elimSwitchCb(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    if (lv_obj_has_state(obj, LV_STATE_CHECKED)) isElim = true;
    else isElim = false;

}


void gui() {
    static lv_obj_t* tabView = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 40);

    lv_obj_t* autonsTab = lv_tabview_add_tab(tabView, "Autons");
    lv_obj_t* debugTab = lv_tabview_add_tab(tabView, "Debug");
    lv_obj_t* configTab = lv_tabview_add_tab(tabView, "Config");

    lv_obj_set_flex_flow(autonsTab, LV_FLEX_FLOW_ROW_WRAP);
    static lv_style_t invContainerStyle;
    lv_style_init(&invContainerStyle);
    lv_style_set_pad_column(&invContainerStyle, 0);

    lv_obj_t* allianceRow = lv_obj_create(autonsTab);
    lv_obj_t* sideRow = lv_obj_create(autonsTab);
    lv_obj_t* skillsRow = lv_obj_create(autonsTab);
    lv_obj_t* elimRow = lv_obj_create(autonsTab);

    lv_obj_set_size(allianceRow, 215, 80);
    lv_obj_set_size(sideRow, 215, 80);
    lv_obj_set_size(skillsRow, 215, 80);
    lv_obj_set_size(elimRow, 215, 80);


    lv_obj_add_style(allianceRow, &invContainerStyle, LV_STATE_DEFAULT);
    lv_obj_add_style(skillsRow, &invContainerStyle, LV_STATE_DEFAULT);
    lv_obj_add_style(skillsRow, &invContainerStyle, LV_STATE_DEFAULT);
    lv_obj_add_style(elimRow, &invContainerStyle, LV_STATE_DEFAULT);
 
    lv_obj_t* redLabel = lv_label_create(allianceRow);
    lv_label_set_text(redLabel, "Red");
    allianceSwitch = lv_switch_create(allianceRow);
    lv_obj_t* blueLabel = lv_label_create(allianceRow);
    lv_label_set_text(blueLabel, "Blue");

    lv_obj_t* otherLabel = lv_label_create(sideRow);
    lv_label_set_text(otherLabel, "Rings");
    sideSwitch = lv_switch_create(sideRow);
    lv_obj_t* goalLabel = lv_label_create(sideRow);
    lv_label_set_text(goalLabel, "Goal");

    lv_obj_t* offLabel = lv_label_create(skillsRow);
    lv_label_set_text(offLabel, "Off");
    skillsSwitch = lv_switch_create(skillsRow);
    lv_obj_t* skillsLabel = lv_label_create(skillsRow);
    lv_label_set_text(skillsLabel, "Skills");

    lv_obj_t* qualLabel = lv_label_create(elimRow);
    lv_label_set_text(qualLabel, "Quals");
    elimSwitch = lv_switch_create(elimRow);
    lv_obj_t* elimLabel = lv_label_create(elimRow);
    lv_label_set_text(elimLabel, "Elims");

    lv_obj_set_flex_flow(allianceRow, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(allianceRow, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_set_flex_flow(sideRow, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(sideRow, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_set_flex_flow(skillsRow, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(skillsRow, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_set_flex_flow(elimRow, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(elimRow, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    static lv_style_t allianceSwitchStyle;
    lv_style_init(&allianceSwitchStyle);

    static lv_style_t tabViewStyle;
    lv_style_init(&tabViewStyle);
    lv_style_set_bg_color(&tabViewStyle, lv_color_hex(0x000000));
    lv_style_set_text_color(&tabViewStyle, lv_color_hex(0xe6e6e6));
    lv_style_set_border_color(&tabViewStyle, lv_color_hex(0x707070));
    lv_obj_add_style(tabView, &tabViewStyle, LV_STATE_DEFAULT);
    lv_obj_add_style(autonsTab, &tabViewStyle, LV_STATE_DEFAULT);
    lv_obj_add_style(debugTab, &tabViewStyle, LV_STATE_DEFAULT);
    lv_obj_add_style(configTab, &tabViewStyle, LV_STATE_DEFAULT);
    lv_obj_add_style(allianceRow, &tabViewStyle, LV_STATE_DEFAULT);
    lv_obj_add_style(skillsRow, &tabViewStyle, LV_STATE_DEFAULT);
    lv_obj_add_style(elimRow, &tabViewStyle, LV_STATE_DEFAULT);
    lv_obj_add_style(sideRow, &tabViewStyle, LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(autonsTab, lv_color_hex(0x000000), 0);

    lv_obj_set_style_bg_color(allianceSwitch, lv_color_hex(0xed2626), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(sideSwitch, lv_color_hex(0xa8d600), LV_STATE_CHECKED | LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(sideSwitch, lv_color_hex(0x2484e3), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(skillsSwitch, lv_color_hex(0x31cc43), LV_STATE_CHECKED | LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(elimSwitch, lv_color_hex(0x31cc43), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(elimSwitch, lv_color_hex(0xed2626), LV_STATE_CHECKED | LV_PART_INDICATOR);

    lv_obj_add_event_cb(allianceSwitch, allianceSwitchCb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(sideSwitch, sideSwitchCb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(skillsSwitch, skillsSwitchCb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(elimSwitch, elimSwitchCb, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_t* odomContainer = lv_obj_create(debugTab);
    lv_obj_set_width(odomContainer, 445);
    lv_obj_set_height(odomContainer, 60);

    lv_obj_set_flex_flow(odomContainer, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(odomContainer, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_add_style(odomContainer, &invContainerStyle, LV_STATE_DEFAULT);

    poseXLabel = lv_label_create(odomContainer);
    lv_label_set_text(poseXLabel, "X: ##.##");
    poseYLabel = lv_label_create(odomContainer);
    lv_label_set_text(poseYLabel, "Y: ##.##");
    poseThetaLabel = lv_label_create(odomContainer);
    lv_label_set_text(poseThetaLabel, "Theta: ##.##");

    lv_timer_t* odomUpdater = lv_timer_create_basic();
    lv_timer_set_cb(odomUpdater, odomUpdateTimer);
    lv_timer_set_period(odomUpdater, 20);
    lv_timer_set_repeat_count(odomUpdater, -1);

}

void autonSelector() {
    if (isSkills) skillsAuton();
    else if (currentAlliance == BLUE){
        if (currentSide == GOAL) {
            if (isElim); 
            else;
        }
        else if (currentSide == RING) {
            if (isElim);
            else blueRingAuton();
        
        }
    }
    else if (currentAlliance == RED) {
        if (currentSide == GOAL) {
            if (isElim); 
            else;
        }
        else if (currentSide == RING) {
            if (isElim);
            else redRingAuton();
        
        }
    }
}


