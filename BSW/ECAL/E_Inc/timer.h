/*
 * Copyright (c) 2016 - 2018, ChangHui Vehicle Electric, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of ChangHui Vehicle Electric, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*********************************************************************************************
**     Filename    : timer.h
**     Project     : One Button Start PEPS
**     Processor   : S32K144_100
**     Version     : V01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-12-17, 20:30
**     Author      : Hyman.xie
**     Description :
**     Settings    :
*********************************************************************************************/

#ifndef __TIMER_H
#define __TIMER_H

/*********************************************************************************************
**     Include Files
*********************************************************************************************/

#include "timer_App.h"

#define  LOOP_ALWAYS 0xFFFFU
#define TRUE  1
#define FALSE 0

/*********************************************************************************************
**     Global functions prototype
*********************************************************************************************/

extern void Timer_Init(void);
extern void TimerRefresh(void);
extern void TimerRegister(EN_TIMER_ID ucTid, EN_TIMER_TYPE ucType, UINT16 ulLoopInvertal,void (*Callback)(void));
extern void TimerUnRegister(EN_TIMER_ID ucTid);
extern void TimerStart(EN_TIMER_ID ucTid, UINT16 ulTimerLen);
extern void TimerStop(EN_TIMER_ID ucTid);
extern UINT8 TimeOutJudge(EN_TIMER_ID ucTid);


#endif /* __TIMER_H */

/*********************************************************************************************
** EOF
*********************************************************************************************/

