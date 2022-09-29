/* -------------------------------------------------------------------- */
/* Copyright(c) 2009 Renesas Electronics Corporation                    */
/* -------------------------------------------------------------------- */
/* File name:   apslin.h                                                */
/* Version:     0.01                                                    */
/* Date:        2013/01/18                                              */
/* Author:      A.Kondo                                                 */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* History                                                              */
/*   V0.01: 2013.01.18  1st creation.                                   */
/* -------------------------------------------------------------------- */
#ifndef H_APSLIN
#define H_APSLIN

/* -------------------------------------------------------------------- */
/* Type definition                                                      */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Macro definition                                                     */
/* -------------------------------------------------------------------- */
#define APSLIN_u1gSUCCESS ((u1)0x00)                            /* Success */
#define APSLIN_u1gFAIL    ((u1)0xFF)                            /* Fault */

/* Channel abstraction macro for symbols */
#if (defined __LIN_CH0_P1__) || (defined __LIN_CH0_P4__)        /* Use LIN channel0 */
#define ApSLin_u1gRead8bitsSig      ApSLin_u1gRead8bitsSig_0
#define ApSLin_u2gRead16bitsSig     ApSLin_u2gRead16bitsSig_0
#define ApSLin_vogWrite8bitsSig     ApSLin_vogWrite8bitsSig_0
#define ApSLin_vogWrite16bitsSig    ApSLin_vogWrite16bitsSig_0
#define ApSLin_vogReadBytesSig      ApSLin_vogReadBytesSig_0
#define ApSLin_vogWriteBytesSig     ApSLin_vogWriteBytesSig_0
#define ApSLin_u1gTestFlag          ApSLin_u1gTestFlag_0
#define ApSLin_vogClearFlag         ApSLin_vogClearFlag_0
#define ApSLin_vogInitIfc           ApSLin_vogInitIfc_0
#define ApSLin_u1gConnectIfc        ApSLin_u1gConnectIfc_0
#define ApSLin_u1gDisconnectIfc     ApSLin_u1gDisconnectIfc_0
#define ApSLin_vogWakeupIfc         ApSLin_vogWakeupIfc_0
#define ApSLin_u2gReadStatus        ApSLin_u2gReadStatus_0
#endif /* __LIN_CH0__ */

#if (defined __LIN_CH1_P1__) || (defined __LIN_CH1_P10__)       /* Use LIN channel1 */
#define ApSLin_u1gRead8bitsSig      ApSLin_u1gRead8bitsSig_1
#define ApSLin_u2gRead16bitsSig     ApSLin_u2gRead16bitsSig_1
#define ApSLin_vogWrite8bitsSig     ApSLin_vogWrite8bitsSig_1
#define ApSLin_vogWrite16bitsSig    ApSLin_vogWrite16bitsSig_1
#define ApSLin_vogReadBytesSig      ApSLin_vogReadBytesSig_1
#define ApSLin_vogWriteBytesSig     ApSLin_vogWriteBytesSig_1
#define ApSLin_u1gTestFlag          ApSLin_u1gTestFlag_1
#define ApSLin_vogClearFlag         ApSLin_vogClearFlag_1
#define ApSLin_vogInitIfc           ApSLin_vogInitIfc_1
#define ApSLin_u1gConnectIfc        ApSLin_u1gConnectIfc_1
#define ApSLin_u1gDisconnectIfc     ApSLin_u1gDisconnectIfc_1
#define ApSLin_vogWakeupIfc         ApSLin_vogWakeupIfc_1
#define ApSLin_u2gReadStatus        ApSLin_u2gReadStatus_1
#endif /* __LIN_CH1__ */


/* -------------------------------------------------------------------- */
/* Public functions                                                     */
/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */
/* API                                                                  */
/* -------------------------------------------------------------------- */
u1   ApSLin_u1gInitSys(void);                               /* System initialization         */
u1   ApSLin_u1gRead8bitsSig( u1 );                          /* Read a 8 bit signal           */
u2   ApSLin_u2gRead16bitsSig( u1 );                         /* Read a 16 bit signal          */
void ApSLin_vogWrite8bitsSig( u1, u1 );                     /* Write a 8 bit signal          */
void ApSLin_vogWrite16bitsSig( u1, u2 );                    /* Write a 16 bit signal         */
void ApSLin_vogReadBytesSig( u1, u1, u1, u1* const );       /* Read a byte array signal      */
void ApSLin_vogWriteBytesSig( u1, u1, u1, const u1* const); /* Write a byte array signal     */
u1   ApSLin_u1gTestFlag( u1 );                              /* Read a signal update flag     */
void ApSLin_vogClearFlag( u1 );                             /* Clear a signal update flag    */
void ApSLin_vogInitIfc(void);                               /* LIN interface initialization  */
u1   ApSLin_u1gConnectIfc(void);                            /* Connect LIN interface         */
u1   ApSLin_u1gDisconnectIfc(void);                         /* Disconnect LIN interface      */
void ApSLin_vogWakeupIfc(void);                             /* Wake up                       */
u2   ApSLin_u2gReadStatus(void);                            /* Read and clear LIN status     */

/* -------------------------------------------------------------------- */
/* Public constants                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Public variables                                                     */
/* -------------------------------------------------------------------- */

#endif /* H_APSLIN */

/* End of files */
