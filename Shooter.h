#ifndef shooter
#define shooter

#include <CANJaguar.h>
#include <DoubleSolenoid.h>
#include <Talon.h>
#include <ADXL345_I2C.h>
#include <AnalogChannel.h>

class Shooter
{
enum clampPos{
    UP,
    DOWN
};
enum direction{
    UP,
    DOWN
};
public:
    Shooter();
    void toggleClamp();
    void grab();
    void repel();
    void stopRollers();
    void engageClutch();
    void disengageClutch();
    void energize(float speed);
    void energize();
    void fire();
    void move(float angle, float speed);
    void move(float speed);
    void clampUp();
    void clampDown();
    void autoTilt();
    
    static const float POWER = 0.6;
    bool firstCall;

    clampPos position;
    direction dir;
    
    DoubleSolenoid* clamp;
    DoubleSolenoid* clutch;
    
    AnalogChannel* infared;
    ADXL345_I2C* accel;
    
    Talon* grabber;
    CANJaguar* tilt;
    CANJaguar* wormdrive;
    ADXL345_I2C* accel;
};

#endif
