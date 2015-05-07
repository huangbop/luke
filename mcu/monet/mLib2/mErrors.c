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
#define   INSTANTIATE_MERRORS
#include "mErrors.h"

struct sHSTATUS_HERROR mHStatusHError[] =
{
    {0x00,0x00},       //     0  No Error
    {0x01,0x03},       //     1  DRAM Test Fail  
    {0x21,0x00},       //     2  Drive fault  
    {0x01,0x80},       //     3  Interface CRC Error
    {0x01,0x01},       //     4  Address Mark Not Found
    {0x01,0x02},       //     5  Track 0 Not Found
    {0x01,0x10},       //     6  ID Not Found
    {0x04,0x00},       //     7  Correctable Data 
    {0x01,0x40},       //     8  Uncorrectable Data Error
    {0x01,0x04},       //     9  Abort Command
    {0x01,0x04},       //     A  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //     B  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //     C  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //     D  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //     E  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //     F  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //    10  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //    11  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //    12  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //    13  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //    14  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x40},       //    15  Uncorrectable Data Error
    {0x01,0x04},       //    16  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //    17  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //    18  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //    19  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //    1A  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //    1B  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //    1C  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //    1D  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //    1E  Abort Command - for generic error (mEC_ERROR)
    {0x01,0x04},       //    1F  Abort Command - for generic error (mEC_ERROR)
};    

/*******************************************************************
*																   
*  NAME:   	    mErrorGetHstatusError 											   
*															   
*  FILENAME:    mErrors.c 											   
*															   
*  DESCRIPTION: Returns a pointer to the host status and error for a given internal error code.
*
*  PARAMETERS:  Error Code     											   
*															   
*  RETURNS:     Pointer to host status and error   
*
*  date         by              description
*  9/25/02      Roger Sha       Initial Release    											   
*	
********************************************************************/
struct sHSTATUS_HERROR*  mErrorGetHstatusError(mtERROR errorCode)
{
    mUINT_NATIVE   eCode = (mUINT_NATIVE) errorCode;

    // Since each group of error code is given 256 (0xff) slots....
    return (&mHStatusHError[(mINT_16)(eCode >> 0x08)]);
}
