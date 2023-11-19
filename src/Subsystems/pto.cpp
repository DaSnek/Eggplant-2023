#include "pto.hpp"

pros::ADIDigitalOut pto(PTO_ADI);

using namespace okapi::literals;

static okapi::Timer timer;

static bool toggled = false;
okapi::QTime start_time;

void update_pto() {     //add delay  two button
    int input = controller.getDigital(PTO_ACTUATE); 

    if (input) {
        if (!toggled) {
            toggled = true;
            return;
        }

        if (toggled && (timer.millis() - start_time) > 2000_ms) {
            pto.set_value(1);
            pros::lcd::set_text(5, "pto activated");
            controller.rumble(".");
            
            toggled = false;
            start_time = timer.millis();
            
        }
    } else {
        toggled = false;
        start_time = timer.millis();
    }   
}
