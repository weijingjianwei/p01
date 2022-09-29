/* -------------------------------------------------------------------- */
/* Copyright(c) 2009 Renesas Electronics Corporation                    */
/* -------------------------------------------------------------------- */
/* File name: lcoresresp.c                                              */
/* Version:   0.02                                                      */
/* Date:      2015/02/02                                                */
/* Author:    A.Kondo, Shoichiro Sugawara                               */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* History                                                              */
/*   V0.01: 2013.01.18  1st creation.                                   */
/*   V0.02: 2015.02.02  Corresponded to RISRA-C                         */
/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */
/* Including header files                                               */
/* -------------------------------------------------------------------- */
#include "../com/common.h"
#include "../conf/confslin.h"
#include "../drv/drvsuart.h"
#include "./lcorescom.h"
#include "./lcoresdiag.h"
#include "./lcoresmes.h"
#include "./lcoresresp.h"
#include "./lcoresstat.h"

/* -------------------------------------------------------------------- */
/* Type definition                                                      */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Macro definition                                                     */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Function prototype declaration                                       */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Constant declaration                                                 */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Variable declaration                                                 */
/* -------------------------------------------------------------------- */
static u1 LCoreSResp_u1sCurPid;  /* PID of the response communication   */

/* -------------------------------------------------------------------- */
/* Public functions                                                     */
/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */
/* Description : Initialize the response module                         */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LCoreSResp_vogInitAll(void)
{

    LCoreSResp_u1sCurPid = (u1)0x00;

    
    return;
}


/* ------------------------------------------------------------------- */
/* Description : Start the response operation                          */
/*               Start process of response transmission and         */
/*               reception corresponding to the PID which are given.   */
/* Parameters  : u1tPid = PID(With parity)                             */
/* Return value: LCORESRESP_u1gIGNORE = Unnecessary send and receive   */
/*               LCORESRESP_u1gRECEIVE = Start the receiving process   */
/*               LCORESRESP_u1gSEND   = Start the transmission process */
/* Misc.       : Nothing                                               */
/* ------------------------------------------------------------------- */
u1
LCoreSResp_u1gStartResponse( u1 u1tPid )
{
    u1 u1tRespDir;


    /* Set the current PID (Common in Diagnostic frame and Normal frame) */
    LCoreSResp_u1sCurPid = u1tPid;


    /* Process the response of diagnostic frame */
    u1tRespDir = LCoreSDiag_u1gStartResponse( u1tPid );
    if( u1tRespDir == (u1)LCORESRESP_u1gIGNORE ) {
        
        /* Process the response of normal frame if there is no response processing of diagnostic frame */
        /* (If there is no update, RespDir is set to IGNORE.) */
        u1tRespDir = LCoreSMes_u1gStartResponse( u1tPid );
        if( u1tRespDir == (u1)LCORESRESP_u1gIGNORE ) {
            
            /* Execute the processing of no response from driver layer if there is no need of sending and receiving response */
            LDrvSUart_vogSetNonResp();
        }
    }
    
    
    /* Update the state of the driver */
    /* (In the case of IGNORE, do not set here because WAITHEADER is configured on the caller) */
    if( u1tRespDir == (u1)LCORESRESP_u1gRECEIVE ) {
        LCoreSCom_u1gFsm = (u1)LCORESCOM_u1gFSMRECDATA;
    }
    else if( u1tRespDir == (u1)LCORESRESP_u1gSEND ) {
        LCoreSCom_u1gFsm = (u1)LCORESCOM_u1gFSMSENDDATA;
    }
    else {
        
        /* No processing */
    }


    return u1tRespDir;
}


/* -------------------------------------------------------------------- */
/* Description : Process of response reception success               */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LCoreSResp_vogFinishRecResp( void )
{

    /* Set the Successful Transfer */
    LCoreSStat_vogSetSuccess( LCoreSResp_u1sCurPid );


    /* Process of the diagnostic frame */
    /* (State may shift to SLEEP in the function) */
    if( LCoreSDiag_u1gFinishRecResp( LCoreSResp_u1sCurPid ) == (u1)FALSE ) {
        
        /* If there is no process of the diagnostic frame, do the noraml frame process */
        LCoreSMes_u1gFinishRecResp( LCoreSResp_u1sCurPid );
        
    }


    return;
}


/* -------------------------------------------------------------------- */
/* Description : Process of response transmission success            */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LCoreSResp_vogFinishSendResp( void )
{

    /* Set the Successful Transfer */
    LCoreSStat_vogSetSuccess( LCoreSResp_u1sCurPid );


    /* Process of the diagnostic frame */
    if( LCoreSDiag_u1gFinishSendResp( LCoreSResp_u1sCurPid ) == (u1)FALSE ) {
        
        /* If there is no process of the diagnostic frame, do the noraml frame process */
        LCoreSMes_u1gFinishSendResp( LCoreSResp_u1sCurPid );
        
    }
    

    return;
}


/* -------------------------------------------------------------------- */
/* Description : Set the response error                                 */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LCoreSResp_vogSetErrorStatus( void )
{

    /* Set the error status using the current PID */
    LCoreSStat_vogSetErrorStatus( LCoreSResp_u1sCurPid );


    return;
}


/* -------------------------------------------------------------------- */
/* Internal functions                                                             */
/* -------------------------------------------------------------------- */


/* End of files */
