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

#ifndef     _MERRORS_H_INC
  #define   _MERRORS_H_INC
            

#include "mGLOBALS.h"
#include "m5540prm.h"

#ifdef      EXTERN
  #undef    EXTERN
#endif

#ifdef      INSTANTIATE_MERRORS
  #define   EXTERN
#else
  #define   EXTERN extern
#endif


/*----------------------------------------------------------------------------
    Public data structure definitions and defines
 ---------------------------------------------------------------------------*/

// The error codes for this enum are reassigned. Now, each group is given 256 (0xff)
// slots to use. Bit 8 and higher bits are the group number which is used to index to other
// error handling data structure. Purpose of this arrange is to make the finding
// of the index is easier with a small+simple function (see mErrorGetHstatusError()).
// If you want to expand the group size, you may increase the number of bits for it. 
// For example, give it 10 bits to use (expand it from 0xff to 0x3ff). Then, bit 10
// and higher bits are group number. If you make this change, don't forget to change
// mErrorGetHstatusError().
typedef enum
{
    // group 0 errors
    mEC_NO_ERROR                    =  0,           // no error
    mEC_NOT_SUPPORTED               =  0x0f,        // not supported, general purpose

    // group 1 errors
    mEC_ABORTED_CMD                 = 0x0104,       // aborted cmd
    mEC_BUF_TEST_FAIL               = 0x0105,       // buffer test fail

    // group 2 errors
    mEC_FMT_DRV_FAULT               = 0x0210,       // Formatter drive fault
    mEC_WRITE_FAULT                 = 0x0211,       // Write Fault error
    mEC_STREAMING_CMD_TO            = 0x0280,       // streaming command timeout.
    mEC_ERR_IN_STREAMING            = 0x0281,       // error in streaming command 

    // group 3 errors
    mEC_CRC_ERROR                   = 0x0315,       // Interface CRC Error

    // group 4 errors
    mEC_ADDRMARK_NOT_FOUND          = 0x0420,       // address mark not found
    
    // group 5 errors
    mEC_TRK0_NOT_FOUND              = 0x0525,       // trk0 not found

    // group 6 errors
    mEC_ID_NOT_FOUND                = 0x0630,       // id not found
    mEC_SBYTE_TIMEOUT               = 0x0631,       // Sbyte time out error
    
    // group 7 errors
    mEC_CORR_ERROR                  = 0x0735,       // correctable error

    // group 8 errors
    mEC_UNCORR_ERROR                = 0x0840,       // uncorrectable error

    // group 9 errors                               // all abort command
    mEC_FLASH_WRITE_ERROR           = 0x0900,       // Write to flash error
    
    mEC_INV_COMMAND                 = 0x0950,       // invalid command
    mEC_SPN_NO_COMM                 = 0x0951,       // No commutation detected at spindle start
    mEC_SPN_NO_START                = 0x0952,       // Spindle unable to start up.
    mEC_SPN_NO_UP_SPD               = 0x0953,       // Spindle unable reach product speed
    mEC_SPN_BAD_STAGE2              = 0x0954,       // Spindle stage 2 failed (Phased COMM accel).
    mEC_SPN_BAD_STAGE3              = 0x0955,       // Spindle stage 3 failed (Closed COMM accel).
    mEC_SPN_ILLEGAL_STAGE           = 0x0956,       // Spindle ISR was commanded to sequence to illegal stage
    mEC_COMBO_FAIL_SVOCAL           = 0x0957,       // Combo failed VCM offset or Coil Rm cancellation

    mEC_INV_COMMAND_SYS_BUSY        = 0x0958,       // invalid command, system is busy with background operations.
    mEC_INV_COMMAND_SYS_DOWN        = 0x0959,       // invalid command, system is down due to failsafe.
    mEC_INV_COMMAND_PRE_ERR         = 0x095A,       // invalid command, system has P_ERR while decoding.
    mEC_INV_COMMAND_Q14             = 0x095B,       // invalid command, system is in DFPDMAQ14_STATE, waiting for READLOG EXT 10h.

    // Servo Errors
    mEC_SVO_NO_SGATE                = 0x0960,       // No Servo Gate detected from the state machine           
    mEC_SVO_NO_SMARK                = 0x0961,       // No SIM/SAM detected during push out           
    mEC_SVO_LOST_LOCK               = 0x0962,       // Had synchronized to the wedge and then lost it
    mEC_SVO_DRV_FAULT               = 0x0963,       // Servo drive fault
    mEC_SVO_OFF_TRK                 = 0x0964,       // Servo off track
    mEC_SVO_SHOCK_FAULT             = 0x0965,       // Servo shock fault
    mEC_SVO_HD_LOAD_FLT             = 0x0966,       // Unable to load heads 
    mEC_SVO_HD_UNLOAD_FLT           = 0x0967,       // Unable to unload heads
    mEC_BUMP_ERROR                  = 0x0968,       // Offtrk error during read

    mEC_SVO_SK_ERROR                = 0x0969,       // Seek Incomplete error 
    mEC_SVO_SK_TIMEOUT              = 0x096A,       // Seek Timeout error 

    mEC_SVO_FATAL_RECOVER           = 0x096B,       // Went through fatal servo recovery and recovered. 
    mEC_SVO_FATAL_UNRECOVER         = 0x096C,       // Went through fatal servo recovery and did not recover. 
    mEC_SVO_REC_IN_PROGRESS         = 0x096D,

    // Read / Write Errors
    mEC_WRITE_SYSTEM                = 0x0980,       // Error in writing to system sector.
    mEC_READ_SYSTEM                 = 0x0981,       // Error in reading from a system sector.
    mEC_UNKNOWN_FILE_ID             = 0x0982,       // Unknow file id
    mEC_INV_CDB                     = 0x0983,       // Invalid CDB error 
    mEC_INV_PROTOCOL                = 0x0984,       // Invalid Protocol error 
    mEC_INV_OPCODE                  = 0x0985,       // Invalid Opcode
    mEC_SEC_PULSE_RG                = 0x0986,       // next sector pulse is asserted during the current sector read 
    mEC_SEC_PULSE_WR                = 0x0987,       // next sector pulse is asserted during the current sector write 
    mEC_FIFO_OVER_UNDER             = 0x0988,       // FIFO Overrun/Underrun
    mEC_RETRY_TIMEOUT               = 0x0989,       // Retry Timeout
    mEC_READ_SYSTEM_CHKSUM          = 0x098A,       // Error in reading from a system sector.
    mEC_READ_SYSTEM_WRONG_ID        = 0x098B,       // Error in reading from a system sector.
    mEC_WRITE_SYSTEM_BAD_ID         = 0x098C,       // Error in writing to system sector.
    mEC_SPLT_EN_TIMEOUT             = 0x0990,       // Split Enable Timeout
    mEC_SAIL_ERROR                  = 0x0991,       // Sail Error 
    mEC_TA_ERROR                    = 0x0992,       // TA detected error 
    mEC_SPLIT_EN_TIMEOUT            = 0x0993,       // Split enable timeout 
    mEC_DM_NOT_ACTIVE               = 0x0994,       // DM Inactive error
    mEC_BUF_NOT_RDY                 = 0x0995,       // Buffer not ready error
    mEC_UNKNOWN_ERROR               = 0x0996,       // Formatter unknown error
    mEC_INV_PARAMETER               = 0x0997,       // invalid command parameters
    mEC_DFCT_LIST_FULL              = 0x0998,       // defect list full
    mEC_NO_MORE_SPARE               = 0x0999,       // no more spare
    mEC_EVENT_TIMEOUT               = 0x099A,       // Event timeout during disktrackreadwrite

    // memory allocation/free errors.
    mEC_MEM_EXHAUST                 = 0x09a0,       // memory pool is exhausted.
    mEC_MEM_ALLOC                   = 0x09a1,       // memory allocation failed.
    mEC_MEM_FREE                    = 0x09a2,       // memory free failed.
    mEC_MEM_REQ_ZERO                = 0x09a3,       // User requested to allocate 0 byte memory.
    
    // Servo zone calibration errors
    mEC_BASIC_SEEK                  = 0x09b4,       // Incomplete basic or calibration seek error 
    mEC_RRO_CAL                     = 0x09b5,       // RRO cal error
    mEC_BIAS_CAL                    = 0x09b6,       // Bias cal error
    mEC_PES_CAL                     = 0x09b7,       // PES cal error
    mEC_GAMMA_CAL                   = 0x09b8,       // GAMMA cal error
    mEC_PES_LIN_CAL                 = 0x09b9,       // PES_LIN cal error
    mEC_GRAB_TRACK                  = 0x09ba,       // Grab track error    
    mEC_VCM_DAC_CENTER_CAL          = 0x09bb,       // VCM_DAC_CENTER cal error
    mEC_ARF_PHASE_CAL               = 0x09bc,       // ARF phase cal error
    mEC_SERVO_DEAD                  = 0x09bd,       // Servo dead
#if (EXT_PES_CAL == mENABLE)
    mEC_EXTRA_PES_CAL               = 0x09be,       // PES cal error    
#endif //(EXT_PES_CAL == mENABLE)

    // Esata Error - maynot be a good place to put it ... for now only - Kim
    mEC_eSATA_rxCrcErr              = 0x09c0,
    mEC_eSATA_rxFlowErr             = 0x09c1,
    mEC_eSATA_rxLengthErr           = 0x09c2,
    mEC_eSATA_txRerrDet             = 0x09c3,
    mEC_eSATA_txFlowErr             = 0x09c4,
    mEC_eSATA_tmFifoErr             = 0x09c5,
    mEC_eSATA_RxFlowPause           = 0x09c6,
    mEC_eSATA_linkDisparityErr      = 0x09c7,
    mEC_eSATA_linkCodeErr           = 0x09c8,
    mEC_eSATA_linkHung              = 0x09c9,
    mEC_eSATA_reTxErr               = 0x09ca,
    mEC_eSATA_rxIllegalFis          = 0x09cb,
    mEC_eSATA_qCmdExeErr            = 0x09cc,
    mEC_eSATA_rxRerrDet             = 0x09cd,
    mEC_eSATA_errDet                = 0x09ce,

    // streaming cmds errors
    mEC_INV_ERR_LBA                 = 0x09d0,      // invalid err lba.
    mEC_UNCONFIGURED_STREAM_ID      = 0x09d1,      // stream ID uncofigured.
    mEC_CCTL                        = 0x09d2,      // can not support this CCTL.
    mEC_ALLOC_UNIT                  = 0x09d3,      // can not support this drive config.
    mEC_TIMER                       = 0x09d4,      // no timer resource available. Used up all the available timer.

    mEC_BI_GENERIC_ERROR            = 0x0A00,   // error code squatter for burnin
    mEC_BI_SYS_OUTPUT_FULL          = 0x0A01,
    mEC_BI_SYS_NO_MEM               = 0x0A02,
    mEC_BI_RESTART_READ             = 0x0A03,   // restart event in read
    
// serial flash error    
    mEC_SF_SEND_ERR                 = 0x0A10,
    mEC_SF_GET_ERR                  = 0x0A11,
    mEC_SF_MID_ERR                  = 0x0A12,   // manufacturer ID error
    mEC_SF_DID_ERR                  = 0x0A13,   // device ID error

    mEC_SF_CMP_ERR                  = 0x0A14,
    mEC_SF_WR_LATCH_ENABLE_ERR      = 0x0A15,
    mEC_SF_ERASE_ERR                = 0x0A16,
    mEC_SF_WRITE_PAGE_ERR           = 0x0A17,
    mEC_NO_SF_DEVICE                = 0x0A18,
    mEC_SF_BAD_FW                   = 0x0A20,

    //group 10 errors
    
    //group 11 errors

    // 0x1200 - 0x2000 reserved for NV project
    //group 12 errors
    mEC_NV_DEVICE_WRITE_FAILURE     = 0x1200,
    mEC_NV_DEVICE_ERASE_FAILURE     = 0x1201,
    mEC_NV_PAGE_OVRMLT              = 0x1206,
    mEC_NV_COL_OVRLMT               = 0x1207,
    mEC_NV_AUX_DATA_MISMATCH        = 0x1208,
    mEC_NV_DEFECT_LIST_FULL         = 0x1210,
    mEC_NV_GROWN_DEFECT             = 0x1211,
    mEC_NV_BAD_DEFECT_LIST0         = 0x1212,
    mEC_NV_BAD_DEFECT_LIST1         = 0x1213,
    mEC_NV_BAD_DEFECT_LIST2         = 0x1214,
    mEC_NV_BAD_DEFECT_LIST3         = 0x1215,
    mEC_NV_BAD_DEFECT_LIST4         = 0x1216,
    
    
    mEC_NV_INIT_LUT_WRITE_FAIL      = 0x1220,
    mEC_NV_INIT_NVIIB_WRITE_FAIL    = 0x1221,
    mEC_NV_INIT_SYSLT_WRITE_FAIL    = 0x1222,
    mEC_NV_INIT_WERU_0_BAD          = 0x1223,
    mEC_NV_INIT_NVIIB_READ_FAIL     = 0x1224,
    mEC_NV_INIT_RVS_LUT_WRITE_FAIL  = 0x1225,
    mEC_NV_PWRUP_BAD_DEVICES        = 0x1230,
    mEC_NV_PWRUP_LOW_CAPACITY       = 0x1231,
    mEC_NV_PWRUP_BAD_QUEUE          = 0x1232,
    mEC_NV_PWRUP_BAD_PARTIAL_QUEUE  = 0x1233,
    mEC_NV_PWRUP_BAD_VALID_QUEUE    = 0x1233,
    mEC_NV_FORMAT_LOW_CAPACITY      = 0x1240,
    mEC_NV_FORMAT_BAD_SYS_WERU      = 0x1241,
    
    
    //group 13 errors
    mEC_NV_PAA_WRITE_FAIL           = 0x1300,
    mEC_NV_PAA_READ_FAIL            = 0x1301,
    mEC_NV_PAA_ERASE_FAIL           = 0x1302,
    mEC_NV_FMT_CANT_READ_PAA        = 0x1303,
    mEC_NV_WERU_ERASE_FAIL          = 0x1304,
    mEC_NV_WERU_ERASE_EXCEED        = 0x1305,
    mEC_NV_FLSH_ABORTED             = 0x1306,

    //group 14 errors
    mEC_NV_OP_TIMEOUT               = 0x1400,
    mEC_NV_OP_AUX_FIFO_OVER         = 0x1401,
    mEC_NV_OP_AUX_FIFO_UNDER        = 0x1402,
    mEC_NV_OP_DES_FIFO_OVER         = 0x1403,

    //Group 15 errors will be reported as Uncorrectable errors
    //See errors.c:  KEEP READ ERROR in 0x1500, see NvTrkEpilog
    mEC_NV_PAGE_UNCORR_ERROR        = 0x1500,
    mEC_NV_COL_UNCORR_ERROR         = 0x1501,
    mEC_NV_PAGE_MCRC_ERROR          = 0x1502,
    
    mEC_NV_POWER_DOWN_ERROR         = 0x1602,
    mEC_NV_SEQ_STILL_ACTIVE         = 0x1603,
    mEC_NV_DDR_BIST_FAIL            = 0x1604,
    mEC_NV_NAND_BIST_FAIL           = 0x1605,
    
    mEC_NV_BAD_LUT                  = 0x1700,
    mEC_NV_BAD_WD                   = 0x1701,
    
        
    //group 1F errors
    mEC_NV_WRONG_SIGNATURE          = 0x1FF0,
    mEC_NV_WRONG_SYS_LAA_LAYOUT     = 0x1FF1,
    mEC_NV_CANNOT_READ_SYSLT        = 0x1FF2,
    mEC_NV_CANNOT_READ_WERUD        = 0x1FF3,
    mEC_NV_CANNOT_READ_LUT          = 0x1FF4,
    mEC_NV_CANNOT_READ_NVIIB        = 0x1FF5,
    mEC_NV_CANNOT_READ_GLOBALQ      = 0x1FF6,
    mEC_NV_CANNOT_READ_SYS_VEC      = 0x1FF7,
    mEC_NV_CANNOT_READ_BAD_PAA      = 0x1FF8,
    mEC_NV_ASSERT                   = 0x1FF9,

    mEC_FLUSH_INTERRUPTED_0         = 0xF000,
    mEC_FLUSH_INTERRUPTED_1         = 0xF001,
    mEC_ERROR                       = 0xFFFF    // Generic error. NOTE: This should always be the last one in last group.
}mtERROR;

struct sHSTATUS_HERROR
{
    mUINT_8 hStatus;
    mUINT_8 hError;
};

/*----------------------------------------------------------------------------
 Public Data (other modules can use these vars by including this .h file:
 ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 Public Function Prototypes (other modules can use these functions by
 including this .h file):
 ---------------------------------------------------------------------------*/
extern struct sHSTATUS_HERROR*  mErrorGetHstatusError(mtERROR errorCode);


#endif  //_*_H_INC
