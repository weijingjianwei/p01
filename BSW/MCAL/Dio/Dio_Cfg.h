/*******************************************************************************
 *
 * Description:     : Pin Config for Dio
 *
*******************************************************************************/
#ifndef __DIO_CFG_H
#define __DIO_CFG_H

/*******************************************************************************
 *
 * Description:     : Macro Description Section
 *
*******************************************************************************/
#define SIGNAL_INPUT_ON_OFF                 (P6&0x01)
#define SIGNAL_INPUT_AC                     (P6&0x02)
#define SIGNAL_INPUT_AIR_PLUS               (P6&0x08)
#define SIGNAL_INPUT_AIR_MINUS              (P6&0x04)
#define SIGNAL_INPUT_TEMP_PLUS              (P8&0x80)
#define SIGNAL_INPUT_TEMP_MINUS             (P3&0x04)
#define SIGNAL_INPUT_AirInner               (P8&0x40)
#define SIGNAL_INPUT_AUTO                   (P8&0x10)
#define SIGNAL_INPUT_Mode                   (P8&0x04)

/*******************************************************************************
 *
 * Description:     : output control interface	
 *
*******************************************************************************/

#define SIGNAL_OUTPUT_PwrPull_CTRL_HIGH_LEVEL()             (P3 |=0x10)
#define SIGNAL_OUTPUT_PwrPull_CTRL_LOW_LEVEL()              (P3 &=0xEF)

#define IND_ON_OFF_OPEN()               (P8 |=0x01)
#define IND_ON_OFF_COLSE()              (P8 &=0xFE)
#define IND_AC_OPEN()                   (P8 |=0x02)
#define IND_AC_COLSE()                  (P8 &=0xFD)
#define IND_AUTO_OPEN()                 (P8 |=0x08)
#define IND_AUTO_COLSE()                (P8 &=0xF7)
#define IND_AIRINNER_OPEN()             (P8 |=0x20)
#define IND_AIRINNER_COLSE()            (P8 &=0xDF)

/*******************************************************************************
 *
 * Description:     : CAN_MODE control interface
 *
*******************************************************************************/


/*******************************************************************************
 *
 * Description:     : LIN_MODE control interface
 *
*******************************************************************************/

#define SIGNAL_OUTPUT_LinSlp_CTRL_HIGH_LEVEL()             (P1 |=0x04)
#define SIGNAL_OUTPUT_LinSlp_CTRL_LOW_LEVEL()              (P1 &=0xFB)

#define SIGNAL_OUTPUT_LinTx_CTRL_HIGH_LEVEL()              (P1 |=0x08)
#define SIGNAL_OUTPUT_LinTx_CTRL_LOW_LEVEL()               (P1 &=0xF7)

typedef enum{
    Sgl_OFF = 0,
    Sgl_ON
}En_SglVal;
typedef enum{
    Ind_OFF = 0,
    Ind_ON,
}En_EnIndSgl;
/*******************************************************************************
 *
 * Description:     : Global Function Prototype Declaration	
 *
*******************************************************************************/
extern uint8_t LOW_Fn_OnOffSignalGet(void);
extern uint8_t LOW_Fn_ACSignalGet(void);
extern uint8_t LOW_Fn_AirPlusSignalGet(void);
extern uint8_t LOW_Fn_AirMinusSignalGet(void);
extern uint8_t LOW_Fn_TempPlusSignalGet(void);
extern uint8_t LOW_Fn_TempMinusSignalGet(void);
extern uint8_t LOW_Fn_AutoSignalGet(void);
extern uint8_t LOW_Fn_ModeSignalGet(void);
extern uint8_t LOW_Fn_AirInnerSignalGet(void);


extern void LOW_Fn_Borard_PwrPullCtl_Enable(void);
extern void LOW_Fn_Borard_PwrPullCtl_Disble(void);
extern void LOW_Fn_Borard_Lin_Slp_Enable(void);
extern void LOW_Fn_Borard_Lin_Slp_Disble(void);
extern void LOW_Fn_Borard_Lin_Tx_Enable(void);
extern void LOW_Fn_Borard_Lin_Tx_Disble(void);

extern void LOW_Fn_Borard_ONOFF_IndCtrl(En_EnIndSgl SetVal);
extern void LOW_Fn_Borard_AC_IndCtrl(En_EnIndSgl SetVal);
extern void LOW_Fn_Borard_Auto_IndCtrl(En_EnIndSgl SetVal);
extern void LOW_Fn_Borard_AirInner_IndCtrl(En_EnIndSgl SetVal);

#endif


