#ifndef _SWITCH_H_
#define _SWITCH_H_
/*******************************************************************************
 *
 * Description:     : Macro Description Section
 *
*******************************************************************************/
#include "r_cg_macrodriver.h"

/*******************************************************************************
 *
 * Description:     : Structure Type Declaration Section
 *
*******************************************************************************/


/****************************************************************************************
 				            Global Variable Definition Section 									
*****************************************************************************************/

extern volatile uint8_t ucAirValue;
extern volatile uint8_t ucTempValue;



/*******************************************************************************
 *
 * Description:     : Global Function Prototype Declaration	
 *
*******************************************************************************/

extern	void vSwitch_Mess_Init(void);						/* 按键初始化函数	*/
extern	void vSys_Button_Filter_Deal(void);				/* 开关信号滤波函数	*/
extern  uint8_t SwitchDriveModeSignalGet(void);
extern  void vSwitchDriveModeSignalSet(uint8_t Value);
#endif
