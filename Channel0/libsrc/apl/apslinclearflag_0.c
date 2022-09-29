/* -------------------------------------------------------------------- */
/* Copyright(c) 2009 Renesas Electronics Corporation                    */
/* -------------------------------------------------------------------- */
/* File name:   apslinclearflag.c                                       */
/* Version:     0.01                                                    */
/* Date:        2013/01/18                                              */
/* Author:      A.Kondo                                                 */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* History                                                              */
/*   V0.01: 2013.01.18  1st creation.                                   */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Pragma declaration                                                   */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Including header files                                               */
/* -------------------------------------------------------------------- */
#include "../com/common.h"
#include "../conf/confslin.h"
#include "./apslin.h"
#include "../lcore/lcoresmes.h"

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
/* Description : Clear a signal update flag                             */
/* Parameters  : u1tSigName = signal name                               */
/* Return value: Nothing                                                */
/* Misc.       : It is another name for LIN API l_clr_flg.              */
/*               This process has the period of suspending interrupts.  */
/* -------------------------------------------------------------------- */
void
ApSLin_vogClearFlag( u1 u1tSigName )
{
    u1 u1tIrq;

    if( u1tSigName < ConfSLin_u1gSIGNUM ) {

        u1tIrq =  ConfSLin_vogCallDisableIrq();
        /*-----------------------*/
        /*   Disable interrupt   */
        /*                       */


        LCoreSMes_vogClrSigFlag( u1tSigName );


        /*                       */
        /*   Enable interrupt    */
        /*-----------------------*/
        ConfSLin_vogCallRestoreIrq( u1tIrq );

    }

    return;
}

/* End of files */
