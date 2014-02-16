#include <Joystick.h>

#include "main.h"
#include "612.h"
#include "SmoothJoystick.h"
#include "Drivetrain.h"

robot_class* robot=NULL;

robot_class::robot_class()
{
}

void robot_class::RobotInit()
{
    robot = this;
    driverJoy = new SmoothJoystick(1);
    gunnerJoy = new SmoothJoystick(2);
    
    driveT = new Drivetrain();
}

void robot_class::DisabledInit()
{
}

void robot_class::DisabledPeriodic()
{
}

void robot_class::AutonomousInit()
{

}

void robot_class::AutonomousPeriodic()
{

}

void robot_class::TeleopInit()
{

}

void robot_class::TeleopPeriodic()
{
    updateRegistry.update();
    driveT -> drive();
    //commented out to avoid compiler warning barf
}

void robot_class::TestInit()
{
    
}

void robot_class::TestPeriodic()
{

}

//vision
void robot_class::init_vision() 
{

}

void robot_class::stop_vision() 
{

}

START_ROBOT_CLASS(robot_class)
