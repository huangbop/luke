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

#ifndef     _MBM_H_INC
   #define  _MBM_H_INC
             
#include "mGLOBALS.h"
#include "mREGS.h"

#ifdef      EXTERN
   #undef   EXTERN
#endif

#ifdef      INSTANTIATE_MBM
   #define  EXTERN
#else
   #define  EXTERN extern
#endif

/*----------------------------------------------------------------------------
    Public data structure definitions and defines
 ---------------------------------------------------------------------------*/
typedef mUINT_32 mtBM_BFR_ADDRESS;

#define mBM_CPU_FIFO_SIZE    (2 * 8) 

#define MEM_0Mb         0x00
#define MEM_64Mb        0x01
#define MEM_128Mb       0x02
#define MEM_256Mb       0x04
#define MEM_512Mb       0x08
#define MEM_1Gb         0x10
#define MEM_2Gb         0x20
#define MEM_4Gb         0x40
#define MEM_8Gb         0x80

/*----------------------------------------------------------------------------
 Public Data (other modules can use these vars by including this .h file:
 ---------------------------------------------------------------------------*/

typedef struct
{
    mUINT_32            nextSsdIndex;       // Bits 0-15 index of next SSD.
    mUINT_32            ssdStartBufAddr;    // Bits 0-25 are the start address of the current SSD.
    mUINT_32            ssdEndBufAddr;      // Bits 0-25 are the end address of the current SSD.
} mtBFR_SSD;

#if 0
#ifdef __ghs__
  #pragma ghs section bss    = ".ssd_data_dram"
#else
  #pragma arm section zidata = "ssd_data_dram"
#endif

    #define     BFR_SSD_COUNT	    1022UL         // 32M

#define       INTERNAL_BFR_SSD      0x24    // This number should be the same as mBFR_LL_NUM_INTERNAL_LINK, it also should be > sys_LUT_AU_CMT + 4
  
  #ifdef        BFR_SSD_INTERLINK
  #else
    #define     BFR_SSD_INTERNAL_LINK   BFR_SSD_COUNT
  #endif
  
  EXTERN mtBFR_SSD  mBfrSSD[BFR_SSD_COUNT  + INTERNAL_BFR_SSD];     // for VG, 10-22-09: 1046 total
 
#ifdef __ghs__
  #pragma ghs section bss    = ".ctlr_data_sram"
#else
  #pragma arm section zidata = "ctlr_data_sram"
#endif
#endif
/*----------------------------------------------------------------------------
 Public Function Prototypes (other modules can use these functions by
 including this .h file):
 ---------------------------------------------------------------------------*/
EXTERN __inline void        mBMhostByteCntRst       (void);
EXTERN __inline void        mBMenableSailParity     (void);
EXTERN __inline void        mBMsetHstSSCtoSSC1      (void); 
EXTERN __inline void        mBMclearHstSSCtoSSC1    (void); 
EXTERN __inline void        mBMinitCntrl            (mUINT_16 val);
EXTERN __inline void        mBMsetCntrl             (mUINT_16 val); 
EXTERN __inline void        mBMclrCntrl             (mUINT_16 val); 
EXTERN __inline void        mBMsetCntrl1            (mUINT_16 val); 
EXTERN __inline void        mBMclrCntrl1            (mUINT_16 val);
EXTERN __inline void        mBMintr0Init            (mUINT_16 val);
EXTERN __inline void        mBMintr0Enable          (mUINT_16 val);
EXTERN __inline void        mBMintr0Disable         (mUINT_16 val);
EXTERN __inline void        mBMintr1Init            (mUINT_16 val);
EXTERN __inline void        mBMintr1Enable          (mUINT_16 val);
EXTERN __inline void        mBMintr1Disable         (mUINT_16 val);
EXTERN __inline void        mBMsetHostSeg0Size      (mUINT_16 val);   
EXTERN __inline void        mBMsetHostSeg1Size      (mUINT_16 val);   
EXTERN __inline void        mBMsetHostSeg2Size      (mUINT_16 val);   
EXTERN __inline void        mBMsetHostSeg3Size      (mUINT_16 val);   
EXTERN __inline void        mBMsetHostSeg4Size      (mUINT_16 val);   
EXTERN __inline void        mBMsetHostSeg5Size      (mUINT_16 val);   
EXTERN __inline void        mBMsetHostSeg6Size      (mUINT_16 val);   
EXTERN __inline void        mBMsetHostSeg7Size      (mUINT_16 val); 
EXTERN __inline void        mBMsetHostSeg0LnkLstPtr (mUINT_16 val);
EXTERN __inline void        mBMsetHostSeg1LnkLstPtr (mUINT_16 val);
EXTERN __inline void        mBMsetHostSeg2LnkLstPtr (mUINT_16 val);
EXTERN __inline void        mBMsetHostSeg3LnkLstPtr (mUINT_16 val);
EXTERN __inline void        mBMsetHostSeg4LnkLstPtr (mUINT_16 val);
EXTERN __inline void        mBMsetHostSeg5LnkLstPtr (mUINT_16 val);
EXTERN __inline void        mBMsetHostSeg6LnkLstPtr (mUINT_16 val);
EXTERN __inline void        mBMsetHostSeg7LnkLstPtr (mUINT_16 val);
EXTERN __inline void        mBMsetCntrl0            (mUINT_16 val); 
EXTERN __inline void        mBMclrCntrl0            (mUINT_16 val);
EXTERN __inline void        mBMsetStatus1           (mUINT_16 val);

EXTERN __inline void        mBMhostSegAdjSel        (mUINT_16 value);
EXTERN __inline void        mBMinitDram             (mUINT_16 controlBits);
EXTERN __inline void        mBMsetHostSectorSize    (mUINT_16 hostWords); 
EXTERN __inline void        mBMsetDiskSectorSize    (mUINT_16 diskWords); 

EXTERN __inline void        mBMsetDiskseg0SectCnt    (mINT_NATIVE value);
EXTERN __inline void        mBMdiskSegSecCntSel     (mUINT_NATIVE val); 
EXTERN __inline void        mBMinitHS0SC            (mINT_NATIVE value);
EXTERN __inline void        mBMinitHS1SC            (mINT_NATIVE value);
EXTERN __inline void        mBMinitHS2SC            (mINT_NATIVE value);
EXTERN __inline void        mBMinitHS3SC            (mINT_NATIVE value);
EXTERN __inline void        mBMinitHS4SC            (mINT_NATIVE value);
EXTERN __inline void        mBMinitHS5SC            (mINT_NATIVE value);
EXTERN __inline void        mBMinitHS6SC            (mINT_NATIVE value);
EXTERN __inline void        mBMinitHS7SC            (mINT_NATIVE value);
EXTERN __inline void        mBMadjustHostSegSectCnt (mINT_NATIVE value);

EXTERN __inline void        mBMsetHostSegPtr        (mtBUFFER_ADDRESS bufferStartAddress);
EXTERN __inline void        mBMsetDiskSeg0Ptr        (mtBUFFER_ADDRESS bufferStartAddress);

EXTERN __inline mUINT_16    mBMgetDiskSegSize       (void); 
EXTERN __inline mUINT_16    mBMgetDisksegSectCnt    (void);
EXTERN __inline mUINT_16    mBMgetHostSeg0Size      (void);
EXTERN __inline mUINT_16    mBMgetHostSeg1Size      (void);
EXTERN __inline mUINT_16    mBMgetHostSeg2Size      (void);
EXTERN __inline mUINT_16    mBMgetHostSeg3Size      (void);
EXTERN __inline mUINT_16    mBMgetHostSeg4Size      (void);
EXTERN __inline mUINT_16    mBMgetHostSeg5Size      (void);
EXTERN __inline mUINT_16    mBMgetHostSeg6Size      (void);
EXTERN __inline mUINT_16    mBMgetHostSeg7Size      (void);

EXTERN __inline mINT_16     mBMgetHS0SC             (void);
EXTERN __inline mINT_16     mBMgetHS1SC             (void);
EXTERN __inline mINT_16     mBMgetHS2SC             (void);
EXTERN __inline mINT_16     mBMgetHS3SC             (void);
EXTERN __inline mINT_16     mBMgetHS4SC             (void);
EXTERN __inline mINT_16     mBMgetHS5SC             (void);
EXTERN __inline mINT_16     mBMgetHS6SC             (void);
EXTERN __inline mINT_16     mBMgetHS7SC             (void);

EXTERN __inline mUINT_16    mBMgetStatus0           (void);
EXTERN __inline mUINT_16    mBMgetStatus1           (void);
EXTERN __inline mUINT_16    mBMgetHostSeg0LnkLstPtr (void);
EXTERN __inline mUINT_16    mBMgetHostSeg1LnkLstPtr (void);
EXTERN __inline mUINT_16    mBMgetHostSeg2LnkLstPtr (void);
EXTERN __inline mUINT_16    mBMgetHostSeg3LnkLstPtr (void);
EXTERN __inline mUINT_16    mBMgetHostSeg4LnkLstPtr (void);
EXTERN __inline mUINT_16    mBMgetHostSeg5LnkLstPtr (void);
EXTERN __inline mUINT_16    mBMgetHostSeg6LnkLstPtr (void);
EXTERN __inline mUINT_16    mBMgetHostSeg7LnkLstPtr (void);

EXTERN __inline mtBUFFER_ADDRESS mBMgetHostSegPtr   (void);
EXTERN __inline mUINT_NATIVE     mBMgetDiskLogicSegSecCntSel    (void); 

EXTERN __inline void      mBMsetExpHostSeg0LnkLstPtr  (mUINT_16 val);
EXTERN __inline void      mBMsetExpHostSeg1LnkLstPtr  (mUINT_16 val);
EXTERN __inline void      mBMsetExpHostSeg2LnkLstPtr  (mUINT_16 val);
EXTERN __inline void      mBMsetExpHostSeg3LnkLstPtr  (mUINT_16 val);
EXTERN __inline void      mBMsetExpDiskSeg0LnkLstPtr  (mUINT_16 val);
EXTERN __inline void      mBMsetHostSegLnkLstStopPtr  (mUINT_16 val);
EXTERN __inline void      mBMsetDiskSegLnkLstStopPtr  (mUINT_16 val);

EXTERN __inline void      mBMrestoreHstSSCtoSSC1  (mUINT_16); 
EXTERN __inline void      mBMsetDiskSeg0LnkLstPtr (mUINT_16 val);
EXTERN __inline void      mBMsetDiskSeg1LnkLstPtr (mUINT_16 val);
EXTERN __inline void      mBMsetDiskSeg2LnkLstPtr (mUINT_16 val);
EXTERN __inline void      mBMsetDiskSeg3LnkLstPtr (mUINT_16 val);
EXTERN __inline void      mBMsetExtSeg0LnkLstPtr(mUINT_16 val);
EXTERN __inline void      mBMsetExtSeg1LnkLstPtr (mUINT_16 val);
EXTERN __inline void      mBMsetExtSeg2LnkLstPtr (mUINT_16 val);
EXTERN __inline void      mBMsetExtSeg3LnkLstPtr (mUINT_16 val);
EXTERN __inline void      mBMsetSectorSizeRatio   (mUINT_16 val); 
EXTERN __inline void      mBMsetSubSegDescSize    (mUINT_16 val); 
EXTERN __inline void      mBMsetHstSSCtoSSC1AndDiskSegSecCntSel(mUINT_16 val);
EXTERN __inline void      mBMsetDiskSeg0Size       (mUINT_16 num_sectors);
EXTERN __inline void      mBMsetDiskSeg1Size      (mUINT_16 num_sectors);
EXTERN __inline void      mBMsetDiskSeg2Size      (mUINT_16 num_sectors);
EXTERN __inline void      mBMsetDiskSeg3Size      (mUINT_16 num_sectors);
EXTERN __inline void      mBMsetDiskseg0SectCnt    (mINT_NATIVE value);
EXTERN __inline void      mBMsetDiskseg1SectCnt   (mINT_NATIVE value);
EXTERN __inline void      mBMsetDiskseg2SectCnt   (mINT_NATIVE value);
EXTERN __inline void      mBMsetDiskseg3SectCnt   (mINT_NATIVE value);
EXTERN __inline void      mBMsetExtSeg0Size       (mUINT_16 num_sectors);
EXTERN __inline void      mBMsetExtSeg1Size      (mUINT_16 num_sectors);
EXTERN __inline void      mBMsetExtSeg2Size      (mUINT_16 num_sectors);
EXTERN __inline void      mBMsetExtSeg3Size      (mUINT_16 num_sectors);
EXTERN __inline void      mBMsetExtseg0SectCnt    (mINT_NATIVE value);
EXTERN __inline void      mBMsetExtseg1SectCnt   (mINT_NATIVE value);
EXTERN __inline void      mBMsetExtseg2SectCnt   (mINT_NATIVE value);
EXTERN __inline void      mBMsetExtseg3SectCnt   (mINT_NATIVE value);
EXTERN __inline void      mBMdiskSegSel           (mUINT_NATIVE val);
EXTERN __inline void      mBMsetSubSegDescTableStartAddr  (mUINT_32 val); 
EXTERN __inline void      mBMsetSubSegDescTableEndAddr    (mUINT_32 val); 
EXTERN __inline void      mBMsetDiskSeg0Ptr        (mtBUFFER_ADDRESS bufferStartAddress);
EXTERN __inline void      mBMsetDiskSeg1Ptr       (mtBUFFER_ADDRESS bufferStartAddress);
EXTERN __inline void      mBMsetDiskSeg2Ptr       (mtBUFFER_ADDRESS bufferStartAddress);
EXTERN __inline void      mBMsetDiskSeg3Ptr       (mtBUFFER_ADDRESS bufferStartAddress);
EXTERN __inline void      mBMsetExtSeg0Ptr        (mtBUFFER_ADDRESS bufferStartAddress);
EXTERN __inline void      mBMsetExtSeg1Ptr       (mtBUFFER_ADDRESS bufferStartAddress);
EXTERN __inline void      mBMsetExtSeg2Ptr       (mtBUFFER_ADDRESS bufferStartAddress);
EXTERN __inline void      mBMsetExtSeg3Ptr       (mtBUFFER_ADDRESS bufferStartAddress);

EXTERN __inline mUINT_8   mGetBMdiskSegSel        (void);
EXTERN __inline mUINT_16  mBMgetDiskseg0SectCnt   (void);
EXTERN __inline mUINT_16  mBMgetDiskseg1SectCnt   (void);
EXTERN __inline mUINT_16  mBMgetDiskseg2SectCnt   (void);
EXTERN __inline mUINT_16  mBMgetDiskseg3SectCnt   (void);
EXTERN __inline mUINT_16  mBMgetDiskSegSize       (void); 
EXTERN __inline mUINT_16  mBMgetDiskSeg1Size      (void); 
EXTERN __inline mUINT_16  mBMgetDiskSeg2Size      (void); 
EXTERN __inline mUINT_16  mBMgetDiskSeg3Size      (void); 
EXTERN __inline mUINT_16  mBMgetHstSSCtoSSC1      (void); 

EXTERN __inline mUINT_16  mBMgetDiskSeg0LnkLstPtr           (void);
EXTERN __inline mUINT_16  mBMgetDiskSeg0LnkLstPtr           (void);
EXTERN __inline mUINT_32  mBMgetSubSegDescTableEndAddr      (void); 
EXTERN __inline mUINT_32  mBMgetSubSegDescTableStartAddr    (void); 

  //#if(mDAVINCI_COMPATIBLE == mENABLE)
  #if 0
    EXTERN __inline void    mBMsetDskSSCtoSSC1	            (void); 
    EXTERN __inline void    mBMclearDskSSCtoSSC1            (void); 
  #endif
  EXTERN __inline mUINT_16  mBMgetHostCurSegSecCntSel       (void); 
  EXTERN __inline void      mBMsetHostCurSegSecCntSel       (mUINT_16 value);
  EXTERN __inline void      mBMsetDVcompatibleMode          (mtBOOLEAN val); 

#ifdef __ghs__
  #pragma ghs section bss = ".rHDC_BM"
  EXTERN volatile  mtBUFF_MNGR   rBM;  
  #pragma ghs section
#else  
  #pragma arm section zidata = "rHDC_BM"
  EXTERN volatile  mtBUFF_MNGR   rBM;  
  #pragma arm section zidata
#endif    

/*******************************************************************
 *
 *  NAME:           mBMinitDram
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     uint 16 value control bits
 *
 *  DESCRIPTION:    Init Dram control with control bits specified in 
 *                  the 'controlBits' parameter.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMinitDram(mUINT_16 controlBits) 
{
    rBM.cntrlReg1.all = controlBits;
}

/*******************************************************************
 *
 *  NAME:           mBMstartDram
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     uint 16 value control bits
 *
 *  DESCRIPTION:    Init Dram control with control bits specified in 
 *                  the 'controlBits' parameter.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMstartDram(mUINT_16 controlBits) 
{
    rBM.cntrlReg1.all |= controlBits;
}

/*******************************************************************
 *
 *  NAME:           mBMhostByteCntRst
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     void
 *
 *  DESCRIPTION:    Host Byte Counter Reset 
 *              
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMhostByteCntRst(void) 
{
}

/*******************************************************************
 *
 *  NAME:           mBMsetCntrl0  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 val
 *					
 *  DESCRIPTION:    Or (set) the bits contained in the parameter "val'
 *                  in the buffer manager control register 0.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMsetCntrl0(mUINT_16 val) 
{
    rBM.cntrlReg0.all |= val;
}

/*******************************************************************
 *
 *  NAME:           mBMclrCntrl0  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 val
 *					
 *  DESCRIPTION:    And the negation (clear) the bits contained in the 
 *                  parameter "val' in the buffer manager control register 0.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMclrCntrl0(mUINT_16 val) 
{
    rBM.cntrlReg0.all &= ~val;
}

/*******************************************************************
*																   
*  NAME:        mBMSetHostSegnLnkLstPtr
*
*  FILENAME:    mBM.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set Host Link List Pointer
*
*  RETURNS:     None
*
********************************************************************/
__inline void mBMsetHostSeg0LnkLstPtr(mUINT_16 val)
{
    rBM.hostSeg0LnkLstPtr.all = val;

}
__inline void mBMsetHostSeg1LnkLstPtr(mUINT_16 val)
{
    rBM.hostSeg1LnkLstPtr.all = val;

}
__inline void mBMsetHostSeg2LnkLstPtr(mUINT_16 val)
{
    rBM.hostSeg2LnkLstPtr.all = val;

}
__inline void mBMsetHostSeg3LnkLstPtr(mUINT_16 val)
{
    rBM.hostSeg3LnkLstPtr.all = val;

}
__inline void mBMsetHostSeg4LnkLstPtr(mUINT_16 val)
{
    rBM.hostSeg4LnkLstPtr.all = val;

}
__inline void mBMsetHostSeg5LnkLstPtr(mUINT_16 val)
{
    rBM.hostSeg5LnkLstPtr.all = val;

}
__inline void mBMsetHostSeg6LnkLstPtr(mUINT_16 val)
{
    rBM.hostSeg6LnkLstPtr.all = val;

}
__inline void mBMsetHostSeg7LnkLstPtr(mUINT_16 val)
{
    rBM.hostSeg7LnkLstPtr.all = val;

}

__inline mUINT_16 mBMgetHostSeg0LnkLstPtr(void)
{
    return rBM.hostSeg0LnkLstPtr.all;
}

__inline mUINT_16 mBMgetHostSeg1LnkLstPtr(void)
{
    return rBM.hostSeg1LnkLstPtr.all;
}

__inline mUINT_16 mBMgetHostSeg2LnkLstPtr(void)
{
    return rBM.hostSeg2LnkLstPtr.all;
}

__inline mUINT_16 mBMgetHostSeg3LnkLstPtr(void)
{
    return rBM.hostSeg3LnkLstPtr.all;
}

__inline mUINT_16 mBMgetHostSeg4LnkLstPtr(void)
{
    return rBM.hostSeg4LnkLstPtr.all;
}

__inline mUINT_16 mBMgetHostSeg5LnkLstPtr(void)
{
    return rBM.hostSeg5LnkLstPtr.all;
}

__inline mUINT_16 mBMgetHostSeg6LnkLstPtr(void)
{
    return rBM.hostSeg6LnkLstPtr.all;
}

__inline mUINT_16 mBMgetHostSeg7LnkLstPtr(void)
{
    return rBM.hostSeg7LnkLstPtr.all;
}



__inline void mBMsetDiskSeg0LnkLstPtr(mUINT_16 val)
{
    rBM.diskSeg0LnkLstPtr.all = val;
}

__inline void mBMsetDiskSeg1LnkLstPtr(mUINT_16 val)
{
    rBM.diskSeg1LnkLstPtr.all = val;
}

__inline void mBMsetDiskSeg2LnkLstPtr(mUINT_16 val)
{
    rBM.diskSeg2LnkLstPtr.all = val;
}

__inline void mBMsetDiskSeg3LnkLstPtr(mUINT_16 val)
{
    rBM.diskSeg3LnkLstPtr.all = val;
}

__inline mUINT_16 mBMgetDiskSeg0LnkLstPtr(void)
{
    return rBM.diskSeg0LnkLstPtr.all;
}


__inline void mBMsetExtSeg0LnkLstPtr(mUINT_16 val)
{
    rBM.extdSeg0LnkLstPtr.all = val;
}

__inline void mBMsetExtSeg1LnkLstPtr(mUINT_16 val)
{
    rBM.extdSeg1LnkLstPtr.all = val;
}

__inline void mBMsetExtSeg2LnkLstPtr(mUINT_16 val)
{
    rBM.extdSeg2LnkLstPtr.all = val;
}

__inline void mBMsetExtSeg3LnkLstPtr(mUINT_16 val)
{
    rBM.extdSeg3LnkLstPtr.all = val;
}

/*******************************************************************
*																   
*  NAME:        mBMSetSubSegnLnkAddr
*
*  FILENAME:    mBM.h
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set subsegment Link Address
*
*  RETURNS:     None
*
********************************************************************/
__inline volatile mtBFR_SSD * mBMgetSubSegNextLLPointerAddr(mUINT_16 index)
{
    //return(&(mBfrSSD[index]));
    return 0;
}

/*******************************************************************
 *
 *  NAME:           mBMsetHostSegPtr
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mtBUFFER_ADDRESS bufferStartAddress
 *
 *  DESCRIPTION:    Load the host segment transfer pointer with the address
 *                  specified in the 'bufferStartAddress' parameter.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
//for 6545, 6541, 6745, 6740 and 8825
 __inline void mBMsetHostSeg0Ptr (mtBUFFER_ADDRESS bufferStartAddress)
 {
    rBM.hostSeg0XferPtrL=bufferStartAddress&0xFFFF;
    rBM.hostSeg0XferPtrH=(bufferStartAddress >> 16) ; 
 }
 
 __inline void mBMsetHostSeg1Ptr (mtBUFFER_ADDRESS bufferStartAddress)
 {
    rBM.hostSeg1XferPtrL=bufferStartAddress&0xFFFF;
    rBM.hostSeg1XferPtrH=(bufferStartAddress >> 16) ; 
 }
 
 __inline void mBMsetHostSeg2Ptr (mtBUFFER_ADDRESS bufferStartAddress)
 {
    rBM.hostSeg2XferPtrL=bufferStartAddress&0xFFFF;
    rBM.hostSeg2XferPtrH=(bufferStartAddress >> 16) ; 
 }
 
 __inline void mBMsetHostSeg3Ptr (mtBUFFER_ADDRESS bufferStartAddress)
 {
    rBM.hostSeg3XferPtrL=bufferStartAddress&0xFFFF;
    rBM.hostSeg3XferPtrH=(bufferStartAddress >> 16) ; 
 }
 
 __inline void mBMsetHostSeg4Ptr (mtBUFFER_ADDRESS bufferStartAddress)
 {
    rBM.hostSeg4XferPtrL=bufferStartAddress&0xFFFF;
    rBM.hostSeg4XferPtrH=(bufferStartAddress >> 16) ; 
 }
 
 __inline void mBMsetHostSeg5Ptr (mtBUFFER_ADDRESS bufferStartAddress)
 {
    rBM.hostSeg5XferPtrL=bufferStartAddress&0xFFFF;
    rBM.hostSeg5XferPtrH=(bufferStartAddress >> 16) ; 
 }
 
 __inline void mBMsetHostSeg6Ptr (mtBUFFER_ADDRESS bufferStartAddress)
 {
    rBM.hostSeg6XferPtrL=bufferStartAddress&0xFFFF;
    rBM.hostSeg6XferPtrH=(bufferStartAddress >> 16) ; 
 }
 
 __inline void mBMsetHostSeg7Ptr (mtBUFFER_ADDRESS bufferStartAddress)
 {
    rBM.hostSeg7XferPtrL=bufferStartAddress&0xFFFF;
    rBM.hostSeg7XferPtrH=(bufferStartAddress >> 16) ; 
 }    

/*******************************************************************
 *
 *  NAME:           mBMgetHostSegPtr
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     None
 *
 *  DESCRIPTION:    Get host segment transfer pointer 
 *
 *  RETURNS:        Host segment transfer pointer
 *
 *******************************************************************/
//for 6545, 6541, 6745, 6740 and 8825
 __inline mtBUFFER_ADDRESS mBMgetHostSeg0Ptr (void)
 {
    return(((mUINT_32)rBM.hostSeg0XferPtrH << 16) | (mUINT_32)rBM.hostSeg0XferPtrL);   
 }
 
 __inline mtBUFFER_ADDRESS mBMgetHostSeg1Ptr (void)
 {
    return(((mUINT_32)rBM.hostSeg1XferPtrH << 16) | (mUINT_32)rBM.hostSeg1XferPtrL);   
 }
 
 __inline mtBUFFER_ADDRESS mBMgetHostSeg2Ptr (void)
 {
    return(((mUINT_32)rBM.hostSeg2XferPtrH << 16) | (mUINT_32)rBM.hostSeg2XferPtrL);   
 }
 
 __inline mtBUFFER_ADDRESS mBMgetHostSeg3Ptr (void)
 {
    return(((mUINT_32)rBM.hostSeg3XferPtrH << 16) | (mUINT_32)rBM.hostSeg3XferPtrL);   
 }
 
 __inline mtBUFFER_ADDRESS mBMgetHostSeg4Ptr (void)
 {
    return(((mUINT_32)rBM.hostSeg4XferPtrH << 16) | (mUINT_32)rBM.hostSeg4XferPtrL);   
 }
 
 __inline mtBUFFER_ADDRESS mBMgetHostSeg5Ptr (void)
 {
    return(((mUINT_32)rBM.hostSeg5XferPtrH << 16) | (mUINT_32)rBM.hostSeg5XferPtrL);   
 }
 
 __inline mtBUFFER_ADDRESS mBMgetHostSeg6Ptr (void)
 {
    return(((mUINT_32)rBM.hostSeg6XferPtrH << 16) | (mUINT_32)rBM.hostSeg6XferPtrL);   
 }
 
 __inline mtBUFFER_ADDRESS mBMgetHostSeg7Ptr (void)
 {
    return(((mUINT_32)rBM.hostSeg7XferPtrH << 16) | (mUINT_32)rBM.hostSeg7XferPtrL);   
 }

/*******************************************************************
 *
 *  NAME:           mBMgetDiskSegPtr
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     None
 *
 *  DESCRIPTION:    Get host segment transfer pointer 
 *
 *  RETURNS:        Host segment transfer pointer
 *
 *******************************************************************/
__inline mtBUFFER_ADDRESS mBMgetDiskSeg0Ptr (void)
{
    return(((mUINT_32)rBM.diskSeg0XferPtrH << 16) | (mUINT_32)rBM.diskSeg0XferPtrL);
}

__inline mtBUFFER_ADDRESS mBMgetDiskSeg1Ptr (void)
{
    return(((mUINT_32)rBM.diskSeg1XferPtrH << 16) | (mUINT_32)rBM.diskSeg1XferPtrL);
}

__inline mtBUFFER_ADDRESS mBMgetDiskSeg2Ptr (void)
{
    return(((mUINT_32)rBM.diskSeg2XferPtrH << 16) | (mUINT_32)rBM.diskSeg2XferPtrL);
}

__inline mtBUFFER_ADDRESS mBMgetDiskSeg3Ptr (void)
{
    return(((mUINT_32)rBM.diskSeg3XferPtrH << 16) | (mUINT_32)rBM.diskSeg3XferPtrL);
}

/*******************************************************************
 *
 *  NAME:           mBMsetDiskSegPtr
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mtBUFFER_ADDRESS bufferStartAddress
 *
 *  DESCRIPTION:    Load the disk segment transfer pointer with the address
 *                  specified in the 'bufferStartAddress' parameter.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMdiskSegPtr0Lzero (mUINT_16 bitsToClr)
{   // zero out desired bits
    rBM.diskSeg0XferPtrL &= ~bitsToClr;
}

__inline void mBMdiskSegPtr1Lzero (mUINT_16 bitsToClr)
{   // zero out desired bits
    rBM.diskSeg1XferPtrL &= ~bitsToClr;
}

__inline void mBMsetDiskSeg0Ptr (mtBUFFER_ADDRESS bufferStartAddress)
{
    // tell Disk where in the buffer to start transferring data
    rBM.diskSeg0XferPtrL=bufferStartAddress&0xFFFF;
    rBM.diskSeg0XferPtrH=(bufferStartAddress >> 16);
}

__inline void mBMsetDiskSeg1Ptr (mtBUFFER_ADDRESS bufferStartAddress)
{
    // tell Disk where in the buffer to start transferring data
    rBM.diskSeg1XferPtrL=bufferStartAddress&0xFFFF;
    rBM.diskSeg1XferPtrH=(bufferStartAddress >> 16);
}

__inline void mBMsetDiskSeg2Ptr (mtBUFFER_ADDRESS bufferStartAddress)
{
    // tell Disk where in the buffer to start transferring data
    rBM.diskSeg2XferPtrL=bufferStartAddress&0xFFFF;
    rBM.diskSeg2XferPtrH=(bufferStartAddress >> 16);
}

__inline void mBMsetDiskSeg3Ptr (mtBUFFER_ADDRESS bufferStartAddress)
{
    // tell Disk where in the buffer to start transferring data
    rBM.diskSeg3XferPtrL=bufferStartAddress&0xFFFF;
    rBM.diskSeg3XferPtrH=(bufferStartAddress >> 16);
}


__inline void mBMsetExtSeg0Ptr (mtBUFFER_ADDRESS bufferStartAddress)
{
    // tell Disk where in the buffer to start transferring data
    rBM.extdSeg0XferPtrL=bufferStartAddress&0xFFFF;
    rBM.extdSeg0XferPtrH=(bufferStartAddress >> 16);
}

__inline void mBMsetExtSeg1Ptr (mtBUFFER_ADDRESS bufferStartAddress)
{
    // tell Disk where in the buffer to start transferring data
    rBM.extdSeg1XferPtrL=bufferStartAddress&0xFFFF;
    rBM.extdSeg1XferPtrH=(bufferStartAddress >> 16);
}

__inline void mBMsetExtSeg2Ptr (mtBUFFER_ADDRESS bufferStartAddress)
{
    // tell Disk where in the buffer to start transferring data
    rBM.extdSeg2XferPtrL=bufferStartAddress&0xFFFF;
    rBM.extdSeg2XferPtrH=(bufferStartAddress >> 16);
}

__inline void mBMsetExtSeg3Ptr (mtBUFFER_ADDRESS bufferStartAddress)
{
    // tell Disk where in the buffer to start transferring data
    rBM.extdSeg3XferPtrL=bufferStartAddress&0xFFFF;
    rBM.extdSeg3XferPtrH=(bufferStartAddress >> 16);
}

/*******************************************************************
 *
 *  NAME:           mBMinitCntrl  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 val
 *					
 *  DESCRIPTION:    Initialize the buffer manager control register 0
 *                  with the value passed in the 'val' parameter.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMinitCntrl(mUINT_16 val)
{ 
    rBM.cntrlReg0.all = val;
}

/*******************************************************************
 *
 *  NAME:           mBMsetCntrl  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 val
 *					
 *  DESCRIPTION:    Or (set) the bits contained in the parameter "val'
 *                  in the buffer manager control register 0.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMsetCntrl(mUINT_16 val) 
{
    rBM.cntrlReg0.all |= val;
}

/*******************************************************************
 *
 *  NAME:           mBMclrCntrl  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 val
 *					
 *  DESCRIPTION:    And the negation (clear) the bits contained in the 
 *                  parameter "val' in the buffer manager control register 0.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMclrCntrl(mUINT_16 val) 
{
    rBM.cntrlReg0.all &= ~val;
}

/*******************************************************************
 *
 *  NAME:           mBMsetCntrl1  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 val
 *					
 *  DESCRIPTION:    Or (set) the bits contained in the parameter "val'
 *                  in the buffer manager control register 1.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMsetCntrl1(mUINT_16 val) 
{
    rBM.cntrlReg1.all |= val;
}

/*******************************************************************
 *
 *  NAME:           mBMclrCntrl1  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 val
 *					
 *  DESCRIPTION:    And the negation (clear) the bits contained in the 
 *                  parameter "val' in the buffer manager control register 1.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMclrCntrl1(mUINT_16 val) 
{
    rBM.cntrlReg1.all &= ~val;
}


/*******************************************************************
 *
 *  NAME:           mBMsetExpHostSeg0LnkLstPtr, mBMgetExpHostSeg0LnkLstPtr
 *                  mBMsetExpHostSeg1LnkLstPtr, mBMgetExpHostSeg1LnkLstPtr
 *                  mBMsetExpHostSeg2LnkLstPtr, mBMgetExpHostSeg2LnkLstPtr
 *                  mBMsetExpHostSeg3LnkLstPtr, mBMgetExpHostSeg3LnkLstPtr
 *                  mBMsetExpDiskSeg0LnkLstPtr, mBMgetExpDiskSeg0LnkLstPtr 
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 words
 *
 *  DESCRIPTION:    Set/get host or disk expected link list pointer
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMsetExpHostSeg0LnkLstPtr(mUINT_16 val)
{
    rBM.expHostSeg0LnkLstPtr.all = val;
}

__inline mUINT_16 mBMgetExpHostSeg0LnkLstPtr(void)
{
    return rBM.expHostSeg0LnkLstPtr.all;
}

__inline void mBMsetExpHostSeg1LnkLstPtr(mUINT_16 val)
{
    rBM.expHostSeg1LnkLstPtr.all = val;
}

__inline mUINT_16 mBMgetExpHostSeg1LnkLstPtr(void)
{
    return rBM.expHostSeg1LnkLstPtr.all;
}

__inline void mBMsetExpHostSeg2LnkLstPtr(mUINT_16 val)
{
    rBM.expHostSeg2LnkLstPtr.all = val;
}

__inline mUINT_16 mBMgetExpHostSeg2LnkLstPtr(void)
{
    return rBM.expHostSeg2LnkLstPtr.all;
}

__inline void mBMsetExpHostSeg3LnkLstPtr(mUINT_16 val)
{
    rBM.expHostSeg3LnkLstPtr.all = val;
}

__inline mUINT_16 mBMgetExpHostSeg3LnkLstPtr(void)
{
    return rBM.expHostSeg3LnkLstPtr.all;
}

__inline void mBMsetExpDiskSeg0LnkLstPtr(mUINT_16 val)
{
    rBM.expDiskSeg0LnkLstPtr.all = val;
}

__inline mUINT_16 mBMgetExpDiskSeg0LnkLstPtr(void)
{
    return rBM.expDiskSeg0LnkLstPtr.all;
}

/*******************************************************************
 *
 *  NAME:           mBMsetHostSegLnkLstStopPtr, mBMsetDiskSegLnkLstStopPtr
 *                  mBMgetHostSegLnkLstStopPtr, mBMgetDiskSegLnkLstStopPtr
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 words
 *
 *  DESCRIPTION:    Set host or disk stop link list pointer
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMsetHostSegLnkLstStopPtr(mUINT_16 val)
{
    rBM.hostSegLnkLstStopPtr.all = val;
}

__inline void mBMsetDiskSegLnkLstStopPtr(mUINT_16 val)
{
    rBM.diskSegLnkLstStopPtr.all = val;
}

__inline mUINT_16 mBMgetHostSegLnkLstStopPtr(void)
{
    return rBM.hostSegLnkLstStopPtr.all;
}

__inline mUINT_16 mBMgetDiskSegLnkLstStopPtr(void)
{
    return rBM.diskSegLnkLstStopPtr.all;
}

/*******************************************************************
 *
 *  NAME:           mBMsetSectorSize  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 words
 *
 *  DESCRIPTION:    Load the buffer manager sector size register
 *                  with the contents of the 'words' parameter.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMsetHostSectorSize(mUINT_16 hostWords) 
{
    rBM.hostSectorSize.all = hostWords;
}

__inline void mBMsetDiskSectorSize(mUINT_16 diskWords) 
{
    rBM.diskSectorSize.all = diskWords;
}

/*******************************************************************
 *
 *  NAME:           mBMgetDiskSegSize  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     None
 *
 *  DESCRIPTION:    Returns the contents of the buffer manager  
 *                  Disk segment size register
 *
 *  RETURNS:        type mUINT_16 
 *
 *******************************************************************/
__inline mUINT_16 mBMgetDiskSegSize(void)   
{
    return rBM.diskSeg0Size;
}

__inline mUINT_16 mBMgetDiskSeg1Size(void)   
{
    return rBM.diskSeg1Size;
}

__inline mUINT_16 mBMgetDiskSeg2Size(void)   
{
    return rBM.diskSeg2Size;
}

__inline mUINT_16 mBMgetDiskSeg3Size(void)   
{
    return rBM.diskSeg3Size;
}

/*******************************************************************
 *
 *  NAME:           mBMsetDiskSegSize  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 num_sectors
 *
 *  DESCRIPTION:    Load the buffer manager Disk segment size register
 *                  with the contents of the 'num_sectors' parameter.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMsetDiskSeg0Size(mUINT_16 num_sectors)   
{
    rBM.diskSeg0Size = (mtDISK_SEG_SIZE)num_sectors;
}

__inline void mBMsetDiskSeg1Size(mUINT_16 num_sectors)   
{
    rBM.diskSeg1Size = (mtDISK_SEG_SIZE)num_sectors;
}

__inline void mBMsetDiskSeg2Size(mUINT_16 num_sectors)   
{
    rBM.diskSeg2Size = (mtDISK_SEG_SIZE)num_sectors;
}

__inline void mBMsetDiskSeg3Size(mUINT_16 num_sectors)   
{
    rBM.diskSeg3Size = (mtDISK_SEG_SIZE)num_sectors;
}


/*******************************************************************
 *
 *  NAME:           mBMsetExtSegSize  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 num_sectors
 *
 *  DESCRIPTION:    Load the buffer manager Disk segment size register
 *                  with the contents of the 'num_sectors' parameter.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMsetExtSeg0Size(mUINT_16 num_sectors)   
{
    rBM.extdSeg0Size = (mtEXTD_SEG_SIZE)num_sectors;
}

__inline void mBMsetExtSeg1Size(mUINT_16 num_sectors)   
{
    rBM.extdSeg1Size = (mtEXTD_SEG_SIZE)num_sectors;
}

__inline void mBMsetExtSeg2Size(mUINT_16 num_sectors)   
{
    rBM.extdSeg2Size = (mtEXTD_SEG_SIZE)num_sectors;
}

__inline void mBMsetExtSeg3Size(mUINT_16 num_sectors)   
{
    rBM.extdSeg3Size = (mtEXTD_SEG_SIZE)num_sectors;
}

/*******************************************************************
 *
 *  NAME:           mBMgetStatus, mBMsetStatus  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     None
 *
 *  DESCRIPTION:    Returns the contents of the buffer manager 
 *                  status register.
 *
 *  RETURNS:        type mUINT_16 
 *
 *******************************************************************/
__inline mUINT_16 mBMgetStatus0(void)
{
    return rBM.stat0.all;
}

__inline void mBMsetStatus1(mUINT_16 val)
{
    rBM.stat1.all = val;
}

__inline mUINT_16 mBMgetStatus1(void)
{
    return rBM.stat1.all;
}


/*******************************************************************
 *
 *  NAME:           mBMsetHostSegStart
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mtBUFFER_ADDRESS bufferStartAddress
 *
 *  DESCRIPTION:    Load the host segment starting address with the address
 *                  specified in the 'bufferStartAddress' parameter.
 *
 *  RETURNS:        None
 *
 *******************************************************************/

 /*******************************************************************
 *
 *  NAME:           mBMinitHSSC
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mINT_NATIVE value
 *
 *  DESCRIPTION:    Load the host segment sector count with the value
 *                  specified in the 'value' parameter.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
 //code for LJ
__inline void  mBMinitHS0SC (mINT_NATIVE value)
{
    rBM.hostSeg0SecCnt = value;
}

__inline void  mBMinitHS1SC (mINT_NATIVE value)
{
    rBM.hostSeg1SecCnt = value;
}

__inline void  mBMinitHS2SC (mINT_NATIVE value)
{
    rBM.hostSeg2SecCnt = value;
}

__inline void  mBMinitHS3SC (mINT_NATIVE value)
{
    rBM.hostSeg3SecCnt = value;
}

__inline void  mBMinitHS4SC (mINT_NATIVE value)
{
    rBM.hostSeg4SecCnt = value;
}

__inline void  mBMinitHS5SC (mINT_NATIVE value)
{
    rBM.hostSeg5SecCnt = value;
}

__inline void  mBMinitHS6SC (mINT_NATIVE value)
{
    rBM.hostSeg6SecCnt = value;
}

__inline void  mBMinitHS7SC (mINT_NATIVE value)
{
    rBM.hostSeg7SecCnt = value;
}

                    
 /*******************************************************************
 *
 *  NAME:           mBMgetHSSC
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     None
 *
 *  DESCRIPTION:    Get the host segment sector count 
 *
 *  RETURNS:        Host segment sector count
 *
 *******************************************************************/
__inline mINT_16 mBMgetHS0SC (void)
{
    return rBM.hostSeg0SecCnt;
}

__inline mINT_16 mBMgetHS1SC (void)
{
    return rBM.hostSeg1SecCnt;
}

__inline mINT_16 mBMgetHS2SC (void)
{
    return rBM.hostSeg2SecCnt;
}

__inline mINT_16 mBMgetHS3SC (void)
{
    return rBM.hostSeg3SecCnt;
}

__inline mINT_16 mBMgetHS4SC (void)
{
    return rBM.hostSeg4SecCnt;
}

__inline mINT_16 mBMgetHS5SC (void)
{
    return rBM.hostSeg5SecCnt;
}

__inline mINT_16 mBMgetHS6SC (void)
{
    return rBM.hostSeg6SecCnt;
}

__inline mINT_16 mBMgetHS7SC (void)
{
    return rBM.hostSeg7SecCnt;
}



/*******************************************************************
 *
 *  NAME:           mBMsetDisksegSectCnt  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mINT_NATIVE value
 *
 *  DESCRIPTION:    Load the Disk segment sector count with the value
 *                  specified in the 'value' parameter.
 *
 *  RETURNS:        None 
 *
 *******************************************************************/
__inline void mBMsetDiskseg0SectCnt(mINT_NATIVE value)
{
    rBM.diskSeg0SectorCnt = value;
}

__inline void mBMsetDiskseg1SectCnt(mINT_NATIVE value)
{
    rBM.diskSeg1SectorCnt = value;
}

__inline void mBMsetDiskseg2SectCnt(mINT_NATIVE value)
{
    rBM.diskSeg2SectorCnt = value;
}

__inline void mBMsetDiskseg3SectCnt(mINT_NATIVE value)
{
    rBM.diskSeg3SectorCnt = value;
}

/*******************************************************************
 *
 *  NAME:           mBMgetDisksegSectCnt  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     None
 *
 *  DESCRIPTION:    Returns the contents of the buffer manager disk 
 *                  segment sector count register.
 *
 *  RETURNS:        type mUINT_16 
 *
 *******************************************************************/
__inline mUINT_16 mBMgetDiskseg0SectCnt(void)
{
    return rBM.diskSeg0SectorCnt;
}

__inline mUINT_16 mBMgetDiskseg1SectCnt(void)
{
    return rBM.diskSeg1SectorCnt;
}

__inline mUINT_16 mBMgetDiskseg2SectCnt(void)
{
    return rBM.diskSeg2SectorCnt;
}

__inline mUINT_16 mBMgetDiskseg3SectCnt(void)
{
    return rBM.diskSeg3SectorCnt;
}



/*******************************************************************
 *
 *  NAME:           mBMsetExtsegSectCnt  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mINT_NATIVE value
 *
 *  DESCRIPTION:    Load the Disk segment sector count with the value
 *                  specified in the 'value' parameter.
 *
 *  RETURNS:        None 
 *
 *******************************************************************/
__inline void mBMsetExtseg0SectCnt(mINT_NATIVE value)
{
    rBM.extdSeg0SectorCnt = value;
}

__inline void mBMsetExtseg1SectCnt(mINT_NATIVE value)
{
    rBM.extdSeg1SectorCnt = value;
}

__inline void mBMsetExtseg2SectCnt(mINT_NATIVE value)
{
    rBM.extdSeg2SectorCnt = value;
}

__inline void mBMsetExtseg3SectCnt(mINT_NATIVE value)
{
    rBM.extdSeg3SectorCnt = value;
}

/*******************************************************************
 *
 *  NAME:           mBMsetAWsegSectCnt  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mINT_NATIVE value
 *
 *  DESCRIPTION:    Load the AutoWrite segment sector count with the value
 *                  specified in the 'value' parameter.
 *
 *  RETURNS:        None 
 *
 *******************************************************************/

/*******************************************************************
 *
 *  NAME:           mBMhostSegAdjSel  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 value
 *
 *  DESCRIPTION:    Select Host segment to adjust sector count.
 *
 *  RETURNS:        None 
 *
 *******************************************************************/
__inline void mBMhostSegAdjSel(mUINT_16 value)
{
    rBM.hostSegAdjSel = value;
}

/*******************************************************************
 *
 *  NAME:           mBMadjustHostsegSectCnt  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mINT_NATIVE value
 *
 *  DESCRIPTION:    Adjust Host segment sector count with the value
 *                  specified in the 'value' parameter.
 *
 *  RETURNS:        None 
 *
 *******************************************************************/
__inline void mBMadjustHostSegSectCnt(mINT_NATIVE value)
{
    rBM.hostSegSectCntAdj = value;
}

/*******************************************************************
 *
 *  NAME:           mBMadjustDisksegSectCnt  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mINT_NATIVE value
 *
 *  DESCRIPTION:    Adjust Disk segment sector count with the value
 *                  specified in the 'value' parameter.
 *
 *  RETURNS:        None 
 *
 *******************************************************************/
__inline void mBMadjustDiskSegSectCnt(mINT_NATIVE value)
{
    rBM.SSC1adjust = value;
}

/*******************************************************************
 *
 *  NAME:           mBMdiskSegSecCntSel  
 *
 *  FILENAME:       mBM.h
 *
 *  DESCRIPTION:    Load the buffer manager disk segment sector
 *                  counter control with the contents of the 'val'
 *                  parameter.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
  //#if (mDAVINCI_COMPATIBLE == mENABLE)
#if 0
__inline void mBMdiskSegSecCntSel(mUINT_NATIVE val) 
{
    rBM.diskLSSCsel.bits.dskLSSC = val;
}

__inline mUINT_NATIVE mBMgetDiskLogicSegSecCntSel(void) 
{
	return (rBM.diskLSSCsel.bits.dskLSSC);
}

__inline void mBMsetHstSSCtoSSC1(void) 
{
    rBM.diskLSSCsel.bits.hstSSCtoSSC1 = 1;      
}

__inline void mBMclearHstSSCtoSSC1(void) 
{
    rBM.diskLSSCsel.bits.hstSSCtoSSC1 = 0;      
}

__inline mUINT_16 mBMgetHstSSCtoSSC1(void) 
{
    return(rBM.diskLSSCsel.bits.hstSSCtoSSC1);      
}

__inline void mBMrestoreHstSSCtoSSC1(mUINT_16 val) 
{
    rBM.diskLSSCsel.bits.hstSSCtoSSC1 = val;      
}

  #else //(mDAVINCI_COMPATIBLE == mENABLE)
__inline void mBMdiskSegSecCntSel(mUINT_NATIVE val) 
{
    rBM.diskStreamCtrl.bits.diskHostSel = val;
}

__inline mUINT_NATIVE mBMgetDiskLogicSegSecCntSel(void) 
{
	return (rBM.diskStreamCtrl.bits.diskHostSel);
}

__inline void mBMsetHstSSCtoSSC1(void) 
{
    rBM.diskStreamCtrl.bits.host2disk = 1;      
}

__inline void mBMclearHstSSCtoSSC1(void) 
{
    rBM.diskStreamCtrl.bits.host2disk = 0;      
}

__inline mUINT_16 mBMgetHstSSCtoSSC1(void) 
{
    return(rBM.diskStreamCtrl.bits.host2disk);      
}

__inline void mBMrestoreHstSSCtoSSC1(mUINT_16 val) 
{
    rBM.diskStreamCtrl.bits.host2disk = val;      
}
  #endif //(mDAVINCI_COMPATIBLE == mENABLE)


/*******************************************************************
 *
 *  NAME:           mBMdiskSegSel  
 *
 *  FILENAME:       mBM.h
 *
 *  DESCRIPTION:    Select disk segment
 *
 *  RETURNS:        None
 *
 *******************************************************************/
  //#if(mDAVINCI_COMPATIBLE == mENABLE)
  #if 0
__inline void mBMdiskSegSel(mUINT_NATIVE val)
{
    rBM.diskSegSelect.bits.dskSegsel = val;
    rBM.diskSegAdjSel = val;
}

__inline void mBMsetDskSSCtoSSC1(void) 
{
    rBM.diskSegSelect.bits.dskSCCtoSSC1 = 1;
}

__inline void mBMclearDskSSCtoSSC1(void) 
{
    rBM.diskSegSelect.bits.dskSCCtoSSC1 = 0;
}

__inline void mBMsetHstSSCtoSSC1AndDiskSegSecCntSel(mUINT_16 val) 
{
    rBM.diskLSSCsel.all = (1 << 5) + val;      
}

  #else //(mDAVINCI_COMPATIBLE == mENABLE)
__inline void mBMdiskSegSel(mUINT_NATIVE val)
{
    rBM.diskSegSelect.bits.dskSegsel = val;
    rBM.diskSegAdjSel = val;
}

__inline void mBMsetDskSSCtoSSC1(void) 
{
    rBM.diskStreamCtrl.bits.host2disk = 1;
}

__inline void mBMclearDskSSCtoSSC1(void) 
{
    rBM.diskStreamCtrl.bits.host2disk = 0;
}

__inline void mBMsetHstSSCtoSSC1AndDiskSegSecCntSel(mUINT_16 val) 
{
    mUINT_16 diskStreamCtrl;
    
    diskStreamCtrl = rBM.diskStreamCtrl.all;
    diskStreamCtrl &= 0xFFF0;
    rBM.diskStreamCtrl.all = (diskStreamCtrl | ((1 << 5) + val));
}
  #endif //(mDAVINCI_COMPATIBLE == mENABLE)


__inline void mBMExtSegSel(mUINT_NATIVE val)
{
    rBM.extdSegSel.bits.extSegsel = val;
    rBM.extdSegAdjSel = val;
}


__inline mUINT_8 mGetBMdiskSegSel()
{
    return(rBM.diskSegSelect.bits.dskSegsel);
}

/*******************************************************************
 *
 *  NAME:           mBMintrDisable  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 val
 *
 *  DESCRIPTION:    Load the buffer manager interrupt enable register
 *                  with the contents of the 'val' parameter.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMintr0Init(mUINT_16 val) 
{
    rBM.intEnable0.all = val;
}

__inline void mBMintr0Enable(mUINT_16 val) 
{
    rBM.intEnable0.all &= ~val;
}

__inline void mBMintr0Disable(mUINT_16 val) 
{
    rBM.intEnable0.all |= val;
}

__inline void mBMintr1Init(mUINT_16 val) 
{
    rBM.intEnable1.all = val;
}

__inline void mBMintr1Enable(mUINT_16 val) 
{
    rBM.intEnable1.all &= ~val;
}

__inline void mBMintr1Disable(mUINT_16 val) 
{
    rBM.intEnable1.all |= val;
}

/*******************************************************************
 *
 *  NAME:           mBMgetHostsegSize  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     None
 *
 *  DESCRIPTION:    Returns the contents of the buffer manager AW 
 *                  segment size register.
 *
 *  RETURNS:        type mUINT_16 
 *
 *******************************************************************/
__inline mUINT_16 mBMgetHostSeg0Size(void)   
{
    return rBM.hostSeg0Size ;
}

__inline mUINT_16 mBMgetHostSeg1Size(void)   
{
    return rBM.hostSeg1Size ;
}

__inline mUINT_16 mBMgetHostSeg2Size(void)   
{
    return rBM.hostSeg2Size ;
}

__inline mUINT_16 mBMgetHostSeg3Size(void)   
{
    return rBM.hostSeg3Size ;
}

__inline mUINT_16 mBMgetHostSeg4Size(void)   
{
    return rBM.hostSeg4Size ;
}

__inline mUINT_16 mBMgetHostSeg5Size(void)   
{
    return rBM.hostSeg5Size ;
}

__inline mUINT_16 mBMgetHostSeg6Size(void)   
{
    return rBM.hostSeg6Size ;
}

__inline mUINT_16 mBMgetHostSeg7Size(void)   
{
    return rBM.hostSeg7Size ;
}

/*******************************************************************
 *
 *  NAME:           mBMsetHostSegSize  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 num_sectors
 *
 *  DESCRIPTION:    Load the buffer manager Host segment size register
 *                  with the contents of the 'num_sectors' parameter.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMsetHostSeg0Size(mUINT_16 num_sectors)   
{
    rBM.hostSeg0Size = (mtHOST_SEG_SIZE)num_sectors;
}

__inline void mBMsetHostSeg1Size(mUINT_16 num_sectors)   
{
    rBM.hostSeg1Size = (mtHOST_SEG_SIZE)num_sectors;
}

__inline void mBMsetHostSeg2Size(mUINT_16 num_sectors)   
{
    rBM.hostSeg2Size = (mtHOST_SEG_SIZE)num_sectors;
}

__inline void mBMsetHostSeg3Size(mUINT_16 num_sectors)   
{
    rBM.hostSeg3Size = (mtHOST_SEG_SIZE)num_sectors;
}

__inline void mBMsetHostSeg4Size(mUINT_16 num_sectors)   
{
    rBM.hostSeg4Size = (mtHOST_SEG_SIZE)num_sectors;
}

__inline void mBMsetHostSeg5Size(mUINT_16 num_sectors)   
{
    rBM.hostSeg5Size = (mtHOST_SEG_SIZE)num_sectors;
}

__inline void mBMsetHostSeg6Size(mUINT_16 num_sectors)   
{
    rBM.hostSeg6Size = (mtHOST_SEG_SIZE)num_sectors;
}

__inline void mBMsetHostSeg7Size(mUINT_16 num_sectors)   
{
    rBM.hostSeg7Size = (mtHOST_SEG_SIZE)num_sectors;
}


/*******************************************************************
 *
 *  NAME:           mBMinitRefreshPeriod
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     uint 16 value
 *
 *  DESCRIPTION:    Initialize refresh period setting with the value
 *                  passed in the 'val' parameter.
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMinitRefreshPeriod(mUINT_16 val)
{ 
    rBM.refPeriod.bits.value = val;
}
/*******************************************************************
 *
 *  NAME:           mBMsetSectorRate  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     None
 *
 *  DESCRIPTION:    Sets the  sector size ratio register
 *                  
 *
 *  RETURNS:        None
 *
 *******************************************************************/
__inline void mBMsetSectorSizeRatio(mUINT_16 val) 
{
    rBM.sectorSizeRatio = val;
}

/*******************************************************************
 *
 *  NAME:           mBMsetSubSegDescSize, mBMgetSubSegDescSize  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     See below.
 *
 *  DESCRIPTION:    Set or get the Sub Segment Descriptor Size.
 *
 *  RETURNS:        See below.
 *
 *******************************************************************/
__inline void mBMsetSubSegDescSize(mUINT_16 val)
{
    rBM.ssdCtrl.bits.descSize = val;
} 
__inline mUINT_16 mBMgetSubSegDescSize(void)
{
    return (rBM.ssdCtrl.bits.descSize);
} 

/*******************************************************************
 *
 *  NAME:           mBMsetSubSegDescTableStartAddr, mBMgetSubSegDescTableStartAddr 
 *                  mBMsetSubSegDescTableEndAddr, mBMgetSubSegDescTableEndAddr
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     See below.
 *
 *  DESCRIPTION:    Set or get the Sub Segment Descriptor table start or end address.
 *
 *  RETURNS:        See below.
 *
 *******************************************************************/
__inline void mBMsetSubSegDescTableStartAddr(mUINT_32 val)
{
    rBM.ssdTableStartL = val;
    rBM.ssdTableStartH = val >> 16;
} 
__inline mUINT_32 mBMgetSubSegDescTableStartAddr(void) 
{
    return (((mUINT_32)rBM.ssdTableStartH) << 16 + rBM.ssdTableStartL);
}

__inline void mBMsetSubSegDescTableEndAddr(mUINT_32 val) 
{
    rBM.ssdTableEndL = val;
    rBM.ssdTableEndH = val >> 16;
} 

__inline mUINT_32 mBMgetSubSegDescTableEndAddr(void) 
{
    return (((mUINT_32)rBM.ssdTableEndH) << 16 + rBM.ssdTableEndL);
}

/*******************************************************************
 *
 *  NAME:           mBMSelectFStoESSC  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mINT_NATIVE value
 *
 *  DESCRIPTION:    Flash Segment connect to ES segment 
 *                  specified in the 'value' parameter.
 *
 *  RETURNS:        None 
 *
 *******************************************************************/
__inline void mBMSelectFStoESSC(mINT_NATIVE value)
{
    rBM.diskStreamCtrl.bits.diskExtdSel = value;
}

/*******************************************************************
 *
 *  NAME:           mBMSelectEStoFSSC  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mINT_NATIVE value
 *
 *  DESCRIPTION:    Extend Segment connect to FS segment 
 *                  specified in the 'value' parameter.
 *
 *  RETURNS:        None 
 *
 *******************************************************************/
__inline void mBMSelectEStoFSSC(mINT_NATIVE value)
{
    rBM.extdStreamCtrl.bits.extdDiskSel = value;
}

/*******************************************************************
 *
 *  NAME:           mBMSelectHStoFSSC  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mINT_NATIVE value
 *
 *  DESCRIPTION:    Host Segment connect to FS segment 
 *                  specified in the 'value' parameter.
 *
 *  RETURNS:        None 
 *
 *******************************************************************/
__inline void mBMSelectHStoFSSC(mINT_NATIVE value)
{
    rBM.hostStreamCtrl.bits.hostDiskSel = value;
}

/*******************************************************************
 *
 *  NAME:           mBMSelectHStoESSC  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mINT_NATIVE value
 *
 *  DESCRIPTION:    Host Segment connect to ES segment 
 *                  specified in the 'value' parameter.
 *
 *  RETURNS:        None 
 *
 *******************************************************************/
__inline void mBMSelectHStoESSC(mINT_NATIVE value)
{
    rBM.hostStreamCtrl.bits.hostExtdSel = value;
}

/*******************************************************************
 *
 *  NAME:           mBMSelectFStoHSSC  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mINT_NATIVE value
 *
 *  DESCRIPTION:    Flash Segment connect to HS segment 
 *                  specified in the 'value' parameter.
 *
 *  RETURNS:        None 
 *
 *******************************************************************/
__inline void mBMSelectFStoHSSC(mINT_NATIVE value)
{
    rBM.diskStreamCtrl.bits.diskHostSel = value;
}

/*******************************************************************
 *
 *  NAME:           mBMSelectEStoHSSC  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mINT_NATIVE value
 *
 *  DESCRIPTION:    Extend Segment connect to HS segment 
 *                  specified in the 'value' parameter.
 *
 *  RETURNS:        None 
 *
 *******************************************************************/
__inline void mBMSelectEStoHSSC(mINT_NATIVE value)
{
    rBM.extdStreamCtrl.bits.extdHostSel = value;
}

/*******************************************************************
 *
 *  NAME:           mBMCopyHSSCtoFSSC  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mINT_NATIVE value
 *
 *  DESCRIPTION:    Copy HSSC to FSSC 
 *
 *  RETURNS:        None 
 *
 *******************************************************************/
__inline void mBMCopyHSSCtoFSSC(mINT_NATIVE value)
{
    rBM.diskStreamCtrl.bits.host2disk = value ;
}

/*******************************************************************
 *
 *  NAME:           mBMCopyFSSCtoHSSC  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mINT_NATIVE value
 *
 *  DESCRIPTION:    Copy FSSC to HSSC 
 *
 *  RETURNS:        None 
 *
 *******************************************************************/
__inline void mBMCopyFSSCtoHSSC(mINT_NATIVE value)
{
    rBM.hostStreamCtrl.bits.disk2host = value ;
}
/*******************************************************************
 *
 *  NAME:           mBMdiskSegAdjSel  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 value
 *
 *  DESCRIPTION:    Select disk segment to adjust sector count.
 *
 *  RETURNS:        None 
 *
 *******************************************************************/
__inline void mBMdiskSegAdjSel(mUINT_16 value)
{
    rBM.diskSegAdjSel = value;
}

/*******************************************************************
 *
 *  NAME:           mBMgetHostCurSegSecCntSel  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     
 *
 *  DESCRIPTION:    get curent host segment selected
 *
 *  RETURNS:        current host segment selected 
 *
 *******************************************************************/
__inline mUINT_16 mBMgetHostCurSegSecCntSel(void) 
{
	return (rBM.curHostSegSel.bits.curhSegSel);
}

/*******************************************************************
 *
 *  NAME:           mBMsetHostCurSegSecCntSel  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 value
 *
 *  DESCRIPTION:    set curent host segment selected
 *
 *  RETURNS:        current host segment selected 
 *
 *******************************************************************/
__inline void mBMsetHostCurSegSecCntSel(mUINT_16 value) 
{
	rBM.curHostSegSel.bits.curhSegSel = value;
}

/*******************************************************************
 *
 *  NAME:           mBMsetDVcompatibleMode  
 *
 *  FILENAME:       mBM.h
 *
 *  PARAMETERS:     type mUINT_16 value
 *
 *  DESCRIPTION:    set DV compatible mode
 *
 *  RETURNS:        none 
 *
 *******************************************************************/
__inline void mBMsetDVcompatibleMode(mtBOOLEAN val) 
{
	rBM.bmTestModeSel.bits.DVcompatible = val;
}

#endif  //_H_INC


