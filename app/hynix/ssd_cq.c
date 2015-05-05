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
** Function Name         : DMACPYData
** Function Describe     : Copy Data from DDR to DDR
** Input  Parameter      : ByteLen from 0x001~0x2000 1~8K
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DMACPYData(INT32U RdDDRByteAddr, INT32U WrDDRByteAddr, INT16U XferByteLen)
{
#if 1
//DDR Operation
  (*(volatile unsigned short*)(0x1C00F000)) = 0x03;
  (*(volatile unsigned long*)(0x1C00F014)) = RdDDRByteAddr;
  (*(volatile unsigned long*)(0x1C00F018)) = WrDDRByteAddr;
  (*(volatile unsigned short*)(0x1C00F010)) = XferByteLen;
  (*(volatile unsigned short*)(0x1C00F008)) = 0x0011;
  (*(volatile unsigned short*)(0x1C00F004)) = 0x01;

  while(!((*(volatile unsigned short*)(0x1C00F00C)) &0x01))
    ;
#else 
  INT16U tCnt;

  for(tCnt = 0x00; tCnt < XferByteLen; tCnt += 0x04)
  {
    IO_REG32(DDRCPUACCESSBASE + WrDDRByteAddr + tCnt) = IO_REG32(DDRCPUACCESSBASE + RdDDRByteAddr + tCnt);
  }
#endif 

}

#if CFG_FAKECQOP > 0
/*********************************************************************************************************
** Function Name         : FCReadOperation
** Function Describe     : Fake FC Read Operation
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
BOOLEAN FCReadOperation(CMDQENTRY *pCmdQEntry, INT32U LBAAddr, INT32U SecCnt)
{
  INT32U CurLPN, CurOffset, CurLen, CurXferCnt;
  INT32U CurDDRReadAdrByte, CurDDRWriteAdrByte;
  INT16U CurCacheIndex, NextBfrSSDPtr, StartBfrSSDPtr, CurXferSSDCnt;
  CXSBLINK *pCxsbEntry;

  StartBfrSSDPtr = BfrSSDParam.RDSSDFCPtr;

  pCxsbEntry = CxsbGetFromFree();

  if(pCxsbEntry)
  {
    CurXferCnt = SecCnt;
    CurXferSSDCnt = 0x00;

    while(SecCnt)
    {
      CurLPN = ((LBAAddr &LBA_LPNNUMMASK) >> LBA_LPNNUMOFST);
      CurOffset = ((LBAAddr &LBA_LPNOFFMASK) >> LBA_LPNOFFOFST);
      CurLen = LBA_LPNSECSIZE - CurOffset;
      if(CurLen > SecCnt)
      {
        CurLen = SecCnt;
      }

      CurCacheIndex = CacheLookUP(CurLPN);

      if(CurCacheIndex != 0xFFFF)
      {
//Hit the cache
        while(WrCache[CurCacheIndex].CacheSta == CACHESTA_WR)
        {
          CommandXfer();	
#if CFG_XFERFINFUN > 0		  
	      CommandFin( );
#endif 
        }
	
        pmBfrSSD[BfrSSDParam.RDSSDFCPtr].ssdStartBufAddr = (WrCache[CurCacheIndex].DDRByteAddr + (CurOffset << 0x09));
        pmBfrSSD[BfrSSDParam.RDSSDFCPtr].ssdEndBufAddr = (WrCache[CurCacheIndex].DDRByteAddr + (CurOffset + CurLen << 0x09)) - 0x02;

      }
      else
      {
//Missing cache	
        CurDDRReadAdrByte = (((CurLPN << LBA_LPNNUMOFST) + CurOffset) << 0x09);
        CurDDRReadAdrByte += SIMRAMDISKOFST_B;
        CurDDRWriteAdrByte = (RdCache[BfrSSDParam.RDSSDFCPtr].DDRByteAddr + (CurOffset << 0x09));

        DMACPYData(CurDDRReadAdrByte, CurDDRWriteAdrByte, (CurLen << 0x09));
        pmBfrSSD[BfrSSDParam.RDSSDFCPtr].ssdStartBufAddr = (RdCache[BfrSSDParam.RDSSDFCPtr].DDRByteAddr + (CurOffset << 0x09));
        pmBfrSSD[BfrSSDParam.RDSSDFCPtr].ssdEndBufAddr = (RdCache[BfrSSDParam.RDSSDFCPtr].DDRByteAddr + (CurOffset + CurLen << 0x09)) - 0x02;
      }

      LBAAddr += CurLen;
      SecCnt -= CurLen;
      NextBfrSSDPtr = BfrSSDParam.RDSSDFCPtr + 0x01;
      if(NextBfrSSDPtr == BFR_SSD_RDCNT)
      {
        NextBfrSSDPtr = 0x00;
      }
      if(SecCnt == 0x00)
      {
        pmBfrSSD[BfrSSDParam.RDSSDFCPtr].nextSsdIndex = StartBfrSSDPtr;
      }
      else
      {
        pmBfrSSD[BfrSSDParam.RDSSDFCPtr].nextSsdIndex = NextBfrSSDPtr;
      }

      BfrSSDParam.RDSSDFCPtr = NextBfrSSDPtr;
      BfrSSDParam.RDSSDCnt--;
      CurXferSSDCnt++;

    }

    pCxsbEntry->HSNum = CmdQueueParam.curHSNum;
    CmdQueueParam.curHSNum++;
    CmdQueueParam.curHSNum &= CMDQHSMAXMASK;
    pCxsbEntry->HSPtrNum = StartBfrSSDPtr;
    pCxsbEntry->XferDDRByteAddr = pmBfrSSD[StartBfrSSDPtr].ssdStartBufAddr;
    pCxsbEntry->XferLen = CurXferCnt;
	pCxsbEntry->CxsbFlag.bits.ExecBit = FALSE;
    pCxsbEntry->CxsbFlag.bits.WRCMD = FALSE;
    pCxsbEntry->CxsbFlag.bits.NCQCmd = pCmdQEntry->CmdFlag.bits.NCQCmd;
    pCxsbEntry->NCQTag = pCmdQEntry->NCQTag;
    pCxsbEntry->XferSSDCnt = CurXferSSDCnt;

    pCmdQEntry->LbaAdr += CurXferCnt;
    pCmdQEntry->SecCnt -= CurXferCnt;
    if(pCmdQEntry->SecCnt)
    {
      pCxsbEntry->CxsbFlag.bits.EndBit = FALSE;
    }
    else
    {
      pCxsbEntry->CxsbFlag.bits.EndBit = TRUE;
    }

    CxsbSaveToXfer(pCxsbEntry);
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}



/*********************************************************************************************************
** Function Name         : FCWriteOperation
** Function Describe     : Fake FC Read Operation
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
BOOLEAN FCWriteOperation(CMDQENTRY *pCmdQEntry, INT32U LBAAddr, INT32U SecCnt)
{
  INT32U CurLPN, CurOffset, CurLen, CurXferCnt;
  INT32U CurDDRReadAdrByte, CurDDRWriteAdrByte;
  INT16U CurCacheIndex, NextBfrSSDPtr, StartBfrSSDPtr, WrCacheIndex, CurXferSSDCnt;
  CXSBLINK *pCxsbEntry;

  StartBfrSSDPtr = BfrSSDParam.WRSSDHSPtr;

  pCxsbEntry = CxsbGetFromFree();
  if(pCxsbEntry)
  {
    CurXferCnt = SecCnt;
    CurXferSSDCnt = 0x00;

    while(SecCnt)
    {
      CurLPN = ((LBAAddr &LBA_LPNNUMMASK) >> LBA_LPNNUMOFST);
      CurOffset = ((LBAAddr &LBA_LPNOFFMASK) >> LBA_LPNOFFOFST);
      CurLen = LBA_LPNSECSIZE - CurOffset;
      if(CurLen > SecCnt)
      {
        CurLen = SecCnt;
      }

      WrCacheIndex = BfrSSDParam.WRSSDHSPtr - BFR_SSD_RDCNT;

      if((CurOffset == 0x00) && (CurLen == LBA_LPNSECSIZE))
      {
//Full Write    

        pmBfrSSD[BfrSSDParam.WRSSDHSPtr].ssdStartBufAddr = (WrCache[WrCacheIndex].DDRByteAddr + (CurOffset << 0x09));
        pmBfrSSD[BfrSSDParam.WRSSDHSPtr].ssdEndBufAddr = (WrCache[WrCacheIndex].DDRByteAddr + (CurOffset + CurLen << 0x09)) - 0x02;
        WrCache[WrCacheIndex].LogPageNum = CurLPN;
        WrCache[WrCacheIndex].CacheSta = CACHESTA_WR;
        CacheSetTbl(CurLPN, WrCacheIndex);

      }
      else
      {
//Nt Full Write	   
        CurCacheIndex = CacheLookUP(CurLPN);
        if(CurCacheIndex != 0xFFFF)
        {        
//Hit the cache, copy the all data to this Cache
          while(WrCache[CurCacheIndex].CacheSta == CACHESTA_WR)
          {
            CommandXfer();
#if CFG_XFERFINFUN > 0			
	        CommandFin( );		
#endif
          }
		  
          CurDDRReadAdrByte = (WrCache[CurCacheIndex].DDRByteAddr);
          CurDDRWriteAdrByte = (WrCache[WrCacheIndex].DDRByteAddr);
          DMACPYData(CurDDRReadAdrByte, CurDDRWriteAdrByte, (LBA_LPNSECSIZE << 0x09));
        }
        else
        {
//Not Hit the Cache, read all 4K data from ramdisk
          CurDDRReadAdrByte = ((CurLPN << LBA_LPNNUMOFST) << 0x09);
          CurDDRReadAdrByte += SIMRAMDISKOFST_B;
          CurDDRWriteAdrByte = (WrCache[WrCacheIndex].DDRByteAddr);
          DMACPYData(CurDDRReadAdrByte, CurDDRWriteAdrByte, (LBA_LPNSECSIZE << 0x09));
        }

        pmBfrSSD[BfrSSDParam.WRSSDHSPtr].ssdStartBufAddr = (WrCache[WrCacheIndex].DDRByteAddr + (CurOffset << 0x09));
        pmBfrSSD[BfrSSDParam.WRSSDHSPtr].ssdEndBufAddr = (WrCache[WrCacheIndex].DDRByteAddr + (CurOffset + CurLen << 0x09)) - 0x02;
        WrCache[WrCacheIndex].LogPageNum = CurLPN;
        WrCache[WrCacheIndex].CacheSta = CACHESTA_WR;
        CacheSetTbl(CurLPN, (BfrSSDParam.WRSSDHSPtr - BFR_SSD_RDCNT));

      }


      LBAAddr += CurLen;
      SecCnt -= CurLen;
      NextBfrSSDPtr = BfrSSDParam.WRSSDHSPtr + 0x01;
      if(NextBfrSSDPtr == BFR_SSD_COUNT)
      {
        NextBfrSSDPtr = BFR_SSD_RDCNT;
      }
      if(SecCnt == 0x00)
      {
        pmBfrSSD[BfrSSDParam.WRSSDHSPtr].nextSsdIndex = StartBfrSSDPtr;
      }
      else
      {
        pmBfrSSD[BfrSSDParam.WRSSDHSPtr].nextSsdIndex = NextBfrSSDPtr;
      }

      BfrSSDParam.WRSSDHSPtr = NextBfrSSDPtr;
      BfrSSDParam.WRSSDCnt--;
      CurXferSSDCnt++;
    }

    pCxsbEntry->HSNum = CmdQueueParam.curHSNum;
    CmdQueueParam.curHSNum++;
    CmdQueueParam.curHSNum &= CMDQHSMAXMASK;
    pCxsbEntry->HSPtrNum = StartBfrSSDPtr;
    pCxsbEntry->XferDDRByteAddr = pmBfrSSD[StartBfrSSDPtr].ssdStartBufAddr;
    pCxsbEntry->XferLen = CurXferCnt;
	pCxsbEntry->CxsbFlag.bits.ExecBit = FALSE;
    pCxsbEntry->CxsbFlag.bits.WRCMD = TRUE;
    pCxsbEntry->CxsbFlag.bits.NCQCmd = pCmdQEntry->CmdFlag.bits.NCQCmd;
    pCxsbEntry->NCQTag = pCmdQEntry->NCQTag;
    pCxsbEntry->XferSSDCnt = CurXferSSDCnt;

    pCmdQEntry->LbaAdr += CurXferCnt;
    pCmdQEntry->SecCnt -= CurXferCnt;
    if(pCmdQEntry->SecCnt)
    {
      pCxsbEntry->CxsbFlag.bits.EndBit = FALSE;
    }
    else
    {
      pCxsbEntry->CxsbFlag.bits.EndBit = TRUE;
    }

    CxsbSaveToXfer(pCxsbEntry);
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}


/*********************************************************************************************************
** Function Name         : FCFlushOperation
** Function Describe     : Fake FC Flush Data from Cache to Ramdisk
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void FCFlushOperation(CXSBLINK *pCxsbEntry)
{
  INT32U CurDDRReadAdrByte, CurDDRWriteAdrByte;
  INT16U WrCacheIndex, tWRCacheCnt;


  if(BfrSSDParam.WRSSDCnt != BFR_SSD_WRCNT)
  {
    tWRCacheCnt = pCxsbEntry->XferSSDCnt;
    while(tWRCacheCnt)
    {
      WrCacheIndex = BfrSSDParam.WRSSDFCPtr - BFR_SSD_RDCNT;

      CurDDRReadAdrByte = (WrCache[WrCacheIndex].DDRByteAddr);
      CurDDRWriteAdrByte = ((WrCache[WrCacheIndex].LogPageNum << LBA_LPNNUMOFST) << 0x09);
      CurDDRWriteAdrByte += SIMRAMDISKOFST_B;
      WrCache[WrCacheIndex].CacheSta = CACHESTA_WRFIN;
      WrCache[WrCacheIndex].CacheSta = CACHESTA_FLUSH;
      DMACPYData(CurDDRReadAdrByte, CurDDRWriteAdrByte, (LBA_LPNSECSIZE << 0x09));
      WrCache[WrCacheIndex].CacheSta = CACHESTA_IDLE;
      CacheSetTbl(WrCache[WrCacheIndex].LogPageNum, 0xFFFF);
      WrCache[WrCacheIndex].LogPageNum = 0xFFFF;


      BfrSSDParam.WRSSDCnt++;
      BfrSSDParam.WRSSDFCPtr++;
      if(BfrSSDParam.WRSSDFCPtr == BFR_SSD_COUNT)
      {
        BfrSSDParam.WRSSDFCPtr = BFR_SSD_RDCNT;
      }
      tWRCacheCnt--;
    }

  }
}


/*********************************************************************************************************
** Function Name         : FCFlushOperation
** Function Describe     : Fake FC Flush Data from Cache to Ramdisk
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void HSReadOperation(CXSBLINK *pCxsbEntry)
{
  if(BfrSSDParam.RDSSDCnt != BFR_SSD_RDCNT)
  {
    BfrSSDParam.RDSSDCnt += pCxsbEntry->XferSSDCnt;
    BfrSSDParam.RDSSDHSPtr += pCxsbEntry->XferSSDCnt;
    BfrSSDParam.RDSSDHSPtr &= BFR_SSD_RDMASK;
  }
}

#endif 


/*******************************************************************************************************
*                                                                     End Of File
        ********************************************************************************************************/
