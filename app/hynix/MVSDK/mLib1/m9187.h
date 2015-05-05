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

#ifndef  _m9187_H_INC
#define  _m9187_H_INC

#include "mGLOBALS.h"
#include "Conds.h"
#define  m8010_SEQ_NUM_CHAN          8
#define  m8010_SEQ_TIMING_CONTROL    6       // number of entries in sequencerInterfaceTiming table
//=======================================================================
//     [[[[ MPU Interface Module ]]]]
//=======================================================================

typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 rsvd_b0_bit4   : 5;
        mUINT_16 bm     		: 1;
        mUINT_16 mpu     		: 1;
        mUINT_16 rsvd_b7_b8  	: 2;
        mUINT_16 esata   		: 1;
        mUINT_16 rsvd_b10_15    : 6;
    } bits;
}mtHDC_INT;               // HDC interrupt 


typedef struct
{
    mtHDC_INT      intrMask;        // 0x2800
    mtHDC_INT      intrStatus;      // 0x2802

    struct
    {
        mUINT_16 cpuTO      	    : 1;
        mUINT_16 rsvd_b1_b15  		: 15;
    } status;                       			// MPU stat

    union 
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 rsvd_b0_b4     : 5;
            mUINT_16 bm     		: 2;
            mUINT_16 rsvd_b7_b15    : 9;
        }bits;
    } reset;                        		// MPU RST 0x2806

    mUINT_16     padR2808;          		// 0x2808
    mUINT_16     waitCntr   	    : 16;   // 0x280A
 } mtHDC_MPU;              // HDC MPU Block


//=======================================================================
//     [[[[ Clock Generator and Power Management ]]]]
//=======================================================================
typedef struct
{
    mUINT_16 TBG_ssc_en             : 1;
    mUINT_16 TBG_pu_ssc             : 1;
    mUINT_16 TBG_vco_vrng           : 2;
    mUINT_16 TBG_kvco               : 4;
    mUINT_16 TBG_vcodiv_sel         : 2;
    mUINT_16 rsvd                   : 5;
    mUINT_16 TBG_lock               : 1;
} mtTBGcontrol1;          


#define mCLK_DIV_HI     0
#define mCLK_DIV_BY_1   1
#define mCLK_DIV_BY_2   2
#define mCLK_DIV_BY_3   3
#define mCLK_DIV_BY_4   4
#define mCLK_DIV_BY_5   5
#define mCLK_DIV_BY_6   6

typedef struct
{
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 oscStableCnt	: 4;	// Oscillator Stable Count  
            mUINT_16 cpuTbgSel		: 1;	// CPU TBG Select
            mUINT_16 bmTbgSel	    : 1;	// BM TBG Select
            mUINT_16 rsvd_b6_b7     : 2;
            mUINT_16 pwrCnt	        : 8;	// Power Down Count
        } bits;
     } pwrDownCnt;					// RA800: Power Down / Test Registers
     

    struct
    {
        mUINT_16 cpuClk				: 3;	// CPU TBG Divider Select
		mUINT_16 rsvd_b3			: 1;
        mUINT_16 hdcClk  			: 3;	// BM TBG Divider Select
		mUINT_16 rsvd_b7_b15		: 9;

    } clkDiv0;						// RA802: Clock Divider 0
    

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 cpuClk         : 1;		// CPU Clock Select
            mUINT_16 hdcClk         : 1;		// BM Clock Select
            mUINT_16 rsvd_b2_b13    : 12;
            mUINT_16 oscClk         : 2;		// Oscillator Clock Divider Select
        } bits;
    } clkDiv1;						// RA804: Clock Divider 1
    
    union
    {
        mUINT_16 all; 
        struct
        {
            mUINT_16 sRomPwrdn           :1;	// SROM Power Down
            mUINT_16 hRomPwrdn           :1;	// HROM Power Down
            mUINT_16 rsvd_b2_b3          :2;	
            mUINT_16 rsvd_b4             :1;  
            mUINT_16 disBMclk            :1;	// BM/SDRAM Clock Disable
            mUINT_16 tcmPwrdnEn          :1;	// TCM Power Down Enable
            mUINT_16 rsvd_b7             :1;	
            mUINT_16 tcmNceRdyCnt        :4;	// TCM NCE Ready Count
            mUINT_16 partialPwrdn1       :1;	// Partial Power Down 1 Mode
            mUINT_16 partialPwrdn2       :1;	// Partial Power Down 2 Mode
            mUINT_16 fullPwrdn           :1;	// Full Power Down
            mUINT_16 oscStabCntTestMode  :1;	// Oscillator Stable Count Test Mode
        } bits;
    } pwrMngmtCntrl;				// RA806: Power Management Control
    
    union
    {
      mUINT_16 all;          
      struct
      {

        mUINT_16     rsvd_b0_b14         :15;
        mUINT_16     PwrDnDetected 		 :1;   // Power Down Detected
      } bits;
   }pwrCntrl0;						// RA808: Power Control 0

    mUINT_16 rsvd;					// RA80A: Reserved
  
    struct
    {
        mUINT_16 TBGnS			:5;			// TBG_A M Frequency Divider
        mUINT_16 rstTBGA		:1;			// TBG_A Disable (0: Enable  1: Powered Down)			
        mUINT_16 disTBGA		:1;			// TBG_A Reset (0: Active  1: Reset)
        mUINT_16 TBGnF			:9;			// TBG_A N Frequency Divider
    } TBGAcontrol;					// RA80C: TBG_A Control Register 

    struct
    {
        mUINT_16 TBGnS			:5;			// TBG_B M Frequency Divider
        mUINT_16 rstTBGB		:1;			// TBG_B Disable (0: Enable  1: Powered Down)
        mUINT_16 disTBGB		:1;			// TBG_B Reset (0: Active  1: Reset)
        mUINT_16 TBGnF			:9;			// TBG_B N Frequency Divider
    } TBGBcontrol;					// RA80E: TBG_B Control Register 


    struct
    {
        mUINT_16 TBGA_ICHP			:3;		// TBG_A Charge Pump Current
        mUINT_16 TBGB_ICHP          :3;		// TBG_B Charge Pump Current
        mUINT_16 TBGActrl           :4;		// TBG_A Test Control
        mUINT_16 TBGBctrl           :4;		// TBG_B Test Control
        mUINT_16 rstTBGBdiv         :1;		// TBG_A Divider Reset
        mUINT_16 rstTBGAdiv         :1;		// TBG_B Divider Reset
    } TBGconfig;					// RA810: TBG Configuration

    struct
    {
        mUINT_16 sscEn				:1;		// TBG_A Spread Spectrum Control
        mUINT_16 puEn         		:1;		// TBG_A Power Up Control for SSC Logic
        mUINT_16 gain				:2;		// TBG_A PLL V to I Gain Control
        mUINT_16 kvco       		:4;		// TBG_A KVCO selection
        mUINT_16 vcoDivSel   		:2;		// TBG_A VCO Divisor Select
        mUINT_16 rsvd_b10_b14   	:5;
        mUINT_16 lock          		:1;		// TBG_A Lock
    } TBGAcontrol1;					// RA812: TBG_A Control 1 
    
    struct
    {
        mUINT_16 sscEn				:1;		// TBG_B Spread Spectrum Control
        mUINT_16 puEn         		:1;		// TBG_B Power Up Control for SSC Logic
        mUINT_16 gain				:2;		// TBG_B PLL V to I Gain Control
        mUINT_16 kvco       		:4;		// TBG_B KVCO selection
        mUINT_16 vcoDivSel   		:2;		// TBG_B VCO Divisor Select
        mUINT_16 rsvd_b10_b14   	:5;
        mUINT_16 lock          		:1;		// TBG_B Lock
    } TBGBcontrol1;					// RA814: TBG_B Control 1         
 

    struct
    {
        mUINT_16 OSC_stable_cnt     :4;		// Oscillator Stable Counter
        mUINT_16 rsvd_b4_b7         :4;
        mUINT_16 PWR_DN_CNT         :8;		// Power Down Counter
    } pwrStatus;					// RA816: Power Status 

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 eccTbgDivSel    :3;	// ECC TBG Divisor Select
            mUINT_16 rsvd_b3         :1;	
            mUINT_16 eccTbgSel       :1;	// ECC TBG Select
            mUINT_16 eccClkDis  	 :1;	// ECC Clock Disable
            mUINT_16 eccClkSel	     :1;	// ECC Clock Select
            mUINT_16 rsvd_b7_b15     :9;	

        } bits;
    } clkDiv2;						// RA818: Clock Divider 2 

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 flaTbgDivSel   :3;		// Flash TBG Divider Select		
            mUINT_16 rsvd_b3        :1;		
            mUINT_16 flaTbgSel      :1;		// Flash TBG Select
            mUINT_16 flaClkDis      :1;		// Flash Clock Disable
            mUINT_16 flaClkSel      :1;		// Flash Clock Select
            mUINT_16 rsvd7          :1;
            mUINT_16 flaClkPreSel   :3;		// Flash Clock Prescaler Select
            mUINT_16 rsvd_b11_b15   :5;
        } bits;
    } clkDiv3;						// RA81A: Clock Divider 3    

    mUINT_16         rsvd1;					// RA81C: Reserved / Clock Divider 4

    mUINT_16         HDCrev			:16;    // RA81E: revision number 
    
} mtCLK_PWR_MNGMNT;

                                   

//=======================================================================
//     [[[[ Host Bus Interface Embedded Serial ATA (SATA) ]]]]
//=======================================================================

typedef struct                                                                                        
{
    mUINT_32     LBA0_31;              // the index of last Q cmd
    mUINT_16     LBA32_47;             // the index of next Q cmd
    union
    {
        mUINT_8  all;
        struct
        {
            mUINT_8  NXQ   : 5;              
            mUINT_8  NXF   : 3;
        }bits;
    } nextLink;
    union                                       // status of the 
    {
        mUINT_8    all;
        struct
        {
            mUINT_8  rsvd  : 3;              
            mUINT_8  type  : 1;    
            mUINT_8  op    : 1;    
            mUINT_8  state : 1;    
            mUINT_8  X     : 1;         
            mUINT_8  A     : 1;         
        } bits;
    } controlbits;    
    mUINT_8          cmd;             
    mUINT_8          device_head;        
    mUINT_16         feature0_15;                    
    mUINT_32         bufOffset;  
          
}mtHBI_QRAM;


typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16 tmFifoParErr    :1;          // 0: TM FIFO Parity Error
        mUINT_16 t10CRCerr       :1;          // 1: T10 CRC error
        mUINT_16 rdHlbaErr       :1;          // 2: HLBA compare Error
        mUINT_16 hCrc1Err        :1;          // 3: Host CRC1 Error
        mUINT_16 qStat           :2;          // 5-4: Queue Status - 00:non-queue, 01:Lagacy, 10:Native, 11:Reserved
        mUINT_16 maxLbaErr       :1;          // 6: Max LBA Error
        mUINT_16 reTxErr         :1;          // 7: Retransmit Error 
        
        mUINT_16 crsbParErr      :1;          // 8: CRSB Parity Error
        mUINT_16 cxsbParErr      :1;          // 9: CXSB Parity Error
        mUINT_16 xmlogsbParErr   :1;          // 10: XMLOGSB Parity Error
        mUINT_16 qramParErr      :1;          // 11: QRAM FIFO Parity Error
        mUINT_16 qTagErr         :1;          // 12: Queue Tag Error Detect
        mUINT_16 qMixErr         :1;          // 13: Queue Mix between Lagacy and Native
        mUINT_16 qMixNQerr       :1;          // 14: Queue Mix with Non-queue Error
        mUINT_16 xferPaused      :1;          // 15: current data xfer paused due to Notified LBA condition
    } bits;
} mtHBI_TM_STATUS_LOW;                        //  offset = 0xA10

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16 rpCrsbParErr    :1;          // 0: Read Port CRSB Parity Error
        mUINT_16 rpCmdHistParErr :1;          // 1: Read Port Command History Parity Error
        mUINT_16 rpQramParErr    :1;          // 2: Read Port QRAM FIFO Parity Error
        mUINT_16 cxsbParErr      :1;          // 3: Read port CXSB Parity Error
        mUINT_16 rpXmlogsbParErr :1;          // 4: Read port XMLOGSB Parity Error
        mUINT_16 rpHfifoParErr   :1;          // 5: Read port Hfifo Parity Error
        mUINT_16 hFIFOunderrun   :1;          // 6: Host FIFO underrurn
        mUINT_16 hFIFOoverrun    :1;          // 7: Host FIFO overrun
        
        mUINT_16 rxFpauseDet     :1;          // 8: RX flow pause detected
        mUINT_16 bmErrDet        :1;          // 9: BM error detected
        mUINT_16 lbgErrDet       :1;          // 10: LBG error detected
        mUINT_16 lbatErrDet      :1;          // 11: LBAT error detected
        mUINT_16 lbrtErrDet      :1;          // 12: LBRT error detected
        mUINT_16 newNcqOpDet     :1;          // 13: new NCQ opcode detected
        mUINT_16 rsvd_b14_b15    :2;
    } bits;
} mtHBI_TM_STATUS_HI;                         //  offset = 0xA12

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16 hardReset              :1;                 //  0: Host Hard Reset
        mUINT_16 softReset              :1;                 //  1: Host Soft Reset
        mUINT_16 cmdAborted             :1;                 //  2: Command Abort
        mUINT_16 newCmd                 :1;                 //  3: New Command Detect
        mUINT_16 cmdExecErr             :1;                 //  4: Command Execution Error
        mUINT_16 cmdProcessErr          :1;                 //  5: Command Process Error
        mUINT_16 cmdRcvdErr             :1;                 //  6: Command Receive Error
        mUINT_16 esataErr               :1;                 //  7: ESATA error (PHY, LINK and Xport)
        
        mUINT_16 xPortInt               :1;                 //  8: Transport Manager Flow Det (R4AB0)
        mUINT_16 msgLogDet              :1;                 //  9: Message Log Detect 
        mUINT_16 fwXferDone             :1;                 // 10: Firmware Data Xfer Done
        mUINT_16 xferDone               :1;                 // 11: Hardware Data Xfer Done
        mUINT_16 nonAceCmd              :1;                 // 12: non Auto Command
        mUINT_16 autoWrCmd              :1;                 // 13: Auto Write command
        mUINT_16 ncqChangedPriority     :1;                 // 14: NCQ changed priority
        mUINT_16 seqCmdDet              :1;                 // 15: sequential command detected
    } bits;
} mtHBI_INT;                                    // R4A14, 4A16

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16 seqWrDmaFuaEn      :1;    //  0: Enable Sequential Write Dma FUA (cmd=0x3d)
        mUINT_16 seqWrDmaEn         :1;    //  1: Enable Sequential Write Dma (cmd=0xca,0x35)
        mUINT_16 seqWrStreamDmaEn   :1;    //  2: Enable Sequential Write Dma Stream (cmd=0x3A)
        mUINT_16 seqWrMultFuaEn     :1;    //  3: Enable Sequential Write Multiple FUA (cmd=0xce)
        mUINT_16 seqWrMultEn        :1;    //  4: Enable Sequential Write Multiple (cmd=0xc5,0x39)
        mUINT_16 seqWrPioEn         :1;    //  5: Enable Sequential Write PIO (cmd=0x30,0x34)
        mUINT_16 seqWrStreamPioEn   :1;    //  6: Enable Sequential Write PIO Stream (cmd=0x3b)
        mUINT_16 seqNcqWrEn         :1;    //  7: Enable Sequential NCQ Write (cmd=0x60)
        
        mUINT_16 seqNcqRdEn         :1;    //  8: Enable Sequential NCQ Read  (cmd=0x61)
        mUINT_16 seqRdDmaEn         :1;    //  9: Enable Sequential Read Dma (cmd=0xc8,0xc9,0x25)
        mUINT_16 seqRdStreamDmaEn   :1;    // 10: Enable Sequential Read Dma Stream (cmd=0x2A)
        mUINT_16 seqRdMultEn        :1;    // 11: Enable Sequential Read Multiple (cmd=0xc4,0x29)
        mUINT_16 seqRdPioEn         :1;    // 12: Enable Sequential Read PIO (cmd=0x20,0x24)
        mUINT_16 seqRdStreamPioEn   :1;    // 13: Enable Sequential Read PIO Stream (cmd=0x2b)
        mUINT_16 rdStreamEn         :1;    // 14: Enable Read Stream ID check
        mUINT_16 wrStreamEn         :1;    // 15: Enable Write Stream ID check
    } bits;
} mtHBI_ACE_CONFIG_1    ;                  // ACE Configuration 1                                  offset = 0xA5C

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16 wrDmaFuaEn         :1;    //  0: ACE Write DMA FUA Enable (cmd=0x3d)
        mUINT_16 wrDmaEn            :1;    //  1: ACE Write DMA Enable (cmd=0xca,0x35)
        mUINT_16 wrDmaStreamEn      :1;    //  2: ACE Write DMA Stream Enable (cmd = 0x3a)
        mUINT_16 wrMultFuaEn        :1;    //  3: ACE Write Multiple FUA Enable (cmd=0xce)
        mUINT_16 wrMultEn           :1;    //  4: ACE Write Multiple Enable (cmd=0xc5,0x39)
        mUINT_16 wrPioEn            :1;    //  5: ACE Write PIO Enable 
        mUINT_16 wrStreamPioEn      :1;    //  6: ACE Write PIO Stream Enable
        mUINT_16 wrSeqLbaMode       :1;    //  7: Write Sequential LBA mode
        
        mUINT_16 seqWrLogEn         :1;    //  8: Sequential Write Log Enable
        mUINT_16 seqWrLogStatus     :1;    //  9: Sequential Write Log Status
        mUINT_16 seqRdLogEn         :1;    // 10: Sequential Read Log Enable
        mUINT_16 seqRdLogStatus     :1;    // 11: Sequential Read Log Status
        mUINT_16 rsvd_b12_b13       :2;    // 12_13:
        mUINT_16 wrBuf              :1;    // 14: write buffer command
        mUINT_16 rsvd_b15           :1;    // 15:
    } bits;
} mtHBI_ACE_CONFIG_2    ;                  // ACE Configuration 2                                  offset = 0xA5E

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16 aceWrXferStopMsgLogEn   :1;  //  0: ACE Write Xfer Stop Message Log Auto Enable
        mUINT_16 aceWrXferStartMsgLogEn  :1;  //  1: ACE Write Xfer Start Message Log Auto Enable
        mUINT_16 seqWrXferStopMsgLogEn   :1;  //  2: Sequential Write Xfer Stop Message Log Auto Enable
        mUINT_16 seqWrXferStartMsgLogEn  :1;  //  3: Sequential Write Xfer Start Message Log Auto Enable
        mUINT_16 seqRdXferStopMsgLogEn   :1;  //  4: Sequential Read Xfer Stop Message Log Auto Enable
        mUINT_16 seqRdXferStartMsgLogEn  :1;  //  5: Sequential Read Xfer Start Message Log Auto Enable
        mUINT_16 wrFuaXferStopMsgLogEn   :1;  //  6: Write FUA Xfer Stop Message Log Auto Enable
        mUINT_16 wrFuaXferStartMsgLogEn  :1;  //  7: Write FUA Xfer Start Message Log Auto Enable
        
        mUINT_16 rsvd_b8_b15             :8;
    } bits;
} mtHBI_MSGLOG_CONFIG;                        // Message Log Configuration                          offset = 0xA60

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16 ncqSeqRdAutoStatEn        :1;    // 0: NCQ Sequential Read Dma Auto Status Enable
        mUINT_16 ncqSeqWrAutoStatEn        :1;    // 1: NCQ Sequential Write Dma Auto Status Enable
        mUINT_16 seqWrStreamDmaAutoStatEn  :1;    // 2: Sequential Write Stream Dma Auto Status Enable
        mUINT_16 seqRdDmaAutoStatEn        :1;    // 3: Sequential Read Dma Auto Status Enable
        mUINT_16 seqRdStreamDmaAutoStatEn  :1;    // 4: Sequential Read Stream Dma Auto Status Enable
        mUINT_16 seqWrDmaAutoStatEn        :1;    // 5: Sequential Write Dma Auto Status Enable
        mUINT_16 seqWrMultAutoStatEn       :1;    // 6: Sequential Write Multiple Auto Status Enable
        mUINT_16 seqWrAutoStatEn           :1;    // 7: Sequential Write Auto Status Enable
        mUINT_16 seqWrStreamAutoStatEn     :1;    // 8: Sequential Write Stream Auto Status Enable
        mUINT_16 rsvd_b9_b10               :2;
        mUINT_16 wbufThresholdChk          :1;    // 11: Write buffer threshold check
        mUINT_16 notifyLbaEn               :1;    // 12: Write buffer threshold check
        mUINT_16 notifyLbaPause            :1;    // 13: Execution SM pauses xfer at the end of the FIS
        mUINT_16 rsvd_b14_b15              :2;
    } bits;
} mtHBI_AUTOSTATUS_CONFIG;                        // Auto Status Configuration                 offset = 0xA62

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16    rsvd       :16;   // Kim - need to expand later
    } bits;
} mtHBI_ACE_OPCODE_0_CONFIG;                        // ACE Opcode 0 Configuration                 offset = 0xA8E

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16    rsvd   :16;             // Kim - need to expand later
    } bits;
} mtHBI_ACE_OPCODE_1_CONFIG;    // ACE Opcode 1 Configuration                                     offset = 0xA90

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16    rsvd   :16;   // Kim - need to expand later
    } bits;
} mtHBI_ACE_OPCODE_2_CONFIG;                        // ACE Opcode 2 Configuration                 offset = 0xA92

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16    rsvd   :16;   // Kim - need to expand later
    } bits;
} mtHBI_ACE_OPCODE_3_CONFIG;                    // ACE Opcode 3 Configuration                      offset = 0xA94

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16 rxCrcErr         : 1; //  0: Receive CRC Error Detect
        mUINT_16 rxRerrFisDet     : 1; //  1: Receive Protocol Error Detect
        mUINT_16 rxFlowErr        : 1; //  2: Receive Flow Error Detect
        mUINT_16 rxLengthErr      : 1; //  3: Receive Length Error Detect
        mUINT_16 txRerrDet        : 1; //  4: Transmit R-ERR Detect
        mUINT_16 txFlowErr        : 1; //  5: Transmit Flow Error Detect
        mUINT_16 rxRerrDataFisDet : 1; //  6: Rerr in Rx Data Fis Detect
        mUINT_16 tmFifoErr        : 1; //  7: Transport Manager FIFO error
        mUINT_16 rxDataSyncDet    : 1; //  8: Receive Data Sync Detect
        mUINT_16 txDataSyncDet    : 1; //  9: Transmit Data Sync Detect
        mUINT_16 txRerrDataFisDet : 1; // 10: Rerr in Tx Data Fis Detect
        mUINT_16 linkCodeErr      : 1; // 11: Link Code Error
        mUINT_16 linkHung         : 1; // 12: Link Hung Detect
        mUINT_16 cmdxhTSsaturated : 1; // 13: CMDXH time stamp saturated (command Execution History)
        mUINT_16 crsbTSsaturated  : 1; // 14: CRSB time stamp saturated  (command receive sequence buffer)
        mUINT_16 phyTimeOut       : 1; // 15: PHY Time Out Detect
    }bits;
} mtHBI_ESATA_ERROR_INT;           // R4AAC

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  disAutoRdSeqDet    : 1; // 0: Disable Auto-Read Sequential  Detect 
        mUINT_16  fuaornewNcqOpDet   : 1; // 1: FUA or new NCQ opcode detected
        mUINT_16  RxFisDet           : 1; // 2: Receive FIS Detect
        mUINT_16  disAutoWrSeqDet    : 1; // 3; Disable Auto-Wrtie Sequential Detect
        mUINT_16  RxBISTfis          : 1; // 4; Receive BIST Detect
        mUINT_16  RxUserFis          : 1; // 5: Receive User-Defined Type Detect
        mUINT_16  xRDYdet            : 1; // 6: X_RDY Detect
        mUINT_16  slumberPMcancel    : 1; // 7: Device Slumber PM cancel Detect
        
        mUINT_16  partialPMcancel    : 1; // 8: Device Partial PM cancel Detect
        mUINT_16  TxFisDone          : 1; // 9: Transmit FIS Done Detect
        mUINT_16  slumberPM          : 1; // 10: Slumber Detect
        mUINT_16  partialPM          : 1; // 11: Partial Power Mode Detect
        mUINT_16  comReset           : 1; // 12: COMRESET Power Mode Detect
        mUINT_16  comWake            : 1; // 13; COMWAKE Power Mode Detect
        mUINT_16  phyRdy             : 1; // 14: PHY Ready Detect
        mUINT_16  phyNotRdy          : 1; // 15: PHY NOT Ready Dectect 
    }bits;
} mtHBI_TM_FLOW_INT;                      // R4AB0

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  errRxFisType       : 8; // Rx FIS Type Error
        mUINT_16  rsvd_b8_b15        : 8;
    }bits;
} mtHBI_TM_RxFIS_ERROR_LOG;         // R4AA4

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  errTxFisType       : 8; // Tx FIS Type Error
        mUINT_16  rsvd_b8_b15        : 8;
    }bits;
} mtHBI_TM_TxFIS_ERROR_LOG;            // R4AA6

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  RxFisType          : 8; // 7:0 - Rx FIS Type
        
        mUINT_16  rsvd_b8_b11        : 4; 
        mUINT_16  RxUtype            : 1; // 12: Receive Unrecognize Type Error
        mUINT_16  rsvd_b13           : 1; 
        mUINT_16  RxForceRErr        : 1; // Receive Force R-ERR up on pausing during Rx flow
        mUINT_16  RxForceROk         : 1; // Receive Force R-OK up on pausing during Rx flow
    }bits;
} mtHBI_TM_RxFIS_LOG;     			      // R4AB4

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  TxFisType          : 8; // Tx FIS Type
        
        mUINT_16  rsvd_b8_b2         : 5; // 
        mUINT_16  RxForceSync        : 1; // 13: Rx Force R_SYNC 
        mUINT_16  rxFisDoneResetEn   : 1; // 14: Rx FIS Done Event (is reset by hardware) Dectect Enable
        mUINT_16  txFisDoneResetEn   : 1; // 15: Tx FIS Done Event (is reset by hardware) Dectect Enable
    }bits;
} mtHBI_TM_TxFIS_LOG;             		  // R4AB6


// R4AB6 - TM_TXFISLOG - TxLinkErrState [12:8]
#define m_tHBI_TM_TxFIS_LOG_TxLinkErrState_COLLISION            0x1000
#define m_tHBI_TM_TxFIS_LOG_TxLinkErrState_DMAT_TO_ABORT        0x0800
#define m_tHBI_TM_TxFIS_LOG_TxLinkErrState_SYNC_TO_ABORT        0x0400
#define m_tHBI_TM_TxFIS_LOG_TxLinkErrState_FIFO_ERROR           0x0200
#define m_tHBI_TM_TxFIS_LOG_TxLinkErrState_R_ERR                0x0100
// R4AB6 - TM_TXFIS_LOG - TxFisType [7:0]
#define m_tHBI_TM_TxFIS_LOG_txFisType_D2H_REG                   0x0007
#define m_tHBI_TM_TxFIS_LOG_txFisType_PIO_DATA                  0x0006
#define m_tHBI_TM_TxFIS_LOG_txFisType_DMA_DATA                  0x0005
#define m_tHBI_TM_TxFIS_LOG_txFisType_DMA_SETUP                 0x0004
#define m_tHBI_TM_TxFIS_LOG_txFisType_SDB                       0x0003
#define m_tHBI_TM_TxFIS_LOG_txFisType_PIO_SETUP                 0x0002
#define m_tHBI_TM_TxFIS_LOG_txFisType_DMA_ACTIVATE              0x0001
#define m_tHBI_TM_TxFIS_LOG_txFisType_IDLE                      0x0000

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  TxFlowRst          : 1; // 0: Tx Flow Reset
        mUINT_16  RxFlowRst          : 1; // 1: Rx Flow Reset
        mUINT_16  linkRst            : 1; // 2: Link Reset
        mUINT_16  phyRst             : 1; // 3: Phy Reset
        mUINT_16  sataBusReq         : 1; // 4: f/w request hw to send x_rdy to request bus manually
        mUINT_16  pwrRdyEn           : 1; // 5: Power Ready Enable with Tx_ComWake_Hold Enable  
        mUINT_16  rsvd_b6            : 1; // 
        mUINT_16  TMsoftRst          : 1; // 7: TM soft reset 
        mUINT_16  rxFlowDis          : 1; // 8: disable rx from sending R_RDY by sending SYNC 
        mUINT_16  cmdExeRst          : 1; // 9: Reset Command Execution SM
        mUINT_16  cmdProcRst         : 1; // 10: Reset Command Processn SM
        mUINT_16  ncqPhaseRst        : 1; // 11: Ncq phase reset 
        mUINT_16  qCntlReset         : 1; // 12: One shot reset to Queue Control logic
        mUINT_16  rxCntlReset        : 1; // 13: One shot reset to Rx Control Logic  
        mUINT_16  lnkSMreset         : 1; // 14: Link State Machine Reset - back to idle 
        mUINT_16  sataBusGranted     : 1; // 15: Sata Bus Granted
    }bits;
} mtHBI_ESATA_FLOW_PWR_RESET_CNTRL;       // R4AB8


typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  fisRTxEn            : 1; // 0: FIS retransmit Enable
        mUINT_16  rsvd_b1             : 1;
        mUINT_16  CDintSel            : 1; // 2: Code violation and Disparity Error Interrupt Select
        mUINT_16  setHBxferActive     : 1; // 3: set HBXFER_ACTIVE
        mUINT_16  manualFisFlowEn     : 1; // 4: Manual Tx/Rx FIS flow enable 
        mUINT_16  rsvd_b5_b6          : 2;
        mUINT_16  pauseEn             : 1; // 7: Pause Enable (on unrecognized type or 2nd error)
        mUINT_16  aggregateSDBEn      : 1; // 8: Aggregate SDB Enable 
        mUINT_16  fDMAactivateDis     : 1; // 9: First DMA Activate FIS Disable
        mUINT_16  rsvd_b10            : 1; 
        mUINT_16  manualFisXferReq    : 1; // 11: Manual FIS transfer request
        mUINT_16  rabVwaitDis         : 1; // 12: RAB Variable Wait Disable
        mUINT_16  ignoreRxdSync       : 1; // 13: ignore host buffer CRC error
        mUINT_16  chsb28En            : 1; 
        mUINT_16  chsbTstmp32bEn      : 1; 
    }bits;
} mtHBI_ESATA_CONFIG;                      // R4ABA

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  reTxCntLimit       : 4; // 3:0 - Retransmit Count Limit
        mUINT_16  rsvd_b4_b7         : 4;  
        
        mUINT_16  h2dCntRst          : 1; // 8: H2D Counters Reset 
        mUINT_16  d2hCntRst          : 1; // 9: D2H Counters Reset 
        mUINT_16  phyRdyCntEn        : 1; // 10: Phy Ready Count Enable
        mUINT_16  sataCntEn          : 1; // 11: Sata Count Enable
        mUINT_16  rsvd_b12_b15       : 4;  
    }bits;
} mtHBI_SATA_MISC_CNTL ;  				 // R4ABC

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  hFifoWrThrehResume : 7; // 6:0 - Host Write FIFO Resume Threshold during Read
        mUINT_16  hFifoWrThrehEn     : 1; // 7: - Host Write FIFO Resume Threshold Enable
        mUINT_16  hFifoRdThrehResume : 7; // 14:6 - Host FIFO Resume Threshold during Read
        mUINT_16  hFifoRdThresEn     : 1; // 15: Host FIFO Read Threshold Enable 
    }bits;
} mtHBI_HFIFO_CONNECT_THRESHOLD;          // R4ABE

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  TxManType          : 8; //  7:0 - manual Tx FIS Type
        mUINT_16  TxManSel           : 1; //    8: Tx Data Source Selection for Manual Tx
        mUINT_16  TxFsize            : 3; // 11:9 - Size of User Defined Reg type FIS
        mUINT_16  rsvd_b12_b15       : 4;  
    }bits;
} mtHBI_TM_MANUAL_FLOW_CNTL ;             // R4AE0




typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  readPtr           : 5; // Read Pointer 
        mUINT_16  rsvd_b5_b7        : 3; 
        
        mUINT_16  writePtr          : 5; // Write Pointer
        mUINT_16  rsvd_b13_b15      : 3;  
    }bits;
} mtHBI_CRSB_PTR ;                       // R4AF6

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  cmdTag             : 5; 
        mUINT_16  nonQflg            : 1;
        mUINT_16  timeStamp          : 10; 
    }bits;
} mtHBI_CRSB_DATA;							// R4AFA


typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  count              : 6; // 5:0 - Read Pointer Lock
        mUINT_16  fullDet            : 1; // 6: crsb Full
        mUINT_16  emptyDet           : 1; // 7: crsb Empty 
        mUINT_16  newIDresume        : 1; // 8: Command Process SM Resume with New CMDID
        mUINT_16  lastIDresume       : 1; // 9: Command Process SM Resume with Last CMDID
        mUINT_16  paused             : 1; // 10: Command Decode SM Paused status 
        mUINT_16  pausedReq          : 1; // 11: Command Decode SM Paused Request 
        mUINT_16  parityDis          : 1; // 12: Crsb Parity Disable
        mUINT_16  rsvd_b13           : 1; 
        mUINT_16  rdWrPtrReset       : 1; // 14: Crsb reset
        mUINT_16  timeStampReset     : 1; // 15: Time Stamp Reset
    }bits;
} mtHBI_CRSB_CNTL_STAT ;   				  // R4AF8


typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  rtxCnt	         : 4; // Retransmit Count Limit
        mUINT_16  rsvd_b4_b7  	     : 4; 
        mUINT_16  h2dCntrReset       : 1; // H2D counter Reset
        mUINT_16  d2hCntrReset       : 1; // D2H counter Reset
        mUINT_16  phyRdyCntEn        : 1; // Phy Ready Counter Enable
        mUINT_16  sataCntEn          : 1; // 
        mUINT_16  rsvd_b12_b15       : 4; 
    }bits;
} mtHBI_ESATA_MISC_CNTL_STAT;  				// R4ABC

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  wptr               : 5; // 4:0 - CRHS write ptr
        mUINT_16  wrapped            : 1; // 5: more than 8 cmds received
        mUINT_16  wrPtrRst           : 1; // 6: write ptr reset
        mUINT_16  timeStampReset     : 1; // 7: Time Stamp Reset
        
        mUINT_16  rsvd_b8_b15        : 8; 
    }bits;
} mtHBI_CRHS_CNTL_STAT;					  // R4AFC

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  readPtr           : 6; // Read Pointer 
        mUINT_16  rsvd_b6_b7        : 2; 
        
        mUINT_16  writePtr          : 6; // Write Pointer
        mUINT_16  rsvd_b14_b15      : 2;  
    }bits;
} mtHBI_CXSB_PTR ; 						 // R4B00

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  count              : 7; // 6:0 - Read Pointer Lock
        mUINT_16  rsvd_b7            : 1; 
        
        mUINT_16  reset              : 1; // 8: Cxsb reset
        mUINT_16  pauseEn            : 1; // 9: Pause Enable
        mUINT_16  fullDet            : 1; // 10: cxsb Full
        mUINT_16  emptyDet           : 1; // 11: cxsb Empty 
        mUINT_16  parityDis          : 1; // 12: Cxsb Parity Disable
        mUINT_16  two16bitWordEntry  : 1; // 13: Cxsb is two 16-bit word entry
        mUINT_16  fwWrHold   	     : 1; // 14: F/W Write Hold Status
        mUINT_16  hoqHold            : 1; // 15: Head Of Queue Hold Status
    }bits;
} mtHBI_CXSB_CNTL_STAT ;     // R4B02

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  cmdTag             : 5; // 4:0 - cmd tag
        mUINT_16  nonQcmd            : 1; //  5: non queue Command 
        mUINT_16  logXferDoneMsgEn   : 1; //  6: Log Xfer Done Message Enable
        mUINT_16  logXferStartMsgEn  : 1; //  7: Log Xfer Start Message Enable
        
        mUINT_16  reqType            : 4; // 11:8 - fw request type
        mUINT_16  bufSegSel          : 3; // 14:12: fw request buffer Segment Select
        mUINT_16  fwReqEocEn         : 1; // 15: fw request Eoc Enable
    }bits;
} mtHBI_CXSB_FW_REQ0 ;                    // R4B04 

#define  m_tHBI_CXSB_FWREQ_DATAXFER     0x0100
#define  m_tHBI_CXSB_FWREQ_EOC          0x0200
#define  m_tHBI_CXSB_FWREQ_MSG          0x0300
#define  m_tHBI_CXSB_FWREQ_ACESEQRD     0x0400
#define  m_tHBI_CXSB_FWREQ_ACESEQWR     0x0500
#define  m_tHBI_CXSB_FWREQ_ACEWR        0x0600
#define  m_tHBI_CXSB_FWREQ_RDVFY        0x0700
#define  m_tHBI_CXSB_FWREQ_AGEOC        0x0800
#define  m_tHBI_CXSB_FWREQ_logXferstartMsgEn 0x0080
#define  m_tHBI_CXSB_FWREQ_logXferDoneMsgEn 0x0040

typedef union           
{
    mUINT_16 all;
    struct
    {
        mUINT_16  sectCnt            : 16; // 15:0 - sector Count
    }bits;
} mtHBI_CXSB_FW_REQ1 ;                     // R4B06 

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  cmdTag             : 5; // 4:0 - cmd tag
        mUINT_16  nonQcmd            : 1; //  5: non queue Command 
        mUINT_16  logXferDoneMsgEn   : 1; //  6: Log Xfer Done Message Enable
        mUINT_16  logXferStartMsgEn  : 1; //  7: Log Xfer Start Message Enable
        
        mUINT_16  reqType            : 4; // 11:8 - fw request type
        mUINT_16  bufSegSel          : 3; // 14:12: fw request buffer Segment Select
        mUINT_16  fwReqEocEn         : 1; // 15: fw request Eoc Enable
    }bits;
} mtHBI_CXSB_HOQ_REQ0 ;                   // R4B08 

typedef union           
{
    mUINT_16 all;
    struct
    {
        mUINT_16  sectCnt            : 16; // 15:0 - sector Count
    }bits;
} mtHBI_CXSB_HOQ_REQ1 ;                   // R4B0A 

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  readPtr           : 6; // Read Pointer 
        mUINT_16  rsvd_b6_b7        : 2; 
        
        mUINT_16  writePtr          : 6; // Write Pointer
        mUINT_16  rsvd_b14_b15      : 2;  
    }bits;
} mtHBI_XMLOGSB_PTR ;                    // R4B48

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  count              : 6; // 5:0 - Read Pointer Lock
        mUINT_16  reset              : 1; // 6: MsgLog reset
        mUINT_16  parityDis          : 1; // 7: msg log Parity Disable
        
        mUINT_16  seqRdWoEoc         : 1; // 8: hw Auto Sequential Read w/o EOC
        mUINT_16  seqWrWoEoc         : 1; // 9: hw Auto Sequential Write w/o EOC
        mUINT_16  hwAutoWr           : 1; // 10: hw Auto Write
        mUINT_16  notifyLba          : 1; // 11: Notify LBA 
        mUINT_16  hwAbortErr         : 1; // 12: Hw Abort Error
        mUINT_16  halfFullDet        : 1; // 13: Half Full
        mUINT_16  fullDet            : 1; // 14: msg Log Full
        mUINT_16  notEmptyDet        : 1; // 15: Msg Log NOT Empty 
    }bits;
} mtHBI_XMLOGSB_CNTL_STAT ;               // R4B4A

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  cmdTag             : 5; // 4:0 Cmd Tag
        mUINT_16  nonQflg            : 1; // 5: nonQ cmd
        mUINT_16  aceType            : 2; // 7:6: Automation type
        
        mUINT_16  msgType            : 4; // 11-8: msg Log Type
        mUINT_16  hwErrMsg           : 4; // 15-12: HW error message
    }bits;
} mtHBI_XMLOGSB_DATA ;                    // R4B4C

typedef union           
{
    mUINT_16 all;
    struct
    {
        mUINT_16  CntLow                : 16; // 15:0 - TimeStamp Clock Counter Low
    }bits;
} mtHBI_TIMSTMP_CNT_LOW;                    // R4B50 

typedef union           
{
    mUINT_16 all;
    struct
    {
        mUINT_16  CntHigh               : 4;  // 3:0 -  TimeStamp Clock Counter High
        mUINT_16  rsvd_b4_b15           : 12; // reserved
    }bits;
} mtHBI_TIMSTMP_CNT_HIGH;                   // R4B52


#define mtHBI_XMLOGSBDATA_HWERRMSG          0xF000
#define mtHBI_XMLOGSBDATA_NOERROR           0x0000
#define mtHBI_XMLOGSBDATA_RXCRCERR          0x1000
#define mtHBI_XMLOGSBDATA_RXPARITYERR       0x2000
#define mtHBI_XMLOGSBDATA_RXT10CRCERR       0x3000
#define mtHBI_XMLOGSBDATA_RXSYNCERR         0x4000
#define mtHBI_XMLOGSBDATA_RXFISSIZEERR      0x5000
#define mtHBI_XMLOGSBDATA_HFIFOCRCERR       0x7000
#define mtHBI_XMLOGSBDATA_TXRERRD2H         0xA000
#define mtHBI_XMLOGSBDATA_TXRERRDATA        0xB000
#define mtHBI_XMLOGSBDATA_TXRERRDMASETUP    0xC000
#define mtHBI_XMLOGSBDATA_TXRERRPIOSETUP    0xD000
#define mtHBI_XMLOGSBDATA_TXRERRSDBSETUP    0xE000
#define mtHBI_XMLOGSBDATA_TXRERRDMAACT      0xF000

#define mtHBI_XMLOGSBDATA_MSGTYPE           0x0F00
#define mtHBI_XMLOGSBDATA_AGGREGATEEOCDONE  0x0000
#define mtHBI_XMLOGSBDATA_EOCINPROCESS      0x0100
#define mtHBI_XMLOGSBDATA_EOCDONE           0x0200
#define mtHBI_XMLOGSBDATA_FWMSG             0x0300
#define mtHBI_XMLOGSBDATA_XFERDONE_NOEOC    0x0400
#define mtHBI_XMLOGSBDATA_XFERDONE_EOC      0x0500
#define mtHBI_XMLOGSBDATA_XFERSTART         0x0600
#define mtHBI_XMLOGSBDATA_NOTIFYLBADET      0x0700
#define mtHBI_XMLOGSBDATA_PARTIALXFERDONE   0x0800
#define mtHBI_XMLOGSBDATA_READVERIFYDONE    0x0C00

#define mtHBI_XMLOGSBDATA_ACETYPE           0x00C0
#define mtHBI_XMLOGSBDATA_ACESEQRD          0x0000
#define mtHBI_XMLOGSBDATA_ACESEQWR          0x0040
#define mtHBI_XMLOGSBDATA_ACEPIOWR          0x0080
#define mtHBI_XMLOGSBDATA_FWREQ             0x00C0

#define mtHBI_XMLOGSBDATA_CMDTAG            0x001F
typedef struct 
{
    mUINT_16   status         :8;            //   ATA Status Register                        //  Offset = 0xA00
    mUINT_16   error          :8;            //   Error Register

    mUINT_16  altStatus       :8;            // Alternate Status                            // offset = 0xA20
    mUINT_16  altError        :8;            // Alternate Error                             

    mUINT_16   sectorNum      :8;            //   Sector Number Register                     //  offset = 0xA04
    mUINT_16   cylLow         :8;            //   Cylinder Low Register

    mUINT_16   cylHigh        :8;            //   Cylinder High Register   
    mUINT_16   devHead        :8;            //   Device/Head Register                       
                                                                    
    union  
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 rsvd_b0        :1;         // 0
            mUINT_16 ienN           :1;         // 1
            mUINT_16 srst           :1;         // 2
            mUINT_16 rsvd_b3_b7     :5;         // 7:3 
			
            mUINT_16 rsvd_b8_b15    :8;         // 15:8 
        } bits;
    } devCntrl;                             //  Device Control Register                         offset = 0xA08


    mUINT_16   sectorCnt      :8;            //  sector count / set features / tag command   //  offset = 0xA0A
    mUINT_16   PAD0           :8;            //   

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 lbaRangeEn      :1;         // 0: LBA Range Check Enable
            mUINT_16 maxLbaRangeChkEn :1;        // 1: Max LBA range Check Enable
            mUINT_16 forceDMAxferEn  :1;         // 2: Force DMA mode xfer Enable
            mUINT_16 extLbaMode      :1;         // 3: Extended LBA mode - set by host 48-bit command
            mUINT_16 hDppEn          :1;         // 4: Host Buffer DPP enable
            mUINT_16 hlbaCrc1En      :1;         // 5: Host LBA write seeded in CRC1 enable
            mUINT_16 hlbaIncEn       :1;         // 6: Host LBA increment at the end of each sector
            mUINT_16 forceCrcErr     :1;         // 7: Force Sata CRC error on read pio/multiple
            
            mUINT_16 hdgT10CrcEn     :1;         // 8: Host Data Guard T10 CRC enable 
            mUINT_16 writeDir        :1;         // 9: Host Direction for vendor Unique cmd
            mUINT_16 forceMultCmd    :1;         // 10: Forced Multiple Command for vendor Unique
            mUINT_16 rsvd_b11        :1;
            mUINT_16 ncqAutoRelDis   :1;         // 12: NCQ Auto Released Disable
            mUINT_16 tcqAutoRelDis   :1;         // 13: TCQ Auto Released Disable
            mUINT_16 overrideHWbsy   :1;         // 14: override HW busy (active low)
            mUINT_16 MppEn           :1;         // 15: MPP enable
        } bits;
    } ATmode0;                                                                              //  offset = 0xA0C 


    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 stopXfer        :1;         // 0: stopXfer
            mUINT_16 clrHbiRst       :1;         // 1: clear TmRst
            mUINT_16 altHintrq       :1;         // 2: alternate Host Interrupt  
            mUINT_16 altHintselq     :1;         // 3: alternate Host Interrupt Select
            mUINT_16 fwEocIbit       :1;         // 4: use for F/W to set I bit
            mUINT_16 rsvd_b5         :1;         // 5: reserved
            mUINT_16 waitDmaEn       :1;         // 6: do not xfer till buffer space = threhold (R4A70)
            mUINT_16 TmRst           :1;         // 7: Transport Manager Reset
            
            mUINT_16 qAbort          :1;         // 8: Queue Abort - queue command block gets reset
            mUINT_16 execResume      :1;         // 9: Current execution resume
            mUINT_16 rawLbaSel       :1;         // 10: upper 28 bit will not be masked
            mUINT_16 rsvd_b11        :1;
            mUINT_16 tfIncEn         :1;         // 12: tf Increment update
            mUINT_16 scntDecEn       :1;         // 13: sector count Dec Enable
            mUINT_16 rsvd_b14        :1;         // 14: reserved
            mUINT_16 updateTF        :1;         // 15: update TaskFile
        } bits;
    } ATdevConfgCntrl;                                                                      //  offset = 0xA0E

    mtHBI_TM_STATUS_LOW     tmStatusLow;                                                        //  offset = 0xA10
    mtHBI_TM_STATUS_HI      tmStatusHi;                                                         //  offset = 0xA12

    mtHBI_INT hostIntMask;               // Host Interrupt Mask Register                         offset = 0xA14
    mtHBI_INT hostIntStat0;              // Host Interrupt Status Register                       offset = 0xA16

    mUINT_16  autoWrThreshold  ;         // Auto Write Threshold                                 offset = 0xA18
    mUINT_16  MdataFisSize     ;         // data FIS size for multiple command                   offset = 0xA1A
    mUINT_16  hostBlkSize     :8;        // Host Block Size Register                             offset = 0xA1C
    mUINT_16  RA1C_PAD3       :8;        //                                                      offset = 0xA1D
    mUINT_16  hostSecPerTrk   :8;        // Host Sector Per Track Register                       offset = 0xA1E
    mUINT_16  hostHdPerCyl    :8;        // Host Heads Per Cylinder Register                     offset = 0xA1F
    mUINT_16  hostSectorErr    ;         // Host Sector Count upon Error                         offset = 0xA20
    mUINT_16  PAD_RA22         ;         //                                                      offset = 0xA22
    mUINT_16  seqSectorNum    :8;        // Sequential Sector Number Register                    offset = 0xA24
    mUINT_16  seqCylLow       :8;        // Sequential Cylinder Low Register                     offset = 0xA25
    mUINT_16  seqCylHigh      :8;        // Sequential Cylinder High Register                    offset = 0xA26
    mUINT_16  seqDevHead      :8;        // Sequential Device/Head Register                      offset = 0xA27

    mUINT_16  PAD_RA28       :16;        //                                                      offset = 0xA28
    mUINT_16  initSectorCnt   :8;        // Initial Sector Count Register                        offset = 0xA2A
    mUINT_16  RA28_PAD7       :8;        //                                                      offset = 0xA2B

    mUINT_16  initSectorNum   :8;        // Initial Sector Number Register                       offset = 0xA2C
    mUINT_16  initCylLow      :8;        // Initial Cylinder Low Register                        offset = 0xA2D
    mUINT_16  initCylHigh     :8;        // Initial Cylinder High Register                       offset = 0xA2E
    mUINT_16  initDevHd       :8;        // Initial Device/Head Register                         offset = 0xA2F
 
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 xferStop        :1;  // Read only - host xfer stop due to an error condition or buffer full
            mUINT_16 xferActive      :1;  // Read/Write - host and buffer data transfer active
            mUINT_16 sRst            :1;  // Software reset - transport manager is in the host Soft reset mode
            mUINT_16 laRrdy          :1;  // Tx flow has won the arbitration to transmit a FIS
            mUINT_16 txFISstate      :4;  // Tx FIS State
            mUINT_16 diagNode2       :4;
            mUINT_16 diagNode1       :4;
        } bits;
    } hostMiscStatus;                     // Host misc status                                     offset = 0xA30
 
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 secCntChkEn     :3;  // 2-0:
            mUINT_16 rsvd_b3         :1;  // 3:
            mUINT_16 expandsecCntChk :3;  // 6-4:
            mUINT_16 rsvd_b7         :1;  // 7:
              
            mUINT_16 deviceChkEn     :4;  // 11-8:
            mUINT_16 rsvd_b12        :1;
            mUINT_16 device5ChkEn    :1;  // 13:
            mUINT_16 rsvd_b14_b15    :2;  
        } bits;
    } aceCntrl;                     // Ace Override Control                                      offset = 0xA32

    mUINT_16  targetLBALow         ;      //                                                     offset = 0xA34
    mUINT_16  targetLBAMid         ;      //                                                     offset = 0xA36
    mUINT_16  targetLBAHi          ;      //                                                     offset = 0xA38
    mUINT_16  FISsize              ;      // Transport Manager Data FIS size                     offset = 0xA3A
    mUINT_16  hostBlkXferCnt1_0    ;     // dflt: 1,                                             offset = 0xA3C
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16  feature0        :8;// dflt: 0,                                             offset = 0xA3E
            mUINT_16  feature1        :8;// dflt: 0,                                             offset = 0xA3F
        } bits;
    }feature1_0;                         
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 lba0    :8;         // dflt: 0,                                             offset = 0xA40
            mUINT_16 lba1    :8;         // dflt: 0,                                             offset = 0xA41
        } bits;
    }lba1_0;                             //                                                      offset = 0xA40
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 lba2    :8;         // dflt: 0,                                             offset = 0xA42
            mUINT_16 lba3    :8;         // dflt: 0,                                             offset = 0xA43
        } bits;
    }lba3_2;                             //                                                      offset = 0xA42
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 lba4    :8;         // dflt: 0,                                             offset = 0xA44
            mUINT_16 lba5    :8;         // dflt: 0,                                             offset = 0xA45
        } bits;
    }lba5_4;                             //                                                      offset = 0xA44
  
    mUINT_16  sectorCnt0_1      ;        //                                                      offset = 0xA46
    mUINT_16  rdSeqLba01        ;        //                                                      offset = 0xA48
    mUINT_16  rdSeqLba23        ;        //                                                      offset = 0xA4A
    mUINT_16  rdSeqLba45        ;        //                                                      offset = 0xA4C
    mUINT_16  PAD_RA4E          ;        //                                                      offset = 0xA4E
   
    mUINT_16  initialLba1_0     ;        //                                                      offset = 0xA50
    mUINT_16  initialLba3_2     ;        //                                                      offset = 0xA52
    mUINT_16  initialLba5_4     ;        //                                                      offset = 0xA54

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16  initialSectCnt0 :8;         //                                             offset = 0xA56
            mUINT_16  initialSectCnt1 :8;         //                                             offset = 0xA57
        } bits;
    }initialSectCnt1_0;                  //                                                      offset = 0xA56

    mUINT_16  cmnd            :16;       //   Command Register                                   offset = 0xA58

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 rdStreamId         :4; 
            mUINT_16 wrStreamId         :4;  
            
            mUINT_16 rsvd_b8_b15        :8;
        } bits;
    } streamIdConf;                       // Stream Id Configuration                              offset = 0xA5A

    mtHBI_ACE_CONFIG_1          aceConfig1      ;    // ACE Configuration 1                      offset = 0xA5C
    mtHBI_ACE_CONFIG_2          aceConfig2      ;    // ACE Configuration 2                      offset = 0xA5E
    mtHBI_MSGLOG_CONFIG         msgLogConfig     ;   // Message Log Configuration                offset = 0xA60
                 
    mtHBI_AUTOSTATUS_CONFIG     autoStatusConfig   ; // Auto Status Configuration                offset = 0xA62

    mUINT_16  wrSeqLba01      ;                                                              // offset = 0xA64
    mUINT_16  wrSeqLba23      ;                                                              // offset = 0xA66
    mUINT_16  wrSeqLba45      ;                                                              // offset = 0xA68
    mUINT_16  wbufThreshold   ;                                                              // offset = 0xA6A

    union
    {
        mUINT_16 all;
        struct
        {       
            mUINT_16     manualSegSel    : 3;      //  2:0
            mUINT_16     rdSeqSegSel     : 3;      //  5:3
            mUINT_16     wrSeqSegSel     : 3;      //  8:6
            mUINT_16     wrDmaSegSel     : 3;      // 11:9
            mUINT_16     wrPioSegSel     : 3;      // 14:12
            mUINT_16     rsvd_b15        : 1;
        } bits;
    } hostBufferSegSel;                            //  offset = 0xA6C

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16  rdPort             :8;                                   
            mUINT_16  mode               :8;                                   
        } bits;
    }eSata_testMux;                                //  offset = 0xA6E  
                      
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16    tmFifoThresh     :4;       // 3:0 - TM FIFO Threshold
            mUINT_16    rsvd_b4_b7       :4;  
            
            mUINT_16    tmFifoWordCnt    :8;       // 15:8 - TM FITO Word Count
        }bits;
    }tmFIFOthreshold;                              //  Transport Manager FIFO threshold                  offset = 0xA70


    union
    {
        mUINT_16 all;
        struct
        {       
            mUINT_16     HFifoWrtPtr     : 7;
            mUINT_16     rsvd_b7         : 1;
            
            mUINT_16     HFifoRdPtr      : 7;
            mUINT_16     rsvd_b15        : 1;
        } bits;
    } tmFifoReadWrite;                  //  Transport Manager FIFO read/write ptr               offset = 0xA72                                                                

    mUINT_16  qExePartialStatLo      ;  // Queue Command Partial Execution Enable Status Low    offset = 0xA74
    mUINT_16  qExePartialStatHi      ;  // Queue Command Partial Execution Enable Status High   offset = 0xA76
    mUINT_16  qExePendStatLo         ;  // Queue Command Pending Execution Enable Status Low    offset = 0xA78
    mUINT_16  qExePendStatHi         ;  // Queue Command Pending Execution Enable Status High   offset = 0xA7a
    mUINT_16  ramTune                ;  //                                                      offset = 0xA7c
 
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 malformFIS         : 1;    // 0: malForm FIS detection disable
            mUINT_16 rxFlowErr          : 1;    // 1: 
            mUINT_16 rxCrcErr           : 1;    // 2:   
            mUINT_16 t10CrcErr          : 1;    // 3: 
            mUINT_16 hostBufferCrcErr   : 1;    // 4: 
            mUINT_16 hFifoQramParErr    : 1;    // 5: 
            mUINT_16 hLbaErr            : 1;    // 6: 
            mUINT_16 cxsbParErr         : 1;    // 7: 
            
            mUINT_16 xmLogParErr        : 1;    // 8: 
            mUINT_16 bmStopErr          : 1;    // 9: 
            mUINT_16 rxLenErr           : 1;    // 10: 
            mUINT_16 reTxErr            : 1;    // 11: Retransmit upon Tx Error detection disable
            mUINT_16 crsbParErr         : 1;    // 12: 
            mUINT_16 t10CrcFlipEn       : 1;    // 13: 
            mUINT_16 forceSync          : 1;    // 14: 
            mUINT_16 dataFisChk         : 1;    // 15: update TaskFile
        } bits;
    } overrideCntl;                             // Override Error Detection Control             offset = 0xA7E

    mUINT_16         qCmdBsyStatLo       ;      // Queue Command Busy Status Low                offset = 0xA80
    mUINT_16         qCmdBsyStatHi       ;      // Queue Command Busy Status High               offset = 0xA82
    mUINT_16         lbaErrorLo          ;      // Lba Error in CRC1, T10 or compare            offset = 0xA84
    mUINT_16         lbaErrorMid         ;      // Lba Error in CRC1, T10 or compare            offset = 0xA86
    mUINT_16         lbaErrorHi          ;      // Lba Error in CRC1, T10 or compare            offset = 0xA88
    mUINT_16         qActiveLo           ;      // Queue Command Active Low                     offset = 0xA8A
    mUINT_16         qActiveHi           ;      // Queue Command Active Hi                      offset = 0xA8C
    mtHBI_ACE_OPCODE_0_CONFIG aceOpcode0Confg;  // ACE Opcode 0 Configuration                   offset = 0xA8E
    mtHBI_ACE_OPCODE_1_CONFIG aceOpcode1Confg;  // ACE Opcode 1 Configuration                   offset = 0xA90
    mtHBI_ACE_OPCODE_2_CONFIG aceOpcode2Confg;  // ACE Opcode 2 Configuration                   offset = 0xA92
    mtHBI_ACE_OPCODE_3_CONFIG aceOpcode3Confg;  // ACE Opcode 3 Configuration                   offset = 0xA94

    mUINT_16         qTagIDlow           ;      // Queue TagID low                              offset = 0xA96                                     
    mUINT_16         qTagIDhi            ;      // Queue TagID Hi                               offset = 0xA98                                    
    mUINT_16         bistPat             ;      // BIST pattern                                 offset = 0xA9A
    mUINT_16         bistWord1Lo         ;      // BIST word 1 Low                              offset = 0xA9C
    mUINT_16         bistWord1Hi         ;      // BIST word 1 Hi                               offset = 0xA9E
    mUINT_16         bistWord2Lo         ;      // BIST word 2 Low                              offset = 0xAA0
    mUINT_16         bistWord2Hi         ;      // BIST word 2 Hi                               offset = 0xAA2
    mtHBI_TM_RxFIS_ERROR_LOG tmRxFISTypeErrLog ;  // Transport Manager Rx FIS type Error Log    offset = 0xAA4 
    mtHBI_TM_TxFIS_ERROR_LOG tmTxFISTypeErrLog ;  // Transport Manager Tx FIS type Error Log    offset = 0xAA6 
    mUINT_16         disparityCnt        ;  // Disparity Count                                  offset = 0xAA8
    mUINT_16         codeErrCnt          ;  // Code Violation Count                             offset = 0xAAA
    mtHBI_ESATA_ERROR_INT eSataErrIntStat;  // ESTAT Error Interrupt Status                 offset = 0xAAC
    mtHBI_ESATA_ERROR_INT eSataErrIntMsk ;  // ESTAT Error Interrupt Mask                   offset = 0xAAE
    mtHBI_TM_FLOW_INT tmFlowIntStatus    ;  // Transport Manager Flow Interrupt Status      offset = 0xAB0
    mtHBI_TM_FLOW_INT tmFlowIntMsk       ;  // Transport Manager Flow Interrupt Mask        offset = 0xAB2
    mtHBI_TM_RxFIS_LOG tmRxFISTypeLog    ;  // Transport Manager Receive FIS type Log       offset = 0xAB4
    mtHBI_TM_TxFIS_LOG tmTxFISTypeLog    ;  // Transport Manager Transmit FIS type Log      offset = 0xAB6
    mtHBI_ESATA_FLOW_PWR_RESET_CNTRL eSataFlowPwrRstCntl;  // ESATA Flow Power Reset Control   offset = 0xAB8
    mtHBI_ESATA_CONFIG eSataConfig       ;     // ESATA Configuration                       offset = 0xABA
    mtHBI_SATA_MISC_CNTL sataMiscCntl    ;  // SATA Misc Cntrol                             offset = 0xABC
    mtHBI_HFIFO_CONNECT_THRESHOLD hFifoConThreshold ; // Host FIFO Connection Threshold     offset = 0xABE
    mUINT_16         uRegFIS0L           ;  // User Defined FIS Word 0 Low                  offset = 0xAC0
    mUINT_16         uRegFIS0H           ;  // User Defined FIS Word 0 High                 offset = 0xAC2
    mUINT_16         uRegFIS1L           ;  // User Defined FIS Word 1 Low                  offset = 0xAC4
    mUINT_16         uRegFIS1H           ;  // User Defined FIS Word 1 High                 offset = 0xAC6
    mUINT_16         uRegFIS2L           ;  // User Defined FIS Word 2 Low                  offset = 0xaC8
    mUINT_16         uRegFIS2H           ;  // User Defined FIS Word 2 High                 offset = 0xACA
    mUINT_16         uRegFIS3L           ;  // User Defined FIS Word 3 Low                  offset = 0xaCC
    mUINT_16         uRegFIS3H           ;  // User Defined FIS Word 3 High                 offset = 0xACE
    mUINT_16         uRegFIS4L           ;  // User Defined FIS Word 4 Low                  offset = 0xAD0
    mUINT_16         uRegFIS4H           ;  // User Defined FIS Word 4 High                 offset = 0xAD2
    mUINT_16         uRegFIS5L           ;  // User Defined FIS Word 5 Low                  offset = 0xAD4
    mUINT_16         uRegFIS5H           ;  // User Defined FIS Word 5 High                 offset = 0xAD6
    mUINT_16         uRegFIS6L           ;  // User Defined FIS Word 6 Low                  offset = 0xAD8
    mUINT_16         uRegFIS6H           ;  // User Defined FIS Word 6 High                 offset = 0xADA
    mUINT_16         uRegFIS7L           ;  // User Defined FIS Word 7 Low                  offset = 0xADC
    mUINT_16         uRegFIS7H           ;  // User Defined FIS Word 7 High                 offset = 0xADE
    mtHBI_TM_MANUAL_FLOW_CNTL tmManualCntl ;   // Transport Manual Control                  offset = 0xAE0
    mUINT_16         PAD_RAE2            ;  //                                              offset = 0xAE2
    mUINT_16         wrMaxLBA1_0         ;  // write maximum LBA1/LBA0                      offset = 0xAE4
    mUINT_16         wrMaxLBA3_2         ;  // write maximum LBA3/LBA2                      offset = 0xAE6
    mUINT_16         wrMaxLBA5_4         ;  // write maximum LBA5/LBA4                      offset = 0xAE8
    mUINT_16         rdMaxLBA1_0         ;  // read maximum LBA1/LBA0                       offset = 0xAEA
    mUINT_16         rdMaxLBA3_2         ;  // read maximum LBA3/LBA2                       offset = 0xAEC
    mUINT_16         rdMaxLBA5_4         ;  // read maximum LBA5/LBA4                       offset = 0xAEE
    mUINT_16         maxLBA1_0           ;  // read maximum LBA1/LBA0                       offset = 0xAF0
    mUINT_16         maxLBA3_2           ;  // read maximum LBA3/LBA2                       offset = 0xAF2
    mUINT_16         maxLBA5_4           ;  // read maximum LBA5/LBA4                       offset = 0xAF4
    mtHBI_CRSB_PTR   crsbPtr             ;  // Command Receive Sequence Buffer Pointer      offset = 0xAF6
    mtHBI_CRSB_CNTL_STAT crsbCntlStat    ;  // Crsb Control and Status                      offset = 0xAF8
    mtHBI_CRSB_DATA  crsbData            ;  // Crsb Data Port / Command ID                  offset = 0xAFA
    mtHBI_CRHS_CNTL_STAT crhsCntl        ;  // Crhs (command history sequence)              offset = 0xAFC
    mUINT_16         PAD_RAFE            ;  //                                              offset = 0xAFE
    mtHBI_CXSB_PTR   cxsbPtr             ;  // Command Execution Sequence Buffer Pointer    offset = 0xB00
    mtHBI_CXSB_CNTL_STAT cxsbCntlStat    ;  // Command Execution Control and Status         offset = 0xB02
    mtHBI_CXSB_FW_REQ0 cxsbFwReq0        ;  // Command Execution Firmware Request 0         offset = 0xB04
    mtHBI_CXSB_FW_REQ1 cxsbFwReq1        ;  // Command Execution Firmware Request 1         offset = 0xB06
    mtHBI_CXSB_HOQ_REQ0 cxsbHOQreq0      ;  // Command Execution Head of Queue Request 0    offset = 0xB08
    mtHBI_CXSB_HOQ_REQ1 cxsbHOQreq1      ;  // Command Execution Head of Queue Request 1    offset = 0xB0A
    mUINT_16         cxsbCurr0           ;  // Command Execution Current 0                  offset = 0xB0C
    mUINT_16         cxsbCurr1           ;  // Command Execution Current 1                  offset = 0xB0E
    mUINT_16         d2hReTxCnt          ;  // D2H retransmit count                         offset = 0xB10
    mUINT_16         d2hRerrCnt          ;  // D2H R_err count                              offset = 0xB12
    mUINT_16         d2hDataCntLo        ;  // D2H Data FIS count low                       offset = 0xB14
    mUINT_16         d2hDataCntHi        ;  // D2H Data FIS count hi                        offset = 0xB16
    mUINT_16         d2hPioCntLo         ;  // D2H PIO FIS count low                        offset = 0xB18
    mUINT_16         d2hPioCntHi         ;  // D2H PIO FIS count hi                         offset = 0xB1A
    mUINT_16         d2hDmaActCntLo      ;  // D2H DMA Activate FIS count low               offset = 0xB1C
    mUINT_16         d2hDmaActCntHi      ;  // D2H DMA Activate FIS count hi                offset = 0xB1E
    mUINT_16         d2hNDCntLo          ;  // D2H Non-Data FIS count low                   offset = 0xB20
    mUINT_16         d2hNDCntHi          ;  // D2H Non-Data FIS count hi                    offset = 0xB22
    mUINT_16         d2hDDWCntLo         ;  // D2H Data Dword FIS count low                 offset = 0xB24
    mUINT_16         d2hDDWCntHi         ;  // D2H Data Dword FIS count hi                  offset = 0xB26
    mUINT_16         d2hNDDWCntLo        ;  // D2H non-Data Dword FIS count low             offset = 0xB28
    mUINT_16         d2hNDDWCntHi        ;  // D2H non-Data Dword FIS count hi              offset = 0xB2A
    mUINT_16         PAD_RB2C;              //                                              offset = 0xB2C
    mUINT_16         d2hDmaSetupCnt      ;  // D2H DMA Setup FIS count low                  offset = 0xB2E
    mUINT_16         h2dNDDisparityCnt   ;  // H2D non-Data FIS Disparity error count       offset = 0xB30
    mUINT_16         h2dNDCrcErrCnt      ;  // H2D non-Data FIS CRC error count             offset = 0xB32
    mUINT_16         h2dDataCrcErrCnt    ;    // H2D Data FIS CRC error count               offset = 0xB34
    mUINT_16         h2dDataDisparityCnt  ; // H2D non-Data FIS Disparity error count       offset = 0xB36
    mUINT_16         h2dDataCntLo         ; // H2D Data FIS count low                       offset = 0xB38
    mUINT_16         h2dDataCntHi         ; // H2D Data FIS count hi                        offset = 0xB3A
    mUINT_16         h2dNonDataFisCntLo   ; // H2D Non-Data FIS count low                   offset = 0xB3C
    mUINT_16         h2dNonDataFisCntHi   ; // H2D Non-Data FIS count hi                    offset = 0xB3E
    mUINT_16         h2dDataDwordCntLo    ; // H2D Data Dword FIS count low                 offset = 0xB40
    mUINT_16         h2dDDWCntHi          ;  // H2D Data Dword FIS count hi                 offset = 0xB42
    mUINT_16         h2dNDDWCntLo         ;  // H2D non-Data Dword FIS count low            offset = 0xB44
    mUINT_16         h2dNDDWCntHi         ;  // H2D non-Data Dword FIS count hi             offset = 0xB46
    mtHBI_XMLOGSB_PTR xmlogsbPtr          ;  // xmlogsb Pointer                             offset = 0xB48
    mtHBI_XMLOGSB_CNTL_STAT xmlogsbCntlStat ;  // xmlogsb Control and Status                offset = 0xB4A
    mtHBI_XMLOGSB_DATA      xmlogsbData   ;  // xmlogsb Data                                offset = 0xB4C
    mUINT_16         PAD_RB4E             ;  //                                             offset = 0xB4E
    mtHBI_TIMSTMP_CNT_LOW  timestampClkCntrLo;  // Timestamp Clock Counter Low              offset = 0xB50
    mtHBI_TIMSTMP_CNT_HIGH timestampClkCntrHi;  // Timestamp Clock Counter High             offset = 0xB52
    mUINT_16         crsbRtimestamp       ;  // Crsb running timestamp                      offset = 0xB54             
    mUINT_16         PAD_RB56             ;  //                                             offset = 0xB56             
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 cmdProcPhase    :4;         // 3-0: Command Process Phase
            mUINT_16 ncqCmdPhase     :4;         // 7-4: NCQ Command Phase 
            mUINT_16 rsvd10_8        :3;         // 10-8: 
            mUINT_16 cmdExePhase     :4;         // 14-11: Command Execution Phase
            mUINT_16 ncqCmdRcvStat   :1;         // 15: NCQ Command Received Status
        } bits;
    } tmPhase;                          // Transport Phase                                  offset = 0xB58
    mUINT_16         hDWxfrCnt            ;  // [12:0] Host DoubleWord Transfer count       offset = 0xB5A
    mUINT_16         PAD_RB5C[2]          ;  //                                             offset = 0xB5C-0xB5E             
    mUINT_16         mistPat1Low          ;  //                                             offset = 0xB60
    mUINT_16         mistPat1Hi           ;  //                                             offset = 0xB62
    mUINT_16         mistPat2Low          ;  //                                             offset = 0xB64
    mUINT_16         mistPat2Hi           ;  //                                             offset = 0xB66
    mUINT_16         mistPat3Low          ;  //                                             offset = 0xB68
    mUINT_16         mistPat3Hi           ;  //                                             offset = 0xB6A
    mUINT_16         mistCntl             ;  // Kim - need to expand                        offset = 0xB6C
    mUINT_16         mistCmdAndType       ;  // Kim - need to expan                         offset = 0xB6E                                     
    mUINT_16         waitDmaBlkCnt        ;  // hw check against before initiating a DMA xfer  offset = 0xB70
    mUINT_16         mistCmdHistTimestamp ;  //                                             offset = 0xB72
    mUINT_16         hFifoDataLo          ;  // Host FIFO Data Port Low                     offset = 0xB74
    mUINT_16         hFifoDataHi          ;  // Host FIFO Data Port Hi                      offset = 0xB76
    mUINT_16         PAD_RB78             ;  //                                             offset = 0xB78
    mUINT_16         hFifoTestPtr         ;  // Host FIFO test Pointer                      offset = 0xB7A
    mUINT_16         PAD_RB7C[1]          ;  //                                             offset = 0xB7C
    mUINT_16         sataRevID            ;  // Sata Revision ID                            offset = 0xB7E
    mUINT_16         rdSeqStartLba01      ;  // Read Sequential Start LBA                   offset = 0xB80
    mUINT_16         rdSeqStartLba23      ;  // Read Sequential Start LBA                   offset = 0xB82
    mUINT_16         rdSeqStartLba45      ;  // Read Sequential Start LBA                   offset = 0xB84
    mUINT_16         latchedStatErr       ;  // Latched AT error/status                     offset = 0xB86
    mUINT_16         rdSeqCmdCntrLow      ;  // Read Sequential Command Counter Low         offset = 0xB88
    mUINT_16         rdSeqCmdCntr1Hi      ;  // Read Sequential Command Counter Hi          offset = 0xB8A                                          
    mUINT_16         rdSeqSectCntrLow     ;  // Read Sequential Sector Counter Low          offset = 0xB8C
    mUINT_16         rdSeqSectCntr1Hi     ;  // Read Sequential Sector Counter Hi           offset = 0xB8E                                          
    mUINT_16         wrSeqStartLba01      ;  // Write Sequential Start LBA                  offset = 0xB90
    mUINT_16         wrSeqStartLba23      ;  // Write Sequential Start LBA                  offset = 0xB92
    mUINT_16         wrSeqStartLba45      ;  // Write Sequential Start LBA                  offset = 0xB94
    mUINT_16         PAD_RB96             ;  // Reserved                                    offset = 0xB96
    mUINT_16         wrSeqCmdCntrLow      ;  // Write Sequential Command Counter Low        offset = 0xB98
    mUINT_16         wrSeqCmdCntr1Hi      ;  // Write Sequential Command Counter Hi         offset = 0xB9A                                         
    mUINT_16         wrSeqSectCntrLow     ;  // Write Sequential Sector Counter Low         offset = 0xB9C
    mUINT_16         wrSeqSectCntr1Hi     ;  // Write Sequential Sector Counter Hi          offset = 0xB9E                                         
    mUINT_16         crsbFifo[32]         ;  // CRSB FIFO                                   offset = 0xBA0 - 0xBDE
    mUINT_16         PAD_RDE0[16]         ;
    mUINT_16         PAD_RC00[64]         ;  //                                             offset = 0xC00 - 0xC7E
    mUINT_16         xmsglogsbFifo[64]    ;  // XMSGLOGSB FIFO                              offset = 0xC80 - 0xCFE
    mUINT_16         chsbFifo[64]         ;  // CHSB FIFO                                   offset = 0xD00 - 0xD7E
    mUINT_16         cxsbFifo[64]         ;  // CXSB FIFO                                   offset = 0xD80 - 0xDFE
    mtHBI_QRAM       QRAMstruct[32]       ;  // Queue RAM                                   offset = 0x4E00 - 0x4ffe
    mUINT_16         seqThreadParams[8]   ;  // Sequential Thread Parameters 0-7            offset = 0x5000 - 0x500E
    mUINT_16         seqMultThreadConfig1 ;  // Kim - need to expand                        offset = 0x5010
    mUINT_16         seqMultThreadConfig2 ;  // Kim - need to expand                        offset = 0x5012
    mUINT_16         PAD_R5014[6]         ;  //                                             offset = 0x5014 - 0x501E
    mUINT_16         bistCntl             ;  // Kim - need to expand                        offset = 0x5020                                                
    mUINT_16         bistStatus0          ;  // Kim - need to expand                        offset = 0x5022
    mUINT_16         bistStatus1          ;  // Kim - need to expand                        offset = 0x5024
    mUINT_16         errInjectCntrMatchLo ;  //                                             offset = 0x5026
    mUINT_16         errInjectCntrMatchHi ;  //                                             offset = 0x5028
    mUINT_16         errInjectCntl        ;    // Kim - need to expand                      offset = 0x502A
    mUINT_16         bufBlkXferCnt        ;  // Buffer Block Xfer Count                     offset = 0x502C
     
}mtHOST_BUS_INTERFACE;        // Host Bus Embedded Serial ATA


//=======================================================================
//     [[[[ Phy-Link Registers ]]]]
//=======================================================================

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  det              : 4; // Phy state and Interface Device Detection
        mUINT_16  Spd              : 4; // Interface Speed (Gen 1/ Gen 2)
        mUINT_16  ipm              : 4; // current Interface Power Management State 
        mUINT_16  rsvd_b12_b15     : 4;
    } bits;
} mtPHYLINK_STATUS_LOW;

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  rsvd_b0          : 1;
        mUINT_16  recComErr        : 1; // Recovered Communication Error 
        mUINT_16  rsvd_b2_b15      : 14; 
    } bits;
} mtPHYLINK_ERROR_LOW;

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  phyRdyChg         : 1; // Phy Ready State change
        mUINT_16  phyInErr          : 1; // Phy internal Error (not supported)
        mUINT_16  comWake           : 1; // ComWake
        mUINT_16  decodeErr         : 1; // 10b to 8b Decode error
        mUINT_16  disparityErr      : 1; // Disparity error
        mUINT_16  crcErr            : 1; // CRC error
        mUINT_16  rErr              : 1; // handshake error (R_ERR received)
        mUINT_16  linkSeqErr        : 1; // Link Sequence error
        mUINT_16  tpStateErr        : 1; // Transport State Transition Error
        mUINT_16  unrecFIS          : 1; // Unrecognize FIS (not supported)
        mUINT_16  xFlag             : 1; // Host presence has changed since last cleared
        mUINT_16  rsvd11            : 1;
        mUINT_16  hostDiscErr       : 1; // Host Disconnect Error
        mUINT_16  rsvd15_13         : 3;
    } bits;
} mtPHYLINK_ERROR_HIGH;

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16  phyStateMode      : 4; // Phy State detection mode
        mUINT_16  speedConfig       : 4; // Speed Negotiation mode
        mUINT_16  pmConfig          : 4; // Power Management mode
        mUINT_16  pmStateSel        : 4; // Power Management State Selection (Partial, Slumber, Active)
    } bits;
} mtPHYLINK_CONTROL_LOW;

typedef union
{
    mUINT_16    all;
    struct
    {
        mUINT_16  txComWakeHold     : 1; //  0: Tx ComWake Hold enable during slumber mode waking up from host

        mUINT_16  rsvd_b1_b3        : 3;
        mUINT_16  fTxCrcErr         : 1; //  4: Force Tx CRC Error
        mUINT_16  syncrecovDis      : 1; //  5: Sync Recovery Disable
        mUINT_16  rsvd_b6           : 1;
        mUINT_16  nearEndLupBack    : 1; //  7:
        mUINT_16  linkStateMode     : 1; //  8: selection of Link SM goes to Idle or not after receiving SYNC 
        mUINT_16  rErrEn            : 1; //  9: either send R_ERR or SYNC if receive other than SOF or X_RDY after sending R_RDY
        mUINT_16  crcMode           : 1; // 10: normal CRC mode or reverse-significant DWORD data to permute CRC
        mUINT_16  crcCheckDis       : 1; // 11: CRC check enable for FIS
        mUINT_16  rxScrbDis         : 1; // 12: Descrambling on receiving data disable
        mUINT_16  txScrbDis         : 1; // Descrambling on transmitting data disable
        mUINT_16  contEn            : 1; // CONT primitive Disable 
        mUINT_16  phyBypass         : 1; // link layer bypass PHYRDY state
    } bits;
} mtPHYLINK_LTMODE_LOW;

typedef union
{
    mUINT_16    all;
    struct
    {
        mUINT_16  oobSyncLock       : 1; //  0: 
        mUINT_16  txDMAsel          : 1; //  1:
        mUINT_16  linkTimer         : 1; //  2:
        mUINT_16  ignoreSrst        : 1; //  3: 
        mUINT_16  rxDMATsel         : 1; //  4: 
        mUINT_16  d10OOBen          : 1; //  5
        mUINT_16  deviceTo          : 1; //  6:
        mUINT_16  pmAckExtEn        : 1; //  7: 
        mUINT_16  txPrimDis         : 1; //  8: 
        mUINT_16  rsvd_b9_b10       : 2; //  9:10
        mUINT_16  speedAdjEn        : 1; // 11: 
        mUINT_16  allignThreshold   : 2; // 12:13
        mUINT_16  commaDetEn        : 1; // 14: 
        mUINT_16  synClockMode      : 1; // 15: Sync Lock Mode
    } bits;
} mtPHYLINK_LTMODE_HIGH;                 // Link mode hi                            offset = 0x580E

typedef struct  // PHY-LINK
{
    mtPHYLINK_STATUS_LOW    sataStatLow     ;    //  SATA STATUS LOw                        offset = 0x5800  
    mUINT_16                sataStatHigh    ;    //  SATA STATUS HIGH                       offset = 0x5802
    mtPHYLINK_ERROR_LOW     sataErrLow      ;    //  SATA ERROR LOW                         offset = 0x5804
    mtPHYLINK_ERROR_HIGH    sataErrHi       ;    //  SATA ERROR HI                          offset = 0x5806
    mtPHYLINK_CONTROL_LOW   sataCntlLow     ;    //                                         offset = 0x5808
    mUINT_16                sataCntlHi      ;    //                                         offset = 0x580A
    mtPHYLINK_LTMODE_LOW    ltModeLo;            // Link mode low                           offset = 0x580C
    mtPHYLINK_LTMODE_HIGH   ltModeHi;            // Link mode hi                            offset = 0x580E
    mUINT_16                PAD_R5810[7];        //                                         offset = 0x5810-0x581C
    mUINT_16                phyLinkTestCntl ;    //                                         offset = 0x581E
    mUINT_16                oobConf1Lo      ;    // Phy mode 5 low                          offset = 0x5820
    mUINT_16                oobConf1Hi      ;    // Phy mode 5 hi                           offset = 0x5822
    mUINT_16                oobConf2Lo      ;    // Phy mode 6 low                          offset = 0x5824
    mUINT_16                oobConf2Hi      ;    // Phy mode 6 hi                           offset = 0x5826
    mUINT_16                oobConf3Lo      ;    // Phy mode 6 low                          offset = 0x5828
    mUINT_16                oobConf3Hi      ;    // Phy mode 6 hi                           offset = 0x582A
    mUINT_16                oobConf4        ;    // Phy mode 6 low                          offset = 0x582C
    mUINT_16                PAD_R582E       ;    //                                         offset = 0x582E
    mUINT_16                phyConfLo       ;    // Phy mode 4                              offset = 0x5830
    mUINT_16                phyConfHi       ;    // Phy mode 4                              offset = 0x5832
    mUINT_16                idleCnt         ;    //                                         offset = 0x5834
    mUINT_16                powerCntl       ;    //                                         offset = 0x5836
    mUINT_16                autoP2S			;    //                                         offset = 0x5838 
    mUINT_16                alignThr        ;    //                                         offset = 0x583A
    mUINT_16                PAD_R583C[1]    ;    //                                         offset = 0x583C
    mUINT_16                phySMconfig0    ;    //                                         offset = 0x583E

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 BISTtestCFG    :8;     //  host transfer stop-set when xpr_active is set and buffer conditions related.
            mUINT_16 BISTmode       :1;
            mUINT_16 BISTen         :1;
            mUINT_16 BISTresult     :1;
            mUINT_16 rsvd_b11       :1;     // Kim - need to expand here!
            mUINT_16 rsvd_b12       :1;     // Kim - need to expand here!
            mUINT_16 rsvd_b13_b15   :3;     // Kim - need to expand here!
        } bits;
    } testCntlLo;                           // Phy-link test control low - 0x5840
    
    // !!! ATTENTION !!!!
    // BIG CHANGE BELOW;
    // 5842, 5860, 5862, 586C, 586E, 5870 redefined from 89X5 to 90X5 
    // every other reg from 5844 thru 58AE present on 89X5 was removed on 90X5
    // the balance of the new 65nm PHY was added from 5900 to 59F4
    // !!! ATTENTION !!!!
    
    mUINT_16                newtestCntlHi       ; // Phy-link test control high;    offset = 0x5842  ==> redefined from 89X5
    mUINT_16                PAD_R5844[14]       ; //                                offset = 0x5844 - 0x585e 
    mUINT_16                newPhyMode1Lo       ; // Phy Mode 1 Low                 offset = 0x5860
    mUINT_16                newPhyMode1Hi       ; // Phy Mode 1 Hi                  offset = 0x5862
    mUINT_16                PAD_R5864[4]        ; //                                offset = 0x5864 - 0x586A 
    mUINT_16                newPhyMode4Lo       ; //                                offset = 0x586C
    mUINT_16                newPhyMode4Hi       ; //                                offset = 0x586E
    mUINT_16                newPhyTestCntl      ; //                                offset = 0x5870
    mUINT_16                PAD_R5872[71]       ; //                                offset = 0x5872 - 0x58FE
    
    mUINT_16                PhyRevision         ; //                                offset = 0x5900
    mUINT_16                PAD_R5902[1]        ; //                                offset = 0x5902
    mUINT_16                PllRate             ; //                                offset = 0x5904
    mUINT_16                PhySpeedCntl        ; //                                offset = 0x5906
    mUINT_16                PAD_R5908[3]        ; //                                offset = 0x5908 - 0x590C
    mUINT_16                PllBWAdjust         ; //                                offset = 0x590E
    mUINT_16                PAD_R5910[1]        ; //                                offset = 0x5910
    mUINT_16                CalCntl             ; //                                offset = 0x5912
    mUINT_16                ImpCal              ; //                                offset = 0x5914
    mUINT_16                ImpCntl             ; //                                offset = 0x5916
    mUINT_16                DccKvcoCntl         ; //                                offset = 0x5918
    mUINT_16                PAD_R591A[7]        ; //                                offset = 0x591A - 0x5926
    mUINT_16                PreDeEmphasisEn     ; //                                offset = 0x5928
    mUINT_16                AmpEmphCntl         ; //                                offset = 0x592A
    mUINT_16                SlewRateSelect      ; //                                offset = 0x592C
    mUINT_16                PAD_R592E[1]        ; //                                offset = 0x592E
    mUINT_16                SSCCntl             ; //                                offset = 0x5930
    mUINT_16                PAD_R5932[5]        ; //                                offset = 0x5932 - 0x593A
    mUINT_16                SqDetThrSetting     ; //                                offset = 0x593C
    mUINT_16                CdrInitCoeffVal     ; //                                offset = 0x593E
    mUINT_16                DtlSqPhLoopCntl     ; //                                offset = 0x5940
    mUINT_16                PAD_R5942[2]        ; //                                offset = 0x5942 - 0x5944
    mUINT_16                FFeRCCntl           ; //                                offset = 0x5946
    mUINT_16                PAD_R5948[1]        ; //                                offset = 0x5948
    mUINT_16                DFeCoeffResCntl     ; //                                offset = 0x594A
    mUINT_16                DFeF0F1CoeffCntl    ; //                                offset = 0x594C
    mUINT_16                DFeF2F5CoeffCntl    ; //                                offset = 0x594E
    mUINT_16                DFeMisc0            ; //                                offset = 0x5950
    mUINT_16                PAD_R5952[2]        ; //                                offset = 0x5952 - 0x5954
    mUINT_16                DFeCoeffCntl        ; //                                offset = 0x5956
    mUINT_16                PAD_R5958[2]        ; //                                offset = 0x5958 - 0x595A
    mUINT_16                DFeTimer            ; //                                offset = 0x595C
    mUINT_16                PAD_R595E[2]        ; //                                offset = 0x595E - 0x5960
    mUINT_16                EOMCktCntl          ; //                                offset = 0x5962
    mUINT_16                EOMSet1Cntl0        ; //                                offset = 0x5964
    mUINT_16                EOMSet1Cntl1        ; //                                offset = 0x5966
    mUINT_16                EOMSet1PopCnt[4]    ; //                                offset = 0x5968 - 0x596E
    mUINT_16                EOMSet1ThrCnt[4]    ; //                                offset = 0x5970 - 0x5976
    mUINT_16                EOMSet1SmpCnt[4]    ; //                                offset = 0x5978 - 0x597E
    mUINT_16                EOMSet1ErrCnt[4]    ; //                                offset = 0x5980 - 0x5986
    mUINT_16                EOMSet2Cntl0        ; //                                offset = 0x5988
    mUINT_16                EOMSet2Cntl1        ; //                                offset = 0x598A
    mUINT_16                EOMSet2PopCnt[4]    ; //                                offset = 0x598C - 0x5992
    mUINT_16                EOMSet2ThrCnt[4]    ; //                                offset = 0x5994 - 0x599A
    mUINT_16                G1Setting0          ; //                                offset = 0x599C
    mUINT_16                G1Setting1          ; //                                offset = 0x599E
    mUINT_16                G2Setting0          ; //                                offset = 0x59A0
    mUINT_16                G2Setting1          ; //                                offset = 0x59A2
    mUINT_16                G3Setting0          ; //                                offset = 0x59A4
    mUINT_16                G3Setting1          ; //                                offset = 0x59A6
    mUINT_16                PAD_R59A8[2]        ; //                                offset = 0x59A8 - 0x59AA
    mUINT_16                ConfigReg0          ; //                                offset = 0x59AC
    mUINT_16                PAD_R59AE[1]        ; //                                offset = 0x59AE
    mUINT_16                PllRegOutputCntl0   ; //                                offset = 0x59B0
    mUINT_16                PAD_R59B2[1]        ; //                                offset = 0x59B2
    mUINT_16                PowerCntlReg        ; //                                offset = 0x59B4
    mUINT_16                ResetCntl           ; //                                offset = 0x59B6
    mUINT_16                PAD_R59B8[2]        ; //                                offset = 0x59B8 - 0x59BA
    mUINT_16                PhyTestCntl0        ; //                                offset = 0x59BC
    mUINT_16                PhyTestCntl1        ; //                                offset = 0x59BE
    mUINT_16                PhyTestData[6]      ; //                                offset = 0x59C0 - 0x59CA
    mUINT_16                PhyTestPrbsCnt[3]   ; //                                offset = 0x59CC - 0x59D0
    mUINT_16                PhyTestPrbsErrCnt[2] ; //                                offset = 0x59D2 - 0x59D4
    mUINT_16                PAD_R59D6[3]        ; //                                offset = 0x59D6 - 0x59DA
    mUINT_16                DigitalLoopbackEn   ; //                                offset = 0x59DC
    mUINT_16                PAD_R59DE[1]        ; //                                offset = 0x59DE
    mUINT_16                Misc1               ; //                                offset = 0x59F0
    mUINT_16                SyncPat             ; //                                offset = 0x59F2
    mUINT_16                SyncMask            ; //                                offset = 0x59F4
    mUINT_16                PAD_R59F6[5]        ; //                                offset = 0x59F6 - 0x59FE
    
} mtPHYLINK_INTERFACE;



//#SYMGEN_OMIT


                                 
                                   
// Error Register Equates          
#define     mIF_CRC_ERR      mBIT(7)
#define     mUNCOR_DATA_ERR  mBIT(6)
#define     mID_NOT_FOUND    mBIT(5)
#define     mABORTED_CMND    mBIT(2)
#define     mTRK0_NOT_FOUND  mBIT(1)
#define     mAM_NOT_FOUND    mBIT(0)




// ATA Status Register
#define     mBSY             mBIT(7)
#define     mDEV_RDY         mBIT(6)
#define     mDEV_FAULT       mBIT(5)
#define     mDEV_SK_CMPLT    mBIT(4)
#define     mDRQ             mBIT(3)
#define     mCORR_DATA_ERR   mBIT(2)
#define     mTRK_INDEX       mBIT(1)
#define     mINTR            mBIT(1)
#define     mERR             mBIT(0)

// SATA FIS TYPE
#define     mH2D_FIS            0x27
#define     mD2H_FIS            0x34
#define     mDMAACTIVATE_FIS    0x39
#define     mDMASETUP_FIS       0x41
#define     mDATA_FIS           0x46
#define     mBIST_FIS           0x58
#define     mPIOSETUP_FIS       0x5F
#define     mSDB_FIS            0xA1   // Set Device Bits


//#SYMGEN_OMIT_END


//=======================================================================
//     [[[[ Buffer Manager (BM) ]]]]
//=======================================================================
#define m_tBM_CNTRL_REG1_bits_CrcSegMode      		0x0100
#define m_tBM_CNTRL_REG1_bits_diskBurstLenSel64		0x0028
#define m_tBM_CNTRL_REG1_bits_diskBurstLenSel48		0x0020
#define m_tBM_CNTRL_REG1_bits_diskBurstLenSel32		0x0018
#define m_tBM_CNTRL_REG1_bits_diskBurstLenSel24		0x0010
#define m_tBM_CNTRL_REG1_bits_diskBurstLenSel16		0x0008
#define m_tBM_CNTRL_REG1_bits_diskBurstLenSel8		0x0000
#define m_tBM_CNTRL_REG1_bits_hostBurstLenSel64		0x0005
#define m_tBM_CNTRL_REG1_bits_hostBurstLenSel48		0x0004
#define m_tBM_CNTRL_REG1_bits_hostBurstLenSel32		0x0003
#define m_tBM_CNTRL_REG1_bits_hostBurstLenSel24		0x0002
#define m_tBM_CNTRL_REG1_bits_hostBurstLenSel16		0x0001
#define m_tBM_CNTRL_REG1_bits_hostBurstLenSel8		0x0000


typedef  union                  // Buffer Manager Control Register1 
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 hostBurstLenSel    : 3;
        mUINT_16 diskBurstLenSel    : 3;
        mUINT_16 rsvd_b6            : 1;
        mUINT_16 bmDPDPen           : 1;    

        mUINT_16 CrcSegMode         : 1;
        mUINT_16 intModeSel         : 1;    
        mUINT_16 rsvd11_10          : 2;
        mUINT_16 DRAMstart          : 1;
        mUINT_16 DRAMPwrDownStart   : 1;
        mUINT_16 rsvd_b15_14        : 2;
    }bits;
}mtBM_CNTRL_REG1;               


typedef  union                  // Buffer Manager Control 0 Register 
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 rsvd_b0            : 1;
        mUINT_16 diskByteCntrRst    : 1;
        mUINT_16 rsvd_b2_3          : 2;
        mUINT_16 sdramWpEn          : 1;
        mUINT_16 forceOdtEn         : 1;
        mUINT_16 diskMatchStopEn    : 1;
        mUINT_16 hostMatchStopEn    : 1;

        mUINT_16 ssdParityEn        : 1;
        mUINT_16 ssdWpEn            : 1;
        mUINT_16 rsvd_b10_11        : 2;
        mUINT_16 extBurstLenSel     : 3;
        mUINT_16 rsvd_b15           : 1;
    }bits;
}mtBM_CNTRL_REG0;               


typedef  union                  // Buffer Manager Round Robin Control 0
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 slotClientSel0     : 3;
        mUINT_16 slotClientSel1     : 3;
        mUINT_16 slotClientSel2     : 3;
        mUINT_16 slotClientSel3     : 3;
        mUINT_16 slotClientSel4     : 3;
        mUINT_16 rsvd_b15           : 1;
    }bits;
}mtBM_RR_CNTRL0;               


typedef  union
{
    mUINT_16 all;
    struct                      // Buffer Manager Round Robin Control 1
    {
        mUINT_16 slotClientSel5     : 3;
        mUINT_16 slotClientSel6     : 3;
        mUINT_16 slotClientSel7     : 3;
        mUINT_16 slotClientSel8     : 3;
        mUINT_16 rsvd_b9_15         : 4;
    }bits;
}mtBM_RR_CNTRL1;                


typedef  union                  // Buffer Manager Shared 2 Slot Control.
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 s2_priority0       : 3;
        mUINT_16 s2_priority1       : 3;
        mUINT_16 s2_priority2       : 3;
        mUINT_16 s2_priority3       : 3;
        mUINT_16 s2_priority4       : 3;
        mUINT_16 rsvd_b15           : 1;
    }bits;
}mtBM_SHARED_2_SLOT_CNTRL;      


typedef  union                  // Buffer Manager Shared 2 Slot Control.
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 s1_priority0       : 3;
        mUINT_16 s1_priority1       : 3;
        mUINT_16 s1_priority2       : 3;
        mUINT_16 s1_priority3       : 3;
        mUINT_16 s1_priority4       : 3;
        mUINT_16 rsvd_b15           : 1;
    }bits;
}mtBM_SHARED_1_SLOT_CNTRL;      


typedef  union                  // Buffer Manager Shared 1 Slot Control.

{
    mUINT_16 all;
    struct 
    {
        mUINT_16 s3_priority0       : 3;
        mUINT_16 s3_priority1       : 3;
        mUINT_16 s3_priority2       : 3;
        mUINT_16 s3_priority3       : 3;
        mUINT_16 s3_priority4       : 3;
        mUINT_16 rsvd_b15           : 1;
    }bits;
}mtBM_SHARED_3_SLOT_CNTRL;      


typedef  union                  // Buffer Manager Round Robin Slot Mask
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 rrSlotMask0        : 1;
        mUINT_16 rrSlotMask1        : 1;
        mUINT_16 rrSlotMask2        : 1;
        mUINT_16 rrSlotMask3        : 1;
        mUINT_16 rrSlotMask4        : 1;
        mUINT_16 rrSlotMask5        : 1;
        mUINT_16 rrSlotMask6        : 1;
        mUINT_16 rrSlotMask7        : 1;
        
        mUINT_16 rrSlotMask8        : 1;
        mUINT_16 rsvd_b9_15         : 7;
    }bits;
}mtBM_RR_SLOT_MASK;             


typedef union                   // Buffer Manager Status 0 Register 
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 hostBfrEmpty       : 1;
        mUINT_16 hostBfrFull        : 1;
        mUINT_16 rsvd_b0_2          : 1;
        mUINT_16 extToWp            : 1;
        mUINT_16 hostToWp           : 1;
        mUINT_16 diskToWp           : 1;
        mUINT_16 rsvd_b6            : 1;
        mUINT_16 mpuToWp            : 1;

        mUINT_16 hostSsdParErr      : 1;
        mUINT_16 diskSsdParErr      : 1;
        mUINT_16 rsvd_b11_10        : 2;
        mUINT_16 diskSegEmpty       : 1;
        mUINT_16 diskSegFull        : 1;
        mUINT_16 curHSegEmpty       : 1;
        mUINT_16 curHSegFull        : 1;
    }bits;
}mtBM_STAT0;                    


typedef union                   // Buffer Manager Status 1 Register 
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 HLL0matched        : 1;    //  Match expect.
        mUINT_16 HLL1matched        : 1;    //  Match expect.
        mUINT_16 HLL2matched        : 1;    //  Match expect.
        mUINT_16 HLL3matched        : 1;    //  Match expect.
                                       
        mUINT_16 HLL4matched        : 1;    //  Match expect.
        mUINT_16 HLL5matched        : 1;    //  Match expect.
        mUINT_16 HLL6matched        : 1;    //  Match expect.
        mUINT_16 HLL7matched        : 1;    //  Match expect.

        mUINT_16 DLL0matched        : 1;    //  Match expect.
        mUINT_16 DLL1matched        : 1;    //  Match expect.
        mUINT_16 DLL2matched        : 1;    //  Match expect.
        mUINT_16 DLL3matched        : 1;    //  Match expect.

        mUINT_16 rsvd_b12           : 1;
        mUINT_16 ELLmatchStop       : 1;    //  Match stop.
        mUINT_16 HLLmatchStop       : 1;    //  Match stop.
        mUINT_16 DLLmatchStop       : 1;    //  Match stop.
    }bits;
}mtBM_STAT1;                    


typedef union                   // Buffer Manager Status 2 Register 
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 ddrLock_L0         : 1;
        mUINT_16 ddrLock_L1         : 1;
        mUINT_16 ddrInitDone        : 1;
        
        mUINT_16 rsvd_b3_14         : 12;
        mUINT_16 dramRdy            : 1;
    } bits;
}mtBM_STAT2;                    


typedef union                   // Buffer Manager Status 3 Register 
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 es0LLmatch         : 1;
        mUINT_16 es1LLmatch         : 1;
        mUINT_16 es2LLmatch         : 1;
        mUINT_16 es3LLmatch         : 1;
        mUINT_16 rsvd_b4_7          : 4; 
        
        mUINT_16 extSsdParErr       : 1;
        mUINT_16 rsvd_b9_11         : 3; 
        mUINT_16 extSegEmpty        : 1;
        mUINT_16 rsvd_b13_14        : 2;
        mUINT_16 extSegFull         : 1;
        
    } bits;
}mtBM_STAT3;                    


typedef union
{                               // Buffer Manager DRAM Control Register 1, 0x2E20
    mUINT_16 all;
    struct 
    {
        mUINT_16 tWrSel             : 3;
        mUINT_16 refreshModeSel     : 1;
        mUINT_16 tRPSel             : 3;
        mUINT_16 multiRowDis        : 1;
        mUINT_16 memSize            : 3;
        mUINT_16 ckeCtl             : 2;
        mUINT_16 dblDdrEn           : 1;
        mUINT_16 rsvd_b14           : 1;
        mUINT_16 ddr3En             : 1;
    } bits;
} mtBM_DRAM_CNTRL_REG1;         


typedef union                   // Buffer Manager DRAM Control Register 0
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 tRFC               : 6;
        mUINT_16 otfZQ              : 1;
        mUINT_16 tWtrSel            : 2;
        mUINT_16 rsvd_b9_10         : 2;
        mUINT_16 tRasSel            : 4;
        mUINT_16 dramReset          : 1;
    } bits;
} mtBM_DRAM_CNTRL_REG0;         


typedef  union                  // Refresh Period Register 
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 value              : 13;
        mUINT_16 rsvd_b13_15        : 3;
    }bits;
}mtBM_REF_PRD;                 


typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 rsvd_b0_2          : 3;
        mUINT_16 cwl                : 3;
        mUINT_16 sdramExt2mode      : 9;
        mUINT_16 emr2WrEn           : 1;
    } bits;
} mtBM_DRAM_EXT_MODE2;          // Buffer Manager DRAM Extended Mode 2


typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 sdramExtMode3Regs  : 15;
        mUINT_16 emr3WrEn           : 1;
    } bits;
} mtBM_DRAM_EXT_MODE;           // Buffer Manager DRAM Extended Mode 2

typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 burstLen           : 3;
        mUINT_16 burstType          : 1;
        mUINT_16 cas_ltncy          : 3;
        mUINT_16 rsvd_b7            : 1;
        mUINT_16 dramDllRst         : 1;
        mUINT_16 ddrWrRecovery      : 3;
        mUINT_16 dllCtrlPpd         : 1;
        mUINT_16 rsvd_b13_14        : 2;
        mUINT_16 modeWrEn           : 1;
    } bits;
} mtBM_DRAM_MODE_CNTL;          // Buffer Manager DRAM Mode Control



typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 dllEn              : 1;
        mUINT_16 dicSel             : 1;
        mUINT_16 odtB0              : 1;
        mUINT_16 addLtncy           : 3;
        mUINT_16 odtB1              : 1;
        mUINT_16 ocdMode            : 3;
        mUINT_16 dqsEn              : 1;
        mUINT_16 rdqsEn             : 1;
        mUINT_16 rsvd_b12_14        : 3;
        mUINT_16 emr1WrEn           : 1;
    } bits;
} mtBM_DRAM_EXT_MODE1;          // Buffer Manager DRAM Extended Mode 1  for DDR2


typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 dll0PhaseDly       : 5;
        mUINT_16 rsvd_b5_b6         : 2;
        mUINT_16 dll0Reset          : 1;
        
        mUINT_16 dll0PhaseByp       : 5;
        mUINT_16 dll0UpdateEn       : 1;
        mUINT_16 dll0AutoUpdate     : 1;
        mUINT_16 dll0BypassEn       : 1;
    } bits;
} mtBM_DDR_PHY0;           // Buffer Manager DDR PHY DLL0 Control R2EA0h


typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 dll1PhaseDly       : 5;
        mUINT_16 rsvd_b5_b6         : 2;
        mUINT_16 dll1Reset          : 1;
        
        mUINT_16 dll1PhaseByp       : 5;
        mUINT_16 dll1UpdateEn       : 1;
        mUINT_16 dll1AutoUpdate     : 1;
        mUINT_16 dll1BypassEn       : 1;
    } bits;
} mtBM_DDR_PHY1;           // Buffer Manager DDR PHY DLL1 Control R2EA2h


typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 dqRcvP             : 3;
        mUINT_16 dqRcvN             : 3;
        mUINT_16 qsRcvType          : 1;
        mUINT_16 dqRcvType          : 1;
        
        mUINT_16 dqMode             : 1;
        mUINT_16 qsDelay            : 3;
        mUINT_16 dqDelay            : 3;
        mUINT_16 rsvd_b15           : 1;
    } bits;
} mtBM_DDR_PHY_DQ_PAD_CTL0;     // Buffer Manager DDR_ PHY DQ PAD Control0  R2EB0h


typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 dqPmosDrvF         : 4;
        mUINT_16 dqNmosDrvF         : 4;
        
        mUINT_16 qsReference        : 2;
        mUINT_16 dqReference        : 2;
        mUINT_16 dqZd               : 1;
        mUINT_16 qsPd               : 1;
        mUINT_16 dqPd               : 1;
        mUINT_16 dqFtermEn          : 1;
    } bits;
} mtBM_DDR_PHY_DQ_PAD_CTL1;     // Buffer Manager DDR_ PHY DQ PAD Control1  R2EB2h


typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 dqPmosZ            : 4;
        mUINT_16 dqNmosZ            : 4;
        mUINT_16 dqPmosDrvC         : 4;
        mUINT_16 dqNmosDrvC         : 4;
    } bits;
} mtBM_DDR_PHY_DQ_PAD_CTL2;     // Buffer Manager DDR_ PHY DQ PAD Control2  R2EB4h


typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 ckPmosDrv          : 4;
        mUINT_16 ckNmosDrv          : 4;
        
        mUINT_16 ckDelay            : 3;
        mUINT_16 rsvd_bit11         : 1;
        mUINT_16 ckPd               : 1;
        mUINT_16 ckZd               : 1;
        mUINT_16 ckRecEn            : 1;
        mUINT_16 ckOutEn            : 1;
    } bits;
} mtBM_DDR_PHY_CLK_PAD;    // Buffer Manager DDR_ PHY CLOCK PAD Control  R2EB6h


typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 adcmRcvP           : 3;
        mUINT_16 adcmRcvN           : 3;
        mUINT_16 adcmRcvType        : 1;
        mUINT_16 adcmMode           : 1;
        
        mUINT_16 adcmDelay          : 3;
        mUINT_16 adcmRecEn          : 1;
        mUINT_16 adcmOutEn          : 1;
        mUINT_16 rsvd_b13_b15       : 3;
    } bits;
} mtBM_DDR_PHY_ADCM_PAD_CTL0;    // Buffer Manager DDR_ PHY ADCM PAD Control0  R2EB8h


typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 adcmPmosDrvF       : 4;
        mUINT_16 adcmNmosDrvF       : 4;
        
        mUINT_16 adcmReference      : 2;
        mUINT_16 rsvd_b10_b11       : 2;
        mUINT_16 adcmZd             : 1;
        mUINT_16 adcmPd             : 1;
        mUINT_16 rsvd_b14_b15       : 2;
    } bits;
} mtBM_DDR_PHY_ADCM_PAD_CTL1;   // Buffer Manager DDR_ PHY ADCM PAD Control1  R2EBAh


typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 adcmPmosZ          : 4;
        mUINT_16 adcmNmosZ          : 4;
        
        mUINT_16 adcmPmosDrvC       : 4;
        mUINT_16 adcmNmosDrvC       : 4;
    } bits;
} mtBM_DDR_PHY_ADCM_PAD_CTL2;    // Buffer Manager DDR_ PHY ADCM PAD Control2  R2EBCh


typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 calPmosDrv         : 4;
        mUINT_16 calNmosDrv         : 4;
        
        mUINT_16 rsvd_b10_b11       : 4;
        mUINT_16 calOut             : 1;
        mUINT_16 rsvd_b13           : 1;
        mUINT_16 nCalEn             : 1;
        mUINT_16 pCalEn             : 1;
    } bits;
} mtBM_DDR_PHY_ADCM_PAD_CTL3;    // Buffer Manager DDR_ PHY ADCM PAD Control3  R2EBEh


typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 rsvd_b0_b3         : 4;
        mUINT_16 ddrRfifoDly        : 2;
        mUINT_16 ddrSyncEn          : 1;
        mUINT_16 ddrSyncRst         : 1;
        
        mUINT_16 rsvd_b2_b18        : 8;
    } bits;
} mtBM_DDR_PHY_DEBUG;           // Buffer Manager DDR_ PHY Debug  R2EC0h


typedef union                   // Buffer Manager DRAM TM Command

{
    mUINT_16 all;
    struct 
    {
        mUINT_16 ddrCmd             : 4;
        mUINT_16 rsvd               : 11;
        mUINT_16 updateEn           : 1;
    } bits;
} mtBM_DRAM_TM_CMD;             


typedef union                   // Buffer Manager DRAM Address
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 sdramAddr          : 13;
        mUINT_16 bs                 : 2;
        mUINT_16 reserved           : 1;
    } bits;
} mtBM_DRAM_TM_ADDR;            


typedef  union                  //  Host Linked List Pointer  Register 
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 pointer            : 16;
    }bits;
}mtHOST_LNK_LST_PTR;            


typedef  union                  //  Disk Linked List Pointer Register 
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 pointer            : 16;
    }bits;
}mtDISK_LNK_LST_PTR;              


typedef  union                  //  Extended Linked List Pointer Register 
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 pointer            : 16;
    }bits;
}mtEXTD_LNK_LST_PTR;              


typedef  union                  //  Host Expected Linked List Pointer Register
{                                                             
    mUINT_16 all;
    struct 
    {
        mUINT_16 expHLLptr          : 16;
    }bits;
}mtHOST_EXP_LNK_LST_PTR;          


typedef  union                  //  Disk Expected Linked List Pointer Register
{                                                             
    mUINT_16 all;
    struct 
    {
        mUINT_16 expHLLptr          : 16;
    }bits;

}mtDISK_EXP_LNK_LST_PTR;         


typedef  union                  //  Extended Expected  Linked List Pointer Register
{                                                             
    mUINT_16 all;
    struct 
    {
        mUINT_16 expHLLptr          : 16;
    }bits;

}mtEXTD_EXP_LNK_LST_PTR;        


typedef  union                  //  Host Segment Link List Stop Pointer Register
{                                                             
    mUINT_16 all;
    struct 
    {
        mUINT_16 hllStopPtr         : 16;
    }bits;
}mtHOST_LNK_LST_STOP_PTR;       


typedef  union                  //  Disk Segment Link List Stop Pointer Register
{                                                             
    mUINT_16 all;
    struct 
    {
        mUINT_16 dllStopPtr         : 16;
    }bits;
}mtDISK_LNK_LST_STOP_PTR;       


typedef  union                  //  Extended Segment Link List Stop Pointer Register
{                                                             
    mUINT_16 all;
    struct 
    {
        mUINT_16 dllStopPtr         : 16;
    }bits;
}mtEXTD_LNK_LST_STOP_PTR;       


typedef union                   // Host Sector Size Register
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 size               : 13;
        mUINT_16 rsvd               : 3;
    }bits;
}mtHOST_SECTOR_SIZE;            


typedef union                   // Disk Sector Size Register
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 size               : 13;
        mUINT_16 rsvd               : 3;
    }bits;
}mtDISK_SECTOR_SIZE;            


typedef union                   // Disk Sector Size Register
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 size               : 13;
        mUINT_16 rsvd               : 3;
    }bits;
}mtEXTD_SECTOR_SIZE;            


typedef union                   // Disk Segment Select Register
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 dskSegsel      : 3;
        mUINT_16 rsvd_b3_b4     : 2;
        mUINT_16 dskSCCtoSSC1   : 1;
        mUINT_16 rsvd_b6_14     : 9;
        mUINT_16 dskSegSelEn    : 1;
    }bits;
}mtDISK_SEG_SEL;              

typedef union                   // Ext Segment Select Register
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 extSegsel      : 3;
        mUINT_16 rsvd_b3_b13    : 11;
        mUINT_16 extSSizeEn     : 1;
        mUINT_16 extSegSelEn    : 1;
    }bits;
}mtEXT_SEG_SEL; 


typedef union                                   // Disk Logical Sector Count Select Register
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 dskLSSC       : 6;
        mUINT_16 rsvd4         : 1;
        mUINT_16 hstSSCtoSSC1  : 1;
        mUINT_16 rsvd6         : 8;
    }bits;
}mtDISK_LOG_SECTOR_CNT_SEL;          


typedef union                                   // Current Host Segment Select
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 curhSegSel    : 3;
        mUINT_16 rsvd_b3_b14   : 12;
        mUINT_16 hostSegSelEn  : 1;
    }bits;
}mtHOST_CUR_SEG_SEL;                          


typedef union                                   // Disk Stream Control
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 diskHostSel        : 6;
        mUINT_16 rsvd_b4_6          : 1;
        mUINT_16 host2disk          : 1;
    
        mUINT_16 diskExtdSel        : 4;
        mUINT_16 rsvd_b11_14        : 3;
        mUINT_16 extd2disk          : 1;
    }bits;
}mtDISK_STREAM_CTRL;                          


typedef union                                   // Host Stream Control
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 hostDiskSel        : 4;
        mUINT_16 rsvd_b3_6          : 3;
        mUINT_16 disk2host          : 1;
    
        mUINT_16 hostExtdSel        : 4;
        mUINT_16 rsvd_b11_14        : 3;
        mUINT_16 extd2host          : 1;
    }bits;
}mtHOST_STREAM_CTRL;                          


typedef union                                   // Extended Stream Control
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 extdHostSel        : 6;
        mUINT_16 rsvd_b4_6          : 1;
        mUINT_16 host2extd          : 1;
    
        mUINT_16 extdDiskSel        : 4;
        mUINT_16 rsvd_b11_14        : 3;
        mUINT_16 disk2extd          : 1;
    }bits;
}mtEXTD_STREAM_CTRL;      

                    
typedef union                                   // BM mode select
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 bmTestModeSel      : 8;
        
        mUINT_16 longJumpPtrEn      : 1;
        mUINT_16 segPtrJumpEn       : 1;
        mUINT_16 rsvd_b10_11        : 2;
        mUINT_16 DVcompatible       : 1;
        mUINT_16 longIdRdEn         : 1;
        mUINT_16 ddrTestModeEn      : 1;
        mUINT_16 chipRdEn           : 1;
    }bits;
}mtBM_TEST_MODE_SELECT;                          


typedef union                                   // SSD Control
{
    mUINT_16 all;
    struct 
    {
        mUINT_16 descSize           : 4;
        mUINT_16 extdDescCntEn      : 1;
        mUINT_16 hostDescCntEn      : 1;
        mUINT_16 diskDescCntEn      : 1;
        mUINT_16 rsvd_b7            : 1;
   
        mUINT_16 extdDescCntMode    : 1;
        mUINT_16 hostDescCntMode    : 1;
        mUINT_16 diskDescCntMode    : 1;
        mUINT_16 rsvd_b11_b15       : 5;
    }bits;
}mtSSD_CTRL;                          


typedef mINT_16     mtHOST_SEG_SECTOR_CNT;      // Host Segment Sector Count Register
typedef mINT_16     mtDISK_SEG_SECTOR_CNT;      // Disk Segment Sector Count Register
typedef mINT_16     mtEXTD_SEG_SECTOR_CNT;      // Extended Segment Sector Count Register
typedef mINT_16     mtHOST_SEG_0_SECTOR_CNT_ADJ;// Host Segment 0 Sector Count Adjust Register
typedef mINT_16     mtHOST_SEG_FREE_SPACE_CUR;  // Current Host Segment Free Space Register
typedef mINT_16     mtSEG_SECT_CNT_0;           // Segment Sector Count 0  Register
typedef mINT_16     mtSEG_SECT_CNT_1;           // Segment Sector Count 1  Register
typedef mINT_16     mtHOST_AVAIL_CNT;           // Host available sector count
typedef mINT_16     mtSEG_SECT_CNT_0_ADJ;       // Segment Sector Count 0 Adjust Register
typedef mINT_16     mtSEG_SECT_CNT_1_ADJ;       // Segment Sector Count 1 Adjust Register
typedef mINT_16     mtCUR_HS_SEG_SEC_CNT;       // Current host segment Sector Count
typedef mINT_16     mtCUR_FS_SEG_SEC_CNT;       // Current flash segment Sector Count
typedef mUINT_16    mtDISK_XFER_SECTOR_CNT;     // Disk XFER sector Count
typedef mUINT_16    mtHOST_SEG_SIZE;            // Host Segment Size Register 
typedef mUINT_16    mtDISK_SEG_SIZE;            // Disk Segment Size Register 
typedef mUINT_16    mtEXTD_SEG_SIZE;            // Extended Segment Size Register 
typedef mUINT_16    mtCUR_DSEG_FREE_SPACE;      // Disk Segment Free Space Register
typedef mUINT_16    mtDISK_XFER_BYTE_CNT;       // Disk Transfer Byte Count Register
typedef mUINT_16    mtHOST_XFER_BYTE_CNT;       // Host Transfer Byte Count Register
typedef mUINT_16    mtEXTD_XFER_BYTE_CNT;       // Extended Transfer Byte Count Register
typedef mUINT_16    mtHOST_SEG_XFER_PTR;        // Host Segment Transfer Pointer Register 
typedef mUINT_16    mtDISK_SEG_XFER_PTR;        // Disk Segment Transfer Pointer Register
typedef mUINT_16    mtEXTD_SEG_XFER_PTR;        // Extended Segment Transfer Pointer Register


typedef struct      // buffer manager
{
    mtBM_CNTRL_REG1             cntrlReg1;      // Buffer Manager Control 1 Register            offset = 0xE00
    mtBM_CNTRL_REG0             cntrlReg0;      // Buffer Manager Control 0 Register            offset = 0xE02
    mtBM_RR_CNTRL0              rrCntrl0;       // Buffer Manager Rount Robin Control 0         offset = 0xE04
    mtBM_RR_CNTRL1              rrCntrl1;       // Buffer Manager Rount Robin Control 1         offset = 0xE06
    mtBM_SHARED_2_SLOT_CNTRL    shared2SlotCntl;// Buffer Manager Shared 2 Slot Control         offset = 0xE08
    mtBM_SHARED_1_SLOT_CNTRL    shared1SlotCntl;// Buffer Manager Shared 1 Slot Control         offset = 0xE0A
    mtBM_SHARED_3_SLOT_CNTRL    shared3SlotCntl;// Buffer Manager Shared 3 Slot Control         offset = 0xE0C
    mtBM_RR_SLOT_MASK           rrSlotMask;     // Buffer Manager Round Robin Slot Mask         offset = 0xE0E
    mtBM_STAT0                  stat0;          // Buffer Manager Status 0 Register             offset = 0xE10
    mtBM_STAT1                  stat1;          // Buffer Manager Status 1 Register             offset = 0xE12
    mtBM_STAT2                  stat2;          // Buffer Manager Status 2 Register             offset = 0xE14
    mtBM_STAT3                  stat3;          // Buffer Manager Status 3 Register             offset = 0xE16
    mtBM_STAT0                  intEnable0;     // Buffer Manager Int Mask 0 Register           offset = 0xE18
    mtBM_STAT1                  intEnable1;     // Buffer Manager Int Mask 1 Register           offset = 0xE1A
    mtBM_STAT2                  intEnable2;     // Buffer Manager Int Mask 2 Register           offset = 0xE1C
    mtBM_STAT3                  intEnable3;     // Buffer Manager Int Mask 3 Register           offset = 0xE1E
    mtBM_DRAM_CNTRL_REG1        dramCntl1;      // Buffer Manager DRAM control register 1       offset = 0xE20
    mtBM_DRAM_CNTRL_REG0        dramCntl0;      // Buffer Manager DRAM control register 0       offset = 0xE22
    mUINT_16                    PAD2E24;        //                                              offset = 0xE24
    mtBM_REF_PRD                refPeriod;      // Buffer Manager DRAM Refresh period           offset = 0xE26
    mtBM_DRAM_EXT_MODE2         dramExtMode2;   // Buffer Manager DRAM Ext Mode Control 2       offset = 0xE28
    mtBM_DRAM_EXT_MODE          dramExtMode3;   // Buffer Manager DRAM Ext Mode                 offset = 0xE2A
    mtBM_DRAM_MODE_CNTL         dramModeCntl;   // Buffer Manager DRAM Mode Control             offset = 0xE2C
    mtBM_DRAM_EXT_MODE1         dramExtMode1;   // Buffer Manager DRAM Ext Mode Control 1       offset = 0xE2E
    mUINT_16                    PADE32_E3E[8];  //                                              offset = 0xE30-E3E
    mtHOST_LNK_LST_PTR          hostSeg1LnkLstPtr;      // Host Segment 1 Linked List Pointer Register  offset = 0xE40
    mtHOST_LNK_LST_PTR          hostSeg0LnkLstPtr;      // Host Segment 0 Linked List Pointer Register  offset = 0xE42
    mtHOST_LNK_LST_PTR          hostSeg3LnkLstPtr;      // Host Segment 3 Linked List Pointer Register  offset = 0xE44
    mtHOST_LNK_LST_PTR          hostSeg2LnkLstPtr;      // Host Segment 2 Linked List Pointer Register  offset = 0xE46
    mtHOST_LNK_LST_PTR          hostSeg5LnkLstPtr;      // Host Segment 5 Linked List Pointer Register  offset = 0xE48
    mtHOST_LNK_LST_PTR          hostSeg4LnkLstPtr;      // Host Segment 4 Linked List Pointer Register  offset = 0xE4A
    mtHOST_LNK_LST_PTR          hostSeg7LnkLstPtr;      // Host Segment 7 Linked List Pointer Register  offset = 0xE4C
    mtHOST_LNK_LST_PTR          hostSeg6LnkLstPtr;      // Host Segment 6 Linked List Pointer Register  offset = 0xE4E
    mtHOST_EXP_LNK_LST_PTR      expHostSeg1LnkLstPtr;   // Expected Host Segment 1 Linked List Ptr Reg  offset = 0xE50
    mtHOST_EXP_LNK_LST_PTR      expHostSeg0LnkLstPtr;   // Expected Host Segment 0 Linked List Ptr Reg  offset = 0xE52
    mtHOST_EXP_LNK_LST_PTR      expHostSeg3LnkLstPtr;   // Expected Host Segment 3 Linked List Ptr Reg  offset = 0xE54
    mtHOST_EXP_LNK_LST_PTR      expHostSeg2LnkLstPtr;   // Expected Host Segment 2 Linked List Ptr Reg  offset = 0xE56
    mtHOST_EXP_LNK_LST_PTR      expHostSeg5LnkLstPtr;   // Expected Host Segment 5 Linked List Ptr Reg  offset = 0xE58
    mtHOST_EXP_LNK_LST_PTR      expHostSeg4LnkLstPtr;   // Expected Host Segment 4 Linked List Ptr Reg  offset = 0xE5A
    mtHOST_EXP_LNK_LST_PTR      expHostSeg7LnkLstPtr;   // Expected Host Segment 7 Linked List Ptr Reg  offset = 0xE5C
    mtHOST_EXP_LNK_LST_PTR      expHostSeg6LnkLstPtr;   // Expected Host Segment 6 Linked List Ptr Reg  offset = 0xE5E
    mtDISK_LNK_LST_PTR          diskSeg1LnkLstPtr;      // Disk Linked List 1 Pointer Register          offset = 0xE60
    mtDISK_LNK_LST_PTR          diskSeg0LnkLstPtr;      // Disk Linked List 0 Pointer Register          offset = 0xE62
    mtDISK_LNK_LST_PTR          diskSeg3LnkLstPtr;      // Disk Linked List 3 Pointer Register          offset = 0xE64
    mtDISK_LNK_LST_PTR          diskSeg2LnkLstPtr;      // Disk Linked List 2 Pointer Register          offset = 0xE66
    mtDISK_EXP_LNK_LST_PTR      expDiskSeg1LnkLstPtr;   // Expected Disk Segment 1 Linked List Ptr Reg  offset = 0xE68
    mtDISK_EXP_LNK_LST_PTR      expDiskSeg0LnkLstPtr;   // Expected Disk Segment 0 Linked List Ptr Reg  offset = 0xE6A
    mtDISK_EXP_LNK_LST_PTR      expDiskSeg3LnkLstPtr;   // Expected Disk Segment 3 Linked List Ptr Reg  offset = 0xE6C
    mtDISK_EXP_LNK_LST_PTR      expDiskSeg2LnkLstPtr;   // Expected Disk Segment 2 Linked List Ptr Reg  offset = 0xE6E
    mtDISK_LNK_LST_STOP_PTR     diskSegLnkLstStopPtr;   // Disk Segment Link List Stop Pointer          offset = 0xE70
    mtHOST_LNK_LST_STOP_PTR     hostSegLnkLstStopPtr;   // Host Segment Link List Stop Pointer          offset = 0xE72
    mINT_16                     PAD2E74;                //                                              offset = 0xE74
    mtEXTD_LNK_LST_STOP_PTR     extdSegLnkLstStopPtr;   // Ext Segment Link List Stop Pointer           offset = 0xE76
    mtEXTD_LNK_LST_PTR          extdSeg1LnkLstPtr;      // Ext Linked List 1 Pointer Register           offset = 0xE78
    mtEXTD_LNK_LST_PTR          extdSeg0LnkLstPtr;      // Ext Linked List 0 Pointer Register           offset = 0xE7A
    mtEXTD_LNK_LST_PTR          extdSeg3LnkLstPtr;      // Ext Linked List 3 Pointer Register           offset = 0xE7C
    mtEXTD_LNK_LST_PTR          extdSeg2LnkLstPtr;      // Ext Linked List 2 Pointer Register           offset = 0xE7E
    mtEXTD_EXP_LNK_LST_PTR      expExtdSeg1LnkLstPtr;   // Expected Ext Segment 1 Linked List Ptr Reg   offset = 0xE80
    mtEXTD_EXP_LNK_LST_PTR      expExtdSeg0LnkLstPtr;   // Expected Ext Segment 0 Linked List Ptr Reg   offset = 0xE82
    mtEXTD_EXP_LNK_LST_PTR      expExtdSeg3LnkLstPtr;   // Expected Ext Segment 3 Linked List Ptr Reg   offset = 0xE84
    mtEXTD_EXP_LNK_LST_PTR      expExtdSeg2LnkLstPtr;   // Expected Ext Segment 2 Linked List Ptr Reg   offset = 0xE86
    mINT_16                     PADE88_E9E[12];         //                                              offset = 0xE88-0xE9E
    mtBM_DDR_PHY0               dramPhyDll0Cntl;        // Buffer Manager DDR Phy DLL0 Control          offset = 0xEA0
    mtBM_DDR_PHY1               dramPhyDll1Cntl;        // Buffer Manager DDR Phy DLL1 Control          offset = 0xEA2
    mINT_16                     PADEA4_EAE[6];          //                                              offset = 0xEA4-0xEAE
    mtBM_DDR_PHY_DQ_PAD_CTL0    dramPhyDqPadCtl0;       // Buffer Manager DDR Phy DQ Pad Control0       offset = 0xEB0
    mtBM_DDR_PHY_DQ_PAD_CTL1    dramPhyDqPadCtl1;       // Buffer Manager DDR Phy DQ Pad Control1       offset = 0xEB2
    mtBM_DDR_PHY_DQ_PAD_CTL2    dramPhyDqPadCtl2;       // Buffer Manager DDR Phy DQ Pad Control2       offset = 0xEB4
    mtBM_DDR_PHY_CLK_PAD        dramPhyClockPad;        // Buffer Manager DDR Phy Clock Pad             offset = 0xEB6
    mtBM_DDR_PHY_ADCM_PAD_CTL0  dramPhyAdcmPadCtl0;     // Buffer Manager DDR Phy ADCM Pad Control0     offset = 0xEB8
    mtBM_DDR_PHY_ADCM_PAD_CTL1  dramPhyAdcmPadCtl1;     // Buffer Manager DDR Phy ADCM Pad Control1     offset = 0xEBA
    mtBM_DDR_PHY_ADCM_PAD_CTL2  dramPhyAdcmPadCtl2;     // Buffer Manager DDR Phy ADCM Pad Control2     offset = 0xEBC
    mtBM_DDR_PHY_ADCM_PAD_CTL3  dramPhyAdcmPadCtl3;     // Buffer Manager DDR Phy ADCM Pad Control3     offset = 0xEBE
    mtBM_DDR_PHY_DEBUG          dramDebug;              // Buffer Manager DRAM Debug                    offset = 0xEC0
    mtBM_TEST_MODE_SELECT       bmTestModeSel;          // Debug, test mode select                      offset = 0xEC2
    mINT_16                     dramWrtCntrl;           //                                              offset = 0xEC4
    mINT_16                     dramWrtCmdCntrl;        //                                              offset = 0xEC6
    mINT_16                     PADEC8_EFE[28];         //                                              offset = 0xEC8-0xEFE
    mtDISK_SECTOR_SIZE          diskSectorSize;         // Disk Sector Size                             offset = 0xF00
    mtHOST_SECTOR_SIZE          hostSectorSize;         // Host Sector Size                             offset = 0xF02
    mtHOST_SEG_SIZE             hostSeg0Size;           // Host Segment0 Size                           offset = 0xF04
    mUINT_16                    sectorSizeRatio;        // Host/Disk Sector Size Ratio                  offset = 0xF06
    mtHOST_SEG_SIZE             hostSeg2Size;           // Host Segment2 Size                           offset = 0xF08
    mtHOST_SEG_SIZE             hostSeg1Size;           // Host Segment1 Size                           offset = 0xF0A
    mtHOST_SEG_SIZE             hostSeg4Size;           // Host Segment4 Size                           offset = 0xF0C
    mtHOST_SEG_SIZE             hostSeg3Size;           // Host Segment3 Size                           offset = 0xF0E
    mtHOST_SEG_SIZE             hostSeg6Size;           // Host Segment6 Size                           offset = 0xF10
    mtHOST_SEG_SIZE             hostSeg5Size;           // Host Segment5 Size                           offset = 0xF12
    mtHOST_SEG_SECTOR_CNT       hostSeg0SecCnt;         // Host Segment0 Sector Count                   offset = 0xF14
    mtHOST_SEG_SIZE             hostSeg7Size;           // Host Segment7 Size                           offset = 0xF16
    mtHOST_SEG_SECTOR_CNT       hostSeg2SecCnt;         // Host Segment2 Sector Count                   offset = 0xF18
    mtHOST_SEG_SECTOR_CNT       hostSeg1SecCnt;         // Host Segment1 Sector Count                   offset = 0xF1A
    mtHOST_SEG_SECTOR_CNT       hostSeg4SecCnt;         // Host Segment4 Sector Count                   offset = 0xF1C
    mtHOST_SEG_SECTOR_CNT       hostSeg3SecCnt;         // Host Segment3 Sector Count                   offset = 0xF1E
    mtHOST_SEG_SECTOR_CNT       hostSeg6SecCnt;         // Host Segment6 Sector Count                   offset = 0xF20
    mtHOST_SEG_SECTOR_CNT       hostSeg5SecCnt;         // Host Segment5 Sector Count                   offset = 0xF22
    mtDISK_SEG_SIZE             diskSeg0Size;           // disk segment0 Size                           offset = 0xF24
    mtHOST_SEG_SECTOR_CNT       hostSeg7SecCnt;         // Host Segment7 Sector Count                   offset = 0xF26
    mtDISK_SEG_SIZE             diskSeg2Size;           // disk segment2 Size                           offset = 0xF28
    mtDISK_SEG_SIZE             diskSeg1Size;           // disk segment1 Size                           offset = 0xF2A
    mtDISK_SEG_SECTOR_CNT       diskSeg0SectorCnt;      // Disk Segment0 Sector Count                   offset = 0xF2C
    mtDISK_SEG_SIZE             diskSeg3Size;           // Disk segment3 Size                           offset = 0xF2E
    mtDISK_SEG_SECTOR_CNT       diskSeg2SectorCnt;      // Disk Segment2 Sector Count                   offset = 0xF30
    mtDISK_SEG_SECTOR_CNT       diskSeg1SectorCnt;      // Disk Segment1 Sector Count                   offset = 0xF32
    mtDISK_SEG_SEL              diskSegSelect;          // Disk Segment Select                          offset = 0xF34
    mtDISK_SEG_SECTOR_CNT       diskSeg3SectorCnt;      // Disk Segment3 Sector Count                   offset = 0xF36
    mtHOST_SEG_FREE_SPACE_CUR   curHostSegFreeSpace;    // Current Host Segment Free Space              offset = 0xF38
    mtDISK_LOG_SECTOR_CNT_SEL   diskLSSCsel;            // Disk Logical Segment Sector Count Select     offset = 0xF3A
    mtCUR_HS_SEG_SEC_CNT        curHostSegSectorCnt;    // current host segment sector count            offset = 0xF3C
    mtCUR_DSEG_FREE_SPACE       curDSegFreeSpace;       // Current Disk Segment Free Space              offset = 0xF3E
    mtHOST_AVAIL_CNT            hostAvailCnt;           // Host Available count                         offset = 0xF40
    mtCUR_FS_SEG_SEC_CNT        curDiskSegSectorCnt;    // Current flash seg sector count               offset = 0xF42
    mUINT_16                    hostSegAdjSel;          // Host Segment Adjust Select                   offset = 0xF44
    mtSEG_SECT_CNT_1_ADJ        SSC1adjust;             // Segment Sector Count1 Adjust Register        offset = 0xF46
    mtHOST_CUR_SEG_SEL          curHostSegSel;          // Current Host Segment Select                  offset = 0xF48
    mtSEG_SECT_CNT_0_ADJ        hostSegSectCntAdj;      // Host Segment Sector Count Adjust Register    offset = 0xF4A
    mtDISK_XFER_BYTE_CNT        diskXferByteCnt;        // Disk Transfer Byte Count Register            offset = 0xF4C
    mUINT_16                    diskSegAdjSel;          // Disk Segment Adjust Select                   offset = 0xF4E
    mUINT_16                    curExtdSegSectorCnt;    // Current Extended Segment Sector Count        offset = 0xF50
    mUINT_16                    curExtdSegFreeSpace;    // Current Extended Segment Free Space          offset = 0xF52
    mUINT_16                    extdSegSectCntAdj;      // Extended Segment Count Adjust                offset = 0xF54
    mUINT_16                    extdSegAdjSel;          // Extended Segment Adjust Select               offset = 0xF56
    mtEXT_SEG_SEL               extdSegSel;             // Extended Segment  Select                     offset = 0xF58
    mtEXTD_SECTOR_SIZE          extdSecSize;            // Extended Segment Sector Size                 offset = 0xF5A
    mUINT_16                    PADF5C_F5E[2];          //                                              offset = 0x2F5C_5E
    mtDISK_STREAM_CTRL          diskStreamCtrl;         // Disk Streaming Control                       offset = 0x2F60            
    mtHOST_STREAM_CTRL          hostStreamCtrl;         // Host Streaming Control                       offset = 0x2F62      
    mUINT_16                    PADF64;                 //                                              offset = 0x2F64
    mtEXTD_STREAM_CTRL          extdStreamCtrl;         // Extended Streaming Control                   offset = 0x2F66        
    mUINT_16                    PADF68_6A[2];           //                                              offset = 0x2F68_2F6A
    mUINT_16                    extdXferCnt;            // Extended Segment  Xfer Count                 offset = 0xF6C
    mUINT_16                    PADFF6E;                //                                              offset = 0x2F6E
    mtEXTD_SEG_SIZE             extdSeg1Size;           // Extended Segment1 Size                       offset = 0xF70
    mtEXTD_SEG_SIZE             extdSeg0Size;           // Extended Segment0 Size                       offset = 0xF72
    mtEXTD_SEG_SIZE             extdSeg3Size;           // Extended Segment3 Size                       offset = 0xF74
    mtEXTD_SEG_SIZE             extdSeg2Size;           // Extended Segment2 Size                       offset = 0xF76
    mtEXTD_SEG_SECTOR_CNT       extdSeg1SectorCnt;      // Extended Segment1 Sector Count               offset = 0xF78
    mtEXTD_SEG_SECTOR_CNT       extdSeg0SectorCnt;      // Extended Segment0 Sector Count               offset = 0xF7A
    mtEXTD_SEG_SECTOR_CNT       extdSeg3SectorCnt;      // Extended Segment3 Sector Count               offset = 0xF7C
    mtEXTD_SEG_SECTOR_CNT       extdSeg2SectorCnt;      // Extended Segment2 Sector Count               offset = 0xF7E
    mUINT_16                    PADF80_F86[4];          //                                              offset = 0x2F80_2F86
    mtHOST_SEG_XFER_PTR         hostSeg0XferPtrL;       // Host Segment 0 Transfer Pointer Low          offset = 0x2F88
    mtHOST_SEG_XFER_PTR         hostSeg0XferPtrH;       // Host Segment 0 Transfer Pointer Hi           offset = 0x2F8A
    mtHOST_SEG_XFER_PTR         hostSeg1XferPtrL;       // Host Segment 1 Transfer Pointer Low          offset = 0x2F8C
    mtHOST_SEG_XFER_PTR         hostSeg1XferPtrH;       // Host Segment 1 Transfer Pointer Hi           offset = 0x2F8E
    mtHOST_SEG_XFER_PTR         hostSeg2XferPtrL;       // Host Segment 2 Transfer Pointer Low          offset = 0x2F90
    mtHOST_SEG_XFER_PTR         hostSeg2XferPtrH;       // Host Segment 2 Transfer Pointer Hi           offset = 0x2F92
    mtHOST_SEG_XFER_PTR         hostSeg3XferPtrL;       // Host Segment 3 Transfer Pointer Low          offset = 0x2F94
    mtHOST_SEG_XFER_PTR         hostSeg3XferPtrH;       // Host Segment 3 Transfer Pointer Hi           offset = 0x2F96
    mtHOST_SEG_XFER_PTR         hostSeg4XferPtrL;       // Host Segment 4 Transfer Pointer Low          offset = 0x2F98
    mtHOST_SEG_XFER_PTR         hostSeg4XferPtrH;       // Host Segment 4 Transfer Pointer Hi           offset = 0x2F9A
    mtHOST_SEG_XFER_PTR         hostSeg5XferPtrL;       // Host Segment 5 Transfer Pointer Low          offset = 0x2F9C
    mtHOST_SEG_XFER_PTR         hostSeg5XferPtrH;       // Host Segment 5 Transfer Pointer Hi           offset = 0x2F9E
    mtHOST_SEG_XFER_PTR         hostSeg6XferPtrL;       // Host Segment 6 Transfer Pointer Low          offset = 0x2FA0
    mtHOST_SEG_XFER_PTR         hostSeg6XferPtrH;       // Host Segment 6 Transfer Pointer Hi           offset = 0x2FA2
    mtHOST_SEG_XFER_PTR         hostSeg7XferPtrL;       // Host Segment 7 Transfer Pointer Low          offset = 0x2FA4
    mtHOST_SEG_XFER_PTR         hostSeg7XferPtrH;       // Host Segment 7 Transfer Pointer Hi           offset = 0x2FA6
    mtDISK_SEG_XFER_PTR         diskSeg0XferPtrL;       // Disk Segment Transfer Pointer Low            offset = 0x2FA8
    mtDISK_SEG_XFER_PTR         diskSeg0XferPtrH;       // Disk Segment Transfer Pointer High           offset = 0x2FAA
    mtDISK_SEG_XFER_PTR         diskSeg1XferPtrL;       // Disk Segment Transfer Pointer Low            offset = 0x2FAC
    mtDISK_SEG_XFER_PTR         diskSeg1XferPtrH;       // Disk Segment Transfer Pointer High           offset = 0x2FAE
    mtDISK_SEG_XFER_PTR         diskSeg2XferPtrL;       // Disk Segment Transfer Pointer Low            offset = 0x2FB0
    mtDISK_SEG_XFER_PTR         diskSeg2XferPtrH;       // Disk Segment Transfer Pointer High           offset = 0x2FB2
    mtDISK_SEG_XFER_PTR         diskSeg3XferPtrL;       // Disk Segment Transfer Pointer Low            offset = 0x2FB4
    mtDISK_SEG_XFER_PTR         diskSeg3XferPtrH;       // Disk Segment Transfer Pointer High           offset = 0x2FB6
    mUINT_32                    crcBaseAddress;
    mUINT_16                    PADFB8_FD6[14];         //                                              offset = 0x2FBc_0x2FD6
    mUINT_16                    wpStartAddrL;           // Write Protection Start Address Low           offset = 0x2FD8
    mUINT_16                    wpStartAddrH;           // Write Protection Start Address Hi            offset = 0x2FDA
    mUINT_16                    wpEndAddrL;             // Write Protection End Address Low             offset = 0x2FDC
    mUINT_16                    wpEndAddrH;             // Write Protection End Address Hi              offset = 0x2FDE
    mUINT_16                    ssdTableStartL;         // SSD Table Start Address Low Register         offset = 0x2FE0
    mUINT_16                    ssdTableStartH;         // SSD Table Start Address High Register        offset = 0x2FE2
    mUINT_16                    ssdTableEndL;           // SSD Table End Address Low Register           offset = 0x2FE4
    mUINT_16                    ssdTableEndH;           // SSD Table End Address High Register          offset = 0x2FE6
    mUINT_16                    PADFE8_FEE[4];          //                                              offset = 0x2FE8_0x2FEE
    mtEXTD_SEG_XFER_PTR         extdSeg0XferPtrL;       // Extended Segment0 Transfer Pointer Low       offset = 0x2FF0
    mtEXTD_SEG_XFER_PTR         extdSeg0XferPtrH;       // Extended Segment0 Transfer Pointer Hi        offset = 0x2FF2
    mtEXTD_SEG_XFER_PTR         extdSeg1XferPtrL;       // Extended Segment0 Transfer Pointer Low       offset = 0x2FF4
    mtEXTD_SEG_XFER_PTR         extdSeg1XferPtrH;       // Extended Segment0 Transfer Pointer Hi        offset = 0x2FF6
    mtEXTD_SEG_XFER_PTR         extdSeg2XferPtrL;       // Extended Segment0 Transfer Pointer Low       offset = 0x2FF8
    mtEXTD_SEG_XFER_PTR         extdSeg2XferPtrH;       // Extended Segment0 Transfer Pointer Hi        offset = 0x2FFA
    mtEXTD_SEG_XFER_PTR         extdSeg3XferPtrL;       // Extended Segment0 Transfer Pointer Low       offset = 0x2FFC
    mtEXTD_SEG_XFER_PTR         extdSeg3XferPtrH;       // Extended Segment0 Transfer Pointer Hi        offset = 0x2FFE
    
    mUINT_32                    currDiskSSD_31_0;       //                                              offset = 0x3000
    mUINT_32                    currDiskSSD_63_32;      //                                              offset = 0x3004
    mUINT_32                    currDiskSSD_95_64;      //                                              offset = 0x3008
    mUINT_16                    PAD300C__30C2[92];      //                                              offset = 0x300C_0x30C2
    mtSSD_CTRL                  ssdCtrl;                // SSD control register                         offset = 0x30C4
    
    
} mtBUFF_MNGR;

//=======================================================================
//     [[[[ Digital Data Output (DDO) ]]]]
//=======================================================================

typedef struct
{
    union
    {
        mUINT_16 all;
        struct 
        {            
            mUINT_16 w64Ddo              : 1;      // [0] Starts shifting the 64-bit DDO. Auto-cleared
            mUINT_16 w128Ddo             : 1;      // [1] Starts shifting the 128-bit DDO. Auto-cleared
            mUINT_16 reserved2           : 13;
            mUINT_16 ddoRdy              : 1;      // [15] Ready for a new DDO Word
        }bits;
    } ddoControl;                               // 0x1C00_A600 DDO Control

    union
    {
        mUINT_16 all;
        struct 
        {            
            mUINT_16 ddoClkDiv           : 2;      // [1:0] 0=Disabled, 1=CPU Clock, 2=CpuClk/4, 3=CpuClk/8
            mUINT_16 reserved12          : 14;
        }bits;
    } ddoConfig;                                // 0x1C00_A602 DDO Configuration

    mUINT_16         ddoReserved02[6];           // 0x1C00_A604 - A608 reserved

    mUINT_16         ddoBits15_0;                // 0x1C00_A610 These registers contain the DDO data to be written
    mUINT_16         ddoBits31_16;               // 0x1C00_A612
    mUINT_16         ddoBits47_32;               // 0x1C00_A614
    mUINT_16         ddoBits63_48;               // 0x1C00_A616
    mUINT_16         ddoBits79_64;               // 0x1C00_A618
    mUINT_16         ddoBits95_80;               // 0x1C00_A61A
    mUINT_16         ddoBits111_96;              // 0x1C00_A61C
    mUINT_16         ddoBits127_112;             // 0x1C00_A61E

} mtDDO_BLOCK;

//=======================================================================
//     [[[[ Error Injection Logic Register Map ]]]]
//=======================================================================

typedef struct
{
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 intnlErrInjctEn : 1;
            mUINT_16 extnlErrInjctEn : 1;
            mUINT_16 svo_dt_mode        : 2;
            mUINT_16 TAerrInjctEn    : 1;
            mUINT_16 sbdErrInjctEn      : 1;
            mUINT_16 sbdSMFErrInjctEn   : 1;
            mUINT_16 rsvd15_7           : 9;
        } bits;
    } ErrInjectionCtrl;                      // RAC50

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 intnlLocMatch   : 1;
            mUINT_16 extnlTriggerDet : 1;
            mUINT_16 rsvd            :14;
        } bits;
    } ErrInjectionStatus;                    // RAC52

    mUINT_16   intrnlErrInjctLSNStart;		 // RAC54
    mUINT_16   intrnlErrInjctLSNEnd;		 // RAC56
    mUINT_16   intrnlErrInjctSSNStart;		 // RAC58
    mUINT_16   intrnlErrInjctSSNEnd;		 // RAC5A
    mUINT_16   intrnlDataErrInjctLoc0;	     // RAC5C
    mUINT_16   intrnlDataErrInjctLoc1;	     // RAC5E
    mUINT_16   intrnlServoErrInjctLoc0;	     // RAC60

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 intnlErrInjctPat0  : 8;
            mUINT_16 rsvd            : 6;
            mUINT_16 errType0           : 2;
        } bits;
    } dataErrInjectionPat0;                  // RAC62

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 intnlErrInjctPat1  : 8;
            mUINT_16 rsvd               : 6;
            mUINT_16 errType1           : 2;
        } bits;
    } dataErrInjectionPat1;                  // RAC64

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 intnlErrInjctSvoPat0   : 8;
            mUINT_16 rsvd                   : 6;
            mUINT_16 errTypeSrv0            : 2;
        } bits;
    } servoErrInjectionPat0;                 // RAC66

    mUINT_16   intrnlErrInjctDataLen;        // RAC68
    mUINT_16   intrnlErrInjctServoLen;       // RAC6A


} mtERR_INJECTION_BLOCK;                                                                            
                                                                                                    
                                                                                                    
// WORD_SWAP                                                                                        
// ENUM for ATA TASK FILE  access                                                                   
typedef enum                                                                                        
{
    mTF_STATUS_REG      =0,     //   ATA Status Register 
    mTF_ERROR_REG       =1,     //   Error Register
    mTF_COMMAND_REG     =2,     //   Command Register 
    mTF_FEATURES_REG    =3,     //   FEATURE Register  
    mTF_SECTOR_NUM_REG  =4,     //   Sector Number Register
    mTF_CYL_LOW_REG     =5,     //   Cylinder Low Register
    mTF_CYL_HIGH_REG    =6,     //   Cylinder High Register 
    mTF_DEV_HEAD_REG    =7,     //   Device/Head Register
    mTF_DEV_CNTL        =8,
    mTF_PAD1            =9,
    mTF_SECTOR_CNT_REG  =0xA    //   Sector Count

} mtATA_TASK_FILE_REGS;

typedef enum                                                                                        
{
    mLBA1_0          =0,     //   lba0_1 
    mLBA3_2          =1,     //   lba3_2
    mLBA5_4          =2,     //   lba5_4
} mLBA_48_BIT_REGS;

//=======================================================================
//     [[[[ Flash Sequencer(SEQ) ]]]]
//=======================================================================
typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16     trkDone         : 1;
        mUINT_16     trkErr          : 1;
        mUINT_16     rsvd0           : 2;
        mUINT_16     opDone          : 1;
        mUINT_16     rsvd1           : 1;
        mUINT_16     desOverFlow     : 1; //dnumOver
        mUINT_16     trkOverFlow     : 1; //tnumOver
        mUINT_16     auDecDoneOvFlow : 1; //adecOver
        mUINT_16     auEncDoneOvFlow : 1; //aencOver
        mUINT_16     mqp1Full        : 1;
        mUINT_16     mqp0Full        : 1;
        mUINT_16     SacRErr         : 1;
        mUINT_16     SacWErr         : 1;
        mUINT_16     rsvd2           : 2;
    } bits;
}mtSEQ_INT;               // Sequencer interrupt

typedef struct
{
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     rsvd0           : 7;
        mUINT_16     enErrMq         : 1;  
        mUINT_16     mqArbMode       : 2;   
        mUINT_16     rsvd1           : 1;   
        mUINT_16     trkStatusHold   : 1;    
        mUINT_16     trkConf         : 2;   
        mUINT_16     rsvd2           : 1;   
        mUINT_16     trkOrder        : 1;   
      } bits;
    }seqConfig1;                 // Sequencer configuration 1: 0xD000
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     clkAutoPd       : 1;
        mUINT_16     rsvd0           : 4;
        mUINT_16     sramAutoPd      : 1;
        mUINT_16     sramPdTh        : 3;
        mUINT_16     rsvd1           : 1;
        mUINT_16     sramPdExit      : 3;
        mUINT_16     rsvd2           : 1;
        mUINT_16     trkSramPdwn     : 1;
        mUINT_16     sqcrClkDis      : 1;   
      } bits;
    }seqConfig2;                 // Sequencer configuration 2: 0xD002
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     twoLbaEn        : 1;
        mUINT_16     auxDataMode     : 2;    // auxSize
        mUINT_16     auxMetaSel      : 1;
        mUINT_16     rsvd0           : 5;
        mUINT_16     paMode          : 1;
        mUINT_16     paRatio         : 3;
        mUINT_16     rsvd1           : 1;
        mUINT_16     errCntEn        : 1;
        mUINT_16     rsvd2           : 1;
      } bits;
    }seqConfig3;                 // Sequencer configuration 3: 0xD004

    mUINT_16 maxActTrk;          // Sequencer configuration 4: 0xD006

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     testBusSel       : 8;
        mUINT_16     strmInexChk      : 1;
        mUINT_16     doneAccpSel      : 1;
        mUINT_16     enAbortRpt       : 1;
        mUINT_16     ecEnCtrlDis      : 1;
        mUINT_16     desBurstDis      : 1;
        mUINT_16     lastAuFrc        : 2;
        mUINT_16     ecAuNumMsb       : 1;
      } bits;
    }seqConfig41;                // Sequencer configuration 4-1: 0xD008
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     bistRstb         : 1;
        mUINT_16     bistRowColSwit   : 1;
        mUINT_16     bistRunStop      : 1;
        mUINT_16     bistStatusEn     : 1;
        mUINT_16     bistStatusClk    : 1;
        mUINT_16     bistStatusIn     : 1;
        mUINT_16     rsvd             : 1;
        mUINT_16     bistMode         : 1;
        mUINT_16     trkSramRtc       : 2;
        mUINT_16     trkSramWtc       : 2;
        mUINT_16     bistFinish       : 1;
        mUINT_16     bistFail         : 1;
        mUINT_16     bistError        : 1;
        mUINT_16     bistStatusOut    : 1;
      } bits;
    }seqConfig42;                // Sequencer configuration 4-2: 0xD00A

    mUINT_16    rsvd1[2];        // 0xD00C, 0xD00E
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     seqBusy         : 1;
        mUINT_16     rsvd0           : 7;
        mUINT_16     dlcAdjFail      : 1;
        mUINT_16     rsvd1           : 3;
        mUINT_16     seqEnable       : 1;
        mUINT_16     seqAbtMode      : 1;
        mUINT_16     rsvd2           : 1;
        mUINT_16     seqReset        : 1;
      } bits;
    }seqControl1;                // Sequencer control 1: 0xD010    

    mUINT_16 rsvd2;              // 0xD012
    
    mtSEQ_INT   seqIntrStatus;   // Sequencer interrupt status: 0xD014   
 
    mtSEQ_INT   seqIntrMask;     // Sequencer interrupt mask: 0xD016

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     trkId           : 9;
        mUINT_16     rsvd            : 7;
      } bits;
    }trkStatusId;                // Sequencer status ID: 0xD018 
    
    mUINT_16    rsvd3[2];        // 0xD01A, 0xD01C
    
    union
    {
      mUINT_16 all;          
      struct
      {                          
        mUINT_16     desStatusPtr     : 5;
        mUINT_16     rsvd0            : 3;
        mUINT_16     desDonePtr       : 4;
        mUINT_16     rsvd1            : 4;
      } bits;
    }trkPointer;               // Track pointer: 0xD01E
    
    union
    {
      mUINT_32 all;          
      struct
      {                          
        mUINT_32     trkPos           : 1;
        mUINT_32     trkLos           : 1;
        mUINT_32     desProc          : 8;
        mUINT_32     desTot           : 8;
        mUINT_32     errAuNum         : 3;
        mUINT_32     errMpNum         : 2;
        mUINT_32     errAuDesId       : 8;
        mUINT_32     errAuType        : 1;
      } bits;
    }trkOverallStatus;               // Track overall status: 0xD020 ~ 0xD022

    union
    {
        mUINT_32 all;
        struct
        {
            mUINT_16 trkDesDoneL;             // Track descriptor done lower: 0xD024
            mUINT_16 trkDesDoneH;        // Track descriptor done upper: 0xD026
        } words;
    }trkDesDone;
    
    
    mUINT_16    rsvd4[2];        // 0xD028, 0xD02A
    
    union
    {
        mUINT_32 all;
        struct
        {
            mUINT_16 trkDesStatusL;           // Track descriptor status lower: 0xD02C
            mUINT_16 trkDesStatusH;           // Track descriptor status upper: 0xD02E
        } words;
    }trkDesStatus;
    
    union
    {
        mUINT_32 all;
        struct
        {
            mUINT_16    desFifoStartAddL;     // Descriptor FIFO start address lower: 0xD030 
            mUINT_16    desFifoStartAddH;     // Descriptor FIFO start address upper  0xD032
        } words;
    }desFifoStartAddress;

    union
    {
        mUINT_32 all;
        struct
        {
            mUINT_16    desFifoEndAddL;       // Descriptor FIFO end address lower: 0xD034 
            mUINT_16    desFifoEndAddH;       // Descriptor FIFO end address upper  0xD036
        } words;                            
    }desFifoEndAddress;
    
    union
    {
        mUINT_32 all;
        struct
        {
            mUINT_16    desFifoPtrL;          // Descriptor FIFO end address lower: 0xD038 
            mUINT_16    desFifoPtrH;          // Descriptor FIFO end address upper  0xD03A
        } words;                            
    }desFifoPointer;

    mUINT_16    rsvd5[2];        // 0xD03C, 0xD03E
    mUINT_16    desLoopCnt;      // Descriptor loop count: 0xD040
    mUINT_16    desLoopCntAdj;   // Descriptor loop count adjust: 0xD042
    mUINT_16    desFifoCnt;      // Descriptor FIFO Count: 0xD044

    mUINT_16    rsvd6[5];        // 0xD046, 0xD048, 0xD04A, 0xD04C, 0xD04E

    union
    {
        mUINT_32 all;
        struct
        {
            mUINT_16    auxInsFifoStartAddL;    // Aux Insert FIFO start address lower: 0xD050 
            mUINT_16    auxInsFifoStartAddH;    // Aux Insert FIFO start address upper  0xD052
        } words;
    }auxInsFifoStartAddress;
 
 
    union
    {
        mUINT_32 all;
        struct
        {
            mUINT_16    auxInsFifoEndAddL;      // Aux Insert FIFO end address lower: 0xD054 
            mUINT_16    auxInsFifoEndAddH;      // Aux Insert FIFO end address upper: 0xD056
        } words;
    }auxInsFifoEndAddress;    

    union
    {
      mUINT_32 all;          
      struct
      {
        mUINT_16     auxInsFifoPtrL;            // Aux Insert FIFO pointer: 0xD058 
        mUINT_16     auxInsFifoPtrH;            // Aux Insert FIFO pointer: 0xD05A
      } bits;
    }auxInsFifoPtr;               // AUX Insert FIFO pointer

    mUINT_16    rsvd7[2];         // 0xD05C, 0xD05E

    union
    {
        mUINT_32 all;
        struct
        {
            mUINT_16    auxCompFifoStartAddL;    // Aux Compare FIFO start address lower: 0xD060 
            mUINT_16    auxCompFifoStartAddH;    // Aux Compare FIFO start address upper  0xD062
        } words;
    }auxCompFifoStartAddress;
 
 
    union
    {
        mUINT_32 all;
        struct
        {
            mUINT_16    auxCompFifoEndAddL;      // Aux Compare FIFO end address lower: 0xD064 
            mUINT_16    auxCompFifoEndAddH;      // Aux Compare FIFO end address upper: 0xD066
        } words;
    }auxCompFifoEndAddress;    

    union
    {
      mUINT_32 all;          
      struct
      {
        mUINT_16     auxCompFifoPtrL;            // Aux Compare FIFO pointer: 0xD068 
        mUINT_16     auxCompFifoPtrH;            // Aux Compare FIFO pointer: 0xD06A
      } bits;
    }auxCompFifoPtr;               // AUX Compare FIFO pointer

    mUINT_16    rsvd8[2];         // 0xD06C, 0xD06E

    union
    {
        mUINT_32 all;
        struct
        {
            mUINT_16    auxExtFifoStartAddL;    // Aux Extract FIFO start address lower: 0xD070 
            mUINT_16    auxExtFifoStartAddH;    // Aux Extract FIFO start address upper  0xD072
        } words;
    }auxExtFifoStartAddress;
 
 
    union
    {
        mUINT_32 all;
        struct
        {
            mUINT_16    auxExtFifoEndAddL;      // Aux Extract FIFO end address lower: 0xD074 
            mUINT_16    auxExtFifoEndAddH;      // Aux Extract FIFO end address upper: 0xD076
        } words;
    }auxExtFifoEndAddress;    

    union
    {
      mUINT_32 all;          
      struct
      {
        mUINT_16     auxExtFifoPtrL;            // Aux Extract FIFO pointer: 0xD078 
        mUINT_16     auxExtFifoPtrH;            // Aux Extract FIFO pointer: 0xD07A
      } bits;
    }auxExtFifoPtr;                // AUX Extract FIFO pointer

    mUINT_16    rsvd9[2];          // 0xD07C, 0xD07E

    union
    {
      mUINT_32 all;          
      struct
      {
        mUINT_16     hcfStartL;    // HLBA Compare FIFO Start Address Low:  0xD080 
        mUINT_16     hcfStartH;    // HLBA Compare FIFO Start Address High: 0xD082
      } bits;
    }hlbaCompFifoStartAddress;     // HLBA Compare FIFO Start Address.

    union
    {
      mUINT_32 all;          
      struct
      {
        mUINT_16     hcfEndL;      // HLBA Compare FIFO End Address Low:  0xD084 
        mUINT_16     hcfEndH;      // HLBA Compare FIFO End Address High: 0xD086
      } bits;
    }hlbaCompFifoEndAddress;       // HLBA Compare FIFO Start Address.

    union
    {
      mUINT_32 all;          
      struct
      {
        mUINT_16     hcfPtrL;      // HLBA Compare FIFO Pointer Low:  0xD088 
        mUINT_16     hcfPtrH;      // HLBA Compare FIFO Pointer High: 0xD08A
      } bits;
    }hlbaCompFifoPointer;          // HLBA Compare FIFO Pointer.

    mUINT_16    rsvd10[2];          // 0xD08C, 0xD08E

    mUINT_16    auEncDoneCnt;     // AU encoder done count: 0xD090
    mUINT_16    auDecDoneCnt;     // AU decoder done count: 0xD092
    mUINT_16    rsvd11[4];        // 0xD094, 0xD096, 0xD098, 0xD09A,
    mUINT_16    auEncRcvCnt;      // AU encoder receive count: 0xD09C
    mUINT_16    auDecRcvCnt;      // AU decoder receive count: 0xD09E

    union
    {
      mUINT_32 all;          
      struct
      {
        mUINT_16     errCntFifoStartL;    // Error Count FIFO Start Address Low:  0xD0A0 
        mUINT_16     errCntFifoStartH;    // Error Count FIFO Start Address High: 0xD0A2
      } bits;
    }errCntFifoStartAddress;     // Error Count FIFO Start Address.

    union
    {
      mUINT_32 all;          
      struct
      {
        mUINT_16     errCntFifoEndL;      // Error Count FIFO End Address Low:  0xD0A4 
        mUINT_16     errCntFifoEndH;      // Error Count FIFO End Address High: 0xD0A6
      } bits;
    }errCntFifoEndAddress;       // Error Count FIFO Start Address.

    union
    {
      mUINT_32 all;          
      struct
      {
        mUINT_16     errCntFifoPtrL;      // Error Count FIFO Pointer Low:  0xD0A8 
        mUINT_16     errCntFifoPtrH;      // Error Count FIFO Pointer High: 0xD0AA
      } bits;
    }errCntFifoPointer;          // Error Count FIFO Pointer.

    mUINT_16    rsvd12[2];          // 0xD0AC, 0xD0AE

    union
    {
        mUINT_32 all;
        struct
        {
            mUINT_16    rowIncL;    // Row increment lower: 0xD0B0 
            mUINT_16    rowIncH;    // Row increment upper  0xD0B2
        } words;
    }rowInc;     

    mUINT_16    cfDesXferCntSel0;   // Compact format xfer count sel 0: 0xD0B4
    mUINT_16    cfDesXferCntSel1;   // Compact format xfer count sel 1: 0xD0B6
    mUINT_16    cfDesColAddrSel0;   // Compact format col address sel 0: 0xD0B8
    mUINT_16    cfDesColAddrSel1;   // Compact format col address sel 1: 0xD0BA
    
    mUINT_16    rsvd13[2];          // 0xD0BC, 0xD0BE
    
    mUINT_16    afDesXferCntSel0;   // Auto format xfer count sel 0: 0xD0C0
    mUINT_16    afDesXferCntSel1;   // Auto format xfer count sel 1: 0xD0C2     
    mUINT_16    afDesColAddrSel0;   // Auto format col address sel 0: 0xD0C4
    mUINT_16    afDesColAddrSel1;   // Auto format col address sel 1: 0xD0C6
    
    union
    {
        mUINT_32 all;
        struct
        {
            mUINT_16    afDesRowAdrSel0L;    // Auto format row address sel 0 lower: 0xD0C8 
            mUINT_16    afDesRowAdrSel0H;    // Auto format row address sel 0 upper: 0xD0CA
        } words;
    }afDesRowAddrSel0; 

    union
    {
        mUINT_32 all;
        struct
        {
            mUINT_16    afDesRowAdrSel1L;    // Auto format row address sel 1 lower: 0xD0CC 
            mUINT_16    afDesRowAdrSel1H;    // Auto format row address sel 1 upper: 0xD0CE
        } words;
    }afDesRowAddrSel1; 
    
    mUINT_32     refAuxDataMask1;             //mask for word 1 of Aux data.  D0D0, D0D2
    mUINT_32     refAuxDataMask2;             //D4, D6
    mUINT_32     refAuxDataMask3;             // D8, DA
    mUINT_32     refAuxDataMask4;             // DC, DE
    
    mUINT_16    rsvd14[16];
    
    mUINT_16    corrPwrChan0;                // ECU correction for channel 0  D100
    mUINT_16    corrPwrChan1;                // ECU correction for channel 0  D102
    mUINT_16    corrPwrChan2;                // ECU correction for channel 0  D104
    mUINT_16    corrPwrChan3;                // ECU correction for channel 0  D106
    mUINT_16    corrPwrChan4;                // ECU correction for channel 0  D108
    mUINT_16    corrPwrChan5;                // ECU correction for channel 0  D10a
    mUINT_16    corrPwrChan6;                // ECU correction for channel 0  D10c
    mUINT_16    corrPwrChan7;                // ECU correction for channel 0  D10E
    mUINT_16    corrPwrChan8;                // ECU correction for channel 0  D110
    mUINT_16    corrPwrChan9;                // ECU correction for channel 0  D112
    mUINT_16    corrPwrChan10;                // ECU correction for channel 0  D114
    mUINT_16    corrPwrChan11;                // ECU correction for channel 0  D116
    mUINT_16    corrPwrChan12;                // ECU correction for channel 0  D118
    mUINT_16    corrPwrChan13;                // ECU correction for channel 0  D11A
    mUINT_16    corrPwrChan14;                // ECU correction for channel 0  D11C
    mUINT_16    corrPwrChan15;                // ECU correction for channel 0  D11E
    
    mUINT_32    auEncoderCmdFIFOStartAddr;    // FIFO start address for AU Encoder Command FIFO  D120:D122
    mUINT_16    auEncoderCmdFIFOSize;         // FIFO size D124
    mUINT_16    auEncoderCmdFIFOPopCnt;       // Number of pending cmds in AU Encoder Cmd FIFO D126
    mUINT_16    auEncoderCmdFIFOPrefetchCnt;  // Number of cmds pending prefetch   D128
    mUINT_16    auEncoderCmdFIFOFLCCnt;       // Number of au cmds pending FLC  D12A
    
    mUINT_16    rsvd15[2];
    
    mUINT_32    auEncoderCmdFIFOPushPtr;      // D130:D132
    mUINT_32    auEncoderCmdFIFOPopPtr;       // D134:D136
    mUINT_32    auEncoderCmdFIFOPrefetchPtr;  // D138:D13A
    mUINT_32    auEncoderCmdFIFOFLCPtr;       // D13C:D13E
    
    mUINT_32    auDecoderCmdFIFOStartAddr;    //D140
    //mUINT_16    rsvd16[1];
    mUINT_16    auDecoderCmdFIFOSize;         // FIFO size D144
    mUINT_16    auDecoderCmdFIFOPopCnt;       // Number of pending cmds in AU Encoder Cmd FIFO D146
    mUINT_16    auDecoderCmdFIFOPrefetchCnt;  // Number of cmds pending prefetch   D148
    mUINT_16    auDecoderCmdFIFOFLCCnt;       // Number of au cmds pending FLC  D14A
    
    mUINT_16    rsvd17[2];
    
    mUINT_32    auDecoderCmdFIFOPushPtr;      // D150:D152
    mUINT_32    auDecoderCmdFIFOPopPtr;       // D154:D156
    mUINT_32    auDecoderCmdFIFOPrefetchPtr;  // D158:D15A
    mUINT_32    auDecoderCmdFIFOFLCPtr;       // D15C:D15E
    
    mUINT_32    mqPort0FIFOStartAddr;         // D160
    mUINT_16    mqPort0FIFOSize;              // D164
    mUINT_16    mqPort0FIFOCnt;               // D166
    
    mUINT_16    rsvd18[4];
    
    mUINT_32    mqPort0FIFOPushPtr;           //D170:D172
    mUINT_32    mqPort0FIFOPopPtr;            //D174:D176
    
    mUINT_16    rsvd19[4];
    
    mUINT_32    mqPort1FIFOStartAddr;         // D180
    mUINT_16    mqPort1FIFOSize;              // D184
    mUINT_16    mqPort1FIFOCnt;               // D186
    
    mUINT_16    rsvd20[4];
    
    mUINT_32    mqPort1FIFOPushPtr;           //D190:D192
    mUINT_32    mqPort1FIFOPopPtr;            //D194:D196
    
    mUINT_16    rsvd21[20];
    
    mUINT_32    nandParameterFIFOStartAddr;    //D1C0:D1C2
    mUINT_32    nandParameterFIFOEndAddr;      //D1C4:D1C6
    mUINT_32    nandParameterFIFOPtr;          // D1C8:D1cA
    
    mUINT_16    rsvd22[282];
    
    mUINT_32    seqLUTStartAddr;              // D400:D402
    
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16    seqLUTEsize    : 2;    // Sequencer LUT Entry size 0xD404 
            mUINT_16    rsvd           : 14;    
        } bits;
    }seqLUTConfig; 
    
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16    sacRdErrID      : 4;    // Sequencer LUT Entry size 0xD406 
            mUINT_16    sacRdErrRSP     : 2; 
            mUINT_16    sacRdChkDis     : 1;
            mUINT_16    sacRdErrRSM     : 1;
            
            mUINT_16    sacWrErrID      : 4;
            mUINT_16    sacWrErrRsp     : 2;
            mUINT_16    sacWrChkDis     : 1;
            mUINT_16    sacWrErrRSM     : 1;   
        } bits;
    }seqAXIErrorControl; 
    
    mUINT_32 seqAXIReadAddr;                   //D408:D40A
    mUINT_32 seqAXIWriteAddr;                  //D40C:D40E
    
    
    
    
        
}mtNV_SEQ;   


//=======================================================================
//     [[[[ Flash Controller(FC) ]]]]
//=======================================================================
typedef union
{
    mUINT_16 all;          
    struct
    {
        mUINT_16     dev0           : 1;
        mUINT_16     dev1           : 1;
        mUINT_16     dev2           : 1;
        mUINT_16     dev3           : 1;
        mUINT_16     dev4           : 1;
        mUINT_16     dev5           : 1;
        mUINT_16     dev6           : 1;
        mUINT_16     dev7           : 1;
        mUINT_16     lt0            : 1;
        mUINT_16     lt1            : 1;
        mUINT_16     lt2            : 1;
        mUINT_16     lt3            : 1;
        mUINT_16     lt4            : 1;
        mUINT_16     lt5            : 1;
        mUINT_16     lt6            : 1;
        mUINT_16     lt7            : 1;
    } bits;
}mtNV_SEQ_TIMING_CONFIG;

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16    lunCh0          : 4;
        mUINT_16    lunCh1          : 4;
        mUINT_16    lunCh2          : 4;
        mUINT_16    lunCh3          : 4;
    } bits;
}mtNV_SEQ_LUN_CONFIG; 

typedef union
{
  mUINT_16 all;          
  struct
  {
    mUINT_16     blkBndrSelCh   : 8;     
    mUINT_16     blkBndr1Ch     : 3;     
    mUINT_16     rsvd0          : 1;     
    mUINT_16     blkBndr2Ch     : 3;     
    mUINT_16     rsvd1          : 1;     
  } bits;
}mtNV_SEQ_BLK_BDRY_INFO;        // Flash sequencer Channel block boundary information

typedef struct
{
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     flashmode       : 2;
        mUINT_16     flashType       : 2;
        mUINT_16     flashBW         : 1;   
        mUINT_16     rsvd0           : 1;   
        mUINT_16     intf_reset      : 1;
        mUINT_16     pd_en           : 1;
        mUINT_16     nfif            : 1;
        mUINT_16     clkPdEn         : 1;
        mUINT_16     extRowEn        : 1;
        mUINT_16     eceEn           : 1;
        mUINT_16     clkStopEn       : 1;
        mUINT_16     tsbMode         : 1;
        mUINT_16     fifteenCeEn     : 1;
        mUINT_16     rsvd1           : 1;   
      } bits;
    }flashIntfConfig;              // Flash interface configuration 1: 0xB600
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     dev_num         : 8;
        mUINT_16     chan_num        : 4;
        mUINT_16     en_aw           : 1;
        mUINT_16     lt_latchTiming  : 1;
        mUINT_16     rsvd            : 2;
      } bits;
    }dirIndirConfig;              // Flash direct/indirect access configuration 1: 0xB602

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     T1              : 3;
        mUINT_16     T2              : 3;
        mUINT_16     T3              : 3;
        mUINT_16     T4              : 3;
        mUINT_16     T5              : 2;
        mUINT_16     T6              : 2;
      } bits;
    }intfTimingCtrl1;              // Flash interface timing control 1: 0xB604    

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     T1              : 3;
        mUINT_16     T2              : 3;
        mUINT_16     T3              : 3;
        mUINT_16     T4              : 3;
        mUINT_16     T5              : 2;
        mUINT_16     T6              : 2;
      } bits;
    }intfTimingCtrl2;              // Flash interface timing control 2: 0xB606   
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     T1              : 3;
        mUINT_16     T2              : 3;
        mUINT_16     T3              : 3;
        mUINT_16     T4              : 3;
        mUINT_16     T5              : 2;
        mUINT_16     T6              : 2;
      } bits;
    }intfTimingCtrl3;              // Flash interface timing control 3: 0xB608
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     T1              : 3;
        mUINT_16     T2              : 3;
        mUINT_16     T3              : 3;
        mUINT_16     T4              : 3;
        mUINT_16     T5              : 4;
      } bits;
    }intfTimingCtrl4;              // Flash interface timing control 2: 0xB60A
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     CLE             : 1;
        mUINT_16     ALE             : 1;
        mUINT_16     RE              : 1;
        mUINT_16     WE              : 1;
        mUINT_16     WP              : 1;
        mUINT_16     DQS_OE          : 1;
        mUINT_16     CE              : 1;
        mUINT_16     OE_EN           : 1;
        mUINT_16     MON_CLE         : 1;
        mUINT_16     MON_ALE         : 1;
        mUINT_16     MON_RE          : 1;
        mUINT_16     MON_WE          : 1;
        mUINT_16     MON_WP          : 1;
        mUINT_16     DQS             : 1;
        mUINT_16     MON_CE          : 1;
        //mUINT_16     MON_RDYB        : 1;  
        mUINT_16     MON_DQS         : 1;  
      } bits;
    }dirAcesCtrlPort1;              // Flash direct access control port1: 0xB60C  
    
    mUINT_16 dirAcesAddrData;       // Flash direct access addr/data port: 0xB60E 
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     T7Ch0           : 6;
        mUINT_16     rsvd0           : 2;
        mUINT_16     T7Ch1           : 6;
        mUINT_16     rsvd1           : 2;
      } bits;
    }intfTimingCtrlCh0Ch1;         // Flash interface timing control Ch0/Ch1: 0xB610
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     T7Ch2           : 6;
        mUINT_16     rsvd0           : 2;
        mUINT_16     T7Ch3           : 6;
        mUINT_16     rsvd1           : 2;
      } bits;
    }intfTimingCtrlCh2Ch3;         // Flash interface timing control Ch2/Ch3: 0xB612

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     T7Ch4           : 6;
        mUINT_16     rsvd0           : 2;
        mUINT_16     T7Ch5           : 6;
        mUINT_16     rsvd1           : 2;
      } bits;
    }intfTimingCtrlCh4Ch5;         // Flash interface timing control Ch4/Ch5: 0xB614
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     T7Ch6           : 6;
        mUINT_16     rsvd0           : 2;
        mUINT_16     T7Ch7           : 6;
        mUINT_16     rsvd1           : 2;
      } bits;
    }intfTimingCtrlCh6Ch7;         // Flash interface timing control Ch6/Ch7: 0xB616
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     T7Ch8           : 6;
        mUINT_16     rsvd0           : 2;
        mUINT_16     T7Ch9           : 6;
        mUINT_16     rsvd1           : 2;
      } bits;
    }intfTimingCtrlCh8Ch9;         // Flash interface timing control Ch8/Ch9: 0xB618            
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     T7Ch10          : 6;
        mUINT_16     rsvd0           : 2;
        mUINT_16     T7Ch11          : 6;
        mUINT_16     rsvd1           : 2;
      } bits;
    }intfTimingCtrlCh10Ch11;        // Flash interface timing control Ch10/Ch11: 0xB61A            

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     T7Ch12          : 6;
        mUINT_16     rsvd0           : 2;
        mUINT_16     T7Ch13          : 6;
        mUINT_16     rsvd1           : 2;
      } bits;
    }intfTimingCtrlCh12Ch13;       // Flash interface timing control Ch12/Ch13: 0xB61C            

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     T7Ch14          : 6;
        mUINT_16     rsvd0           : 2;
        mUINT_16     T7Ch15          : 6;
        mUINT_16     rsvd1           : 2;
      } bits;
    }intfTimingCtrlCh14Ch15;       // Flash interface timing control Ch14/Ch15: 0xB61E            

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     command         : 4;
        mUINT_16     in_out          : 1;
        mUINT_16     ct              : 1;
        mUINT_16     fifo_reset      : 1;
        mUINT_16     start           : 1;
        mUINT_16     dummy_RBB       : 1;
        mUINT_16     dummy_CE        : 1;
        mUINT_16     dummy_dqsoe     : 1;
        mUINT_16     rsvd            : 3;
        mUINT_16     fifo_status     : 1;
        mUINT_16     dqsIntStr       : 1;
      } bits;
    }indirAcesConfig;              // Flash indirect access configuration: 0xB620      
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     byte0           : 8;
        mUINT_16     byte1           : 8;
      } bits;
    }indirAcesCmdPort1;              // Flash indirect access command port1: 0xB622

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     byte2           : 8;
        mUINT_16     byte3           : 8;
      } bits;
    }indirAcesCmdPort2;              // Flash indirect access command port2: 0xB624     

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     byte4           : 8;
        mUINT_16     byte5           : 8;
      } bits;
    }indirAcesCmdPort3;              // Flash indirect access command port3: 0xB626

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     byte6           : 8;
        mUINT_16     byte7           : 8;
      } bits;
    }indirAcesCmdPort4;              // Flash indirect access command port4: 0xB628 
    
    mUINT_16 indirAcesDataXferCnt;   // Flash indirect access data transfer count: 0xB62A 
    
    mtUNION_UINT_32 indirAcesDataPort;   // Flash indirect access data port: 0xB62C and 0xB62E
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     t7IndJdc        : 6;
        mUINT_16     byte5           : 10;
      } bits;
    }flashInterfaceTimingControl5;   // Flash interface timing control5: 0xB630

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     t8Seq           : 4;
        mUINT_16     t9Seq           : 4;
        mUINT_16     t8Ind           : 4;
        mUINT_16     t9Ind           : 4;
      } bits;
    }flashInterfaceTimingControl6;   // Flash interface timing control6: 0xB632

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     tcs             : 4;
        mUINT_16     revd            : 12;
      } bits;
    }flashInterfaceTimingControl7;   // Flash interface timing control6: 0xB634

    mUINT_16 rsvd1[2];               // 0xB636, 0xB638
    
    mUINT_16 seqIntrStatus;             // Flash sequencer interrupt status: 0xB63A   
    mUINT_16 seqErrorDesId;             // Flash sequencer error descriptor ID: 0xB63C

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     dummyCmd        : 1;
        mUINT_16     fifoAutoPd      : 1;
        mUINT_16     statusByteSel   : 1;
        mUINT_16     regAccessEn     : 1;
        mUINT_16     interSeqSel     : 1;
        mUINT_16     crcEn           : 1;
        mUINT_16     crcStatus       : 1;
        mUINT_16     smIdle          : 1;
        mUINT_16     errStrSel       : 4;
        mUINT_16     errStr          : 2;
        mUINT_16     rsvd            : 1;
        mUINT_16     intEn           : 1;
      } bits;
    }seqCtrl2;                        // Flash sequencer control 2: 0xB63E
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     seq_en          : 1;
        mUINT_16     seq_reset       : 1;
        mUINT_16     fail_bit        : 3;
        mUINT_16     ready_bit       : 3;
        mUINT_16     ch_sel          : 4;
        mUINT_16     str_sel         : 2;
        mUINT_16     rsvd            : 2;
      } bits;
    }seqCtrl1;                        // Flash sequencer control 1: 0xB640 
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     rbyte0          : 8;
        mUINT_16     rbyte1          : 8;
      } bits;
    }seqCmdPort1;                    // Flash sequencer command port1: 0xB642                          

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     rbyte2          : 8;
        mUINT_16     rsvd            : 8;
        //mUINT_16     rbyte3          : 8;
      } bits;
    }seqCmdPort2;                    // Flash sequencer command port2: 0xB644
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     pbyte0          : 8;
        mUINT_16     pbyte1          : 8;
      } bits;
    }seqCmdPort3;                    // Flash sequencer command port3: 0xB646 
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     ebyte0          : 8;
        mUINT_16     ebyte1          : 8;
      } bits;
    }seqCmdPort4;                    // Flash sequencer command port4: 0xB648 
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     sbyte          : 8;
        mUINT_16     abyte          : 8;
      } bits;
    }seqCmdPort5;                    // Flash sequencer command port5: 0xB64A

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     ssaByte        : 8;
        mUINT_16     rsvd           : 8;
      } bits;
    }seqCmdPort6;                    // Flash sequencer command port6: 0xB64C    
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     flash_status   : 8;
        mUINT_16     desc_id        : 8;
      } bits;
    }seqStatusPort;                 // Flash sequencer status port: 0xB64E
    
    // Flash sequencer I/F timing CH8-CH15 config: 0xB650 - 0xB65E
    mtNV_SEQ_TIMING_CONFIG seqTimingChConfigExt[m8010_SEQ_NUM_CHAN];
    // Flash sequencer I/F timing CH0-CH7 config: 0xB660 - 0xB66E
    mtNV_SEQ_TIMING_CONFIG seqTimingChConfig[m8010_SEQ_NUM_CHAN];
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     wcnt12         : 7;
        mUINT_16     rsvd           : 1;
        mUINT_16     wcnt11         : 6;
        mUINT_16     div1           : 2;
      } bits;
    }seqTimingCtrl1;           // Flash sequencer I/F timing control1: 0xB670 
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     wcnt22         : 7;
        mUINT_16     rsvd           : 1;
        mUINT_16     wcnt21         : 6;
        mUINT_16     div2           : 2;
      } bits;
    }seqTimingCtrl2;           // Flash sequencer I/F timing control2: 0xB672
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     wcnt32         : 7;
        mUINT_16     rsvd           : 1;
        mUINT_16     wcnt31         : 6;
        mUINT_16     div3           : 2;
      } bits;
    }seqTimingCtrl3;           // Flash sequencer I/F timing control3: 0xB674
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     wcnt42         : 7;
        mUINT_16     rsvd           : 1;
        mUINT_16     wcnt41         : 6;
        mUINT_16     div4           : 2;
      } bits;
    }seqTimingCtrl4;           // Flash sequencer I/F timing control4: 0xB676
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     pcnt52         : 7;
        mUINT_16     rsvd           : 1;
        mUINT_16     pcnt51         : 4;
        mUINT_16     rsvd1          : 2;
        mUINT_16     div5           : 2;
      } bits;
    }seqTimingCtrl5;           // Flash sequencer I/F timing control5: 0xB678 
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     wcnt62         : 7;
        mUINT_16     rsvd           : 1;
        mUINT_16     wcnt61         : 6;
        mUINT_16     div6           : 2;
      } bits;
    }seqTimingCtrl6;           // Flash sequencer I/F timing control6: 0xB67A
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     wcnt72         : 7;
        mUINT_16     rsvd           : 1;
        mUINT_16     wcnt71         : 6;
        mUINT_16     div7           : 2;
      } bits;
    }seqTimingCtrl7;           // Flash sequencer I/F timing control7: 0xB67C

    mUINT_16 rsvd2[1];              //0xB07E
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     pdCh0          : 1;
        mUINT_16     pdCh1          : 1;
        mUINT_16     pdCh2          : 1;
        mUINT_16     pdCh3          : 1;
        mUINT_16     pdCh4          : 1;
        mUINT_16     pdCh5          : 1;
        mUINT_16     pdCh6          : 1;
        mUINT_16     pdCh7          : 1;
        mUINT_16     extCeEnCh0     : 1;
        mUINT_16     extCeEnCh1     : 1;
        mUINT_16     extCeEnCh2     : 1;
        mUINT_16     extCeEnCh3     : 1;
        mUINT_16     extCeEnCh4     : 1;
        mUINT_16     extCeEnCh5     : 1;
        mUINT_16     extCeEnCh6     : 1;
        mUINT_16     extCeEnCh7     : 1;
      } bits;
    }seqChanEngineClkCtrl1;           // Flash Sequencer Channel Engine Clock Control1: 0xB680

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     pdCh8          : 1;
        mUINT_16     pdCh9          : 1;
        mUINT_16     pdCh10         : 1;
        mUINT_16     pdCh11         : 1;
        mUINT_16     pdCh12         : 1;
        mUINT_16     pdCh13         : 1;
        mUINT_16     pdCh14         : 1;
        mUINT_16     pdCh15         : 1;
        mUINT_16     extCeEnCh8     : 1;
        mUINT_16     extCeEnCh9     : 1;
        mUINT_16     extCeEnCh10    : 1;
        mUINT_16     extCeEnCh11    : 1;
        mUINT_16     extCeEnCh12    : 1;
        mUINT_16     extCeEnCh13    : 1;
        mUINT_16     extCeEnCh14    : 1;
        mUINT_16     extCeEnCh15    : 1;
      } bits;
    }seqChanEngineClkCtrl2;           // Flash Sequencer Channel Engine Clock Control2: 0xB682

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     sbyte1         : 8;     //used to be sbyte2
        mUINT_16     failBit        : 3;
        mUINT_16     rsvd           : 1;
        mUINT_16     readyBit       : 3;
        mUINT_16     rsvd1          : 1;
      } bits;
    }seqStatusByteCtrl1;           // Flash sequencer status byte control1: 0xB684
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     sbyte2         : 8;     
        mUINT_16     sbyte3         : 8;     
      } bits;
    }seqStasByteCtrl2;           // Flash sequencer status byte control2: 0xB686

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     failBit2       : 3;
        mUINT_16     rsvd           : 1;
        mUINT_16     readyBit2      : 3;
        mUINT_16     rsvd1          : 1;
        mUINT_16     failBit3       : 3;
        mUINT_16     rsvd2          : 1;
        mUINT_16     failBit4       : 3;
        mUINT_16     rsvd3          : 1;
      } bits;
    }seqStasByteCtrl3;           // Flash sequencer status byte control3: 0xB688
    
    mUINT_16 rsvd3[3];
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     rbyte3         : 8;     
        mUINT_16     rbyte4         : 8;     
      } bits;
    }seqCmdPort7;                // Flash sequencer command port7: 0xB690

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     rbyte5         : 8;     
        mUINT_16     rbyte6         : 8;     
      } bits;
    }seqCmdPort8;                // Flash sequencer command port8: 0xB692

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     rbyte7         : 8;     
        mUINT_16     rbyte8         : 8;     
      } bits;
    }seqCmdPort9;                // Flash sequencer command port9: 0xB694

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     pbyte2         : 8;     
        mUINT_16     pbyte3         : 8;     
      } bits;
    }seqCmdPort10;                // Flash sequencer command port10: 0xB696

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     pbyte4         : 8;     
        mUINT_16     ebyte2         : 8;     
      } bits;
    }seqCmdPort11;                // Flash sequencer command port11: 0xB698

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     pbyte5         : 8;     
        mUINT_16     rsvd           : 8;     
      } bits;
    }seqCmdPort12;                // Flash sequencer command port12: 0xB69A

    mUINT_16 rsvd4[2];
    
    // Flash sequencer CH0~15 block boundary information: 0xB6A0 - 0xB6BE
    mtNV_SEQ_BLK_BDRY_INFO seqChBlockBoundaryInfo[m8010_SEQ_NUM_CHAN*2];

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     chStr          : 16;
      } bits;
    }seqStatusPort2;                // Flash sequencer status port2: 0xB6C0

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     devStr          : 8;
        mUINT_16     rsvd            : 6;
        mUINT_16     efPStr          : 1;
        mUINT_16     efRstr          : 1;
      } bits;
    }seqStatusPort3;                // Flash sequencer status port3: 0xB6C2

    mUINT_16 rsvd5[6];              // 0xB6C4, 0xB6C6, 0xB6C8, 0xB6CA, 0xB6CC, 0xB6CE
                                     
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     rsvd0          : 2;
        mUINT_16     colMask        : 1;
        mUINT_16     rsvd1          : 2;
        mUINT_16     noDeadlockFix  : 2;
        mUINT_16     rsvd2          : 9;
      } bits;
    }efFifoClkCtrlPort;         // EF_FIFO clock control port: 0xB6D0

    mUINT_16 rsvd6[7];              // 0xB6D2, 0xB6D4, 0xB6D6, 0xB6D8, 0xB6DA, 0xB6DC, 0xB6DE

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     efFifoSel      : 4;
        mUINT_16     efFifoAdrSel   : 1;
        mUINT_16     efFifoAcsEn    : 1;
        mUINT_16     sr2pSel        : 1;
        mUINT_16     efFifoAcsSel   : 1;
        mUINT_16     rowColSel      : 1;
        mUINT_16     rsvd           : 1;
        mUINT_16     testSel        : 4;
        mUINT_16     eDir           : 1;
        mUINT_16     eDebug         : 1;
      } bits;
    }efFifoAcesConfig;         // EF_FIFO access configuration: 0xB6E0
    
    mUINT_16 efFifoAddrPort;   // EF_FIFO address port: 0xB6E2
    
    mUINT_16 efFifoDataPort1;  // EF_FIFO data port1: 0xB6E4
    
    mUINT_16 efFifoDataPort2;  // EF_FIFO data port2: 0xB6E6
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     efSramRtc      : 2;
        mUINT_16     efSramWtc      : 2;
        mUINT_16     efSramRettst   : 1;
        mUINT_16     bistChSel      : 1;
        mUINT_16     efBistFail     : 1;
        mUINT_16     efBistReady    : 1;
        mUINT_16     efFifoBistEn   : 8;
      } bits;
    }efFifoTestPort;           // EF_FIFO test port: 0xB6E8
    
    mUINT_16 efFifoDataPort3;  // EF_FIFO data port3: 0xB6EA
    mUINT_16 efFifoDataPort4;  // EF_FIFO data port3: 0xB6EC

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     disPrt         : 1;
        mUINT_16     ctlAbort       : 1;
        mUINT_16     cpuAbort2      : 1;
        mUINT_16     cpuAbort1      : 1;
        mUINT_16     resvd          : 12;
      } bits;
    }marvellDebugReg;           // Marvell Debug Register 0xB6EE
    
    mUINT_16 rsvd7[8];              // 0xB6F0, 0xB6F2, 0xB6F4, 0xB6F6, 0xB6F8, 0xB6FA, 0xB6FC , 0xB6FE

    // Flash sequencer CH0~CH15 LUN configuration: 0xB700 - 0xB707
    mtNV_SEQ_LUN_CONFIG lunConfig[4];    
                  
}mtNV_FC;

//==========================================================================
//     [[[[ Flash FCT(FCT) and SPM (Scratchpad Memory) Parity Registers ]]]]
//==========================================================================
typedef union
{
    mUINT_16 all;
    struct 
    {
        mUINT_16     rsvd0           : 1; //aesIntr         : 1;
        mUINT_16     flashIntr       : 1;
        mUINT_16     seqIntr         : 1;
        mUINT_16     rsvd1           : 13;
    } bits;
}mtFCT_INT;               // FCT interrupt

typedef struct  
{
    mtFCT_INT   fctIntrStatus;       // FC interrupt status: 0xBA00
    
    mtFCT_INT   fctIntrEnable;       // FC interrupt enable: 0xBA02

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     testBusSel      : 3;  // 000:AES 001:NAND 010:SEQ 011:FMTR 100:ECU
        mUINT_16     rsvd            : 13;
      } bits;
    }fctTestBusSelect;              // FC Test Bus Select: 0xBA04

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     seqBlkId        : 8; 
        mUINT_16     nFlashBlkId     : 8; 
      } bits;
    }nandFlashSeqRevId;              // NAND Flash and Sequencer Revision ID: 0xBA08

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     fmtBlkId        : 8; 
        mUINT_16     eccBlkId        : 8; 
      } bits;
    }eccFormatterRevId;              // ECC and Formatter Revision ID: 0xBA0A

    mUINT_16 reserved[2];            // 0xBA0C, 0xBA0E  

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     spmParOff       : 1; 
        mUINT_16     spmErrRst       : 1; 
        mUINT_16     spmNoErrRsp     : 1; 
        mUINT_16     rsvd0           : 1; 
        mUINT_16     spmErrStaSel    : 2; // 0:CPU0 1:CPU1 2:SEQ 3:revd 
        mUINT_16     rsvd1           : 2; 
        mUINT_16     spmB0ErrInj     : 1; 
        mUINT_16     spmB1ErrInj     : 1; 
        mUINT_16     spmB2ErrInj     : 1; 
        mUINT_16     spmB3ErrInj     : 1; 
        mUINT_16     rsvd2           : 4; 
      } bits;
    }spmParityControl;              // SPM Parity Control: 0xBA10

    mUINT_16 spmParityErrAddress;   // SPM Parity Error Address: 0xBA12

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     spmErrByte      : 4; 
        mUINT_16     rsvd            : 12; 
      } bits;
    }spmParityErrByte;              // SPM Parity Error Byte: 0xBA14

}mtNV_FCT;


//=======================================================================
//     [[[[ Error Correction Unit (ECU) ]]]]
//=======================================================================
typedef struct                                              
{
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     ecSoftReset             : 1;
        mUINT_16     rsvd                    : 3;
        mUINT_16     eciTestMuxSel           : 9;
        mUINT_16     rsvd1                   : 3;
      } bits;
    }ctrlConfig1;           // ECU control and config1: 0xB200
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     rsvd                    : 1;
        mUINT_16     stopOnMpEccErr          : 1;
        mUINT_16     rsvd1                   : 1;
        mUINT_16     stopOnUncorr            : 1;
        mUINT_16     stopOnOvrLmt            : 1;
        mUINT_16     stopOnMCrcErr           : 1;
        mUINT_16     stopOnAUXMismatch       : 1;
        mUINT_16     stopOnErase             : 1;
        mUINT_16     stopOnDppErr            : 1;
        mUINT_16     stopOn16Au              : 1;
        mUINT_16     stopOnRaidDppErr        : 1;
        mUINT_16     stopOnRaidIDErr         : 1;
        mUINT_16     rsvd2                   : 4;
        
      } bits;
    }ctrlConfig2;           // ECU control and config2: 0xB202
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     rsvd                    : 3;
        mUINT_16     sendOnUnCorr            : 1;
        mUINT_16     sendOnOvrLimit          : 1;
        mUINT_16     sendOnMCrcErr           : 1;
        mUINT_16     sendOnAuxMisMatch       : 1;
        mUINT_16     sendOnErase             : 1;
        mUINT_16     sendOnDppErr            : 1;
        mUINT_16     sendOn16Au              : 1;
        mUINT_16     sendOnRaidDppErr        : 1;
        mUINT_16     sendOnRaidIdErr         : 1;
        mUINT_16     rsvd1                   : 4;
      } bits;
    }ctrlConfig3;             // ECU control and config3: 0xB204
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     longModeEn              : 1;
        mUINT_16     erasePageDetOnly        : 1;
        mUINT_16     lbaRcvrMode             : 1;
        mUINT_16     metaRdOnly              : 1;
        mUINT_16     metaRdSkip              : 1;
        mUINT_16     eccDecBypassEn          : 1;
        mUINT_16     rsvd                    : 10;
      } bits;
    }ctrlConfig4;             // ECU control and config4: 0xB206

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     fit2PhyPage             : 1;
        mUINT_16     dsEn                    : 1;
        mUINT_16     eccInvMode              : 1;
        mUINT_16     mCrcInvMode             : 1;
        mUINT_16     metaEccEn               : 1;
        mUINT_16     rsvd                    : 2;
        mUINT_16     exConfEn                : 1;
        mUINT_16     manEraseTrshEn          : 1;
        mUINT_16     rsvd1                   : 2;
        mUINT_16     ddrMcPortConf           : 1;
        mUINT_16     rsvd2                   : 1;
        mUINT_16     sendStatusMode          : 1;
        mUINT_16     rsvd3                   : 1;
        mUINT_16     eccByteOrder            : 1;
      } bits;
    }ctrlConfig5;             // ECU control and config5: 0xB208

    
    mUINT_16 rsvd[3];     
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     ecuMPEccEn              : 1;
        mUINT_16     ecuHLBAChkEn            : 1;
        mUINT_16     ecuHLBAMode             : 2;
        mUINT_16     rsvd                    : 12;
        
      } bits;
    }ctrlConfig7;             // ECU control and config7: 0xB210

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     hostSectorSize          : 14;
        mUINT_16     rsvd                    : 2;
      } bits;
    }ctrlConfig8;             // ECU control and config8: 0xB212

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     ecu2HostRatio           : 5;
        mUINT_16     rsvd                    : 11;
      } bits;
    }ctrlConfig9;             // ECU control and config9: 0xB214
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     metaSize                : 9;
        mUINT_16     rsvd                    : 7;
      } bits;
    }ctrlConfig10;             // ECU control and config10: 0xB216    
    
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     longModeSize            : 11;
        mUINT_16     rsvd                    : 5;
      } bits;
    }ctrlConfig11;             // ECU control and config11: 0xB218    

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     aesClkEn                : 1;
        mUINT_16     aesMRE1LbEn             : 1;
        mUINT_16     aesMRE2LbEn             : 1;
        mUINT_16     rsvd                    : 13;
      } bits;
    }ctrlConfig12;             // ECU control and config11: 0xB21A
        
    mUINT_16 rsvd1[2];          
   
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     codeWordsPerAU          : 3;
        mUINT_16     rsvd                    : 1;
        mUINT_16     twoLevelEn              : 1;
        mUINT_16     rsvd1                   : 11;
      } bits;
    }ecuConfig1;           // ECU encode status report: 0xB220

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     phyPageSize   : 15;
        mUINT_16     rsvd          : 1;
      } bits;
    }ecuConfig2;           // ECU  0xB222
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     metaT          : 4;
        mUINT_16     metaThrshld    : 4;
        mUINT_16     rsvd           : 8;
      } bits;
    }ecuConfig3;           // ECU  0xB224
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     tWeak          : 8;
        mUINT_16     tStrong        : 8;
      } bits;
    }ecuConfig4;           // ECU  0xB226
 
 
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     thrshdWeak     : 8;
        mUINT_16     thrshdStrong   : 8;
      } bits;
    }ecuConfig5;           // ECU  0xB228
    
    mUINT_16 rsvd2[2];          
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     eraseThrshdWeak   : 8;
        mUINT_16     rsvd              : 8;
      } bits;
    }ecuConfig6;           // ECU  0xB22E

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     exCWPerAU         : 3;
        mUINT_16     rsvd              : 1;
        mUINT_16     exTwoLevelEn      : 1;
        mUINT_16     rsvd1             : 11;        
      } bits;
    }ecuExtendedConfig1;           // ECU  0xB230
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     exPhyPageSize     : 15;
        mUINT_16     rsvd              : 1;
      } bits;
    }ecuExtendedConfig2;           // ECU  0xB232
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     exMetaT           : 4;
        mUINT_16     exMetaThshld      : 4;
        mUINT_16     rsvd              : 8;
      } bits;
    }ecuExtendedConfig3;           // ECU  0xB234
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     exTWeak           : 8;
        mUINT_16     exTStrong         : 8;
      } bits;
    }ecuExtendedConfig4;           // ECU  0xB236
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     exThrshdWeak      : 8;
        mUINT_16     exThrshdStrong    : 8;
      } bits;
    }ecuExtendedConfig5;           // ECU  0xB238
    
    mUINT_16 rsvd3[2];
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     exEraseThshdWeak  : 8;
        mUINT_16     rsvd              : 8;
      } bits;
    }ecuExtendedConfig6;           // ECU  0xB23E


    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     ecuEncResume          : 1;
        mUINT_16     mpeccErrBefifo        : 1;
        mUINT_16     mpeccErrDDRMc         : 1;
        mUINT_16     encDPPErr             : 1;
        mUINT_16     encDsDPPErr           : 1;
        mUINT_16     rsvd                  : 2;
        mUINT_16     raidEncDPPErr         : 1;
        mUINT_16     raidEncInvalidIdErr   : 1;
        mUINT_16     rsvd1                 : 6;
        mUINT_16     confErr               : 1;
      } bits;
    }ecuEncodeStat0;           // ECU  0xB240

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     mpeccErrCodeWordCount      : 5;
        mUINT_16     rsvd                       : 3;
        mUINT_16     mpeccSyndPtr               : 4;
        mUINT_16     rsvd1                      : 4;
      } bits;
    }ecuEncodeStat1;           // ECU  0xB242
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     mpeccErrCodeWordNum1  : 5;
        mUINT_16     rsvd                  : 3;
        mUINT_16     mpeccErrCodeWordNum2  : 5;
        mUINT_16     rsvd1                 : 3;
      } bits;
    }ecuMPECCErrStatus1;           // ECU  0xB244

    mUINT_16 ecuMPECCErrStat2;       // ECU  0xB246
    
    mUINT_16 rsvd4[4];    
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     ecuDecResume          : 1;
        mUINT_16     curAuUnCorr           : 1;
        mUINT_16     curAuOvrLimit         : 1;
        mUINT_16     curAuMetaMCrcErr      : 1;
        mUINT_16     curAuMCrc             : 1;
        mUINT_16     curAuAuxMisMatch      : 1;
        mUINT_16     curAuErase            : 1;
        mUINT_16     curAu16               : 1;
        mUINT_16     curEcuStrgSydErr      : 1;
        mUINT_16     rsvd                  : 1;
        mUINT_16     curRaidDecDPPErr      : 1;
        mUINT_16     curRaidDecInvalidID   : 1;
        mUINT_16     curDecBufDPPErr       : 1;
        mUINT_16     curErrBufDPPErr       : 1;
        mUINT_16     rsvd1                 : 2;
      } bits;
    }ecuDecoderStat0;           // ECU  0xB250
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     cwXUnclean            : 1;
        mUINT_16     cwXUnCorr             : 1;
        mUINT_16     cwXWeakOvrLimit       : 1;
        mUINT_16     cwXStrongOvrLimit     : 1;
        mUINT_16     rsvd                  : 4;
        mUINT_16     strongDecUsed         : 1;
        mUINT_16     cwStrongUnCorr        : 1;
        mUINT_16     curWordStrongOverLimit: 1;
        mUINT_16     rsvd1                 : 5;
      } bits;
    }ecuDecoderStat1;           // ECU  0xB252
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     auDecodeStatPtr       : 4;
        mUINT_16     rsvd                  : 4;
        mUINT_16     codeWordDecStatPtr    : 4;
        mUINT_16     rsvd1                 : 4;
      } bits;
    }ecuDecoderStat2;           // ECU  0xB254
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     rsvd                  : 1;
        mUINT_16     auUnCorr              : 1;
        mUINT_16     auOvrLimit            : 1;
        mUINT_16     auMetaMCrcErr         : 1;
        mUINT_16     auMCrcErr             : 1;
        mUINT_16     auAuxMisMatch         : 1;
        mUINT_16     auErase               : 1;
        mUINT_16     au16                  : 1;
        mUINT_16     auStrgSyndErr         : 1;
        mUINT_16     rsvd1                 : 1;
        mUINT_16     raidDecDPPErr         : 1;
        mUINT_16     raidDecInvalidID      : 1;
        mUINT_16     decBufDPPErr          : 1;
        mUINT_16     errBufDPPErr          : 1;
        mUINT_16     rsvd2                 : 2;
      } bits;
    }ecuDecoderStat3;           // ECU  0xB256
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     cwXCorrCount          : 8;
        mUINT_16     rsvd                  : 8;
      } bits;
    }ecuDecoderStat4;           // ECU  0xB258
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     auCorrCount           : 10;
        mUINT_16     rsvd                  : 6;
      } bits;
    }ecuDecoderStat5;           // ECU  0xB25A

    
    mUINT_16 ecuDecoderStat6;   // ECU decode status report 6: 0xB25C
    
    mUINT_16 ecuDecoderStat7;   // ECU decode status report 7: 0xB25E
    
    mUINT_16 ecuDecoderStat8;   // ECU decode status report 8: 0xB260
    
    mUINT_16 ecuDecoderStat9;   // ECU decode status report 9: 0xB262
    
    mUINT_16 ecuDecoderStat10;   // ECU decode status report 9: 0xB264
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     vrefCntMSB            : 1;
        mUINT_16     rsvd                  : 15;
      } bits;
    }ecuDecoderStat11;           // ECU  0xB266
    
    mUINT_16 ecuDecoderStat12;   // ECU decode status report 9: 0xB268
    
    mUINT_16 ecuDecoderStat13;   // ECU decode status report 9: 0xB26A
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     cwXCorrCount0to1      : 8;
        mUINT_16     cwXCorrCount1to0      : 8;
      } bits;
    }ecuDecoderStat14;           // ECU  0xB26C
    
    

    mUINT_16 rsvd5[17];    
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     ecuBufCpuEn              : 1;
        mUINT_16     ecuBufCpuAdderAutoIncEn  : 1;
        mUINT_16     ecuBufPwdnEn             : 1;
        mUINT_16     rsvd                     : 5;
        mUINT_16     ecuBufCpuSel             : 6;
        mUINT_16     rsvd1                    : 2;
      } bits;
    }ecuBufferCpuAccess0;           // ECU  0xB290
    
    mUINT_16 ecuBufferCpuAccess1;           // ECU  0xB292
    
    mUINT_16 ecuBufferCpuAccess2;           // ECU  0xB294
    
    mUINT_16 ecuBufferCpuAccess3;           // ECU  0xB296
    
    mUINT_16 ecuBufferCpuAccess4;           // ECU  0xB298
    
    mUINT_16 ecuBufferCpuAccess5;           // ECU  0xB29a
    
    mUINT_16 rsvd6[4];    

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     bistReset               : 1;
        mUINT_16     bistRowColSwitch        : 1;
        mUINT_16     bistRunStop             : 1;
        mUINT_16     bistStatusEn            : 1;
        mUINT_16     bistStatusClk           : 1;
        mUINT_16     rsvd                    : 11;
      } bits;
    }ecuBufferBistControlStat1;           // ECU decode status report 4: 0xB2a4
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     bistModeUeFifo0Buf      : 1;
        mUINT_16     rsvd                    : 1;
        mUINT_16     bistModeEncBuf          : 1;
        mUINT_16     bistModeDecBuf          : 1;
        mUINT_16     bistModeErrBuf          : 1;
        mUINT_16     bistModeRaidBuf         : 1;
        mUINT_16     rsvd1                   : 10;
      } bits;
    }ecuBufferBistControlStat2;           // ECU decode status report 4: 0xB2a6
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     bistFinishBeFIFO        : 1;
        mUINT_16     rsvd                    : 1;
        mUINT_16     bistFinishEncBuf        : 1;
        mUINT_16     bistFinishDecBuf        : 1;
        mUINT_16     bistFinishErrBuf        : 1;
        mUINT_16     bistFinishRaidBuf       : 1;
        mUINT_16     rsvd1                   : 2;
        mUINT_16     bistErrorBeFIFO         : 1;
        mUINT_16     rsvd2                   : 1;
        mUINT_16     bistErrorEncBuf         : 1;
        mUINT_16     bistErrorDecBuf         : 1;
        mUINT_16     bistErrorErrBuf         : 1;
        mUINT_16     bistErrRaidBuf          : 1;
        mUINT_16     rsvd3                   : 2;
      } bits;
    }ecuBufferBistControlStat3;           // ECU decode status report 4: 0xB2a8
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     bistAnyBistFailBeFIFO   : 1;
        mUINT_16     rsvd                    : 2;
        mUINT_16     bistAnyBistFailDecBuf   : 1;
        mUINT_16     bistAnyBistFailErrBuf   : 1;
        mUINT_16     bistAnyBistFailRaidBuf  : 1;
        mUINT_16     rsvd1                   : 2;
        mUINT_16     bistFailBeFifoEnc       : 1;
        mUINT_16     bistFailBeFIFODec       : 1;
        mUINT_16     rsvd2                   : 2;
        mUINT_16     bistFailEncBuf          : 1;
        mUINT_16     rsvd3                   : 3;
      } bits;
    }ecuBufferBistControlStat4;           // ECU decode status report 4: 0xB2aa
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     bistFailDecBuf0         : 1;
        mUINT_16     bistFailDecBuf1         : 1;
        mUINT_16     bistFailDecBuf2         : 1;
        mUINT_16     bistFailDecBuf3         : 1;
        mUINT_16     bistFailDecBuf4         : 1;
        mUINT_16     bistFailDecBuf5         : 1;
        mUINT_16     bistFailDecBuf6         : 1;
        mUINT_16     bistFailDecBuf7         : 1;
        mUINT_16     bistFailErrBuf0         : 1;
        mUINT_16     bistFailErrBuf1         : 1;
        mUINT_16     bistFailErrBuf2         : 1;
        mUINT_16     bistFailErrBuf3         : 1;
        mUINT_16     bistFailErrBuf4         : 1;
        mUINT_16     bistFailErrBuf5         : 1;
        mUINT_16     bistFailErrBuf6         : 1;
        mUINT_16     bistFailErrBuf7         : 1;
      } bits;
    }ecuBufferBistControlStat5;           // ECU decode status report 4: 0xB2ac
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     bistFailRaidBuf0         : 1;
        mUINT_16     bistFailRaidBuf1         : 1;
        mUINT_16     bistFailRaidBuf2         : 1;
        mUINT_16     bistFailRaidBuf3         : 1;
        mUINT_16     bistFailRaidBuf4         : 1;
        mUINT_16     bistFailRaidBuf5         : 1;
        mUINT_16     bistFailRaidBuf6         : 1;
        mUINT_16     bistFailRaidBuf7         : 1;
        mUINT_16     bistFailRaidBuf8         : 1;
        mUINT_16     bistFailRaidBuf9         : 1;
        mUINT_16     bistFailRaidBuf10        : 1;
        mUINT_16     bistFailRaidBuf11        : 1;
        mUINT_16     rsvd                     : 4;
      } bits;
    }ecuBufferBistControlStat6;           // ECU decode status report 4: 0xB2ae
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     bistStatusOutBeFIFO      : 1;
        mUINT_16     rsvd                     : 1;
        mUINT_16     bistStatusOutEncBuf      : 1;
        mUINT_16     bistStatusOutDecBuf      : 1;
        mUINT_16     bistStatusOutErrBuf      : 1;
        mUINT_16     bistStatusOutRaidBuf     : 1;
        mUINT_16     rsvd1                    :10;
      } bits;
    }ecuBufferBistControlStat7;           // ECU decode status report 4: 0xB2b0
    
    mUINT_16 rsvd7[1];    
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     beFIFOEncWTC             : 2;
        mUINT_16     beFIFOEncRTC             : 2;
        mUINT_16     beFIFODecWTC             : 2;
        mUINT_16     beFIFODecRTC             : 2;
        mUINT_16     rsvd                     : 8;
      } bits;
    }ecuBufferConfig0;           // ECU decode status report 4: 0xB2b4
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     encBufWTC                : 2;
        mUINT_16     encBufRTC                : 2;
        mUINT_16     rsvd                     : 12;
      } bits;
    }ecuBufferConfig1;           // ECU decode status report 4: 0xB2b6
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     decBuf0WTC                : 2;
        mUINT_16     decBuf0RTC                : 2;
        mUINT_16     decBuf1WTC                : 2;
        mUINT_16     decBuf1RTC                : 2;
        mUINT_16     decBuf2WTC                : 2;
        mUINT_16     decBuf2RTC                : 2;
        mUINT_16     decBuf3WTC                : 2;
        mUINT_16     decBuf3RTC                : 2;
      } bits;
    }ecuBufferConfig2;           // ECU decode status report 4: 0xB2b8
   
   union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     decBuf4WTC                : 2;
        mUINT_16     decBuf4RTC                : 2;
        mUINT_16     decBuf5WTC                : 2;
        mUINT_16     decBuf5RTC                : 2;
        mUINT_16     decBuf6WTC                : 2;
        mUINT_16     decBuf6RTC                : 2;
        mUINT_16     decBuf7WTC                : 2;
        mUINT_16     decBuf7RTC                : 2;
      } bits;
    }ecuBufferConfig3;           // ECU decode status report 4: 0xB2bA
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     errBuf0WTC                : 2;
        mUINT_16     errBuf0RTC                : 2;
        mUINT_16     errBuf1WTC                : 2;
        mUINT_16     errBuf1RTC                : 2;
        mUINT_16     errBuf2WTC                : 2;
        mUINT_16     errBuf2RTC                : 2;
        mUINT_16     errBuf3WTC                : 2;
        mUINT_16     errBuf3RTC                : 2;
      } bits;
    }ecuBufferConfig4;           // ECU decode status report 4: 0xB2bC
   
   union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     errBuf4WTC                : 2;
        mUINT_16     errBuf4RTC                : 2;
        mUINT_16     errBuf5WTC                : 2;
        mUINT_16     errBuf5RTC                : 2;
        mUINT_16     errBuf6WTC                : 2;
        mUINT_16     errBuf6RTC                : 2;
        mUINT_16     errBuf7WTC                : 2;
        mUINT_16     errBuf7RTC                : 2;
      } bits;
    }ecuBufferConfig5;           // ECU decode status report 4: 0xB2bE
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     raidBuf0WTC                : 2;
        mUINT_16     raidBuf0RTC                : 2;
        mUINT_16     raidBuf1WTC                : 2;
        mUINT_16     raidBuf1RTC                : 2;
        mUINT_16     raidBuf2WTC                : 2;
        mUINT_16     raidBuf2RTC                : 2;
        mUINT_16     raidBuf3WTC                : 2;
        mUINT_16     raidBuf3RTC                : 2;
      } bits;
    }ecuBufferConfig6;           // ECU decode status report 4: 0xB2C0
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     raidBuf4WTC                : 2;
        mUINT_16     raidBuf4RTC                : 2;
        mUINT_16     raidBuf5WTC                : 2;
        mUINT_16     raidBuf5RTC                : 2;
        mUINT_16     raidBuf6WTC                : 2;
        mUINT_16     raidBuf6RTC                : 2;
        mUINT_16     raidBuf7WTC                : 2;
        mUINT_16     raidBuf7RTC                : 2;
      } bits;
    }ecuBufferConfig7;           // ECU decode status report 4: 0xB2C2
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     raidBuf8WTC                : 2;
        mUINT_16     raidBuf8RTC                : 2;
        mUINT_16     raidBuf9WTC                : 2;
        mUINT_16     raidBuf9RTC                : 2;
        mUINT_16     raidBuf10WTC               : 2;
        mUINT_16     raidBuf10RTC               : 2;
        mUINT_16     raidBuf11WTC               : 2;
        mUINT_16     raidBuf11RTC               : 2;
      } bits;
    }ecuBufferConfig8;           // ECU decode status report 4: 0xB2C4
    
    mUINT_16 rsvd8[5];    
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     eccRaidEn                  : 1;
        mUINT_16     eccRaidSRST                : 1;
        mUINT_16     rsvd                       : 14;
      } bits;
    }ecuRaidControlAndStat0;           // ECU decode status report 4: 0xB2D0
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     raidActiveBufEnc           : 12;
        mUINT_16     rsvd                       : 4;
      } bits;
    }ecuRaidControlAndStat1;           // ECU decode status report 4: 0xB2D2
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     raidActiveBufDec           : 12;
        mUINT_16     rsvd                       : 4;
      } bits;
    }ecuRaidControlAndStat2;           // ECU decode status report 4: 0xB2D4
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     raidDPPErrEnc              : 1;
        mUINT_16     raidIDErrEnc               : 1;
        mUINT_16     raidCurBufAll0Enc          : 1;
        mUINT_16     rsvd                       : 5;
        mUINT_16     raidDPPErrDec              : 1;
        mUINT_16     raidIDErrDec               : 1;
        mUINT_16     raidCurBufAll0Dec          : 1;
        mUINT_16     rsvd1                      : 5;
      } bits;
    }ecuRaidControlAndStat3;           // ECU decode status report 4: 0xB2D6
    
    mUINT_16 rsvd9[3];     
    
    mUINT_16 ecuRaidMonitorRaid1;   // ECU decode status report 5: 0xB2DE
    
    mUINT_16 rsvd10[8];     
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     monitorPtrMisc             : 8;
        mUINT_16     rsvd                       : 8;
      } bits;
    }ecuMonitorMisc0;           // ECU decode status report 4: 0xB2F0
   
    mUINT_16 ecuMonitorMisc1;   // ECU decode status report 5: 0xB2F2
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     monitorPtrEnc              : 8;
        mUINT_16     rsvd                       : 8;
      } bits;
    }ecuMonitorEncode0;           // ECU decode status report 4: 0xB2F4
    
    mUINT_16 ecuMonitorEncode1;   // ECU decode status report 5: 0xB2F6
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     monitorPtrDec              : 8;
        mUINT_16     rsvd                       : 8;
      } bits;
    }ecuMonitorDecode0;           // ECU decode status report 4: 0xB2F8
    
    mUINT_16 ecuMonitorDecode1;   // ECU decode status report 5: 0xB2FA
    
    mUINT_16 rsvd11[1];    
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     socRev                     : 8;
        mUINT_16     ecuRev                     : 8;
      } bits;
    }ecuID;           // ECU decode status report 4: 0xB2FE  
        
}mtNV_ECU;                                                                                


//=======================================================================
//     [[[[ Flash AES(AES) ]]]]
//=======================================================================
#if (VG_REV_2_0 != mENABLE)
typedef struct                                              
{
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     aesSoftReset            : 1;
        mUINT_16     rsvd0                   : 3;
        mUINT_16     entropyEnable           : 1;
        mUINT_16     rsvd1                   : 11;
      } bits;
    }aesCtrl;           // AES control: 0xB800
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     decryptErr              : 1;
        mUINT_16     encryptErr              : 1;
        mUINT_16     rsvd0                   : 2;
        mUINT_16     entropyRdy              : 1;
        mUINT_16     rsvd1                   : 3;
        mUINT_16     aesDisable              : 1;
        mUINT_16     uartDisable             : 1;
        mUINT_16     faDisable               : 1;
        mUINT_16     rsvd2                   : 5;
      } bits;
    }aesStatus;           // AES status: 0xB802
    
    mUINT_16 rsvd0[3];

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     aesAccNum               : 4;
        mUINT_16     rsvd0                   : 12;
      } bits;
    }aesRdWrReqNum;       // AES read/write request number: 0xB80A
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     aesAccGrant             : 4;
        mUINT_16     aesAccRst               : 1;
        mUINT_16     rsvd0                   : 11;
      } bits;
    }aesAccessAuth;       // AES access authorization: 0xB80C

    mUINT_16 rsvd1;

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     aesMode                 : 2;
        mUINT_16     rsvd0                   : 1;
        mUINT_16     entropySrc              : 2;
        mUINT_16     aesNkMode               : 1;
        mUINT_16     rsvd1                   : 2;
        mUINT_16     aesErrStop              : 1;
        mUINT_16     cryptErrMsk             : 1;
        mUINT_16     rsvd2                   : 6;
      } bits;
    }aesConfig;       // AES config: 0xB810
    
    mUINT_16 entropyNum;            // Entropy number: 0xB812
    
    mUINT_16 encryptKeyL;          // Encryption key low: 0xB814
    
    mUINT_16 encryptKeyH;          // Encryption key high: 0xB816
    
    mUINT_16 decryptKeyL;          // Decryption key low: 0xB818

    mUINT_16 decryptKeyH;          // Decryption key high: 0xB81A
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     encKeyPtr               : 2;
        mUINT_16     rsvd0                   : 5;
        mUINT_16     encPtrInc               : 1;
        mUINT_16     decKeyPtr               : 2;
        mUINT_16     rsvd1                   : 5;
        mUINT_16     decPtrInc               : 1;
      } bits;
    }encDecPtr;                   // Encryption/decryption pointer: 0xB81C    
    
    mUINT_16 rsvd2;
    
    mUINT_16 encryptionIv;       // Encryption IV: 0xB820
    
    mUINT_16 rsvd3;
    
    mUINT_16 decryptionIv;       // Decryption IV: 0xB824
    
}mtNV_AES;
#else   // (VG_REV_2_0 == mENABLE)
typedef struct                                              
{
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     aes_srst               :1;    // bit0   
        mUINT_16     rsvd0                  :3;    // bit3:1 
        mUINT_16     entropy_en             :1;    // bit4   
        mUINT_16     enc_self_chk_en        :1;    // bit5   
        mUINT_16     dec_self_chk_en        :1;    // bit6   
        mUINT_16     rsvd1                  :9;    // bit15:7 
      } bits;
    }aesCtrl;           // AES control: 0xB800 (aes_ctrl)
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     rsvd0                  :4; // bit3:0    RSVD
        mUINT_16     entropy_rdy            :1; // bit4      ENTROPY_RDY
        mUINT_16     rsvd1                  :3; // bit7:5    RSVD
        mUINT_16     aes_disable            :1; // bit8      AES_DISABLE
        mUINT_16     uart_disable           :1; // bit9      UART_DISABLE
        mUINT_16     fa_disable             :1; // bit10     FA_DISABLE
        mUINT_16     rsvd2                  :1; // bit11     RSVD
        mUINT_16     enc_self_chk_done      :1; // bit12     ENC_SELF_CHK_DONE
        mUINT_16     dec_self_chk_done      :1; // bit13     DEC_SELF_CHK_DONE
        mUINT_16     enc_self_chk_fail      :1; // bit14     Encryptor Self Check Fail.
        mUINT_16     dec_self_chk_fail      :1; // bit15     Decryptor Self Check Fail  
      } bits;
    }aesStatus;           // AES status: 0xB802 (aes_status)
    
    union
    {
      mUINT_16 all;          
      struct
      {
       
        mUINT_16     pp_en                  :1; // bit0 Post Processor Enable.
        mUINT_16     rng_slow_osc_en        :1; // bit1 RNG Slow (Noisy) Osc Enable.
        mUINT_16     rng_fast_osc_en        :1; // bit2 RNG Fast (Free-Running) OSC Enable
        mUINT_16     rng_pu_bias            :1; // bit3 Power Up Bias.
        mUINT_16     rng_rstn               :1; // bit4 RNG Reset. 0: RNG reset; 1: Normal operation.
        mUINT_16     rng_clk_sel            :1; // bit5 RNG Clean (Fast) Clock Select. 0: rab_clk; 1: RNG Fast OSC output.
        mUINT_16     pp_bypass              :1; // bit6 Post Processor Bypass.
        mUINT_16     rsvd                   :9; // bit15:7  
      } bits;
    }OscEBGControl;         // AES OSC EBG Control: 0xB804 (aes_osc_ctl)

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     rng_slow_div_val       :8; // bit7:0 RNG Slow Osc Divider Value. Minimum value is 2. Recommend setting to greater than 30
        mUINT_16     ds_ratio               :8; // bit15:8 Down sampling ratio in the EBG downsampling circuit, which further downsamples the RNG slow (noisy) oscillator output. This downsampling is done outside of the RNG macro. Minimum value is 2.
      } bits;
    }OscEBGControl2;        // AES OSC EBG Control 2: 0xB806 (aes_osc_ctl2)

    mUINT_16 rsvd0;         // 0xB808

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     aes_acc_num            : 4;   // bit3:0. When the firmware reads the register, the hardware latches in an access grant value (a free-running 4-bit counter).
        mUINT_16     rsvd                   : 12;  // bit15:4
      } bits;
    }aesRdWrReqNum;       // AES read/write request number: 0xB80A (aes_rwreq)
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     aes_acc_grant          : 4;    // bit3:0. AES Access Grant. When the firmware writes to this field with AES_ACC_NUM(RB80Ah [3:0]) (that the firmware has read) and AES_ACC_RST (RB80Ch [4]) = 0, the hardware enables the firmware to perform Read/Write access to the AES registers where access request is required.
        mUINT_16     aes_acc_rst            : 1;    // bit4. AES Access Reset. After the firmware completes Read/Write operations to the protected AES registers, it writes this bit with a 1 to disable the register Read/Write access grant logic (one shot). The firmware needs a new access request sequence before writing or reading to the protected AES registers.
        mUINT_16     rsvd                   : 11;   // bit15:5
      } bits;
    }aesAccessAuth;       // AES access authorization: 0xB80C (aes_rwgrant)

    mUINT_16 rsvd1;

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16    aes_mode                :3;     // bit2:0.  000: Normal encryption and/or decryption
                                                    //          001: Bypass 
                                                    //          010: Media Re-encryption Program
                                                    //          011: Media Re-encryption Loopback
                                                    //          100: Self-checking mode  
                                                    //          Other: Reserved

        mUINT_16    entropy_src             :2;     // bit4:3.  Entropy Source Selection. 
                                                    //          00: Source 1 (random number generator).
                                                    //          01: Source 2 (ebit latched by rab_clk).
                                                    //          10: Source 3 (ebg_clk latched by rab_clk).
                                                    //          11: Source 4 (reserved).
        
        mUINT_16    aes_nk_mode             :2;     // bit6:5.  Key Size Select. 00: 128-bit key. 01: 256-bit key. others : Reserved
        mUINT_16    rsvd                    :3;     // bit9:7 
        mUINT_16    aes_blk_mode            :2;     // bit11:10 AES Block Cipher Mode. 00: (ECB); 01: (CBC); 10: (CTR); 11: XTS(IEEE P1619).
        mUINT_16    aes_iv_mode             :2;     // bit13:12 AES Initial Vector Mode. 00: Raw IV; 01: Swap IV; 10: XOR IV; 11: Reserved
        mUINT_16    rsvd1                   :2;     // bit15:14 Reserved.
      } bits;
    }aesConfig;                     // AES config: 0xB810 (aes_cfg)
    
    mUINT_16 entropyNum;            // AES Entropy number:      0xB812 (aes_entropy)
    mUINT_16 encryptKeyL;           // AES Encryption key low:  0xB814 (aes_enc_keyl)	
    mUINT_16 encryptKeyH;           // AES Encryption key high: 0xB816 (aes_enc_keyh)	
    mUINT_16 decryptKeyL;           // AES Decryption key low:  0xB818 (aes_dec_keyl)	
    mUINT_16 decryptKeyH;           // AES Decryption key high: 0xB81A (aes_dec_keyh)	
    
    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     enc_key_ptr            :3; // bit2:0   Encryption Key Pointer.
        mUINT_16     enc_key_ptr_reset      :1; // bit3     Encryption Key Pointer Reset.
        mUINT_16     enc_iv_ptr_reset       :1; // bit4     Encryption IV Pointer Reset.
        mUINT_16     rsvd                   :2; // bit6:5   Reserved.
        mUINT_16     enc_ptr_inc            :1; // bit7     Encryption Key Auto Increment. When set, ENC_KEY_PTR auto increments after each Read/Write to both ENCRYPT_KEY_L and ENCRYPT_KEY_H.
        mUINT_16     dec_key_ptr            :3; // bit10:8  DEC_KEY_PTR R/W 0h Decryption Key Pointer.
        mUINT_16     dec_key_ptr_reset      :1; // bit11    Decryption Key Pointer Reset. When set, this bit resets Decryption Key Pointer.
        mUINT_16     dec_iv_ptr_reset       :1; // bit12    Decryption IV Pointer Reset. When set, this bit resets Decryption IV Pointer.
        mUINT_16     rsvd2                  :2; // bit14:13 Reserved.
        mUINT_16     dec_ptr_inc            :1; // bit15    Decryption Key Auto Increment. When set the DEC_KEY_PTR (RB81Ch [9:8]) auto increments after each Read/Write to DECRYPT_KEY_L(RB818h [15:0]) and DECRYPT_KEY_H (RB81Ah [15:0]).
      } bits;
    }encDecPtr;                     // Encryption/decryption pointer: 0xB81C (aes_enc_dec_ptr)   
    
    mUINT_16 rsvd2;                 // 0xB81E
    mUINT_16 encryptionIv;          // Encryption IV: 0xB820 (aes_enc_nonce)
    mUINT_16 rsvd3;
    mUINT_16 decryptionIv;          // Decryption IV: 0xB824 (aes_dec_nonce)
    
    mUINT_16 XTSEncryptKeyL;        // 0xB826 (aes_xts_enc_keyl)
    mUINT_16 XTSEncryptKeyH;	    // 0xB828 (aes_xts_enc_keyh)
    mUINT_16 XTSDecryptKeyL;	    // 0xB82A (aes_xts_dec_keyl)
    mUINT_16 XTSDecryptKeyH;        // 0xB82C (aes_xts_dec_keyh)

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     xts_enc_key_ptr        :3; // bit2:0   XTS Encrypt Key Pointer
        mUINT_16     xts_enc_key_ptr_reset  :1; // bit3     XTS Encryption Key Pointer Reset.
        mUINT_16     rsvd                   :4; // bit7:4   Reserved.
        mUINT_16     xts_dec_key_ptr        :3; // bit10:8  XTS Decrypt Key Pointer.
        mUINT_16     xts_dec_key_ptr_reset  :1; // bit11    XTS Decryption Key Pointer Reset.
        mUINT_16     rsvd1                  :4; // bit15:12 Reserved.
      } bits;
    }XTSEncDecPtr;                  // 0xB82E XTS Encryption/Decryption Pointer


    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     otp1_pgm               :1; // bit0     OTP1 PGM Signal Setting.
        mUINT_16     otp1_wprot             :1; // bit1     OTP1 WPROT Signal Setting.
        mUINT_16     otp1_csb               :1; // bit2     OTP1 CSB Signal Setting.
        mUINT_16     otp1_rst_b             :1; // bit3     OTP1_RST_B OTP1 Reset B Signal Setting.
        mUINT_16     otp1_sclk              :1; // bit4     OTP1 Signal Clock (Sclk) Setting.
        mUINT_16     rsvd                   :3; // bit7:5   Reserved.
        mUINT_16     otp2_pgm               :1; // bit8     OTP2 PGM Signal Setting.
        mUINT_16     otp2_wprot             :1; // bit9     OTP2 WPROT Signal Setting.
        mUINT_16     otp2_csb               :1; // bit10    OTP2 Csb Signal Setting.
        mUINT_16     otp2_rst_b             :1; // bit11    OTP2 Reset B Signal Setting.
        mUINT_16     otp2_sclk              :1; // bit12    OTP2 Signal Clock (Sclk) Setting.
        mUINT_16     fa_enable              :1; // bit13    FA Enable. When set to 1, the hardware enables external port access (overrides OTP1 setting), but blocks out read/write to the OTP1/OTP2 circuit, which effectively disables access to 256-bit S/N (stored at OTP2), which protects the KEK. When reset to 0, the OTP1 setting determines whether to enable or disable the external port access.
        mUINT_16     otp_rptr_rst           :1; // bit14    OTP1/OTP2 Read Pointer Reset. 0: Normal operation. 1: Reset OTP1 read pointer to 1h. Reset OTP2 read pointer to 1h.
        mUINT_16     rsvd1                  :1; // bit15    Reserved.
      } bits;
    } OTPControl1;                  // 0xB830 OTP Control 1 (aes_otp_ctl)  


    mUINT_16    OTPReadPort1;       // 0xB832   OTP Read Port 1 (aes_otp_read)
    mUINT_16    OTPReadPort2;       // 0xB834   OTP Read Port 2 (aes_otp_read2)

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     otp3_pgm               :1; // bit0     OTP3 PGM Signal Setting.
        mUINT_16     otp3_wprot             :1; // bit1     OTP3 WPROT Signal Setting.
        mUINT_16     otp3_csb               :1; // bit2     OTP3 CSB Signal Setting.
        mUINT_16     otp3_rst_b             :1; // bit3     OTP3 Reset B Signal Setting.
        mUINT_16     otp3_sclk              :1; // bit4     OTP3 Signal Clock (Sclk) Setting.
        mUINT_16     rsvd                   :11;// bit15:5  Reserved.
      } bits;
    } OTPControl2;                  // 0xB836   OTP Control 2


    mUINT_16    OTPReadPort3;       // 0xB838   OTP Read Port 3
    mUINT_16    RSVD4[3];           // 0xB83A, ... 0xB83E.

    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     ext_key_ptr            :4; // bit3:0   Extended Key Pointer.
        mUINT_16     rsvd                   :4; // bit7:4   Reserved.
        mUINT_16     key_16set_en           :1; // bit8     Key 16 Mode Enable. 0: Hardware support 1 set of key; 1: Hardware support 16 sets of keys
        mUINT_16     cpu_acc_par_en         :1; // bit9     CPU Access KeyRAM Parity Enable. 0: KeyRAM parity is generated by hardware; 1: KeyRAM parity is written by firmware
        mUINT_16     rsvd1                  :2; // bit11:10 Reserved.
        mUINT_16     cpu_acc_par            :4; // bit15:12 CPU Access KeyRAM Parity
      } bits;
    } KeyRAMControl;                // 0xB840   Key RAM Control


    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     bist_fail              :4; // bit3:0   BIST Failure for KeyRAM. 1h: KeyRAM 1 (ENC Key); 2h: KeyRAM2 (DEC Key); 4h: KeyRAM3 (ENC XTS Key); 8h: KeyRAM4 (DEC XTS Key)
        mUINT_16     bist_finish            :1; // bit4     BIST Finished for KeyRAM
        mUINT_16     bist_error             :1; // bit5     Error During Diagnostic Mode for KeyRAM. This can be cleared by BistRunStop.
        mUINT_16     bist_any_bist_fail     :1; // bit6     KeyRAM Memory Bank Failure During BIST.
        mUINT_16     biststatus_out         :1; // bit7     BistStatus Output.
        mUINT_16     rsvd                   :2; // bit9:8   Reserved.
        mUINT_16     bist_reset             :1; // bit10    Firmware Reset BIST Logic.
        mUINT_16     bist_row_col_switch    :1; // bit11    Row Colum Switch. 0: {Column, Row}; 1: {Row, Column}
        mUINT_16     bist_run_stop          :1; // bit12    BIST Run Stop. Diagonstic mode enable. 0: Normal Mode. 1: Diagnostic Mode. 
        mUINT_16     biststatus_en          :1; // bit13    BIST Status Enable.
        mUINT_16     biststatus_clk         :1; // bit14    BIST Status Clock.
        mUINT_16     bist_mode              :1; // bit15    BIST Mode.
      } bits;
    } KeyRAMBIST;                   // 0xB842   Key RAM BIST


    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     keyram0_rtc            :2; // bit1:0   KeyRAM0 (ENC Key) Read Timing Control.
        mUINT_16     keyram0_wtc            :2; // bit3:2   KeyRAM0 (ENC Key) Write Timing Control.
        mUINT_16     keyram1_rtc            :2; // bit5:4   KeyRAM1 (DEC Key) Read Timing Control.
        mUINT_16     keyram1_wtc            :2; // bit7:6   KeyRAM1 (DEC Key) Write Timing Control.
        mUINT_16     keyram2_rtc            :2; // bit9:8   KeyRAM2 (ENC XTS Key) Read Timing Control.
        mUINT_16     keyram2_wtc            :2; // bit11:10 KeyRAM2 (ENC XTS Key) Write Timing Control.
        mUINT_16     keyram3_rtc            :2; // bit13:12 KeyRAM3 (DEC XTS Key) Read Timing Control.
        mUINT_16     keyram3_wtc            :2; // bit15:14 KeyRAM3 (DEC XTS Key) Write Timing Control.
      } bits;
    } KeyRAMConfig1;                // 0xB844   Key RAM Configuration 1


    union
    {
      mUINT_16 all;          
      struct
      {
        mUINT_16     keyram0_pdwn           :1; // bit0     KeyRAM0 Power Down Mode.
        mUINT_16     keyram1_pdwn           :1; // bit1     KeyRAM1 Power Down Mode.
        mUINT_16     keyram2_pdwn           :1; // bit2     KeyRAM2 Power Down Mode.
        mUINT_16     keyram3_pdwn           :1; // bit3     KeyRAM3 Power Down Mode
        mUINT_16     rsvd                   :12;// bit15:4  Reserved.
      } bits;
    } KeyRAMConfig2;                // 0xB846   Key RAM Configuration 2
 }mtNV_AES;
#endif  // End of #if (VG_REV_2_0 != mENABLE)

#endif // 
