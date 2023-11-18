#ifndef __AUTONFUNCS_HPP__
#define __AUTONFUNCS_HPP__

using namespace okapi::literals;

#include "drive.hpp"

//-----------------------------------
//remap to -180 to 180
inline double remap(double d) {
    if (d == 0) {
        return 0;
    }

    double fp = d - (int)d;
    int id = (int)d;

    if (d > 0) {
        id = id % 360;
    } else {
        id = (-id % 360) * -1 + 360;
    }

    d = id + fp;
    return (d <= 180) ? d : (d - 360);
}

//------------------------------------

double to_IMU_heading(double heading);

void drive_dis(double, double scalar=1, bool stop=true);
void turnToAngle(double, double scalar=0.88, bool reversed=false);
void driveToPoint(double, double, double speed=0.8, bool backward=false);

void j_curve(double, double, bool reversed=false, double turn_scalar=1);
void drive_arc(double, double, double scalar=0.8, bool reversed=false);

#endif
