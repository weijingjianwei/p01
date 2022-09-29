#ifndef _NM_H_ 
#define _NM_H_ 
              
#include "include.h"

/*******************************************************************************
 *
 * Description:     : Macro Description Section
 *
*******************************************************************************/


/*******************************************************************************
 *
 * Description:     : Mapping Macro Description Section	
 *
*******************************************************************************/


/*******************************************************************************
 *
 * Description:     : Structure Type Declaration Section
 *
*******************************************************************************/

typedef enum {
  SleepMode = 0,
  WakeUpMode 
 } EN_MCU_MODE_VALUE;
/*******************************************************************************
 *
 * Description:     : Global Variable Declaration Section
 *
*******************************************************************************/
/*Globle Variable*/

/*******************************************************************************
 *
 * Description:     : Calibration Variable Declaration Section	
 *
*******************************************************************************/
extern uint16_t uLinsts;
/*******************************************************************************
 *
 * Description:     : Const Table Variable Declaration Section	
 *
*******************************************************************************/


/*******************************************************************************
 *
 * Description:     : Const Variable Declaration Section	
 *
*******************************************************************************/




/*******************************************************************************
 *
 * Description:     : Global Function Prototype Declaration	
 *
*******************************************************************************/  
/*Globle Function*/
extern	void vSleepWakeupInit(void);
extern	void vWakeup_Judge(void);
extern	void vMLp_Sleep_Wakeup_Deal(void);
extern  void vMcuResetSET(void);


#endif