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
#ifndef _m5540PRM_H_INC
#define _m5540PRM_H_INC

#include "mGLOBALS.h"
#include "CONDS.h"
//#include "Config.h"

#ifdef   EXTERN
#undef   EXTERN
#endif


/*----------------------------------------------------------------------------
    Public data structure definitions and defines
 ---------------------------------------------------------------------------*/
typedef struct
{
    mUINT_16     reserved[7];
    mUINT_16     revision;      // Upper byte: revision, lower byte: ID (e.g. VBPI)
} mtHEADER_PARAM_PAGE;

 
    #define mSECTOR_RATE    1
    
/*************************************************************
 PM Parameters Page
*************************************************************/
typedef struct
{
    mUINT_16            params0;            // 
    mUINT_16            params1;            // 
    union
    {
        mINT_16         all;
        struct
        {
            mUINT_16    enPm        : 1;
            mUINT_16    enAutoPm    : 1;
            mUINT_16    enDIPM      : 1;
            mUINT_16    enPwrUpInStdby: 1;
			mUINT_16    DIPMen      : 1;
			mUINT_16    HIPMen      : 1;
            mUINT_16    reserved    : 10;   // reserved
        } bits;
    } cntlFlags;
    
    mUINT_16            reserved;
} mtPARAM_PM_PARAMS;


typedef struct
{
    mtHEADER_PARAM_PAGE     header;
    mtPARAM_PM_PARAMS       params;
    // other param structs
} mtPARAM_PM_PAGE;

/*************************************************************
 HBI Parameters Page
*************************************************************/
typedef struct
{
    mUINT_16        mode0;
    mUINT_16        intrSrcs;
    mUINT_16        devCntl;
    mUINT_16        aceWr;
    mUINT_16        aceRd;
    mUINT_16        hdPerCyl;
    mUINT_16        secPerTrk;
    
    mUINT_16        devCntl_1;
    mUINT_16        hostBufferSegSel;

    mUINT_16        qcmdCntrl;
    mUINT_16        qcmdInt;
    mUINT_16        esataErrint;
    mUINT_16        tmIntsrc;
    mUINT_16        esataCnfg;
    mUINT_16        reserved[1];


    union
    {
        mINT_16     all;
        struct
        {
            mUINT_16    flag0   : 1;
            mUINT_16    flag1   : 1;
        } bits;
    } cntlFlags;
    
} mtPARAM_HBI_PARAMS;


typedef struct
{
    mtHEADER_PARAM_PAGE      header;
    mtPARAM_HBI_PARAMS       params;
    // other param structs
} mtPARAM_HBI_PAGE;



/*----------------------------------------------------------------------------
 Public Data (other modules can use these vars by including this .h file:
 ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 Public Function Prototypes (other modules can use these functions by
 including this .h file):
 ---------------------------------------------------------------------------*/

#endif  //_H_INC
