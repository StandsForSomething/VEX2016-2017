#include "main.h"

void pidController(void *taskArgs)
{
    pControllerArgs* argsPointer = taskArgs;
    pControllerArgs  args = *argsPointer;
    float  pidSensorCurrentValue;
    float  pidError;
    float  pidDrive;

    while(true)
    {
        // Read the sensor value and scale
        pidSensorCurrentValue = getSensor(args.pidSensor);

        // calculate error
        pidError =  args.pidValue - pidSensorCurrentValue;

        // calculate drive
        pidDrive = (args.pid_Kp * pidError);

        // limit drive
        if(pidDrive > 127)
            pidDrive = 127;
        if(pidDrive < -127)
            pidDrive = -127;

        // send to motors
        setMotor(args.pidMotor, pidDrive);

        // Don't hog cpu
        delay(20);
    }
}
