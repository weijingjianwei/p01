/* -------------------------------------------------------------------- */
/* Copyright(c) 2009 Renesas Electronics Corporation                    */
/* -------------------------------------------------------------------- */
/* File name: apslinreadstatus.c                                        */
/* Version:   0.01                                                      */
/* Date:      2013/01/18                                                */
/* Author:    A.Kondo                                                   */
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
/* Description : Read and clear LIN status                              */
/* Parameters  : Nothing                                                */
/* Return value: LIN status                                             */
/* Misc.       : This function is an alias of LIN API l_ifc_read_status.*/
/*               This process has the period of suspending interrupts.  */
/* -------------------------------------------------------------------- */
u2
ApSLin_u2gReadStatus(void)
{
    u1 u1tIrq;
    u2 u2tStatus;


    u1tIrq =  ConfSLin_vogCallDisableIrq();
    /*-----------------------*/
    /*   Disable interrupt   */
    /*                       */


    u2tStatus = LCoreSStat_u2gGetStatus();


    /*                       */
    /*   Enable interrupt    */
    /*-----------------------*/
    ConfSLin_vogCallRestoreIrq( u1tIrq );


    return u2tStatus;
}

/* End of files */