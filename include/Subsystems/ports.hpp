#ifndef __PORTS_HPP__
#define __PORTS_HPP__

//----------drive----------
#define RIGHT_FRONT     19
#define RIGHT_MIDDLE    11
#define RIGHT_BACK      12 

#define LEFT_FRONT      10 
#define LEFT_MIDDLE     2
#define LEFT_BACK       1 
//-------------------------

//--------flywheel--------
#define FW_PORT_1       18
#define FW_PORT_2       8
//------------------------

//---------sensors---------
#define IMU_PORT        13 
//-------------------------

//-------pneumatics--------
#define WINGS_ADI       'A'
#define T_BAR_ADI       'C'
#define PTO_ADI         'B'

#define EXPANDER_PORT   -1
//-------------------------

//---------------------------buttons-------------------------------
#define BUTTON_FW_FORWARD           okapi::ControllerDigital::R2
#define BUTTON_FW_BACKWARD          okapi::ControllerDigital::R1

#define WINGS_ACTUATE_O             okapi::ControllerDigital::B
#define WINGS_ACTUATE_I             okapi::ControllerDigital::down
#define T_BAR_ACTUATE_U             okapi::ControllerDigital::L1
#define T_BAR_ACTUATE_D             okapi::ControllerDigital::L2

#define PTO_ACTUATE                 okapi::ControllerDigital::right

#define BUTTON_INTAKE               okapi::ControllerDigital::Y
//-----------------------------------------------------------------

#endif
