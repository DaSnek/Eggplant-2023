#ifndef __PORTS_HPP__
#define __PORTS_HPP__

//----------drive----------
#define RIGHT_FRONT     18
#define RIGHT_MIDDLE    19
#define RIGHT_BACK      11 

#define LEFT_FRONT      16 
#define LEFT_MIDDLE     17
#define LEFT_BACK       12 
//-------------------------

//----------intake----------
#define INTAKE_PORT     10
//--------------------------

//----------catapult----------
#define SLAPPER_PORT    21 
//--------------------------

//---------sensors----------
#define IMU_PORT        7 
//--------------------------

//---------pneumatics----------
#define WINGS_ADI       'A'
#define BLOCKER_ADI     'H'
//-----------------------------

//----------------------buttons-------------------------------
#define BUTTON_INTAKE           okapi::ControllerDigital::R1
#define BUTTON_OUTTAKE          okapi::ControllerDigital::R2

#define AUTON_M_ACTUATE         okapi::ControllerDigital::L2
#define WINGS_ACTUATE           okapi::ControllerDigital::L1
#define BLOCKER_ACTUATE         okapi::ControllerDigital::B

#define BUTTON_SLAPPER          okapi::ControllerDigital::L2

#define BUTTON_HOLD             okapi::ControllerDigital::X
#define BUTTON_COAST            okapi::ControllerDigital::Y
//-----------------------------------------------------------

#endif
