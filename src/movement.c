#include "main.h"

void controlDrive(int speed, direction dir)
{
    switch(dir)
    {
    case FORWARD:
        setMotor(LFDrive, speed);
        setMotor(LBDriveI, speed);
        setMotor(LBDriveO, speed);
        setMotor(RFDrive, speed);
        setMotor(RBDriveI, speed);
        setMotor(RBDriveO, speed);
        break;

    case BACKWARD:
        setMotor(LFDrive, -speed);
        setMotor(LBDriveI, -speed);
        setMotor(LBDriveO, -speed);
        setMotor(RFDrive, -speed);
        setMotor(RBDriveI, -speed);
        setMotor(RBDriveO, -speed);
        break;

    case LEFT_TURN:
        setMotor(LFDrive, -speed);
        setMotor(LBDriveI, -speed);
        setMotor(LBDriveO, -speed);
        setMotor(RFDrive, speed);
        setMotor(RBDriveI, speed);
        setMotor(RBDriveO, speed);
        break;

    case RIGHT_TURN:
        setMotor(LFDrive, speed);
        setMotor(LBDriveI, speed);
        setMotor(LBDriveO, speed);
        setMotor(RFDrive, -speed);
        setMotor(RBDriveI, -speed);
        setMotor(RBDriveO, -speed);
        break;

    case LEFT_TURN_WIDE:
        setMotor(LFDrive, 0);
        setMotor(LBDriveI, 0);
        setMotor(LBDriveO, 0);
        setMotor(RFDrive, speed);
        setMotor(RBDriveI, speed);
        setMotor(RBDriveO, speed);
        break;

    case RIGHT_TURN_WIDE:
        setMotor(LFDrive, speed);
        setMotor(LBDriveI, speed);
        setMotor(LBDriveO, speed);
        setMotor(RFDrive, 0);
        setMotor(RBDriveI, 0);
        setMotor(RBDriveO, 0);
        break;
        
    case STOP:
        setMotor(LFDrive, 0);
        setMotor(LBDriveI, 0);
        setMotor(LBDriveO, 0);
        setMotor(RFDrive, 0);
        setMotor(RBDriveI, 0);
        setMotor(RBDriveO, 0);
        break;

    default:
        return;
        break;
    }
}
void controlDriveEnc(int speed, direction dir, double counts)
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

    controlDrive(0, STOP);
}

void controlLift(int speed)
{
    setMotor(liftLeft, speed);
    setMotor(liftRight, speed);
}

typedef struct controlLiftEncArgs
{
    int speed;
    double encValue;
}controlLiftEncArgs;

void controlLiftEncTask(void *funcArgs)
{
    controlLiftEncArgs* argsPointer = funcArgs;
    controlLiftEncArgs args = *argsPointer;

    controlLift(args.speed);
    encoderReset(armEnc.shaftEncoder);
    if(args.speed >= 0)
    {
        while(getSensor(armEnc.parent) < args.encValue)
        {
            //printf("%f\n\r", getSensor(armEnc.parent));
            delay(20);
        }
    }
    else
    {
        while(getSensor(armEnc.parent) > args.encValue)
        {
            //printf("%f\n\r", getSensor(armEnc.parent));
            delay(20);
        }
    }
    controlLift(0);
}

void controlLiftEnc(int speed, double encValue, bool waitForTaskEnd)
{
    controlLiftEncArgs args = {speed, encValue};

    if(!waitForTaskEnd)
    {
        taskCreate(controlLiftEncTask,
                   TASK_DEFAULT_STACK_SIZE, &args, TASK_PRIORITY_DEFAULT);
        delay(20);
    }

    else
    {
        controlLiftEncTask(&args);
    }
    printf("exit\n\r");
}
