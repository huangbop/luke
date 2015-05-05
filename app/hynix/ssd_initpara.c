/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#include "HEAD.H"

/*----------------------------------------------------------------------------
 Function Definitions
 ---------------------------------------------------------------------------*/
#define mCOMM_RX_TX   (m_tCPU_INTR_bits_comTx | m_tCPU_INTR_bits_comRxLatched)

#if (mREALMONITOR != mENABLE)
  #define mDEFAULT_CPU_INTERRUPT_SRCS (m_tCPU_INTR_bits_sataIn | m_tCPU_INTR_bits_hdcInt | m_tCPU_INTR_bits_servoInt)
    #define mDEFAULT_INTERRUPT_SRCS (m_mSOC_INTR_bits_timer0 | m_mSOC_INTR_bits_IPCCmdWritten)
#else
  #define mDEFAULT_CPU_INTERRUPT_SRCS (mCOMM_RX_TX | m_tCPU_INTR_bits_sataIn | m_tCPU_INTR_bits_hdcInt | m_tCPU_INTR_bits_servoInt)
  #define mDEFAULT_INTERRUPT_SRCS (m_mSOC_INTR_bits_timer0 | m_mSOC_INTR_bits_IPCCmdWritten)
#endif

#define SDRAM_DIRECT_START  0x50000000          // Mapping of BM linear address to DDR2 column, row, block.
#define COLUMN512           0x400
#define ROW4096             0x800000
#define ROW8192             0x1000000
#define BLOCK4              0x8000000

#define COLUMN  1024                            //Parameters for a 256MByte DDR2 
#define ROW     16384
#define BLOCK   8


/*************************************************************
 HBI (Host Block Interface) Parameters Page
*************************************************************/
// SATA HOST FEATURES
#define mENABLE_HOST_CRC            mFALSE
#define mENABLE_HOST_CBW            mFALSE
#define mENABLE_WORD_XFER           mFALSE
#define mENABLE_SINGLE_WRD_DMA      mFALSE
#define mENABLE_DMA                 mTRUE

// Define default ATA host xfer modes/features
#if mENABLE_HOST_CRC == mTRUE 
  #define mXX_LOCAL_CRC_ON              m_tHOST_BUS_INTERFACE_ATmode0_bits_crcEn
  #define mXX_LOCAL_CRC_SEC_SIZE_ADJ    4UL
#else
  #define mXX_LOCAL_CRC_ON              0
  #define mXX_LOCAL_CRC_SEC_SIZE_ADJ    0UL
#endif


#if mENABLE_WORD_XFER == mTRUE
  #define mXX_LOCAL_mWORD_EN            m_tHOST_BUS_INTERFACE_ATmode0_bits_wordEn
#else
  #define mXX_LOCAL_mWORD_EN            0
#endif

#if mENABLE_SINGLE_WRD_DMA  == mTRUE
  #define mXX_LOCAL_SINGLE_WRD_DMA      m_tHOST_BUS_INTERFACE_ATmode0_bits_snglWdmaEn
#else
  #define mXX_LOCAL_SINGLE_WRD_DMA      0 
#endif

#if mENABLE_DMA == mTRUE
  #define mXX_LOCAL_DMA                 m_tHOST_BUS_INTERFACE_ATmode0_bits_dmaModeEn
#else
  #define mXX_LOCAL_DMA                 0
#endif

//
// All XX_LOCALS values varies depending on conditions ABOVE
//
  #define mHST_ECC_SEL                  0x24    // HARDCODED for 5B CRC + 60B ECC

  #define mDEFAULT_AT_MODE0_VAL  (0x0)
  #define mDEFAULT_AT_DEV_CNTRL_VAL   (m_tHOST_BUS_INTERFACE_ATdevConfgCntrl_bits_altHintselq | \
                                        m_tHOST_BUS_INTERFACE_ATdevConfgCntrl_bits_tfIncEn | \
                                        m_tHOST_BUS_INTERFACE_ATdevConfgCntrl_bits_scntDecEn)


#define mDEFAULT_AT_INTERRUPT_SRCS  (m_tHBI_INT_bits_xPortInt | \
                                    m_tHBI_INT_bits_esataErr | \
                                    m_tHBI_INT_bits_cmdProcessErr | \
                                    m_tHBI_INT_bits_cmdExecErr | \
                                    m_tHBI_INT_bits_cmdRcvdErr | \
                                    m_tHBI_INT_bits_cmdAborted | \
                                    m_tHBI_INT_bits_softReset | \
                                    m_tHBI_INT_bits_hardReset)                                   
  #define mDEFAULT_QCMDCNTLR_VAL   (0x0)
  
  #define mDEFAULT_ESATAERRINT_SRCS (m_tHBI_ESATA_ERROR_INT_bits_linkHung | \
                                    m_tHBI_ESATA_ERROR_INT_bits_txRerrDataFisDet | \
                                    m_tHBI_ESATA_ERROR_INT_bits_txDataSyncDet |\
                                    m_tHBI_ESATA_ERROR_INT_bits_rxDataSyncDet |\
                                    m_tHBI_ESATA_ERROR_INT_bits_rxLengthErr | \
                                    m_tHBI_ESATA_ERROR_INT_bits_tmFifoErr | \
                                    m_tHBI_ESATA_ERROR_INT_bits_rxRerrDataFisDet )

  #define mDEFAULT_TMFLOWINT_SRCS   0x0
  #define mDEFAULT_ESATACONFIG_VAL  (m_tHBI_ESATA_CONFIG_bits_fisRTxEn )

#define mDEFAULT_QCMDINTR_SRCS  0x0

volatile INT32U mBufferEnd, mDDRSize, firstOOB;
mtPARAM_HBI_PAGE mParamPageHBI;
/* 
{
    // 8 hword header
    {0,1,2,3,4,5,6,7},

    // HBI params
    {
        mDEFAULT_AT_MODE0_VAL,      //mode0
        mDEFAULT_AT_INTERRUPT_SRCS, //intrSrcs
        mDEFAULT_AT_DEV_CNTRL_VAL,  //devCntl	
        0x00,                       // aceWr - Kim LJ- may need to turn on for validation 
        0x00,                       //aceRd
        0x0f,                       //hdPerCyl
        0x3F,                       //secPerTrk
        0x100,                      //devCntl_1 , Write Sequential Config
        0x100,						// hostBufferSegSel
// HBI_Transport Manager params
        mDEFAULT_QCMDCNTLR_VAL,         // R4A70 - qcmdCntr - Queue Command Control
        mDEFAULT_QCMDINTR_SRCS,         // R4A76 - qcmdInt - Queue Interrupt Enable
        mDEFAULT_ESATAERRINT_SRCS,      // R4AAE - esataErrint - ESATA Error Interrupt Mask
        mDEFAULT_TMFLOWINT_SRCS,        // R4AB2 - tmIntSrc - Transport Manager Flow Interrupt Mask
        mDEFAULT_ESATACONFIG_VAL,       // R4ABA - esataCnfg - eSATA Configuration
    },
    
    // other param struct values
};
*/

/*******************************************************************
*																   
*  NAME:        mInitSystemVars												   
*																   
*  FILENAME:    config.c 											   
*																   
*  PARAMETERS:  None    											   
*																   
*  DESCRIPTION: Initializes some basic configuration structures.    
*																   
*  RETURNS:     None 
*
*  date         by              description 
*  10/14/00     Lau Nguyen      Initial release     											   
*	   
********************************************************************/

void mInitSystemVars (void)
{
    mSystemState.uFlags.all             = 0x0000;   // clear all bits
    mSystemState.curState               = mRESET_STATE;
 
	mParamPageHBI.header.reserved[0] = 0x00;
	mParamPageHBI.header.reserved[1] = 0x01;
	mParamPageHBI.header.reserved[2] = 0x02;
	mParamPageHBI.header.reserved[3] = 0x03;
	mParamPageHBI.header.reserved[4] = 0x04;
	mParamPageHBI.header.reserved[5] = 0x05;
	mParamPageHBI.header.reserved[6] = 0x06;
    mParamPageHBI.header.revision = 0x07;

	mParamPageHBI.params.mode0 = mDEFAULT_AT_MODE0_VAL;
	mParamPageHBI.params.intrSrcs = mDEFAULT_AT_INTERRUPT_SRCS;
	mParamPageHBI.params.devCntl = mDEFAULT_AT_DEV_CNTRL_VAL;
	mParamPageHBI.params.aceWr =0x00;
	mParamPageHBI.params.aceRd =0x00;
	mParamPageHBI.params.hdPerCyl =0x0f;
	mParamPageHBI.params.secPerTrk = 0x3f;
	mParamPageHBI.params.devCntl_1 = 0x100;
	mParamPageHBI.params.hostBufferSegSel = 0x100;
	mParamPageHBI.params.qcmdCntrl = mDEFAULT_QCMDCNTLR_VAL;
	mParamPageHBI.params.qcmdInt = mDEFAULT_QCMDINTR_SRCS;
	mParamPageHBI.params.esataErrint = mDEFAULT_ESATAERRINT_SRCS;
	mParamPageHBI.params.tmIntsrc = mDEFAULT_TMFLOWINT_SRCS;
	mParamPageHBI.params.esataCnfg = mDEFAULT_ESATACONFIG_VAL;
 
}

/*******************************************************************
*																   
*  NAME:        mInitClkSystem												   
*																   
*  FILENAME:    InitRtns.c 											   
*																   
*  PARAMETERS:  None    											   
*																   
*  DESCRIPTION: Initilizes the clock block    
*																   
*  RETURNS:     None      											   
*	   
*  From InitRTns.C Line 177
********************************************************************/
void mInitClkSystem(void)
{
    int delay, delay1;

    //##### Clocks #######
    // the following values can be generated by a separate macro / program
  // Initialize TBG only when it is not Manteca build.
  // In Manteca build, TBG should have been already initialized by unpack at this point.
  // #if (mMANTECA_FLASH != mENABLE)
    // Set Buffer RAB to 2, ESATA wait state to 2 and HDC RAB waitstate to 3.
    rCPU.CPUTimingCntl = 0xa953;   

    mCLKPWRsrcSelInit(0x2180);          // sel CPU, BM from OSC
    
    #if (mRAB_FREQ == 150)
    mCLKPWRcpuDiv(mCLK_DIV_BY_2);       // CPU = 250Mhz
    //mCLKPWRhdcDiv(mCLK_DIV_BY_2);     // BM = 200Mhz
#if CFG_MVLBOARD > 0    
    mCLKPWRhdcDiv(mCLK_DIV_BY_1);       // BM = 400Mhz  
#else
    mCLKPWRhdcDiv(mCLK_DIV_BY_3);       // BM = 400Mhz  
#endif
    #else // mRAB_FREQ == 120
    mSHOULD_NOT_GET_HERE();
    #endif

    // set and cal TBGA
    #if (OSC_25MHZ == mENABLE)          // mENABLE for 25MHz OSC, mDISABLE for 40MHz OSC
    if ((rSFRS2.testLatch.bits.b6) || (rSFRS2.testLatch.bits.b5))       // Latched bits 6 and 5 must be both zero to select 25MHz input clock
    {
        mSHOULD_NOT_GET_HERE();         // Code clock and PCB jumper do not match.
    }
    // 25MHz OSC
    mCLKPWRsetTBG(1,118);                // TBG A - 500Mhz
    #else
    if (!(rSFRS2.testLatch.bits.b6) || (rSFRS2.testLatch.bits.b5))   // Latched bit 6 = 1 and bit 5=0  to select 40MHz input clock
    {
        mSHOULD_NOT_GET_HERE();         // Code clock and PCB jumper do not match.
    }
    // 40MHz OSC
    mCLKPWRsetTBG(2,98);                // TBG A - 500Mhz
    #endif
    rCLKPWR.TBGAcontrol1.vcoDivSel = 1;    // TBGA VCO Divider = 2.
    rCLKPWR.TBGAcontrol1.kvco = 7;          
    rCLKPWR.TBGAcontrol1.gain = 2;
    //while (!rCLKPWR.TBGAcontrol1.lock);
    // wait for 400 us for TBG lock (instead of using TBG lock)
    for (delay = 0; delay < 2000; delay++)
        for (delay1 = 0; delay1 < 10; delay1++);
  
    // set and cal TBGB
    #if (OSC_25MHZ == mENABLE)          // mENABLE for 25MHz OSC, mDISABLE for 40MHz OSC
    if ((rSFRS2.testLatch.bits.b6) || (rSFRS2.testLatch.bits.b5))       // Latched bits 6 and 5 must be both zero to select 25MHz input clock
    {
        mSHOULD_NOT_GET_HERE();         // Code clock and PCB jumper do not match.
    }

    // 25MHz OSC
    mCLKPWRsetTBGB(1,94);              // TBG B - 800Mhz
    #else
    if (!(rSFRS2.testLatch.bits.b6) || (rSFRS2.testLatch.bits.b5))   // Latched bit 6 = 1 and bit 5=0  to select 40MHz input clock
    {
        mSHOULD_NOT_GET_HERE();         // Code clock and PCB jumper do not match.
    }
    // 40MHz OSC
    mCLKPWRsetTBGB(2,78);              // TBG B - 800Mhz
    #endif
    rCLKPWR.TBGBcontrol1.vcoDivSel = 0; // TBGB VCO Divider = 1.
    rCLKPWR.TBGBcontrol1.kvco = 7;          
    rCLKPWR.TBGBcontrol1.gain = 2;
    //while (!rCLKPWR.TBGBcontrol1.lock);
    // wait for 400 us for TBG lock (instead of using TBG lock)
    for (delay = 0; delay < 2000; delay++)
        for (delay1 = 0; delay1 < 10; delay1++);

    mCLKPWRinitFlashClock(0x551);       // FC prescaler divides by 5, select TBGB, TBG divides by 1
                                        // from TBGB = 800MHz, FC clock could be 800/5 = 160MHz 

    mCLKPWRinitEccClock(0x142);         // select TBGA, TBG divides by 2
                                        // from TBGA = 500MHz, ECC clock could be 500/2=250MHz
                                          
    mCLKPWRinitPwrDownCount(0xFFE4);    // CPU use TBGA, BM use TBGB
    
    
    mCLKPWRsrcSelInit(0x2183);          // sel CPU, BM from dividers.

//    mSFR2initXmClk(0x45);             // XM clk = 100 Mhz, use TBGA
    mSFR2initXmClk(0x55);               // XM clk = 160 Mhz, use TBGB
    mSFR2initStepDnCntl0(0xff);         // Enable all interrupts to switch the CPU 0 clock back to normal.
    mSFR2initStepDnCntl5(0xff);         // Enable all interrupts to switch the CPU 1 clock back to normal.

    mSFR2initStepDnCntl1(0x0621);       // Stepdown control for RAB clock, step-down divisor = 16, normal divisor = 2.
    mSFR2initStepDnCntl2(0x0020);       // Stepdown control for CORE 0 CPU clock.
    mSFR2initStepDnCntl3(0x0020);       // Stepdown control for CORE 1 CPU clock.
    //mSFR2initStepDnCntl4(0x0620);     // Stepdown control for ETM clock. removed from spec? - Karen   
    mTIMERclkCtrlInit(0x0044);          // Run the counter clock at 125Mhz, same as RAB clk

    //mHDCreset(0x1f);            // toggle reset to all blocks of HDC except BM

    // will revisit this later - Karen
    //rSFRS2.ddrPadDrive = 0x0077;
    //rSFRS2.mfJtPadDrive = 0x0203;
    //rSFRS2.testSerPadDrive = 0x0202;
    //rSFRS2.rdcPadDrive = 0x7777;


}


/*******************************************************************
*																   
*  NAME:        mInitSFRs												   
*																   
*  FILENAME:    InitRtns.c 											   
*																   
*  PARAMETERS:  None    											   
*																   
*  DESCRIPTION: Various early Initializations, clears all status
*               sets all gpio lines to input, e.t.c.    
*																   
*  RETURNS:     None      											   
*	   
********************************************************************/
void mInitSFRs (void)
{
    mSFRintrStatusClr(0xffff);              // clear all status          
    rSFRS2.testOutputCntl.test16sel    = 7; // TestIO, needed for Packet Req In

    mCPUintrEnInit(0);
    mSFRintrEnInit(0);
    mSFR2gpioDataInit(0x00,0x00);

    // polarity of GPIO's are opposite for rev 1.0 vs rev 1.1 on 8010
    // KVL - For VanGogh - Alfred will need to make change later

    if(mCLKPWRGetChipRev() == rev1P0)
    {
        mSFR2gpioDirInit(0x7FFF, 0x46);
    }
    else
    {
        //mSFR2gpioDirInit(0x8000, 0x46);         // test 15 is Pack-Ack (Input), test12 (packet Request Out)
    }

    mSFRfiq0Sel(0);                             // enable nothing for core 0 FIQ
    mSFRfiq1Sel(0);                             // enable nothing for core 1 FIQ

    mSFRirq0Sel(mICU_FC | mICU_HDC | mICU_PERIPHERALS | mICU_ESATA);  // enable FC, hdc, esata and peripherals for core 0 irq
    mSFRirq1Sel(0);                                                   // enable nothing for core 1 irq

    // Init cpuIntrCntl1.
    // Basically, disable all interrupt latch and disable JTAG reset by UART.
    mSFRinitcpuIntrCntl1();
    // Will enable HDC and Sata Interrupt after HBI and BM is initialized
    mCPUintrEnInit(mDEFAULT_CPU_INTERRUPT_SRCS &(~(m_tCPU_INTR_bits_sataIn | m_tCPU_INTR_bits_hdcInt)));
    // This is common for both cores.
    mSFRintrEnInit(mDEFAULT_INTERRUPT_SRCS);
#if (ETM_POWER_DOWN == mENABLE)
	mPmCmdETM_PowerDown();
#endif	 

}
// This function initializes/configures BM for two 2Gbit DDR2 chips
// This function must be stored and executed from internal SRAM,  External DDR2 will not be accesible while executing this function.
PRIVATE __inline void mInitDDR2(mUINT_16 size)
{
    volatile unsigned short *wptr;
    volatile unsigned short s_data;
    mUINT_16 delay;	  
  #if(VG_REV_2_0 == mENABLE)
    rHDC.reset.all = 0x0000;                        // R2806h; Clear HDC_reset


   //Program DDR PHY registers
    rBM.dramPhyDqPadCtl0.all = 0xFFFF;              // R2EB0h = 0xFFFF 
    rBM.dramPhyDqPadCtl1.all = 0xFA77;              // R2EB2h = 0xFA77
    rBM.dramPhyDqPadCtl2.all = 0x332C;              // R2EB4h = 0x332C
    rBM.dramPhyClockPad.all  = 0xA077;              // R2EB6h = 0xA077
    rBM.dramPhyAdcmPadCtl0.all = 0x10C0;            // R2EB8h = 0x10C0
    rBM.dramPhyAdcmPadCtl1.all = 0x1277;            // R2EBAh = 0x1277
    rBM.dramPhyAdcmPadCtl2.all = 0x3300;            // R2EBCh = 0x3300
//    rBM->dramPhyAdcmPadCtl3.all = 0x0000;         // R2EBEh = 0x0000

  // Progrqam the read DLL controls
    rBM.dramPhyDll0Cntl.bits.dll0Reset=1;           // R2EA0h[7] Set Reset DLL0 flag
    rBM.dramPhyDll1Cntl.bits.dll1Reset=1;           // R2EA2h[7] Set Reset DLL1 flag
    
    rBM.dramPhyDll0Cntl.all=0x1010;                 // R2EA0h Clear Reset DLL flag and set DLL0 Delay to midpoint, 10000b
    rBM.dramPhyDll1Cntl.all=0x1010;                 // R2EA2h Set DLL1 Delay to midpoint, 10000b

    delay=200;   
    while (delay--);                                // Wait for reset to complete

    
    rBM.dramCntl1.all = 0x66B4;                     // R2E20h;   DDR3_EN=0, RSVD=1, Double_DDR2=1,  Mem_Size=110, 2Gb 
                                                     // Multi_row=1, tRP =  6T, tWR  =  6T
    //  Regardless of size parameter, present code configures for TWO 2Gbit DDR2s 
    // If this assumption is not adequate, uncomment size and/or number of DDR2 installed
//    rBM->dramCntl1.bits.memSize = size;            // Sets size of DDR2
//    rBM->dramCntl1.bits.dblDdrEn = 0;              // Sets BM for a single DDR2
    rBM.dramCntl0.all = 0x60BA;                     // R2E22 Set tRAS = 18T, tWTR =  2T, tRFC = 0x3A(131T)

//    rBM->dramExtMode2.all = 0x0000;                  // R2E28h;  Cas Write Latency = 5T
//Extended Mode Register 2 (EMR2) bits are resereved for DDR2

    rBM.dramModeCntl.all = 0x1A62;                  // R2E2Ch;  Set DLL_CTRL_PPD=1, WR_RECOV =  6T,CAS_L = 6T,BURST_L =4
    
    // from Fidencio, needs to kill the 2nd one when not in used.
    rBM.dramExtMode1.all = 0x0000;                 // R2E2Eh; RDQS_EN=0, DQS_N_EN=0, To select single ended DM and differential DQS. 
                                                    //  Disable On Die Termination  to avoid ODT1 glitches while accessing chip0


   // Program the refresh period
    rBM.refPeriod.all = (7.8*400);                 // R2E26h Program refresh period
    
    rBM.cntrlReg1.bits.DRAMstart = 1;               // R2E00h[12] start SDRAM init

    while (!(rBM.stat2.all & 0x8003));              // R2E14h wait for SDRAM available AND ( DLL0 & DLL1 ) are both locked
      

    rSFRS2.hcpuBankAdr = 0;                         // Activate Chip select 0

    rBM.dramModeCntl.bits.modeWrEn = 1;             // R2E2Ch; set bit15, so bits [14:0] of R2E2Ch are send to DDR2 controlled by CS 0
    rBM.dramExtMode1.bits.emr1WrEn = 1;             // R2E2Eh; set bit15, so bits [14:0] of R2E2Eh are send to DDR2 controlled by CS 0

    rBM.dramModeCntl.bits.modeWrEn = 0;             // Clear bit15 of R2E2Ch
    rBM.dramExtMode1.bits.emr1WrEn = 0;             // Clear bit15 of R2E2Eh

    rSFRS2.hcpuBankAdr = 1;                         // Activate Chip select 1

    rBM.dramModeCntl.bits.modeWrEn = 1;             // R2E2Ch; set bit15, so bits [14:0] of R2E2Ch are send to DDR2 controlled by CS 1
    rBM.dramExtMode1.bits.emr1WrEn = 1;             // R2E2Eh; set bit15, so bits [14:0] of R2E2Eh are send to DDR2 controlled by CS 1

    rBM.dramModeCntl.bits.modeWrEn = 0;             // Clear bit15 of R2E2Ch
    rBM.dramExtMode1.bits.emr1WrEn = 0;             // Clear bit15 of R2E2Eh

    rSFRS2.hcpuBankAdr = 0;                         // Switch back to DDR2 controlled by Chip Select 0


         //TEMPORARY patch for an issue with Van Gogh rev1.0

    rBM.dramPhyDll0Cntl.bits.dll0AutoUpdate = 1;     // R2EA0h[14] Enable auto DLL delay update
    rBM.dramPhyDll1Cntl.bits.dll1AutoUpdate = 1;     // R2EA2h[14] Enable auto DLL delay update
    
    for(delay=0;delay<32;delay++)                       //  
    {                                                   // Perform several reads from DDR2 to update DLL delay
        wptr = (unsigned short *)(SDRAM_DIRECT_START+8*delay);    // Burst mode = 4 half words, thus multiplier "8"
        s_data = *wptr;
    }

    rBM.dramPhyDll0Cntl.bits.dll0AutoUpdate = 0;       // R2EA0h[14] Disable auto update delay
    rBM.dramPhyDll1Cntl.bits.dll1AutoUpdate = 0;       // R2EA2h[14] Disable auto update delay
 
         //END of TEMPORARY patch for an issue with Van Gogh rev1.0
  #else
    rHDC.reset.all = 0x0000;                         // R2806h; Clear HDC_reset

    rBM.dramDebug.bits.ddrSyncRst = 0;              // R2EC0h[1] TEMPORARY Reset Write pointer

    delay=5;   
    while (delay--);                                // Let write pointer reset

    rBM.dramDebug.bits.ddrSyncRst = 1;              // R2EC0h[1] TEMPORARY Release Write pointer reset

    rBM.dramPhyDll0Cntl.bits.dll0Reset=1;            // R2EA0h[7] Set Reset DLL flag
    rBM.dramPhyDll0Cntl.all=0x1010;                 // R2EA0h Clear Reset DLL flag and set DLL0 Delay to midpoint, 10000b
    rBM.dramPhyDll1Cntl.all=0x1010;                 // R2EA2h Set DLL1 Delay to midpoint, 10000b

    delay=200;   
    while (delay--);                                // Wait for reset to complete

    rBM.dramPhyDqPadCtl1.bits.qsPd=1;               // R2EB2h[13] Weak pull down enabled for QS
    
    rBM.dramCntl0.all = 0x60BA;                     // R2E22 Set tRAS = 18T, tWTR =  2T, tRFC = 0x3A(131T)

    rBM.dramCntl1.all = 0x66B4;                     // R2E20h;   DDR3_EN=0, RSVD=1, Double_DDR2=1,  Mem_Size=110, 2Gb 
                                                    // Multi_row=1, tRP =  6T, tWR  =  6T
    //  Regardless of size parameter, present code configures for TWO 2Gbit DDR2s 
    // If this assumption is not adequate, uncomment size and/or number of DDR2 installed
//    rBM.dramCntl1.bits.memSize = size;            // Sets size of DDR2
//    rBM.dramCntl1.bits.dblDdrEn = 0;              // Sets BM for a single DDR2


    rBM.dramModeCntl.all = 0x1A62;                  // R2E2Ch;  Set DLL_CTRL_PPD=1, WR_RECOV =  6T,CAS_L = 6T,BURST_L =4
    
    // from Fidencio, needs to kill the 2nd one when not in used.
    rBM.dramExtMode1.all = 0x0000;                  // R2E2Eh; RDQS_EN=0, DQS_N_EN=0, To select single ended DM and differential DQS. 

    rBM.dramPhyDqPadCtl0.bits.qsRcvType = 0;        // R2EB0h[6] Clear bit 6 to select differential DQS receiver

    rBM.refPeriod.all = 0x0500;                     // R2E26h Program refresh period
    
    rBM.cntrlReg1.bits.DRAMstart = 1;               // R2E00h[12] start SDRAM init

    while (!(rBM.stat2.all & 0x8003));              // R2E14h wait for SDRAM available AND ( DLL0 & DLL1 ) are both locked
      

    rSFRS2.hcpuBankAdr = 0;                         // Activate Chip select 0

    rBM.dramModeCntl.bits.modeWrEn = 1;             // R2E2Ch; set bit15, so bits [14:0] of R2E2Ch are send to DDR2 controlled by CS 0
    rBM.dramExtMode1.bits.emr1WrEn = 1;             // R2E2Eh; set bit15, so bits [14:0] of R2E2Eh are send to DDR2 controlled by CS 0

    rBM.dramModeCntl.bits.modeWrEn = 0;             // Clear bit15 of R2E2Ch
    rBM.dramExtMode1.bits.emr1WrEn = 0;             // Clear bit15 of R2E2Eh

    rSFRS2.hcpuBankAdr = 1;                         // Activate Chip select 1

    rBM.dramModeCntl.bits.modeWrEn = 1;             // R2E2Ch; set bit15, so bits [14:0] of R2E2Ch are send to DDR2 controlled by CS 1
    rBM.dramExtMode1.bits.emr1WrEn = 1;             // R2E2Eh; set bit15, so bits [14:0] of R2E2Eh are send to DDR2 controlled by CS 1

    rBM.dramModeCntl.bits.modeWrEn = 0;             // Clear bit15 of R2E2Ch
    rBM.dramExtMode1.bits.emr1WrEn = 0;             // Clear bit15 of R2E2Eh

    rSFRS2.hcpuBankAdr = 0;                         // Switch back to DDR2 controlled by Chip Select 0


         //TEMPORARY patch for an issue with Van Gogh rev1.0
    rBM.dramPhyDll0Cntl.bits.dll0AutoUpdate = 1;    // R2EA0h[14] Enable auto DLL delay update

    for(delay=0;delay<32;delay++)                   //  
    {                                               // Perform several reads from DDR2 to update DLL delay
        wptr = (unsigned short *)(SDRAM_DIRECT_START+8*delay);    // Burst mode = 4 half words, thus multiplier "8"
        s_data = *wptr;
    }

    rBM.dramPhyDll0Cntl.bits.dll0AutoUpdate = 0;    // R2EA0h[14] Disable auto update delay
         //END of TEMPORARY patch for an issue with Van Gogh rev1.0
  #endif //(REV_2_0 == mENABLE)
}

//    Procedure for Van Gogh and DDR2
/*
       Assign  COLUMN=  1024                          ( Assume it is a 256MByte )
       Assign  ROW=    16384                            
       Assign  BLOCK=      4                            

1st   Verify DDR2 is functional.    
      Write, Read, compare memory address SDRAM_DIRECT_START   
      Use two patterns, all "0" and all "F" to make sure no data bit is stuck. 
      This address  is common for every DDR2 that you are interested.  
      Assign DDR size = MEM_0Mb if data miscompares.
 
2nd   Determine number of COLUMNS supported by installed DDR2 chip.
      Write  address  SDRAM_DIRECT_START+COLUMN512 with pattern 0x0512   ( row 0, column 512, block 0)
      Read  address  SDRAM_DIRECT_START                                  ( row 0, column   0, block 0 )
      If data read from  SDRAM_DIRECT_START is = 0x0512,  then assign column=512    

 
3rd   Determine number of ROWS supported by installed DDR2 chip.
      Write  address  SDRAM_DIRECT_START + ROW4096 with pattern 0x4096   ( row 4096, column 0, block 0)
      Read  address  SDRAM_DIRECT_START                                  ( row    0, column 0, block 0)
      If Data read from  SDRAM_DIRECT_START  is = 0x4096,  then assign row=4096
      and  you are done with rows detection, go to step four.
      
      Write  address  SDRAM_DIRECT_START + ROW8192 with pattern 0x8192   ( row 8192, column 0, block 0)
      Read  address  SDRAM_DIRECT_START                                  ( row    0, column 0, block 0)
      If Data read from  SDRAM_DIRECT_START  is = 0x8192,  then assign row=8192
      
 
4th  Determine number of BLOCKS supported by installed DDR2 chip.
      Write  address  SDRAM_DIRECT_START + BLOCK4 with pattern 0x0004   ( row 0, column 0, block 4)
      Read  address  SDRAM_DIRECT_START                                 ( row 0, column 0, block 0)
      If Data read from  SDRAM_DIRECT_START  is = 0x0004,  then assign block=4
      
5th   Select DDR2 size based on collected column, row, block      

                block = 4                                          block = 8
                column                                             column
------------------------------------                ------------------------------------
row    |    512      |    1024     |                row    |    512    |    1024    |
------------------------------------                ------------------------------------
4096   | MEM_128Mb   |  MEM_0Mb    |                4096   | MEM_0Mb   |  MEM_0Mb   |
------------------------------------                ------------------------------------
8192   | MEM_256Mb   | MEM_512Mb   |                8192   | MEM_0Mb   | MEM_1Gb    |
------------------------------------                ------------------------------------
16384  | MEM_0Mb     | MEM_0Mb     |                16384  | MEM_0Mb   | MEM_2Gb    |
------------------------------------                ------------------------------------

*/

PRIVATE __inline void mInitDDR3(mUINT_16 size)
{
  #if(VG_REV_2_0 == mDISABLE)

    volatile unsigned short *wptr;
    volatile unsigned short s_data;
    mUINT_16 delay;	  

    rHDC.reset.all = 0x0000;                        // R2806h; Clear HDC_reset

    rBM.dramPhyDqPadCtl0.all = 0x01FF;              // R2EB0h = 0xFFFF 
    rBM.dramPhyDqPadCtl1.all = 0xF977;              // R2EB2h = 0xFA77
    rBM.dramPhyDqPadCtl2.all = 0x332C;              // R2EB4h = 0x332C
    rBM.dramPhyClockPad.all  = 0xA077;              // R2EB6h = 0xA077
    rBM.dramPhyAdcmPadCtl0.all = 0x10C0;            // R2EB8h = 0x10C0
    rBM.dramPhyAdcmPadCtl1.all = 0x1277;            // R2EBAh = 0x1277
    rBM.dramPhyAdcmPadCtl2.all = 0x3300;            // R2EBCh = 0x3300


    rBM.dramDebug.bits.ddrSyncRst = 0;              // R2EC0h[1] TEMPORARY Reset Write pointer

    delay=10;   
    while (delay--);                                // Let write pointer reset

    rBM.dramDebug.bits.ddrSyncRst = 1;              // R2EC0h[1] TEMPORARY Release Write pointer reset
    rBM.dramDebug.all |= 0x0010;                    // R2EC0h[1] TEMPORARY Release Write pointer reset

    rBM.dramPhyDll0Cntl.bits.dll0Reset=1;           // R2EA0h[7] Set Reset DLL flag
    rBM.dramPhyDll0Cntl.all=0x1010;                 // R2EA0h Clear Reset DLL flag and set DLL0 Delay to midpoint, 10000b
    rBM.dramPhyDll1Cntl.all=0x1010;                 // R2EA2h Set DLL1 Delay to midpoint, 10000b

    delay=1000;   
    while (delay--);                                // Wait for DLL reset to complete

    rBM.dramPhyDqPadCtl1.bits.qsPd=1;               // R2EB2h[13] Weak pull down enabled for QS
    
    rBM.dramModeCntl.all = 0x1A40;                  // R2E2Ch;  Set DLL_CTRL_PPD=1, WR_RECOV = 10T,CAS_L = 6T,BURST_L =8
    rBM.dramExtMode1.all = 0x0000;                  // Micron
    rBM.dramExtMode2.all = 0x0000;                  // R2E28h;  Cas Write Latency = 5T
    rBM.refPeriod.all = 0x0C30;                     // R2E26h Program refresh period
   
    rBM.dramCntl0.all = 0x188E;                     // R2E22 Set tRAS = 17T, tWTR =  5T, tRFC = 0xE(63T)


//
    rBM.dramCntl1.all = 0xCEB4;                     // R2E20h;   DDR3_EN=1, RSVD=1, Double_DDR3=0,  CKE=01, Mem_Size=110, 2Gb, 
                                                    // Set ODT_RTT_BIT1=1, and ODT_RTT_BIT0=1  to select 50 Ohms On Die Termination.
    rBM.dramPhyDqPadCtl0.bits.qsRcvType = 0;        // R2EB0h[6] Clear bit 6 to select differential DQS receiver

    rBM.dramCntl0.bits.dramReset = 1;               // R2E22h Reset Signal for DDR3
    delay=10000;   
    while (delay--);                                // Wait for reset to complete

   
    rBM.cntrlReg1.bits.DRAMstart = 1;               // R2E00h[12] start SDRAM init

    while (!(rBM.stat2.all & 0x8003));              // R2E14h wait for SDRAM available AND ( DLL0 & DLL1 ) are both locked
      
    rBM.dramCntl1.all &= 0xf7ff;                    // R2E20h[12:11] = 0,  CKE
    delay=4;   
    
    while (delay--);                                // Wait for reset to complete

    rSFRS2.hcpuBankAdr = 0;                         // Activate Chip select 0  [A960]

    rBM.dramExtMode2.bits.emr2WrEn = 1;             // R2E28h; set bit15, so bits [14:0] of R2E28h are send to DDR3 controlled by CS 0
    rBM.dramExtMode2.bits.emr2WrEn = 0;             // Clear bit15 of R2E28h
    delay=2;   
    while (delay--);                                // Wait for reset to complete


    rBM.dramExtMode1.bits.emr1WrEn = 1;             // R2E2Eh; set bit15, so bits [14:0] of R2E2Eh are send to DDR3 controlled by CS 0
    rBM.dramExtMode1.bits.emr1WrEn = 0;             // Clear bit15 of R2E2Eh
    delay=2;   
    while (delay--);                                // Wait for reset to complete

    rBM.dramModeCntl.bits.modeWrEn = 1;             // R2E2Ch; set bit15, so bits [14:0] of R2E2Ch are send to DDR3 controlled by CS 0
    rBM.dramModeCntl.bits.modeWrEn = 0;             // Clear bit15 of R2E2Ch
    delay=26000;   
    while (delay--);                                // Wait for reset to complete

    rBM.dramCntl0.bits.otfZQ = 1;                   // R2E22h[6]=1 on the fly zero calibration command
    rBM.dramCntl0.bits.otfZQ = 0;                   // R2E22h[6]=0
    
    //TEMPORARY patch for an issue with Van Gogh rev1.0
    rBM.dramPhyDll0Cntl.bits.dll0AutoUpdate = 1;    // R2EA0h[14] Enable auto DLL delay update

    for(delay=0;delay<32;delay++)                   //  
    {                                               // Perform several reads from DDR3 to update DLL delay
        wptr = (unsigned short *)(SDRAM_DIRECT_START+8*delay);    // Burst mode = 4 half words, thus multiplier "8"
        s_data = *wptr;
    }

    rBM.dramPhyDll0Cntl.bits.dll0AutoUpdate = 0;     // R2EA0h[14] Disable auto update delay
  
  #endif //(VG_REV_2_0 == mDISABLE)
}

//    Procedure for Van Gogh and DDR2
/*
       Assign  COLUMN=  1024                          ( Assume it is a 256MByte )
       Assign  ROW=    16384                            
       Assign  BLOCK=      4                            

1st   Verify DDR2 is functional.    
      Write, Read, compare memory address SDRAM_DIRECT_START   
      Use two patterns, all "0" and all "F" to make sure no data bit is stuck. 
      This address  is common for every DDR2 that you are interested.  
      Assign DDR size = MEM_0Mb if data miscompares.
 
2nd   Determine number of COLUMNS supported by installed DDR2 chip.
      Write  address  SDRAM_DIRECT_START+COLUMN512 with pattern 0x0512   ( row 0, column 512, block 0)
      Read  address  SDRAM_DIRECT_START                                  ( row 0, column   0, block 0 )
      If data read from  SDRAM_DIRECT_START is = 0x0512,  then assign column=512    

 
3rd   Determine number of ROWS supported by installed DDR2 chip.
      Write  address  SDRAM_DIRECT_START + ROW4096 with pattern 0x4096   ( row 4096, column 0, block 0)
      Read  address  SDRAM_DIRECT_START                                  ( row    0, column 0, block 0)
      If Data read from  SDRAM_DIRECT_START  is = 0x4096,  then assign row=4096
      and  you are done with rows detection, go to step four.
      
      Write  address  SDRAM_DIRECT_START + ROW8192 with pattern 0x8192   ( row 8192, column 0, block 0)
      Read  address  SDRAM_DIRECT_START                                  ( row    0, column 0, block 0)
      If Data read from  SDRAM_DIRECT_START  is = 0x8192,  then assign row=8192
      
 
4th  Determine number of BLOCKS supported by installed DDR2 chip.
      Write  address  SDRAM_DIRECT_START + BLOCK4 with pattern 0x0004   ( row 0, column 0, block 4)
      Read  address  SDRAM_DIRECT_START                                 ( row 0, column 0, block 0)
      If Data read from  SDRAM_DIRECT_START  is = 0x0004,  then assign block=4
      
5th   Select DDR2 size based on collected column, row, block      

                block = 4                                          block = 8
                column                                             column
------------------------------------                ------------------------------------
row    |    512      |    1024     |                row    |    512    |    1024    |
------------------------------------                ------------------------------------
4096   | MEM_128Mb   |  MEM_0Mb    |                4096   | MEM_0Mb   |  MEM_0Mb   |
------------------------------------                ------------------------------------
8192   | MEM_256Mb   | MEM_512Mb   |                8192   | MEM_0Mb   | MEM_1Gb    |
------------------------------------                ------------------------------------
16384  | MEM_0Mb     | MEM_0Mb     |                16384  | MEM_0Mb   | MEM_2Gb    |
------------------------------------                ------------------------------------

*/

// This function must be stored and executed from internal SRAM,  External DDR2 will not be accesible while executing this function.

PRIVATE __inline mUINT_16 mCalcDdr2Size(mUINT_16 cs)
{

#if (VG_REV_2_0 == mENABLE)
    if (cs)
        if (0 == rBM.dramCntl1.bits.dblDdrEn)
            return MEM_0Mb;

    switch (rBM.dramCntl1.bits.memSize)
    {
        case 0:
            return MEM_8Gb;

        case 1:
            return MEM_64Mb;

        case 2:
            return MEM_128Mb;

        case 3:
            return MEM_256Mb;
        
        case 4:
            return MEM_512Mb;

        case 5:
            return MEM_1Gb;

        case 6:
            return MEM_2Gb;

        case 7:
            return MEM_4Gb;
        default:
            mSHOULD_NOT_GET_HERE();            
    }
    return(0);
#else
    
    volatile unsigned short *wptr;
    volatile unsigned short s_data;
    mUINT_16        memSize, column, row, block, chipSelect;

    column = COLUMN;                                //assumed it is a 256MByte DDR2 and set column, row, and block accordingly
    row    = ROW;
    block  = BLOCK;

    chipSelect = cs;                                // DDR2 Chip Select
    if(chipSelect == 0)
    {
        rSFRS2.hcpuBankAdr = 0;                    // Activate Chip select 0
    }
    else if (chipSelect == 1)
    {
        rSFRS2.hcpuBankAdr = 1;                    // Activate Chip select 1
    }     
    else
    {
            mSHOULD_NOT_GET_HERE();                 // Not a valid chip select!!
    }
    
    // Verify basic DDR2 functionality, write/read
    wptr = (unsigned short *)SDRAM_DIRECT_START;    // Load first DDR2 address
    *wptr = 0x0000;                                 // With pattern 0x0000
    s_data = *wptr;
    
    if(s_data != 0x0000)
    {
        memSize = MEM_0Mb;                          // Cannot access DDR2
        return(memSize);                            // Return size 0
    }

    *wptr = 0xFFFF;                                 // Then with pattern 0xFFFF
    s_data = *wptr;

    if(s_data != 0xFFFF)
    {
        memSize = MEM_0Mb;                          // Cannot access DDR2
        return(memSize);                            // Return size 0
    }


            
    // Column Detection 
    wptr = (unsigned short *)(SDRAM_DIRECT_START+COLUMN512); // Try writing at column 512, row 0, block 0
    *wptr = 0x0512;                                         // With pattern 0x0512

    wptr = (unsigned short *)SDRAM_DIRECT_START;    // First DDR2 address
    s_data = *wptr;                                 // Read from column 0, row 0, block 0

    if (s_data == 0x0512)                           // Column 512 and 0 select same physical DDR2 address?
    {
        column = 512;                               // Then DDR2 only supports 512 columns
    }


    // Row Detection

    wptr = (unsigned short *)(SDRAM_DIRECT_START + ROW4096);    // Try writing at row 4096, column 0, block 0
    *wptr = 0x4096;                                             // With pattern 0x4096

    wptr = (unsigned short *)SDRAM_DIRECT_START;    // First DDR2 address
    s_data = *wptr;                                 // Read from column 0, row 0, block 0

    if (s_data == 0x4096)                           // Row 4096 and 0 select same physical DDR address?
    {
        row = 4096;                                 // Then external DDR2 only supports 4096 rows
    }
    else
    {
        wptr = (unsigned short *)(SDRAM_DIRECT_START + ROW8192);    // Try writing at row 8192, column 0, block 0
        *wptr = 0x8192;                                             // With pattern 0x8192

        wptr = (unsigned short *)SDRAM_DIRECT_START;    // First DDR2 address
        s_data = *wptr;                                 // Read from column 0, row 0, block 0

        if (s_data == 0x8192)                           // Row 8192 and 0 select same physical DDR address?
        {
            row = 8192;                                 // Then external DDR2 only supports 8192 rows
        }
    }    
    
    
    // Block Detection
    wptr = (unsigned short *)(SDRAM_DIRECT_START + BLOCK4); // Try writing at column 0, row 0, block 4
    *wptr = 0x0004;                                         // With pattern 0x0004

    wptr = (unsigned short *)SDRAM_DIRECT_START;    // First DDR2 address
    s_data = *wptr;                                 // Read from column 0, row 0, block 0

    if (s_data == 0x0004)                           // Block 4 and 0 select same physical DDR2 address?
    {
        block = 4;                                  // Then DDR2 only supports 4 blocks
    }
 

                                                    // DDR2 size test is completed
    rSFRS2.hcpuBankAdr = 0;                         // Force  Chip select 0, regardless of DDR2 being tested
 
    
    // determine DDR size from column, row, and block
    
    if (block == 4)
    {
        if (column==1024 && row==8192) 
        {
            memSize = MEM_512Mb;                    // 64 MByte external DDR
        }
        else if (column==512 && row==8192)
        {
            memSize = MEM_256Mb;                    // 32 MByte external DDR
        }
        else if (column==512 && row==4096)
        {
            memSize = MEM_128Mb;                    // 16 MByte external DDR
        }
        else  //Not a valid configuration
        {
            memSize = MEM_0Mb;                      // Cannot detect DDR size
        }
    }
    else                // for block = 8
    {
        if (column==1024 && row ==16384) 
        {
            memSize = MEM_2Gb;                      // 256 MByte external DDR
        }
        else if (column==1024 && row==8192)
        {
            memSize = MEM_1Gb;                      // 128 MByte external DDR
        }
        else  //Not a valid configuration
        {
            memSize = MEM_0Mb;                      // Cannot detect DDR size
        }
    }


    return(memSize);
#endif    
}

/*
PRIVATE void dummy_read(mUINT_16 words)
{
  mUINT_16 i;

  for(i=0;i<words;i++)
  {
   (*((volatile mUINT_16 *)(mBFR_SDRAM_START_UNBUF + 4*i)));
  }
}

PRIVATE __inline void mSetupBM(mUINT_16 size)
{
    mUINT_16 delay = 5;

    rHDC.reset.bits.bm = 0x0;     // BM reset off  
    
    // Toggle sync_enable R2EC0[1]
    // Drive sync_rst and sync_en to DDR PHY 
    (*(volatile mUINT_16 *)0x1C002EC0) &= 0xfffd;
    while (delay--);
    (*(volatile mUINT_16 *)0x1C002EC0) |= 0x2;
    
    // Set DLL reset
    (*(volatile mUINT_16 *)0x1C002EA0) |= (1<<7);
    
    // Clear DLL reset
    (*(volatile mUINT_16 *)0x1C002EA0) = 0x1010;
    (*(volatile mUINT_16 *)0x1C002EA2) = 0x1010;
    
    delay = 200;
    while (delay--);
    
    // Set R2EB2[13] weak pull down enable for QS
    (*(volatile mUINT_16 *)0x1C002EB2) |= 0x2000;
    
    // now set up DDR timing
    
    if (size == MEM_512Mb)
    {
       rBM.dramCntl0.all = 0x60BA;
       rBM.dramCntl1.all = 0x44B4;
    }
    else if (size == MEM_256Mb)
    {
    }
    else if (size == MEM_128Mb)
    {
    }
    else
    {
    }

    rBM.dramModeCntl.all = 0x1A62;
    rBM.dramExtMode1.all = 0x0400;
    rBM.refPeriod.all = 0x0500;
    
    rBM.cntrlReg1.all |= 0x1000;          // start SDRAM init
    
    while (!(rBM.stat2.all & 0x8003));    // wait for SDRAM available
    
    // toggle WR_RECOV R2E2C[15]
    (*(volatile mUINT_16 *)0x1C002E2C) |= 0x8000;
    (*(volatile mUINT_16 *)0x1C002E2C) &= 0x7FFF;
    
    // toggle extended mode
    (*(volatile mUINT_16 *)0x1C002E2E) = 0x8400;
    (*(volatile mUINT_16 *)0x1C002E2E) &= 0x7FFF;
    
    (*(volatile mUINT_16 *)0x1C002EA0) |= 0x4000;
    
    // issue dummy read
    dummy_read(0x1024);
    
    (*(volatile mUINT_16 *)0x1C002EA0) &= 0xB000;

}
*/

//This is to detect external DDR size--support up to 64MB 
/*
1st    Configure size of DDR to 64 Mbytes, either boot mode or by writing to register.
 
2nd   Verify DDR is functional.    
         Write, Read, compare memory addresses in the range of 0x14000000  to 0x14000010.  
         Use two patterns, all "0" and all "F" to make sure no data bit is stuck. 
         This address range is common to all four sizes of DDR that you are interested.  
         Assign DDR size = 0MB if data miscompares.
 
3rd   Determine number of  DDR COLUMNS supported by installed DDR chip.
       Assign  COLUMNS=1024                          ( Assume it is a 64MByte )
       Write  address  0x14000200 with D=0x0256      ( DDR row 0, column 256)
       Read  address  0x14000000                     ( DDR row 0, column 0 )
       If Data read from  0x14000000 is = 0x0256,  then assign COLUMNS=256    
       and you are done with column detection, go to step four.
       Write  address  0x14000400 with D=0x0512      ( DDR row 0, column 512)
       Read  address  0x14000000                     ( DDR row 0, column 0 )
       If Data read from  0x14000000 is = 0x0512,  then assign COLUMNS=512    
       and you are done with column detection, go to step four.
 
4th  Determine number of  DDR ROWS supported by installed DDR chip.
       Assign  ROWS=8192                             ( Assume it is a 64MByte )
       Write  address  0x14800000 with D=0x4096      ( DDR row 4096, column 0)
       Read  address  0x14000000                     ( DDR row    0, column 0 )
       If Data read from  0x14000000 is = 0x4096,  then assign ROWS=4096 and 
       you are done with rows detection, go to step five.
 
5th  Chose DDR size from table below.
 
                           COLUMNS
------------------------------------------------
ROWS   | 256    |  512    |    1024  |
------------------------------------------------
4096     | 8 MB  | 16 MB |  Invalid
----------------------------------------------
8192     |Invalid | 32MB   | 64 MB
*/

/*******************************************************************
*
*  NAME:        mInitDRAM
*
*  FILENAME:    InitRtns.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Initializes the DRAM
*
*  RETURNS:     None
*
********************************************************************/
void mInitDRAM(void)
{


/*  Procedure for Van Gogh to initialize Buffer Manager, external DDR2 chip(s).
    Detect size of external memory
    Configure Buffer Manager for detected size. Note Buffer manager is limited to a linear address range of 256 MB. 
    To operate beyond this limitation, firmware must manipulate block size. rSFRS2.hcpuBankAdr for master CPU core
    rSFRS2.scpuBankAdr for slave CPU core.
     
    Adjust size of data buffer, depending of detected memory size, up to a max limit of 256MB.
*/
    mUINT_16    cs0Ddr2size, cs1Ddr2size;           // size of DDR2 controlled by CS0 and CS1.

    if (rSFRS2.testLatch.bits.b9)                   // Is latched TES_09 high, indicating DDR3 installed?,  Latched bit9=1                               
    {                                                 
        #if (VG_REV_2_0 == mENABLE)
        #else
        mInitDDR3(MEM_2Gb);                         // Initialize Buffer Manager for TWO  2Gb DDR2 parts
        #endif
        cs0Ddr2size = mCalcDdr2Size(0);             // Determine size of DDR2 controlled by CS0
        rBM.dramCntl1.bits.dblDdrEn = 0;            // Configure for Single DDR2
        mDDRSize = cs0Ddr2size;                 // Total memory is just the size of DDR2 controlled by CS0  
    }
    else                                                    
    {                                               // This section is for DDR2
        #if (VG_REV_2_0 == mENABLE)
        #else
        mInitDDR2(MEM_2Gb);                         // Initialize Buffer Manager for TWO  2Gb DDR2 parts
        #endif
        cs0Ddr2size = CS0DDRSIZE;//mCalcDdr2Size(0);             // Determine size of DDR2 controlled by CS0
        cs1Ddr2size = CS1DDRSIZE;//mCalcDdr2Size(1);             // Determine size of DDR2 controlled by CS1

        if(cs0Ddr2size == cs1Ddr2size)              // If the size of two DDR2 is identical, use DUAL DDR2 config.
        {                                           // ( It is possible to use two DDR2 of different size, but I did not consider it a viable option
                                                    // If in the future this option is implemented, configure R2E20[memSize] for smaller of two sizes.)
            rBM.dramCntl1.bits.dblDdrEn = 1;        // Keep Dual DDR2 Configuration

            if(cs0Ddr2size == MEM_2Gb)              // If the size of a single DDR2 matches the maximum linear address range of Buffer Manager, 256Mb             
            {                                       // 
                mDDRSize = cs0Ddr2size;         // Then Limit Total Memory size to max linear address range of Buffer Manager. 
                                                    // so data buffer size does not exceed, max linear address range of Buffer Manager.
            }
            else
            {
                mDDRSize = cs0Ddr2size << 1;    // Total size of memory is (2 * cs0Ddr2size)  
            }                                       // Buffer manager can access both DDR2s, without firmware intervention.
        }
        else
        {
            rBM.dramCntl1.bits.dblDdrEn = 0;        // Configure for Single DDR2

            mDDRSize = cs0Ddr2size;             // Total memory is just the size of DDR2 controlled by CS0  
        }
    }
    
    // R2E20[memSize] is define as the memory size  per DDR2 chip,  Not total memory.
    if (cs0Ddr2size == MEM_0Mb) 
    {                                                     
        mSHOULD_NOT_GET_HERE();                     // No active DDR2 found
    }
    else if (cs0Ddr2size == MEM_64Mb) 
    {                                                     
        rBM.dramCntl1.bits.memSize = 1;             // Set Memory size to  64Mb
    }
    else if (cs0Ddr2size == MEM_128Mb) 
    {                                                     
        rBM.dramCntl1.bits.memSize = 2;             // Set Memory size to  128Mb
    }
    else if (cs0Ddr2size == MEM_256Mb)                 
    {
        rBM.dramCntl1.bits.memSize = 3;             // Set Memory size to  256Mb
    }      
    else if (cs0Ddr2size == MEM_512Mb)                  
    {
        rBM.dramCntl1.bits.memSize = 4;             // Set Memory size to  512Mb
    }               
    else if (cs0Ddr2size == MEM_1Gb)                    
    {
        rBM.dramCntl1.bits.memSize = 5;             // Set Memory size to  1Gb
    }              
    else if (cs0Ddr2size == MEM_2Gb)                    
    {
        rBM.dramCntl1.bits.memSize = 6;             // Set Memory size to  2Gb
    } 

     // End of buffer depends on total memory size
    if (mDDRSize == MEM_0Mb) 
    {                                               // No valid DDR detected     
        mSHOULD_NOT_GET_HERE();                     // 
    }
    else if (mDDRSize == MEM_128Mb)             // 16MB
    {
        mBufferEnd = 0xffffffUL;
    }       
    else if (mDDRSize == MEM_256Mb)             // 32MB
    {
        mBufferEnd = 0x1ffffffUL;
    }      
    else if (mDDRSize == MEM_512Mb)             // 64MB
    {
        mBufferEnd = 0x3ffffffUL;  
    }               
    else if (mDDRSize == MEM_1Gb)               // 128MB
    {
        mBufferEnd = 0x7ffffffUL;  
    }              
    else if (mDDRSize == MEM_2Gb)               // 256MB
    {
        mBufferEnd = 0xfffffffUL;   
    } 
    else                                            // ??? MB
    {                                               // No valid DDR detected     
        mSHOULD_NOT_GET_HERE();                     // 
    }
}




/*******************************************************************
*
*  NAME:        InitHdcBM
*
*  FILENAME:    InitRtns.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Initializes the HDC BM
*
*  RETURNS:     None
*
********************************************************************/
void InitHdcBM(void)
{
    mBMintr0Init(0xffff);          // all off
    mBMintr1Init(0xffff);        

    mBMstartDram(mBFR_DPD_EN);     // enable dynamic power down

  #if (mDAVINCI_COMPATIBLE == mENABLE)
    mBMsetDVcompatibleMode(mTRUE);
  #else //(mDAVINCI_COMPATIBLE == mENABLE)
    mBMsetDVcompatibleMode(mFALSE);
  #endif //(mDAVINCI_COMPATIBLE == mENABLE)

    mBMsetHostSectorSize(0x100);       // words 
    mBMsetSectorSizeRatio(1<<8 | mNV_SECTOR_SIZE_RATIO<<4 | mNV_SECTOR_SIZE_RATIO);           // sets host/disk sector size ratio
    mBMsetDiskSectorSize(mAU_SIZE/2);                       // words for AU size
// set up BM transfer pointer 
// For now, use Host Segment 0 for Write and Host Segment 1 for Read (except Write Long)
// Host Segment 2 for Write Seq and Host Segment 3 for Read Sequential, Host Segment 7 for Internal (tbd)
    mBMsetHostSeg0Size(0x8);
    mBMsetHostSeg1Size(0x8);
	mBMsetHostSeg2Size(0x8);
	mBMsetHostSeg3Size(0x8);
	mBMsetHostSeg4Size(0x8);
	mBMsetHostSeg5Size(0x8);
	mBMsetHostSeg6Size(0x8);
	mBMsetHostSeg7Size(0x8);
#if 0
    // Host Segment 0 set as 4K, Cache Start at 128K
    mBfrSetSegSize(mBFR_HOST_SEGMENT0,mConfig.sBuffer.segSize);
    mBfrSetHostSegPtr(mBFR_HOST_SEGMENT0, mConfig.sBuffer.segmentHostStart);



    // Host Segment 1 
    mBfrSetSegSize(mBFR_HOST_SEGMENT1,mConfig.sBuffer.segSize);
    mBfrSetHostSegPtr(mBFR_HOST_SEGMENT1, mConfig.sBuffer.segmentHostStart);

    // Host Segment 2 
    mBfrSetSegSize(mBFR_HOST_SEGMENT2,mConfig.sBuffer.segSize);
    mBfrSetHostSegPtr(mBFR_HOST_SEGMENT2, mConfig.sBuffer.segmentHostStart);

    // Host Segment 3 
    mBfrSetSegSize(mBFR_HOST_SEGMENT3,mConfig.sBuffer.segSize);
    mBfrSetHostSegPtr(mBFR_HOST_SEGMENT3, mConfig.sBuffer.segmentHostStart);

    // Host Segment 7 
    mBfrSetSegSize(mBFR_HOST_SEGMENT7,mConfig.sBuffer.segSize);
    mBfrSetHostSegPtr(mBFR_HOST_SEGMENT7, mConfig.sBuffer.segmentHostStart);

    // Disk Segment  
    mBfrSetSegSize(mBFR_DISK_SEGMENT,mConfig.sBuffer.segSize);
    mBfrSetDiskSegPtr(mConfig.sBuffer.segmentDiskStart);
#endif

    //Note since the set function or's in the value, we must clear the entire field first to know what's there.
    mBMclrCntrl1(m_tBM_CNTRL_REG1_bits_diskBurstLenSel64 | m_tBM_CNTRL_REG1_bits_diskBurstLenSel48 | m_tBM_CNTRL_REG1_bits_diskBurstLenSel32 | m_tBM_CNTRL_REG1_bits_diskBurstLenSel16);
    mBMsetCntrl1(m_tBM_CNTRL_REG1_bits_diskBurstLenSel64);

    mBMclrCntrl1(m_tBM_CNTRL_REG1_bits_hostBurstLenSel64 | m_tBM_CNTRL_REG1_bits_hostBurstLenSel48 | m_tBM_CNTRL_REG1_bits_hostBurstLenSel32 | m_tBM_CNTRL_REG1_bits_hostBurstLenSel16);
   #if (VANGOGH_1_1_BM_BUG == mENABLE)
    mBMsetCntrl1(m_tBM_CNTRL_REG1_bits_hostBurstLenSel64);
   #else
    mBMsetCntrl1(m_tBM_CNTRL_REG1_bits_hostBurstLenSel64);
   #endif //(VANGOGH_1_1_BM_BUG == mENABLE)
    
}


/*******************************************************************
*																   
*  NAME:        InitTestMuxes 												   
*																   
*  FILENAME:    InitRtns.c 											   
*																   
*  PARAMETERS:  None    											   
*																   
*  DESCRIPTION: Initializes the Test Muxes    
*																   
*  RETURNS:     None
*
********************************************************************/
void InitTestMuxes (void)
{
    rSFRS2.testOutputCntl.test7_0sel   = 0x10; // HFIQ, HIRQ, SFIQ, SIRQ, sector, SG, RG, WG. (sorry but no INDEX)
// jra    rSFRS2.testOutputCntl.test7_0sel   = 0x1f; // testout 0-7
    rSFRS2.testOutputCntl.test8sel      = 0;    // RC NRZ[8]
    rSFRS2.testOutputCntl.test9sel      = 7;    // TestIO9

    rSFRS2.testOutputCntl.test10sel     = 7;    // TestIO, M_READ_FAULT for media, Not used for host
#if (mDDO_ENABLE == mENABLE)
    rSFRS2.testOutputCntl.test11sel     = 0x2;  // DDO
#else
    rSFRS2.testOutputCntl.test11sel     = 0xf;  // TEST Output
#endif
    rSFRS2.testOutputCntl.test12sel     = 0xf;  // TestIO, Seek Complete In(Host)/Out(Media)
    rSFRS2.testOutputCntl.test13sel     = 0xf;  // TestIO, needed for Packet Data Out/In

#if (mDDO_ENABLE == mENABLE)
    rSFRS2.testOutputCntl.test14sel     = 0x1;  // DDO CLK
#else
    rSFRS2.testOutputCntl.test14sel    = 0xf;  // TEST Output
#endif
    rSFRS2.testOutputCntl.test15sel     = 7;    // TestIO, REQ OUT(Host), ACK OUT(Media)
    rSFRS2.testOutputCntl.test16sel     = 7;    // TestIO, ACK IN(Host), REQ IN(Media)

    rSFRS2.testOutputCntl.txOutSel      = 1;    // Select UART xmit output
    rSFRS2.testOutputCntl.rxOutSel      = 1;    // Select UART recv
    rSFRS2.testOutputCntl.f_dOutSel     = 0;
    rSFRS2.testOutputCntl.f_clkOutSel   = 0;
    rSFRS2.testOutputCntl.txOutSel      = 0;
    rSFRS2.testOutputCntl.rxOutSel      = 0;
}




/*******************************************************************
*																   
*  NAME:        mInitHDC												   
*																   
*  FILENAME:    InitRtns.c 											   
*																   
*  PARAMETERS:  None    											   
*																   
*  DESCRIPTION: Initializes the different blocks in the HDC    
*  RETURNS:     None 
*
*  date         by              description 
*  12/14/00     Lau Nguyen      Added init. of Channel, servo, rest of blocks     											   
********************************************************************/
void mInitHDC(void)
{
    mHostReset();   // if Host does not continuously sending ComReset, we can reset our TM here if not
                    // we have to wait for PHY enable
    if ((mPhyLinkGetSataPmState() & 0x0F0F) != 0x0103)

    {   // at power up we force to InitSataPhyLink, the reason for checking host presence and phy established
        // is for the debugged time when someone just want to reload code but not power up.  In this case, we
        // don't need to initialize Phy/Link again because we will not get PhyRdyDet.
        mInitSataPhyLink();	 
        mSystemState.curState = mPOWER_UP_STATE;
        firstOOB = mTRUE;
    }
    InitTestMuxes();
    mHDCClearIntrStatus();
    mHDCintrEnInit(0);
    InitHdcBM();

    mPmData.curPowerMode = mPM_ACTIVE;
   
}


/*******************************************************************
*																   
*  NAME:        mInitHBI												   
*																   
*  FILENAME:    InitRtns.c 											   
*																   
*  PARAMETERS:  None    											   
*																   
*  DESCRIPTION: Initalizes the HBI    
*																   
*  RETURNS:     None      											   
*	   
********************************************************************/
void mInitHBI (void)
{

    //do the next line esle sector count gets cleared to a 0
//YW : Clear ATA mode reg to read mode    
    mHostClrBitAtMode(m_tHOST_BUS_INTERFACE_ATmode0_bits_writeDir);
    mHostInitParams(&mParamPageHBI,mMASTER_ONLY);
    mHostInitTMparams(&mParamPageHBI);     
    
    if ((mSystemState.curState == mPOWER_UP_STATE)||(mSystemState.curState == mRESET_STATE))
    {
        mHostSetTaskFileReg(mTF_SECTOR_NUM_REG,1);
        mHostSetTaskFileReg(mTF_SECTOR_CNT_REG,1);
        mHostSetTaskFileReg(mTF_CYL_HIGH_REG  ,0);
        mHostSetTaskFileReg(mTF_CYL_LOW_REG   ,0);
        mHostSetTaskFileReg(mTF_DEV_HEAD_REG  ,0);
        
        //  Cannot write to mTF_ERROR because it would send a D2H, write to alternate port
        //    mHostSetTaskFileReg(mTF_ERROR_REG     ,1);
        mHostSetAltAtError(1);
    }
}




/*********************************************************************************************************
** Function Name         : InitSystem
** Function Describe     : The init of all
** Input  Parameter      : None
** Output Parameter      : None
** Global Parameter      : None
********************************************************************************************************/
void InitSystem(void)
{  
  mInitClkSystem();
  mInitSFRs();
  mInitSystemVars( );
  mInitDRAM();
  mInitHDC();
  mInitHBI( );

//Memoright Init function
  InitSATA( );
  InitSeq();
  InitIntc( );
  InitSPI();
 // TestSPI();
//  TestSPI1();
  //Test();
  while ((mPhyLinkGetSataPmState() & 0x0F0F) != 0x0103); 
  mSendStatusToHost( );

}
/*******************************************************************************************************
*                                                                     End Of File
            ********************************************************************************************************/
