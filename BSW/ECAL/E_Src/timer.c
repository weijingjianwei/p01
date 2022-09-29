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
**     Filename    : timer.c
**     Project     : One Button Start PEPS
**     Processor   : S32K144_100
**     Version     : V01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-12-17, 20:30
**     Author      : Hyman.xie
**     Description :
**     Settings    :
*********************************************************************************************/

/*********************************************************************************************
**     Include Files
*********************************************************************************************/
//#include "timer_App.h"
#include "timer.h"

/*********************************************************************************************
**     Local Global Variable
*********************************************************************************************/

static S_TIMER g_timerlist[TIMER_BUTT];

/*********************************************************************************************
  Function:        TimerInit
  Description:     Timer refresh interface
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:   
  Input:          void
  Output:          
  Return:          void
  Others:          
*********************************************************************************************/
void Timer_Init(void)
{
    UINT8 ucLoop = 0;
	
    for(ucLoop = 0; ucLoop < TIMER_BUTT; ucLoop++)
    {
        g_timerlist[ucLoop].unCtrl.ucByte = 0;
		g_timerlist[ucLoop].ulCount = 0;
		g_timerlist[ucLoop].ulInterval = 0;
        g_timerlist[ucLoop].ulIntervalLoad = 0;
		g_timerlist[ucLoop].Callback = (void *)0;
	}
}
/*********************************************************************************************
  Function:        TimerRefresh
  Description:     Timer refresh interface
  Calls:           
  Called By:       
  Table Accessed:  
  Table Updated:   
  Input:           void
  Output:          
  Return:          void
  Others:          
*********************************************************************************************/
void TimerRefresh(void)
{
    UINT8 ucLoop = 0;
	UINT8 ucLoopMaxValue;

    ucLoopMaxValue = TIMER_BUTT;

	for(ucLoop = 0; ucLoop < ucLoopMaxValue; ucLoop++)
	{
	    if((TRUE == g_timerlist[ucLoop].unCtrl.stBits.ucValid ) &&
	       (FALSE == g_timerlist[ucLoop].unCtrl.stBits.ucTimeOut))
		{
			if(LOOP_ALWAYS != g_timerlist[ucLoop].ulCount)
			{
	            g_timerlist[ucLoop].ulCount--;
			}
				
	        if(0 == g_timerlist[ucLoop].ulCount)
	        {
	            g_timerlist[ucLoop].unCtrl.stBits.ucTimeOut = TRUE;

				if(((void *)0 != g_timerlist[ucLoop].Callback) &&
				   (ONCE_TIMER == g_timerlist[ucLoop].unCtrl.stBits.ucType))
			    {
	                g_timerlist[ucLoop].Callback();
				}
			}
				
	        if(LOOP_TIMER == g_timerlist[ucLoop].unCtrl.stBits.ucType)
	        {
	            g_timerlist[ucLoop].ulInterval--;
					
	            if(0 == g_timerlist[ucLoop].ulInterval)
	            {
	                if((void *)0 != g_timerlist[ucLoop].Callback)
			    	{
	                   	g_timerlist[ucLoop].Callback();
					}

					g_timerlist[ucLoop].ulInterval = g_timerlist[ucLoop].ulIntervalLoad;
				}
			}
		}
	}	
}

/*********************************************************************************************
  Function:        TimerCycleReg
  Description:     
  Calls:           
  Called By:       
  Table Accessed:  
  Table Updated:   
  Input:           enTid-----Timer ID
                     callbackfunc
  Output:          
  Return:          void
  Others:          
*********************************************************************************************/
void TimerRegister(EN_TIMER_ID ucTid, EN_TIMER_TYPE ucType, UINT16 ulLoopInvertal, void (*Callback)(void))
{
    if((ucTid >= TIMER_BUTT) ||
      ((ucType != LOOP_TIMER) && (ucType != ONCE_TIMER)))
    {
        return;
	}

    g_timerlist[ucTid].unCtrl.stBits.ucType = ucType;

	if(LOOP_TIMER == ucType)
	{
        g_timerlist[ucTid].ulIntervalLoad = ulLoopInvertal;
        g_timerlist[ucTid].ulInterval = ulLoopInvertal;
	}

	g_timerlist[ucTid].Callback = Callback;
	
	return;
}
/*********************************************************************************************
  Function:        TimerCycleReg
  Description:     
  Calls:           
  Called By:      
  Table Accessed: 
  Table Updated:   
  Input:           enTid-----Timer ID
                     callbackfunc
  Output:          
  Return:          void
  Others:          
*********************************************************************************************/
void TimerUnRegister(EN_TIMER_ID ucTid)
{
    if(ucTid >= TIMER_BUTT)
    {
        return;
	}

    g_timerlist[ucTid].unCtrl.stBits.ucTimeOut = FALSE; 
    g_timerlist[ucTid].unCtrl.ucByte = 0;
	g_timerlist[ucTid].ulCount = 0;
	g_timerlist[ucTid].ulInterval = 0;
    g_timerlist[ucTid].ulIntervalLoad = 0;
	g_timerlist[ucTid].Callback = (void *)0;

	return;
}

/*********************************************************************************************
  Function:        TimerCycleReg
  Description:     
  Calls:           
  Called By:       
  Table Accessed:  
  Table Updated:   
  Input:           enTid-----Timer ID
                     ucTimerLen 
  Output:          
  Return:          void
  Others:          
*********************************************************************************************/
void TimerStart(EN_TIMER_ID ucTid, UINT16 ulTimerLen)
{
    if(ucTid >= TIMER_BUTT)
    {
        return;
	}
	
	g_timerlist[ucTid].ulCount = ulTimerLen;
	g_timerlist[ucTid].unCtrl.stBits.ucTimeOut = FALSE; 
	g_timerlist[ucTid].unCtrl.stBits.ucValid = TRUE; 
	
	return;
}
/*********************************************************************************************
  Function:        TimerCycleReg
  Description:     
  Calls:           
  Called By:       
  Table Accessed:  
  Table Updated:   
  Input:           enTid-----Timer ID
  Output:          
  Return:          void
  Others:          
*********************************************************************************************/
void TimerStop(EN_TIMER_ID ucTid)
{
    if(ucTid >= TIMER_BUTT)
    {
        return;
	}	
	
    g_timerlist[ucTid].unCtrl.ucByte = 0;
	g_timerlist[ucTid].ulCount = 0;
	g_timerlist[ucTid].ulInterval = 0;
    g_timerlist[ucTid].ulIntervalLoad = 0;
	g_timerlist[ucTid].Callback = (void *)0;
}

/*********************************************************************************************
  Function:        TimerCycleReg
  Description:     
  Calls:           
  Called By:       
  Table Accessed:  
  Table Updated:   
  Input:           enTid-----Timer ID
  Output:          
  Return:          True: 
                     False: 
  Others:          
*********************************************************************************************/
UINT8 TimeOutJudge(EN_TIMER_ID ucTid)
{
    if(ucTid >= TIMER_BUTT)
    {
        return FALSE;
	}

	return ((UINT8)(g_timerlist[ucTid].unCtrl.stBits.ucTimeOut));
}

/*********************************************************************************************
** EOF
*********************************************************************************************/

