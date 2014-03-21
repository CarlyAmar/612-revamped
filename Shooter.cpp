#include "Shooter.h"
#include <cmath>

const float Shooter::POWER = 0.6;

Shooter::Shooter()
{
    grabber = new Talon(1,5);
    tilt = new CANJaguar(1);
    wormdrive = new CANJaguar(2);
    accel = new ADXL345_I2C(1);
    clutch = new DoubleSolenoid(1,3,4);
    clamp = new DoubleSolenoid(1,5,6);
    infared = new AnalogChannel(1,5);
//     position = CLAMP_UP;
    accel = new ADXL345_I2C(1);
    firstCall = true;
}
void Shooter::toggleClamp()
{
    /*
    if (position == UP)
        clampDown();
    else if (position == DOWN)
        clampUp();
    
    */
}
void Shooter::clampUp()
{
    clamp->Set(DoubleSolenoid::kReverse);
    position = CLAMP_UP;
}
void Shooter::clampDown()
{
    clamp->Set(DoubleSolenoid::kForward);
    position = CLAMP_DOWN;
}
void Shooter::grab()
{
    grabber -> Set(-1.0);
}
void Shooter::repel()
{
    grabber->Set(1.0);
}
void Shooter::stopRollers()
{
    grabber->Set(0.0);
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
    if (speed > 0.1)
    {
        wormdrive->Set(1.0);
    }
    else if (speed < -0.1)
    {
        wormdrive->Set(-1.0);
    }
    else
    {
        wormdrive->Set(0.0);
    }
}
void Shooter::fire()
{
    clutch->Set(DoubleSolenoid::kReverse);
    wormdrive->Set(0.0);
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
        tilt->Set(-POWER);
    }
    else if (speed < -0.1)
    {
        tilt ->Set(POWER);
    }
    else
    {
        tilt->Set(0.0);
    }
}
void Shooter::energize()
{
    clutch->Set(DoubleSolenoid::kForward);
    wormdrive->Set(1.0);
}
void Shooter::autoTilt(float angle)
{
    if (firstCall)
    {
        if (getPitch() < angle)
        {
            dir = UP;
            std::printf("Pitch is less than angle\n");
        }
        else if (getPitch() > angle)
        {
            dir = DOWN;
            std::printf("Pitch is greater than Angle\n");
        }
    }
//     static int count = 0;
    if (dir == UP)
    {
        if (getPitch() < angle)
        {
            tilt->Set(0.5);
//             if (count % 10 == 0)
//                 std::printf("Less than angle, moving positive\n"
        }
        else 
        {
            tilt->Set(0.0);
//             if (count % 10 == 0)
//                 std::printf("Done moving positive!\n");
        }
//         count++;
    }
    else if (dir == DOWN)
    {
        if (getPitch() > angle)
        {
            tilt->Set(-0.5);
//             if (count % 10 == 0)
//                 std::printf("Greater than angle, moving negative\n");
        }
        else
        {
            tilt->Set(0.0);
//             if (count % 10 == 0)
//                 std::printf("Done moving negative!\n");
        }
//         count++;
    }
}
double Shooter::getPitch()
{
    double xAxis = accel->GetAcceleration(ADXL345_I2C::kAxis_X);
    double yAxis = accel->GetAcceleration(ADXL345_I2C::kAxis_Y);
    double zAxis = accel->GetAcceleration(ADXL345_I2C::kAxis_Z);
    
    //double roll = atan(-yAxis/zAxis)*(180/3.141592654);
    double pitch = atan(xAxis/(sqrt((yAxis*yAxis) + (zAxis*zAxis))))*(180/3.141592654);
    return pitch;
}
