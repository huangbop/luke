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
#ifndef     _MPHYLINK_H_INC
  #define   _MPHYLINK_H_INC

#include "mGLOBALS.h"
#include "mREGS.h"
#include "mErrors.h"
#include "mPLI.h"

#ifdef      EXTERN
  #undef    EXTERN
#endif

#ifdef      INSTANTIATE_MHOST
  #define   EXTERN
#else
  #define   EXTERN extern
#endif

/*----------------------------------------------------------------------------
    Public data structure definitions and defines
 ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 Public Data (other modules can use these vars by including this .h file:
 ---------------------------------------------------------------------------*/
 
/*----------------------------------------------------------------------------
 Public Function Prototypes (other modules can use these functions by
 including this .h file):
 ---------------------------------------------------------------------------*/

EXTERN INLINE void mPhyLinkInitPhyMode1(mUINT_16 val);
EXTERN INLINE void mPhyLinkInitPhyMode2(mUINT_16 val);
EXTERN INLINE void mPhyLinkInitPhyMode4(mUINT_16 val);
EXTERN INLINE void mPhyLinkInitLinkMode (void);
EXTERN INLINE void mPhyLinkInitPhyControl (mUINT_16 val);
EXTERN INLINE void mPhyLinkClrErrLo (mUINT_16 val);
EXTERN INLINE void mPhyLinkClrErrHi (mUINT_16 val);
EXTERN void mInitSataPhyLink(void);
#define mPhyLinkSetPhyControl(v)    mPLIsetPhyControl(v)	// SATA CONTROL LOW R5808
#define mPhyLinkGetSataPmState()    mPLIgetSataPmState()
#define mPhyLinkSetSataPmState(v)   mPLISataConfig(v)

#define mPhyLinkSetLTModeLow(v)     mPLIsetLTModeLow(v)		// LTMODE LOW R580C
#define mPhyLinkClrLTModeLow(v)     mPLIclrLTModeLow(v)

#define mPhyReadRegPhyConfHi(v)		mPLIgetPhyConfHi(v)		// PHY CONFIG HIGH R5832		
#define mPhyLinkSetPhyConfHi(v)		mPLIsetPhyConfHi(v)
#define mPhyLinkClrPhyConfHi(v)		mPLIclrPhyConfHi(v)

#define mPhyLinkSetIdlePdCnt(v)     mPLIsetIdlePdCnt(v);
#define mPhyLinkSetIdleTmCnt(v)     mPLIsetIdleTmCnt(v);
#define mPhyLinkSetPowerCntl(v)     mPLIsetPowerCntl(v);    // SATA POWER CONTROL R5836
#define mPhyLinkClrPowerCntl(v)     mPLIclrPowerCntl(v);    // SATA POWER CONTROL R5836
#define mPhyLinkSetSlumberCnt(v)    mPLIsetSlumberCnt(v);


#endif  //_H_INC
