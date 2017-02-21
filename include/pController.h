#ifndef ARMPCONTROLLER_H_
#define ARMPCONTROLLER_H_

typedef struct pControllerArgs
{
    double pid_Kp;
    double *pidValue;
    motor pidMotor;
    sensor pidSensor;
    bool *disabled;
}pControllerArgs;

extern double claw1PidValue;
extern bool disableClaw1Pid;

extern double claw2PidValue;
extern bool disableClaw2Pid;

extern double driveLPidValue;
extern double driveRPidValue;
extern bool disableDrivePid;

extern void pidController(void *taskArgs);
#endif
