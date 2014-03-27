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
    leftEncoder = new Encoder(1,5,1,6); 
    leftEncoder->SetDistancePerPulse(1.0);//TODO GET THIS SHIT DONE
    firstDrive = true;
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
    
    if (air->Get() == 0)
    {
        compressor->Set(Relay::kOn);
    }
    else
    {
        compressor->Set(Relay::kOff);
    }
}
void Drivetrain::initAutoDrive()
{
    leftEncoder->Reset();
    leftEncoder->Start();
}
bool Drivetrain::originalAutoDrive(double inches)//84 inches
{
    if (firstDrive)
    {
                leftEncoder->Start();
                firstDrive = false;
    }
    if (((double)leftEncoder->Get()*-1.0) >= inches)
    {
        /*
            *       if (((double)leftEncoder->Get()*-1.0) >= inches)
            *           std::printf("done driving\n");
        *       if (((double)leftEncoder->Get()*-1.0) < 10.0)
        *           std::printf("Went Backwards\n");
        */
        TankDrive(0.0,0.0);
        return true;
    }
    else
    {
        TankDrive(-0.5,-0.5);
        return false;
    }
}
bool Drivetrain::autoDrive(double inches)//84 inches
{
    if (((double)leftEncoder->Get()*-1.0) >= inches)
    {
        /*
        if (((double)leftEncoder->Get()*-1.0) >= inches)
            std::printf("done driving\n");
        if (((double)leftEncoder->Get()*-1.0) < 10.0)
            std::printf("Went Backwards\n");
        */
        TankDrive(0.0,0.0);
        return true;
    }
    else
    {
        TankDrive(-0.5,-0.5);
        return false;
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
