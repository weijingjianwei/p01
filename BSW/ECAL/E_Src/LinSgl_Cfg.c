/***************************************************************************
 * Copyright (c) 2021 - 2025, ChangHui Vehicle Electric, Inc.
 * All rights reserved. 

|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Version   Author  Description
| ---------  --------  ------  -----------------------------------------------
| 2021-07- 15  v1.0      zbj    Creation 

|***************************************************************************/
#include "LinSgl_Cfg.h"
#include "conflin_0.h"
/* static variables */
/* -----------------------------------------------------------------------------
	 &&&~  Tx Message Buffers
----------------------------------------------------------------------------- */ 
volatile c_CCSM_msgType     g_CCSMSwitch;
volatile uint8_t uCCSM_Buf[DLC_CCSM_MSG_ID];

uint16_t status = 0;
/* -----------------------------------------------------------------------------
	 &&&~  Rx Message Buffers
 ----------------------------------------------------------------------------- */ 

void OrgVoltageFailSts_CCSMSignalSet(EN_ErrVal ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.VoltageFailSts_CCSM)
  	{
		g_CCSMSwitch.VoltageFailSts_CCSM = ((uint8_t)ucSetValue&0x01u);
  	}		
}
void OrgACOffSwtReqSignalSet(EN_ReqVal ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.ACOffSwtReq)
  	{
		g_CCSMSwitch.ACOffSwtReq = ((uint8_t)ucSetValue&0x01u);
  	}	
}
void OrgACOffSwtErrStsSignalSet(EN_ErrVal ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.ACOffSwtErrSts)
  	{
		g_CCSMSwitch.ACOffSwtErrSts = ((uint8_t)ucSetValue&0x01u);
  	}	
}
void OrgAutoModSwtReqSignalSet(EN_ReqVal ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.AutoModSwtReq)
  	{
		g_CCSMSwitch.AutoModSwtReq = ((uint8_t)ucSetValue&0x01u);
  	}

}
void OrgAutoModSwtErrStsSignalSet(EN_ErrVal ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.AutoModSwtErrSts)
  	{
		g_CCSMSwitch.AutoModSwtErrSts = ((uint8_t)ucSetValue&0x01u);
  	}

}
void OrgACRotationSwtSyncSignalSet(EN_SynVal ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.ACRotationSwtSync)
  	{
		g_CCSMSwitch.ACRotationSwtSync = ((uint8_t)ucSetValue&0x01u);
  	}
}
void OrgACRotationSwtStsSignalSet(uint8_t ucSetValue)
{
	if(((uint8_t)ucSetValue&0x3F)!= g_CCSMSwitch.ACRotationSwtSts)
  	{
		g_CCSMSwitch.ACRotationSwtSts = ((uint8_t)ucSetValue&0x3Fu);
  	}
}
void OrgACRotationSwtErrStsSignalSet(En_AirErr ucSetValue)
{
	if(((uint8_t)ucSetValue&0x3)!= g_CCSMSwitch.ACRotationSwtErrSts)
  	{
		g_CCSMSwitch.ACRotationSwtErrSts = ((uint8_t)ucSetValue&0x03u);
  	}	
}

void OrgDrvTempSwSyncSignalSet(EN_SynVal ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.DrvTempSwSync)
  	{
		g_CCSMSwitch.DrvTempSwSync = ((uint8_t)ucSetValue&0x01u);
  	}
}

void OrgDrvTempSwStsSignalSet(uint8_t ucSetValue)
{
	if(((uint8_t)ucSetValue&0x3F)!= g_CCSMSwitch.DrvTempSwSts)
  	{
		g_CCSMSwitch.DrvTempSwSts = ((uint8_t)ucSetValue&0x3Fu);
  	}
}

void OrgDrvTempSwErrorStsSignalSet(En_AirErr ucSetValue)
{
	if(((uint8_t)ucSetValue&0x3)!= g_CCSMSwitch.DrvTempSwErrorSts)
  	{
		g_CCSMSwitch.DrvTempSwErrorSts = ((uint8_t)ucSetValue&0x03u);
  	}	
}

void OrgAirInletSwtReqSignalSet(EN_ReqVal ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.AirInletSwtReq)
  	{
		g_CCSMSwitch.AirInletSwtReq = ((uint8_t)ucSetValue&0x01u);
  	}
}
void OrgAirInletSwtErrStsSignalSet(EN_ErrVal ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.AirInletSwtErrSts)
  	{
		g_CCSMSwitch.AirInletSwtErrSts = ((uint8_t)ucSetValue&0x01u);
  	}

}

void OrgCmprSwtReqSignalSet(EN_ReqVal ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.CmprSwtReq)
  	{
		g_CCSMSwitch.CmprSwtReq = ((uint8_t)ucSetValue&0x01u);
  	}	
}
void OrgCmprSwtErrStsSignalSet(EN_ErrVal ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.CmprSwtErrSts)
  	{
		g_CCSMSwitch.CmprSwtErrSts = ((uint8_t)ucSetValue&0x01u);
  	}	
}

void OrgDrvAirDistribModSwReqSignalSet(EN_ReqVal ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.DrvAirDistribModSwReq)
  	{
		g_CCSMSwitch.DrvAirDistribModSwReq = ((uint8_t)ucSetValue&0x01u);
  	}

}
void OrgDrvAirDistribModSwErrorStsSignalSet(EN_ErrVal ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.DrvAirDistribModSwErrorSts)
  	{
		g_CCSMSwitch.DrvAirDistribModSwErrorSts = ((uint8_t)ucSetValue&0x01u);
  	}

}

void OrgOneBtnIntCirclnSwtReqSignalSet(EN_ReqVal ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.OneBtnIntCirclnSwtReq)
  	{
		g_CCSMSwitch.OneBtnIntCirclnSwtReq = ((uint8_t)ucSetValue&0x01u);
  	}
}
void OrgOneBtnIntCirclnSwtReqErrStsSignalSet(EN_ErrVal ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.OneBtnIntCirclnSwtReqErrSts)
  	{
		g_CCSMSwitch.OneBtnIntCirclnSwtReqErrSts = ((uint8_t)ucSetValue&0x01u);
  	}

}


void OrgCCSM_Res0SignalSet(uint8_t ucSetValue)
{
	if(((uint8_t)ucSetValue&0xff)!= g_CCSMSwitch.CCSM_Res0)
  	{
		g_CCSMSwitch.CCSM_Res0 = ((uint8_t)ucSetValue&0xffu);
  	}
}
void OrgCCSM_Res1SignalSet(uint8_t ucSetValue)
{
	if(((uint8_t)ucSetValue&0xf)!= g_CCSMSwitch.CCSM_Res1)
  	{
		g_CCSMSwitch.CCSM_Res1 = ((uint8_t)ucSetValue&0xfu);
  	}
}
void OrgCCSM_Res2SignalSet(uint8_t ucSetValue)
{
	if(((uint8_t)ucSetValue&0x1)!= g_CCSMSwitch.CCSM_Res2)
  	{
		g_CCSMSwitch.CCSM_Res2 = ((uint8_t)ucSetValue&0x1u);
  	}
}

void OrgCCSM_Res3SignalSet(uint8_t ucSetValue)
{
	if(((uint8_t)ucSetValue&0x7)!= g_CCSMSwitch.CCSM_Res3)
  	{
		g_CCSMSwitch.CCSM_Res3 = ((uint8_t)ucSetValue&0x7u);
  	}
}

void OrgCCSM_Res4SignalSet(uint8_t ucSetValue)
{
	if(((uint8_t)ucSetValue&0xff)!= g_CCSMSwitch.CCSM_Res4)
  	{
		g_CCSMSwitch.CCSM_Res4 = ((uint8_t)ucSetValue&0xffu);
  	}
}
void OrgCCSM_Res5SignalSet(uint8_t ucSetValue)
{
	if(((uint8_t)ucSetValue&0xff)!= g_CCSMSwitch.CCSM_Res5)
  	{
		g_CCSMSwitch.CCSM_Res5 = ((uint8_t)ucSetValue&0xffu);
  	}
}
void LinSglHandler(void)
{
	 memcpy((uint8_t*)&uCCSM_Buf,(uint8_t*)&g_CCSMSwitch,DLC_CCSM_MSG_ID); 
	 l_u8_wr(CCSM_DATA0,uCCSM_Buf[0]);
	 l_u8_wr(CCSM_DATA1,uCCSM_Buf[1]>>1);
	 l_u8_wr(CCSM_DATA2,uCCSM_Buf[2]);
	 l_u8_wr(CCSM_DATA3,uCCSM_Buf[3]);
	 l_u8_wr(CCSM_DATA4,uCCSM_Buf[4]);
	 l_u8_wr(CCSM_DATA5,uCCSM_Buf[5]);
	 l_u8_wr(CCSM_DATA6,uCCSM_Buf[6]);
	 l_u8_wr(CCSM_DATA7,uCCSM_Buf[7]);

}
void LinSglInit(void)
{
	/*
	OrgCCSM_Res0SignalSet(0xFF);
	OrgCCSM_Res1SignalSet(0xFF);
	OrgCCSM_Res2SignalSet(0xFF);
	OrgCCSM_Res3SignalSet(0xFF);
	OrgCCSM_Res4SignalSet(0xFF);
	OrgCCSM_Res5SignalSet(0xFF);
	*/
}