#include "main.h"

#include "okapi/api/odometry/point.hpp"

using namespace okapi;

//---------------------------------Group-definitions---------------------------------------

Motor rightFront(RIGHT_FRONT, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightMiddle(RIGHT_MIDDLE, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightBack(RIGHT_BACK, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

Motor leftFront(LEFT_FRONT, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor leftMiddle(LEFT_MIDDLE, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor leftBack(LEFT_BACK, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

MotorGroup leftDrive({leftFront, leftMiddle, leftBack}); 
MotorGroup rightDrive({rightFront, rightMiddle, rightBack});

MotorGroup Drive({rightFront, rightMiddle, rightBack, leftFront, leftMiddle, leftBack});

std::shared_ptr<OdomChassisController> drive = ChassisControllerBuilder()
    .withMotors({leftFront, leftMiddle, leftBack}, {rightFront, rightMiddle, rightBack}) 
    .withDimensions(AbstractMotor::gearset::blue, {{WHEEL_SIZE, DRIVE_WIDTH}, okapi::imev5BlueTPR * (GEAR_RATIO)})
    .withOdometry() 
    .buildOdometry();

okapi::IMU inertial = okapi::IMU(IMU_PORT);

//-------------------------------------functions------------------------------------------

//debug
void print_state(std::string title, const okapi::OdomState& os) {
    printf("%s: %lf, %lf, %lf\n", title.c_str(),
        os.y.convert(okapi::foot), os.x.convert(okapi::foot),
        os.theta.convert(okapi::degree));
}

//debug
void print_cur_state() {
    print_state("current state", drive->getState());
}

void motors_init() {
    printf("RF: %lf, ", rightFront.getPosition());
    printf("RM: %lf, ", rightMiddle.getPosition());
    printf("RB: %lf\n", rightBack.getPosition());

    printf("............................\n");

    printf("LF: %lf, ", leftFront.getPosition());
    printf("LM: %lf, ", leftMiddle.getPosition());
    printf("LB: %lf\n", leftBack.getPosition());

    printf("\n");
}

void odom_set_zero() {
    okapi::OdomState zero_state = {
            .x = 0_ft,
            .y = 0_ft,
            .theta = 0_deg
    };
    drive->setState(zero_state);
} 


extern okapi::IMU inertial;

bool toggled = false;

extern okapi::Controller controller;
void updateDrive() {
    pros::lcd::set_text(1, std::to_string(drive->getState().y.convert(okapi::foot))); 
    pros::lcd::set_text(2, std::to_string(drive->getState().x.convert(okapi::foot)));
    
    pros::lcd::set_text(3, std::to_string(inertial.controllerGet()));

    drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY), 
            controller.getAnalog((ControllerAnalog::rightX)));

#if 0
    //test-----------------------------------------------------
    if (controller.getDigital(okapi::ControllerDigital::A)) {
            //controller.setText(0, 0, "button A pressed");
            controller.rumble(".");
    } else {
            //controller.clearLine(0);
    }
    //---------------------------------------------------------

    if (controller.getDigital(okapi::ControllerDigital::up) == 1) {
        turnToAngle(20);
        toggled = true;
    }
#endif

    if (controller.getDigital(BUTTON_HOLD) == 1) {
        leftDrive.setBrakeMode(AbstractMotor::brakeMode::hold); 
        rightDrive.setBrakeMode(AbstractMotor::brakeMode::hold);

    } else if (controller.getDigital(BUTTON_COAST) == 1) {
        leftDrive.setBrakeMode(AbstractMotor::brakeMode::coast); 
        rightDrive.setBrakeMode(AbstractMotor::brakeMode::coast);
    }
}
