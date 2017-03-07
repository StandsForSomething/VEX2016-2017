
/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions
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

//the main header file for every file in a PROS project
#include "main.h"

/*
 * Runs pre-initialization code. This function will be started in kernel mode one
 * time while the VEX Cortex is starting up. As the scheduler is still paused,
 * most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes
 * (pinMode()) and port states (digitalWrite()) of limit switches, push buttons,
 * and solenoids. It can also safely configure a UART port (usartOpen()) but
 * cannot set up an LCD (lcdInit()).
 */
void initializeIO()
{
}
/*
 * Runs user initialization code. This function will be started in its own task
 * with the default priority and stack size once when the robot is starting up.
 * It is possible that the VEXnet communication link may not be fully established
 * at this time, so reading from the VEX Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics),
 * LCDs, global variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and
 * autonomous() tasks will not start. An autonomous mode selection menu like the
 * pre_auton() in other environments can be implemented in this task if desired.
 */

void initialize()
{
    printf("encoders setup\n\r");
    encoderSetup();
    gyroSetup();
    static pControllerArgs claw1Args;
    claw1Args = (pControllerArgs){0.2, &claw1PidValue, claw1, claw1Pot,
                                  &disableClaw1Pid, &claw1Moving, false};
    static pControllerArgs claw2Args;
    claw2Args = (pControllerArgs){0.2, &claw2PidValue, claw2, claw2Pot,
                                  &disableClaw2Pid, &claw2Moving, false};
    static pControllerArgs driveLArgs;
    driveLArgs = (pControllerArgs){1, &driveLPidValue, LDrive,
                                   encoderLeft.parent, &disableDrivePid,
                                   &driveLMoving, false};
    static pControllerArgs driveRArgs;
    driveRArgs = (pControllerArgs){1, &driveRPidValue, RDrive,
                                   encoderRight.parent, &disableDrivePid,
                                   &driveRMoving, false};

    static pControllerArgs liftArgs;
    liftArgs = (pControllerArgs){0.2, &liftPidValue, liftLeft,
                                   armPot, &disableArmPid,
                                   &liftMoving, true};
    printf("LCD display\n\r");
    lcdInit(uart1);
    lcdClear(uart1);
    newItem("no auton", NULL);
    newItem("skills", NULL);
    newItem("dump preload R", NULL);
    newItem("dump preload L", NULL);
    newItem("cube R", NULL);
    newItem("cube L", NULL);
    newItem("rerun test", NULL);
    selectionPot = autoSelect;
    taskCreate(LCDMenuTask, TASK_DEFAULT_STACK_SIZE, NULL,
               TASK_PRIORITY_DEFAULT);
    taskCreate(pidController, TASK_DEFAULT_STACK_SIZE, &claw1Args,
               TASK_PRIORITY_DEFAULT);
    taskCreate(pidController, TASK_DEFAULT_STACK_SIZE, &claw2Args,
               TASK_PRIORITY_DEFAULT);
    taskCreate(pidController, TASK_DEFAULT_STACK_SIZE, &driveLArgs,
               TASK_PRIORITY_DEFAULT);
    taskCreate(pidController, TASK_DEFAULT_STACK_SIZE, &driveRArgs,
             TASK_PRIORITY_DEFAULT);
    taskCreate(pidController, TASK_DEFAULT_STACK_SIZE, &liftArgs,
             TASK_PRIORITY_DEFAULT);
    printf("initialized\n\r");
}
