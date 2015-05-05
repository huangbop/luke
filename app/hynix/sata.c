/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "HEAD.H"
const INT16U IDFY_DATA[128] = 
{

  0x0040, 0x3FFF, 0xC837, 0x0010, 0x0000, 0x0000, 0x003F, 0x0000,  // 000~007
  0x0000, 0x0000, 0x3030, 0x3037, 0x3434, 0x3030, 0x3031, 0x2020,  // 008~015
  0x2020, 0x2020, 0x2020, 0x2020, 0x0000, 0x0000, 0x0000, 0x5665,  // 016~023
  0x722E, 0x3030, 0x3031, 0x4D52, 0x2D45, 0x5450, 0x5635, 0x4445,  // 024~031
  0x4D4F, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020,  // 032~039
  0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x8010,  // 040~047
  0x0000, 0x0F00, 0x4000, 0x0200, 0x0000, 0x0007, 0x3FFF, 0x0010,  // 048~055
  0x003F, 0xFC10, 0x00FB, 0x0110, 0x0000, 0x03C0, 0x0000, 0x0007,  // 056~063
  0x0003, 0x0078, 0x0078, 0x0078, 0x0078, 0x0000, 0x0000, 0x0000,  // 064~071
  0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0048, 0x0040,  // 072~079
  0x00FE, 0x0021, 0x7860, 0x5000, 0x4000, 0x7860, 0x1000, 0x4000,  // 080~087
  0x007F, 0x0001, 0x0000, 0x0000, 0xFFFE, 0x0000, 0x0000, 0x0000,  // 088~095
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x03C0, 0x0000, 0x0000,  // 096~103
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // 104~111
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4000,  // 112~119
  0x4000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // 120~127

//AS 256GB Ramdisk
/*
0x4000, 0xFF3F, 0x37C8, 0x1000, 0x0000, 0x0000, 0x3F00, 0x0000,  // 000~007
0x0000, 0x0000, 0x3030, 0x3730, 0x3434, 0x3030, 0x3130, 0x3030,  // 008~015
0x3030, 0x3030, 0x3030, 0x3031, 0x0000, 0x0000, 0x0000, 0x6556,  // 016~023
0x2E72, 0x3030, 0x3130, 0x524D, 0x452D, 0x4854, 0x4259, 0x4952,  // 024~031
0x4244, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020,  // 032~039
0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x2020, 0x0180,  // 040~047
0x0000, 0x000F, 0x0040, 0x0002, 0x0000, 0x0700, 0xFF3F, 0x1000,  // 048~055
0x3F00, 0x10FC, 0xFB00, 0x0101, 0x0000, 0x000F, 0x0000, 0x0000,  // 056~063
0x0300, 0x7800, 0x7800, 0x7800, 0x7800, 0x0000, 0x0000, 0x0000,  // 064~071
0x0000, 0x0000, 0x0000, 0x0000, 0x0400, 0x0000, 0x4800, 0x4000,  // 072~079
0xFE00, 0x2100, 0x6070, 0x0054, 0x0040, 0x6070, 0x0014, 0x0040,  // 080~087
0x7F00, 0x0100, 0x0000, 0x8000, 0x0000, 0x0020, 0x0000, 0x0000,  // 088~095
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0100, 0x0000, 0x0000,  // 096~103
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // 104~111
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0040,  // 112~119
0x0040, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // 120~127
*/
};

const INT8U mCmdVectorTable[256] =                                                                                 
{                                                                                                                                                                                     
0,                                                    // 0x00                              
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
                                                                                           
0,                                                    // 0x10                              
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
                                                                                           
(CMDFLAG_RDCMD + CMDFLAG_DCMD),                       // 0x20: read sector                 
(CMDFLAG_RDCMD + CMDFLAG_DCMD),                       // 0x21: read sector                                                                                                                                           
(CMDFLAG_RDCMD),                                                                  
(CMDFLAG_RDCMD),                                                                                                                                                                                           
(CMDFLAG_RDCMD + CMDFLAG_DCMD + CMDFLAG_EXTCMD),      // 0x24: read sector EXT          
(CMDFLAG_RDCMD + CMDFLAG_DCMD + CMDFLAG_EXTCMD),      // 0x25: read dma EXT             
0,                                                                                         
CMDFLAG_EXTCMD,                                       // 0x27 ,read native max address ext
0,                                                                                         
(CMDFLAG_EXTCMD + CMDFLAG_RDCMD + CMDFLAG_DCMD),      // 0x29: Read Multiple EXT        
0,                                                    // 0x2A                              
0,                                                    // 0x2B                              
0,                                                                                         
0,                                                                                         
0,                                                                                                                                                                                                                   
CMDFLAG_EXTCMD,                                       // 0x2F: read log ext                   
                                                                                           
(CMDFLAG_WRCMD + CMDFLAG_DCMD),                       // 0x30: write sector                 
(CMDFLAG_WRCMD + CMDFLAG_DCMD),                       // 0x31: write sector                                                                                                                                           
(CMDFLAG_WRCMD),                                                                 
(CMDFLAG_WRCMD),                                                                                                                                                                                           
(CMDFLAG_EXTCMD + CMDFLAG_WRCMD + CMDFLAG_DCMD),      // 0x34: write sectors EXT       
(CMDFLAG_EXTCMD + CMDFLAG_WRCMD + CMDFLAG_DCMD),      // 0x35: write dma EXT           
0,                                                                                         
0,                                                                                         
0,                                                                                         
 (CMDFLAG_EXTCMD + CMDFLAG_WRCMD + CMDFLAG_DCMD),     // 0x39: Write Multiple EXT     
0,                                                    // 0x3A                              
0,                                                    // 0x3B                              
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
                                                                                           
0                             ,                       // 0x40  read verify w/o retry        
0                             ,                       // 0x41  read verify                  
(CMDFLAG_EXTCMD)              ,                       // 0x42  read verify EXT                                                                                                                                   
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
                                                                                           
0,                                                    // 0x50                              
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
                                                                                           
(CMDFLAG_QCMD + CMDFLAG_EXTCMD + CMDFLAG_RDCMD + CMDFLAG_DCMD),     // 0x60                         
(CMDFLAG_QCMD + CMDFLAG_EXTCMD + CMDFLAG_WRCMD + CMDFLAG_DCMD),     // 0x61                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
                                                                                           
0,                                                    // 0x70: seekCmd                     
0,                                                    // 0x71: seekCmd                     
0,                                                    // 0x72: seekCmd                     
0,                                                    // 0x73: seekCmd                     
0,                                                    // 0x74: seekCmd                     
0,                                                    // 0x75: seekCmd                     
0,                                                    // 0x76: seekCmd                     
0,                                                    // 0x77: seekCmd                     
0,                                                    // 0x78: seekCmd                     
0,                                                    // 0x79: seekCmd                     
0,                                                    // 0x7a: seekCmd                     
0,                                                    // 0x7b: seekCmd                     
0,                                                    // 0x7c: seekCmd                     
0,                                                    // 0x7d: seekCmd                     
0,                                                    // 0x7e: seekCmd                     
0,                                                    // 0x7f: seekCmd                     
                                                                                           
0,                                                    // 0x80                              
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
                                                                                           
0,                                                    // 0x90                              
0,                                                    // 0x91: Init Device                   
CMDFLAG_EXTCMD,                                       // 0x92  Download Microcode          
0,                                                                                         
0,                                                    // 0x94: StandBy Immediate           
0,                                                    // 0x95: Idle Immediate              
0,                                                    // 0x96: StandBy                     
0,                                                    // 0x97: mIdle                       
0,                                                    // 0x98: Check power mode            
0,                                                    // 0x99h                             
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
                                                                                           
0,                                                    // 0xA0                              
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
                                                                                           
0,                                                    // 0xB0                                                                                                                                                                  
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
                                                                                           
0,                                                    // 0xC0                              
0,                                                                                         
0,                                                                                         
0,                                                    // 0xC3                                                                                                                                                        
(CMDFLAG_RDCMD + CMDFLAG_DCMD),                       // 0xC4: Read Multiple               
(CMDFLAG_WRCMD + CMDFLAG_DCMD),                       // 0xC5: Write Multiple              
0,                                                    // 0xC6: Set Multiple                                                                                                                                          
0,                                                                                         
(CMDFLAG_RDCMD + CMDFLAG_DCMD),                       // 0xc8: read dma                    
(CMDFLAG_RDCMD + CMDFLAG_DCMD),                       // 0xc9: read dma                    
(CMDFLAG_WRCMD + CMDFLAG_DCMD),                       // 0xca: write dma                   
(CMDFLAG_WRCMD + CMDFLAG_DCMD),                       // 0xcb: write dma                                                                                                                                             
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,   
                                                           
0,                                                    // 0xD0                              
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                                                                                                                                                   
0,                                                                                         
0,                                                                                         
                                                                                           
0,                                                    // 0xE0: StandBy Immediate           
0,                                                    // 0xE1: mIdle Immediate             
0,                                                    // 0xE2: StandBy                     
0,                                                    // 0xE3: mIdle                       
0,                                                    // 0xE4: Read Buffer                 
0,                                                    // 0xE5: Check power mode            
0,                                                    // 0xE6h                             
0,                                                    // 0xE7h                             
0,                                                                                         
0,                                                                                                                                                                                                                   
CMDFLAG_EXTCMD,                                       // 0xEAh Flush Cache EXT                                                                                                                                       
0,                                                                                         
0,                                                    // 0xEC: Indentify Drive             
0,                                                                                         
0,                                                                                         
0,                                                    // 0xef: set features                

0,                                                    // 0xf0                                                                                                                                                                                                                                                                                                   
0,                                                    //f1                                                                                  
0,                                                    //f2                                                                                  
0,                                                    //f3                                                                                  
0,                                                    //f4                                                                                  
0,                                                    //f5                                                                                  
0,                                                    //f6                                                                                                                                                                                                
0,                                                    //f7                                                                                  
0,                                                    // 0xF8: read native max address 
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
0,                                                                                         
};                                                                                                                        


#define SSD_IDFYDDRBYTEADDR                  0x5FFFFE00
#define SSD_IDFYDATA                         ((volatile unsigned short *)(SSD_IDFYDDRBYTEADDR))

CMDQENTRY CmdQueuePool[NCQQUEUEDEPTH];
CXSBLINK CxsbXferPool[NCQQUEUEDEPTH];
CMDQPARAM CmdQueueParam;

volatile BOOLEAN bPowerOff, bRamDisk;
volatile INT8U CurIDFYCheckSum, BSemNATACMD;
volatile INT8U BSemCurXferFinCnt;
volatile INT8U CurPwerMode, CurSleepPend;


volatile INT32U CurMaxLBAAdr;

mtBFR_SSD mBfrSSD;
mtBFR_SSD *pmBfrSSD = &mBfrSSD;

/*********************************************************************************************************
** Function Name         : RVSIDFYData
** Function Describe     : Reverse the IDFY data
** Input  Parameter      : 16-bit word
** Output Parameter      : 16-bit word
** Global Parameter      : None
********************************************************************************************************/
INT16U RVSIDFYData(INT16U OriWord)
{
#if 0
  INT16U tWord;
  INT8U tByteH, tByteL;
  tByteL = BYTE0_OF(OriWord);
  tByteH = BYTE1_OF(OriWord);
  tWord = (((tByteL) << 0x08) | (tByteH));

  return tWord;
#else 
  return OriWord;
#endif 
}

/*********************************************************************************************************
** Function Name         : GetIDFYData
** Function Describe     : Get the Identify word for Microblazer
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
INT16U GetIDFYData(INT8U WordOffset)
{
  INT16U tWord;
  tWord = RVSIDFYData(SSD_IDFYDATA[WordOffset]);
  return (tWord);
}

/*********************************************************************************************************
** Function Name         : PrepareIDFYData
** Function Describe     : Set The Feature
** Input  Parameter      : WordOffset, WordVal
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void UpdateIDFYData(INT16U WordOffset, INT16U WordVal)
{
  INT8U CKSM;
  INT16U tWord;
  SSD_IDFYDATA[WordOffset] = RVSIDFYData(WordVal);
  CKSM = 0;
  for(tWord = 0; tWord < 255; tWord++)
  {
    CKSM += SSD_IDFYDATA[tWord] &0x00ff;
    CKSM += ((SSD_IDFYDATA[tWord] &0xff00) >> 8);
  }
  CKSM += 0xA5;
  CKSM = 0x100 - CKSM;
  SSD_IDFYDATA[255] = 0xA500 | CKSM;
}

/*********************************************************************************************************
** Function Name         : PrepareIDFYData
** Function Describe     : Set The Feature
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void PrepareIDFYData(void)
{
  INT8U tByte, tCheckSum;
  INT16U tWord;
  if(bRamDisk)
  {
    tCheckSum = 0x00;
    for(tByte = 0; tByte < 0x80; tByte++)
    {
      SSD_IDFYDATA[tByte + 0x00] = IDFY_DATA[tByte];
      tCheckSum += ((IDFY_DATA[tByte] &0x00FF) >> 0x00);
      tCheckSum += ((IDFY_DATA[tByte] &0xFF00) >> 0x08);
    }
    for(tByte = 0; tByte < 0x7F; tByte++)
    {
      SSD_IDFYDATA[(tByte + 0x80)] = 0x0000;
    }
    tCheckSum += 0xA5;
    tCheckSum = 0-tCheckSum;
    CurIDFYCheckSum = tCheckSum;
    tByte = SSD_IDFYCKSM_OFST;
    SSD_IDFYDATA[tByte] = ((tCheckSum) | 0xA500);
//SMART Command
    tWord = GetIDFYData(IDFY_W82_FEA);
    tWord |= 0x0001;
    UpdateIDFYData(IDFY_W82_FEA, tWord);
    tWord = GetIDFYData(IDFY_W84_FEA);
    tWord |= 0x0003;
    UpdateIDFYData(IDFY_W84_FEA, tWord);
    tWord = GetIDFYData(IDFY_W85_FEA);
    tWord |= 0x0001;
    UpdateIDFYData(IDFY_W85_FEA, tWord);
    UpdateIDFYData(IDFY_W60_28SIZE, 0x0000); //120G
    UpdateIDFYData(IDFY_W61_28SIZE, 0x0F00);
    UpdateIDFYData(IDFY_W100_48SIZE, 0x0000);
    UpdateIDFYData(IDFY_W101_48SIZE, 0x0F00);
    UpdateIDFYData(IDFY_W102_48SIZE, 0x0000);
    UpdateIDFYData(IDFY_W103_48SIZE, 0x0000);
//update model name
    UpdateIDFYData(IDFY_W27_MDN, 0x4D52); // MR
    UpdateIDFYData(IDFY_W28_MDN, 0x4D4F); //MO
    UpdateIDFYData(IDFY_W29_MDN, 0x4E45); // NE
    UpdateIDFYData(IDFY_W30_MDN, 0x5452); // TR
    UpdateIDFYData(IDFY_W31_MDN, 0x414D); //AM
    UpdateIDFYData(IDFY_W32_MDN, 0x4449); //DI
    UpdateIDFYData(IDFY_W33_MDN, 0x534B); //SK
#if 1
    UpdateIDFYData(IDFY_W34_MDN, 0x2020); //__
    UpdateIDFYData(IDFY_W35_MDN, 0x2020); //__
#else 
    UpdateIDFYData(IDFY_W34_MDN, 0x3349); //I3
    UpdateIDFYData(IDFY_W35_MDN, 0x4E34); //N4 ->4N
#endif 
  }
  CurMaxLBAAdr = GetIDFYData(IDFY_W101_48SIZE) << 16;
  CurMaxLBAAdr |= GetIDFYData(IDFY_W100_48SIZE);
  CurMaxLBAAdr--;
#if CFG_TRIM>0
//UpdateIDFYData(IDFY_W69_TRIM, 0x4000); //support TRIM word 69
//UpdateIDFYData(IDFY_W169_TRIM, 0x0001); //support TRIM word 169
//UpdateIDFYData(IDFY_W105_TRIM, 0x0080); //support TRIM word 105, 64K =128Sector
#endif 
//update fw version
  UpdateIDFYData(IDFY_W23_FV, 0x4D42); // M B
  UpdateIDFYData(IDFY_W24_FV, 0x4C31); // L 1
  UpdateIDFYData(IDFY_W25_FV, 0x3544); // 5 D
  UpdateIDFYData(IDFY_W25_FV, 0x4C41); // G A
#if CFG_NCQEN > 0
  UpdateIDFYData(IDFY_W47_MUL, 0x8001);
  UpdateIDFYData(IDFY_W59_MUL, 0x0101);
  tWord = (NCQQUEUEDEPTH - 1);
  UpdateIDFYData(IDFY_W75_NCQ, tWord);
  tWord = 0x1F04;
  UpdateIDFYData(IDFY_W76_NCQ, tWord);
  tWord = 0x005E;
  UpdateIDFYData(IDFY_W78_NCQ, tWord);
  tWord = 0x0000;
  UpdateIDFYData(IDFY_W79_NCQ, tWord);
  tWord = 0x1008;
  UpdateIDFYData(IDFY_W222_NCQ, tWord);
#endif 
/********************************/
/*    Add by shangzhao                             */
#if CFG_RWLOG_EXT>0
//support read/write LOG
  UpdateIDFYData(0x54, 0x4023); //support GPL
  UpdateIDFYData(0x57, 0x4023); //support GPL
#endif 
//Word 76 : bit 1 means support SATA Generation 1
//			   bit 2 means support SATA Generation 2
//			   bit 9 means support Host interface power management
  tWord = GetIDFYData(IDFY_W76_NCQ);
  tWord |= 0x0206;
  UpdateIDFYData(IDFY_W76_NCQ, tWord);
//Word 79 : bit 9 to zero means not support Device power management
  tWord = GetIDFYData(IDFY_W79_NCQ);
  tWord &= 0xFFF7;
  UpdateIDFYData(IDFY_W79_NCQ, tWord);
//For all Serial ATA devices, the entire contents of Word 93 in IDENTIFY DEVICE data shall be cleared to zero
  UpdateIDFYData(IDFY_W93_HWRST, 0x0000);
/********************************/
}

/*********************************************************************************************************
** Function Name         : XferIDFYData
** Function Describe     : Transfer the Identify data
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
BOOLEAN XferIDFYData(void)
{
  SataReadDDRData(SSD_IDFYDDRBYTEADDR, 0x01);
  return TRUE;
}

/*********************************************************************************************************
** Function Name         : StatusReturn
** Function Describe     : Set the regisger for non-data command
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void StatusReturn(BOOLEAN Rval)
{
  if(Rval)
  {
    mHostSetFwStatus(0x50);
  }
  else
  {
    mHostSetFwStatus(0x51);
  }
  

  mHostSetBitATdevConfgCntrl(m_tHOST_BUS_INTERFACE_ATdevConfgCntrl_bits_fwEocIbit); // send intrq
  mHostSetCxsbFwReqEoc();
  
}

/*********************************************************************************************************
** Function Name         : SetRSTStatus
** Function Describe     : Set the regisger for RST
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void SetRSTStatus(INT8U Mode){

}
/*********************************************************************************************************
** Function Name         : BufDataXfer
** Function Describe     : Transfer the Buffer Command data
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
BOOLEAN BufDataXfer(void)
{

  return TRUE;
}

/*********************************************************************************************************
** Function Name         : SetXFERMode
** Function Describe     : Set the feature for xfer mode
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
BOOLEAN SetXFERMode(INT8U SubFeature)
{
  INT8U XferMode, XferLevel;
  XferMode = (SubFeature &0xF8) >> 3;
  XferLevel = (SubFeature &0x07) >> 0;
  switch(XferMode)
  {
    case XFER_PIO_DFMD:
// It doesn't effect the IDFY data		
    break;
    case XFER_PIO_FLMD:
// TO DO : Add the code of set PIO FLMD,set IDFYDATA	
// It doesn't effect the IDFY data	
    break;
    case XFER_DMA_MTMD:
// TO DO : Add the code of set Multiword DMA ,set IDFYDATA	
// We do not support Multiword DMA, so just return
    break;
    case XFER_DMA_ULMD:
// TO DO : Add the code of set Ultra DMA ,set IDFYDATA	
    UpdateIDFYData(IDFY_W88_FEA, ((0x0100 << XferLevel) | 0x7F));
    break;
    default:
    return FALSE;
  }
  return TRUE;
}

/*********************************************************************************************************
** Function Name         : SetXFERMode
** Function Describe     : Set the feature for SATAII
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
BOOLEAN SetSataFeature(INT8U Feature, INT8U SubFeature)
{
//Enable sata feature
  if(Feature == FEA_ENA_SATA)
  {
    switch(SubFeature)
    {
      case SUBFEA_NZERO_OFFSET:
      case SUBFEA_AUTO_ACTIVATE:
      case SUBFEA_POWER_TRAN:
      case SUBFEA_INORDER_DATA:
      case SUBFEA_ASYN_NOTIFY:
      case SUBFEA_SETTING_PRES:
      break;
      default:
      return FALSE;
    }
  }
//Disable sata feature	
  else
  {
    switch(SubFeature)
    {
      case SUBFEA_NZERO_OFFSET:
      case SUBFEA_AUTO_ACTIVATE:
      case SUBFEA_POWER_TRAN:
      case SUBFEA_INORDER_DATA:
      case SUBFEA_ASYN_NOTIFY:
      case SUBFEA_SETTING_PRES:
      break;
      default:
      return FALSE;
    }
  }
  return TRUE;
}

/*********************************************************************************************************
** Function Name         : SetFeature
** Function Describe     : Set the feature for SATAII
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void SetFeature(ATA_REG *pCurAtaReg)
{
  INT8U FeaReg, SubFeaReg;
  BOOLEAN Rval;
  INT16U TmpVal;
  Rval = TRUE;
  FeaReg = pCurAtaReg->ATA_REG_FEA;
  SubFeaReg = pCurAtaReg->ATA_REG_SCNT;
  switch(FeaReg)
  {
//Enable or Disable Write Cache
    case FEA_ENA_WCACHE:
    case FEA_DIS_WCACHE:
    TmpVal = GetIDFYData(IDFY_W85_FEA);
    if(FeaReg &0x80)
// Disable
    {
      TmpVal &= 0xFFDF; //Set Bit 5 to 0
    }
    else
    {
      TmpVal |= 0x0020; //Set Bit 5 to 1
    }
    UpdateIDFYData(IDFY_W85_FEA, TmpVal);
    break;
//Set Transfer Mode
    case FEA_SET_XMODE:
    Rval = SetXFERMode(SubFeaReg);
    break;
    case FEA_ENA_APWRMAN:
    break;
    case FEA_DIS_APWRMAN:
    break;
    case FEA_ENA_PWRSTBY:
    case FEA_DIS_PWRSTBY:
    TmpVal = GetIDFYData(IDFY_W86_FEA);
    if(FeaReg &0x80)
    {
      TmpVal &= 0xFFDF; //Set Bit 5 to 0
    }
    else
    {
      TmpVal |= 0x0020; //Set Bit 5 to 1
    }
    UpdateIDFYData(IDFY_W86_FEA, TmpVal);
    break;
//Enable or Disable Sata Feature
    case FEA_ENA_SATA:
    case FEA_DIS_SATA:
    Rval = SetSataFeature(FeaReg, SubFeaReg);
    break;
    case FEA_ENA_PWRDSPUP:
    case FEA_ENA_REVPMODDF:
    case FEA_DIS_REVPMODDF:
    break;
    case FEA_ENA_RDLKAHEAD:
    case FEA_DIS_RDLKAHEAD:
    TmpVal = GetIDFYData(IDFY_W85_FEA);
    if(FeaReg &0x80)
    {
      TmpVal |= 0x0040; //Set Bit 6 to 1
    }
    else
    {
      TmpVal &= 0xFFBF; //Set Bit 6 to 0
    }
    UpdateIDFYData(IDFY_W85_FEA, TmpVal);
    break;
    default:
    Rval = FALSE;
    break;
  }
  StatusReturn(Rval);
}




/*******************************************************************
*																   
*  NAME:        InitCmdQ												   
*																   
*  FILENAME:    CmdDisp.c 											   
*																   
*  PARAMETERS:  None.    											   
*																   
*  DESCRIPTION: Initializes mtCMDQ and mtCMDQ_ENTRY data structures before using.    
*																   
*  RETURNS:     None.   
*
********************************************************************/
void InitCmdQ(void)
{
  INT8U tCnt;

  CmdQueueParam.cmdqIdleCnt = NCQQUEUEDEPTH;
  CmdQueueParam.cmdqRcrdCnt = 0x00;
  CmdQueueParam.cxsbIdleCnt = NCQQUEUEDEPTH;
  CmdQueueParam.cxsbXferCnt = 0x00;

  CmdQueueParam.pFreeListHead = &CmdQueuePool[0];
  CmdQueueParam.pFreeListTail = &CmdQueuePool[NCQQUEUEDEPTH - 1];

  CmdQueueParam.pRcrdListHead = NULL;
  CmdQueueParam.pRcrdListTail = NULL;

  CmdQueueParam.pCxsbFreeHead = &CxsbXferPool[0];
  CmdQueueParam.pCxsbFreeTail = &CxsbXferPool[NCQQUEUEDEPTH - 1];
  ;

  CmdQueueParam.pCxsbXferHead = NULL;
  CmdQueueParam.pCxsbXferTail = NULL;

  CmdQueueParam.curHSNum = 0x00;
  CmdQueueParam.curFSNum = 0x00;

  for(tCnt = 0; tCnt < NCQQUEUEDEPTH; tCnt++)
  {
    if(tCnt == 0x00)
    {
      CmdQueuePool[tCnt].pPrevious = NULL;
      CxsbXferPool[tCnt].pPrevious = NULL;

    }
    else
    {
      CmdQueuePool[tCnt].pPrevious = &(CmdQueuePool[tCnt - 1]);
      CxsbXferPool[tCnt].pPrevious = &(CxsbXferPool[tCnt - 1]);
    }

    if(tCnt == (NCQQUEUEDEPTH - 1))
    {
      CmdQueuePool[tCnt].pNext = NULL;
      CxsbXferPool[tCnt].pNext = NULL;
    }
    else
    {
      CmdQueuePool[tCnt].pNext = &(CmdQueuePool[tCnt + 1]);
      CxsbXferPool[tCnt].pNext = &(CxsbXferPool[tCnt + 1]);
    }
  }
}


/*******************************************************************
*																   
*  NAME:        BufferInit
*																   
*  FILENAME:    Buffer.c 											   
*																   
*  PARAMETERS:  Indication of reset buffer records or not.
*																   
*  DESCRIPTION: Initialize buffer manager data structure.   
*																   
*  RETURNS:     None.  
*
********************************************************************/
void BufferInit(void)
{
  volatile mtBFR_SSD *pSsd;
  mUINT_32 i;
  mUINT_32 bfrAdrs;

  pmBfrSSD = (mtBFR_SSD*)(BFR_SSD_LOCATION);
  bfrAdrs = RDCacheStaDDR_B;
  pSsd = pmBfrSSD;
  for(i = 0; i < BFR_SSD_ALLCNT; i++)
  {
    pSsd->nextSsdIndex = i;
    pSsd->ssdStartBufAddr = bfrAdrs;
    pSsd->ssdEndBufAddr = bfrAdrs + (mBFR_SUBSEG_SIZE *mSECTOR_SIZE) - 2;
    bfrAdrs = bfrAdrs + (mBFR_SUBSEG_SIZE *mSECTOR_SIZE);
    pSsd++;
  }

  mBMsetSubSegDescTableStartAddr(((mUINT_32)(&pmBfrSSD[0]) - 0x50000000));
  mBMsetSubSegDescTableEndAddr(((mUINT_32)(&pmBfrSSD[BFR_SSD_ALLCNT]) - 0x50000000));

#if (mRELINK_SSD == mENABLE)
  mBMsetSubSegDescSize(1);
#else 
  mBMsetSubSegDescSize((sizeof(mtBFR_SSD) - 12) >> 2);
#endif //(mRELINK_SSD == mENABLE)


#if (mDAVINCI_COMPATIBLE == mENABLE)
#else //(mDAVINCI_COMPATIBLE == mENABLE)
  mBMSelectFStoESSC(4); // Flash Segment is not connected to ES
  mBMSelectEStoFSSC(4); // Extend Segment is not connected to FS
  mBMSelectHStoFSSC(0); // Host Segment is connected to FS0
  mBMSelectHStoESSC(4); // Host Segment is not connected to ES

  mBMSelectEStoHSSC(8); // Extend Segment is not connected to HS
#endif //(mDAVINCI_COMPATIBLE == mENABLE)

  mBMdiskSegSecCntSel(8);

}


//Marvell SDK Function
void mSendStatusToHost(void)
{
//mUINT_8 cmd;

  switch(mSystemState.curState)
  {
    case mPOWER_UP_STATE:
    case mRESET_STATE:
// DSR0 state
//waitForReadLog10 = mFALSE;
    mHostReset();
    mHostSetFwStatus(0x50);
    mHostInitAtStatus(0x50); // set 0x50 , clear hw busy
    mHostClrIntrStatus(0xffff); // clear all Interrupts
    mHostIntrSrcEn(mParamPageHBI.params.intrSrcs);
    mHostReset();
    mHostSetConfgCntrl(mParamPageHBI.params.devCntl);
    mToggleCmdExeReset();
    mHostSetCxsbFwReqEoc();
// testing for ComReset with No Status
// 1.Waits for 20 XM_CLK 
// 2.Check for signature
//   R4A30[7:4]=0x7 - D2H FIS is armed to be sent
//   R4B58=0x4800 - Cmd_exe is at EOC phase
//   R4A6e[7:5]=0 
// 3.Toggle R4AB8[7] and reinitialize the transport registers
    {
      mUINT_16 j;
      for(j = 0; j < 200; j++)
        ;
      if((rHBI.hostMiscStatus.bits.txFISstate == 0x7) && (rHBI.tmPhase.all == 0x4800))
      {
        *(volatile mUINT_16*)0x1c004A6E |= 0x6000;
        if(((*(volatile mUINT_16*)0x1c004A6E) &0x00E0) == 0)
        {
          mHostSetESATAflowPwrRstCntl(m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_TMsoftRst);
          mHostClrESATAflowPwrRstCntl(m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_TMsoftRst);
          mInitHBI();
          mHostReset();
          mHostSetFwStatus(0x50);
          mHostInitAtStatus(0x50); // set 0x50 , clear hw busy
          mHostClrIntrStatus(0xffff); // clear all Interrupts
          mHostIntrSrcEn(mParamPageHBI.params.intrSrcs);
          mHostReset();
          mHostSetConfgCntrl(mParamPageHBI.params.devCntl);
          mHostSetCxsbFwReqEoc();
        }
      }
    }
    mHostIntrSrcEn(m_tHBI_INT_bits_nonAceCmd);
    break;

#if 0		
    case mQCMD_NON_EXE_ERROR_STATE:
// DFPDMAQ12 state
//mOutf("SND NONEXE ERR,");
//waitForReadLog10 = mTRUE;
    mHostClrTMflowIntrStatus(0xffff);
    cmd = mHostGetCmdOpcodeFromStagingTF();
    if((cmd != NCQ_RD_CMD) && (cmd != NCQ_WR_CMD))
    {
      mHostSetFwStatus(((mUINT_16)mHostGetAtStatus() &(~mBSY)) | mDEV_SK_CMPLT | mERR | mDEV_RDY); // send D2H=0x0441
    }
    else
    {
      mHostSetFwStatus(((mUINT_16)mHostGetAtStatus() &(~mBSY) &(~mDEV_SK_CMPLT)) | mERR | mDEV_RDY); // send D2H=0x0441
    }
    mHostSetBitATdevConfgCntrl(m_tHOST_BUS_INTERFACE_ATdevConfgCntrl_bits_fwEocIbit); // send intrq
    mHostSetCxsbFwReqEoc();
    mSystemState.curState = mDFPDMAQ13_STATE;
    break;

    case mQCMD_EXE_ERROR_STATE:
//waitForReadLog10 = mTRUE;
    mHostSetFwError((mUINT_16)ncqCmdErr &0xff); // set error code
    mHostSetFwStatus((mHostGetAtStatus() &~mBSY) | mERR | mDEV_RDY); // send D2H=0x0441
    mHostSetBitATdevConfgCntrl(m_tHOST_BUS_INTERFACE_ATdevConfgCntrl_bits_fwEocIbit); // send intrq
//mOutfnl("SND EXE ERR");

#if (VG_REV_2_0 == mENABLE)
    if(newCmdRcvd)
    {
      mHostClrESATAflowPwrRstCntl(m_tHBI_ESATA_FLOW_PWR_RESET_CNTRL_bits_sataBusReq);
      mHostClrTMflowIntrStatus(m_tHBI_TM_FLOW_INT_bits_TxFisDone);
//construct BIST active FIS
      mHostSetUserFISword0L(0x40A1); // SDB FIS
      mHostSetUserFISword0H(0x4051); // Error, Status
      mHostSetUserFISword1L(0x0000); // Sactive
      mHostSetUserFISword1H(0x0000); // Sactive
      mHostSetManualFlowControl(0x04A1);
      while(!(mHostGetTMflowIntrStatus() &m_tHBI_TM_FLOW_INT_bits_TxFisDone))
      {
        if(mSystemState.curState != mPOWER_UP_STATE)
        {
          return ;
        }
      }
      newCmdRcvd = 0;
    }
    else
    {
      NcqSendSDB(0, 0, (mHostGetAtStatus() &~mBSY) | mERR | (((mUINT_16)ncqCmdErr) << 8));
    }
#else 
    NcqSendSDB(0, 0, (mHostGetAtStatus() &~mBSY) | mERR | (((mUINT_16)ncqCmdErr) << 8));
#endif 

    mSystemState.curState = mDFPDMAQ13_STATE;
    break;

    case mDFPDMAQ13_STATE:
//mOutfnl("mDFPDMAQ13_STATE");
    NcqSendSDB(0, 0, (mHostGetAtStatus() &~mBSY) | mERR | (((mUINT_16)ncqCmdErr) << 8));
    mSystemState.curState = mDFPDMAQ13_STATE;
    break;

    case mINTF_ERROR_STATE:
    mHostInitAtStatus(mDEV_RDY | mDEV_SK_CMPLT); // set 0x50, clear h/w busy 
//kvl           if (!mHostGetQslotBsy()) 
    if(!waitForReadLog10)
// NonQ case
    {
//mOutfnl("SND INTF ERR STATUS");
      mHostClrTMflowIntrStatus(0xffff);
      mHostClrBitATdevConfgCntrl(m_tHOST_BUS_INTERFACE_ATdevConfgCntrl_bits_stopXfer);
      mHostSetFwError(mIF_CRC_ERR + mCORR_DATA_ERR); // set error code
      mHostSetFwStatus(mDEV_RDY + mDEV_SK_CMPLT + mERR); // send D2H=0x8451
      mHostSetBitATdevConfgCntrl(m_tHOST_BUS_INTERFACE_ATdevConfgCntrl_bits_fwEocIbit); // send intrq
      mOutfnl("SND INTF ERR D2H");
      mHostSetCxsbFwReqEoc();
    }
    else
    {
//mOutfnl("SENT SDB %x", mHostGetAtMode());
      mHostSetBitATdevConfgCntrl(m_tHOST_BUS_INTERFACE_ATdevConfgCntrl_bits_fwEocIbit); // send intrq
      NcqSendSDB(0, 0, (0x8441)); // post CRC error
//              NcqSendSDB(0,0,(mHostGetAtStatus()&~mBSY)|mINTR|mERR|(((mUINT_16)mUNCOR_DATA_ERR)<<8));
    }
    break;

    case mDFPDMAQ14_STATE:
//mOutfnl("mDFPDMAQ14_STATE");
    mHostSetAltAtError(0);
    mHostClrTMflowIntrStatus(0xffff);
    mHostSetFwError(0);
    mHostSetFwStatus((mHostGetAtStatus() &~mBSY) | mDEV_RDY); // send D2H=0x0441
    mHostSetBitATdevConfgCntrl(m_tHOST_BUS_INTERFACE_ATdevConfgCntrl_bits_fwEocIbit); // send intrq
    NcqSendSDB(0xffff, 0xffff, (mUINT_16)mHostGetAtStatus() &(~mERR) &(~mBSY) &(~mINTR) &(~mDEV_SK_CMPLT));
    break;
#endif 
  }
// To get out of not having TxFisDone the following should be done
// send status
// set up for 10 ms
// if no SDB FIS resend one more time
// if not then send comReset
// ComReset then check for PhyReady
// If PhynotReady then Infinite Comreset



}


/*********************************************************************************************************
** Function Name         : SataReadDDRData
** Function Describe     : Read DDR Data(in 4K)
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Function copy from SDK VuCmds.C SendDataToHost
********************************************************************************************************/
void SataReadDDRData(INT32U DDRByteAddr, INT32U DataSecSize)
{
  INT8U CurHSNum;

  CurHSNum = CmdQueueParam.curHSNum;
  CmdQueueParam.curHSNum++;
  CmdQueueParam.curHSNum &= CMDQHSMAXMASK;

  DDRByteAddr = DDRByteAddr - 0x50000000;

  mHostClrBitAtMode(m_tHOST_BUS_INTERFACE_ATmode0_bits_writeDir);
  mBMhostByteCntRst();
  pmBfrSSD[BFR_SSD_VNDINDEX].nextSsdIndex = BFR_SSD_VNDINDEX;
  pmBfrSSD[BFR_SSD_VNDINDEX].ssdStartBufAddr = DDRByteAddr;
  pmBfrSSD[BFR_SSD_VNDINDEX].ssdEndBufAddr = DDRByteAddr + (DataSecSize << 9) - 2;


  mBfrLLcurrLink(CurHSNum, BFR_SSD_VNDINDEX);
  mBfrSegAdrsOffsetInit(CurHSNum, DDRByteAddr);
  mHBIsetHostBufferSegSel(CurHSNum);


  mHostSetTaskFileReg(mTF_CYL_LOW_REG, DataSecSize);
  mHostSetTaskFileReg(mTF_CYL_HIGH_REG, 0x80);

  mBMdiskSegSecCntSel(8);
  mBfrHostSegSecCntInit(CurHSNum, DataSecSize);
  mHostClrIntrStatus(m_tHBI_INT_bits_fwXferDone);

  mHostSetCxsbFwReqNonQDataXfer(DataSecSize, CurHSNum, mREAD_OP, mTRUE);

  while(!(mHostGetIntrStatus() &m_tHBI_INT_bits_fwXferDone))
  {
    if(mSystemState.curState != mPOWER_UP_STATE)
    {
      return ;
    }
  }
  mHostClrIntrStatus(m_tHBI_INT_bits_fwXferDone);


}

/*********************************************************************************************************
** Function Name         : SataWriteDDRData
** Function Describe     : Write DDR Data(in 4K)
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Function copy from SDK VuCmds.C ReceiveDataFromHost
********************************************************************************************************/
void SataWriteDDRData(INT32U DDRByteAddr, INT32U DataSecSize)
{
  INT8U CurHSNum;

  CurHSNum = CmdQueueParam.curHSNum;
  CmdQueueParam.curHSNum++;
  CmdQueueParam.curHSNum &= CMDQHSMAXMASK;

  DDRByteAddr = DDRByteAddr - 0x50000000;

  mHostSetBitAtMode(m_tHOST_BUS_INTERFACE_ATmode0_bits_writeDir);
  mBMhostByteCntRst();
  pmBfrSSD[BFR_SSD_VNDINDEX].nextSsdIndex = BFR_SSD_VNDINDEX;
  pmBfrSSD[BFR_SSD_VNDINDEX].ssdStartBufAddr = DDRByteAddr;
  pmBfrSSD[BFR_SSD_VNDINDEX].ssdEndBufAddr = DDRByteAddr + (DataSecSize << 9) - 2;

  mBfrLLcurrLink(CurHSNum, BFR_SSD_VNDINDEX);
  mBfrSegAdrsOffsetInit(CurHSNum, DDRByteAddr);
  mHBIsetHostBufferSegSel(CurHSNum);


  mHostSetTaskFileReg(mTF_CYL_LOW_REG, DataSecSize);
  mHostSetTaskFileReg(mTF_CYL_HIGH_REG, 0x00);

  mBMdiskSegSecCntSel(8);
  mBfrHostSegSecCntInit(CurHSNum, (0-DataSecSize));
  mHostClrIntrStatus(m_tHBI_INT_bits_fwXferDone);

  mHostSetCxsbFwReqNonQDataXfer(DataSecSize, CurHSNum, mWRITE_OP, mTRUE);

  while(!(mHostGetIntrStatus() &m_tHBI_INT_bits_fwXferDone))
  {
    if(mSystemState.curState != mPOWER_UP_STATE)
    {
      return ;
    }
  }
  mHostClrIntrStatus(m_tHBI_INT_bits_fwXferDone);

}



/*********************************************************************************************************
** Function Name         : CmdQGetFromFree
** Function Describe     : Command Get free node from the free link
** Input  Parameter      : value
** Output Parameter      : CMDQENTRY node ptr
** Global Parameter      : None
** Call Module           :
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
CMDQENTRY *CmdQGetFromFree(void)
{
  CMDQENTRY *q;

  if(CmdQueueParam.cmdqIdleCnt == 0)
  {
    mSHOULD_NOT_GET_HERE();
//return NULL;
  }

  q = CmdQueueParam.pFreeListHead;
  CmdQueueParam.cmdqIdleCnt--;
  if(0x00 == CmdQueueParam.cmdqIdleCnt)
  {
    CmdQueueParam.pFreeListHead = (CMDQENTRY*)0;
    CmdQueueParam.pFreeListTail = (CMDQENTRY*)0;
  }
  else
  {
    CmdQueueParam.pFreeListHead = CmdQueueParam.pFreeListHead->pNext;
    CmdQueueParam.pFreeListHead->pPrevious = (CMDQENTRY*)0;
  }
  return (q);

}

/*********************************************************************************************************
** Function Name         : CmdQSaveToRcrd
** Function Describe     : Command save to the record link
** Input  Parameter      : CMDQENTRY node ptr
** Output Parameter      : value
** Global Parameter      : None
** Call Module           :
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CmdQSaveToRcrd(CMDQENTRY *pCmdQ)
{
  if((CmdQueueParam.pRcrdListHead == NULL) && (CmdQueueParam.pRcrdListTail == NULL))
  {
    pCmdQ->pNext = NULL;
    pCmdQ->pPrevious = NULL;
    CmdQueueParam.pRcrdListHead = pCmdQ;
    CmdQueueParam.pRcrdListTail = pCmdQ;
  }
  else
  {
    CmdQueueParam.pRcrdListTail->pNext = pCmdQ;
    pCmdQ->pPrevious = CmdQueueParam.pRcrdListTail;
    pCmdQ->pNext = NULL;
    CmdQueueParam.pRcrdListTail = pCmdQ;
  }

  CmdQueueParam.cmdqRcrdCnt++;
}

/*********************************************************************************************************
** Function Name         : CmdQReturnToIdle
** Function Describe     : Command return the Exec finish node to Idle
** Input  Parameter      : CMDQENTRY node ptr
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CmdQReturnToIdle(CMDQENTRY *pCmdQ)
{

  if((pCmdQ->pPrevious) == NULL)
  {
//Head  
    if((pCmdQ->pNext) == NULL)
    {
      CmdQueueParam.pRcrdListHead = NULL;
      CmdQueueParam.pRcrdListTail = NULL;
    }
    else
    {
      pCmdQ->pNext->pPrevious = NULL;
      CmdQueueParam.pRcrdListHead = pCmdQ->pNext;
    }
  }
  else
  {
    if((pCmdQ->pNext) == NULL)
    {
//Tail
      pCmdQ->pPrevious->pNext = NULL;
      CmdQueueParam.pRcrdListTail = pCmdQ->pPrevious;
    }
    else
    {
//Body	
      pCmdQ->pNext->pPrevious = pCmdQ->pPrevious;
      pCmdQ->pPrevious->pNext = pCmdQ->pNext;
    }
  }

  CmdQueueParam.cmdqRcrdCnt--;

  if(CmdQueueParam.pFreeListHead == NULL)
  {
    pCmdQ->pPrevious = (CMDQENTRY*)0;
    pCmdQ->pNext = (CMDQENTRY*)0;
    CmdQueueParam.pFreeListHead = pCmdQ;
    CmdQueueParam.pFreeListTail = pCmdQ;
  }
  else
  {
    CmdQueueParam.pFreeListTail->pNext = pCmdQ;
    pCmdQ->pPrevious = CmdQueueParam.pFreeListTail;
    pCmdQ->pNext = (CMDQENTRY*)0;
    CmdQueueParam.pFreeListTail = pCmdQ;
  }
  CmdQueueParam.cmdqIdleCnt++;
}






/*********************************************************************************************************
** Function Name         : CxsbGetFromFree
** Function Describe     : Command Get free node from the free link
** Input  Parameter      : value
** Output Parameter      : CXSBLINK node ptr
** Global Parameter      : None
** Call Module           :
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
CXSBLINK *CxsbGetFromFree(void)
{
  CXSBLINK *q;

#if 0
  if(CmdQueueParam.cxsbIdleCnt == 0)
  {
    //mSHOULD_NOT_GET_HERE();
    return NULL;
  }
#else 
  if(CmdQueueParam.cxsbIdleCnt <= 0x18)
  {
//mSHOULD_NOT_GET_HERE( );
    return NULL;
  }
#endif 

  q = CmdQueueParam.pCxsbFreeHead;

  CmdQueueParam.cxsbIdleCnt--;
  if(0x00 == CmdQueueParam.cxsbIdleCnt)
  {
    CmdQueueParam.pCxsbFreeHead = (CXSBLINK*)0;
    CmdQueueParam.pCxsbFreeTail = (CXSBLINK*)0;
  }
  else
  {
    CmdQueueParam.pCxsbFreeHead = CmdQueueParam.pCxsbFreeHead->pNext;
    CmdQueueParam.pCxsbFreeHead->pPrevious = (CXSBLINK*)0;
  }
  return (q);

}

/*********************************************************************************************************
** Function Name         : CxsbSaveToXfer
** Function Describe     : Command save to the xfer
** Input  Parameter      : CMDQENTRY node ptr
** Output Parameter      : value
** Global Parameter      : None
** Call Module           :
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CxsbSaveToXfer(CXSBLINK *pCxsb)
{
  if((CmdQueueParam.pCxsbXferHead == NULL) && (CmdQueueParam.pCxsbXferTail == NULL))
  {
    pCxsb->pPrevious = NULL;
    pCxsb->pNext = NULL;
    CmdQueueParam.pCxsbXferHead = pCxsb;
    CmdQueueParam.pCxsbXferTail = pCxsb;
  }
  else
  {
    CmdQueueParam.pCxsbXferTail->pNext = pCxsb;
    pCxsb->pPrevious = CmdQueueParam.pCxsbXferTail;
    pCxsb->pNext = NULL;
    CmdQueueParam.pCxsbXferTail = pCxsb;
  }

  CmdQueueParam.cxsbXferCnt++;
  CmdQueueParam.cxsbWaitCnt++;
}

/*********************************************************************************************************
** Function Name         : CmdQReturnToIdle
** Function Describe     : Command return the Exec finish node to Idle
** Input  Parameter      : CMDQENTRY node ptr
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CxsbReturnToIdle(CXSBLINK *pCxsb)
{

  if((pCxsb->pPrevious) == NULL)
  {
//Head  
    if((pCxsb->pNext) == NULL)
    {
      CmdQueueParam.pCxsbXferHead = NULL;
      CmdQueueParam.pCxsbXferTail = NULL;
    }
    else
    {
      pCxsb->pNext->pPrevious = NULL;
      CmdQueueParam.pCxsbXferHead = pCxsb->pNext;
    }
  }
  else
  {
    if((pCxsb->pNext) == NULL)
    {
//Tail
      pCxsb->pPrevious->pNext = NULL;
      CmdQueueParam.pCxsbXferTail = pCxsb->pPrevious;
    }
    else
    {
//Body	
      pCxsb->pNext->pPrevious = pCxsb->pPrevious;
      pCxsb->pPrevious->pNext = pCxsb->pNext;
    }
  }

  CmdQueueParam.cxsbXferCnt--;

  if(CmdQueueParam.pCxsbFreeHead == NULL)
  {
    pCxsb->pPrevious = (CXSBLINK*)0;
    pCxsb->pNext = (CXSBLINK*)0;
    CmdQueueParam.pCxsbFreeHead = pCxsb;
    CmdQueueParam.pCxsbFreeTail = pCxsb;
  }
  else
  {
    CmdQueueParam.pCxsbFreeTail->pNext = pCxsb;
    pCxsb->pPrevious = CmdQueueParam.pCxsbFreeTail;
    pCxsb->pNext = (CXSBLINK*)0;
    CmdQueueParam.pCxsbFreeTail = pCxsb;
  }
  CmdQueueParam.cxsbIdleCnt++;
}


/*********************************************************************************************************
** Function Name         : CommandOneDecode
** Function Describe     : Decode One Command
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOLEAN CommandOneDecode(INT8U NtNCQCmd)
{
  INT8U CylinderH, CylinderL, SecNum, HeadNum;
  INT16U CylinderNum;
  INT8U EXFlag;
  CMDQENTRY *pCurCmdEntry;
  EXFlag = FALSE;


  pCurCmdEntry = CmdQGetFromFree();

  if(pCurCmdEntry)
  {
    if(NtNCQCmd)
    {
//Save the ATA Regs for all Non-Q Command
      pCurCmdEntry->atareg.ATA_REG_CMD = rHBI.cmnd;
      pCurCmdEntry->CmdFlag.all = mCmdVectorTable[pCurCmdEntry->atareg.ATA_REG_CMD];
      EXFlag = pCurCmdEntry->CmdFlag.bits.ExtCmd;
      if(EXFlag)
      {
        pCurCmdEntry->atareg.ATA_REG_DEVHEAD = (rHBI.initialLba3_2 | 0xE000) >> 8;
      }
      else
      {
        pCurCmdEntry->atareg.ATA_REG_DEVHEAD = rHBI.initDevHd;
      }
      pCurCmdEntry->atareg.ATA_REG_LBAH = rHBI.initCylHigh;
      pCurCmdEntry->atareg.ATA_REG_LBAM = rHBI.initCylLow;

      if(EXFlag)
      {
        pCurCmdEntry->atareg.ATA_REG_PRELBAM = (mUINT_8)(rHBI.initialLba5_4);
        pCurCmdEntry->atareg.ATA_REG_PRELBAH = (mUINT_8)(rHBI.initialLba5_4) >> 8;
      }

      {
// Debounce this register to have an accurate reading for auto commands.
        mUINT_8 temp1, temp2;
        for(;;)
        {
          temp1 = rHBI.initSectorNum;
          temp2 = rHBI.initSectorNum;
          if(temp1 == temp2)
          {
            break;
          }
        }
        pCurCmdEntry->atareg.ATA_REG_LBAL = temp1;
      }

      if(EXFlag)
      {
        pCurCmdEntry->atareg.ATA_REG_PRELBAL = rHBI.initialLba3_2 >> 8;
        pCurCmdEntry->atareg.ATA_REG_SCNT = rHBI.initialSectCnt1_0.all;
        pCurCmdEntry->atareg.ATA_REG_FEA = rHBI.feature1_0.all;
      }
      else
      {
        pCurCmdEntry->atareg.ATA_REG_SCNT = rHBI.initialSectCnt1_0.bits.initialSectCnt0;
        pCurCmdEntry->atareg.ATA_REG_FEA = rHBI.feature1_0.bits.feature0;
      }

//Handler Not NCQ Command    
      if(pCurCmdEntry->CmdFlag.bits.DiskCmd)
      {
//Cal the LBA and SecCnt for DiskCmd      
        pCurCmdEntry->SecCnt = pCurCmdEntry->atareg.ATA_REG_SCNT;
        if(EXFlag)
        {
          pCurCmdEntry->LbaAdr = (pCurCmdEntry->atareg.ATA_REG_PRELBAL << 24 | pCurCmdEntry->atareg.ATA_REG_PRELBAH << 16 | pCurCmdEntry->atareg.ATA_REG_LBAM << 8 | pCurCmdEntry->atareg.ATA_REG_LBAL);
          if((pCurCmdEntry->SecCnt) == 0x0000)
          {
            pCurCmdEntry->SecCnt = 0x10000;
          }

        }
        else
        {
          if(pCurCmdEntry->atareg.ATA_REG_DEVHEAD &0x40)
          {
            pCurCmdEntry->LbaAdr = (((pCurCmdEntry->atareg.ATA_REG_DEVHEAD &0x0F) << 24) | (pCurCmdEntry->atareg.ATA_REG_LBAH << 16) | (pCurCmdEntry->atareg.ATA_REG_LBAM << 8) | (pCurCmdEntry->atareg.ATA_REG_LBAL));

          }
          else
          {
            CylinderL = pCurCmdEntry->atareg.ATA_REG_LBAM;
            CylinderH = pCurCmdEntry->atareg.ATA_REG_LBAH;
            CylinderNum = (CylinderH << 8) | (CylinderL);
            HeadNum = (pCurCmdEntry->atareg.ATA_REG_DEVHEAD &0x0F);
            SecNum = pCurCmdEntry->atareg.ATA_REG_LBAL;
            pCurCmdEntry->LbaAdr = (((CylinderNum *M_HEADNUM) + HeadNum) *M_SECNUM) + SecNum - 1;

          }

          if(pCurCmdEntry->SecCnt == 0x00)
          {
            pCurCmdEntry->SecCnt = 0x100;
          }

        }
      }
    }
    else
    {
//Handler NCQ Command	        
      pCurCmdEntry->NCQTag = mHostGetCrsbCmdTag();
      pCurCmdEntry->NCQSlotNum = pCurCmdEntry->NCQTag;
      pCurCmdEntry->atareg.ATA_REG_CMD = mHostGetCmdfromQslot(pCurCmdEntry->NCQSlotNum);
      pCurCmdEntry->LbaAdr = mHostGetLBAfromQslot(pCurCmdEntry->NCQSlotNum);
      pCurCmdEntry->SecCnt = mHostGetSectorCntfromQslot(pCurCmdEntry->NCQSlotNum);
      pCurCmdEntry->CmdFlag.all = mCmdVectorTable[pCurCmdEntry->atareg.ATA_REG_CMD];
    }


    pCurCmdEntry->LbaAdr = (pCurCmdEntry->LbaAdr &0x3FFFF);
    mHostCrsbCmdResume(m_tHBI_CRSB_CNTL_STAT_bits_newIDresume);

    CmdQSaveToRcrd(pCurCmdEntry);
    return SUCCESS;

  }
  else
  {
    return FAIL;
  }


}

/*********************************************************************************************************
** Function Name         : CommandDecode
** Function Describe     : Get the Command shadow register
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOLEAN CommandNCQExist(void)
{
  if((!mHostIsNonQcmd()) && mHostGetCrsbCount())
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/*********************************************************************************************************
** Function Name         : CommandDecode
** Function Describe     : Get the Command shadow register
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOLEAN CommandDecode(void)
{
  INT8U NTNCQCmd;

  NTNCQCmd = mHostIsNonQcmd();
  if(NTNCQCmd)
  {
    CommandOneDecode(NTNCQCmd);
    mHostClrIntrStatus(m_tHBI_INT_bits_newCmd | m_tHBI_INT_bits_nonAceCmd);
    mHostIntrSrcEn(m_tHBI_INT_bits_nonAceCmd);

    return SUCCESS;

  }
  else
  {
    do
    {
      CommandOneDecode(NTNCQCmd);
    }
    while(CommandNCQExist());
    mHostIntrSrcEn(m_tHBI_INT_bits_nonAceCmd);

    return SUCCESS;
  }
}

/*********************************************************************************************************
** Function Name         : CommandNTDiskProcess
** Function Describe     : Process Not Disk Command
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
** Call Module           :
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CommandNTDiskProcess(CMDQENTRY *pCurCmdEntry)
{
  switch(pCurCmdEntry->atareg.ATA_REG_CMD)
  {
    case ATACMD_NOP:
    StatusReturn(FALSE);
    break;

    case ATACMD_READ_VERIFY:
    case ATACMD_READ_VERIFY_EXT:
    StatusReturn(TRUE);
    break;

    case ATACMD_RECALIBRATE:
    case ATACMD_SEEK:
    StatusReturn(TRUE);
    break;

    case ATACMD_INIT_DEV_PARA:
    StatusReturn(TRUE);
    break;

    case ATACMD_DEVICEDIAG:
    SetRSTStatus(TRUE);
    break;

    case ATACMD_SMART:
    StatusReturn(FALSE);
    break;

    case ATACMD_SET_MULTIMOD:
    if(pCurCmdEntry->atareg.ATA_REG_SCNT == 0x01)
    {
      StatusReturn(TRUE);
    }
    else
    {
      StatusReturn(FALSE);
    }
    break;

    case ATACMD_STANDBY:
    case ATACMD_STANDBY_M:
    case ATACMD_STANDBY_IM:
    case ATACMD_STANDBY_IM_M:
    CurPwerMode = PWR_STBYMOD;
    StatusReturn(TRUE);
    break;

    case ATACMD_IDLE:
    case ATACMD_IDLE_M:
    case ATACMD_IDLE_IM:
    case ATACMD_IDLE_IM_M:
    CurPwerMode = PWR_IDLEMOD;
    StatusReturn(TRUE);
    break;

    case ATACMD_CHK_POWER_MODE:
    case ATACMD_CHK_POWER_MODE_M:
	mHostSetTaskFileReg(mTF_SECTOR_CNT_REG,0xff);
    StatusReturn(TRUE);
    break;

    case ATACMD_SLEEP:
    case ATACMD_SLEEP_M:
    CurSleepPend = TRUE;
    StatusReturn(TRUE);
    break;

    case ATACMD_FLUSH_CACHE:
    case ATACMD_FLUSH_CACHE_EXT:
    StatusReturn(TRUE);
    break;

    case ATACMD_READ_NATIVE_MAXADR:
    case ATACMD_READ_NATIVE_MAXADR_EXT:
    StatusReturn(FALSE);
    break;

    case ATACMD_READ_BUFFER:
    case ATACMD_WRITE_BUFFER:
    BufDataXfer();
    break;

    case ATACMD_IDFY_DEVICE:
    XferIDFYData();
    break;

    case ATACMD_SET_FEATURE:
    SetFeature(&pCurCmdEntry->atareg);
    break;

    case ATACMD_SECURITY_SETPSWD:
    case ATACMD_SECURITY_UNLOCK:
    case ATACMD_SECURITY_FREESELOCK:
    case ATACMD_SECURITY_DISPSWD:
    case ATACMD_SECURITY_PREESE:
    case ATACMD_SECURITY_ERASE:
    StatusReturn(FALSE);
    break;

    case ATACMD_SETMAX:
    StatusReturn(FALSE);
    break;

    case ATACMD_READ_LOG_EXT:
    StatusReturn(FALSE);
    break;

    case ATACMD_WRITE_LOG_EXT:
    StatusReturn(FALSE);
    break;

    case ATACMD_VDCMDALL:
    DBG_VDOperation(pCurCmdEntry);
    break;

    case ATACMD_TRIM_DMA:
    StatusReturn(FALSE);
    break;

//case ATACMD_DNFW:
    default:
    StatusReturn(FALSE);
    break;
  }

}



/*********************************************************************************************************
** Function Name         : InitSATA
** Function Describe     : Init SATA Module
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void InitSATA(void)
{
  bPowerOff = FALSE;
  bRamDisk = TRUE;
  BSemNATACMD = 0;
  BSemCurXferFinCnt = 0;
  CurMaxLBAAdr = 0x10000000;

  InitCmdQ();
  BufferInit();
  mCacheInit();
  InitDebug();
  PrepareIDFYData();
}






/*******************************************************************************************************
*                                                                     End Of File
           ********************************************************************************************************/
