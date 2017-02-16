#ifndef ARMPCONTROLLER_H_
#define ARMPCONTROLLER_H_

typedef struct pControllerArgs
{
    double pid_Kp;
    double *pidValue;
    motor pidMotor;
    sensor pidSensor;
}pControllerArgs;

extern double claw1PidValue;
extern double claw2PidValue;
extern double driveLPidValue;
extern double driveRPidValue;

extern void pidController(void *taskArgs);
#endif
