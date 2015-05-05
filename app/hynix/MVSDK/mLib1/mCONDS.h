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
#ifndef _mCONDS_H_INC
#define _mCONDS_H_INC

#define mENABLE             1
#define mDISABLE            0

/*****************************************************************************
 Define Hardware Platform here.  Other conditionals will be set according
 to the platform. 
 ****************************************************************************/
#define m5540               1
#define m6540               2
#define m6310               3
#define m6545               4
#define m6360               5
#define m6541               6
#define m6745               7
#define m6311               8
#define m6313               9
#define m8825               10
#define m6740               11
#define m8810               12
#define m8037               13
#define m8010               14
#define m8925               15
#define m9174               16
#define m9187               17

// Power Driver and PreAmp Vendors
#define mMARVG5014          0       // Marvell's 81g5014 preamp
#define mMARVG5122          1       // Marvell's 81g5122 preamp
#define mMARVG102M          2       // Marvell's 81g204m preamp
#define mMARVG204M          3       // Marvell's 81g204m preamp
#define mMARVG214M          4       // Marvell's 81g214m preamp
#define mMARV1000           5       // Marvell's 88m1000 power driver           
#define mMARV1050           6       // Marvell's 88m1050 power driver           
#define mMARV1060           7       // Marvell's 88m1060 power driver
#define mMARV1500           8       // Marvell's 88m1500 power driver           
#define mMARV1550           9       // Marvell's 88m1550 power driver           
#define mMARV2000           10      // Marvell's 88m2000 power driver                      
#define mMARV2050           11      // Marvell's 88m2000 power driver                      
#define mMARV3000           12      // Marvell's 88m3000 power driver           
#define mMARV3040           13      // Marvell's 88m3040 power driver           
#define mHITACHI            14
#define mENOS               15
#define mGENERIC            16
#define mRS2G               17      // STM Pre-amp 
#define mJANUSPRE           18      // 81G204M-like preamp
#define mWALLETPRE          19      // TI preamp
#define mCOOPERPRE          20      // "COOPER" preamp
#define mTI_PWR          	21      // TI power driver
#define mMARVG192T          22      // Marvell's 81G192T preamp
#define mPARAGONPRE         23      // "Paragon" preamp
#define mHA13645			24      // Hitachi HA13645 combo
#define mPONYPRE            25      // TI Preamp for PONY
#define mMARVG7114          26      // Marvell's 81G7114 preamp
#define mPEARLPRE           27      // TI Preamp for PEARL
#define mMARVG814           28      // Marvell's 81G814 preamp
#define mMARV3168           29      // Marvell's 88m3168 power driver
#define mMARV2168           30      // Marvell's 88m2168 power driver
#define mCOMBO_NOT_DEFINED  0xff    // Used for makefile only. Do not change it.

#define mHOST_PROCESSOR     1
#define mMEDIA_PROCESSOR    2
#define mHDA_PRESENT        3
#define mHDA_SS_P40         4
#define mHDA_ENOS           5
#define mHDA_MDES           6
#define mHDA_SS_2G          7
#define mHDA_SS_5G          8
#define mHDA_AIKI           9
#define mHDA_RS2G           10
#define mHDA_JANUS          11
#define mHDA_WALLET         12
#define mHDA_COOPER         13
#define mHDA_RENO           14
#define mHDA_TRIDENT_E0     15
#define mHDA_PARAGON        16
#define mHDA_AWG            17
#define mHDA_PONY           18
#define mHDA_LIGHTNING      19
#define mHDA_PEARL          20
#define mHDA_NEZHA          21
#define mHDA_NOT_DEFINED    0xff    // Used for makefile only. Do not change it.

// type of Interface
#define mATA                1
#define mSATA               2            
#define mCF                 3
#define mUSB                4
#define mIRDA               5
#define mSD                 6
#define mCEATA              7
#define mINTERFACE_NOT_DEFINED    0xff   // Used for makefile only. Do not change it.

#define mRUN_SINGLE_CORE    1
#define mSINGLE_CORE_EMUL   2
#define mTRUE_SMP           3

#define mMHZ                1000000
#define mKHZ                1000
#define mRATED_ERASE_CYLE   0xFFFFFFFF
// type of Interface - One and only one must be defined.
// If you are using Codewarrior, make change here to build a correct platform.
#ifndef mCMD_LINE_MAKE
 #define mINTERFACE_TYPE    mSATA

#else
  #if mCMD_LINE_INTERFACE == mINTERFACE_NOT_DEFINED     // If we don't get the interface type defined from make command line input.
    #define mINTERFACE_TYPE mSATA
  #else
    #define mINTERFACE_TYPE mCMD_LINE_INTERFACE
  #endif
#endif     

#ifndef mBLACK_BIRD
  #ifdef BLACKBIRD
    #if ( BLACKBIRD == mENABLE )
      #define mBLACK_BIRD   mENABLE
    #else
      #define mBLACK_BIRD   mDISABLE
    #endif
  #else
    #define mBLACK_BIRD     mDISABLE
  #endif
#endif

// If you are using Codewarrior, make change here to build a correct platform.
// change this line affects "depend".   For now, move it to m8825
#ifndef mCMD_LINE_MAKE
  #define mSOC              m9174
#else
  // If you are using Makefile, no need to make any change here.
  // Makefile will build the platform correctly, but 
  // You may need to touch this file to provide correct time-stamp
  // to makefile.
  #ifdef M8010
    #define mSOC   m9187
  #endif
  
  #ifdef M9174
    #define mSOC   m9174
  #endif   
  
  #ifdef M9187
    #define mSOC    m9187
  #endif    
 
#endif

    
/**********************************
 ***    Establish SOC Families  ***
 **********************************/
#define mDAVINCI_FAMILY      ((mSOC == m8010) || (mSOC == m9174) || (mSOC == m9187))
#define mVANGOGH_FAMILY      ((mSOC == m9174) || (mSOC == m9187))
 
/***************************
 ***    m9187  Platform    ***
 **************************/
 
   #ifndef mCMD_LINE_MAKE
    #define mHDA                    mHDA_MDES
  #else               // HDA is selected from make command line.
    #if (mCMD_LINE_HDA == mHDA_NOT_DEFINED)       
      #define mHDA                  mHDA_MDES
    #else  
      #define mHDA                  mCMD_LINE_HDA
    #endif  
  #endif 
  
    #define mTRIM_CMD               mDISABLE
    #define SUPPORT_4CH             mDISABLE
    
    #define SKIP_META_LOG_FLUSH     mENABLE
  
    #define mSUPPORT_256MB          mENABLE         //  default is to support 256 MB DDR
  
    //  PICK YOUR POISON!!!
    #define mNAND_200314_R2_ONFI2   mDISABLE    // this is used to lower target capacity
    #define mNAND_200314_R4_ONFI2   mDISABLE    // SLC
    #define mNAND_200314_R5_ONFI2   mDISABLE	// MLC   Rev1 - 31410
    #define mNAND_200340_ONFI22     mDISABLE   // MLC   8k AU, ONFI 2.2, 512Gb, Micron 25nm part
    
    #define mSSD_200330_ONFI2       mENABLE    // Current active, 8 die per channel
    #define mNAND_200331_08         mDISABLE    // 8-K page NAND, SLC, MT29F256G08AUCAB
    #define mNAND_NX287_256G08CMCAB mDISABLE    // 8-K page NAND, MLC, MT29F256G08CMCAB, also turn on OPTIMIZED_SEQ_ALLOC

  #if (mNAND_200314_R4_ONFI2 == mENABLE) || (mNAND_200314_R5_ONFI2 == mENABLE) || (mNAND_200314_R2_ONFI2 == mENABLE) || (mSSD_200330_ONFI2 == mENABLE) || (mNAND_200331_08 == mENABLE) || (mNAND_NX287_256G08CMCAB==mENABLE)
    #define R200314_MICRON_ONFI2    mENABLE     // to control the new way of reading defect bytes
  #else
    #define R200314_MICRON_ONFI2    mDISABLE
  #endif

    #if (mNAND_200331_08 == mENABLE) || (mNAND_NX287_256G08CMCAB == mENABLE)
        #define mUSE_SCRAMBLER     mENABLE
    #else
        #define mUSE_SCRAMBLER     mDISABLE
    #endif

    // (mSSD_200330_ONFI2 options defined below)

    #define mPAGE_SIZE_IN_K             (4UL)
    #define mSUPPORT_4KAU_8KPAGE        mDISABLE
    #define mCHECK_RDY_BIT_5_FOR_STATUS mDISABLE
    #define mNV_INTERLEAVE_OP           mDISABLE    // m9174: note we support ONFI&Samsung interleave sequence
    #define mNV_MULTIPLANE_OP           mDISABLE    // m9174
    #define mNV_NUM_PLANES              1
    #define mNV_MPDO_FACTOR             0
    #define mNV_ONFI                    mENABLE
    #define DUMB_DUMB                   mENABLE 
    #define NV_GEN_PAAWIDTH_NEW_2_GEN   mDISABLE
    
    #define mECC_LEVEL                  0       // default
    #define mUSE_ERASE_PAA              mENABLE
    #define mUSE_ERASE_COUNT_FROM_INFO  mDISABLE
    #define mWRITE_WD_CHUNKS            mDISABLE
    #define mFORCE_TWO_AU_ALLOC         mDISABLE
    

    #if (mNAND_200314_R5_ONFI2 == mENABLE)
      #undef    mCHECK_RDY_BIT_5_FOR_STATUS
      #undef    mECC_LEVEL
      #define   mECC_LEVEL              1
      #define   mCHECK_RDY_BIT_5_FOR_STATUS mENABLE
    #endif
    
    #if (mSSD_200330_ONFI2 ==  mENABLE)
      #undef    mCHECK_RDY_BIT_5_FOR_STATUS
      #undef    mNV_INTERLEAVE_OP          
      #undef    mNV_MULTIPLANE_OP          
      #undef    mNV_NUM_PLANES             
      #undef    mNV_ONFI                   
      #undef    DUMB_DUMB                  
      #undef    NV_GEN_PAAWIDTH_NEW_2_GEN  
      #undef    mECC_LEVEL
      #undef    mUSE_ERASE_PAA
      #undef    mUSE_ERASE_COUNT_FROM_INFO
      #undef    mWRITE_WD_CHUNKS

      #undef    R200314_MICRON_ONFI2
        #define R200314_MICRON_ONFI2        mENABLE
      

      #define   mWRITE_WD_CHUNKS        mENABLE
      #define   mUSE_ERASE_COUNT_FROM_INFO  mENABLE
      #define   mUSE_ERASE_PAA      mDISABLE
      #define   mECC_LEVEL          1
      #define   mNV_INTERLEAVE_OP   mENABLE
      #define   mNV_MULTIPLANE_OP   mDISABLE //mENABLE
      #define   mNV_NUM_PLANES      2
      #define   mNV_ONFI            mENABLE
      //#define mFORCE_EVEN_ALLOC     mDISABLE
      #define   DUMB_DUMB           mENABLE 
      #define   NV_GEN_PAAWIDTH_NEW_2_GEN   mENABLE
      #define   mCHECK_RDY_BIT_5_FOR_STATUS mENABLE
      #undef mRATED_ERASE_CYLE
         #define mRATED_ERASE_CYLE  5000
      
    #endif

    #if (mNAND_200331_08 == mENABLE)
      #undef    R200314_MICRON_ONFI2
        #define R200314_MICRON_ONFI2        mENABLE

      #undef    mPAGE_SIZE_IN_K
        #define mPAGE_SIZE_IN_K         (8UL)
        
      #undef    mCHECK_RDY_BIT_5_FOR_STATUS
      #undef    mNV_INTERLEAVE_OP
        #define   mNV_INTERLEAVE_OP   mDISABLE
      
      #undef    mNV_MULTIPLANE_OP          
        #define   mNV_MULTIPLANE_OP   mDISABLE //mENABLE
      #undef    mNV_NUM_PLANES             
      #undef    mNV_ONFI                   
      #undef    DUMB_DUMB                  
      #undef    NV_GEN_PAAWIDTH_NEW_2_GEN  
      #undef    mECC_LEVEL

      #undef    mUSE_ERASE_PAA
      #define   mUSE_ERASE_PAA              mDISABLE

      #undef    mUSE_ERASE_COUNT_FROM_INFO
      #define   mUSE_ERASE_COUNT_FROM_INFO  mENABLE
      
      #undef    mWRITE_WD_CHUNKS
      #define   mWRITE_WD_CHUNKS            mENABLE
      
      #undef    mSUPPORT_4KAU_8KPAGE
      #define   mSUPPORT_4KAU_8KPAGE        mENABLE

      #undef    mFORCE_TWO_AU_ALLOC
      #define   mFORCE_TWO_AU_ALLOC         mENABLE
      
      #define   mECC_LEVEL          1
      #define   mNV_NUM_PLANES      2
      #define   mNV_ONFI            mENABLE
      //#define mFORCE_EVEN_ALLOC     mDISABLE
      #define   DUMB_DUMB           mENABLE 
      #define   NV_GEN_PAAWIDTH_NEW_2_GEN   mENABLE
      #define   mCHECK_RDY_BIT_5_FOR_STATUS mENABLE

      #define   mFAT_WERU           mENABLE     // a weru D does not fit into an AU
    #endif
    
    #if (mNAND_NX287_256G08CMCAB == mENABLE)
      #undef    R200314_MICRON_ONFI2
        #define R200314_MICRON_ONFI2        mENABLE

      #undef    mPAGE_SIZE_IN_K
        #define mPAGE_SIZE_IN_K         (8UL)
        
      #undef    mCHECK_RDY_BIT_5_FOR_STATUS
      #undef    mNV_INTERLEAVE_OP
        #define   mNV_INTERLEAVE_OP   mDISABLE
      
      #undef    mNV_MULTIPLANE_OP          
        #define   mNV_MULTIPLANE_OP   mDISABLE //mENABLE
      #undef    mNV_NUM_PLANES             
      #undef    mNV_MPDO_FACTOR
        #define   mNV_MPDO_FACTOR  7
      #undef    mNV_ONFI                   
      #undef    DUMB_DUMB                  
      #undef    NV_GEN_PAAWIDTH_NEW_2_GEN  
      #undef    mECC_LEVEL

      #undef    mUSE_ERASE_PAA
      #define   mUSE_ERASE_PAA              mDISABLE

      #undef    mUSE_ERASE_COUNT_FROM_INFO
      #define   mUSE_ERASE_COUNT_FROM_INFO  mENABLE
      
      #undef    mWRITE_WD_CHUNKS
      #define   mWRITE_WD_CHUNKS            mENABLE
      
      #undef    mSUPPORT_4KAU_8KPAGE
      #define   mSUPPORT_4KAU_8KPAGE        mENABLE
      
      #undef    mFORCE_TWO_AU_ALLOC
      #define   mFORCE_TWO_AU_ALLOC         mENABLE
      
      #define   mECC_LEVEL          1
      #define   mNV_NUM_PLANES      2
      #define   mNV_ONFI            mENABLE
      //#define mFORCE_EVEN_ALLOC     mDISABLE
      #define   DUMB_DUMB           mENABLE 
      #define   NV_GEN_PAAWIDTH_NEW_2_GEN   mENABLE
      #define   mCHECK_RDY_BIT_5_FOR_STATUS mENABLE

      #define   mFAT_WERU           mENABLE     // a weru D does not fit into an AU
    #endif      // end of mNAND_NX287_256G08CMCAB
        
    
    #define mNV_INTERLEAVE_RD_OP    mDISABLE    // m9174
    #define mNV_ONFI_MODE           4           // default mode for normal op
    
    #if (mNAND_200314_R5_ONFI2 == mENABLE) || (mSSD_200330_ONFI2 == mENABLE)
      #if (mNV_INTERLEAVE_OP == mENABLE) && (mNV_MULTIPLANE_OP == mENABLE)
        #define mFAT_WERU           mENABLE     // a weru D does not fit into an AU
      #endif
    #endif
    
    #define MINI_200                mDISABLE
    
    #define USE_SINGLE_FLUSH        mDISABLE
    #define mUSE_6G_ONLY            mDISABLE

    #define USER_250                mDISABLE        //  implies 8/9 MB cache, MEM_MISER should be enabled also
//    #define USER_250                mENABLE        //  implies 8/9 MB cache, MEM_MISER should be enabled also
    

        #define MEM_MISER               mDISABLE
	#if ( mNV_MPDO_FACTOR == mENABLE )
        	#define OPTIMIZED_SEQ_ALLOC     mENABLE
	#else
        	#define OPTIMIZED_SEQ_ALLOC     mDISABLE
	#endif
    // cleaned up memory aconfiguration and compressed WD
    
    #ifdef mFAT_WERU
    #else
      #define    mFAT_WERU          mDISABLE
    #endif
                                                     
    #if (mNV_MULTIPLANE_OP == mENABLE) && (mNV_ONFI == mDISABLE)
      #error "ONFI multi-plane only"              // note we only support ONFI multi-plane sequence
    #endif
    
    #if (mNV_MULTIPLANE_OP == mENABLE) && (mNV_INTERLEAVE_OP == mENABLE) && (mNV_ONFI == mDISABLE)
      #error "ONFI interleaved multi-plane only"  // note we only support ONFI interleaved multi-plane sequence
    #endif    
    
    #if (mNV_INTERLEAVE_OP == mDISABLE) && (mNV_INTERLEAVE_RD_OP == mENABLE)
      #error "wrong setting with mNV_INTERLEAVE_RD_OP" 
    #endif
    
    #if (mNV_INTERLEAVE_OP == mENABLE)&&(mNV_MULTIPLANE_OP == mENABLE)
      #define mNV_MPF               4           // multiply factor
      #define mNV_MPF_SHIFT         2
      #define mNV_MAX_MPF_SHIFT     2           // used in shifting
    #elif (mNV_INTERLEAVE_OP == mENABLE) || (mNV_MULTIPLANE_OP == mENABLE)
      #define mNV_MPF               2           // multiply factor
      #define mNV_MPF_SHIFT         1
      #define mNV_MAX_MPF_SHIFT     1           // used in shifting
    #else   // normal mode
      #define mNV_MPF               1           // multiply factor
      #define mNV_MPF_SHIFT         0
      #define mNV_MAX_MPF_SHIFT     0           // used in shifting
    #endif  // (mNV_INTERLEAVE_OP == mENABLE)&&(mNV_MULTIPLANE_OP == mENABLE) 

    // CPU Settings
    #define mRAB_FREQ               150         // In Mhz
    #define mTMR_FREQ               125         // Timers/Counters clock frequency, In Mhz
    
    // Other Conditionals
    #define mDUAL_CORE_SUPPORT      mENABLE 
    #define mDUAL_CORE_FW_ARCH      mSINGLE_CORE_EMUL // mRUN_SINGLE_CORE // 
    
  #ifdef M_FLASH
    #define mMANTECA_FLASH          mENABLE     // Between mMANTECA_FLASH and mSERIAL_FLASH, only one can be enabled.
    #define mSERIAL_FLASH           mDISABLE 
  #else
    #define mMANTECA_FLASH          mDISABLE    // Between mMANTECA_FLASH and mSERIAL_FLASH, only one can be enabled.
    #define mSERIAL_FLASH           mENABLE 
  #endif
  
    #define OSC_25MHZ               mENABLE     // mENABLE for 25MHz OSC, mDISABLE for 40MHz OSC
    
    #define mNV_SIM_LEANMAN_NOCMP   mENABLE
    #define mNV_SIM_LEANMAN         mENABLE		// SIM_LEANMAN	    
    #define mNV_SEQ_TEST            mENABLE		// SIM_LEANMAN

    #define mNV_SIMULATION          mDISABLE
    #define mNV_RAM_DISK            mENABLE //mDISABLE	// enable/disable RAM disk simulation
    #define mNV_RELEASE_LOW_LEVEL   mDISABLE
    // if both are enables, make sure you change the conditions in CONDS.H
    
    #define EXTERNAL_DDR            mENABLE

    #define SYSTEM_USER_MIXED       mENABLE     // Allow system data and user data mixing together -- can happen when clean up hits

    #define SEE_FATMAN_WORK         mDISABLE
    #define mNV_32CEs               mENABLE     // Support for up to 32 devices per track
    // turn this one mENABLE if using > 32 devices
    
    #if (mNV_INTERLEAVE_OP == mENABLE) || (mNV_MULTIPLANE_OP == mENABLE)
      #define mMORE_THAN_32         mENABLE
    #else
      #define mMORE_THAN_32         mDISABLE
    #endif
    
    #define     PAGES_PER_BLOCK     256
    
    #if (mNAND_200314_R4_ONFI2 == mENABLE) || (mNAND_200331_08 == mENABLE)
      #define mNV_128_PAGES_BLK     mENABLE     // enable for device which has 128 (4K)pages per block
      #undef    PAGES_PER_BLOCK
      #define PAGES_PER_BLOCK       128
    #else
      #define mNV_128_PAGES_BLK     mDISABLE    // enable for device which has 128 (4K)pages per block 
    #endif
    
    #if (mNAND_200314_R5_ONFI2 == mENABLE) || (mSSD_200330_ONFI2 == mENABLE) || (mNAND_NX287_256G08CMCAB == mENABLE)
      #define mNV_256_PAGES_BLK     mENABLE     // enable for device which has 256 (4K)pages per block
      #undef    PAGES_PER_BLOCK
      #define PAGES_PER_BLOCK       256
    #else
      #define mNV_256_PAGES_BLK     mDISABLE    // enable for device which has 256 (4K)pages per block
    #endif
    
    #if (mNV_128_PAGES_BLK == mENABLE) && (mNV_256_PAGES_BLK == mENABLE)
        AHA
    #endif

    #define mNV_CUSTOMER_SWITCH     mENABLE     // must be "mENABLE", DO NOT change
    
    
        #define mNV_SAVE_LAA_TO_AUX     mDISABLE
    
        #undef  mNV_SAVE_LAA_TO_AUX
        #define mNV_SAVE_LAA_TO_AUX mENABLE
    
    #define DYNAMIC_CAPACITY        mDISABLE
    
    // these two switches are here for test purposes only!!!
    #define mTHUMB_MODE             mDISABLE
    #define mSTREAMING_CMDS         mDISABLE
    #define mDDO_ENABLE             mENABLE         // Turn on DDO output to test14(DDO_CLK) and test11(DDO)
    #define ETM_POWER_DOWN          mDISABLE
    #define DAVINCI_1_0_BUG_FIX     mDISABLE        // enable to build for Davinci 1.0 bug work around
    #define mNV_FC_INTR_HANDLER     mENABLE

    #define mNCQ_OP                 mDISABLE
    #define DMA_SETUP_FIS_AUTO_ACTIVATE mDISABLE
    #define mDSW_FUN                mDISABLE
    #define m4K_SUBSEGMENT          mDISABLE    
    #define m128K_SUBSEGMENT        mDISABLE 
    #define mSSD_TABLE              mDISABLE        // use SSD for linking 
    #define mRELINK_SSD             mDISABLE      
    #define mREMOVE_PARTIAL_BIN		mDISABLE
    #define mWERU_UPDATE_CACHE      mENABLE
    #define mINTERNAL_ALLOC			mENABLE

    #define mPOWER_LOSS_DETECTION   mDISABLE
    
    #define mSELF_CPR               mENABLE
    
    #define mDUAL_VALID_LIST		mENABLE 
    #define mDPP                    mDISABLE        //   
    #define mTCM_DP                 mDISABLE        // turned this on to catch TCM error  
    #define mWA_CHECK                mENABLE
        #define ASC_NOTIFICATION        mDISABLE    // Asynchronous Notification feature is for Cisco / Vanir only
        #define mSMART          	mDISABLE 
    
    #define mNV_NEW_DEFECT			mENABLE
    #define mCLEANUP_DEBUG			mDISABLE
	#define mCLEANUP_DEBUG_LEVEL_1  mDISABLE
    #define mCLEANUP_SCOPE			mDISABLE
	#define mDPB_TOSS_ERASEBIN 		mENABLE
    #define mNV_BIST                mDISABLE 
    #define VG_REV_2_0              mDISABLE 
    #if (VG_REV_2_0 == mENABLE)
      #define mFORCE_EVEN_ALLOC     mENABLE
      
      #if (mNAND_200331_08 == mENABLE) || (mNAND_NX287_256G08CMCAB == mENABLE)

        #if ( mNV_MPDO_FACTOR == mENABLE )
            YOU ARE MESSED UP.
        #else
            #define FORCE_EVEN_ALLOC_PADDING      (3UL) // To make it 4-aligned, this should be 3
        #endif
        
      #else
        #define FORCE_EVEN_ALLOC_PADDING      (1UL) // to make it 2-aligned.   To make it 4-aligned, this should be 3
      #endif
      
      
      #define VANGOGH_1_1_BM_BUG    mDISABLE    // enable to build for VanGogh 1.0/1.1 BM bug work around
      #define mVG_REV_2_AES         mENABLE    // Temp disabled and wait for mem re-arrange
    #else
      #define mFORCE_EVEN_ALLOC     mDISABLE
      #define VANGOGH_1_1_BM_BUG    mENABLE     // enable to build for VanGogh 1.0/1.1 BM bug work around
      #define mVG_REV_2_AES         mENABLE
    #endif      
    #define mDAVINCI_COMPATIBLE     mDISABLE
    #define CACHELBA0_VISTA_INSTALL mDISABLE
    
    #define mUSE_SMART_MODULO       mENABLE
    #define mHALF_SYS_VEC_WIDTH     mENABLE
   
      #define mNV_DISPARATE_SEC_SIZE    mDISABLE
    
      #define MAP_WHOLE_WERU            mENABLE
	  #define mSAL						mDISABLE	/// Victor
	  #define mCSAR_DEBUG_LEVEL0		mDISABLE	/// Victor
	  #define mCSAR_DEBUG_LEVEL1		mDISABLE	/// Victor

        #define     AVOID_SYS_WERU      mDISABLE
        #define     mMULTI_FLUSH        mDISABLE

    #define MICRO_FLUSH                 mENABLE
    
    #define mPOWER_UP_FLUSH_ALWAYS      mENABLE
    
    #define mCHECK_LUT                  mDISABLE
    
    #define MICRO_FLUSH_CONVERT         mDISABLE
    
        #define USE_LUT_QUEUE_ONLY          mDISABLE		// mENABLE when MICRO_FLUSH is mENABLE
        #define SAL_RING_BUFFER             mDISABLE        // mENABLE when MICRO_FLUSH is mENABLE
        #define META_LOG_HE			        mDISABLE        // mENABLE when MICRO_FLUSH is mENABLE
    
    #define SERIAL_ATA_FEATURE_PM       mDISABLE
    #define DEBUG_TIMEOUT               mDISABLE
    #define mFLUSH_DEBUG                mDISABLE
    #define mHANDLE_LUT_WERUQ           mDISABLE
    #define mCHECK_VALID_MAP            mENABLE            // TURN OFF FOR OFFICIAL RELEASE
	// #if (MINI_200 == mENABLE)
    #define mCHECK_LUT_PAA              mDISABLE           // TURN OFF FOR OFFICIAL RELEASE
	// #endif
    
    #define mUSE_HOST_FULL_FLUSH        mDISABLE
    
    #define CSCO_OFFICIAL_RELEASE       mDISABLE		// LEANMAN
    
    #define mCHECK_VALID_MAP_RT         mDISABLE        // check valid map while process worked weru
    
    #define NV_EXITCOUNTDOWN_IN_AUS  mDISABLE // if enabled, exitcountdown is in units of AU's instead of tracks
    
    #define S1_MODEL             mDISABLE
    #define S1_64                mDISABLE
    #define S1_128               mDISABLE
    #define S1_256               mDISABLE
    #define S1_512               mDISABLE
    
    #define mALLOW_ONLY_ONE_CLEANUP_RLUT    mDISABLE
    
  #if ((mPAGE_SIZE_IN_K == 8) && (mUSE_SCRAMBLER == mDISABLE))
     #error MUST HAVE SCRAMBLER ON FOR ALL 8K PAGES!!!
  #endif


//
// end of m9187 
//


// COMMON SWITCH

#define AU_TO_PAGE_FACTOR     (mPAGE_SIZE_IN_K/mAU_SIZE_IN_K)

#define	mWRITE_INFO		        mENABLE
#define QUICK_FLUSH             mDISABLE

#ifndef USE_DEBUG_FIFO
    #define USE_DEBUG_FIFO      mENABLE
#endif

#ifndef MINI_200
    #define MINI_200    mDISABLE
#endif    

#ifndef LOG_VALID_COUNT
    #define LOG_VALID_COUNT   mDISABLE
#endif

#ifndef SYS_SEQ
    #define SYS_SEQ     mENABLE
#endif

#ifndef         MICRO_FLUSH   
    #define     MICRO_FLUSH   mDISABLE    
#endif

#ifndef         USE_LUT_QUEUE_ONLY
    #define     USE_LUT_QUEUE_ONLY      mDISABLE
#endif

#ifndef mPACK_DEBUG
    #define mPACK_DEBUG         mDISABLE 
#endif




#ifndef mALLOW_DEFECT_FLUSH
    #define mALLOW_DEFECT_FLUSH     mDISABLE
#endif

#ifndef mRLUT_BATCH
  #define mRLUT_BATCH               mDISABLE
#endif

#ifndef SHORT_STROKE_CSCO
  #define SHORT_STROKE_CSCO         0
#endif

#ifndef mMULTI_FLUSH
  #define     mMULTI_FLUSH          mDISABLE
#endif

#ifndef DUMB_DUMB
  #define DUMB_DUMB                 mDISABLE 
#endif    

#ifndef mFORCE_EVEN_ALLOC
  #define mFORCE_EVEN_ALLOC         mDISABLE
#endif

#ifndef SERIAL_ATA_FEATURE_PM
  #define SERIAL_ATA_FEATURE_PM     mDISABLE
#endif

#ifndef     mNAND_200314_R2_ONFI2
  #define    mNAND_200314_R2_ONFI2  mDISABLE
#endif

#ifndef mNAND_200314_R4_ONFI2
  #define    mNAND_200314_R4_ONFI2  mDISABLE
#endif

#ifndef mNAND_200314_R5_ONFI2
  #define    mNAND_200314_R5_ONFI2  mDISABLE
#endif

#ifndef mSSD_200330_ONFI2
  #define mSSD_200330_ONFI2         mDISABLE
#endif

#ifndef mNV_SEQ_TEST
  #define mNV_SEQ_TEST              mENABLE
#endif

#ifndef mNV_MPF
  #define mNV_MPF                   1           // multiply factor
#endif

#ifndef mNV_MPF_SHIFT
  #define mNV_MPF_SHIFT             0
#endif

#ifndef mNV_CUSTOMER_SWITCH
  #define mNV_CUSTOMER_SWITCH       mENABLE
#endif


#ifdef FORCE_2G
#else
  #define     FORCE_2G              0
#endif

#ifdef FORCE_1G
#else
  #define     FORCE_1G              0
#endif

#ifdef mPOWER_LOSS_DETECTION
#else
  #define     mPOWER_LOSS_DETECTION mDISABLE
#endif

#ifdef mPOWER_DOWN_FLUSH
#else
  #define     mPOWER_DOWN_FLUSH     mDISABLE
#endif

#ifdef USE_WWN
#else
  #define USE_WWN     0
#endif

#ifdef  SEE_FATMAN_WORK
#else
  #define     SEE_FATMAN_WORK       mDISABLE
#endif    

#ifdef NEW_10_ALPHANUMERIC
#else
  #define	NEW_10_ALPHANUMERIC	    mDISABLE
#endif
#ifdef m4K_SUBSEGMENT
#else
  #define m4K_SUBSEGMENT            mDISABLE
  #define mSSD_TABLE                mDISABLE
#endif
    
#ifdef mDUAL_VALID_LIST
#else
  #define mDUAL_VALID_LIST          mDISABLE
#endif

#ifdef mHALF_SYS_VEC_WIDTH
#else
  #define mHALF_SYS_VEC_WIDTH       mDISABLE
#endif

#ifdef mSSD_TABLE
#else
  #define mSSD_TABLE                mDISABLE
#endif

#ifdef  mNV_SIMULATION
#else
  #define mNV_SIMULATION            mDISABLE    // enable/disable RAM disk simulation 
#endif

#ifndef mNV_SAVE_LAA_TO_AUX
  #define mNV_SAVE_LAA_TO_AUX       mDISABLE
#endif

#ifndef mNV_SIM_LEANMAN
  #define mNV_SIM_LEANMAN           mENABLE
#endif

#ifndef mNV_SIM_LEANMAN_NOCMP
  #define mNV_SIM_LEANMAN_NOCMP     mENABLE
#endif

#ifndef EXTERNAL_DDR
  #define EXTERNAL_DDR              mDISABLE
#endif

#ifndef DYNAMIC_CAPACITY
  #define DYNAMIC_CAPACITY          mDISABLE
#endif

#ifndef m8945_m8014_DIFF
  #define m8945_m8014_DIFF          mDISABLE
#endif


#ifndef mREV_1P
#define mREV_1P mDISABLE
#endif

#ifndef mARF_COMPENSATION
#define mARF_COMPENSATION mDISABLE
#endif

#ifndef mSPIRAL_SERVO
#define mSPIRAL_SERVO mDISABLE
#endif

#ifndef mNONHARMONIC_FINAL
#define mNONHARMONIC_FINAL mDISABLE
#endif

#ifndef DAVINCI_FPGA
#define DAVINCI_FPGA mDISABLE
#endif

#ifndef mALLOW_ONLY_ONE_CLEANUP_RLUT
#define mALLOW_ONLY_ONE_CLEANUP_RLUT mDISABLE
#endif

#ifndef LONG_TERM_WEAR_TEST
#define LONG_TERM_WEAR_TEST mDISABLE
#endif

#ifndef mRev2pt0
#define mRev2pt0 mDISABLE
#endif

#ifndef mREAD_PROMOTION
#define mREAD_PROMOTION mDISABLE
#endif


#ifndef mNV_16MB
  #define mNV_16MB                  mDISABLE
#endif

#ifndef mSUPPORT_256MB
  #define mSUPPORT_256MB            mDISABLE
#endif

#ifndef SYSTEM_USER_MIXED
  #define SYSTEM_USER_MIXED         mDISABLE
#endif

#ifndef mNV_FC_INTR_HANDLER
  #define mNV_FC_INTR_HANDLER       mDISABLE
#endif

#ifndef     mSELF_CPR
  #define mSELF_CPR                 mDISABLE
#endif

#ifndef     mSMART
  #define mSMART                    mDISABLE
#endif

#ifndef mTRIM_CMD
    #define mTRIM_CMD               mDISABLE
#endif

#ifndef mFRAG_FLUSH
    #define mFRAG_FLUSH         mDISABLE
#endif


#define mVERTICAL_REC               mDISABLE

#if (mHDA == mHDA_MDES)
    // POWER DRIVER
  #if mCMD_LINE_COMBO == mCOMBO_NOT_DEFINED     // If a makefile user does not define a particular HDA.
    #define mPWR_DRIVER             mMARV1500
  #else
    #define mPWR_DRIVER             mCMD_LINE_COMBO
  #endif    
    // PREAMP
    #define mPRE_AMP                mMARVG5014
    #define mRAMP_LOAD              mDISABLE
    #define mSPINDLE_SINE_DRIVE     mDISABLE
    #define mASSW                   mDISABLE
    #define mWRITE_SPIRAL           mDISABLE
    #define mRSSW                   mDISABLE
    #define mRSSW_DEBUG             mDISABLE
    #define mSSW_MEMORY_MODEL       mDISABLE
    #define mRFF_PLL                mDISABLE
    #define mREC_PLL                mDISABLE
    #define mREC_SPIN               mDISABLE
    #define mHALF_SAMPLE_RATE		mDISABLE
    #define mNEW_WCS_STYLE          mDISABLE
    #define mMAP_HEADS              mDISABLE
    #define EXT_PES_CAL             mDISABLE
#else
  #error !!! Wrong HDA condition !!!
#endif  // HDA platform

#endif //_H_INC
