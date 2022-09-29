/* -------------------------------------------------------------------- */
/* Copyright(c) 2009 Renesas Electronics Corporation                    */
/* -------------------------------------------------------------------- */
/* File name: drvssafe.c                                                */
/* Version:   0.01                                                      */
/* Date:      2013/01/18                                                */
/* Author:    A.Kondo                                                   */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* History                                                              */
/*   V0.01: 2013.01.18  1st creation.                                   */
/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */
/* Including header files                                               */
/* -------------------------------------------------------------------- */
#include "../conf/confslin_opt.h"
#include "../dev/device.h"
#include "../com/common.h"
#include "../conf/confslin.h"
#include "./drvssafe.h"
#include "./drvstimer.h"
#include "./drvsuart.h"
#include "./drvsext.h"

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
/* Description : Initialize the safety driver                           */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : No process                                             */
/* -------------------------------------------------------------------- */
void
LDrvSSafe_vogInitAll( void )
{
    return;
}


/* -------------------------------------------------------------------- */
/* Description : Refresh registers driver layer                         */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LDrvSSafe_vogRefreshReg( void )
{

    LDrvSUart_vogRefreshReg();
    LDrvSTimer_vogRefreshReg();
    LDrvSExt_vogRefreshReg();


    return;
}


/* -------------------------------------------------------------------- */
/* Internal functions                                                   */
/* -------------------------------------------------------------------- */
/* End of files */
