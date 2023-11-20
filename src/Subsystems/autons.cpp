#include "autons.hpp"
#include "main.h"
#include "Subsystems/drive.hpp"

void auton_test();
void auton_awp();
void auton_awp_s();
void auton_triballs_2();
void skills();

void autons() {
    odom_set_zero();        //do not delete    

    auton_awp();
}


void auton_test() {
    drive_arc(0.8, 90, 0.90);
}

void auton_awp_s() {
    wings.set_state(1);
    drive_dis(0.42, 1);
    wings.set_state(0);
    drive_dis(-0.8, 1);
    turnToAngle(45, 0.8);
    drive_arc(0.5, 45, 0.8);
    turnToAngle(135, 0.8);
    drive_dis(2.8);
    wings.set_state(1);
}

void auton_triballs_2() {
    drive_dis(0.32, 0.88);
    drive_arc(0.77, -45, 0.8);
    //turnToAngle(-45, 0.8);
    wings.set_state(1);
    drive_arc(0.5, -100, 0.925);
    wings.set_state(0);
    turnToAngle(-88, 0.88);
    drive_dis(1.6, 1);

    drive_dis(-0.8, 0.8);   //temp end
}

void auton_awp() {
    drive_dis(1.28, 0.88);
    pros::delay(32);
    turnToAngle(45, 0.88);
    drive_dis(2.3, 1);
    turnToAngle(0, 0.88);
    wings.set_state(1);
    drive->getModel()->tank(0.935, 0.935);
    pros::delay(210);
    drive->getModel()->tank(0, 0);
    turnToAngle(-24, 0.95);
    pros::delay(160);
    turnToAngle(24, 0.95);
    pros::delay(160);
    turnToAngle(0, 0.90);
    wings.set_state(0);
    //drive_arc(0.5, 90, 0.64, true);
    
    turnToAngle(90, 0.88);
    t_bar.set_state(1);
    pros::delay(510);
    t_bar.set_state(0);
    pros::delay(640);
    drive_dis(-2, 1);
    flywheel.moveVoltage(0);
    drive_dis(2, 1);

    turnToAngle(36, 0.8);
    drive_dis(-3.14, 1);
    drive_arc(0.67, 135, 0.8, true);
    drive_dis(0.64, 0.88, false);
    wings.set_state(1);
    turnToAngle(95, 1);
    //drive_arc(0.64, 90, 0.93);
    wings.set_state(0);
    drive_dis(1.8, 1);
    turnToAngle(90, 0.80);
    drive_dis(1.5, 1);
    wings.set_state(1);
}











#if 0
void auton_awp() {
    drive_dis(1.28, 0.88);
    pros::delay(32);
    turnToAngle(45, 0.88);
    drive_dis(2.3, 1);
    turnToAngle(0, 0.88);
    wings.set_state(1);
    drive->getModel()->tank(0.88, 0.88);
    pros::delay(280);
    drive->getModel()->tank(0, 0);
    turnToAngle(-16, 0.93);
    pros::delay(160);
    turnToAngle(16, 0.93);
    pros::delay(160);
    turnToAngle(0, 0.88);
    wings.set_state(0);

    turnToAngle(36, 0.8);
    drive_dis(-3.56, 1);
    drive_arc(0.68, 135, 0.8, true);
    wings.set_state(1);
    drive_arc(0.53, 90, 0.93);
    wings.set_state(0);
    drive_dis(2.8, 0.8);
    t_bar.set_state(1);
}


void auton_awp() {
    drive_dis(4.10, 0.88);
    pros::delay(32);    //imu cal
    turnToAngle(91, 0.8);
    wings.set_state(1);
    
    //drive->getModel()->tank(0.95, 0.95);
    //pros::delay(374);
    //drive->getModel()->tank(0.19, 0.19);
    //pros::delay(880);
    //drive->getModel()->tank(0, 0);
    drive_dis(1.5, 1);
    drive_arc(0.5, 0, 0.8);

    drive_dis(-0.64, 0.72);
    wings.set_state(0);
    //go to matchload zone--->
    turnToAngle(45, 0.8);
    drive_dis(-4, 1);
    drive_arc(0.64, 135, 0.8, true);
    wings.set_state(1);
    drive_arc(0.53, 90, 0.93);
    wings.set_state(0);
    drive_dis(2.8, 0.8);
    t_bar.set_state(1);


        
}
#endif