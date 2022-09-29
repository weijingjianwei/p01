/* -------------------------------------------------------------------- */
/* Copyright(c) 2009-2016 Renesas Electronics Corporation               */
/* -------------------------------------------------------------------- */
/* File name: drvstimer.c                                               */
/* Version:   0.04                                                      */
/* Date:      2016/06/14                                                */
/* Author:    A.Kondo, Shoichiro Sugawara                               */
/* -------------------------------------------------------------------- */
/* History                                                              */
/*   V0.01: 2013.01.18  1st creation.                                   */
/*   V0.02: 2013.08.22  The operation for WAITHEADERDOM and WAKEUPDOM   */
/*                      was added into LDrvSTimer_vogVecCompare.        */
/*   V0.03: 2015.02.02  Processing corresponding to the same            */
/*                      restriction was deleted by lifting              */
/*                      restrictions of FTS bit set timing of RLIN3.    */
/*                      Macro definition and function name of the       */
/*                      [Public function]                               */
/*                      - LDrvSTimer_vogVecCompare                      */
/*                        - Processing was corrected.                   */
/*   V0.04: 2016.06.14  CS+ CC-RL support.                              */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Including header files (must be defined before pragma)               */
/* -------------------------------------------------------------------- */
#include "../conf/confslin_opt.h"
#include "../dev/device.h"

/* -------------------------------------------------------------------- */
/* Channel abstraction macro for static symbols and interrupt functions */
/* -------------------------------------------------------------------- */
#if (defined __LIN_CH0_P1__) || (defined __LIN_CH0_P4__)
#define LDrvSTimer_u2sTimeOut               LDrvSTimer_u2sTimeOut_0
#endif /* __LIN_CH0__ */

#if (defined __LIN_CH1_P1__) || (defined __LIN_CH1_P10__)
#define LDrvSTimer_u2sTimeOut               LDrvSTimer_u2sTimeOut_1
#endif /* __LIN_CH1__ */

/* -------------------------------------------------------------------- */
/* Pragma declaration                                                   */
/* -------------------------------------------------------------------- */
#if (defined __LIN_CH0_P1__) || (defined __LIN_CH0_P4__)
 #if   (CONFSLIN_OPT_u1gTMUNIT_CFG == CONFSLIN_OPT_u1gTMUNIT_UNIT0)

  #ifdef __CA78K0R__
   #if   (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH0)
#pragma Vect    INTTM00        LDrvSTimer_vogVecCompare_0
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH1)
#pragma Vect    INTTM01        LDrvSTimer_vogVecCompare_0
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH2)
#pragma Vect    INTTM02        LDrvSTimer_vogVecCompare_0
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH3)
#pragma Vect    INTTM03        LDrvSTimer_vogVecCompare_0
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH4)
#pragma Vect    INTTM04        LDrvSTimer_vogVecCompare_0
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH5)
#pragma Vect    INTTM05        LDrvSTimer_vogVecCompare_0
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH6)
#pragma Vect    INTTM06        LDrvSTimer_vogVecCompare_0
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH7)
#pragma Vect    INTTM07        LDrvSTimer_vogVecCompare_0
   #endif /* CONFSLIN_OPT_u1gTMCH_CFG */
  #endif /* __CA78K0R__ */

  #ifdef __CCRL__
   #if   (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH0)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM00)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH1)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM01)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH2)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM02)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH3)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM03)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH4)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM04)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH5)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM05)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH6)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM06)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH7)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM07)
   #endif /* CONFSLIN_OPT_u1gTMCH_CFG */
  #endif /* __CCRL__ */

 #elif (CONFSLIN_OPT_u1gTMUNIT_CFG == CONFSLIN_OPT_u1gTMUNIT_UNIT1)

  #ifdef __CA78K0R__
   #if   (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH0)
#pragma Vect    INTTM10        LDrvSTimer_vogVecCompare_0
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH1)
#pragma Vect    INTTM11        LDrvSTimer_vogVecCompare_0
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH2)
#pragma Vect    INTTM12        LDrvSTimer_vogVecCompare_0
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH3)
#pragma Vect    INTTM13        LDrvSTimer_vogVecCompare_0
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH4)
#pragma Vect    INTTM14        LDrvSTimer_vogVecCompare_0
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH5)
#pragma Vect    INTTM15        LDrvSTimer_vogVecCompare_0
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH6)
#pragma Vect    INTTM16        LDrvSTimer_vogVecCompare_0
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH7)
#pragma Vect    INTTM17        LDrvSTimer_vogVecCompare_0
   #endif /* CONFSLIN_OPT_u1gTMCH_CFG */
  #endif /* __CA78K0R__ */

  #ifdef __CCRL__
   #if   (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH0)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM10)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH1)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM11)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH2)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM12)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH3)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM13)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH4)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM14)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH5)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM15)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH6)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM16)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH7)
#pragma interrupt   LDrvSTimer_vogVecCompare_0      (vect=INTTM17)
   #endif /* CONFSLIN_OPT_u1gTMCH_CFG */
  #endif /* __CCRL__ */

 #endif /* CONFSLIN_OPT_u1gTMUNIT_CFG */
#endif /* __LIN_CH0__ */

#if (defined __LIN_CH1_P1__) || (defined __LIN_CH1_P10__)
 #if   (CONFSLIN_OPT_u1gTMUNIT_CFG == CONFSLIN_OPT_u1gTMUNIT_UNIT0)

  #ifdef __CA78K0R__
   #if   (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH0)
#pragma Vect    INTTM00        LDrvSTimer_vogVecCompare_1
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH1)
#pragma Vect    INTTM01        LDrvSTimer_vogVecCompare_1
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH2)
#pragma Vect    INTTM02        LDrvSTimer_vogVecCompare_1
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH3)
#pragma Vect    INTTM03        LDrvSTimer_vogVecCompare_1
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH4)
#pragma Vect    INTTM04        LDrvSTimer_vogVecCompare_1
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH5)
#pragma Vect    INTTM05        LDrvSTimer_vogVecCompare_1
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH6)
#pragma Vect    INTTM06        LDrvSTimer_vogVecCompare_1
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH7)
#pragma Vect    INTTM07        LDrvSTimer_vogVecCompare_1
   #endif /* CONFSLIN_OPT_u1gTMCH_CFG */
  #endif /* __CA78K0R__ */

  #ifdef __CCRL__
   #if   (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH0)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM00)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH1)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM01)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH2)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM02)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH3)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM03)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH4)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM04)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH5)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM05)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH6)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM06)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH7)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM07)
   #endif /* CONFSLIN_OPT_u1gTMCH_CFG */
  #endif /* __CCRL__ */

 #elif (CONFSLIN_OPT_u1gTMUNIT_CFG == CONFSLIN_OPT_u1gTMUNIT_UNIT1)

  #ifdef __CA78K0R__
   #if   (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH0)
#pragma Vect    INTTM10        LDrvSTimer_vogVecCompare_1
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH1)
#pragma Vect    INTTM11        LDrvSTimer_vogVecCompare_1
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH2)
#pragma Vect    INTTM12        LDrvSTimer_vogVecCompare_1
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH3)
#pragma Vect    INTTM13        LDrvSTimer_vogVecCompare_1
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH4)
#pragma Vect    INTTM14        LDrvSTimer_vogVecCompare_1
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH5)
#pragma Vect    INTTM15        LDrvSTimer_vogVecCompare_1
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH6)
#pragma Vect    INTTM16        LDrvSTimer_vogVecCompare_1
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH7)
#pragma Vect    INTTM17        LDrvSTimer_vogVecCompare_1
   #endif /* CONFSLIN_OPT_u1gTMCH_CFG */
  #endif /* __CA78K0R__ */

  #ifdef __CCRL__
   #if   (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH0)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM10)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH1)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM11)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH2)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM12)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH3)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM13)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH4)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM14)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH5)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM15)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH6)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM16)
   #elif (CONFSLIN_OPT_u1gTMCH_CFG == CONFSLIN_OPT_u1gTMCH_CH7)
#pragma interrupt   LDrvSTimer_vogVecCompare_1      (vect=INTTM17)
   #endif /* CONFSLIN_OPT_u1gTMCH_CFG */
  #endif /* __CCRL__ */

 #endif /* CONFSLIN_OPT_u1gTMUNIT_CFG */
#endif /* __LIN_CH1__ */

/* -------------------------------------------------------------------- */
/* Including header files                                               */
/* -------------------------------------------------------------------- */
#include "../com/common.h"
#include "../conf/confslin.h"
#include "./drvsext.h"
#include "./drvstimer.h"
#include "./drvsuart.h"
#include "../lcore/lcorescom.h"
#include "../lcore/lcoreshead.h"
#include "../lcore/lcoressleep.h"
#include "../lcore/lcoresstat.h"
#include "../lcore/lcoresresp.h"

/* -------------------------------------------------------------------- */
/* Type definition                                                      */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Macro definition                                                     */
/* -------------------------------------------------------------------- */
#define LDRVSTIMER_u2sTIMERBASE     (0xFFFF)

/* -------------------------------------------------------------------- */
/* Function prototype declaration                                       */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Constant declaration                                                 */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Variable declaration                                                 */
/* -------------------------------------------------------------------- */
static u2 LDrvSTimer_u2sTimeOut;        /* Time-out count [Time]        */


/* -------------------------------------------------------------------- */
/* Public functions                                                     */
/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */
/* Description : Initialize the timer driver                            */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LDrvSTimer_vogInitAll( void )
{

    /* Set the interrupt priority */
    DEV_b1gINTVLTMPR0 =  ((u1)CONFSLIN_OPT_u1gINTTMPR_CFG & (u1)0x01);
    DEV_b1gINTVLTMPR1 = (((u1)CONFSLIN_OPT_u1gINTTMPR_CFG & (u1)0x02) >> 1);


    /* (Supplement) */
    /* Considering stopping the TAU clock supply while the driver is sleeping,  */
    /* this function does not access the register of TAU macros.                */
    /* (Because this function is not called upon wake-up)                       */

    
    return;
}


/* -------------------------------------------------------------------- */
/* Description : Refresh timer driver register                          */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LDrvSTimer_vogRefreshReg( void )
{

    /* Set the interrupt priority */
    DEV_b1gINTVLTMPR0 =  ((u1)CONFSLIN_OPT_u1gINTTMPR_CFG & (u1)0x01);
    DEV_b1gINTVLTMPR1 = (((u1)CONFSLIN_OPT_u1gINTTMPR_CFG & (u1)0x02) >> 1);


    return;
}


/* -------------------------------------------------------------------- */
/* Description : Start the timer clock supply and initialize            */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : This function does not start the timer count.          */
/* -------------------------------------------------------------------- */
void
LDrvSTimer_vogPowerOnAndInit( void )
{

    /* (Supplement) */
    /* Because there is a possibility that the user is using the other channels, */
    /* clock control should not be set here.                                     */
    /* This function process only start clock supplying,                         */
    /* because it is hard for the user to set the clock ON in advance.           */
    if( DEV_b1gINTVLTAUEN == 0 ) {
        DEV_b1gINTVLTAUEN = 1;
    }


    /* Stop timer */
    LDrvSTimer_vogStopTimeout();
    LDrvSTimer_u2sTimeOut = (u2)0;
    

    return;
}


/* -------------------------------------------------------------------- */
/* Description : Start the interval timer                               */
/* Parameters  : u4TimeoutMs : Interval time(LSB:[ms])                  */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LDrvSTimer_vogStartTimeout( u4 u4TimeoutMs )
{
    u4 u4tCount;
    
    
    LDrvSTimer_vogStopTimeout();
    

    /* (Supplement) */
    /* The timer clock divider value setting and the timer mode setting below are processed in this function also as a refreshing. */
    /* (Because state of the timer is unknown in the execution timing of LDrvSTimer_vogRefreshReg,                                 */
    /* refreshing the function of 2 above is impossible.)                                                                          */


    /* Set the timer clock divider value */
#if   (CONFSLIN_OPT_u2gTMCLKSEL_CFG == CONFSLIN_OPT_u2gTMCLKSEL_SEL0)
    DEV_u2gINTVLTPS = (DEV_u2gINTVLTPS & (u2)0xFFF0) |  (u2)CONFSLIN_OPT_u2gTMCLKDIV_CFG;
#elif (CONFSLIN_OPT_u2gTMCLKSEL_CFG == CONFSLIN_OPT_u2gTMCLKSEL_SEL1)
    DEV_u2gINTVLTPS = (DEV_u2gINTVLTPS & (u2)0xFF0F) | ((u2)CONFSLIN_OPT_u2gTMCLKDIV_CFG << 4);
#endif

    /* Set the timer mode */
    /* (disable external interruption, single channel, 16-bit timer,          */
    /* software trigger, interval timer, no interruption when timer starting) */
    DEV_u2gINTVLTMR = (u2)CONFSLIN_OPT_u2gTMCLKSEL_CFG;


    /* If the set time is 0 [ms], the timer does not start */
    if( u4TimeoutMs > (u4)0 ) {
        
        u4tCount = (((u4)ConfSLin_u2gTMPERICLOCK * (u4)10 * u4TimeoutMs) / 
                    ((u4)1 << (u4)CONFSLIN_OPT_u2gTMCLKDIV_CFG));
        
        
        /* Timer laps */
        if( u4tCount <= (u2)LDRVSTIMER_u2sTIMERBASE ) {
            
            LDrvSTimer_u2sTimeOut = (u2)1;  /* (Because it is compared with 0 after -1 within timer interrupt) */
            DEV_u2gINTVLTDR       = (u2)u4tCount;
        }
        else {
            
            /* 0x8000 is a flag of the first cycle of timer */
            LDrvSTimer_u2sTimeOut = (u2)((u4tCount / ((u4)LDRVSTIMER_u2sTIMERBASE + (u4)1)) + (u4)1) | (u2)0x8000;
            DEV_u2gINTVLTDR       = (u2)(u4tCount & (u4)LDRVSTIMER_u2sTIMERBASE);
        }


        DEV_b1gINTVLTMIF = 0;       /* Clear interrupt flag of timer.             */
        DEV_b1gINTVLTMMK = 0;       /* Enable timer interrupt.                    */

        DEV_b1gINTVLTS = 1;         /* Start interval timer.                      */
    }


    return;
}


/* -------------------------------------------------------------------- */
/* Description : Stop counting time out                                 */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LDrvSTimer_vogStopTimeout( void )
{

    DEV_b1gINTVLTMMK = 1;           /* Disable the timer interrupt */
    DEV_b1gINTVLTT   = 1;           /* Stop the timer              */


    return;
}


/* -------------------------------------------------------------------- */
/* Internal functions                                                   */
/* -------------------------------------------------------------------- */

/* -------------------------------------------------------------------- */
/* Interrupt handler                                                    */
/* -------------------------------------------------------------------- */
/* -------------------------------------------------------------------- */
/* Description : Timer comparing interrupt interface                    */
/* Parameters  : Nothing                                                */
/* Return value: Nothing                                                */
/* Misc.       : Nothing                                                */
/* -------------------------------------------------------------------- */
void
LDrvSTimer_vogVecCompare( void )
{

    /* In case a flag of the 1st cycle of timer is set. */
    if( (LDrvSTimer_u2sTimeOut & (u2)0x8000) != (u2)0 )
    {
        /* Set TDR for 2nd cycle of timer.                           */
        /* Set timer base value to operate the same mode as free run timer. */
        DEV_u2gINTVLTDR  = (u2)LDRVSTIMER_u2sTIMERBASE;

        LDrvSTimer_u2sTimeOut &= (u2)0x7FFF;    /* Clear a flag of the 1st cycle of timer. */
    }
    else
    {
        LDrvSTimer_u2sTimeOut--;                /* Decrement timeout count. */

        if( LDrvSTimer_u2sTimeOut == (u2)0 )
        {
            switch( LCoreSCom_u1gFsm ) {
            case LCORESCOM_u1gFSMWAKEUP:
            {
                /* If wake-up pulse is transmitting, retry that. */
                LCoreSSleep_vogRtrySendWakeup();
                
                break;
            }

            case LCORESCOM_u1gFSMWAITHEADER:
            {
                /* Bus timeout */
                LCoreSSleep_vogSleep();

                break;
            }

            case LCORESCOM_u1gFSMRECDATA:
            case LCORESCOM_u1gFSMSENDDATA:
            {
                /* Record the error code if the bus times out while waiting on response */
                /* (Time-out is not specified in LIN2.0, but because of the notification to the user) */
                LCoreSStat_vogSetErrorCode( LCORESSTAT_u2gERRCD_RESPTIMEOUT );
                LCoreSResp_vogSetErrorStatus();
                LCoreSSleep_vogSleep();

                break;
            }

            default:
            {
                /* Come here if SENDWAKEUP, SLEEP, DORMANT (As Fail-safe) */
                LCoreSHead_vogWaitHdrFromErr( (u2)LCORESSTAT_u2gERRCD_FAILSAFE );

                break;
            }
            }
        }
    }


    return;
}

/* End of files */
