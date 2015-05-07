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
// Must Put INSTANTIATE definition first!
#define  INSTANTIATE_MARVELL_HBI
#include "mHBI.h"
#include "mREGS.h"

/*----------------------------------------------------------------------------
 Private include files: Local only to this file
 ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 Private Data:
 ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 Private Prototypes:
 ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 Temporary include files: (should clean up eventually)
 ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 Functions
 ---------------------------------------------------------------------------*/


/*******************************************************************
*																   
*  NAME:        mHBIsetTaskFileReg    												   
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  type (enumerated) mtATA_TASK_FILE_REGS AtReg, 
*               type mUINT_8 value
*
*  DESCRIPTION: API function to write the AT task file register  
*               specified in the 'AtReg' parameter with the contents
*               of the 'value' parameter.
*
*  RETURNS:     None
*
********************************************************************/
void mHBIsetTaskFileReg (mtATA_TASK_FILE_REGS tfReg, mUINT_8 value)  
{
    volatile mtUNION_INT_16 *p;

    p = (void *)&rHBI;
     
    if (tfReg & 1)
        (p + (tfReg>>1))->bytes.msb=value;
    else   
        (p + (tfReg>>1))->bytes.lsb=value;
}

/*******************************************************************
*																   
*  NAME:        mHBIgetTaskFileReg    												   
*
*  FILENAME:    mHBI.c
*
*  PARAMETERS:  type (enumerated) mtATA_TASK_FILE_REGS AtReg
*
*  DESCRIPTION: API function to return the contents of the AT task   
*               file register specified in the 'AtReg' parameter.
*
*  RETURNS:     type UNIT_8 value task file reg
*
********************************************************************/
mUINT_8 mHBIgetTaskFileReg(mtATA_TASK_FILE_REGS tfReg)  
{
    volatile mtUNION_INT_16 *p;

    p=(void *)&rHBI;
      
    if(tfReg & 1)
       return((p+(tfReg>>1))->bytes.msb);
    else   
       return((p+(tfReg>>1))->bytes.lsb);
}


void mHBIsetTimeStampCountLow(mUINT_16 val)
{
    mHBIsetTimeStampCntLow(val);

}

void mHBIsetTimeStampCountHigh(mUINT_16 val)
{
    mHBIsetTimeStampCntHigh(val);

}

