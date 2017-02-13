#ifndef ARMPCONTROLLER_H_
#define ARMPCONTROLLER_H_

typedef struct pControllerArgs
{
    float pid_Kp;
    float pidValue;
    motor pidMotor;
    sensor pidSensor;
}pControllerArgs;

extern void pidController(void *taskArgs);
#endif
