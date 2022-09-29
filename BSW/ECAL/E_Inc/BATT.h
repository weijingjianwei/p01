#ifndef _BATT_H_
#define _BATT_H_

/*******************************************************************************
 *
 * Description:     : Macro Description Section
 *
*******************************************************************************/
/*10K上拉，2K拉地*/
/*10K上拉，2K拉地*/
#define	CSystem_B_To_C_Up_Voltage			617U		/*19V*/
#define	CSystem_C_To_B_Down_Voltage			600U		/*18.5*/
#define	CSystem_A_To_B_Up_Voltage			532U		/*16.5V*/
#define	CSystem_B_To_A_Down_Voltage			523U		/*16.0V*/  
#define	CSystem_B_To_A_Up_Voltage			275U		/*9.0V*/
#define	CSystem_A_To_B_Down_Voltage			264U		/*8.5V*/
#define	CSystem_C_To_B_Up_Voltage			194U		/*6.5V*/
#define	CSystem_B_To_C_Down_Voltage			182U 		/*6.0V*/

#define CSystem_BattRes_Value               47U        /*电源电压采集靠近电源端电阻阻值，单位（KΩ）*/
#define CSystem_GndRes_Value                10U        /*电源电压采集靠近地端电阻阻值，单位（KΩ）*/

#define	CMAC_System_Voltage_Mode_A			2U			/*A Status*/
#define	CMAC_System_Voltage_Mode_B			1U			/*B Status*/
#define	CMAC_System_Voltage_Mode_C			0U			/*C Status*/

/*******************************************************************************
 *
 * Description:     : Mapping Macro Description Section	
 *
*******************************************************************************/
#define PowerErr_SET          0x01
#define PowerErr_CRL          0xFE

/*******************************************************************************
 *
 * Description:     : Structure Type Declaration Section
 *
*******************************************************************************/



/*******************************************************************************
 *
 * Description:     : Global Variable Declaration Section
 *
*******************************************************************************/



/*******************************************************************************
 *
 * Description:     : Calibration Variable Declaration Section	
 *
*******************************************************************************/

/*******************************************************************************
 *
 * Description:     : Const Table Variable Declaration Section	
 *
*******************************************************************************/


/*******************************************************************************
 *
 * Description:     : Const Variable Declaration Section	
 *
*******************************************************************************/
/*******************************************************************************
 *
 * Description:     : Global Function Prototype Declaration	
 *
*******************************************************************************/
extern void SSW_Fn_BATT_AdGet(void);
extern uint8_t SSW_Fn_BATT_DetectGet(void);

extern void SSW_Fn_BATT_Init(void);
extern void SSW_Fn_BATT_DetectDeal(void);
extern void SSW_Fn_BATT_DetectDeal_Init(void);

extern uint8_t PID_BATT_VoltageLowResGet(void);
extern uint16_t PID_BATT_VoltageGet(void);




#endif

