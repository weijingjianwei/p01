/* -------------------------------------------------------------------- */
/* Copyright(c) 2009 Renesas Electronics Corporation                    */
/* -------------------------------------------------------------------- */
/* File name: lcoressleep.c                                             */
/* Version:   0.04                                                      */
/* Date:      2015/02/02                                                */
/* Author:    A.Kondo, Shoichiro Sugawara                               */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* History                                                              */
/*   V0.01: 2013.01.18  1st creation.                                   */
/*   V0.02: 2013.04.08  Fix how to reset RLIN3                          */
/*   V0.03: 2013.08.22  [LCoreSSleep_vogSleep]                          */
/*                       Cases for WAITHEADERDOM and WAKEUPDOM were     */
/*                       added.                                         */
/*                      [LCoreSSleep_vogWakeup]                         */
/*                       DisableEdge was deleted.                       */
/*                       (Not needed due to after sending wakeup)       */
/*                       If LIN bus is dominant level at setting FTS,   */
/*                       this function returns with enabling detecting  */
/*                       rising edge.                                   */
/*                      [LCoreSSleep_vogSendWakeup]                     */
/*                       Verbose DisableEdge in BUSWAKEUP_EDGE was      */
/*                       deleted.                                       */
/*                      [LCoreSSleep_vogRtrySendWakeup]                 */
/*                       Renamed due to MISRA-C.                        */
/*                       WAITHEADERDOM and WAKEUPDOM were considered.   */
/*   V0.04: 2015.02.02  Processing corresponding to the same            */
/*                      restriction was deleted by lifting              */
/*                      restrictions of FTS bit set timing of RLIN3.    */
/*                      [Public function]                               */
/*                      - LCoreSSleep_vogSleep                          */
/*                        - The processing divided into Auto-BR mode    */
/*                          and Fixed-BR mode was deleted.              */
/*                        - Part where LDrvSExt_vogEnableNegEdge        */
/*                          is called is corrected in                   */
/*                          LDrvSExt_vogEnableEdge.                     */
/*                        - Comment was corrected.                      */
/*                      - LCoreSSleep_vogWakeup                         */
/*                        - Processing of fixed-BR mode was deleted.    */
/*                      - LCoreSSleep_vogRtrySendWakeup                 */
/*                        - The processing divided into Auto-BR mode    */
/*                          and Fixed-BR mode was deleted.              */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Channel abstraction macro for static symbols and interrupt functions */
/* -------------------------------------------------------------------- */
#if (defined __LIN_CH0_P1__) || (defined __LIN_CH0_P4__)
#define LCoreSSleep_u1sWakeupRetryCnt   LCoreSSleep_u1sWakeupRetryCnt_0
#endif /* __LIN_CH0__ */

#if (defined __LIN_CH1_P1__) || (defined __LIN_CH1_P10__)
#define LCoreSSleep_u1sWakeupRetryCnt   LCoreSSleep_u1sWakeupRetryCnt_1
#endif /* __LIN_CH1__ */

/* -------------------------------------------------------------------- */
/* Including header files                                               */
/* -------------------------------------------------------------------- */
#include "../com/common.h"
#include "../conf/confslin.h"
#include "../conf/confslin_opt.h"
#include "../drv/drvsext.h"
#include "../drv/drvstimer.h"
#include "../drv/drvsuart.h"
#include "../drv/drvssafe.h"
#include "./lcorescom.h"
#include "./lcoreshead.h"
#include "./lcoressleep.h"
#include "./lcoresstat.h"

/* -------------------------------------------------------------------- */
/* Type definition                                                      */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Macro definition                                                     */
/* -------------------------------------------------------------------- */
#define LCORESSLEEP_u1sWAKEUPMAXRETRY (3) /* Maximum number of retries  */

/* -------------------------------------------------------------------- */
/* Function prototype declaration                                       */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Constant declaration                                                 */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Variable declaration                                                 */
/* -------------------------------------------------------------------- */
static u1 LCoreSSleep_u1sWakeupRetryCnt;         /* Retry count [number of times] */

/* -------------------------------------------------------------------- */
/* Public functions                                                     */
/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */
/* Description : Initialize the sleep module                            */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LCoreSSleep_vogInitAll( void )
{
    LCoreSSleep_u1sWakeupRetryCnt = (u1)0;

    return;
}


/* -------------------------------------------------------------------- */
/* Description : Change the state to SLEEP                              */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : This function must be processed during the state of    */
/*               waiting for header.                                    */
/* -------------------------------------------------------------------- */
void
LCoreSSleep_vogSleep( void )
{   
    u1 u1tTrResult;


    if( (LCoreSCom_u1gFsm == (u1)LCORESCOM_u1gFSMWAITHEADER) ||
        (LCoreSCom_u1gFsm == (u1)LCORESCOM_u1gFSMRECDATA)    ||
        (LCoreSCom_u1gFsm == (u1)LCORESCOM_u1gFSMSENDDATA)   ||
        (LCoreSCom_u1gFsm == (u1)LCORESCOM_u1gFSMWAKEUP) ) {

        LDrvSTimer_vogStopTimeout();

        /* If the process below - Sleep -> Send wake-up pulse -> ... - is repeated, */
        /* there is no register refresh timing. So, it is done here.                */
        /* (Refreshing in SendWakeup is redundant)                                  */
        LDrvSSafe_vogRefreshReg();


#if ( CONFSLIN_OPT_u1gBUSWKUP_CFG == CONFSLIN_OPT_u1gBUSWKUP_EDGE )
        /*------------------------------------------*/
        /* Wake-up method : Falling-edge detection  */

        /* Disconnect from the bus and allow edge detection */
        LCoreSCom_u1gDisconnect();
        LDrvSExt_vogEnableEdge();
        
        u1tTrResult = (u1)OK;

#elif ( CONFSLIN_OPT_u1gBUSWKUP_CFG == CONFSLIN_OPT_u1gBUSWKUP_WIDTH )
        /*-------------------------------------------*/
        /* Wake-up method : Dominant width detection */
        
        /* Reset the UART driver and start the dominant width detection */
        LCoreSCom_u1gDisconnect();
        LCoreSCom_vogConnect();
        u1tTrResult = LDrvSUart_u1gEnableWakeupRx();
        
#endif /* CONFSLIN_OPT_u1gBUSWKUP_CFG */


        if( u1tTrResult == (u1)LDRVSUART_u1gERROR_TRTIMEOUT ) {

            /* If the transition state of the UART driver times out, shift to DORMANT */
            LCoreSStat_vogSetErrorCode( (u2)LCORESSTAT_u2gERRCD_TRTOWKUPRX );
            LCoreSCom_u1gDisconnect();
        }
        else {
            
            /*  State transition success */
            LCoreSStat_vogSetSleepFlag();

            LCoreSCom_u1gFsm = (u1)LCORESCOM_u1gFSMSLEEP;   /* State transition of driver */
            ConfSLin_vogCallSleepIfc( LIN_CHANNEL );        /* User call out              */
        }
    }


    return;
}


/* -------------------------------------------------------------------- */
/* Description : Shift the state from wake-up pulse transmitting        */
/*               to header waiting                                      */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LCoreSSleep_vogWakeup( void )
{
    u1 u1tTrResult;


    if( LCoreSCom_u1gFsm == (u1)LCORESCOM_u1gFSMSENDWAKEUP ) {

        /* RLIN3 reset is needed by following reasons.                          */
        /* -     __LIN_HW_AUTO_BR__ : In order to transit auto baudrate mode.   */
        /* - not __LIN_HW_AUTO_BR__ : In order to set LBRP.                     */
        u1tTrResult = LDrvSUart_u1gDisable();
        
        if( u1tTrResult == (u1)LDRVSUART_u1gERROR_TRTIMEOUT ) {

            /* If go to reset is timed out, disconnect from bus. */
            LCoreSStat_vogSetErrorCode( (u2)LCORESSTAT_u2gERRCD_TRTORESET );
            LCoreSCom_u1gDisconnect();
        }
        else {

            u1tTrResult = LDrvSUart_u1gEnableNormal();

            if( u1tTrResult != (u1)LDRVSUART_u1gERROR_TRTIMEOUT ) {

                /* Except RLIN3 state transition timed out. Start timer to mesure until next request. */
                if( LCoreSSleep_u1sWakeupRetryCnt < ((u1)LCORESSLEEP_u1sWAKEUPMAXRETRY - (u1)1) ) {
                    LDrvSTimer_vogStartTimeout( (u4)CONFSLIN_OPT_u4gWAKEUPINTVL ); /* 1st and 2nd time */
                }
                else {
                    LDrvSTimer_vogStartTimeout( (u4)CONFSLIN_OPT_u4gWAKEUPINTVL3 ); /* 3rd time */
                }

                LDrvSExt_vogEnableEdgeNoInt();
                LCoreSCom_u1gFsm = (u1)LCORESCOM_u1gFSMWAKEUP;
            }
            else {
                
                /* RLIN3 state transition timed out. */
                LCoreSCom_u1gDisconnect();
                LCoreSStat_vogSetErrorCode( (u2)LCORESSTAT_u2gERRCD_TRTONORM );
            }
        }
    }
    
    
    return;

}



/* -------------------------------------------------------------------- */
/* Description : Start sending wake-up pulse                            */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LCoreSSleep_vogSendWakeup(void)
{
    u1 u1tTrResult;


    if( LCoreSCom_u1gFsm == (u1)LCORESCOM_u1gFSMSLEEP ) {

#if ( CONFSLIN_OPT_u1gBUSWKUP_CFG == CONFSLIN_OPT_u1gBUSWKUP_EDGE )
        /*------------------------------------------*/
        /* Wake-up method : Falling-edge detection  */

        LCoreSCom_vogConnect();
        
        u1tTrResult = (u1)OK;

#elif ( CONFSLIN_OPT_u1gBUSWKUP_CFG == CONFSLIN_OPT_u1gBUSWKUP_WIDTH )
        /*-------------------------------------------*/
        /* Wake-up method : Dominant width detection */

        /* Transmitting and receiving direction switching must be processed during FTS = 0, so once reset */
        u1tTrResult = LDrvSUart_u1gDisable();

#endif /* CONFSLIN_OPT_u1gBUSWKUP_CFG */


        if( u1tTrResult == (u1)LDRVSUART_u1gERROR_TRTIMEOUT ) {
            
            /* If the state transition of the UART driver times out, shift to DORMANT */
            LCoreSStat_vogSetErrorCode( (u2)LCORESSTAT_u2gERRCD_TRTORESET );
            LCoreSCom_u1gDisconnect();
        }
        else {

            LCoreSSleep_u1sWakeupRetryCnt = 0;

            /* Send a first wake-up pulse */
            if( LDrvSUart_u1gEnableWakeupTx() == (u1)LDRVSUART_u1gERROR_TRTIMEOUT ) {

                /* If the transition state of the UART driver has timed out to DORMANT */
                LCoreSStat_vogSetErrorCode( (u2)LCORESSTAT_u2gERRCD_TRTOWKUPTX );
                LCoreSCom_u1gDisconnect();
            }
            else {
                
                LDrvSTimer_vogStartTimeout( ConfSLin_u4gBUSTIMEOUT );
                
                /* Update the state of the driver */
                LCoreSCom_u1gFsm = (u1)LCORESCOM_u1gFSMSENDWAKEUP;
            }
        }
    }


    return;
}


/* -------------------------------------------------------------------- */
/* Description : Retry sending wake-up pulse                            */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : This function must be processed during the state of    */
/*               waiting for header.                                    */
/* -------------------------------------------------------------------- */
void
LCoreSSleep_vogRtrySendWakeup( void )
{

    if(  LCoreSCom_u1gFsm == (u1)LCORESCOM_u1gFSMWAKEUP ) {

        if( LCoreSSleep_u1sWakeupRetryCnt < (u1)LCORESSLEEP_u1sWAKEUPMAXRETRY ) {

            /* In WAKEUPDOM, ReadBusStatus() is 1 by rising edge detection. */
            /* In this case, wakeup request is absolutely sent because can't wait header in RLIN3 reset mode. */
            if( LDrvSExt_u1gReadBusStatus() == (u1)0 ) {
                
                /* Reset the UART driver and start sending wake-up pulse */
                LCoreSCom_u1gDisconnect();
                LCoreSCom_vogConnect();

                if( LDrvSUart_u1gEnableWakeupTx() != (u1)LDRVSUART_u1gERROR_TRTIMEOUT ) {
                    
                    LCoreSSleep_u1sWakeupRetryCnt++;
                    LDrvSTimer_vogStartTimeout( ConfSLin_u4gBUSTIMEOUT );
                
                    /* Update the state of the driver */
                    LCoreSCom_u1gFsm = (u1)LCORESCOM_u1gFSMSENDWAKEUP;
                }
                else {
                    /* If the transition state of the UART driver has timed out to DORMANT */
                    LCoreSStat_vogSetErrorCode( (u2)LCORESSTAT_u2gERRCD_TRTOWKUPTX );
                    LCoreSCom_u1gDisconnect();
                }

                /* (Supplement) */
                /* If the transition state of the UART driver times out in SendWakeupCore,              */
                /* transmission success interrupt does not occur because the wake-up pulse is not sent. */
                /* Therefore the state can not shift to WAKEUP, and remains DORMANT(clock OFF).         */
                /* (Do not shift to SLEEP)                                                              */

            }
            else {
                
                /* Shift state to waiting for reception complete of the header, if there is a edge(perhaps header) to the bus in advance */
                LCoreSHead_vogWaitHeader();
            }
        }
        else {

            /* If it is after third retry, sleep again */
            LCoreSSleep_vogSleep();
        }
    }


    return;
}


/* -------------------------------------------------------------------- */
/* Internal functions                                                   */
/* -------------------------------------------------------------------- */

/* End of files */
