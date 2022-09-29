/*
 *  Created on: 2019-1-14
 *      Author: zhangbaojia

 */
/*-------------------------------------------------------------------------------------*/
#include "include.h"
#include "r_cg_macrodriver.h"
#include "fdl.h" 
#include "fdl_types.h" 
#include "fdl_descriptor.h"
#include "eel.h"
#include "eel_types.h"
#include "eel_descriptor.h"
#include "eel_user_types.h"
#include "EEPROM.h"

/*-------------------------------------------------------------------------------------*/
/*Macro define*/
eel_request_t   dtyEelReq;
fdl_status_t    fdlStatus = FDL_OK;

uint8_t   au8ExtReprogRequestFlag[1] = {0x0};
uint8_t   au8AppSoftwareVersion[16];
uint8_t   au8HardwareVersion[16];
uint8_t   au8BlSoftwareVersion[16];
uint8_t   au8AppFlashValidFlag[1];


uint8_t   utExtReprogRequest_WriteEnableFlag = 0;

/*-------------------------------------------------------------------------------------*/
/*Globle parameter*/
/*-------------------------------------------------------------------------------------*/

/*
Function:		vMLp_Sys_EEPROM_Init
Description:
Input： 			void
Output： 		void
Time 			
Others: 		void
*/
void vMLp_Sys_EEPROM_Init(void)
{
    dtyEelReq.address_pu08   = 0;
    dtyEelReq.identifier_u08 = 0;
    dtyEelReq.command_enu    = EEL_CMD_UNDEFINED;
    dtyEelReq.status_enu     = EEL_OK;
    
    fdlStatus = FDL_Init( &fdl_descriptor_str );
    
    if( fdlStatus == FDL_OK )
    {
	 
	FDL_Open();
        dtyEelReq.status_enu = EEL_Init();
        if( dtyEelReq.status_enu == EEL_OK )
        {		 
	  EEL_Open();
			
		//检查是否被格式化过,未格式则格式化
	   do{
	            dtyEelReq.command_enu = EEL_CMD_STARTUP;
	            EEL_Execute( &dtyEelReq ); 
	            while( dtyEelReq.status_enu == EEL_BUSY )
	            {
	                EEL_Handler(); 
	            }
	            if( dtyEelReq.status_enu == EEL_ERR_POOL_INCONSISTENT )
	            {
	                dtyEelReq.command_enu = EEL_CMD_FORMAT;
	                EEL_Execute( &dtyEelReq );
	                while( dtyEelReq.status_enu == EEL_BUSY )
	                {
	                   EEL_Handler();  
	                }
	            }
              }while((dtyEelReq.command_enu == EEL_CMD_FORMAT ) &&( dtyEelReq.status_enu  == EEL_OK));
			 
			 //关闭在STOP指令前执行
			 //EEL_Close();	
		}
		//关闭在STOP指令前执行
        //FDL_Close(); 		 
	}	


}

/*-------------------------------------------------------------------------------------*/
/*
Function:		vMLp_Sys_EEPROM_Write
Description:
Input： 			void
Output： 		void
Time 			
Others: 		void
*/
void vMLp_Sys_EEPROM_Write (void)
{
	
        uint8_t uTemp = 0;
	if(utExtReprogRequest_WriteEnableFlag == Cuc_All_Valid_Flag)
	{
	    utExtReprogRequest_WriteEnableFlag = 0;
		uTemp = Cuc_All_Valid_Flag;
		
		EEPROM_Write_Data(&uTemp,NO_1_ID_EE);
		WDTE = 0xAfU;     /*  restart */ 	
	}
}

/*-------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
/*
Function:		vMLp_Sys_EEPROM_Read
Description:
Input： 			void
Output： 		void
Time 			
Others: 		void
*/
void vMLp_Sys_EEPROM_Read (void)
{

   EEPROM_Read_Data(au8BlSoftwareVersion,NO_4_ID_EE);
   EEPROM_Read_Data(au8HardwareVersion,NO_3_ID_EE);	
   EEPROM_Read_Data(au8ExtReprogRequestFlag,NO_1_ID_EE);
   EEPROM_Read_Data(au8AppFlashValidFlag,NO_7_ID_EE);
}
/*-------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
/*
Function:		EEPROM_Write_Data(dtyEelReq.address_pu08,dtyEelReq.identifier_u08)
Description:
Input： 			void
Output： 		void
Time 			
Others: 		void
*/


void EEPROM_Write_Data(uint8_t *address_pu08,uint8_t identifier_u08)
{
	if( dtyEelReq.status_enu == EEL_OK )
	{
	  do{
	        dtyEelReq.address_pu08   = address_pu08;
            dtyEelReq.identifier_u08 = identifier_u08; 
			dtyEelReq.command_enu	 = EEL_CMD_WRITE;
			EEL_Execute( &dtyEelReq );
			while( dtyEelReq.status_enu == EEL_BUSY )
			{
				EEL_Handler();
			}
	
			if (dtyEelReq.status_enu == EEL_ERR_POOL_FULL)
			{
				dtyEelReq.command_enu	 = EEL_CMD_REFRESH;
				EEL_Execute( &dtyEelReq );
				while( dtyEelReq.status_enu == EEL_BUSY )
				{
					EEL_Handler();
				}
			}
		} while( ( dtyEelReq.command_enu == EEL_CMD_REFRESH ) && ( dtyEelReq.status_enu  == EEL_OK));		
			
	}



}

/*-------------------------------------------------------------------------------------*/
/*
Function:		EEPROM_Read_Data(dtyEelReq.address_pu08,dtyEelReq.identifier_u08)
Description:
Input： 			void
Output： 		void
Time 			
Others: 		void
*/

void EEPROM_Read_Data(uint8_t *address_pu08,uint8_t identifier_u08)
{

	if( dtyEelReq.status_enu == EEL_OK )
	{
	    dtyEelReq.address_pu08   = address_pu08;
        dtyEelReq.identifier_u08 = identifier_u08;
		dtyEelReq.command_enu	 = EEL_CMD_READ;

		EEL_Execute( &dtyEelReq );
		
		while( dtyEelReq.status_enu == EEL_BUSY )
		{
			EEL_Handler();
		}

	}



}


