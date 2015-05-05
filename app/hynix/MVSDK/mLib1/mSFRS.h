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

#ifndef     _mSFRS_H_INC
  #define   _mSFRS_H_INC

#include "mGLOBALS.h"

#ifdef      EXTERN
  #undef    EXTERN
#endif

#ifdef      INSTANTIATE_SYMBOLS_SPEC_FUNC_REGS		 // symbols for SFRs
  #define   EXTERN
#else
  #define   EXTERN extern
#endif

//#SYMGEN_OMIT

typedef enum 
{
    mFLASH_WAIT_ZERO = 0,	    // spelled out to avoid mixing with alphabet "O"
    mFLASH_WAIT_1,
    mFLASH_WAIT_2,
    mFLASH_WAIT_3,
    mFLASH_WAIT_4,
    mFLASH_WAIT_5,
    mFLASH_WAIT_6,
    mFLASH_WAIT_7,
    mFLASH_WAIT_8,
    mFLASH_WAIT_9,

    mFLASH_WAIT_10,
    mFLASH_WAIT_11,
    mFLASH_WAIT_12,
    mFLASH_WAIT_13,
    mFLASH_WAIT_14,
    mFLASH_WAIT_15
} mtFLASH_WAIT_STATE;

//#SYMGEN_OMIT_END

//----------------------------------------------------------------------------
typedef union
{
    mUINT_16  all;
    struct
    {
        mUINT_16 fiq0Select     : 4;
        mUINT_16 irq0Select     : 4;
        mUINT_16 fiq1Select     : 4;
        mUINT_16 irq1Select     : 4;
    } bits;
} mtINTR_CNTL0;


// This is one of those registers that are useless but have to be initialized.
typedef union
{
    mUINT_16  all;
    struct
    {
        mUINT_16 C0SrvIntLatEn  : 1;
        mUINT_16 C0HdcIntLatEn  : 1;
        mUINT_16 rsvd0          : 1;
        mUINT_16 C0SataIntLatEn : 1;

        mUINT_16 rsvd1          : 4;

        mUINT_16 C1SrvIntLatEn  : 1;
        mUINT_16 C1HdcIntLatEn  : 1;
        mUINT_16 rsvd2          : 1;
        mUINT_16 C1SataIntLatEn : 1;

        mUINT_16 rsvd3          : 2;
        mUINT_16 JTAGResetDis   : 1;
        mUINT_16 JTAGSoftReset  : 1;
    } bits;
} mtINTR_CNTL1;


typedef struct
{
    mtINTR_CNTL0    cpuIntrCntl0;           // 0xa000
    mtINTR_CNTL1    cpuIntrCntl1;           // 0xa002
    mUINT_16        warmReset;              // 0xa004
    mUINT_16        RSVD0;                  // 0xa006

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 manualFlush    : 1;
            mUINT_16 wrapDis        : 1;
            mUINT_16 lcFlushDis     : 1;
            mUINT_16 rsvd0          : 2;
            mUINT_16 LC_wtc         : 1;
            mUINT_16 LC_tmx_sel     : 1;
            mUINT_16 LC_fsm_sel     : 1;

            mUINT_16 FLCFlush       : 1;
            mUINT_16 LC_rtc         : 3;

            mUINT_16 rsvd1          : 4;
        } bits;
    } cpuConfig;                            // 0xa008
    mUINT_16        cpuIntrCntl2;           // 0xa00a
    mUINT_16        RSVD1[0x10];            // 0xa00c-0xa02a

    mUINT_16        watchdogLimitLo;        // 0xa02c
    mUINT_16        watchdogLimitHi;        // 0xa02e

    mUINT_16        HIPCCommand0Lo;         // 0xa030
    mUINT_16        HIPCCommand0Hi;         // 0xa032
    mUINT_16        HIPCCommand1Lo;         // 0xa034
    mUINT_16        HIPCCommand1Hi;         // 0xa036
    mUINT_16        HIPCCommand2Lo;         // 0xa038
    mUINT_16        HIPCCommand2Hi;         // 0xa03a
    mUINT_16        SIPCCommand0Lo;         // 0xa03c
    mUINT_16        SIPCCommand0Hi;         // 0xa03e

    mUINT_16        HIPCStatus;             // 0xa040
    mUINT_16        SIPCStatus;             // 0xa042
    
    mUINT_16        RSVD2[6];               // 0xa044-0xa4e
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 rsved0               : 1;
            mUINT_16 DTCM_ECC_WB_En       : 1;
            mUINT_16 DTCM_ECC_DEC_En      : 1;
            mUINT_16 DTCM_ECC_ENC_En      : 1;
            mUINT_16 ITCM_ECC_RMW_En      : 1;
            mUINT_16 rsved5               : 1;
            mUINT_16 ITCM_ECC_DEC_En      : 1;
            mUINT_16 ITCM_ECC_ENC_En      : 1;
            mUINT_16 ITCM_ECC_RMW_Wr_En   : 1;
            mUINT_16 rsved9To11           : 3;
            #if (VG_REV_2_0 == mDISABLE)
            mUINT_16 DTCM_Err_Cntr_Rst_C0 : 1;
            mUINT_16 DTCM_Err_Cntr_Rst_C1 : 1;
            mUINT_16 ITCM_Err_Cntr_Rst_C0 : 1;
            mUINT_16 ITCM_Err_Cntr_Rst_C1 : 1;
            #else
            mUINT_16 rsved12to15          : 4;
            #endif //(VG_REV_2_0 == mDISABLE)
        } bits;
    } TCMCtrl;                            // 0xa050
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 DTCM_C0 : 4;
            mUINT_16 DTCM_C1 : 4;
            mUINT_16 ITCM_C0 : 4;
            mUINT_16 ITCM_C1 : 4;
        } bits;
    } TCMErrCntr;                            // 0xa052
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 resrved0  : 1;
            mUINT_16  address  : 14;
            mUINT_16 resrved1  : 1;
        } bits;
    } DTCM_ECCHiBankErrAddrC0;                            // 0xa054
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 resrved0  : 1;
            mUINT_16  address  : 14;
            mUINT_16 resrved1  : 1;
        } bits;
    } DTCM_ECCLoBankErrAddrC0;                            // 0xa056
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 loBankErrBytes : 4;
            mUINT_16 loBankErr      : 2;
            #if (VG_REV_2_0 == mDISABLE)
            mUINT_16 resrved0       : 2;
            #else
            mUINT_16 abortEn        : 1;
            mUINT_16 Err_Cntr_Rst   : 1;
            #endif //(VG_REV_2_0 == mDISABLE)
            mUINT_16 hiBankErrBytes : 4;
            mUINT_16 hiBankErr      : 2;
            #if (VG_REV_2_0 == mDISABLE)
            mUINT_16 corrFlagReset  : 1;
            #else
            mUINT_16 resrved1       : 1;
            #endif //(VG_REV_2_0 == mDISABLE)
            mUINT_16 errFlagReset   : 1;
        } bits;
    } DTCM_ECCErrStatusC0;                            // 0xa058
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 resrved0  : 1;
            mUINT_16  address  : 14;
            mUINT_16 resrved1  : 1;
        } bits;
    } DTCM_ECCHiBankErrAddrC1;                            // 0xa05a
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 resrved0  : 1;
            mUINT_16  address  : 14;
            mUINT_16 resrved1  : 1;
        } bits;
    } DTCM_ECCLoBankErrAddrC1;                            // 0xa05c
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 loBankErrBytes : 4;
            mUINT_16 loBankErr      : 2;
            #if (VG_REV_2_0 == mDISABLE)
            mUINT_16 resrved0       : 2;
            #else
            mUINT_16 abortEn        : 1;
            mUINT_16 Err_Cntr_Rst   : 1;
            #endif //(VG_REV_2_0 == mDISABLE)
            mUINT_16 hiBankErrBytes : 4;
            mUINT_16 hiBankErr      : 2;
            #if (VG_REV_2_0 == mDISABLE)
            mUINT_16 corrFlagReset  : 1;
            #else
            mUINT_16 resrved1       : 1;
            #endif //(VG_REV_2_0 == mDISABLE)
            mUINT_16 errFlagReset   : 1;
        } bits;
    } DTCM_ECCErrStatusC1;                            // 0xa05e
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 address   : 15;
            mUINT_16 resrved0  : 1;
        } bits;
    } ITCM_ErrAddrC0;                            // 0xa060
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 errBytes      : 4;
            #if (VG_REV_2_0 == mDISABLE)
            mUINT_16 corrErr       : 1;
            #else
            mUINT_16 resrved0      : 1;
            #endif //(VG_REV_2_0 == mDISABLE)
            mUINT_16 err           : 1;
            #if (VG_REV_2_0 == mDISABLE)
            mUINT_16 corrFlagReset : 1;
            #else
            mUINT_16 resrved1      : 1;
            #endif //(VG_REV_2_0 == mDISABLE)
            mUINT_16 errFlagReset  : 1;
            #if (VG_REV_2_0 == mDISABLE)
            mUINT_16 resrved0      : 8;
            #else
            mUINT_16 Err_Cntr_Rst  : 1;
            mUINT_16 resrved2      : 7;
            #endif //(VG_REV_2_0 == mDISABLE)
        } bits;
    } ITCM_ECCErrStatusC0;                            // 0xa062
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 address   : 15;
            mUINT_16 resrved0  : 1;
        } bits;
    } ITCM_ErrAddrC1;                            // 0xa064
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 errBytes      : 4;
            #if (VG_REV_2_0 == mDISABLE)
            mUINT_16 corrErr       : 1;
            #else
            mUINT_16 resrved0      : 1;
            #endif //(VG_REV_2_0 == mDISABLE)
            mUINT_16 err           : 1;
            #if (VG_REV_2_0 == mDISABLE)
            mUINT_16 corrFlagReset : 1;
            #else
            mUINT_16 resrved1      : 1;
            #endif //(VG_REV_2_0 == mDISABLE)
            mUINT_16 errFlagReset  : 1;
            #if (VG_REV_2_0 == mDISABLE)
            mUINT_16 resrved0      : 8;
            #else
            mUINT_16 Err_Cntr_Rst  : 1;
            mUINT_16 resrved2      : 7;
            #endif //(VG_REV_2_0 == mDISABLE)
        } bits;
    } ITCM_ECCErrStatusC1;                            // 0xa066
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 romEccErrStatusC0  : 2;
            mUINT_16 romEccErrStatusC1  : 2;
            mUINT_16 resrved0           : 11;
            mUINT_16 ECCEn              : 1;
        } bits;
    } ROM_ECCConfigAndStatus;               // 0xa068
    mUINT_16        RSVD3[27];              // 0xa06a-0x09e

    mUINT_16        serMemCntrl0;           // 0xa0a0
    mUINT_16        serMemCntrl1;           // 0xa0a2
    mUINT_16        reservedA4;             // 0xa0a4
    mUINT_16        serMemDataOut;          // 0xa0a6
    mUINT_16        reservedA8;             // 0xa0a8
    mUINT_16        serMemDataIn;           // 0xa0aa
    mUINT_16        PAD_RA0AC[2];           // 0xa0ac--0xa0ae
    mUINT_16        etmCntl1;               // 0xa0B0
    mUINT_16        etmCntl2;               // 0xa0B2
    mUINT_16        etmCntl3;               // 0xa0B4
    mUINT_16        etmCntl4;               // 0xa0B6
    mUINT_16        etmCntl5;               // 0xa0B8
    mUINT_16        etmCntl6;               // 0xa0BA
    mUINT_16        etmCntl7;               // 0xa0BC
    mUINT_16        etmCntl8;               // 0xa0BE
} mtDOH_SFRS;


typedef union
{
    mUINT_16  all;
    struct
    {
        mUINT_16 servoInt       : 1;
        mUINT_16 hdcInt         : 1;
        mUINT_16 rsvd0          : 1;
        mUINT_16 sataInt        : 1;

        mUINT_16 rsvd1          : 9;
        mUINT_16 comRxLatched   : 1;
        mUINT_16 comTx          : 1;
        mUINT_16 watchdogTO     : 1;
    } bits;
} mtCPU_INTR;					   


typedef union
{
    mUINT_16  all;
    struct
    {
        mUINT_16 IPCCmdWritten  : 1;
        mUINT_16 IPCStatusRead  : 1;
        mUINT_16 uartRx         : 1;
        mUINT_16 uartTx         : 1;

        mUINT_16 rsvd0          : 1;
        mUINT_16 minnowSpinInt  : 1;
        mUINT_16 servSpinInt    : 1;
        mUINT_16 test16         : 1;

        mUINT_16 timer0         : 1;
        mUINT_16 timer1         : 1;
        mUINT_16 timer2         : 1;
        mUINT_16 timer3         : 1;

        mUINT_16 timer4         : 1;
        mUINT_16 tbgUnlock      : 1;
        mUINT_16 rsvd           : 1;
        mUINT_16 itcmRmwEccInt  : 1;
    } bits;
} mtPERI_INTR;					   


typedef struct
{
    mtCPU_INTR      cpuIntrStatus;          // 0x0000
    mtCPU_INTR      cpuIntrEnable;          // 0x0002
    mtPERI_INTR     periIntrStatus;         // 0x0004
    mtPERI_INTR     periIntrEn;             // 0x0006
    union
    {
        mUINT_16 all;
        
        struct
        {
            mUINT_16 swFiq      : 1;
            mUINT_16 swIrq      : 1;
            mUINT_16 rsvd0      : 14;
        } bits;
    } intrControl;                          // 0x0008

    mUINT_16        RSVD0[3];               // 0x000a-0x000e

    mUINT_16        watchdogTOAddrLo;       // 0x0010
    mUINT_16        watchdogTOAddrHi;       // 0x0012
    mUINT_16        ControlStatus;          // 0x0014
    mUINT_16        RSVD1[0x73];            // 0x0016-0x00fa
    mUINT_16        CPUMode1Reg;            // 0x00fc
    mUINT_16        CPUTimingCntl;          // 0x00fe
    mUINT_8         RSVD2[0xB030-0x100];    // 0x0100-0xB02F
    mUINT_32        desWrData;              // 0xB030-0xB033
    mUINT_8         RSVD3[0xB050-0xB034];   // 0xB034-0xB04F
    mUINT_32        auxWrData;              // 0xB050-0xB053
#if (VG_REV_2_0 == mENABLE)
    mUINT_16        rsvdB054_B05E[6];
    mUINT_32        auxcWrData;              // 0xB060-0xB063
    mUINT_16        rsvdB064_B072[8];
    mUINT_32        auxeRdData;              // 0xB074-0xB077
#else    
    mUINT_32        auxRdData;              // 0xB054-0xB057
#endif
} mtCPU_REG;


typedef struct
{
    union
    {
        mUINT_16 all16;   
        struct 
        {
            mUINT_16  dataInCount           :5; 	// number of 16-bit data words in one read
            mUINT_16  reserved              :11; 
        }bit;           
	} count;					// REG 8100

    union 
    {
        mUINT_16 all16;   
        struct 
        {
            mUINT_16  serialParallel        :1; 	//parallel = 0  serial = 1
            mUINT_16  eccEnable             :1;  
            mUINT_16  eccErrorInturuptEnable:1; 
            mUINT_16  reserved              :1; 
            mUINT_16  resetFlash  		    :1;  
            mUINT_16  resetFlashInterface   :1; 
            mUINT_16  writeEnable           :1;     // write protect
            mUINT_16  enableFlashInterface  :1;	    // 1 = enable
            mUINT_16  resetLCacheFlags      :1; 	//MFLC invalid
            mUINT_16  resetLCache           :1;
            mUINT_16  reserved2             :6; 
        }bit;           
	} config;                                       // REG 8102

	mUINT_32    address;                            // REG 8104	- 8106		 address high and low

    union
    {
        mUINT_16 all16;   
        struct 
        {
            mUINT_16  flashCmd	            :8; 
            mUINT_16  ead		            :2; 	// instruction code bits EAD 8-9
            mUINT_16  reserved              :2; 
            mUINT_16  writeOpStart          :1; 
            mUINT_16  eraseOpStart          :1; 
            mUINT_16  readStatusStart       :1; 
            mUINT_16  infoReadStart         :1; 	// Also for read status ??
        }bit;           
	} cmd;                                          // REG 8108

    union
    {
        mUINT_16 all16;   
        struct 
        {
            mUINT_16  commandDone           : 1; 
            mUINT_16  readFifoEmpty         : 1;    //TEST ONLY 
            mUINT_16  readFifoOverflow      : 1;    //TEST ONLY
            mUINT_16  readFifoUnderflow     : 1;    //TEST ONLY
            mUINT_16  infoFifoEmpty         : 1;    //TEST ONLY
            mUINT_16  infoFifoOverflow      : 1;    //TEST ONLY
            mUINT_16  infoFifoUnderflow     : 1;    //TEST ONLY
            mUINT_16  infoEccError          : 1;    //TEST ONLY
            mUINT_16  reserved              : 8; 
        }bit;           
    } interfaceStatus;				                // REG 810A

	union
    {
        mUINT_16 all16;   
        struct 
        {
            mUINT_16  flashStatus           : 8; 
            mUINT_16  reserved              : 8; 
        }bit;           
    } flashStatus;						            // REG 810C

	mUINT_16  reserved_810E;				        // REG 810E

	mUINT_32 	DATA;					            // REG 8110 -8112 DATA LOW DATA HIGH

} mtMANTECA_INTERFACE;	  


#ifdef __ghs__
    #pragma ghs section bss = ".rSOC_SFRS"
    EXTERN volatile  mtDOH_SFRS     rSFRS;
    #pragma ghs section bss = ".cpu_reg"
    EXTERN volatile  mtCPU_REG      rCPU;
    #pragma ghs section bss = ".rSOC_MANTECA"
    EXTERN volatile  mtMANTECA_INTERFACE    rMFIF;
    #pragma ghs section
#else  
    #pragma arm section zidata = "rSOC_SFRS"
    EXTERN volatile  mtDOH_SFRS     rSFRS;
    #pragma arm section zidata = "cpu_reg"
    EXTERN volatile  mtCPU_REG      rCPU;	
//    #pragma arm section zidata = "rSOC_sMANTECA"
//    EXTERN volatile  mtMANTECA_INTERFACE    rMFIF;
    #pragma arm section zidata
#endif    

#define mICU_FC             mBIT(0)
#define mICU_HDC            mBIT(1)
#define mICU_PERIPHERALS    mBIT(2)
#define mICU_ESATA          mBIT(3)  

EXTERN INLINE void          mSFRmFlashIfaceEnable   (void);
EXTERN INLINE void          mSFRmFparallelMode      (void);
EXTERN INLINE void          mSFRclrSwIrq            (void);
EXTERN INLINE void          mSFRgenerateSwIrq       (void);
EXTERN INLINE void          mSFRinitcpuIntrCntl1    (void);
EXTERN INLINE void          mSFRinitcpuIntrCntl2    (void);

EXTERN INLINE void          mSFRfiq0Sel             (mUINT_8 value);
EXTERN INLINE void          mSFRirq0Sel             (mUINT_8 value);
EXTERN INLINE void          mSFRfiq1Sel             (mUINT_8 value);
EXTERN INLINE void          mSFRirq1Sel             (mUINT_8 value);

EXTERN INLINE void          mCPUintrEnInit          (mUINT_16 value);
EXTERN INLINE void          mCPUintrEn              (mUINT_16 value);
EXTERN INLINE void          mCPUintrDis             (mUINT_16 value);
EXTERN INLINE void          mCPUClrIntrStatus       (mUINT_16 bitMask);
EXTERN INLINE void          mSFRintrEnInit          (mUINT_16 value);
EXTERN INLINE void          mSFRintrEn              (mUINT_16 value);
EXTERN INLINE void          mSFRintrDis             (mUINT_16 value);
EXTERN INLINE void          mSFRintrStatusClr       (mUINT_16 intSource);

EXTERN INLINE mUINT_16      mCPUintrStatus          (void);
EXTERN INLINE mUINT_16      mSFRintrStatus          (void);
EXTERN INLINE mUINT_16      mSFRcheckSwIrq          (void);
EXTERN void                 mSFRSendMailBoxCmd(mUINT_16 *pCmd);





#endif // *_H_INC
