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


//code
/****************************************************************************************  
@函数名称       : void  LOW_Fn_PWM_ON(void)  
                       
@参数           : void 
 
@返回值         : void 
 
@描述           : 初始化PWM模块

@最后编辑时间   : 2013-04-15 
 
@版本           : v1.0  

@备注           :             
*****************************************************************************************/
void LOW_Fn_PWM_ON(void)
{
	R_TMR_RD1_Start();
}


/****************************************************************************************  
@函数名称       : void  LOW_Fn_PWM_OFF(void)  
                       
@参数           : void 
 
@返回值         : void 
 
@描述           : PWM模块关闭

@最后编辑时间   : 2012-02-20 
 
@版本           : v1.0  

@备注           :               
*****************************************************************************************/
void LOW_Fn_PWM_OFF(void)
{
	R_TMR_RD1_Stop();
}

/****************************************************************************************  
@函数名称       : void LOW_Fn_PWM_DutySet(uint8 Channel ,uint8 Duty)
                        
@参数           : 
                  
@返回值         : void 

@描述           :   Duty = 0 -100 级
                    
@最后编辑时间   : 

@版本           : v1.0  

@备注                      
*****************************************************************************************/
void LOW_Fn_PWM_DutySet(uint8_t Channel,uint8_t Duty)
{   
    uint16_t fTempRatio = TRDGRA1/PMW_Rate_Value;
    switch(Channel)
    {
        case 0U :
        {    
			if(Duty == PMW_Rate_Value)
			{
			   TRDGRC1 = TRDGRA1+1;
			}else if(Duty == 0)
			{
			   TRDGRC1 = TRDGRA1;	
			}else{
			
			   TRDGRC1 = (uint16_t)(fTempRatio*Duty);
			}
				
	        break ;
        }
        case 1U :
        {   
			if(Duty == PMW_Rate_Value)
			{
			   TRDGRD1 = TRDGRA1+1;
			}else if(Duty == 0)
			{
			   TRDGRD1 = TRDGRA1;	
			}else{
			
			   TRDGRD1 = (uint16_t)(fTempRatio*Duty);
			}
            break ;
        }
	case 2U :
        {   
			if(Duty == PMW_Rate_Value)
			{
			   TRDGRD0 = TRDGRA1+1;
			}else if(Duty == 0)
			{
			   TRDGRD0 = TRDGRA1;	
			}else{
			
			   TRDGRD0 = (uint16_t)(fTempRatio*Duty);
			}
            break ;
        }
        default :
        {
          
            break ;
        }
    }
}


