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

#define SKILLS 1
#define DUMP_PRELOAD 2
#define TEST 3

#define RED false
#define BLUE true
bool color = BLUE;

void loads(int loads)
{
    for(int i = 0; i < loads; i++)
    {
        controlClaw(CLAW_CLOSE_POSITION, true);
        controlDrive(3000, BACKWARD, false);
        delay(1500);
        controlLiftPot(127, ARM_LAUNCH_HEIGHT, false);
        while(getSensor(armPot) < ARM_LAUNCH_HEIGHT)
        {
            delay(20);
        }
        controlClaw(CLAW_OPEN_POSITION, false);
        controlLiftPot(-127, ARM_MIN_HEIGHT, false);
        if(i < loads - 2)
        {
            controlDrive(3000, FORWARD, true);
            delay(1000);
        }
    }
}

void autonomous()
{
    if(getSensor(powerExpand) > 1000)
    {
        disableDrivePid = false;
        switch(currentSelection)
        {
        case SKILLS:
            controlDrive(500, BACKWARD, true);
            controlClaw(CLAW_OPEN_POSITION, false);
            delay(1000);
            controlDrive(250, FORWARD, true);
            loads(3);
            break;

        case DUMP_PRELOAD:
            break;

        case TEST:
            controlDrive(1320, FORWARD, true);
            controlDrive(1320, BACKWARD, true);
            controlDrive(1320, LEFT_TURN, true);
            controlDrive(1320, RIGHT_TURN, true);
            break;

            default:
                printf("error, selected autonomous doesn't exist\n\r");
                break;
            }
        }
    printf("end autonomous\n\r");
}
