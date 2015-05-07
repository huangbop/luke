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

#ifndef     _mPLI_H_INC
  #define   _mPLI_H_INC

#include "mGLOBALS.h"
#include "mREGS.h"
#include "mCONDS.h"

// Include files that will propagate (put local include files in the .c file)

/*----------------------------------------------------------------------------
    Put Overrides here:
 ---------------------------------------------------------------------------*/
// Must Put EXTERN definition last!
#ifdef      EXTERN
  #undef    EXTERN
#endif

#ifdef      INSTANTIATE_MARVELL_PLI
  #define   EXTERN
#else
  #define   EXTERN extern
#endif

/*----------------------------------------------------------------------------
    Public data structure definitions and defines
 ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 Public Variables (other modules can use these vars by including this .h file:
 ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 Public Function Prototypes (other modules can use these functions by
 including this .h file):
 ---------------------------------------------------------------------------*/

  EXTERN __inline mUINT_16 mPLIgetSataPmState   (void);   
  EXTERN __inline mUINT_16 mPLIgetPRBSL         (void);   
  EXTERN __inline mUINT_16 mPLIgetprbsCnt1L     (void);   
  EXTERN __inline void mPLIinitPhyControl       (mUINT_16 val); 
  EXTERN __inline void mPLIinitTestControlH     (mUINT_16 val); 
  EXTERN __inline void mPLIsetPhyControl        (mUINT_16 val); 
  EXTERN __inline void mPLIinitLinkMode         (mUINT_16 val); 
  EXTERN __inline void mPLIsetLTModeLow         (mUINT_16 bits); 
  EXTERN __inline void mPLIclrLTModeLow         (mUINT_16 bits); 
  EXTERN __inline void mPLIinitPhyMode1         (mUINT_16 val); 
  EXTERN __inline void mPLIinitPhyMode2         (mUINT_16 val); 
  EXTERN __inline void mPLIinitPhyMode4         (mUINT_16 val); 
  EXTERN __inline void mPLIclrErrLo             (mUINT_16 val); 
  EXTERN __inline void mPLIclrErrHi             (mUINT_16 val); 
  EXTERN __inline void mPLIsetLoopBackData15_0  (mUINT_16 val); 
  EXTERN __inline void mPLIsetLoopBackData31_16 (mUINT_16 val); 
  EXTERN __inline void mPLIsetLoopBackData47_32 (mUINT_16 val); 
  EXTERN __inline void mPLIsetLoopBackData63_48 (mUINT_16 val); 
  EXTERN __inline void mPLIinitTestControlL     (mUINT_16 val); 
  EXTERN __inline void mPLIsetBitTestControlL   (mUINT_16 val); 
  EXTERN __inline mUINT_16  mPLIgetTestControlL (void); 
  EXTERN __inline void mPLIOOBConf3Init         (mUINT_32 val);   
  EXTERN __inline void mPLIsetPhyConfHi         (mUINT_16 val); 


  #ifdef __ghs__
    #pragma ghs section bss = ".rHDC_PHY"
    EXTERN volatile  mtPHYLINK_INTERFACE rPLI;  
    #pragma ghs section
  #else  
    #pragma arm section zidata = "rHDC_PHY"
    EXTERN volatile  mtPHYLINK_INTERFACE rPLI;  
    #pragma arm section zidata
  #endif    

/*******************************************************************
*																   
*  NAME:        mPLIinitLinkMode 
*
*  FILENAME:    mPLI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to Initialize Link mode of communcation
*
*  RETURNS:     type mUINT_16 
*
********************************************************************/
__inline void mPLIinitLinkMode (mUINT_16 val) 
{
    rPLI.ltModeLo.all = val;
}

/*******************************************************************
*																   
*  NAME:        mPLIsetLTModeLow
*
*  FILENAME:    mPLI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to set the bits contained in the parameter 
*               "val" in LTMODE Low    
*
*  RETURNS:     None
*
********************************************************************/
__inline void mPLIsetLTModeLow(mUINT_16 bits) 
{
    rPLI.ltModeLo.all |= bits;
}
__inline void mPLIsetLTModeHi(mUINT_16 bits) 
{
    rPLI.ltModeHi.all |= bits;
}

/*******************************************************************
*																   
*  NAME:        mPLIclrLTModeLow
*
*  FILENAME:    mPLI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to clear the bits contained in the parameter 
*               "val" in LTMODE Low     
*
*  RETURNS:     None
*
********************************************************************/
__inline void mPLIclrLTModeLow(mUINT_16 bits) 
{
    rPLI.ltModeLo.all &= ~(bits);
}

/*******************************************************************
 *
 *  NAME:           mPLIgetSataPmState  
 *
 *  FILENAME:       mPLI.h
 *
 *  PARAMETERS:     None
 *
 *  DESCRIPTION:    Returns the contents of SATA Status Low register
 *                  power management state.  
 *
 *  RETURNS:        type mUINT_16 
 *
 *******************************************************************/
__inline mUINT_16 mPLIgetSataPmState(void)   
{                           
    return rPLI.sataStatLow.all;
}


/*******************************************************************
*																   
*  NAME:        mPLIinitPhyControl
*
*  FILENAME:    mPLI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to Initialize Phy mode of communcation
*
*  RETURNS:    NONE 
*
********************************************************************/
__inline void mPLIinitPhyControl (mUINT_16 val) 
{
    rPLI.sataCntlLow.all = val;		// R5808
}

/*******************************************************************
*																   
*  NAME:        mPLISataConfig
*
*  FILENAME:    mPLI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to Configure SATA interface
*
*  RETURNS:     NONE 
*
********************************************************************/
__inline void mPLISataConfig (mUINT_16 val)
{
    rPLI.sataCntlLow.all &= val;	// R5808
}


__inline void mPLIsetIdlePdCnt (mUINT_8 val)
{
	rPLI.idleCnt &= 0x00FF;
	rPLI.idleCnt |= (val << 8);		// IDLE_PD_CNT  R5834
}

__inline void mPLIsetIdleTmCnt (mUINT_16 val)
{

    rPLI.idleCnt &= 0xFF00;
	rPLI.idleCnt |= val;		    // IDLE_TM_CNT  R5834
}


__inline void mPLIsetPowerCntl (mUINT_16 val)
{
    rPLI.powerCntl |= val;           // SATA POWER CONTROL R5836
}

__inline void mPLIclrPowerCntl (mUINT_16 val)
{
    rPLI.powerCntl &= ~val;           // SATA POWER CONTROL R5836
}

__inline void mPLIsetSlumberCnt (mUINT_16 val)
{
    rPLI.autoP2S &= 0xFF00;
    rPLI.autoP2S |= val;           // AUTO PARTIAL TO SLUMBER R5838
}




/*******************************************************************
*																   
*  NAME:        mPLIsetPhyControl
*
*  FILENAME:    mPLI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to set the bits contained in the parameter 
*               "val" in Phy mode of communcation
*
*  RETURNS:     None 
*
********************************************************************/
__inline void mPLIsetPhyControl (mUINT_16 val) 
{
    rPLI.sataCntlLow.all |= val;
}




/*******************************************************************
 *
 *  NAME:           mPLIOOBConf3Init  
 *
 *  FILENAME:       mPLI.h
 *
 *  PARAMETERS:     None
 *
 *  DESCRIPTION:    Init the OOB config3 reg
 *
 *  RETURNS:        void 
 *
 *******************************************************************/
__inline void mPLIOOBConf3Init(mUINT_32 val)   
{                           
    rPLI.oobConf3Lo = val & 0xFFFF;
    rPLI.oobConf3Hi = val >> 16;
}

/*******************************************************************
 *
 *  NAME:           mPLIgetPhyConfHi  
 *
 *  FILENAME:       mPLI.h
 *
 *  PARAMETERS:     None
 *
 *  DESCRIPTION:    Returns the contents of PhyConfHi register
 *
 *  RETURNS:        type mUINT_16 
 *
 *******************************************************************/
__inline mUINT_16 mPLIgetPhyConfHi(void)   
{                           
    return rPLI.phyConfHi;
}

/*******************************************************************
*																   
*  NAME:        mPLIsetPhyConfHi
*
*  FILENAME:    mPLI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to set the bits contained in the parameter 
*               "val" in PhyConfHi register
*
*  RETURNS:     None 
*
********************************************************************/
__inline void mPLIsetPhyConfHi (mUINT_16 val) 
{
    rPLI.phyConfHi |= val;
}

/*******************************************************************
*																   
*  NAME:        mPLIclrPhyConfHi
*
*  FILENAME:    mPLI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to clear the bits contained in the parameter 
*               "val" in PhyConfHi register
*
*  RETURNS:     None 
*
********************************************************************/
__inline void mPLIclrPhyConfHi (mUINT_16 val) 
{
    rPLI.phyConfHi &= ~val;
}



/*******************************************************************
*																   
*  NAME:        mPLIclrErrLo
*
*  FILENAME:    mPLI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to Initialize RxTx impedance, squelch
*
*  RETURNS:     type mUINT_16 
*
********************************************************************/
__inline void mPLIclrErrLo (mUINT_16 val) 
{
    rPLI.sataErrLow.all = val;
}

/*******************************************************************
*																   
*  NAME:        mPLIclrErrHi
*
*  FILENAME:    mPLI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to Initialize RxTx impedance, squelch
*
*  RETURNS:     type mUINT_16 
*
********************************************************************/
__inline void mPLIclrErrHi (mUINT_16 val) 
{
    rPLI.sataErrHi.all = val;  
}


/*******************************************************************
*																   
*  NAME:        mPLIinitTestControlL
*
*  FILENAME:    mPLI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to init test control L reg
*
*  RETURNS:     none 
*
********************************************************************/
__inline void mPLIinitTestControlL (mUINT_16 val) 
{
    rPLI.testCntlLo.all = val;  
}

/*******************************************************************
*																   
*  NAME:        mPLIsetBitTestControlL
*
*  FILENAME:    mPLI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to set bits in test control L reg
*
*  RETURNS:     none 
*
********************************************************************/
__inline void mPLIsetBitTestControlL (mUINT_16 val) 
{
    rPLI.testCntlLo.all |= val;  
}

/*******************************************************************
*																   
*  NAME:        mPLIgetTestControlL
*
*  FILENAME:    mPLI.h
*
*  PARAMETERS:  none
*
*  DESCRIPTION: HAL function to get data from test control L reg
*
*  RETURNS:     mUINT_16  
*
********************************************************************/
__inline mUINT_16 mPLIgetTestControlL (void) 
{
    return(rPLI.testCntlLo.all);  
}


#endif  //_*_H_INC
