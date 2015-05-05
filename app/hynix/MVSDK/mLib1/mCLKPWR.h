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
#ifndef     _MCLKPWR_H_INC
  #define   _MCLKPWR_H_INC
            
#ifdef      EXTERN
  #undef    EXTERN
#endif

#ifdef      INSTANTIATE_CLKPWR
  #define   EXTERN
#else
  #define   EXTERN extern
#endif

#include "mREGS.h"
typedef enum {mSRC0,mSRC1,mTBG_CLK,mTBG_CLK_DIV2} mtCLKPWR_TCLK_SEL;

typedef enum {mREGVOLT_1800mv,mREGVOLT_19000mv,mREGVOLT_1850mv,mREGVOLT_2000mv} mtCLKPWR_REGULATOR_VOLTAGE;

typedef mUINT_16 mCLKPWR_CLOCK_SEL;      // TBD: can expand this type into an enum


typedef enum
{ 
    mDF_CLK_DIS     =   mBIT(0),
    mECU_CLK_DIS    =   mBIT(1),
    mSAIL_CLK_DIS   =   mBIT(2),
    mDM_CLK_DIS     =   mBIT(3),
    mTM_CLK_DIS     =   mBIT(4),
    mBM_CLK_DIS     =   mBIT(5),
    mRC_CLK_DIS     =   mBIT(6),
    mSIF_CLK_DIS    =   mBIT(8),
    mV_CLK_DIS      =   mBIT(10),
    mSERVO_CLK_DIS  =   mBIT(11),
    mCLK_PARTIAL_PWRDN1 = mBIT(12),
    mCLK_PARTIAL_PWRDN2 = mBIT(13),
    mCLK_FULL_PWRDN = mBIT(14)
} mtCLKPWR_PWRDOWN_MODE;


typedef enum
{ 
    mSD_CLK_DIS     =   mBIT(0),
    mUSB_CLK_DIS    =   mBIT(1),
    mTBG_DIS        =   mBIT(15),
} mtCLKPWR_DEV_CLK_MODE;


typedef enum
{ 
    mCPU_CLK_SEL    =   mBIT(0),
    mHDC_CLK_SEL    =   mBIT(1),
    mSRV_CLK_SEL0   =   mBIT(3),
    mSRV_CLK_SEL1   =  	mBIT(4),
    mRAB_CLK_SEL    =   mBIT(8),
    mAHB_CLK_SEL    =   mBIT(9)
} mtCLKPWR_DIVIDER1;


typedef enum 
{
    mTEST_OUTPUT_ZERO = 0,
    mTEST_OUTPUT_1,
    mTEST_OUTPUT_2,
    mTEST_OUTPUT_3,
    mTEST_OUTPUT_4,
    mTEST_OUTPUT_5,
    mTEST_OUTPUT_6,
    mTEST_OUTPUT_7,
    mTEST_OUTPUT_8,
    mTEST_OUTPUT_9,
    mTEST_OUTPUT_10,
    mTEST_OUTPUT_11,
    mTEST_OUTPUT_12,
    mTEST_OUTPUT_13,
    mTEST_OUTPUT_14,
    mTEST_OUTPUT_15
} mtCLKPWR_TEST_OUTPUT_SEL;

/*----------------------------------------------------------------------------
    Public data structure definitions and defines
 ---------------------------------------------------------------------------*/

EXTERN __inline void        mCLKPWRinitPwrDownCount     (mUINT_16 val); 
EXTERN __inline void        mCLKPWRsetPwrDownCount      (mUINT_8 val);
EXTERN __inline void        mCLKPWRsetOscStableCount    (mUINT_8 val);
EXTERN __inline void        mCLKPWRsetHBIClkPwrDown     (mUINT_8 val);  
EXTERN __inline void        mCLKPWRsetRange             (mUINT_8 hikVco, mUINT_8 np);
EXTERN __inline void        mCLKPWRsetRangeB            (mUINT_8 hikVco, mUINT_8 np);
EXTERN __inline void        mCLKPWRsrcSelSet            (mUINT_16 srcSelection);
EXTERN __inline void        mCLKPWRsrcSelClr            (mUINT_16 srcSelection);
EXTERN __inline void        mCLKPWRsrcSelInit           (mUINT_16 srcSelection);
EXTERN __inline void        mCLKPWRinitClks             (mUINT_16 divSel);
EXTERN __inline void        mCLKPWRdisPwrManagementControl  (mUINT_16 bits);  
EXTERN __inline void        mCLKPWRenPwrManagementControl   (mUINT_16 bits); 
EXTERN __inline void        mCLKPWRselTCLK              (mtCLKPWR_TCLK_SEL source);
EXTERN __inline void        mCLKPWRclockDisable         (mCLKPWR_CLOCK_SEL clockSel);
EXTERN __inline void        mCLKPWRsetVoltageRegulator  (mtCLKPWR_REGULATOR_VOLTAGE voltage);
EXTERN __inline void        mCLKPWRselTestOutputs       (mtCLKPWR_TEST_OUTPUT_SEL value); 

EXTERN __inline mUINT_8     mCLKPWRgetPwrDownCount      (void);

EXTERN __inline mUINT_8		mCLKPWRgetPwrDnDetected 	(void);      

EXTERN __inline void    mCLKPWRtbgSel               (mUINT_8 srcSel);      
EXTERN __inline void    mCLKPWRcpuDiv               (mUINT_8 divider);
EXTERN __inline void    mCLKPWRhdcDiv               (mUINT_8 divider);
EXTERN __inline void    mCLKPWRataDiv               (mUINT_8 divider);
EXTERN __inline void    mCLKPWRsrvDiv               (mUINT_8 divider);
EXTERN __inline void    mCLKPWRsetTBG               (mUINT_8 nS, mUINT_8 nF);
EXTERN __inline void    mCLKPWRsetTBGB              (mUINT_8 nS, mUINT_8 nF);
EXTERN __inline void    mCLKPWRsetSlewPN            (mUINT_8 valN, mUINT_8 valP);
EXTERN __inline void    mCLKPWRsetSlewDatStrbPN     (mUINT_8 valN, mUINT_8 valP);


EXTERN __inline void mCLKPWRsetPwrCntrl0(mUINT_16 val);
EXTERN __inline mUINT_16 mCLKPWRGetChipRev          (void); 


#ifdef __ghs__
    #pragma ghs section bss = ".rHDC_CLK_PWR"
    EXTERN volatile  mtCLK_PWR_MNGMNT rCLKPWR;  
    #pragma ghs section
#else  
    #pragma arm section zidata = "rHDC_CLK_PWR"
    EXTERN volatile  mtCLK_PWR_MNGMNT rCLKPWR;  
    #pragma arm section zidata
#endif    


/*******************************************************************
*																   
*  NAME:        mCLKPWRinitVcmSerialClock     												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  mUINT_16 Select VCM_DIVSEL, VCM_TBG_SEL, VCM_PSCL_SEL 
*              
*
*  DESCRIPTION: HAL Configures the VCM serial clock frequency as derived from TBG    
*               
*
*  RETURNS:     None
*
********************************************************************/
__inline void mCLKPWRinitFlashClock(mUINT_16 val) 
{
    rCLKPWR.clkDiv3.all = val;
}

/*******************************************************************
*																   
*  NAME:            mCLKPWRsetTBG     												   
*
*  FILENAME:        mCLKPWR.h
*
*  PARAMETERS:      mUINT_8 nS - time base generator source divider
*                   mUINT_8 nF - time base generator feedback divider
*
*  DESCRIPTION:     HAL function to load the time base generator divider   
*                   registers with the input parameters 'nS' and 'nF.' 
*
*  RETURNS:         None
*
********************************************************************/
__inline void mCLKPWRsetTBG  (mUINT_8 nS, mUINT_8 nF)
{
    rCLKPWR.TBGAcontrol.TBGnS = nS;
    rCLKPWR.TBGAcontrol.TBGnF = nF;
}

/*******************************************************************
*																   
*  NAME:        mCLKPWRsetTBGB     												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  mUINT_8 nS - time base generator source divider
*               mUINT_8 nF - time base generator feedback divider
*
*  DESCRIPTION: HAL function to load the time base generator divider   
*               registers with the input parameters 'nS' and 'nF.' 
*
*  RETURNS:     None
*
********************************************************************/
__inline void mCLKPWRsetTBGB  (mUINT_8 nS, mUINT_8 nF)
{
    rCLKPWR.TBGBcontrol.TBGnS = nS;
    rCLKPWR.TBGBcontrol.TBGnF = nF;
}

/*******************************************************************
*																   
*  NAME:        mCLKPWRtbgSel     												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  mUINT_8 srcSel - time base generator source select
*               
*
*  DESCRIPTION: HAL function to select the time base generator divider   
*               
*
*  RETURNS:     None
*
********************************************************************/
__inline void mCLKPWRtbgSel  (mUINT_8 srcSel)
{
#if 0 
    rCLKPWR.pwrDownCnt.bits.clkSel = srcSel;
#endif
}

/*******************************************************************
*																   
*  NAME:        mCLKPWRcpuDiv     												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  mUINT_8 divider - time base generator divider 
*               
*
*  DESCRIPTION: HAL function to set the cpu time base generator divider   
*               
*
*  RETURNS:     None
*
********************************************************************/
__inline void mCLKPWRcpuDiv (mUINT_8 divider)
{
    rCLKPWR.clkDiv0.cpuClk = divider;

}

/*******************************************************************
*																   
*  NAME:        mCLKPWRhdcDiv     												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  mUINT_8 divider - time base generator divider 
*               
*
*  DESCRIPTION: HAL function to set the hdc time base generator divider   
*               
*
*  RETURNS:     None
*
********************************************************************/
 __inline void mCLKPWRhdcDiv (mUINT_8 divider)
{
    rCLKPWR.clkDiv0.hdcClk = divider;
}

/*******************************************************************
*																   
*  NAME:        mCLKPWRinitEccClock     												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:   
*              
*
*  DESCRIPTION: HAL Configures ECC clock    
*               
*
*  RETURNS:     None
*
********************************************************************/
__inline void mCLKPWRinitEccClock(mUINT_16 val) 
{
    rCLKPWR.clkDiv2.all = val;
}


/*******************************************************************
*																   
*  NAME:        mCLKPWRsrcSelSet     												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  mUINT_16 srcSelection - clock source selection
*
*  DESCRIPTION: HAL function to select the clock source   
*              
*  RETURNS:     None
*
********************************************************************/
__inline void mCLKPWRsrcSelSet (mUINT_16 srcSelection)
{
    rCLKPWR.clkDiv1.all |= srcSelection;
}

/*******************************************************************
*																   
*  NAME:        mCLKPWRsrcSelClr     												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  mUINT_16 srcSelection - clock source selection
*
*  DESCRIPTION: HAL function to clr the clock source   
*              
*  RETURNS:     None
*
********************************************************************/
__inline void mCLKPWRsrcSelClr (mUINT_16 srcSelection)
{
    rCLKPWR.clkDiv1.all &= ~srcSelection;
}

/*******************************************************************
*																   
*  NAME:        mCLKPWRsrcSelInit     												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  mUINT_16 srcSelection - clock source selection
*
*  DESCRIPTION: HAL function to initialize the clock source   
*               
*  RETURNS:     None
*
********************************************************************/
__inline void mCLKPWRsrcSelInit (mUINT_16 srcSelection)
{
    rCLKPWR.clkDiv1.all = srcSelection;
}


/*******************************************************************
*																   
*  NAME:            mCLKPWRclockDisable    												   
*
*  FILENAME:        mCLKPWR.h
*
*  PARAMETERS:      type mCLKPWR_CLOCK_SEL clockSel
*
*  DESCRIPTION:     HAL function to disable specific clocks using bits     
*                   the corresponding bits in the 'clockSel' parameter. 
*
*  RETURNS:         None
*
********************************************************************/
__inline void mCLKPWRclockDisable (mCLKPWR_CLOCK_SEL clockSel)
{
    rCLKPWR.pwrMngmtCntrl.all = clockSel;
}


/*******************************************************************
*																   
*  NAME:        mCLKPWRinitPwrDownCount    												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Initialize power down count register
*
*  RETURNS:     None
*
********************************************************************/
__inline void mCLKPWRinitPwrDownCount(mUINT_16 val) 
{
    rCLKPWR.pwrDownCnt.all = val;
}

/*******************************************************************
*																   
*  NAME:        mCLKPWRsetPwrDownCount    												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  type mUINT_8 val
*
*  DESCRIPTION: HAL function to load power down count value 0-255.
*               This value is the number of oscillator clocks from
*               standby/sleep mode set to diabling TBG / oscillator.
*               0 for 1 clock, 0xFF for 256 clocks.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mCLKPWRsetPwrDownCount(mUINT_8 val) 
{
    rCLKPWR.pwrDownCnt.bits.pwrCnt = val;
}

/*******************************************************************
*																   
*  NAME:        mCLKPWRsetOscStableCount    												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  type mUINT_8 val
*
*  DESCRIPTION: HAL function to load the oscillator stable count 
*               in units of 2^12 oscillator clocks. 0 for (2^12),
*               0xF for 16 * (2^12). The circuitry will wait this 
*               number of clocks before starting normal operation
*               after power on or sleep mode.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mCLKPWRsetOscStableCount(mUINT_8 val)  
{
    rCLKPWR.pwrDownCnt.bits.oscStableCnt=val;
}

/*******************************************************************
*																   
*  NAME:        mCLKPWRgetPwrDownCount    												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to return the contents of the power
*               down count register in the clock and power 
*               management block.
*
*  RETURNS:     type mUINT_8 power down count
*
********************************************************************/
__inline mUINT_8 mCLKPWRgetPwrDownCount(void) 
{
    return rCLKPWR.pwrDownCnt.bits.pwrCnt;
}

/*******************************************************************
*																   
*  NAME:        mCLKPWRsetHBIClkPwrDown    												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  type mUINT_8 val
*
*  DESCRIPTION: HAl function to set HBI clock power down
*               000 - Normal - support both 8-bit and 16-bit PIO modes 
*               010 - only support 16-bit PIO modes  
*               011 - No clock - should set this value so the HBI 
*                     logic does not depend on a clock to detect the 
*                     Device Reset command, which is used by the host
*                     to wake up the device.
*  RETURNS:     None
*
********************************************************************/
__inline void mCLKPWRsetHBIClkPwrDown(mUINT_8 val)  
{
}

/*******************************************************************
*																   
*  NAME:        mCLKPWRenPwrManagementControl    												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  type mUINT_16 bits
*
*  DESCRIPTION: HAl function to set the bits in the Power Management
*               control register marked in the 'bits' parameter. Setting
*               bits in the Power Management register will enable
*               the power save mode for the corresponding function.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mCLKPWRenPwrManagementControl(mUINT_16 bits)  
{
    rCLKPWR.pwrMngmtCntrl.all |= bits;
}

/*******************************************************************
*																   
*  NAME:        mCLKPWRdisPwrManagementControl    												   
*
*  FILENAME:    mCLKPWR.h 
*
*  PARAMETERS:  type mUINT_16 bits
*
*  DESCRIPTION: HAl function to clear the bits in the Power management 
*               control register marked in the 'bits' parameter. Clearing
*               bits in the Power management register will disable
*               the power save mode for the corresponding function.
*
*  RETURNS:     None
*
********************************************************************/
__inline void       mCLKPWRdisPwrManagementControl(mUINT_16 bits)   
{
    rCLKPWR.pwrMngmtCntrl.all &= ~(bits);
}

/*******************************************************************
*			   											   
*  NAME:        mCLKPWRmFclockInit
*
*  FILENAME:    mCLKPWR.h
*
*  DESCRIPTION: Initialize Manteca Flash interface and its speed.
*
*  PARAMETERS:  MFClkDiv - Division for Manteca flash (parallel interface) clock.
*               SifClkSel - Serial Interface clock selector (0 = Oscillator CLK_P1, 1 = output of SIF clock divider.
*               SIFclockDiv - SIF clock prescaler+1.
*              
*  RETURNS:     None
*
********************************************************************/
__inline void mCLKPWRmFclockInit(mUINT_32 MFClkDiv, mUINT_32 SifClkSel, mUINT_32 SIFclockDiv)
{
} 


/*******************************************************************
*																   
*  NAME:        mCLKPWRgetPwrDnDetected    												   
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAl function to return the state of the Power Down 
*               Detected bit. This bit is set on wake-up condition 
*               while the device in mSleep mode.
*
*  RETURNS:     type mUINT_8
*
********************************************************************/
__inline mUINT_8 mCLKPWRgetPwrDnDetected(void)      
{
    return rCLKPWR.pwrCntrl0.bits.PwrDnDetected;
}


/*******************************************************************
*																   
*  NAME:        mCLKPWRGetChipRev
*
*  FILENAME:    mCLKPWR.h
*
*  PARAMETERS:  none
*
*  DESCRIPTION: HAL function to get chip id
*              
*
*  RETURNS:     None
*
********************************************************************/
__inline mUINT_16 mCLKPWRGetChipRev(void)
{
#define rev1P0 0x100

    return(rCLKPWR.HDCrev);
}

/*******************************************************************
*															   
*  NAME:        mCLKPWRsetPwrCntrl0    												   
*
*  FILENAME:    mCLKPWR.h 
*
*  PARAMETERS:  type mUINT_16 bits
*
*  DESCRIPTION: HAl function to initialize the SATA Clock Control  
*
*  RETURNS:     None
*
********************************************************************/
__inline void mCLKPWRsetPwrCntrl0(mUINT_16 val)
{
    rCLKPWR.pwrCntrl0.all = val;
}

#endif  //_*_H_INC

