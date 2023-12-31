#include "main.h"
#include "globals.hpp"

okapi::Controller controller;

pneumaticSys wings(WINGS_ADI, WINGS_ACTUATE_O, WINGS_ACTUATE_I);
pneumaticSys t_bar(T_BAR_ADI, T_BAR_ACTUATE_U, T_BAR_ACTUATE_D);
