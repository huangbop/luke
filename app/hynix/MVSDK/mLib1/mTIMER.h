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
#ifndef  	_mTIMER_H_INC
  #define   _mTIMER_H_INC
            
#include "mGLOBALS.h"

#ifdef      EXTERN
  #undef    EXTERN
#endif

#ifdef      INSTANTIATE_SYMBOLS_TIMER_REGS	        // symbols for UART Chip
  #define   EXTERN
#else
  #define   EXTERN extern
#endif

#define mCOUNTER_ENABLE_ONE_SHOT            0x00    // start fr enable one shot, 
#define mCOUNTER_ENABLE_CONTINUOS           0x01    // start fr enable re-trigger
#define mCOUNTER_TRIGGER_SOURCE_ONE_SHOT    0x10    // start fr trigger_source one-shot
#define mCOUNTER_TRIGGER_SOURCE_CONTINOUS   0x11    // start fr trigger_source re-trigger

typedef union
{
    mUINT_16 all;
    struct
    {
        mUINT_16 countEnable        : 1;        // bit 0
        mUINT_16 counterActive      : 1;        // bit 1
        
        mUINT_16 counterMode        : 2;        // bit 3,2
                                                // mCOUNTER_ENABLE_ONE_SHOT 00 start fr enable one shot, 
                                                // mCOUNTER_ENABLE_CONTINUOS 01 start fr enable re-trigger
                                                // mCOUNTER_TRIGGER_SOURCE_ONE_SHOT 10 start fr trigger_source one-shot
                                                // mCOUNTER_TRIGGER_SOURCE_CONTINOUS 11 start fr trigger_source re-trigger
        mUINT_16 triggerSource      : 4;        // bit 7..4
                                                // 0000 servo gate
                                                // 0001 sector pulse
                                                // 0010 index pulse
                                                // 0011 servo interrupt
                                                // 0100 Counter 1 end count
                                                // 0101 Counter 2 end count
                                                // 0110 HDC interrupt
                                                // 0111 Peripheral interrupt
                                                // 1000 Reserved
                                                // 1001 Reserved
                                                // 1010 Reserved
                                                // 1011 Reserved
                                                // 1100 Reserved
                                                // 1101 Reserved
                                                // 1110 Reserved
                                                // 1111 Reserved
        
        mUINT_16 conterPrescaler    :   8;      // bit 15..8 
    }bits;
} mtCOUNTER;


typedef struct 
{
    mUINT_16    padRA200;           // Reg A200h 
    mtCOUNTER   counter0;           // Reg A202h
    
    mUINT_16    counter0_value_lo;  // Reg A204h
    mUINT_16    counter0_value_hi;  // Reg A206h

    mUINT_16    reserved1;          // Reg A208h
    
    mtCOUNTER   counter1;           // Reg A20ah
    mUINT_16    counter1_value_lo;  // Reg A20ch
    mUINT_16    counter1_value_hi;  // Reg A20eh
    mUINT_16    reserved3;          // Reg A210h
    
    mtCOUNTER   counter2;           // Reg A212h
    mUINT_16    counter2_value_lo;  // Reg A214h
    mUINT_16    counter2_value_hi;  // Reg A216h
    mUINT_16    reserved5;          // Reg A218h
    
    mtCOUNTER   counter3;           // Reg A21ah
    
    mUINT_16    counter3_value_lo;  // Reg A21ch
    mUINT_16    counter3_value_hi;  // Reg A21eh
    
    mUINT_16    reserved7;          // Reg A220h
    mtCOUNTER   counter4;           // Reg A222h

#if(0) // (mSOC == m9187)
    mUINT_16    counter4_value_lo;  // Reg A224h
    mUINT_16    counter4_value_hi;  // Reg A226h

#else    
    mUINT_16    counter4_value;     // Reg A224h
    mUINT_16    rsvdA226;           // Reg A226
#endif    
    mUINT_16    rsvdA227[4];        // Reg A226h - A22Eh
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16 cntrTbgDivSel  :3;
            mUINT_16 rsvd3          :1;
            mUINT_16 cntrTbgSel     :1;
            mUINT_16 cntrClkDis     :1;
            mUINT_16 cntrClkSel     :1;
            mUINT_16 rsvd15_7       :9;
        } bits;
    } counterClkCtrl;               // Counter Clock control RA230h
}mtSOC_TIMER;




#ifdef __ghs__
    #pragma ghs section bss = ".rSOC_TIMER"
    EXTERN  volatile  mtSOC_TIMER  rTimer;
    #pragma ghs section
#else  
    #pragma arm section zidata = "rSOC_TIMER"
    EXTERN  volatile  mtSOC_TIMER  rTimer;
    #pragma arm section zidata
#endif    


/*----------------------------------------------------------------------------
    Public data structure definitions and defines
 ---------------------------------------------------------------------------*/


/*******************************************************************
*															   
*  NAME:        mTIMERclkCtrlInit    												   
*
*  FILENAME:    mTIMER.h 
*
*  PARAMETERS:  type mUINT_16 bits
*
*  DESCRIPTION: HAl function to initialize the Counter Clock Control  
*
*  RETURNS:     None
*
********************************************************************/
__inline void mTIMERclkCtrlInit(mUINT_16 bits)  
{
    rTimer.counterClkCtrl.all = bits;
}

/*******************************************************************
*																   
*  NAME:   	    mTIMERclockSelect											   
*																   
*  FILENAME:    mUART.h 											   
*																   
*  PARAMETERS:  None      											   
*																   
*  DESCRIPTION: Selects clock for TIMERS
*               - 0 : CPU clock 
*               - 1 : Oscilator clock 
*																   
*  RETURNS:     None      											   
*	
********************************************************************/
__inline void mTIMERclockSelect(mtBOOLEAN sel)                
{
    rTimer.counterClkCtrl.bits.cntrClkSel = sel; 
}        


#endif //mTIMER_H_INC
