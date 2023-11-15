#include "main.h"

okapi::Motor flywheel_m1(FW_PORT_1, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor flywheel_m2(FW_PORT_2, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);

void update_flywheel() {
    if (controller.getDigital(BUTTON_FW_FORWARD) == 1) {
        flywheel_m1.moveVelocity(600);
        flywheel_m2.moveVelocity(600);
    } 

    if (controller.getDigital(BUTTON_FW_BACKWARD) == 1) {
        flywheel_m1.moveVelocity(-600);
        flywheel_m2.moveVelocity(-600);
    }

    if (controller.getDigital(BUTTON_FW_FORWARD) == 0 && (controller.getDigital(BUTTON_FW_BACKWARD) == 0)){
        flywheel_m1.moveVelocity(0);
        flywheel_m2.moveVelocity(0);
    }
}
