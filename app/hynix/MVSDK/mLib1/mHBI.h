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

#ifndef     _mHBI_H_INC
  #define   _mHBI_H_INC

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

#ifdef      INSTANTIATE_MARVELL_HBI
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
EXTERN __inline void    mHBIreset               (void);
EXTERN __inline void    mHBIstartXfer           (void);
EXTERN __inline void    mHBIstopXfer            (void);
EXTERN __inline void    mHBIsetCxsbFwReqEoc     (void);
EXTERN __inline void    mHBIclrXMLOGSBCnt       (void);
EXTERN __inline void    mHBIclrHBIreset         (void);
EXTERN __inline void    mHBIsetSeqRdLbaMode     (void);  
EXTERN __inline void    mHBIsetSeqWrLbaMode     (void); 
EXTERN __inline void    mHBIsetHdPerCyl         (mUINT_8 val);
EXTERN __inline void    mHBIsetSecPerTrk        (mUINT_8 val);
EXTERN __inline void    mHBIsetStatus           (mUINT_8 bit);
EXTERN __inline void    mHBIsetError            (mUINT_8 bit);
EXTERN __inline void    mHBIclrStatus           (mUINT_8 bits);
EXTERN __inline void    mHBIinitStatus          (mUINT_8 bits);
EXTERN __inline void    mHBIsetFwStatus         (mUINT_8 val);
EXTERN __inline void    mHBIsetAltAtError       (mUINT_8 bits);
EXTERN __inline void    mHBIsetAltAtStatus      (mUINT_8 bits);

EXTERN __inline void    mHBIclrIntrStatus       (mUINT_16 bits); 
EXTERN __inline void    mHBIsetBitAtMode        (mUINT_16 bits);
EXTERN __inline void    mHBIclrBitAtMode        (mUINT_16 bits);
EXTERN __inline void    mHBIsetHostDir          (mUINT_16 dir);
EXTERN __inline void    mHBIsetConfgCntrl       (mUINT_16 val);

EXTERN __inline void    mHBIsetMultipleBlkSize  (mINT_16 sectorsPerBlk);
EXTERN __inline void    mHBIsetAutoWriteCntl    (mUINT_16 val);
EXTERN __inline void    mHBIsetESATAflowPwrRstCntl  (mUINT_16 bits); 
EXTERN __inline void    mHBIclrESATAflowPwrRstCntl  (mUINT_16 bits); 
EXTERN __inline void    mHBIsetCxsbFwReqSDBFisSend  (mUINT_16 qSlot);
EXTERN __inline void    mHBIclrTmStatusLow          (mUINT_16 bits);
EXTERN __inline void    mHBIclrTmStatusHi           (mUINT_16 bits);
EXTERN __inline void    mHBIsetMsgLogCntl           (mUINT_16 val);
EXTERN __inline void    mHBIsetBitMsgLogCntl        (mUINT_16 bits);
EXTERN __inline void    mHBIsetBitCxsbCntl          (mUINT_16 bits);
EXTERN __inline void    mHBIclrBitCxsbCntl          (mUINT_16 bits);
EXTERN __inline void    mHBIsetFdmaActivateDis      (mtBOOLEAN val); 
EXTERN __inline void    mHBISetBitMiscStatus        (mUINT_16 bits);
EXTERN __inline void    mHBIsetHostBufferSegSel     (mUINT_16 val);
EXTERN __inline void    mHBISetBitESATAconfig       (mUINT_16 bits);  
EXTERN __inline void    mHBIClrBitESATAconfig       (mUINT_16 bits);  
EXTERN __inline void    mHBIsetFISsize              (mUINT_16 val); 
EXTERN __inline void    mHBIclrTMflowIntrStatus     (mUINT_16 val);
EXTERN __inline void    mHBIsetEsataErrIntrSrc      (mUINT_16 val); 
EXTERN __inline void    mHBIclrEsataErrIntrStatus   (mUINT_16 val); 
EXTERN __inline void    mHBIinitPhyTunningControl   (mUINT_16 val);
EXTERN __inline void    mHBIsetSectorCount          (mUINT_16 val);
EXTERN __inline void    mHBIsetBlkXferCount         (mUINT_16 val);
EXTERN __inline void    mHBIsetUserFISword0L        (mUINT_16 val);
EXTERN __inline void    mHBIsetUserFISword0H        (mUINT_16 val);
EXTERN __inline void    mHBIsetUserFISword1L        (mUINT_16 val);
EXTERN __inline void    mHBIsetUserFISword1H        (mUINT_16 val);
EXTERN __inline void    mHBIsetUserFISword2L        (mUINT_16 val);
EXTERN __inline void    mHBIsetUserFISword2H        (mUINT_16 val);
EXTERN __inline void    mHBIsetUserFISword3L        (mUINT_16 val);
EXTERN __inline void    mHBIsetUserFISword3H        (mUINT_16 val);
EXTERN __inline void    mHBIsetUserFISword4L        (mUINT_16 val);
EXTERN __inline void    mHBIsetUserFISword4H        (mUINT_16 val);
EXTERN __inline void    mHBIsetManualFlowControl    (mUINT_16 val);
EXTERN __inline void    mHBIsetSectorNum            (mUINT_16 val);
EXTERN __inline void    mHBIsetMultipleFisSize      (mINT_16 sectorsPerBlk);
 
EXTERN __inline void    mHBIsetCxsbFwReqNonQDataXfer(mUINT_16 val, mUINT_16 bSeg, mtBOOLEAN writeOp, mtBOOLEAN autoStatusForWrite);
EXTERN __inline void    mHBIsetCxsbFwReqQcmdDataXfer(mUINT_16 count, mUINT_16 bSeg, mtBOOLEAN writeOp, mUINT_16 qSlot, mtBOOLEAN autoStatusForWrite);

EXTERN __inline mtBOOLEAN   mHBIisReadXferActive    (void);

EXTERN __inline mUINT_8     mHBIgetAtStatus         (void);
EXTERN __inline mUINT_8     mHBIgetAtCmd            (void);
EXTERN __inline mUINT_8     mHBIgetFwStatus         (void);
EXTERN __inline mUINT_8     mHBIgetFwError          (void);

EXTERN __inline mUINT_16    mHBIgetAutoReadCntl     (void);
EXTERN __inline mUINT_16    mHBIgetAutoWriteCntl    (void);
EXTERN __inline mUINT_16    mHBIgetMultipleBlkSize  (void);
EXTERN __inline mUINT_16    mHBIgetHostIntrStatus   (void);
EXTERN __inline mUINT_16    mHBIgetIntrDisable      (void);
EXTERN __inline mUINT_16    mHBIgetConfgCntrl       (void);
EXTERN __inline mUINT_16    mHBIgetAtMode           (void);
EXTERN __inline mUINT_16    mHBIgetMiscStatus       (void);
EXTERN __inline mUINT_16    mHBIgetQCmdControl      (void);  
EXTERN __inline mUINT_16    mHBIGetTMflowStatus     (void); 
EXTERN __inline mUINT_16    mHBIgetFISsize          (void); 
EXTERN __inline mUINT_16    mHBIgetTMflowIntrStatus (void);
EXTERN __inline mUINT_16    mHBIGetSectorNum        (void);
EXTERN __inline mUINT_16    mHBIgetEsataErrIntStatus(void);
EXTERN __inline mUINT_16    mHBIGetEsataErrIntSrc   (void);
EXTERN __inline mUINT_16    mHBIGetUserFISword1L    (void);
EXTERN __inline mUINT_16    mHBIGetESATAConfig      (void);
EXTERN __inline mUINT_16    mHBIgetESATAflowPowerResetCntl(void);
//SATA BIST command related functions
EXTERN __inline mUINT_16    mHBIgetBISTpattern      (void); 
EXTERN __inline mUINT_16    mHBIgetBISTW1L          (void); 
EXTERN __inline mUINT_16    mHBIgetBISTW1H          (void); 
EXTERN __inline mUINT_16    mHBIgetBISTW2L          (void); 
EXTERN __inline mUINT_16    mHBIgetBISTW2H          (void); 
EXTERN __inline mUINT_16    mHBIgetBlkXferCnt       (void);
EXTERN __inline mUINT_16    mHBIgetXMLOGSBCnt       (void);
EXTERN __inline mUINT_16    mHBIgetXMLOGSBData      (void);
EXTERN __inline mUINT_16    mHBIgetTmPhase          (void);
EXTERN __inline mUINT_16    mHBIgetTmStatusLow      (void);
EXTERN __inline mUINT_16    mHBIgetCxsbCntl         (void);
EXTERN __inline mUINT_16    mHBIgetMsgLogCntl       (void);
EXTERN __inline mUINT_16    mHBIgetCmdTagId         (void);

EXTERN __inline void        mHBIsetSequentialReadLba    (mtLBA lba);
EXTERN __inline mtLBA       mHBIgetSequentialReadLba    (void);
EXTERN  void                mHBIsetTaskFileReg          (mtATA_TASK_FILE_REGS AtReg,mUINT_8 value);  
EXTERN  mUINT_8             mHBIgetTaskFileReg          (mtATA_TASK_FILE_REGS AtReg);

EXTERN void                 mHBIsetTimeStampCountLow(mUINT_16 val);
EXTERN void                 mHBIsetTimeStampCountHigh(mUINT_16 val);

#define mDWORDS_PER_SECTOR 0x80
#define mAUTO_RD_SEQ_BITS  0x7
#define mAUTO_WR_SEQ_BITS  0x90E
 
#define mHostGetSectorCntfromQslot(val)   mHBIgetSectorCntfromQslot ((val))



#ifdef __ghs__
    #pragma ghs section bss = ".rHDC_HBI"
    EXTERN volatile  mtHOST_BUS_INTERFACE rHBI;  
    #pragma ghs section
#else  
    #pragma arm section zidata = "rHDC_HBI"
    EXTERN volatile  mtHOST_BUS_INTERFACE rHBI;  
    #pragma arm section zidata
#endif    

/*******************************************************************
*																   
*  NAME:        mHBIclrHBIreset    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to clear reset of HBI block.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIclrHBIreset(void)
{
    rHBI.ATdevConfgCntrl.bits.clrHbiRst = 1;        // clear HBI reset
}


/*******************************************************************
*																   
*  NAME:        mHBIreset    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to reset the ATA  host bus interface.   
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIreset(void)
{
    mHBIclrIntrStatus (m_tHBI_INT_bits_hardReset);
    rHBI.ATdevConfgCntrl.bits.clrHbiRst = 1;        // clear HBI reset
}

/*******************************************************************
*																   
*  NAME:        mHBIsetTimeStampCntLow    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to set the value of Timestamp Counter Low R4B50
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetTimeStampCntLow(mUINT_16 val)
{
    rHBI.timestampClkCntrLo.all = val;      
}


/*******************************************************************
*																   
*  NAME:        mHBIsetTimeStampCntHigh    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to set the value of Timestamp Counter High R4B52
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetTimeStampCntHigh(mUINT_16 val)
{
	rHBI.timestampClkCntrHi.all &= 0xFFF0;
    rHBI.timestampClkCntrHi.all |= val;
}



/*******************************************************************
*																   
*  NAME:        mHBIsetHostBufferSegSel    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to select which segment is used for AutoWRite,
*               auto sequential Write, manual read/write, auto read..
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetHostBufferSegSel(mUINT_16 val)
{
    rHBI.hostBufferSegSel.all = val;        
}


/*******************************************************************
*																   
*  NAME:        mHBIstartXfer    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to start host transfer 
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIstartXfer(void)
{
    rHBI.hostMiscStatus.bits.xferActive = 1; 
}

/*******************************************************************
*																   
*  NAME:        mHBIstopXfer    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to stop host transfer 
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIstopXfer(void)
{
}

/*******************************************************************
*																   
*  NAME:        mHBIisReadXferActive    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to check if host xfer is active for a read command. 
*
*  RETURNS:     mTRUE or mFALSE
*
********************************************************************/
__inline mtBOOLEAN mHBIisReadXferActive(void)
{
    if ((mHBIgetMiscStatus() & m_tHOST_BUS_INTERFACE_hostMiscStatus_bits_xferActive) && (!(mHBIgetAtMode() & m_tHOST_BUS_INTERFACE_ATmode0_bits_writeDir)))
    {
        return mTRUE;
    }
    else
    {
        return mFALSE;
    } 
}

/*******************************************************************
*																   
*  NAME:        mHBIsetHostDir    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 dir (0 or 1)
*
*  DESCRIPTION: HAL function to Set host direction (0 Read, 
*               1 write)     
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetHostDir(mUINT_16 dir)
{
    rHBI.ATmode0.bits.writeDir = dir;        
}



/*******************************************************************
*																   
*  NAME:        mHBIsetConfgCntrl    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to load the HBI config register with
*               the contents of the 'val' parameter.    
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetConfgCntrl(mUINT_16 val) 
{
    rHBI.ATdevConfgCntrl.all = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetError    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_8 bits
*
*  DESCRIPTION: HAl function to set the bits in HBI block error    
*               register marked by the 'bits' parameter. 
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetError(mUINT_8 bits)
{
    rHBI.error = bits;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetAutoWriteCntl    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to load the HBI Auto Write Control 
*               register with the contents of the 'val' parameter.    
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetAutoWriteCntl(mUINT_16 val) 
{
// Kim - need to revist for m8925 - just for initial release to fix compile errors
    rHBI.aceConfig2.all = (rHBI.aceConfig2.all) | val;
}

/*******************************************************************
*																   
*  NAME:        mHBIgetAutoWriteCntl    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to return the contents of the HBI   
*               Auto Write Control register.
*
*  RETURNS:     type UNIT_8 HBI Auto Write Control register
*
********************************************************************/
__inline mUINT_16 mHBIgetAutoWriteCntl(void)
{
    return (rHBI.aceConfig2.all & 0x7F);
}

/*******************************************************************
*																   
*  NAME:        mHBIsetAutoReadCntl    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_8 val
*
*  DESCRIPTION: HAL function to load the HBI Auto Read Control 
*               register with the contents of the 'val' parameter.    
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetAutoReadCntl(mUINT_16 val)  
{
    rHBI.aceConfig2.all = (rHBI.aceConfig2.all) | val;
}

/*******************************************************************
*																   
*  NAME:        mHBIgetAutoReadCntl    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to return ACE Control register.    
*
*  RETURNS:     ACE for read setting.
*
********************************************************************/
__inline mUINT_16 mHBIgetAutoReadCntl(void)
{
  return (rHBI.aceConfig1.all & 0x7F00);
}

/*******************************************************************
*																   
*  NAME:        mHBIsetHdPerCyl    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_8 val
*
*  DESCRIPTION: HAL function to load the HBI Host head per cylinder  
*               register with the contents of the 'val' parameter.    
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetHdPerCyl(mUINT_8 val)   
{
    rHBI.hostHdPerCyl = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetSecPerTrk    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_8 val
*
*  DESCRIPTION: HAL function to load the HBI host sector per track  
*               register with the contents of the 'val' parameter.    
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetSecPerTrk(mUINT_8 val)  
{
    rHBI.hostSecPerTrk = val;
}


/*******************************************************************
*																   
*  NAME:        mHBIgetStatus    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:     
*  DESCRIPTION: HAL function to get the bits in HBI block status    
*               register m
*  RETURNS:     mUINT_16
*
********************************************************************/
__inline mUINT_16 mHBIgetStatus(void)
{
    return (rHBI.status);
}

/*******************************************************************
*																   
*  NAME:        mHBIsetStatus    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_8 bits
*
*  DESCRIPTION: HAL function to set the bits in HBI block status    
*               register marked by the 'bits' parameter (The
*               'bits' parameter is OR'd into the HBI status
*               register).
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetStatus(mUINT_8 bits)
{
    rHBI.status |= bits;
}

/*******************************************************************
*																   
*  NAME:        mHBIclrStatus    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_8 bits
*
*  DESCRIPTION: HAL function to clear the bits in HBI block status    
*               register marked by the 'bits' parameter (The negated
*               'bits' parameter is AND'd into the HBI status
*               register).
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIclrStatus(mUINT_8 bits)
{
    rHBI.status &= ~(bits);
}

/*******************************************************************
*																   
*  NAME:        mHBIinitStatus    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_8 bits
*
*  DESCRIPTION: HAL function to load the HBI block status register 
*               with the contents of the 'bits' parameter.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIinitStatus(mUINT_8 bits)
{
    rHBI.status = bits;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetAltAtStatus    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_8 bits
*
*  DESCRIPTION: HAL function to load the HBI block status register 
*               with the contents of the 'bits' parameter.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetAltAtStatus(mUINT_8 bits)
{
    rHBI.altStatus = bits;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetBlkXferCnt    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_8 numberOfSectors
*
*  DESCRIPTION: HAL function to load the host block transfer count  
*               register with the contents of the 'numberOfSectors' 
*               parameter.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetBlkXferCnt (mUINT_16 numberOfSectors)
{
    rHBI.hostBlkXferCnt1_0 = numberOfSectors;  // since ACE is disabled.
}

/*******************************************************************
*																   
*  NAME:        mHBIgetBlkXferCnt    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to get the host block transfer count  
*
*  RETURNS:     host block transfer count
*
********************************************************************/
__inline mUINT_16 mHBIgetBlkXferCnt (void)
{
    mUINT_16    sample0, sample1;

    sample0 = rHBI.hostBlkXferCnt1_0;
    for ( ; ; )
    {
        sample1 = rHBI.hostBlkXferCnt1_0;
        if ( sample0 == sample1 )
            break;
        else
            sample0 = sample1;
    }

    return (sample0);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetAtStatus    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to return the contents of the HBI   
*               status register.
*
*  RETURNS:     type UNIT_8 AT status register
*
********************************************************************/
__inline mUINT_8 mHBIgetAtStatus (void)
{
    return (rHBI.status); 
}

/*******************************************************************
*																   
*  NAME:        mHBIgetAtCmd    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to return the contents of the HBI   
*               cmd register.
*
*  RETURNS:     type UNIT_8 AT Cmd register
*
********************************************************************/
__inline mUINT_8 mHBIgetAtCmd (void)
{
    return (rHBI.cmnd); 
}


/*******************************************************************
*																   
*  NAME:        mHBIsetMultipleFisSize    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_8 sectorsPerBlk
*
*  DESCRIPTION: HAL function to load the host block size register   
*               with the contents of the 'SectorsPerBlk' parameter. 
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetMultipleFisSize(mINT_16 sectorsPerBlk)
{
    rHBI.MdataFisSize = sectorsPerBlk * mDWORDS_PER_SECTOR;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetMultipleBlkSize    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_8 sectorsPerBlk
*
*  DESCRIPTION: HAL function to load the host block size register   
*               with the contents of the 'SectorsPerBlk' parameter. 
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetMultipleBlkSize(mINT_16 sectorsPerBlk)
{
    rHBI.hostBlkSize = sectorsPerBlk;
}

/*******************************************************************
*																   
*  NAME:        mHBIgetMultipleBlkSize    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to get the host block size    
*
*  RETURNS:     host block size
*
********************************************************************/
__inline mUINT_16 mHBIgetMultipleBlkSize(void)
{
    return rHBI.hostBlkSize;
}

/*******************************************************************
*																   
*  NAME:        mHBIgetHostIntrStatus    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to return the contents of the host 
*               interrupt status register   
*
*  RETURNS:     type mUINT_16 host interrupt status
*
********************************************************************/
__inline mUINT_16 mHBIgetHostIntrStatus (void)
{
    return (rHBI.hostIntStat0.all);
}


/*******************************************************************
*																   
*  NAME:        mHBIclrIntrStatus    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 bits
*
*  DESCRIPTION: HAL function to load the host interrupt status register   
*               with the contents of the 'bits' parameter. 
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIclrIntrStatus (mUINT_16 bits) 
{
    rHBI.hostIntStat0.all = bits;
}

/*******************************************************************
*																   
*  NAME:        mHBIgetIntrDisable    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to return the contents of the host 
*               interrupt mask register   
*
*  RETURNS:     type mUINT_16 host interrupt mask value
*
********************************************************************/
__inline mUINT_16 mHBIgetIntrDisable (void)
{
    return rHBI.hostIntMask.all;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetBitAtMode    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to set the bits in the AT Mode    
*               register marked by the 'bits' parameter (The
*               'bits' parameter is OR'd into the AT Mode
*               register).
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetBitAtMode (mUINT_16 bits)
{
    rHBI.ATmode0.all |= bits;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetBitFdmaActivateDis
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  none
*
*  DESCRIPTION: HBI function to set/clear the First Dma Auto-Activate FIS 
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetFdmaActivateDis(mtBOOLEAN val)
{
    rHBI.eSataConfig.bits.fDMAactivateDis = val;
}

__inline void mHBIsetQcmdAbort()
{
    rHBI.ATdevConfgCntrl.bits.qAbort = 1;
}

__inline void mHBIsetBitATdevConfgCntrl (mUINT_16 bits)
{
    rHBI.ATdevConfgCntrl.all |= bits;
}
__inline void mHBIclrBitATdevConfgCntrl (mUINT_16 bits)
{
    rHBI.ATdevConfgCntrl.all &= ~bits;
}

__inline void mHBIclrTmStatusLow (mUINT_16 bits) 
{
    rHBI.tmStatusLow.all = bits;
}

__inline mUINT_16 mHBIgetTmStatusLow() 
{
    return (rHBI.tmStatusLow.all);
}

__inline mUINT_16 mHBIgetTmStatusHi() 
{
    return (rHBI.tmStatusHi.all);
}

__inline mUINT_16 mHBIgetCmdTagId(void)
{
    return (rHBI.crsbData.bits.cmdTag);
}

__inline void mHBIclrTmStatusHi (mUINT_16 bits) 
{
    rHBI.tmStatusHi.all = bits;
}

__inline void mHBIsetBitMiscStatus (mUINT_16 bits)
{
    rHBI.hostMiscStatus.all |= bits;
}

__inline void mHBIclrBitMiscStatus (mUINT_16 bits)
{
    rHBI.hostMiscStatus.all &= ~bits;
}

__inline void mHBIsetBitAceConfg1 (mUINT_16 bits)
{
    rHBI.aceConfig1.all |= bits;
}

__inline void mHBIsetBitAceConfg2 (mUINT_16 bits)
{
    rHBI.aceConfig2.all |= bits;
}

__inline void mHBIsetBitAutoStatusConfg (mUINT_16 bits)
{
    rHBI.autoStatusConfig.all |= bits;
}

__inline void mHBIsetBitOverrideCntl (mUINT_16 bits)
{
    rHBI.overrideCntl.all |= bits;
}

__inline void mHBIresetCmdxh (void)
{
    rHBI.crhsCntl.all = 0xc0;             // R4AFC
    rHBI.crhsCntl.all = 0;                     
}

__inline void mHBIresetCrsb (void)
{
    rHBI.crsbCntlStat.all = 0xc000;        // R4AF8
    rHBI.crsbCntlStat.all = 0;
}

__inline void mHBIsetBitMsgLogConfg (mUINT_16 bits)
{
    rHBI.msgLogConfig.all |= bits;         // R4A60
}

__inline void mHBIsetMsgLogCntl (mUINT_16 val)
{
    rHBI.xmlogsbCntlStat.all = val;       // R4B4A
}

__inline void mHBIsetBitMsgLogCntl (mUINT_16 bits)
{
    rHBI.xmlogsbCntlStat.all |= bits;       // R4B4A
}

__inline void mHBIsetBitCxsbCntl (mUINT_16 bits)
{
    rHBI.cxsbCntlStat.all |= bits;       // R4B02
}

__inline void mHBIclrBitCxsbCntl (mUINT_16 bits)
{
    rHBI.cxsbCntlStat.all &= ~bits;       // R4B02
}


__inline mUINT_16 mHBIgetCxsbCntl (void)
{
    return (rHBI.cxsbCntlStat.all);       // R4B02
}


__inline mUINT_16  mHBIgetMsgLogCntl (void)
{
    return (rHBI.xmlogsbCntlStat.all);
}

__inline void mHBIresetFlowCntl (void)
{
    rHBI.eSataFlowPwrRstCntl.all = 0x1e01;        // R4AF8[12,11,10,9,0]
    rHBI.eSataFlowPwrRstCntl.all = 0;
}

__inline void mHBIsetFwStatus(mUINT_8 bits)
{
    rHBI.altStatus = bits;
    //*(volatile mUINT_16 *)0x1C004A02 = ((mUINT_8)(rHBI.altError) << 8 | bits);
}

__inline mUINT_16 mHBIgetXMLOGSBCnt(void)
{
    mUINT_16    sample0, sample1;

    sample0 = rHBI.xmlogsbCntlStat.bits.count;
    // to debounce
    for ( ; ; )
    {
        sample1 = rHBI.xmlogsbCntlStat.bits.count;
        if ( sample0 == sample1 )
            break;
        else
            sample0 = sample1;
    }
    return (sample0);
}

__inline void mHBIclrXMLOGSBCnt(void)
{
    rHBI.xmlogsbCntlStat.bits.reset = 1;  // self clear in Rev 1
    rHBI.xmlogsbCntlStat.bits.reset = 0;  // not self clear in Rev 2
}

__inline mUINT_16 mHBIgetXMLOGSBData(void)
{
    return (rHBI.xmlogsbData.all);
}

__inline mUINT_16 mHBIgetTmPhase(void)
{
    return (rHBI.tmPhase.all);
}

__inline mUINT_8 mHBIgetFwError(void)
{
    return (rHBI.altError);
}

__inline mUINT_8 mHBIgetFwStatus(void)
{
    return (rHBI.altStatus);
}

__inline void mHBIsetCxsbFwReqEoc(void)
{
    rHBI.hostIntStat0.all = m_tHBI_INT_bits_fwXferDone;
    rHBI.cxsbFwReq1.all = 0x1;
    rHBI.cxsbFwReq0.all = m_tHBI_CXSB_FWREQ_EOC | m_tHBI_CXSB_FW_REQ0_bits_nonQcmd;
}

__inline void mHBIsetCxsbFwReqNonQDataXfer(mUINT_16 hostSectors, mUINT_16 bSeg, mtBOOLEAN writeOp, mtBOOLEAN autoStatusForWrite)
{
    rHBI.hostIntStat0.all = m_tHBI_INT_bits_fwXferDone;
    if( writeOp)
    {
        rHBI.cxsbFwReq1.all = hostSectors;
        if (autoStatusForWrite)
        {
            // autostatus=1, SegmentSelect=Bseg, ReqType=0001 (dataXfer), Nonq = 1, exe_tag = 0
            rHBI.cxsbFwReq0.all = m_tHBI_CXSB_FW_REQ0_bits_fwReqEocEn | (bSeg << 12) | m_tHBI_CXSB_FWREQ_DATAXFER | m_tHBI_CXSB_FW_REQ0_bits_nonQcmd;
        }
        else
        {
            // autostatus=0,SegmentSelect=Bseg, ReqType=0001 (dataXfer), Nonq = 1, exe_tag = 0
            rHBI.cxsbFwReq0.all = (bSeg << 12) | m_tHBI_CXSB_FWREQ_DATAXFER | m_tHBI_CXSB_FW_REQ0_bits_nonQcmd;
        }
    }
    else // Read has auto status
    {
        rHBI.cxsbFwReq1.all = hostSectors;
		if (autoStatusForWrite)
		{
          rHBI.cxsbFwReq0.all = m_tHBI_CXSB_FW_REQ0_bits_fwReqEocEn | (bSeg << 12) | m_tHBI_CXSB_FWREQ_DATAXFER | m_tHBI_CXSB_FW_REQ0_bits_nonQcmd;
		}
		else
		{
          rHBI.cxsbFwReq0.all = (bSeg << 12) | m_tHBI_CXSB_FWREQ_DATAXFER | m_tHBI_CXSB_FW_REQ0_bits_nonQcmd;
		}
    }
}

__inline void mHBIsetCxsbFwReqSDBFisSend(mUINT_16 qSlot)
{
    rHBI.hostIntStat0.all = m_tHBI_INT_bits_fwXferDone | m_tHBI_INT_bits_msgLogDet;
    rHBI.cxsbFwReq1.all = 0x1;
//    rHBI.cxsbFwReq0.all = m_tHBI_CXSB_FW_REQ0_bits_fwReqEocEn | m_tHBI_CXSB_FWREQ_EOC | m_tHBI_CXSB_FW_REQ0_bits_logXferDoneMsgEn | qSlot;
    rHBI.cxsbFwReq0.all = m_tHBI_CXSB_FW_REQ0_bits_fwReqEocEn | m_tHBI_CXSB_FWREQ_EOC | qSlot;
}

__inline void mHBIsetCxsbFwReqSDBAggresatedFisSend(void)
{
    rHBI.hostIntStat0.all = m_tHBI_INT_bits_fwXferDone | m_tHBI_INT_bits_msgLogDet;
    rHBI.cxsbFwReq1.all = 0x1;
//    rHBI.cxsbFwReq0.all = m_tHBI_CXSB_FWREQ_AGEOC | m_tHBI_CXSB_FW_REQ0_bits_logXferDoneMsgEn;
    rHBI.cxsbFwReq0.all = m_tHBI_CXSB_FWREQ_AGEOC;
}

__inline void mHBIsetCxsbFwReqQcmdDataXfer(mUINT_16 hostSectors, mUINT_16 bSeg, mtBOOLEAN writeOp, mUINT_16 qSlot, mtBOOLEAN autoStatusForWrite)
{
    #if (DMA_SETUP_FIS_AUTO_ACTIVATE == mENABLE)
    mUINT_16 savedIntrMask;
    #endif

    rHBI.hostIntStat0.all = m_tHBI_INT_bits_fwXferDone;
    if (writeOp)
    {
       #if (DMA_SETUP_FIS_AUTO_ACTIVATE == mENABLE)
            // apply work around for FirstDMAActivate Disable
            if (rHBI.eSataConfig.bits.fDMAactivateDis)
            {
                savedIntrMask = rHBI.hostIntMask.all;
                rHBI.hostIntMask.all = 0xFFFF;           // mask all interrupt
                rHBI.aceConfig2.bits.wrDmaEn = 1;
            }
       #endif

        rHBI.cxsbFwReq1.all = hostSectors;
        if (autoStatusForWrite)
        {
//            rHBI.cxsbFwReq0.all = m_tHBI_CXSB_FW_REQ0_bits_fwReqEocEn | (bSeg << 12) | m_tHBI_CXSB_FWREQ_DATAXFER | m_tHBI_CXSB_FW_REQ0_bits_logXferDoneMsgEn | qSlot;;
            rHBI.cxsbFwReq0.all = m_tHBI_CXSB_FW_REQ0_bits_fwReqEocEn | (bSeg << 12) | m_tHBI_CXSB_FWREQ_DATAXFER | qSlot;;
        }
        else
        {
//            rHBI.cxsbFwReq0.all = (bSeg << 12) | m_tHBI_CXSB_FWREQ_DATAXFER | m_tHBI_CXSB_FW_REQ0_bits_logXferDoneMsgEn | qSlot;
            rHBI.cxsbFwReq0.all = (bSeg << 12) | m_tHBI_CXSB_FWREQ_DATAXFER | qSlot;
        }
       #if (DMA_SETUP_FIS_AUTO_ACTIVATE == mENABLE)
            // apply work around for FirstDMAActivate Disable
            if (rHBI.eSataConfig.bits.fDMAactivateDis)
            {
                while (!rHBI.hostMiscStatus.bits.xferActive);
                {
                    rHBI.aceConfig2.bits.wrDmaEn = 0;
                    rHBI.hostIntMask.all = savedIntrMask;           // restore mask 
                }
            }
       #endif

    
    }
    else // Read has auto status
    {
        rHBI.cxsbFwReq1.all = hostSectors;
//        rHBI.cxsbFwReq0.all = m_tHBI_CXSB_FW_REQ0_bits_fwReqEocEn | (bSeg << 12) | m_tHBI_CXSB_FWREQ_DATAXFER | m_tHBI_CXSB_FW_REQ0_bits_logXferDoneMsgEn | qSlot;
      	if (autoStatusForWrite)
      	{
          rHBI.cxsbFwReq0.all = m_tHBI_CXSB_FW_REQ0_bits_fwReqEocEn | (bSeg << 12) | m_tHBI_CXSB_FWREQ_DATAXFER | qSlot;
      	}
		else
		{
		  rHBI.cxsbFwReq0.all = (bSeg << 12) | m_tHBI_CXSB_FWREQ_DATAXFER | qSlot;
		}
    }
}

__inline mtBOOLEAN mHBIisNonQcmd(void)
{
    return (rHBI.crsbData.bits.nonQflg);
}

__inline void mHBIcrsbCmdResume(mUINT_16 bits)
{
    rHBI.crsbCntlStat.all |= bits;
    rHBI.crsbCntlStat.all = 0;
}

__inline mUINT_16 mHBIgetBmSectorsXfer(void)
{
    return (rHBI.bufBlkXferCnt);
}


/*******************************************************************
*																   
*  NAME:        mHBIclrBitAtMode    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_8 bits
*
*  DESCRIPTION: HAL function to clear the bits in the AT Mode    
*               register marked by the 'bits' parameter (The negated
*               'bits' parameter is AND'd into the AT Mode
*               register).
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIclrBitAtMode (mUINT_16 bits)
{
    rHBI.ATmode0.all &= ~bits;
}

__inline void mHBIdisAutoPIOsecMode (void)
{
    rHBI.aceConfig2.bits.wrPioEn = 0;
}
__inline void mHBIenableAutoPIOsecMode (void)
{
    rHBI.aceConfig2.bits.wrPioEn = 1;
}

/*******************************************************************
*                                                                  
*  NAME:        mHBIgetConfgCntrl
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to get the value of Host Confg Cntrl Reg.
*
*  RETURNS:     None
*
*  DATE          BY              DESCRIPTION 
********************************************************************/
__inline mUINT_16 mHBIgetConfgCntrl (void)
{
    return  rHBI.ATdevConfgCntrl.all;
}

/*******************************************************************
*                                                                  
*  NAME:        mHBIgetAtMode
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to return AT Mode 0 value.
*
*  RETURNS:     None
*               
*  DATE         BY              DESCRIPTION 
********************************************************************/
__inline mUINT_16 mHBIgetAtMode (void)
{
    return rHBI.ATmode0.all ;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetSeqRdLbaMode    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to set sequential read LBA mode 
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetSeqRdLbaMode(void)  
{
    rHBI.seqDevHead = 0x40;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetSeqWrLbaMode    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to set sequential write LBA mode 
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetSeqWrLbaMode(void)  
{
    rHBI.aceConfig2.bits.wrSeqLbaMode = mTRUE;
}

/*******************************************************************
*																   
*  NAME:        mHBIgetDeviceControl    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None.
*
*  DESCRIPTION: HAL function to return content of device control register.
*
*  RETURNS:     content of device control register.
*
********************************************************************/
__inline mUINT_16 mHBIgetDeviceControl(void)
{
    return (rHBI.devCntrl.all);
}

/*******************************************************************
*                                                                  
*  NAME:        mHBIgetMiscStatus
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to get the value of Host Misc Status
*
*  RETURNS:     None
*
*  DATE          BY              DESCRIPTION 
********************************************************************/
__inline mUINT_16 mHBIgetMiscStatus (void)
{
    return  rHBI.hostMiscStatus.all;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetAltAtError    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_8 bits
*
*  DESCRIPTION: HAl function to set the bits in HBI block error    
*               register marked by the 'bits' parameter. 
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetAltAtError(mUINT_8 bits)
{
    rHBI.altError = bits;
}

/*******************************************************************
*																   
*  NAME:        mHBISetBitESATAconfig
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HBI function to load the ESATA configuration 
*               register with the contents of the 'val' parameter.    
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBISetBitESATAconfig(mUINT_16 bits) 
{
    rHBI.eSataConfig.all |= bits;
}

/*******************************************************************
*																   
*  NAME:        mHBIClrBitESATAconfig
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HBI function to load the ESATA configuration 
*               register with the contents of the 'val' parameter.    
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIClrBitESATAconfig(mUINT_16 bits) 
{
    rHBI.eSataConfig.all &= ~(bits);
}


/*******************************************************************
*																   
*  NAME:        mHBIsetFISsize
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to load the HBI FIS size register
*               with the contents of the 'val' parameter.    
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetFISsize(mUINT_16 val)  
{
    rHBI.FISsize = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIgetFISsize
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to load the HBI FIS size register
*               with the contents of the 'val' parameter.    
*
*  RETURNS:     None
*
********************************************************************/
__inline mUINT_16 mHBIgetFisSize(void)  
{
    return (rHBI.FISsize);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetMultipleFisSize    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_8 sectorsPerBlk
*
*  DESCRIPTION: HAL function to load the host block size register   
*               with the contents of the 'SectorsPerBlk' parameter. 
*
*  RETURNS:     None
*
********************************************************************/
__inline mUINT_16 mHBIgetMultipleFisSize(void)
{
    return (rHBI.MdataFisSize);
}


/*******************************************************************
*																   
*  NAME:        mHBIsetTMforceRerr
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to send R_err to host
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetTMforceRerr(void)
{
    // first clear tmRxFistype
    rHBI.tmRxFISTypeLog.all = 0;
    rHBI.tmRxFISTypeLog.bits.RxForceRErr = 1;
}

/*******************************************************************
*																   
*  NAME:        mHBIgetRxFIStype
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to return the contents of the HBI 
*               transport manager Rx Fis Type
*
*  RETURNS:     None
*
********************************************************************/
__inline mUINT_16 mHBIgetRxFIStype()
{
    return (rHBI.tmRxFISTypeLog.bits.RxFisType);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetTxFIStype
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to return the contents of the HBI 
*               transport manager Tx Fis Type
*
*  RETURNS:     None
*
********************************************************************/
__inline mUINT_16 mHBIgetTxFIStype()
{
    return (rHBI.tmTxFISTypeLog.bits.TxFisType);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetRxFIStypeErrLog
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to return the contents of the HBI 
*               transport manager Rx Fis Type Error Log
*
*  RETURNS:     None
*
********************************************************************/
__inline mUINT_16 mHBIgetRxFisTypeErrLog()
{
    // RxFisTypeErrLog is available only for Zuma and over
    // This error log register is cleared when fw reads.
      return (rHBI.tmRxFISTypeErrLog.bits.errRxFisType);
}
/*******************************************************************
*																   
*  NAME:        mHBIgetTxFIStypeErrLog
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to return the contents of the HBI 
*               transport manager Rx Fis Type Error Log
*
*  RETURNS:     None
*
********************************************************************/
__inline mUINT_16 mHBIgetTxFisTypeErrLog()
{
    // TxFisTypeErrLog is available only for Zuma and over
    // This error log register is cleared when fw reads.
      return (rHBI.tmTxFISTypeErrLog.bits.errTxFisType);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetTMflowtIntrStatus    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  none
*
*  DESCRIPTION: HAL function to return the contents of the HBI 
*               transport manager flow interrupt status
*
*  RETURNS:     type mUINT_16 host interrupt status
*
********************************************************************/
__inline mUINT_16 mHBIgetTMflowIntrStatus () 
{
     return (rHBI.tmFlowIntStatus.all);
}

/*******************************************************************
*																   
*  NAME:        mHBIclrTMflowtIntrStatus    												   
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type UNIT_16
*
*  DESCRIPTION: HAL function to clear the contents of the HBI 
*               transport manager flow interrupt status
*
*  RETURNS:     type mUINT_16 host interrupt status
*
********************************************************************/
__inline void mHBIclrTMflowIntrStatus (mUINT_16 val) 
{
    rHBI.tmFlowIntStatus.all = val;
}

/*******************************************************************
*																   
*  NAME:        mHBISataErrStatus
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type UINT_16
*
*  DESCRIPTION: HAL function to clear the contents of the HBI 
*               ESATA Errror Interrupt Status
*
*  RETURNS:     none
*
********************************************************************/
__inline void mHBIclrEsataErrIntrStatus (mUINT_16 val) 
{
    rHBI.eSataErrIntStat.all = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIinitPhyTunningControl
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: API function to set phy tunning control
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIinitPhyTunningControl(mUINT_16 val)  
{
}


/*******************************************************************
*																   
*  NAME:        mHBIsetEsataErrIntrMsk
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to set FIS size
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetEsataErrIntrSrc(mUINT_16 val)
{
    rHBI.eSataErrIntMsk.all = ~(val);
}

__inline mUINT_16 mHBIgetEsataErrIntrSrc(void)
{
    return rHBI.eSataErrIntMsk.all;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetTMflowIntrMsk
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to set FIS size
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetTMflowIntrSrc(mUINT_16 val)
{
    rHBI.tmFlowIntMsk.all = ~(val);
}

__inline mUINT_16 mHBIgetTMflowIntrSrc(void)
{
    return rHBI.tmFlowIntMsk.all;
}

/*******************************************************************
*																   
*  NAME:        mHBISetTMfifoThreshold
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set TM fifo Threshold
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBISetTMfifoThreshold(mUINT_16 val)
{
    rHBI.tmFIFOthreshold.bits.tmFifoThresh |= val;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetSectorCount
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set sector count
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetSectorCount(mUINT_16 val)
{
    rHBI.sectorCnt = val;
}



/*******************************************************************
*																   
*  NAME:        mHBIsetUserFISword0L
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set user defined FIS word 0 Low
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetUserFISword0L(mUINT_16 val)
{
    rHBI.uRegFIS0L = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetUserFISword0H
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set user defined FIS word 0 high
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetUserFISword0H(mUINT_16 val)
{
    rHBI.uRegFIS0H = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetUserFISword1L
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set user defined FIS word 1 Low
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetUserFISword1L(mUINT_16 val)
{
    rHBI.uRegFIS1L = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetUserFISword1H
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set user defined FIS word 1 high
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetUserFISword1H(mUINT_16 val)
{
    rHBI.uRegFIS1H = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetUserFISword2L
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set user defined FIS word 2 Low
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetUserFISword2L(mUINT_16 val)
{
    rHBI.uRegFIS2L = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetUserFISword2H
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set user defined FIS word 2 high
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetUserFISword2H(mUINT_16 val)
{
    rHBI.uRegFIS2H = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetUserFISword3L
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set user defined FIS word 3 Low
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetUserFISword3L(mUINT_16 val)
{
    rHBI.uRegFIS3L = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetUserFISword3H
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set user defined FIS word 3 high
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetUserFISword3H(mUINT_16 val)
{
    rHBI.uRegFIS3H = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetUserFISword4L
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set user defined FIS word 4 Low
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetUserFISword4L(mUINT_16 val)
{
    rHBI.uRegFIS4L = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetUserFISword4H
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set user defined FIS word 4 high
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetUserFISword4H(mUINT_16 val)
{
    rHBI.uRegFIS4H = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetManualFlowControl
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set user defined FIS word 4 high
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetManualFlowControl(mUINT_16 val)
{
    rHBI.tmManualCntl.all = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetSectorNum
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set register Sylinder low / sector number
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetSectorNum(mUINT_16 val)
{
    rHBI.sectorNum = val;
}

/*******************************************************************
*																   
*  NAME:        mHBIgetFlowPowerResetCntl
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: to set register ESATA flow power / reset control
*
*  RETURNS:     None
*
********************************************************************/
__inline mUINT_16 mHBIgetESATAflowPowerResetCntl(void)
{
    return(rHBI.eSataFlowPwrRstCntl.all);
}

/*******************************************************************
*																   
*  NAME:        mHBIGetSectorNum
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  non
*
*  DESCRIPTION: to get sector number from task file register
*
*  RETURNS:     sector number in task file register
*
********************************************************************/
__inline mUINT_16 mHBIGetSectorNum(void)
{
    return(rHBI.sectorNum);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetEsataErrIntStatus
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  non
*
*  DESCRIPTION: to get ESATA error interrupt status
*
*  RETURNS:     ESATA error interrupt status
*
********************************************************************/
__inline mUINT_16 mHBIgetEsataErrIntStatus(void)
{
    return(rHBI.eSataErrIntStat.all);
}

/*******************************************************************
*																   
*  NAME:        mHBIGetUserFISword1L
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  non
*
*  DESCRIPTION: to get user defined FIS word 1 low
*
*  RETURNS:     user defined FIS word 1 low
*
********************************************************************/
__inline mUINT_16 mHBIGetUserFISword1L(void)
{
    return(rHBI.uRegFIS1L);
}

/*******************************************************************
*																   
*  NAME:        mHBIGetESATAConfig
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  non
*
*  DESCRIPTION: to get contents from register ESATA configuration
*
*  RETURNS:     ESATA configuration
*
********************************************************************/
__inline mUINT_16 mHBIGetESATAConfig(void)
{
    return(rHBI.eSataConfig.all);
}

/*******************************************************************
*																   
*  NAME:        mHBIsetQcmdCntl
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16 val
*
*  DESCRIPTION: load the Q command control register with the parameter val
*
*  RETURNS:     none
*
********************************************************************/


/*******************************************************************
*																   
*  NAME:        mHBIsetQcmdCntrl
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_16 val
*
*  DESCRIPTION: load the Q command control register with the parameter val
*
*  RETURNS:     none
*
********************************************************************/
__inline void mHBIclrQcmdCntrl(mUINT_16 val)
{
}


/*******************************************************************
*																   
*  NAME:        mHBIclrQcmdIntr
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to clear Q command interrupt, write 1
*               to the bit will clear the specific interrupt status
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIclrQcmdIntr(mUINT_16 val)
{
}

/*******************************************************************
*																   
*  NAME:        mHBIgetQcmdIntrStatus
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to get Q command interrupt status
*
*  RETURNS:     Q command interrupt status
*
********************************************************************/
__inline mUINT_16 mHBIgetQcmdIntrStatus(void)
{
    return(0); // Kim - need to revisit     
}

/*******************************************************************
*																   
*  NAME:        mHBIgetQslotBsy
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to get Queue Busy slot
*
*  RETURNS:     busy slots
*
********************************************************************/
__inline mUINT_32 mHBIgetQslotBsy(void)
{
    return(rHBI.qCmdBsyStatHi | (rHBI.qCmdBsyStatLo <<16));      
}





/*******************************************************************
*																   
*  NAME:        mHBIgetQhead
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to get next Q tail offset
*
*  RETURNS:     start Q head offset
*
********************************************************************/
__inline mUINT_8 mHBIgetQhead(void)
{
    return(0);   
}

/*******************************************************************
*																   
*  NAME:        mHBIsetQhead
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to get next Q tail offset
*
*  RETURNS:     start Q head offset
*
********************************************************************/
// This API writes to Q Head Offset register to start host to tx data content
// specified by a q cmd (of the qSlotNum).
__inline void mHBIsetQhead(mUINT_NATIVE qSlotNum)
{
}



/*******************************************************************
*																   
*  NAME:        mHBIgetLBAfromQslot
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  Qslot 
*
*  DESCRIPTION: API function to get LBA from Qram
*
*  RETURNS:     start Q head offset
*
********************************************************************/
__inline mUINT_32 mHBIgetLBAfromQslot(mUINT_8 val)
{
    return (rHBI.QRAMstruct[val].LBA0_31);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetNextQslot
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  none 
*
*  DESCRIPTION: API function to get LBA from Qram
*
*  RETURNS:     start Q head offset
*
********************************************************************/
__inline mUINT_8 mHBIgetNextQslot(mUINT_8 val)
{
    return(0); 
}

/*******************************************************************
*																   
*  NAME:        mHBIsetQramNextQslot
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  val-Qslot number, valNext-the next Q slot number 
*
*  DESCRIPTION: API function to set the nextQ field in the Qslot
*
*  RETURNS:     none
*
********************************************************************/
__inline void mHBIsetQramNextQslot(mUINT_8 val,mUINT_8 valNext)
{
}

/*******************************************************************
*																   
*  NAME:        mHBIgetNewQCmd
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  void 
*
*  DESCRIPTION: API function to get command code from the last Q slot
*
*  RETURNS:     none
*
********************************************************************/
__inline mUINT_8 mHBIgetNewQCmd(void)
{
    return(0);
}

/*******************************************************************
*																   
*  NAME:        mHBIlockQram
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  void 
*
*  DESCRIPTION: API function to lock Qram, and confirm that it is locked
*
*  RETURNS:     none
*
********************************************************************/
__inline void mHBIlockQram(void)
{
}

/*******************************************************************
*																   
*  NAME:        mHBIfreeQram
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  void 
*
*  DESCRIPTION: API function to free Qram
*
*  RETURNS:     none
*
********************************************************************/
__inline void mHBIfreeQram(void)
{
}


/*******************************************************************
*																   
*  NAME:        mHBIsetSActiveReg
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  value for SActive Low and Hight registers 
*
*  DESCRIPTION: set value for SActive Low and Hight registers
*
*  RETURNS:     none
*
********************************************************************/
__inline void mHBIsetSActiveReg(mUINT_16 sactiveLo,mUINT_16 sactiveHi)
{
    rHBI.qActiveLo = sactiveLo;
    rHBI.qActiveHi = sactiveHi;
}



/*******************************************************************
*																   
*  NAME:        mHBIgetBISTpattern
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  none
*
*  DESCRIPTION: HAL function to get data from BIST pattern reg
*
*  RETURNS:     mUINT_16  
*
********************************************************************/
__inline mUINT_16 mHBIgetBISTpattern (void) 
{
    return(rHBI.bistPat);  
}

/*******************************************************************
*																   
*  NAME:        mHBIgetBISTW1L
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  none
*
*  DESCRIPTION: HAL function to get data from BIST word1_Low reg
*
*  RETURNS:     mUINT_16  
*
********************************************************************/
__inline mUINT_16 mHBIgetBISTW1L (void) 
{
    return(rHBI.bistWord1Lo);  
}

/*******************************************************************
*																   
*  NAME:        mHBIgetBISTW1H
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  none
*
*  DESCRIPTION: HAL function to get data from BIST word1_High reg
*
*  RETURNS:     mUINT_16  
*
********************************************************************/
__inline mUINT_16 mHBIgetBISTW1H (void) 
{
    return(rHBI.bistWord1Hi);  
}


/*******************************************************************
*																   
*  NAME:        mHBIgetBISTW2L
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  none
*
*  DESCRIPTION: HAL function to get data from BIST word2_Low reg
*
*  RETURNS:     mUINT_16  
*
********************************************************************/
__inline mUINT_16 mHBIgetBISTW2L (void) 
{
    return(rHBI.bistWord2Lo);  
}

/*******************************************************************
*																   
*  NAME:        mHBIgetBISTW2H
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  none
*
*  DESCRIPTION: HAL function to get data from BIST word2_High reg
*
*  RETURNS:     mUINT_16  
*
********************************************************************/
__inline mUINT_16 mHBIgetBISTW2H (void) 
{
    return(rHBI.bistWord2Hi);  
}

/*******************************************************************
*																   
*  NAME:        mHBIsetESATAflowPwrRstCntl
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to set the bits contained in the parameter 
*               "val" in ESATA Flow Power Reset Control    
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetESATAflowPwrRstCntl(mUINT_16 bits) 
{
    rHBI.eSataFlowPwrRstCntl.all |= bits;
}

/*******************************************************************
*																   
*  NAME:        mHBIclrESATAflowPwrRstCntl
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to clear the bits contained in the parameter 
*               "val" in ESATA Flow Power Reset Control     
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIclrESATAflowPwrRstCntl(mUINT_16 bits) 
{
    rHBI.eSataFlowPwrRstCntl.all &= ~(bits);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetSectorCntfromQslot
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  Qslot number
*
*  DESCRIPTION: API function to get sector count from Qram
*
*  RETURNS:     start Q head offset
*
********************************************************************/
__inline mUINT_16 mHBIgetSectorCntfromQslot(mUINT_32 val)
{
    return (rHBI.QRAMstruct[val].feature0_15);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetCmdfromQslot
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  Qslot number
*
*  DESCRIPTION: API function to get command from Qram
*
*  RETURNS:     the command 
*
********************************************************************/
__inline mUINT_8 mHBIgetCmdfromQslot(mUINT_32 val)
{
    return (rHBI.QRAMstruct[val].cmd);
}


/*******************************************************************
*																   
*  NAME:        mHBIgetDevHdfromQslot
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  Qslot number
*
*  DESCRIPTION: API function to get device/head from Qram
*
*  RETURNS:     start Q head offset
*
********************************************************************/
__inline mUINT_8 mHBIgetDevHdfromQslot(mUINT_32 val)
{
    return (rHBI.QRAMstruct[val].device_head);
}
 
/*******************************************************************
*																   
*  NAME:        mHBIgetFeaturesfromQslot
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  Qslot number
*
*  DESCRIPTION: API function to get features from Qram
*
*  RETURNS:     start Q head offset
*
********************************************************************/
__inline mUINT_16 mHBIgetFeaturesfromQslot(mUINT_32 val)
{
    return (rHBI.QRAMstruct[val].feature0_15);
         
}

/*******************************************************************
*																   
*  NAME:        mHBIsetQRAMbSeg
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_NATIVE qSlotNum
*               mUINT_NATIVE segNum
*
*  DESCRIPTION: API function to assign bufger segment number for this q cmd.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetQRAMbSeg(mUINT_NATIVE qSlotNum, mUINT_NATIVE segNum)
{
}

/*******************************************************************
*																   
*  NAME:        mHBIsetQRAMxferByteCount
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_NATIVE qSlotNum
*               mUINT_NATIVE hostSectors
*
*  DESCRIPTION: API function to init the bytecount of transfer for this q cmd.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetQRAMxferByteCount(mUINT_NATIVE qSlotNum, mUINT_NATIVE hostSectors)
{
}


/*******************************************************************
*																   
*  NAME:        mHBIsetQRAMbufOffset
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_NATIVE qSlotNum
*               mUINT_NATIVE bufOffset
*
*  DESCRIPTION: API function to set the buffer offset of transfer for this q cmd.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetQRAMbufOffset(mUINT_NATIVE qSlotNum, mUINT_NATIVE bufOffset)
{
    rHBI.QRAMstruct[qSlotNum].bufOffset = bufOffset; 
}

/*******************************************************************
*																   
*  NAME:        mHBIsetQRAMbitX
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_NATIVE qSlotNum
*
*  DESCRIPTION: API function to set the X bit of a qslot to mark this q cmd is active now.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetQRAMbitX(mUINT_NATIVE qSlotNum)
{
    rHBI.QRAMstruct[qSlotNum].controlbits.bits.X = 1;
}
/*******************************************************************
*																   
*  NAME:        mHBIclrQRAMbitX
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_NATIVE qSlotNum
*
*  DESCRIPTION: API function to clear the X bit of a qslot to mark this q cmd is active now.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIclrQRAMbitX(mUINT_NATIVE qSlotNum)
{
    rHBI.QRAMstruct[qSlotNum].controlbits.bits.X = 0;
}

/*******************************************************************
*																   
*  NAME:        mHBIgetQRAMbitX
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to read X-bit status of a Queue Command slot.
*
*  RETURNS:     X-bit status.
*
********************************************************************/
__inline mUINT_NATIVE mHBIgetQRAMbitX(mUINT_NATIVE qSlotNum)
{
    return (rHBI.QRAMstruct[qSlotNum].controlbits.bits.X);
}

/*******************************************************************
*																   
*  NAME:        mHBIsetSActive
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_32 qSlotNum
*
*  DESCRIPTION: API function to set SActive accordingly with Tag.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetSActive(mUINT_32 qSlotNum)
{
    mUINT_NATIVE tagId;

    // Get the tag number and set the bit of the tag position.
    // Note: One bit only will be set in these two 16-bit registers.
    // All other bits are zeroed out.
    tagId = rHBI.crsbData.bits.cmdTag;
//    rHBI.qActiveLo = (volatile mUINT_16)(0x1 << tagId); 
//    rHBI.qActiveHi = (volatile mUINT_16)((0x1 << tagId) >> 16); 
    mHBIsetSActiveReg((mUINT_16)(0x1 << tagId),(mUINT_16)((0x1 << tagId) >> 16));
}
/*******************************************************************
*																   
*  NAME:        mHBIclrSActive
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  mUINT_32 qSlotNum
*
*  DESCRIPTION: API function to set SActive accordingly with Tag.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIclrSActiveReg()
{
    rHBI.qActiveLo = 0;
    rHBI.qActiveHi = 0;
}

/*******************************************************************
*																   
*  NAME:        mHBIclrDisparityCnt
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: 
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIclrDisparityCnt(void)
{
    rHBI.disparityCnt = 0;
}

/*******************************************************************
*																   
*  NAME:        mHBIclrCodeViolationCnt
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: 
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIclrCodeViolationCnt(void)
{
    rHBI.codeErrCnt = 0;
}

/*******************************************************************
*																   
*  NAME:        mHBIgetQcmdBusyStatLo
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Inline function to return QCMD_BUSY_STATUS_LOW register content.
*
*  RETURNS:     mUINT_16
*
********************************************************************/
__inline mUINT_16 mHBIgetQcmdBusyStatLo(void)
{
    return (rHBI.qCmdBsyStatLo);
}


/*******************************************************************
*																   
*  NAME:        mHBIgetQcmdBusyStatHi
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Inline function to return QCMD_BUSY_STATUS_HIGH register content.
*
*  RETURNS:     nUINT_16
*
********************************************************************/
__inline mUINT_16 mHBIgetQcmdBusyStatHi(void)
{
    return (rHBI.qCmdBsyStatHi);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetCRSBreadPtr
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Inline function to return CRSB Read Ptr
*
*  RETURNS:     nUINT_16
*
********************************************************************/
__inline mUINT_16 mHBIgetCrsbReadPtr(void)
{
    return (rHBI.crsbPtr.bits.readPtr);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetCrsbWritePtr
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Inline function to return CRSB Write Ptr
*
*  RETURNS:     nUINT_16
*
********************************************************************/
__inline mUINT_16 mHBIgetCrsbWritePtr(void)
{
    return (rHBI.crsbPtr.bits.writePtr);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetCxsbReadPtr
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Inline function to return CXSB Read Ptr
*
*  RETURNS:     nUINT_16
*
********************************************************************/
__inline mUINT_16 mHBIgetCxsbReadPtr(void)
{
    return (rHBI.cxsbPtr.bits.readPtr);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetCxsbWritePtr
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Inline function to return CXSB Write Ptr
*
*  RETURNS:     nUINT_16
*
********************************************************************/
__inline mUINT_16 mHBIgetCxsbWritePtr(void)
{
    return (rHBI.cxsbPtr.bits.writePtr);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetCrsbCmdTag
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Inline function to return current CRSB Queue Tag Cmd
*
*  RETURNS:     nUINT_16
*
********************************************************************/
__inline mUINT_16 mHBIgetCrsbCmdTag(void)
{
    return (rHBI.crsbData.bits.cmdTag);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetCrsbCount
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Inline function to return current CRSB Count
*
*  RETURNS:     nUINT_16
*
********************************************************************/
__inline mUINT_16 mHBIgetCrsbCount(void)
{
    return (rHBI.crsbCntlStat.bits.count);
}

/*******************************************************************
*																   
*  NAME:        mHBIresetCmdFifo
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Inline function to reset command FIFO
*
*  RETURNS:     nUINT_16
*
********************************************************************/
__inline void mHBIresetCmdFifo(void)
{
    rHBI.crsbCntlStat.bits.rdWrPtrReset = 1;
    rHBI.crsbCntlStat.bits.rdWrPtrReset = 0;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetResetTxFisDone                              *
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Enable H/W to reset TxFisDone at every FIS
*
*  RETURNS:                                                        *
********************************************************************/
__inline void mHBIsetResetTxFisDone()
{
    rHBI.tmTxFISTypeLog.bits.txFisDoneResetEn = 1;
    rHBI.tmTxFISTypeLog.bits.rxFisDoneResetEn = 1;
}

/*******************************************************************
*																   
*  NAME:        mHBIclrResetTxFisDone                              *
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Disable H/W to reset TxFisDone at every FIS
*
*  RETURNS:                                                        *
********************************************************************/
__inline void mHBIclrResetTxFisDone()
{
    rHBI.tmTxFISTypeLog.bits.txFisDoneResetEn = 0;
}

/*******************************************************************
*																   
*  NAME:        mHBIsetLBA1_0
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: HAL function to load the LBA1_0,LBA3_2 OR LBA5_4 register
*               with the contents of the 'val' parameter.    
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIset48BitLBA(mLBA_48_BIT_REGS reg, mUINT_16 val)  
{
    // Store mode for each rev.
    switch(reg)
    {
        case mLBA1_0: 
           rHBI.lba1_0.all = val;
           break;
        case mLBA3_2:
           rHBI.lba3_2.all = val;
           break;
        case mLBA5_4:
           rHBI.lba5_4.all = val;
           break;
        default:  
           break;
    }
}

/*******************************************************************
*																   
*  NAME:        mHBIsetSequentialReadLba
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mtLBA val
*
*  DESCRIPTION: HAL function to set sequential read LBA registers.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetSequentialReadLba(mtLBA lba)
{
    rHBI.rdSeqLba01 = (mUINT_16)lba;
    rHBI.rdSeqLba23 = (mUINT_16)(lba >> 16);
    //rHBI.rdSeqLba45 = (mUINT_16)(lba >> 32);
}

/*******************************************************************
*																   
*  NAME:        mHBIgetSequentialReadLba
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HAL function to get sequential read LBA registers.
*
*  RETURNS:     type of mtLBA value
*
********************************************************************/
__inline mtLBA mHBIgetSequentialReadLba(void)
{
    return ((mtLBA)rHBI.rdSeqLba01 + (((mtLBA)rHBI.rdSeqLba23) >> 16));
}

/*******************************************************************
*																   
*  NAME:        mHBIsetSequentialWriteLba
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  type mtLBA val
*
*  DESCRIPTION: HAL function to set sequential write LBA registers.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHBIsetSequentialWriteLba(mtLBA lba)
{
    rHBI.wrSeqLba01 = (mUINT_16)lba;
    rHBI.wrSeqLba23 = (mUINT_16)(lba >> 16);
    //rHBI.wrSeqLba45 = (mUINT_16)(lba >> 32);
}

#ifdef __ghs__
    #pragma ghs section
#else  
    #pragma arm section
#endif    

#endif  //_*_H_INC
