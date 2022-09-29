/****************************************************************************************
 				            Include File Section 									
*****************************************************************************************/
#include "NM_Cfg.h"
#include "NM.h"
#include "include.h"


/*******************************************************************************
|    Global variables Declaration
|******************************************************************************/
uint16_t uLinsts = 0;
//uint8_t  uPwOnWakeUpCount = 0;
/*code*/
/****************************************************************************************  
| Function name		: vMcuResetSET
| Called by			: vMain_Init_All
| Preconditions		: void
| Input Parameters	: void
| Return Value		: void
| Description		: Be called main task
|             
*****************************************************************************************/
void vMcuResetSET(void) 
{

}
/*******************************************************************************
| Function name		: vSys_SleepWakeup_Init
| Called by			: vMain_Init_All
| Preconditions		: void
| Input Parameters	: void
| Return Value		: void
| Description		: Be called main task
|
|******************************************************************************/
void vSleepWakeupInit(void)
{


}
/*******************************************************************************
| Function name		: vSys_Sleep_Judge
| Called by			: vMLp_Sys_Sleep_Wakeup_Deal
| Preconditions		: void
| Input Parameters	: void
| Return Value		: void
| Description		: Be called main task
|
|******************************************************************************/
 void vSleep_Judge(void)
{

}
/*******************************************************************************
| Function name		: vMLp_Sys_Wakeup_Judge
| Called by			: vSys_Init_Cycle
| Preconditions		: void
| Input Parameters	: void
| Return Value		: void
| Description		: Be called initial task
|
|******************************************************************************/
void vWakeup_Judge(void)
{


}
/****************************************************************************************  
| Function name		: void vMcuOperationMode(EN_MCU_MODE_VALUE vSetValue)
| Called by			: vSys_Init_Cycle
| Preconditions		: void
| Input Parameters	: void
| Return Value		: void
| Description		: Be called initial task
|          
*****************************************************************************************/

   

/*******************************************************************************
| Function name		: vMLp_Sys_Sleep_Wakeup_Deal
| Called by			: vSys_Main_Cycle
| Preconditions		: void
| Input Parameters	: void
| Return Value		: void
| Description		: Be called main task
|
|******************************************************************************/
void vMLp_Sleep_Wakeup_Deal(void)
{
	uint16_t TmpStatus = 0;
	TmpStatus = l_ifc_read_status( LIN_CHANNEL0 );
	uLinsts = TmpStatus;
	if((TmpStatus&LD_MASK_SLEEP )==LD_MASK_SLEEP)
	{
		DI();
    		PM1 |= _00_PMn3_MODE_OUTPUT;
		LOW_Fn_Borard_Lin_Tx_Disble();
		LOW_Fn_Borard_Lin_Slp_Disble();
	}

}
