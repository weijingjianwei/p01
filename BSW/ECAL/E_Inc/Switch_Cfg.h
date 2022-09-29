#ifndef _SWITCH_CFG_H_
#define _SWITCH_CFG_H_


#define CuiKey_ShortPressCount     100    //1s
#define CuiKey_LongPressIncCount   20     //200ms

#define CuiKey_PwOnDelayCount   150 //1.5S????2H4H4L KEY
#define CuiBCM_SignlLossCount    6   //
/*******************************************************************************
 *
 * Description:     : Macro Description Section
 *
*******************************************************************************/  
#define KEY_Kc_ShortFilterTime      50U     /*units:mSec; typeSize:16; Low bound:0; Upper Bound:65535; Bench Value:50; MAUs:; Address:0x7F0012; Description:锟教帮拷锟斤拷锟缴硷拷时锟斤�? Transform Equation:XXXXXXXX;*/
#define KEY_Kc_LongFilterTime       500U    /*units:mSec; typeSize:16; Low bound:0; Upper Bound:65535; Bench Value:300; MAUs:; Address:0x7F0013; Description:锟斤拷锟斤拷锟斤拷锟缴硷拷时锟斤�? Transform Equation:XXXXXXXX;*/
#define KEY_Kc_FirstLongFilterTime  500U    /*units:mSec; typeSize:16; Low bound:0; Upper Bound:65535; Bench Value:300; MAUs:; Address:0x7F0013; Description:锟斤拷锟斤拷锟斤拷First锟缴硷拷时锟斤拷; Transform Equation:XXXXXXXX;*/
#define KEY_Kc_OverFilterTime       60U     /*units:Sec; typeSize:8; Low bound:0; Upper Bound:255; Bench Value:30; MAUs:; Address:0x7F0013; Description:锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷时锟斤拷; Transform Equation:XXXXXXXX;*/

#define	CuiKEY_Dead_Count				 (KEY_Kc_OverFilterTime*100U)			/* 锟斤拷锟斤拷锟斤拷锟酵达拷时,6000锟轿ｏ拷每锟斤拷10ms锟斤拷锟斤拷60s	*/
#define CuiKeyTxCnt					3
#define CuiKeyTxTrmCnt			    40
#define KEY_Kc_LongPresTrm          200u     //2s
#endif
