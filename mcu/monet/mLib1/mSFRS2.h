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

#ifndef     _mSFRS2_H_INC
   #define  _mSFRS2_H_INC

#include "mGLOBALS.h"
#include "mREGS.h"     

#ifdef      EXTERN
   #undef   EXTERN
#endif

#ifdef      INSTANTIATE_SFRS2
   #define  EXTERN
#else
   #define  EXTERN extern
#endif

//#SYMGEN_OMIT
//=======================================================================
//     [[[[ Test Pin IO Select ]]]]
//=======================================================================
typedef union
{
        mUINT_16 all;
        struct
        {
            mUINT_16 b0      : 1;
            mUINT_16 b1      : 1;
            mUINT_16 b2      : 1;
            mUINT_16 b3      : 1;

            mUINT_16 b4      : 1;
            mUINT_16 b5      : 1;
            mUINT_16 b6      : 1;
            mUINT_16 b7      : 1;

            mUINT_16 b8      : 1;
            mUINT_16 b9      : 1;
            mUINT_16 b10     : 1;
            mUINT_16 b11     : 1;

            mUINT_16 b12     : 1;
            mUINT_16 b13     : 1;
            mUINT_16 b14     : 1;
            mUINT_16 b15     : 1;
        } bits;
} mtTESTIO;

typedef struct
{
    struct
    {
        mUINT_16 test7_0sel          : 5;       // Test Output control 0 - RA820
        mUINT_16 rsvd75              : 3;
        mUINT_16 test8sel            : 4;
        mUINT_16 test9sel            : 4;

        mUINT_16 test10sel           : 4;       // Test Output Control 1 - RA822
        mUINT_16 test11sel           : 4;
        mUINT_16 test12sel           : 4;
        mUINT_16 test13sel           : 4;

        mUINT_16 test14sel           : 4;       // Test Output Control 2 - RA824        
        mUINT_16 test15sel           : 4;
        mUINT_16 test16sel           : 4;
        mUINT_16 rsvd15_12           : 4;

        mUINT_16 vcsmSIsel           : 1;        // Test Output control 3 - RA826
        mUINT_16 preampSIsel         : 1;
        mUINT_16 pwmOutSel           : 1;
        mUINT_16 rsvd_4_3            : 2;
        mUINT_16 bistStatus          : 2;
        mUINT_16 rsvd_11_7           : 5;
        mUINT_16 cpuMonitor          : 3;
        mUINT_16 chanMode            : 1;

        mUINT_16 f_dOutSel           : 4;        // Test Output control 4 - RA828
        mUINT_16 f_clkOutSel         : 4;
        mUINT_16 txOutSel            : 4;
        mUINT_16 rxOutSel            : 4;

        mUINT_16 jt_di_sel           : 1;        // Test Output control 5 - RA82A
        mUINT_16 jt_do_sel           : 1;
        mUINT_16 rsvd7_2             : 6;
        mUINT_16 nrz_mon_cntl        : 2;
        mUINT_16 rsvd11_10           : 2;
        mUINT_16 iddq_test           : 1;
        mUINT_16 rsvd_b13            : 1;
        mUINT_16 MXP1InSel           : 2;
    } testOutputCntl;          // Test Output Control 0-5    RA820-RA82A
    
    struct
    {
        mUINT_16 vcoBufSply			:1;		// TBG_A VCO Clock Buffer Supply
        mUINT_16 loadCap       		:3;		// TBG_A Load Capacitor Select
        mUINT_16 vr1V8				:2;		// TBG_A Regulator for 2V5 to 1V8
        mUINT_16 intSel       		:2;		// TBG_A Interpolator Bias Current Select
        mUINT_16 vddCtrl   			:2;		// TBG_A VDD Supply Control
        mUINT_16 vcoCtrl   			:2;		// TBG_A VCO Supply Control
        mUINT_16 rsvd_12_15			:4;
    } TBGAcontrol2;					// RA82C: TBG_A Control 2


    struct
    {
        mUINT_16 vcoBufSply			:1;		// TBG_B VCO Clock Buffer Supply
        mUINT_16 loadCap       		:3;		// TBG_B Load Capacitor Select
        mUINT_16 vr1V8				:2;		// TBG_B Regulator for 2V5 to 1V8
        mUINT_16 intSel       		:2;		// TBG_B Interpolator Bias Current Select
        mUINT_16 vddCtrl   			:2;		// TBG_B VDD Supply Control
        mUINT_16 vcoCtrl   			:2;		// TBG_B VCO Supply Control
        mUINT_16 rsvd_12_15			:4;
    } TBGBcontrol2;					// RA82E: TBG_B Control 2 

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 sataTBGunlockStatus	: 1;	// SATA TBG unlock Status
            mUINT_16 rsvd_1				: 1;	
            mUINT_16 tbgBunlockStatus   : 1;	// TBG_B unlock Status
            mUINT_16 tbgAunlockStatus   : 1;	// TBG_A unlock Status
            mUINT_16 rsvd_4_15          : 12;
        } bits;
    } TBGLockStatus;				// RA830: TBG Lock Status

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 sataTBGLockChkEn	: 1;	// SATA TBG Lock Check Enable
            mUINT_16 rsvd_1				: 1;
            mUINT_16 tbgBLockCheckEn    : 1;	// TBG_B Lock Check Enable	
            mUINT_16 tbgALockCheckEn    : 1;	// TBG_A Lock Check Enable	
            mUINT_16 rsvd_4_15          : 12;
        } bits;
    } TBGlockCheckEn;				            // RA832: TBG unlock Check Enable


    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 setmTmxTbgDivSel	: 3;	// SETM TMX Clock TBG Divider Select
                                                // 000: always high, 001: div by 1, 010: div by 2..
            mUINT_16 rsvd_1				: 1;
            mUINT_16 setmTmxTbgSel      : 1;	// SETM TMX Clock TBG Select
            mUINT_16 setmTmxClkDis      : 1;	// SETM TMX Clock Disable
            mUINT_16 setmTmxClkSel      : 1;	// SETM TMX Clock Select
            mUINT_16 rsvd_7_15          : 9;
        } bits;
    } clkDiv5;						// RA834: Clock Divider 5

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 xmTbgDivSel        : 3;	// XM Clock TBG Divider Select
            mUINT_16 rsvd_1				: 1;
            mUINT_16 xmTbgSel           : 1;	// XM Clock TBG Select
            mUINT_16 xmClkDis           : 1;	// XM Clock Disable
            mUINT_16 xmClkSel           : 1;	// XM Clock Select
            mUINT_16 rsvd_7_15          : 9;
        } bits;
    } clkDiv6;						// RA836: Clock Divider 6
    
    struct
    {
        mUINT_16 tbga_ssc_freq_div  : 15;
        mUINT_16 tbgA_ssc_mode      : 1;
    } TBGAcontrol30;				    // RA838: TBG_A Control 3
    
    mUINT_16    revsion_no_3;           // RA83A
    
    struct
    {
        mUINT_16 tbga_ssc_freq_div  : 15;
        mUINT_16 tbgA_ssc_mode      : 1;
    } TBGBcontrol30;				    // RA83C: TBG_B Control 3
    
    struct
    {
        mUINT_16 tbga_ssc_range     : 14;
        mUINT_16 tbgA_ssc_gain2X    : 1;
        mUINT_16 tbgA_ssc_reset_ext : 1;
    } TBGAcontrol31;				    // RA83E: TBG_A Control 3

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 dsramWtc			: 2;	// dsram write timing control
            mUINT_16 rsvd_2_3           : 2;
            mUINT_16 dsramRtc           : 2;    // dsram read timing control
            mUINT_16 rsvd_6_7           : 2;
            mUINT_16 isramWtc           : 2;    // isram write timing control
            mUINT_16 rsvd_10_11         : 2;
            mUINT_16 isramRtc           : 2;    // isram read timing control
            mUINT_16 rsvd_14_15         : 2;
        } bits;
    } sramCfg1;						// RA840: Internal SRAM Speed Configuration 1

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 romh_rtc_ref       : 2;	// CPU 0 ROM Read Timing Reference
            mUINT_16 romh_rtc           : 2;	// CPU 0 ROM Read Timing Control
            mUINT_16 bpm_rtc			: 2;	// HCPU BPM Read Timing Control
            mUINT_16 bpm_wtc			: 2;	// HCPU BPM Write Timing Control
            mUINT_16 roms_rtc_ref       : 2;	// ROMS Read Timing Reference
            mUINT_16 roms_rtc           : 2;	// ROMS Read Timing Control
            mUINT_16 bpm_rtc_c1			: 2;	// SCPU BPM Read Timing Control
            mUINT_16 bpm_wtc_c1			: 2;	// SCPU BPM Write Timing Control
        } bits;
    } sramCfg2;						// RA842: Internal SRAM Speed Configuration 2

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 test0dir    : 1;
            mUINT_16 test1dir    : 1;
            mUINT_16 test2dir    : 1;
            mUINT_16 test3dir    : 1;
            mUINT_16 test4dir    : 1;
            mUINT_16 test5dir    : 1;
            mUINT_16 test6dir    : 1;
            mUINT_16 test7dir    : 1;
                
            mUINT_16 test8dir    : 1;
            mUINT_16 test9dir    : 1;
            mUINT_16 test10dir   : 1;
            mUINT_16 test11dir   : 1;
            mUINT_16 test12dir   : 1;
            mUINT_16 test13dir   : 1;
            mUINT_16 test14dir   : 1;
            mUINT_16 test15dir   : 1;
        } bits;
    } ioControl;					// RA844: Test Pin I/O Control
        

    mtTESTIO    testLatch;              // 0xa846
    mtTESTIO    testIn;                 // 0xa848
    mtTESTIO    testOut;                // 0xa84a

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 rsvd_2_3	: 4;
            mUINT_16 txOutput   : 1;	// TX Output
            mUINT_16 rxOutput   : 1;	// RX Output
            mUINT_16 txOutputEn : 1;	// TX Output Enable
            mUINT_16 rxOutputEn : 1;	// RX Output Enable
            mUINT_16 uartDis    : 1;	// UART Disable
            mUINT_16 rsvd_9_15  : 7;
        } bits;
    } ioControlExt;					// RA84C: Test Pin I/O Control Extended
        
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 rsvd_0_3		: 4;
            mUINT_16 UART_TX_in		: 1;	// UART TX Input
            mUINT_16 UART_RX_in		: 1;	// UART RX Input 
            mUINT_16 UART_TX_latch	: 1;	// UART TX Latched
            mUINT_16 UART_RX_latch	: 1;	// UART RX Latched
            mUINT_16 rsvd_8_15		: 8;
        } bits;
    } testIOext;					// RA84E: Test Pin I/O Extended

    mtTESTIO        testOut1;               // RA850
    mUINT_16        testOeExt;              // RA852
    mUINT_16        testOutExt;             // RA854
    mUINT_16        testInExt;              // RA856
    mUINT_16        testLatchExt;           // RA858


    struct
    {
        mUINT_16 sscRange			:14;	// TBG_B SSC Range Selection
        mUINT_16 sscGain2x       	:1;		// TBG_B SSC Dithering Amplitude
        mUINT_16 sscReset			:1;		// TBG_B SSC External Reset
    } TBGBcontrol4;					// RA85A: TBG_B Control 4


    mUINT_16        rsvd_A85C_A85E[2];      // RA85C - RA85E


    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 cpu0BmHdcIntStpclrEn	: 1;	// CPU0 BM Interrupt Step Clear Enable
            mUINT_16 cpu0FlashIntStpclrEn   : 1;	// CPU0 Flash Controller Interrupt Step Clear Enable
            mUINT_16 cpu0SataIntStpclrEn    : 1;	// CPU0 SATA Interrupt Step Clear Enable
            mUINT_16 cpu0Tmr0IntStpclrEn    : 1;	// CPU0 Timer0 Interrupt Step Clear Enable
            mUINT_16 cpu0Tmr1IntStpclrEn    : 1;	// CPU0 Timer1 Interrupt Step Clear Enable
            mUINT_16 cpu0Tmr2IntStpclrEn    : 1;	// CPU0 Timer2 Interrupt Step Clear Enable
            mUINT_16 cpu0UartRxIntStpclrEn  : 1;	// CPU0 Uart Rx Interrupt Step Clear Enable
            mUINT_16 cpu0CommRxIntStpclrEn  : 1;	// CPU0 Comm Rx Interrupt Step Clear Enable
            mUINT_16 cpu0Tmr3IntStpclrEn    : 1;	// CPU0 Timer3 Interrupt Step Clear Enable
            mUINT_16 cpu0Tmr4IntStpclrEn    : 1;	// CPU0 Timer4 Interrupt Step Clear Enable
            mUINT_16 rsvd_10_11             : 2;
            mUINT_16 cpu0IpcWrIntStpclrEn   : 1;	// CPU0 IPC Write Interrupt Step Clear Enable
            mUINT_16 cpu0IpcRdIntStpclrEn   : 1;	// CPU0 IPC Read Interrupt Step Clear Enable
            mUINT_16 cpu0TestPinIntStpclrEn : 1;	// CPU0 Test Pin 16 Interrupt Step Clear Enable
            mUINT_16 rsvd_15                : 1;
        } bits;
    } stepdownCntl0;				// RA860: Step Down Control 0

        
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 rabClkNrmlDivSel       : 2;	// RAB Clock Normal Dividor Select
            mUINT_16 rsvd_2_3               : 2;		
            mUINT_16 rabClkStpDwnDivSel     : 2;	// RAB Clock Step Down Divisor Select
            mUINT_16 rsvd_6_7               : 2;
            mUINT_16 rabClkStpDwnEn         : 1;	// RAB Clock Step Down Enable
            mUINT_16 cpuIntSrcEn            : 2;	// CPU Interrupt Source Enable
            mUINT_16 rsvd_11_12_13          : 3;
            mUINT_16 cpu1rabClkStpDwnStat   : 1;	// CPU1 RAB Clock Step Down Status
            mUINT_16 cpu0rabClkStpDwnStat   : 1;	// CPU0 RAB Clock Step Down Status
        } bits;
    } stepdownCntl1;				// RA862: Step Down Control 1

        
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 cpu0ClkNrmlDivSel      : 2;	// CPU0 Clock Normal Divisor Select
            mUINT_16 rsvd_2_3               : 2;
            mUINT_16 cpu0ClkStpDwnDivSel    : 2;	// CPU0 Clock Step Down Divisor Select
            mUINT_16 rsvd_6_7               : 2;
            mUINT_16 cpu0ClkStpDwnEn        : 1;	// CPU0 Clock Step Down Enable
            mUINT_16 rsvd_9_14              : 6;
            mUINT_16 cpu0ClkStpDwnStat      : 1;	// CPU0 Clock Step Down Status
        } bits;
    } stepdownCntl2;				// RA864: Step Down Control 2
        
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 cpu1ClkNrmlDivSel      : 2;	// CPU1 Clock Normal Divisor Select
            mUINT_16 rsvd_2_3               : 2;
            mUINT_16 cpu1ClkStpDwnDivSel    : 2;	// CPU1 Clock Step Down Divisor Select
            mUINT_16 rsvd_6_7               : 2;
            mUINT_16 cpu1ClkStpDwnEn        : 1;	// CPU1 Clock Step Down Enable
            mUINT_16 rsvd_9_14              : 6;
            mUINT_16 cpu1ClkStpDwnStat      : 1;	// CPU1 Clock Step Down Status
        } bits;
    } stepdownCntl3;				// RA866: Step Down Control 3

        
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 ETMclkNormalDivSel     : 2;
            mUINT_16 rsvd0                  : 2;
            mUINT_16 ETMclkStepDnDivSel     : 2;
            mUINT_16 rsvd1                  : 2;
            mUINT_16 ETMclkStepDnEn         : 1;
            mUINT_16 cpuIntSrcEn            : 2;
            mUINT_16 rsvd2                  : 3;
            mUINT_16 cpu1ETMclkStepDnStat   : 1;
            mUINT_16 cpu0ETMclkStepDnStat   : 1;
        } bits;
    } stepdownCntl4;				// RA868: Step Down Control 4 - Not defined in VG1

        
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 cpu1BmHdcIntStpclrEn	: 1;	// CPU1 BM Interrupt Step Clear Enable
            mUINT_16 cpu1FlashIntStpclrEn   : 1;	// CPU1 Flash Controller Interrupt Step Clear Enable
            mUINT_16 cpu1SataIntStpclrEn    : 1;	// CPU1 SATA Interrupt Step Clear Enable
            mUINT_16 cpu1Tmr0IntStpclrEn    : 1;	// CPU1 Timer0 Interrupt Step Clear Enable
            mUINT_16 cpu1Tmr1IntStpclrEn    : 1;	// CPU1 Timer1 Interrupt Step Clear Enable
            mUINT_16 cpu1Tmr2IntStpclrEn    : 1;	// CPU1 Timer2 Interrupt Step Clear Enable
            mUINT_16 cpu1UartRxIntStpclrEn  : 1;	// CPU1 Uart Rx Interrupt Step Clear Enable
            mUINT_16 cpu1CommRxIntStpclrEn  : 1;	// CPU1 Comm Rx Interrupt Step Clear Enable
            mUINT_16 cpu1Tmr3IntStpclrEn    : 1;	// CPU1 Timer3 Interrupt Step Clear Enable
            mUINT_16 cpu1Tmr4IntStpclrEn    : 1;	// CPU1 Timer4 Interrupt Step Clear Enable
            mUINT_16 rsvd_10_11             : 2;
            mUINT_16 cpu1IpcWrIntStpclrEn   : 1;	// CPU1 IPC Write Interrupt Step Clear Enable
            mUINT_16 cpu1IpcRdIntStpclrEn   : 1;	// CPU1 IPC Read Interrupt Step Clear Enable
            mUINT_16 cpu1TestPinIntStpclrEn : 1;	// CPU1 Test Pin 16 Interrupt Step Clear Enable
            mUINT_16 rsvd_15                : 1;
        } bits;
    } stepdownCntl5;				// RA86A: Step Down Control 5

        
    mUINT_16         rsvd_A86C_A86E[2];		// 0A86C-0xA86E

    mUINT_16         ringOscCntl;			// 0xA870 Oscillator Control Register

    #if (VG_REV_2_0 == mENABLE)
    mUINT_16         rsvd_A872_A874[2];		// 0xA872-0xA874
    
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfData6				: 8;	
            mUINT_16 nfData4				: 8;	
        } bits;
    } nandPadCtrlCh4Ch6;				// RA876: NAND CH4/Ch6 Pad control

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfData5				: 8;	
            mUINT_16 nfCtrl2				: 8;	
        } bits;
    } nandPadCtrlCh2Ch5;				// RA878: NAND CH2/Ch5 Pad control
    
    mUINT_16         rsvd_A87A_A87E[3];		// 0xA87A-0xA87E

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfCtrl3				: 8;	
            mUINT_16 nfCtrl1				: 8;	
        } bits;
    } nandPadCtrlCh1Ch3;				// RA880: NAND CH1/Ch3 Pad control
        
    #else
    mUINT_16         rsvd_A872_A880[8];		// 0xA872-0xA880
    #endif

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 ch0Buf2xEn				: 1;	// Channel 0WE/RE Strength
            mUINT_16 ch1Buf2xEn				: 1;	// Channel 1WE/RE Strength
            mUINT_16 ch2Buf2xEn				: 1;	// Channel 2WE/RE Strength
            mUINT_16 ch3Buf2xEn				: 1;	// Channel 3WE/RE Strength
            mUINT_16 ch4Buf2xEn				: 1;	// Channel 4WE/RE Strength
            mUINT_16 ch5Buf2xEn				: 1;	// Channel 5WE/RE Strength
            mUINT_16 ch6Buf2xEn				: 1;	// Channel 6WE/RE Strength
            mUINT_16 ch7Buf2xEn				: 1;	// Channel 7WE/RE Strength
            mUINT_16 ch8Buf2xEn				: 1;	// Channel 8WE/RE Strength
            mUINT_16 ch9Buf2xEn				: 1;	// Channel 9WE/RE Strength
            mUINT_16 rsvd_10_15             : 6;
        } bits;
    } NandPadControl;				// RA882: NAND Flash Pad BUF2X Control



    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfCalProc				: 1;	// NAND Flash Calibration Process
            mUINT_16 nfCalEn				: 1;	// NAND Flash Calibration Enable
            mUINT_16 nfCalInd				: 1;	// NAND Flash Calibration Indicator
            mUINT_16 rsvd_3					: 1;	
            mUINT_16 nfCalZn				: 4;	// NAND Flash NMOS Impedance Setting
            mUINT_16 nfCalZp				: 4;	// NAND Flash PMOS Impedance Setting
            mUINT_16 rsvd_12_15				: 4;	
        } bits;
    } NandPadCalib;					// RA884: NAND Flash Pad Calibration

    #if (VG_REV_2_0 == mENABLE)
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfCtrl0				: 8;	
            mUINT_16 nfCtrl4				: 8;	
        } bits;
    } nandPadCtrlCh0Ch4;				// RA886: NAND CH0/Ch4 Pad control
    #else
    mUINT_16         nfControlDriveStrength0;  //0xa886
    #endif
    mUINT_16         rsvdA888_A88E[0x4];  // 0xa888-0xa90c

  #if (VG_REV_2_0 == mENABLE)
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfCtrl5				: 8;	
            mUINT_16 nfCtrl6				: 8;	
        } bits;
    } nandPadCtrlCh5Ch6;				// RA890: NAND CH5/Ch6 Pad control
    
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfCtrl7				: 8;	
            mUINT_16 rsvd   				: 8;	
        } bits;
    } nandPadCtrlCh7;				// RA892: NAND CH7 Pad control      
  #else  
    mUINT_16         nfControlDriveStrength1;  //0xa890
    mUINT_16         nfControlDriveStrength2;  //0xa892
  #endif
    
    #if (VG_REV_2_0 == mENABLE)
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfData0				: 8;	
            mUINT_16 nfData1				: 8;	            	
        } bits;
    } nandPadCtrlCh0Ch1;				// RA894: NAND CH0/CH1 Pad control       
    #else  
    mUINT_16         nfDataDriveStrength0;     //0xa894
    #endif

  #if (VG_REV_2_0 == mENABLE)
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfData2				: 8;	
            mUINT_16 nfData3				: 8;
        } bits;
    } nandPadCtrlCh2Ch3;				// RA896: NAND CH2/CH3 Pad control  
    
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfData7				: 8;	
            mUINT_16 rsvd   				: 8;	
        } bits;
    } nandPadDataCh7;				// RA898: NAND CH7 Pad control        
  #else  
    mUINT_16         nfDataDriveStrength1;     //0xa896
    mUINT_16         nfDataDriveStrength2;     //0xa898
  #endif

    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 sfPinZn				: 3;	// Serial Flash Pin ZN
            mUINT_16 rsvd_3					: 1;
            mUINT_16 sfPinZp				: 3;	// Serial Flash Pin ZP
            mUINT_16 rsvd_7					: 1;
            mUINT_16 jtagPinZn				: 3;	// JTAG Pin ZN
            mUINT_16 rsvd_11				: 1;
            mUINT_16 jtagPinZp				: 3;	// JTAG Pin ZP
            mUINT_16 rsvd_15				: 1;
        } bits;
    } nfMiscDriveStrength1;			// RA89A: NF Misc Drive Strength 1


    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 testPinZn				: 3;	// Test Pin ZN
            mUINT_16 rsvd_3					: 1;
            mUINT_16 testPinZp				: 3;	// Test Pin ZP
            mUINT_16 rsvd_7					: 1;
            mUINT_16 uartPinZn				: 3;	// UART Pin ZN
            mUINT_16 rsvd_11				: 1;
            mUINT_16 uartPinZp				: 3;	// UART Pin ZP
            mUINT_16 rsvd_15				: 1;
        } bits;
    } nfMiscDriveStrength2;			// RA89C: NF Misc Drive Strength 2


    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfPinPD				: 1;	// NAND Flash Pin Power Down
            mUINT_16 nfV18En				: 1;	// NAND Flash Pad V18 Enable
            mUINT_16 rsvd_2_15				: 14;
        } bits;
    } pdbControl;					// RA89E: PDB Control


    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfCE0Zp				: 4;	// NAND ZP Drive Strength for Ch.0's CE Pin 1,2,3,4
            mUINT_16 nfCE0Zn				: 4;	// NAND ZN Drive Strength for Ch.0's CE Pin 1,2,3,4
            mUINT_16 nfCE1Zp				: 4;	// NAND ZP Drive Strength for Ch.1's CE Pin 1,2,3,4
            mUINT_16 nfCE1Zn				: 4;	// NAND ZN Drive Strength for Ch.1's CE Pin 1,2,3,4
        } bits;
    } nfCeDrStrength01;				// RA8A0: NF CE Drive Strength Ch.0-1


    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfCE2Zp				: 4;	// NAND ZP Drive Strength for Ch.2's CE Pin 1,2,3,4
            mUINT_16 nfCE2Zn				: 4;	// NAND ZN Drive Strength for Ch.2's CE Pin 1,2,3,4
            mUINT_16 nfCE3Zp				: 4;	// NAND ZP Drive Strength for Ch.3's CE Pin 1,2,3,4
            mUINT_16 nfCE3Zn				: 4;	// NAND ZN Drive Strength for Ch.3's CE Pin 1,2,3,4
        } bits;
    } nfCeDrStrength23;				// RA8A2: NF CE Drive Strength Ch.2-3


    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfCE4Zp				: 4;	// NAND ZP Drive Strength for Ch.4's CE Pin 1,2,3,4
            mUINT_16 nfCE4Zn				: 4;	// NAND ZN Drive Strength for Ch.4's CE Pin 1,2,3,4
            mUINT_16 nfCE5Zp				: 4;	// NAND ZP Drive Strength for Ch.5's CE Pin 1,2,3,4
            mUINT_16 nfCE5Zn				: 4;	// NAND ZN Drive Strength for Ch.5's CE Pin 1,2,3,4
        } bits;
    } nfCeDrStrength45;				// RA8A4: NF CE Drive Strength Ch.4-5


    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfCE6Zp				: 4;	// NAND ZP Drive Strength for Ch.6's CE Pin 1,2,3,4
            mUINT_16 nfCE6Zn				: 4;	// NAND ZN Drive Strength for Ch.6's CE Pin 1,2,3,4
            mUINT_16 nfCE7Zp				: 4;	// NAND ZP Drive Strength for Ch.7's CE Pin 1,2,3,4
            mUINT_16 nfCE7Zn				: 4;	// NAND ZN Drive Strength for Ch.7's CE Pin 1,2,3,4
        } bits;
    } nfCeDrStrength67;				// RA8A6: NF CE Drive Strength Ch.6-7


    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 nfCE8Zp				: 4;	// NAND ZP Drive Strength for Ch.8's CE Pin 1,2,3,4
            mUINT_16 nfCE8Zn				: 4;	// NAND ZN Drive Strength for Ch.8's CE Pin 1,2,3,4
            mUINT_16 nfCE9Zp				: 4;	// NAND ZP Drive Strength for Ch.9's CE Pin 1,2,3,4
            mUINT_16 nfCE9Zn				: 4;	// NAND ZN Drive Strength for Ch.9's CE Pin 1,2,3,4
        } bits;
    } nfCeDrStrength89;				// RA8A8: NF CE Drive Strength Ch.8-9


    mUINT_16         rsvd_A8AA_A90C[0x32];	// 0xA8AA-0xA90C
    mUINT_16         padBondingOption;      // 0xA90E
    mUINT_16         rsvd_A910_A95E[40];    // 0xA910-0xA95E
    mUINT_16         hcpuBankAdr;           // 0xA960
    mUINT_16         scpuBankAdr;           // 0xA962

    
} mtSFRS2;


EXTERN INLINE void          mSFR2gpioDirInit        (mUINT_16 value1, mUINT_16 value2); 
EXTERN INLINE void          mSFR2gpioDataInit       (mUINT_16 value1, mUINT_16 value2);

EXTERN INLINE mUINT_16      mSFR2gpioDataExtGet     (void);
EXTERN INLINE mUINT_16      mSFR2gpioCtrlExtGet     (void); 
EXTERN INLINE void          mSFR2gpioDataSet        (mUINT_16 bits);
EXTERN INLINE void          mSFR2gpioDataClr        (mUINT_16 bits);
EXTERN INLINE void          mSFRgpioDataToggle      (mUINT_16 bit);
EXTERN INLINE void          mSFR2gpioCtrlExtSet     (mUINT_16 bits);
EXTERN INLINE void          mSFR2gpioCtrlExtClr     (mUINT_16 bits); 
EXTERN INLINE void          mSFR2gpioDataExtSet     (mUINT_16 bits);
EXTERN INLINE void          mSFR2gpioDataExtClr     (mUINT_16 bits); 
EXTERN INLINE mUINT_NATIVE  mSFR2gpioDataGet        (void);
EXTERN INLINE mUINT_16      mSFR2gpioDataExtNewInGet (void);
EXTERN INLINE void          mSFR2gpioCtrlClr(mUINT_16 bits);
EXTERN INLINE void          mSFR2gpioCtrlExtNewClr  (mUINT_16 bits); 
EXTERN INLINE void          mSFR2gpioCtrlExtNewSet  (mUINT_16 bits); 
EXTERN INLINE void          mSFR2gpioTestOutExtSet(mUINT_16 bits);
EXTERN INLINE void          mSFR2gpioTestOutExtClr(mUINT_16 bits);

EXTERN INLINE void          mSFR2gpioCtrlSet        (mUINT_16 bits);
EXTERN INLINE void          mSFR2gpioDataExtNewInSet (mUINT_16 bits);
EXTERN INLINE void          mSFR2gpioDataExtNewInClr (mUINT_16 bits); 

EXTERN INLINE void          mSFR2setStepDnCntl0     (mUINT_16 val); 
EXTERN INLINE void          mSFR2initStepDnCntl0    (mUINT_16 val); 
EXTERN INLINE void          mSFR2clrStepDnCntl0     (mUINT_16 val);
EXTERN INLINE void          mSFR2setStepDnCntl1     (mUINT_16 val); 
EXTERN INLINE void          mSFR2initStepDnCntl1    (mUINT_16 val); 
EXTERN INLINE void          mSFR2clrStepDnCntl1     (mUINT_16 val);
EXTERN INLINE void          mSFR2setStepDnCntl2     (mUINT_16 val); 
EXTERN INLINE void          mSFR2initStepDnCntl2    (mUINT_16 val); 
EXTERN INLINE void          mSFR2clrStepDnCntl2     (mUINT_16 val);
EXTERN INLINE void          mSFR2setStepDnCntl3     (mUINT_16 val); 
EXTERN INLINE void          mSFR2initStepDnCntl3    (mUINT_16 val); 
EXTERN INLINE void          mSFR2clrStepDnCntl3     (mUINT_16 val);
EXTERN INLINE void          mSFR2setStepDnCntl4     (mUINT_16 val); 
EXTERN INLINE void          mSFR2initStepDnCntl4    (mUINT_16 val); 
EXTERN INLINE void          mSFR2clrStepDnCntl4     (mUINT_16 val);
EXTERN INLINE void          mSFR2setStepDnCntl5     (mUINT_16 val); 
EXTERN INLINE void          mSFR2initStepDnCntl5    (mUINT_16 val); 
EXTERN INLINE void          mSFR2clrStepDnCntl5     (mUINT_16 val);
EXTERN INLINE mUINT_16      mSFR2getStepDnCntl2     (void); 

EXTERN INLINE void          mSFR2initXmClk          (mUINT_16 val);

#ifdef __ghs__
    #pragma ghs section bss = ".rHDC_TEST_PIN"
    EXTERN volatile  mtSFRS2   rSFRS2;   
    #pragma ghs section
#else  
    #pragma arm section zidata = "rHDC_TEST_PIN"
    EXTERN volatile  mtSFRS2   rSFRS2;   
    #pragma arm section
#endif    

#endif // *_H_INC

