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

#ifndef     _MHDC_H_INC
  #define   _MHDC_H_INC

#include "mGLOBALS.h"
#include "mREGS.h"

#ifdef      EXTERN
  #undef    EXTERN
#endif

#ifdef      INSTANTIATE_MHDC
  #define   EXTERN
#else
  #define   EXTERN extern
#endif

/*----------------------------------------------------------------------------
    Public data structure definitions and defines
 ---------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 Public Data (other modules can use these vars by including this .h file:
 ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 Public Function Prototypes (other modules can use these functions by
 including this .h file):
 ---------------------------------------------------------------------------*/
EXTERN __inline mUINT_16 mHDCgetIntrMask      (void); 
EXTERN __inline mUINT_16 mHDCgetIntrStatus    (void); 
EXTERN __inline void     mHDCClearIntrStatus  (void); 

EXTERN __inline void    mHDCreset           (mUINT_16 value);  
EXTERN __inline void    mHDCintrEnInit      (mUINT_16 value); 
EXTERN __inline void    mHDCintrEn          (mUINT_16 value);
EXTERN __inline void    mHDCintrDis         (mUINT_16 value);


#ifdef __ghs__
    #pragma ghs section bss = ".rHDC_HDC"
    EXTERN volatile  mtHDC_MPU rHDC;
    #pragma ghs section
#else  
    #pragma arm section zidata = "rHDC_HDC"
    EXTERN volatile  mtHDC_MPU rHDC;
    #pragma arm section zidata
#endif    

/*******************************************************************
*																   
*  NAME:        mHDCreset    												   
*
*  FILENAME:    mHDC.h
*
*  PARAMETERS:  type mUINT_16 value
*
*  DESCRIPTION: API function to momentarily load the HDC reset 
*               register with the contents of the 'value' parameter. 
*               A '1' bit will reset the corresponding functional
*               block.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHDCreset(mUINT_16 value)  
{
    rHDC.reset.all = value; 
    rHDC.reset.all = 0x0;
}

/*******************************************************************
*																   
*  NAME:        mHDCintrEnInit
*
*  FILENAME:    mHDC.h
*
*  PARAMETERS:  type mUINT_16 value
*
*  DESCRIPTION: API function to clear the bits in the HDC interrupt 
*               mask register marked in 'value' parameter. A negated  
*               'value' parameter is AND'd into the interrupt mask
*               register. Clearing a bit in this register enables 
*               it's corresponding interrupt.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHDCintrEnInit(mUINT_16 value) 
{
    rHDC.intrMask.all = (~value);
}

/*******************************************************************
*																   
*  NAME:        mHDCintrEn    												   
*
*  FILENAME:    mHDC.c
*
*  PARAMETERS:  type mUINT_16 value
*
*  DESCRIPTION: API function to clear the bits in the HDC interrupt 
*               mask register marked in 'value' parameter. A negated  
*               'value' parameter is AND'd into the interrupt mask
*               register. Clearing a bit in this register enables 
*               it's corresponding interrupt.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHDCintrEn(mUINT_16 value) 
{
    rHDC.intrMask.all &= ~value;
}

/*******************************************************************
*																   
*  NAME:        mHDCintrDis    												   
*
*  FILENAME:    mHDC.c
*
*  PARAMETERS:  type mUINT_16 value
*
*  DESCRIPTION: API function to load the HDC interrupt mask register 
*               with the contents of the 'value' parameter.
*               Setting a bit in this register disables it's 
*               corresponding interrupt.
*
*  RETURNS:     None
*
********************************************************************/
__inline void mHDCintrDis(mUINT_16 value) 
{
    rHDC.intrMask.all |= value;
}

/*******************************************************************
*																   
*  NAME:        mHDCgetIntrMask    												   
*
*  FILENAME:    mHDC.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to return the contents of the HDC 
*               interrupt mask register. 
*
*  RETURNS:     type mUINT_16 HDC interrupt mask
*
********************************************************************/
__inline mUINT_16 mHDCgetIntrMask(void) 
{
    return rHDC.intrMask.all;
}

/*******************************************************************
*																   
*  NAME:        mHDCgetIntrStatus    												   
*
*  FILENAME:    mHDC.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to return the contents of the HDC 
*               interrupt status register. 
*
*  RETURNS:     type mUINT_16 HDC interrupt status
*
********************************************************************/
__inline mUINT_16 mHDCgetIntrStatus(void) 
{
    return rHDC.intrStatus.all;
}

/*******************************************************************
*																   
*  NAME:        mHDCgetIntrStatus    												   
*
*  FILENAME:    mHDC.c
*
*  PARAMETERS:  None
*
*  DESCRIPTION: API function to clear interrupt status
*
*  RETURNS:     nothing
*
********************************************************************/
__inline void mHDCClearIntrStatus(void) 
{
    rHDC.intrStatus.all = mHDCgetIntrStatus();
}
#endif // _H_INC
