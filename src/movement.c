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
    while(waitForTargetReached &&
          (abs(getSensor(encoderLeft.parent)) > abs(targetL) + 20 ||
           abs(getSensor(encoderLeft.parent)) < abs(targetL) - 20))
    {
        printf("%f : %f\n\r", getSensor(encoderLeft.parent), getSensor(encoderRight.parent));
        delay(20);
    }

    if(waitForTargetReached)
    {
        targetR = getSensor(encoderRight.parent);
    }
}

void controlLift(int speed)
{
    setMotor(liftLeftY, speed);
    setMotor(liftLeft, speed);
    setMotor(liftRightY, speed);
    setMotor(liftRight, speed);
}

typedef struct controlLiftPotArgs
{
    int speed;
    double potValue;
}controlLiftPotArgs;

void controlLiftPotTask(void *funcArgs)
{
    controlLiftPotArgs* argsPointer = funcArgs;
    controlLiftPotArgs args = *argsPointer;
    if(args.speed >= 0)
    {
        while(getSensor(armPot) < args.potValue)
        {
            controlLift(args.speed);
            delay(20);
        }
    }
    else
    {
        while(getSensor(armPot) > args.potValue)
        {
            delay(20);
            controlLift(args.speed);
        }
    }

    if(getSensor(armPot) < ARM_CONST_POWER_HEIGHT_MAX ||
       getSensor(armPot) > ARM_CONST_POWER_HEIGHT_MIN)
    {
        controlLift(ARM_CONST_POWER);
    }

    else
    {
        controlLift(0);
    }
}

void controlLiftPot(int speed, double potValue, bool waitForTaskEnd)
{
    static controlLiftPotArgs args;
    args = (controlLiftPotArgs){speed, potValue};

    if(!waitForTaskEnd)
    {
        taskCreate(controlLiftPotTask,
                   TASK_DEFAULT_STACK_SIZE, &args, TASK_PRIORITY_DEFAULT);
    }

    else
    {
        controlLiftPotTask(&args);
    }
    printf("exit\n\r");
}

void controlClaw(double target, bool waitForTargetReached)
{
    claw1PidValue = target;
    claw2PidValue = target;

    while(waitForTargetReached && (claw1Moving || claw2Moving) &&
          (getSensor(claw1Pot) > target + 35 ||
           getSensor(claw1Pot) < target - 35 ||
           getSensor(claw2Pot) > target + 35 ||
           getSensor(claw2Pot) < target - 35))
    {
        delay(20);
    }
}

int rGyros()
{
    //return (gyroGet(gyro1) + gyroGet(gyro2)) / 2;
    return gyroGet(gyro1);
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
}
