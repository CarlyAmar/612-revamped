#ifndef MAIN_H
#define MAIN_H

#include <IterativeRobot.h>

#include "SmoothJoystick.h"
#include "Drivetrain.h"
#include "Shooter.h"
#include "UpdateRegistry.h"

class robot_class : public IterativeRobot
{
public:
    robot_class();

    void RobotInit();   

    void DisabledInit();
    void DisabledPeriodic();

    void AutonomousInit();
    void AutonomousPeriodic();

    void autoWithDrive();
    void autoWithTilt();

    void TeleopInit();
    void TeleopPeriodic();

    void TestInit();
    void TestPeriodic();
    
    void init_vision();
    void stop_vision();
    
    void doControls();
    
    //DerekDrive* test_drivetrain;
    SmoothJoystick* driverJoy;
    SmoothJoystick* gunnerJoy;
    
    Drivetrain* driveT;
    Shooter* shoot;
    
    UpdateRegistry updateRegistry;
private:
    //autonomous flags
    bool imgFlag;
    bool hgClose;
    //task booleans
    bool shooting;
    bool turning;
    bool driving;
    bool energized;
};

#endif // MAIN_H
