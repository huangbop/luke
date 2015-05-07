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

#ifndef     _CONDS_H_INC
  #define   _CONDS_H_INC

#include "mGLOBALS.h"

#define mREALMONITOR            mDISABLE
#define mNUTR_SMART             mDISABLE    		// SIM_LEANMAN
#define mBUF_ACCESS_ONLY        mDISABLE            // SIM_LEANMAN
#define mPACK_FROM_RW           mDISABLE    // command packing is done by the RW task, mixed cmds do not work.
#define NV_DEEP_RW_PIPELINE     mDISABLE
#define mBYPASS_CMD_PACKING     mDISABLE
#define mDM_TBL_CREATER         mDISABLE
#define mPROGRAMMABLE_FPGA      mDISABLE
#define mMARVELL_INTERNAL       mENABLE
#define mMARVELL_WRITE_CACHE    mDISABLE             // SIM_LEANMAN
#define mMARVELL_SEQREAD_CACHE  mDISABLE             // SIM_LEANMAN
#define mMARVELL_SEQWRITE_CACHE mDISABLE             // SIM_LEANMAN
#define mMARVELL_WR_AGING_CACHE mDISABLE
#define READ_SYSFILE_ON_POWERUP mDISABLE
#define mTBG_UNLOCK_FUN         mDISABLE
#define mDSW_FUN_TEST           mDISABLE
#define mFW_ECC_RECOVERY        mDISABLE
#define mMARVELL_PM             mDISABLE
#define mIDLE_IMMED_WITH_UNLOAD mDISABLE
#define mPWR_UP_IN_STDBY        mDISABLE
#define ADVANCED_PM             mDISABLE
//#define SERIAL_ATA_FEATURE_PM   mDISABLE
#define mRESET_BUFFER_RECORD    mDISABLE
#define mPC_DISK_PRESENT        mTRUE
#define mDIAG_SW                mFALSE
#define mUSE_BIST               mFALSE
#define mPRINT_OUT              mDISABLE
#define mSCOPE_OUT              mDISABLE
#define NV_DEBUG                mDISABLE
#define DIAG_TOOL               mDISABLE

    #if (USE_DEBUG_FIFO == mDISABLE)
#define mCACHE_DEBUG            mDISABLE
#define mCACHE_DEBUG_PACK       mDISABLE        // SIM_LEANMAN
    #else
#define mCACHE_DEBUG            mENABLE        // SIM_LEANMAN
#define mCACHE_DEBUG_PACK       mDISABLE       // SIM_LEANMAN
    #endif

#define PACK_STAT               mDISABLE
#define mDPP_DEBUG              mDISABLE
#define mCACHE_DEBUG_EXTENDED   mDISABLE 
#define mNV_ALIGN_SAL           mENABLE
// If you are using Codewarrior, make change here to build a correct target.

#define mCMD_HISTORY          mDISABLE

#ifdef BLACKBIRD
  #if ( BLACKBIRD == mENABLE )
    #define mBLACK_BIRD         mENABLE
  #else
    #define mBLACK_BIRD         mDISABLE
  #endif
#else
    #define mBLACK_BIRD         mDISABLE
#endif

// Media side is always ATA interface.

#define REV_1                   1
#define REV_2                   2
#define REV_3                   3
#define REV_4                   4

//#define mFILESYS_REV            REV_1
#define mFILESYS_REV            REV_2

#define mSECURE_ERASE_SECURITY           mDISABLE
#define mSECURE_ERASE                    mDISABLE

#endif //_H_INC
