/* -------------------------------------------------------------------- */
/* Copyright(c) 2009 Renesas Electronics Corporation                    */
/* -------------------------------------------------------------------- */
/* File name: lcorescom.h                                               */
/* Version:   0.03                                                      */
/* Date:      2015/02/02                                                */
/* Author:    A.Kondo, Shoichiro Sugawara                               */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* History                                                              */
/*   V0.01: 2013.01.18  1st creation.                                   */
/*   V0.02: 2013.08.22  WAITHEADERDOM and WAKEUPDOM were added(FixedBR).*/
/*   V0.03: 2015.02.02  Processing corresponding to the same            */
/*                      restriction was deleted by lifting              */
/*                      restrictions of FTS bit set timing of RLIN3.    */
/*                      [Macro]                                         */
/*                      - A driver state definition was set to the      */
/*                        following 7 patterns.                         */
/*                        - LCORESCOM_u1gFSMDORMANT                     */
/*                        - LCORESCOM_u1gFSMWAITHEADER                  */
/*                        - LCORESCOM_u1gFSMRECDATA                     */
/*                        - LCORESCOM_u1gFSMSENDDATA                    */
/*                        - LCORESCOM_u1gFSMWAKEUP                      */
/*                        - LCORESCOM_u1gFSMSENDWAKEUP                  */
/*                        - LCORESCOM_u1gFSMSLEEP                       */
/* -------------------------------------------------------------------- */
#ifndef H_LCORESCOM
#define H_LCORESCOM

/* -------------------------------------------------------------------- */
/* Type definition                                                      */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Macro definition                                                     */
/* -------------------------------------------------------------------- */
/* The addition of channel number to the function name and variable name*/
#if (defined __LIN_CH0_P1__) || (defined __LIN_CH0_P4__)
#define LCoreSCom_vogInitAll                LCoreSCom_vogInitAll_0
#define LCoreSCom_u1gDisconnect             LCoreSCom_u1gDisconnect_0
#define LCoreSCom_vogConnect                LCoreSCom_vogConnect_0
#define LCoreSCom_u1gFsm                    LCoreSCom_u1gFsm_0
#endif /* __LIN_CH0__ */

#if (defined __LIN_CH1_P1__) || (defined __LIN_CH1_P10__)
#define LCoreSCom_vogInitAll                LCoreSCom_vogInitAll_1
#define LCoreSCom_u1gDisconnect             LCoreSCom_u1gDisconnect_1
#define LCoreSCom_vogConnect                LCoreSCom_vogConnect_1
#define LCoreSCom_u1gFsm                    LCoreSCom_u1gFsm_1
#endif /* __LIN_CH1__ */


/* Define the state of the driver */
#define LCORESCOM_u1gFSMDORMANT             ((u1)0x01)    /* State: Dormant.          */
#define LCORESCOM_u1gFSMWAITHEADER          ((u1)0x02)    /* State: Waiting header.   */
#define LCORESCOM_u1gFSMRECDATA             ((u1)0x03)    /* State: Receiving data.   */
#define LCORESCOM_u1gFSMSENDDATA            ((u1)0x04)    /* State: Sending data.     */
#define LCORESCOM_u1gFSMWAKEUP              ((u1)0x05)    /* State: Wake up.          */
#define LCORESCOM_u1gFSMSENDWAKEUP          ((u1)0x06)    /* State: Sending wake up.  */
#define LCORESCOM_u1gFSMSLEEP               ((u1)0x07)    /* State: Sleep.            */

/* Define return value of the function */
#define LCORESCOM_u1gERROR_TRTIMEOUT        ((u1)OK + 1)


/* -------------------------------------------------------------------- */
/* Public functions                                                     */
/* -------------------------------------------------------------------- */
void LCoreSCom_vogInitAll( void );          /* Initialize lower-level LIN driver   */
u1   LCoreSCom_u1gDisconnect( void );       /* Disconnect from LIN interface       */
void LCoreSCom_vogConnect( void );          /* Connect LIN interface               */


/* -------------------------------------------------------------------- */
/* Public constants                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Public variables                                                     */
/* -------------------------------------------------------------------- */
extern u1 LCoreSCom_u1gFsm;                 /* State of the driver      */


#endif /* H_LCORESCOM */

/* End of files */
