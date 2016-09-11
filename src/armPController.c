#include "main.h"

// These could be constants but leaving
// as variables allows them to be modified in the debugger "live"
const float pid_KpWrist = 0.2;
float pidValue;

/*-----------------------------------------------------------------------------*/
/*  pid control task                                                           */
/*-----------------------------------------------------------------------------*/

void pidController()
{
    float  pidSensorCurrentValue;
    float  pidError;
    float  pidDrive;
    
    while(true)
    {
        // Read the sensor value and scale
        pidSensorCurrentValue = getSensor(armEnc.parent);
        
        // calculate error
        pidError =  pidValue - pidSensorCurrentValue;
        
        // calculate drive
        pidDrive = (pid_KpWrist * pidError);
        
        // limit drive
        if(pidDrive > 127)
            pidDrive = 127;
        if(pidDrive < -127)
            pidDrive = -127;
        
        // send to motors
        setMotor(leftLift1, pidDrive);
        setMotor(leftLift2, pidDrive);
        setMotor(rightLift1, pidDrive);
        setMotor(rightLift2, pidDrive);
        
        // Don't hog cpu
        delay(20);
    }
}
