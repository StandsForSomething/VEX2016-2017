/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions
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
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source
 * code may be obtained from http://sourceforge.net/projects/freertos/files/ or
 * on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via the
 * Field Management System or the VEX Competition Switch in the autonomous mode.
 * If the robot is disabled or communications is lost, the autonomous task will
 * be stopped by the kernel. Re-enabling the robot will restart the task, not
 * re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX
 * Joystick. However, the autonomous function can be invoked from another task if
 * a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never
 * exit. If it does so, the robot will await a switch to another mode or
 * disable/enable cycle.
 */

#define RED false
#define BLUE true

bool color = BLUE;
/*
void moveCornerStar()
{
    controlDriveEnc(127, FORWARD,   1.7);
    if(color == BLUE)
    {
        controlDriveEnc(127, RIGHT_TURN, 0.73);
        controlDriveEnc(127, FORWARD, 0.3);
    }

    else if(color == RED)
    {
        controlDriveEnc(127, LEFT_TURN, -0.73);
    }
    controlDriveEnc(127, FORWARD,   1.1);
}

void scoreCornerStar()
{
    moveCornerStar();
    controlDriveEnc(127, FORWARD,   1.5);
}

void pushStarsUnderFence(int times)
{
    for(int i = 0; i < times; i++)
    {
        controlDriveEnc(127, FORWARD,   0.5);
        controlDriveEnc(127, BACKWARD,  -0.5);
    }
}

void starsOffFence()
{
    controlLiftEnc(127, 20, true);
    controlLiftEnc(-127, -20, true);
    controlLiftEnc(127, 10, true);
}

void expand()
{
    controlLiftEnc(127, 27, false);
    controlDriveEnc(127, BACKWARD, -0.7);
}

void hang()
{
    controlDriveEnc(127, FORWARD, 0.5);
    controlLiftEnc(-127, -180.0, true);
}
*/
void autonomous()
{/*
    switch(currentSelection)
    {
    case 1:
        printf("auton: 1: corner star\n\r");
        expand();
        scoreCornerStar();
        break;

    case 2:
        printf("auton: 2: 1 + return\n\r");
        expand();
        scoreCornerStar();
        controlDriveEnc(127, BACKWARD,  -10.0);
        break;

    case 3:
        printf("auton: 3: 1 + fence\n\r");
        expand();
        scoreCornerStar();
        starsOffFence();
        break;


    case 5: //not working yet
        printf("auton: 5: hang\n\r");
        expand();
        moveCornerStar();
        controlLiftEnc(127, 70, false);
        controlDriveEnc(127, RIGHT_TURN, 0.25);
        controlDriveEnc(127, BACKWARD, -2.2);
        hang();
        break;

    case 100:  //not working yet
        printf("auton: 100: the big one\n\r");
        expand();
        controlDriveEnc(127, FORWARD, 1.3);
        controlDriveEnc(127, RIGHT_TURN_WIDE, 1.3);
        controlDriveEnc(127, FORWARD, 2.2);
        controlDriveEnc(127, BACKWARD, -1.8);
        controlDriveEnc(127, LEFT_TURN, -0.5);
        controlDriveEnc(127, FORWARD, 0.6);
        controlDriveEnc(127, RIGHT_TURN, 0.6);
        controlDriveEnc(127, FORWARD, 5);
        break;


    default:
        printf("error, selected autonomous doesn't exist\n\r");
    break;
    }

    printf("end autonomous\n\r");*/
}
