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
    shoot = new Shooter();
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
    driveT -> pressurize();
    driveT -> drive();
    if (driverJoy->Joystick::GetRawButton(5))
    {
        driveT->shifter->Set(DoubleSolenoid::kReverse);
    }
    else if (driverJoy->Joystick::GetRawButton(6))
    {
        driveT->shifter->Set(DoubleSolenoid::kForward);
    }
    else
    {
        driveT->shifter->Set(DoubleSolenoid::kOff);
    }
    //gunner
    shoot->move(gunnerJoy->GetRawAxis(2)); //move tilt based on left stick
    shoot->energize(gunnerJoy->GetRawAxis(5)); //move launcher on right stick
    if (gunnerJoy->Joystick::GetRawButton(1))//press X to grab
    {
        shoot->grab(1.0);
    }
    else if (gunnerJoy->Joystick::GetRawButton(3))
    {
        shoot->repel(1.0);
    }
    else if (gunnerJoy->Joystick::GetRawButton(1))
    {
        shoot->grab(-1.0);
    }
    else
    {
        shoot->grab(0.0);
    }
    if (gunnerJoy->Joystick::GetRawButton(2))
    {
        shoot->clamp->Set(DoubleSolenoid::kForward);
    }
    else if (gunnerJoy->Joystick::GetRawButton(4))
    {
        shoot->clamp->Set(DoubleSolenoid::kReverse);
    }
    else
    {
        shoot->clamp->Set(DoubleSolenoid::kOff);
    }
    if (gunnerJoy->Joystick::GetRawButton(6))
    {
        shoot->clutch->Set(DoubleSolenoid::kReverse);
    }
    else
    {
        shoot->clutch->Set(DoubleSolenoid::kForward);
    }
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
