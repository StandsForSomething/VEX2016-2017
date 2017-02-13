# include "main.h"
//////////
//motors//
//////////

//left drive motors
motor LDrive = {5, false};


//right drive motors
motor RDrive = {6, true};

//lift motors
motor liftLeftY = {4, true};
motor liftLeft = {3, false};
motor liftRightY = {7, false};
motor liftRight = {8, true};

//claw motors
motor claw1 = {2, false};
motor claw2 = {9, true};

///////////
//sensors//
///////////
//digital
sensor powerExpandJumper = {10, DIGITAL, true};


//analog
sensor powerExpand = {1, ANALOG, false};
sensor autoSelect = {2, ANALOG, false};
sensor armPot = {3, ANALOG, false};

//encoders
encoder encoderLeft;
encoder encoderRight;


void encoderSetup()
{
    initEncoderTW(&encoderLeft, 8, 9, true, SPEED, ROTATIONS, 1.0);
    initEncoderTW(&encoderRight, 11, 12, false, SPEED, ROTATIONS, 1.0);
}
