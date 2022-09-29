/*------------------------------------------------------------------------------------------------+
| File: timer.h  	                                                                              |
+-------------------------------------------------------------------------------------------------+
| Project: ECU_PEPS                                                                               |
+-------------------------------------------------------------------------------------------------+
| Short description:                                                                              |
| Description of the file		                                                                  |
|                                                                                                 |
|                                                                                                 |
+-------------------------------------------------------------------------------------------------+
| Change history:                                                                                 |
| 01.01.10: Initial version                                                                       |
|																								  |
| Add new lines above                                                                             |
+-------------------------------------------------------------------------------------------------+
| for Information, to do:                                                                         |
|                                                                                                 |
|                                                                                                 |
+-------------------------------------------------------------------------------------------------+
| $Revision::   1.16                                                                           $: |
| $Date::   Nov 05 2015 08:16:24                                                               $: |
| $Author::   pjiang1                                                                          $: |
| $URL::                                                                                       $: |
|                                                                                                 |
+------------------------------------------------------------------------------------------------*/
/*	example
	Init:	
		Timer_Init(); 
	
	start:
		TimerRegister(DIAG_SECURITY_ACCESS_DELAY_TIMER,ONCE_TIMER,0,NULL);
		TimerStart(DIAG_SECURITY_ACCESS_DELAY_TIMER,SA_DELAY_TIMER_cfg);
	
	end:
		if(TRUE == TimeOutJudge(DIAG_SECURITY_ACCESS_DELAY_TIMER))	
		{
				 TimerUnRegister(DIAG_SECURITY_ACCESS_DELAY_TIMER);
				 TimerStop(DIAG_SECURITY_ACCESS_DELAY_TIMER);
		}
	
	|
*/

#ifndef TIMER_APP_H_
#define TIMER_APP_H_

typedef unsigned char UINT8;
typedef unsigned int UINT16;
typedef unsigned long UINT32;

/* timer status */
typedef union
{
     struct
	 {
         UINT16 ucValid        :  1;
         UINT16 ucType         :  1;  /*0---once timer  1---loop timer*/
         UINT16 ucTimeOut      :  1;  /*0---no timeout  1---already timeout*/
         UINT16 ucResv0        :  5;
         UINT16 ucResv1        :  8;
     } stBits;

	 UINT16 ucByte;
}U_TIMER_CTL;

/* timer configuration */
typedef  struct
{
    U_TIMER_CTL unCtrl;
    UINT8  ucUnused;
	UINT16 ulIntervalLoad;      /*the initial loop timer Interval*/
    UINT16 ulInterval;         /*loop timer Interval*/
	UINT16 ulCount;            /*the timer total and present time*/
    void (*Callback)(void);    /*timeout callback function*/
} S_TIMER;

/* timer ID for all function */
typedef enum
{
     SYS_POWER_ON_LIN_SIGNAL_TIMER,
		 LIN_SIGNAL_LOSS_TIMER,
	   IND_FLASH_CYCLE_TIMER,
     TIMER_BUTT
} EN_TIMER_ID;

/* timer type */
typedef enum
{
   ONCE_TIMER = 0,
	 LOOP_TIMER
} EN_TIMER_TYPE;

#endif /* TIMER_APP_H_ */

/*********************************************************************************************
** EOF
*********************************************************************************************/

