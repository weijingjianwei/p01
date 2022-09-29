
/****************************************************************************************
 				            Include File Section 									
*****************************************************************************************/
#include "include.h"

/****************************************************************************************
 				            Pragma Define Section 									
*****************************************************************************************/


/****************************************************************************************
 				            Global Variable Definition Section 									
*****************************************************************************************/

/*
** ===================================================================
**     Method      :  
**     Description :
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
 uint8_t LOW_Fn_OnOffSignalGet(void)
 {
	return(SIGNAL_INPUT_ON_OFF); 
 }
  uint8_t LOW_Fn_ACSignalGet(void)
 {
	return(SIGNAL_INPUT_AC); 
 } 
 uint8_t LOW_Fn_AirPlusSignalGet(void)
 {
	return(SIGNAL_INPUT_AIR_PLUS);
 }
 
 uint8_t LOW_Fn_AirMinusSignalGet(void)
 {
	return(SIGNAL_INPUT_AIR_MINUS);
 }

 uint8_t LOW_Fn_TempPlusSignalGet(void)
 {
	return(SIGNAL_INPUT_TEMP_PLUS); 
 }
  uint8_t LOW_Fn_AutoSignalGet(void)
 {
	return(SIGNAL_INPUT_AUTO); 
 }
 
 uint8_t LOW_Fn_TempMinusSignalGet(void)
 {
	return(SIGNAL_INPUT_TEMP_MINUS);
 }
 uint8_t LOW_Fn_ModeSignalGet(void)
 {
	 return(SIGNAL_INPUT_Mode);
 }
 uint8_t LOW_Fn_AirInnerSignalGet(void)
 {
	 return(SIGNAL_INPUT_AirInner);
 }
 
/****************************************************************************************  
@函数名称       : void HIGHT_Fn_Dio_LINMODESet(uint8_t State)
                         
@参数           : void
  
@返回值         : 

@描述           : 

@最后编辑时间   : 
 
@版本           : v1.0
  
@备注           :	                 
*****************************************************************************************/

void LOW_Fn_Borard_PwrPullCtl_Enable(void)
{
	SIGNAL_OUTPUT_PwrPull_CTRL_HIGH_LEVEL();
}
void LOW_Fn_Borard_PwrPullCtl_Disble(void)
{
	SIGNAL_OUTPUT_PwrPull_CTRL_LOW_LEVEL();
}
void LOW_Fn_Borard_Lin_Slp_Enable(void)
{
	SIGNAL_OUTPUT_LinSlp_CTRL_HIGH_LEVEL();
}
void LOW_Fn_Borard_Lin_Slp_Disble(void)
{
	SIGNAL_OUTPUT_LinSlp_CTRL_LOW_LEVEL();
}
void LOW_Fn_Borard_Lin_Tx_Enable(void)
{
	SIGNAL_OUTPUT_LinTx_CTRL_HIGH_LEVEL();
}
void LOW_Fn_Borard_Lin_Tx_Disble(void)
{
	SIGNAL_OUTPUT_LinTx_CTRL_LOW_LEVEL();
}

void LOW_Fn_Borard_ONOFF_IndCtrl(En_EnIndSgl SetVal)
{
	if(SetVal==Ind_ON)
	{
		IND_ON_OFF_OPEN();
	}else{
		IND_ON_OFF_COLSE();
	}

}

void LOW_Fn_Borard_AC_IndCtrl(En_EnIndSgl SetVal)
{
	if(SetVal==Ind_ON)
	{
		IND_AC_OPEN();
	}else{
		IND_AC_COLSE();
	}

}
void LOW_Fn_Borard_Auto_IndCtrl(En_EnIndSgl SetVal)
{
	if(SetVal==Ind_ON)
	{
		IND_AUTO_OPEN();
	}else{
		IND_AUTO_COLSE();
	}
}
void LOW_Fn_Borard_AirInner_IndCtrl(En_EnIndSgl SetVal)
{
	if(SetVal==Ind_ON)
	{
		IND_AIRINNER_OPEN();
	}else{
		IND_AIRINNER_COLSE();
	}
}





