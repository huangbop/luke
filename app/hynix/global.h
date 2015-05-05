/****************************************Copyright (c)**************************************************
**                            Memoright Memoritech (Shenzhen) Co.,Ltd
**                                      RD Department
**
**                                  http://www.memoright.com
**
*******************************************************************************************************/
#ifndef SSD_GLOBAL_H
#define SSD_GLOBAL_H

/*
*********************************************************************************************************
*                                   Define the typedef Macro
*********************************************************************************************************
*/
typedef unsigned char                      BOOLEAN; 
typedef unsigned char                      INT8U; 
typedef unsigned short                     INT16U;
typedef unsigned int                       INT32U;
typedef signed char                        INT8S;


#define TRUE                               1
#define FALSE                              0
//add by yao_qs 20100728
/*---------------------------*/
#define SUCCESS                            0
#define FAIL                               1
#define NULL                               0
/*
*********************************************************************************************************
*                                   Define the typedef Macro
*********************************************************************************************************
*/
#define IO_REG08(r)                        (*((volatile unsigned char *) (r)))
#define IO_REG16(r)                        (*((volatile unsigned short *) (r)))
#define IO_REG32(r)                        (*((volatile unsigned int *) (r)))

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

/*
********************************************************************************************************
*                                 Firmware configuration
********************************************************************************************************
*/
#define SSD_25TSBBGA128G                     1    /* 2.5 Toshiba BGA 128GB SSD T0029*/
#define SSD_25TSBBGA256G                     2    /*  2.5 Toshiba BGA 256GB SSD T0030*/
#define SSD_25TSBBGA512G                     3    /*  2.5 Toshiba BGA 512GB SSD T0031*/
#define SSD_25TSBBGA512G                     4    /*  2.5 Toshiba BGA 512GB SSD T0032*/
#define SSD_25TSBBGA256G                     5    /* 2.5 Toshiba BGA 256GB SSD T0033*/
#define SSD_25TSBBGA512G                     6    /*  2.5 Toshiba BGA 512GB SSD T0034*/
#define SSD_25TSBBGA1T                     7    /*  2.5 Toshiba BGA 1TB SSD T0035*/


/* Use this macro to define all the other macros need change in FW*/
#define CFG_CURFWCONFIG                      SSD_25TSBBGA128G

#if (CFG_CURFWCONFIG == SSD_25TSBBGA128G)
#define CFG_ENABLECEMAP						           1
#define CFG_INTERLEAVEEN                     0    /* Enable(1) or Disable(0) Interleave Operation for 2.5-512 */
#define CFG_DDR768SIZEEN                     0    /* Enable(1) or Disable(0) DDR3 Size as 768MB for the 512GB SSD*/
#define DIE_SHIFT 12 // 2048 block
#define CS0DDRSIZE							 MEM_2Gb
#define CS1DDRSIZE							 MEM_0Mb
#define NUM_OF_DDR3_CHIPS                    1
#define FWVER0                               'T2'
#define FWVER1                               '9C'
#endif

#if (CFG_CURFWCONFIG == SSD_25TSBBGA256G)
#define CFG_ENABLECEMAP						           1
#define CFG_INTERLEAVEEN                     0    /* Enable(1) or Disable(0) Interleave Operation for 2.5-512 */
#define CFG_DDR768SIZEEN                     0    /* Enable(1) or Disable(0) DDR3 Size as 768MB for the 512GB SSD*/
#define DIE_SHIFT 13 // 4096 block
#define CS0DDRSIZE							 MEM_4Gb
#define CS1DDRSIZE							 MEM_0Mb
#define NUM_OF_DDR3_CHIPS                    1
#define FWVER0                               'T3'
#define FWVER1                               '0C'
#endif

#if (CFG_CURFWCONFIG == SSD_25TSBBGA512G)
#define CFG_ENABLECEMAP						           0
#define CFG_INTERLEAVEEN                     0    /* Enable(1) or Disable(0) Interleave Operation for 2.5-512 */
#define CFG_DDR768SIZEEN                     0    /* Enable(1) or Disable(0) DDR3 Size as 768MB for the 512GB SSD*/
#define DIE_SHIFT 13 // 4096 block
#define CS0DDRSIZE							 MEM_4Gb
#define CS1DDRSIZE							 MEM_2Gb
#define NUM_OF_DDR3_CHIPS                    2
#define FWVER0                               'T3'
#define FWVER1                               '4C'
#endif

#if (CFG_CURFWCONFIG == SSD_25TSBBGA1T)
#define CFG_ENABLECEMAP						           0
#define CFG_INTERLEAVEEN                     1    /* Enable(1) or Disable(0) Interleave Operation for 2.5-512 */
#define CFG_DDR768SIZEEN                     0    /* Enable(1) or Disable(0) DDR3 Size as 768MB for the 512GB SSD*/
#define DIE_SHIFT 13 // 4096 block
#define CS0DDRSIZE							 MEM_4Gb
#define CS1DDRSIZE							 MEM_4Gb
#define NUM_OF_DDR3_CHIPS                    2
#define FWVER0                               'T3'
#define FWVER1                               '5C'
#endif

#define CFG_IDFY                             0    /* Enable(1) or Disable(0) FW Identify Table*/
#define CFG_NCQEN                            1    /* Enable(1) or Disable(0) FW NCQ Function*/
#define CFG_RWLOG_EXT                        0    /* Enable(1) or Disable(0) FW Log Long Cmd*/
#define CFG_FAKECQOP                         1    /* Enable(1) or Disable(0) FW FakeCQ OP*/
#define CFG_SETRAMVALUE                      0    /* Enable(1) or Disable(0) FW Set RamDefault Value*/
#define CFG_MVLBOARD                         0    /* Enable(1) or Disable(0) FW Init PLL for Marvell Board or OCZ Board*/
#define CFG_XFERFINFUN                       1    /* Enable(1) or Disable(0) FW Transfer Finish using Function*/

#endif

/*******************************************************************************************************
*                                                        End Of File
********************************************************************************************************/
