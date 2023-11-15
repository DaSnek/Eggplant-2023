#include "pneumatics.hpp"

pneumaticSys::pneumaticSys(char port, okapi::ControllerDigital _button)
        : last_input(0), piston_state(0), piston(port), button(_button) {}

int pneumaticSys::get_state() const {
    return piston_state;
}

void pneumaticSys::set_state(int state) {
    piston.set_value(state);
    piston_state = state;
}

void pneumaticSys::driver_update() {
    int input = controller.getDigital(button);

    if (input && !last_input) {
        if (!piston_state) {
            piston.set_value(1);
            piston_state = 1;
        } else {
            piston.set_value(0);
            piston_state = 0;
        }
    }

    last_input = input;
}

pneumaticSys::~pneumaticSys() = default;
