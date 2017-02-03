# include "main.h"
//////////
//motors//
//////////

//left drive motors
motor LFDrive = {2, false};
motor LBDriveO = {3, true};
motor LBDriveI = {4, false};

//right drive motors
motor RFDrive = {7, true};
motor RBDriveO = {8, false};
motor RBDriveI = {9, true};

//lift motors
motor liftLeft = {5, true};
motor liftRight = {6, false};

//claw motors
motor claw1 = {1, true};
motor claw2 = {10, false};

///////////
//sensors//
///////////
//digital
sensor powerExpandJumper = {10, DIGITAL, true};
sensor driveConfigJumper = {5, DIGITAL, true};

//analog
sensor powerExpand = {1, ANALOG, false};
sensor autoSelect = {2, ANALOG, false};
sensor armPot = {3, ANALOG, false};

//encoders
encoder encoderLeft;
encoder encoderRight;
encoder armEnc;

void encoderSetup()
{
    initEncoderTW(&armEnc, 6, 7, false, TORQUE, COUNTS, 1.0);
    initEncoderTW(&encoderLeft, 11, 12, true, SPEED, ROTATIONS, 1.0);
    initEncoderTW(&encoderRight, 8, 9, false, SPEED, ROTATIONS, 1.0);
}
