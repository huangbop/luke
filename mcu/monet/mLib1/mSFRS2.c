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
#define   INSTANTIATE_SFRS2
#include "mSFRS2.h"

/*******************************************************************
*																   
*  NAME:            mSFR2gpioDataInit    												   
*
*  FILENAME:        mSFRS2.c
*
*  PARAMETERS:      type UINT_16 value
*
*  DESCRIPTION:    API function to load the GPIO data register 
*                  with the contents of the 'value' parameter.
*                  These bits are driven onto the GPIO pins.
*
*  RETURNS:        None
*
********************************************************************/
INLINE void mSFR2gpioDataInit(mUINT_16 value1, mUINT_16 value2)
{
    rSFRS2.testOut.all = value1;
    rSFRS2.testIOext.all = value2;
}

/*******************************************************************
*																   
*  NAME:            mSFR2gpioDirInit    												   
*
*  FILENAME:        mSFRS2.c
*
*  PARAMETERS:      type UINT_16 value
*
*  DESCRIPTION:     API function to load the GPIO direction register 
*                   with the contents of the 'value' parameter.
*                   Loading a '1' to any bit position designates the
*                   falling edge of the corresponding GPIO bit sets
*                   the interrupt for that bit. '0' = rising edge. 
*
*  RETURNS:         None
*
********************************************************************/
INLINE void mSFR2gpioDirInit(mUINT_16 value1, mUINT_16 value2) 
{
    rSFRS2.ioControl.all = value1;
    rSFRS2.ioControlExt.all = value2;
}

/*******************************************************************
*																   
*  NAME:            mSFR2gpioCtrlExtGet   												   
*
*  FILENAME:        mSFRS2.c
*
*  PARAMETERS:      none
*
*  DESCRIPTION:     return the value in register test pin IO control extended
*
*  RETURNS:         type UINT_16 value
*
********************************************************************/
INLINE mUINT_16 mSFR2gpioCtrlExtGet(void) 
{
    return (rSFRS2.ioControlExt.all);
}

/*******************************************************************
*																   
*  NAME:            mSFR2gpioDataExtGet   												   
*
*  FILENAME:        mSFRS2.c
*
*  PARAMETERS:      none
*
*  DESCRIPTION:     return the value in register test pin IO extended
*
*  RETURNS:         type UINT_16 value
*
********************************************************************/
INLINE mUINT_16 mSFR2gpioDataExtGet(void) 
{
    return (rSFRS2.testIOext.all);
}

/*******************************************************************
*																   
*  NAME:            mSFR2gpioDataExtNewInGet   												   
*
*  FILENAME:        mSFRS2.c
*
*  PARAMETERS:      none
*
*  DESCRIPTION:     return the value in register test pin IO extended
*                   This is at the new location for the Ext
*
*  RETURNS:         type UINT_16 value
*
********************************************************************/
INLINE mUINT_16 mSFR2gpioDataExtNewInGet(void) 
{
    return (rSFRS2.testInExt);
}

/*******************************************************************
*																   
*  NAME:            mSFR2gpioDataSet
*
*  FILENAME:        mSFRS2.c
*
*  PARAMETERS:      type UINT_16 value
*
*  DESCRIPTION:     set register test out
*
*  RETURNS:         none
*
********************************************************************/
INLINE void mSFR2gpioDataSet(mUINT_16 bits) 
{
    rSFRS2.testOut.all |= bits;
}

/*******************************************************************
*																   
*  NAME:            mSFR2gpioDataClr    												   
*
*  FILENAME:        mSFRS2.c
*
*  PARAMETERS:      type UINT_16 value
*
*  DESCRIPTION:     set register test out
*
*  RETURNS:         none
*
********************************************************************/
INLINE void mSFR2gpioDataClr(mUINT_16 bits) 
{
    rSFRS2.testOut.all &= ~bits;
}

/*******************************************************************
*																   
*  NAME:        mSFR2gpioCtrlExtSet    												   
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  type mUINT_16 bits
*
*  DESCRIPTION: API function to set the control extended IO register 
*               with the contents of the 'bits' parameter.
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2gpioCtrlExtSet (mUINT_16 bits)
{
    rSFRS2.ioControlExt.all |= bits;
}

/*******************************************************************
*																   
*  NAME:            mSFR2gpioCtrlExtClr    												   
*
*  FILENAME:        mSFRS2.c
*
*  PARAMETERS:      type UINT_16 value
*
*  DESCRIPTION:     API function to clear the control extended IO register 
*                   with the contents of the 'bits' parameter.
*
*  RETURNS:         none
*
********************************************************************/
INLINE void mSFR2gpioCtrlExtClr(mUINT_16 bits) 
{
    rSFRS2.ioControlExt.all &= ~bits;
}

/*******************************************************************
*																   
*  NAME:        mSFR2gpioCtrlExtNewSet    												   
*
*  FILENAME:    mSFRS2.c
*
*  PARAMETERS:  type mUINT_16 bits
*
*  DESCRIPTION: API function to set the control extended IO register 
*               with the contents of the 'bits' parameter.
*               This is at the new location for the Ext
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2gpioCtrlExtNewSet (mUINT_16 bits)
{
    rSFRS2.testOeExt |= bits;
}

INLINE void mSFR2gpioTestOutExtSet(mUINT_16 bits)
{
    rSFRS2.testOutExt |= bits;
}

INLINE void mSFR2gpioTestOutExtClr(mUINT_16 bits)
{
    rSFRS2.testOutExt &= ~bits;
}

INLINE void mSFR2gpioCtrlSet(mUINT_16 bits) 
{
    rSFRS2.ioControl.all |= bits;
}

/*******************************************************************
*																   
*  NAME:        mSFR2gpioCtrlExtNewClr    												   
*
*  FILENAME:    mSFRS2.c
*
*  PARAMETERS:  type UINT_16 value
*
*  DESCRIPTION: API function to clear the control extended IO register 
*               with the contents of the 'bits' parameter.
*               This is at the new location for the Ext
*
*  RETURNS:     none
*
********************************************************************/
INLINE void mSFR2gpioCtrlExtNewClr(mUINT_16 bits) 
{
    rSFRS2.testOeExt &= ~bits;
}

INLINE void mSFR2gpioCtrlClr(mUINT_16 bits) 
{
    rSFRS2.ioControl.all &= ~bits;
}


/*******************************************************************
*																   
*  NAME:        mSFR2gpioDataExtSet    												   
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  type mUINT_16 bits
*
*  DESCRIPTION: API function to set the data extended IO register 
*               with the contents of the 'bits' parameter.
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2gpioDataExtSet (mUINT_16 bits)
{
    rSFRS2.testIOext.all |= bits;
}

/*******************************************************************
*																   
*  NAME:            mSFR2gpioDataExtClr    												   
*
*  FILENAME:        mSFRS2.c
*
*  PARAMETERS:      type UINT_16 value
*
*  DESCRIPTION:     API function to clear the data extended IO register 
*                   with the contents of the 'bits' parameter.
*
*  RETURNS:         none
*
********************************************************************/
INLINE void mSFR2gpioDataExtClr(mUINT_16 bits) 
{
    rSFRS2.testIOext.all &= ~bits;
}

/*******************************************************************
*																   
*  NAME:        mSFR2gpioDataExtNewInSet    												   
*
*  FILENAME:    mSFRS2.c
*
*  PARAMETERS:  type mUINT_16 bits
*
*  DESCRIPTION: API function to set the data extended IO register 
*               with the contents of the 'bits' parameter.
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2gpioDataExtNewInSet (mUINT_16 bits)
{
    rSFRS2.testInExt |= bits;
}

/*******************************************************************
*																   
*  NAME:            mSFR2gpioDataExtNewInClr    												   
*
*  FILENAME:        mSFRS2.c
*
*  PARAMETERS:      type UINT_16 value
*
*  DESCRIPTION:     API function to clear the data extended IO register 
*                   with the contents of the 'bits' parameter.
*
*  RETURNS:         none
*
********************************************************************/
INLINE void mSFR2gpioDataExtNewInClr(mUINT_16 bits) 
{
    rSFRS2.testInExt &= ~bits;
}

/*******************************************************************
*																   
*  NAME:        mSFRgpiotDataToggle    												   
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  type mUINT_16 bit
*
*  DESCRIPTION: API function to toggle the GPIO bits corresponding to
*               those set in the 'bit' parameter. 
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFRgpioDataToggle(mUINT_16 bit)
{
    //mUINT_NATIVE i;

    rSFRS2.testOut.all ^= bit;
    //for (i=0x4; i>0; i--);
    rSFRS2.testOut.all ^= bit;
}

/*******************************************************************
*                                                                  
*  NAME:        mSFR2gpioDataGet
*
*  FILENAME:    mSFRS.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to get the value on the pins
*
*  RETURNS:     None
*
********************************************************************/
INLINE mUINT_NATIVE mSFR2gpioDataGet (void)
{
    return rSFRS2.testIn.all;
}

/*******************************************************************
*
*  NAME:        mSFR2setStepDnCntl0
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2setStepDnCntl0(mUINT_16 val)
{
    rSFRS2.stepdownCntl0.all |= val;
}

/*******************************************************************
*
*  NAME:        mSFR2initStepDnCntl0
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2initStepDnCntl0(mUINT_16 val)
{
    rSFRS2.stepdownCntl0.all = val;
}

/*******************************************************************
*
*  NAME:        mSFR2clrStepDnCntl0
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2clrStepDnCntl0(mUINT_16 val)
{
    rSFRS2.stepdownCntl0.all &= ~val;
}

/*******************************************************************
*
*  NAME:        mSFR2setStepDnCntl1
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2setStepDnCntl1(mUINT_16 val)
{
    rSFRS2.stepdownCntl1.all |= val;
}

/*******************************************************************
*
*  NAME:        mSFR2initStepDnCntl1
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2initStepDnCntl1(mUINT_16 val)
{
    rSFRS2.stepdownCntl1.all = val;
}

/*******************************************************************
*
*  NAME:        mSFR2clrStepDnCntl1
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2clrStepDnCntl1(mUINT_16 val)
{
    rSFRS2.stepdownCntl1.all &= ~val;
}


/*******************************************************************
*
*  NAME:        mSFR2setStepDnCntl2
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2setStepDnCntl2(mUINT_16 val)
{
    rSFRS2.stepdownCntl2.all |= val;
}

/*******************************************************************
*
*  NAME:        mSFR2initStepDnCntl2
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2initStepDnCntl2(mUINT_16 val)
{
    rSFRS2.stepdownCntl2.all = val;
}

/*******************************************************************
*
*  NAME:        mSFR2clrStepDnCntl2
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2clrStepDnCntl2(mUINT_16 val)
{
    rSFRS2.stepdownCntl2.all &= ~val;
}


/*******************************************************************
*
*  NAME:        mSFR2setStepDnCntl3
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2setStepDnCntl3(mUINT_16 val)
{
    rSFRS2.stepdownCntl3.all |= val;
}

/*******************************************************************
*
*  NAME:        mSFR2initStepDnCntl3
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2initStepDnCntl3(mUINT_16 val)
{
    rSFRS2.stepdownCntl3.all = val;
}

/*******************************************************************
*
*  NAME:        mSFR2clrStepDnCntl3
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2clrStepDnCntl3(mUINT_16 val)
{
    rSFRS2.stepdownCntl3.all &= ~val;
}


/*******************************************************************
*
*  NAME:        mSFR2setStepDnCntl4
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2setStepDnCntl4(mUINT_16 val)
{
    rSFRS2.stepdownCntl4.all |= val;
}

/*******************************************************************
*
*  NAME:        mSFR2initStepDnCntl4
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2initStepDnCntl4(mUINT_16 val)
{
    rSFRS2.stepdownCntl4.all = val;
}

/*******************************************************************
*
*  NAME:        mSFR2clrStepDnCntl4
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2clrStepDnCntl4(mUINT_16 val)
{
    rSFRS2.stepdownCntl4.all &= ~val;
}


/*******************************************************************
*
*  NAME:        mSFR2setStepDnCntl5
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2setStepDnCntl5(mUINT_16 val)
{
    rSFRS2.stepdownCntl5.all |= val;
}

/*******************************************************************
*
*  NAME:        mSFR2initStepDnCntl5
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2initStepDnCntl5(mUINT_16 val)
{
    rSFRS2.stepdownCntl5.all = val;
}

/*******************************************************************
*
*  NAME:        mSFR2clrStepDnCntl5
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  type mUINT_16 val
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2clrStepDnCntl5(mUINT_16 val)
{
    rSFRS2.stepdownCntl5.all &= ~val;
}



/*******************************************************************
*																   
*  NAME:        mSFR2getStepDnCntl2
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  None
*
*  DESCRIPTION: Refer to the function name
*
*  RETURNS:     mUINT_16
*
********************************************************************/
INLINE mUINT_16 mSFR2getStepDnCntl2(void) 
{
    return rSFRS2.stepdownCntl2.all;
}


/*******************************************************************
*																   
*  NAME:        mSFR2initXmClk
*
*  FILENAME:    mSFRS2.h
*
*  PARAMETERS:  mUINT_16 divider, TBG select, Clock Select
*              
*
*  DESCRIPTION: HAL function to set the spin error time base generator divider   
*              
*
*  RETURNS:     None
*
********************************************************************/
INLINE void mSFR2initXmClk(mUINT_16 val)
{
    rSFRS2.clkDiv6.all     = val;
}

