//21S rerun code ported to PROS

#include "main.h"

void record()
{
    gyroReset(gyro1);
    gyroReset(gyro2);
    encoderReset(encoderRight.shaftEncoder);
    encoderReset(encoderLeft.shaftEncoder);
    int j = 10, s = 1;
    for(int i = 0; i < 150; i++)
    {
        if(j == 10)
        {
            printf("   /* %d Second(s) */\n\r", s);
            s++;
            j = 0;
        }
        j++;
        printf("    auton(%f, %f, %f, %f, %f, %d);\n\r",
               getSensor(armPot), getSensor(encoderLeft.parent),
               getSensor(encoderRight.parent), getSensor(claw1Pot),
               getSensor(claw2Pot), rGyros());
        delay(100);
    }
}

int s;

void auton(double liftTarget, double driveLTarget, double driveRTarget,
           double claw1Target , double claw2Target, int gyros)
{
    for (int i = 0; i < 100; i++)
    {
        liftPidValue = liftTarget;
        driveLPidValue = driveLTarget;
        driveRPidValue = driveRTarget;
        claw1PidValue = claw1Target;
        claw2PidValue = claw2Target;
        /*if(rGyros() < gyros - 10 || rGyros() > gyros + 10)
        {
            rTurn(gyros, 3, 60, true);
            }*/
        delay(1);
    }
}
