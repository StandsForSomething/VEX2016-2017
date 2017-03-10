# include "main.h"
//////////
//motors//
//////////

//left drive motors
motor LDrive = {5, false, CORTEX};


//right drive motors
motor RDrive = {6, true, CORTEX};

//lift motors
motor liftLeftY = {4, true, POWER_EXPANDER};
motor liftLeft = {3, false, CORTEX};
motor liftRightY = {7, false, POWER_EXPANDER};
motor liftRight = {8, true, CORTEX};

//claw motors
motor claw1 = {2, true, CORTEX};
motor claw2 = {9, false, CORTEX};

///////////
//sensors//
///////////
//digital
sensor powerExpandJumper = {10, DIGITAL, true};


//analog
sensor powerExpand = {1, ANALOG, false};
sensor autoSelect = {2, ANALOG, false};
sensor armPot = {3, ANALOG, false};
sensor claw1Pot = {4, ANALOG, false};
sensor claw2Pot = {5, ANALOG, false};
Gyro gyro1;
Gyro gyro2;

//encoders
encoder encoderLeft;
encoder encoderRight;

void gyroSetup()
{
    gyro1 = gyroInit(7, 206);
    gyro2 = gyroInit(8, 170);
}

void encoderSetup()
{
    initEncoderTW(&encoderLeft, 8, 9, true, SPEED, COUNTS, 1.0);
    initEncoderTW(&encoderRight, 11, 12, false, SPEED, COUNTS, 1.0);
}
