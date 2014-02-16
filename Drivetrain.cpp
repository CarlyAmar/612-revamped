#include "Drivetrain.h"
#include "612.h"
#include "SmoothJoystick.h"

Drivetrain::Drivetrain() : RobotDrive(new Talon(1,4),new Talon(1,3),new Talon(1,1),new Talon(1,2))
{
    SetInvertedMotor(kFrontLeftMotor , true);
    SetInvertedMotor(kFrontRightMotor , true);
    SetInvertedMotor(kRearLeftMotor , true);
    SetInvertedMotor(kRearRightMotor , true);
    SetSafetyEnabled(false);
    
    compressor = new Relay(1,8);
    air = new DigitalInput(1,8);
    shifter = new DoubleSolenoid(1,7,8);
}

void Drivetrain::drive()
{
    if ((robot->driverJoy->GetRawAxis(2) > 0.1 || robot->driverJoy->GetRawAxis(2) < -0.1) || (robot->driverJoy->GetRawAxis(5) > 0.1 || robot->driverJoy->GetRawAxis(5) < -0.1))
    {
        TankDrive(robot->driverJoy->GetRawAxis(2), robot->driverJoy->GetRawAxis(5));
    }
    else
    {
        TankDrive(0.0,0.0);
    }
}
void Drivetrain::pressurize()
{
    
    if (air->Get() == 1)
    {
        compressor->Set(Relay::kOn);
    }
    else
    {
        compressor->Set(Relay::kOff);
    }
}
/*
void Drivetrain::shiftHigh()
{
    robot->pnum->solenoidForward(shifter);
}
void Drivetrain::shiftLow()
{
    robot->pnum->solenoidReverse(shifter);
}
*/
