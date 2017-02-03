#ifndef MOTORS_H_
#define MOTORS_H_

//left drive motors
extern motor LFDrive;  //port 2, not reversed
extern motor LBDriveO;  //port 3, reversed
extern motor LBDriveI;  //port 4, not reversed

//right drive motors
extern motor RFDrive;  //port 7,  reversed
extern motor RBDriveO;  //port 8, not reversed
extern motor RBDriveI;  //port 9, reversed

//arm motors
extern motor liftLeft;  //port 4, reversed
extern motor liftRight;  //port 5, not reversed

//claw
extern motor claw1;  //port 1, reversed
extern motor claw2;  //port 10, not reversed

//digital
extern sensor powerExpandJumper;    //digital port 2, input, reversed
extern sensor driveConfigJumper;

//analog
extern sensor powerExpand;         //analog port 1, not reversed
extern sensor autoSelect;        //analog port 2, not reversed

extern encoder armEnc;
extern encoder encoderLeft;
extern encoder encoderRight;

void encoderSetup();

//definition for cortex pins
#define ENC_RIGHT_TOP 8
#define ENC_RIGHT_BOT 9
#define ENC_LEFT_TOP 11
#define ENC_LEFT_BOT 12
#define ARM_ENC_TOP 6
#define ARM_ENC_BOT 7

#define DRIVE_CONFIG_JUMP 5
#define POWER_EXPAND_JUMP 10       //digital port 2

#define POWER_EXPAND 13            //analog port 1
#define AUTO_SELECT 14           //analog port 2
#endif
