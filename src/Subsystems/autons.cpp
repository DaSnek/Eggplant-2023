#include "autons.hpp"
#include "main.h"

void auton_test();
void auton_awp();
void auton_triballs();
void skills();

void autons() {
    odom_set_zero();        //do not delete    

    auton_test();
}


void auton_test() {
    turnToAngle(90);
}
