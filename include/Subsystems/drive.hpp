#ifndef __DRIVE_HPP__
#define __DRIVE_HPP__

#define WHEEL_SIZE      3.25_in
#define DRIVE_WIDTH     11_in
#define GEAR_RATIO      ((double)5. / 3.)

#define DRIVE_H_WIDTH     5.5

extern okapi::MotorGroup leftDrive;
extern okapi::MotorGroup rightDrive;
extern okapi::MotorGroup Drive;

extern std::shared_ptr<okapi::OdomChassisController> drive;

//-------------------------------------------------

void print_state(std::string, const okapi::OdomState&);
void print_cur_state();
void motors_init();
void odom_set_zero();

void updateDrive();

#endif
