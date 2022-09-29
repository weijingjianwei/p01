/* -------------------------------------------------------------------- */
/* Copyright(c) Renesas Electronics Corporation                         */
/* File name: conflin.h                                                 */
/* Version:   1.04                                                      */
/* ---------------------------------------------------------------------*/

/* -------------------------------------------------------------------- */
/* History                                                              */
/*   V1.04: 2015.07.28  Add parameters of RL78/F15 RLIN3                */
/*   V1.03: 2014.03.31  Add macro definition area for application       */
/*   V1.02: 2013.04.24  Add parameters of RL78/F13,F14 RLIN3            */
/*   V1.01: 2012.03.28  Add parameters of RL78/F12 UARTF and change     */
/*                      copyright                                       */
/*   V1.00: 2005.12.19  New                                             */
/* -------------------------------------------------------------------- */
#ifndef H_CONFLIN
#define H_CONFLIN

/* ******************************************************************** */
/* [Add macro definitions for LIN application] (from here)              */
/*                                                                      */
/* [Example]                                                            */
/*   #define __LIN_CH0__                                                */
/*                                                                      */
/* [Note]                                                               */
/*   Definition contents are different by each devices.                 */
/*   For more detail, see "compile option" in readme.txt .              */
/* ******************************************************************** */


/* ******************************************************************** */
/* [Add macro definitions for LIN application] (to here)                */
/* ******************************************************************** */

/*!!!!!!!!!!! The following values are defined by user !!!!!!!!!!!!!!!!!*/
/* Index of the array, ConfLin_stgSignal, are named as signal name.     */
/*   (This array is defined in conflin.c)                               */
#define SysPowerMod     (0)
#define PosLmpOutputSts (1)
#define ACOpenSts       (2)
#define ACAutoModEnaSts (3)
#define ACAirInletSts   (4)
#define ACCmprEnaSts    (5)
#define CCSM_DATA0      (6)
#define CCSM_ResErr     (7)
#define CCSM_DATA1      (8)
#define CCSM_DATA2      (9)
#define CCSM_DATA3      (10)
#define CCSM_DATA4      (11)
#define CCSM_DATA5      (12)
#define CCSM_DATA6      (13)
#define CCSM_DATA7      (14)

/*!!!!! Frame name. This section is filled by LIN Configurator. !!!!!!!!*/
#define BCM_LINFr30_S  (0)
#define CCSM_LINFr39_S (1)

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/


/* ******************************************************************** */
/* [Not user setting]                                                   */
/* ******************************************************************** */

#if (defined __LIN_KX__)            || \
    (defined __LIN_FX_UART60__)     || \
    (defined __LIN_FX_UART61__)     || \
    (defined __LIN_FX_L__)
#define LIN_CHANNEL0  ((u1)0x00)

#define ConfLin_u2gCRWAKEUP        Conflin_u2gCRWAKEUP
#define ConfLin_u2gTIMEWAKEUP      Conflin_u2gTIMEWAKEUP
#define ConfLin_u2gCRWAKEUPAF3     Conflin_u2gCRWAKEUPAF3
#define ConfLin_u2gTIMEWAKEUPAF3   Conflin_u2gTIMEWAKEUPAF3
#endif /* __LIN_KX__, __LIN_FX_UART60__, __LIN_FX_UART61__, __LIN_FX_L__ */


#if (defined __LIN_FX3_UARTD0__)    || \
    (defined __LIN_FX3_UARTD1__)    || \
    (defined __LIN_FX3_UARTD2__)    || \
    (defined __LIN_FX3_UARTD3_P4__) || \
    (defined __LIN_FX3_UARTD3_P8__) || \
    (defined __LIN_FX3_UARTD4__)    || \
    (defined __LIN_FX3_UARTD5__)    || \
    (defined __LIN_FX3_UARTD6__)    || \
    (defined __LIN_FX3_UARTD7__)
#define LIN_CHANNEL0  ((u1)0x00)

#define ConfLin_u1gCKSRINIT        ConfLin_u1gUACTL1INIT
#define ConfLin_u1gBRGCINIT        ConfLin_u1gUACTL2INIT
#endif /* __LIN_FX3_UARTDn__ */


#if (defined __LIN_78K0R_FX3__)     || \
    (defined __LIN_RL78_F12__)      || \
    (defined __LIN_RL78_F13_F14__) || \
    (defined __LIN_RL78_F15__)

/* Channel abstraction macros for symbols */
#define ConfLin_stMesInfo          ConfSLin_stMesInfo
#define ConfLin_stSignal           ConfSLin_stSignal
#define ConfLin_stNode             ConfSLin_stNode
#define ConfLin_stEventInfo        ConfSLin_stEventInfo
#define ConfLin_stMesBuf           ConfSLin_stMesBuf

#define ApLin_u1gInitSys           ApSLin_u1gInitSys
#define ConfLin_vogCallDisableIrq  ConfSLin_vogCallDisableIrq
#define ConfLin_vogCallRestoreIrq  ConfSLin_vogCallRestoreIrq
#define ConfLin_vogCallSleepIfc    ConfSLin_vogCallSleepIfc
#define ConfLin_vogCallWakeupIfc   ConfSLin_vogCallWakeupIfc

#if (defined __LIN_CH0__)           || \
    (defined __LIN_CH0_P1__)        || \
    (defined __LIN_CH0_P4__)        /* UARTF0, RLIN3 channel 0 */
#define LIN_CHANNEL0 0              /* LIN channel number */

#define ConfLin_u1gMESNUM          ConfSLin_u1gMESNUM_0
#define ConfLin_u1gSIGNUM          ConfSLin_u1gSIGNUM_0
#define ConfLin_u1gEVENTNUM        ConfSLin_u1gEVENTNUM_0
#define ConfLin_stgMESINFO         ConfSLin_stgMESINFO_0
#define ConfLin_stgSIGNAL          ConfSLin_stgSIGNAL_0
#define ConfLin_stgNODE            ConfSLin_stgNODE_0
#define ConfLin_stgEVENTINFO       ConfSLin_stgEVENTINFO_0
#define ConfLin_stgMesBuf          ConfSLin_stgMesBuf_0
#define ConfLin_u1gEventPid        ConfSLin_u1gEventPid_0
#define ConfLin_u1gMesNoTbl        ConfSLin_u1gMesNoTbl_0
#define ConfLin_u1gMesPid          ConfSLin_u1gMesPid_0

#if (defined __LIN_RL78_F13_F14__) || \
    (defined __LIN_RL78_F15__)
#define ConfSLin_u4gBUSTIMEOUT     ConfSLin_u4gBUSTIMEOUT_0
#define ConfSLin_u2gPERICLOCK      ConfSLin_u2gPERICLOCK_0
#define ConfSLin_u2gTMPERICLOCK    ConfSLin_u2gTMPERICLOCK_0
#define ConfSLin_u2gBAUDRATENORM   ConfSLin_u2gBAUDRATENORM_0
#else
#define ConfLin_u2gBUSTIMEOUT      ConfSLin_u2gBUSTIMEOUT_0
#define ConfLin_u1gAPITMPMESNO     ConfSLin_u1gAPITMPMESNO_0
#define ConfLin_u1gCORETMPMESNO    ConfSLin_u1gCORETMPMESNO_0
#define ConfLin_u2gTIMEBASE        ConfSLin_u2gTIMEBASE_0
#define ConfLin_u2gUFCTL1INIT      ConfSLin_u2gUFCTL1INIT_0
#define ConfLin_u2gRESSPACETIME    ConfSLin_u2gRESSPACETIME_0
#define ConfLin_u2gRESSPACEBASE    ConfSLin_u2gRESSPACEBASE_0
#define ConfLin_u2gCRWAKEUP        ConfSLin_u2gCRWAKEUP_0
#define ConfLin_u2gTIMEWAKEUP      ConfSLin_u2gTIMEWAKEUP_0
#define ConfLin_u2gCRWAKEUPAF3     ConfSLin_u2gCRWAKEUPAF3_0
#define ConfLin_u2gTIMEWAKEUPAF3   ConfSLin_u2gTIMEWAKEUPAF3_0
#endif /* __LIN_RL78_F13_F14__, __LIN_RL78_F15__ */

#ifdef __LIN_SIGNAL_32__
#define ConfLin_u4gMesSig          ConfSLin_u4gMesSig_0
#define ConfLin_u4gMesSubSig       ConfSLin_u4gMesSubSig_0
#else
#define ConfLin_u2gMesSig          ConfSLin_u2gMesSig_0
#define ConfLin_u2gMesSubSig       ConfSLin_u2gMesSubSig_0
#endif /* __LIN_SIGNAL_32__ */

#define ApLin_u1gRead8bitsSig      ApSLin_u1gRead8bitsSig_0
#define ApLin_u2gRead16bitsSig     ApSLin_u2gRead16bitsSig_0
#define ApLin_vogWrite8bitsSig     ApSLin_vogWrite8bitsSig_0
#define ApLin_vogWrite16bitsSig    ApSLin_vogWrite16bitsSig_0
#define ApLin_vogReadBytesSig      ApSLin_vogReadBytesSig_0
#define ApLin_vogWriteBytesSig     ApSLin_vogWriteBytesSig_0
#define ApLin_u1gTestFlag          ApSLin_u1gTestFlag_0
#define ApLin_vogClearFlag         ApSLin_vogClearFlag_0
#define ApLin_vogInitIfc           ApSLin_vogInitIfc_0
#define ApLin_u1gConnectIfc        ApSLin_u1gConnectIfc_0
#define ApLin_u1gDisconnectIfc     ApSLin_u1gDisconnectIfc_0
#define ApLin_vogWakeupIfc         ApSLin_vogWakeupIfc_0
#define ApLin_u2gReadStatus        ApSLin_u2gReadStatus_0

#endif /* __LIN_CH0__ */

#if (defined __LIN_CH1_P1__)        || \
    (defined __LIN_CH1_P7__)        || \
    (defined __LIN_CH1_P10__)       /* UARTF1, RLIN3 channel 1 */
#define LIN_CHANNEL0 1              /* LIN channel number */

#define ConfLin_u1gMESNUM          ConfSLin_u1gMESNUM_1
#define ConfLin_u1gSIGNUM          ConfSLin_u1gSIGNUM_1
#define ConfLin_u1gEVENTNUM        ConfSLin_u1gEVENTNUM_1
#define ConfLin_stgMESINFO         ConfSLin_stgMESINFO_1
#define ConfLin_stgSIGNAL          ConfSLin_stgSIGNAL_1
#define ConfLin_stgNODE            ConfSLin_stgNODE_1
#define ConfLin_stgEVENTINFO       ConfSLin_stgEVENTINFO_1
#define ConfLin_stgMesBuf          ConfSLin_stgMesBuf_1
#define ConfLin_u1gEventPid        ConfSLin_u1gEventPid_1
#define ConfLin_u1gMesNoTbl        ConfSLin_u1gMesNoTbl_1
#define ConfLin_u1gMesPid          ConfSLin_u1gMesPid_1

#if (defined __LIN_RL78_F13_F14__) || \
    (defined __LIN_RL78_F15__)
#define ConfSLin_u4gBUSTIMEOUT     ConfSLin_u4gBUSTIMEOUT_1
#define ConfSLin_u2gPERICLOCK      ConfSLin_u2gPERICLOCK_1
#define ConfSLin_u2gTMPERICLOCK    ConfSLin_u2gTMPERICLOCK_1
#define ConfSLin_u2gBAUDRATENORM   ConfSLin_u2gBAUDRATENORM_1
#else
#define ConfLin_u2gBUSTIMEOUT      ConfSLin_u2gBUSTIMEOUT_1
#define ConfLin_u1gAPITMPMESNO     ConfSLin_u1gAPITMPMESNO_1
#define ConfLin_u1gCORETMPMESNO    ConfSLin_u1gCORETMPMESNO_1
#define ConfLin_u2gTIMEBASE        ConfSLin_u2gTIMEBASE_1
#define ConfLin_u2gUFCTL1INIT      ConfSLin_u2gUFCTL1INIT_1
#define ConfLin_u2gRESSPACETIME    ConfSLin_u2gRESSPACETIME_1
#define ConfLin_u2gRESSPACEBASE    ConfSLin_u2gRESSPACEBASE_1
#define ConfLin_u2gCRWAKEUP        ConfSLin_u2gCRWAKEUP_1
#define ConfLin_u2gTIMEWAKEUP      ConfSLin_u2gTIMEWAKEUP_1
#define ConfLin_u2gCRWAKEUPAF3     ConfSLin_u2gCRWAKEUPAF3_1
#define ConfLin_u2gTIMEWAKEUPAF3   ConfSLin_u2gTIMEWAKEUPAF3_1
#endif /* __LIN_RL78_F13_F14__, __LIN_RL78_F15__ */

#ifdef __LIN_SIGNAL_32__
#define ConfLin_u4gMesSig          ConfSLin_u4gMesSig_1
#define ConfLin_u4gMesSubSig       ConfSLin_u4gMesSubSig_1
#else
#define ConfLin_u2gMesSig          ConfSLin_u2gMesSig_1
#define ConfLin_u2gMesSubSig       ConfSLin_u2gMesSubSig_1
#endif /* __LIN_SIGNAL_32__ */

#define ApLin_u1gRead8bitsSig      ApSLin_u1gRead8bitsSig_1
#define ApLin_u2gRead16bitsSig     ApSLin_u2gRead16bitsSig_1
#define ApLin_vogWrite8bitsSig     ApSLin_vogWrite8bitsSig_1
#define ApLin_vogWrite16bitsSig    ApSLin_vogWrite16bitsSig_1
#define ApLin_vogReadBytesSig      ApSLin_vogReadBytesSig_1
#define ApLin_vogWriteBytesSig     ApSLin_vogWriteBytesSig_1
#define ApLin_u1gTestFlag          ApSLin_u1gTestFlag_1
#define ApLin_vogClearFlag         ApSLin_vogClearFlag_1
#define ApLin_vogInitIfc           ApSLin_vogInitIfc_1
#define ApLin_u1gConnectIfc        ApSLin_u1gConnectIfc_1
#define ApLin_u1gDisconnectIfc     ApSLin_u1gDisconnectIfc_1
#define ApLin_vogWakeupIfc         ApSLin_vogWakeupIfc_1
#define ApLin_u2gReadStatus        ApSLin_u2gReadStatus_1

#endif /* __LIN_CH1__ */

#if (defined __LIN_CH2_P15__)       /* RLIN3 channel 2(RL78/F15 only) */
#define LIN_CHANNEL0 2              /* LIN channel number */

#define ConfLin_u1gMESNUM          ConfSLin_u1gMESNUM_2
#define ConfLin_u1gSIGNUM          ConfSLin_u1gSIGNUM_2
#define ConfLin_u1gEVENTNUM        ConfSLin_u1gEVENTNUM_2
#define ConfLin_stgMESINFO         ConfSLin_stgMESINFO_2
#define ConfLin_stgSIGNAL          ConfSLin_stgSIGNAL_2
#define ConfLin_stgNODE            ConfSLin_stgNODE_2
#define ConfLin_stgEVENTINFO       ConfSLin_stgEVENTINFO_2
#define ConfLin_stgMesBuf          ConfSLin_stgMesBuf_2
#define ConfLin_u1gEventPid        ConfSLin_u1gEventPid_2
#define ConfLin_u1gMesNoTbl        ConfSLin_u1gMesNoTbl_2
#define ConfLin_u1gMesPid          ConfSLin_u1gMesPid_2

#define ConfSLin_u4gBUSTIMEOUT     ConfSLin_u4gBUSTIMEOUT_2
#define ConfSLin_u2gPERICLOCK      ConfSLin_u2gPERICLOCK_2
#define ConfSLin_u2gTMPERICLOCK    ConfSLin_u2gTMPERICLOCK_2
#define ConfSLin_u2gBAUDRATENORM   ConfSLin_u2gBAUDRATENORM_2

#ifdef __LIN_SIGNAL_32__
#define ConfLin_u4gMesSig          ConfSLin_u4gMesSig_2
#define ConfLin_u4gMesSubSig       ConfSLin_u4gMesSubSig_2
#else
#define ConfLin_u2gMesSig          ConfSLin_u2gMesSig_2
#define ConfLin_u2gMesSubSig       ConfSLin_u2gMesSubSig_2
#endif /* __LIN_SIGNAL_32__ */

#define ApLin_u1gRead8bitsSig      ApSLin_u1gRead8bitsSig_2
#define ApLin_u2gRead16bitsSig     ApSLin_u2gRead16bitsSig_2
#define ApLin_vogWrite8bitsSig     ApSLin_vogWrite8bitsSig_2
#define ApLin_vogWrite16bitsSig    ApSLin_vogWrite16bitsSig_2
#define ApLin_vogReadBytesSig      ApSLin_vogReadBytesSig_2
#define ApLin_vogWriteBytesSig     ApSLin_vogWriteBytesSig_2
#define ApLin_u1gTestFlag          ApSLin_u1gTestFlag_2
#define ApLin_vogClearFlag         ApSLin_vogClearFlag_2
#define ApLin_vogInitIfc           ApSLin_vogInitIfc_2
#define ApLin_u1gConnectIfc        ApSLin_u1gConnectIfc_2
#define ApLin_u1gDisconnectIfc     ApSLin_u1gDisconnectIfc_2
#define ApLin_vogWakeupIfc         ApSLin_vogWakeupIfc_2
#define ApLin_u2gReadStatus        ApSLin_u2gReadStatus_2

#endif /* __LIN_CH2__ */

#endif /* __LIN_78K0R_FX3__, __LIN_RL78_F12__, __LIN_RL78_F13_F14__, __LIN_RL78_F15__ */


/* -------------------------------------------------------------------- */
/* Type definition                                                      */
/* -------------------------------------------------------------------- */

typedef unsigned char  u1;
typedef unsigned short u2;
typedef   signed short s2;
typedef unsigned long  u4;

#define l_bool          u1
#define l_u8            u1
#define l_u16           u2
#define l_irqmask       u1
#define l_signal_handle u1
#define l_flag_handle   u1
#define l_ifc_handle    u1


typedef struct                                       /* Message information                         */
{
    u2 u2MesId;                                      /* Message ID                                  */
    u1 u1Dir;                                        /* 0 is publish, and 1 is subscribe            */
    u1 u1ByteSize;                                   /* Message size                                */
    u1 u1InitPid;                                    /* Initial PID                                 */
    u1 u1SumType;                                    /* Checksum (0 is classic, and 1 is enhanced)  */
    u1 u1InitData[8];                                /* Initial data                                */
} ConfLin_stMesInfo;


typedef struct                                       /* Signal information                          */
{
    u1 u1OffsetByte;                                 /* Byte offset                                 */
    u1 u1OffsetBit;                                  /* Bit offset in the starting byte of signal   */
    u1 u1BitSize;                                    /* Bit size                                    */
#ifdef __LIN_SIGNAL_32__
    u2 u2SigNum;                                     /* Signal number                               */
#else
    u1 u1SigNum;                                     /* Signal number                               */
#endif /* __LIN_SIGNAL_32__ */
} ConfLin_stSignal;


typedef struct                                       /* Node information                            */
{
    u1 u1InitNad;                                    /* Initial NAD                                 */
    u2 u2SupId;                                      /* Supplier ID                                 */
    u2 u2FunId;                                      /* Function ID                                 */
    u1 u1Variant;                                    /* Variant                                     */
    u1 u1ErrRes;                                     /* Signal number of Resonse_Error              */
} ConfLin_stNode;


typedef struct                                       /* Event triggered frame information           */
{
    u2 u2MesId;                                      /* Message ID                                  */
    u1 u1InitEventPid;                               /* Initial PID                                 */
    u1 u1MesNum;                                     /* Associated message buffer number            */
} ConfLin_stEventInfo;


typedef struct                                       /* Message buffer                              */
{
    u1 u1DataBuf[8];                                 /* Data buffer for transmission and reception  */
} ConfLin_stMesBuf;


/* -------------------------------------------------------------------- */
/* Macro definition                                                     */
/* -------------------------------------------------------------------- */

/* l_ifc_read_status        */
#define LD_MASK_LAST_FRAME_PID      ((u2)0xFF00)
#define LD_MASK_SLEEP               ((u2)0x0008)
#define LD_MASK_OVERRUN             ((u2)0x0004)
#define LD_MASK_SUCCESSFUL_TRANSFER ((u2)0x0002)
#define LD_MASK_ERROR_IN_RESPONSE   ((u2)0x0001)
#define LD_MASK_INIT                ((u2)0x0000)

/* l_bool */
#define L_SUCCESS ((u1)0x00)
#define L_FAIL    ((u1)0xFF)

#define CONFLIN_u1gPUBLISH     ((u1)0x00)       /* Publish   */
#define CONFLIN_u1gSUBSCRIBE   ((u1)0x01)       /* Subscribe */

#define CONFLIN_u1gCLASSICSUM  ((u1)0x00)       /* Classic checksum  */
#define CONFLIN_u1gENHANCEDSUM ((u1)0x01)       /* Enhanced checksum */


/* Convert function names with internal coding rule to external interface names */
#if (defined __LIN_78K0R_FX3__)     || \
    (defined __LIN_RL78_F12__)      || \
    (defined __LIN_RL78_F13_F14__)  || \
    (defined __LIN_RL78_F15__)
#define l_ifc_init(ch)                    ApSLin_vogInitIfc_DUMMY(ch)
#define ApSLin_vogInitIfc_DUMMY(ch)       ApSLin_vogInitIfc_##ch()
#define l_ifc_connect(ch)                 ApSLin_u1gConnectIfc_DUMMY(ch)
#define ApSLin_u1gConnectIfc_DUMMY(ch)    ApSLin_u1gConnectIfc_##ch()
#define l_ifc_disconnect(ch)              ApSLin_u1gDisconnectIfc_DUMMY(ch)
#define ApSLin_u1gDisconnectIfc_DUMMY(ch) ApSLin_u1gDisconnectIfc_##ch()
#define l_ifc_wake_up(ch)                 ApSLin_vogWakeupIfc_DUMMY(ch)
#define ApSLin_vogWakeupIfc_DUMMY(ch)     ApSLin_vogWakeupIfc_##ch()
#define l_ifc_read_status(ch)             ApSLin_u2gReadStatus_DUMMY(ch)
#define ApSLin_u2gReadStatus_DUMMY(ch)    ApSLin_u2gReadStatus_##ch()

#define l_sys_init         ApSLin_u1gInitSys

#if (defined __LIN_CH0__)           || \
    (defined __LIN_CH0_P1__)        || \
    (defined __LIN_CH0_P4__)            /* UARTF0, RLIN3 channel 0 */
#define l_bool_rd          ApSLin_u1gRead8bitsSig_0
#define l_u8_rd            ApSLin_u1gRead8bitsSig_0
#define l_u16_rd           ApSLin_u2gRead16bitsSig_0
#define l_bool_wr          ApSLin_vogWrite8bitsSig_0
#define l_u8_wr            ApSLin_vogWrite8bitsSig_0
#define l_u16_wr           ApSLin_vogWrite16bitsSig_0
#define l_bytes_rd         ApSLin_vogReadBytesSig_0
#define l_bytes_wr         ApSLin_vogWriteBytesSig_0
#define l_flg_tst          ApSLin_u1gTestFlag_0
#define l_flg_clr          ApSLin_vogClearFlag_0
#endif /* __LIN_CH0__ */

#if (defined __LIN_CH1_P1__)        || \
    (defined __LIN_CH1_P7__)        || \
    (defined __LIN_CH1_P10__)           /* UARTF1, RLIN3 channel 1 */
#define l_bool_rd          ApSLin_u1gRead8bitsSig_1
#define l_u8_rd            ApSLin_u1gRead8bitsSig_1
#define l_u16_rd           ApSLin_u2gRead16bitsSig_1
#define l_bool_wr          ApSLin_vogWrite8bitsSig_1
#define l_u8_wr            ApSLin_vogWrite8bitsSig_1
#define l_u16_wr           ApSLin_vogWrite16bitsSig_1
#define l_bytes_rd         ApSLin_vogReadBytesSig_1
#define l_bytes_wr         ApSLin_vogWriteBytesSig_1
#define l_flg_tst          ApSLin_u1gTestFlag_1
#define l_flg_clr          ApSLin_vogClearFlag_1
#endif /* __LIN_CH1__ */

#if (defined __LIN_CH2_P15__)           /* RLIN3 channel 2 */
#define l_bool_rd          ApSLin_u1gRead8bitsSig_2
#define l_u8_rd            ApSLin_u1gRead8bitsSig_2
#define l_u16_rd           ApSLin_u2gRead16bitsSig_2
#define l_bool_wr          ApSLin_vogWrite8bitsSig_2
#define l_u8_wr            ApSLin_vogWrite8bitsSig_2
#define l_u16_wr           ApSLin_vogWrite16bitsSig_2
#define l_bytes_rd         ApSLin_vogReadBytesSig_2
#define l_bytes_wr         ApSLin_vogWriteBytesSig_2
#define l_flg_tst          ApSLin_u1gTestFlag_2
#define l_flg_clr          ApSLin_vogClearFlag_2
#endif /* __LIN_CH2__ */

#define l_sys_irq_disable  ConfSLin_vogCallDisableIrq
#define l_sys_irq_restore  ConfSLin_vogCallRestoreIrq
#define l_sys_call_sleep   ConfSLin_vogCallSleepIfc
#define l_sys_call_wake_up ConfSLin_vogCallWakeupIfc
#endif /* __LIN_78K0R_FX3__, __LIN_RL78_F12__, __LIN_RL78_F13_F14__, __LIN_RL78_F15__ */


#if (defined __LIN_KX__)            || \
    (defined __LIN_FX_UART60__)     || \
    (defined __LIN_FX_UART61__)     || \
    (defined __LIN_FX_L__)          || \
    (defined __LIN_FX3_UARTD0__)    || \
    (defined __LIN_FX3_UARTD1__)    || \
    (defined __LIN_FX3_UARTD2__)    || \
    (defined __LIN_FX3_UARTD3_P4__) || \
    (defined __LIN_FX3_UARTD3_P8__) || \
    (defined __LIN_FX3_UARTD4__)    || \
    (defined __LIN_FX3_UARTD5__)    || \
    (defined __LIN_FX3_UARTD6__)    || \
    (defined __LIN_FX3_UARTD7__)
#define l_sys_init         ApLin_u1gInitSys
#define l_bool_rd          ApLin_u1gRead8bitsSig
#define l_u8_rd            ApLin_u1gRead8bitsSig
#define l_u16_rd           ApLin_u2gRead16bitsSig
#define l_bool_wr          ApLin_vogWrite8bitsSig
#define l_u8_wr            ApLin_vogWrite8bitsSig
#define l_u16_wr           ApLin_vogWrite16bitsSig
#define l_bytes_rd         ApLin_vogReadBytesSig
#define l_bytes_wr         ApLin_vogWriteBytesSig
#define l_flg_tst          ApLin_u1gTestFlag
#define l_flg_clr          ApLin_vogClearFlag
#define l_ifc_init         ApLin_vogInitIfc
#define l_ifc_connect      ApLin_u1gConnectIfc
#define l_ifc_disconnect   ApLin_u1gDisconnectIfc
#define l_ifc_wake_up      ApLin_vogWakeupIfc
#define l_ifc_read_status  ApLin_u2gReadStatus
#define l_sys_irq_disable  ConfLin_vogCallDisableIrq
#define l_sys_irq_restore  ConfLin_vogCallRestoreIrq
#define l_sys_call_sleep   ConfLin_vogCallSleepIfc
#define l_sys_call_wake_up ConfLin_vogCallWakeupIfc
#endif /* __LIN_KX__, __LIN_FX_UART60__, __LIN_FX_UART61__, __LIN_FX_L__, __LIN_FX3_UARTDn__ */


/* -------------------------------------------------------------------- */
/* Public functions                                                     */
/* -------------------------------------------------------------------- */

/* APIs that do not have channel number as arguments */
u1   ApLin_u1gInitSys(void);
u1   ApLin_u1gRead8bitsSig(u1);
u2   ApLin_u2gRead16bitsSig(u1);
void ApLin_vogWrite8bitsSig(u1, u1);
void ApLin_vogWrite16bitsSig(u1, u2);
void ApLin_vogReadBytesSig(u1, u1, u1, u1* const);
void ApLin_vogWriteBytesSig(u1, u1, u1, const u1* const);
u1   ApLin_u1gTestFlag(u1);
void ApLin_vogClearFlag(u1);
u1   ConfLin_vogCallDisableIrq(void);
void ConfLin_vogCallRestoreIrq(u1);
void ConfLin_vogCallSleepIfc(u1);
void ConfLin_vogCallWakeupIfc(u1);


/* APIs that have channel number as arguments */
#if (defined __LIN_78K0R_FX3__)     || \
    (defined __LIN_RL78_F12__)      || \
    (defined __LIN_RL78_F13_F14__)  || \
    (defined __LIN_RL78_F15__)
void ApLin_vogInitIfc(void);                                /* LIN interface initialization  */
u1   ApLin_u1gConnectIfc(void);                             /* Connect LIN interface         */
u1   ApLin_u1gDisconnectIfc(void);                          /* Disconnect LIN interface      */
void ApLin_vogWakeupIfc(void);                              /* Wakeup                        */
u2   ApLin_u2gReadStatus(void);                             /* Read and clear LIN status     */
#endif /* __LIN_78K0R_FX3__, __LIN_RL78_F12__, __LIN_RL78_F13_F14__, __LIN_RL78_F15__ */


#if (defined __LIN_KX__)            || \
    (defined __LIN_FX_UART60__)     || \
    (defined __LIN_FX_UART61__)     || \
    (defined __LIN_FX_L__)          || \
    (defined __LIN_FX3_UARTD0__)    || \
    (defined __LIN_FX3_UARTD1__)    || \
    (defined __LIN_FX3_UARTD2__)    || \
    (defined __LIN_FX3_UARTD3_P4__) || \
    (defined __LIN_FX3_UARTD3_P8__) || \
    (defined __LIN_FX3_UARTD4__)    || \
    (defined __LIN_FX3_UARTD5__)    || \
    (defined __LIN_FX3_UARTD6__)    || \
    (defined __LIN_FX3_UARTD7__)
void ApLin_vogInitIfc(u1);
u1   ApLin_u1gConnectIfc(u1);
u1   ApLin_u1gDisconnectIfc(u1);
void ApLin_vogWakeupIfc(u1);
u2   ApLin_u2gReadStatus(u1);
#endif /* __LIN_KX__, __LIN_FX_UART60__, __LIN_FX_UART61__, __LIN_FX_L__, __LIN_FX3_UARTDn__ */


/* -------------------------------------------------------------------- */
/* Public constants                                                     */
/* -------------------------------------------------------------------- */

extern const u1 ConfLin_u1gMESNUM;                          /* Message buffer number                */
extern const u1 ConfLin_u1gSIGNUM;                          /* Signal number                        */
extern const u1 ConfLin_u1gEVENTNUM;                        /* Event triggered frame number         */


#if (defined __LIN_RL78_F13_F14__)  || \
    (defined __LIN_RL78_F15__)
extern const u4 ConfSLin_u4gBUSTIMEOUT;                     /* Bus timeout time(normally 4sec)      */
extern const u2 ConfSLin_u2gPERICLOCK;                      /* Peripheral H/W clock                 */
extern const u2 ConfSLin_u2gTMPERICLOCK;                    /* Peripheral H/W clock for timer       */
extern const u2 ConfSLin_u2gBAUDRATENORM;                   /* Normal LIN baudrate                  */
#else
extern const u2 ConfLin_u2gBUSTIMEOUT;                      /* Bus timeout time(normally 4sec)      */
extern const u1 ConfLin_u1gAPITMPMESNO;
extern const u1 ConfLin_u1gCORETMPMESNO;
extern const u2 ConfLin_u2gTIMEBASE;                        /* Basic 10ms timer count for TM00                      */
extern const u2 ConfLin_u2gRESSPACETIME;                    /* For generation of wait time for response space       */
extern const u2 ConfLin_u2gRESSPACEBASE;                    /* For generation of wait time for response space       */
extern const u2 ConfLin_u2gCRWAKEUP;                        /* Time interval of wake up transmission (CR Reg)       */
extern const u2 ConfLin_u2gTIMEWAKEUP;                      /* Time interval of wake up transmission (Count)        */
extern const u2 ConfLin_u2gCRWAKEUPAF3;                     /* Time interval of third wake up transmission (CR Reg) */
extern const u2 ConfLin_u2gTIMEWAKEUPAF3;                   /* Time interval of third wake up transmission (Count)  */
#endif /* __LIN_RL78_F13_F14__, __LIN_RL78_F15__ */


#if (defined __LIN_78K0R_FX3__)     || \
    (defined __LIN_RL78_F12__)
extern const u2 ConfLin_u2gUFCTL1INIT;                      /* Initial value of UFCTL1 register                     */
#endif /* __LIN_78K0R_FX3__, __LIN_RL78_F12__ */

#if (defined __LIN_KX__)            || \
    (defined __LIN_FX_UART60__)     || \
    (defined __LIN_FX_UART61__)     || \
    (defined __LIN_FX_L__)          || \
    (defined __LIN_FX3_UARTD0__)    || \
    (defined __LIN_FX3_UARTD1__)    || \
    (defined __LIN_FX3_UARTD2__)    || \
    (defined __LIN_FX3_UARTD3_P4__) || \
    (defined __LIN_FX3_UARTD3_P8__) || \
    (defined __LIN_FX3_UARTD4__)    || \
    (defined __LIN_FX3_UARTD5__)    || \
    (defined __LIN_FX3_UARTD6__)    || \
    (defined __LIN_FX3_UARTD7__)
extern const u1 ConfLin_u1gBRGCINIT;                        /* Initial value of BRGC6 register                      */
extern const u1 ConfLin_u1gCKSRINIT;                        /* Initial value of CKSR6 register                      */
#endif /* __LIN_KX__, __LIN_FX_UART60__, __LIN_FX_UART61__, __LIN_FX_L__, __LIN_FX3_UARTDn__ */

#if (defined __LIN_KX__)            || \
    (defined __LIN_FX_UART60__)     || \
    (defined __LIN_FX_UART61__)     || \
    (defined __LIN_FX_L__)
extern const u2 ConfLin_u2gSynchCntMin;                     /* Minimum value of bit width                           */
extern const u2 ConfLin_u2gSynchCntMax;                     /* Maximum value of bit width                           */
#endif /* __LIN_KX__, __LIN_FX_UART60__, __LIN_FX_UART61__, __LIN_FX_L__ */

#if (defined __LIN_FX3_UARTD0__)    || \
    (defined __LIN_FX3_UARTD1__)    || \
    (defined __LIN_FX3_UARTD2__)    || \
    (defined __LIN_FX3_UARTD3_P4__) || \
    (defined __LIN_FX3_UARTD3_P8__) || \
    (defined __LIN_FX3_UARTD4__)    || \
    (defined __LIN_FX3_UARTD5__)    || \
    (defined __LIN_FX3_UARTD6__)    || \
    (defined __LIN_FX3_UARTD7__)
 #if (!defined __LIN_AUTO_BR__) && (defined __LIN_CORRECT_BR__)
extern const u2 ConfLin_u2gSynchCntMin;                     /* Minimum value of bit width.                          */
extern const u2 ConfLin_u2gSynchCntMax;                     /* Maximum value of bit width.                          */
 #endif /* __LIN_AUTO_BR__, __LIN_CORRECT_BR__ */
#endif /* __LIN_FX3_UARTDn__ */

extern const ConfLin_stMesInfo   ConfLin_stgMESINFO[];
extern const ConfLin_stSignal    ConfLin_stgSIGNAL[];
extern const ConfLin_stNode      ConfLin_stgNODE;
extern const ConfLin_stEventInfo ConfLin_stgEVENTINFO[];


/* -------------------------------------------------------------------- */
/* Public variables                                                     */
/* -------------------------------------------------------------------- */

extern       ConfLin_stMesBuf    ConfLin_stgMesBuf[];
extern       u1                  ConfLin_u1gEventPid[];
extern       u1                  ConfLin_u1gMesNoTbl[];
extern       u1                  ConfLin_u1gMesPid[];
#ifdef __LIN_SIGNAL_32__
extern       u4                  ConfLin_u4gMesSig[];
extern       u4                  ConfLin_u4gMesSubSig[];
#else
extern       u2                  ConfLin_u2gMesSig[];
extern       u2                  ConfLin_u2gMesSubSig[];
#endif /* __LIN_SIGNAL_32__ */


#endif /* H_CONFLIN */


/* End of files */
