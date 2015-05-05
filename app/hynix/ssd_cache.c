/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "HEAD.H"

LPNCACHE_NODE RdCache[RDCacheCnt];
LPNCACHE_NODE WrCache[WRCacheCnt];
BFRSSDPARAMETER BfrSSDParam;




void CacheLookUPTblInit(void)
{
  INT32U tDDRByteAddr, tDDRByteEndAddr;

  tDDRByteAddr = (DDRCPUACCESSBASE + CACHE_LOOKUPTBLADR_B);
  tDDRByteEndAddr = (tDDRByteAddr + CACHE_LOOKUPTBLSIZE);

  for(; tDDRByteAddr < tDDRByteEndAddr; tDDRByteAddr += 0x02)
  {
    IO_REG16(tDDRByteAddr) = 0xFFFF;
  }

}


INT16U CacheLookUP(INT32U LogicLPN)
{
  INT32U tDDRByteAddr;
  INT16U CacheIndex;

  tDDRByteAddr = (DDRCPUACCESSBASE + CACHE_LOOKUPTBLADR_B);
  tDDRByteAddr += LogicLPN << 0x01;

  CacheIndex = IO_REG16(tDDRByteAddr);

  return CacheIndex;

}

void CacheSetTbl(INT32U LogicLPN, INT16U CacheIndex)
{
  INT32U tDDRByteAddr;

  tDDRByteAddr = (DDRCPUACCESSBASE + CACHE_LOOKUPTBLADR_B);
  tDDRByteAddr += LogicLPN << 0x01;

  IO_REG16(tDDRByteAddr) = CacheIndex;
}

#if CFG_SETRAMVALUE > 0
INT32U DDRValueDWord(INT32U tDworValue)
{
  INT32U tRval;

  tRval = ((BYTE0_OF(tDworValue) << 0x18) | (BYTE1_OF(tDworValue) << 0x10) | (BYTE2_OF(tDworValue) << 0x08) | (BYTE3_OF(tDworValue) << 0x00));
  return tRval;
}

void DDRSetValue(void)
{
  INT32U tMaxByteSize, tCnt, ttCnt, tVal, tByteInSct;
  INT32U tDDRAddr;
//Ramdisk as 128M Bytes  
//tMaxByteSize = 128*1024*1024;
  tMaxByteSize = 8 * 1024 * 1024;
  tByteInSct = 0x200;
  tVal = 0x00000000;
  for(tCnt = 0x00; tCnt < tMaxByteSize; tCnt += 0x200)
  {
    for(ttCnt = 0x00; ttCnt < tByteInSct; ttCnt += 0x04)
    {
      tDDRAddr = DDRCPUACCESSBASE + SIMRAMDISKOFST_B + tCnt + ttCnt;
      IO_REG32(tDDRAddr) = DDRValueDWord(tVal);
    }
    tVal += 0x00000001;
  }
}

#endif 

/*********************************************************************************************************
** Function Name         : CalCacheCnt
** Function Describe     : Calculate the 4K Cache Count
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
INT16U CalCacheCnt(INT32U LBAAddr, INT32U SecCnt)
{
  INT32U FirstOffset, FirstLen, NoHeadSecCnt;
  INT16U CacheCnt;

  FirstOffset = ((LBAAddr &LBA_LPNOFFMASK) >> LBA_LPNOFFOFST);
  FirstLen = LBA_LPNSECSIZE - FirstOffset;
  if(FirstLen > SecCnt)
  {
    FirstLen = SecCnt;
  }

  NoHeadSecCnt = SecCnt - FirstLen;
  CacheCnt = NoHeadSecCnt / LBA_LPNSECSIZE + ((NoHeadSecCnt % LBA_LPNSECSIZE) != 0);
  CacheCnt++;

  return CacheCnt;

}

/*********************************************************************************************************
** Function Name         : CalSecCnt
** Function Describe     : Calculate the Sector Count from CacheCnt, typically in the situation of Free Cache is less than require Cache
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
INT32U CalSecCnt(INT32U LBAAddr, INT32U SecCnt, INT16U CacheCnt)
{
  INT32U FirstOffset, FirstLen, LastOffset, LastLen, EndLBA, SectorCnt;
  INT32U RealCacheCnt;


  FirstOffset = ((LBAAddr &LBA_LPNOFFMASK) >> LBA_LPNOFFOFST);
  FirstLen = LBA_LPNSECSIZE - FirstOffset;
  if(FirstLen > SecCnt)
  {
    FirstLen = SecCnt;
    return FirstLen;
  }
  else
  {
    SectorCnt = ((CacheCnt - 0x01) << LBA_LPNNUMOFST);
    SectorCnt += FirstLen;
    RealCacheCnt = CalCacheCnt(LBAAddr, SecCnt);

    if(RealCacheCnt > CacheCnt)
    {
      return SectorCnt;
    }
    else
    {

      EndLBA = LBAAddr + SecCnt;
      LastOffset = ((EndLBA &LBA_LPNOFFMASK) >> LBA_LPNOFFOFST);
      if(LastOffset)
      {
        LastLen = LBA_LPNSECSIZE - LastOffset;
        SectorCnt -= LastLen;
      }
      return SectorCnt;
    }
  }
}



/*********************************************************************************************************
** Function Name         : CacheReadOperation
** Function Describe     : Read Command Operation
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
BOOLEAN CacheReadOperation(CMDQENTRY *pCmdQEntry)
{
  INT32U CurFCLBA, CurFCSecCnt, CurExecSecCnt;
  INT16U CurFCCacheCnt;

  if((BfrSSDParam.RDSSDCnt != 0x00) && (pCmdQEntry->SecCnt != 0x00))
  {
    CurFCLBA = pCmdQEntry->LbaAdr;
    CurFCSecCnt = pCmdQEntry->SecCnt;
    CurFCCacheCnt = CalCacheCnt(CurFCLBA, CurFCSecCnt);

    if(CurFCCacheCnt > BfrSSDParam.RDSSDCnt)
    {
      CurFCCacheCnt = BfrSSDParam.RDSSDCnt;
    }

    CurExecSecCnt = CalSecCnt(CurFCLBA, CurFCSecCnt, CurFCCacheCnt);

    if(SUCCESS == FCReadOperation(pCmdQEntry, CurFCLBA, CurExecSecCnt))
    {

      if((pCmdQEntry->SecCnt) == 0x00)
      {
        CmdQReturnToIdle(pCmdQEntry);
      }
      return SUCCESS;
    }
    else
    {
      return FAIL;
    }
  }
  else
  {
    return FAIL;
  }


}



/*********************************************************************************************************
** Function Name         : CacheWriteOperation
** Function Describe     : Write Command Operation
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
BOOLEAN CacheWriteOperation(CMDQENTRY *pCmdQEntry)
{
  INT32U CurFCLBA, CurFCSecCnt, CurExecSecCnt;
  INT16U CurFCCacheCnt;

  if((BfrSSDParam.WRSSDCnt != 0x00) && (pCmdQEntry->SecCnt != 0x00))
  {
    CurFCLBA = pCmdQEntry->LbaAdr;
    CurFCSecCnt = pCmdQEntry->SecCnt;
    CurFCCacheCnt = CalCacheCnt(CurFCLBA, CurFCSecCnt);

    if(CurFCCacheCnt > BfrSSDParam.WRSSDCnt)
    {
      CurFCCacheCnt = BfrSSDParam.WRSSDCnt;
    }

    CurExecSecCnt = CalSecCnt(CurFCLBA, CurFCSecCnt, CurFCCacheCnt);

    if(SUCCESS == FCWriteOperation(pCmdQEntry, CurFCLBA, CurExecSecCnt))
    {

      if((pCmdQEntry->SecCnt) == 0x00)
      {
        CmdQReturnToIdle(pCmdQEntry);
      }
      return SUCCESS;
    }
    else
    {
      return FAIL;
    }
  }
  else
  {
    return FAIL;
  }


}

/*********************************************************************************************************
** Function Name         : mCacheInit
** Function Describe     : Cache Init function
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void mCacheInit(void)
{
  INT32U tCacheCnt;

  for(tCacheCnt = 0x00; tCacheCnt < RDCacheCnt; tCacheCnt++)
  {
    RdCache[tCacheCnt].DDRByteAddr = (RDCacheStaDDR_B + (tCacheCnt *CACHESIZE_B));
    RdCache[tCacheCnt].LogPageNum = 0xFFFFFFFF;
    RdCache[tCacheCnt].CacheSta = 0x00;
  }

  for(tCacheCnt = 0x00; tCacheCnt < WRCacheCnt; tCacheCnt++)
  {
    WrCache[tCacheCnt].DDRByteAddr = (WRCacheStaDDR_B + (tCacheCnt *CACHESIZE_B));
    WrCache[tCacheCnt].LogPageNum = 0xFFFFFFFF;
    WrCache[tCacheCnt].CacheSta = 0x00;
  }

  BfrSSDParam.RDSSDCnt = RDCacheCnt;
  BfrSSDParam.RDSSDFCPtr = BfrSSDParam.RDSSDHSPtr = BfrSSDParam.RDSSDXferPtr = 0x00;

  BfrSSDParam.WRSSDCnt = WRCacheCnt;
  BfrSSDParam.WRSSDFCPtr = BfrSSDParam.WRSSDHSPtr = BfrSSDParam.WRSSDXferPtr = RDCacheCnt;

  CacheLookUPTblInit();
#if CFG_SETRAMVALUE > 0
  DDRSetValue();
#endif 
}


/*******************************************************************************************************
*                                                                     End Of File
       ********************************************************************************************************/
