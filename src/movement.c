#include "main.h"

void controlDrive(double target, direction dir, bool waitForTargetReached)
{   encoderReset(encoderLeft.shaftEncoder);
    encoderReset(encoderRight.shaftEncoder);
    disableDrivePid = false;
    double targetL = 0;
    double targetR = 0;
    switch(dir)
    {
    case FORWARD:
        targetL = target;
        targetR = target;
        break;

    case BACKWARD:
        targetL = -target;
        targetR = -target;
        break;

    case LEFT_TURN:
        targetL = -target;
        targetR = target;
        break;

    case RIGHT_TURN:
        targetL = target;
        targetR = -target;
        break;

    case LEFT_TURN_WIDE:
        targetR = target;
        break;

    case LEFT_TURN_WIDE_BACKWARD:
        targetL = -target;
        break;
        
    case RIGHT_TURN_WIDE:
        targetL = target;
        break;

    case RIGHT_TURN_WIDE_BACKWARD:
        targetR = -target;

    case STOP:
        targetL = getSensor(encoderLeft.parent);
        targetR = getSensor(encoderRight.parent);
        break;

    default:
        return;
        break;
    }

    driveLPidValue = targetL;
    driveRPidValue = targetR;

    if(waitForTargetReached)
    {
        delay(500);
        while(driveLMoving || driveRMoving)
        {
            printf("%f : %f\n\r", getSensor(encoderLeft.parent), getSensor(encoderRight.parent));
            delay(20);
        }
    }
}

void controlLift(double target, bool waitForTargetReached)
{
    liftPidValue = target;

    if(waitForTargetReached)
    {
        delay(500);
        while(liftMoving)
        {
            delay(20);
        }
    }
}

void controlClaw(double target, bool waitForTargetReached)
{
    claw1PidValue = target;
    claw2PidValue = target;

    if(waitForTargetReached)
    {
        delay(500);
        while(claw1Moving || claw2Moving)
        {
            delay(20);
        }
    }
}

int rGyros()
{
    return (gyroGet(gyro1) + gyroGet(gyro2)) / 2;
}

void rTurn(int degrees, int tolerance, int power, bool isAbsolute)
{
    disableDrivePid = true;
    if (!isAbsolute)
    {
        gyroReset(gyro1);
        gyroReset(gyro2);
    }
    if (degrees > rGyros() + tolerance)
    {
        while (degrees > rGyros())
        {
            setMotor(LDrive, -power);
            setMotor(RDrive, power);
        }

    }

    else if (degrees < rGyros() - tolerance)
    {
        while (degrees < rGyros())
        {
            setMotor(LDrive, power);
            setMotor(RDrive, -power);
        }
    }
    driveLPidValue = getSensor(encoderLeft.parent);
    driveRPidValue = getSensor(encoderRight.parent);
    disableDrivePid = false;
    delay(1000);
}
