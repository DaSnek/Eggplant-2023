#include "main.h"

okapi::Motor flywheel_m1(FW_PORT_1, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor flywheel_m2(FW_PORT_2, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);

okapi::MotorGroup flywheel({flywheel_m1, flywheel_m2});

void update_flywheel() {
    if (controller.getDigital(BUTTON_FW_FORWARD) == 1) {
        flywheel.moveVelocity(600);
        
        leftDrive.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        rightDrive.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
    } 

    if (controller.getDigital(BUTTON_FW_BACKWARD) == 1) {
        flywheel.moveVelocity(-600);

        leftDrive.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        rightDrive.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
    }

    if (controller.getDigital(BUTTON_FW_FORWARD) == 0 && (controller.getDigital(BUTTON_FW_BACKWARD) == 0)){
        flywheel.moveVelocity(0);

        leftDrive.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
        rightDrive.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
    }
}