/* -------------------------------------------------------------------- */
/* Copyright(c) 2009 Renesas Electronics Corporation                    */
/* -------------------------------------------------------------------- */
/* File name: lcoresdiag.c                                              */
/* Version:   0.02                                                      */
/* Date:      2015/02/02                                                */
/* Author:    A.Kondo, Shoichiro Sugawara                               */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* History                                                              */
/*   V0.01: 2013.01.18  1st creation.                                   */
/*   V0.02: 2015.02.02  Corresponded to RISRA-C                         */
/* -------------------------------------------------------------------- */
/* ---------------------------------------------------------------------*/
/* The addition of LIN channel number in function name and variable name*/
/* ---------------------------------------------------------------------*/
#if (defined __LIN_CH0_P1__) || (defined __LIN_CH0_P4__)        /* Use LIN channel 0 */
#define LCoreSDiag_vosAnalysisPdu   LCoreSDiag_vosAnalysisPdu_0
#define LCoreSDiag_vosSetReadById   LCoreSDiag_vosSetReadById_0
#define LCoreSDiag_u1sAssignId      LCoreSDiag_u1sAssignId_0
#define LCoreSDiag_u1sDataBuf       LCoreSDiag_u1sDataBuf_0
#define LCoreSDiag_u1sSignalFlag    LCoreSDiag_u1sSignalFlag_0
#define LCoreSDiag_u1sNad           LCoreSDiag_u1sNad_0
#endif /* __LIN_CH0__ */

#if (defined __LIN_CH1_P1__) || (defined __LIN_CH1_P10__)       /* Use LIN channel 1 */
#define LCoreSDiag_vosAnalysisPdu   LCoreSDiag_vosAnalysisPdu_1
#define LCoreSDiag_vosSetReadById   LCoreSDiag_vosSetReadById_1
#define LCoreSDiag_u1sAssignId      LCoreSDiag_u1sAssignId_1
#define LCoreSDiag_u1sDataBuf       LCoreSDiag_u1sDataBuf_1
#define LCoreSDiag_u1sSignalFlag    LCoreSDiag_u1sSignalFlag_1
#define LCoreSDiag_u1sNad           LCoreSDiag_u1sNad_1
#endif /* __LIN_CH1__ */


/* -------------------------------------------------------------------- */
/* Including header files                                               */
/* -------------------------------------------------------------------- */
#include "../com/common.h"
#include "../conf/confslin.h"
#include "../drv/drvsuart.h"
#include "./lcoresdiag.h"
#include "./lcoresresp.h"   /* Just to use response direction */
#include "./lcoressleep.h"
/* -------------------------------------------------------------------- */
/* Type definition                                                      */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Macro definition                                                     */
/* -------------------------------------------------------------------- */
#define LCORESDIAG_u1sNONUPDATED        (0x00)
#define LCORESDIAG_u1sUPDATED           (0x01)

#define LCORESDIAG_u1sASSIGNFRAMEID     (0xB1)      /* SID definition */
#define LCORESDIAG_u1sREADBYIDREQ       (0xB2)
#define LCORESDIAG_u1sNADWILDCARD       (0x7F)
                                                        
#define LCORESDIAG_u1sCustomREADBYIDREQ       (0x22)    /*add Sevicer SID       zbj*/
#define LCORESDIAG_u1sCustomWRITEIDREQ        (0x2E)

#define LCORESDIAG_u1sMASTERREQUESTID   (0x3C)      /* Master request ID(Including parity) */
#define LCORESDIAG_u1sSLAVERESPONSEID   (0x7D)      /* Slave response ID(Including parity) */

#define LCORESDIAG_uSwLen               25u


const u1 uSwCode[LCORESDIAG_uSwLen] = {'5','-','0','6','4','-','1','1','2','7','x','x','_','S','W','2','2','0','4','1','3','V','2','.','0'};
/* -------------------------------------------------------------------- */
/* Function prototype declaration                                       */
/* -------------------------------------------------------------------- */
static void LCoreSDiag_vosAnalysisPdu( void );      /* Analysis process PDU          */
static void LCoreSDiag_vosSetReadById( u1 );        /* Reading process by Identifier */
static u1   LCoreSDiag_u1sAssignId( u2, u1 );       /* Allocation process PID        */

/* -------------------------------------------------------------------- */
/* Constant declaration                                                 */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Variable declaration                                                 */
/* -------------------------------------------------------------------- */
static u1 LCoreSDiag_u1sDataBuf[8];                 /* Buffer for sending diagnostic response */
static u1 LCoreSDiag_u1sSignalFlag;                 /* Diagnosis update flag                  */
static u1 LCoreSDiag_u1sNad;                        /* NAD                                    */

/* -------------------------------------------------------------------- */
/* Public functions                                                     */

static u1  LCoreSDiag_u1ResDataLen;
static u1  LCoreSDiag_u1CFval;

/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */
/* Description : Initialize this diagnostic driver                      */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */
void
LCoreSDiag_vogInitAll( void )
{
    u1 i;

    LCoreSDiag_u1sSignalFlag = (u1)LCORESDIAG_u1sNONUPDATED;

    for(i = (u1)0; i < (u1)8; i++)
    {
        LCoreSDiag_u1sDataBuf[i] = (u1)0x00;
    }

    LCoreSDiag_u1sNad = ConfSLin_stgNODE.u1InitNad;

    return;
}


/* -------------------------------------------------------------------- */
/* Description : Start sending and receiving response.                  */
/* Parameters  : u1tPid = PID                                           */
/* Return value: LCORESRESP_u1gIGNORE  = Not need to do diag action     */
/*               LCORESRESP_u1gRECEIVE = Start reception process        */
/*               LCORESRESP_u1gSEND    = Start transmission process     */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
u1
LCoreSDiag_u1gStartResponse( u1 u1tPid )
{
    u1 u1tRespDir;
     
    
    u1tRespDir = (u1)LCORESRESP_u1gIGNORE;
    
    if( u1tPid == (u1)LCORESDIAG_u1sMASTERREQUESTID ) {
        
        /* If the request is from master, receive unconditionally */
        LDrvSUart_vogRecvResponse( 8, (u1)CONFSLIN_u1gCLASSICSUM );
        u1tRespDir = (u1)LCORESRESP_u1gRECEIVE;
    }
    else if( u1tPid == (u1)LCORESDIAG_u1sSLAVERESPONSEID ) {
        
        /* If the request is from slave, send only if the diagnostic information has been updated */
        if( LCoreSDiag_u1sSignalFlag == (u1)LCORESDIAG_u1sUPDATED ) {
            
            LDrvSUart_vogSetBuf( &LCoreSDiag_u1sDataBuf[0], 8 );
            LDrvSUart_vogSendResponse( 8, (u1)CONFSLIN_u1gCLASSICSUM );
            u1tRespDir = (u1)LCORESRESP_u1gSEND;
        }
    }
    else {
        
        /* No processing */
    }


    return u1tRespDir;
}


/* -------------------------------------------------------------------- */
/* Description : Process of when response is successfully received      */
/* Parameters  : u1tPid = PID                                           */
/* Return value: TRUE  = There is process as a diagnostic module        */
/*               FALSE = There is no process as a diagnostic module     */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
u1
LCoreSDiag_u1gFinishRecResp( u1 u1tPid )
{
    u1 u1tResult;
    

    if( u1tPid == (u1)LCORESDIAG_u1sMASTERREQUESTID ) {
        
        /* Copy 8 bytes from the data buffer of RLIN3 */
        /* (In order to reduce processing time, copy only if PID matches) */
        LDrvSUart_vogGetBuf( &LCoreSDiag_u1sDataBuf[0], (u1)8 );
        if( LCoreSDiag_u1sDataBuf[0] == (u1)0x00 ) {
            
            /* Master request frame(Request SLEEP) */
            LCoreSSleep_vogSleep();
        }
        else {
            
            /* Master request frame(Request except SLEEP) */
            LCoreSDiag_vosAnalysisPdu();    /* Diag processing */
        }
        
        /* Returns TRUE if there is process as a diagnostic module */
        u1tResult = (u1)TRUE;
    }
    else {

        /* Returns FALSE if there is no process as a diagnostic module */
        u1tResult = (u1)FALSE;
    }
    
    
    return u1tResult;
}


/* -------------------------------------------------------------------- */
/* Description : Process of when response is response successfully sent */
/* Parameters  : u1tPid = PID                                           */
/* Return value: TRUE  = There is process as a diagnostic module        */
/*               FALSE = There is no process as a diagnostic module     */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
u1
LCoreSDiag_u1gFinishSendResp( u1 u1tPid )
{
    u1 u1tResult;
    
    
    if( u1tPid == (u1)LCORESDIAG_u1sSLAVERESPONSEID ) {
        
        /* Clear the diagnosis update flag because slave response transmission is completed, */
        if(LCoreSDiag_u1ResDataLen >= 25)
        {
            LCoreSDiag_u1sSignalFlag = (u1)LCORESDIAG_u1sNONUPDATED;       
        }else{
            LCoreSDiag_u1sDataBuf[0] = LCoreSDiag_u1sNad;
            LCoreSDiag_u1sDataBuf[1] = LCoreSDiag_u1CFval;
            LCoreSDiag_u1sDataBuf[2] = uSwCode[LCoreSDiag_u1ResDataLen];
            LCoreSDiag_u1sDataBuf[3] = uSwCode[LCoreSDiag_u1ResDataLen+1];
            LCoreSDiag_u1sDataBuf[4] = uSwCode[LCoreSDiag_u1ResDataLen+2];
            LCoreSDiag_u1sDataBuf[5] = uSwCode[LCoreSDiag_u1ResDataLen+3];
            LCoreSDiag_u1sDataBuf[6] = uSwCode[LCoreSDiag_u1ResDataLen+4];
            LCoreSDiag_u1sDataBuf[7] = uSwCode[LCoreSDiag_u1ResDataLen+5];
            LCoreSDiag_u1ResDataLen += 6;
            LCoreSDiag_u1CFval++;
        }
        //LCoreSDiag_u1sSignalFlag = (u1)LCORESDIAG_u1sNONUPDATED;       
        
        u1tResult = (u1)TRUE;
    }
    else {
        u1tResult = (u1)FALSE;
    }
    
    
    return u1tResult;
}


/* -------------------------------------------------------------------- */
/* Internal functions                                                   */
/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */
/* Description : PDU frame analysis, the diagnostic process             */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : The receive data must be stored in                     */
/*               LCoreSDiag_u1sDataBuf in advance. If you want to       */
/*               enable this function for other diagnostic frame,       */
/*               please fix this function.                              */
/* -------------------------------------------------------------------- */
static void
LCoreSDiag_vosAnalysisPdu( void )
{
    u1 u1tRet;

    /* Check whether message is compatible with PDU supported by this driver */
    if( ( (LCoreSDiag_u1sDataBuf[0] == LCoreSDiag_u1sNad) ||             /* Byte0 : NAD or Wild card  */
          (LCoreSDiag_u1sDataBuf[0] == (u1)LCORESDIAG_u1sNADWILDCARD) ) &&
          (LCoreSDiag_u1sDataBuf[1] == (u1)0x06) ) {                     /* Byte1 : PCI is only compatible with 6 */


        if( LCoreSDiag_u1sDataBuf[2] == (u1)LCORESDIAG_u1sREADBYIDREQ ) { /* Byte2:SID                      */

            if ( (( (u2)LCoreSDiag_u1sDataBuf[4] | (u2)((u2)LCoreSDiag_u1sDataBuf[5] << 8) ) == ConfSLin_stgNODE.u2SupId)
              && (( (u2)LCoreSDiag_u1sDataBuf[6] | (u2)((u2)LCoreSDiag_u1sDataBuf[7] << 8) ) == ConfSLin_stgNODE.u2FunId) ) {

                /************************/
                /* Read By ID           */

                LCoreSDiag_vosSetReadById( LCoreSDiag_u1sDataBuf[3] );  /* Read identifier(Byte3)          */
                LCoreSDiag_u1sSignalFlag = (u1)LCORESDIAG_u1sUPDATED;   /* Update the diagnostic flags       */
            }
        }
        else if( LCoreSDiag_u1sDataBuf[2] == (u1)LCORESDIAG_u1sASSIGNFRAMEID )
        {
            if(( (u2)LCoreSDiag_u1sDataBuf[3] | (u2)((u2)LCoreSDiag_u1sDataBuf[4] << 8) ) == ConfSLin_stgNODE.u2SupId ) {

                /************************/
                /* Assign Frame ID      */

                u1tRet = LCoreSDiag_u1sAssignId(( (u2)LCoreSDiag_u1sDataBuf[5] | (u2)((u2)LCoreSDiag_u1sDataBuf[6] << 8) ), 
                                                  LCoreSDiag_u1sDataBuf[7]);  /* Command assignment ID      */
                if( u1tRet != (u1)OK )
                {
                    /* Because there is no response for Assign frame identifier, */
                    /* process for the allocation failure is not necessary.      */
                    ;
                }
            }
        }       
        else
        {
            /* If there is no the case in the above conditions, exit doing nothing */

        }
    }else{
            if(LCoreSDiag_u1sDataBuf[2] == LCORESDIAG_u1sCustomREADBYIDREQ)    /*Add Server SID 0x22   zbj*/
            {
                if( (LCoreSDiag_u1sDataBuf[3] == 0xFB) && (LCoreSDiag_u1sDataBuf[4] == 0x01))
                {                   
                    LCoreSDiag_u1sDataBuf[0] = LCoreSDiag_u1sNad;
                    LCoreSDiag_u1sDataBuf[1] = 0x10;
                    LCoreSDiag_u1sDataBuf[2] = LCORESDIAG_uSwLen+3;
                    LCoreSDiag_u1sDataBuf[3] = LCORESDIAG_u1sCustomREADBYIDREQ+0x40;
                    LCoreSDiag_u1sDataBuf[4] = 0xFB;
                    LCoreSDiag_u1sDataBuf[5] = 0x01;
                    LCoreSDiag_u1sDataBuf[6] = uSwCode[0];
                    LCoreSDiag_u1sDataBuf[7] = uSwCode[1];                    
                    LCoreSDiag_u1ResDataLen = 2;
                    LCoreSDiag_u1CFval = 0x21;
                    
                    LCoreSDiag_u1sSignalFlag = (u1)LCORESDIAG_u1sUPDATED;   /* Update the diagnostic flags       */

                }

            }
    }

    return;
}


/* -------------------------------------------------------------------- */
/* Description : Read by identifier                                     */
/* Parameters  : u1tId = identifier                                     */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
static void
LCoreSDiag_vosSetReadById( u1 u1tId )
{
    if( u1tId == (u1)0x00 )                                               /* Read LIN product identification   */
    {                                                                    
        LCoreSDiag_u1sDataBuf[1] = (u1)0x06;                              /* Set the PCI                       */
        LCoreSDiag_u1sDataBuf[2] = (u1)0xf2;                              /* Set the RSID                      */
        LCoreSDiag_u1sDataBuf[3] = (u1)ConfSLin_stgNODE.u2SupId;          /* Set the supplier ID (LSB)         */
        LCoreSDiag_u1sDataBuf[4] = (u1)(ConfSLin_stgNODE.u2SupId >> 8);   /* Set the supplier ID (MSB)         */
        LCoreSDiag_u1sDataBuf[5] = (u1)ConfSLin_stgNODE.u2FunId;          /* Set the function ID (LSB)         */
        LCoreSDiag_u1sDataBuf[6] = (u1)(ConfSLin_stgNODE.u2FunId >> 8);   /* Set the function ID (MSB)         */
        LCoreSDiag_u1sDataBuf[7] = ConfSLin_stgNODE.u1Variant;            /* Set the variant ID                */
    }
    else                                                                  /* Set the negative response in the other conditions */
    {
        LCoreSDiag_u1sDataBuf[1] = (u1)0x03;                              /* Set the PCI  */
        LCoreSDiag_u1sDataBuf[2] = (u1)0x7f;                              /* Set the RSID */
        LCoreSDiag_u1sDataBuf[3] = (u1)0xb2;                              /* Set D1       */
        LCoreSDiag_u1sDataBuf[4] = (u1)0x12;                              /* Set D2       */
        LCoreSDiag_u1sDataBuf[5] = (u1)0xff;                              /* Set D3       */
        LCoreSDiag_u1sDataBuf[6] = (u1)0xff;                              /* Set D4       */
        LCoreSDiag_u1sDataBuf[7] = (u1)0xff;                              /* Set D5       */
    }

    LCoreSDiag_u1sDataBuf[0] = LCoreSDiag_u1sNad;                         /* Set the NAD */

    return;
}

/* -------------------------------------------------------------------- */
/* Description : Assign PID                                             */
/* Parameters  : u2tMessageId = message ID                              */
/*               u1tNewPid    = new PID                                 */
/* Return value: Process result                                         */
/*                OK    = OK                                            */
/*                ERROR = Error                                         */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
static u1
LCoreSDiag_u1sAssignId( u2 u2tMessageId, u1 u1tNewPid )
{
    u1 i;
    u1 u1tResult;

    u1tResult = (u1)ERROR;

    for(i = (u1)0; i < ConfSLin_u1gMESNUM; i++)
    {
        if( ConfSLin_stgMESINFO[i].u2MesId == u2tMessageId )         /* Compare the message ID */
        {
            ConfSLin_u1gMesPid[i] = u1tNewPid;                       /* Set the specified PID as a new PID */
            u1tResult = (u1)OK;

            break;                                                   /* Break to make the process light */
        }
    }

    for(i = (u1)0; i < ConfSLin_u1gEVENTNUM; i++)                    /* Event */
    {
        if( ConfSLin_stgEVENTINFO[i].u2MesId == u2tMessageId )       /* Compare the message ID */
        {
            ConfSLin_u1gEventPid[i] = u1tNewPid;                     /* Set the specified PID as a new PID */
            u1tResult = (u1)OK;                                      /* The break statement is not used because some event triggered frame PID can be in one node */
        }
    }

    return u1tResult;
}

/* End of files */
