#include "main.h"

double claw1PidValue;
bool disableClaw1Pid = false;

double claw2PidValue;
bool disableClaw2Pid = false;

double driveLPidValue;
double driveRPidValue;
bool disableDrivePid = true;

void pidController(void *taskArgs)
{
    pControllerArgs* argsPointer = taskArgs;
    pControllerArgs  args = *argsPointer;
    float  pidSensorCurrentValue;
    float  pidError;
    float  pidDrive;
    *args.pidValue = getSensor(args.pidSensor);
    while(true)
    {
        // Read the sensor value and scale
        pidSensorCurrentValue = getSensor(args.pidSensor);

        // calculate error
        pidError =  *args.pidValue - pidSensorCurrentValue;

        // calculate drive
        pidDrive = (args.pid_Kp * pidError);

        // limit drive
        if(pidDrive > 127)
            pidDrive = 127;
        if(pidDrive < -127)
            pidDrive = -127;

        if(!*args.disabled)
        {
            // send to motor
            setMotor(args.pidMotor, pidDrive);
        }

        // Don't hog cpu
        delay(20);
    }
}
