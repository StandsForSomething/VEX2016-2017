/*
 * hardwareSetup.c
 *
 *  Created on: Oct 25, 2015
 *      Author: username
 */

#include "main.h"


typedef struct motor
{
    int port;
    bool reversed;
}motor;

//right conveyor belt motors
motor ROConveyor = {2, false};
motor RIConveyor = {3, true};

//left conveyor belt motors
motor LIConveyor = {4, false};
motor LOConveyor = {5, true};

//right motors
motor RFDrive = {5, true};
motor RBDrive = {7, true};

//left motors
motor LBDrive = {8, false};
motor LFDrive = {9, false};

///////////
//sensors//
///////////

//well, technically DIGITAL_OUT isn't a sensor but whatever.
typedef enum sensorType {ANALOG, DIGITAL, DIGITAL_OUT, IME, QUAD_ENC}sensorType;

//structure for sensors
typedef struct sensor
{
    int port;
    sensorType sensortype;
    bool reversed;
}sensor;

//digital
sensor powerExpandJumper = {1, DIGITAL, true};
sensor configJumper = {2,DIGITAL, true};

//analog
sensor tileSelect = {1, ANALOG, false};
sensor movementSelect = {2, ANALOG, false};
sensor powerExpand = {3, ANALOG, false};

//IME's
sensor RFenc = {0, IME, false};
sensor RBenc = {1, IME, false};
sensor BRenc = {2, IME, false};
sensor BLenc = {3, IME, false};
sensor LBenc = {4, IME, false};
sensor LFenc = {5, IME, false};
sensor FLenc = {6, IME, false};
sensor FRenc = {7, IME, false};

void setMotor(struct motor theMotor, int speed)
{
    motorSet(theMotor.port, theMotor.reversed ? -speed : speed);
}

void setOutput(struct sensor theSensor, bool value)
{
    //if HIGH should be written as LOW and vise versa
    if(theSensor.reversed)
        //make sure the correct value is written
        digitalWrite(theSensor.port, value ? HIGH : LOW);

    //if HIGH should be written as HIGH and LOw should be written as LOW
    else
        //write the value
        digitalWrite(theSensor.port, value);
}

int getSensor(struct sensor theSensor)
{
    //for less typing
    int sensorValue;

    //if the sensor iuct sensor theSensor is digital and not reversed
    if(theSensor.sensortype == DIGITAL && !theSensor.reversed)                  
    {
        //return the value of the sensor
        return(digitalRead(theSensor.port));
    }

    //if the sensor is digital and reversed
    else if(theSensor.sensortype == DIGITAL)
    {
        //return the opposite of what is read
        return digitalRead(theSensor.port) ? false : true;
    }

    else
    {
        //if the sensor is analog
        if(theSensor.sensortype == ANALOG)
            //set sensorValue to, well the value of the sensor.
            sensorValue = analogRead(theSensor.port);
        
        //if the sensor a motor encoder
        else if(theSensor.sensortype == IME)
            //set sensorValue to the IME
            imeGet(theSensor.port, &sensorValue);
        
        //if the sensor is reversed return the reveresed value,
        //otherwise return the value as it is.
        return(theSensor.reversed ? -sensorValue : sensorValue);
    }
}
