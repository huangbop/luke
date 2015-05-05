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

#ifndef  _NVUTILS_H_INC
#define  _NVUTILS_H_INC

#ifdef      EXTERN
  #undef    EXTERN
#endif

#ifdef      INSTANTIATE_NV_UTILS
  #define   EXTERN
#else
  #define   EXTERN extern
#endif    
   
/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#define NULL  0
#define FTL     0
#define TOSHIBA  1
#define PAGE16K
#define DEBUG  1
#define AUXILIARY_SUPPORT

#define metasize      0
#define metat      0
#define MAXSEG 8
#define mAU_SIZE 4096
#define BFR_SSD_RDCNT 256
#define BFR_SSD_WDCNT 256
#define PAGEPBLOCK_SHIFT    8
#define PAGEMASK    0xff
#define AU_FORMAT_CNT    4

#ifdef PAGE16K
#define PARATIO       4
#define AU_PLANE   4
#define shift_4k_per_page  3    //  32k per log page(2 phy page)
#define mask_4k_per_page  0x07
#else
#define PARATIO       2
#define AU_PLANE   2
#define shift_4k_per_page  2    //  16k per log page(2 phy page)
#define mask_4k_per_page  0x03
#endif

#define FC_CMD_ERASE       0
#define FC_CMD_READ         1
#define FC_CMD_PROGRAM         2
#define FC_CMD_2P_ERASE        3
#define FC_CMD_2P_DATAIN         4
#define FC_CMD_2P_PROGRAM         5
#define FC_CMD_CHANGECLM         6
#define FC_CMD_2P_READ         7
#define FC_CMD_2P_CHANGECLM         8
#define FC_CMD_DATAOUT         9
#define FC_CMD_R_STS         10

#define FC_CMD_STS_70    0x70
#define FC_CMD_STS_78    0x78
#define FC_CMD_STS_71    0x71

//#if FTL == 0
#define CHN_SHIFT 3
#define ROW_SHIFT 1 // 2 Row
#define PAGE_SHIFT 1 // 2*4KB
#define BLK_SHIFT (8+PAGE_SHIFT) // 256*8K
//#define DIE_SHIFT 12 // 2048 block
#define PLANE_SHIFT 1 // 2 plane
#define NUM_PAGE (1<<BLK_SHIFT) // physical page
#define NUM_PLANE (1<<PLANE_SHIFT) // 2plane
#define NUM_BLK (1<<DIE_SHIFT)
#define NUM_CHN (1<<CHN_SHIFT)
#define NUM_ROW (1<<ROW_SHIFT)
#define NUM_DIE (NUM_CHN*NUM_ROW)
#define TOT_BLK (NUM_DIE*NUM_BLK*NUM_PLANE)
#define TOT_PAGE (NUM_DIE*NUM_BLK*NUM_PLANE*NUM_PAGE)
//#endif

//typedef unsigned char                      BOOLEAN; 
//typedef unsigned char                      INT8U; 
//typedef unsigned short                     INT16U;
//typedef unsigned int                       INT32U;
//typedef signed char                        INT8S;

typedef volatile unsigned char             VINT8U;
typedef volatile unsigned short            VINT16U;
typedef volatile unsigned int              VINT32U;


typedef unsigned char                      u8;
typedef unsigned short                     u16;
typedef unsigned int                       u32;
typedef unsigned long long                 u64;

typedef signed int                         s32;
typedef signed short                       s16;
typedef signed char                        s8;

typedef volatile u8                        vu8;
typedef volatile u16                       vu16;
typedef volatile u32                       vu32;

typedef unsigned char                      bool;

typedef u32 tag32_t;

#define REG32_READ(x)                      (* (VINT32U*) (x))

static __inline void
REG32_WRITE(mUINT_32 reg, mUINT_32 val)
{
    (* (VINT32U*) (reg) = (mUINT_32) (val));    
}

#define REG16_READ(x)                      (* (VINT16U*) (x))

static __inline void
REG16_WRITE(mUINT_32 reg, mUINT_16 val)
{
    (* (VINT16U*) (reg) = (mUINT_16) (val));    
}

#define REG8_READ(x)                       (* (VINT8U*) (x))
#define REG8_WRITE(x, v)                   (* (VINT8U*) (x) = (mUINT_8) (v))

#define BYTE0_OF(v)                        (((v) & 0x000000FF))
#define BYTE1_OF(v)                        (((v) & 0x0000FF00) >> 8)
#define BYTE2_OF(v)                        (((v) & 0x00FF0000) >> 16)
#define BYTE3_OF(v)                        (((v) >> 24))

#define min(a,b)                           (((a)<(b))?(a):(b))
#define max(a,b)                           (((a)>(b))?(a):(b))
#define mid(a,b)                           ((a+b)>>1)

#define INIT_SECTION                       __attribute__((section ("Init")))
#define ALWAYS_INLINE                      __attribute__((always_inline))
#define _at_(s)                            __attribute__((at(s)))

#define BIT(x)                             (1 << x)
#define mBIT(n)                         (1 << (n))
#define BIT_0                              (1 << 0)
#define BIT_1                              (1 << 1)
#define BIT_2                              (1 << 2)
#define BIT_3                              (1 << 3)
#define BIT_4                              (1 << 4)
#define BIT_5                              (1 << 5)
#define BIT_6                              (1 << 6)
#define BIT_7                              (1 << 7)
#define BIT_8                              (1 << 8)
#define BIT_9                              (1 << 9)
#define BIT_10                             (1 << 10)
#define BIT_11                             (1 << 11)
#define BIT_12                             (1 << 12)
#define BIT_13                             (1 << 13)
#define BIT_14                             (1 << 14)
#define BIT_15                             (1 << 15)
#define BIT_16                             (1 << 16)
#define BIT_17                             (1 << 17)
#define BIT_18                             (1 << 18)
#define BIT_19                             (1 << 19)
#define BIT_20                             (1 << 20)
#define BIT_21                             (1 << 21)
#define BIT_22                             (1 << 22)
#define BIT_23                             (1 << 23)
#define BIT_24                             (1 << 24)
#define BIT_25                             (1 << 25)
#define BIT_26                             (1 << 26)
#define BIT_27                             (1 << 27)
#define BIT_28                             (1 << 28)
#define BIT_29                             (1 << 29)
#define BIT_30                             (1 << 30)
#define BIT_31                             (1 << 31)

//#define REG16_READ(x)       (* (u16*) (x))
#define _max(a, b)  ((a) > (b) ? (a) : (b))
#define _min(a, b)  ((a) < (b) ? (a) : (b))
#define isolate_rmb1(x)     ((x) & -(x))

#define le16_unaligned_get(p)        \
    ((u16) (                         \
    (((u16) ((u8 *) (p))[1]) << 8) | \
    (((u16) ((u8 *) (p))[0])) ))

#define le32_unaligned_get(p)          \
    ((u32) (                           \
    (((u32) ((u8 *) (p))[3]) << 24) |  \
    (((u32) ((u8 *) (p))[2]) << 16) |  \
    (((u32) ((u8 *) (p))[1]) << 8)  |  \
    (((u32) ((u8 *) (p))[0])) ))

#define SEQ_TRIVAL_IRQS ( 0     \
    | SEQ_IRQ_SAC_W_ERR         \
    | SEQ_IRQ_SAC_R_ERR         \
    | SEQ_IRQ_TNUM_OVER         \
    | SEQ_IRQ_DNUM_OVER         \
    | SEQ_IRQ_DES_INV           \
    )

#define SEQ_HANDLED_IRQS ( 0    \
    | SEQ_TRIVAL_IRQS           \
    | SEQ_IRQ_OP_DONE           \
    | SEQ_IRQ_TRK_ERR           \
    | SEQ_IRQ_TRK_DONE          \
    )

#define FC_REG_BASE      0x1C000000L
#define ROC_FLASH_REG_BASE   (FC_REG_BASE + 0x00000)
#define _FC_REG_BASE    (ROC_FLASH_REG_BASE + 0xb600)

#define _EC_REG_BASE    (ROC_FLASH_REG_BASE + 0xb200)
#define RC_REG(x)       (_EC_REG_BASE + (x))

#define _SEQ_REG_BASE       (ROC_FLASH_REG_BASE + 0xd000)
#define SEQ_REG(x)          (_SEQ_REG_BASE + (x))
#define SEQ_REG_CONFIG_1            SEQ_REG(0x00)
#define SEQ_TRK_ORDR             BIT_15
#define SEQ_TRK_CONF_MASK        0x7
#define SEQ_TRK_CONF_BIT_OFF     12
#define SEQ_TRK_DONE_HOLD_DIS    BIT_11
#define SEQ_TRK_CTRL_DIS         BIT_10
#define SEQ_USE_AUTO_MODE        BIT_6
#define SEQ_DES_SP_EN            BIT_5
#define SEQ_OP_DONE_EN           BIT_4
#define SEQ_R_ERR_PASS_EN        BIT_3
#define TRK_CONF                3 /* 0~4 */

#define SEQ_REG_CONFIG_2            SEQ_REG(0x02)
#define SEQ_CLK_DIS              BIT_15
#define SEQ_DFIFO_CPU_LOW_PRIO   BIT_5
#define SEQ_AFIFO_CPU_LOW_PRIO   BIT_4
#define SEQ_AUX_VD_MODE          BIT_3   // 
#define SEQ_AUX_EN               BIT_2   // AUX_D_MODE
#define SEQ_LAST_AU_DIS          BIT_1
#define SEQ_SRAM_AUTO_PD         BIT_0

#define SEQ_REG_CONFIG_3            SEQ_REG(0x04)
#define SEQ_DS_INIT_EN           BIT_15
#define SEQ_ERR_CNT_EN           BIT_14
#define SEQ_PA_RATIO_MASK        0x7
#define SEQ_PA_RATIO_BIT_OFF     10
#define SEQ_PA_MODE              BIT_9
#define SEQ_LBA_4B_MODE          BIT_4
#define SEQ_AUX_META_SEL         BIT_3
#define SEQ_AUX_SIZE_MASK        0x3
#define SEQ_AUX_SIZE_BIT_OFF     1
#define SEQ_TWO_LBA_EN           BIT_0

#define SEQ_REG_CONFIG_4            SEQ_REG(0x06)
#define SEQ_REG_CONFIG_5            SEQ_REG(0x08)
#define SEQ_REG_CONTROL_1           SEQ_REG(0x10)
#define SEQ_REG_IRQ_STATUS          SEQ_REG(0x14)
#define SEQC_RW_INTSTA                 SEQ_REG(0x14)
#define SEQ_REG_IRQ_MASK            SEQ_REG(0x16)
#define SEQ_IRQ_SAC_W_ERR        BIT_13
#define SEQ_IRQ_SAC_R_ERR        BIT_12
#define SEQ_IRQ_AENC_OVER        BIT_9
#define SEQ_IRQ_ADEC_OVER        BIT_8
#define SEQ_IRQ_TNUM_OVER        BIT_7
#define SEQ_IRQ_DNUM_OVER        BIT_6
#define SEQ_IRQ_DES_INV          BIT_5
#define SEQ_IRQ_OP_DONE          BIT_4
#define SEQ_IRQ_TRK_ERR          BIT_1
#define SEQ_IRQ_TRK_DONE         BIT_0
#define SEQ_RESET                BIT_15
#define SEQ_BUSY                 BIT_0
#define SEQ_REG_CONFIG_3            SEQ_REG(0x04)
#define SEQ_DS_INIT_EN           BIT_15
#define SEQ_ERR_CNT_EN           BIT_14
#define SEQ_PA_RATIO_MASK        0x7
#define SEQ_PA_RATIO_BIT_OFF     10
#define SEQ_REG_TRK_STATUS_ID       SEQ_REG(0x18)
#define SEQC_RW_TRACKSTAID SEQ_REG(0x18)
#define SEQ_REG_TRK_PTR             SEQ_REG(0x1E)
#define SEQ_REG_TRK_STATUS1         SEQ_REG(0x20)   // 32 bit
#define SEQ_TS_NAND_ERR              BIT_0
#define SEQ_TS_ECC_ERR               BIT_1
#define SEQ_TS_DESC_PROC(v)          (((v) >> 2) & 0x7f)
#define SEQ_TS_DESC_TOTAL(v)         (((v) >> 9) & 0x7f)
#define SEQ_TS_FAIL_AU_NO(v)         (((v) >> 16) & 0x1f)
#define SEQ_TS_FAIL_AU_DESC_ID(v)    (((v) >> 21) & 0x7f)
#define SEQ_TS_FAIL_AU_ENC           BIT_28

#define SEQ_REG_TRK_STATUS2         SEQ_REG(0x24)   // 32 bit
#define SEQ_REG_TRK_DES_DONE        SEQ_REG(0x28)   // 32 bit
#define SEQ_REG_TRK_DES_STATUS      SEQ_REG(0x2C)   // 32 bit
#define SEQ_REG_DF_START_ADDR       SEQ_REG(0x30)   // 32 bit
#define SEQ_REG_DF_END_ADDR         SEQ_REG(0x34)   // 32 bit
#define SEQ_REG_DF_PTR              SEQ_REG(0x38)   // 32 bit

#define SEQ_REG_DES_LOOP_CNT        SEQ_REG(0x40)
#define SEQ_REG_DES_LOOP_CNT_ADJ    SEQ_REG(0x42)
#define SEQ_REG_DES_FIFO_CNT        SEQ_REG(0x44)
#define SEQ_REG_DES_DONE_CNT        SEQ_REG(0x46)
#define SEQ_REG_AUX_FIFO_INS_START  SEQ_REG(0x50)
#define SEQ_REG_AUX_FIFO_INS_END    SEQ_REG(0x54)
#define SEQ_REG_AUX_FIFO_INS_PTR    SEQ_REG(0x58)
#define SEQ_REG_AUX_FIFO_CMP_START  SEQ_REG(0x60)
#define SEQ_REG_AUX_FIFO_CMP_END    SEQ_REG(0x64)
#define SEQ_REG_AUX_FIFO_CMP_PTR    SEQ_REG(0x68)

#define SEQ_REG_AUX_FIFO_EXA_START  SEQ_REG(0x70)
#define SEQ_REG_AUX_FIFO_EXA_END    SEQ_REG(0x74)
#define SEQ_REG_AUX_FIFO_EXA_PTR    SEQ_REG(0x78)

#define SEQ_REG_AU_ENC_CMD_FIFO_RD          SEQ_REG(0x80)    // 32 bit
#define SEQ_REG_AU_ENC_CMD_FIFO_RP          SEQ_REG(0x84)
#define SEQ_REG_AU_ENC_CMD_FIFO_PUSHP       SEQ_REG(0x86)
#define SEQ_REG_AU_ENC_CMD_FIFO_POPP        SEQ_REG(0x88)
#define SEQ_REG_AU_ENC_CMD_FIFO_PREFETCHP   SEQ_REG(0x8A)

#define SEQ_REG_AU_DEC_CMD_FIFO_RD          SEQ_REG(0x90)    // 32 bit
#define SEQ_REG_AU_DEC_CMD_FIFO_RP          SEQ_REG(0x94)
#define SEQ_REG_AU_DEC_CMD_FIFO_PUSHP       SEQ_REG(0x96)
#define SEQ_REG_AU_DEC_CMD_FIFO_POPP        SEQ_REG(0x98)
#define SEQ_REG_AU_DEC_CMD_FIFO_PREFETCHP   SEQ_REG(0x9A)

#define SEQ_REG_AU_ENC_DONE_CNT             SEQ_REG(0xA0)
#define SEQ_REG_AU_DEC_DONE_CNT             SEQ_REG(0xA2)
#define SEQ_REG_AU_ENC_CMD_FIFO_POP_CNT     SEQ_REG(0xA4)
#define SEQ_REG_AU_DEC_CMD_FIFO_POP_CNT     SEQ_REG(0xA6)
#define SEQ_REG_AU_ENC_CMD_FIFO_PREFETCH_CNT     SEQ_REG(0xA8)
#define SEQ_REG_AU_DEC_CMD_FIFO_PREFETCH_CNT     SEQ_REG(0xAA)
#define SEQ_REG_AU_ENC_RCV_CNT              SEQ_REG(0xAC)
#define SEQ_REG_AU_DEC_RCV_CNT              SEQ_REG(0xAE)

#define SEQ_REG_ROW_INCREMENT               SEQ_REG(0xB0)    // 32bit

#define SEQ_REG_CP_DESC_XFER_CNT_SEL0       SEQ_REG(0xB4)
#define SEQ_REG_CP_DESC_XFER_CNT_SEL1       SEQ_REG(0xB6)
#define SEQ_REG_CP_DESC_COL_ADDR_SEL0       SEQ_REG(0xB8)
#define SEQ_REG_CP_DESC_COL_ADDR_SEL1       SEQ_REG(0xBA)

#define SEQ_REG_AUTO_DESC_XFER_CNT_SEL0     SEQ_REG(0xC0)
#define SEQ_REG_AUTO_DESC_XFER_CNT_SEL1     SEQ_REG(0xC2)
#define SEQ_REG_AUTO_DESC_COL_ADDR_SEL0     SEQ_REG(0xC4)
#define SEQ_REG_AUTO_DESC_COL_ADDR_SEL1     SEQ_REG(0xC6)
#define SEQ_REG_AUTO_DESC_ROW_ADDR_SEL0     SEQ_REG(0xC8)  // 32bit
#define SEQ_REG_AUTO_DESC_ROW_ADDR_SEL1     SEQ_REG(0xCC)  // 32bit

#define SEQ_REG_REF_AUX_DATA_MASK_1         SEQ_REG(0xD0)  // 32 bit
#define SEQ_REG_REF_AUX_DATA_MASK_2         SEQ_REG(0xD4)  // 32 bit
#define SEQ_REG_REF_AUX_DATA_MASK_3         SEQ_REG(0xD8)  // 32 bit

#define SEQ_REG_TRKM_START                  SEQ_REG(0x1A0)  // 32bit
#define SEQ_REG_AENC_START                  SEQ_REG(0x120)  // 32bit
#define SEQ_REG_AENC_SIZE                   SEQ_REG(0x124)  // 32bit
#define SEQ_REG_ADEC_START                  SEQ_REG(0x140)  // 32bit
#define SEQ_REG_ADEC_SIZE                   SEQ_REG(0x144)  // 32bit

#define SEQ_REG_SAC_ERR_CTL                 SEQ_REG(0x406)  // 16bit
#define SEQ_REG_SAC_R_ERR_ADDR              SEQ_REG(0x408)  // 32bit
#define SEQ_REG_SAC_W_ERR_ADDR              SEQ_REG(0x40C)  // 32bit

#define SEQ_ENABLE               BIT_12

#define _FC_REG_BASE    (ROC_FLASH_REG_BASE + 0xb600)
#define _FCT_REG_BASE   (ROC_FLASH_REG_BASE + 0xba00)
#define FC_REG(x)               (_FC_REG_BASE + (x))
#define FCT_REG(x)              (_FCT_REG_BASE + (x))
#define FCT_REG_IRQ_STATUS      FCT_REG(0x00)
#define FCT_REG_IRQ_EN          FCT_REG(0x02)
#define FCT_INT_SEQ             BIT_2
#define FCT_INT_FLASH           BIT_1
#define FCT_INT_AES             BIT_0

#define EC_REG_CNTL_CFG1            RC_REG(0x00)
#define EC_SOFT_RESET            BIT_0

#define EC_REG_CNTL_CFG2            RC_REG(0x02)
#define EC_STOP_ON_RAID_BUF0CHK_ERR BIT_13
#define EC_STOP_ON_AES_ERR          BIT_12
#define EC_STOP_ON_RAID_ID_ERR      BIT_11
#define EC_STOP_ON_RAID_DPP_ERR     BIT_10
#define EC_STOP_ON_16_AU            BIT_9
#define EC_STOP_ON_DPP_ERR          BIT_8
#define EC_STOP_ON_ERASE_ERR        BIT_7
#define EC_STOP_ON_AUX_MMATCH_ERR   BIT_6
#define EC_STOP_ON_MCRC_ERR         BIT_5
#define EC_STOP_ON_OVRLMT_ERR       BIT_4
#define EC_STOP_ON_UNCORR_ERR       BIT_3
#define EC_STOP_ON_HLBA_MMATCH_ERR  BIT_2
#define EC_STOP_ON_MPECC_ERR        BIT_1

#define EC_REG_DEFAULT_CNTL_CFG2   0   \
            | EC_STOP_ON_RAID_BUF0CHK_ERR \
            | EC_STOP_ON_AES_ERR          \
            | EC_STOP_ON_RAID_ID_ERR      \
            | EC_STOP_ON_RAID_DPP_ERR     \
            | EC_STOP_ON_DPP_ERR          \
            | EC_STOP_ON_ERASE_ERR        \
            | EC_STOP_ON_AUX_MMATCH_ERR   \
            | EC_STOP_ON_MCRC_ERR         \
            //| EC_STOP_ON_OVRLMT_ERR       \
            | EC_STOP_ON_UNCORR_ERR       \
            | EC_STOP_ON_MPECC_ERR        \
            | EC_STOP_ON_HLBA_MMATCH_ERR
            


#define EC_REG_CNTL_CFG3            RC_REG(0x04)
#define EC_SEND_ON_RAID_BUF0CHK_ERR BIT_13
#define EC_SEND_ON_RAID_ID_ERR      BIT_11
#define EC_SEND_ON_RAID_DPP_ERR     BIT_10
#define EC_SEND_ON_16_AU            BIT_9
#define EC_SEND_ON_DPP_ERR          BIT_8
#define EC_SEND_ON_ERASE            BIT_7
#define EC_SEND_ON_AUX_MMATCH       BIT_6
#define EC_SEND_ON_MCRC_ERR         BIT_5
#define EC_SEND_ON_OVRLMT           BIT_4
#define EC_SEND_ON_UNCORR           BIT_3

#define EC_REG_CNTL_CFG4            RC_REG(0x06)
#define EC_META_READ_SKIP           BIT_4
#define EC_META_AUX_RCVR            BIT_2
#define EC_ERASE_PAGE_DET_ONLY      BIT_1

#define EC_REG_CNTL_CFG5            RC_REG(0x08)    // PHY_PAGE_SIZE
#define EC_ECU2METALC_MPECD_EN      BIT_14
#define EC_DDRMC_PORT_CONF          BIT_11
#define EC_DDR_SYNC_BYPASS_EN       BIT_9
#define EC_MANUAL_ERASE_THRSHD_EN   BIT_8
#define EC_ECC_DEC_BYPASS_EN        BIT_5
#define EC_META_ECC_EN              BIT_4
#define EC_MCRC_INV_MODE            BIT_3
#define EC_ECC_INV_MODE             BIT_2
#define EC_FIT_2_PHY_PAGE           BIT_0

#define EC_REG_DEFAULT_CNTL_CFG5    0 \
            | EC_MANUAL_ERASE_THRSHD_EN  \
            | EC_META_ECC_EN  


#define EC_REG_CNTL_CFG6            RC_REG(0x0A)    // ERASE_CNT_THRSH
#define EC_REG_CNTL_CFG7            RC_REG(0x10)    
#define EC_ECU_HLBA_STRIP_MODE_OFFSET BIT_4
#define EC_ECU_HLBA_MODE_OFFSET       BIT_2
#define EC_ECU_MPECC_EN               BIT_0

#define EC_REG_CNTL_CFG8            RC_REG(0x12)    // Host Sector Size
#define EC_REG_CNTL_CFG9            RC_REG(0x14)    // reserved
#define EC_REG_CNTL_CFG10           RC_REG(0x16)    // reserved
#define EC_REG_CNTL_CFG12           RC_REG(0x1A)    // reserved

#define EC_REG_CNTL_CFG13              RC_REG(0x1C)
#define EC_REG_SCR_USER_SEED_SRC            BIT_5 
#define EC_REG_SCR_USER_EN               BIT_4 
#define EC_REG_SCR_META_INV_EN              BIT_3 
#define EC_REG_SCR_META_SEED_SRC            BIT_1 
#define EC_REG_SCR_META_EN               BIT_0 
#define EC_REG_AU_FORMAT_CFG_PTR        RC_REG(0x1E)
#define EC_REG_CFG1                     RC_REG(0x20)
#define EC_REG_CFG2                     RC_REG(0x22)
#define EC_REG_CFG3                     RC_REG(0x24)
#define EC_REG_CFG4                     RC_REG(0x26)
#define EC_REG_CFG5                     RC_REG(0x28)
#define EC_REG_CFG6                     RC_REG(0x2E)
#define EC_SOFT_RESET            BIT_0
#define EC_REG_ENCODE_STATUS_0          RC_REG(0x40)
#define EC_ENC_STOP_RESUME               BIT_0   //EC Encoder resume
#define EC_REG_DECODE_STATUS_REPORT0    RC_REG(0x50)
#define EC_DEC_CUR_RAID_DEC_0CHK_ERR         BIT_15  //RAID decode RAID Buffer Zero Check Error
#define EC_DEC_CUR_AES_DEC_ERR               BIT_14  //AES Error Status for Current AU READ
#define EC_DEC_CUR_ERRBUF_DPP_ERR            BIT_13  //Error Buffer DPP Error Status for Current AU READ
#define EC_DEC_CUR_DECBUF_DPP_ERR            BIT_12  //Decode Buffer DPP Error Status for Current AU READ
#define EC_DEC_CUR_RAID_DEC_INVALID_ID_ERR   BIT_11  //RAID Invalid ID Status for Current AU READ
#define EC_DEC_CUR_RAID_DEC_DPP_ERR          BIT_10  //RAID Buffer DPP Error Status for Current AU READ
#define EC_DEC_CUR_ECU_STRG_SYND_ERR         BIT_8   //Strong Syndrome Erro Status for Current AU READ.
#define EC_DEC_CUR_AU_AU16                   BIT_7   //Current AU at 16th AU.
#define EC_DEC_CUR_AU_ERASE                  BIT_6   //Erase Pager Status for Current AU READ.
#define EC_DEC_CUR_AU_AUX_MMATCH             BIT_5   //Auxiliary Data Mismatch Error Status for Current AU
#define EC_DEC_CUR_AU_MCRC                   BIT_4   //AU MCRC Error Status for Current AU READ.
#define EC_DEC_CUR_AU_META_MCRC              BIT_3   //META_MCRC Error Status for Current AU.
#define EC_DEC_CUR_AU_OVRLMT                 BIT_2   //Over-Limit Status for Current AU READ.
#define EC_DEC_CUR_AU_UNCORR                 BIT_1   //Uncorrectable Status for Current AU READ.
#define EC_DEC_STOP_RESUME                   BIT_0   //EC Decoder resume






//#define FC_REG(x)               (_FC_REG_BASE + (x))
#define FC_REG_IF_CFG                       FC_REG(0x00)
#define FC_REG_xDIRECT_ACCESS_CNTL          FC_REG(0x02)
#define FC_REG_TIMING_CNTL1                 FC_REG(0x04)
#define FC_REG_TIMING_CNTL2                 FC_REG(0x06)
#define FC_REG_TIMING_CNTL3                 FC_REG(0x08)
#define FC_REG_TIMING_CNTL4                 FC_REG(0x0A)
#define FC_REG_DIRECT_ACCESS_CNTL_PORT1     FC_REG(0x0C)
#define FC_REG_DATA_LATCH_TIMING_CNTL_CH01  FC_REG(0x10)
#define FC_REG_DATA_LATCH_TIMING_CNTL_CH23  FC_REG(0x12)
#define FC_REG_DATA_LATCH_TIMING_CNTL_CH45  FC_REG(0x14)
#define FC_REG_DATA_LATCH_TIMING_CNTL_CH67  FC_REG(0x16)
#define FC_REG_DATA_LATCH_TIMING_CNTL_CH89  FC_REG(0x18)
#define FC_REG_DATA_LATCH_TIMING_CNTL_CHAB  FC_REG(0x1A)
#define FC_REG_DATA_LATCH_TIMING_CNTL_CHCD  FC_REG(0x1C)
#define FC_REG_DATA_LATCH_TIMING_CNTL_CHEF  FC_REG(0x1E)
#define FC_REG_INDIRECT_ACCESS_CFG          FC_REG(0x20)
#define FC_REG_INDIRECT_ACCESS_CMD_PORT1    FC_REG(0x22)
#define FC_REG_INDIRECT_ACCESS_CMD_PORT2    FC_REG(0x24)
#define FC_REG_INDIRECT_ACCESS_CMD_PORT3    FC_REG(0x26)
#define FC_REG_INDIRECT_ACCESS_CMD_PORT4    FC_REG(0x28)
#define FC_REG_INDIRECT_ACCESS_XFER_CNT     FC_REG(0x2A)
#define FC_REG_INDIRECT_ACCESS_DATA_PORT1   FC_REG(0x2C)    // 32bit register
#define FC_REG_INDIRECT_ACCESS_DATA_PORT2   FC_REG(0x2E)
#define FC_REG_TIMING_CNTL6                 FC_REG(0x32)
#define FC_REG_SEQ_CNTL1                    FC_REG(0x40)
#define FC_REG_SEQ_CNTL2                    FC_REG(0x3E)
#define FC_REG_SEQ_IF_TIMING_CFG_CH0        FC_REG(0x60)
#define FC_REG_SEQ_IF_TIMING_CFG_CH1        FC_REG(0x62)
#define FC_REG_SEQ_IF_TIMING_CFG_CH2        FC_REG(0x64)
#define FC_REG_SEQ_IF_TIMING_CFG_CH3        FC_REG(0x66)
#define FC_REG_SEQ_IF_TIMING_CFG_CH4        FC_REG(0x68)
#define FC_REG_SEQ_IF_TIMING_CFG_CH5        FC_REG(0x6A)
#define FC_REG_SEQ_IF_TIMING_CFG_CH6        FC_REG(0x6C)
#define FC_REG_SEQ_IF_TIMING_CFG_CH7        FC_REG(0x6E)
#define FC_REG_SEQ_IF_TIMING_CNTL1          FC_REG(0x70)
#define FC_REG_SEQ_IF_TIMING_CNTL2          FC_REG(0x72)
#define FC_REG_SEQ_IF_TIMING_CNTL3          FC_REG(0x74)
#define FC_REG_SEQ_IF_TIMING_CNTL4          FC_REG(0x76)
#define FC_REG_SEQ_IF_TIMING_CNTL5          FC_REG(0x78)
#define FC_REG_SEQ_IF_TIMING_CNTL6          FC_REG(0x7A)
#define FC_REG_SEQ_STATUS_BYTE_CNTL1        FC_REG(0x84)
#define FC_REG_SEQ_STATUS_BYTE_CNTL2        FC_REG(0x86)
#define FC_REG_SEQ_STATUS_BYTE_CNTL3        FC_REG(0x88)
#define FC_REG_SEQ_CMD_PORT7                FC_REG(0x90)
#define FC_REG_SEQ_CMD_PORT8                FC_REG(0x92)
#define FC_REG_SEQ_CMD_PORT9                FC_REG(0x94)
#define FC_REG_SEQ_CMD_PORT10               FC_REG(0x96)
#define FC_REG_SEQ_CMD_PORT11               FC_REG(0x98)
#define FC_REG_SEQ_CH0_BLK_BNDRY_INFO       FC_REG(0xA0)
#define FC_REG_SEQ_CH1_BLK_BNDRY_INFO       FC_REG(0xA2)
#define FC_REG_SEQ_CH2_BLK_BNDRY_INFO       FC_REG(0xA4)
#define FC_REG_SEQ_CH3_BLK_BNDRY_INFO       FC_REG(0xA6)
#define FC_REG_SEQ_CH03_LUN_INFO            FC_REG(0x100)
#define FC_REG_SEQ_CH47_LUN_INFO            FC_REG(0x102)
#define FC_REG_SEQ_CH8B_LUN_INFO            FC_REG(0x104)
#define FC_REG_SEQ_CHCF_LUN_INFO            FC_REG(0x106)

#define FC_READY_BIT                        (0x07 << 5)
#define FC_FSEQ_EN                          BIT_0
#define FC_DLY_US   10                                      // temporily set 10 us delay for debugging purpose
#define FC_SM_IDLE                          BIT_7
#define FC_IF_RESET                         BIT_6
#define FC_PD_EN                            BIT_7

#define ONFI_SYNC_ENABLE        0x10
#define FC_NFIF_JDBC_ONFI_SYNC              BIT_8
#define DEV_TYPE_BASIC_MASK                 0x0F    //bit0-3 representing basic type
#define DEV_TYPE_JEDEC_MASK                 BIT_4    //bit4 representing JEDEC
#define DEV_TYPE_TOGGLE_MASK                BIT_5    //bit5 representing TOGGLE
#define DEV_TYPE_ONFI_MASK                  BIT_6    //bit6 representing ONFI
#define DEV_TYPE_SYNC_MASK                  BIT_7    //bit7 representing SYNC
#define DEV_TYPE_BASIC_MICRON               0x00
#define DEV_TYPE_BASIC_SAMSUNG              0x01
#define DEV_TYPE_BASIC_TOSHIBA              0x02
#define DEV_TYPE_BASIC_HYNIX                0x03
#define FC_FLTYPE_MASK                      (0x03 << 2)

#define PMC_REG_BASE     0xB0070000L
#define OSC_CTRL_REG             (PMC_REG_BASE + 0x0318)
#define FC_CLK_CTRL_REG          (PMC_REG_BASE + 0x0308)

#define IO_VOLTAGE_3P3V 0
#define IO_VOLTAGE_1P8V 1
#define DEV_TYPE_MICRON_CONV_ASYNC          0x00
#define DEV_TYPE_MICRON_ONFI_ASYNC          0x40    //bit6 representing ONFI
#define DEV_TYPE_SAMSUNG_CONV_ASYNC         0x01
#define DEV_TYPE_TOSHIBA_CONV_ASYNC         0x02
#define DEV_TYPE_HYBIX_CONV_ASYNC           0x03
                                                    //bit4 representing JEDEC
#define DEV_TYPE_SAMSUNG_JEDEC_TOGGLE       0x31    //bit5 representing TOGGLE
#define DEV_TYPE_TOSHIBA_JEDEC_TOGGLE       0x32    //bit5 representing TOGGLE
#define DEV_TYPE_MICRON_ONFI_SYNC           0xC0    //bit7 representing SYNC

#define DEV_TYPE_INITIAL_ASYNC              DEV_TYPE_MICRON_CONV_ASYNC
#define DEV_TYPE_INITIAL_TOGGLE             DEV_TYPE_SAMSUNG_JEDEC_TOGGLE

#define ONFI_TIMING_MODE_0        0x00
#define ONFI_TIMING_MODE_1        0x01
#define ONFI_TIMING_MODE_2        0x02
#define ONFI_TIMING_MODE_3        0x03
#define ONFI_TIMING_MODE_4        0x04
#define ONFI_TIMING_MODE_5        0x05


#define INITIAL_TIMING_MODE_SEL        ONFI_TIMING_MODE_0



#define FC_FLAMODE_MASK                     0x03
#define FC_ACCESS_MODE_SEQ                  2
#define FC_DIRECT_OE_EN                     BIT_7
#define FC_DIRECT_CE                        BIT_6
#define FC_DIRECT_DQS_OE                    BIT_5
#define FC_DIRECT_WP                        BIT_4
#define FC_DIRECT_WE                        BIT_3
#define FC_DIRECT_RE                        BIT_2
#define FC_DIRECT_ALE                       BIT_1
#define FC_DIRECT_CLE                       BIT_0

#define FC_ACCESS_MODE_DIRECT               0
#define FC_ACCESS_MODE_INDIRECT             1
#define FC_ACCESS_MODE_SEQ                  2

// Commands to the flash
#define mFC_NOP_00                      0x00                // NOP 00
#define mFC_ADDR_00                     0x00                // address 00
#define mFC_CMD_READ_MODE               0x00
#define mFC_CMD_RESET_FLASH             0xFF                // reset command
#define mFC_CMD_SYNC_RESET_FLASH        0xFC                // onfi sync reset command
#define mFC_CMD_READ_FLASH_ID           0x90                // read id command
#define mFC_CMD_READ_STATUS             0x70                // read status
#define mFC_CMD_READ_FLASH_1ST          0x00                // read, 1st cycle, etc.
#define mFC_CMD_READ_FLASH_2ND          0x30                // read, 2nd cycle
#define mFC_CMD_RND_DO_1ST              0x05                // random data output 1st cycle
#define mFC_CMD_RND_DO_2ND              0xE0                // random data output 2nd cycle
#define mFC_CMD_PRG_FLASH_1ST           0x80                // program 1st cycle
#define mFC_CMD_PRG_FLASH_2ND           0x10                // program 2nd cycle
#define mFC_CMD_RND_DI                  0x85                // random data input
#define mFC_CMD_ERASE_FLASH_1ST         0x60                // erase 1st cycle
#define mFC_CMD_ERASE_FLASH_2ND         0xD0                // erase 2nd cycle
#define mFC_FLASH_STATUS_FAIL           0x01
#define mFC_FLASH_STATUS_FAILC          0x02
#define mFC_FLASH_STATUS_VSP            0x10
#define mFC_FLASH_STATUS_AREADY         0x20
#define mFC_FLASH_STATUS_READY          0x40
#define mFC_FLASH_STATUS_WP_DISABLED    0x80
#define mFC_CMD_ONFI_GET_FEATURES   0xEE
#define mFC_CMD_ONFI_SET_FEATURES   0xEF
#define mFC_CMD_ONFI_READ_PARAMETER 0xEC    // ONFI read parameter page
#define FC_PLL0_DIVIDER 0x80020554                          //Vangogh2.0 only has 2 PLLs
#define FC_PLL1_DIVIDER 0x80020558

#define FC_DLY_CNTS 10   

#define FC_xDIRECT_CHDEV_MASK               0x0fff
#define FC_xDIRECT_CH_BIT_OFF               8
#define FC_xDIRECT_DEV_BIT_OFF              0

#define FC_INDIRECT_FIFO_STATUS             BIT_14
#define FC_INDIRECT_DUMMY_CE                BIT_9
#define FC_INDIRECT_DUMMY_RBB               BIT_8
#define FC_INDIRECT_ACCESS_START            BIT_7
#define FC_INDIRECT_FIFO_RESET              BIT_6
#define FC_INDIRECT_CT                      BIT_5           // CLE signal will be generated with 1st byte and end of command byte
#define FC_INDIRECT_OUT                     BIT_4

#define FC_INDIRECT_TIME_OUT_COUNT         100      // loop count for timeout of indirect access, about 100us
#define FC_INDIRECT_RESET_TIME_OUT_US     1000      //  1ms for time out of indirect reset access
#define FC_INDIRECT_READ_TIME_OUT_US      1000      //  1ms for timeout of indirect read access
#define FC_INDIRECT_PRG_TIME_OUT_US      3000      //  1ms for timeout of indirect read access
#define FC_INDIRECT_ERASE_TIME_OUT_US      5000      //  1ms for timeout of indirect erase access

#define NAND_DEVICE_CLASS_UNKNOWN    0   // initial
#define NAND_DEVICE_CLASS_LISTED     1   // it is in the supported list but not ONFI or TOGGLE devices
#define NAND_DEVICE_CLASS_ONFI       2   // it is ONFI device
#define NAND_DEVICE_CLASS_TOGGLE     3   // it is TOGGLE device
#define INITIAL_TOGGLE_TIMING_MODE_SEL        (ONFI_TIMING_MODE_1 | ONFI_SYNC_ENABLE)    //Toggle 66Mbps
#define FC_CLK_PD_EN                        BIT_9
#define FC_SQRA_EN                          BIT_3
#define FC_SMAPD_EN                         BIT_1

#define nv_err_ok                   0       // 0x00000000, succeed, no error
#define nv_err_failed               (-1)    // 0xFFFFFFFF, failed, hard to tell why
#define nv_err_meta_mismatched      (-2)    // 0xFFFFFFFE, unexpected meta data
#define nv_err_no_mem               (-3)    // 0xFFFFFFFD, running out of memory
#define nv_err_no_sysvec            (-4)    // 0xFFFFFFFC, no system vector found
#define nv_err_inv_sysvec           (-5)    // 0xFFFFFFFB, invalid system vector
#define nv_err_incorrect_ver        (-6)    // 0xFFFFFFFA, incompatible firmware version
#define nv_err_inv_sysdata          (-7)    // 0xFFFFFFF9, invalid system data, corrupted?
#define nv_err_dev_missing          (-8)    // 0xFFFFFFF8, a device existed before now is gone
#define nv_err_dirty                (-9)    // 0xFFFFFFF7, dirty, reconstruction is required
#define nv_err_virgin               (-10)   // 0xFFFFFFF6, virgin system, format is required
#define nv_err_weru0_err            (-11)   // 0xFFFFFFF5, WERU0 error, that's bad
#define nv_err_defect_overflow      (-12)   // 0xFFFFFFF4, too many defects
#define nv_err_assertion            (-13)   // 0xFFFFFFF3, assertion triggerred in nv_init
#define nv_err_dev_inconsistent     (-14)   // 0xFFFFFFF2, different NAND device models detected
#define nv_err_no_dev               (-15)   // 0xFFFFFFF1, no NAND device attached???
#define nv_err_dev_not_supported    (-16)   // 0xFFFFFFF0, not supported device model device detected
#define nv_err_inv_plist            (-17)   // 0xFFFFFFEF, invalid primary defect list
#define nv_err_out_of_range         (-18)   // 0xFFFFFFEE, out of user AU range
#define nv_err_out_of_space         (-19)   // 0xFFFFFFED, ran out of physical space

#define nv_err_flash_media          (-20)   // 0xFFFFFFEC, Flash Media Error: device error or uncorrectable ECC.
#define nv_err_fc_operation         (-21)   // 0xFFFFFFEB, FC Hardware operation error.
#define nv_err_fc_sw                (-22)   // 0xFFFFFFEA, FC SW Setup Error.
#define nv_err_cur_au_erase         (-23)   // 0xFFFFFFE9, Erase page status for current AU error.
#define nv_err_cur_au_ecc_ovrlmt    (-24)   // 0xFFFFFFE8, Over-Limit status for current AU error.
#define nv_err_timeout              (-25)   // 0xFFFFFFE7, The F/W forces time out error.
#define nv_err_trk_aborted          (-26)   // 0xFFFFFFE6, Track abort
#define nv_err_op_aborted           (-27)   // 0xFFFFFFE5, Operation abort

#define nv_err_bad_crc              (-28)   // 0xFFFFFFE4, 
#define nv_err_invalid_dev_cfg      (-29)   // 0xFFFFFFE3, 
#define nv_err_inv_rlut             (-30)   // 0xFFFFFFE2, 
#define nv_err_inv_laa              (-31)   // 0xFFFFFFE1, invalid laa
#define nv_err_ce_inconsistent      (-32)   // 0xFFFFFFE0, different CEs on channels detected
#define nv_err_ch_inconsistent      (-33)   // 0xFFFFFFDF, different channels on CEs detected
#define nv_err_device_not_listed    (-34)   // 0xFFFFFFDE, device not in the supported list and not ONFI
#define nv_err_sw_coding            (-35)   // 0xFFFFFFDD, software coding error
#define nv_err_unread               (-36)   // 0xFFFFFFDC, system can't read
#define nv_err_unread_unwritten     (-37)   // 0xFFFFFFDB, system can't read or write

#define nv_err_reconstructing       (-40)   // 0xFFFFFFD8, not a real error, UI only
#define nv_err_not_started          (-41)   // 0xFFFFFFD7, not a real error, UI only
#define nv_err_started_with_err     (-42)   // 0xFFFFFFD6, not a real error, UI only

#define nv_err_readonly             (-50)   // cannot write
#define nv_err_cmd_not_supported    (-51)
#define nv_err_access_denied        (-52)
#define nv_err_inv_weru0            (-53)   // invalid weru0 data
#define nv_err_sysdata_mismatch     (-54)

/* mmc-related errors */
#define nv_err_part_not_created     (-53)
#define nv_err_part_invalid         (-54)
#define nv_err_addr_out_of_range    (-55)
#define nv_err_otp_only             (-56)
#define nv_err_out_of_area          (-57)
#define nv_err_data_jump            (-58)
#define nv_err_wp_violation         (-59)
#define nv_err_wp_erase_skip        (-60)

#define READ_PARAM_ADDR_ONFI         0x00
#define READ_PARAM_ADDR_TOGGLE       0x40
#define ONFI_PARAM_PAGE_SIGNATURE   'IFNO'
#define TOGGLE_PARAM_PAGE_SIGNATURE   'DSEJ'

#define field_offset(type, field)   ((unsigned int) &(((type *) 0)->field))

#define ONFI_FA_TIMING_MODE          0x01
#define ONFI_OUTPUT_DRIVE_STRENGTH_OD2        0x00
#define ONFI_OUTPUT_DRIVE_STRENGTH_OD1        0x01
#define ONFI_OUTPUT_DRIVE_STRENGTH_NOMINAL    0x02
#define ONFI_OUTPUT_DRIVE_STRENGTH_UD        0x03
#define ONFI_OUTPUT_DRIVE_STRENGTH_SEL        ONFI_OUTPUT_DRIVE_STRENGTH_OD2
#define TOGGLE_OUTPUT_DRIVE_STRENGTH_OD2        0x08
#define TOGGLE_OUTPUT_DRIVE_STRENGTH_OD1        0x06
#define TOGGLE_OUTPUT_DRIVE_STRENGTH_NOMINAL    0x04
#define TOGGLE_OUTPUT_DRIVE_STRENGTH_UD            0x02
#define TOGGLE_OUTPUT_DRIVE_STRENGTH_SEL        TOGGLE_OUTPUT_DRIVE_STRENGTH_OD2
#define ONFI_FA_IO_DRIVE_STRENGTH    0x10

#define SEQ_DESC_SA     BIT_24
#define SEQ_DESC_TYPE_READ          0
#define SEQ_DESC_TYPE_PROG          1
#define SEQ_DESC_TYPE_ERASE         2
#define SEQ_DESC_TYPE_READ_STATUS   3
#define SEQ_DESC_TYPE_MP_EN            4
#define SEQ_DESC_TYPE_ML_EN            8

#define ECC_POWER_TABLE_MAX 8
#define AU_SETTING_META_ECC_EN       BIT_7
#define AU_SETTING_MCRC_INV_MODE     BIT_6
#define AU_SETTING_ECC_INV_MODE      BIT_5
#define AU_SETTING_FIT_2_PHY_PAGE    BIT_4
#define AU_SETTING_AU_MCRC_EN        BIT_3
#define AU_SETTING_META_MCRC_EN      BIT_2
#define AU_SETTING_SCR_USER_EN       BIT_1
#define AU_SETTING_SCR_META_EN       BIT_0
#define AU_SETTING_ECU_MPECC_EN      BIT_7
#define AU_SETTING_SCR_META_INV_EN   BIT_6
#define AU_SETTING_SCR_USER_SEED_SRC BIT_4
#define AU_SETTING_SCR_META_SEED_SRC BIT_2
#define AU_SETTING_SCR_USER_SEED_SRC_SHIFT 4
#define AU_SETTING_SCR_META_SEED_SRC_SHIFT 2
   
#define EC_ECU_HLBA_STRIP_MODE_OFFSET BIT_4
#define EC_ECU_HLBA_MODE_OFFSET       BIT_2
#define EC_ECU_MPECC_EN               BIT_0
#define EC_REG_SCR_USER_SEED_SRC_SHIFT 5
#define EC_REG_SCR_META_SEED_SRC_SHIFT 1
#define EC_REG_SCR_USER_SEED_SRC            BIT_5 
#define EC_REG_SCR_USER_EN               BIT_4 
#define EC_REG_SCR_META_INV_EN              BIT_3 
#define EC_REG_SCR_META_SEED_SRC            BIT_1 
#define EC_REG_SCR_META_EN               BIT_0 
#define EC_META_MCRC_EN                   BIT_8
#define EC_AU_MCRC_EN                      BIT_5


#define T_STRONG_MAX        72
#define T_WEAK_MAX          54
#define STRONG_THRESHOLD_T_RATIO    10 // t_strong : threashold_strong
#define WEAK_THRESHOLD_T_RATIO      5  // t_weak : threashold_weak

#define FDMA_STATE_INIT             0
#define FDMA_STATE_ALLOCATED        1
#define FDMA_STATE_SUBMITTED        2
#define FDMA_STATE_COMPLETED        3

/*---------------------------------------------------------------------------*/

/*
 * the tag implementation has to be changed if more than 32 commands is needed.
 */


/*
 * DMA_Q_DEPTH is defined for both delivery and completion queues.
 * The queue depth must be larger than maximum number of requests
 * so that we can tell whether the queue is full or empty when the
 * read and write pointer are equal.
 */



#define FIRST_DESCRIPTOR                1
#define LAST_DESCRIPTOR                 0
#define HEAD_GROUP                      1
#define TAIL_GROUP                      0

#define CMD_DES_RGL_DES_TYPE                    0
#define CMD_DES_CPT_DES_TYPE                    1
#define CMD_DES_GEN_DES_TYPE                    2

/*High Dword of 1st long word of REGULAR DESCRIPTOR (DF=00b)*/
#define CMD_DES_RGL_FD_BIT_OFF          31
#define CMD_DES_RGL_LD_BIT_OFF          30
#define CMD_DES_RGL_RR_BIT_OFF          29
#define CMD_DES_RGL_DC_BIT_OFF          28
#define CMD_DES_RGL_SA_BIT_OFF          27
#define CMD_DES_RGL_LC_BIT_OFF          26
#define CMD_DES_RGL_LE_BIT_OFF          25
#define CMD_DES_RGL_HCI_BIT_OFF         24
#define CMD_DES_RGL_EM_BIT_OFF          21
#define CMD_DES_RGL_MV_BIT_OFF          18
#define CMD_DES_RGL_HV_BIT_OFF          17
#define CMD_DES_RGL_DV_BIT_OFF          16
#define CMD_DES_RGL_DF_MASK             0x3
#define CMD_DES_RGL_DF_BIT_OFF          12
#define CMD_DES_RGL_ML_BIT_OFF          11
#define CMD_DES_RGL_MP_BIT_OFF          10
#define CMD_DES_RGL_DES_TYPE_MASK       0x3
#define CMD_DES_RGL_DES_TYPE_BIT_OFF    8
#define CMD_DES_RGL_CH_MASK             0xF
#define CMD_DES_RGL_CH_BIT_OFF          4
#define CMD_DES_RGL_DEV_MASK            0xF
#define CMD_DES_RGL_DEV_BIT_OFF         0
/*Low Dword of 1st long word of REGULAR DESCRIPTOR (DF=00b)*/
#define CMD_DES_RGL_AU_SEG_MASK         0xF
#define CMD_DES_RGL_AU_SEG_BIT_OFF      24
#define CMD_DES_RGL_DES_RDSR_MASK       0x3
#define CMD_DES_RGL_DES_RDSR_BIT_OFF    22
#define CMD_DES_RGL_AU_NUM_MASK         0x7
#define CMD_DES_RGL_AU_NUM_BIT_OFF      19
#define CMD_DES_RGL_CMD_ENH_0_MASK      0x7
#define CMD_DES_RGL_CMD_ENH_0_BIT_OFF   16
#define CMD_DES_RGL_MP_NUM_MASK         0x7
#define CMD_DES_RGL_MP_NUM_BIT_OFF      12
#define CMD_DES_RGL_TRACK_ID_MASK       0x7FF
#define CMD_DES_RGL_TRACK_ID_BIT_OFF    0

/*High Dword of 2nd long word of REGULAR DESCRIPTOR (DF=00b)*/
#define CMD_DES_RGL_DES_MPDO_BIT_OFF    28
#define CMD_DES_RGL_CMD_ENH_1_MASK      0x3
#define CMD_DES_RGL_CMD_ENH_1_BIT_OFF   14
#define CMD_DES_RGL_AU_FORMAT_MASK      0x1F
#define CMD_DES_RGL_AU_FORMAT_BIT_OFF   9
#define CMD_DES_RGL_AES_KEYSEL_MASK     0x1F
#define CMD_DES_RGL_AES_KEYSEL_BIT_OFF  4

/*High Dword of 3rd long word of REGULAR DESCRIPTOR (DF=00b)*/
#define CMD_DES_RGL_CMD_DES_MPDO_MASK       0xF
#define CMD_DES_RGL_CMD_DES_MPDO_BIT_OFF    28
#define CMD_DES_RGL_CMD_RAID_CMD1_MASK      0xF
#define CMD_DES_RGL_CMD_RAID_CMD1_BIT_OFF   12
#define CMD_DES_RGL_CMD_RAID_ID1_MASK       0xF
#define CMD_DES_RGL_CMD_RAID_ID1_BIT_OFF    8
#define CMD_DES_RGL_CMD_RAID_CMD0_MASK      0xF
#define CMD_DES_RGL_CMD_RAID_CMD0_BIT_OFF   4
#define CMD_DES_RGL_CMD_RAID_ID0_MASK       0xF
#define CMD_DES_RGL_CMD_RAID_ID0_BIT_OFF    0
/*Low Dword of 3rd long word of REGULAR DESCRIPTOR (DF=00b)*/
#define CMD_DES_RGL_XF_COUNT_MASK           0xFFFF
#define CMD_DES_RGL_XF_COUNT_BIT_OFF        16
#define CMD_DES_RGL_START_COL_ADDR_MASK     0xFFFF
#define CMD_DES_RGL_START_COL_ADDR_BIT_OFF  0

/*4th long word of REGULAR DESCRIPTOR (DF=00b)*/
#define CMD_DES_RGL_START_ROW_ADDR_2_BIT_OFF    32
#define CMD_DES_RGL_START_ROW_ADDR_1_BIT_OFF    0

/*5th long word of REGULAR DESCRIPTOR (DF=00b)*/
#define CMD_DES_RGL_START_ROW_ADDR_4_BIT_OFF    32
#define CMD_DES_RGL_START_ROW_ADDR_3_BIT_OFF    0

/*6th long word of REGULAR DESCRIPTOR (DF=00b)*/
#define CMD_DES_RGL_START_ROW_ADDR_6_BIT_OFF    32
#define CMD_DES_RGL_START_ROW_ADDR_5_BIT_OFF    0

/*7th long word of REGULAR DESCRIPTOR (DF=00b)*/
#define CMD_DES_RGL_START_ROW_ADDR_8_BIT_OFF    32
#define CMD_DES_RGL_START_ROW_ADDR_7_BIT_OFF    0

/*High Dword of 1st long word of GENERIC DESCRIPTOR (DF=10b)*/
#define CMD_DES_GEN_FD_BIT_OFF          31
#define CMD_DES_GEN_LD_BIT_OFF          30
#define CMD_DES_GEN_READY_MASK          0x7
#define CMD_DES_GEN_READY_BIT_OFF       27
#define CMD_DES_GEN_LC_BIT_OFF          26
#define CMD_DES_GEN_LE_BIT_OFF          25
#define CMD_DES_GEN_HCI_BIT_OFF         24
#define CMD_DES_GEN_EM_BIT_OFF          21
#define CMD_DES_GEN_MV_BIT_OFF          18
#define CMD_DES_GEN_HV_BIT_OFF          17
#define CMD_DES_GEN_DV_BIT_OFF          16
#define CMD_DES_GEN_PA_BIT_OFF          14
#define CMD_DES_GEN_DF_MASK             0x3
#define CMD_DES_GEN_DF_BIT_OFF          12
#define CMD_DES_GEN_ML_BIT_OFF          11
#define CMD_DES_GEN_DES_TYPE_MASK       0x3
#define CMD_DES_GEN_DES_TYPE_BIT_OFF    8
#define CMD_DES_GEN_CH_MASK             0xF
#define CMD_DES_GEN_CH_BIT_OFF          4
#define CMD_DES_GEN_DEV_MASK            0xF
#define CMD_DES_GEN_DEV_BIT_OFF         0

/*Low Dword of 1st long word of GENERIC DESCRIPTOR (DF=10b)*/
#define CMD_DES_GEN_AU_SEG_BIT_OFF      24
#define CMD_DES_GEN_RAID_CMD_MASK       0xF
#define CMD_DES_GEN_RAID_CMD_BIT_OFF    20
#define CMD_DES_GEN_RAID_ID_MASK        0xF
#define CMD_DES_GEN_RAID_ID_BIT_OFF     16
#define CMD_DES_GEN_AU_NUM_MASK         0x7
#define CMD_DES_GEN_AU_NUM_BIT_OFF      12

/*High Dword of 2nd long word of GENERIC DESCRIPTOR (DF=10b)*/
#define CMD_DES_GEN_AU_FORMAT_MASK      0x1F
#define CMD_DES_GEN_AU_FORMAT_BIT_OFF   9
#define CMD_DES_GEN_AES_KEYSEL_MASK     0x1F
#define CMD_DES_GEN_AES_KEYSEL_BIT_OFF  4

/*High Dword of 3rd long word of GENERIC DESCRIPTOR (DF=10b)*/
#define CMD_DES_GEN_RAID_SID_MASK           0xF
#define CMD_DES_GEN_RAID_SID_BIT_OFF        28
#define CMD_DES_GEN_OPT_CRC_MASK            0x3
#define CMD_DES_GEN_OPT_CRC_BIT_OFF         20
#define CMD_DES_GEN_OPT_CRC_ENH_MASK        0x3
#define CMD_DES_GEN_OPT_CRC_ENH_BIT_OFF     18
#define CMD_DES_GEN_OPT_ISS_00_DAT_BIT_OFF  17
#define CMD_DES_GEN_OPT_ISS_ADR_MASK        0x3
#define CMD_DES_GEN_OPT_ISS_ADR_BIT_OFF     15
#define CMD_DES_GEN_OPT_FNL_STA_MASK        0x3
#define CMD_DES_GEN_OPT_FNL_STA_BIT_OFF     13
#define CMD_DES_GEN_OPT_ISS_00_CMD_OFF      12
#define CMD_DES_GEN_OPT_2ND_CMD_CYC_OFF     11
#define CMD_DES_GEN_OPT_1ST_CMD_CYC_OFF     10
#define CMD_DES_GEN_OPT_RST_ADD_OFF         9
#define CMD_DES_GEN_OPT_CMD_POL_MASK        0x3
#define CMD_DES_GEN_OPT_CMD_POL_BIT_OFF     7
#define CMD_DES_GEN_OPT_WAT_CNT_MASK        0xF
#define CMD_DES_GEN_OPT_WAT_CNT_BIT_OFF     3
#define CMD_DES_GEN_OPT_ADR_TYP_MASK        0x7
#define CMD_DES_GEN_OPT_ADR_TYP_BIT_OFF     0

#define CMD_DES_GEN_OPT_ISS_COL_ROW_ADR     0x0
#define CMD_DES_GEN_OPT_ISS_COL_ADR         0x1
#define CMD_DES_GEN_OPT_ISS_ROW_ADR         0x2
#define CMD_DES_GEN_OPT_NOT_ISS_ADR         0x3
#define CMD_DES_GEN_OPT_ISS_LSB_COL_ADR     0x4

/*Low Dword of 3rd long word of GENERIC DESCRIPTOR (DF=10b)*/
#define CMD_DES_GEN_XF_COUNT_MASK           0xFFFF
#define CMD_DES_GEN_XF_COUNT_BIT_OFF        16
#define CMD_DES_GEN_START_COL_ADDR_MASK     0xFFFF
#define CMD_DES_GEN_START_COL_ADDR_BIT_OFF  0

/*High Dword of 4th long word of GENERIC DESCRIPTOR (DF=10b)*/
#define CMD_DES_GEN_CMD1_MASK               0xFF
#define CMD_DES_GEN_CMD1_BIT_OFF            24
#define CMD_DES_GEN_CMD2_MASK               0xFF
#define CMD_DES_GEN_CMD2_BIT_OFF            16
#define CMD_DES_GEN_SCMD_MASK               0xFF
#define CMD_DES_GEN_SCMD_BIT_OFF            8
#define CMD_DES_GEN_FAIL_MASK               0xFF
#define CMD_DES_GEN_FAIL_BIT_OFF            0

/*Low Dword of 4th long word of GENERIC DESCRIPTOR (DF=10b)*/
#define CMD_DES_GEN_START_ROW_ADDR_BIT_OFF  0

//#define AUXILIARY_SUPPORT
#define SPM_BASE_START  0x1B000000L //  80k
#define SPM_BASE_END      0x1B013FFFL
#define DF_START        SPM_BASE_START
//#define MAX_NR_DES          260 /*Maximum number of descriptors with auxiliary support*/
#define MAX_NR_DES          1024 /*Maximum number of descriptors with auxiliary support*/
#define DESCRIPTOR_LENGTH       32  /*Length of descriptor in bytes*/
#ifdef AUXILIARY_SUPPORT
#define AUXILIARY_LENGTH        12 /*Maximum length of auxiliary data in bytes*/
//#define AUXILIARY_LENGTH        4 /*Maximum length of auxiliary data in bytes*/
#endif
#define DF_SIZE         (MAX_NR_DES * DESCRIPTOR_LENGTH)
#define DF_END          (DF_START + DF_SIZE - 8)

#define TRKM_START      (DF_END + 8)   
    /*32 trk and 256 des each track*/
#define TRKM_SIZE          0x3100
#define TRKM_END        (TRKM_START + TRKM_SIZE - 4)
#ifdef AUXILIARY_SUPPORT
    /*Auxiliary insert FIFO*/
    #define AIF_START       (TRKM_END + 4)
    #define AIF_SIZE        (MAX_NR_DES * AUXILIARY_LENGTH)
    #define AIF_END         (AIF_START + AIF_SIZE - 4)

    /*Auxiliary compare FIFO*/
    #define ACF_START       (AIF_END + 4)
    //#define ACF_SIZE        (MAX_NR_DES * AUXILIARY_LENGTH)
	#define ACF_SIZE        (256 * AUXILIARY_LENGTH)
    #define ACF_END         (ACF_START + ACF_SIZE - 4)

    /*Auxiliary extract FIFO*/
    #define AEF_START       (ACF_END + 4)
    //#define AEF_SIZE        (MAX_NR_DES * AUXILIARY_LENGTH)
	#define AEF_SIZE        (256 * AUXILIARY_LENGTH)
    #define AEF_END         (AEF_START + AEF_SIZE - 4)
#endif /*End of #ifdef AUXILIARY_SUPPORT*/
/*AU Encode FIFO*/
#ifdef AUXILIARY_SUPPORT
    #define AENC_START      (AEF_END + 4)
#else
    #define AENC_START      (TRKM_END + 4)
#endif /*End of #ifdef AUXILIARY_SUPPORT*/
#define AENC_SIZE       0x40
#define AENC_END        (AENC_START + 20 * AENC_SIZE - 20)

/*AU Decode FIFO*/
#define ADEC_START      (AENC_END + 20 + 4 - ((AENC_END + 20) % 4))
#define ADEC_SIZE       0x40
#define ADEC_END        (ADEC_START + 20 * ADEC_SIZE - 20)

#define DF_8BYTE_ALIGN_END (DF_END + 4)

#define SEQ_DESC_RDSR_0          0   //0x70

/**
    <b>Macro for copyback FAA</b>
    
    \par Description:
    \n 0x78 for micron or 0x71 for toshiba
*/
#define SEQ_DESC_RDSR_1          1   //0x78 for micron or 0x71 for toshiba

/**
    <b>Macro for copyback FAA</b>
    
    \par Description:
    \n 0xF1
*/
#define SEQ_DESC_RDSR_2          2   //0xF1

/**
    <b>Macro for copyback FAA</b>
    
    \par Description:
    \n 0xF2
*/
#define SEQ_DESC_RDSR_3          3   //0xF2

#define READ_OPERATION             0
#define WRITE_OPERATION            1
#define ERASE_OPERATION            2
#define XF_COUNT_BIT_OFF                        16

#define FDMA_DEC_REG_BASE   0x80060000L
#define FDMA_ENC_REG_BASE   0x80070000L
#define FLASHDMA_DEC    0
#define FLASHDMA_ENC    1
#define FLASHDMA_MAX    2

// alias
#define FLASHDMA_READ   FLASHDMA_DEC
#define FLASHDMA_WRITE  FLASHDMA_ENC

#define DMA_CONFIG              0x900
#define DMA_CONTROL             0x904
#define DMA_ENABLE  (1 << 0)
#define DMA_RESET   (1 << 1)
#define DMA_ABORT   (1 << 2)
#define DMA_ERROR   (1 << 30)
#define DMA_ACTIVE  (1 << 31)
#define DMA_LST_ADDR            0x908
#define DMA_LST_ADDR_HI         0x90c
#define DMA_DELV_Q_CONFIG       0x910
#define DMA_QUEUE_SIZE_MASK 0xFFF
#define DMA_QUEUE_ENABLE    (1 << 16)
#define DMA_DELV_Q_ADDR         0x914
#define DMA_DELV_Q_ADDR_HI      0x918
#define DMA_DELV_Q_WR_PTR       0x91c
#define DMA_DELV_Q_RD_PTR       0x920
#define DMA_CMPL_Q_CONFIG       0x924
#define DMA_CMPL_Q_ADDR         0x928
#define DMA_CMPL_Q_ADDR_HI      0x92c
#define DMA_CMPL_Q_WR_PTR       0x930
#define DMA_COAL_CONFIG         0x938
#define DMA_COAL_TIMEOUT        0x93c
#define DMA_IRQ_STAT            0x940
#define DMA_CMD_CMPL_IRQ     (1 << 0)
#define DMA_PARITY_ERR_IRQ   (1 << 2)
#define DMA_UR_ERR_IRQ       (1 << 3)
#define DMA_IRQ_MASK            0x944
#define DMA_SM_STATE            0x948
#define DMA_INTEFACE_SEL_REG0   0x950
#define DMA_INTEFACE_SEL_REG1   0x954
#define DMA_INTEFACE_SEL_REG2   0x958
#define DMA_INTEFACE_SEL_REG3   0x95c
#define DMA_INTEFACE_SEL_REG4   0x960
#define DMA_INTEFACE_SEL_REG5   0x964
#define DMA_INTEFACE_SEL_REG6   0x968
#define DMA_INTEFACE_SEL_REG7   0x96c
#define DMA_ERR_CODE            0x970
#define DMA_ERR_TBL_ADDR        0x974
#define DMA_ERR_TBL_ADDR_HI     0x978
#define DMA_AU_SIZE             0x980
#define DMA_R988                0x988
#define DMA_R98C                0x98C
#define DMA_R990                0x990

#define DDR_ATTR            0x59L
#define SPD_ATTR            0x59L
#define SD_ATTR             0x0fL
#define FDMA_ATTR           0x59L

#define IF_SDMMC                0
#define IF_DDR                  1
#define IF_SPD                  2
#define IF_FDMA_D               3
#define IF_FDMA_E               4

#define IF_SEL_REG(x)   (DMA_INTEFACE_SEL_REG0 + (x) * 4)
#define FLASHDMA_SD_IF          IF_SDMMC
#define FLASHDMA_DDR_IF         IF_DDR
#define FLASHDMA_SPD_IF         IF_SPD
#define FLASHDMA_FDMA_D_IF      IF_FDMA_D
#define FLASHDMA_FDMA_E_IF      IF_FDMA_E

#define UNIT_ATTR_MBUS_ID(attr, mbus_id)    \
    (((attr) << 24) | (1L << (mbus_id)))

#define SD_MBUS_ID          0x0
#define SPI_MBUS_ID			0x1
#define GPIO_MBUS_ID        0x1
#define UART_MBUS_ID        0x1
#define CPU_MBUS_ID         0x2
#define FDMA_DEC_MBUS_ID    0x3
#define FDMA_ENC_MBUS_ID    0x4
#define SPD_MBUS_ID			0x5
#define DDR_MBUS_ID         0x7             // LPDDR data port MBUS ID

#define INTRFC_DDR        UNIT_ATTR_MBUS_ID(DDR_ATTR, DDR_MBUS_ID)
#define INTRFC_SRAM       UNIT_ATTR_MBUS_ID(SPD_ATTR, SPD_MBUS_ID)
#define INTRFC_SD         UNIT_ATTR_MBUS_ID(SD_ATTR, SD_MBUS_ID)
#define INTRFC_FDMA_D     UNIT_ATTR_MBUS_ID(FDMA_ATTR, FDMA_DEC_MBUS_ID)
#define INTRFC_FDMA_E     UNIT_ATTR_MBUS_ID(FDMA_ATTR, FDMA_ENC_MBUS_ID)

#define INTR_COAL_CFG_VALUE     0   // ((1L<<16) | 0x1ff)
#define INTR_COAL_TIMEOUT_VALUE 0   // ((1L<<16) | 0x2000)

#define TBL_DATA                0 //tbl0
#define TBL_META                1 //tbl23[0]

#define XplusYns    9250

typedef struct _dev_rw_timing_t
{
    u16 t_rel;                              // RE# low hold time
    u16 t_reh;                              // RE# high hold time
    u16 t_wel;                              // WE# low hold time
    u16 t_weh;                              // WE# high hold time
    u16 t_rea;                              // RE# access time
} dev_rw_timing_t;


// 56 bytes
typedef struct _nand_t
{
    u8 id[7];           // ID4321
    u8 nr_id_byte;      // number of valid bytes of id
    
    u16 total_space_in_gbit;
    u16 nr_page_per_block;

    u16 spare_sz;
    u16 nr_bad_blocks_max;

    u32 page_sz;

    u32 endurance;

    u8 nr_luns;
    u8 nr_planes;

    u8 io_1p8v;         // select NAND interface voltage, 0 for 3.3V, 1 for 1.8V

    u8 dev_type;                                    // device type defined above
    
    u8 max_mode_nr;
    u8 factory_defect_check_pages;                  // factory defect blocks check the assigned pages
                                                    // bit0:3 for first page +0, +1, +2, +3; 
                                                    // bit4:7 for  last page -3, -2, -1, -0
    u8 cell_type;                                   // number of bits per cell, 0:1; 1:2; 2:3; 3:4               
    u8 rsvd;                                        // reserved for future use
    
    u16 rd_dly_us;                                  // rd_dly_us: read delay time in us.
    u16 wrt_dly_us;                                 // wrt_dly_us: write delay time in us.
    u16 ers_dly_us;                                 // ers_dly_us: erase delay time in us.
    u16 rst_dly_us;                                 // rst_dly_us: reset delay time in us.
    u16 tcad_ns;                                    // tCAD parameter, cmd, adr, data delay    
    u16 trhw_ns;                                    // tRHW parameter, RE# high to WE# low
    u16 tccs_ns;                                    // tCCS parameter, change column setup to data in/out or next command
    u16 opt_cmds_spt;                               // optional commands support
    //u16 rsvd2[2];  
} nand_t;

typedef struct _nvhwcfg_t
{
    u32 fc_clk_mhz;                         //flash controller clock in MHz
    u32 fc_clk_freq_ps;                     //flash controller clock period in ps
//    u32 encoded_ecc_au_sz;                  //encoded ECC AU size including ECC and data
//    u32 encoded_ecc_au_sz1;
//    u32 encoded_page_sz;                    //encoded page size including ECC and data
//    u32 encoded_page_sz1;                    //encoded page size includi
//    u32 encoded_ecc_au_meta_read_only_sz;   //HW ECC AU Meta data size including ECC and meta data
//    u32 encoded_page_meta_read_only_sz;     //HW page Meta data size including ECC and meta data
    u8 t_weak;                              //ECC correction bits for weak
    u8 t_strong;                            //ECC correction bits for strong
//    u8 t_meta;                              //ECC correction bits for meta
//    u8 meta_mcrc_enable;                    //ECC meta media-crc enable
//    u8 meta_ecc_enable;                     //ECC meta ecc enable
//    u8 au_mcrc_enable;                        //ECC AU media-crc enable
    //u8 rsv[2];
    //u8 two_level_bch15;                     //ECC two level
    u8 timing_mode_sel;                     //NAND timing mode selection
    u8 flash_type;                          //flash type, same as R5B600 bit3:2

    // 0: Type-A; 1: Type-B; 2: Type-C
    //u8 flash_access_mode;                   //flash type, same as R5B600 bit1:0
    // 0: direct; 1: indirect; 2: sequencer
} nvhwcfg_t;

typedef struct _dev_t
{
    u8 ch;
    u8 dev;
    u8 chdev;                           // (ch << 4) | dev
    u8 rsvd;
} dev_t;

typedef struct _nvcfg_t
{
    //u32 state;
    //u16 stage;                              // NV_STAGE_xxx
    //int err_powerup;                        // records power on error status

    /*------------------------------------------------------------------------------*/

    /* 
     * following fields are initialized in nvcfg_init_flash_related (called by
     * nvcfg_init_prolog. These fields are determined by mounted flash devices
     */
    u32 ecc_au_sz;                          // ECC AU size                                                                   nvcfg.ecc_au_sz = nand->page_sz
    u32 page_sz;                            // page data size                                                                 nvcfg.page_sz = nand->page_sz
    u32 full_page_sz;                       // page data size plus spare size                                           nvcfg.full_page_sz = nand->page_sz + nand->spare_sz
    u32 nr_defect_max;                      // maximum number of defect blocks
    u32 endurance;                          // block endurance
    u16 total_sz_in_GB;                     // total size in giga bytes                                                   nvcfg.total_sz_in_GB = (nand->total_space_in_gbit >> 3) *nvcfg.nr_ch *nvcfg.nr_dev_per_ch
    u16 nr_page_per_eu;                     // number of pages per device erase unit (block)                   nvcfg.nr_page_per_eu = nand->nr_page_per_block
 
    u8 ecc_au_sz_shift;                     // 2 ^ ecc_au_sz_shift = ecc_au_sz
    u8 page_sz_shift;                       // 2 ^ page_sz_shift = page_sz
    u8 nr_page_per_eu_shift;                // 2 ^ nr_page_per_eu_shift = nr_page_per_eu
    u8 rsv0[1];                             // reserved to keep 32bit alignment
    u32 faa_sz;                             // FAA data size                                                                       nvcfg.faa_sz = _max(nvcfg.page_sz, nvcfg.ecc_au_sz);
    u16 nr_page_per_faa;                    // number of page per FAA                                                 1
    u16 nr_ecc_au_per_page;                 // number of ECC AU per page                                         1
    u8 faa_sz_shift;                        // 2 ^ faa_sz_shift = faa_sz
    u8 nr_page_per_faa_shift;               // 2 ^ nr_page_per_faa_shift = nr_page_per_faa
    u8 nr_ecc_au_per_page_shift;            // 2 ^ nr_ecc_au_per_page_shift = nr_ecc_au_per_page
    u8 rsv1[2];                             // reserved to keep 32bit alignment

    /* 
      * following fields are initialized in cfg_init_lb_related. They are
      * logical block (sector) related. The wear leveling itself doesn't
      * care about these fields. The upper command translation layer cares.
      */
//    u32 lb_sz;                              // logical block (aka. sector) size in byte */
//    u8 lb_sz_shift;                         // 2 ^ lb_sz_shift = lb_sz

    /*------------------------------------------------------------------------------*/

    // following fields are initialized in device_discovery
    u8 tag0[2];
    u8 nand_device_class;                   // 0: Unknown, 1: Listed Conventional, 2: ONFI, 3: TOGGLE
                                           
    u8 nand_device_type;                    // 0: Samsung Conventional; 1: others
    u8 nr_ch;                               // number of channels
    u8 nr_plane_per_lun;
    u8 nr_lun_per_dev;

    u8 nr_dev_per_ch;                       // number of devices per channel
    u8 nr_ch_shift;                         // 2 ^ nr_ch_shift = nr_ch
    u8 nr_plane_per_lun_shift;              // 2 ^ nr_plane_per_lun_shift = nr_plane_per_lun
    u8 nr_lun_per_dev_shift;                // 2 ^ nr_lun_per_dev_shift = nr_lun_per_dev
    u8 nr_dev_per_ch_shift;                 // 2 ^ nr_dev_per_ch_shift = nr_dev_per_ch
    u8 nr_ch_plane_shift;                   // nr_ch_plane_shift = nr_ch_shift + nr_plane_per_lun_shift
    u8 nr_ch_plane_lun_shift;               // nr_ch_plane_lun_shift = nr_ch_shift + nr_plane_per_lun_shift + nr_lun_per_dev_shift
    u8 nr_ch_plane_dev_shift;               // nr_ch_plane_dev_shift = nr_ch_shift + nr_plane_per_lun_shift + nr_dev_per_dev_shift
    u8 lun_to_page_shift;                   // 2 ^ lun_to_page_shift = number of pages in a LUN
    u8 rsv3[3];

    u32 mp_read_device_address;             // for mp operation, set 0 to DW0 of descriptor for samsung devices, SEQ_DESC_SA for other devices
    u32 lun_des_type;                       // for ml operation, set this value to DW0 for lun enable/disable
    u16 nr_wdevs;                           // number of wide devices, = nr_ch * nr_plane_per_lun * nr_lun_per_dev * nr_dev_per_ch
    u16 defect_array_size;                  // defect map array size, = nr_wdevs/32
    u16 nr_ch_plane;                        // number of ch & plane, = nr_plane_per_lun * nr_ch
    u16 nr_eu_per_plane;                    // number of erase units (blocks) per plane.

    u8 nr_wdevs_shift;                      // 2 ^ nr_wdevs_shift = nr_wdevs
    u8 ch_consecutive;                      // 1: channel consecutive
    u8 dev_consecutive;                     // 1: device consecutive
    u8 chdev;                               // higher half byte: maximum channels, lower half byte: minimum channels 

    u8 flash_id[8];                         // flash ID string, so far we can only support unique flash device type
    dev_t devs[32];  // quick translation from device id to ch/dev
    u16 opt_cmds_spt;                       // optional commands support
    u16 rsv[1];
} nvcfg_t;


//flexible au format structure
typedef struct _flex_au_fmt
{
//user input
    u32 flex_au_setting_0; //combination of flexible au setting
                           //Bit 7: Meta ECC enable. Only used when only metadata is read.
                           //Bit 6: MCRC inv mode. 0: Enable (default and recommended) 1: Disable
                           //Bit 5: ECC inv mode. 0: Enable (default and recommended) 1: Disable
                           //Bit 4: fit_2_phy_page. Fit ECU to physial page boundary by zeros padding if enabled.
                           //Bit 3: au media-CRC enable.
                           //Bit 2: metadata media-CRC enable.
                           //Bit 1: user data scrambler enable.
                           //Bit 0: meta data scrambler enable.

    u32 flex_au_setting_1; 
                           //BIT 7: MPECC mode enable.
                           //BIT 6: metadata scrambler output invert enable.
                           //BIT 4-5: userdata scrambler seed source selection. 
                           //BIT 2-3: metadata scrambler seed source selection.

//comment for settings for debug use (raw data, etc.)

    u16 host_sector_size; // host sector size in bytes
    u16 meta_size;        // meta data size. (maximum 512 bytes, must be 4-bytes multiplier)

    u8  aux_size;         // aux data size. (0, 4, 8, 12 bytes)
    u8  meta_data_only;   // metadata only mode: 0: OFF 1: ON                            
    u8  t_strong;         // t-strong
    u8  t_weak;           // t-weak

    u8  meta_t;           // correction power for meta ECC 
    u8  page_au_ratio;        //number of au per page
    u8  ecu_hlba_strip_mode;  // HLBA stip mode    
    u8  ecu_hlba_mode;        // Host LBA mode
// need get from nand
    u16 phy_page_size;       // physical page size in bytes. Read from NAND
    u8  two_level_en;        // two-level ECC enable 1: both T-strong and T-weak
    u8  cw_per_au;           // number of ECC codewords per AU

//calculated
    u8  meta_threshold;   // threshold for meta-ECC
    u8  erase_threshold_weak; //erase page detection threshold
    u8  threshold_strong; // threshold strong
    u8  threshold_weak;   // threshold weak

    u16 ecu2host_ratio;   // AU to host sector size ratio. 
    u16 rsvd;

    u32 encoded_ecc_au_sz;                 // encoded ECC AU size including ECC and data
    u32 encoded_page_sz;                   // encoded page size including ECC and data
    u32 encoded_ecc_au_meta_read_only_sz;  // HW ECC AU Meta data size including ECC and meta data
    u32 encoded_page_meta_read_only_sz;    // HW page Meta data size including ECC and meta data
} flex_au_fmt, *flex_au_fmt_ptr;

typedef struct _ec_nvcfg_t
{
    u32 full_page_sz;
    u32 page_sz;
    u8  nr_ecc_au_per_page_shift;
    u8  rsvd[3];
} ec_nvcfg_t;

typedef struct _ecc_power_fmt
{
    u16 spare_sz;
    u8 t_weak;
    u8 t_strong;
}ecc_power_fmt;

typedef struct _onfi_param_page_t
{
    // it sucks that the ONFI definition is not naturally DWORD aligned...

    // revision information and features block
    u32 signature;          // ONFI_PARAM_PAGE_SIGNATURE
    u16 revision;           // ONFI_REV_xxx
    u16 features;           // ONFI_FEATURE_xxx
    u16 opt_cmds;           // ONFI_OPT_CMD_xxx
    u16 rsvd_byte_10_11;
    u16 ext_param_page_len;
    u8 nr_param_pages;
    u8 rsvd_byte_15_31[17];
    
    // manufacture information block, offset 32
    u8 manufacture[12];
    u8 model[20];
    u8 jedec_id;
    u8 date_code[2];
    u8 rsvd_byte_67_79[13];
    
    // memory organization block, offset 80
    u8 page_sz[4];
    u8 spare_sz[2];
    u8 partial_page_sz[4];
    u8 partial_spare_sz[2];
    u8 nr_pages_per_block[4];
    u8 nr_blocks_per_lun[4];
    u8 nr_luns;
    u8 nr_addr_cycles;      // bit0-3: row address cycles, bit4..7: column address cycles
    u8 nr_bits_per_cell;
    u8 nr_bad_blocks_per_lun_max[2];
    u8 block_endurance[2];
    u8 guaranteed_valid_blocks;
    u8 guaranteed_valid_blocks_endurance[2];
    u8 nr_progs_per_page;
    u8 partial_prog_attrs;
    u8 nr_ecc_corr;
    u8 nr_interleaved_addr_bits;
    u8 interleaved_op_attrs;
#define ONFI_INTERLEAVE_OP_READ_CACHE_SUPPORT   (1 << 4)
#define ONFI_INTERLEAVE_OP_ADDR_REST_PROG_CACHE (1 << 3)
#define ONFI_INTERLEAVE_OP_PROG_CACHE_SUPPORT   (1 << 2)
#define ONFI_INTERLEAVE_OP_NO_BLOCK_ADDR_REST   (1 << 1)
#define ONFI_INTERLEAVE_OP_OVERLAPPED_SUPPORT   (1 << 0)

    u8 rsvd_byte_115_127[13];
    
    // Electrical parameters block, offset 128
    u8 io_pin_cap_max;
    u8 async_timing_modes[2];
    u8 async_prog_cache_timing_modes[2];
    u8 t_prog_max[2];       // in us
    u8 t_bers_max[2];       // in us
    u8 t_r_max[2];          // in us
    u8 t_ccs_min[2];        // in ns
    u8 src_sync_timing_modes[2];
    u8 src_sync_features;
    u8 clk_in_pin_cap_typ[2];
    u8 io_pin_cap_typ[2];
    u8 in_pin_cap_typ[2];
    u8 in_pin_cap_max;
    u8 driver_strengths;
    u8 t_r_max_interleaved[2];
    u8 rsvd_byte_154_163[10];
    
    // vendor block, offste 164
    u16 ven_revision;
    u8 vendor_specific[88];
    u16 crc;
} onfi_param_page_t;

typedef struct _toggle_param_page_t
{
    // it sucks that the TOGGLE definition is not naturally DWORD aligned...

    // revision information and features block
    u32 signature;          // JESD(TOGGLE)_PARAM_PAGE_SIGNATURE
    u16 revision;           // TOGGLE_REV_xxx
    u16 features;           // TOGGLE_FEATURE_xxx
    u8 opt_cmds[3];         // TOGGLE_OPT_CMD_xxx
    u8 rsvd_byte_11_31[21]; // reserved
    
    // manufacture information block, offset 32
    u8 manufacture[12];
    u8 model[20];
    u8 jedec_id;
    u8 rsvd_byte_65_79[15];
    
    // memory organization block, offset 80
    u8 page_sz[4];
    u8 spare_sz[2];
    u8 rsvd_byte_86_89[4];
    u8 rsvd_byte_90_91[2];
    u8 nr_pages_per_block[4];
    u8 nr_blocks_per_lun[4];
    u8 nr_luns;
    u8 rsvd_byte_101_152[52];
    u8 t_prog_max[2];        // in us
    u8 t_bers_max[2];        // in ms
    u8 t_r_max[2];           // in us
    u8 t_r_mp_man[2];        // in ns
    u8 rsvd_byte_161_255[95];    
} toggle_param_page_t;


//flexible au format return
typedef struct _flex_au_rtn_fmt
{
    u32 encoded_ecc_au_meta_read_only_sz;
    u32 encoded_ecc_au_sz;
    u32 encoded_page_sz;
    u32 encoded_page_meta_read_only_sz;
    u16 ecu2host_ratio;
    u16 host_sector_size;    
    u16 meta_size;
    u8  aux_size;         // aux data size. (0, 4, 8, 12 bytes)
    u8  meta_data_only;
    u32 au_format_no;
} flex_au_rtn_fmt;




typedef struct _cmd_des_gen_info
{
	u8 au_cnt;
	u8 tid;
	u8 rdy_bit;
	u8 fail_bit;	

	u8 au_seg;
	u8 fst_des;
	u8 lst_des;
	u8 readpad;
	
	u8 ch;
	u8 device;
	u8 scd_cmd_off;//option[11]
	u8 fst_cmd_off;//option[10]

	u8 au_format_no;
	u8 status_poll_time;//option[8:7]
	u8 status_wait_time;//option[6:3]
	u8 add_type;//option[2:0]	

	u8 des_cmd;//0-read 1-program 2-erase	
	u8 scmd;
	u8 cmd2;
	u8 cmd1;

	u16 col_add;
	u16 encoded_ecc_au_sz;

	u32 row_add;
    
} cmd_des_gen_info;

typedef struct _cmd_fc_info
{
	u8 ch;
	u8 device;	
	u16 data_len;	
	
	u16 phyblock;
	u16 phypage;
	u32 buf_add; 
	u32 padbuf_add; 
} cmd_fc_info;

typedef struct _row_tuple_t
{
    u8 lun;
    u8 plane;
    u8 rsvd[2];
    u32 block;
    u32 page;
} row_tuple_t;

typedef struct _urow_tuple_t
{
    u8 ch;
    u8 device;
    u8 rsvd[2];
    row_tuple_t rt;
} urow_tuple_t;

typedef struct _fc_cmd_r
{
	u8 ch;
	u8 device;
	u8 au_type;//0 for data(2 au/page), 1 for table(8 au/page)
	u8 au_seg;
	
	u32 ssdindex;
	
	u32 page_add; 
	u32 data_add;// 1 add for data,   8 add for table
	u32 meta_add;// 1 add for data,   8 add for table
}fc_cmd_r;

typedef struct _fc_cmd_w
{
	u8 ch;
	u8 device;
	u8 au_type;//0 for data(2 au/page), 1 for table(8 au/page)
	u8 au_seg;
	
	u32 ssdindex;
	
	u32 page_add; 
	u32 data_add;// 1 add for data,   8 add for table
	u32 meta_add;// 1 add for data,   8 add for table
}fc_cmd_w;

typedef struct _fc_cmd_w_2plane
{
	u8 ch;
	u8 device;
	u8 au_type;//0 for data(2 au/page), 1 for table(8 au/page)
	u8 au_seg;

	u32 ssdindex;
	
	u32 page_add_p0; 
	u32 page_add_p1;
	u32 data_add[2];// 2*8k
	u32 meta_add[2];
}fc_cmd_w_2plane;

typedef struct _fc_cmd_e
{
	u8 ch;
	u8 device;	
	u16 block; 	
}fc_cmd_e;

typedef struct _fc_trk_seg
{
	volatile u8 id;
	volatile u8 rw;	
	volatile u8 fs_num; 
	volatile u8 es_num; 
}fc_trk_seg;

typedef struct _fc_rtn_val
{
	u16 seg_num;
	u16 ssd_index;	
	u32 data_add; 	
}fc_rtn_val;

typedef struct _fc_cmd
{
	volatile u8 ch;
	volatile u8 device;
	volatile u8 cmd_type;
	volatile u8 resev0;
	
	volatile u8 au_type;
	volatile u8 au_offset;
	volatile u8 au_cnt;
	volatile u8 readpad;

	volatile u8 tid_num;
	volatile u8 seg_num;	
	volatile u8 fst_des;
	volatile u8 lst_des;
	
	volatile u16 ssd_index;
	volatile u16 cache_index;

	volatile u16 phyblk_add;
	volatile u16 phypage_add; 
	
	//volatile u32 data_add;
	//volatile u32 meta_add;
}fc_cmd;





/*
typedef struct _fc_die_sts
{
	u32 Au_Cnt;
	u16 Ssd_Index[8];
	u32 Lba[8];// if cache record, cancel
}fc_die_sts;
fc_die_sts die_sts[8];

typedef struct _fc_track_sts
{
	u8 Is_Program;// if 10h,release ssd
	u8 Fs_Num;// if data in, release fs
	u16 Die_Num;
}fc_track_sts;
fc_track_sts track_sts[32];  

typedef struct _fc_read_cmd_sts
{
	u8 tag;
	u8 Es_Num;
	u16 Ssd_Index;
}fc_read_cmd_sts;
u8 Es_sts[8];
*/
#define NR_SUPPORTED_DEVS   (sizeof(_supported_devices) / sizeof(nand_t))
#define DMA_COMP_Q_ENT_SLOT_MASK    ((1 << 12) - 1)


extern nand_t nand_detected;
extern nvhwcfg_t nvhwcfg;
extern nvcfg_t nvcfg;
extern onfi_param_page_t pparam_data_three_copies[3];

extern volatile u8 tid_sts[32];
extern volatile u8 tid_error[32];
extern volatile u8 fs_sts[8];
extern volatile u8 es_sts[8];
extern fc_trk_seg trk_seg[32];
extern volatile u32 cur_tid;
extern fc_cmd fc_cmd_all;
extern volatile u32 FS_FREE_PTR;
extern volatile u32 FS_BUSY_PTR;
extern volatile u32 ES_FREE_PTR;
extern volatile u32 ES_BUSY_PTR;

void FC_Seq_Done(void);
void  InitSeq(void);
void Test(void);
u8 FC_Get_Tid(void);
u8 Ftl_Get_Chan(u32 lba);
u8 Ftl_Get_Dev(u32 lba);
u16 Ftl_Get_Phypage(u32 lba);
u16 Ftl_Get_Phyblock(u32 lba);
u8 Ftl_Get_AUoffset(u32 lba);
u8 FC_Operation(void);
u32 fctl_operation(void);
//void Test(void);
//void FC_Seq_Done(void);
//u8 FC_Program_Page_2Plane(fc_cmd_w_2plane cmd);
//void InitSsd(void);

#endif // _H_INC
