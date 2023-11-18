#include "main.h"
#include "drive.hpp"
#include "autonfunctions.hpp"

#include <assert.h>

#define TO_DEG  (180 / 3.14159265359)

//----------------------------functions---------------------------------------
static double normalize(double d) {      //input[0,360] -> output[-180,180]
    if (d > 180)
        d -= 360;
    return d;
}

static double angle_diff(double d1, double d2) {        //[0, 180)
    double pd = std::max(d1, d2) - std::min(d1, d2);
    return (pd > 180) ? (360 - pd) : pd;
}

static double angle_diff_dir(double d1, double d2) {        //[-180, 180)
    double pd = d2 - d1;
    return (pd > 180) ? (360 - pd) : pd;
}
//--------------------------------------

double to_IMU_heading(double d) {
    return normalize(90 - d);
}

void drive_dis(double distance, double scalar, bool stop) {         
    if (abs(distance) <= 0.01)
        return;
    okapi::IterativePosPIDController drivePID = okapi::IterativeControllerFactory::posPID(0.848, 0.00, 0.0000);

    double target = distance;

    drivePID.setTarget(target);

    double orgPosX = drive->getState().x.convert(okapi::foot);
    double orgPosY = drive->getState().y.convert(okapi::foot);

    printf("\n-->  start    => %10.3lf    : state = (%9.5lf, %9.5lf, %9.8lf)\n", 
            distance, orgPosX, orgPosY, inertial.controllerGet());

    double distTravelled = 0;
                                                       
    while (abs(target-distTravelled) >= (stop ? 0.16 : 0.53) || abs(leftDrive.getActualVelocity()) > (stop ? 8 : 512)) { 
    //while (true) {                  //tuning
        double state_x = drive->getState().x.convert(okapi::foot);
        double state_y = drive->getState().y.convert(okapi::foot);

        double dx = state_x - orgPosX;
        double dy = state_y - orgPosY;

        //printf("IMU: %lf\n", inertial.controllerGet());

        distTravelled = sqrt(dx * dx + dy * dy);

        if (distance < 0)
            distTravelled = -distTravelled;
        printf("     %10.3lf  => %10.3lf    : state = (%10.3lf, %10.3lf)\n", distTravelled, distance, state_x, state_y);

        double vel = drivePID.step(distTravelled);

        //printf("distTravelled: %lf, cur_x: %lf, cur_y:%lf\n",
        //   distTravelled, drive->getState().y.convert(okapi::foot), drive->getState().x.convert(okapi::foot));

        drive->getModel()->tank(vel * scalar, vel * scalar);
        pros::delay(16);   
    }

    drivePID.reset(); 
    
    if (stop) 
        drive->getModel()->tank(0, 0); 

    double state_x = drive->getState().x.convert(okapi::foot);
    double state_y = drive->getState().y.convert(okapi::foot);
    printf("-->   end      : state = (%10.3lf, %10.3lf)\n", state_x, state_y);
}

void turnToAngle(double targetAngle, double scalar, bool reversed) {
    okapi::IterativePosPIDController rotatePID = 
                okapi::IterativeControllerFactory::posPID((double)0.024816, 0.000000, 0.000326); 

    rotatePID.setTarget(0);

    double initAngle = remap(inertial.controllerGet() - targetAngle);

    while (abs(0 - initAngle) >= 3 || abs(leftDrive.getActualVelocity()) > 15) {
    //while (true) {   //tuning
        printf("<offset: %lf\n", initAngle) ; 
        initAngle = remap(inertial.controllerGet() - targetAngle);

        if (initAngle >= 190) {
            printf("uhhhhh this went bad\n");
            break;
        }

        double vel = rotatePID.step(initAngle);
        drive->getModel()->tank(vel * scalar * (reversed ? -1 : 1), -vel * scalar * (reversed ? -1 : 1));

        pros::delay(20);
    }

    rotatePID.reset();
    drive->getModel()->tank(0, 0);

    printf("IMU: %lf\n", inertial.controllerGet());
}

void driveToPoint(double posX, double posY, double speed, bool backward) {
    double ogXPos = drive->getState().y.convert(okapi::foot); 
    double ogYPos = drive->getState().x.convert(okapi::foot);

    double distance = sqrt(pow((posX - ogXPos), 2) + pow((posY - ogYPos), 2));

    double targetAngle = 0;

    //----------------n_algo-----------
    double dx = posX - ogXPos;
    double dy = posY - ogYPos;

    printf("distance: %lf, dX: %lf, dY: %lf\n", distance, dx, dy);

    if (!dx && !dy) {
        return;
    }

    if (dx == 0) {
        targetAngle = (dy > 0) ? 90 : -90;
    } else if (dx > 0) {
        targetAngle = atan(dy/dx) * TO_DEG;
    } else if (dx < 0) {
        targetAngle = 180 + (atan(dy/dx)) * TO_DEG;
    }

    //normalizing + IMU convert
    targetAngle = to_IMU_heading(normalize(targetAngle));

    if (backward) {                    //If driving intake backward 
        if (targetAngle >= 0) {
            targetAngle += -180;
        } else if (targetAngle < 0) {
            targetAngle += 180;
        }
    }

    turnToAngle(targetAngle, speed);
    drive_dis((backward ? -1 : 1) * distance, speed);
}

static double cal_t_angle(double tx, double ty) {
    double dx = tx - drive->getState().x.convert(okapi::foot);
    double dy = ty - drive->getState().y.convert(okapi::foot);

    if (!dx && !dy) {
        return 0;
    }

    double target_angle = 0;

    if (dx == 0) {
        target_angle = (dy > 0) ? 90 : -90;
    } else if (dx > 0) {
        target_angle = atan(dy/dx) * TO_DEG;
    } else if (dx < 0) {
        target_angle = 180 + (atan(dy/dx)) * TO_DEG;
    }

    target_angle = to_IMU_heading(normalize(target_angle));

    return target_angle;
}


//note: reverse all coordinate pairs
void j_curve(double tx, double ty, bool reversed, double turn_scalar) {
    okapi::IterativePosPIDController forwardPID = okapi::IterativeControllerFactory::posPID(0.848, 0.00, 0.0000);
    okapi::IterativePosPIDController turnPID = 
                okapi::IterativeControllerFactory::posPID((double)1/32.0, 0.000000, 0.0005856);

    double ix = drive->getState().y.convert(okapi::foot);
    double iy = drive->getState().x.convert(okapi::foot);

    printf("-------------ix: %lf, iy: %lf---------------\n", ix, iy);

    double dx = tx - ix;
    double dy = ty - iy;

    double d_dis = sqrt(dx * dx + dy * dy);
    forwardPID.setTarget(d_dis);

    int ta_reached = 0;
    double dvn_dis = 0;

    int msg_counter = 0;

    while (abs(d_dis - dvn_dis) >= 0.5 || std::max(abs(leftDrive.getActualVelocity()), abs(rightDrive.getActualVelocity())) > 10) {
    //while (true) { 
        double cx = drive->getState().y.convert(okapi::foot);
        double cy = drive->getState().x.convert(okapi::foot);

        double dvn_x = cx - ix;
        double dvn_y = cy - iy;

        dvn_dis = sqrt(dvn_x * dvn_x + dvn_y * dvn_y);

        double fs = forwardPID.step(dvn_dis);

        double ta = cal_t_angle(tx, ty);
        double ca = remap(inertial.controllerGet() + ((reversed) ? 180 : 0));
        double ts;

        turnPID.setTarget(ta);     //recalc
        ts = turnPID.step(ca) * turn_scalar;

        if (!msg_counter % 5) {
            printf("drvn_d: %lf, ta: %lf, ca: %lf, ta_r: %d, F_S: %lf, T_S: %lf, ca_diff: %lf\n"
                    , dvn_dis, ta, ca, ta_reached, fs, ts, angle_diff(ta, ca));
        }
        msg_counter++;
        msg_counter = msg_counter % 5;
        
        double left_spd = (fs + ts) * 0.5 * ((reversed) ? -1 : 1);
        double right_spd = (fs - ts) * 0.5 * ((reversed) ? -1 : 1); 
        
        printf("ls: %lf, rs: %lf\n", left_spd, right_spd);

        drive->getModel()->tank(left_spd, right_spd);
        pros::delay(23);
   }

    turnPID.reset();
    forwardPID.reset();
    drive->getModel()->tank(0, 0);

    pros::delay(8);
}

//r > 0, theta -> (-180, 180), reversed drives backwards to same angle
void drive_arc(double r, double targetAngle, double scalar, bool reversed) {     //returns distance, arc to theta
    double sd = abs(r * 12) - (DRIVE_H_WIDTH);
    double ld = abs(r * 12) + (DRIVE_H_WIDTH);
    printf("smaller dis: %lf, larger dis: %lf\n", sd, ld);

    double initAngle = remap(inertial.controllerGet() - targetAngle);

    //determine left right          targetAngle : > 0
    double left_speed = ((initAngle < 0) ? 1 : (sd / ld)) * scalar;     //change: used init not target
    double right_speed = ((initAngle < 0) ? (sd / ld) : 1) * scalar;

    //determine if reverse
    if (reversed) {
        double ts = left_speed;

        left_speed = right_speed * -1;
        right_speed = ts * -1;
    }

    //speed constants adjustments should be done
    printf("left speed: %lf, right speed: %lf\n", left_speed, right_speed); 

//---------------------------------------------
    //if reversed=true to target(ex 0):
    //      flip l and R
    //      * -1 both speeds
    //else 
    //      do nothing?
//------------------------------------------------

    printf("current angle: %lf, target angle: %lf\n", inertial.controllerGet(), targetAngle);

    okapi::IterativePosPIDController rotatePID = 
                okapi::IterativeControllerFactory::posPID((double)0.024816, 0.000000, 0.000326); //28, 42
    rotatePID.setTarget(0);

    //double initAngle = remap(inertial.controllerGet() - targetAngle);     //moved up
    bool a_adj = initAngle > 0;     //compensation for negative PID output

    while (abs(initAngle) >= 4
            || std::max(abs(leftDrive.getActualVelocity()), abs(rightDrive.getActualVelocity())) > 16) {

        printf("<offset: %lf\n", initAngle) ;
        initAngle = remap(inertial.controllerGet() - targetAngle);

        if (initAngle >= 190) {
            printf("uhhhhh this went bad\n");
            break;
        }

        double vel = rotatePID.step(initAngle);
        drive->getModel()->tank(left_speed * vel * (a_adj ? -1 : 1), right_speed * vel * (a_adj ? -1 : 1));

        pros::delay(20);
    }

    rotatePID.reset();
    drive->getModel()->tank(0, 0);

    angle_diff_dir(0, 0);

    printf("IMU: %lf\n", inertial.controllerGet());
}

