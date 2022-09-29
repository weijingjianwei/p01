/****************************************************************************************
 				            Include File Section 									
*****************************************************************************************/
#include  "include.h"

/****************************************************************************************
 				            Pragma Define Section 									
*****************************************************************************************/


/****************************************************************************************
 				            Global Variable Definition Section 									
*****************************************************************************************/
//static	uint8_t ucPeriod_Service_AdChannel = _00_AD_INPUT_CHANNEL_0;

uint16_t  ATD_Kt_PAD[7];


/*code*/
/****************************************************************************************  
@函数名称       : void  LOW_Fn_ATD_ON(void)
                         
@参数           : void
  
@返回值         : void
  
@描述           : 

@最后编辑时间   : 
  
@版本           :
 
@备注           :                  
*****************************************************************************************/
void LOW_Fn_ATD_ON(void)
{
      
   R_ADC_Start();
}

/****************************************************************************************  
@函数名称       : void  LOW_Fn_ATD_OFF(void)
                         
@参数           : void
  
@返回值         : void
  
@描述           : 

@最后编辑时间   : 
  
@版本           : v1.0 
 
@备注           :                   
*****************************************************************************************/
void LOW_Fn_ATD_OFF(void)
{
   R_ADC_Stop();
}
/****************************************************************************************  
@函数名称       : void LOW_Fn_ATD_AdGet(void)
                         
@参数           : void
  
@返回值         : void 

@描述           : 周期性读取通道的AD值 125uS

@最后编辑时间   :  
 
@版本           : v1.0
  
@备注           :                  
*****************************************************************************************/
void  LOW_Fn_ATD_AdGet(void)
{  
	
	//ADS = _01_AD_INPUT_CHANNEL_0;	
	R_ADC_Get_Result(&ATD_Kt_PAD[0]);
	/*switch(ucPeriod_Service_AdChannel)
	{
		case _00_AD_INPUT_CHANNEL_0:	
		{
				
			R_ADC_Get_Result(&ATD_Kt_PAD[0]);
			ADS = _01_AD_INPUT_CHANNEL_1;			
			
			//ucPeriod_Service_AdChannel++;
			break;
			
		}
		case _01_AD_INPUT_CHANNEL_1:	
		{
			
			R_ADC_Get_Result(&ATD_Kt_PAD[1]); 
						
       			ADS = _02_AD_INPUT_CHANNEL_2;			
			
			ucPeriod_Service_AdChannel++;
			break;
			
		}	
		
		case _02_AD_INPUT_CHANNEL_2:	
		{
			
			R_ADC_Get_Result(&ATD_Kt_PAD[2]);
			ADS = _03_AD_INPUT_CHANNEL_3;			
			
			ucPeriod_Service_AdChannel++;
			break;
			
		}
		case _03_AD_INPUT_CHANNEL_3:	
		{
			
			R_ADC_Get_Result(&ATD_Kt_PAD[3]);
			ADS = _04_AD_INPUT_CHANNEL_4;			
			
			ucPeriod_Service_AdChannel++;
			break;
			
		}
		case _04_AD_INPUT_CHANNEL_4:	
		{
			
			R_ADC_Get_Result(&ATD_Kt_PAD[4]);
			ADS = _05_AD_INPUT_CHANNEL_5;			
			
			ucPeriod_Service_AdChannel++;
			break;
			
		}
		 case _05_AD_INPUT_CHANNEL_5:	
		{
			
			R_ADC_Get_Result(&ATD_Kt_PAD[5]);
			ADS = _06_AD_INPUT_CHANNEL_6;			
			
			ucPeriod_Service_AdChannel++;
			break;
			
		}
		case _06_AD_INPUT_CHANNEL_6:	
		{
			
			R_ADC_Get_Result(&ATD_Kt_PAD[6]);
			ADS = _00_AD_INPUT_CHANNEL_0;			
			
			ucPeriod_Service_AdChannel = _00_AD_INPUT_CHANNEL_0;
			break;
			
		}
		default:
		{
			
			ucPeriod_Service_AdChannel = _00_AD_INPUT_CHANNEL_0;	
			ADS = _00_AD_INPUT_CHANNEL_0;
			break;
			
		}
	
	
	}*/

}

