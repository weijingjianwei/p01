/* -------------------------------------------------------------------- */
/* Copyright(c) 2009 Renesas Electronics Corporation                    */
/* -------------------------------------------------------------------- */
/* File name: drvssafe.h                                                */
/* Version:   0.01                                                      */
/* Date:      2013/01/18                                                */
/* Author:    A.Kondo                                                   */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* History                                                              */
/*   V0.01: 2013.01.18  1st creation.                                   */
/* -------------------------------------------------------------------- */
#ifndef H_DRVSSAFE
#define H_DRVSSAFE

/* -------------------------------------------------------------------- */
/* Type definition                                                      */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Macro definition                                                     */
/* -------------------------------------------------------------------- */
/* Channel abstraction macro for symbols */
#if (defined __LIN_CH0_P1__) || (defined __LIN_CH0_P4__)
#define LDrvSSafe_vogInitAll                LDrvSSafe_vogInitAll_0
#define LDrvSSafe_vogRefreshReg             LDrvSSafe_vogRefreshReg_0
#endif /* __LIN_CH0__ */

#if (defined __LIN_CH1_P1__) || (defined __LIN_CH1_P10__)
#define LDrvSSafe_vogInitAll                LDrvSSafe_vogInitAll_1
#define LDrvSSafe_vogRefreshReg             LDrvSSafe_vogRefreshReg_1
#endif /* __LIN_CH1__ */

/* -------------------------------------------------------------------- */
/* Public functions                                                     */
/* -------------------------------------------------------------------- */
void LDrvSSafe_vogInitAll( void );          /* Initialize the safety driver */
void LDrvSSafe_vogRefreshReg( void );       /* Refresh registers            */

/* -------------------------------------------------------------------- */
/* Public constants                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Public variables                                                     */
/* -------------------------------------------------------------------- */

#endif /* H_DRVSSAFE */

/* End of files */
