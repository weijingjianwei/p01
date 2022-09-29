
/****************************************************************************************
 				            Include File Section 									
*****************************************************************************************/
#include "Output_Cfg.h" 
#include "Output.h"
#include "include.h"


/****************************************************************************************
 				            Pragma Define Section 									
*****************************************************************************************/

static uint8_t bEnUser = 0xff;                    /* Enable/Disable device by user */

uint16_t uLmpPwmVal = 0;
/****************************************************************************************
 				            Global Variable Definition Section 									
*****************************************************************************************/

/*code*/
void vIndicatorLightInit (void)
{
	uLmpPwmVal = Cal_Ind_Off;

}

void vIndicatorLightingDeal(void)
{
	if(CMAC_System_Voltage_Mode_A == SSW_Fn_BATT_DetectGet()&& (l_u8_rd(SysPowerMod)== Sys_ON))
	{
		if(l_flg_tst(PosLmpOutputSts))
		{
			l_flg_clr(PosLmpOutputSts);
			if(l_u8_rd(PosLmpOutputSts))
			{
				uLmpPwmVal = IndNightMode;
			}else{
				uLmpPwmVal = IndDayMode;
			}
		}else{
			;
		}
		LOW_Fn_PWM_DutySet(PWM_D1_CHANNEL, uLmpPwmVal);


		if(l_flg_tst(ACOpenSts) == TRUE)  //ONOFF
		{
			l_flg_clr(ACOpenSts);
			if(l_u8_rd(ACOpenSts) != 0)
			{
				IND_ON_OFF_OPEN();
			}else{	
				IND_ON_OFF_COLSE();
			}		
		}	

		if(l_flg_tst(ACCmprEnaSts) == TRUE)  //AC
		{
			l_flg_clr(ACCmprEnaSts);
			if(l_u8_rd(ACCmprEnaSts) != 0)
			{
				IND_AC_OPEN();
			}else{			
				IND_AC_COLSE();
			}		
		}
		if(l_flg_tst(ACAutoModEnaSts) == TRUE)  //AUTO
		{
			l_flg_clr(ACAutoModEnaSts);
			if(l_u8_rd(ACAutoModEnaSts) != 0)
			{
				IND_AUTO_OPEN();
			}else{			
				IND_AUTO_COLSE();
			}		
		}
	
		if(l_flg_tst(ACAirInletSts) == TRUE)	//AirInlet
		{
			l_flg_clr(ACAirInletSts);
			if(l_u8_rd(ACAirInletSts) == 0u)
			{
				IND_AIRINNER_OPEN();
			}else{			
				IND_AIRINNER_COLSE();
			}		
		}

		
	}else{
		LOW_Fn_PWM_DutySet(PWM_D1_CHANNEL, Cal_Ind_Off);
		IND_ON_OFF_COLSE();
		IND_AC_COLSE();
		IND_AUTO_COLSE();
		IND_AIRINNER_COLSE();
	}

}


/****************************************************************************************  
@函数名称       : void vDrvModeIndDeal(void)                         
@参数           : void  
@返回值         : 
@描述           : 
@最后编辑时间   :  
@版本           : v1.0  
@备注           :           
*****************************************************************************************/
