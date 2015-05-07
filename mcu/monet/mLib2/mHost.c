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

/*----------------------------------------------------------------------------
 Include files:
 ---------------------------------------------------------------------------*/
#define   INSTANTIATE_MHOST

//#include "mMACROS.h"
#include "mHost.h"
#include "mHBI.h"
#include "mSFRS.h"
#include "mCLKPWR.h"
#include "mHDC.h"   // also allow access to HDC object locally
//#include "mCARDS.h"
//#include "mKrnl.h"
//#include "SerTask.h"
//#include "mCacheSegmentManager.h"
//#include "mCache.h"
//#include "CmdTable.h"
#include "Conds.h"
#include "mParams.h"
//#include "HostSata.h"

//#include "RTOSparams.h"
//#include "mBfr.h"
#include "mPLI.h"
#include "mPhyLink.h"
//#include "Ncq.h"



void mToggleTxFlowReset(void)
{
   mHostSetESATAflowPwrRstCntl(m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_TxFlowRst);
   mHostClrESATAflowPwrRstCntl(m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_TxFlowRst);
}

void mToggleRxTxFlowReset(void)
{
   mHostSetESATAflowPwrRstCntl(m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_TxFlowRst | m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_RxFlowRst);
   mHostClrESATAflowPwrRstCntl(m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_TxFlowRst | m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_TxFlowRst);
}

void mToggleNcqPhaseReset(void)
{
   mHostSetESATAflowPwrRstCntl(m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_ncqPhaseRst);
   mHostClrESATAflowPwrRstCntl(m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_ncqPhaseRst);
}
void mToggleCmdExeReset(void)
{
   mHostSetESATAflowPwrRstCntl(m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_cmdExeRst);
   mHostClrESATAflowPwrRstCntl(m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_cmdExeRst);
}

void mToggleLinkSMReset(void)
{ 
    mHostSetESATAflowPwrRstCntl(m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_lnkSMreset);
    mHostClrESATAflowPwrRstCntl(m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_lnkSMreset);
}

void mToggleCxsbReset(void)
{
    mHostSetBitCxsbCntl(m_tHBI_CXSB_CNTL_STAT_bits_reset); 
    mHostClrBitCxsbCntl(m_tHBI_CXSB_CNTL_STAT_bits_reset); 
}

/*******************************************************************
*
*  NAME:        mHostSetBitAtMode
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: API function to set AT mode register 
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostSetBitATdevConfgCntrl(mUINT_16 bits)
{
   mHBIsetBitATdevConfgCntrl(bits);
}

INLINE void mHostClrBitATdevConfgCntrl(mUINT_16 bits)
{
   mHBIclrBitATdevConfgCntrl(bits);
}

INLINE void mHostSetBitAutoStatusConfg(mUINT_16 bits)
{
   mHBIsetBitAutoStatusConfg(bits);
}

INLINE void mHostClrBitMiscStatus(mUINT_16 bits)
{
   mHBIclrBitMiscStatus(bits);
}

INLINE void mHostSetBitMiscStatus(mUINT_16 bits)
{
   mHBIsetBitMiscStatus(bits);
}

INLINE void mHostSetCxsbFwReqQcmdDataXfer (mUINT_16 secCnt, mUINT_16 bSeg, mtBOOLEAN writeOp, mUINT_16 qSlot, mtBOOLEAN autoStatusForWrite)
{
    
    mHBIsetCxsbFwReqQcmdDataXfer(secCnt,  bSeg,  writeOp,  qSlot, autoStatusForWrite);
}

INLINE void mHostSetCxsbFwReqNonQDataXfer (mUINT_16 secCnt, mUINT_16 bSeg, mtBOOLEAN writeOp, mtBOOLEAN autoStatusForWrite)
{
    mHBIsetCxsbFwReqNonQDataXfer(secCnt, bSeg, writeOp, autoStatusForWrite);
}

INLINE void mHostsetCxsbFwReqSDBFisSend (mUINT_16 qSlot)
{
    mHBIsetCxsbFwReqSDBFisSend  (qSlot);
}

INLINE void mHostsetCxsbFwReqSDBAggregatedFisSend (void)
{
    mHBIsetCxsbFwReqSDBAggresatedFisSend();
}

INLINE void mHostSetCxsbFwReqEoc()
{
    mHBIsetCxsbFwReqEoc();
    #if ( DAVINCI_FPGA == mENABLE )
    #else
    while (!rHBI.hostIntStat0.bits.fwXferDone)
    {
        if (mSystemState.curState != mPOWER_UP_STATE)
            return;
        //mKrnlWaitForEvents(0); // let others have the CPU while I am waiting
    }
    #endif
    rHBI.hostIntStat0.all = m_tHBI_INT_bits_fwXferDone;
}

INLINE void mHostSetBitAceConfg1 (mUINT_16 bits)
{
    mHBIsetBitAceConfg1(bits);
}
INLINE void mHostSetBitAceConfg2 (mUINT_16 bits)
{
    mHBIsetBitAceConfg2(bits);
}
INLINE void mHostSetBitOverrideCntl (mUINT_16 bits)
{
    mHBIsetBitOverrideCntl(bits);
}

//INLINE void mHostSetBitCrhsCntl(mUINT_16 bits)
//{
//    mHBIsetBitCrhsCntl(bits);
//}

INLINE void mHostResetCmdxh ()
{
    mHBIresetCmdxh();
}

INLINE void mHostResetCrsb ()
{
    mHBIresetCrsb();
}

INLINE void mHostResetFlowCntl ()
{
    mHBIresetFlowCntl();
}

INLINE void mHostSetBitMsgLogConfg(mUINT_16 bits)
{
    mHBIsetBitMsgLogConfg(bits);
}

INLINE void mHostSetMsgLogCntl(mUINT_16 val)
{
    mHBIsetMsgLogCntl(val);
}

INLINE void mHostSetBitMsgLogCntl(mUINT_16 val)
{
    mHBIsetBitMsgLogCntl(val);
}

INLINE void mHostSetBitCxsbCntl(mUINT_16 val)
{
    mHBIsetBitCxsbCntl(val);
}

INLINE void mHostClrBitCxsbCntl(mUINT_16 val)
{
    mHBIclrBitCxsbCntl(val);
}

INLINE mUINT_16 mHostGetCxsbCntl(void)
{
    return (mHBIgetCxsbCntl());
}

INLINE mUINT_16 mHostGetMsgLogCntl(void)
{
    return (mHBIgetMsgLogCntl());
}

INLINE mtBOOLEAN mHostIsNonQcmd(void)
{
    return (mHBIisNonQcmd());
}

INLINE void mHostCrsbCmdResume(mUINT_16 val)
{
    mHostClrIntrStatus(m_tHBI_INT_bits_nonAceCmd); // needed for uPack
    mHBIcrsbCmdResume(val);
}

INLINE void mHostSetFwStatus(mUINT_8 status )
{
    mHBIsetFwStatus(status);     
}

INLINE void mHostSetFwError(mUINT_8 error )
{
    mHBIsetAltAtError(error);     
}

INLINE mUINT_8 mHostGetFwStatus(void )
{
    return (mHBIgetFwStatus());     
}

INLINE mUINT_8 mHostGetFwError(void )
{
    return (mHBIgetFwError());
}

INLINE mUINT_16 mHostGetBmSectorsXfer(void)
{
    return (mHBIgetBmSectorsXfer());
}

void mHostSendFwStatus (mUINT_8 status)
{
    mHostSetFwStatus(status); 
    mHostSetBitATdevConfgCntrl(m_tHOST_BUS_INTERFACE_ATdevConfgCntrl_bits_fwEocIbit); // send intrq
    mHostSetCxsbFwReqEoc();
}

/*******************************************************************
*
*  NAME:   	    mHostInitParams
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  pointer to HBI Parameter page struct, master slave mode
*
*  DESCRIPTION: Initializes the HDC Host Bus Interface
*
*  RETURNS:     None  
*
*  date         by              description
*  7/1/01       Lau Nguyen      Add prelim. support for Master/Slave    											   
*	
********************************************************************/
void mHostInitParams (mtPARAM_HBI_PAGE *pmParamPage, mtHOST_MASTER_SLAVE_MODE masterSlaveMode)
{
    mtPARAM_HBI_PARAMS   *pParams;

    pParams = &(pmParamPage->params);

 // mHostReset();  

    mHostClrIntrStatus(0xffff);                 // clear all Interrupts
 
//    mHostSetConfgCntrl(pParams->devCntl) ;       
 // mHostIntrSrcInit(pParams->intrSrcs);
    mHostSetESATAflowPwrRstCntl(0x1E01);  // Kim - need to setup define later for this setting
                                          // toggle bits 0,9,10,11,12
    mHostClrESATAflowPwrRstCntl(0x1E01);
                                          //R4A08 =0 ?  Ask Kevin
  
    mHostSetBitAtMode(pParams->mode0);    // Currently all disable - Kim - need to check later
    mHostSetBitAutoStatusConfg(0);        // Kim - need to add in params page
    mHostSetBitOverrideCntl(0x13FE);      // R4A7E - Disable all parity checking, enable Malformed FIS detection ; 
    mHostSetBitCxsbCntl(m_tHBI_CXSB_CNTL_STAT_bits_parityDis); // R4B02[12] 
    mHostSetFdmaActivateDis(mFALSE);      
    mHostSetAutoWriteCntl(pParams->aceWr);
    mHostSetAutoReadCntl(pParams->aceRd);
    mHostSetHdPerCyl(pParams->hdPerCyl);
    mHostSetSecPerTrk(pParams->secPerTrk);


}

/*******************************************************************
*
*  NAME:   	    mHostGetCDB
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  pointer to mtCDB object
*
*  DESCRIPTION: API function that fills out an mtCDB from the values in the HDC
*
*  RETURNS:     None  
*
*  date         by              description 
*  09/14/00     Lau Nguyen      Initial release
*	
********************************************************************/
void mHostGetCDB(mtCDB *pmtCDB)
{
#if 0
    mUINT_8 cmdFlag;

    pmtCDB->command  =   rHBI.cmnd;

    cmdFlag = mCmdVectorTable[pmtCDB->command].uFlags.all;

    // NOTE: Code only supports 32 bit Lba for now
    //This will need to be changed for 48 bit lba mode
    if (cmdFlag & mEXTENDED_CMD)
    {
        pmtCDB->drvHd    =   (rHBI.initialLba3_2 | 0xE000)>>8;    
    }
    else
    {
        pmtCDB->drvHd    =   rHBI.initDevHd;
    }
    pmtCDB->cylHi    =   rHBI.initCylHigh;
    pmtCDB->cylLo    =   rHBI.initCylLow;

   if (cmdFlag & mEXTENDED_CMD)
   	{
        pmtCDB->PrevCylLo = (mUINT_8) (rHBI.initialLba5_4);
        pmtCDB->PrevCylHi = (mUINT_8) (rHBI.initialLba5_4)>>8 ;
   	}

    {   // Debounce this register to have an accurate reading for auto commands.
        mUINT_8 temp1, temp2; 
        for (; ;)
        {
            temp1 = rHBI.initSectorNum;
            temp2 = rHBI.initSectorNum;
            if (temp1 == temp2)
            {
                break;
            }
        }
        pmtCDB->secNum = temp1;
    }

    if (cmdFlag & mEXTENDED_CMD)
    {
        pmtCDB->PrevSecNum = rHBI.initialLba3_2 >> 8;
        pmtCDB->secCnt     =  rHBI.initialSectCnt1_0.all;
        pmtCDB->features   =  rHBI.feature1_0.all;
    }
    else
    {
        pmtCDB->secCnt     =  rHBI.initialSectCnt1_0.bits.initialSectCnt0;
        pmtCDB->features   =  rHBI.feature1_0.bits.feature0;
    }
#endif    
}

/*******************************************************************
*
*  NAME:   	    mHostGetCDBfromQram
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  pointer to mtCDB object and the Q slot number
*
*  DESCRIPTION: API function that fills out an mtCDB from the values in the Qram
*
*  RETURNS:     None  
*
*	
********************************************************************/
void mHostGetCDBfromQram(mtCDB *pmtCDB, mUINT_16 slotNum)
{
    mUINT_32 newLBA;
    
    newLBA = mHostGetLBAfromQslot(slotNum);
    pmtCDB->drvHd    =   mHostGetDevHdfromQslot(slotNum);
    pmtCDB->command  =   mHostGetCmdfromQslot(slotNum);
    pmtCDB->cylHi    =   (mUINT_8)(newLBA>>16);
    pmtCDB->cylLo    =   (mUINT_8)(newLBA>>8);
    pmtCDB->secNum   =   (mUINT_8)newLBA;
    pmtCDB->secCnt   =   mHostGetSectorCntfromQslot(slotNum);
    pmtCDB->PrevSecNum = (mUINT_8)(newLBA>>24);
    pmtCDB->PrevCylLo  = 0;
    pmtCDB->PrevCylHi  = 0;
}

/*******************************************************************
*
*  NAME:   	    mHostGetCDBfromStagingTF
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  pointer to mtCDB object and the Q slot number
*
*  DESCRIPTION: API function that fills out an mtCDB from staging taskfile
*
*  RETURNS:     None  
*
*	
********************************************************************/
void mHostGetCDBfromStagingTF(mtCDB *pmtCDB)
{
    pmtCDB->command  =   (mUINT_8)rHBI.uRegFIS0H;
    pmtCDB->features =   (mUINT_8)(rHBI.uRegFIS0H>>8);
    pmtCDB->drvHd    =   (mUINT_8)(rHBI.uRegFIS1H>>8);
    pmtCDB->cylHi    =   (mUINT_8)rHBI.uRegFIS1H;
    pmtCDB->cylLo    =   (mUINT_8)(rHBI.uRegFIS1L>>8);
    pmtCDB->secNum   =   (mUINT_8)rHBI.uRegFIS1L;
    pmtCDB->secCnt   =   rHBI.uRegFIS3L;
    pmtCDB->PrevSecNum = (mUINT_8)rHBI.uRegFIS2L;;
    pmtCDB->PrevCylLo  = 0;
    pmtCDB->PrevCylHi  = 0;
}

INLINE mUINT_8 mHostGetCmdOpcodeFromStagingTF(void)
{
    return ((mUINT_8)rHBI.uRegFIS0H);
}


/*******************************************************************
*
*  NAME:   	    mHostSetupForDataXfer
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  number of sectors to transfer, transfer direction, and auto status for write option.
*
*  DESCRIPTION: API function to setup HBI to transfer to/from Host
*
*  RETURNS:     None 
*
********************************************************************/
void mHostSetupForDataXfer(mINT_NATIVE sectors, mtBOOLEAN writeOp, mtBOOLEAN autoStatusForWrite)
{
    //mHostSetCxsbFwReqNonQDataXfer(sectors,mBfr.hostSectorCountNum,writeOp,autoStatusForWrite);     

}

/*******************************************************************
*
*  NAME:   	    mHostDMAen
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function enables DMA mode and disables UDAM
*
*  RETURNS:     None
*	
********************************************************************/
INLINE void mHostDMAen(void)
{
}


/*******************************************************************
*
*  NAME:   	    mHostSetMultipleFisSize
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  sectorsPerBlk
*
*  DESCRIPTION: API function to set number of sectors per block
*               for read/write multiple cmds
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostSetMultipleFisSize(mUINT_16 sectorsPerBlk)
{
    mHBIsetMultipleFisSize(sectorsPerBlk);
}

/*******************************************************************
*
*  NAME:        mHostGetFISsize
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
INLINE mUINT_16 mHostGetFisSize(void)
{
    return (mHBIgetFisSize());
}

/*******************************************************************
*
*  NAME:   	    mHostGetMultipleFisSize
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  sectorsPerBlk
*
*  DESCRIPTION: API function to set number of sectors per block
*               for read/write multiple cmds
*
*  RETURNS:     None
*
********************************************************************/
INLINE mUINT_16 mHostGetMultipleFisSize(void)
{
    return (mHBIgetMultipleFisSize());
}

/*******************************************************************
*
*  NAME:   	    mHostSetMultipleBlkSize
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  sectorsPerBlk
*
*  DESCRIPTION: API function to set number of sectors per block
*               for read/write multiple cmds
*
*  RETURNS:     None
*	
********************************************************************/
INLINE void mHostSetMultipleBlkSize(mINT_16 sectorsPerBlk)
{
    mHBIsetMultipleBlkSize(sectorsPerBlk);
}

/*******************************************************************
*
*  NAME:   	    mHostGetMultipleBlkSize
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to get number of sectors per block
*               for read/write multiple cmds
*
*  RETURNS:     mUINT_16      											   
*
********************************************************************/
INLINE mUINT_16 mHostGetMultipleBlkSize(void)
{
    return (mHBIgetMultipleBlkSize());
}

/*******************************************************************
*
*  NAME:        mHostInitAtStatus
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  status
*
*  DESCRIPTION: API function to set bits in the AT status reg (1501h)
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostInitAtStatus(mINT_16 status )
{
    mHBIinitStatus(status);     
}

/*******************************************************************
*
*  NAME:        mHostSetAtStatus
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  status
*
*  DESCRIPTION: API function to set bit or bits in the AT status reg (R4A02)
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostSetAtStatus(mINT_16 status )
{
    mHBIsetStatus(status);  // Errors 
}

/*******************************************************************
*
*  NAME:        mHostSetAltStatus
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  status
*
*  DESCRIPTION: API function to set bits in the Alternate AT status reg (R4A02)
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostSetAltAtStatus(mUINT_16 status )
{
    mHBIsetAltAtStatus(status);     
}

/*******************************************************************
*
*  NAME:   	    mHostClrAtStatus
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  status
*
*  DESCRIPTION: API function to clear bit or bits in AT status reg (1501h)
*
*  RETURNS:     None
* 
********************************************************************/
INLINE void mHostClrAtStatus(mINT_16 status )
{
    mHBIclrStatus(status);  // Clear Errors 
}

/*******************************************************************
*
*  NAME:        mHostGetAtStatus
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to return AT status
*
*  RETURNS:     mUINT 8 bit value of  Register 1501h
*
********************************************************************/
INLINE mUINT_8 mHostGetAtStatus (void)
{
    return (mHBIgetStatus ()); 
}

/*******************************************************************
*
*  NAME:   	    mHostGetIntrStatus
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to get value of host intr status reg (0x150A)
*
*  RETURNS:     mUINT_16
*	
********************************************************************/
INLINE mUINT_16 mHostGetIntrStatus (void)
{
    return (mHBIgetHostIntrStatus());
}

/*******************************************************************
* 
*  NAME:   	    mHostGetQslotbsy
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to get value of queue slot busy
*
*  RETURNS:     mUINT_32
*	
********************************************************************/
INLINE mUINT_32    mHostGetQslotBsy(void)
{
    return (mHBIgetQslotBsy());
}


/*******************************************************************
*																   
*  NAME:   	    mHostClrIntrStatus											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  mUINT 16 bit value    											   
*																   
*  DESCRIPTION: API func to set specific host intr value overwriting
*               existing value. Reg 0x151Dh
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
INLINE void mHostClrIntrStatus (mUINT_16 bits) 
{
    mHBIclrIntrStatus (bits);
}

/*******************************************************************
*																   
*  NAME:   	    mHostGetIntrDisable 											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  None    											   
*																   
*  DESCRIPTION: API func to read host interrupt mask register. (150Bh)
*																   
*  RETURNS:     mUINT 16 bit value      											   
*	
********************************************************************/
INLINE mUINT_16 mHostGetIntrDisable (void)
{
    return (mHBIgetIntrDisable ());
}

/*******************************************************************
*																   
*  NAME:   	    mHostSetBlkXferCnt											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  mUINT 8 bit numberOfSectors , 16 bit for 6545   											   
*																   
*  DESCRIPTION: API func to call mHBI function to set num of sector
*               for transfer block count.
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
INLINE void mHostSetBlkXferCnt (mUINT_16 numberOfSectors)
{
    mHBIsetBlkXferCnt (numberOfSectors);
}
/*******************************************************************
*																   
*  NAME:   	    mtHostSetTaskFileReg											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  type mATA_TASK_FILE_REGS AtReg value, int 8 of value to use   											   
*				 											   
*  DESCRIPTION: Api func to set a given register to a specified value 
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
INLINE void mHostSetTaskFileReg (mtATA_TASK_FILE_REGS AtReg, mUINT_8 value)  
{
    mHBIsetTaskFileReg(AtReg, value);  
}

/*******************************************************************
*																   
*  NAME:   	    mHostGetTaskFileReg 											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  type mtATA_TASK_FILE_REGS AtReg value to check    											   
*																   
*  DESCRIPTION: API func to retrieve the value stored in a specified AtReg
*																   
*  RETURNS:     mUINT 8 value stored in the specified register      											   
*	
********************************************************************/
INLINE mUINT_8 mHostGetTaskFileReg (mtATA_TASK_FILE_REGS AtReg)  
{
    return (mHBIgetTaskFileReg (AtReg));
}

/*******************************************************************
*																   
*  NAME:   	     mHostSet48BitReg											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  type mLBA_48_BIT_REGS  AtReg value to update    											   
*																   
*  DESCRIPTION: API func to update the value stored in a specified AtReg
*																   
*  RETURNS:     mUINT 16 value to be stored in the specified register      											   
*	
********************************************************************/
INLINE void  mHostSet48BitReg(mLBA_48_BIT_REGS  reg, mUINT_16  val)  
{
     mHBIset48BitLBA(reg, val);  
}

/*******************************************************************
*																   
*  NAME:   	    mHostStartXfer											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  None    											   
*																   
*  DESCRIPTION: API func to start host xfer
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
INLINE void mHostStartXfer(void)
{
    mHBIstartXfer();
}

/*******************************************************************
*																   
*  NAME:   	    mHostStopXfer											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  None    											   
*																   
*  DESCRIPTION: API func to stop host xfer
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
INLINE void mHostStopXfer(void)
{
    mHBIstopXfer();
}

/*******************************************************************
*																   
*  NAME:   	    mHostIsReadXferActive											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  None    											   
*																   
*  DESCRIPTION: API func to get check if the host is active for read.
*																   
*  RETURNS:     mTRUE or mFALSE      											   
*	
********************************************************************/
INLINE mtBOOLEAN mHostIsReadXferActive(void)
{
    return mHBIisReadXferActive();
}

/*******************************************************************
*																   
*  NAME:   	    mHostSetDir											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  mUINT_16 value of directrion, 0 Read, 1 Write.    											   
*																   
*  DESCRIPTION: API func to set set direction of host
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
INLINE void mHostSetDir(mUINT_16 dir)
{
    mHBIsetHostDir(dir);
}

/*******************************************************************
*																   
*  NAME:   	    mHostSetAutoWriteCntl										   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  mUINT_16 value     											   
*																   
*  DESCRIPTION: API func to set AutoWriteCntl  Reg
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
INLINE void mHostSetAutoWriteCntl(mUINT_16 val)
{
    mHBIsetAutoWriteCntl(val);
}

/*******************************************************************
*																   
*  NAME:   	    mHostGetAutoWriteCntl										   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:       											   
*																   
*  DESCRIPTION: API func to get the value AutoWriteCntl  Reg
*																   
*  RETURNS:     mUINT_16 value      											   
*	
********************************************************************/
INLINE mUINT_16 mHostGetAutoWriteCntl(void)
{
    return (mHBIgetAutoWriteCntl());

}

/*******************************************************************
*                                                                  
*  NAME:        mHostGetConfgCntrl
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to get the value of Host Confg Cntrl Reg.
*
*  RETURNS:     mUINT_16
*
********************************************************************/
INLINE mUINT_16 mHostGetConfgCntrl (void)
{
    return (mHBIgetConfgCntrl());
}


/*******************************************************************
*  NAME:        mHostGetConfgCntrl
*
*  DESCRIPTION: returns 1 if Host interface is active, 0 not active
*
*  RETURNS:     mUINT_16
********************************************************************/
INLINE mtBOOLEAN mHostTransferActiveChk (void)
{
    return (mHBIgetMiscStatus() & m_tHOST_BUS_INTERFACE_hostMiscStatus_bits_xferActive);
}

/*******************************************************************
*                                                                  
*  NAME:        mHostSetConfgCntrl
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: API function to set the bits in Host Confg Cntrl Reg.
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostSetConfgCntrl (mUINT_16 bits)
{
    mHBIsetConfgCntrl(bits);
}

/*******************************************************************
*																   
*  NAME:   	    mHostGetResetStatus											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  None    											   
*																   
*  DESCRIPTION: API func to return host reset register value
*																   
*  RETURNS:     mUINT_16 status      											   
*	
********************************************************************/
INLINE mUINT_16 mHostGetResetStatus(void)
{
    return (mHBIgetHostIntrStatus());
}

/*******************************************************************
*                                                                  
*  NAME:        mHostGetAtMode
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to retrieve AT mode register value.
*
*  RETURNS:     mUINT_16
*
********************************************************************/
INLINE mUINT_16 mHostGetAtMode (void)
{
    return (mHBIgetAtMode());
}

INLINE mUINT_8 mHostUseDefaultCfgSrc (void)
{
    return 0;
}



/*******************************************************************
*
*  NAME:        mHostSetBitAtMode
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: API function to set AT mode register 
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostSetBitAtMode(mUINT_16 bits)
{
   mHBIsetBitAtMode(bits);
}

/*******************************************************************
*
*  NAME:        mHostClrBitAtMode
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: API function to clear bits in AT mode register 
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostClrBitAtMode (mUINT_16 bits)
{
   mHBIclrBitAtMode(bits);
}

/*******************************************************************
*																   
*  NAME:        mHostSetAtError 	 											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  mUINT_16 error   											   
*																   
*  DESCRIPTION: API function to set bit or bits in the AT error reg (1501h)
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
INLINE void mHostSetAtError(mINT_16 error)
{
    mHBIsetError(error);    // Errors 
}

/*******************************************************************
*																   
*  NAME:        mHostSetAltAtError 	 											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  mUINT_16 error   											   
*																   
*  DESCRIPTION: API function to set bit or bits in the Alternate AT error reg (4A22)
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
INLINE void mHostSetAltAtError(mUINT_16 error)
{
    mHBIsetAltAtError(error);    // Errors 
}

/*******************************************************************
*																   
*  NAME:        mHostGetFdmaActivated
*
*  FILENAME:    mHBI.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: HBI function to get the First Dma Auto-Activate FIS 
*
*  RETURNS:     None
*
********************************************************************/
INLINE mtBOOLEAN mHostGetFdmaActivated(void)
{
#if (mNCQ_OP == mENABLE ) 
    return mHostStatus.sataMode.bits.autoFdmaActivated;
#else
    return mFALSE;
#endif
}

/*******************************************************************
*																   
*  NAME:        mHostSetFdmaActivateDis
*
*  FILENAME:    mHOST.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: API function to set ESATA configuration
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostSetFdmaActivateDis(mtBOOLEAN val)
{
#if (mNCQ_OP == mENABLE)
    mHostStatus.sataMode.bits.autoFdmaActivated = val;
    mHBIsetFdmaActivateDis(val);
#endif    
}


/*******************************************************************
*																   
*  NAME:        mHostReset    												   
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to reset the ATA  host bus interface.   
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostReset(void)
{
    mHBIreset();
}


/*******************************************************************
*																   
*  NAME:        mHostIntrSrcInit/En/Dis
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  type mUINT_8 intr
*
*  DESCRIPTION: API function to clear the bits in HBI host interrupt  
*                   mask marked by the 'intr' parameter (The negated 
*                  'intr' parameter is AND'd into host interrupt mask
*                   register).
*
*  RETURNS:     None
*
********************************************************************/
INLINE  void mHostIntrSrcInit(mUINT_16 intr) 
{
    mUINT_32    savedCPSR;

    // Step 1. Save state of IRQ flag or CPSR
    #ifdef __ghs__
    savedCPSR = __GETSR();
    #else      
    __asm
    {
        MRS savedCPSR, CPSR
    }
    #endif    
    mDISABLE_IRQ(); // Disable IRQ before entering critical region.
    
    rHBI.hostIntMask.all = ~(intr); // Step 3. Read-Modify-Write the mask register while IRQ is disabled

    // Step 4. Restore state of IRQ flag or CPSR
    #ifdef __ghs__
    __RIR (savedCPSR);
    #else
    __asm
    {
        MSR       CPSR_c, savedCPSR
    }
    #endif
}

INLINE  void mHostIntrSrcEn(mUINT_16 intr) 
{
    mUINT_32    savedCPSR;

    // Step 1. Save state of IRQ flag or CPSR
    #ifdef __ghs__
    savedCPSR = __GETSR();
    #else      
    __asm
    {
        MRS savedCPSR, CPSR
    }
    #endif    
    mDISABLE_IRQ(); // Disable IRQ before entering critical region.

    rHBI.hostIntMask.all &= ~(intr); // Step 3. Read-Modify-Write the mask register while IRQ is disabled

    // Step 4. Restore state of IRQ flag or CPSR
    #ifdef __ghs__
    __RIR (savedCPSR);
    #else
    __asm
    {
        MSR       CPSR_c, savedCPSR
    }
    #endif
}

INLINE  void mHostIntrSrcDis(mUINT_16 intr) 
{
    mUINT_32    savedCPSR;

    // Step 1. Save state of IRQ flag or CPSR
    #ifdef __ghs__
    savedCPSR = __GETSR();
    #else      
    __asm
    {
        MRS savedCPSR, CPSR
    }
    #endif    
    mDISABLE_IRQ(); // Disable IRQ before entering critical region.

    rHBI.hostIntMask.all |= intr; // Step 3. Read-Modify-Write the mask register while IRQ is disabled

    // Step 4. Restore state of IRQ flag or CPSR
    #ifdef __ghs__
    __RIR (savedCPSR);
    #else
    __asm
    {
        MSR       CPSR_c, savedCPSR
    }
    #endif
}


/*******************************************************************
*																   
*  NAME:        mHostSetAutoReadCntl    												   
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: API function to load the HBI Auto Read Control 
*               register with the contents of the 'val' parameter.    
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostSetAutoReadCntl(mUINT_16 val)  
{
    mHBIsetAutoReadCntl(val);
}

/*******************************************************************
*																   
*  NAME:        mHostGetAutoReadCntl    												   
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to return HBI Auto Read Control 
*               register.    
*
*  RETURNS:     Auto read setting.
*
********************************************************************/
INLINE mUINT_16 mHostGetAutoReadCntl(void)  
{
    return mHBIgetAutoReadCntl();
}

/*******************************************************************
*																   
*  NAME:        mHostSetHdPerCyl    												   
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  type mUINT_8 val
*
*  DESCRIPTION: API function to load the HBI Host head per cylinder  
*               register with the contents of the 'val' parameter.    
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostSetHdPerCyl(mUINT_8 val)   
{
    mHBIsetHdPerCyl(val);
}

/*******************************************************************
*																   
*  NAME:        mHostSetSecPerTrk    												   
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  type mUINT_8 val
*
*  DESCRIPTION: API function to load the HBI host sector per track  
*               register with the contents of the 'val' parameter.    
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostSetSecPerTrk(mUINT_8 val)  
{
    mHBIsetSecPerTrk(val);
}



/*******************************************************************
*																   
*  NAME:        mHostSetSeqRdLbaMode   												   
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to set sequential read LBA mode.
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostSetSeqRdLbaMode(void) 
{
    mHBIsetSeqRdLbaMode();
}

/*******************************************************************
*																   
*  NAME:        mHostSetSeqWrLbaMode   												   
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to set sequential write LBA mode.
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostSetSeqWrLbaMode(void) 
{
    mHBIsetSeqWrLbaMode();
}

/*******************************************************************
*																   
*  NAME:        mHostClrHBIreset    												   
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to clear reset of HBI block.
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostClrHBIreset(void)
{
    mHBIclrHBIreset();      // clear HBI reset
}


/*******************************************************************
*																   
*  NAME:        mHostSetBufferSegSel
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: API function to load the HBI config register with
*               the contents of the 'val' parameter.    
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostSetBufferSegSel(mUINT_16 val) 
{
    mHBIsetHostBufferSegSel(val);
}
/*******************************************************************
*																   
*  NAME:        mHostSetESATAconfig
*
*  FILENAME:    mHOST.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: API function to set ESATA configuration
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostSetESATAconfig(mUINT_16 bits)
{
    mHBISetBitESATAconfig(bits);
}


/*******************************************************************
*								  							   
*  NAME:       mHostInitPhyTunningControl
*
*  FILENAME:    mHOST.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: API function to set Phy Tunning Control
*
*  RETURNS:     TM flow status
*
********************************************************************/
INLINE void mHostInitPhyTunningControl(mUINT_16 val)
{
    mHBIinitPhyTunningControl(val);
}

/*******************************************************************
*								  							   
*  NAME:       mHostGetTMflowStatus
*
*  FILENAME:    mHOST.c
*
*  PARAMETERS:  void
*
*  DESCRIPTION: API function to get TM flow status
*
*  RETURNS:     TM flow status
*
********************************************************************/
INLINE mUINT_16 mHostGetTMflowStatus(void)
{
    return (mHostGetTMflowIntrStatus());
}

/*******************************************************************
*																   
*  NAME:        mHostGetESATAflowPowerResetControl
*
*  FILENAME:    mHOST.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: API function to get ESATA configuration
*
*  RETURNS:     None
*
********************************************************************/
INLINE mUINT_16 mHostGetESATAflowPwrRstCntl(void)
{
    return (mHBIgetESATAflowPowerResetCntl());
}


/*******************************************************************
*																   
*  NAME:        mHostClrBitESATAconfig
*
*  FILENAME:    mHOST.c
*
*  PARAMETERS:  mUINT_16
*
*  DESCRIPTION: API function to set ESATA configuration
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mHostClrBitESATAconfig(mUINT_16 bits)
{
    mHBIClrBitESATAconfig(bits);
}

/*******************************************************************
*																   
*  NAME:        mHostSetFISsize
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
INLINE void mHostSetFISsize(mUINT_16 val)
{
    mHBIsetFISsize(val);
}

/*******************************************************************
*																   
*  NAME:        mHostSetTMforceRerr
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
INLINE void mHostSetTMforceRerr(void)
{
    mHBIsetTMforceRerr();
}

/*******************************************************************
*																   
*  NAME:        mHostGettFISRxtype
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to get FIS Received type
*
*  RETURNS:     None
*
********************************************************************/
INLINE mUINT_16 mHostGetRxFISType (void)
{
    return (mHBIgetRxFIStype());
}

/*******************************************************************
*																   
*  NAME:        mHostGettFISTxtype
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to get FIS Received type
*
*  RETURNS:     None
*
********************************************************************/
INLINE mUINT_16 mHostGetTxFISType (void)
{
    return (mHBIgetTxFIStype());
}

INLINE mUINT_16 mHostGetRxFisTypeErrLog (void)
{
    return (mHBIgetRxFisTypeErrLog());
}

INLINE mUINT_16 mHostGetTxFisTypeErrLog (void)
{
    return (mHBIgetTxFisTypeErrLog());
}

/*******************************************************************
*																   
*  NAME:   	    mHostGetTMflowIntrStatus											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  None   											   
*																   
*  DESCRIPTION: API function to get value of TM flow intr status reg (0x4AB0)
*																   
*  RETURNS:     mUINT_16      											   
*	
********************************************************************/
INLINE mUINT_16 mHostGetTMflowIntrStatus (void)
{
    return (mHBIgetTMflowIntrStatus());
}


/*******************************************************************
*																   
*  NAME:   	    mHostGetTMflowIntrStatus											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  None   											   
*																   
*  DESCRIPTION: API function to get value of TM flow intr status reg (0x4AB0)
*																   
*  RETURNS:     mUINT_16      											   
*	
********************************************************************/
INLINE void mHostClrTMflowIntrStatus (mUINT_16 val)
{
    mHBIclrTMflowIntrStatus (val);
}

/*******************************************************************
*																   
*  NAME:   	    mHosClrEsataErrIntrStatus 
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  None   											   
*																   
*  DESCRIPTION: API function to get value of TM flow intr status reg (0x4AB0)
*																   
*  RETURNS:     mUINT_16      											   
*	
********************************************************************/
INLINE void mHostClrEsataErrIntrStatus (mUINT_16 val)
{
    mHBIclrEsataErrIntrStatus (val);
}

//#if (mDAVINCI_FAMILY == mENABLE)
//INLINE void mHostClrTmStatusHi (mUINT_16 val)
//{
//    mHBIclrTmStatusHi(val);
//}
//#endif // (mSOC == m8925)

#if (mTHUMB_MODE == mENABLE)
#pragma thumb
#endif

/*******************************************************************
*																   
*  NAME:   	    mHostinitNCQparams											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  pointer type mtPARAM_ECU_PAGE     											   
*																   
*  DESCRIPTION: API function to setup NCQ block initial values
*               from a mPARAM page.
*																   
*  RETURNS:     None
*	
********************************************************************/
void mHostInitTMparams(mtPARAM_HBI_PAGE *pmParamPage)
{

    mtPARAM_HBI_PARAMS   *pParams;
    
    pParams = &(pmParamPage->params);

    // Clear all Interrupts
    mHostClrEsataErrIntrStatus(0xFFFF);
    mHostClrTMflowIntrStatus(0xFFFF);

    // Clear all Disparity Count and Code Violation Count
    mHostClrDisparityCnt();
    mHostClrCodeViolationCnt();

    mHostSetBlkXferCnt(0);   

    mHostSetFISsize(mMAX_FIS_SIZE);
    mHostSetTMfifoThreshold(0xf);    // Set Threshold to max   

    mHostSetResetTxFisDone();           // Enable H/W to reset TxFISDone at every FIS
    mHostSetBitMsgLogConfg(0x00);       // Disable all Message Log R4A60
    #if (mNCQ_OP == mENABLE)
    mHostSetQcmdAbort();                // Abort all Qs
    mHostSetBitMsgLogCntl(0xffc0);      // Disable Message Log Control Status R4B4A[6] Kim - need to add
    mHostClrTmStatusLow(0xFFFF);        // Clear all Errors
    mHostClrTmStatusHi(0xFFFF);         // Clear all Errors
    // Clear Qram
    {
        volatile mUINT_32 *pHdcReg;
        mUINT_32 i;

        pHdcReg = (mUINT_32 *)(0x1c004E00);
        for (i =0; i < 128 ; i ++)
        {
            *pHdcReg = 0;
            pHdcReg++;
        }
    }
    #else // NOT - (mNCQ_OP == mENABLE)
    mHostSetBitMsgLogCntl(0xffc0);          // Message Log Control Status R4B4A[6] Kim - need to add
    #endif
//Add-    mHostSetSataMiscCntl(0xf00);   // R4ABC
//Add-    mHostSetSataMiscCntl(0xc00);   // R4ABC
    mHostResetCmdxh();        // Cmd Execution History R4AFC[7:6]
    mHostResetCrsb();         // Cmd Execution History R4AF8[15:14]
    mHostResetFlowCntl();     // Reset TxFlow, Qcntl
    mToggleNcqPhaseReset();  // Has to be in the data FIS
    mHostSetEsataErrIntrSrc(pParams->esataErrint);  
    mHostSetTMflowIntrSrc(pParams->tmIntsrc);           
    mHostSetESATAconfig(pParams->esataCnfg);
    mHostClrIntrStatus(0xffff);                 // clear all Interrupts
 //   mHostIntrSrcInit(pParams->intrSrcs);
 //   mHostReset();  
 //   mHostSetConfgCntrl(pParams->devCntl) ;       

    
}

#if (mTHUMB_MODE == mENABLE)
#pragma arm
#endif



/*******************************************************************
*																   
*  NAME:        mHostSetEsataErrIntrSrc / mHostGetEsataErrIntrSrc
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  type mUINT_16 intr
*
*  DESCRIPTION: API function to set the bits in ESATA Error Interrupt 
*                   Mask 
*
*  RETURNS:     None
*
********************************************************************/
INLINE  void mHostSetEsataErrIntrSrc(mUINT_16 val) 
{
    mHBIsetEsataErrIntrSrc(val);
}

INLINE  mUINT_16 mHostGetEsataErrIntrSrc(void) 
{
    return mHBIgetEsataErrIntrSrc();
}

/*******************************************************************
*																   
*  NAME:        mHostSetTMflowIntrSrc / mHostGetTMflowIntrSrc
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  type mUINT_16 intr
*
*  DESCRIPTION: API function to set the bits in ESATA Transport Manager
*               Interrupt Mask
*
*  RETURNS:     None
*
********************************************************************/
INLINE  void mHostSetTMflowIntrSrc(mUINT_16 val) 
{
    mHBIsetTMflowIntrSrc(val);
}

INLINE  mUINT_16 mHostGetTMflowIntrSrc(void) 
{
    return mHBIgetTMflowIntrSrc();
}

/*******************************************************************
*																   
*  NAME:        mHostSetTMfifoThreshold
*
*  FILENAME:    mHost.c
*
*  PARAMETERS:  type mUINT_8 
*
*  DESCRIPTION: API function to set the TM fifo threshold
*
*  RETURNS:     None
*
********************************************************************/
INLINE  void mHostSetTMfifoThreshold(mUINT_16 val) 
{
    mHBISetTMfifoThreshold(val);
}



#ifdef __ghs__
  #pragma ghs section text   = ".ctlr_code_dram"
  #pragma ghs section rodata = ".ctlr_rodata_dram"
  #pragma ghs section data   = ".ctlr_data_dram"
  #pragma ghs section bss    = ".ctlr_bss_dram"
#else
  #pragma arm section code   = "ctlr_code_dram"
  #pragma arm section rodata = "ctlr_data_dram"
  #pragma arm section rwdata = "ctlr_data_dram"
  #pragma arm section zidata = "ctlr_data_dram"
#endif

/*******************************************************************
*																   
*  NAME:   	    mHostInitRelease 											   
*																   
*  FILENAME:    mHost.c 											   
*																   
*  PARAMETERS:  number of buffer sectors, number of host sectors, transfer direction    											   , 
*															   
*  DESCRIPTION: API function to setup HDC to transfer to/from Host
*																   
*  RETURNS:     None 
*
*  date         by              description 
*  09/14/00     Lau Nguyen      Initial release     											   
*	
********************************************************************/
void mHostInitRelease (mINT_NATIVE cachedSectors, mINT_NATIVE hostSectors,mUINT_NATIVE writeDir)
{
#if 0
    mUINT_16   targHostSeg;

#if (VG_REV_2_0 != mENABLE) 
    mUINT_16 temp1,temp2,temp3; 
#endif

    targHostSeg = mBfrHostSegStreamChk();
    mBfrDiskSegSecCntSel(8);    // disk connect streaming first
    mBfrHostSegSecCntInit(targHostSeg,cachedSectors);  
    mHostClrIntrStatus(m_tHBI_INT_bits_fwXferDone);

#if (VG_REV_2_0 != mENABLE) 
//Kim - this is a temporary workaround for VanGogh rev 1.0 only
// for now just check in and worry about the conditional later!!
    temp1 = *(volatile mUINT_16 *)0x1c004A0C; 
    temp2 = *(volatile mUINT_16 *)0x1c004A1C; 
    temp3 = *(volatile mUINT_16 *)0x1c004A1A; 

    if (!writeDir)
    {
        *(volatile mUINT_16 *)0x1c004A0A = hostSectors;
        *(volatile mUINT_16 *)0x1c004A46 = hostSectors;

        *(volatile mUINT_16 *)0x1c004A0C |= 0x400;
        *(volatile mUINT_16 *)0x1c004A1C = 1;
        *(volatile mUINT_16 *)0x1c004A1A = (0x80) * hostSectors;
    }
#endif

    /* setup the Host and Buffer to transfer numberOfSectors to/from Host */
    mHostSetCxsbFwReqNonQDataXfer(hostSectors,targHostSeg,writeDir,mFALSE); 

    while (!(mHostGetIntrStatus() & m_tHBI_INT_bits_fwXferDone))
    {
        if (mSystemState.curState != mPOWER_UP_STATE) return;
        mKrnlWaitForEvents(0); // let others have the CPU while I am waiting
    }
    mHostClrIntrStatus(m_tHBI_INT_bits_fwXferDone);

#if (VG_REV_2_0 != mENABLE) 
//Kim - this is a temporary workaround for VanGogh rev 1.0 only
// for now just check in and worry about the conditional later!!
    *(volatile mUINT_16 *)0x1c004A0C = temp1;
    *(volatile mUINT_16 *)0x1c004A1C = temp2;
    *(volatile mUINT_16 *)0x1c004A1A = temp3;
#endif
#endif
}

/*******************************************************************
*                                                                  
*  NAME:        mHostContinueRelease                                               
*                                                                  
*  FILENAME:    mHost.c                                                
*                                                                  
*  PARAMETERS:  number of host sectors, transfer direction                                                   , 
*                                                              
*  DESCRIPTION: API function to setup HDC to transfer to/from Host
*                                                                  
*  RETURNS:     None 
*
*  date         by              description 
*  09/14/00     Lau Nguyen      Initial release                                                    
*   
********************************************************************/
// no playing around with buffer hot sectors
void mHostContinueRelease ( mUINT_NATIVE hostSectors,mUINT_NATIVE writeDir)
{
}

#if (mTHUMB_MODE == mENABLE)
#pragma thumb
#endif

// Kim - need to revisit for 8925
/*******************************************************************
*
*  NAME:        mHostManualFISxfer()
*
*  FILENAME:    ATCmds.c
*
*  PARAMETERS:  pointer to mtCMDQ_ENTRY type
*
*  DESCRIPTION: In La Jolla, ECC byte transfer to host uses Manual mode
*
*
*  RETURNS:     None
*
*  OUTPUTS:     
*
********************************************************************/
void mHostManualFISxfer(mUINT_NATIVE writeDir)
{
#if 0
    rHBI.msgLogConfig.all = 0;  // R4A60

    // Clear writeDir and forceDMAxferEn bits
    mHostClrBitAtMode(m_tHOST_BUS_INTERFACE_ATmode0_bits_writeDir | m_tHOST_BUS_INTERFACE_ATmode0_bits_forceDMAxferEn);

    // Special test code, hackbink
    mHostSetSectorCount(0); // Host Sector count - should not have to do this in the future
    mHostSetBlkXferCnt(0);  // set Host block count

    // set up hbi
    mHostCrsbCmdResume(m_tHBI_CRSB_CNTL_STAT_bits_newIDresume);

    mHostSetFISsize(mLONG_FIS_SIZE);
    // setup manual transfer
    mHostSetESATAconfig(m_tHBI_ESATA_CONFIG_bits_manualFisFlowEn + m_tHBI_ESATA_CONFIG_bits_manualFisXferReq);
    mHostClrResetTxFisDone();    // Disable H/W to reset TxFISDone at every FIS
    rHBI.tmTxFISTypeLog.bits.rxFisDoneResetEn = 0;
    mHostClrTMflowIntrStatus(m_tHBI_TM_FLOW_INT_bits_TxFisDone);    
    if (writeDir) 
    {
        // start with empty buffer
        mBfrHostSegSecCntInit(0, 0);
        mHostSetBitAtMode(m_tHOST_BUS_INTERFACE_ATmode0_bits_writeDir);
        mHostSetUserFISword0L(0x005f); //  FIS opcode, direction, interrupt
        mHostSetUserFISword0H(0x0058); //  Start status,error
    }
    else  // For Read
    {
        mBfrHostSegSecCntInit(1, 1);
        mHostClrBitAtMode(m_tHOST_BUS_INTERFACE_ATmode0_bits_writeDir);
        mHostSetUserFISword0L(0x605f); //  FIS opcode, direction, interrupt
        mHostSetUserFISword0H(0x0058); //  Start status,error
    }
    mHostSetUserFISword1L(mHostGetSectorNum()); //  sector number
    // mHostSetUserFISword1H(); Don't have to set Cyl/Hd
    mHostSetUserFISword2L(0);
    mHostSetUserFISword2H(0);
    mHostSetUserFISword3L(0);                  // sector count
    if (!writeDir)  
    {
        mHostSetUserFISword3H(0x5000); // Set End status, and done
    }
    else
    {
        mHostSetUserFISword3H(0xD000); // Set End status, and done
    }
    mHostSetUserFISword4L(2*mLONG_HOST_SIZE);
    mHostSetManualFlowControl(0xA5F);  // transfer PIO FIS 
    while (! (mHostGetTMflowIntrStatus() & m_tHBI_TM_FLOW_INT_bits_TxFisDone))
    {
        if (mSystemState.curState != mPOWER_UP_STATE)
            return;
        mKrnlWaitForEvents(0);              // let others have the CPU 
    }
    mHostClrTMflowIntrStatus(m_tHBI_TM_FLOW_INT_bits_TxFisDone);    

    mHostSetSectorCount(1); // Host Sector count - should not have to do this in the future
    mHostSetBlkXferCnt(1);  // set Host block count
    mBfrSetHostSectorSize(mLONG_HOST_SIZE);    
    // Assert HOT_BYTE_CNTR_RST to initialize the new host sector size (mLONG_HOST_SIZE).
    mBfrHostByteCntRst();
    // setup manual transfer
    mHostSetESATAconfig(m_tHBI_ESATA_CONFIG_bits_manualFisFlowEn + m_tHBI_ESATA_CONFIG_bits_manualFisXferReq);
    mHostSetManualFlowControl(0x346); // Transfer data
    while (!(mHostGetTMflowIntrStatus() & m_tHBI_TM_FLOW_INT_bits_TxFisDone))
    {
        if (mSystemState.curState != mPOWER_UP_STATE)
            return;
        mKrnlWaitForEvents(0);              // let others have the CPU 
    }
    mHostClrTMflowIntrStatus(m_tHBI_TM_FLOW_INT_bits_TxFisDone);    

    mHostSetESATAflowPwrRstCntl(m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_TxFlowRst);
    mHostClrESATAflowPwrRstCntl(m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_TxFlowRst);
    mHostClrAtStatus(mDRQ);

    mHostClrBitESATAconfig(m_tHBI_ESATA_CONFIG_bits_manualFisFlowEn + m_tHBI_ESATA_CONFIG_bits_manualFisXferReq);
    mBfrSetHostSectorSize(mNORMAL_HOST_SIZE);  
    mHostSetResetTxFisDone();    // Enable H/W to reset TxFISDone at every FIS

    // restore HBI
    mHostSetFISsize(mMAX_FIS_SIZE);
    
    // Assert HOT_BYTE_CNTR_RST to initialize the new host sector size (mLONG_HOST_SIZE).
    mBfrHostByteCntRst();
#endif	
}

#ifdef __ghs__
    #pragma ghs section
#else  
    #pragma arm section
#endif    

#pragma arm

