/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
**----------------------------------------File Information----------------------------------------------
** File Name             : Ssd_debug.c
** File Version          : V1.0
** File Creator          : Qin Zhi
** File Create Data      : 2012-08-23
** File Description      : The debug intface
*******************************************************************************************************/
#include "HEAD.H"

// global ram addr  variable define
INT32U dbgDDRBaseAddr;
INT32U dbgDDRCmdAddr;
INT32U dbgDDRDataAddr;
INT32U dbgDDRRstAddr;
INT32U dbgDDRPadAddr;
INT32U dbgDDRMetaBufAddr;

// follow called by xx function in main
INT16U dbgGloCriticalBlks      = 0;
INT8U   dbgGloRealRowCnts   = 0;
INT8U   dbgGloInterleavingFlag        = 0;
INT8U   dbgGloLun    =0;


INT16U  dbgGloBlkCnts = 0;
INT8U    dbgGloChpCnts  = 0;
INT8U    dbgGloRowCnts = 0;
INT8U    dbgGloRunFlag = 0;
INT16U  dbgCurBlk = 0;
INT8U    bdblkCnts[64];
/*********************************************************************************************************
** Function Name         : InitDebug
** Function Describe     : Init debug module
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void InitDebug(void)
{
	INT8U i;
	dbgDDRBaseAddr         = DBG_DDR_BASE_ADDR;
	dbgDDRCmdAddr          = DBG_DDR_CMD_ADDR;
	dbgDDRDataAddr         = DBG_DDR_DATA_ADDR;
	dbgDDRRstAddr          = DBG_DDR_RST_ADDR;
	dbgDDRPadAddr          = DBG_DDR_PAD_ADDR;
	dbgDDRMetaBufAddr      = DBG_DDR_METABUF_ADDR;
	// Modify  for init global variable  by qinzhi 20130929
       dbgGloCriticalBlks      = 0;
       dbgGloRealRowCnts   = 0;
       dbgGloInterleavingFlag        = 0;
       dbgGloLun    =0;


       dbgGloBlkCnts = 0;
       dbgGloChpCnts  = 0;
       dbgGloRowCnts = 0;
       dbgGloRunFlag = 0;
       dbgCurBlk = 0;
	for(i=0; i<64; i++)
	{
		bdblkCnts[i] = 0;
	}
}
/*********************************************************************************************************
** Function Name         : DBG_FillSram
** Function Describe     : Debug Interface Fill the ddr with byte Value
** Input  Parameter      : Mode :0 as TOGGLE mode; 1 as Onfi mode
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
void DBG_FillDDR(INT32U StartAddr, INT32U Len, INT8U Value)
{
  INT32U tAddr, tMaxAddr;

  tMaxAddr = StartAddr + Len;

  for(tAddr =StartAddr; tAddr <tMaxAddr; tAddr++)
  {
	REG8_WRITE(tAddr, Value);
  }
}
/*********************************************************************************************************
** Function Name         : DBG_FillDDRDW
** Function Describe     : Debug Interface Fill the ddr with Dword Value
** Input  Parameter      :  
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
void DBG_FillDDRDW(INT32U StartAddr, INT32U Len, INT32U Value)
{
  INT32U tAddr, tMaxAddr;

  tMaxAddr = StartAddr + Len;

  for(tAddr =StartAddr; tAddr <tMaxAddr; tAddr+=4)
  {
	REG32_WRITE(tAddr, Value);
	* (VINT32U*) (tAddr) =Value ;  
  }
}
/*********************************************************************************************************
** Function Name         : DBG_CheckDDRDW
** Function Describe     : Debug Interface Fill the ddr with Dword Value
** Input  Parameter      :  
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
INT8U DBG_CheckDDRDW(INT32U StartAddr, INT32U Len, INT32U chkValue)
{

  INT32U  tAddr, tMaxAddr;
  INT32U  ddrValue;
  tMaxAddr = StartAddr + Len;

  for(tAddr =StartAddr; tAddr <tMaxAddr; tAddr+=4)
  {
	ddrValue = REG32_READ(tAddr);
	if(ddrValue != chkValue)
	{
		return 0;
	}
  }
  return 1;

}
/*********************************************************************************************************
** Function Name         : DBG_VDOperation
** Function Describe     : all vondor cmd operation
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_VDOperation(CMDQENTRY *pCurCmdEntry)
{
	INT8U featureReg = pCurCmdEntry->atareg.ATA_REG_FEA;
	switch(featureReg)
	{
		case DBG_ARG_SBCMD_WRCMD:
			DBG_VendorAllCmd(pCurCmdEntry);
		break;
		case DBG_ARG_SBCMD_RDDAT:
			DBG_RDDataSubCmd(pCurCmdEntry);
		break;
		case DBG_ARG_SBCMD_WRDAT:
			DBG_WRDataSubCmd(pCurCmdEntry);
		break;
		case DBG_ARG_SBCMD_RDRSLT:
			DBG_RDResultSubCmd(pCurCmdEntry);
		break;
	
	}
}

/*********************************************************************************************************
** Function Name         : DBG_GETRegDump
** Function Describe     : Read Register Dump
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_GETRegDump(DBG_CMD_INF *pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
  IO_REG16(dbgDDRDataAddr) = IO_REG16(pDbgCmdinf->ddrAddr);
  pCmdResult->success = DBG_SUCCESS;
}
/*********************************************************************************************************
** Function Name         : DBG_WriteReg
** Function Describe     :Write Register 
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_WriteReg(DBG_CMD_INF *pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
  IO_REG16(pDbgCmdinf->ddrAddr) = pDbgCmdinf->param;
  pCmdResult->success = DBG_SUCCESS;
}
/*********************************************************************************************************
** Function Name         : DBG_VendorAllCmd
** Function Describe     : None
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_VendorAllCmd(CMDQENTRY *pCurCmdEntry)
{
	P_DBG_CMD_INF         pDbgCmdinf;
	P_DBG_CMD_RESULT      pDbgCmdResult;

	// cmdresult ddr addr
	pDbgCmdResult = (P_DBG_CMD_RESULT)(dbgDDRRstAddr);
	// cmd ddr addr
	pDbgCmdinf = (P_DBG_CMD_INF)(dbgDDRCmdAddr);
	// write cmd format to ddr by sata
	SataWriteDDRData(dbgDDRCmdAddr,1);

	// vendor cmd case 
	switch(pDbgCmdinf->vndCmd)
	{
		case DBG_CMD_RDDDR:
			DBG_VDReadDDRCmd(pDbgCmdinf, pDbgCmdResult);
			break;
		case DBG_CMD_WRDDR:
			DBG_VDWriteDDRCmd(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_RST:
			DBG_VDRstCmd(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_SETFEA:
			DBG_VDSetFeaCmd(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_RDID:
			DBG_VDReadAllIDCmd(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_SETFEATURE:
			DBG_VDSetFeatureCmd(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_READCHIPID:
			DBG_VDREADCHIPIDCmd(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_FLASHRESET:
			DBG_VDFLASHRESETCmd(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_RDPAGE: 
			DBG_VDReadPageCmd(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_WRPAGE: 
			DBG_VDWritePageCmd(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_WR2PPAGE: 
			DBG_VD2PlaneWritePageCmd(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_ERZBLOCK: 
			DBG_VDEraseBlkCmd(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_FINDBADBLK: 
			DBG_VDFindBlkCmd(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_WRITEPAD :
			DBG_VDWritePadDataCmd(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_READPAD:
			DBG_VDReadPadDataCmd(pDbgCmdinf, pDbgCmdResult);
			break;
		case DBG_CMD_RDFW_SPI:
			DBG_VDReadFWSPI(pDbgCmdinf, pDbgCmdResult);
			break;
		case DBG_CMD_WRFW_SPI:
			DBG_VDWriteFWSPI(pDbgCmdinf, pDbgCmdResult);
			break;
		case DBG_CMD_ERASE_SPI:
			DBG_VDEraseSPI(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_WP_SPI:	
		    	DBG_VDWriteProtectSPI(pDbgCmdinf, pDbgCmdResult);
		    	break;
		case DBG_CMD_STS_SPI:	
		    	DBG_VDReadProtectSPI(pDbgCmdinf, pDbgCmdResult);
		    	break;
		case DBG_CMD_PCB_TEST:
			DBG_VDPCBTest(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_FDBADBLK_BY_ERASEALL:
			DBG_VDFindBlkByEaseAllCmd(pDbgCmdinf, pDbgCmdResult);
			break;
		case DBG_CMD_QUERY_FINISH_STATUS:
		      DBG_VDQueryFinishStatus(pDbgCmdinf, pDbgCmdResult);
			break;
		case DBG_CMD_CHECKUNECC:
			DBG_CheckUneccCmd(pDbgCmdinf,pDbgCmdResult);
			break;
		case DBG_CMD_GETREGDUMP:
			DBG_GETRegDump(pDbgCmdinf, pDbgCmdResult);
			break;
		case DBG_CMD_WRITE_REG:
			DBG_WriteReg(pDbgCmdinf, pDbgCmdResult);
			break;
	}
}

/*********************************************************************************************************
** Function Name         : DBG_RDDataSubCmd
** Function Describe     : Read return data subcmd
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_RDDataSubCmd(CMDQENTRY *pCurCmdEntry)
{
	SataReadDDRData(dbgDDRDataAddr, pCurCmdEntry->atareg.ATA_REG_SCNT);
}
/*********************************************************************************************************
** Function Name         : DBG_WRDataSubCmd
** Function Describe     : Write data subcmd
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_WRDataSubCmd(CMDQENTRY *pCurCmdEntry)
{
	SataWriteDDRData(dbgDDRDataAddr, pCurCmdEntry->atareg.ATA_REG_SCNT);
}
/*********************************************************************************************************
** Function Name         : DBG_RDResultSubCmd
** Function Describe     : Read result data subcmd
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_RDResultSubCmd(CMDQENTRY *pCurCmdEntry)
{
    INT32U i;
	
//    DBG_FillDDR(dbgDDRRstAddr, 0x200, 0x00);
//	for(i= 0; i< 0X20; i++)
//	{
//	  IO_REG08(dbgDDRRstAddr + i+0x100) = tid_error[i];
//	}
	SataReadDDRData(dbgDDRRstAddr, 1);
}
/*********************************************************************************************************
** Function Name         : DBG_VDReadDDRCmd
** Function Describe     : Vendor cmd read ddr context
** Input  Parameter      : DBG_CMD_INF P_DBG_CMD_RESULT
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_VDReadDDRCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
	INT32U ddrAddr = 0x50000000 + pDbgCmdinf->ddrAddr;
	INT32U byteLen = pDbgCmdinf->SecCnt*512;
	DMACPYData(pDbgCmdinf->ddrAddr, dbgDDRDataAddr, byteLen);
	pCmdResult->success = DBG_SUCCESS;
}
/*********************************************************************************************************
** Function Name         : DBG_VDWriteDDRCmd
** Function Describe     : Vendor cmd write ddr
** Input  Parameter      : DBG_CMD_INF P_DBG_CMD_RESULT
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_VDWriteDDRCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
	INT32U ddrAddr = 0x50000000 + pDbgCmdinf->ddrAddr;
	INT32U byteLen = pDbgCmdinf->SecCnt*512;
	DMACPYData(dbgDDRDataAddr, ddrAddr, byteLen);
	pCmdResult->success = DBG_SUCCESS;
}

/*********************************************************************************************************
** Function Name         : 
** Function Describe     : 
** Input  Parameter      : DBG_CMD_INF P_DBG_CMD_RESULT
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_VDRstCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
	cmd_fc_info cmd;
	cmd.ch     = pDbgCmdinf->chan;
	cmd.device = pDbgCmdinf->row;
	FC_Debug_ResetFlash(cmd);
	pCmdResult->success = DBG_SUCCESS;
}

/*********************************************************************************************************
** Function Name         : 
** Function Describe     : 
** Input  Parameter      : DBG_CMD_INF P_DBG_CMD_RESULT
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_VDSetFeaCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
	pCmdResult->success = DBG_SUCCESS;
}

/*********************************************************************************************************
** Function Name         : 
** Function Describe     : 
** Input  Parameter      : DBG_CMD_INF P_DBG_CMD_RESULT
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_VDReadAllIDCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{


	  INT8U idCnt, id[8];
	  INT8U ChanNum, RowNum, nr_id_byte;
	  INT32U SramByteAddr, tmp1, tmp2;
	  cmd_fc_info cmd;

  	  DBG_FillDDR(dbgDDRDataAddr, 512, 0x5f);	  //FC_Set_Indirect_Mode();
	  
	  for(ChanNum = 0; ChanNum < 8; ChanNum++)
	  {
	    for(RowNum = 0; RowNum < 8; RowNum++)
	    {
	      for(idCnt = 0x00; idCnt < 0x08; idCnt++)
	      {
	        id[idCnt] = 0xFF;
	      }

		  cmd.ch       = ChanNum;
		  cmd.device   = RowNum;
		  cmd.buf_add  = dbgDDRDataAddr+ (ChanNum<<0x06)+(RowNum<<0x03);  
		  FC_Debug_ReadId(cmd);
	    }
	  }
	  pCmdResult->success = DBG_SUCCESS;
}
void DBG_VDSetFeatureCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
    INT8U chan,row,err=0;
    chan= pDbgCmdinf->chan;
    row = pDbgCmdinf->row;
    err = FC_Set_Feature(chan, row, pDbgCmdinf->ddrAddr, pDbgCmdinf->param);

    if(err)
    {
    	pCmdResult->success = DBG_FAIL;
    }
    else
    {
       pCmdResult->success = DBG_SUCCESS;
    }
}

void DBG_VDREADCHIPIDCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
    cmd_fc_info cmd;
    INT8U idCnt, id[8];

	
    DBG_FillDDR(dbgDDRDataAddr, 512, 0x5f);	  //FC_Set_Indirect_Mode();
    

    for(idCnt = 0x00; idCnt < 0x08; idCnt++)
    {
    id[idCnt] = 0xFF;
    }
    
    cmd.ch       = pDbgCmdinf->chan;
    cmd.device   = pDbgCmdinf->row;
    cmd.buf_add  = dbgDDRDataAddr;  
    FC_Debug_ReadId(cmd);
    
    pCmdResult->success = DBG_SUCCESS;}

void DBG_VDFLASHRESETCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
    int err = 0;
    int tChan, tRow;
    
    FC_Set_Indirect_Mode();
    
    err = FC_Indirect_Reset_All_Devices(8,4,1);
    
    DelayUS(1000);
    
    pCmdResult->success = err;
}

/*********************************************************************************************************
** Function Name         : 
** Function Describe     : 
** Input  Parameter      : DBG_CMD_INF P_DBG_CMD_RESULT
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_VDReadPageCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{

	cmd_fc_info cmd;
	int idx;
	u8 tid;
	DBG_FillDDR(dbgDDRDataAddr, PAGE_SIZE, 0x5f);

//	if(pDbgCmdinf->row>3)
//	{
//		pDbgCmdinf->row      = pDbgCmdinf->row-4;
//		pDbgCmdinf->blkNum   = pDbgCmdinf->blkNum+4096; 
//	}
	DBG_CalcRowAndBlk(pDbgCmdinf);
	
	if(pDbgCmdinf->flag.bits.byPassBits == 1)
	{
		cmd.buf_add  = dbgDDRDataAddr;
		cmd.padbuf_add = dbgDDRPadAddr;
		cmd.ch       = pDbgCmdinf->chan;// channel
		cmd.device   = pDbgCmdinf->row;// row
		cmd.data_len = 16*1024;
		cmd.phyblock = pDbgCmdinf->blkNum;
		cmd.phypage = pDbgCmdinf->pageNum;
		FC_Debug_ReadPage_Bp(cmd);	

	}
	else
	{
//		if(pDbgCmdinf->flag.bits.tableRDBits == 1)
		if(1)
		{ // table read
	  	  	cmd.ch        = pDbgCmdinf->chan;  // channel
			cmd.device    = pDbgCmdinf->row;   // row
			cmd.phyblock  = pDbgCmdinf->blkNum;
			cmd.phypage   = pDbgCmdinf->pageNum;
			cmd.buf_add   = dbgDDRDataAddr-0x50000000;
			cmd.padbuf_add = dbgDDRPadAddr;

		}
		else
		{ // data read
			pmBfrSSD[BFR_SSD_VNDINDEX].ssdStartBufAddr = dbgDDRDataAddr-0x50000000;
			pmBfrSSD[BFR_SSD_VNDINDEX].ssdEndBufAddr = dbgDDRDataAddr-0x50000000 + 16*1024;		
	  	  	cmd.ch        = pDbgCmdinf->chan;  // channel
			cmd.device    = pDbgCmdinf->row;   // row
			cmd.phyblock  = pDbgCmdinf->blkNum;
			cmd.phypage   = pDbgCmdinf->pageNum;
			cmd.padbuf_add = dbgDDRPadAddr;
			cmd.buf_add   = dbgDDRDataAddr-0x50000000;
		}
		
		FC_Debug_ReadPage(cmd);
//        if(tid_error[cur_tid] ! = 0x00)
//		{

//		}
		
		DBG_CheckDone()	;
		//while(tid_sts[0]);
	}
	DBG_CheckDone();
	pCmdResult->success = DBG_SUCCESS;
}

/*********************************************************************************************************
** Function Name         : 
** Function Describe     : 
** Input  Parameter      : DBG_CheckUneccCmd
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_CheckUneccCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{

	cmd_fc_info cmd;
	int idx;
	u8 tid;
	DBG_FillDDR(dbgDDRDataAddr, PAGE_SIZE, 0x5f);

//	if(pDbgCmdinf->row>3)
//	{
//		pDbgCmdinf->row      = pDbgCmdinf->row-4;
//		pDbgCmdinf->blkNum   = pDbgCmdinf->blkNum+4096; 
//	}

	DBG_CalcRowAndBlk(pDbgCmdinf);
	if(1)
	{ // table read
  	  	cmd.ch        = pDbgCmdinf->chan;  // channel
		cmd.device    = pDbgCmdinf->row;   // row
		cmd.phyblock  = pDbgCmdinf->blkNum;
		cmd.phypage   = pDbgCmdinf->pageNum;
		cmd.buf_add   = dbgDDRDataAddr-0x50000000;
		cmd.padbuf_add = dbgDDRPadAddr;

	}
	
	FC_Debug_ReadPage(cmd);
	DBG_CheckDone();
	if(tid_error[cur_tid])
	{
		pCmdResult->success = DBG_FAIL;
	}
	else		
	{
		pCmdResult->success = DBG_SUCCESS;
	}

}
void DBG_CheckDone()
{
	int i = 0;
	for(i=0;i<32;i++)
    {
    	while(tid_sts[i])
    		FC_Seq_Done();
    }
}
/*********************************************************************************************************
** Function Name         : 
** Function Describe     : 
** Input  Parameter      : DBG_CMD_INF P_DBG_CMD_RESULT
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_VDWritePageCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
 	cmd_fc_info cmd;
//	if(pDbgCmdinf->flag.bits.tableRDBits==1)
//	if(pDbgCmdinf->row>3)
//	{
//		pDbgCmdinf->row      = pDbgCmdinf->row-4;
//		pDbgCmdinf->blkNum   = pDbgCmdinf->blkNum+4096; 
//	}

	DBG_CalcRowAndBlk(pDbgCmdinf);
	
	if(1)
	{   // table write
    
		cmd.ch       = pDbgCmdinf->chan;
		cmd.device   = pDbgCmdinf->row;
		cmd.phyblock = pDbgCmdinf->blkNum;
		cmd.phypage = pDbgCmdinf->pageNum;
		cmd.buf_add  = dbgDDRDataAddr-0x50000000;
		cmd.padbuf_add = dbgDDRPadAddr;
	}
	else
	{   // data write
		pmBfrSSD[BFR_SSD_VNDINDEX].ssdStartBufAddr = dbgDDRDataAddr-0x50000000;
		pmBfrSSD[BFR_SSD_VNDINDEX].ssdEndBufAddr = dbgDDRDataAddr -0x50000000+ 16*1024;	
		cmd.ch       = pDbgCmdinf->chan;
		cmd.device   = pDbgCmdinf->row;
		cmd.phyblock = pDbgCmdinf->blkNum;
		cmd.phypage = pDbgCmdinf->pageNum;
		cmd.padbuf_add = dbgDDRPadAddr;
		cmd.buf_add  = dbgDDRDataAddr-0x50000000;
	}

	FC_Debug_ProgramPage(cmd);
	DBG_CheckDone();
	pCmdResult->success = DBG_SUCCESS;
}
/*********************************************************************************************************
** Function Name         : 
** Function Describe     : 
** Input  Parameter      : DBG_CMD_INF P_DBG_CMD_RESULT
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_VD2PlaneWritePageCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
 	cmd_fc_info cmd;

	DBG_CalcRowAndBlk(pDbgCmdinf);
	
	cmd.ch       = pDbgCmdinf->chan;
	cmd.device   = pDbgCmdinf->row;
	cmd.phyblock = pDbgCmdinf->blkNum;
	cmd.data_len = pDbgCmdinf->param;
	cmd.phypage = pDbgCmdinf->pageNum;
	cmd.buf_add  = dbgDDRDataAddr-0x50000000;
	cmd.padbuf_add = dbgDDRPadAddr;

	FC_Debug_Program2PPage(cmd);
	DBG_CheckDone();
	pCmdResult->success = DBG_SUCCESS;

}

/*********************************************************************************************************
** Function Name         : 
** Function Describe     : 
** Input  Parameter      : DBG_CMD_INF P_DBG_CMD_RESULT
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_VDEraseBlkCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
	cmd_fc_info cmd;
//	if(pDbgCmdinf->row>3)
//	{
//		pDbgCmdinf->row      = pDbgCmdinf->row-4;
//		pDbgCmdinf->blkNum   = pDbgCmdinf->blkNum+4096; 
//	}

	DBG_CalcRowAndBlk(pDbgCmdinf);
	
  	cmd.ch       = pDbgCmdinf->chan;
	cmd.device   = pDbgCmdinf->row;
	cmd.phyblock = pDbgCmdinf->blkNum;

	FC_Debug_EraseBlock(cmd);
	DBG_CheckDone();
	pCmdResult->success = DBG_SUCCESS;
}

/*********************************************************************************************************
** Function Name         : 
** Function Describe     : 
** Input  Parameter      : DBG_CMD_INF P_DBG_CMD_RESULT
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void DBG_VDFindBlkCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
	cmd_fc_info cmd;
//	if(pDbgCmdinf->row>3){
//		cmd.device    =pDbgCmdinf->row-4;
//		cmd.phyblock  = pDbgCmdinf->blkNum+4096; 
//	}else{
//		cmd.device    = pDbgCmdinf->row;
//	    cmd.phyblock  = pDbgCmdinf->blkNum; // StartBlockNum
//      }

	DBG_CalcRowAndBlk(pDbgCmdinf);
  	cmd.ch       = pDbgCmdinf->chan;
	cmd.device   = pDbgCmdinf->row;
	cmd.phyblock = pDbgCmdinf->blkNum;

//	cmd.device = DBG_CalcRow(pDbgCmdinf, INT8U row)
		
	cmd.buf_add   = dbgDDRDataAddr;

	DBG_FillDDR(dbgDDRDataAddr, PAGE_SIZE, 0x5f);
	
	FC_Debug_FindBadBlock(cmd, pDbgCmdinf->param);
	pCmdResult->success = DBG_SUCCESS;
}

/*********************************************************************************************************
** Function Name         : DBG_WriteMetaData
** Function Describe     : DBG_WriteMetaData

** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
void DBG_VDWritePadDataCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
  DMACPYData(dbgDDRDataAddr, dbgDDRPadAddr, pDbgCmdinf->SecCnt*512);
  pCmdResult->success = DBG_SUCCESS;
}


/*********************************************************************************************************
** Function Name         : DBG_VDReadPadDataCmd
** Function Describe     : DBG_VDReadPadDataCmd

** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
void DBG_VDReadPadDataCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
	cmd_fc_info cmd;
	int idx;
	u8 tid;
	DBG_FillDDR(dbgDDRDataAddr, PAGE_SIZE, 0x5f);
	DBG_FillDDR(dbgDDRPadAddr, PAGE_SIZE, 0x5e);

//	if(pDbgCmdinf->row>3)
//	{
//		pDbgCmdinf->row      = pDbgCmdinf->row-4;
//		pDbgCmdinf->blkNum   = pDbgCmdinf->blkNum+4096; 
//	}

	DBG_CalcRowAndBlk(pDbgCmdinf);
	if(1)
	{ // table read
  	  	cmd.ch        = pDbgCmdinf->chan;  // channel
		cmd.device    = pDbgCmdinf->row;   // row
		cmd.phyblock  = pDbgCmdinf->blkNum;
		cmd.phypage   = pDbgCmdinf->pageNum;
		cmd.buf_add   = dbgDDRDataAddr-0x50000000;
		cmd.padbuf_add = dbgDDRPadAddr;
	}
	
	FC_Debug_ReadPage(cmd);
	DBG_CheckDone();
	pCmdResult->success = DBG_SUCCESS;
}
/*********************************************************************************************************
** Function Name         : DBG_VDReadFWSPI
** Function Describe     : DBG_VDReadFWSPI

** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
void DBG_VDReadFWSPI(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
	int sec = 0;
	sec = pDbgCmdinf->param;
	SPI_READ(sec, dbgDDRDataAddr);
	pCmdResult->success = DBG_SUCCESS;
}

/*********************************************************************************************************
** Function Name         : DBG_VDWriteFWSPI
** Function Describe     : DBG_VDWriteFWSPI

** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
void DBG_VDWriteFWSPI(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
  INT8U tStatus;
  int secNum = 0;

  if(pDbgCmdinf->SecCnt == 0x5AA55AA5)
  {
	  secNum = pDbgCmdinf->param;
	  SPI_Write(secNum, dbgDDRDataAddr);
	  pCmdResult->success = DBG_SUCCESS;
  }
  else
  {
	  tStatus = SPI_ReadStatus();
	  if(tStatus != 0x00)
	  {
	        SPI_WriteStatus(0x8E);
	  }
	  secNum = pDbgCmdinf->param;
	  SPI_Write(secNum, dbgDDRDataAddr);
	  pCmdResult->success = DBG_SUCCESS;
	  SPI_WriteStatus(0x00);
	  do
	  {
	    SPI_WriteStatus(0x92);
	    tStatus = SPI_ReadStatus();
	  }
	  while(tStatus != 0x90);
  }
}

/*********************************************************************************************************
** Function Name         : DBG_VDEraseSPI
** Function Describe     : DBG_VDEraseSPI

** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
void DBG_VDEraseSPI(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
  INT8U tStatus;
  if(pDbgCmdinf->SecCnt == 0x5AA55AA5)
  {
	SPI_Erase(pDbgCmdinf->param);
  }
  else
  {
	tStatus = SPI_ReadStatus();
	if(tStatus != 0x00)
	{
	  do
	  {
	    SPI_WriteStatus(0x8E);
	  }
	  while(SPI_ReadStatus() != 0x8C);
	}    

	SPI_Erase(0);
	SPI_Erase(1);
	SPI_Erase(2);
	SPI_Erase(3);
	SPI_WriteStatus(0x00);
	do
	{
	SPI_WriteStatus(0x92);
	tStatus = SPI_ReadStatus();
	}
	while(tStatus != 0x90);
  }
  pCmdResult->success = DBG_SUCCESS;  
}

void DBG_VDWriteProtectSPI(DBG_CMD_INF *pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
  do
  {
    SPI_WriteStatus(pDbgCmdinf->param+2);
  }
  while(SPI_ReadStatus() != (pDbgCmdinf->param));
	  
  pCmdResult->success = DBG_SUCCESS;
}

void DBG_VDReadProtectSPI(DBG_CMD_INF *pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{	  
  pCmdResult->success = SPI_ReadStatus();
  pCmdResult->resv0 = 0x5A;
  pCmdResult->resv1 = 0x5B;
  pCmdResult->resv2 = 0x5C;
  pCmdResult->resv3 = 0x5D;
}

/*********************************************************************************************************
** Function Name         : DBG_VDPCBTest
** Function Describe     : DBG_VDPCBTest

** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
********************************************************************************************************/
void DBG_VDPCBTest(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
	INT32U ddrSizeType,testCnt;
	INT32U testStartAddr;
    REG8_WRITE(dbgDDRRstAddr, 0);	
	//ddrSizeType:64M 2:128M 4:256M 8:512M
	ddrSizeType = pDbgCmdinf->param;

	for(testCnt=0; testCnt<ddrSizeType; testCnt++)
	{
		testStartAddr = 0x50000000+(testCnt*64*1024*1024);
		DBG_FillDDRDW(testStartAddr, 1024*1024, 0x5555aaaa);
		if(!DBG_CheckDDRDW(testStartAddr, 1024*1024,0x5555aaaa))
		{
		  REG8_WRITE(dbgDDRRstAddr, 0);
  		  REG32_WRITE(dbgDDRRstAddr+4, testStartAddr);
		  return;
		}

		DBG_FillDDRDW(testStartAddr, 1024*1024, 0xffff0000);
		if(!DBG_CheckDDRDW(testStartAddr, 1024*1024,0xffff0000))
		{
		  REG8_WRITE(dbgDDRRstAddr, 0);
  		  REG32_WRITE(dbgDDRRstAddr+4, testStartAddr);
		  return;
		}
	}
    REG8_WRITE(dbgDDRRstAddr, 1);
    REG8_WRITE(dbgDDRRstAddr+1, 1);
	pCmdResult->success = DBG_SUCCESS;
}

/*********************************************************************************************************
** Function Name         : 
** Function Describe     : 
** Input  Parameter       : DBG_VDFindBlkByEaseAllCmd
** Output Parameter     :  None
** Global Parameter     :  None
********************************************************************************************************/
void DBG_VDFindBlkByEaseAllCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{
	cmd_fc_info cmd;
	int i=0;
	cmd.ch        = pDbgCmdinf->chan;
	if(dbgGloRunFlag == 1) 
	{
		return;
	}
	else
	{
		dbgCurBlk = 0;
	}
	
	dbgGloBlkCnts   = pDbgCmdinf->blkNum;
	dbgGloChpCnts  = pDbgCmdinf->chan*pDbgCmdinf->row;
	dbgGloRowCnts = pDbgCmdinf->row;


       dbgGloCriticalBlks            = pDbgCmdinf->criticalBlks; 
       dbgGloRealRowCnts               = pDbgCmdinf->realRowCnts;
	dbgGloInterleavingFlag     = pDbgCmdinf->interleavingFlag;
	dbgGloLun                        = pDbgCmdinf->lun;

	dbgGloRunFlag = 1;

	
	  for(i=0; i<dbgGloChpCnts; i++)
	  {
	  	bdblkCnts[i] = 0;
	  } 
	DBG_FillDDR(dbgDDRDataAddr, 16*1024, 0xff);
	pCmdResult->success = DBG_SUCCESS;
}
void DBG_GloCallFindBlkByEaseAllCmd()
{
  u8 tid[64];
  u8 cnts = 0;
  INT8U die=0;
  INT16U blk=0;
  cmd_fc_info cmd;
  u8 chip,dienum;


   for(blk=dbgCurBlk; blk<dbgGloBlkCnts; blk++)
   {
       dbgCurBlk = blk;	
	 
	if(cnts == 2)
	{
		break;
	}
	else
	{
	      cnts++;
	}
	// erase
	for(die=0;die<dbgGloChpCnts;die++)
	{

		INT8U chan    = die&0x7;
		INT8U row      = die>>3;
		INT16U phyBlk = blk;

		if(die == 32)
		{
			for(chip=0;chip<32;chip++)
			{
				while(tid_sts[tid[chip]]);
			}
		}

		if(dbgGloLun >= 2)
		{
			if(dbgGloInterleavingFlag == 1)
			{
				if(row >= dbgGloRealRowCnts)
				{
					row     = row - dbgGloRealRowCnts;
					phyBlk = phyBlk + dbgGloCriticalBlks;
				}
			}
		}
		
		cmd.ch         = chan;
		cmd.device    = row;
		cmd.phyblock = phyBlk;
		
		FC_Debug_EraseBlockEX(cmd);
		tid[die]=cur_tid;

		
     }
	for(die=0;die<dbgGloChpCnts;die++)
	{
		while(tid_sts[tid[die]]);
	}

	// write
	FC_FS_Setup_SSD();
	for(die=0;die<dbgGloChpCnts;die++){

		INT8U chan    = die&0x7;
		INT8U row      = die>>3;
		INT16U phyBlk = blk;

		if(die == 32)
		{
			for(chip=0;chip<32;chip++)
			{
				while(tid_sts[tid[chip]]);
			}
		}

		if(dbgGloLun >= 2)
		{
			if(dbgGloInterleavingFlag == 1)
			{
				if(row >= dbgGloRealRowCnts)
				{
					row     = row - dbgGloRealRowCnts;
					phyBlk = phyBlk + dbgGloCriticalBlks;
				}
			}
		}

//		if(row>3)
//		{
//			row       = row-4;
//			phyBlk  = phyBlk+4096; 
//		}
		
		if(1)
		{   // table write
	    
			cmd.ch           =    chan;
			cmd.device     =    row;
			cmd.phyblock =    phyBlk;
			cmd.phypage  =    0;
			cmd.buf_add   =    dbgDDRDataAddr-0x50000000;
			cmd.padbuf_add = dbgDDRPadAddr;
		}
		FC_Debug_ProgramPageEX(cmd);
		tid[die]=cur_tid;
      }
	for(die=0;die<dbgGloChpCnts;die++)
	{
		while(tid_sts[tid[die]]);
	}

	// read
	FC_ES_Setup_SSD();
	for(die=0;die<dbgGloChpCnts;die++){

		INT8U chan    = die&0x7;
		INT8U row      = die>>3;
		INT16U phyBlk = blk;

		if(die == 32)
		{			
			for(chip = 0;chip < 32;chip++)
			{
				while(tid_sts[tid[chip]]);
				if(tid_error[tid[chip]])
				{
					if(bdblkCnts[chip] >= 128)
					{
					   continue;
					}
					REG16_WRITE(dbgDDRDataAddr+chip*256+bdblkCnts[chip]*2, blk);
					bdblkCnts[chip]++;
		         }
			}
		}


		if(dbgGloLun >= 2)
		{
			if(dbgGloInterleavingFlag == 1)
			{
				if(row >= dbgGloRealRowCnts)
				{
					row     = row - dbgGloRealRowCnts;
					phyBlk = phyBlk + dbgGloCriticalBlks;
				}
			}
		}
		
//		if(row>3)
//		{
//			row       = row-4;
//			phyBlk  = phyBlk+4096; 
//		}
		
  	  	cmd.ch            = chan;  // channel
		cmd.device      = row;   // row
		cmd.phyblock  = phyBlk;
		cmd.phypage   = 0;
		cmd.buf_add    =   dbgDDRDataAddr-0x50000000;
		cmd.padbuf_add = dbgDDRPadAddr;
		FC_Debug_ReadPageEX(cmd);
		tid[die]=cur_tid;
      }

	if(dbgGloChpCnts > 32)
		dienum = 32;
	else
		dienum=0;
	
	for(die=dienum;die<dbgGloChpCnts;die++)
	{
		while(tid_sts[tid[die]]);
		if(tid_error[tid[die]])
		{
			if(bdblkCnts[die] >= 128)
			{
			   continue;
			}
			REG16_WRITE(dbgDDRDataAddr+die*256+bdblkCnts[die]*2, blk);
			bdblkCnts[die]++;
         }
	}
	if(dbgCurBlk == (dbgGloBlkCnts-1))
	{
		dbgGloRunFlag = 0;
	}

   }

}

void DBG_VDQueryFinishStatus(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult)
{

	// check findbadblk by eraseall finish status when param == 0
      if(pDbgCmdinf->param == 0)
      {
	      REG16_WRITE(dbgDDRRstAddr+2, dbgCurBlk);      
      }
}
void DBG_CalcRowAndBlk(DBG_CMD_INF* pDbgCmdinf)
{

	if(pDbgCmdinf->lun >= 2)
	{
		if(pDbgCmdinf->interleavingFlag == 1)
		{
			if(pDbgCmdinf->row >= pDbgCmdinf->realRowCnts)
			{
				pDbgCmdinf->row     = pDbgCmdinf->row - pDbgCmdinf->realRowCnts;
				pDbgCmdinf->blkNum = pDbgCmdinf->blkNum + pDbgCmdinf->criticalBlks;
			}
		}
	}

}

/*******************************************************************************************************
*                            End Of File
 ********************************************************************************************************/
