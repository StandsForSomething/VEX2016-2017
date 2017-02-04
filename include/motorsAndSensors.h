#ifndef MOTORS_H_
#define MOTORS_H_

//left drive motors
extern motor LFDrive;  //port 6, reversed
extern motor LBDrive;  //port 7, reversed


//right drive motors
extern motor RFDrive;  //port 4, not reversed
extern motor RBDrive;  //port 5, not reversed

//arm motors
extern motor liftLeft1Y;  //port 3,  reversed
extern motor liftleft2;  //port 2, reversed
extern motor liftRight1Y;  //port 8, not reversed
extern motor liftRight2;  //port 9, not reversed

//claw
extern motor claw1;  //port 1, reversed
extern motor claw2;  //port 10, not reversed

//digital
extern sensor powerExpandJumper;    //digital port 2, input, reversed


//analog
extern sensor powerExpand;         //analog port 1, not reversed
extern sensor autoSelect;        //analog port 2, not reversed


extern encoder encoderLeft;
extern encoder encoderRight;

void encoderSetup();

//definition for cortex pins
#define ENC_RIGHT_TOP 8
#define ENC_RIGHT_BOT 9
#define ENC_LEFT_TOP 11
#define ENC_LEFT_BOT 12


#define POWER_EXPAND_JUMP 10       //digital port 2

#define POWER_EXPAND 13            //analog port 1
#define AUTO_SELECT 14           //analog port 2
#define ARM_POT 15 //analog port 3
#endif
