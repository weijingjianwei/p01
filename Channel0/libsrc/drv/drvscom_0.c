/* -------------------------------------------------------------------- */
/* Copyright(c) 2009 Renesas Electronics Corporation                    */
/* -------------------------------------------------------------------- */
/* File name: drvscom.c                                                 */
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
#include "../com/common.h"
#include "../conf/confslin.h"
#include "./drvscom.h"

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
/* Description : Memory copy                                            */
/* Parameters  : pu1tDst  = destination pointer for copy                */
/*             : pu1tSrc  = source pointer for copy                     */
/*             : u1tSize  = copy size                                   */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
#ifndef __LIN_MEMCOPY_ASM__
void
LDrvSCom_vogCopyBuf( u1 *pu1tDst, const u1* pu1tSrc, u1 u1tSize )
{
    u1 u1tDataIndex;

    if( (pu1tDst != (u1*)0) && (pu1tSrc != (u1*)0) ) {

        for( u1tDataIndex = (u1)0; u1tDataIndex < u1tSize; u1tDataIndex++ ) {
            (*pu1tDst) = (*pu1tSrc);
            pu1tDst++;
            pu1tSrc++;
        }
    }

    return;
}
#endif /* __LIN_MEMCOPY_ASM__ */

/* End of files */
