/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012, 2018 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/F13 V2.03.02.05 [30 May 2018]
* Device(s)    : R5F10BGE
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 2022-3-4
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_adc.h"
#include "r_cg_timer.h"
#include "r_cg_wdt.h"
/* Start user code for include. Do not edit comment generated here */
#include "include.h"
#include "conflin_0.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
#define Cui_Time_Task_Init_Value      40000U /*40 ms */

#define NO_0_10MS            0  /*main task counter 0 */
#define NO_1_10MS            1  /*main task counter 1 */
#define NO_2_10MS            2  /*main task counter 2 */
#define NO_3_10MS            3  /*main task counter 3 */
#define NO_4_10MS            4  /*main task counter 4 */

uint16_t u16AdValue = 0;

uint8_t  ucFlag_Init_Task_Succeed;

static	volatile uint8_t	ucPeriod_Service_Num = 0 ;		/*main task service counter*/
static	uint16_t	  uiFlag_Init_Task_Counter = 0;				/*70ms;Counter for ucFlag_Init_Task_Succeed*/

static void vMian_Period_Routine(void);
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */    
    while(1)
    {
    	vMian_Period_Routine();
	//slave_task();
    }
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */ 
    LOW_Fn_Borard_PwrPullCtl_Enable();
    R_ADC_Start();    
    LinSglInit();
    SSW_Fn_BATT_Init();
    vSwitch_Mess_Init();
    vSleepWakeupInit();
	vIndicatorLightInit();
    R_TMR_RD1_Start();
    R_TAU0_Channel1_Start();    
    l_sys_init();
    l_ifc_init(LIN_CHANNEL0);    
	l_ifc_disconnect(LIN_CHANNEL0);
    P1|=0x04;
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */

/****************************************************************************************  
@闁告垼濮ら弳鐔煎触瀹ュ泦锟�?      : void vMian_Period_Routine(void)                        
@闁告瑥鍊归弳锟�           : void 
@閺夆晜鏌ㄥú鏍晸閿燂�?        :  
@闁硅绻楅崼锟�           : 
@闁哄牃鍋撻柛姘捣缁鳖亝娼忛幋鐐搭槯闁跨噦鎷�?  :    cycle task;include initial and tasks;  
@闁绘鐗婂﹢锟�           :
@濠㈣泛娲﹂弫锟�           :    infinite loop in main             
*****************************************************************************************/
void vMian_Period_Routine(void)
{
	if(ucFlag_Init_Task_Succeed != Cuc_All_Valid_Flag)
	{
		if(ucFlag_2ms_Period != 0U)
		{
			ucFlag_2ms_Period = 0U;
			if(uiFlag_Init_Task_Counter < (Cui_Time_Task_Init_Value/Cui_Time_Base_Cycle_Value))
			{
				uiFlag_Init_Task_Counter++;
				/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
				/*cycle task in Initial*/
				R_WDT_Restart(); /* feeds the dog */
										/*Read eeprom after power on*/
				SSW_Fn_BATT_AdGet();						/* AD Sample Value */	
				SSW_Fn_BATT_DetectDeal_Init();
			}else{
				//l_sys_irq_restore(LI0);	          /* Enable the device */
				l_ifc_connect(LIN_CHANNEL0);
				ucFlag_Init_Task_Succeed = Cuc_All_Valid_Flag;/*finish fast cycle after power on*/
			}
		}
	}else{
		   /*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
			if(ucFlag_2ms_Period != 0U)
			{	
				/*2ms valid and initial is closed*/
				ucFlag_2ms_Period = 0U;				 
				SSW_Fn_BATT_AdGet();
//				vMLp_Sys_Encolder_Filter_Deal();			
				/*cycle task in process*/
				/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
				switch(ucPeriod_Service_Num)
				{
					case NO_0_10MS: 						/*task 0,the first 10ms*/
					{
						R_WDT_Restart();
						SSW_Fn_BATT_DetectDeal();
						ucPeriod_Service_Num++;
						break;
					}
					case NO_1_10MS: 						/*task 1,the second 10ms*/
					{
						vSys_Button_Filter_Deal();
						LinSglHandler();
						ucPeriod_Service_Num++;
						break;
						/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
					}
					case NO_2_10MS: 						/*task 2,the second 10ms*/
					{
						TimerRefresh();
						vIndicatorLightingDeal();										
						ucPeriod_Service_Num++;
						break;
						/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
					}
					case NO_3_10MS: 						/*task 3,the second 10ms*/
					{				
						
						ucPeriod_Service_Num++;
						break;
						/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
					}
					case NO_4_10MS: 						/*task 4,the second 10ms*/
					{
						if(SSW_Fn_BATT_DetectGet() == CMAC_System_Voltage_Mode_A)
						{
							vMLp_Sleep_Wakeup_Deal();
						}
						ucPeriod_Service_Num = NO_0_10MS;
						break;
						/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
					}
					default:
					{
						/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
						ucPeriod_Service_Num = NO_0_10MS;	/*wrong routine, back to original mode*/
						break;
						/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
					}
			}

		}
	}
}
l_irqmask l_sys_irq_disable(void)
{
	return 0;
}

void l_sys_irq_restore(u1 u1tPreIrq)
{
	return;
}

void l_sys_call_sleep(u1 u1tIfcName)
{
	return;
}

void l_sys_call_wake_up(u1 u1tIfcName)
{
	return;
}
/* End user code. Do not edit comment generated here */
