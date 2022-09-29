
#include "Switch_Cfg.h"
#include "Switch.h"
#include "include.h"
#include "lcoresmes.h"

/****************************************************************************************
 				            Include File Section 									
*****************************************************************************************/


typedef struct										     
{
	uint8_t		Signal_Time_Count;						
	uint8_t		Signal_Old_Status;						
	uint8_t		Signal_Now_Status;						
	uint16_t	    Signal_Dead_Count;						
	uint8_t      ucAction_Val;                           /*switch value*/
	uint8_t      ucAction_Trig;                          /*trigger flag*/
}Button_Input_Struct;

/****************************************************************************************
 				            Pragma Define Section 									
*****************************************************************************************/

Button_Input_Struct stKey_OnOff_Button;    			
Button_Input_Struct stKey_AirPlus_Button;   			
Button_Input_Struct stKey_AirMinus_Button;     
Button_Input_Struct stKey_AC_Button;     
Button_Input_Struct stKey_Auto_Button; 
Button_Input_Struct stKey_Mode_Button; 
Button_Input_Struct stKey_TempPlus_Button; 
Button_Input_Struct stKey_TempMinus_Button; 
Button_Input_Struct stKey_AirInlet_Button; 

uint8_t ucOnOffTxCnt = 0;
uint8_t ucOnOffNxtTxCnt = 0;
uint8_t ucOnOffUserEn = 0;

uint8_t ucACCTxCnt = 0;
uint8_t ucACCNxtTxCnt = 0;
uint8_t ucACCUserEn = 0;

uint8_t ucModeTxCnt = 0;
uint8_t ucModeNxtTxCnt = 0;
uint8_t ucModeUserEn = 0;

uint8_t ucAutoTxCnt = 0;
uint8_t ucAutoNxtTxCnt = 0;
uint8_t ucAutoUserEn = 0;

uint8_t ucAirInletTxCnt = 0;
uint8_t ucAirInletNxtTxCnt = 0;
uint8_t ucAirInletUserEn = 0;
uint8_t ucAirInletCnt = 0;
uint8_t ucOneBtnIntTxCnt = 0;


uint8_t	ucAirPlusDelayCount = 0;
uint8_t	ucAirPlusShortPressValid =0;
uint8_t	ucAirPlusLongPressValid = 0;
uint8_t	ucAirMinusDelayCount = 0;
uint8_t	ucAirMinusShortPressValid =0;
uint8_t	ucAirMinusLongPressValid = 0;
volatile uint8_t ucAirValue = 0;
uint8_t ucAirValueDelayCount = 0;
uint8_t ucAirSynDelayCout  = 0;
uint8_t ucAirSickCount = 0;

uint8_t	ucTempPlusDelayCount = 0;
uint8_t	ucTempPlusShortPressValid =0;
uint8_t	ucTempPlusLongPressValid = 0;
uint8_t	ucTempMinusDelayCount = 0;
uint8_t	ucTempMinusShortPressValid =0;
uint8_t	ucTempMinusLongPressValid = 0;
volatile uint8_t ucTempValue = 0;
uint8_t ucTempValueDelayCount = 0;
uint8_t ucTempSynDelayCout  = 0;
uint8_t ucTempSickCount = 0;

uint8_t ucAutoSwEnCnt = 0;
uint8_t ucAutoSwCount = 0;
uint8_t ucAutoSwEnStik = 0;

uint8_t ucModeSwEnCnt = 0;
uint8_t ucModeSwCount = 0;
uint8_t ucModeSwEnStik = 0;

#define KEY_OFF            0
#define KEY_ON             1


void vStruct_Message_Init(Button_Input_Struct *pButton_Signal);
void vSignal_Debounce_Deal(Button_Input_Struct *pDebounce_Signal,uint8_t ucDebounce_Port_Value);
/****************************************************************************************
 				            Global Variable Definition Section 									
*****************************************************************************************/

/*
函数功能(Function):按键信号初始化结构体
函数输入(Input):
函数输出(Output):
函数运行时间(Time):运行时间约为2us
其他(Other):
*/
void vStruct_Message_Init(Button_Input_Struct *pButton_Signal)
{
		pButton_Signal->Signal_Time_Count = 0U; 				/* 信号稳定计时变量 */
		pButton_Signal->Signal_Old_Status = 0U; 				/* 上一次端口�?	*/
		pButton_Signal->Signal_Now_Status = 0U; 				/* 去抖后的实际端口�?*/
		pButton_Signal->Signal_Dead_Count = 0U; 				/* 按键卡死时间计算�?*/
	
}

/*
函数功能(Function):初始化按键开关参数函�?
函数输入(Input):
函数输出(Output):
函数运行时间(Time):运行时间约为3us
其他(Other):
*/
void vSwitch_Mess_Init(void)
{
/* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */
	/*行驶控制开关*/

	vStruct_Message_Init(&stKey_OnOff_Button);				/*不同按键的结构体变量	*/
	vStruct_Message_Init(&stKey_AirPlus_Button);
	vStruct_Message_Init(&stKey_AirMinus_Button);
	vStruct_Message_Init(&stKey_AC_Button);
	vStruct_Message_Init(&stKey_Mode_Button);
	vStruct_Message_Init(&stKey_TempPlus_Button);
	vStruct_Message_Init(&stKey_Auto_Button);
	vStruct_Message_Init(&stKey_TempMinus_Button);
	vStruct_Message_Init(&stKey_AirInlet_Button);
/* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */
	
}
/*---------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------*/
/*
函数功能(Function):按键输入检测函�?
函数输入(Input):
函数输出(Output):
函数运行时间(Time):运行时间约为2.75us
其他(Other):
*/
void vSignal_Debounce_Deal(Button_Input_Struct *pDebounce_Signal,uint8_t ucDebounce_Port_Value)
{
		uint8_t Temp_Kv_KeyValue = 0;
		uint8_t Temp_Kv_KeyShortCount = 0;											
		uint16_t Temp_Kv_KeyOverCount = 0;		
		
		Temp_Kv_KeyShortCount=(uint8_t)(KEY_Kc_ShortFilterTime/10U);
	  Temp_Kv_KeyOverCount=(uint16_t)(((uint32_t)KEY_Kc_OverFilterTime)*1000U/10U); 
		
		Temp_Kv_KeyValue=0U ;															/* Port的输入值，存入Temp_Kv_IgnValue*/
																			  
		if(ucDebounce_Port_Value == 0U)													/* 如果输入端口的值不�?				*/
		{
			Temp_Kv_KeyValue=1U;														/* 端口实际值为1						*/
		}																		  
		else																			/* 如果当前按键松开，即可认为按键无卡滞 */
		{
			pDebounce_Signal->Signal_Now_Status=0U ;
			pDebounce_Signal->Signal_Old_Status=0U ;
			pDebounce_Signal->Signal_Dead_Count=0U;
		}
		
		if(pDebounce_Signal->Signal_Time_Count<255U)									/* 如果输入信号的有效时间小�?55,未溢�?*/
		{
			pDebounce_Signal->Signal_Time_Count++;										/* 输入信号的有效时间累�?			*/
		}  
		if(pDebounce_Signal->Signal_Old_Status!=Temp_Kv_KeyValue)						/* 如果端口的实际值不等于上一次的端口�?*/
		{
			pDebounce_Signal->Signal_Time_Count=0U ;									/* 将信号输入计时时间清�?			*/	 
		}
		
		pDebounce_Signal->Signal_Old_Status=Temp_Kv_KeyValue ;							/* 将端口的实际值赋到上一次端口的变量�?*/
		
		if(pDebounce_Signal->Signal_Time_Count>=Temp_Kv_KeyShortCount)					/* 如果输入信号的有效时间大于或等于信号去抖的时�?*/
		{			
			pDebounce_Signal->Signal_Now_Status=pDebounce_Signal->Signal_Old_Status ;	/* 将上一次端口的值赋值到去抖后实际端口信号值变量中 */			
			pDebounce_Signal->Signal_Dead_Count++;										/* 去抖完毕后再增量 */
			if(pDebounce_Signal->Signal_Dead_Count>=Temp_Kv_KeyOverCount)
			{
				pDebounce_Signal->Signal_Dead_Count = Temp_Kv_KeyOverCount;
				pDebounce_Signal->Signal_Now_Status=0U ;
				pDebounce_Signal->Signal_Old_Status=0U ;
			}
	
		}
	}

/*---------------------------------------------------------------------------------------*/

/*
函数功能(Function):开关信号滤波函�?
函数输入(Input):
函数输出(Output):
函数运行时间(Time):运行时间约为
其他(Other):
*/
void vSys_Button_Filter_Deal(void)			      
{
  /* 对不同按键进行滤波处�?*/
	vSignal_Debounce_Deal(&stKey_OnOff_Button, LOW_Fn_OnOffSignalGet());
	vSignal_Debounce_Deal(&stKey_AC_Button, LOW_Fn_ACSignalGet());	
	vSignal_Debounce_Deal(&stKey_Auto_Button, LOW_Fn_AutoSignalGet());
	vSignal_Debounce_Deal(&stKey_Mode_Button, LOW_Fn_ModeSignalGet());
	vSignal_Debounce_Deal(&stKey_AirInlet_Button, LOW_Fn_AirInnerSignalGet());
	vSignal_Debounce_Deal(&stKey_AirPlus_Button, LOW_Fn_AirPlusSignalGet());
	vSignal_Debounce_Deal(&stKey_AirMinus_Button, LOW_Fn_AirMinusSignalGet());
	vSignal_Debounce_Deal(&stKey_TempPlus_Button, LOW_Fn_TempPlusSignalGet());
	vSignal_Debounce_Deal(&stKey_TempMinus_Button, LOW_Fn_TempMinusSignalGet());
	
	/*AC KEY*/
	if(stKey_AC_Button.Signal_Dead_Count >= CuiKEY_Dead_Count)
	{
		OrgCmprSwtErrStsSignalSet(ccsm_Err);
		OrgCmprSwtReqSignalSet(ccsm_NoReq);
	
	}else{
		OrgCmprSwtErrStsSignalSet(ccsm_NoErr);
		if((stKey_AC_Button.Signal_Now_Status!=0U) &&(CMAC_System_Voltage_Mode_A == SSW_Fn_BATT_DetectGet())&&(l_u8_rd(SysPowerMod)== Sys_ON))
		{
			if(ucACCUserEn== FALSE )
			{
				ucACCUserEn = TRUE;
				if(ucACCTxCnt!=0u)
				{
					ucACCNxtTxCnt = CuiKeyTxCnt +1u;
				}else{
					ucACCTxCnt = CuiKeyTxCnt;
				}
			}else{
				ucACCTxCnt = CuiKeyTxCnt;
			}	

		}else
		{
			ucACCUserEn = FALSE;	
			
		}
	}
	
	/*ON/OFF KEY*/
	if(stKey_OnOff_Button.Signal_Dead_Count >= CuiKEY_Dead_Count)
	{
		OrgACOffSwtErrStsSignalSet(ccsm_Err);
		OrgACOffSwtReqSignalSet(ccsm_NoReq);
	
	}else{
		OrgACOffSwtErrStsSignalSet(ccsm_NoErr);
		if((stKey_OnOff_Button.Signal_Now_Status!=0U) &&(CMAC_System_Voltage_Mode_A == SSW_Fn_BATT_DetectGet())&&(l_u8_rd(SysPowerMod)== Sys_ON))
		{
			if(ucOnOffUserEn== FALSE )
			{
				ucOnOffUserEn = TRUE;
				if(ucOnOffTxCnt!=0u)
				{
					ucOnOffNxtTxCnt = CuiKeyTxCnt +1u;
				}else{
					ucOnOffTxCnt = CuiKeyTxCnt;
				}
			}else{
				ucOnOffTxCnt = CuiKeyTxCnt;
			}
		}else
		{
			ucOnOffUserEn = FALSE;			
		}
	}

	/*MODE KEY*/
	if(stKey_Mode_Button.Signal_Dead_Count >= CuiKEY_Dead_Count)
	{
		OrgDrvAirDistribModSwErrorStsSignalSet(ccsm_Err);
		OrgDrvAirDistribModSwReqSignalSet(ccsm_NoReq);
	
	}else{
		OrgDrvAirDistribModSwErrorStsSignalSet(ccsm_NoErr);
		if((stKey_Mode_Button.Signal_Now_Status!=0U) &&(CMAC_System_Voltage_Mode_A == SSW_Fn_BATT_DetectGet())&&(l_u8_rd(SysPowerMod)== Sys_ON))
		{
			if(ucModeUserEn== FALSE )
			{
				ucModeUserEn = TRUE;
				if(ucModeTxCnt!=0u)
				{
					ucModeNxtTxCnt = CuiKeyTxCnt +1u;
				}else{
					ucModeTxCnt = CuiKeyTxCnt;
				}
			}else{
				ucModeTxCnt = CuiKeyTxCnt;
			}
		}else
		{
			ucModeUserEn = FALSE;			
		}
	}
	/*AirInlet KEY*/
	if(stKey_AirInlet_Button.Signal_Dead_Count >= CuiKEY_Dead_Count)
	{
		OrgAirInletSwtErrStsSignalSet(ccsm_Err);
		OrgOneBtnIntCirclnSwtReqErrStsSignalSet(ccsm_Err);
		OrgAirInletSwtReqSignalSet(ccsm_NoReq);
		OrgOneBtnIntCirclnSwtReqSignalSet(ccsm_NoReq);
		ucAirInletCnt = 0;
		ucOneBtnIntTxCnt = 0;
	
	}else{
		OrgAirInletSwtErrStsSignalSet(ccsm_NoErr);
		OrgOneBtnIntCirclnSwtReqErrStsSignalSet(ccsm_NoErr);
		if((stKey_AirInlet_Button.Signal_Now_Status!=0U) &&(CMAC_System_Voltage_Mode_A == SSW_Fn_BATT_DetectGet())&&(l_u8_rd(SysPowerMod)== Sys_ON))
		{
			ucAirInletCnt++;
			if(ucAirInletCnt>= KEY_Kc_LongPresTrm)
			{
				ucAirInletCnt = KEY_Kc_LongPresTrm;
				ucOneBtnIntTxCnt = CuiKeyTxCnt;
				//ucAirInletTxCnt = CuiKeyTxCnt;
				ucAirInletUserEn = FALSE;
			}else{
				ucAirInletUserEn =TRUE;
			}			
			
			
		}else
		{
			ucAirInletCnt = 0;
			if(ucAirInletUserEn== TRUE )
			{
				ucAirInletUserEn = FALSE;
				if(ucAirInletTxCnt!=0u)
				{
					ucAirInletNxtTxCnt = CuiKeyTxCnt +1u;
				}else{
					ucAirInletTxCnt = CuiKeyTxCnt;
				}
			}	
		}
	}
	//AUTO 
	if(stKey_Auto_Button.Signal_Dead_Count >= CuiKEY_Dead_Count)
	{
		OrgAutoModSwtErrStsSignalSet(ccsm_Err);
		OrgAutoModSwtReqSignalSet(ccsm_NoReq);
	
	}else{
		OrgAutoModSwtErrStsSignalSet(ccsm_NoErr);
		if((stKey_Auto_Button.Signal_Now_Status!=0U) &&(CMAC_System_Voltage_Mode_A == SSW_Fn_BATT_DetectGet())&&(l_u8_rd(SysPowerMod)== Sys_ON))
		{
			if(ucAutoUserEn== FALSE )
			{
				ucAutoUserEn = TRUE;
				if(ucAutoTxCnt!=0u)
				{
					ucAutoNxtTxCnt = CuiKeyTxCnt +1u;
				}else{
					ucAutoTxCnt = CuiKeyTxCnt;
				}
			}else{
				ucAutoTxCnt = CuiKeyTxCnt;
			}	

		}else
		{
			ucAutoUserEn = FALSE;	
			
		}
	}

//Air
	 if(stKey_AirPlus_Button.Signal_Dead_Count >= CuiKEY_Dead_Count && stKey_AirMinus_Button.Signal_Dead_Count >= CuiKEY_Dead_Count)
	 {
		ucAirPlusDelayCount = 0;
		ucAirPlusShortPressValid =0;
		ucAirPlusLongPressValid = 0;

		ucAirMinusDelayCount = 0;
		ucAirMinusShortPressValid =0;
		ucAirMinusLongPressValid = 0;
		OrgACRotationSwtErrStsSignalSet(Air_IncDecErr);
	 }else if(stKey_AirPlus_Button.Signal_Dead_Count >= CuiKEY_Dead_Count){
	 
		ucAirPlusDelayCount = 0;
		ucAirPlusShortPressValid =0;
		ucAirPlusLongPressValid = 0;
		OrgACRotationSwtErrStsSignalSet(Air_IncErr);
	 }else if(stKey_AirMinus_Button.Signal_Dead_Count >= CuiKEY_Dead_Count)
	 {
	 	ucAirMinusDelayCount = 0;
		ucAirMinusShortPressValid =0;
		ucAirMinusLongPressValid = 0;
		OrgACRotationSwtErrStsSignalSet(Air_DecErr);
	 }else{
		 OrgACRotationSwtErrStsSignalSet(AirNoErr);
		if((stKey_AirPlus_Button.Signal_Now_Status!=0U) && (stKey_AirMinus_Button.Signal_Now_Status!=0U))
		{
			ucAirPlusDelayCount = 0;
			ucAirPlusShortPressValid =0;
			ucAirPlusLongPressValid = 0;
			ucAirValueDelayCount = 0;

			ucAirMinusDelayCount = 0;
			ucAirMinusShortPressValid =0;
			ucAirMinusLongPressValid = 0;
		 
		}else if((stKey_AirPlus_Button.Signal_Now_Status!=0U) && (CMAC_System_Voltage_Mode_A == SSW_Fn_BATT_DetectGet())&&(l_u8_rd(SysPowerMod)== Sys_ON)/*&& (ucAirSickCount==0)*/)
		{
			ucAirPlusDelayCount++;
			if(ucAirPlusDelayCount >= CuiKey_ShortPressCount)
			{
				ucAirPlusDelayCount = CuiKey_ShortPressCount;
				ucAirPlusLongPressValid = Cuc_All_Valid_Flag;
				ucAirPlusShortPressValid = 0;
				ucAirValueDelayCount++;
			}else{
			 
				ucAirPlusShortPressValid = Cuc_All_Valid_Flag;
				ucAirPlusLongPressValid =0;
			}
		
		}else if((stKey_AirMinus_Button.Signal_Now_Status!=0U) && (CMAC_System_Voltage_Mode_A == SSW_Fn_BATT_DetectGet())&&(l_u8_rd(SysPowerMod)== Sys_ON)/* && (ucAirSickCount==0)*/)
		{
			ucAirMinusDelayCount++;
			if(ucAirMinusDelayCount >= CuiKey_ShortPressCount)
			{
				ucAirMinusDelayCount = CuiKey_ShortPressCount;
				ucAirMinusLongPressValid = Cuc_All_Valid_Flag;
				ucAirMinusShortPressValid = 0;
				ucAirValueDelayCount++;
			}else{
				ucAirMinusShortPressValid = Cuc_All_Valid_Flag;
				ucAirMinusLongPressValid =0;
			}
		}else{	
			ucAirPlusDelayCount = 0	;     //bug01
			ucAirMinusDelayCount = 0;			//bug01
			ucAirPlusLongPressValid = 0;
			ucAirMinusLongPressValid = 0;			
			ucAirValueDelayCount = 0;	
		/*	if(ucAirSickCount !=0)
			{
				ucAirSickCount--;
			}		*/	
			if(ucAirPlusShortPressValid == Cuc_All_Valid_Flag)
			{
				ucAirPlusDelayCount = 0;
				ucAirPlusShortPressValid = 0;
				ucAirSynDelayCout = 2;
//				l_flg_clr_LI0_ACRotationSwtSync_flag();	
				OrgACRotationSwtSyncSignalSet(ccsm_SynOn);
				if(ucAirValue >= 63)
				{
					ucAirValue = 0;
				}else{
					ucAirValue++;	
				}	        			
			}	
			
			if(ucAirMinusShortPressValid == Cuc_All_Valid_Flag)
			{
				ucAirMinusDelayCount = 0;
				ucAirMinusShortPressValid = 0;
				ucAirSynDelayCout = 2;
//				l_flg_clr_LI0_ACRotationSwtSync_flag();	
				OrgACRotationSwtSyncSignalSet(ccsm_SynOn);
				if(ucAirValue == 0)
				{
					ucAirValue = 63;
				}else{
					ucAirValue--;	
				}	       			
			}
		}		
	  if((ucAirValueDelayCount >= CuiKey_LongPressIncCount) && (ucAirPlusLongPressValid == Cuc_All_Valid_Flag))
		{		
			ucAirValueDelayCount=0;
			ucAirSynDelayCout = 2;
//			l_flg_clr_LI0_ACRotationSwtSync_flag();	
			OrgACRotationSwtSyncSignalSet(ccsm_SynOn);
			if(ucAirValue >=63)
			{
				ucAirValue = 0;
			}else{
				ucAirValue++;	
			}				
		}
		if((ucAirValueDelayCount >= CuiKey_LongPressIncCount) && (ucAirMinusLongPressValid == Cuc_All_Valid_Flag))
		{
			ucAirValueDelayCount=0;
			ucAirSynDelayCout = 2;
//			l_flg_clr_LI0_ACRotationSwtSync_flag();	
			OrgACRotationSwtSyncSignalSet(ccsm_SynOn);
			if(ucAirValue == 0)
			{
				ucAirValue = 63;
			}else{
				ucAirValue--;	
			}			
		}	
		OrgACRotationSwtStsSignalSet(ucAirValue);
	 }

//TEMP
if(stKey_TempPlus_Button.Signal_Dead_Count >= CuiKEY_Dead_Count && stKey_TempMinus_Button.Signal_Dead_Count >= CuiKEY_Dead_Count)
	 {
		ucTempPlusDelayCount = 0;
		ucTempPlusShortPressValid =0;
		ucTempPlusLongPressValid = 0;

		ucTempMinusDelayCount = 0;
		ucTempMinusShortPressValid =0;
		ucTempMinusLongPressValid = 0;
		//ucTempSickCount = 6;
		//l_bool_wr_LI0_DrvTempSwSync(FALSE);
		OrgDrvTempSwErrorStsSignalSet(Air_IncDecErr);
	 }else if(stKey_TempPlus_Button.Signal_Dead_Count >= CuiKEY_Dead_Count){
	 
		ucTempPlusDelayCount = 0;
		ucTempPlusShortPressValid =0;
		ucTempPlusLongPressValid = 0;
		//ucTempSickCount = 6;
		//l_bool_wr_LI0_DrvTempSwSync(FALSE);
	  OrgDrvTempSwErrorStsSignalSet(Air_IncErr);
	 }else if(stKey_TempMinus_Button.Signal_Dead_Count >= CuiKEY_Dead_Count)
	 {
	 	ucTempMinusDelayCount = 0;
		ucTempMinusShortPressValid =0;
		ucTempMinusLongPressValid = 0;
		//ucTempSickCount = 6;
		//l_bool_wr_LI0_DrvTempSwSync(FALSE);
		OrgDrvTempSwErrorStsSignalSet(Air_DecErr);
	 }else{
		OrgDrvTempSwErrorStsSignalSet(AirNoErr);
		if((stKey_TempPlus_Button.Signal_Now_Status!=0U) && (stKey_TempMinus_Button.Signal_Now_Status!=0U))
		{
			ucTempPlusDelayCount = 0;
			ucTempPlusShortPressValid =0;
			ucTempPlusLongPressValid = 0;
			ucTempValueDelayCount = 0;

			ucTempMinusDelayCount = 0;
			ucTempMinusShortPressValid =0;
			ucTempMinusLongPressValid = 0;
		 
		}else if((stKey_TempPlus_Button.Signal_Now_Status!=0U) && (CMAC_System_Voltage_Mode_A == SSW_Fn_BATT_DetectGet())&&(l_u8_rd(SysPowerMod)== Sys_ON)/* && (ucTempSickCount ==0)*/)
		{
			ucTempPlusDelayCount++;
			if(ucTempPlusDelayCount >= CuiKey_ShortPressCount)
			{
			ucTempPlusDelayCount = CuiKey_ShortPressCount;
			ucTempPlusLongPressValid = Cuc_All_Valid_Flag;
			ucTempPlusShortPressValid = 0;
			ucTempValueDelayCount++;
		  }else{
			ucTempPlusShortPressValid = Cuc_All_Valid_Flag;
			ucTempPlusLongPressValid =0;
			}
		
		}else if((stKey_TempMinus_Button.Signal_Now_Status!=0U) && (CMAC_System_Voltage_Mode_A == SSW_Fn_BATT_DetectGet())&&(l_u8_rd(SysPowerMod)== Sys_ON)/* && (ucTempSickCount ==0)*/)
		{
			ucTempMinusDelayCount++;
			if(ucTempMinusDelayCount >= CuiKey_ShortPressCount)
			{
			ucTempMinusDelayCount = CuiKey_ShortPressCount;
			ucTempMinusLongPressValid = Cuc_All_Valid_Flag;
			ucTempMinusShortPressValid = 0;
			ucTempValueDelayCount++;
		  }else{
			ucTempMinusShortPressValid = Cuc_All_Valid_Flag;
			ucTempMinusLongPressValid =0;
			}
		}else{	
			ucTempPlusDelayCount = 0;    //bug01
			ucTempMinusDelayCount = 0;		//bug01	
			
			ucTempPlusLongPressValid = 0;
			ucTempMinusLongPressValid = 0;			
			ucTempValueDelayCount = 0;	
			/*if(ucTempSickCount !=0)
			{
				ucTempSickCount--;
			}*/
			if(ucTempPlusShortPressValid == Cuc_All_Valid_Flag)
			{
				ucTempPlusDelayCount = 0;
				ucTempPlusShortPressValid = 0;
				ucTempSynDelayCout = 2;
				OrgDrvTempSwSyncSignalSet(ccsm_SynOn);
				if(ucTempValue >= 63)
				{
					ucTempValue = 0;
				}else{
					ucTempValue++;	
				}	        			
			}			
			if(ucTempMinusShortPressValid == Cuc_All_Valid_Flag)
			{
				ucTempMinusDelayCount = 0;
				ucTempMinusShortPressValid = 0;
				ucTempSynDelayCout = 2;
				OrgDrvTempSwSyncSignalSet(ccsm_SynOn);
				if(ucTempValue == 0)
				{
					ucTempValue = 63;
				}else{
					ucTempValue--;	
				}	       			
			}
		}		
	  if((ucTempValueDelayCount >= CuiKey_LongPressIncCount) && (ucTempPlusLongPressValid == Cuc_All_Valid_Flag))
		{
			ucTempValueDelayCount=0;
			ucTempSynDelayCout = 2;
			OrgDrvTempSwSyncSignalSet(ccsm_SynOn);
			if(ucTempValue >= 63)
			{
				ucTempValue = 0;
			}else{
				ucTempValue++;	
			}				
		}
		if((ucTempValueDelayCount >= CuiKey_LongPressIncCount) && (ucTempMinusLongPressValid == Cuc_All_Valid_Flag))
		{
			ucTempValueDelayCount=0;
			ucTempSynDelayCout = 2;
			OrgDrvTempSwSyncSignalSet(ccsm_SynOn);
			if(ucTempValue == 0)
			{
				ucTempValue = 63;
			}else{
				ucTempValue--;	
			}			
		}			

		OrgDrvTempSwStsSignalSet(ucTempValue);		 	 
 }
   if(l_u8_rd(SysPowerMod)== Sys_OFF)
	{

		OrgDrvTempSwSyncSignalSet(ccsm_SynOff);
		ucTempValue = 0u;
		OrgACRotationSwtSyncSignalSet(ccsm_SynOff);
		ucAirValue = 0u;
	} 
	 
	
	if(LCoreSMes_u1MesTxFinishFlgGet(0x39) == TRUE)
	{
		LCoreSMes_u1MesTxFinishFlgCtl(0x39);

		if(ucOnOffTxCnt !=0u)
		{
			ucOnOffTxCnt--;	
			OrgACOffSwtReqSignalSet(ccsm_Req);
		
		}else{
			if(ucOnOffNxtTxCnt>3u)
			{
				OrgACOffSwtReqSignalSet(ccsm_NoReq);
				ucOnOffNxtTxCnt--;
			}else{
				if(ucOnOffNxtTxCnt!=0)
				{		
					ucOnOffNxtTxCnt--;	
					OrgACOffSwtReqSignalSet(ccsm_Req);		
				}else{
					OrgACOffSwtReqSignalSet(ccsm_NoReq);
				}
			}			
		}
		
		if(ucACCTxCnt !=0u)
		{
			ucACCTxCnt--;	
			OrgCmprSwtReqSignalSet(ccsm_Req);
		
		}else{
			if(ucACCNxtTxCnt>3u)
			{
				OrgCmprSwtReqSignalSet(ccsm_NoReq);
				ucACCNxtTxCnt--;
			}else{
				if(ucACCNxtTxCnt!=0)
				{		
					ucACCNxtTxCnt--;	
					OrgCmprSwtReqSignalSet(ccsm_Req);		
				}else{
					OrgCmprSwtReqSignalSet(ccsm_NoReq);
				}
			}			
		}	

		if(ucModeTxCnt !=0u)
		{
			ucModeTxCnt--;	
			OrgDrvAirDistribModSwReqSignalSet(ccsm_Req);
		
		}else{
			if(ucModeNxtTxCnt>3u)
			{
				OrgDrvAirDistribModSwReqSignalSet(ccsm_NoReq);
				ucModeNxtTxCnt--;
			}else{
				if(ucModeNxtTxCnt!=0)
				{		
					ucModeNxtTxCnt--;	
					OrgDrvAirDistribModSwReqSignalSet(ccsm_Req);		
				}else{
					OrgDrvAirDistribModSwReqSignalSet(ccsm_NoReq);
				}
			}			
		}		
				
		if(ucAutoTxCnt !=0u)
		{
			ucAutoTxCnt--;	
			OrgAutoModSwtReqSignalSet(ccsm_Req);
		
		}else{
			if(ucAutoNxtTxCnt>3u)
			{
				OrgAutoModSwtReqSignalSet(ccsm_NoReq);
				ucAutoNxtTxCnt--;
			}else{
				if(ucAutoNxtTxCnt!=0)
				{		
					ucAutoNxtTxCnt--;	
					OrgAutoModSwtReqSignalSet(ccsm_Req);		
				}else{
					OrgAutoModSwtReqSignalSet(ccsm_NoReq);
				}
			}			
		}	

		if(ucAirInletTxCnt !=0u)
		{
			ucAirInletTxCnt--;	
			OrgAirInletSwtReqSignalSet(ccsm_Req);
		
		}else{
			if(ucAirInletNxtTxCnt>3u)
			{
				OrgAirInletSwtReqSignalSet(ccsm_NoReq);
				ucAirInletNxtTxCnt--;
			}else{
				if(ucAirInletNxtTxCnt!=0)
				{		
					ucAirInletNxtTxCnt--;	
					OrgAirInletSwtReqSignalSet(ccsm_Req);		
				}else{
					OrgAirInletSwtReqSignalSet(ccsm_NoReq);
				}
			}			
		}

		if(ucOneBtnIntTxCnt!=0)
		{
			ucOneBtnIntTxCnt--;
			OrgOneBtnIntCirclnSwtReqSignalSet(ccsm_Req);
		}else{
			OrgOneBtnIntCirclnSwtReqSignalSet(ccsm_NoReq);
		}


		
	}
	

}

