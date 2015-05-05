/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
**----------------------------------------File Information----------------------------------------------
** File Name             : Ssd_debug.h
** File Version          : V1.0
** File Creator          : Qin Zhi
** File Create Data      : 2012-08-23
** File Description      : SATA vendor command debug for new CQ structure macro definition
**
**----------------------------------------File History--------------------------------------------------
** Modified Man          : 
** Modified Date         : 
** Modified Info         : 
**----------------------------------------File Current Status-------------------------------------------
** Update Date         : 2012-08-23
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/

#ifndef SSD_SATA_VENDOR_COMMAND_DEBUG_H
#define SSD_SATA_VENDOR_COMMAND_DEBUG_H



#define CALC_ROWADD(blk, pg)           ((blk<<PAGEPBLOCK_SHIFT)+pg)
#define MULTI_1K_VALUE                  8

/*
*1.1  Common Command Format
* ----------------------------------------------------------------------------------------------------------------------------
* |BYTE	  | 151-24   |23-20    |	19-16	|  15-12	  |   11-8     |7-6     |5-4  |  3             |2    |1    |   0     |
* ----------------------------------------------------------------------------------------------------------------------------
* |Content |  pad    | SecCnt  |  LBA       |  Parameter  |	DDR Addr   |PgNum   |BLK  | Bypass(0:0)    |     |     |         |
* |       |          |         |            |             |            |     	|     | TBFLG(1:1)     |Row |Chan |VNDCMD    |
* |       |          |         |            |             |            |     	|     | Protocol(7:2)  |     |     |         |
* ----------------------------------------------------------------------------------------------------------------------------
* |BYTE	  |511-152   |         |            |             |            |     	|     |                |     |     |         |
*-----------------------------------------------------------------------------------------------------------------------------
*| Content |Resv     |         |            |             |            |     	|     |                |     |     |         |
*|        |          |         |            |             |            |     	|     |                |     |     |         |
*-----------------------------------------------------------------------------------------------------------------------------
*/

// Debug Command Format
typedef struct _DBG_CMD_INF
{
	INT8U vndCmd;
	INT8U chan;
	INT8U row;
	union{
		INT8U uValue;
		struct
		{
			INT8U byPassBits:1;
			INT8U tableRDBits:1;
			INT8U protocolBits:6;
		}bits;
	}flag;

	INT16U blkNum;
	INT16U pageNum;
	INT32U ddrAddr;
	INT32U param;
	INT32U lba;
	INT32U SecCnt;
	INT8U  padInf[128];
	INT8U  interleavingFlag;
	INT8U  realRowCnts;
	INT16U criticalBlks;
	INT8U  lun;
	INT8U  resv0;
	INT8U  resv1;
	INT8U  resv2;
}DBG_CMD_INF, *P_DBG_CMD_INF;

// Debug Command Result Format
typedef struct _DBG_CMD_RESULT_
{
	INT8U success; //0:Fail 1:success
	INT8U resv0;
	INT8U resv1;
	INT8U resv2;
	INT8U resv3;
} DBG_CMD_RESULT, *P_DBG_CMD_RESULT;

// return result type define
#define DBG_SUCCESS   1
#define DBG_FAIL      0 

// sub cmd define
#define DBG_ARG_SBCMD_WRCMD           0x00
#define DBG_ARG_SBCMD_RDDAT           0x01
#define DBG_ARG_SBCMD_WRDAT           0x02
#define DBG_ARG_SBCMD_RDRSLT          0x03

// vendor cmd define
#define DBG_CMD_RST                                     0x01
#define DBG_CMD_SETFEA                               0x02
#define DBG_CMD_RDID                                    0x03
#define DBG_CMD_RDPAGE                              0x04
#define DBG_CMD_WRPAGE                             0x05
#define DBG_CMD_ERZBLOCK                          0x06
#define DBG_CMD_RDDDR                                0x07
#define DBG_CMD_WRDDR                               0x08
#define DBG_CMD_FINDBADBLK                       0x09
#define DBG_CMD_WRITEPAD                          0x0a
#define DBG_CMD_RDFW_SPI                          0x0b
#define DBG_CMD_WRFW_SPI                         0x0c
#define DBG_CMD_ERASE_SPI                         0x0d
#define DBG_CMD_PCB_TEST                          0x0e
#define DBG_CMD_FDBADBLK_BY_ERASEALL 0x0f
#define DBG_CMD_QUERY_FINISH_STATUS       0x10
#define DBG_CMD_CHECKUNECC                     0x11
#define DBG_CMD_READPAD                           0x12
#define DBG_CMD_GETREGDUMP            0x13
#define DBG_CMD_WRITE_REG		0x21
#define DBG_CMD_WP_SPI				  0x23
#define DBG_CMD_STS_SPI				  0x24
#define DBG_CMD_WR2PPAGE                 0x40
#define DBG_CMD_SETFEATURE                 0x41
#define DBG_CMD_READCHIPID                 0x42
#define DBG_CMD_FLASHRESET                0x43
// vendor ddr addr define
//#define DBG_DDR_BASE_ADDR    (0x50000000+0x10000000 - (64*1024))
//#define DBG_DDR_CMD_ADDR     ( DBG_DDR_BASE_ADDR)                //0x5FFFF0000
//#define DBG_DDR_DATA_ADDR    (DBG_DDR_CMD_ADDR+(512))            //0x5FFFF0200
//#define DBG_DDR_RST_ADDR     (DBG_DDR_DATA_ADDR+32*1024)         //0x5FFFF8200
//#define DBG_DDR_PAD_ADDR     (DBG_DDR_RST_ADDR+512)              //0x5FFFF8400
//#define DBG_DDR_METABUF_ADDR (DBG_DDR_PAD_ADDR+512)              //0x5FFFF8600

// vendor ddr addr define
#define DBG_DDR_BASE_ADDR    (0x50000000+0x10000000 - (128*1024))
#define DBG_DDR_CMD_ADDR     ( DBG_DDR_BASE_ADDR)                //0x5FFE0000
#define DBG_DDR_DATA_ADDR    (DBG_DDR_CMD_ADDR+(512))            //0x5FFE0200
#define DBG_DDR_RST_ADDR     (DBG_DDR_DATA_ADDR+64*1024)         //0x5FFF0200
#define DBG_DDR_PAD_ADDR     (DBG_DDR_RST_ADDR+512)              //0x5FFF0400
#define DBG_DDR_METABUF_ADDR (DBG_DDR_PAD_ADDR+512)              //0x5FFF0600


// global ram addr  variable declare
extern INT32U dbgDDRBaseAddr;
extern INT32U dbgDDRCmdAddr;
extern INT32U dbgDDRDataAddr;
extern INT32U dbgDDRRstAddr;
extern INT32U dbgDDRPadAddr;

extern INT16U dbgGloCriticalBlks;
extern INT8U   dbgGloRealRowCnts;
extern INT8U   dbgGloInterleavingFlag;
extern INT8U   dbgGloLun;

extern INT16U  dbgGloBlkCnts;
extern INT8U   dbgGloChpCnts;
extern INT8U   dbgGloRowCnts ;
extern INT8U   dbgGloRunFlag;
extern INT16U  dbgCurBlk;
extern INT8U    bdblkCnts[64];
#define PAGE_SIZE 16*1024


//FLASHTYPE TAG
#define FLASH_TYPE_TOSHIBA 1
#define FLASH_TYPE_SANDISK 2
#define FLASH_TYPE_SAMSUNG 3

void DBG_CheckDone();

// Init Debug function called by InitSata func
void InitDebug(void);
// Fill ddr
void  DBG_FillDDR(INT32U StartAddr, INT32U Len, INT8U Value);
void  DBG_FillDDRDW(INT32U StartAddr, INT32U Len, INT32U Value);
INT8U DBG_CheckDDRDW(INT32U StartAddr, INT32U Len, INT32U chkValue);

// follow  distribute function
void DBG_VDOperation(CMDQENTRY *pCurCmdEntry);
void DBG_VendorAllCmd(CMDQENTRY *pCurCmdEntry);

// follow sub cmd fuction
void DBG_RDResultSubCmd(CMDQENTRY *pCurCmdEntry);
void DBG_WRDataSubCmd(CMDQENTRY *pCurCmdEntry);
void DBG_RDDataSubCmd(CMDQENTRY *pCurCmdEntry);

// follow vendor cmd fuction
void DBG_VDReadDDRCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDWriteDDRCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDRstCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDSetFeaCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDReadAllIDCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDSetFeatureCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDREADCHIPIDCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDFLASHRESETCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDReadPageCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDWritePageCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VD2PlaneWritePageCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDEraseBlkCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDFindBlkCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDWritePadDataCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDReadPadDataCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);

void DBG_ReadSPIStatus(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDReadFWSPI(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDWriteFWSPI(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDWriteProtectSPI(DBG_CMD_INF *pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDReadProtectSPI(DBG_CMD_INF *pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDEraseSPI(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDPCBTest(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDFindBlkByEaseAllCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_VDQueryFinishStatus(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_CheckUneccCmd(DBG_CMD_INF* pDbgCmdinf, P_DBG_CMD_RESULT pCmdResult);
void DBG_CalcRowAndBlk(DBG_CMD_INF* pDbgCmdinf);
#endif 
/*****************************************************************************************************
**                                  End of File                                                       
 ******************************************************************************************************/
