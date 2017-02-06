# include "main.h"
//////////
//motors//
//////////

//left drive motors
motor LFDrive = {4, false};
motor LBDrive = {5, false};


//right drive motors
motor RFDrive = {6, true};
motor RBDrive = {7, true};

//lift motors
motor liftLeft1Y = {3, false};
motor liftleft2 = {2, true};
motor liftRight1Y = {8, true};
motor liftRight2 = {9, false};

//claw motors
motor claw1 = {1, false};
motor claw2 = {10,true};

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
    initEncoderTW(&encoderLeft, 11, 12, true, SPEED, ROTATIONS, 1.0);
    initEncoderTW(&encoderRight, 8, 9, false, SPEED, ROTATIONS, 1.0);
}
