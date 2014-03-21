#include <Joystick.h>

#include "main.h"
#include "612.h"
#include "SmoothJoystick.h"
#include "Drivetrain.h"
#include "Controls.h"

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
    shoot->clampDown();
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
    //double infaredDistance = (double)((robot->shoot->infared->GetVoltage()))/**18.777777777777777)*/;
    updateRegistry.update();
    driveT -> pressurize();
    driveT -> drive();
    doControls();
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
void robot_class::doControls()
{
    //SHIFTING
    if (driverJoy->Joystick::GetRawButton(BUTTON_L1))//L1
        driveT->shifter->Set(DoubleSolenoid::kForward);
    else if (driverJoy->Joystick::GetRawButton(BUTTON_R1))//R1
        driveT->shifter->Set(DoubleSolenoid::kReverse);
    else
        driveT->shifter->Set(DoubleSolenoid::kOff);
    
    /*
     * clamp A                      DONE
     * energize b
     * fire X
     * tilt left stick (inverted)
     * rollers right (up == in)
     */
    
    /* ROLLERS */
    if (gunnerJoy->GetRawAxis(RIGHT_JOYSTICK_Y) > 0.1) // Grabbing with right stick
        shoot->repel();
    else if (gunnerJoy->GetRawAxis(RIGHT_JOYSTICK_Y) < -0.1)
        shoot->grab();
    else
        shoot->stopRollers();
    
    shoot->move(gunnerJoy->GetRawAxis(LEFT_JOYSTICK_Y)); //Tilting
    
    /* CLAMP */
    if (gunnerJoy->Joystick::GetRawButton(BUTTON_Y))//Adjust clamp with Y and B
        shoot->clampUp();
    else if (gunnerJoy->Joystick::GetRawButton(BUTTON_A))//B
        shoot->clampDown();
    else
        shoot->clamp->Set(DoubleSolenoid::kOff);
    
    /* ENERGIZING */
    if (gunnerJoy->Joystick::GetRawButton(BUTTON_B))//R1 //Down is kForward
        shoot->energize();
    
    //worm drive positive FULL
    
    /* FIRING */
    if (gunnerJoy->GetRawButton(BUTTON_X))
        shoot->fire();
    
    /* PRESETS */
    if (gunnerJoy->GetRawButton(BUTTON_L1)
        shoot->autoTilt(30.0); //TODO get real presets
    //TODO repeat here
}

START_ROBOT_CLASS(robot_class)
