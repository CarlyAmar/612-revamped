#ifndef drivetrain
#define drivetrain

#include <Talon.h>
#include <RobotDrive.h>
#include <Relay.h>
#include <DigitalInput.h>
#include <DoubleSolenoid.h>

enum gear
{
    HIGH,
    LOW
};

class Drivetrain : public RobotDrive
{
public:
    Drivetrain();
    void drive();
    void pressurize();
    void shiftHigh();
    void shiftLow();
    
    Relay* compressor;
    DigitalInput* air;
    
    DoubleSolenoid* shifter;
    
    gear currentGear;
};
#endif
