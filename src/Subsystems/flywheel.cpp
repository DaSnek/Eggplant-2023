#include "main.h"

okapi::Motor flywheel_m1(FW_PORT_1, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor flywheel_m2(FW_PORT_2, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::degrees);

okapi::MotorGroup flywheel({flywheel_m1, flywheel_m2});

//--------------------------------------------------------------

void update_flywheel() {
    if (controller.getDigital(BUTTON_FW_FORWARD)) {
        flywheel.moveVelocity(590);
    
        
        leftDrive.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        rightDrive.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
    } 

    if (controller.getDigital(BUTTON_FW_BACKWARD)) {
        flywheel.moveVelocity(-590);

        leftDrive.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        rightDrive.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
    }

    if (controller.getDigital(BUTTON_INTAKE)) {
        flywheel.moveVoltage(4800);
    }

    if (!controller.getDigital(BUTTON_FW_FORWARD) && !controller.getDigital(BUTTON_FW_BACKWARD) 
            && !controller.getDigital(BUTTON_INTAKE)) {
        flywheel.moveVelocity(0);

        leftDrive.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
        rightDrive.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
    }
}
