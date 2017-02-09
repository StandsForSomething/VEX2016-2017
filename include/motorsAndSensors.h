#ifndef MOTORS_H_
#define MOTORS_H_

//left drive motors
extern motor LFDrive;  //port 6, not reversed
extern motor LBDrive;  //port 7, not reversed


//right drive motors
extern motor RFDrive;  //port 4, reversed
extern motor RBDrive;  //port 5, reversed

//arm motors
extern motor liftLeftY;  //port 3, reversed
extern motor liftLeft;  //port 2, not reversed
extern motor liftRightY;  //port 8, not reversed
extern motor liftRight;  //port 9, reversed

//claw
extern motor claw1;  //port 1, not reversed
extern motor claw2;  //port 10, reversed

//digital
extern sensor powerExpandJumper;    //digital port 2, input, reversed


//analog
extern sensor powerExpand;         //analog port 1, not reversed
extern sensor autoSelect;        //analog port 2, not reversed
extern sensor armPot;


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
