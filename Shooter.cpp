#include "Shooter.h"
#include <cmath>

Shooter::Shooter()
{
    grabber = new Talon(1,5);
    tilt = new CANJaguar(1);
    wormdrive = new CANJaguar(2);
    accel = new ADXL345_I2C(1);
    clutch = new DoubleSolenoid(1,3,4);
    clamp = new DoubleSolenoid(1,5,6);
}
void Shooter::toggleClamp()
{
    //TODO
}
void Shooter::grab(double power)
{
    grabber -> Set(power);
}
void Shooter::engageClutch()
{
    //toggle clutch
}
void Shooter::disengageClutch()
{
    
}
void Shooter::energize(float speed)
{
    if (speed > 0.1 || speed < -0.1)
    {
        wormdrive->Set(1.0);
    }
    else
    {
        wormdrive->Set(0.0);
    }
}
void Shooter::fire()
{
    disengageClutch();
}
void Shooter::move(float angle, float speed)
{
    double xAxis = accel->GetAcceleration(ADXL345_I2C::kAxis_X);
    double yAxis = accel->GetAcceleration(ADXL345_I2C::kAxis_Y);
    double zAxis = accel->GetAcceleration(ADXL345_I2C::kAxis_Z);
    
    double pitch = atan(yAxis/(sqrt((xAxis*xAxis) + (zAxis*zAxis))))*(180/3.141592654);
    //TODO make this better with tolorances
    if (pitch < angle)
    {
        tilt->Set(speed);
    }
    else if (pitch > angle)
    {
        tilt->Set(-speed);
    }
    else
    {
        tilt->Set(0.0);
    }
}
void Shooter::move(float speed)
{
    if (speed > 0.1)
    {
        tilt->Set(speed);
    }
    else if (speed < -0.1)
    {
        tilt ->Set(speed);
    }
    else
    {
        tilt->Set(0.0);
    }
}
