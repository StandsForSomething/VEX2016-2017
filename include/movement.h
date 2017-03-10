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
void controlLift(double target, bool waitForTargetReached);
void controlClaw(double target, bool waitForTargetReached);
int rGyros();
void rTurn(int degrees, int tolerance, int power, bool isAbsolute);
#endif //MOVEMENT_H_
