
#ifndef __CAN_CFG_H_
#define __CAN_CFG_H_
/***************************************************************************
 * Copyright (c) 2021 - 2025, ChangHui Vehicle Electric, Inc.
 * All rights reserved. 

|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Version   Author  Description
| ---------  --------  ------  -----------------------------------------------
| 2021-07-15  v1.0      zbj    Creation 

|***************************************************************************/
#include "include.h"
/*******************************************************************************
 *
 * Description:     : Macro Description Section
 *
*******************************************************************************/
#define DLC_CCSM_MSG_ID       8U

/* -----------------------------------------------------------------------------
    &&&~ Signal Structures
 ----------------------------------------------------------------------------- */
typedef struct c_CCSM_msgTypeTag
{		
	/*	byte0*/
	uint8_t CCSM_Res0 : 8;
	/*	byte1*/
	uint8_t CCSM_RespEr : 1;
	uint8_t VoltageFailSts_CCSM :1;
	uint8_t CmprSwtReq : 1;
	uint8_t CmprSwtErrSts : 1;
	uint8_t AirInletSwtReq : 1;
	uint8_t AirInletSwtErrSts : 1;
	uint8_t DrvTempSwErrorSts : 2;	
	/*	byte2*/
	uint8_t CCSM_Res1 : 4;
	uint8_t AutoModSwtReq : 1;
	uint8_t AutoModSwtErrSts : 1;
	uint8_t ACOffSwtReq : 1;
	uint8_t ACOffSwtErrSts : 1;	
	/*	byte3*/
	uint8_t DrvTempSwSts :6;
	uint8_t DrvTempSwSync :1;
	uint8_t CCSM_Res2 : 1;
	/*	byte4*/
	uint8_t OneBtnIntCirclnSwtReq : 1;
	uint8_t OneBtnIntCirclnSwtReqErrSts : 1;
	uint8_t DrvAirDistribModSwReq : 1;
	uint8_t ACRotationSwtSync : 1;
	uint8_t DrvAirDistribModSwErrorSts : 1;
	uint8_t CCSM_Res3 : 3;
	/*	byte5*/
	uint8_t CCSM_Res4 : 8;
	/*	byte6*/
	uint8_t ACRotationSwtSts :6;
	uint8_t ACRotationSwtErrSts : 2;
	/*	byte7*/
	uint8_t CCSM_Res5 : 8;
	
}c_CCSM_msgType;

typedef enum{
  ccsm_NoErr = 0,
  ccsm_Err
}EN_ErrVal;

typedef enum{
  ccsm_NoReq = 0,
  ccsm_Req
}EN_ReqVal;

typedef enum{
  ccsm_SynOff = 0,
  ccsm_SynOn
}EN_SynVal;

typedef enum{
	Sys_OFF = 0,
 	Sys_ACC,
	Sys_ON,
	SYS_CRANK
}EN_SYS_MODE;

typedef enum{
	AirNoErr = 0,
 	Air_IncErr,
	Air_DecErr,
	Air_IncDecErr
}En_AirErr;
typedef enum{
	TempNoErr = 0,
 	Temp_IncErr,
	Temp_DecErr,
	Temp_IncDecErr
}En_TempErr;
/* -----------------------------------------------------------------------------
    &&&~  Tx Message Buffers
 ----------------------------------------------------------------------------- */
extern volatile c_CCSM_msgType     g_CCSMSwitch;
extern volatile uint8_t uCCSM_Buf[DLC_CCSM_MSG_ID];
/* -----------------------------------------------------------------------------
    &&&~  Tx Message Indicator flag
 ----------------------------------------------------------------------------- */ 


/* -----------------------------------------------------------------------------
    &&&~  Rx Message Buffers
 ----------------------------------------------------------------------------- */


/* -----------------------------------------------------------------------------
    &&&~  Rx Message Indicator flag
 ----------------------------------------------------------------------------- */
 


/* -----------------------------------------------------------------------------
	Get Rx Signal Access
 ----------------------------------------------------------------------------- */


/* -----------------------------------------------------------------------------
	Set Tx Signal Access for 
 ----------------------------------------------------------------------------- */
extern void OrgVoltageFailSts_CCSMSignalSet(EN_ErrVal ucSetValue);
extern void OrgACOffSwtReqSignalSet(EN_ReqVal ucSetValue);
extern void OrgACOffSwtErrStsSignalSet(EN_ErrVal ucSetValue);
extern void OrgAutoModSwtReqSignalSet(EN_ReqVal ucSetValue);
extern void OrgAutoModSwtErrStsSignalSet(EN_ErrVal ucSetValue);
extern void OrgACRotationSwtSyncSignalSet(EN_SynVal ucSetValue);
extern void OrgACRotationSwtStsSignalSet(uint8_t ucSetValue);
extern void OrgACRotationSwtErrStsSignalSet(En_AirErr ucSetValue);
extern void OrgDrvTempSwSyncSignalSet(EN_SynVal ucSetValue);
extern void OrgDrvTempSwStsSignalSet(uint8_t ucSetValue);
extern void OrgDrvTempSwErrorStsSignalSet(En_AirErr ucSetValue);
extern void OrgAirInletSwtReqSignalSet(EN_ReqVal ucSetValue);
extern void OrgAirInletSwtErrStsSignalSet(EN_ErrVal ucSetValue);
extern void OrgCmprSwtReqSignalSet(EN_ReqVal ucSetValue);
extern void OrgCmprSwtErrStsSignalSet(EN_ErrVal ucSetValue);
extern void OrgDrvAirDistribModSwReqSignalSet(EN_ReqVal ucSetValue);
extern void OrgDrvAirDistribModSwErrorStsSignalSet(EN_ErrVal ucSetValue);
extern void OrgOneBtnIntCirclnSwtReqSignalSet(EN_ReqVal ucSetValue);
extern void OrgOneBtnIntCirclnSwtReqErrStsSignalSet(EN_ErrVal ucSetValue);

extern void OrgCCSM_Res0SignalSet(uint8_t ucSetValue);
extern void OrgCCSM_Res4SignalSet(uint8_t ucSetValue);
extern void OrgCCSM_Res5SignalSet(uint8_t ucSetValue);
extern void LinSglHandler(void);
extern void LinSglInit(void);

#endif
