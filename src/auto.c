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
#define DUMP_PRELOAD_RIGHT_TILE 2
#define DUMP_PRELOAD_LEFT_TILE 3
#define CUBE_RIGHT_TILE 4
#define CUBE_LEFT_TILE 5

#define TEST 6
#define TEST_GYRO 7

#define RED false
#define BLUE true
bool color = BLUE;

int gyroValue;

void loads(int loads, double distance)

{
    for(int i = 0; i < loads; i++)
    {
        controlClaw(CLAW_CLOSE_POSITION, true);
        delay(500);
        controlDrive(distance, BACKWARD, false);
        delay(1500);
        gyroValue = rGyros();
        controlLiftPot(127, ARM_LAUNCH_HEIGHT, false);
        while(getSensor(armPot) < ARM_RELEASE_HEIGHT)
        {
            delay(20);
        }
        controlClaw(CLAW_OPEN_POSITION, false);
        while(getSensor(armPot) < ARM_LAUNCH_HEIGHT)
        {
            delay(20);
        }
        controlLiftPot(-127, ARM_MIN_HEIGHT, true);
        rTurn(gyroValue, 3, 127, true);
        if(i < loads - 1)
        {
            controlDrive(distance, FORWARD, true);
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
            controlDrive(650, BACKWARD, true);
            controlClaw(CLAW_OPEN_POSITION, false);
            delay(1000);
            controlDrive(200, FORWARD, true);
            loads(2, 1200);
            rTurn(-35, 3, 127, false);
            controlDrive(1200, FORWARD, true);
            loads(1, 1200);
            rTurn(90, 3, 127, false);
            controlDrive(2000, FORWARD, true);
            break;

        case DUMP_PRELOAD_RIGHT_TILE:
            controlDrive(650, BACKWARD, true);
            controlClaw(CLAW_OPEN_POSITION+100, false);
            rTurn(35, 3, 127, false);
            delay(1000);
            controlDrive(500, FORWARD, true);
            loads(1, 1600);
            controlClaw(CLAW_OPEN_POSITION - 600, false);
            controlDrive(600, BACKWARD, false);
            controlLiftPot(127, ARM_LAUNCH_HEIGHT, false);
            delay(2000);
            controlLiftPot(127, ARM_MIN_HEIGHT, true);
            break;

        case DUMP_PRELOAD_LEFT_TILE:
            controlDrive(650, BACKWARD, true);
            controlClaw(CLAW_OPEN_POSITION+100, false);
            rTurn(-25, 3, 127, false);
            delay(1000);
            controlDrive(500, FORWARD, true);
            loads(1, 1600);
            controlClaw(CLAW_OPEN_POSITION - 600, false);
            controlDrive(600, BACKWARD, false);
            controlLiftPot(127, ARM_LAUNCH_HEIGHT, true);
            controlLiftPot(127, ARM_MIN_HEIGHT, true);
            
            break;

        case CUBE_RIGHT_TILE:
            controlDrive(650, BACKWARD, true);
            controlClaw(CLAW_OPEN_POSITION+100, false);
            rTurn(25, 3, 127, false);
            delay(1000);
            controlDrive(500, FORWARD, true);
            loads(1, 1600);
            controlClaw(CLAW_OPEN_POSITION - 600, false);
            controlDrive(600, BACKWARD, false);
            controlLiftPot(127, ARM_LAUNCH_HEIGHT, false);
            controlLiftPot(127, ARM_MIN_HEIGHT, true);
            rTurn(-35, 3, 127, false);
            controlDrive(500, FORWARD, true);
            controlClaw(CLAW_CLOSE_POSITION, true);
            controlLiftPot(127, CONST_POWER_HEIGHT + 30, true);
            rTurn(35, 3, 127, true);
            controlLiftPot(127, ARM_LAUNCH_HEIGHT, false);
            while(getSensor(armPot) < ARM_RELEASE_HEIGHT)
            {
                delay(20);
            }
            controlClaw(CLAW_OPEN_POSITION, false);
            while(getSensor(armPot) < ARM_LAUNCH_HEIGHT)
            {
                delay(20);
            }
            controlLiftPot(127, ARM_MIN_HEIGHT, true);
            controlDrive(600, FORWARD, true);
            loads(1);
            break;

        case TEST:
            controlDrive(1320, FORWARD, true);
            controlDrive(1320, BACKWARD, true);
            controlDrive(1320, LEFT_TURN, true);
            controlDrive(1320, RIGHT_TURN, true);
            break;

        case TEST_GYRO:
            rTurn(360, 3, 127, false);
            break;

            default:
                printf("error, selected autonomous doesn't exist\n\r");
                break;
        }
    }
    printf("end autonomous\n\r");
}
