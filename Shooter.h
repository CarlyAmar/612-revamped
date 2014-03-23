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
    CLAMP_UP,
    CLAMP_DOWN
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
    void disable();
    void fire();
    void move(float angle, float speed);
    void move(float speed);
    void clampUp();
    void clampDown();
    void initAutoTilt(float);
    bool autoTilt();
    double getPitch();
    float angle;
    static const float POWER;
    bool done;
    bool ACworking;

    clampPos position;
    direction dir;
    
    DoubleSolenoid* clamp;
    DoubleSolenoid* clutch;
    
    AnalogChannel* infared;
    ADXL345_I2C* accel;
    
    Talon* grabber;
    CANJaguar* tilt;
    CANJaguar* wormdrive;
};

#endif
