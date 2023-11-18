#include "pneumatics.hpp"

pneumaticSys::pneumaticSys(char port, okapi::ControllerDigital _button_out, okapi::ControllerDigital _button_in)
        : last_input(0), piston_state(0), piston(port), button_out(_button_out), button_in(_button_in) {} 

pneumaticSys::pneumaticSys(int exp_port, char adi_port, okapi::ControllerDigital _button_out, okapi::ControllerDigital _button_in)
        : last_input(0), piston_state(0), piston({{exp_port, adi_port}}), button_out(_button_out), button_in(_button_in) {} 

int pneumaticSys::get_state() const {
    return piston_state;
}

void pneumaticSys::set_state(int state) {
    piston.set_value(state);
    piston_state = state;
}

void pneumaticSys::driver_update() {
    int input_out = controller.getDigital(button_out);
    int input_in = controller.getDigital(button_in);

    if (input_out) {
        piston.set_value(1);
    } else if (input_in) {
        piston.set_value(0);
    }
}

pneumaticSys::~pneumaticSys() = default;
