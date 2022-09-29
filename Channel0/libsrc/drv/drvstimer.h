/* -------------------------------------------------------------------- */
/* Copyright(c) 2009 Renesas Electronics Corporation                    */
/* -------------------------------------------------------------------- */
/* File name: drvstimer.h                                               */
/* Version  : 0.02                                                      */
/* Date     : 2013/08/05                                                */
/* Author:  : A.Kondo                                                   */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* History                                                              */
/*   V0.01: 2013.01.18  1st creation.                                   */
/*   V0.02: 2013.08.05  CH adding macro for vogRefreshReg was added.    */
/* -------------------------------------------------------------------- */
#ifndef H_DRVSTIMER
#define H_DRVSTIMER

/* -------------------------------------------------------------------- */
/* Type definition                                                      */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Macro definition                                                     */
/* -------------------------------------------------------------------- */
/* Channel abstraction macro for symbols */
#if (defined __LIN_CH0_P1__) || (defined __LIN_CH0_P4__)
#define LDrvSTimer_vogInitAll               LDrvSTimer_vogInitAll_0
#define LDrvSTimer_vogRefreshReg            LDrvSTimer_vogRefreshReg_0
#define LDrvSTimer_vogPowerOnAndInit        LDrvSTimer_vogPowerOnAndInit_0
#define LDrvSTimer_vogStartTimeout          LDrvSTimer_vogStartTimeout_0
#define LDrvSTimer_vogStopTimeout           LDrvSTimer_vogStopTimeout_0
#define LDrvSTimer_vogVecCompare            LDrvSTimer_vogVecCompare_0
#endif /* __LIN_CH0__ */

#if (defined __LIN_CH1_P1__) || (defined __LIN_CH1_P10__)
#define LDrvSTimer_vogInitAll               LDrvSTimer_vogInitAll_1
#define LDrvSTimer_vogRefreshReg            LDrvSTimer_vogRefreshReg_1
#define LDrvSTimer_vogPowerOnAndInit        LDrvSTimer_vogPowerOnAndInit_1
#define LDrvSTimer_vogStartTimeout          LDrvSTimer_vogStartTimeout_1
#define LDrvSTimer_vogStopTimeout           LDrvSTimer_vogStopTimeout_1
#define LDrvSTimer_vogVecCompare            LDrvSTimer_vogVecCompare_1
#endif /* __LIN_CH1__ */


/* -------------------------------------------------------------------- */
/* Public functions                                                     */
/* -------------------------------------------------------------------- */
void LDrvSTimer_vogInitAll( void );         /* Initialize the timer driver       */
void LDrvSTimer_vogRefreshReg( void );      /* Refresh register                  */
void LDrvSTimer_vogPowerOnAndInit( void );  /* Set the timer mode                */
void LDrvSTimer_vogStartTimeout( u4 );      /* Start counting time out           */
void LDrvSTimer_vogStopTimeout( void );     /* Stop counting time out            */
void LDrvSTimer_vogVecCompare( void );      /* Timer compare interrupt interface */

/* -------------------------------------------------------------------- */
/* Public constants                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Public variables                                                     */
/* -------------------------------------------------------------------- */

#endif /* H_DRVSTIMER */

/* End of files */
