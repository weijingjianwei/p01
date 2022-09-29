/* -------------------------------------------------------------------- */
/* Copyright(c) 2009-2016 Renesas Electronics Corporation               */
/* -------------------------------------------------------------------- */
/* File name: drvsext.c                                                 */
/* Version:   0.05                                                      */
/* Date:      2016/06/14                                                */
/* Author:    A.Kondo, Shoichiro Sugawara                               */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* History                                                              */
/*   V0.01: 2013.01.18  1st creation.                                   */
/*   V0.02: 2013.05.17  Interrupt name INTPx was changed to INTLINnWUP. */
/*   V0.03: 2013.08.22  Name of LDrvSExt_vogEnaNegEdgeNoInt was changed.*/
/*                      LDrvSExt_vogEnablePosEdge was added.            */
/*                      Name of LDrvSExt_vogEnableNegEdge was changed.  */
/*                      Added operation into LDrvSExt_vogEnableNegEdge. */
/*                      Added operation into LDrvSExt_vogDisableEdge.   */
/*                      Added operation into LDrvSExt_vogVecExt only    */
/*                      FixedBR mode. (If LIN bus was dominant level    */
/*                      when FTS was set, FTS setting is done at rise   */
/*                      edge)                                           */
/*                      The compiled timing of LDrvSExt_vogVecExt was   */
/*                      changed as edge wake-up or FixedBR mode.        */
/*   V0.04: 2015.02.02  Processing corresponding to the same            */
/*                      restriction was deleted by lifting              */
/*                      restrictions of FTS bit set timing of RLIN3.    */
/*                      [#pragma]                                       */
/*                        - Condition was corrected.                    */
/*                      [Public function]                               */
/*                      - LDrvSExt_vogEnableEdgeNoInt                   */
/*                        - Function name was corrected.                */
/*                      - LDrvSExt_vogEnablePosEdge                     */
/*                        - Function was deleted.                       */
/*                      - LDrvSExt_vogEnableEdge                        */
/*                        - Name and processing of the function were    */
/*                          corrected.                                  */
/*                      - LDrvSExt_vogDisableEdge                       */
/*                        - Processing was corrected.                   */
/*                      - LDrvSExt_vogVecEdge                           */
/*                        - Processing was corrected.                   */
/*   V0.05: 2016.06.13  CS+ CC-RL support.                              */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Including header files (must be defined before pragma)               */
/* -------------------------------------------------------------------- */
#include "../dev/device.h"
#include "../conf/confslin_opt.h"

/* -------------------------------------------------------------------- */
/* Channel abstraction macro for static symbols and interrupt functions */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Pragma declaration                                                   */
/* -------------------------------------------------------------------- */
#if ( CONFSLIN_OPT_u1gBUSWKUP_CFG == CONFSLIN_OPT_u1gBUSWKUP_EDGE )

 #if (defined __LIN_CH0_P1__) || (defined __LIN_CH0_P4__)
  #ifdef __CA78K0R__
#pragma Vect    INTLIN0WUP  LDrvSExt_vogVecEdge_0
  #endif /* __CA78K0R__ */
  #ifdef __CCRL__
#pragma interrupt   LDrvSExt_vogVecEdge_0   (vect=INTLIN0WUP)
  #endif /* __CCRL__ */
 #endif /* __LIN_CH0__ */

 #if (defined __LIN_CH1_P1__) || (defined __LIN_CH1_P10__)
  #ifdef __CA78K0R__
#pragma Vect    INTLIN1WUP  LDrvSExt_vogVecEdge_1
  #endif /* __CA78K0R__ */
  #ifdef __CCRL__
#pragma interrupt   LDrvSExt_vogVecEdge_1   (vect=INTLIN1WUP)
  #endif /* __CCRL__ */
 #endif /* __LIN_CH1__ */

#endif /* CONFSLIN_OPT_u1gBUSWKUP_CFG */

/* -------------------------------------------------------------------- */
/* Including header files                                               */
/* -------------------------------------------------------------------- */
#include "../com/common.h"
#include "../conf/confslin.h"
#include "./drvsext.h"
#include "./drvsuart.h"
#include "../lcore/lcorescom.h"
#include "../lcore/lcoreshead.h"
#include "../lcore/lcoresstat.h"

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

/* -------------------------------------------------------------------- */
/* Public functions                                                     */
/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */
/* Description : Initialize the external interrupt driver               */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LDrvSExt_vogInitAll( void )
{

    /* Mask external interrupt */
    DEV_b1gPMK  = 1;

    /* Disable the detection of both edges */
    DEV_b1gEGP  = 0;
    DEV_b1gEGN  = 0;

    /* Clear external interrupt request */
    DEV_b1gPIF  = 0;

    /* Set interrupt priority */
    DEV_b1gPPR0 =  (CONFSLIN_OPT_u1gINTPPR_CFG & 0x01);
    DEV_b1gPPR1 = ((CONFSLIN_OPT_u1gINTPPR_CFG & 0x02) >> 1);

    /* Connect input signal from LIN reception pin to an external interrupt. */
    /* (External interrupt pins are not used) */
    DEV_b1gISC  = 1;
    

    return;
}


/* -------------------------------------------------------------------- */
/* Description : Refresh driver registers of the external interrupt     */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LDrvSExt_vogRefreshReg( void )
{

    /* Refresh interrupt priority setting */
    DEV_b1gPPR0 =  (CONFSLIN_OPT_u1gINTPPR_CFG & 0x01);
    DEV_b1gPPR1 = ((CONFSLIN_OPT_u1gINTPPR_CFG & 0x02) >> 1);

    /* Refresh the connection settings to the LIN reception pin */
    DEV_b1gISC  = 1;


    return;
}


/* -------------------------------------------------------------------- */
/* Description : Enable the falling edge detection function             */
/*               (without interrupt)                                    */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Because this function does not set the interrupt mask, */
/*               execute after LDrvSExt_vogDisableEdge.                 */
/* -------------------------------------------------------------------- */
void
LDrvSExt_vogEnableEdgeNoInt( void )
{
    DEV_b1gEGN  = 1; /* Enable the falling edge of the external interrupt */
    DEV_b1gPIF  = 0; /* Clear the request of the external interrupt       */

    return;
}


#if ( CONFSLIN_OPT_u1gBUSWKUP_CFG == CONFSLIN_OPT_u1gBUSWKUP_EDGE )
/* ------------------------------------------------------------------------------------------ */
/* Description : Enable reception of the falling edge                                         */
/* Parameters  : Nothing                                                                      */
/* Return value: Nothing                                                                      */
/* Misc.       : This function is not used if Wake-up method is the dominant width detection. */
/* ------------------------------------------------------------------------------------------ */
void
LDrvSExt_vogEnableEdge( void )
{
    DEV_b1gEGN  = 1; /* Enable the falling edge of the external interrupt */
    DEV_b1gPIF  = 0; /* Clear the request of the external interrupt       */
    DEV_b1gPMK  = 0; /* Enable the external interrupt                     */

    return;
}
#endif /* CONFSLIN_OPT_u1gBUSWKUP_CFG */


/* -------------------------------------------------------------------- */
/* Description : Disable external interrupts                            */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LDrvSExt_vogDisableEdge( void )
{
    DEV_b1gPMK  = 1; /* Disable the external interrupt                     */
    DEV_b1gEGN  = 0; /* Disable the falling edge of the external interrupt */

    return;
}


/* -------------------------------------------------------------------- */
/* Description : Read the external interrupt request flag               */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
u1
LDrvSExt_u1gReadBusStatus( void )
{
    return (u1)DEV_b1gPIF;
}


/* -------------------------------------------------------------------- */
/* Internal functions                                                   */
/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */
/* Interrupt handler                                                    */
/* -------------------------------------------------------------------- */

#if ( CONFSLIN_OPT_u1gBUSWKUP_CFG == CONFSLIN_OPT_u1gBUSWKUP_EDGE )
/* ------------------------------------------------------------------------------------------ */
/* Description : External interrupt interface for edge detection                              */
/* Parameters  : Nothing                                                                      */
/* Return value: Nothing                                                                      */
/* Misc.       : This function is not used if Wake-up method is the dominant width detection. */
/* ------------------------------------------------------------------------------------------ */
void
LDrvSExt_vogVecEdge( void )
{

    switch( LCoreSCom_u1gFsm ) {

    case LCORESCOM_u1gFSMSLEEP:
    {
        ConfSLin_vogCallWakeupIfc( LIN_CHANNEL );   /* Call the user defined callback             */

        LCoreSCom_vogConnect();                     /* Connect LIN interface                      */
        LCoreSHead_u1gWaitHdrFromDis();             /* Set the initialization header with waiting */

        break;
    }

    default:
    {
        /* Because it is not usually possible to come here,  */
        /* a transition is made to wait for the header as a fail-safe */
        LCoreSHead_vogWaitHdrFromErr( (u2)LCORESSTAT_u2gERRCD_FAILSAFE );

        break;
    }
    } /* switch */


    return;
}
#endif /* CONFSLIN_OPT_u1gBUSWKUP_CFG */

/* End of files */
