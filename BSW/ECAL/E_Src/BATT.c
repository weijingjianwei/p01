/****************************************************************************************
 				            Include File Section 									
*****************************************************************************************/
#include "include.h"
#include "BATT_Cfg.h"
#include "BATT.h"

/****************************************************************************************
 				            Pragma Define Section 									
*****************************************************************************************/
//#pragma CODE_SEG __FAR_SEG DEFAULT

/****************************************************************************************
 				            Global Variable Definition Section 									
*****************************************************************************************/
//#pragma DATA_SEG __RPAGE_SEG FAR_RAM


static uint16_t  BATT_Kt_Ad[8U];
static uint8_t  BATT_Kv_FilterCnt=0U;

static uint8_t  BATT_Kv_Status=0U;
static uint8_t  BATT_Kv_Change_Count=0U;
static uint8_t  BATT_Kv_ModeA_Flag=0U;
static uint8_t  BATT_Kv_ModeB_Flag=0U;
static uint8_t  BATT_Kv_ModeC_Flag=0U;

static uint8_t    EnUser;                    /* Enable/Disable device by user */

void vMLp_Voltage_Mag_Deal(void);
void  LIN_Enable(void);
void  LIN_Disable(void);

//#pragma DATA_SEG __NEAR_SEG DEFAULT


/*code*/
/****************************************************************************************  
@函数名称       : uint8_t SSW_Fn_BATT_DetectGet(void)
                         
@参数           : void
  
@返回值         : 返回8位
                  0：为正常工作电压
                  1：为低压或高压
                  2: 为低低压或高高压

@描述           : 蓄电池电压诊断

@最后编辑时间   : 2012-05-30
 
@版本           : v1.0
  
@备注           : 
-------6.5----7.0-----8.5------9.0-------------16.0------16.5----18.5-----19.0
|---C---|--BC--|---B---|---BA---|-------A---------|---AB---|---B---|---BC---|---C---| 
|---0---|--BC--|---1---|---BA---|-------2---------|---AB---|---1---|---BC---|---0---|              
*****************************************************************************************/
uint8_t SSW_Fn_BATT_DetectGet(void)
{
    return(BATT_Kv_Status);
}

/****************************************************************************************  
@函数名称       : uint16_t SSW_Fn_BATT_BubbleSortGet(void)
                         
@参数           : 索引号
  
@返回值         : 中位值

@描述           : 在AD数据组中，采用冒泡算法并取中位值

@最后编辑时间   : 2012-01-16
                  2012-05-19
                  2012-11-10
                  2012-12-06
 
@版本           : v1.3
  
@备注           : 	                 
*****************************************************************************************/
static uint16_t SSW_Fn_BATT_BubbleSortGet(void)
{
    uint8_t Temp_Kv_AdBufferSize;
    uint8_t Temp_Kv_AvgCalLoopBig;				    	/*high AD variable for cycle count，最大的AD值			*/
	uint8_t Temp_Kv_AvgCalLoopSmall;				        /*low AD variable for cycle coun，最小的AD值				*/
	uint16_t Temp_Kv_AvgCalValue;							/*store the succeed AD value as return，返回储存的AD平均值	*/

	if(BATT_Kc_AdBufferSize>=8U)
    {
        Temp_Kv_AdBufferSize=8U;
    }
    else
    
    {
        Temp_Kv_AdBufferSize=BATT_Kc_AdBufferSize;
    }

	/*Get AD delta value from Up-Down，使AD值从小到大排列*/
	for	(Temp_Kv_AvgCalLoopBig=0U;Temp_Kv_AvgCalLoopBig<=(Temp_Kv_AdBufferSize-1U);Temp_Kv_AvgCalLoopBig++)
	{
		for	(Temp_Kv_AvgCalLoopSmall=Temp_Kv_AvgCalLoopBig+1U; Temp_Kv_AvgCalLoopSmall<=(Temp_Kv_AdBufferSize-1U); Temp_Kv_AvgCalLoopSmall++)
		{
			if	((BATT_Kt_Ad[Temp_Kv_AvgCalLoopBig]) > (BATT_Kt_Ad[Temp_Kv_AvgCalLoopSmall]))
			{
				Temp_Kv_AvgCalValue = BATT_Kt_Ad[Temp_Kv_AvgCalLoopBig];
				BATT_Kt_Ad[Temp_Kv_AvgCalLoopBig] = BATT_Kt_Ad[Temp_Kv_AvgCalLoopSmall];
				BATT_Kt_Ad[Temp_Kv_AvgCalLoopSmall] = Temp_Kv_AvgCalValue;
			}
		}
	}
    
    if((Temp_Kv_AdBufferSize%2U)==0U)
    {
        Temp_Kv_AvgCalValue=(BATT_Kt_Ad[(Temp_Kv_AdBufferSize/2U)-1U]+BATT_Kt_Ad[Temp_Kv_AdBufferSize/2U])/2U;
    }
    else
    {
        Temp_Kv_AvgCalValue=BATT_Kt_Ad[Temp_Kv_AdBufferSize/2U]; 
    }
    
    return(Temp_Kv_AvgCalValue);
}

/****************************************************************************************  
@函数名称       : void SSW_Fn_BATT_Init(void)
                         
@参数           : 无
  
@返回值         : 无

@描述           : 初始化

@最后编辑时间   : 2012-12-05
 
@版本           : v1.0
  
@备注           :                 
*****************************************************************************************/
void SSW_Fn_BATT_Init(void)
{
    uint8_t Temp_Kv_AvgCalLoopBig=0U ;
    
    for(Temp_Kv_AvgCalLoopBig=0U;Temp_Kv_AvgCalLoopBig<8U;Temp_Kv_AvgCalLoopBig++)
	{
	    BATT_Kt_Ad[Temp_Kv_AvgCalLoopBig]= 0U;
	}
	BATT_Kv_FilterCnt= 0U ;
    
	BATT_Kv_Status = CMAC_System_Voltage_Mode_A;
	BATT_Kv_Change_Count = 0U;
	BATT_Kv_ModeA_Flag = 0U;
	BATT_Kv_ModeB_Flag = 0U;
	BATT_Kv_ModeC_Flag = 0U;
}

/****************************************************************************************  
@函数名称       : void SSW_Fn_BATT_DetectDeal(void)
                         
@参数           : 无
  
@返回值         : 无

@描述           : 蓄电池电压诊断

@最后编辑时间   : 
 
@版本           : v1.0
  
@备注           : 频率10ms
-------6.5----7.0-----8.5------9.0-------------16.0------16.5----18.5-----19.0
|---C---|--BC--|---B---|---BA---|-------A---------|---AB---|---B---|---BC---|---C---|                
*****************************************************************************************/
void SSW_Fn_BATT_DetectDeal(void)
{
    uint8_t Temp_Kv_BatteryFilterCount=0U ;
  //  uint8_t Temp_Kv_BatteryMaxFilterCount=0U ;
    uint16_t Temp_Kv_BatteryAd=0U ;
    
  /*  if(BATT_Kc_FilterTime>=2550U)
    {
        Temp_Kv_BatteryFilterCount=255U;
    }
    else
    {
        Temp_Kv_BatteryFilterCount=(uint8_t)(BATT_Kc_FilterTime/10U);
    }
    
    if(BATT_Kc_MaxFilterTime>=2550U)
    {
        Temp_Kv_BatteryMaxFilterCount=255U;
    }
    else
    {
        Temp_Kv_BatteryMaxFilterCount=(uint8_t)(BATT_Kc_MaxFilterTime/10U);
    }
    */
    Temp_Kv_BatteryFilterCount=(uint8_t)(BATT_Kc_FilterTime/10U);
    Temp_Kv_BatteryAd=SSW_Fn_BATT_BubbleSortGet();
    
	switch(BATT_Kv_Status)
	{
		case	CMAC_System_Voltage_Mode_A:				/*in A mode*/
		{
			if	(Temp_Kv_BatteryAd >= CSystem_A_To_B_Up_Voltage)
			{
				BATT_Kv_Change_Count++;
				if	(BATT_Kv_Change_Count >= Temp_Kv_BatteryFilterCount)
				{
					BATT_Kv_Status = CMAC_System_Voltage_Mode_B;
					BATT_Kv_Change_Count = 0U;
					BATT_Kv_ModeB_Flag = Cuc_All_Valid_Flag;
				}
			}
			else if	(Temp_Kv_BatteryAd  < CSystem_A_To_B_Down_Voltage)
			{
				BATT_Kv_Change_Count++;
				if	(BATT_Kv_Change_Count >= Temp_Kv_BatteryFilterCount)
				{
					BATT_Kv_Status = CMAC_System_Voltage_Mode_B;
					BATT_Kv_Change_Count = 0U;
					BATT_Kv_ModeB_Flag = Cuc_All_Valid_Flag;
				}
			}
			else
			{
				BATT_Kv_Change_Count = 0U;
			}
			break;
		}

		case	CMAC_System_Voltage_Mode_B:				/*in B mode*/
		{
			
			if	((Temp_Kv_BatteryAd  < CSystem_B_To_A_Down_Voltage) && (Temp_Kv_BatteryAd  >= CSystem_B_To_A_Up_Voltage))
			{
				BATT_Kv_Change_Count++;
				if	(BATT_Kv_Change_Count >= Temp_Kv_BatteryFilterCount)
				{
					BATT_Kv_Status = CMAC_System_Voltage_Mode_A;
					BATT_Kv_Change_Count = 0U;
					BATT_Kv_ModeA_Flag = Cuc_All_Valid_Flag;
				}
			}
			else	if	((Temp_Kv_BatteryAd >= CSystem_B_To_C_Up_Voltage) || (Temp_Kv_BatteryAd  < CSystem_B_To_C_Down_Voltage))
			{
				BATT_Kv_Change_Count++;
				if	(BATT_Kv_Change_Count >= Temp_Kv_BatteryFilterCount)
				{
					BATT_Kv_Status = CMAC_System_Voltage_Mode_C;
					BATT_Kv_Change_Count = 0U;
					BATT_Kv_ModeC_Flag = Cuc_All_Valid_Flag;
				}
			}
			else
			{
				BATT_Kv_Change_Count = 0U;
			}
			break;
		}

		case	CMAC_System_Voltage_Mode_C:				/*in C mode*/
		{
			if	((Temp_Kv_BatteryAd  < CSystem_C_To_B_Down_Voltage) && (Temp_Kv_BatteryAd  >= CSystem_C_To_B_Up_Voltage))
			{
				BATT_Kv_Change_Count++;
				if	(BATT_Kv_Change_Count >= Temp_Kv_BatteryFilterCount)
				{
					BATT_Kv_Status = CMAC_System_Voltage_Mode_B;
					BATT_Kv_Change_Count = 0U;
					BATT_Kv_ModeB_Flag = Cuc_All_Valid_Flag;
				}
			}
			else
			{
				BATT_Kv_Change_Count = 0U;
			}
			break;
		}

		default:
		{
			BATT_Kv_Status = CMAC_System_Voltage_Mode_C;
			break;
		}
	}
	
	vMLp_Voltage_Mag_Deal();
	
}

/****************************************************************************************  
@函数名称       : void SSW_Fn_BATT_DetectDeal(void)
                         
@参数           : 无
  
@返回值         : 无

@描述           : 蓄电池电压诊断

@最后编辑时间   : 
 
@版本           : v1.0
  
@备注           : 频率10ms
-------6.5----7.0-----8.5------9.0-------------16.0------16.5----18.5-----19.0
|---C---|--BC--|---B---|---BA---|-------A---------|---AB---|---B---|---BC---|---C---|                
*****************************************************************************************/
void SSW_Fn_BATT_DetectDeal_Init(void)
{
    uint8_t Temp_Kv_BatteryFilterCount=0U ;
//    uint8_t Temp_Kv_BatteryMaxFilterCount=0U ;
    uint16_t Temp_Kv_BatteryAd=0U ;
    
  /*  if(BATT_Kc_FilterTime>=2550U)
    {
        Temp_Kv_BatteryFilterCount=255U;
    }
    else
    {
        Temp_Kv_BatteryFilterCount=(uint8_t)(BATT_Kc_FilterTime/10U);
    }
    
    if(BATT_Kc_MaxFilterTime>=2550U)
    {
        Temp_Kv_BatteryMaxFilterCount=255U;
    }
    else
    {
        Temp_Kv_BatteryMaxFilterCount=(uint8_t)(BATT_Kc_MaxFilterTime/10U);
    }
    */
    Temp_Kv_BatteryFilterCount=(uint8_t)(BATT_Kc_FilterTimeInit/10U);
    Temp_Kv_BatteryAd=SSW_Fn_BATT_BubbleSortGet();
    
	switch(BATT_Kv_Status)
	{
		case	CMAC_System_Voltage_Mode_A:				/*in A mode*/
		{
			if	(Temp_Kv_BatteryAd >= CSystem_A_To_B_Up_Voltage)
			{
				BATT_Kv_Change_Count++;
				if	(BATT_Kv_Change_Count >= Temp_Kv_BatteryFilterCount)
				{
					BATT_Kv_Status = CMAC_System_Voltage_Mode_B;
					BATT_Kv_Change_Count = 0U;
					BATT_Kv_ModeB_Flag = Cuc_All_Valid_Flag;
				}
			}
			else if	(Temp_Kv_BatteryAd  < CSystem_A_To_B_Down_Voltage)
			{
				BATT_Kv_Change_Count++;
				if	(BATT_Kv_Change_Count >= Temp_Kv_BatteryFilterCount)
				{
					BATT_Kv_Status = CMAC_System_Voltage_Mode_B;
					BATT_Kv_Change_Count = 0U;
					BATT_Kv_ModeB_Flag = Cuc_All_Valid_Flag;
				}
			}
			else
			{
				BATT_Kv_Change_Count = 0U;
			}
			break;
		}

		case	CMAC_System_Voltage_Mode_B:				/*in B mode*/
		{
			
			if	((Temp_Kv_BatteryAd  < CSystem_B_To_A_Down_Voltage) && (Temp_Kv_BatteryAd  >= CSystem_B_To_A_Up_Voltage))
			{
				BATT_Kv_Change_Count++;
				if	(BATT_Kv_Change_Count >= Temp_Kv_BatteryFilterCount)
				{
					BATT_Kv_Status = CMAC_System_Voltage_Mode_A;
					BATT_Kv_Change_Count = 0U;
					BATT_Kv_ModeA_Flag = Cuc_All_Valid_Flag;
				}
			}
			else	if	((Temp_Kv_BatteryAd >= CSystem_B_To_C_Up_Voltage) || (Temp_Kv_BatteryAd  < CSystem_B_To_C_Down_Voltage))
			{
				BATT_Kv_Change_Count++;
				if	(BATT_Kv_Change_Count >= Temp_Kv_BatteryFilterCount)
				{
					BATT_Kv_Status = CMAC_System_Voltage_Mode_C;
					BATT_Kv_Change_Count = 0U;
					BATT_Kv_ModeC_Flag = Cuc_All_Valid_Flag;
				}
			}
			else
			{
				BATT_Kv_Change_Count = 0U;
			}
			break;
		}

		case	CMAC_System_Voltage_Mode_C:				/*in C mode*/
		{
			if	((Temp_Kv_BatteryAd  < CSystem_C_To_B_Down_Voltage) && (Temp_Kv_BatteryAd  >= CSystem_C_To_B_Up_Voltage))
			{
				BATT_Kv_Change_Count++;
				if	(BATT_Kv_Change_Count >= Temp_Kv_BatteryFilterCount)
				{
					BATT_Kv_Status = CMAC_System_Voltage_Mode_B;
					BATT_Kv_Change_Count = 0U;
					BATT_Kv_ModeB_Flag = Cuc_All_Valid_Flag;
				}
			}
			else
			{
				BATT_Kv_Change_Count = 0U;
			}
			break;
		}

		default:
		{
			BATT_Kv_Status = CMAC_System_Voltage_Mode_C;
			break;
		}
	}
	
	vMLp_Voltage_Mag_Deal();
	
}

/****************************************************************************************  
@函数名称       : void SSW_Fn_BATT_AdGet(void)
                         
@参数           : 无
  
@返回值         : 无

@描述           : 读取Battery通道的Ad值

@最后编辑时间   : 
 
@版本           : v1.0
  
@备注           : 频率2.5ms 	                 
*****************************************************************************************/
void SSW_Fn_BATT_AdGet(void)
{
    BATT_Kt_Ad[BATT_Kv_FilterCnt]=ATD_Kt_PAD[AD_BATTERY_CHANNEL];

    BATT_Kv_FilterCnt++;
    if(BATT_Kv_FilterCnt>=BATT_Kc_AdBufferSize)
    {
        BATT_Kv_FilterCnt=0U ;
    }
}

/*Other Code*/
/****************************************************************************************  
@函数名称       : uint8_t PID_BATT_VoltageLowResGet(void)
                         
@参数           : void
  
@返回值         : 

@描述           : Battery Voltage Low Resolution

@最后编辑时间   : 
 
@版本           : 
  
@备注           : Battery Voltage (1Byte)
                  y = (1/10)x + 3 Volt            
*****************************************************************************************/
uint8_t PID_BATT_VoltageLowResGet(void)
{
    uint32_t Temp_Kv_Value ;
    
    Temp_Kv_Value=(uint32_t)(SSW_Fn_BATT_BubbleSortGet());
    
    /*V/(BATT_PULLUP_VDD+BATT_PULLDOWN_GND)=5*AD/(4096*100)*/
    /*V=AD*(BATT_PULLUP_VDD+BATT_PULLDOWN_GND)/40960*/
    /*因处理小数点，此处扩大10倍*/
    Temp_Kv_Value=((Temp_Kv_Value*(CSystem_BattRes_Value+CSystem_GndRes_Value))*5U)/1024U;
    /*X=(10Y-300)/10*/
    /*因之前扩大10倍，此处缩小10倍，还原*/
    Temp_Kv_Value=((Temp_Kv_Value*10U)-300U)/10U;
    return((uint8_t)Temp_Kv_Value);
}

/****************************************************************************************  
@函数名称       : uint16_t PID_BATT_VoltageGet(void)
                         
@参数           : void
  
@返回值         : 

@描述           : Battery Voltage

@最后编辑时间   : 
 
@版本           : v1.1
  
@备注           : Volt 0.1 Signed (2Byte)
                  y = (1/10)x V           
*****************************************************************************************/
uint16_t PID_BATT_VoltageGet(void)
{
    uint32_t Temp_Kv_Value ;
    
    Temp_Kv_Value=(uint32_t)(SSW_Fn_BATT_BubbleSortGet());
    
    /*V/(BATT_PULLUP_VDD+BATT_PULLDOWN_GND)=5*AD/(4096*100)*/
    /*V=AD*(BATT_PULLUP_VDD+BATT_PULLDOWN_GND)/40960*/
    /*因处理小数点，此处扩大10倍*/
    //Temp_Kv_Value=((Temp_Kv_Value*(CSystem_BattRes_Value+CSystem_GndRes_Value))*5U)/1024U;
    return((uint16_t)Temp_Kv_Value);
}

void vMLp_Voltage_Mag_Deal(void)
{	
	if(BATT_Kv_Status == CMAC_System_Voltage_Mode_A)
	{
		OrgVoltageFailSts_CCSMSignalSet(ccsm_NoErr);
	}else{
		OrgVoltageFailSts_CCSMSignalSet(ccsm_Err);
	}
	
	if(BATT_Kv_Status == CMAC_System_Voltage_Mode_C)
	{
//		DisableInterrupts;	
		LIN_Disable();
//		EnableInterrupts;		
	}else{
		LIN_Enable();			
	}
}

void  LIN_Enable(void)
{
	  if (!EnUser) {                       /* Is the device disabled by user? */
	    EnUser = 1;                     /* If yes then set the flag "device enabled" */   
	    //l_sys_irq_restore(LI0);	          /* Enable the device */		
		l_ifc_connect(LIN_CHANNEL0) ;
		
	    
	  }
}

void  LIN_Disable(void)
{
	  if (EnUser) {                       /* Is the device disabled by user? */
		  EnUser = 0;                     /* If yes then set the flag "device enabled" */
	    //l_sys_irq_disable(LI0);	          /* Enable the device */
		l_ifc_disconnect(LIN_CHANNEL0);
		
	  }
}



