#include "main.h"

void controlDrive(int speed, direction dir)
{
    switch(dir)
    {
    case FORWARD:
        setMotor(LFDrive, speed);
        setMotor(LBDrive, speed);
        setMotor(RFDrive, speed);
        setMotor(RBDrive, speed);
        break;

    case BACKWARD:
        setMotor(LFDrive, -speed);
        setMotor(LBDrive, -speed);
        setMotor(RFDrive, -speed);
        setMotor(RBDrive, -speed);
        break;

    case LEFT_TURN:
        setMotor(LFDrive, -speed);
        setMotor(LBDrive, -speed);
        setMotor(RFDrive, speed);
        setMotor(RBDrive, speed);
        break;

    case RIGHT_TURN:
        setMotor(LFDrive, speed);
        setMotor(LBDrive, speed);
        setMotor(LBDrive, speed);
        setMotor(RFDrive, -speed);
        setMotor(RBDrive, -speed);
        setMotor(RBDrive, -speed);
        break;

    case LEFT_TURN_WIDE:
        setMotor(LFDrive, 0);
        setMotor(LBDrive, 0);
        setMotor(RFDrive, speed);
        setMotor(RBDrive, speed);
        break;

    case RIGHT_TURN_WIDE:
        setMotor(LFDrive, speed);
        setMotor(LBDrive, speed);
        setMotor(RFDrive, 0);
        setMotor(RBDrive, 0);
        break;

    case STOP:
        setMotor(LFDrive, 0);
        setMotor(LBDrive, 0);
        setMotor(RFDrive, 0);
        setMotor(RBDrive, 0);
        break;

    default:
        return;
        break;
    }
}
void controlDriveEnc(int speed, direction dir, double counts, bool antiDrift)
{
    encoderReset(encoderRight.shaftEncoder);
    encoderReset(encoderLeft.shaftEncoder);
    controlDrive(speed, dir);
    if(dir == LEFT_TURN_WIDE)
    {
        while(getEncoder(encoderRight) < counts)
        {
            printf("%f\n\r", getEncoder(encoderRight));
            delay(20);
        }
    }

    else if(dir == BACKWARD || dir == LEFT_TURN || counts < 0)
    {
        while(getEncoder(encoderLeft) > counts)
        {
           printf("%f\n\r", getEncoder(encoderLeft));
            delay(20);
        }
    }

    else
    {
        while(getEncoder(encoderLeft) < counts)
        {
            printf("%f\n\r", getEncoder(encoderLeft));
            delay(20);
        }
    }

    if(antiDrift)
    {
        controlDrive(-speed, dir);
        delay(400);
    }
    controlDrive(0, STOP);
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

    if(getSensor(armPot) > ARM_CONST_POWER_HEIGHT)
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

void controlClaw(int speed)
{
    setMotor(claw1, speed);
    setMotor(claw2, speed);
}

void controlClawTime(int speed, int timeMS)
{
    controlClaw(speed);
    delay(timeMS);
    controlClaw(0);
}
