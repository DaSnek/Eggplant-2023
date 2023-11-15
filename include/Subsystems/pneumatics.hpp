#ifndef __PNEUMATICS_HPP__
#define __PNEUMATICS_HPP__

#include "main.h"

class pneumaticSys {
    int last_input;
    int piston_state;

    pros::ADIDigitalOut piston;
    okapi::ControllerDigital button;

public:
    pneumaticSys(char, okapi::ControllerDigital);

    int get_state() const;
    void set_state(int);

    void driver_update();

    ~pneumaticSys();
};

#endif
