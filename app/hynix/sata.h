/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
*******************************************************************************************************/
#ifndef SSD_SATA_H
#define SSD_SATA_H

/*******************************************************************************************************
**                                       ATA Command                                                    
*******************************************************************************************************/
#define ATACMD_NOP                           0x00
//read
#define ATACMD_READ_SECTOR                   0x20
#define ATACMD_READ_SECTOR_EXT               0x24
#define ATACMD_READ_MUL                      0xC4
#define ATACMD_READ_MUL_EXT                  0x29
#define ATACMD_READ_DMA                      0xC8
#define ATACMD_READ_DMA_EXT                  0x25
#define ATACMD_READ_FPDMA_QUEUED             0x60
//write
#define ATACMD_WRITE_SECTOR                  0x30
#define ATACMD_WRITE_SECTOR_EXT              0x34
#define ATACMD_WRITE_MUL                     0xC5
#define ATACMD_WRITE_MUL_EXT                 0x39
#define ATACMD_WRITE_DMA                     0xCA
#define ATACMD_WRITE_DMA_EXT                 0x35
#define ATACMD_WRITE_FPDMA_QUEUED            0x61

#define ATACMD_READ_VERIFY                   0x40
#define ATACMD_READ_VERIFY_EXT               0x42

#define ATACMD_READ_NATIVE_MAXADR            0xF8
#define ATACMD_READ_NATIVE_MAXADR_EXT        0x27
#define ATACMD_READ_BUFFER                   0xE4
#define ATACMD_WRITE_BUFFER                  0xE8

#define ATACMD_FLUSH_CACHE                   0xE7
#define ATACMD_FLUSH_CACHE_EXT               0xEA

//Power
#define ATACMD_STANDBY_IM                    0xE0
#define ATACMD_STANDBY_IM_M                  0x94
#define ATACMD_IDLE_IM                       0xE1
#define ATACMD_IDLE_IM_M                     0x95
#define ATACMD_STANDBY                       0xE2
#define ATACMD_STANDBY_M                     0x96
#define ATACMD_IDLE                          0xE3
#define ATACMD_IDLE_M                        0x97
#define ATACMD_CHK_POWER_MODE                0xE5
#define ATACMD_CHK_POWER_MODE_M              0x98
#define ATACMD_SLEEP                         0xE6
#define ATACMD_SLEEP_M                       0x99


//feature
#define ATACMD_DEVICEDIAG                    0x90
#define ATACMD_IDFY_DEVICE                   0xEC
#define ATACMD_SET_MULTIMOD                  0xC6
#define ATACMD_SET_FEATURE                   0xEF
//General Purpose Logging Feature
#define ATACMD_READ_LOG_EXT                  0x2F
#define ATACMD_WRITE_LOG_EXT                 0x3F
//SMART Feature
#define ATACMD_SMART                         0xB0
//Security Feature
#define ATACMD_SECURITY_SETPSWD              0xF1
#define ATACMD_SECURITY_UNLOCK               0xF2
#define ATACMD_SECURITY_PREESE               0xF3
#define ATACMD_SECURITY_ERASE                0xF4
#define ATACMD_SECURITY_FREESELOCK           0xF5
#define ATACMD_SECURITY_DISPSWD              0xF6
#define ATACMD_RDMAXADDR                     0xF8
#define ATACMD_SETMAX                        0xF9
//Vendor
#define ATACMD_VDCMDALL                      0xFF

//obsolete
#define ATACMD_DNFW                          0x92
#define ATACMD_RECALIBRATE                   0x10
#define ATACMD_SEEK                          0x70
#define ATACMD_INIT_DEV_PARA                 0x91

//Add by Ian,2011.01.24
#define ATACMD_TRIM_DMA                      0x06
//-----------------------------------------------------------------------------
// Set Feature Subcommand Feature REG
//-----------------------------------------------------------------------------
//01h Enable 8-bit PIO transfer mode (CFA feature set only)
#define FEA_ENA_BYTEPIO                      0x01
//02h Enable write cache
#define FEA_ENA_WCACHE                       0x02
//03h Set transfer mode based on value in Sector Count register. Table 42 defines values.
#define FEA_SET_XMODE                        0x03
//04h Obsolete
//05h Enable advanced power management
#define FEA_ENA_APWRMAN                      0x05
//06h Enable Power-Up In Standby feature set.
#define FEA_ENA_PWRSTBY                      0x06
//07h Power-Up In Standby feature set device spin-up.
#define FEA_ENA_PWRDSPUP                     0x07
//09h Reserved for Address offset reserved area boot method technical report
#define FEA_RSV_BOOTRPT                      0x09
//0Ah Enable CFA power mode 1
#define FEA_ENA_CFPMOD1                      0x0A
//10h Enable use of SATA feature
#define FEA_ENA_SATA                         0x10
//20h -Reserved for technical report
//21h Reserved for technical report-
//31h Disable Media Status Notification
#define FEA_DIS_MEDSTANFY                    0x31
//33h Obsolete
//42h Enable Automatic Acoustic Management feature set, TO ctrl the Noise??
#define FEA_ENA_AUTOACOMAN                   0x42
//43h Set Maximum Host Interface Sector Times
#define FEA_SET_MAXINTSET                    0x43
//44h Obsolete
//54h Obsolete
//55h Disable read look-ahead feature
#define FEA_DIS_RDLKAHEAD                    0x55
//5Dh Enable release interrupt
#define FEA_ENA_RLSINTER                     0x5D
//5Eh Enable SERVICE interrupt
#define FEA_ENA_SERINTER                     0x5E
//66h Disable reverting to power-on defaults
#define FEA_DIS_REVPMODDF                    0x66
//77h Obsolete
//81h Disable 8-bit PIO transfer mode (CFA feature set only)
#define FEA_DIS_BYTEPIO                      0x81
//82h Disable write cache
#define FEA_DIS_WCACHE                       0x82
//84h Obsolete
//85h Disable advanced power management
#define FEA_DIS_APWRMAN                      0x85
//86h Disable Power-Up In Standby feature set.
#define FEA_DIS_PWRSTBY                      0x86
//88h Obsolete
//89h Reserved for Address offset reserved area boot method technical report
//8Ah Disable CFA power mode 1
#define FEA_DIS_CFPMOD1                      0x8A
//90h Disable use of SATA feature
#define FEA_DIS_SATA                         0x90
//95h Enable Media Status Notification
//99h Obsolete
//9Ah Obsolete
//Aah Enable read look-ahead feature
#define FEA_ENA_RDLKAHEAD                    0xAA
//Abh Obsolete
//BBh Obsolete
//C2h Disable Automatic Acoustic Management feature set
#define FEA_DIS_AUTOACOMAN                   0xC2
//CCh Enable reverting to power-on defaults
#define FEA_ENA_REVPMODDF                    0xCC
//DDh Disable release interrupt
#define FEA_DIS_RLSINTER                     0xDD
//Deh Disable SERVICE interrupt
#define FEA_DIS_SERINTER                     0xDE
//E0h Obsolete
//F0h-FFh Reserved for assignment by the CompactFlash? Association

//PIO default mode 00000b 000b
//PIO default mode, disable IORDY 00000b 001b
#define XFER_PIO_DFMD                        0x00//00000b
//PIO flow control transfer mode 00001b mode
#define XFER_PIO_FLMD                        0x01//00001b
//Retired 00010b na
//Multiword DMA mode 00100b mode
#define XFER_DMA_MTMD                        0x04//00100b
//Ultra DMA mode 01000b mode
#define XFER_DMA_ULMD                        0x08//01000b

//-----------------------------------------------------------------------------
// Advanced power management levels
//-----------------------------------------------------------------------------
//Maximum performance                                                 FEh
//Intermediate power management levels without Standby   81h-FDh
//Minimum power consumption without Standby                 80h
//Intermediate power management levels with Standby       02h-7Fh
//Minimum power consumption with Standby                      01h
//Reserved                                                                  FFh
//Reserved                                                                  00h
#define PERFM_MAXCONSM_MOD                   0xFE
#define PERFM_INTNOSTBY_MAX                  0xFD
#define PERFM_INTNOSTBY_MIN                  0x81
#define PERFM_MINNOSTBY_MOD                  0x80
#define PERFM_INTENSTBY_MAX                  0x7F
#define PERFM_INTENSTBY_MIN                  0x02
#define PERFM_MINENSTBY_MOD                  0x01


//-----------------------------------------------------------------------------
// SATA sub feature (sector count register)
//-----------------------------------------------------------------------------
#define SUBFEA_NZERO_OFFSET                  0x01//non-zero buffer offset in dma setup fis
#define SUBFEA_AUTO_ACTIVATE                 0x02//dma setup fis auto-activate optimization
#define SUBFEA_POWER_TRAN                    0x03//device-initiated interface power state transitions
#define SUBFEA_INORDER_DATA                  0x04//guaranteed in-order data delivery 
#define SUBFEA_ASYN_NOTIFY                   0x05//asynchronous notification
#define SUBFEA_SETTING_PRES                  0x06//software settings preservation

#define M_CYLNUM                             12
#define M_HEADNUM                            16
#define M_SECNUM                             63

//-----------------------------------------------------------------------------
// SATA Status Register Meaning
//-----------------------------------------------------------------------------
#define STATUS_BSY                           0x80// Busy
#define STATUS_DRDY                          0x40// Drive Ready
#define STATUS_DF                            0x20// Drive Fault
#define STATUS_DSC                           0x10// Drive Seek Complete
#define STATUS_DRQ                           0x08// Data Request
#define STATUS_CORR                          0x04// Corrected Data
#define STATUS_IDX                           0x02// Index
#define STATUS_ERROR                         0x01// Error

//-----------------------------------------------------------------------------
// SATA Error Register Meaning
//-----------------------------------------------------------------------------
#define ERROR_BBK                            0x80// Bad Block Detected
#define ERROR_UNC                            0x40// Uncorrectable Data Error
#define ERROR_MC                             0x20// Media Change
#define ERROR_IDNF                           0x10// ID Not Found
#define ERROR_MCR                            0x08// Media Change Requested
#define ERROR_ABRT                           0x04// Abort Command
#define ERROR_TK0NF                          0x02// Track 0 Not Found
#define ERROR_AMNF                           0x01// Address Mark Not Found
#define ERROR_NONE                           0x00// no any error

/*******************************************************************************************************
**                                      SATAII Parameters and Function
********************************************************************************************************/
#define DMA_MODE                             0
#define PIO_MODE                             1
#define NCQ_MODE                             2

#define READ_CMD                             0
#define WRITE_CMD                            1
#define ERZ_CMD                              2

//Fis Type definition
#define FISTYPE_27                           0x27  /* Register FIS (H2D) */
#define FISTYPE_34                           0x34  /* Register FIS (D2H) */
#define FISTYPE_39                           0x39  /* DMA Activate FIS */
#define FISTYPE_41                           0x41  /* DMA Setup FIS */
#define FISTYPE_46                           0x46  /* Data FIS */
#define FISTYPE_5F                           0x5F  /* PIO Setup FIS */
#define FISTYPE_A1                           0xA1  /* Set Device Bits FIS */


#define TXRX_UNKNOWN                         0
#define TXRX_DONE                            1
#define TXRX_ERR                             2

//Sata_bitmask config
#define R0010_DBIT_ON                        (1 << 1)
#define R0010_DBIT_OFF                       (0)
#define R0010_ABIT_ON                        (1 << 2)
#define R0010_ABIT_OFF                       (0)
#define R0010_CBIT_ON                        (1 << 3)
#define R0010_CBIT_OFF                       (0)
#define R0010_IBIT_ON                        (1 << 4)
#define R0010_IBIT_OFF                       (0)

#define SATA_FIS_RETOUT                       0x01000000

#define CONFIG_DEF_HEADS_PER_CYLINDER        16
#define CONFIG_DEF_SECTS_PER_TRACK           63
#define CONFIG_MAX_SECTS_PER_PIOMULTIPLE     16
#define CONFIG_MULTIWORD_DMA_MODE            2
#define CONFIG_ULTRA_DMA_MODE                5
#define CONFIG_PIO_MODE                      4

#define ATA_PM_IDLE                          0x80
#define ATA_PM_STANDBY                       0x00
#define ATA_PM_SLEEP                         0x01

//WORD23 24 25 26----Firmware revision
#define IDFY_W21_WCACH                       0x0015

#define IDFY_W23_REV                         0x0017
#define IDFY_W24_REV                         0x0018
#define IDFY_W25_REV                         0x0019
#define IDFY_W26_REV                         0x001A

#define IDFY_W23_FV                          0x0017   //WORD 23
#define IDFY_W24_FV                          0x0018   //WORD 24
#define IDFY_W25_FV                          0x0019   //WORD 25
#define IDFY_W26_FV                          0x001A   //WORD 26


#define IDFY_W27_MDN                         0x001B
#define IDFY_W28_MDN                         0x001C
#define IDFY_W29_MDN                         0x001D
#define IDFY_W30_MDN                         0x001E
#define IDFY_W31_MDN                         0x001F
#define IDFY_W32_MDN                         0x0020
#define IDFY_W33_MDN                         0x0021
#define IDFY_W34_MDN                         0x0022
#define IDFY_W35_MDN                         0x0023



#define IDFY_W01_CHS                         0x0001
#define IDFY_W03_CHS                         0x0003
#define IDFY_W06_CHS                         0x0006
#define IDFY_W53_CHS                         0x0035
#define IDFY_W54_CHS                         0x0036
#define IDFY_W55_CHS                         0x0037
#define IDFY_W56_CHS                         0x0038
#define IDFY_W57_CHS                         0x0039
#define IDFY_W58_CHS                         0x003A

#define IDFY_W47_MUL                         0x002F
#define IDFY_W59_MUL                         0x003B

#define IDFY_W60_28SIZE                      0x003C
#define IDFY_W61_28SIZE                      0x003D

#define IDFY_W69_TRIM                        0x0045
#define IDFY_W105_TRIM                       0x0069
#define IDFY_W169_TRIM                       0x00A9
#define IDFY_W75_NCQ                         0x004B
#define IDFY_W76_NCQ                         0x004C
#define IDFY_W78_NCQ                         0x004E
#define IDFY_W79_NCQ                         0x004F

#define IDFY_W82_FEA                         0x0052
#define IDFY_W84_FEA                         0x0054
#define IDFY_W85_FEA                         0x0055
#define IDFY_W86_FEA                         0x0056
#define IDFY_W88_FEA                         0x0058

//#define IDFY_W92_REV				0x005C
#define IDFY_W92_MTPSWDVER                   0x005C
#define IDFY_W93_HWRST                       0x005D

#define IDFY_W100_48SIZE                     0x0064
#define IDFY_W101_48SIZE                     0x0065
#define IDFY_W102_48SIZE				     0x0066
#define IDFY_W103_48SIZE                     0x0067

//#define IDFY_W128_SECURITY                0x0080
#define IDFY_W128_PSWDSTATUS                 0x0080
#define IDFY_W129_STA                        0x81     //WORD129  ( vendor specific )----SSD STATE (0x00F0----Security erased)
#define IDFY_W222_NCQ                        0x00DE

#define SSD_IDFYCKSM_OFST                    0x00FF

#define NCQQUEUEDEPTH                        32

#define PWR_STBYMOD                          0x00
#define PWR_IDLEMOD                          0x80
#define PWR_ACTVMOD                          0xFF

#define NCQ_RD_CMD                           0x60                        // NCQ read op code.
#define NCQ_WR_CMD                           0x61                        // NCQ write op code.


#define BFR_SSD_LOCATION                     0x50000000
#define BFR_SSD_RDCNT                        256
#define BFR_SSD_WRCNT                        256
#define BFR_SSD_VNDCNT                       1
#define BFR_SSD_VNDINDEX                     (BFR_SSD_RDCNT + BFR_SSD_WRCNT)
#define BFR_SSD_COUNT                        (BFR_SSD_RDCNT + BFR_SSD_WRCNT)
#define BFR_SSD_ALLCNT                       (BFR_SSD_RDCNT + BFR_SSD_WRCNT + BFR_SSD_VNDCNT)
#define BFR_SSD_RDMASK                       0xFF
#define BFR_SSD_WRMASK                       0x1FF
#define mBFR_SUBSEG_SIZE                     8UL
#define mSECTOR_SIZE                         0x200UL

#define CMDQHSMAXNUM                         0x08
#define CMDQHSMAXMASK                        0x07
#define CMDQFSMAXNUM                         0x04
#define CMDQFSMAXMASK                        0x03

#define CMDFLAG_NTQCMD                       (0 << 0)
#define CMDFLAG_QCMD                         (1 << 0)
#define CMDFLAG_RDCMD                        (0 << 1)
#define CMDFLAG_WRCMD                        (1 << 1)
#define CMDFLAG_NTDCMD                       (0 << 2)
#define CMDFLAG_DCMD                         (1 << 2)
#define CMDFLAG_NTEXTCMD                     (0 << 3)
#define CMDFLAG_EXTCMD                       (1 << 3)

typedef struct ata_reg
{
  INT16U ATA_REG_FEA;
  INT16U ATA_REG_SCNT;
  INT8U ATA_REG_LBAL;
  INT8U ATA_REG_LBAM;
  INT8U ATA_REG_LBAH;
  //INT8U ATA_REG_PREFEA;
  //INT8U ATA_REG_PRESCNT;
  INT8U ATA_REG_PRELBAL;
  INT8U ATA_REG_PRELBAM;
  INT8U ATA_REG_PRELBAH;

  INT8U ATA_REG_DEVHEAD;
  INT8U ATA_REG_CMD;
} ATA_REG;

typedef struct cmdqentry
{
    struct      cmdqentry  *pNext;                        
    struct      cmdqentry  *pPrevious;   
//For Basic Command	
    ATA_REG     atareg;                           

//For Disk Read or Write Command
	INT32U  LbaAdr;
	INT32U  SecCnt;
	INT8U   NCQSlotNum;
	INT8U   NCQTag;
	union
	{
	 INT8U  all;
	 struct
	 {
	   INT8U   NCQCmd   : 1;   // Value 0 for other Command,1 for NCQ Command, 
	   INT8U   WRCMD    : 1;  // Value 0 for Read Command, 1 for Write Command
	   INT8U   DiskCmd  : 1;  // Value 0 for Regular Command, 1 for Disk R/W Command
	   INT8U   ExtCmd   : 1;  // Value 0 for LBA28 Command, 1 for LBA48 Command
	   INT8U   RSVD     : 4;  // RSVD bits in flag
	   
	 }bits;
	}CmdFlag;
	INT8U   ErrFlag;
}CMDQENTRY;

typedef struct cxsblink
{
    struct      cxsblink  *pNext;                        
    struct      cxsblink  *pPrevious;  	
//For CXSB Transfer 
	INT8U   HSNum;
    INT8U   FSNum;
	INT8U   NCQTag;
	union
	{
	 INT8U  all;
	 struct
	 {
	   INT8U   NCQCmd   : 1;
	   INT8U   WRCMD    : 1;  
	   INT8U   EndBit   : 1;
	   INT8U   ExecBit  : 1;
	   INT8U   RSVD     : 4; 
	   
	 }bits;	
	}CxsbFlag;
	INT16U  HSPtrNum;
	INT16U  XferLen;
	INT16U  XferSSDCnt;
	INT32U  XferDDRByteAddr;
}CXSBLINK;

typedef struct cmdqparam
{
  INT8U cmdqIdleCnt;
  INT8U cmdqRcrdCnt;
  INT8U cxsbIdleCnt;
  INT8U cxsbWaitCnt;
  INT8U cxsbXferCnt;
  INT8U curHSNum;
  INT8U curFSNum;
  CMDQENTRY *pFreeListHead;
  CMDQENTRY *pFreeListTail;
  CMDQENTRY *pRcrdListHead;
  CMDQENTRY *pRcrdListTail;

  CXSBLINK *pCxsbFreeHead;
  CXSBLINK *pCxsbFreeTail;
  CXSBLINK *pCxsbXferHead;
  CXSBLINK *pCxsbXferTail;  
 
}CMDQPARAM;

extern CMDQENTRY CmdQueuePool[NCQQUEUEDEPTH];
extern CXSBLINK CxsbXferPool[NCQQUEUEDEPTH];
extern CMDQPARAM CmdQueueParam;

extern volatile BOOLEAN bPowerOff, bRamDisk;
extern volatile INT8U CurIDFYCheckSum, BSemNATACMD;
extern volatile INT8U BSemCurXferFinCnt;
extern volatile INT8U CurPwerMode, CurSleepPend;
extern volatile INT16U *SSD_IDFYDATA;
extern volatile INT32U CurMaxLBAAdr;
extern mtBFR_SSD  *pmBfrSSD;
 

INT16U GetIDFYData(INT8U WordOffset);
void UpdateIDFYData(INT16U WordOffset, INT16U WordVal);
void PrepareIDFYData(void);
BOOLEAN XferIDFYData(void);
BOOLEAN BufDataXfer(void);
void SetFeature(ATA_REG *pCurAtaReg);
void StatusReturn(BOOLEAN Rval);
void SetRSTStatus(INT8U Mode);
void InitSATA(void);
void SataReadDDRData(INT32U DDRByteAddr, INT32U DataSecSize);
void SataWriteDDRData(INT32U DDRByteAddr, INT32U DataSecSize);
CMDQENTRY *CmdQGetFromFree(void);
void CmdQSaveToRcrd(CMDQENTRY * pCmdQ);
void CmdQReturnToIdle(CMDQENTRY * pCmdQ);

CXSBLINK *CxsbGetFromFree(void);
void CxsbSaveToXfer(CXSBLINK * pCxsb);
void CxsbReturnToIdle(CXSBLINK * pCxsb);

BOOLEAN CommandDecode(void);
void CommandNTDiskProcess(CMDQENTRY *pCurCmdEntry);


//Marvell function
void mSendStatusToHost(void);

#endif
/*******************************************************************************************************
                                            End Of File
********************************************************************************************************/
