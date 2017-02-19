#include "main.h"

void controlDrive(double target, direction dir, bool waitForTargetReached)
{   encoderReset(encoderLeft.shaftEncoder);
    encoderReset(encoderRight.shaftEncoder);
    double targetL = 0;
    double targetR = 0;
    switch(dir)
    {
    case FORWARD:
        //fallthrough

    case BACKWARD:
        targetL = target;
        targetR = target;
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
          getSensor(encoderLeft.parent) > targetL + 20 &&
          getSensor(encoderLeft.parent) < targetL - 20 &&
          getSensor(encoderRight.parent) > targetR + 20 &&
          getSensor(encoderRight.parent) < targetR - 20)
    {
        printf("%f : %f\n\r", getSensor(encoderLeft.parent), getSensor(encoderRight.parent));
        delay(20);
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

    controlLift(args.speed);
    if(args.speed >= 0)
    {
        while(getSensor(armPot) < args.potValue)
        {
            delay(20);
        }
    }
    else
    {
        while(getSensor(armPot) > args.potValue)
        {
            delay(20);
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
    controlLiftPotArgs args = {speed, potValue};

    if(!waitForTaskEnd)
    {
        taskCreate(controlLiftPotTask,
                   TASK_DEFAULT_STACK_SIZE, &args, TASK_PRIORITY_DEFAULT);
        delay(20);
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

    while(waitForTargetReached &&
          getSensor(claw1Pot) > target + 20 &&
          getSensor(claw1Pot) < target - 20 &&
          getSensor(claw2Pot) > target + 20 &&
          getSensor(claw2Pot) < target - 20)
    {
        delay(20);
    }
}
