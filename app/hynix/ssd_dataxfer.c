/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "HEAD.H"


/*********************************************************************************************************
** Function Name         : mBfrLLcurrLink
** Function Describe     : Process Disk Command
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void mBfrLLcurrLink(mUINT_NATIVE segNum, mUINT_NATIVE currLink)
{
  switch(segNum)
  {
    case 0:
    mBMsetHostSeg0LnkLstPtr(currLink);
    break;
    case 1:
    mBMsetHostSeg1LnkLstPtr(currLink);
    break;
    case 2:
    mBMsetHostSeg2LnkLstPtr(currLink);
    break;
    case 3:
    mBMsetHostSeg3LnkLstPtr(currLink);
    break;
    case 4:
    mBMsetHostSeg4LnkLstPtr(currLink);
    break;
    case 5:
    mBMsetHostSeg5LnkLstPtr(currLink);
    break;
    case 6:
    mBMsetHostSeg6LnkLstPtr(currLink);
    break;
    case 7:
    mBMsetHostSeg7LnkLstPtr(currLink);
    break;
    default:
    mSHOULD_NOT_GET_HERE();
    break;
  }
}




/*********************************************************************************************************
** Function Name         : CommandXfer
** Function Describe     : Xfer the CXSB Link
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void mBfrSegAdrsOffsetInit(mUINT_NATIVE segNum, mUINT_NATIVE offset)
{

  switch(segNum)
  {
    case 0:
    mBMsetHostSeg0Ptr(offset);
    break;
    case 1:
    mBMsetHostSeg1Ptr(offset);
    break;
    case 2:
    mBMsetHostSeg2Ptr(offset);
    break;
    case 3:
    mBMsetHostSeg3Ptr(offset);
    break;
    case 4:
    mBMsetHostSeg4Ptr(offset);
    break;
    case 5:
    mBMsetHostSeg5Ptr(offset);
    break;
    case 6:
    mBMsetHostSeg6Ptr(offset);
    break;
    case 7:
    mBMsetHostSeg7Ptr(offset);
    break;
    default:
    mSHOULD_NOT_GET_HERE();
    break;
  }
}


/*********************************************************************************************************
** Function Name         : CommandXfer
** Function Describe     : Xfer the CXSB Link
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void mBfrHostSegSecCntInit(mUINT_NATIVE segNum, mUINT_NATIVE value)
{
  switch(segNum)
  {
    case 0:
    mBMinitHS0SC(value);
    break;
    case 1:
    mBMinitHS1SC(value);
    break;
    case 2:
    mBMinitHS2SC(value);
    break;
    case 3:
    mBMinitHS3SC(value);
    break;
    case 4:
    mBMinitHS4SC(value);
    break;
    case 5:
    mBMinitHS5SC(value);
    break;
    case 6:
    mBMinitHS6SC(value);
    break;
    case 7:
    mBMinitHS7SC(value);
    break;
    default:
    mSHOULD_NOT_GET_HERE();
    break;
  }
}

/*********************************************************************************************************
** Function Name         : CommandDiskProcess
** Function Describe     : Process Disk Command
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOLEAN CommandDiskProcess(CMDQENTRY *pCurCmdEntry)
{

//Handler All RW Command
  if(pCurCmdEntry->CmdFlag.bits.WRCMD)
  {
//Write Command    
    return (CacheWriteOperation(pCurCmdEntry));
  }
  else
  {
//Read Command
    return (CacheReadOperation(pCurCmdEntry));
  }

  return SUCCESS;
}


/*********************************************************************************************************
** Function Name         : CommandExec
** Function Describe     : Exec the Command in the Command Link List
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CommandExec(void)
{
  CMDQENTRY *pCurCmdEntry;

  while(CmdQueueParam.pRcrdListHead)
  {
    pCurCmdEntry = CmdQueueParam.pRcrdListHead;

    if(pCurCmdEntry->CmdFlag.bits.DiskCmd)
    {
      if(FAIL == CommandDiskProcess(pCurCmdEntry))
      {
        return ;
      }
    }
    else
    {
      CommandNTDiskProcess(pCurCmdEntry);
      CmdQReturnToIdle(pCurCmdEntry);
    }

  }

}


/*********************************************************************************************************
** Function Name         : CommandXfer
** Function Describe     : Xfer the CXSB Link
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CommandXfer(void)
{
  CXSBLINK *pCxsbEntry;

  if(CmdQueueParam.cxsbWaitCnt)
  {
    pCxsbEntry = CmdQueueParam.pCxsbXferHead;

    while(pCxsbEntry)
    {

      if(pCxsbEntry->CxsbFlag.bits.ExecBit == FALSE)
      {

        if(pCxsbEntry->CxsbFlag.bits.NCQCmd == FALSE)
        {

        if(pCxsbEntry->CxsbFlag.bits.WRCMD)
        {
          mHostSetBitAtMode(m_tHOST_BUS_INTERFACE_ATmode0_bits_writeDir);
        }
        else
        {
          mHostClrBitAtMode(m_tHOST_BUS_INTERFACE_ATmode0_bits_writeDir);
        }


        mHostSetTaskFileReg(mTF_CYL_LOW_REG, pCxsbEntry->XferLen);
        if(pCxsbEntry->CxsbFlag.bits.WRCMD)
        {
          mHostSetTaskFileReg(mTF_CYL_HIGH_REG, 0x00);
        }
        else
        {
          mHostSetTaskFileReg(mTF_CYL_HIGH_REG, 0x80);
        }
        }

        mBMhostByteCntRst();
        mBfrLLcurrLink(pCxsbEntry->HSNum, pCxsbEntry->HSPtrNum);
        mBfrSegAdrsOffsetInit(pCxsbEntry->HSNum, pCxsbEntry->XferDDRByteAddr);
        mHBIsetHostBufferSegSel(pCxsbEntry->HSNum);


        mBMdiskSegSecCntSel(8);
        if(pCxsbEntry->CxsbFlag.bits.WRCMD)
        {
          mBfrHostSegSecCntInit(pCxsbEntry->HSNum, (0-pCxsbEntry->XferLen));
        }
        else
        {
          mBfrHostSegSecCntInit(pCxsbEntry->HSNum, pCxsbEntry->XferLen);
        }
#if CFG_XFERFINFUN > 0

        if(pCxsbEntry->CxsbFlag.bits.NCQCmd)
        {
          mHostSetCxsbFwReqQcmdDataXfer(pCxsbEntry->XferLen, pCxsbEntry->HSNum, pCxsbEntry->CxsbFlag.bits.WRCMD, pCxsbEntry->NCQTag, pCxsbEntry->CxsbFlag.bits.EndBit);
        }
        else
        {
          mHostSetCxsbFwReqNonQDataXfer(pCxsbEntry->XferLen, pCxsbEntry->HSNum, pCxsbEntry->CxsbFlag.bits.WRCMD, pCxsbEntry->CxsbFlag.bits.EndBit);
        }

#else 
        mHostClrIntrStatus(m_tHBI_INT_bits_fwXferDone);
        if(pCxsbEntry->CxsbFlag.bits.NCQCmd)
        {
          mHostSetCxsbFwReqQcmdDataXfer(pCxsbEntry->XferLen, pCxsbEntry->HSNum, pCxsbEntry->CxsbFlag.bits.WRCMD, pCxsbEntry->NCQTag, pCxsbEntry->CxsbFlag.bits.EndBit);
        }
        else
        {
          mHostSetCxsbFwReqNonQDataXfer(pCxsbEntry->XferLen, pCxsbEntry->HSNum, pCxsbEntry->CxsbFlag.bits.WRCMD, pCxsbEntry->CxsbFlag.bits.EndBit);
        }


        while(!(mHostGetIntrStatus() &m_tHBI_INT_bits_fwXferDone))
        {
          if(mSystemState.curState != mPOWER_UP_STATE)
          {
//return FAIL;
            return ;
          }
        }
        mHostClrIntrStatus(m_tHBI_INT_bits_fwXferDone);


        if(pCxsbEntry->CxsbFlag.bits.WRCMD)
        {
          BfrSSDParam.WRSSDXferPtr += pCxsbEntry->XferSSDCnt;
          BfrSSDParam.WRSSDXferPtr &= BFR_SSD_WRMASK;
          FCFlushOperation(pCxsbEntry);
        }
        else
        {
          BfrSSDParam.RDSSDXferPtr += pCxsbEntry->XferSSDCnt;
          BfrSSDParam.RDSSDXferPtr &= BFR_SSD_RDMASK;
          HSReadOperation(pCxsbEntry);
        }

        CxsbReturnToIdle(pCxsbEntry);
#endif 
        CmdQueueParam.cxsbWaitCnt--;
        pCxsbEntry->CxsbFlag.bits.ExecBit = TRUE;
      }

      pCxsbEntry = pCxsbEntry->pNext;
    }

#if CFG_XFERFINFUN > 0
    mHostIntrSrcEn(m_tHBI_INT_bits_fwXferDone);
#endif
	
  }

}


#if CFG_XFERFINFUN > 0
/*********************************************************************************************************
** Function Name         : CommandFin
** Function Describe     : Handler Fin Cxsb
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CommandFin(void)
{
  CXSBLINK *pCxsbEntry, *pNextCxsbEntry;  

  if((BSemCurXferFinCnt) && (CmdQueueParam.cxsbWaitCnt == 0x00))
  {
//The Last Cxsb is finish
    pCxsbEntry = CmdQueueParam.pCxsbXferHead;

    while(pCxsbEntry)
    {
      if(pCxsbEntry->CxsbFlag.bits.ExecBit == TRUE)
      {
        if(pCxsbEntry->CxsbFlag.bits.WRCMD)
        {
          BfrSSDParam.WRSSDXferPtr += pCxsbEntry->XferSSDCnt;
          BfrSSDParam.WRSSDXferPtr &= BFR_SSD_WRMASK;
          FCFlushOperation(pCxsbEntry);
        }
        else
        {
          BfrSSDParam.RDSSDXferPtr += pCxsbEntry->XferSSDCnt;
          BfrSSDParam.RDSSDXferPtr &= BFR_SSD_RDMASK;
          HSReadOperation(pCxsbEntry);
        }
        pNextCxsbEntry = pCxsbEntry->pNext;		
        CxsbReturnToIdle(pCxsbEntry);
		pCxsbEntry = pNextCxsbEntry;
      }
	  else
	  {
        pCxsbEntry = pCxsbEntry->pNext;
	  }
    }

	mHostIntrSrcDis(m_tHBI_INT_bits_fwXferDone);
	BSemCurXferFinCnt--;
  }

}
#endif


/*******************************************************************************************************
*                                                                     End Of File
               ********************************************************************************************************/
