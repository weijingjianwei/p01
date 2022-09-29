


/*---------------------------------------------------------------------------------
 
    Created on: 2019-1-14
    Author: zhangbaojia

-------------------------------------------------------------------------------------*/
/*Macro define        identifier_u08*/

#define NO_1_ID_EE     1     /*   au8ExtReprogRequestFlag  */
#define NO_2_ID_EE     2     /*   au8AppSoftwareVersion    */
#define NO_3_ID_EE     3     /*   au8HardwareVersion       */
#define NO_4_ID_EE     4     /*   au8BlSoftwareVersion     */
#define NO_5_ID_EE     5     /*   au8RepairShopcodeSN     */
#define NO_6_ID_EE     6     /*   au8programmingDate     */
#define NO_7_ID_EE     7     /*   au8AppFlashValidFlag     */
#define NO_8_ID_EE     8     /*   au8blackLightcalvalue   */


#define EXTREPROGREQUEST_LEN      					(uint8_t)1
#define HW_VERSION_DATA_LEN                         (uint8_t)16
#define SW_VERSION_DATA_LEN                         (uint8_t)16
#define BL_VERSION_DATA_LEN  						(uint8_t)16
#define PEPAIRSHOPCODE_DATA_LEN                     (uint8_t)16
#define PROGRAMMING_DATA_LEN                        (uint8_t)4
#define APPSW_VALID_FLAG_LEN      					(uint8_t)1
#define BLACKLIGHT_CAL_VALUE_LEN      				(uint8_t)1


/*-------------------------------------------------------------------------------------*/
/*Globle Variable*/
 extern uint8_t   au8ExtReprogRequestFlag[1];
 extern uint8_t   au8AppSoftwareVersion[16];
 extern uint8_t   au8HardwareVersion[16];
 extern uint8_t   au8BlSoftwareVersion[16];
 extern uint8_t   au8RepairShopcodeSN[16];
 extern uint8_t   au8ProgrammingDate[4];
 extern uint8_t   au8AppFlashValidFlag[1];
 extern uint8_t   au8blackLightcalvalue[1];

 extern uint8_t	 utExtReprogRequest_WriteEnableFlag;

/*-------------------------------------------------------------------------------------*/
/*Globle Function*/
extern  void vMLp_Sys_EEPROM_Init(void);
extern	void vMLp_Sys_EEPROM_Write (void);
extern	void vMLp_Sys_EEPROM_Read (void);
extern  void EEPROM_Write_Data(uint8_t *address_pu08,uint8_t identifier_u08);
extern  void EEPROM_Read_Data(uint8_t *address_pu08,uint8_t identifier_u08);

/*-------------------------------------------------------------------------------------*/
