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

/*----------------------------------------------------------------------------
 Include files:
 ---------------------------------------------------------------------------*/
#define   INSTANTIATE_MPHYLINK

#include "mPhyLink.h"
#include "mPLI.h"
#include "mSFRS.h"
#include "mCLKPWR.h"
#include "mHost.h"

/*----------------------------------------------------------------------------
 Private function prototypes:
 ---------------------------------------------------------------------------*/
  PRIVATE void mSataPLLCalibration(void);

  PRIVATE void mSataPhyPrePLLCalInit(void);

/*******************************************************************
*																   
*  NAME:   	    mPhyLinkInitLinkMode											   
*																   
*  FILENAME:    mPhyLink.c 											   
*																   
*  PARAMETERS:  type mUINT_16 val
*																   
*  DESCRIPTION: API function to initialize Link Mode response
*																   
*  RETURNS:     mUINT_16      											   
*	
********************************************************************/
INLINE void mPhyLinkInitLinkMode ()
{
    mPLIsetLTModeLow(0x100);   // Disable nearEnd loopback

    mPLIsetLTModeHi(0xb010);  // initial LTMODE High R580E, Sync lock mode, 64 Align primitives,
}

/*******************************************************************
*																   
*  NAME:   	    mPhyLinkClrErrL
*																   
*  FILENAME:    mPhyLink.c 											   
*																   
*  PARAMETERS:  type mUINT_16 val
*																   
*  DESCRIPTION: API function to initialize Phy
*																   
*  RETURNS:     mUINT_16      											   
*	
********************************************************************/
INLINE void mPhyLinkClrErrLo (mUINT_16 val)
{
    mPLIclrErrLo (val);

}

/*******************************************************************
*																   
*  NAME:   	    mPhyLinkClrErrH
*																   
*  FILENAME:    mPhyLink.c 											   
*																   
*  PARAMETERS:  type mUINT_16 val
*																   
*  DESCRIPTION: API function to initialize Phy
*																   
*  RETURNS:     mUINT_16      											   
*	
********************************************************************/
INLINE void mPhyLinkClrErrHi (mUINT_16 val)
{
    mPLIclrErrHi (val);

}

/*******************************************************************
*																   
*  NAME:   	    mPhyLinkInitPhyControl
*																   
*  FILENAME:    mPhyLink.c 											   
*																   
*  PARAMETERS:  type mUINT_16 val
*																   
*  DESCRIPTION: API function to initialize Phy
*																   
*  RETURNS:     mUINT_16      											   
*	
********************************************************************/
INLINE void mPhyLinkInitPhyControl (mUINT_16 val)
{
    mPLIinitPhyControl (val);

}




/*******************************************************************
*																   
*  NAME:        InitSataPHY												   
*																   
*  FILENAME:    mPhyLink.c 											   
*																   
*  PARAMETERS:  none    											   
*																   
*  DESCRIPTION: Initializes the PHY block
*  RETURNS:     nothing 
*
********************************************************************/
void mInitSataPhyLink(void)
{
    mUINT_32 delay;	  


    mSataPhyPrePLLCalInit();                            // init some registers before doing PLL CAL

    mSataPLLCalibration();                              // do new PLL CAL

    mPhyLinkInitPhyControl(0x0020);                   // limit negotiation speed to 3G/1.5G
    //mPhyLinkInitPhyControl(0x0000);                     // limit negotiation speed to 6G/3G/1.5G
    mPhyLinkInitLinkMode();                             // initital Link LTMODE
    
//20120614    while (!(mPhyLinkGetSataPmState() & 0x000F));
//20120614    while (!(mHostGetTMflowStatus() & m_tHBI_TM_FLOW_INT_bits_phyRdy)) ;
    delay=0xfff;   
    while (!(mPhyLinkGetSataPmState() & 0x000F))
    {
        if(delay == 0)
        {
            break; 
        }
        delay --;
        
    }
    delay=0xfff;   
    while (!(mHostGetTMflowStatus() & m_tHBI_TM_FLOW_INT_bits_phyRdy)) 
    {
        if(delay == 0)
        {
            break; 
        }
        delay --;
    }



    // wait for PHY to stable
    delay=0xfff;   
    while (delay--);


    // Clear all SATA Link/Phy error
    mPhyLinkClrErrLo(0xFFFF);
    mPhyLinkClrErrHi(0xFFFF);
    mHostClrEsataErrIntrStatus(0xffff);
    mHostClrTmStatusHi(0xff);

}


/*******************************************************************
*																   
*  NAME:        mSataPhyPrePLLCalInit()												   
*																   
*  FILENAME:    mPhyLink.c											   
*																   
*  PARAMETERS:  none    											   
*																   
*  DESCRIPTION: initialize some SATA PHY register after power up but before PLL Calibration 
*
*  RETURNS:     nothing 
*
********************************************************************/
void mSataPhyPrePLLCalInit()
{
    (*(volatile mUINT_16 *)(0x1c005904)) = 0x0040;      // FFE_RES_RD_SEL
    (*(volatile mUINT_16 *)(0x1c00590E)) = 0x1530;      // Rx Imp Cal Threshod, Rx DCC circuit Enable
    (*(volatile mUINT_16 *)(0x1c005914)) = 0x0030;      // Tx Imp Calibration Threshold
    (*(volatile mUINT_16 *)(0x1c005928)) = 0xB065;      // Tx_DRV_CM & TX_DRV_IDLE & SATA_TX_AMP_ADJ & TX_PROCESS_COMP_EN
    (*(volatile mUINT_16 *)(0x1c00592C)) = 0x0800;      // TX_PREDRV_SWING
    (*(volatile mUINT_16 *)(0x1c005940)) = 0x6800;      // DTL_SQ_PLOOP_EN
    (*(volatile mUINT_16 *)(0x1c005946)) = 0x0577;      // FFE_RES_SEL & FFE_CAP_SEL
    (*(volatile mUINT_16 *)(0x1c00594C)) = 0xA000;      // DFE_CLK_ON = 1

    (*(volatile mUINT_16 *)(0x1c00599C)) = 0x8B1A;      // G1 Tx Driver settings
    (*(volatile mUINT_16 *)(0x1c0059A0)) = 0xD2A0;      // G2 Tx Driver settings
    (*(volatile mUINT_16 *)(0x1c0059A4)) = 0x5A2A;      // G3 Tx Driver settings
    (*(volatile mUINT_16 *)(0x1c0059B0)) = 0x0155;      // PLL Calibration Threshold
    (*(volatile mUINT_16 *)(0x1c0059B4)) = 0xFEC0;      // PU_EOM_INTP = 0

    if (*(volatile mUINT_16 *)0x1c00A81E < 0x0200)
    {  // VanGogh 1.0
        (*(volatile mUINT_16 *)(0x1c00599E)) = 0x00F0;      // G1 Rx CDR settings
        (*(volatile mUINT_16 *)(0x1c0059A2)) = 0x00F0;      // G2 Rx CDR settings
        (*(volatile mUINT_16 *)(0x1c0059A6)) = 0x00F5;      // G3 Rx CDR settings
    }
    else
    {
        // VanGogh 2.0 and above
        (*(volatile mUINT_16 *)(0x1c00599E)) = 0x0000;      // G1 Rx CDR settings
        (*(volatile mUINT_16 *)(0x1c0059A2)) = 0x0000;      // G2 Rx CDR settings
        (*(volatile mUINT_16 *)(0x1c0059A6)) = 0x0005;      // G3 Rx CDR settings
        (*(volatile mUINT_16 *)(0x1c0059E6)) = 0xE002;      // DLT_CLAMPING = 11 and DLT_CLAMPING_EN = 1

    }

}


/*******************************************************************
*																   
*  NAME:        mSATA_PLL_CAL()												   
*																   
*  FILENAME:    mPhyLink.c											   
*																   
*  PARAMETERS:  none    											   
*																   
*  DESCRIPTION: SATA PLL Calibration after power up
*  RETURNS:     nothing 
*
********************************************************************/
void mSataPLLCalibration()
{
    mUINT_16 i;    
    mUINT_16 cal_result;

    while (1)
    {
        // Start PLL_IMP_CALIBRATION
        (*(volatile mUINT_16 *)(0x1c005912)) |= mBIT(15);      // Start PHY Calibration        
        // wait for 20 us
        for (i = 0; i < 5000; i++);
        (*(volatile mUINT_16 *)(0x1c005912)) &= ~mBIT(15);     // Clear PHY Calibration
    
        // Poll for PHY_CAL_DONE(R5912[7] = 1) within 20ms timeout. 
        i = 0;
        do 
        {
		    if (((*(volatile mUINT_16 *)0x1c005912))& mBIT(7)) 
			{
			    break;
            }
		    i ++;
	    } while (i < 0x600000);   //time check
		
		if (((*(volatile mUINT_16 *)0x1c005912))& mBIT(7)) 
		{
				break;
		} // break out of while (1)
    }

    // Start risetime CALIBRATION
    (*(volatile mUINT_16 *)(0x1c005912)) |= mBIT(10);     // Start risetime Calibration        
    // wait for 20 us
        for (i = 0; i < 5000; i++);

    (*(volatile mUINT_16 *)(0x1c005912)) &= ~mBIT(10);    // Clear risetime Calibration        
    // wait for 20 us
    for (i = 0; i < 5000; i++);
    // read calibration result
    cal_result = *(volatile mUINT_16 *)(0x1c00591e) & 0xf;
    // set read select to force calibration value 
    (*(volatile mUINT_16 *)(0x1c005904)) = 0x0060;
    // set calibration result
    (*(volatile mUINT_16 *)(0x1c00591e)) |= (0x0010|cal_result);

    // Disable DFE_CLK_ON
    (*(volatile mUINT_16 *)(0x1c00594C)) = 0x2000;
    // Enalbe Tx driver
    (*(volatile mUINT_16 *)(0x1c005928)) = 0xB064;
}





