// =======        test example     ============================================
//                                                                           
//     Copyright (c) Marvell Corporation 2000-2009  -  All rights reserved     
//                                                                           
//  This computer program contains confidential and proprietary information, 
//  and  may NOT  be reproduced or transmitted, in whole or in part,  in any 
//  form,  or by any means electronic, mechanical, photo-optical, or  other- 
//  wise, and  may NOT  be translated  into  another  language  without  the 
//  express written permission from Marvell Corporation.                     
//                                                                           
// ============================================================================
// =      C O M P A N Y      P R O P R I E T A R Y      M A T E R I A L       =
// ============================================================================


/*----------------------------------------------------------------------------
 Include files:
 ---------------------------------------------------------------------------*/
#define   INSTANTIATE_MPM
#include "mPm.h"
#include "mBm.h"
#include "mCLKPWR.h"
#include "mSFRS.h"
//#include "mSerial.h" 
#include "mHDC.h"
//#include "mBfr.h"
#include "mUART.h"

  #include "mPhyLink.h"
  #include "mHost.h"
  //#include "Params.h" 

  #include "mSFRS2.h"      
  #include "mTIMER.h"      


#define Zuma20 mENABLE
#define SELF_REFRESH mDISABLE

#define OLD_RESET_TBGDDR mDISABLE
#define DIV_OSC_BY_8 mENABLE

#if (mTHUMB_MODE == mENABLE)
#pragma thumb
#endif

#ifndef mtNV_INTERF_TYPE
typedef enum
{
    mAsynchronous = 0,     
    mOnfiSyn = 1     
}mtNV_INTERF_TYPE;
#endif



/*******************************************************************
*                                                                  
*  NAME:        mPmRestoreClk
*
*  FILENAME:    mPm.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Restore clock from any power mode
*
*  RETURNS:     None
*
*  DATE         BY              DESCRIPTION 
*  01/08/06     Roger Sha       Initial Release
********************************************************************/
void mPmRestoreClk(void)
{

}

/*******************************************************************
*                                                                  
*  NAME:        mPmSetPMActive
*
*  FILENAME:    mPm.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Set power mode to active
*
*  RETURNS:     None
*
*  DATE         BY              DESCRIPTION 
*  11/21/02     Roger Sha       Initial Release
********************************************************************/
void mPmSetPMActive(void)
{ 

    // enable ECC clock
    rCLKPWR.clkDiv2.bits.eccClkDis = 0;
}

/*******************************************************************
*                                                                  
*  NAME:        mPmSetPMIdle
*
*  FILENAME:    mPm.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Set power mode to idle
*
*  RETURNS:     None
*
*  DATE         BY              DESCRIPTION 
*  11/21/02     Roger Sha       Initial Release
********************************************************************/
void mPmSetPMIdle(void)
{ 
    // disable ECC clock
    rCLKPWR.clkDiv2.bits.eccClkDis = 1;
}

/*******************************************************************
*                                                                  
*  NAME:        mPmSetPMIdle2
*
*  FILENAME:    mPm.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Set power mode to idle2
*
*  RETURNS:     None
*
*  DATE         BY              DESCRIPTION 
*  03/16/07     Roger Sha       Initial Release
********************************************************************/
void mPmSetPMIdle2(void)
{

}

/*******************************************************************
*                                                                  
*  NAME:        mPmSetPMStandby
*
*  FILENAME:    mPm.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Set power mode to standby
*
*  RETURNS:     None
*
*  DATE         BY              DESCRIPTION 
*  11/21/02     Roger Sha       Initial Release
********************************************************************/
void mPmSetPMStandby(void)
{
/// VG2 ///
#if (mSOC == m9174)
    rPLI.ltModeLo.all |= mBIT(0);                   // R580C - set TXCWAKE_hold
    rCLKPWR.clkDiv1.all &= ~(mBIT(0) + mBIT(1));	// RA804: CPU and BM clk from OSC
    // switch all clk to OSC
    rCLKPWR.clkDiv3.all &= ~mBIT(6);				// RA81A: FLASH clk
	rCLKPWR.clkDiv2.all &= ~mBIT(6);				// RA818: ECC clk
	(*(mUINT_16* )0x1C00A836) &= ~mBIT(6);			// RA836: XM clk (clkDiv6)
	rTimer.counterClkCtrl.all &= ~mBIT(6);			// RA230: CNTR clk
	rUART.baudRate.all &= ~mBIT(15);				// RA630: UART clk
        
    /// Power Down the NFLASH_TOP power island /////////////
    rCLKPWR.pwrCntrl0.all &= 0xFFFE;        // RA808 - Clear ISOB to isolate NFLASH_TOP outputs
    rCLKPWR.pwrCntrl0.all &= 0xFFDF;        // RA808 - Clear RSTB_NF_TOP to reset NFLASH_TOP
    rCLKPWR.pwrCntrl0.all |= 0x0006;        // RA808 - Set PWRSW_SLP = 3 to switch off NFLASH_TOP power island
	/////////////////////////////////////////////////////////

    rCLKPWR.TBGAcontrol.disTBGA = 1;        // RA80C _test, turn off TBGA
    rCLKPWR.TBGBcontrol.disTBGB = 1;        // test, turn off TBGB
#endif // (mSOC == m9174)


/// DA VINCI ///

}

/*******************************************************************
*                                                                  
*  NAME:        mPmSetPMSleep
*
*  FILENAME:    mPm.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Set power mode to sleep
*
*  RETURNS:     None
*
*  DATE         BY              DESCRIPTION 
*  11/21/02     Roger Sha       Initial Release
********************************************************************/
void mPmSetPMSleep(void)
{
    mPmSetPMStandby();

}


/*******************************************************************
*                                                                  
*  NAME:            mPmInitialRestore
*
*  FILENAME:        mPm.c
*
*  PARAMETERS:      None
*
*  DESCRIPTION:     Initial restore power from standby or sleep
*
*  RETURNS:         None
*
*  DATE             BY              DESCRIPTION 
*  11/21/02         Roger Sha       Initial Release
********************************************************************/
void mPmInitialRestore(void)
{
#if (mSOC == m9174)
    ///while (!(rCLKPWR.pwrCntrl0.all &= 0x8000));
    rCLKPWR.pwrCntrl0.all |= mBIT(15);      // RA808[15] - Clear PWR_DN_DET
    mPhyLinkSetPhyConfHi(0x0004);           // R5832[2] - Set PU_PLL
    
    rCLKPWR.TBGAcontrol.disTBGA = 0;     // turn on TBGA
    rCLKPWR.TBGBcontrol.disTBGB = 0;     // turn on TBGB
    while ((!rCLKPWR.TBGAcontrol1.lock) && (!rCLKPWR.TBGBcontrol1.lock));
        
    while(((*(mUINT_16* )0x1C00A816)&0x000F)!= 0);    // wait for Stable Counter    

    // switch all the clocks back to TBG
    rCLKPWR.clkDiv2.all |= mBIT(6);				// RA818: ECC clk
    rCLKPWR.clkDiv3.all |= mBIT(6);				// RA81A: FLASH clk
    (*(mUINT_16* )0x1C00A836) |= mBIT(6);		// RA836: XM clk (clkDiv6)
    rUART.baudRate.all |= mBIT(15);				// RA630: UART clk
    rTimer.counterClkCtrl.all |= mBIT(6);		// RA230: CNTR clk 
    rCLKPWR.clkDiv1.all |= mBIT(0) + mBIT(1);	// RA804: CPU and BM clk

    // Power Up the NFLASH_TOP power island
    rCLKPWR.pwrCntrl0.all &= 0xFFFD;
    rCLKPWR.pwrCntrl0.all |= 0x0004;			        // RA808 - Set PWRSW_SLP = 2 to weak-on NFLASH_TOP power island
	while ((rCLKPWR.pwrCntrl0.all & 0x0018) != 0x0010);	// Wait for PWRSW_SLP_O[4:3] = 2
	//DelayUS(300);
	rCLKPWR.pwrCntrl0.all &= 0xFFF9;					// RA808 - Set PWRSW_SLP = 0 - Power On NFLASH_TOP
	while ((rCLKPWR.pwrCntrl0.all & 0x0018) != 0x0000); // Wait for PWRSW_SLP_O = 0
	rCLKPWR.pwrCntrl0.all |= 0x0020;					// RA808 - Deassert Soft Reset to NFLASH_TOP
	rCLKPWR.pwrCntrl0.all |= 0x0001;					// RA808 - Set ISOB - Disable Isolation
	///////////////////////////////////////////

    while (!(rBM.stat2.all & 0x8000));				    // wait for DDR ready
    rBM.dramCntl1.all &= ~mBIT(3);
       
    rCLKPWR.pwrCntrl0.all &= 0xFFF9;        // RA808 - Set PWRSW_SLP = 0 to turn on NFLASH_TOP power island
    while ((rCLKPWR.pwrCntrl0.all & 0x0018) != 0x0000); // Wait for PWRSW_SLP_O = 0
    rCLKPWR.pwrCntrl0.all |= 0x0020;        // RA808 - Set RSTB_NF_TOP to release NFLASH_TOP
    rCLKPWR.pwrCntrl0.all |= 0x0001;        // RA808 - Set ISOB to release NFLASH_TOP outputs
       
    rPLI.ltModeLo.all &= ~mBIT(0);                      // R580C - Clear TXCWAKE_hold

#if 0
	NvSetUpSeqMode();
  #if (mNV_ONFI == mENABLE)
    NvSetupOnfiMode(mNV_ONFI_MODE, 1);        // restore syn mode 
  #endif 
#endif 
#endif // (mSOC == m9174)


  

}

/*******************************************************************
*                                                                  
*  NAME:            mPmSetCPUStandby
*
*  FILENAME:        mPm.c
*
*  PARAMETERS:      None
*
*  DESCRIPTION:     Set ARM CPU to standby
*
*  RETURNS:         None
*
*  DATE             BY              DESCRIPTION 
*  11/21/02         Roger Sha       Initial Release
********************************************************************/
void mPmSetCPUStandby(void)
{

// Due to a bug in Solaris 1 step down hardware design, 
// we cannot utilize step down for RAB clock.
// 1. RAB clock has to be step down only when both core requires to do so,
//  but that hasn't been implemented in Solaris 1.
// 2.Some interrupts can not wake up CPU clock from step down.

// Due to a bug in Solaris 1 step down hardware design, 
// we cannot utilize step down for CPU clock.
// 1. Some interrupts can not wake up CPU clock from step down.

#ifdef __ghs__
    __asm("mov r0, #0x0");
    __asm("MCR p15, 0, r0, c7, c0, 4");
#else
    {
        mINT_32 rd=0;

        __asm
        {
            MCR p15, 0, rd, c7, c0, 4
        }
    }
//    mSFR2clrStepDnCntl2(0x0100);
//    mSFR2clrStepDnCntl1(0x0100);
//    mSFR2clrStepDnCntl4(0x0100);
#endif
}



#pragma arm
