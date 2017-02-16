#ifndef MOVEMENT_H_
#define MOVEMENT_H_
typedef enum direction
{
    FORWARD,
    BACKWARD,
    LEFT_TURN,
    RIGHT_TURN,
    LEFT_TURN_WIDE,
    LEFT_TURN_WIDE_BACKWARD,
    RIGHT_TURN_WIDE,
    RIGHT_TURN_WIDE_BACKWARD,
    STOP
    }direction;

//function prototypes
void controlDrive(double target, direction dir, bool waitForTargetReached);
void controlLift(int speed);
void controlLiftPot(int speed, double potValue, bool waitForTaskEnd);
void controlClaw(double target, bool waitForTargetReached);
#endif //MOVEMENT_H_
