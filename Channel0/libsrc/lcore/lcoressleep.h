/* -------------------------------------------------------------------- */
/* Copyright(c) 2009 Renesas Electronics Corporation                    */
/* -------------------------------------------------------------------- */
/* File name: lcoressleep.h                                             */
/* Version:   0.02                                                      */
/* Date:      2013/08/22                                                */
/* Author:    A.Kondo                                                   */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* History                                                              */
/*   V0.01: 2013.01.18  1st creation.                                   */
/*   V0.02: 2013.08.22  CH adding macro for vogRetrySendWakeup was fixed*/
/*                      vogRtrySendWakeup was renamed for MISRA-C.      */
/* -------------------------------------------------------------------- */
#ifndef H_LCORESSLEEP
#define H_LCORESSLEEP

/* --------------------------------------------------------------------- */
/* The addition of LIN channel number in function name and variable name */
/* --------------------------------------------------------------------- */
#if (defined __LIN_CH0_P1__) || (defined __LIN_CH0_P4__)
#define LCoreSSleep_vogInitAll          LCoreSSleep_vogInitAll_0
#define LCoreSSleep_vogSleep            LCoreSSleep_vogSleep_0
#define LCoreSSleep_vogWakeup           LCoreSSleep_vogWakeup_0
#define LCoreSSleep_vogSendWakeup       LCoreSSleep_vogSendWakeup_0
#define LCoreSSleep_vogRtrySendWakeup   LCoreSSleep_vogRtrySendWakeup_0
#endif /* __LIN_CH0__ */

#if (defined __LIN_CH1_P1__) || (defined __LIN_CH1_P10__)
#define LCoreSSleep_vogInitAll          LCoreSSleep_vogInitAll_1
#define LCoreSSleep_vogSleep            LCoreSSleep_vogSleep_1
#define LCoreSSleep_vogWakeup           LCoreSSleep_vogWakeup_1
#define LCoreSSleep_vogSendWakeup       LCoreSSleep_vogSendWakeup_1
#define LCoreSSleep_vogRtrySendWakeup   LCoreSSleep_vogRtrySendWakeup_1
#endif /* __LIN_CH1__ */

/* -------------------------------------------------------------------- */
/* Type definition                                                      */
/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */
/* Macro definition                                                     */
/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */
/* Public functions                                                     */
/* -------------------------------------------------------------------- */
void LCoreSSleep_vogInitAll( void );         /* Initialize the sleep module           */
void LCoreSSleep_vogSleep( void );           /* Change the state to the sleep state   */
void LCoreSSleep_vogWakeup( void );          /* Change the state to the wake up state */
void LCoreSSleep_vogSendWakeup( void );      /* Start sending wake-up pulse           */
void LCoreSSleep_vogRtrySendWakeup( void );  /* Retry sending wake-up pulse           */

/* -------------------------------------------------------------------- */
/* Public constants                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Public variables                                                     */
/* -------------------------------------------------------------------- */

#endif /* H_LCORESSLEEP */

/* End of files */
