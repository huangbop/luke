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
#ifndef _mGLOBALS_H_INC
#define _mGLOBALS_H_INC

//#include "mMACROS.h"
#include "mCONDS.h"

#define mBIT(n)                     (1 << (n))

#define mSET_MASK(bitPos)           ( mBIT(bitPos))
#define mCLR_MASK(bitPos)           (~(mBIT(bitPos)))

#define mSET_FLAG(flag,bitPos)      ((flag) |= mSET_MASK(bitPos))
#define mCLR_FLAG(flag,bitPos)      ((flag) &= mCLR_MASK(bitPos))

#define mIS_BIT_SET(flag,bitPos)    (((flag) & mSET_MASK(bitPos)) != 0)
#define mIS_BIT_CLR(flag,bitPos)    (((flag) & mSET_MASK(bitPos)) == 0)

#define mMIN(a,b)                   ((a) < (b) ? (a) : (b))
#define mMAX(a,b)                   ((a) > (b) ? (a) : (b))

#define mBYTES2SECT(a)              (a/mSECTOR_SIZE + (a % mSECTOR_SIZE ? 1 : 0))

#define PRIVATE static
#define INLINE

#if (mTHUMB_MODE == mDISABLE)

#ifdef __ghs__
__inline void mENABLE_IRQ(void)
{
    __SETSR(__GETSR()&~0x80);
}    
#else
__inline void mENABLE_IRQ(void)
{
    int tmp;
    __asm
    {
        MRS tmp, CPSR
        BIC tmp, tmp, #0x80
        MSR CPSR_c, tmp
    }
}
#endif



#ifdef __ghs__
__inline void mDISABLE_IRQ(void)
{
    __SETSR(__GETSR()|0x80);
}
#else
__inline void mDISABLE_IRQ(void)
{
    int tmp;
    __asm
    {
        MRS tmp, CPSR
        ORR tmp, tmp, #0x80
        MSR CPSR_c, tmp
    }
}
#endif


#ifdef __ghs__
__inline void mENABLE_FIQ(void)
{
    __SETSR(__GETSR()&~0x40);
}
#else
__inline void mENABLE_FIQ(void)
{
    int tmp;
    __asm
    {
        MRS tmp, CPSR
        BIC tmp, tmp, #0x40
        MSR CPSR_c, tmp
    }
}
#endif



#ifdef __ghs__
__inline void mDISABLE_FIQ(void)
{
    __SETSR(__GETSR()|0x40);
}
#else
__inline void mDISABLE_FIQ(void)
{
    int tmp;
    __asm
    {
        MRS tmp, CPSR
        ORR tmp, tmp, #0x40
        MSR CPSR_c, tmp
    }
}
#endif

#else   // (mTHUMB_MODE == mENABLE)

// When Thumb mode is enabled, these functions are implemented as ASM functions in a .s file.
// We just declare the prototypes here to serve compilation purpose.
  extern  void mENABLE_IRQ(void);
  extern  void mDISABLE_IRQ(void);
  extern  void mENABLE_FIQ(void);
  extern  void mDISABLE_FIQ(void);
#endif  // End of #if (mTHUMB_MODE == mDISABLE)

//
// Max values for native types
//

#define  mMAX_UINT_32    0xffffffff
#define  mMAX_INT_32     0x7fffffff
#define  mMIN_INT_32     0x80000000

#define  mMAX_UINT_16    0xffff
#define  mMAX_INT_16     0x7fff
#define  mMIN_INT_16     0x8000

#define  mMAX_UBYTE      0xff
#define  mMAX_BYTE       0x7f
#define  mMIN_BYTE       0x80



//
// typedefs for  native types- for porting purpose
//
typedef int             mINT_NATIVE;

typedef unsigned int    mUINT_NATIVE;

typedef signed char     mBYTE;          // signed types 1 byte    

typedef unsigned char   mUBYTE;         // unsigned types 1 byte 

typedef signed char     mINT_8;         // signed types 1 byte 
   
typedef unsigned char   mUINT_8;        // unsigned types 1 byte 

typedef short           mINT_16;        // 2 bytes

typedef unsigned short  mUINT_16;       // 2 bytes

typedef int             mINT_32;        // 4 bytes

typedef unsigned int    mUINT_32;       // 4 bytes

typedef long long       mINT_64;        // 8 bytes

typedef unsigned long long  mUINT_64;   // 8 bytes

typedef int             mtBOOLEAN;      // mTRUE/mFALSE 


typedef mUINT_16        mtBUFFER_DATA;
typedef mUINT_32        mtBUFFER_ADDRESS;
typedef mUINT_32        mtUP_ADDRESS;

typedef mUINT_32        mtLBA;

typedef union                           // to provide access to individual bytes
{
    mUINT_16      all16;
    struct
    {
        mUINT_16   lsb:8;
        mUINT_16   msb:8;
    } bytes;
} mtUNION_UINT_16;


typedef union                           // to provide access to individual bytes
{
    mINT_16      all16;
    struct
    {
        mINT_16   lsb:8;
        mINT_16   msb:8;
    } bytes;
} mtUNION_INT_16;


typedef union                           // to provide access to individual bytes
{
    mUINT_32      all32;
    struct
    {
        mUINT_16   lsb:8;
        mUINT_16   mlsb:8;
        mUINT_16   mmsb:8;
        mUINT_16   msb:8;
    } bytes;
} mtUNION_UINT_32;


typedef enum
{
    mFAILED = 0,
    mPASSED = 1
} mtPASSFAIL;



#define mNULL   0
#define mFALSE  0
#define mTRUE   1
#define mID     1
#define mOD     -1
#define mNORMALWEDGE 0
#define mSPRLWEDGE 1
#define mCS_SPIRAL 2
#define mSEEDED_SPIRAL 3
#define mOUTSIDESEEK 0
#define mINSIDESEEK 1
#define mPES 0
#define mPESCOPY 1


#define mINVALID_LBA       (0xFFFFFFFF)
#define mINVALID_CYL        0xffffffffUL
#define mINVALID_HEAD       0xff
#define mINVALID_ZONE       0xff

// function pointer that takes no arg and returns none
typedef void (*SvoVector_void) (void);
typedef void (*SvoVector_U16) (mUINT_16);

typedef void (*SerialAccess) (void);
extern  SerialAccess serialHelper;


/*----------------------------------------------------------------------------
    Public data structure definitions and defines
 ---------------------------------------------------------------------------*/
#define mREAD_OP   0
#define mWRITE_OP  1
#define mNATIVE_OP 2
#define mSPRLRAW_OP 3
#define mSPRLWRITE_OP 4
#define MRCAL_SEEK  0x80    // OR this with the above seek defines


typedef enum
{
    // if new item is inserted before mFID_BI_ADAPTIVE_WPRE, do change FIRST_PAGE_IN_INDEX
    
    mFID_DIRECTORY                  = 0x00,
    mFID_SYSTEM_DEFECT_LIST         = 0x01,
    mFID_SERVO_DEFECT_LIST          = 0x02,
    mFID_INVALID                    = 0x03,
    
    // BI files
    mFID_BI_CODE                    = 0x10, 
    mFID_BI_SCRIPT                  = 0x11,
    mFID_BI_RESULT                  = 0x12,
    mFID_BI_CMD_HISTORY             = 0x13,
    mFID_BI_RES_VARIABLE            = 0x14,
    mFID_BI_SCRATCH_PAD             = 0x15,
    mFID_BI_MICROJOG                = 0x16,
    mFID_BI_ADAPTIVE_WPRE           = 0x17,
    
    //parameter pages files
    // adding new param page:
    // check: EXTERN const  mtPARAMETER_PAGE mParamPages[mMAX_PARAM_PAGES]    // See below for init

    mFID_PARAM_SERVO_PAGE0          = 0x18,
    mFID_PARAM_DM_PAGE              = 0x19,
    mFID_PARAM_ECU_PAGE             = 0x1a,
    mFID_PARAM_HBI_PAGE             = 0x1b,
    mFID_PARAM_TRACK_FORMAT_PAGE    = 0x1c,
    mFID_PARAM_DF_PAGE0             = 0x1d,
    mFID_PARAM_SAIL_PAGE            = 0x1e,
    mFID_PARAM_CHAN_PAGE            = 0x1f,
    mFID_PARAM_ER_PAGE              = 0x20,
    mFID_RWHEADOFFSET               = 0x21,
    mFID_PLANTBIASFORCE             = 0x22,
    mFID_PLANTGAMMA                 = 0x23,
    mFID_NOTCHFILTER                = 0x24,
    mFID_POSRAMPSLOPE               = 0x25,
    mFID_RROHARMONIC                = 0x26,
    mFID_RROGAIN                    = 0x27,
    mFID_RROPHASE                   = 0x28,
    mFID_RROCOSCOEFF                = 0x29,
    mFID_RROSINCOEFF                = 0x2A,
    mFID_PARAM_GDM_PAGE             = 0x2B,
    mFID_FPGA_PAGE                  = 0x2C,
    mFID_PESLINOFFSET               = 0x2D,
    mFID_PESLINGAIN                 = 0x2E,
    mFID_SKTIMETBL                  = 0x2F,
    mFID_HSTIMETBL                  = 0x30,
    mFID_PREAMP                     = 0x31,
    mFID_READLOG_PAGE_10H           = 0x32,
    mFID_READLOG_PAGE_11H           = 0x33,
    mFID_POWER_MAN                  = 0x34,
    
    // Start of non-parameter files
    mFID_DEF_CHAN_SETTING           = 0x80,     // default channel settings page.
    mFID_DEF_DRIVE_INFO             = 0x81,     // default drive info
   
    mFID_BI_W2W_DFCT                = 0x90,
    mFID_BI_SEC_DFCT                = 0x91,
    mFID_BI_ADAPT_BOOST             = 0x92,
    mFID_BI_ADAPT_COMBO             = 0x93,
    mFID_BI_BODE                    = 0x94,
    mFID_BI_TMR                     = 0x95,     // Not used now.
    mFID_BI_LSCAN_DFCT              = 0x96,
    mFID_BI_ADAPT_COMBO_LOCAL       = 0x97,
    mFID_BI_SFILL_DFCT              = 0x98,
    mFID_BI_ADAPT_COMBO_FIR         = 0x99,
    mFID_BI_ASIC_DUMP0              = 0x9A,
    mFID_BI_ASIC_DUMP1              = 0x9B,
    mFID_BI_ASIC_DUMP2              = 0x9C,
    mFID_BI_ASIC_DUMP3              = 0x9D,
    mFID_BI_TMR_NEW                 = 0x9E,
    mFID_DEFECT_SECTOR              = 0xA0,
    mFID_DEFECTSCAN_SECTOR          = 0xA1,
    mFID_DEFECT_SECTOR_DM           = 0xA2,     // defect sector file that is used to produce DM table.
    mFID_DEFECTSCAN_SECTOR_WRITE    = 0xA3,     // use for write mode defect

    mFID_BI_ERROR_RATE_0            = 0xB0,
    mFID_BI_ERROR_RATE_1            = 0xB1,
    mFID_BI_ERROR_RATE_2            = 0xB2,
    mFID_BI_ERROR_RATE_3            = 0xB3,
    mFID_BI_ERROR_RATE_4            = 0xB4,
    mFID_BI_ERROR_RATE_5            = 0xB5,
    mFID_BI_ERROR_RATE_6            = 0xB6,
    mFID_BI_ERROR_RATE_7            = 0xB7,
    mFID_BI_ERROR_RATE_ECC          = 0xB8,
    mFID_BI_ERROR_RATE_OTC          = 0xB9,
    
    mFID_BI_TRAIN_0                 = 0xC0,
    mFID_BI_TRAIN_1                 = 0xC1,
    mFID_BI_TRAIN_2                 = 0xC2,
    mFID_BI_TRAIN_3                 = 0xC3,
    mFID_BI_TRAIN_4                 = 0xC4,
    mFID_BI_TRAIN_5                 = 0xC5,
    mFID_BI_TRAIN_6                 = 0xC6,
    mFID_BI_TRAIN_7                 = 0xC7,
    mFID_BI_TRAIN_8                 = 0xC8,
    mFID_BI_TRAIN_9                 = 0xC9,
    mFID_BI_TRAIN_A                 = 0xCA,
    mFID_BI_TRAIN_B                 = 0xCB,
    mFID_BI_TRAIN_C                 = 0xCC,
    mFID_BI_TRAIN_D                 = 0xCD,
    mFID_BI_TRAIN_E                 = 0xCE,
    mFID_BI_TRAIN_F                 = 0xCF,
    
	mFID_BI                         = 0xF0,
    mFID_BI_SAVE                    = 0xF1,
    mFID_BI_2                       = 0xF2,
    mFID_BI_F3                      = 0xF3,
    mFID_BI_F4                      = 0xF4,
    mFID_BI_F5                      = 0xF5,
    mFID_BI_F6                      = 0xF6,
    mFID_BI_F7                      = 0xF7,
    mFID_BI_F8                      = 0xF8,
    mFID_BI_F9                      = 0xF9,
    mFID_BI_FA                      = 0xFA,
    mFID_BI_FB                      = 0xFB,
//    mFID_P2A                        = 0xA0,
//    mFID_P2A_SLIP                   = 0xA1,
    mFID_FILESTATUS                 = 0xFD,
    mFID_CHECKSUM                   = 0xFE,
    mFID_LAST                       = 0xFF  // last file id
} mtFILE_ID;
#define     FILE_ID_MASK        0xFFF0
#define     FILE_ID_SHIFT       4

#define FIRST_NON_PAGE_FILEID       mFID_DEF_CHAN_SETTING

#define FIRST_PAGE_IN_INDEX  8      // line up with the first parm page to be read listed in mDirectory

#define     SN_LEN      10
#define     FW_LEN      4
#define     MODEL_LEN   20

#endif // _H_INC
