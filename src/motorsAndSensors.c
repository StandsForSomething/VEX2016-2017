#include "main.h"
//////////
//motors//
//////////

//right motors
motor RFDrive = {2, false};
motor RBDriveI = {4, false};
motor RBDriveO = {5, false};

//left motors
motor LFDrive = {3, true};
motor LBDriveI = {6, true};
motor LBDriveO = {7, true};

//lift motors
motor leftLift1 = {1, true};
motor leftLift2 = {8, true};
motor rightLift1 = {10, false};
motor rightLift2 = {9, false};

///////////
//sensors//
///////////
//digital
sensor driveControlJumper = {1, DIGITAL, false};
sensor powerExpandJumper = {12, DIGITAL, true};
//analog
sensor powerExpand = {1, ANALOG, false};
sensor autoSelect = {2, ANALOG, false};

//encoders
encoder encoderLeft;
encoder encoderRight;

void encoderSetup()
{
    initEncoderTW(&encoderLeft, 11, 12, false, SPEED, ROTATIONS, 1.0);
    initEncoderTW(&encoderRight, 8, 9, false, SPEED, ROTATIONS, 1.0);
}
