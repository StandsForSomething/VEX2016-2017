#ifndef MOTORS_H_
#define MOTORS_H_

//left drive motors
extern motor LDrive;  //port 5, not reversed


//right drive motors
extern motor RDrive;  //port 6, reversed

//arm motors
extern motor liftLeftY;  //port 4, reversed
extern motor liftLeft;  //port 3, not reversed
extern motor liftRightY;  //port 7, not reversed
extern motor liftRight;  //port 8, reversed

//claw
extern motor claw1;  //port 2, reversed
extern motor claw2;  //port 9, not reversed

//digital
extern sensor powerExpandJumper;  //digital port 10, input, reversed


//analog
extern sensor powerExpand;  //analog port 1, not reversed
extern sensor autoSelect;  //analog port 2, not reversed
extern sensor armPot;  //analog port 3, not reversed
extern sensor claw1Pot;  //analog port 4, not reversed
extern sensor claw2Pot;  //analog port 5, not reversed

extern Gyro gyro1;
extern Gyro gyro2;


extern encoder encoderLeft;  //digital ports 8 and 9, reversed
extern encoder encoderRight;  // digital ports 11 and 12, not reversed

void gyroSetup();
void encoderSetup();
#endif
