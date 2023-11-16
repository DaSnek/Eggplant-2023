#ifndef __PORTS_HPP__
#define __PORTS_HPP__

//----------drive----------
#define RIGHT_FRONT     -1
#define RIGHT_MIDDLE    -1
#define RIGHT_BACK      -1 

#define LEFT_FRONT      -1 
#define LEFT_MIDDLE     -1
#define LEFT_BACK       -1 
//-------------------------

//----------flywheel----------
#define FW_PORT_1       -1
#define FW_PORT_2       -1
//----------------------------

//---------sensors----------
#define IMU_PORT        -1 
//--------------------------

//---------pneumatics----------
#define WINGS_ADI       ' '
#define T_BAR_ADI       ' '
#define PTO_ADI         ' '
//-----------------------------

//-------------------------buttons-------------------------------
#define BUTTON_FW_FORWARD           okapi::ControllerDigital::R1
#define BUTTON_FW_BACKWARD          okapi::ControllerDigital::R2

#define WINGS_ACTUATE               okapi::ControllerDigital::L1
#define T_BAR_ACTUATE               okapi::ControllerDigital::B
#define PTO_ACTUATE                 okapi::ControllerDigital::B

#define BUTTON_HOLD                 okapi::ControllerDigital::X
#define BUTTON_COAST                okapi::ControllerDigital::Y
//---------------------------------------------------------------

#endif
