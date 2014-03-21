#ifndef drivetrain
#define drivetrain

#include <Talon.h>
#include <RobotDrive.h>
#include <Relay.h>
#include <DigitalInput.h>
#include <DoubleSolenoid.h>
#include <Encoder.h>

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
    bool autoDrive(double inches);
    Relay* compressor;
    DigitalInput* air;
    Encoder* leftEncoder;
    DoubleSolenoid* shifter;
    bool firstDrive;
    gear currentGear;
};
#endif
