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

#ifndef     _MPM_H_INC
  #define   _MPM_H_INC

#include "mGLOBALS.h"

#ifdef      EXTERN
  #undef    EXTERN
#endif

#ifdef      INSTANTIATE_MPM
  #define   EXTERN
#else
  #define   EXTERN extern
#endif

/*----------------------------------------------------------------------------
    Public data structure definitions and defines
 ---------------------------------------------------------------------------*/
#define FORCE_PU_TX			0x1
#define FORCE_PU_RX			0x2
#define PD_PLL_AUTO         0x20

#define FORCE_PU_DEFAULT	FORCE_PU_RX + FORCE_PU_TX
//if default is change above, please change the following to reverse bit for mask
#define FORCE_PU_ALL_OFF_MSK	FORCE_PU_TX	+ FORCE_PU_RX
#define FORCE_PU_ALL_ON 	FORCE_PU_TX	+ FORCE_PU_RX
#define PU_PLL_ON			0x4
#define SATA_PW_ALL_ON		PU_PLL_ON +	FORCE_PU_TX + FORCE_PU_RX

typedef enum
{
    mPM_ACTIVE,                     // Full power mode (active)
    mPM_IDLE,                       // Partial power up mode (idle)
    mPM_IDLE2,                      // All power down mode (idle2)        
    mPM_STANDBY,                    // All power down mode (standby)        
    mPM_SLEEP,                      // All power down mode (sleep)        
} mtPOWER_MODE;

typedef union
{
    mUINT_32 all;
    struct 
    {
        mUINT_32 idle                   : 1;        // Idle
        mUINT_32 idle2                  : 1;        // Idle2
        mUINT_32 standby                : 1;        // Standby
        mUINT_32 sleep                  : 1;        // sleep
        
        mUINT_32 disAutoWr              : 1;
        mUINT_32 drvReady               : 1;
        mUINT_32 chkPmCmd               : 1;
        mUINT_32 pwrUpInStdby           : 1;        // 1: enable power up in standby
        
        mUINT_32 advancedPm             : 1;        // 1: enable advanced PM
        mUINT_32 pmReady                : 1;        // 1: bit to indicate power management is ready for protection
        mUINT_32 pwrOnComplete          : 1;        // 1: bit to indicate power on complete
        mUINT_32 enDIPM                 : 1;        // 1: enable device-initiated interface power state transitions
        
        mUINT_32 devInitPartial         : 1;        // interface partial
        mUINT_32 devInitSlumber         : 1;        // interface slumber
        mUINT_32 reEnterMode            : 1;
        mUINT_32 pdAfterTxDone          : 1;

        mUINT_32 pdAfterRw              : 1;        // run mPmCmdPModeAfterRW()
        mUINT_32 cmdOccurred            : 1;        // interrupt is processed by ISR already
		mUINT_32 DIPMen                 : 1;		// DIPM enable bit
		mUINT_32 HIPMen                 : 1;		// HIPM enable bit
        mUINT_32 reserved               : 12;

    } bits;
} mtPM_FLAG;

typedef struct sPmData
{
    mtPM_FLAG       pmFlag;
    mtPOWER_MODE    curPowerMode;
	mUINT_16        mPmTimer;
	mUINT_16        mPmTimer2;
    mUINT_16        mCurAdvPmLevel;
    mUINT_32		mPmTimeOut; 
    mUINT_32        mStdbyTimer;
    mUINT_32        mPmDevInitTimerOut;
} mtPM_DATA;

/*----------------------------------------------------------------------------
 Public Data (other modules can use these vars by including this .h file:
 ---------------------------------------------------------------------------*/
EXTERN mtPM_DATA mPmData;

/*----------------------------------------------------------------------------
 Public Function Prototypes (other modules can use these functions by
 including this .h file):
 ---------------------------------------------------------------------------*/
EXTERN void mPmSetPMActive  (void);
EXTERN void mPmSetPMIdle    (void);
EXTERN void mPmSetPMIdle2   (void);
EXTERN void mPmSetPMStandby (void);
EXTERN void mPmSetPMSleep   (void);
EXTERN void mPmSetCPUIdle   (void);
EXTERN void mPmSetCPUStandby(void);
EXTERN void mPmInitialRestore(void);


#endif  //_H_INC
