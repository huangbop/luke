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

#ifndef     _MPARAMS_H_INC
  #define   _MPARAMS_H_INC


#include "mGLOBALS.h"
#include "Conds.h"

#ifdef      EXTERN
  #undef    EXTERN
#endif

#ifdef      INSTANTIATE_MPARAMS
  #define   EXTERN
#else
  #define   EXTERN extern
#endif

/*----------------------------------------------------------------------------
    Public data structure definitions and defines
 ---------------------------------------------------------------------------*/
  
typedef enum
{
    mPOWER_UP_STATE = 0         ,
    mRESET_STATE                ,         // 1 
    mQCMD_NON_EXE_ERROR_STATE   ,         // 2
    mQCMD_EXE_ERROR_STATE       ,         // 3
    mINTF_ERROR_STATE           ,         // 4
    mDFPDMAQ13_STATE            ,         // 5 - wait for host to send readlogext or srst
    mDFPDMAQ14_STATE            ,         // 6 - after readlogext page 10h transition to this state (sendQueue_CleanAck)
    mFAULT_ERROR_STATE          ,         // 7 - exe error but due to faulty parity set?
    mPOWERDOWN_FLUSH = 0xff,
} mtCURRENT_STATE;


typedef struct
{
    mtCURRENT_STATE   curState;
    union
    {
        mUINT_16 all;
        struct
        {
            mUINT_16   ramDiskOnly     : 1;        // 1: indicates that all r/w operations are to be only to RAM-DISK
            mUINT_16   disGPIOmsg      : 1;        // 1: disables the sending of GPIO message packets
            mUINT_16   printfOn        : 1;        // 1: Printf() is enabled to TX over UART. 0: disabled.
            mUINT_16   nativeMode      : 1;        // 1: Enable native mode
     
            mUINT_16   multipleCmdMode : 1;        // 1: Command multiple mode
            mUINT_16   reserved        : 11;
        }bits;
    } uFlags; 
} mtSYSTEM_STATE;


/*----------------------------------------------------------------------------
 Public Data (other modules can use these vars by including this .h file:
 ---------------------------------------------------------------------------*/
EXTERN mtSYSTEM_STATE  mSystemState;

#endif  //_H_INC
