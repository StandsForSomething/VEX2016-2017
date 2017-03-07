#include "main.h"

double claw1PidValue;
bool disableClaw1Pid = false;
bool claw1Moving;

double claw2PidValue;
bool disableClaw2Pid = false;
bool claw2Moving;

double driveLPidValue;
double driveRPidValue;
bool disableDrivePid = true;
bool driveLMoving;
bool driveRMoving;

double liftPidValue;
bool disableArmPid = false;
bool liftMoving;

void pidController(void *taskArgs)
{
    pControllerArgs* argsPointer = taskArgs;
    pControllerArgs  args = *argsPointer;
    float  pidSensorCurrentValue;
    float  pidSensorLastValue = getSensor(args.pidSensor);
    float  pidError;
    float  pidDrive;
    unsigned long last_time = millis();
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

        if(last_time + 500 <= millis())
        {
            last_time = millis();
            if(pidSensorCurrentValue + 20 <= pidSensorLastValue ||
               pidSensorCurrentValue - 20 >= pidSensorLastValue)
            {
                *args.movement = false;
            }
            else
            {
                *args.movement = true;
            }
            pidSensorLastValue = pidSensorCurrentValue;
        }

        if(!*args.disabled)
        {
            //well this is crap programming, I'll fix it later...
            if(args.arm)
            {
                setMotor(liftLeftY, pidDrive);
                setMotor(liftLeft, pidDrive);
                setMotor(liftRightY, pidDrive);
                setMotor(liftRight, pidDrive);
            }

            else
            // send to motor
            setMotor(args.pidMotor, pidDrive);
        }

        // Don't hog cpu
        delay(20);
    }
}
