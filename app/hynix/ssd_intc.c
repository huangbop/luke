/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "HEAD.H"

INT32U OsEnterSum;
INT32U MainIRQIntEn;


/*******************************************************************
*																   
*  NAME:        HBIintrHandler												   
*																   
*  FILENAME:    isrs.c 											   
*																   
*  PARAMETERS:  None    											   
*																   
*  DESCRIPTION: Responds to HBI disk interrupts and sends events to RTOS.
*																   
*  RETURNS:     None      											   
*	   
*  DATE         BY              DESCRIPTION 
*  03/06/02     Lau Nguyen      Initial Release
********************************************************************/
/*----------------------------------------------------------------------------
Private functions:
---------------------------------------------------------------------------*/
static void HBIintrHandler(void)
{
  mUINT_16 hostIntStat0;
  mUINT_16 eSataErrIntStatus;
  mUINT_16 tmStatusLow;
  mUINT_16 tmStatusHi;


  tmStatusLow = mHostGetTmStatusLow();
  tmStatusHi = mHostGetTmStatusHi();

  hostIntStat0 = mHostGetIntrStatus() &(~(mHostGetIntrDisable()));
  eSataErrIntStatus = (mHostGetEsataErrIntStatus() &(~(mHostGetEsataErrIntrSrc())));

  if(hostIntStat0 &(m_tHBI_INT_bits_hardReset + m_tHBI_INT_bits_softReset))
  {
// Soft Reset comes by 2 regFIS which in turn causes 2 interrupt
// Don't do anything, wait for SRST deassert from the second FIS before handling the interrupt.
    while(mHBIgetDeviceControl() &m_tHOST_BUS_INTERFACE_devCntrl_bits_srst)
      ;

    mSystemState.curState = mRESET_STATE;
//mKrnlIntrSetEvents(mSERIAL_TASK_RST_EVENT);
    hostIntStat0 &= ~(m_tHBI_INT_bits_hardReset + m_tHBI_INT_bits_softReset);
    mHostClrIntrStatus(m_tHBI_INT_bits_hardReset + m_tHBI_INT_bits_softReset);
    hostIntStat0 &= ~(0xffff); // clear all interrupt when ComReset or SoftReset comes
    mToggleTxFlowReset();
    mToggleCmdExeReset();
    mToggleCmdExeReset();
    mToggleCxsbReset();
    mToggleNcqPhaseReset();
    mHostClrIntrStatus(0xffff);
    mHostIntrSrcDis(0xffff); // Mask all interrupt

//The reinit code for Memoright own Code  
/*
BSemNATACMD = 0;

InitCmdQ();
BufferInit();
mCacheInit();
*/
    return ;
  }
#if (mNCQ_OP == mENABLE)
//Add the code for NCQ function 
#if 0
  if(hostIntStat0 &m_tHBI_INT_bits_cmdRcvdErr)
  {
    hostIntStat0Copy = hostIntStat0;
    if(tmStatusLow &QCMD_NON_EXE_ERR_BITS)
    {
// if not waiting for Readlog10 then let serTask handle the report to host
// H/W hold on to the bus in this case
      mHostSetBitAtMode(m_tHOST_BUS_INTERFACE_ATmode0_bits_ncqAutoRelDis);
// if not waiting for Readlog10 then let serTask handle the report to host
// otherwise let the newCmd handle.
//if (!ncqCmdErr)
      if(!waitForReadLog10)
      {
        mTagErr = mTRUE;
//mOutf("ncqCmdErr\n");
        ncqCmdErr = mABORTED_CMND;
        waitForReadLog10 = mTRUE;
        mSystemState.curState = mQCMD_NON_EXE_ERROR_STATE;
        mKrnlIntrSetEvents(mSERIAL_TASK_RST_EVENT);
        mHostClrIntrStatus(m_tHBI_INT_bits_nonAceCmd);
        hostIntStat0 &= ~(m_tHBI_INT_bits_nonAceCmd);
      }

      if(mHostGetIntrDisable() &m_tHBI_INT_bits_nonAceCmd)
      {
// allowing command to go through if it's a ReadLog 10
        hostIntStat0 |= m_tHBI_INT_bits_nonAceCmd;
      }
    }

    tmStatusLow &= ~QCMD_NON_EXE_ERR_BITS;
    mHostClrTmStatusLow(QCMD_NON_EXE_ERR_BITS);
    hostIntStat0 &= ~(m_tHBI_INT_bits_cmdRcvdErr);
    mHostClrIntrStatus(m_tHBI_INT_bits_cmdRcvdErr);
  }
#endif 
#endif 

// **** handle newCmd
  if(hostIntStat0 &m_tHBI_INT_bits_nonAceCmd)
//if (hostIntStat0 & (m_tHBI_INT_bits_newCmd | m_tHBI_INT_bits_nonAceCmd))
  {
    BSemNATACMD++;
    mHostClrIntrStatus(m_tHBI_INT_bits_newCmd | m_tHBI_INT_bits_nonAceCmd); // for non-NCQ
    mHostIntrSrcDis(m_tHBI_INT_bits_nonAceCmd);

  }

#if CFG_XFERFINFUN > 0
// Handle xfer_done interrupt.
  if(hostIntStat0 &m_tHBI_INT_bits_fwXferDone)
  {
    if ((mHostGetCxsbCntl() & m_tHBI_CXSB_CNTL_STAT_bits_emptyDet) && (mHBIgetBlkXferCnt() == 0) && (!(mHBIgetMiscStatus() & m_tHOST_BUS_INTERFACE_hostMiscStatus_bits_xferActive)) )
    {
      BSemCurXferFinCnt++;
	  mHostClrIntrStatus(m_tHBI_INT_bits_fwXferDone);
	  mHostIntrSrcDis(m_tHBI_INT_bits_fwXferDone);
    }
	else
	{
	  mHostClrIntrStatus(m_tHBI_INT_bits_fwXferDone);
	}    
  }
#endif


  if(hostIntStat0 &m_tHBI_INT_bits_cmdExecErr)
  {
// Just testing for FIFO error case or Host Parity Error
    if(hostIntStat0 &m_tHBI_INT_bits_esataErr)
    {
      if(eSataErrIntStatus)
      {
//if (mSataIntrErrHandler(eSataErrIntStatus))
        if(0)
        {
// Error is in Data FIS
          mSystemState.curState = mINTF_ERROR_STATE;
//mKrnlIntrSetEvents(mSERIAL_TASK_RST_EVENT);
// Error during data FIS - clear CXSB before clearing stopXfer due to Upack code may have more to do.
          mToggleCxsbReset();
          mHostResetFlowCntl();
        }
      }
      mHostClrTmStatusLow(0xFFFF);
      mHostClrTmStatusHi(0xFFFF);
      mHostClrEsataErrIntrStatus(0xffff);
      hostIntStat0 &= ~(m_tHBI_INT_bits_esataErr | m_tHBI_INT_bits_cmdRcvdErr | m_tHBI_INT_bits_cmdExecErr);
      mHostClrIntrStatus(m_tHBI_INT_bits_esataErr | m_tHBI_INT_bits_cmdProcessErr | m_tHBI_INT_bits_cmdRcvdErr | m_tHBI_INT_bits_cmdExecErr);
    }
    else
    {
// error is due to parity errors, last command is done due to us setting 
// override bits already, just clear these interrupt so that 
// next CXSB can be executed.  Don't need to report if this is the case
      mHostClrTmStatusLow(0xFFFF);
      mHostClrTmStatusHi(0xFFFF);
      mHostClrIntrStatus(m_tHBI_INT_bits_cmdProcessErr | m_tHBI_INT_bits_cmdRcvdErr | m_tHBI_INT_bits_cmdExecErr);
    }
  }

}



/*********************************************************************************************************
** Function Name         : IntcIsrFIQ
** Function Describe     : FIQ Interrupt routine
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           : IntcIntrEntryTable
********************************************************************************************************/
void IntcIsrFIQ(void)ALWAYS_INLINE;
void IntcIsrFIQ(void)
{
//TO DO Add the FIQ handler function in here
}

/*********************************************************************************************************
** Function Name         : IntcIsrIRQ
** Function Describe     : IRQ Interrupt routine
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
void IntcIsrIRQ(void)ALWAYS_INLINE;
void IntcIsrIRQ(void)
{
  INT32U intrStat;

// determine which isrs to handle
// if HDC interrupt

#define m_tCPU_INTR_bits_fcInt   m_tCPU_INTR_bits_servoInt 
  if(mCPUintrStatus() &m_tCPU_INTR_bits_fcInt)
// if we got FC interrupt  
  {
    //mCPUintrDis(m_tCPU_INTR_bits_fcInt);
//To Do : Add the FC Int function 
mCPUClrIntrStatus(m_tCPU_INTR_bits_fcInt);
	FC_Seq_Done();


    
	//mCPUintrEn(m_tCPU_INTR_bits_fcInt);

  }

  if(mHDCgetIntrStatus() &m_tHDC_INT_bits_mpu)
  {
    mSHOULD_NOT_GET_HERE();
  }

  if((mHDCgetIntrStatus() &(~(mHDCgetIntrMask()))) && (mHDCgetIntrStatus() &m_tHDC_INT_bits_esata))
  {
    HBIintrHandler();
  }





  intrStat = mSFRintrStatus();
  mSFRintrStatusClr(intrStat);
//To Do : Add the function for other Interrupt

}

/*********************************************************************************************************
** Function Name         : FIQ_Handler
** Function Describe     : FIQ Interrupt handler
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           : IntcIsrFIQ
********************************************************************************************************/
void __irq FIQ_Handler(void)
{
  IntcIsrFIQ();
}

/*********************************************************************************************************
** Function Name         : IRQ_Handler
** Function Describe     : IRQ Interrupt handler
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           : IntcIsrIRQ
********************************************************************************************************/
void __irq IRQ_Handler(void)
{
  IntcIsrIRQ();
}

/*********************************************************************************************************
** Function Name         : IntcEnableIntr
** Function Describe     : Enable one of the Interrupt
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
void IntcEnableIntr(INT32U bitMask)
{
  MainIRQIntEn |= bitMask;

}

/*********************************************************************************************************
** Function Name         : IntcDisableIntr
** Function Describe     : Disable one of the Interrupt
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
void IntcDisableIntr(INT32U bitMask)
{
  MainIRQIntEn &= (~bitMask);

}

/*********************************************************************************************************
** Function Name         : IntcDisableAllIntrs
** Function Describe     : Disable all of the Interrupt
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
void IntcDisableAllIntrs(void)
{
}
/*********************************************************************************************************
** Function Name         : IntcClearIntr
** Function Describe     : Clear one of the Interrupt
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
void IntcClearIntr(INT8U bChnlNum)ALWAYS_INLINE;
void IntcClearIntr(INT8U bChnlNum)
{
}
/*********************************************************************************************************
** Function Name         : IntcClearAllIntrs
** Function Describe     : Clear all of the Interrupt
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
void IntcClearAllIntrs(void)
{
}




/*********************************************************************************************************
** Function Name         : InitIntc
** Function Describe     : Open the MainIRQ
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
void InitIntc(void)
{
  mCPUClrIntrStatus(m_tCPU_INTR_bits_hdcInt | m_tCPU_INTR_bits_sataIn);
  mHDCClearIntrStatus();
  mCPUintrEn(m_tCPU_INTR_bits_hdcInt|m_tCPU_INTR_bits_servoInt); // Enable SATA interrupt through HDC here 
  mHDCintrEn(m_tHDC_INT_bits_esata + m_tHDC_INT_bits_mpu);

//Close all Timer
  rTimer.counter0.bits.countEnable = 0;
  rTimer.counter1.bits.countEnable = 0;
  rTimer.counter2.bits.countEnable = 0;
  rTimer.counter3.bits.countEnable = 0;
  rTimer.counter4.bits.countEnable = 0;

  sysCPUSysModeEnaIRQ();
}

/*******************************************************************************************************
End Of File
       ********************************************************************************************************/
