/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions
 * related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL,a EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source
 * code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

//the main header file for every file in a PROS project
#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own
 * task with the default priority and stack size whenever the robot is enabled
 * via the Field Management System or the VEX Competition Switch in the operator
 * control mode. If the robot is disabled or communications is lost, the operator
 * control task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX
 * Cortex will run the operator control task. Be warned that this will also occur
 * if the VEX Cortex is tethered directly to a computer via the USB A to A cable
 * without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is
 * available and the scheduler is operational. However, proper use of delay() or
 * taskDelayUntil() is highly recommended to give other tasks (including system
 * tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop,
 * even if empty.
 */


int motorSpeed = 0;
int motorTurnSpeed = 0;

void operatorControl()
{
    printf("opcontrol started\n\r");
    int liftControl = 0;
    int clawControl = 0;
    int driveSpeed = 100;
    int turnSpeed = 75;
    bool btn5uPushed = false;
    bool btn5dPushed = false;
    bool btn6uPushed = false;
    bool btn6dPushed = false;
    bool btn8uPushed = false;
    bool tipped = false;

    disableDrivePid = true;
    disableArmPid = true;
    //in the case that the power expander isn't plugged in don't continue until
    //it's plugged in or overriden by placeing a jumper in digital pin 2.
    //this makes sure the robot can't move unless the issue is fixed becuase once
    //the robot moves it can't legally be fixed.  The option of using a jumper to
    //continue is incase the issue can't be fixed.
    while(getSensor(powerExpand) < 1000 && getSensor(powerExpandJumper))
    {
        printf("power expander unplugged!\n\r");
        delay(1000);
    }

    taskCreate(record, TASK_DEFAULT_STACK_SIZE, NULL,
               TASK_PRIORITY_DEFAULT);
    while(1)
    {
        if(C1_5U && !btn5uPushed && !btn5dPushed)
        {
            motorSpeed = driveSpeed;
            btn5uPushed = true;
        }

        else if(!C1_5U && btn5uPushed)
        {
            btn5uPushed = false;
        }

        else if(C1_5D && !btn5dPushed && !btn5uPushed)
        {
            motorSpeed = -driveSpeed;
            btn5dPushed = true;
        }

        else if(!C1_5D && btn5dPushed)
        {
            btn5dPushed = false;
        }

        if(!C1_5U && !C1_5D)
        {
            motorSpeed = 0;
        }

        if(C1_6U && !btn6uPushed && !btn6dPushed)
        {
            motorTurnSpeed = turnSpeed;
            btn6uPushed = true;
        }
        else if(!C1_6U && btn6uPushed)
        {
            btn6uPushed = false;
        }

        else if(C1_6D && !btn6dPushed && !btn6uPushed)
        {
            motorTurnSpeed = -turnSpeed;
            btn6dPushed = true;
        }

        else if(!C1_6D && btn6dPushed)
        {
            btn6dPushed = false;
        }

        if(!C1_6U && !C1_6D)
        {
            motorTurnSpeed = 0;
        }

        setMotor(LDrive,  motorSpeed + motorTurnSpeed);
        setMotor(RDrive, motorSpeed - motorTurnSpeed);

        ////////
        //lift//
        ////////
        liftControl = C1LY;
        clawControl = C1RY;

        if(C1_8U && !btn8uPushed && !tipped)
        {
            tipped = true;
            btn8uPushed = true;
        }

        if(C1_8U && !btn8uPushed && tipped)
        {
            tipped = false;
            btn8uPushed = true;
        }

        else if(!C1_8U && btn8uPushed)
        {
            btn8uPushed = false;
        }

        if(abs(liftControl) > 15 &&
           (getSensor(armPot) <= ARM_LAUNCH_HEIGHT || liftControl < 0 || tipped)
           && (getSensor(armPot) >= ARM_MIN_HEIGHT || liftControl > 0))
        {
            setMotor(liftLeftY, liftControl);
            setMotor(liftLeft, liftControl);
            setMotor(liftRightY, liftControl);
            setMotor(liftRight, liftControl);
        }

        else if(getSensor(armPot) < ARM_CONST_POWER_HEIGHT_MAX &&
                getSensor(armPot) > ARM_CONST_POWER_HEIGHT_MIN)
        {
            setMotor(liftLeftY, ARM_CONST_POWER);
            setMotor(liftLeft, ARM_CONST_POWER);
            setMotor(liftRightY, ARM_CONST_POWER);
            setMotor(liftRight, ARM_CONST_POWER);
        }

        else
        {
            setMotor(liftLeftY, 0);
            setMotor(liftLeft, 0);
            setMotor(liftRightY, 0);
            setMotor(liftRight, 0);
        }

        ////////
        //claw//
        ////////

        if(abs(clawControl) > 15 && (getSensor(armPot) < ARM_RELEASE_HEIGHT ||
                                     tipped))
        {
            claw1PidValue = getSensor(claw1Pot) + (clawControl * 4);
        }


        else if(getSensor(armPot) >= ARM_RELEASE_HEIGHT && !tipped)
        {
            claw1PidValue = CLAW_OPEN_POSITION;
        }

        claw2PidValue = claw1PidValue;
        //motors can only be updated every 20 milliseconds
        delay(20);
    }
}
