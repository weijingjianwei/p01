/* -------------------------------------------------------------------- */
/* Copyright(c) 2009 Renesas Electronics Corporation                    */
/* -------------------------------------------------------------------- */
/* File name: lcoresdiag.h                                              */
/* Version:   0.01                                                      */
/* Date:      2013/01/18                                                */
/* Author:    A.Kondo                                                   */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* History                                                              */
/*   V0.01: 2013.01.18  1st creation.                                   */
/* -------------------------------------------------------------------- */
#ifndef H_LCORESDIAG
#define H_LCORESDIAG

/* -------------------------------------------------------------------- */
/* Type definition                                                      */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Macro definition                                                     */
/* -------------------------------------------------------------------- */
/* Channel abstraction macro for symbol                                 */
#if (defined __LIN_CH0_P1__) || (defined __LIN_CH0_P4__)
#define LCoreSDiag_vogInitAll               LCoreSDiag_vogInitAll_0
#define LCoreSDiag_u1gStartResponse         LCoreSDiag_u1gStartResponse_0
#define LCoreSDiag_u1gFinishRecResp         LCoreSDiag_u1gFinishRecResp_0
#define LCoreSDiag_u1gFinishSendResp        LCoreSDiag_u1gFinishSendResp_0
#endif /* __LIN_CH0__ */

#if (defined __LIN_CH1_P1__) || (defined __LIN_CH1_P10__)
#define LCoreSDiag_vogInitAll               LCoreSDiag_vogInitAll_1
#define LCoreSDiag_u1gStartResponse         LCoreSDiag_u1gStartResponse_1
#define LCoreSDiag_u1gFinishRecResp         LCoreSDiag_u1gFinishRecResp_1
#define LCoreSDiag_u1gFinishSendResp        LCoreSDiag_u1gFinishSendResp_1
#endif /* __LIN_CH1__ */

/* -------------------------------------------------------------------- */
/* Public functions                                                     */
/* -------------------------------------------------------------------- */
void      LCoreSDiag_vogInitAll( void );            /* Initialize diagnostic driver         */
u1        LCoreSDiag_u1gStartResponse( u1 );        /* Start sending and receiving response */
u1        LCoreSDiag_u1gFinishRecResp( u1 );        /* Response successfully received       */
u1        LCoreSDiag_u1gFinishSendResp( u1 );       /* Response successfully sent           */

/* -------------------------------------------------------------------- */
/* Public constants                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Public variables                                                     */
/* -------------------------------------------------------------------- */

#endif /* H_LCORESDIAG */

/* End of files */
