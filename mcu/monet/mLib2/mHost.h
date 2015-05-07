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
#ifndef     _MHOST_H_INC
  #define   _MHOST_H_INC

#include "mGLOBALS.h"
#include "mREGS.h"
#include "mParams.h"
#include "mErrors.h"

#include "mHBI.h"   

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
typedef enum { mMASTER_ONLY,mMASTER_WITH_SLAVE_PRESENT,mSLAVE }mtHOST_MASTER_SLAVE_MODE;

#define mDEV_IS_MASTER      0
#define mDEV_IS_SLAVE       1

  #define mMAX_FIS_SIZE_SECTOR_NUM          0x10
  #define mONE_SECTOR_FIS_SIZE   0x80
  #define mMAX_FIS_SIZE          0x800
  #define mLONG_FIS_SIZE         0xA4  // all in 10-bit symbols: (410 data + 2*(48 ECC symbols + 2 HRLL symbols + 4 CRC symbols + 1 AECC))*10/8/4 and aligned at word(4byte) boundary.
  #define mLONG_HOST_SIZE        0x148 // # of hwords = 2*mLONG_FIS_SIZE
  #define mLONG_HOST_SIZE_REG4L  0x290 // # of bytes = 4*mLONG_FIS_SIZE

#define mNORMAL_HOST_SIZE      0x100
  
typedef struct
{
    // 28-bit address: Feature (na), Sector Count (7:0), lba_low (lba[7:0]),lba_mid (lba[15:8])
    //         lba High (lba[23:16]), Device Register (lba[27:24])
    // 48-bit address: Features (na), Sector Count (2 bytes), lba_low, lba_mid, lba_high are all have 2 bytes
    //         DrvHd (bit 7 and 5 are obsolete, LBA bit shall be set to one, the DEV bit shall indicate the selected device,
    //         bits [3:0] are reserved). 
    // Rearranged the order of the data members in this structure to avoid padding bytes. JSB.
    mUINT_16   secCnt;          // 2 bytes
    mUINT_16   features;        // 2 bytes
    mUINT_8    secNum;          // 1 byte  - lba_low (lba[7:0]) or Sector Number in CHS mode
    mUINT_8    cylLo;           // 1 byte  - lba_mid (lba[15:8])
    mUINT_8    cylHi;           // 1 byte  - lba_hi  (lba[23:16]) 
    mUINT_8    drvHd;           // 1 byte  - in 28 bit mode only: lba [27:24] for lower 4 bits, bit 4 and 5 are not defined, bit 14 (1:lba mode, 0:CHS mode - set by host)
                                //         - in 48 bit mode: bit 6 is used for LBA bit, bit 7 is used for FUA
    mUINT_8    command;         // 1 byte
    mUINT_8    PrevSecNum;      // For 48 bit: lba[31:24]
    mUINT_8    PrevCylLo;       // For 48 bit: lba[39:32]
    mUINT_8    PrevCylHi;       // For 48-bit: lba[47:40]
} mtCDB;

typedef struct
{
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 autoFdmaActivated      : 1;  // first DMA activate disabled
            mUINT_16 reserved               : 15; // reserved
        } bits;
    } sataMode;    
} mtHostStatus;


/*----------------------------------------------------------------------------
 Public Data (other modules can use these vars by including this .h file:
 ---------------------------------------------------------------------------*/
EXTERN mtHostStatus mHostStatus;
 
/*----------------------------------------------------------------------------
 Public Function Prototypes (other modules can use these functions by
 including this .h file):
 ---------------------------------------------------------------------------*/
EXTERN void             mHostSetAtStatus(mINT_16 status);
EXTERN void             mHostClrAtStatus(mINT_16 status);
EXTERN void             mHostSetAtError(mINT_16 error);
EXTERN void             mHostGetCDB(mtCDB *pmtCDB);
EXTERN void             mHostGetCDBfromQram(mtCDB *pmtCDB,mUINT_16 slotNum);
EXTERN void             mHostGetCDBfromStagingTF(mtCDB *pmtCDB);
EXTERN INLINE mUINT_8 mHostGetCmdOpcodeFromStagingTF(void);
EXTERN void             mHostInitRelease (mINT_NATIVE cachedSectors, mINT_NATIVE hostSectors,mUINT_NATIVE writeDir);
EXTERN void             mHostSetupForDataXfer(mINT_NATIVE sectors, mtBOOLEAN writeOp, mtBOOLEAN autoStatusForWrite);
EXTERN void             mHostContinueRelease ( mUINT_NATIVE hostSectors,mUINT_NATIVE writeDir);
EXTERN void             mHostInitParams(mtPARAM_HBI_PAGE *pmParamPage, mtHOST_MASTER_SLAVE_MODE masterSlaveMode);

EXTERN mUINT_8          mHostGetAtStatus(void);
EXTERN mUINT_8          mHostGetAtCmd(void);

EXTERN INLINE void      mHostReset(void);
EXTERN INLINE void      mHostDMAen(void);
EXTERN INLINE void      mHostStopXfer(void);
EXTERN INLINE void      mHostStartXfer(void);
EXTERN INLINE mtBOOLEAN mHostIsReadXferActive(void);
EXTERN INLINE void      mHostSetHdPerCyl(mUINT_8 val);   
EXTERN INLINE void      mHostSetSecPerTrk(mUINT_8 val);  
EXTERN INLINE void      mHostSetAutoReadCntl(mUINT_16 val);
EXTERN INLINE mUINT_16  mHostGetAutoReadCntl(void);
EXTERN INLINE void      mHostSetAutoWriteCntl(mUINT_16 val);
EXTERN INLINE void      mHostSetDir(mUINT_16 dir);
EXTERN INLINE void      mHostIntrSrcInit(mUINT_16 intr);
EXTERN INLINE void      mHostIntrSrcEn(mUINT_16 intr);
EXTERN INLINE void      mHostIntrSrcDis(mUINT_16 intr);
EXTERN INLINE void      mHostClrIntrStatus(mUINT_16 bits);
EXTERN INLINE void      mHostSetConfgCntrl(mUINT_16 bits);
EXTERN INLINE void      mHostSetBitAtMode(mUINT_16 bits);
EXTERN INLINE void      mHostClrBitAtMode(mUINT_16 bits);
EXTERN INLINE void      mHostInitAtStatus(mINT_16 status);
EXTERN INLINE void      mHostSetMultipleBlkSize(mINT_16 sectorsPerBlk);
EXTERN INLINE void      mHostSetDeviceNumber(mtBOOLEAN slaveOrMaster); 
EXTERN INLINE void      mHostSetDeviceNumber(mtBOOLEAN slaveOrMaster); 
EXTERN INLINE void      mHostSetTaskFileReg(mtATA_TASK_FILE_REGS AtReg, mUINT_8 value);
EXTERN INLINE void      mHostIordyEn(void);
EXTERN INLINE void      mHostIordyDis(void);
EXTERN INLINE void      mHostSetSeqRdLbaMode(void);
EXTERN INLINE mUINT_8   mHostGetTaskFileReg(mtATA_TASK_FILE_REGS AtReg);  
EXTERN INLINE mUINT_8   mHostUseDefaultCfgSrc (void);
EXTERN INLINE mUINT_16  mHostGetIntrDisable(void);
EXTERN INLINE mUINT_16  mHostGetResetStatus(void);
EXTERN INLINE mUINT_16  mHostGetAtMode(void);
EXTERN INLINE mUINT_16  mHostGetAutoWriteCntl(void);
EXTERN INLINE mUINT_16  mHostGgetConfgCntrl(void);
EXTERN INLINE mUINT_16  mHostGetMultipleBlkSize(void);
EXTERN INLINE mUINT_16  mHostGetIntrStatus(void);
EXTERN INLINE mUINT_16  mHostGetConfgCntrl(void);
EXTERN INLINE mtBOOLEAN mHostTransferActiveChk (void);
EXTERN INLINE void    mHostSetBlkXferCnt(mUINT_16 numberOfSectors);
EXTERN INLINE void    mHostSet48BitReg(mLBA_48_BIT_REGS reg, mUINT_16 val);
EXTERN INLINE void    mHostSetSeqWrLbaMode(void);  
EXTERN INLINE void    mHostQintrSrcInit(mUINT_16 intr);
EXTERN INLINE void    mHostQintrSrcEn(mUINT_16 intr);
EXTERN INLINE void    mHostQintrSrcDis(mUINT_16 intr);
EXTERN INLINE void    mHostSetFISsize(mUINT_16 val);
EXTERN INLINE mUINT_16    mHostGetFisSize(void);
EXTERN INLINE void    mHostSetMultipleFisSize(mUINT_16 val);
EXTERN INLINE mUINT_16    mHostGetMultipleFisSize(void);
EXTERN INLINE void    mHostClrTMflowIntrStatus (mUINT_16 val);
EXTERN INLINE void    mHostClrEsataErrIntrStatus (mUINT_16 val);
EXTERN INLINE void    mHostSetTMflowIntrSrc(mUINT_16 val); 
EXTERN INLINE void    mHostSetTMfifoThreshold(mUINT_16 val); 
EXTERN INLINE void    mHostClrHBIreset(void);
EXTERN INLINE void    mHostSetEsataErrIntrSrc(mUINT_16 val); 
EXTERN INLINE void    mHostSetESATAconfig(mUINT_16 bits); 
EXTERN INLINE void    mHostClrBitESATAconfig(mUINT_16 bits); 
EXTERN INLINE void    mHostInitPhyTunningControl(mUINT_16 val);  
EXTERN INLINE void    mHostSetBufferSegSel(mUINT_16 val); 
EXTERN INLINE void    mHostInitQoperation(void); 
EXTERN INLINE void    mHostSetTMforceRerr(void);
EXTERN void           mHostSetAltAtError(mUINT_16 error);
EXTERN void           mHostInitTMparams(mtPARAM_HBI_PAGE *pmParamPage);
EXTERN void           mHostSetAltAtStatus(mUINT_16 status);
EXTERN void           mHostManualFISxfer(mUINT_NATIVE writeDir);
EXTERN void           mHostRxBIST(void);
EXTERN mtERROR        mHostBISTDriveInitiator(void);
EXTERN mtERROR        mHostBISTG2HFTP(void);
EXTERN mtERROR        mHostBISTG2MFTP(void);
EXTERN mtERROR        mHostBISTG2LFTP(void);
EXTERN mtERROR        mHostBISTG2SSOP(void);
EXTERN mtERROR        mHostBISTG2_5120COMP(void);
EXTERN mtERROR        mHostBISTG2_81920COMP(void);
EXTERN mtERROR        mHostBISTG2PRBS_7(void);
EXTERN mtERROR        mHostBISTG2LongBit(void);
EXTERN mtERROR        mHostBISTG1HFTP(void);
EXTERN mtERROR        mHostBISTG1PRBS_7(void);
EXTERN mtERROR        mHostBISTG1MFTP(void);
EXTERN mtERROR        mHostBISTG1LongBit(void);
EXTERN mtERROR        mHostBISTG1LFTP(void);
EXTERN mtERROR        mHostBISTG1SSOP(void);
EXTERN mtERROR        mHostBISTG1_5120COMP(void);
EXTERN mtERROR        mHostBISTG1_81920COMP(void);
EXTERN mUINT_16       mHostGetAltAtStatus(void);
EXTERN INLINE mUINT_16    mHostGetRxFISType(void);
EXTERN INLINE mUINT_16    mHostGetTxFISType(void);
EXTERN INLINE mUINT_16    mHostGetRxFisTypeErrLog(void);
EXTERN INLINE mUINT_16    mHostGetTxFisTypeErrLog(void);
EXTERN INLINE mUINT_16    mHostGetTMflowIntrStatus (void);
EXTERN INLINE mUINT_16    mHostGetQcmdIntrSrc(void); 
EXTERN INLINE mUINT_16    mHostGetEsataErrIntrSrc(void); 
EXTERN INLINE mUINT_16    mHostGetTMflowIntrSrc (void);
EXTERN INLINE mUINT_16    mHostGetTMflowStatus(void);
EXTERN mUINT_32           mHostGetQslotBsy(void);
EXTERN INLINE void    mHostSetWrSeqConfig(mUINT_16 val); 
//EXTERN INLINE void mHostClrTmStatusHi           (mUINT_16 val);
EXTERN INLINE mtBOOLEAN mHostGetFdmaActivated(void);
EXTERN INLINE void mHostSetFdmaActivateDis      (mtBOOLEAN val);
EXTERN INLINE void mHostSetBitAutoStatusConfg   (mUINT_16 val);
EXTERN INLINE void mHostSetBitAceConfg1         (mUINT_16 val);
EXTERN INLINE void mHostSetBitAceConfg2         (mUINT_16 val);
EXTERN INLINE void mHostSetBitOverrideCntl      (mUINT_16 val);
EXTERN INLINE void mHostSetCxsbFwReqEoc         (void);
EXTERN INLINE void mHostSetCxsbFwReqNonQDataXfer    (mUINT_16 secCnt, mUINT_16 bSeg, mtBOOLEAN writeOp, mtBOOLEAN autoStatusForWrite);
EXTERN INLINE void mHostSetCxsbFwReqQcmdDataXfer (mUINT_16 secCnt, mUINT_16 bSeg, mtBOOLEAN writeOp, mUINT_16 qSlot, mtBOOLEAN autoStatusForWrite);
EXTERN INLINE void mHostResetCmdxh              (void);
EXTERN INLINE void mHostResetCrsb               (void);
EXTERN INLINE void mHostSetBitMsgLogConfg       (mUINT_16 val);
EXTERN INLINE void mHostSetMsgLogCntl           (mUINT_16 val);
EXTERN INLINE void mHostSetBitMsgLogCntl        (mUINT_16 bits);
EXTERN INLINE void mHostSetBitCxsbCntl          (mUINT_16 bits);
EXTERN INLINE void mHostClrBitCxsbCntl          (mUINT_16 bits);
EXTERN INLINE void mHostSetCrsbCntl             (mUINT_16 val);
EXTERN INLINE mUINT_16 mHostGetCxsbCntl         (void);
EXTERN INLINE mtBOOLEAN mHostIsNonQcmd          (void);
EXTERN INLINE void mHostCrsbCmdResume           (mUINT_16 val);
EXTERN INLINE void mHostSetFwStatus             (mUINT_8 val);
EXTERN INLINE void mHostSetFwError              (mUINT_8 val);
EXTERN INLINE mUINT_16  mHostGetBmSectorsXfer(void);
EXTERN INLINE mUINT_8     mHostGetFwStatus      (void);
EXTERN INLINE mUINT_8     mHostGetFwError       (void);
EXTERN INLINE void mHostSetBitMiscStatus        (mUINT_16 val);
EXTERN INLINE void mHostClrBitMiscStatus        (mUINT_16 val);
EXTERN INLINE void mHostSendFwStatus            (mUINT_8 status);
EXTERN INLINE void mHostSetBitATdevConfgCntrl   (mUINT_16 bits);
EXTERN INLINE void mHostClrBitATdevConfgCntrl   (mUINT_16 bits);
EXTERN INLINE void mHostsetCxsbFwReqSDBFisSend  (mUINT_16 qSlot);
EXTERN INLINE void mHostResetFlowCntl (void);
EXTERN INLINE void mHostsetCxsbFwReqSDBAggregatedFisSend (void);
EXTERN INLINE mUINT_16 mHostGetESATAflowPwrRstCntl(void);

//Add from HostSATA.c
EXTERN void mToggleTxFlowReset(void);
EXTERN void mToggleLinkSMReset(void);
EXTERN void mToggleCmdExeReset(void);
EXTERN void mToggleCxsbReset(void);
EXTERN void mToggleNcqPhaseReset(void);
EXTERN void mToggleRxTxFlowReset(void);



  #define mHostGetAtCmd()             mHBIgetAtCmd()
  #define mHostSetSectorCount(val)      mHBIsetSectorCount((val))
  #define mHostSetUserFISword0L(val)    mHBIsetUserFISword0L((val))
  #define mHostSetUserFISword0H(val)    mHBIsetUserFISword0H((val))
  #define mHostSetUserFISword1L(val)    mHBIsetUserFISword1L((val))
  #define mHostSetUserFISword1H(val)    mHBIsetUserFISword1H((val))
  #define mHostSetUserFISword2L(val)    mHBIsetUserFISword2L((val))
  #define mHostSetUserFISword2H(val)    mHBIsetUserFISword2H((val))
  #define mHostSetUserFISword3L(val)    mHBIsetUserFISword3L((val))
  #define mHostSetUserFISword3H(val)    mHBIsetUserFISword3H((val))
  #define mHostSetUserFISword4L(val)    mHBIsetUserFISword4L((val))
  #define mHostSetUserFISword4H(val)    mHBIsetUserFISword4H((val))
  #define mHostSetManualFlowControl(val)    mHBIsetManualFlowControl((val))
  #define mHostSetSectorNum(val)        mHBIsetSectorNum(val)
  #define mHostGetSectorNum()           mHBIGetSectorNum()
  #define mHostGetEsataErrIntStatus()   mHBIgetEsataErrIntStatus()
  #define mHostGetUserFISword1L()       mHBIGetUserFISword1L()
  #define mHostGetESATAConfig()         mHBIGetESATAConfig()

  #define mHostGetQCmdControl()         mHBIgetQCmdControl()
  #define mHostSetQcmdCntl(val)         mHBIsetQcmdCntl((val))
  #define mHostClrQcmdCntl(val)         mHBIclrQcmdCntrl((val))
  #define mHostClrQcmdIntr(val)         mHBIclrQcmdIntr((val))
  #define mHostGetQcmdIntrStatus()      mHBIgetQcmdIntrStatus()
  #define mHostClrTmStatusHi(val)     mHBIclrTmStatusHi(val)
  #define mHostGetBlkXferCnt()          mHBIgetBlkXferCnt()

//  #if (mNCQ_OP == mENABLE)
    #define mHostGetCmdTagId()          mHBIgetCmdTagId()
    #define mHostClrTmStatusLow(val)    mHBIclrTmStatusLow(val)
    #define mHostClrTmStatusHi(val)     mHBIclrTmStatusHi(val)
    #define mHostGetTmStatusLow()       mHBIgetTmStatusLow()
    #define mHostGetTmStatusHi()        mHBIgetTmStatusHi()
    #define mHostGetXMLOGSBCnt()        mHBIgetXMLOGSBCnt()
    #define mHostClrXMLOGSBCnt()        mHBIclrXMLOGSBCnt()
    #define mHostGetXMLOGSBData()       mHBIgetXMLOGSBData()
    #define mHostSetQcmdAbort()         mHBIsetQcmdAbort()
    #define mHostEnableQCmd()           {                                                                                     \
                                          mHostClrQcmdCntl(m_tHBI_QCMDCNTRL_bits_qAutoRelDis);                              \
                                          mHostSetQcmdCntl(m_tHBI_QCMDCNTRL_bits_qAutoStatEn|m_tHBI_QCMDCNTRL_bits_qCmdEn); \
                                        }
  
    #define mHostSetATdevCongCntl()       mHBIsetBitATdevConfgCntrl (mUINT_16 bits)
//  #endif // (NCQ_OP == mENABLE)
  #define mHostGetLastQslot()           mHBIgetLastQslot()
  #define mHostGetQhead()               mHBIgetQhead()
  #define mHostSetQhead(val)            mHBIsetQhead((val))
  #define mHostGetLBAfromQslot(val)     mHBIgetLBAfromQslot((val))
  #define mHostGetNextEmptyQslot()      mHBIgetNextEmptyQslot()
  #define mHostSetNextQtailOffset(n)    mHBIsetNextQtailOffset((n))
  #define mHostGetNextQslot(val)        mHBIgetNextQslot((val))
  #define mHostSetQramNextQslot(val1,val2)  mHBIsetQramNextQslot((val1),(val2))
  #define mHostGetNewQCmd()             mHBIgetNewQCmd()
  #define mHostLockQram()               mHBIlockQram()
  #define mHostFreeQram()               mHBIfreeQram()
  #define mHostSetSActiveReg(val1,val2) mHBIsetSActiveReg((val1),(val2))
  #define mHostClrSActiveReg()          mHBIclrSActiveReg()
  #define mHostSetESATAflowPwrRstCntl(v)    mHBIsetESATAflowPwrRstCntl(v)
//  #define mHostGetESATAflowPwrRstCntl(v)    mHBIgetESATAflowPwrRstCntl(v)
  #define mHostClrESATAflowPwrRstCntl(v)    mHBIclrESATAflowPwrRstCntl(v)
  
  #define mHostGetSectorCntfromQslot(val)   mHBIgetSectorCntfromQslot ((val))
  #define mHostGetCmdfromQslot(val)         mHBIgetCmdfromQslot       ((val))
  #define mHostGetDevHdfromQslot(val)       mHBIgetDevHdfromQslot     ((val))
  #define mHostGetFeaturesfromQslot(val)    mHBIgetFeaturesfromQslot  ((val))
  
  #define mHostGetQcmdBusyStatLo()          mHBIgetQcmdBusyStatLo()
  #define mHostGetQcmdBusyStatHi()          mHBIgetQcmdBusyStatHi()

  #define mHostSetQRAMbSeg(qSlotNum, segNum)                 mHBIsetQRAMbSeg((qSlotNum), (segNum))
  #define mHostSetQRAMxferByteCount(qSlotNum, hostSectors)   mHBIsetQRAMxferByteCount((qSlotNum), (hostSectors))
  #define mHostSetQRAMbufOffset(qSlotNum, bufOffset)         mHBIsetQRAMbufOffset((qSlotNum), (bufOffset))
  #define mHostSetQRAMbitX(qSlotNum)                         mHBIsetQRAMbitX((qSlotNum))
  #define mHostClrQRAMbitX(qSlotNum)                         mHBIclrQRAMbitX((qSlotNum))
  #define mHostGetQRAMbitX(qSlotNum)                         mHBIgetQRAMbitX((qSlotNum))
  #define mHostSetSActive(qSlotNum)                          mHBIsetSActive((qSlotNum))
  #define mHostTrigsSetDeviceBitsFIS(val)                    mHBItrigsSetDeviceBitsFIS((val))

  #define mHostClrDisparityCnt()        mHBIclrDisparityCnt()                                    
  #define mHostClrCodeViolationCnt()    mHBIclrCodeViolationCnt()
  #define mHostGetMiscStatus()          mHBIgetMiscStatus()
  #define mHostGetCrsbReadPtr()         mHBIgetCrsbReadPtr()
  #define mHostGetCrsbCmdTag()          mHBIgetCrsbCmdTag()
  #define mHostGetCrsbCount()           mHBIgetCrsbCount()
  #define mHostSetResetTxFisDone()      mHBIsetResetTxFisDone()
  #define mHostClrResetTxFisDone()      mHBIclrResetTxFisDone()
  #define mHostResetCmdFifo()           mHBIresetCmdFifo()

  #define mHostSetSeqReadLba(lba)       mHBIsetSequentialReadLba(lba)
  #define mHostGetSeqReadLba()          mHBIgetSequentialReadLba()
  #define mHostSetSeqWriteLba(lba)      mHBIsetSequentialWriteLba(lba)

  #define mHostGetTmPhase()             mHBIgetTmPhase()
#endif  //_H_INC
