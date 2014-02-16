#ifndef drivetrain
#define drivetrain

#include <Talon.h>
#include <RobotDrive.h>

class Drivetrain : public RobotDrive
{
public:
    Drivetrain();
    void drive();
};
#endif
