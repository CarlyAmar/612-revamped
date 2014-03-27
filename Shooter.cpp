#include "Shooter.h"
#include <cmath>

const float Shooter::POWER = 0.6;

Shooter::Shooter()
{
    grabber = new Talon(1,5);
    tilt = new CANJaguar(1);
    wormdrive = new CANJaguar(2);
    clutch = new DoubleSolenoid(1,3,4);
    clamp = new DoubleSolenoid(1,5,6);
    infared = new AnalogChannel(1,5);
//     position = CLAMP_UP;
    accel = new ADXL345_I2C_612(1);
    angle = getPitch();
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
//NOT USED
void Shooter::move(float angle, float speed=0.6)
{
    double pitch;
    {
        double xAxis = accel->GetAcceleration(ADXL345_I2C_612::kAxis_X);
        double yAxis = accel->GetAcceleration(ADXL345_I2C_612::kAxis_Y);
        double zAxis = accel->GetAcceleration(ADXL345_I2C_612::kAxis_Z);
        pitch = atan(yAxis/(sqrt((xAxis*xAxis) + (zAxis*zAxis))))*(180/3.141592654);
    }
    
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
void Shooter::disable()
{
    wormdrive->Set(0.0);
}
void Shooter::initAutoTilt(float a)
{
    angle = a;
    done = false;
    double pitch = getPitch();
    if (pitch < angle)
    {
        dir = UP;
        std::printf("Pitch is less than angle\n");
    }
    else if (pitch > angle)
    {
        dir = DOWN;
        std::printf("Pitch is greater than Angle\n");
    }
}
bool Shooter::autoTilt()
{
//     static int count = 0;
    if (!done)
    {
        if (dir == UP)
        {
            if (getPitch() < angle)
            {
                tilt->Set(-0.5);
    //             if (count % 10 == 0)
    //                 std::printf("Less than angle, moving positive\n"
            }
            else 
            {
                tilt->Set(0.0);
    //             if (count % 10 == 0)
    //                 std::printf("Done moving positive!\n");
                done = true;
            }
    //         count++;
        }
        else if (dir == DOWN)
        {
            if (getPitch() > angle)
            {
                tilt->Set(0.5);
    //             if (count % 10 == 0)
    //                 std::printf("Greater than angle, moving negative\n");
            }
            else
            {
                tilt->Set(0.0);
    //             if (count % 10 == 0)
    //                 std::printf("Done moving negative!\n");
                done = true;
            }
    //         count++;
        }
    }
    return done;
}
double Shooter::getPitch()
{
    double xAxis = accel->GetAcceleration(ADXL345_I2C_612::kAxis_X);
    double yAxis = accel->GetAcceleration(ADXL345_I2C_612::kAxis_Y);
    double zAxis = accel->GetAcceleration(ADXL345_I2C_612::kAxis_Z);
    
    double pitch = atan(xAxis/(sqrt((yAxis*yAxis) + (zAxis*zAxis))))*(180/3.141592654);
    
    if (xAxis == 0.0 && yAxis == 0.0 && zAxis == 0.0)
    {
        ACworking = false;
        done = true;
    }
    else
    {
        ACworking = true;
    }
    return pitch;
}
