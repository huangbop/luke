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

//----------------------------------------------------------------------------
// Include files:
//----------------------------------------------------------------------------
#include "HEAD.H"
volatile u32 cur_tid;
volatile u8 tid_sts[32];
volatile u8 tid_error[32];
volatile u8 fs_sts[8];
volatile u8 es_sts[8];
fc_trk_seg trk_seg[32];
cmd_des_gen_info cmd_des_pro_info_r;
cmd_des_gen_info cmd_des_pro_info_w;
cmd_des_gen_info cmd_des_pro_info_e;
cmd_des_gen_info cmd_des_pro_info_2p_e;
cmd_des_gen_info cmd_des_pro_info_2p_datain;
cmd_des_gen_info cmd_des_pro_info_2p_prg;
cmd_des_gen_info cmd_des_pro_info_changeclm;
cmd_des_gen_info cmd_des_pro_info_2p_r;
cmd_des_gen_info cmd_des_pro_info_2p_changeclm;
cmd_des_gen_info cmd_des_pro_info_dataout;
cmd_des_gen_info cmd_des_pro_info_r_sts;
volatile u32 tabledone;

fc_cmd fc_cmd_all;
volatile u32 FS_FREE_PTR;
volatile u32 FS_BUSY_PTR;
volatile u32 ES_FREE_PTR;
volatile u32 ES_BUSY_PTR;

u32 *des_fifo_pro_dw_ptr;
#ifdef AUXILIARY_SUPPORT
/*Write pointer of inserting AUX insert data*/
u32 *ai_fifo_ins_dw_ptr;
/*Read pointer of extracting AUX data*/
u32 *ae_fifo_rd_dw_ptr;
/*Read pointer of comparing AUX data*/
u32 *ac_fifo_cmp_dw_ptr;
#endif      /* AUXILIARY_SUPPORT */
//u8 onfi_id[4] = {'O', 'N', 'F', 'I'};
//u8 jedec_id[8] = {'J', 'E', 'D', 'E', 'C', 0x02};
nand_t   nand_detected;
nvhwcfg_t nvhwcfg;
nvcfg_t nvcfg;
onfi_param_page_t pparam_data_three_copies[3];
__align(64) const nand_t  
_supported_devices[] = {
    //  ID                                                    NrID      Gbit NrPgPerBlk SpareSz  NrBadMax  
    //  PageSz Endurance   Lun   Plane    IO1p8V dev_type max_mode_nr defect_page cell_type reserved  
    //  rd_dly_us wrt_dly_us ers_dly_us rst_dly_us tcad_ns trhw_ns tccs_ns reserved
    
    //toshiba
    {  { 0x45,0xDE,0x94,0x93,0x76,0xDF,0x00},      6,       64,      256,      1280,      80,
        16384,  5000,       1,       2,       1,    0x02,       7,    0x03,       1,       0,
          50,     1400,    5000,     200,       0,       0,       0,       0  },
          
          {  { 0xAD,0x3A,0x14,0xAB,0x42,0x4A,0x00},      6,       64,      256,      1664,      80,
        18048,  5000,       1,       2,       0,    0x02,       7,    0x03,       1,       0,
          50,     1400,    5000,     200,       0,       0,       0,       0  },
          
{ { 0x98,0x3A,0x95,0x93,0x7A,0xD7,0x00},      6,       64,      256,      1280,      80,
        16384,  5000,       1,       2,       1,    0x02,       7,    0x03,       1,       0,
          50,     1400,    5000,     200,       0,       0,       0,       0  },
{  { 0x98,0xDE,0x94,0x93,0x76,0xD7,0x00},      6,       64,      256,      1280,      80,
        16384,  5000,       1,       2,       1,    0x02,       7,    0x03,       1,       0,
          50,     1400,    5000,     200,       0,       0,       0,       0  }
};
u32 au_format_index = 0;
flex_au_fmt _supported_au_fmt[AU_FORMAT_CNT];

const ecc_power_fmt 
_supported_ecc_power[2][ECC_POWER_TABLE_MAX] = {
    { {40, 10, 11}, {94, 20, 30}, {135, 30, 42}, {188, 42, 58}, 
      {242, 55, 74}, {300, 70, 90}, {400, 95, 118}, {481, 128, 128}
    },

    { {40, 5, 11},    {132, 20, 30}, {188, 29, 42}, {268, 42, 58}, 
      {339, 54, 72}, {432, 70, 90}, {495, 80, 104}, {620, 101, 128}
    }
};


static __inline u32 
clz(u32 v)
{
    __asm {
        CLZ v, v
    }

    return v;
}

static __inline u32 
ctz(u32 v)
{
    /*
     * ~v & (v-1) forms a mask that identifies the trailing 0's, producing
     * all 1's if v = 0 (e.g., 01011000->00000111)
     */

    return 32 - clz(~v & (v-1));
}

static __inline u32 
Get_Cnt_1(u32 v)
{
	u32 i;

	for(i=0;i<32;i++)
	{
		if((v&(1<<i))==0)
			return (i-1);
	}
	return 0;
}

static __inline u8
tag32_get(tag32_t *tag32)
{
    u8 tag;

    if (*tag32 == 0) {
        return 0xff;
    }

    tag = 31 - clz(isolate_rmb1(*tag32));

    *tag32 &= ~(1 << tag);
    return tag;
}

void memory_set(void *id, u8 value, u32 size)
{
	u32 i;
	u8 *data = (u8 *)id;
	for(i=0;i<size;i++)
	{
		*data++=value;
	}
}

void memory_copy(void *buf1, const void *buf2, u32 size)
{
	u32 i;
	u8 *data1 = (u8 *)buf1;
	u8 *data2 = (u8 *)buf2;
	for(i=0;i<size;i++)
	{
		*data1++ = *data2++;
	}
}

u8 memory_cmp(void *buf1, void *buf2, u32 size)
{
	u32 i;
	u8 *data1 = (u8 *)buf1;
	u8 *data2 = (u8 *)buf2;
	for(i=0;i<size;i++)
	{
		if(*data1++ != *data2++)
			return 1;
	}
	return 0;
}


void REG16_CLEAR_BITS(u32 reg, u16 mask)
{
    u16 tmp = REG16_READ(reg);
    tmp &= ~mask;
    REG16_WRITE(reg, tmp);
}

void REG16_SET_BITS(u32 reg, u16 mask)
{
    u16 tmp = REG16_READ(reg);
    tmp |= mask;
    REG16_WRITE(reg, tmp);
}

void FC_Wait_Seq_Idle(void)
{
	u16 tmp;
	
	REG16_CLEAR_BITS(FC_REG_SEQ_CNTL1, FC_READY_BIT | FC_FSEQ_EN);
	DelayUS(FC_DLY_US);

	tmp = 0;
	while ((tmp & FC_SM_IDLE) == 0)
	{
		tmp = REG16_READ(FC_REG_SEQ_CNTL2);
		DelayUS(1);
	}

	 //wait until FC_SM_IDLE is 1
    REG16_CLEAR_BITS(FC_REG_SEQ_CNTL1, FC_READY_BIT);
    REG16_SET_BITS(FC_REG_SEQ_CNTL1, (0x06 << 5) | FC_FSEQ_EN);
    DelayUS(FC_DLY_US);
}

void FC_Set_Flash_Type_H(u8 timing_mode)
{
    u16 tmp;

    FC_Wait_Seq_Idle();

    tmp = REG16_READ(FC_REG_IF_CFG);
    if (timing_mode & ONFI_SYNC_ENABLE) 
    {
        tmp |= FC_NFIF_JDBC_ONFI_SYNC;
    }
    else 
    {
        tmp &= ~FC_NFIF_JDBC_ONFI_SYNC;
    }
    REG16_WRITE(FC_REG_IF_CFG, tmp);
    DelayUS(FC_DLY_US);
}

void FC_Set_Flash_Type_L(u8 nand_device_type)
{
    u16 tmp;
    u16 type;

    if ((nand_device_type & DEV_TYPE_BASIC_MASK) == DEV_TYPE_BASIC_TOSHIBA ||
        (nand_device_type & DEV_TYPE_BASIC_MASK) == DEV_TYPE_BASIC_SAMSUNG)
    {
        type = 0x01 << 2;
    }
    else 
    {
        if ((nand_device_type & DEV_TYPE_BASIC_MASK) == DEV_TYPE_BASIC_HYNIX ||
            (nand_device_type & DEV_TYPE_BASIC_MASK) == DEV_TYPE_BASIC_MICRON) 
        {
            if (nand_device_type & DEV_TYPE_SYNC_MASK)
	     {
                type = 0x02 << 2;
            }
            else 
	     {
                type = 0x00 << 2;
            }
        }
    }
    
    FC_Wait_Seq_Idle();	
    tmp = REG16_READ(FC_REG_IF_CFG);
    tmp &= ~FC_FLTYPE_MASK;
    tmp |= (u16) type;
    REG16_WRITE(FC_REG_IF_CFG, tmp);
    DelayUS(FC_DLY_US);
}

void FC_Set_Device_Seqport(u8 nand_device_type)
{
    switch(nand_device_type & DEV_TYPE_BASIC_MASK) {
    default:
    case DEV_TYPE_BASIC_HYNIX:      // hynix device
    case DEV_TYPE_BASIC_MICRON:     // micron device
        REG16_WRITE(FC_REG_SEQ_STATUS_BYTE_CNTL1, 0x6078);  //0x8005B684
        REG16_WRITE(FC_REG_SEQ_STATUS_BYTE_CNTL2, 0xF2F1);  //0x8005B686
        REG16_WRITE(FC_REG_SEQ_STATUS_BYTE_CNTL3, 0x2160);  //0x8005B688
        REG16_WRITE(FC_REG_SEQ_CMD_PORT7, 0x0600);          //0x8005B690
        REG16_WRITE(FC_REG_SEQ_CMD_PORT8, 0x35E0);          //0x8005B692
        REG16_WRITE(FC_REG_SEQ_CMD_PORT9, 0x0032);          //0x8005B694
        REG16_WRITE(FC_REG_SEQ_CMD_PORT10, 0x8011);         //0x8005B696
        REG16_WRITE(FC_REG_SEQ_CMD_PORT11, 0xD185);         //0x8005B698
        break;
    case DEV_TYPE_BASIC_TOSHIBA:    // toshiba device
    case DEV_TYPE_BASIC_SAMSUNG:    // samsung device
        REG16_WRITE(FC_REG_SEQ_STATUS_BYTE_CNTL1, 0x6071);  //0x8005B684
        REG16_WRITE(FC_REG_SEQ_STATUS_BYTE_CNTL2, 0xF2F1);  //0x8005B686
        REG16_WRITE(FC_REG_SEQ_STATUS_BYTE_CNTL3, 0x2160);  //0x8005B688
        REG16_WRITE(FC_REG_SEQ_CMD_PORT7, 0x0560);          //0x8005B690
        REG16_WRITE(FC_REG_SEQ_CMD_PORT8, 0x35E0);          //0x8005B692
        REG16_WRITE(FC_REG_SEQ_CMD_PORT9, 0x0032);          //0x8005B694
        REG16_WRITE(FC_REG_SEQ_CMD_PORT10, 0x8111);         //0x8005B696
        REG16_WRITE(FC_REG_SEQ_CMD_PORT11, 0xD185);         //0x8005B698
        break;
    }
}



u32 FC_Platform_Get_FC_Clk(u32 timing_mode)
{
#if 1
	if ((timing_mode & ONFI_SYNC_ENABLE) == 0) 
	{
		switch(timing_mode & 0x07)
		{
			case 1:
				mCLKPWRinitFlashClock(0x551);
				return 160000000L;
				break;

			case 2:
				mCLKPWRinitFlashClock(0x452);
				return 100000000L;
				break;

			case 3:
				mCLKPWRinitFlashClock(0x452);
				return 100000000L;
				break;

			case 4:
				mCLKPWRinitFlashClock(0x352);
				return 133000000L;
				break;

			case 5:
				mCLKPWRinitFlashClock(0x142);
				return 250000000L;
				break;
				
			default:
				mCLKPWRinitFlashClock(0x352);
				return 133000000L;
				break;
				
		}
	}
	else
	{
		switch(timing_mode & 0x07)
		{
			case 0:
				mCLKPWRinitFlashClock(0x551);
				return 160000000L;
				break;
				
			case 1:
				mCLKPWRinitFlashClock(0x651);
				return 133000000L;
				break;

			case 2:
				mCLKPWRinitFlashClock(0x451);
				return 200000000L;
				break;

			case 3:
				mCLKPWRinitFlashClock(0x651);
				return 133000000L;
				break;

			case 4:
				mCLKPWRinitFlashClock(0x551);
				return 160000000L;
				break;

			case 5:
				mCLKPWRinitFlashClock(0x451);
				return 200000000L;
				break;
				
			default:
				mCLKPWRinitFlashClock(0x551);
				return 160000000L;
				break;
				
		}
	}
#else

	return 160000000L;
#endif
}

void FC_Clk_For_Timingmode(u32 timing_mode, u32 nand_device_type)
{
	nvhwcfg.fc_clk_mhz = FC_Platform_Get_FC_Clk(timing_mode)/1000000L;	
	nvhwcfg.fc_clk_freq_ps = 1000000L / nvhwcfg.fc_clk_mhz; // in pico-seconds
}

nand_t *  FC_Get_Installed_Nand (void) 
{
    if (0 == ((u8 *) (&nand_detected))[0]) 
    {
        return 0;
    }
    else 
    {
        return &nand_detected;
    }
}


void 
FC_Get_Dev_Rw_Timing_Ps(u32 timing_mode, u32 nand_dev_type, dev_rw_timing_t *pdev_rw_timing)
{

    if( nand_dev_type & DEV_TYPE_TOGGLE_MASK ) 
    {
        switch (timing_mode) 
	 {

        default:

        case 0x11:    //66Mbps
            pdev_rw_timing->t_rel = 13000;     // RE# low hold time in ps
            pdev_rw_timing->t_reh = 13000;    // RE# high hold time in ps
            pdev_rw_timing->t_wel = 11000;    // WE# low hold time in ps
            pdev_rw_timing->t_weh = 11000;    // WE# high hold time in ps
            pdev_rw_timing->t_rea = 30000;  // tRC read cycle ps
            break;

        case 0x12:    //80Mbps
            pdev_rw_timing->t_rel = 11000;    // RE# low hold time in ps
            pdev_rw_timing->t_reh = 11000;    // RE# high hold time in ps
            pdev_rw_timing->t_wel = 11000;    // WE# low hold time in ps
            pdev_rw_timing->t_weh = 11000;    // WE# high hold time in ps
            pdev_rw_timing->t_rea = 25000;  // tRC read cycle ps
            break;

        case 0x13:    //133Mbps
            pdev_rw_timing->t_rel =  6500;    // RE# low hold time in ps
            pdev_rw_timing->t_reh =  6500;    // RE# high hold time in ps
            pdev_rw_timing->t_wel = 11000;    // WE# low hold time in ps
            pdev_rw_timing->t_weh = 11000;    // WE# high hold time in ps
            pdev_rw_timing->t_rea = 15000;  // tRC read cycle ps
            break;

	case 0x14:    //166Mbps
            pdev_rw_timing->t_rel = 5500;    // RE# low hold time in ps
            pdev_rw_timing->t_reh = 5500;    // RE# high hold time in ps
            pdev_rw_timing->t_wel = 11000;    // WE# low hold time in ps
            pdev_rw_timing->t_weh = 11000;    // WE# high hold time in ps
            pdev_rw_timing->t_rea = 12500;  // tRC read cycle ps
            break;

      case 0x15:	//200Mbps
      		pdev_rw_timing->t_rel = 6500; // RE# low hold time in ps
      		pdev_rw_timing->t_reh = 6500; // RE# high hold time in ps
      		pdev_rw_timing->t_wel = 14000; // WE# low hold time in ps
      		pdev_rw_timing->t_weh = 14000; // WE# high hold time in ps
      		pdev_rw_timing->t_rea = 10000; // tRC read cycle ps
      		break;
        }
    }
    else 
    {
        switch (timing_mode & 0x7) 
	 {

        default:

        case 0:
            pdev_rw_timing->t_rel = 50000;   //70000;    // RE# low hold time in ps
            pdev_rw_timing->t_reh = 50000;   //30000;    // RE# high hold time in ps
            pdev_rw_timing->t_wel = 50000;   //70000;    // WE# low hold time in ps
            pdev_rw_timing->t_weh = 50000;   //30000;    // WE# high hold time in ps
            pdev_rw_timing->t_rea = 40000;   // RE# access time in ps
            break;

        case 1:
            pdev_rw_timing->t_rel = 25000;   //35000;    // RE# low hold time in ps
            pdev_rw_timing->t_reh = 25000;   //15000;    // RE# high hold time in ps
            pdev_rw_timing->t_wel = 25000;   //35000;    // WE# low hold time in ps
            pdev_rw_timing->t_weh = 25000;   //15000;    // WE# high hold time in ps
            pdev_rw_timing->t_rea = 30000;   // RE# access time in ps
            break;

        case 2:
            pdev_rw_timing->t_rel = 20000;   //20000;    // RE# low hold time in ps
            pdev_rw_timing->t_reh = 15000;   //15000;    // RE# high hold time in ps
            pdev_rw_timing->t_wel = 20000;   //20000;    // WE# low hold time in ps
            pdev_rw_timing->t_weh = 15000;   //15000;    // WE# high hold time in ps
            pdev_rw_timing->t_rea = 25000;   // RE# access time in ps
            break;

        case 3:
            pdev_rw_timing->t_rel = 20000;   //20000;    // RE# low hold time in ps
            pdev_rw_timing->t_reh = 10000;   //10000;    // RE# high hold time in ps
            pdev_rw_timing->t_wel = 20000;   //20000;    // WE# low hold time in ps
            pdev_rw_timing->t_weh = 10000;   //10000;    // WE# high hold time in ps
            pdev_rw_timing->t_rea = 20000;   // RE# access time in ps
            break;

        case 4:
            pdev_rw_timing->t_rel = 15000;   //15000;    // RE# low hold time in ps
            pdev_rw_timing->t_reh = 10000;   //10000;    // RE# high hold time in ps
            pdev_rw_timing->t_wel = 15000;   //15000;    // WE# low hold time in ps
            pdev_rw_timing->t_weh = 10000;   //10000;    // WE# high hold time in ps
            pdev_rw_timing->t_rea = 20000;   // RE# access time in ps
            break;

        case 5:
            pdev_rw_timing->t_rel = 10000;   //10000;    // RE# low hold time in ps
            pdev_rw_timing->t_reh = 10000;   //10000;    // RE# high hold time in ps
            pdev_rw_timing->t_wel = 10000;   //10000;    // WE# low hold time in ps
            pdev_rw_timing->t_weh = 10000;   //10000;    // WE# high hold time in ps
            pdev_rw_timing->t_rea = 20000;   // RE# access time in ps
            break;
        }
    }

}


u32 
FC_Get_Division_Result(u32 a, u32 b)
{
    u32 tmp, remain;

    tmp = a / b;
    remain = a % b;

    // if the remain is more than about 3% of 'b', increase by 1
    if (remain > (b >> 5)) {
        tmp++;
    }

    return tmp;

}


u32 
FC_Get_Halfclk_Cnts(u32 timing_mode)
{
    u32 halfclk_cnts;
    u32 tmp;

    switch (timing_mode) 
    {

    default:

    case 0:
        tmp = 100000;   //100ns for async mode 0
        break;

    case 1:
        tmp = 50000;    //50ns for async mode 1
        break;

    case 2:
        tmp = 35000;    //35ns for async mode 2
        break;

    case 3:
        tmp = 30000;    //30ns for async mode 3
        break;

    case 4:
        tmp = 25000;    //25ns for async mode 4
        break;

    case 5:
        tmp = 20000;    //20ns for async mode 5
        break;

    case 0x10:
        tmp = 50000;    //50ns for sync mode 0
        break;

    case 0x11:
        tmp = 30000;    //30ns for sync mode 1
        break;

    case 0x12:
        tmp = 20000;    //20ns for sync mode 2
        break;

    case 0x13:
        tmp = 15000;    //15ns for sync mode 3
        break;

    case 0x14:
        tmp = 12000;    //12ns for sync mode 4
        break;

    case 0x15:
        tmp = 10000;    //10ns for sync mode 5
        break;
    }

    halfclk_cnts = FC_Get_Division_Result(tmp >> 1, nvhwcfg.fc_clk_freq_ps);

    if (halfclk_cnts < 1) 
    {
        halfclk_cnts = 1;
    }

    if (halfclk_cnts > 8) 
    {
        halfclk_cnts = 8;
    }

    return halfclk_cnts;
}





void 
Fc_Cfg_For_T123456(u32 timing_mode, u32 nand_device_type, u32 tcad_ns, u32 trhw_ns, u32 tccs_ns)
{

    u16 tmp_u16 = 0, tmp_u16_1, t1, t2, t3, t4, t5, t6;
    u32 halfclk_cnts;
    u32 tmp_u32;
    dev_rw_timing_t dev_rw_timing;

    //Async mode:

    /*
        Asynchronous Mode Timing
        T1 * 1/FC_CLK >= tRP
            ---> T1 = (tRP * FC_CLK + 999) / 1000

        T2 * 1/FC_CLK >= tREH
            ---> T2 = (tREH * FC_CLK + 999) / 1000

        T3 * 1/FC_CLK >= tWP
            ---> T3 = (tWP * FC_CLK + 999) / 1000

        T4 * 1/FC_CLK >= tWH
            ---> T4 = (tWH * FC_CLK + 999) / 1000

        X + Y + tREA - 1/FC_CLK * T1 < Data Latch timing (T5, T6 and LT)
        X + Y = 9.25ns (*)
 */
    if ((timing_mode & ONFI_SYNC_ENABLE) == 0) 
    {
        FC_Get_Dev_Rw_Timing_Ps(timing_mode, nand_device_type, &dev_rw_timing);

        // set t1, t2
        t1 = (u8) FC_Get_Division_Result(
                (u32) dev_rw_timing.t_rel,
                nvhwcfg.fc_clk_freq_ps) - 1;
        t2 = (u8) FC_Get_Division_Result(
                (u32) dev_rw_timing.t_reh,
                nvhwcfg.fc_clk_freq_ps) - 1;
        t3 = (u8) FC_Get_Division_Result(
                (u32) dev_rw_timing.t_wel,
                nvhwcfg.fc_clk_freq_ps) - 1;
        t4 = (u8) FC_Get_Division_Result(
                (u32) dev_rw_timing.t_weh,
                nvhwcfg.fc_clk_freq_ps) - 1;

        if (t1 > 7) {
            t1 = 7;
        }

        if (t2 > 7) {
            t2 = 7;
        }

        if (t3 > 7) {
            t3 = 7;
        }

        if (t4 > 7) {
            t4 = 7;
        }
       //t1 = t2 = t3 = t4 = 7;

        // set t5
        //LT = 0  T5 is controlled by Flash I/F Timing Control1 Register
        //LT = 1  T5 is controlled by Flash I/F Timing Control2 Register
        //t5 = 2;    //latching time 3(T2=1T) for LT=0, or 7 for LT=1
        // For Async mode, t5 should be calculated from:
        // (X+Y)(9.25ns) + tREA(30ns) - 1/FC_CLK * T1 < Data Latch timing (T5, T6(0.6ns) and LT)
        // tREA: Rtypically 20-30ns, Data is valid tREA after the falling edge of RE
        if ((XplusYns + dev_rw_timing.t_rea) > (t1 + 1) * nvhwcfg.fc_clk_freq_ps) 
	 {
            t5 = (u8) FC_Get_Division_Result(
                    (u32)
                        (
                            (
                                XplusYns +
                                dev_rw_timing.t_rea -
                                (t1 + 1) *
                                nvhwcfg.fc_clk_freq_ps
                            ) * 2
                        ),
                    nvhwcfg.fc_clk_freq_ps);
        }
        else 
	 {
            t5 = 0;
        }

        if (t5 > 7) 
	 {
            t5 = 7;
        }

        

        //t5 = 6;    // fixed to 6
        // set t6
        t6 = 0;                 //delay 3, 3x0.6ns
        
        tmp_u16_1 = REG16_READ(FC_REG_xDIRECT_ACCESS_CNTL);
        if (t5 > 7) 
	 {
            
        }
        else if (t5 >= 4) 
	 {
            if (t2 == 0) 
	     {
                
            }

            t5 -= 4;

            tmp_u16 = 0xFF00;
            tmp_u16_1 |= BIT_13;
        }
        else 
	 {
            tmp_u16_1 &= ~BIT_13;
            tmp_u16 = 0x0000;
        }

        REG16_WRITE(FC_REG_xDIRECT_ACCESS_CNTL, tmp_u16_1); // LT for indirect flash latching time
        REG16_WRITE(FC_REG_SEQ_IF_TIMING_CFG_CH0, tmp_u16); // Ch0
        REG16_WRITE(FC_REG_SEQ_IF_TIMING_CFG_CH1, tmp_u16); // Ch1
        REG16_WRITE(FC_REG_SEQ_IF_TIMING_CFG_CH2, tmp_u16); // Ch2
        REG16_WRITE(FC_REG_SEQ_IF_TIMING_CFG_CH3, tmp_u16); // Ch3
        REG16_WRITE(FC_REG_SEQ_IF_TIMING_CFG_CH4, tmp_u16); // Ch4
        REG16_WRITE(FC_REG_SEQ_IF_TIMING_CFG_CH5, tmp_u16); // Ch5
        REG16_WRITE(FC_REG_SEQ_IF_TIMING_CFG_CH6, tmp_u16); // Ch6
        REG16_WRITE(FC_REG_SEQ_IF_TIMING_CFG_CH7, tmp_u16); // Ch7
        tmp_u16 = (t1 << 0)                                 //T1 for RE low pulse width
        | (t2 << 3)                                         //T2 for RE high pulse width
        | (t3 << 6)                                         //T3 for WE low pulse width
        | (t4 << 9)                                         //T4 for WE high pulse width
        | (t5 << 12)                                        //T5 for delay on clock
        | (t6 << 14);                                       //T6 for WE read data latching time

        //tmp_u16 = 0x6492;
        REG16_WRITE(FC_REG_TIMING_CNTL1, tmp_u16);          // Flash I/F Timing Control1 (sequencer mode, ASYNC)
        REG16_WRITE(FC_REG_TIMING_CNTL2, tmp_u16);          // Flash I/F Timing Control2 (sequencer mode, ASYNC)
        REG16_WRITE(FC_REG_TIMING_CNTL3, tmp_u16);          // Flash I/F Timing Control3 (indirect mode, ASYNC/JEDEC DDR)
    }
    else if ( nand_device_type & DEV_TYPE_TOGGLE_MASK ) 
    {
        FC_Get_Dev_Rw_Timing_Ps(timing_mode, nand_device_type, &dev_rw_timing);

        // set t1, t2
        t1 = (u8) FC_Get_Division_Result(
                (u32) dev_rw_timing.t_rel,
                nvhwcfg.fc_clk_freq_ps) - 1;
        t2 = (u8) FC_Get_Division_Result(
                (u32) dev_rw_timing.t_reh,
                nvhwcfg.fc_clk_freq_ps) - 1;
        t3 = (u8) FC_Get_Division_Result(
                (u32) dev_rw_timing.t_wel,
                nvhwcfg.fc_clk_freq_ps) - 1;
        t4 = (u8) FC_Get_Division_Result(
                (u32) dev_rw_timing.t_weh,
                nvhwcfg.fc_clk_freq_ps) - 1;

        if (t1 > 7) 
	 {
            t1 = 7;
        }

        if (t2 > 7) 
	 {
            t2 = 7;
        }

        if (t3 > 7) 
	 {
            t3 = 7;
        }

        if (t4 > 7) 
	 {
            t4 = 7;
        }
//t1 = t2 = t3 = t4 = 7;
        tmp_u16 = (t1 << 0)                                 //T1 for RE low pulse width
        | (t2 << 3)                                         //T2 for RE high pulse width
        | (t3 << 6)                                         //T3 for WE low pulse width
        | (t4 << 9);                                        //T4 for WE high pulse width

        REG16_WRITE(FC_REG_TIMING_CNTL3, tmp_u16);          // Flash I/F Timing Control3 (indirect mode, SYNC/JEDEC DDR)
        REG16_WRITE(FC_REG_TIMING_CNTL4, tmp_u16);          // Flash I/F Timing Control4 (sequencer mode, SYNC/JEDEC DDR)
        
        //tmp_u16 = 0x3333;    //default value
        tmp_u16 = (7 << 12) + (15 << 8) + (7 << 4) + 15;
        REG16_WRITE(FC_REG_TIMING_CNTL6, tmp_u16);          // Flash I/F Timing Control6 (indirect/sequencer mode, SYNC/JEDEC DDR)
    }
    else 
    {

        //Sync mode:
        // for source synchronous mode, t3, t4, t5 are defined differently
        // T3 for tCAD parameter, cmd, adr, data delay
        // T4 for tRHW parameter, RE# high to WE# low
        // T5 for tCCS parameter, change column setup to data in/out or next command
        // set t1, t2
        halfclk_cnts = FC_Get_Halfclk_Cnts(timing_mode);       //set CTL4 using sync timing
        t1 = t2 = halfclk_cnts - 1;
        if (t1 > 7) 
	 {
            t1 = 7;
        }

        if (t2 > 7) 
	 {
            t2 = 7;
        }

        tmp_u32 = FC_Get_Division_Result(tcad_ns * 1000, nvhwcfg.fc_clk_freq_ps);
        t3 = FC_Get_Division_Result(tmp_u32, (t1 + 1) << 1);
        if (t3 < 1) 
	 {
            t3 = 1;
        }

        if (t3 > 8) 
	 {
            t3 = 8;
        }

        t3--;

        tmp_u32 = FC_Get_Division_Result(trhw_ns * 1000, nvhwcfg.fc_clk_freq_ps);
        t4 = FC_Get_Division_Result(tmp_u32, (t1 + 1) << 1);
        t4 = t4 - (t3 + 1);
        if (t4 < 1) 
	 {
            t4 = 1;
        }

        if (t4 > 8) 
	 {
            t4 = 8;
        }

        t4--;

        tmp_u32 = FC_Get_Division_Result(tccs_ns * 1000, nvhwcfg.fc_clk_freq_ps);
        t5 = FC_Get_Division_Result(tmp_u32, ((t1 + 1) << 1) * (t3 + 1));
        if (t5 < 1) 
	 {
            t5 = 1;
        }

        if (t5 > 16) 
	 {
            t5 = 16;
        }

        t5--;

        tmp_u16 = (t1 << 0)                                 //T1 for clock low pulse width
        | (t2 << 3)                                         //T2 for clock high pulse width
        | (t3 << 6)                                         //T3 for tCAD parameter, cmd, adr, data delay
        | (t4 << 9)                                         //T4 for tRHW parameter, RE# high to WE# low
        | (t5 << 12);                                       //T5 for tCCS parameter, change column setup to data in/out or next command
        REG16_WRITE(FC_REG_TIMING_CNTL4, tmp_u16);          // Flash I/F Timing Control4 (sequencer mode, SYNC/JEDEC DDR)
    }

}



void FC_Cfg_For_T7(u32 timing_mode)
{
    if((timing_mode&0x07) == 4)
	{
	  REG16_WRITE(FC_REG_DATA_LATCH_TIMING_CNTL_CH01, 0x0d0a);
	  REG16_WRITE(FC_REG_DATA_LATCH_TIMING_CNTL_CH23, 0x0a0b);
	  REG16_WRITE(FC_REG_DATA_LATCH_TIMING_CNTL_CH45, 0x0d0b);
	  REG16_WRITE(FC_REG_DATA_LATCH_TIMING_CNTL_CH67, 0x0a0d);	
	}
	else
	{
	  REG16_WRITE(FC_REG_DATA_LATCH_TIMING_CNTL_CH01, 0x0907);
	  REG16_WRITE(FC_REG_DATA_LATCH_TIMING_CNTL_CH23, 0x0707);
	  REG16_WRITE(FC_REG_DATA_LATCH_TIMING_CNTL_CH45, 0x0908);
	  REG16_WRITE(FC_REG_DATA_LATCH_TIMING_CNTL_CH67, 0x0609);
	}
}

u16 
FC_Get_Seq_Timing(u32 dly_us, u32 div_shift_0, u32 div_limit, u32 cnt_limit)
{
    s32 div, cnt, max_cnt;
    /*Calculate delay count*/
    max_cnt = (dly_us * nvhwcfg.fc_clk_mhz) >> div_shift_0;
    for (div = 0; div < div_limit; div++) 
    {
        	max_cnt >>= div;
        	for (cnt = cnt_limit; cnt >= 0; cnt--) 
	       {
            		if (cnt <= max_cnt) 
			{
                /*Condition meets*/
                		if (cnt > 0) 
				{
                    			cnt--;
                		}
                		return (u16)((div << 14) | (cnt << 8) | cnt);
            		}
        	}
    }
    
    return (u16)(((div_limit - 1) << 14) | ((cnt_limit - 1)<< 8) | (cnt_limit - 1));
} /*End of get_seq_timing*/

u16 
FC_Get_Seq_Timing_Cnt5(
    u32 rd_rst_poll_us,
    u32 ers_wrt_poll_us,
    u32 div_shift_0,
    u32 div_limit,
    u32 cnt1_limit,
    u32 cnt2_limit)
{
    s32 div, max_cnt1, max_cnt2, cnt1, cnt2;
    /*Calculate delay count*/
    max_cnt1 = (u32) (rd_rst_poll_us * nvhwcfg.fc_clk_mhz) >> div_shift_0;
    max_cnt2 = (u32) (ers_wrt_poll_us * nvhwcfg.fc_clk_mhz) >> div_shift_0;

    for (div = 0; div < div_limit; div++) 
    {
        max_cnt1 >>= div;
        max_cnt2 >>= div;
        for (cnt1 = cnt1_limit; cnt1 >= 0; cnt1--) 
	 {
            if (cnt1 <= max_cnt1) 
	     {
                /*Condition meets*/
                if (cnt1 > 0) 
		  {
                    cnt1--;
                }
                break;
            }
        }
        for (cnt2 = cnt2_limit; cnt2 >= 0; cnt2--) 
	 {
            if (cnt2 <= max_cnt2) 
	     {
                /*Condition meets*/
                if (cnt2 > 0) 
		  {
                    cnt2--;
                }
                break;
            }
        }
        if ((cnt1 <= max_cnt1) && (cnt2 <= max_cnt2)) 
	 {
            /*Condition meets*/
            return  (u16)((div << 14) | (cnt1 << 8) | cnt2);
        }
    }

    if (div == div_limit) 
    {        
        div  = div_limit - 1;
        cnt1 = cnt1_limit - 1;
        cnt2 = cnt2_limit - 1;
    }

    return  (u16)((div << 14) | (cnt1 << 8) | cnt2);
}

void FC_Cfg_For_Seq_Timing(
    u32 rd_dly_us,
    u32 wrt_dly_us,
    u32 ers_dly_us,
    u32 rst_dly_us,
    u32 rd_rst_poll_us,
    u32 ers_wrt_poll_us,
    u32 mp_dly_us)
{

// all delay is multiplied by 3/4 to speed up operation which is faster than averaged delay
    	rd_dly_us  -= rd_dly_us  >> 2;            // rd_dly_us = rd_dly_us*3/4
    	wrt_dly_us -= wrt_dly_us >> 2;            // wrt_dly_us = wrt_dly_us*3/4
    	ers_dly_us -= ers_dly_us >> 2;            // ers_dly_us = ers_dly_us*3/4
    	rst_dly_us -= rst_dly_us >> 2;            // rst_dly_us = rst_dly_us*3/4

    // Change status polling wait time (initial wait & interval)
    // set read delay:
    	REG16_WRITE(FC_REG_SEQ_IF_TIMING_CNTL1, FC_Get_Seq_Timing(rd_dly_us, 6, 4, 0x40));    // default: 0x8A25, 0x8d25 For READ

    //REG16_WRITE(FC_REG_SEQ_IF_TIMING_CNTL1, 0x8A25);  // default: 0x8A25, 0x8d25 For READ
    // set write delay:
    	REG16_WRITE(
        FC_REG_SEQ_IF_TIMING_CNTL2,
        FC_Get_Seq_Timing(wrt_dly_us, 10, 4, 0x40));                                      // default: 0x4C42, 0x5042 For PROG

    //REG16_WRITE(FC_REG_SEQ_IF_TIMING_CNTL2, 0x4C42);  // default: 0x4C42, 0x5042 For PROG
    // set erase delay:
    	REG16_WRITE(
        FC_REG_SEQ_IF_TIMING_CNTL3,
        FC_Get_Seq_Timing(ers_dly_us, 11, 4, 0x40));                                      // For erase, 0x0103

    //REG16_WRITE(FC_REG_SEQ_IF_TIMING_CNTL3, 0x0103);  // For erase, 0x0103
    // set reset delay:
    	REG16_WRITE(
        FC_REG_SEQ_IF_TIMING_CNTL4,
        FC_Get_Seq_Timing(rst_dly_us, 5, 4, 0x40));                                       /* reset timing 0x8D0D */

    //REG16_WRITE(FC_REG_SEQ_IF_TIMING_CNTL4, 0x8D0D);  /* reset timing 0x8D0D */
    // set polling delay:
    	REG16_WRITE(
        FC_REG_SEQ_IF_TIMING_CNTL5,
        FC_Get_Seq_Timing_Cnt5(rd_rst_poll_us, ers_wrt_poll_us, 5, 4, 0x10, 0x80));       /* status polling interval 0x0000 */

    //REG16_WRITE(FC_REG_SEQ_IF_TIMING_CNTL5, 0x423B);  /* status polling interval 0x0000 */
    // set multiplane read status delay:
    	REG16_WRITE(FC_REG_SEQ_IF_TIMING_CNTL6, FC_Get_Seq_Timing(mp_dly_us, 5, 4, 0x40));    /* between 2 planes tDBSY  */
    //REG16_WRITE(FC_REG_SEQ_IF_TIMING_CNTL6, 0x4d0d);  /* between 2 planes tDBSY 0x4DOD */
}


void FC_Cfg_For_Timingmode(u32 timing_mode, u32 nand_device_type)
{
	nand_t *nand;
    
    	nand = FC_Get_Installed_Nand();

	#ifndef FPGA_ENABLE

    	if(nand == NULL) 
	{    // if nand has not been detected yet, just set to default values
        //tcad_ns = 25ns, trhw_ns = 100ns, tccs_ns = 200ns only for source synchronous mode, other mode DON'T care
        	Fc_Cfg_For_T123456(timing_mode, nand_device_type, 25, 100, 200);  

        //rd_dly_us, wrt_dly_us, ers_dly_us, rst_dly_us, rd_rst_poll_us, ers_wrt_poll_us, mp_dly_us
        	FC_Cfg_For_Seq_Timing(25, 160, 1000, 100, 5, 5, 2);    //default setting
    	}
    	else 
	{
        //tcad_ns, trhw_ns, tccs_ns from nand_t only for source synchronous mode, other mode DON'T care
        	Fc_Cfg_For_T123456(timing_mode, nand_device_type, nand->tcad_ns, nand->trhw_ns, nand->tccs_ns);  

        //rd_dly_us, wrt_dly_us, ers_dly_us, rst_dly_us, rd_rst_poll_us, ers_wrt_poll_us, mp_dly_us
        	FC_Cfg_For_Seq_Timing(nand->rd_dly_us, nand->wrt_dly_us, nand->ers_dly_us, nand->rst_dly_us, 5, 5, 2);    //for Micron MT29F32G08A
    	}
    
    	FC_Cfg_For_T7(timing_mode);
	if((timing_mode&0x07) == 4)
  		REG16_WRITE(FC_REG_TIMING_CNTL6, 0x3331); //t8
  	else
		REG16_WRITE(FC_REG_TIMING_CNTL6, 0x3332); //t8

	#else

    	REG16_WRITE(FC_REG_TIMING_CNTL1, 0x6249);           // Flash I/F Timing Control1 (sequencer mode, ASYNC)
    	REG16_WRITE(FC_REG_TIMING_CNTL2, 0x6249);           // Flash I/F Timing Control2 (sequencer mode, ASYNC)
    	REG16_WRITE(FC_REG_TIMING_CNTL3, 0x6249);           // Flash I/F Timing Control3 (indirect mode, ASYNC/JEDEC DDR)

    	//REG16_WRITE(FC_REG_TIMING_CNTL4,0x6249);        // Flash I/F Timing Control4 (sequencer mode, SYNC/JEDEC DDR)
    	REG16_WRITE(FC_REG_TIMING_CNTL4, 0x6240);           // Flash I/F Timing Control4 (sequencer mode, SYNC/JEDEC DDR)
    	FC_Cfg_For_T7(INITIAL_TIMING_MODE_SEL);

    	REG16_WRITE(FC_REG_SEQ_IF_TIMING_CFG_CH0, 0x0000);  // Ch0 LT = 0  T5 is controlled by Flash I/F Timing Control1 Register
    	REG16_WRITE(FC_REG_SEQ_IF_TIMING_CFG_CH1, 0x0000);  // Ch1 LT = 0
    	REG16_WRITE(FC_REG_SEQ_IF_TIMING_CFG_CH2, 0x0000);  // Ch2 LT = 0
    	REG16_WRITE(FC_REG_SEQ_IF_TIMING_CFG_CH3, 0x0000);  // Ch3 LT = 0

    	if (nand == NULL)
	{
        // Change status polling wait time (initial wait & interval)
        	REG16_WRITE(FC_REG_SEQ_IF_TIMING_CNTL1, 0x8a25);    // default: 0x8d25 For READ
        	REG16_WRITE(FC_REG_SEQ_IF_TIMING_CNTL2, 0x4c42);    // default: 0x5042 For PROG
        	REG16_WRITE(FC_REG_SEQ_IF_TIMING_CNTL3, 0x0103);    // For erase
    	} 
	else 
	{
        //rd_dly_us, wrt_dly_us, ers_dly_us, rst_dly_us, rd_rst_poll_us, ers_wrt_poll_us, mp_dly_us
        	FC_Cfg_For_Seq_Timing(nand->rd_dly_us, nand->wrt_dly_us, nand->ers_dly_us, nand->rst_dly_us, 5, 5, 2);
    	} /*End of if((nand == NULL) || (nand_device_type & DEV_TYPE_TOGGLE_MASK))*/       
	#endif    

}

#if 1
void FC_Set_For_Timingmode(u32 timing_mode, u32 nand_device_type)
{
        FC_Clk_For_Timingmode(timing_mode, nand_device_type);
        FC_Cfg_For_Timingmode(timing_mode, nand_device_type);
}
#else
#define SETUP_T(T6,T5,T4,T3,T2,T1)  ( ((T6&0x3)<<14) | ((T5&0x3)<<12) | ((T4&0x7)<<9) | ((T3&0x7)<<6)| ((T2&0x7)<<3) | ((T1&0x7)<<0) )
#define SETUP_T_SYN(T5,T4,T3,T2,T1)  ( ((T5&0xF)<<12) | ((T4&0x7)<<9) | ((T3&0x7)<<6)| ((T2&0x7)<<3) | ((T1&0x7)<<0) )
#define SETUP_T_JEDEC(T4,T3,T2,T1)   ( (0x7 << 12) | ((T4&0x7)<<9) | ((T3&0x7)<<6)| ((T2&0x7)<<3) | ((T1&0x7)<<0) )
#define SETUP_LT(T7)                 ( ((T7&0x3F)<<8) | (T7&0x3F) ) 
void mNvFCsequencerSetLT0(void)
{
	 REG16_CLEAR_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH0, 0xff00); // Ch0
        REG16_CLEAR_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH1, 0xff00); // Ch1
        REG16_CLEAR_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH2, 0xff00); // Ch2
        REG16_CLEAR_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH3, 0xff00); // Ch3
        REG16_CLEAR_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH4, 0xff00); // Ch4
        REG16_CLEAR_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH5, 0xff00); // Ch5
        REG16_CLEAR_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH6, 0xff00); // Ch6
        REG16_CLEAR_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH7, 0xff00); // Ch7
}

void mNvFCsequencerSetLT1(void)
{
	 REG16_SET_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH0, 0xff00); // Ch0
        REG16_SET_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH1, 0xff00); // Ch1
        REG16_SET_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH2, 0xff00); // Ch2
        REG16_SET_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH3, 0xff00); // Ch3
        REG16_SET_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH4, 0xff00); // Ch4
        REG16_SET_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH5, 0xff00); // Ch5
        REG16_SET_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH6, 0xff00); // Ch6
        REG16_SET_BITS(FC_REG_SEQ_IF_TIMING_CFG_CH7, 0xff00); // Ch7
}

void NvOnfiSetupTiming(mUINT_16 T, mUINT_16 T7, mUINT_16 flashClk)
{
    mUINT_NATIVE   i;
    
    mCLKPWRinitFlashClock(flashClk);     // setup flash clk
    REG16_WRITE(FC_REG_TIMING_CNTL4, T);           // setup T5 ~ T1
            
    REG16_WRITE(FC_REG_DATA_LATCH_TIMING_CNTL_CH01, T7);   // Ch0&1  T7 for timing mode
    REG16_WRITE(FC_REG_DATA_LATCH_TIMING_CNTL_CH23, T7);
    REG16_WRITE(FC_REG_DATA_LATCH_TIMING_CNTL_CH45, T7);
    REG16_WRITE(FC_REG_DATA_LATCH_TIMING_CNTL_CH67, T7);
} 

void FC_Set_For_Timingmode(u32 timing_mode, u32 nand_device_type)
{
	nand_t *nand;
    
    	nand = FC_Get_Installed_Nand();
	FC_Clk_For_Timingmode(timing_mode, nand_device_type);
		
	if ((timing_mode & ONFI_SYNC_ENABLE) == 0) 
	{
		switch (timing_mode & 0x07)
        	{
	            case 1:
	                mCLKPWRinitFlashClock(0x551);			  
			  REG16_WRITE(FC_REG_TIMING_CNTL1, SETUP_T(1,3,1,1,1,1));
			  mNvFCsequencerSetLT1();
	                break;
	            case 2:
	                mCLKPWRinitFlashClock(0x452);			  
			  REG16_WRITE(FC_REG_TIMING_CNTL1, SETUP_T(0,2,0,1,0,1));
			  mNvFCsequencerSetLT0();
	                break;
	            case 3:
	                mCLKPWRinitFlashClock(0x452);			  
			  REG16_WRITE(FC_REG_TIMING_CNTL1, SETUP_T(1,3,0,0,0,0));
			  mNvFCsequencerSetLT0();
	                break;
	            case 4:
	                mCLKPWRinitFlashClock(0x352);			  
			  REG16_WRITE(FC_REG_TIMING_CNTL1, SETUP_T(1,3,1,1,1,1));
			  mNvFCsequencerSetLT1();
	                break;
	            case 5:
	                mCLKPWRinitFlashClock(0x142);			  
			  REG16_WRITE(FC_REG_TIMING_CNTL1, SETUP_T(1,3,2,3,2,3));
			  mNvFCsequencerSetLT1();
	                break;            
	            default:
	                break;  // just use default.                
        	}
	}
	else
	{
		switch (timing_mode & 0x07)
	        {
	            case 0x0:
	                // FC_clk = 160MHz, T1 ~ T7 = 3,3,1,0,2,0x22
	                NvOnfiSetupTiming(SETUP_T_SYN(2,0,1,3,3),SETUP_LT(0x22), 0x551); 
	            break;
	            case 0x1:
	                // FC_clk = 133MHz, T1 ~ T7 = 1,1,1,0,3,0x10
	                NvOnfiSetupTiming(SETUP_T_SYN(3,0,1,1,1),SETUP_LT(0x10), 0x651); 
	            break;
	            case 0x2:
	                // FC_clk = 200MHz, T1 ~ T7 = 1,1,2,1,3,0x10
	                NvOnfiSetupTiming(SETUP_T_SYN(3,1,2,1,1),SETUP_LT(0x10), 0x451);         
	            break;
	            case 0x3:
	                // FC_clk = 133MHz, T1 ~ T7 = 0,0,2,1,4,0x9
	                NvOnfiSetupTiming(SETUP_T_SYN(4,1,2,0,0),SETUP_LT(9), 0x651);
	            break;
	            case 0x4:
	                // FC_clk = 160MHz, T1 ~ T7 = 0,0,1,2,4,0x9
	                    NvOnfiSetupTiming(SETUP_T_SYN(7,5,1,0,0),SETUP_LT(0x0C), 0x551);        
	                    REG16_WRITE(FC_REG_TIMING_CNTL6, 0x3332);//t8
	            break;
	            case 0x5:
	                // FC_clk = 200MHz, T1 ~ T7 = 0,0,2,6,6,0x9
	                NvOnfiSetupTiming(SETUP_T_SYN(6,6,2,0,0),SETUP_LT(9), 0x451); 
	            break;           
	        }
	}

	FC_Cfg_For_Seq_Timing(nand->rd_dly_us, nand->wrt_dly_us, nand->ers_dly_us, nand->rst_dly_us, 5, 5, 2); 
}
#endif


void FC_Reset(void)  // reset flash controller to async mode
{
    u16 tmp;

    FC_Wait_Seq_Idle();
    tmp =REG16_READ(FC_REG_IF_CFG);
    /*Enable Auto NFIF power down*/
    tmp |= FC_IF_RESET | FC_PD_EN;
    REG16_WRITE(FC_REG_IF_CFG, tmp);
    tmp &= ~FC_IF_RESET;
    REG16_WRITE(FC_REG_IF_CFG, tmp);
    DelayUS(FC_DLY_US);
}

void 
FC_Set_Access_Mode(u32 mode)
{
    u16 tmp;

    FC_Wait_Seq_Idle();
    tmp = REG16_READ(FC_REG_IF_CFG);
    tmp &= ~FC_FLAMODE_MASK;
    tmp |= (u16) mode;
    REG16_WRITE(FC_REG_IF_CFG, tmp);

    tmp = REG16_READ(FC_REG_DIRECT_ACCESS_CNTL_PORT1);
    if (mode == FC_ACCESS_MODE_SEQ) {
        tmp |= (u16)FC_DIRECT_WP;
    }
    else {
        tmp &= ~FC_DIRECT_WP;
    }
    REG16_WRITE(FC_REG_DIRECT_ACCESS_CNTL_PORT1, tmp);

    DelayUS(FC_DLY_US);
}


void FC_Set_Indirect_Mode()
{
	FC_Reset(); //NAND Flash interface logic reset
	FC_Set_Flash_Type_H(0);
	FC_Set_Flash_Type_L(0);
	FC_Set_Device_Seqport(0);
	FC_Set_For_Timingmode(0,0);
	FC_Set_Access_Mode(FC_ACCESS_MODE_INDIRECT);
}

void
FC_Indirect_Set_Access_Device(u32 ch, u32 dev)
{
    u16 tmp = REG16_READ(FC_REG_xDIRECT_ACCESS_CNTL);
    tmp &= ~FC_xDIRECT_CHDEV_MASK;
    tmp |=
        (
            (((u16) ch) << FC_xDIRECT_CH_BIT_OFF) |
            (((u16) dev) << FC_xDIRECT_DEV_BIT_OFF)
        );
    REG16_WRITE(FC_REG_xDIRECT_ACCESS_CNTL, tmp);
}

u32
FC_Double_Data_Xfer_Eligibility(void)
{
    u16 tmp;
    
    tmp = REG16_READ(FC_REG_IF_CFG);
    
    if( (tmp & FC_NFIF_JDBC_ONFI_SYNC) ) {    //ONFI sync mode or toggle mode
        return 1;
    }
    else 
    {
        return 0;
    }

}

void
FC_Indirect_Fifo_Reset(void)
{
    u16 tmp = REG16_READ(FC_REG_INDIRECT_ACCESS_CFG);

    tmp |= FC_INDIRECT_FIFO_RESET;
    REG16_WRITE(FC_REG_INDIRECT_ACCESS_CFG, tmp);

    tmp &= ~FC_INDIRECT_FIFO_RESET;
    REG16_WRITE(FC_REG_INDIRECT_ACCESS_CFG, tmp);
}

void
FC_Indirect_Set_Xfer_Cnt(u32 cnt)
{
    REG16_WRITE(FC_REG_INDIRECT_ACCESS_XFER_CNT, (u16) cnt);
}

void 
FC_Indirect_Prepare_Cmd(
    u8 *cmd,
    u32 cmd_sz,
    u32 data_sz,
    u32 is_out,
    u32 double_data_xfer_en)
{
    union
    {
        u8 b[8];                                // 8 byte in maximum
        u16 w[4];
        u32 d[2];
    } u;

    u32 i;
    u16 tmp_u16;

    u.d[1] = u.d[0] = 0;

    for (i = 0; i < cmd_sz; i++) 
    {
        u.b[i] = *cmd++;
    }

    REG16_WRITE(FC_REG_INDIRECT_ACCESS_CMD_PORT1, u.w[0]);
    REG16_WRITE(FC_REG_INDIRECT_ACCESS_CMD_PORT2, u.w[1]);
    REG16_WRITE(FC_REG_INDIRECT_ACCESS_CMD_PORT3, u.w[2]);
    REG16_WRITE(FC_REG_INDIRECT_ACCESS_CMD_PORT4, u.w[3]);

    tmp_u16 = REG16_READ(FC_REG_INDIRECT_ACCESS_CFG);
    tmp_u16 |= FC_INDIRECT_OUT;
    REG16_WRITE(FC_REG_INDIRECT_ACCESS_CFG, tmp_u16);

    FC_Indirect_Fifo_Reset();

    if (double_data_xfer_en) 
    {
        FC_Indirect_Set_Xfer_Cnt(data_sz << 1);
    }
    else 
    {
        FC_Indirect_Set_Xfer_Cnt(data_sz);
    }
}

void
FC_Indirect_Execute(u32 v)
{
    REG16_WRITE(FC_REG_INDIRECT_ACCESS_CFG, (u16) v);
}

void
FC_Indirect_Dummy_Rbb_Set(void)
{
    REG16_SET_BITS(FC_REG_INDIRECT_ACCESS_CFG, FC_INDIRECT_DUMMY_RBB);
}

int
FC_Indirect_Wait_For_Fifo_Ready(void)
{
    u16 tmp;
    u32 cnt = 0;

    while(1) 
    {
        tmp = REG16_READ(FC_REG_INDIRECT_ACCESS_CFG);
        if (tmp & FC_INDIRECT_FIFO_STATUS) 
	 {
            break;
        }
        cnt++;
        if (cnt > FC_INDIRECT_TIME_OUT_COUNT) {
            return -1;
        }
        DelayUS(1);
    }

    return 0;
}

void
FC_Indirect_Write_Data_Port(u32 data)
{
    REG32_WRITE(FC_REG_INDIRECT_ACCESS_DATA_PORT1, data);
}

int 
FC_Indirect_Push_Data(void *_data, u32 data_sz, u32 double_data_xfer_en)
{
    u16 *data16 = (u16 *) _data;
    u32 *data = (u32 *) _data, tmp_u32;
    int err = 0;

    if (double_data_xfer_en) 
    {
        data_sz = (data_sz + sizeof(u16) - 1) >> 1; // multiple of u16
        while (data_sz--) 
	 {
            err = FC_Indirect_Wait_For_Fifo_Ready();
            if (err) 
	     {
                return err;
            }

            tmp_u32 = (*data16) & 0xff00;
            tmp_u32 <<= 8;
            tmp_u32 += (*data16) & 0x00ff;
            tmp_u32 += (tmp_u32 << 8);          //duplicate each bytes for SQRA mode
            FC_Indirect_Write_Data_Port(tmp_u32);
            data16++;
        }
    }
    else 
    {
        data_sz = (data_sz + sizeof(u32) - 1) >> 2; // multiple of u32
        while (data_sz--) {
            err = FC_Indirect_Wait_For_Fifo_Ready();
            if (err) {
                return err;
            }

            FC_Indirect_Write_Data_Port(*data);
            data++;
        }
    }

    return err;

}

int
FC_Indirect_Wait_For_Op_Done(void)
{
    u16 tmp;
    u32 cnt = 0;

    while(1) 
    {
        tmp = REG16_READ(FC_REG_INDIRECT_ACCESS_CFG);
        if (!(tmp & FC_INDIRECT_ACCESS_START)) 
	 {
            break;    
        }
        cnt++;
        if (cnt > FC_INDIRECT_TIME_OUT_COUNT) 
	 {
            return -1;
        }
        DelayUS(1);
    } 

    return 0;
}

u32
FC_Indirect_Read_Data_Port(void)
{
    return REG32_READ(FC_REG_INDIRECT_ACCESS_DATA_PORT1);
}

int 
FC_Indirect_Drain_Data(void *_data, u32 data_sz, u32 double_data_xfer_en)
{
    u32 tmp;
    int err = 0;
    u32 i;
    u8 *data = (u8 *) _data;

    while (data_sz) 
    {
        err = FC_Indirect_Wait_For_Fifo_Ready();
        if (err) 
	 {
            return err;
        }

        tmp = FC_Indirect_Read_Data_Port();
        for (i = 0; i < 4 && data_sz; i++) 
	 {
            *data++ = (u8) tmp;
            if (double_data_xfer_en) 
	     {

                // double_data_xfer_en: drain 2 times faster
                tmp >>= 16;
                i++;
            }
            else 
	     {
                tmp >>= 8;
            }

            data_sz--;
        }
    }

    return err;

}



int 
FC_Indirect_Execute_Cmd(
    u8 *cmd,
    u32 cmd_sz,
    void *data,
    u32 data_sz,
    u32 is_out)
{
    u32 double_data_xfer_en, dummy_rbb_ctrl_en;
    u32 tmp;
    int err = 0;

    if (*cmd == mFC_CMD_ONFI_GET_FEATURES
    ||  *cmd == mFC_CMD_READ_FLASH_ID
    ||  *cmd == mFC_CMD_READ_STATUS) 
    {

        // for get feature, drain data is different at sqra mode
        dummy_rbb_ctrl_en = 1;
    }
    else 
    {
        dummy_rbb_ctrl_en = 0;
    }

    double_data_xfer_en = FC_Double_Data_Xfer_Eligibility();

    FC_Indirect_Prepare_Cmd(cmd, cmd_sz, data_sz, is_out, double_data_xfer_en);

    tmp = (cmd_sz - 1) |
        (is_out ? FC_INDIRECT_OUT : 0) |
        FC_INDIRECT_ACCESS_START |
        (dummy_rbb_ctrl_en ? 0 : FC_INDIRECT_DUMMY_RBB);
    FC_Indirect_Execute(tmp);

    if (dummy_rbb_ctrl_en) 
    {
        DelayUS(100);   // delay 1 us to meet tFEAT/tWHR for get feature, read ID and so on
        FC_Indirect_Dummy_Rbb_Set();
    }

    if (is_out && data_sz) 
    {
        err = FC_Indirect_Push_Data(data, data_sz, double_data_xfer_en);
        if (err) 
	 {
            return err;
        }
    }

    err = FC_Indirect_Wait_For_Op_Done();
    if (err) 
    {
        return err;
    }

    if (!is_out && data_sz) 
    {
        err = FC_Indirect_Drain_Data(data, data_sz, double_data_xfer_en);
    }

    return err;
}

int 
FC_Indirect_Execute_Read_Status(u32 *val)
{
    int err;
    u8 cmd[] = { mFC_CMD_READ_STATUS };
    u8 status;

    err = FC_Indirect_Execute_Cmd(cmd, sizeof(cmd), &status, 1, 0);

    *val = (u32) status;
    
    return err;
}

int 
FC_Indirect_Wait_Device_Status(u32 delay_us)
{
    int err = 0;
    u32 status;
    u32 cnt = 0;

    while(1) 
    {
        err = FC_Indirect_Execute_Read_Status(&status);
        if (status & mFC_FLASH_STATUS_READY) 
	 {
            break;
        }
        
        if(err) 
	 {    //if failed to execute the read status command, return here.
            break;
        }
        
        cnt++;
        if (cnt > delay_us) 
	 {

            err = -1;
            break;
        }
        DelayUS(1);
    }

    return err;

}


int
FC_Indirect_Wait_Device_Ready(u32 ch, u32 dev, u32 delay_us)
{
    FC_Indirect_Set_Access_Device(ch, dev);
    return FC_Indirect_Wait_Device_Status(delay_us);
}


int 
FC_Indirect_Reset_All_Devices(u32 channum, u32 devnum, u32 is_sync)
{
    u8 cmd[] = { mFC_CMD_RESET_FLASH };
    u32 ch, dev;
    int err = 0;

    if (is_sync) 
    {
        cmd[0] = mFC_CMD_SYNC_RESET_FLASH;
    }
    else 
    {
        cmd[0] = mFC_CMD_RESET_FLASH;
    }

    // submit the reset command to all devices first
    for (ch = 0; ch < channum; ch++) 
    {
        for (dev = 0; dev < devnum; dev++) 
	 {
            FC_Indirect_Set_Access_Device(0, 0);
            err |= FC_Indirect_Execute_Cmd(cmd, sizeof(cmd), 0, 0, 1);
            // bypass error case. Because during reset, even if some device is not existed
            // we can not quit immediately, and should continue to detect further
            /*
            if (err) {
                return err;
            }
            */
            DelayUS(100);             // 100 delay for device reset ready

            err |= FC_Indirect_Wait_Device_Ready(0, 0, FC_INDIRECT_RESET_TIME_OUT_US);
            // bypass error case. Because during reset, even if some device is not existed
            // we can not quit immediately, and should continue to detect further
            /*
            if (err) {
                return err;
            }
            */
        }
    }
    
    return err;

}

void
FC_Set_Sqra_Mode(void)
{

    FC_Set_Access_Mode(FC_ACCESS_MODE_SEQ);

    REG16_SET_BITS(FC_REG_IF_CFG, FC_CLK_PD_EN);        // software workaround if SW_WORKAROUND_REG_ACCESS not defined
    FC_Wait_Seq_Idle();

    /*Enable EF_FIFO memory AUTO power down*/
    REG16_SET_BITS(FC_REG_SEQ_CNTL2, FC_SQRA_EN | FC_SMAPD_EN);

    DelayUS(FC_DLY_US);

}

void 
FC_Set_Indirect_Sqra_Mode(u8 timing_mode, u8 nand_device_type)
{

    FC_Reset(); //NAND Flash interface logic reset

    FC_Set_Flash_Type_H(timing_mode);
    FC_Set_Flash_Type_L(nand_device_type);

    FC_Set_Device_Seqport(nand_device_type);
    FC_Set_For_Timingmode(timing_mode, nand_device_type);

    if ((timing_mode & ONFI_SYNC_ENABLE) && (nand_device_type & DEV_TYPE_SYNC_MASK)) 
    { 
        //support SQRA mode
        FC_Set_Sqra_Mode();
    }
    else 
    {
        FC_Set_Access_Mode(FC_ACCESS_MODE_INDIRECT);
    }
	

}



int 
Nand_Reset(u8 timing_mode, u8 nand_device_type)
{
    int err= 0;
    int err1 = 0;
    int  tmp1,i;	
    int tChan, tRow;

    //unsigned long myflags;

    //raw_local_irq_save(myflags);
    
    FC_Set_Indirect_Mode();
    //FC_Set_Indirect_Sqra_Mode(timing_mode, nand_device_type);

    err = FC_Indirect_Reset_All_Devices(
        8,//nvcfg.nr_ch
        4,//nvcfg.nr_dev_per_ch
        (timing_mode >> 4) && (nand_device_type & DEV_TYPE_SYNC_MASK));

    DelayUS(1000);

    //raw_local_irq_restore(myflags);

  for(tRow = 0; tRow < 0x04; tRow++)
  {
    for(tChan = 0; tChan < 0x08; tChan++)
    {
      FC_Set_Feature(tChan, tRow, 0x01, 0x20);
	err1=FC_Get_Feature(tChan, tRow,0x01,&tmp1);
	  
    }
  } 
  
    return err;
}

int
FC_Indirect_Get_Status(u32 ch, u32 dev, u32 *status)
{
    FC_Indirect_Set_Access_Device(ch, dev);
    return FC_Indirect_Execute_Read_Status(status);
}

int 
_fc_indirect_execute_read_onfi_id(u8 *id)
{
    u8 cmd[] = { mFC_CMD_READ_FLASH_ID, 0x20 };

    memory_set(id, 0x00, 4);
    //memset(id, 0x00, 4);
    return FC_Indirect_Execute_Cmd(cmd, sizeof(cmd), id, 4, 0);
}

int
FC_Indirect_Execute_Read_Onfi_Id(u32 ch, u32 dev, u8 *id)
{
    FC_Indirect_Set_Access_Device(ch, dev);
    return _fc_indirect_execute_read_onfi_id(id);
}

int 
_fc_indirect_execute_read_toggle_id(u8 *id)
{
    u8 cmd[] = { mFC_CMD_READ_FLASH_ID, 0x40 };

    memory_set(id, 0x00, 6);
    return FC_Indirect_Execute_Cmd(cmd, sizeof(cmd), id, 6, 0);
}

int
FC_Indirect_Execute_Read_Toggle_Id(u32 ch, u32 dev, u8 *id)
{
    FC_Indirect_Set_Access_Device(ch, dev);
    return _fc_indirect_execute_read_toggle_id(id);
}




int 
_fc_indirect_execute_read_id(u8 *id, u32 nr_id_byte)
{
    u8 cmd[] = { mFC_CMD_READ_FLASH_ID, 0 };
    
    memory_set(id, 0x00, nr_id_byte);
    return FC_Indirect_Execute_Cmd(cmd, sizeof(cmd), id, nr_id_byte, 0);
}

int
FC_Indirect_Execute_Read_Id(u32 ch, u32 dev, u8 *id, u32 nr_id_byte)
{
    FC_Indirect_Set_Access_Device(ch, dev);
    return _fc_indirect_execute_read_id(id, nr_id_byte);
}

int 
Nand_Scan_Device(u8 *id_container, dev_t *devs, u32* nr_devs, u8 nr_id_byte)
{
    u32 ch, dev;
    u8 id[8];

    for (dev = 0; dev < (4); dev++) //(nvcfg.chdev & 0xF)
    {  // Scan device (CE)
        for (ch = 0; ch < (8); ch++) //(nvcfg.chdev >> 4)
	 {  // Scan channel (CH)
            FC_Indirect_Execute_Read_Id(ch, dev, id, nr_id_byte);

            if ((id[0] == 0xff) || (id[0] == 0x00)) 
	     {
                continue; //cannot find device, scan next channel
            }            

            if (*nr_devs == 0) 
	     {
                memory_copy((void *)id_container, (const void *)id, nr_id_byte);
            }
            else 
	     {
                if (memory_cmp(id_container, id, nr_id_byte)) 
		  {
                    // if id not match
                    return -1;
                }
            }

            devs[*nr_devs].ch = ch;
            devs[*nr_devs].dev = dev;
            devs[*nr_devs].chdev = ((ch << 4) | dev);
            (*nr_devs)++;

        }   // end for (ch = 0; ch < MAX_CHANNEL; ch++)

    }       //end for (dev = 0; dev < MAX_DEV_PER_CHANNEL; dev++)

    if (*nr_devs == 0) 
    {
        return -1;
    }
    return 0;
}

int 
FC_Indirect_Execute_Data_In(u8 *cmd, u32 cmd_sz, void *data, u32 data_sz)
{
    u32 double_data_xfer_en;
    u32 tmp;
    int err = 0;

    if (*cmd == mFC_CMD_ONFI_GET_FEATURES) 
    {

        // for get feature, drain data is different at sqra mode
        double_data_xfer_en = FC_Double_Data_Xfer_Eligibility();
    }
    else 
    {
        double_data_xfer_en = 0;
    }

    FC_Indirect_Prepare_Cmd(cmd, cmd_sz, 0, 0, 0);

    tmp = (cmd_sz - 1) |
        FC_INDIRECT_ACCESS_START |
        FC_INDIRECT_DUMMY_RBB |
        FC_INDIRECT_CT;
    FC_Indirect_Execute(tmp);

    err = FC_Indirect_Wait_For_Op_Done();
    if (err) 
    {
        return err;
    }

    DelayUS(15);    //delay 15us for read access
    
    err = FC_Indirect_Wait_Device_Status(FC_INDIRECT_READ_TIME_OUT_US);
    if (err) 
    {
        return err;
    }

    cmd[0] = mFC_CMD_READ_MODE;

    FC_Indirect_Prepare_Cmd(cmd, 1, data_sz, 0, double_data_xfer_en);   // Note: command size is 1 here
    tmp = 0 | FC_INDIRECT_ACCESS_START | FC_INDIRECT_DUMMY_RBB;
    FC_Indirect_Execute(tmp);

    FC_Indirect_Drain_Data((u8 *) data, data_sz, double_data_xfer_en);

    return err;

}


int 
_fc_indirect_read_parameter_page(u32 addr, void *data, u32 data_sz)
{
    u8 cmd[2];
    
    cmd[0] = mFC_CMD_ONFI_READ_PARAMETER;
    cmd[1] = (u8)addr;

    return FC_Indirect_Execute_Data_In(cmd, sizeof(cmd), data, data_sz);
}

int
FC_Indirect_Read_Parameter_Page(u32 ch, u32 dev, u32 addr, void *data, u32 data_sz)
{
    FC_Indirect_Set_Access_Device(ch, dev);
    return _fc_indirect_read_parameter_page(addr, data, data_sz);
}

int 
_fc_indirect_read_page(u32 block, u32 page, void *data, u32 data_sz)
{
    u8 cmd[7];
    u32 tmp;
    int err;
    
    cmd[0] = mFC_CMD_READ_FLASH_1ST;
    cmd[1] = 0;//c1
    cmd[2] = 0;//c2
    cmd[3] = (u8)((block<<PAGEPBLOCK_SHIFT)+page);//r1
    cmd[4] = (u8)(((block<<PAGEPBLOCK_SHIFT)+page)>>8);//r2
    cmd[5] = (u8)(((block<<PAGEPBLOCK_SHIFT)+page)>>16);//r3
    cmd[6] = mFC_CMD_READ_FLASH_2ND;
#if 0
	return FC_Indirect_Execute_Data_In(cmd, sizeof(cmd), data, data_sz);
#else
    FC_Indirect_Prepare_Cmd(cmd, sizeof(cmd), 0, 0, 0);

    tmp = (sizeof(cmd) - 1) |
        FC_INDIRECT_ACCESS_START |
        FC_INDIRECT_DUMMY_RBB |
        FC_INDIRECT_CT;
    FC_Indirect_Execute(tmp);

    err = FC_Indirect_Wait_For_Op_Done();
    if (err) 
    {
        return err;
    }

    DelayUS(15);    //delay 15us for read access
    
    err = FC_Indirect_Wait_Device_Status(FC_INDIRECT_READ_TIME_OUT_US);
    if (err) 
    {
        return err;
    }

    cmd[0] = mFC_CMD_READ_MODE;

    FC_Indirect_Prepare_Cmd(cmd, 1, data_sz, 0, 0);   // Note: command size is 1 here
    tmp = 0 | FC_INDIRECT_ACCESS_START | FC_INDIRECT_DUMMY_RBB;
    FC_Indirect_Execute(tmp);

    //DelayUS(150);

    FC_Indirect_Drain_Data((u8*) data, data_sz, 0);

    return err;
#endif
}

int
FC_Indirect_Read_Page(u32 ch, u32 dev, u32 block, u32 page, void *data, u32 data_sz)
{
    FC_Indirect_Set_Access_Device(ch, dev);
    return _fc_indirect_read_page(block,page,data, data_sz);
}


int 
_fc_indirect_write_page(u32 block, u32 page, void *data, u32 data_sz)
{
    u8 cmd[7];
    u32 tmp;
    int err;
    
    cmd[0] = mFC_CMD_PRG_FLASH_1ST;
    cmd[1] = 0;//c1
    cmd[2] = 0;//c2
    cmd[3] = (u8)((block<<PAGEPBLOCK_SHIFT)+page);//r1
    cmd[4] = (u8)(((block<<PAGEPBLOCK_SHIFT)+page)>>8);//r2
    cmd[5] = (u8)(((block<<PAGEPBLOCK_SHIFT)+page)>>16);//r3
    cmd[6] = mFC_CMD_PRG_FLASH_2ND;    
    

    FC_Indirect_Prepare_Cmd(cmd, sizeof(cmd), data_sz, 1, 0);
    tmp = (sizeof(cmd) - 1) |
	 FC_INDIRECT_OUT|
        FC_INDIRECT_ACCESS_START |
        FC_INDIRECT_DUMMY_RBB |
        FC_INDIRECT_CT;
    FC_Indirect_Execute(tmp);
   
    FC_Indirect_Push_Data((u8*) data, data_sz, 0);
    
    err = FC_Indirect_Wait_For_Op_Done();
    if (err) 
    {
        return err;
    }
    DelayUS(15);    //delay 15us for read access
    
    err = FC_Indirect_Wait_Device_Status(FC_INDIRECT_PRG_TIME_OUT_US);
    if (err) 
    {
        return err;
    }    

    //DelayUS(150);

    return err;

}


int
FC_Indirect_Write_Page(u32 ch, u32 dev, u32 block, u32 page, void *data, u32 data_sz)
{
    FC_Indirect_Set_Access_Device(ch, dev);
    return _fc_indirect_write_page(block,page,data, data_sz);
}

int
_fc_indirect_erase_block(u32 block)
{
    u8 cmd[5];
    u32 tmp;
    int err;
    
    cmd[0] = mFC_CMD_ERASE_FLASH_1ST;
    cmd[1] = (u8)((block<<PAGEPBLOCK_SHIFT));//r1
    cmd[2] = (u8)(((block<<PAGEPBLOCK_SHIFT))>>8);//r2
    cmd[3] = (u8)(((block<<PAGEPBLOCK_SHIFT))>>16);//r3
    cmd[4] = mFC_CMD_ERASE_FLASH_2ND;

    FC_Indirect_Prepare_Cmd(cmd, sizeof(cmd), 0, 0, 0);

    tmp = (sizeof(cmd) - 1) |
        FC_INDIRECT_ACCESS_START |
        FC_INDIRECT_DUMMY_RBB |
        FC_INDIRECT_CT;
    FC_Indirect_Execute(tmp);

    err = FC_Indirect_Wait_For_Op_Done();
    if (err) 
    {
        return err;
    }

    DelayUS(15);    //delay 15us for read access
    
    err = FC_Indirect_Wait_Device_Status(FC_INDIRECT_ERASE_TIME_OUT_US);
    if (err) 
    {
        return err;
    }    

    return err;
}

int
FC_Indirect_Erase_Block(u32 ch, u32 dev, u32 block)
{
    FC_Indirect_Set_Access_Device(ch, dev);
    return _fc_indirect_erase_block(block);
}

u16 
Nand_Onfi_Crc_16(u8 *data, u32 size)
{
    // Bit by bit algorithm without augmented zero bytes
    const u32 crcinit = 0x4F4E; // Initial CRC value in the shift register (ONFI required)
    const int order = 16;       // Order of the CRC-16
    const u32 polynom = 0x8005; // Polynomial (ONFI required)
    u32 j, c, bit;
    u32 crc = crcinit;
    u32 crcmask, crchighbit;

    crcmask = (((1UL << (order - 1)) - 1) << 1) | 1;
    crchighbit = 1UL << (order - 1);

    while (size--) 
    {
        c = (u32) * data++;
        for (j = 0x80; j; j >>= 1) 
	 {
            bit = crc & crchighbit;
            crc <<= 1;
            if (c & j) 
	     {
                bit ^= crchighbit;
            }

            if (bit) 
	     {
                crc ^= polynom;
            }
        }

        crc &= crcmask;
    }

    return crc;
}


int 
Nand_Check_Param_Page_Validity(void *param, u32 param_onfi)
{
    if (param_onfi) 
    {
        if (((onfi_param_page_t*)param)->signature != ONFI_PARAM_PAGE_SIGNATURE) 
	 {
            return -1;
        }

        if (Nand_Onfi_Crc_16((u8 *) param,field_offset(onfi_param_page_t, crc)) != ((onfi_param_page_t*)param)->crc)             
        {
            return -2;
        }
    }
    else 
    {
        if (((toggle_param_page_t*)param)->signature != TOGGLE_PARAM_PAGE_SIGNATURE) 
	 {
            return -1;
        }
    }
    return 0;
}

#if 0
void* 
Nand_Read_Parameter_Page(u32 ch, u32 dev, nand_t *nand, u32 param_onfi)
{
	void *pparam_data_three_copies;
	void *pparam;
	u32 i;
	int err = 0;
	
	pparam_data_three_copies =   (void *) local_mm_allocate(sizeof(onfi_param_page_t) * 3);
	memory_set(pparam_data_three_copies, 0x00, sizeof(onfi_param_page_t) * 3);

	if (param_onfi) 
	{
        	FC_Indirect_Read_Parameter_Page(
		       ch, dev, READ_PARAM_ADDR_ONFI, 
            		pparam_data_three_copies, sizeof(onfi_param_page_t) * 3);
        	pparam = (onfi_param_page_t *)((u32)pparam_data_three_copies);
    	}
    	else 
	{
        	FC_Indirect_Read_Parameter_Page(
            		ch, dev, READ_PARAM_ADDR_TOGGLE, 
            		pparam_data_three_copies, sizeof(toggle_param_page_t) * 3);
        	pparam = (toggle_param_page_t *)((u32)pparam_data_three_copies);
    	}

    	if (param_onfi) 
	{
        	for(i=0; i < 3; i++) 
		{
            		err |= Nand_Check_Param_Page_Validity((void*)pparam, param_onfi);
            		pparam = ((onfi_param_page_t*)pparam) + 1;
        	}
    	}
    	else 
	{
        	//for toggle device, only check the first
        	err = Nand_Check_Param_Page_Validity((void*)pparam, param_onfi);
    	}

	return (void*)pparam_data_three_copies;
}
#endif

void* 
Nand_Read_Parameter_Page(u32 ch, u32 dev, nand_t *nand, u32 param_onfi)
{
	//onfi_param_page_t pparam_data_three_copies[3];
	void *pparam;
	u32 i;
	int err = 0;
	
	//pparam_data_three_copies =   (void *) local_mm_allocate(sizeof(onfi_param_page_t) * 3);
	memory_set(pparam_data_three_copies, 0x00, sizeof(onfi_param_page_t) * 3);

	if (param_onfi) 
	{
        	FC_Indirect_Read_Parameter_Page(
		       ch, dev, READ_PARAM_ADDR_ONFI, 
            		(void*)pparam_data_three_copies, sizeof(onfi_param_page_t) * 3);
        	pparam = (onfi_param_page_t *)((u32)pparam_data_three_copies);
    	}
    	else 
	{
        	FC_Indirect_Read_Parameter_Page(
            		ch, dev, READ_PARAM_ADDR_TOGGLE, 
            		(void*)pparam_data_three_copies, sizeof(toggle_param_page_t) * 3);
        	pparam = (toggle_param_page_t *)((u32)pparam_data_three_copies);
    	}

    	if (param_onfi) 
	{
        	for(i=0; i < 3; i++) 
		{
            		err |= Nand_Check_Param_Page_Validity((void*)pparam, param_onfi);
            		pparam = ((onfi_param_page_t*)pparam) + 1;
        	}
    	}
    	else 
	{
        	//for toggle device, only check the first
        	err = Nand_Check_Param_Page_Validity((void*)pparam, param_onfi);
    	}

	if(err)
		return NULL;

	return (void*)pparam_data_three_copies;
}

int  
Nand_Get_Onfi_Parameter_Page(u32 ch, u32 dev, nand_t *nand)
{
	onfi_param_page_t *pparam_data_three_copies;
	void *pparam;
	u32 i;
       u32 temp;
	u32 nr_blocks_per_lun;
	u32 capacity; 
	
	pparam = (void*)Nand_Read_Parameter_Page(ch, dev, nand, 1);
    	if (pparam == NULL) 
	{
        	return -1;
    	}

	pparam_data_three_copies = (onfi_param_page_t *)pparam;
		
    nand->opt_cmds_spt = pparam_data_three_copies->opt_cmds;
    nand->nr_page_per_block = (u16) le32_unaligned_get(pparam_data_three_copies->nr_pages_per_block);
    nand->spare_sz = le16_unaligned_get(pparam_data_three_copies->spare_sz);
    nand->nr_bad_blocks_max = le16_unaligned_get(pparam_data_three_copies->nr_bad_blocks_per_lun_max); 
    nand->page_sz = le32_unaligned_get(pparam_data_three_copies->page_sz);
    nand->nr_luns = pparam_data_three_copies->nr_luns;
    nand->nr_planes = (1 << pparam_data_three_copies->nr_interleaved_addr_bits);
    //set_parameter_page_timing(nand, pparam_data_three_copies);
    if (nand->rd_dly_us  == 0) 
    {
        nand->rd_dly_us  = le16_unaligned_get(pparam_data_three_copies->t_r_max);
    }
    if (nand->wrt_dly_us == 0) {
        nand->wrt_dly_us = le16_unaligned_get(pparam_data_three_copies->t_prog_max);
    }
    if (nand->ers_dly_us == 0) {
        nand->ers_dly_us = le16_unaligned_get(pparam_data_three_copies->t_bers_max);
    }
    if (nand->tccs_ns    == 0) {
        nand->tccs_ns    = le16_unaligned_get(pparam_data_three_copies->t_ccs_min);
    }
    if (nand->rst_dly_us == 0) {
        nand->rst_dly_us = 100;  // 100us, set to default value as it is not givien in parameter list
    }
    if (nand->tcad_ns    == 0) {
        nand->tcad_ns    = 25;      // 25ns, set to default value as it is not givien in parameter list
    }
    if (nand->trhw_ns    == 0) {
        nand->trhw_ns    = 100;     // 100ns, set to default value as it is not givien in parameter list
    }

    if (nand->factory_defect_check_pages == 0) 
    {
        nand->factory_defect_check_pages = 0x01;
    }

    nand->endurance = pparam_data_three_copies->block_endurance[0];
    for (i = 0; i < pparam_data_three_copies->block_endurance[1]; i++) 
    {
        nand->endurance *= 10;  //eg. endurance[0]=1, [1]=5, then endurance is 100000
    }

    nr_blocks_per_lun = le32_unaligned_get(pparam_data_three_copies->nr_blocks_per_lun);
    capacity = nand->page_sz * nand->nr_page_per_block;
    capacity >>= 10;
    capacity *= (nr_blocks_per_lun * pparam_data_three_copies->nr_luns);
    capacity >>= (20 - 3);    // KB*(2^3)->Kbit, Kbit/(2^MB_SHIFT)->Gbit
    nand->total_space_in_gbit = capacity;

    if (pparam_data_three_copies->features & (1<<5)) 
    {
        nand->dev_type = DEV_TYPE_MICRON_ONFI_SYNC;
        temp = (u32) le16_unaligned_get(&pparam_data_three_copies->src_sync_timing_modes);
    }
    else 
    {
        nand->dev_type = DEV_TYPE_MICRON_ONFI_ASYNC;
        temp = (u32) le16_unaligned_get(&pparam_data_three_copies->async_timing_modes);
    }
    //nand->max_mode_nr = ctz(temp);
    nand->max_mode_nr = Get_Cnt_1(temp);

	//nand->dev_type = DEV_TYPE_MICRON_ONFI_ASYNC;
	//nand->max_mode_nr = 4;
#if 0
	nand->dev_type = DEV_TYPE_MICRON_ONFI_ASYNC;
	nand->max_mode_nr = 4;
#endif
    return 0;
}


int  
Nand_Get_Toggle_Parameter_Page(u32 ch, u32 dev, nand_t *nand)
{
	onfi_param_page_t *pparam_data_three_copies;
	void *pparam;
	u32 i;
       u32 temp;
	u32 nr_blocks_per_lun;
	u32 capacity; 
	
	pparam = (void*)Nand_Read_Parameter_Page(ch, dev, nand, 0);
    	if (pparam == NULL) 
	{
        	return -1;
    	}

	pparam_data_three_copies = (onfi_param_page_t *)pparam;
		
    //nand->opt_cmds_spt = pparam_data_three_copies->opt_cmds;
    nand->nr_page_per_block = (u16) le32_unaligned_get(pparam_data_three_copies->nr_pages_per_block);
    nand->spare_sz = le16_unaligned_get(pparam_data_three_copies->spare_sz);
    //nand->nr_bad_blocks_max = le16_unaligned_get(pparam_data_three_copies->nr_bad_blocks_per_lun_max); 
    nand->page_sz = le32_unaligned_get(pparam_data_three_copies->page_sz);
    nand->nr_luns = pparam_data_three_copies->nr_luns;
    //nand->nr_planes = (1 << pparam_data_three_copies->nr_interleaved_addr_bits);    
    
    if (nand->rst_dly_us == 0) {
        nand->rst_dly_us = 100;  // 100us, set to default value as it is not givien in parameter list
    }
    if (nand->tcad_ns    == 0) {
        nand->tcad_ns    = 25;      // 25ns, set to default value as it is not givien in parameter list
    }
    if (nand->trhw_ns    == 0) {
        nand->trhw_ns    = 100;     // 100ns, set to default value as it is not givien in parameter list
    }
    
    nand->factory_defect_check_pages = 0x01;


    return 0;
}

int 
Nand_Scan_Supported_List(u8 *id_container, u32 nr_id_byte, u32 *nand_device_class )
{
    int i;

    for (i = 0; i < NR_SUPPORTED_DEVS; i++)
    {
        if (0 == memory_cmp((void *)id_container, (void *)_supported_devices[i].id, nr_id_byte))
	 {
            memory_copy((void *)(&nand_detected), (const void *)(&_supported_devices[i]), sizeof(nand_t));
            if (*nand_device_class == NAND_DEVICE_CLASS_UNKNOWN)
	     {
                // it is detected as in the support listed, and not ONFI or TOGGLE
                *nand_device_class = NAND_DEVICE_CLASS_LISTED;                   
            }
            return 0;
        }
    }
    return 1;
}



int 
Nand_Find_All_Device(u8 *id_container, u8 *nr_ch, u8 *nr_dev, dev_t *devs)
{
    u8  id[8];
    u32 dev;
    u32 tmp1,tmp2;
    u32 nr_id_byte;
    u32 nand_device_class;
    u32 nr_devs = 0;
    u32 dd_retry_cnt = 0;
    u8 onfi_id[4] = {'O', 'N', 'F', 'I'};
    u8 jedec_id[4] = {'J', 'E', 'D', 'E'};
	
	// init nand_detected to 0
    memory_set(&nand_detected, 0x00, sizeof(nand_t));

Find_Again:
	Nand_Reset(INITIAL_TIMING_MODE_SEL, DEV_TYPE_INITIAL_ASYNC);   
	tmp2 = REG16_READ(FC_REG_IF_CFG);
    	FC_Indirect_Get_Status(0, 0, &tmp1);
    	
    	// set initial value for nr_id_byte and nand_device_class
    	nand_device_class = NAND_DEVICE_CLASS_UNKNOWN;
    	nr_id_byte = 5;
        
    	// check if it is ONFI device
    	FC_Indirect_Execute_Read_Onfi_Id(0, 0, id);//(devs[0].ch, devs[0].dev, id)
	if (0)//(memory_cmp(id, onfi_id, 4) == 0) 
	{
        	nand_device_class = NAND_DEVICE_CLASS_ONFI;    // ONFI device detected
        	nr_id_byte = 5;
    	}
    	else 
	{
        // try to detect if it is TOGGLE device
        	FC_Indirect_Execute_Read_Toggle_Id(0, 0, id);//(devs[0].ch, devs[0].dev, id)
        	if (memory_cmp(id, jedec_id, 4) == 0) 
		{ 
            	// TOGGLE device detected
            		nand_device_class = NAND_DEVICE_CLASS_TOGGLE;    //toggle device detected         
            		nr_id_byte = 5;
            		// set to toggle indirect mode access
            		FC_Set_Indirect_Sqra_Mode(INITIAL_TOGGLE_TIMING_MODE_SEL, DEV_TYPE_INITIAL_TOGGLE);
        	}
    	}

		// scan device through all channel and ce
	//REG16_WRITE(0x1c00b608,0x0DB6);	
    	if (Nand_Scan_Device(id_container, devs, &nr_devs, nr_id_byte) != 0)		
	{
        	if (dd_retry_cnt < 3) 
		{
            		dd_retry_cnt++;
            		goto Find_Again;
        	}
        
        	if (nr_devs == 0) 
		{
            		return nv_err_no_dev;
        	}
        	else 
		{
            		return nv_err_dev_inconsistent;
        	}
    	}

	// Figure out number of channel & device found
    	*nr_ch = 1;
    	for (dev = 1; dev < nr_devs; dev++) 
	{
        	if (devs[dev].ch != devs[0].ch) 
		{
            		(*nr_ch) ++;
        	}
        	else 
		{
            		break;
        	}
    	}
    	*nr_dev = nr_devs / *nr_ch;

	Nand_Scan_Supported_List(id_container, nr_id_byte, &nand_device_class);

	
	
	// get parameter page
    	switch (nand_device_class) 
	{

        	case NAND_DEVICE_CLASS_ONFI:
            		memory_copy((void *)nand_detected.id, (const void *)id_container, nr_id_byte);
            		nand_detected.nr_id_byte = nr_id_byte;
            		Nand_Get_Onfi_Parameter_Page( 0, 0, &nand_detected );
			
            	break;
        	case NAND_DEVICE_CLASS_TOGGLE:
            	//toggle device parameter page should be obtained from preset table
            		memory_copy((void *)nand_detected.id, (const void *)id_container, nr_id_byte);
            		nand_detected.nr_id_byte = nr_id_byte;
			Nand_Get_Toggle_Parameter_Page( 0, 0, &nand_detected );
            	break;
        	default: // Nothing to do
            	break;
    	} // switch (nand_device_class)

    	nvcfg.nand_device_class = (u8)nand_device_class;

    	return 0;
}

u8 
Nand_Get_Dev_Timing_Mode(nand_t *nand)
{
    
    if (nand->dev_type & (DEV_TYPE_TOGGLE_MASK | DEV_TYPE_SYNC_MASK)) 
    {
        return (nand->max_mode_nr | BIT_4);      // set bit4 for toggle or sync mode
    }
    else 
    {
        return nand->max_mode_nr;               // async mode
    }
}

void 
Nand_Select_Hw_Timing_Mode(u32 nand_type)
{
    u32 fc_clk = FC_Platform_Get_FC_Clk(nvhwcfg.timing_mode_sel);

    if (nand_type & DEV_TYPE_TOGGLE_MASK) 
    {
        /* TOGGLE DEVICE */
        if (fc_clk >=  100000000L) 
	 {//  100 MHz
            if (nvhwcfg.timing_mode_sel >= 0x13) 
	     {
                nvhwcfg.timing_mode_sel = 0x13;
            }
        }
        else if (fc_clk >=   66000000L) 
	 {//  66 MHz
            if (nvhwcfg.timing_mode_sel >= 0x12) 
	     {
                nvhwcfg.timing_mode_sel = 0x12;
            }
        }
        else if (fc_clk >=   40000000L) 
	 {//  40 MHz
            if (nvhwcfg.timing_mode_sel >= 0x11) 
	     {
                nvhwcfg.timing_mode_sel = 0x11;
            }
        }
        else 
	 {                                    //  <40 MHz
            nvhwcfg.timing_mode_sel = 0x10;
        }
    }
    else 
    {
        /* SYNC MODE DEVICE */
        if ( (nand_type & DEV_TYPE_SYNC_MASK)
            && (nvhwcfg.timing_mode_sel & BIT_4) ) 
        {
            if (fc_clk >=  166000000L) 
	     {//  166 MHz
                if (nvhwcfg.timing_mode_sel >= 0x15) 
		  {
                    nvhwcfg.timing_mode_sel = 0x15;
                }
            }
            else if (fc_clk >=  133000000L) 
	     {//  133 MHz
                if (nvhwcfg.timing_mode_sel >= 0x14) 
		  {
                    nvhwcfg.timing_mode_sel = 0x14;
                }
            }
            else if (fc_clk >=  100000000L) {//  100 MHz
                if (nvhwcfg.timing_mode_sel >= 0x13) {
                    nvhwcfg.timing_mode_sel = 0x13;
                }
            }
            else if (fc_clk >=   66000000L) 
	     {//  66 MHz
                if (nvhwcfg.timing_mode_sel >= 0x12) 
		  {
                    nvhwcfg.timing_mode_sel = 0x12;
                }
            }
            else if (fc_clk >=   40000000L) 
	     {//  40 MHz
                if (nvhwcfg.timing_mode_sel >= 0x11) 
		  {
                    nvhwcfg.timing_mode_sel = 0x11;
                }
            }
            else 
	     {                                    //  <40 MHz
                nvhwcfg.timing_mode_sel = 0x10;
            }
        }
        else 
	 {
            /* ONFI */
            if (fc_clk >=  80000000L) 
	     {     //  80 MHz
                if (nvhwcfg.timing_mode_sel >= 0x5) 
		  {
                    nvhwcfg.timing_mode_sel = 0x5;
                }
            }
            else if (fc_clk >=  66000000L) 
	     {//  66 MHz
                if (nvhwcfg.timing_mode_sel >= 0x4) 
		  {
                    nvhwcfg.timing_mode_sel = 0x4;
                }
            }
            else if (fc_clk >=  57000000L) 
	     {//  57 MHz
                if (nvhwcfg.timing_mode_sel >= 0x3) 
		  {
                    nvhwcfg.timing_mode_sel = 0x3;
                }
            }
            else if (fc_clk >=   40000000L) 
	     {//  40 MHz
                if (nvhwcfg.timing_mode_sel >= 0x2) 
		  {
                    nvhwcfg.timing_mode_sel = 0x2;
                }
            }
            else if (fc_clk >=   20000000L) 
	     {//  20 MHz
                if (nvhwcfg.timing_mode_sel >= 0x1) 
		  {
                    nvhwcfg.timing_mode_sel = 0x1;
                }
            }
            else 
	     {                                    //  <20 MHz
                nvhwcfg.timing_mode_sel = 0x0;
            }
        }
    }
}

int 
FC_Indirect_Set_Features(u32 ch, u32 dev, u32 fa, void *data, u32 data_sz)
{
    u8 cmd[] = { mFC_CMD_ONFI_SET_FEATURES, 0 };
    int err = 0;

    FC_Indirect_Set_Access_Device(ch, dev);

    cmd[1] = (u8) fa;

    err = FC_Indirect_Execute_Cmd(cmd, sizeof(cmd), data, data_sz, 1);

    DelayUS(1);                               // 1us delay for onfi set feature ready
    err |= FC_Indirect_Wait_Device_Status(0);   // 0 delay, wait device ready
    return err;
}

int 
FC_Set_Feature(u32 ch, u32 dev, u32 feature_addr, u32 feature_value)
{
    u8 px[4];

    px[0] = (u8) ((feature_value & 0xFF));
    px[1] = (u8) ((feature_value & 0xFF00) >> 8);
    px[2] = (u8) ((feature_value & 0xFF0000) >> 16);
    px[3] = (u8) ((feature_value & 0xFF000000) >> 24);

    return FC_Indirect_Set_Features(ch, dev, feature_addr, px, sizeof(px));
}

__inline u32
FC_Check_Sqra_Mode_Eligibility(u32 dev_type)
{
    if(dev_type & DEV_TYPE_SYNC_MASK) {    // only for ONFI SYNC device, return value by checking NFIF bit
        return (REG16_READ(FC_REG_IF_CFG) & FC_NFIF_JDBC_ONFI_SYNC) ? 1 : 0;
    }
    else 
    {    // for other cases including toggle mode, always return 0
        return 0;
    }
}

int 
FC_Indirect_Get_Features(u32 ch, u32 dev, u32 fa, void *data, u32 data_sz)
{
    u8 cmd[] = { mFC_CMD_ONFI_GET_FEATURES, 0 };

    FC_Indirect_Set_Access_Device(ch, dev);

    cmd[1] = (u8) fa;

    return FC_Indirect_Execute_Cmd(cmd, sizeof(cmd), data, data_sz, 0);

}

int 
FC_Get_Feature(u32 ch, u32 dev, u32 feature_addr, u32 *pfeature_value)
{
    u8 px[4];
    int err;

    err = FC_Indirect_Get_Features(ch, dev, feature_addr, px, sizeof(px));

    *pfeature_value = (u32) px[0];

    return err;
}



int 
FC_Set_Feature_Timing_Mode(dev_t* devs, u32 nr_devs, u32 device_class)
{
    u32 dev;
    u32 err = 0;
    u32 tmp1;
    u32 ch;


    //set to asynchronous mode
    FC_Set_Flash_Type_H(0);
    FC_Set_Flash_Type_L(nand_detected.dev_type);

    /*for(ch = 0;ch<nvcfg.nr_ch;ch++)
    {
    	for(dev = 0;dev<nvcfg.nr_dev_per_ch;dev++)
    	{
    		FC_Indirect_Fifo_Reset();
		if (device_class == NAND_DEVICE_CLASS_ONFI) 
		 {
	            FC_Set_Feature(
	                ch, 
	                dev,
	                ONFI_FA_TIMING_MODE,
	                (u32) nvhwcfg.timing_mode_sel);
	        }
		 else
		 {
			FC_Set_Feature(ch,dev,0x80,0);
		 }
    	}
    }*/

    for (dev = 0; dev < nr_devs; dev++) 
    {
        FC_Indirect_Fifo_Reset();
        if (device_class == NAND_DEVICE_CLASS_ONFI) 
	 {
            FC_Set_Feature(
                devs[dev].ch, 
                devs[dev].dev,
                ONFI_FA_TIMING_MODE,
                (u32) nvhwcfg.timing_mode_sel);
        }
	 else
	 {
		FC_Set_Feature(devs[dev].ch,devs[dev].dev,0x02, 0);
	 }
    }

    FC_Set_Flash_Type_H(nvhwcfg.timing_mode_sel);

    if (FC_Check_Sqra_Mode_Eligibility((u32)(FC_Get_Installed_Nand()->dev_type))&& (device_class == NAND_DEVICE_CLASS_ONFI) ) 
    {
        // set to sqra mode for synchrous device, for ONFI device only 
        //FC_Set_Sqra_Mode();
        FC_Set_Indirect_Sqra_Mode(nvhwcfg.timing_mode_sel,nand_detected.dev_type);
    }
	
    if (device_class == NAND_DEVICE_CLASS_TOGGLE) 
		//FC_Set_Indirect_Sqra_Mode(INITIAL_TOGGLE_TIMING_MODE_SEL, DEV_TYPE_INITIAL_TOGGLE);
		//FC_Set_Indirect_Sqra_Mode(((nand_detected.max_mode_nr+1)| ONFI_SYNC_ENABLE), nand_detected.dev_type);
		FC_Set_Indirect_Sqra_Mode(((0x03)| ONFI_SYNC_ENABLE), nand_detected.dev_type);//only support 133M
		
   /* for(ch = 0;ch<nvcfg.nr_ch;ch++)
    {
    	for(dev = 0;dev<nvcfg.nr_dev_per_ch;dev++)
    	{
    		FC_Indirect_Fifo_Reset();
		 if (device_class == NAND_DEVICE_CLASS_ONFI) 
		 {
	            err |= FC_Get_Feature(
	                ch,
	                dev,
	                ONFI_FA_TIMING_MODE,
	                &tmp1);            
	            if (tmp1 != (u32) nvhwcfg.timing_mode_sel) 
		     {
	                err |= 1;
	                return err;
	            }
	         }
		  else
		  {
		  	err |= FC_Get_Feature(ch,dev,0x80,&tmp1);
			if (tmp1 != 0) //toggle mode
		     	{
	                	err |= 1;
	                	return err;
	            	}
		  }
    	}
    }*/

    for (dev = 0; dev < nr_devs; dev++) 
    {
        FC_Indirect_Fifo_Reset();
        if (device_class == NAND_DEVICE_CLASS_ONFI) 
	 {
            err |= FC_Get_Feature(
                devs[dev].ch,
                devs[dev].dev,
                ONFI_FA_TIMING_MODE,
                &tmp1);            
            if (tmp1 != (u32) nvhwcfg.timing_mode_sel) 
	     {
                err |= 1;
                return err;
            }
         }
	  else
	  {
	  	err |= FC_Get_Feature(devs[dev].ch,devs[dev].dev,0x02,&tmp1);
		if (tmp1 != 0) //toggle mode
	     	{
                	err |= 1;
                	return err;
            	}
	  }
    }

    return err;
}

int 
FC_Set_Feature_Drive_Strength(dev_t* devs, u32 nr_devs, u32 device_class)
{
    u32 dev;
    u32 err = 0;
    u32 tmp1;
    u32 drive_strength;

    if(device_class == NAND_DEVICE_CLASS_ONFI) 
    {  
        drive_strength = (u32) ONFI_OUTPUT_DRIVE_STRENGTH_SEL;
    } 
    else 
    {
        drive_strength = (u32) TOGGLE_OUTPUT_DRIVE_STRENGTH_SEL;
    }

    for (dev = 0; dev < nr_devs; dev++) 
    {
        err |= FC_Set_Feature(
            devs[dev].ch,
            devs[dev].dev,
            ONFI_FA_IO_DRIVE_STRENGTH,
            drive_strength);

    	if(device_class == NAND_DEVICE_CLASS_ONFI) 
    	{ 
        // Toggle device does not support get feature
        	err |= FC_Get_Feature(
            devs[dev].ch,
            devs[dev].dev,
            ONFI_FA_IO_DRIVE_STRENGTH,
            &tmp1);       
	
            if (tmp1 != drive_strength) 
	     {
                err |= 1;
                return err;
            }
        }
    }

    return err;
}

void 
FC_Downgrade_Timing_Mode(u32* mode_retry_cnt, u8 min_timing_mode)
{
    (*mode_retry_cnt) ++;

    if (nvhwcfg.timing_mode_sel > min_timing_mode) 
    {
        //check if mode number > min_timing_mode
        if (*mode_retry_cnt > 3) 
	 {
            *mode_retry_cnt = 0;
            if (nvhwcfg.timing_mode_sel ==
                (ONFI_SYNC_ENABLE | ONFI_TIMING_MODE_0)) 
            {
                nvhwcfg.timing_mode_sel = ONFI_TIMING_MODE_5;	// switch from sync mode 0	to async mode 5
            }
            else 
	     {
                nvhwcfg.timing_mode_sel--;						// decrease the mode and try again
            }

        }

        // reset fc and devices
        Nand_Reset(INITIAL_TIMING_MODE_SEL, nand_detected.dev_type);
        FC_Set_Device_Seqport(nand_detected.dev_type);
        FC_Set_For_Timingmode(INITIAL_TIMING_MODE_SEL, nand_detected.dev_type);
	}
}


void
FC_Reset_Sqra_Mode(void)
{
    FC_Wait_Seq_Idle();

    REG16_CLEAR_BITS(FC_REG_SEQ_CNTL2, FC_SQRA_EN);

    DelayUS(FC_DLY_US);

    // from Jeff, disable ef fifo crc
    REG16_CLEAR_BITS(FC_REG_SEQ_CNTL2, 0x20);
}


void 
 FC_Set_Onfi_Toggle_Timing_Mode(u32 device_class)
{
    u32 dev;
    u32 tmp1;
    u32 nr_devs = nvcfg.nr_ch * nvcfg.nr_dev_per_ch;
    dev_t *devs = nvcfg.devs;
    u32 mode_retry_cnt = 0;
    int err = 0;
    u8 min_timing_mode;
        
    if(device_class == NAND_DEVICE_CLASS_ONFI) 
    {  
        min_timing_mode = ONFI_TIMING_MODE_0;
    } 
    else 
    {
        min_timing_mode = ONFI_SYNC_ENABLE | ONFI_TIMING_MODE_1;
    }

    Nand_Select_Hw_Timing_Mode((u32)nand_detected.dev_type);	 
	//set to asynchronous mode
    FC_Set_Flash_Type_H(0);
    FC_Set_Flash_Type_L(nand_detected.dev_type);
    
    do 
    {
        for (dev = 0; dev < nr_devs; dev ++) 
	 {
            FC_Indirect_Get_Status(devs[dev].ch, devs[dev].dev, &tmp1);            
        }
          
            
        err |= FC_Set_Feature_Timing_Mode(devs, nr_devs, device_class);
		
        err |= FC_Set_Feature_Drive_Strength(devs, nr_devs, device_class);
        if (err) 
	 {
            FC_Downgrade_Timing_Mode(&mode_retry_cnt, min_timing_mode);
            err = 0;
        }

        if (FC_Check_Sqra_Mode_Eligibility((u32)(FC_Get_Installed_Nand()->dev_type))
            && (device_class == NAND_DEVICE_CLASS_ONFI) ) 
        {
            // quit sqra mode for synchrous device, for ONFI device only 
            FC_Reset_Sqra_Mode();
        }

    }
    while (err);

}
 

void 
Nand_Set_Timing_Mode(u32 device_class)
{
    switch (device_class) 
    {
    default: // Unknown?
    case NAND_DEVICE_CLASS_LISTED:
        // Conventional device, in the supported list but not ONFI or TOGGLE devices    
    
        nvhwcfg.timing_mode_sel = ONFI_TIMING_MODE_4;  

        if (nvhwcfg.timing_mode_sel >= Nand_Get_Dev_Timing_Mode(&nand_detected) ) 
	 {
            nvhwcfg.timing_mode_sel = Nand_Get_Dev_Timing_Mode(&nand_detected);
        }

        //set default value
        FC_Set_For_Timingmode(nvhwcfg.timing_mode_sel, nand_detected.dev_type);

        break;

    case NAND_DEVICE_CLASS_ONFI:      
    
        nvhwcfg.timing_mode_sel = ONFI_TIMING_MODE_4;
    

        if (nand_detected.dev_type & DEV_TYPE_SYNC_MASK) 
	 {
            nvhwcfg.timing_mode_sel |= ONFI_SYNC_ENABLE;
        }

        if (nvhwcfg.timing_mode_sel >= Nand_Get_Dev_Timing_Mode(&nand_detected) ) 
	 {
            nvhwcfg.timing_mode_sel = Nand_Get_Dev_Timing_Mode(&nand_detected);
        }

        FC_Set_Onfi_Toggle_Timing_Mode(device_class);

        break;

    case NAND_DEVICE_CLASS_TOGGLE:
        
    
        nvhwcfg.timing_mode_sel = (ONFI_TIMING_MODE_3 | ONFI_SYNC_ENABLE);
    

        if (nvhwcfg.timing_mode_sel >= ( Nand_Get_Dev_Timing_Mode(&nand_detected) | ONFI_SYNC_ENABLE ) ) 
	 {
            nvhwcfg.timing_mode_sel = Nand_Get_Dev_Timing_Mode(&nand_detected) | ONFI_SYNC_ENABLE;
        }
       
        FC_Set_Onfi_Toggle_Timing_Mode(device_class);
        break;

    }
    
    if(FC_Get_Installed_Nand()) 
    { 
        //nand_detected.cell_type = (nand_detected.id[2]>>2) & 0x3;         

    }   

}

void 
FC_Set_Samsung_Toshiba_Seq_Block_Boundary(u8 nr_page_per_block)
{
    u32 tmp = 0;

    // nr_page_per_block no less than 32 and is power of 2
    if ((nr_page_per_block >= 32) && 
		(((nr_page_per_block - 1) & nr_page_per_block) == 0)) 
    {

        tmp = ctz(nr_page_per_block) - 5;
        tmp = (tmp << 8) | (tmp << 12) | 0xF;
    }
    REG16_WRITE(FC_REG_SEQ_CH0_BLK_BNDRY_INFO, tmp);
    REG16_WRITE(FC_REG_SEQ_CH1_BLK_BNDRY_INFO, tmp);
    REG16_WRITE(FC_REG_SEQ_CH2_BLK_BNDRY_INFO, tmp);
    REG16_WRITE(FC_REG_SEQ_CH3_BLK_BNDRY_INFO, tmp);
}

void
FC_Direct_Enable_Write_Protection(int enable)//  1 for disable wp?????
{
    u16 tmp = REG16_READ(FC_REG_DIRECT_ACCESS_CNTL_PORT1);
    if (enable) 
    {
        tmp &= ~FC_DIRECT_WP;
    }
    else 
    {
        tmp |= FC_DIRECT_WP;
    }

    REG16_WRITE(FC_REG_DIRECT_ACCESS_CNTL_PORT1, tmp);
}

void
FC_Set_Lun_Cfg(u32 lun_start_bit)
{
    u32 tmp;  

    lun_start_bit -= 16;
    tmp = (lun_start_bit << 12) |
        (lun_start_bit << 8) |
        (lun_start_bit << 4) |
        lun_start_bit;

    /*
        0h: LUN bit = ROW address [18:16]
        1h: LUN bit = ROW address [19:17]
        2h: LUN bit = ROW address [20:18]
        3h: LUN bit = ROW address [21:19]
        4h: LUN bit = ROW address [22:20]
        5h: LUN bit = ROW address [23:21]
        6h: LUN bit = ROW address [24:22]
        7h: LUN bit = ROW address [25:23]
        8h: LUN bit = ROW address [26:24]
        Dh: LUN bit = ROW address [31:29]
        Eh: LUN bit = ROW address [31:30]
        Fh: LUN bit = ROW address [31]
    */
    REG16_WRITE(FC_REG_SEQ_CH03_LUN_INFO, (u16) tmp);       // Plato only has 4 channels

    //REG16_WRITE(FC_REG_SEQ_CH47_LUN_INFO, (u16)tmp);
    //REG16_WRITE(FC_REG_SEQ_CH8B_LUN_INFO, (u16)tmp);
    //REG16_WRITE(FC_REG_SEQ_CHCF_LUN_INFO, (u16)tmp);
}


int Nand_Init_Nvcfg_Related (void) 
{
    nand_t * nand;
    u32 tmp;

    /* what device I am using now? */
    nand = FC_Get_Installed_Nand();
    if (nand == 0) 
    {
        return nv_err_dev_not_supported;
    }

    nvcfg.opt_cmds_spt = nand->opt_cmds_spt;

    //nr_ch & nr_dev_per_ch are detected by function device_discovery()
    nvcfg.total_sz_in_GB = (nand->total_space_in_gbit >> 3) *
        nvcfg.nr_ch *
        nvcfg.nr_dev_per_ch;

    //nvcfg.ecc_au_sz = nand->page_sz;                                // can be changed in the future
    nvcfg.ecc_au_sz = nand->page_sz/PARATIO; 
    if (nvcfg.ecc_au_sz > 8192) 
    {

        // maximum supported ecc au size is MAX_ECC_AU_SIZE=8192
        nvcfg.ecc_au_sz = 8192;
    }

    nvcfg.page_sz = nand->page_sz;
    
    nvcfg.ecc_au_sz_shift = ctz(nvcfg.ecc_au_sz);
    nvcfg.page_sz_shift = ctz(nvcfg.page_sz);

    nvcfg.full_page_sz = nand->page_sz + nand->spare_sz;
    
    nvcfg.nand_device_type = nand->dev_type;

    if( (nvcfg.nand_device_type & DEV_TYPE_BASIC_MASK) == DEV_TYPE_BASIC_SAMSUNG
        || (nvcfg.nand_device_type & DEV_TYPE_BASIC_MASK) == DEV_TYPE_BASIC_TOSHIBA) 
    {
        FC_Set_Samsung_Toshiba_Seq_Block_Boundary(nand->nr_page_per_block);
    }

    switch (nand->id[0]) 
    {
    	default:

    	case 0x2C:                                                      //Micron
    	case 0xAD:                                                      //Hynix
    	case 0x98:                                                      //Toshiba
        	nvcfg.mp_read_device_address = SEQ_DESC_SA;                 // for mp operation, set this value to DW0 of descriptor for new samsung devices?
        break;

    	case 0xEC:                                                      //Samsung
        	nvcfg.mp_read_device_address = SEQ_DESC_SA;                 // for mp operation, set this value to DW0 of descriptor for new samsung devices?

        //nvcfg.mp_read_device_address = 0;            // for mp operation, set this value to DW0 of descriptor for old samsung devices?
        break;
    }


    nvcfg.nr_plane_per_lun = nand->nr_planes;
    nvcfg.nr_lun_per_dev = nand->nr_luns;


    if (nvcfg.nr_lun_per_dev > 1) 
    {
        nvcfg.lun_des_type = SEQ_DESC_TYPE_ML_EN;
    }
    else 
    {
        nvcfg.lun_des_type = 0;
    }
	
    if ( nvcfg.nr_plane_per_lun > 1
         && (nvcfg.nand_device_type & DEV_TYPE_BASIC_MASK) == DEV_TYPE_BASIC_TOSHIBA 
         && (nvcfg.nand_device_type & DEV_TYPE_TOGGLE_MASK) 
        ) 
    {
        FC_Direct_Enable_Write_Protection(0);    //enable wp????
    }
    else 
    {
        FC_Direct_Enable_Write_Protection(0);    //disable wp????
    }

    nvcfg.nr_wdevs = nvcfg.nr_ch *
        nvcfg.nr_dev_per_ch *
        nvcfg.nr_plane_per_lun *
        nvcfg.nr_lun_per_dev;
    nvcfg.defect_array_size = (nvcfg.nr_wdevs + 31) >> 5;
    nvcfg.nr_ch_plane = nvcfg.nr_plane_per_lun * nvcfg.nr_ch;
    
    nvcfg.nr_ch_shift = ctz(nvcfg.nr_ch);
    nvcfg.nr_plane_per_lun_shift = ctz(nvcfg.nr_plane_per_lun);
    nvcfg.nr_lun_per_dev_shift = ctz(nvcfg.nr_lun_per_dev);
    nvcfg.nr_dev_per_ch_shift = ctz(nvcfg.nr_dev_per_ch);

    nvcfg.nr_defect_max = (nand->nr_bad_blocks_max * nand->nr_luns) // new: per device      //old: nvcfg.nr_wdevs;
    << (nvcfg.nr_ch_shift + nvcfg.nr_dev_per_ch_shift);

    nvcfg.endurance = nand->endurance;                              // block endurance
    tmp = ctz(nand->total_space_in_gbit);                           // get valid address in gbits
    tmp += 30 - 3;                              // 30: 1 gbits = 2^30 bits, -3: convert to Bytes
    tmp -= nvcfg.page_sz_shift;                 // convert to row address: - nvcfg.page_sz_shift
    tmp -= ctz(nand->nr_luns);                  // get lun start address bit number
    nvcfg.lun_to_page_shift = (u8) tmp;
    if(nvcfg.nand_device_type & DEV_TYPE_TOGGLE_MASK) 
    {
        nvcfg.lun_to_page_shift += 1;
    }
    FC_Set_Lun_Cfg((u16) tmp);
    
    nvcfg.nr_ch_plane_shift = nvcfg.nr_ch_shift + nvcfg.nr_plane_per_lun_shift; //wdevs composed of dev-lun-plane-ch
    nvcfg.nr_ch_plane_lun_shift = nvcfg.nr_ch_shift +
        nvcfg.nr_plane_per_lun_shift +
        nvcfg.nr_lun_per_dev_shift; //wdevs composed of dev-lun-plane-ch
    nvcfg.nr_ch_plane_dev_shift = nvcfg.nr_ch_shift +
        nvcfg.nr_plane_per_lun_shift +
        nvcfg.nr_dev_per_ch_shift;  //wdevs composed of dev-lun-plane-ch
    nvcfg.nr_wdevs_shift = ctz(nvcfg.nr_wdevs);

    nvcfg.nr_page_per_eu = nand->nr_page_per_block;
    
    nvcfg.nr_page_per_eu_shift = ctz(nvcfg.nr_page_per_eu);

    //nvcfg.nr_eu_per_plane = ( nand->total_space_in_gbit << (30 - 3 - nvcfg.page_sz_shift - nvcfg.nr_page_per_eu_shift) ) // total blocks
     //                        / ( nand->nr_luns * nand->nr_planes );
    nvcfg.nr_eu_per_plane = 2048;

    /*    Sequencer Hardware will automatically mask first row address for Samsung
    tmp = (0x1L << (nvcfg.lun_to_page_shift + nvcfg.nr_lun_per_dev_shift)) - 1;
    nvcfg.samsung_mp_first_row_address_mask = tmp;
    if(fc_get_flash_type() == FC_FLTYPE_TYPEB) {
        tmp = ~((0x1L << nvcfg.lun_to_page_shift) - 1);
        nvcfg.samsung_mp_first_row_address_mask &= tmp;        // for samsun device, masking is further calculated here
    }
    */
    nvcfg.faa_sz = _max(nvcfg.page_sz, nvcfg.ecc_au_sz);
    nvcfg.nr_page_per_faa = nvcfg.faa_sz >> nvcfg.page_sz_shift;
    nvcfg.nr_ecc_au_per_page = nvcfg.page_sz >> nvcfg.ecc_au_sz_shift;

    nvcfg.faa_sz_shift = ctz(nvcfg.faa_sz);
    nvcfg.nr_page_per_faa_shift = ctz(nvcfg.nr_page_per_faa);
    nvcfg.nr_ecc_au_per_page_shift = ctz(nvcfg.nr_ecc_au_per_page);

    return nv_err_ok;
}

__inline void
EC_Reset(void)
{
    u16 tmp = REG16_READ(EC_REG_CNTL_CFG1);
    tmp |= EC_SOFT_RESET;
    REG16_WRITE(EC_REG_CNTL_CFG1, tmp);
    tmp &= ~EC_SOFT_RESET;
    REG16_WRITE(EC_REG_CNTL_CFG1, tmp);
}

int 
EC_Calc_Ecc_Power(flex_au_fmt* au_fmt_ptr, ec_nvcfg_t* ec_nvcfg_ptr)
{
    int table_idx = ECC_POWER_TABLE_MAX - 1;
    int au_spare_sz;
    int meta_mcrc_en = (au_fmt_ptr->flex_au_setting_0 & AU_SETTING_META_MCRC_EN) != 0;
    int au_mcrc_en   = (au_fmt_ptr->flex_au_setting_0 & AU_SETTING_AU_MCRC_EN) != 0;
    int meta_ecc_en = (au_fmt_ptr->flex_au_setting_0 & AU_SETTING_META_ECC_EN) != 0;
    int aux_meta_sel = au_fmt_ptr->aux_size ? 1 : 0;
    int tmp;

    if (aux_meta_sel) 
    { //if aux is selected
        meta_ecc_en = 0;
        meta_mcrc_en = 0;
    }

    if(au_fmt_ptr->meta_size == 0)
    {
    	meta_mcrc_en = 0;
	meta_ecc_en = 0;
    }

    //calculate spare size for au
    au_spare_sz = (ec_nvcfg_ptr->full_page_sz - ec_nvcfg_ptr->page_sz) / au_fmt_ptr->page_au_ratio;

    au_spare_sz = au_spare_sz >> 3 << 3; //should be 8byte aligned

    au_spare_sz -= ( au_fmt_ptr->meta_size + au_fmt_ptr->aux_size + (meta_mcrc_en + au_mcrc_en) * 4 
                  + ((meta_ecc_en * au_fmt_ptr->meta_t * 15 + 7) >> 3));

    if (au_spare_sz <= 0) 
    {
        goto bailout;
    }

    //if user input t_strong & t_weak, calculate
    //if (au_fmt_ptr->t_strong != 0 && au_fmt_ptr->t_weak != 0) 
    if ((au_fmt_ptr->t_strong != 0) || (au_fmt_ptr->t_weak != 0)) 
    {

        tmp = (((au_fmt_ptr->two_level_en) && (au_fmt_ptr->cw_per_au > 1)) ?
                (au_fmt_ptr->t_strong + (au_fmt_ptr->cw_per_au - 1) * au_fmt_ptr->t_weak) * 15 :
                 au_fmt_ptr->cw_per_au * au_fmt_ptr->t_weak * 15);
        tmp = (tmp + 63) >> 6 << 3; //for 8 bytes alignment

        if (tmp > au_spare_sz) 
	 {
            return -1;
        }
        else
	 {
            return 0;
        }
    }
    //else

    if (au_fmt_ptr->cw_per_au == 1) 
    {
       //if only one codeword per au, directly calculate t_weak
       au_fmt_ptr->t_strong = 0;
       au_fmt_ptr->t_weak = au_spare_sz * 8 / 15;
    }
    else 
    {
        //check table
        table_idx = ECC_POWER_TABLE_MAX;

        while (table_idx > 0) 
	 {
            table_idx --;
            if (_supported_ecc_power[au_fmt_ptr->cw_per_au - 2][table_idx].spare_sz <= au_spare_sz) {
                au_fmt_ptr->t_weak = 
                    _supported_ecc_power[au_fmt_ptr->cw_per_au - 2][table_idx].t_weak;
                au_fmt_ptr->t_strong = 
                    _supported_ecc_power[au_fmt_ptr->cw_per_au - 2][table_idx].t_strong;
                break;
            }
        } //End of while (table_idx > 0)

        if (table_idx == 0) 
	 {
            goto bailout;
        }
    }
#if 0
    //adjust t_strong and t_weak based on asic limit
    if(au_fmt_ptr->t_strong > T_STRONG_MAX) 
    {
        au_fmt_ptr->t_strong = T_STRONG_MAX;
    }

    if(au_fmt_ptr->t_weak > T_WEAK_MAX) 
    {
        au_fmt_ptr->t_weak = T_WEAK_MAX;
    }
#endif
    return 0;

bailout:    
    return -1;
}

__inline void
EC_Set_Au_Format_Ptr(u16 au_fmt_cfg_ptr)
{
    u16 tmp = REG16_READ(EC_REG_AU_FORMAT_CFG_PTR);
    
    tmp &= 0xFFE0;  // keep bit 15:5
    tmp |= au_fmt_cfg_ptr;
    REG16_WRITE(EC_REG_AU_FORMAT_CFG_PTR, tmp);
} /*End of ec_set_au_format_ptr*/

__inline void
ECU_Update_Ctl_Cfg5(u16 ctrl_reg)
{
    u8 meta_ecc_en, mcrc_inv_mode, ecc_inv_mode, fit_2_phy_page;

    meta_ecc_en    = ctrl_reg & EC_META_ECC_EN;
    mcrc_inv_mode  = ctrl_reg & EC_MCRC_INV_MODE;
    ecc_inv_mode   = ctrl_reg & EC_ECC_INV_MODE;
    fit_2_phy_page = ctrl_reg & EC_FIT_2_PHY_PAGE;    

    if (meta_ecc_en) 
    {
        REG16_SET_BITS(EC_REG_CNTL_CFG5, EC_META_ECC_EN);
    }
    else 
    {
        REG16_CLEAR_BITS(EC_REG_CNTL_CFG5, EC_META_ECC_EN);
    }

    if (mcrc_inv_mode) 
    {
        REG16_SET_BITS(EC_REG_CNTL_CFG5, EC_MCRC_INV_MODE);
    }
    else 
    {
        REG16_CLEAR_BITS(EC_REG_CNTL_CFG5, EC_MCRC_INV_MODE);
    }

    if (ecc_inv_mode) 
    {
        REG16_SET_BITS(EC_REG_CNTL_CFG5, EC_ECC_INV_MODE);
    }
    else 
    {
        REG16_CLEAR_BITS(EC_REG_CNTL_CFG5, EC_ECC_INV_MODE);
    }

    if (fit_2_phy_page) 
    {
        REG16_SET_BITS(EC_REG_CNTL_CFG5, EC_FIT_2_PHY_PAGE);
    }
    else 
    {
        REG16_CLEAR_BITS(EC_REG_CNTL_CFG5, EC_FIT_2_PHY_PAGE);
    }

    //ECU uses erase thrshold programmed by firmware
    REG16_SET_BITS(EC_REG_CNTL_CFG5, EC_MANUAL_ERASE_THRSHD_EN);

}

__inline void
ECU_Set_Ctl_Cfg7(u8 ecu_hlba_strip_mode, u8 ecu_hlba_mode, u8 ecu_mpecc_en)
{
    u16 tmp;
    
    tmp = (ecu_hlba_strip_mode >> EC_ECU_HLBA_STRIP_MODE_OFFSET) |
          (ecu_hlba_mode >> EC_ECU_HLBA_MODE_OFFSET) |
          ecu_mpecc_en;
    REG16_WRITE(EC_REG_CNTL_CFG7, tmp);
}

__inline void
ECU_Set_Ctl_Cfg8(u16 host_sector_size)
{
    u16 tmp = REG16_READ(EC_REG_CNTL_CFG8);
    
    tmp &= 0xC000;  // keep bit 15:14
    tmp |= host_sector_size;
    REG16_WRITE(EC_REG_CNTL_CFG8, tmp);
}

__inline void
ECU_Set_Ctl_Cfg9(u16 ecu_host_ratio)
{
    u16 tmp = REG16_READ(EC_REG_CNTL_CFG9);
    
    tmp &= 0xFFE0;  // keep bit 15:5
    tmp |= ecu_host_ratio;
    REG16_WRITE(EC_REG_CNTL_CFG9, tmp);
}

__inline void
ECU_Set_Ctl_Cfg10(u16 meta_size)
{
    u16 tmp = REG16_READ(EC_REG_CNTL_CFG10);
    
    tmp &= 0xFC00;  // keep bit 15:10
    tmp |= meta_size;
    REG16_WRITE(EC_REG_CNTL_CFG10, tmp);
}

__inline void
ECU_Set_Ctl_Cfg13(u16 ctrl_reg)
{
    REG16_WRITE(EC_REG_CNTL_CFG13, ctrl_reg);
	REG32_WRITE(0x1c00b238, 0x55aa55aa);
}

__inline void
ECU_Set_Cfg1(u8 au_mcrc_en, u16 cw_per_au, u16 two_level_en)
{
    u16 tmp;
    tmp = (((u16) au_mcrc_en) << 5)
        | (((u16) two_level_en) << 4)    
        | (((u16) cw_per_au) << 0)
        ;
    REG16_WRITE(EC_REG_CFG1, tmp);
}

__inline void
ECU_Set_Cfg2(u16 page_sz)
{
    u16 tmp = REG16_READ(EC_REG_CFG2);
    
    tmp &= 0x8000;  // keep bit 15
    tmp |= page_sz;
    REG16_WRITE(EC_REG_CFG2, tmp);
}

__inline void
ECU_Enable_Meta_Mcrc(void)
{    
    REG16_SET_BITS(EC_REG_CFG3, EC_META_MCRC_EN);
}

__inline void
ECU_Disable_Meta_Mcrc(void)
{    
    REG16_CLEAR_BITS(EC_REG_CFG3, EC_META_MCRC_EN);
}

__inline void
ECU_Set_Cfg3(u32 meta_mcrc_en, u32 meta_threshold, u32 t_meta)
{
    u16 tmp = (((u16) meta_threshold) << 4)
            | (((u16) t_meta) << 0)
            ;
                
    REG16_WRITE(EC_REG_CFG3, tmp);
    
    if(meta_mcrc_en) 
    {
        ECU_Enable_Meta_Mcrc();
    }
    else 
    {
        ECU_Disable_Meta_Mcrc();
    }
    
} /*End of ecu_set_cfg3*/

__inline void
ECU_Set_Cfg4(u32 t_strong, u32 t_weak)
{
    u16 tmp = (((u16) t_strong) << 8)
            | (((u16) t_weak) << 0)
            ;

    REG16_WRITE(EC_REG_CFG4, tmp);
} /*End of ecu_set_cfg4*/

__inline void
ECU_Set_Cfg5(u32 strong_threshold, u32 weak_threshold)
{
    u16 tmp = (((u16) strong_threshold) << 8)
            | (((u16) weak_threshold) << 0)
            ;
            
    REG16_WRITE(EC_REG_CFG5, tmp);
} /*End of ecu_set_cfg5*/

__inline void
ECU_Set_Cfg6(u32 erase_threshold)
{
    u16 tmp = REG16_READ(EC_REG_CFG6);

    tmp &= 0xFF00;
    tmp |= (u16)erase_threshold;
            
    REG16_WRITE(EC_REG_CFG6, tmp);
} /*End of ecu_set_cfg6*/

void 
EC_Set_Au_Format_Cfg(flex_au_fmt* au_fmt_ptr)
{
    int meta_mcrc_en = (au_fmt_ptr->flex_au_setting_0 & AU_SETTING_META_MCRC_EN) != 0;
    int au_mcrc_en   = (au_fmt_ptr->flex_au_setting_0 & AU_SETTING_AU_MCRC_EN) != 0;
    int mpecc_en     = (au_fmt_ptr->flex_au_setting_1 & AU_SETTING_ECU_MPECC_EN) != 0;
    int scr_user_en  = (au_fmt_ptr->flex_au_setting_0 & AU_SETTING_SCR_USER_EN) != 0;
    int scr_meta_en  = (au_fmt_ptr->flex_au_setting_0 & AU_SETTING_SCR_META_EN) != 0;
    int scr_user_seed_src = ((au_fmt_ptr->flex_au_setting_1 >> AU_SETTING_SCR_USER_SEED_SRC_SHIFT) & 0x3);
    int scr_meta_seed_src = ((au_fmt_ptr->flex_au_setting_1 >> AU_SETTING_SCR_META_SEED_SRC_SHIFT) & 0x3);
    int scr_meta_inv_en = ((au_fmt_ptr->flex_au_setting_1 & AU_SETTING_SCR_META_INV_EN) != 0);

    if(au_fmt_ptr->meta_size == 0)
    {
		ECU_Update_Ctl_Cfg5(0);
		meta_mcrc_en = 0;
    }
    else
    	ECU_Update_Ctl_Cfg5((au_fmt_ptr->flex_au_setting_0 & AU_SETTING_META_ECC_EN 
                           ? EC_META_ECC_EN    : 0)
                       |(au_fmt_ptr->flex_au_setting_0 & AU_SETTING_MCRC_INV_MODE
                           ? EC_MCRC_INV_MODE  : 0)
                       |(au_fmt_ptr->flex_au_setting_0 & AU_SETTING_ECC_INV_MODE
                           ? EC_ECC_INV_MODE   : 0)
                       |(au_fmt_ptr->flex_au_setting_0 & AU_SETTING_FIT_2_PHY_PAGE
                           ? EC_FIT_2_PHY_PAGE : 0));

    ECU_Set_Ctl_Cfg7(au_fmt_ptr->ecu_hlba_strip_mode, au_fmt_ptr->ecu_hlba_mode, mpecc_en);

    if (au_fmt_ptr->meta_data_only) 
    {
        // For Meta Data Read only mode, need to set both host block size and ECU2Host ratio to 0.
        ECU_Set_Ctl_Cfg8(0);

        ECU_Set_Ctl_Cfg9(0);
    }
    else 
    {
        ECU_Set_Ctl_Cfg8(au_fmt_ptr->host_sector_size);

        ECU_Set_Ctl_Cfg9(au_fmt_ptr->ecu2host_ratio);
    }

    ECU_Set_Ctl_Cfg10(au_fmt_ptr->meta_size);

    ECU_Set_Ctl_Cfg13((scr_user_seed_src << EC_REG_SCR_USER_SEED_SRC_SHIFT) |
                      (scr_user_en ? EC_REG_SCR_USER_EN : 0) |
                      (scr_meta_inv_en ? EC_REG_SCR_META_INV_EN : 0) |
                      (scr_meta_seed_src << EC_REG_SCR_META_SEED_SRC_SHIFT) |
                      (scr_meta_en ? EC_REG_SCR_META_EN : 0));

    ECU_Set_Cfg1(au_mcrc_en, (u16)au_fmt_ptr->cw_per_au, au_fmt_ptr->two_level_en);

    ECU_Set_Cfg2(au_fmt_ptr->phy_page_size); //Only effective if FIT_2_PHY_PAGE is set.

    ECU_Set_Cfg3(meta_mcrc_en, au_fmt_ptr->meta_threshold, au_fmt_ptr->meta_t);

    ECU_Set_Cfg4(au_fmt_ptr->t_strong, au_fmt_ptr->t_weak);

    ECU_Set_Cfg5(au_fmt_ptr->threshold_strong, au_fmt_ptr->threshold_weak);

    //set different erase threshold based on meta read only or normal case
    if (au_fmt_ptr->meta_data_only) 
    {
        ECU_Set_Cfg6(au_fmt_ptr->meta_t);
    }
    else 
    {
        ECU_Set_Cfg6(au_fmt_ptr->erase_threshold_weak);
    }


}

void 
EC_Calc_Au_Format_Cfg(flex_au_fmt* au_fmt_ptr, ec_nvcfg_t* ec_nvcfg_ptr)
{
    int meta_mcrc_en = (au_fmt_ptr->flex_au_setting_0 & AU_SETTING_META_MCRC_EN) != 0;
    int au_mcrc_en   = (au_fmt_ptr->flex_au_setting_0 & AU_SETTING_AU_MCRC_EN) != 0;
    int meta_ecc_en = (au_fmt_ptr->flex_au_setting_0 & AU_SETTING_META_ECC_EN) != 0;
    int aux_meta_sel = (au_fmt_ptr->aux_size != 0);



    if (aux_meta_sel) 
    { //if aux is selected
        meta_ecc_en = 0;
        meta_mcrc_en = 0;
    }

    if(au_fmt_ptr->meta_size == 0)
    {
    	meta_mcrc_en = 0;
	meta_ecc_en = 0;
    }
	
    au_fmt_ptr->encoded_ecc_au_meta_read_only_sz = 8 * (4 * meta_mcrc_en + au_fmt_ptr->meta_size);
    au_fmt_ptr->encoded_ecc_au_meta_read_only_sz += meta_ecc_en * au_fmt_ptr->meta_t * 15L;    
    au_fmt_ptr->encoded_ecc_au_meta_read_only_sz += 63;        // for 8 byte alignment
    au_fmt_ptr->encoded_ecc_au_meta_read_only_sz >>= 6;        // bits -> 64 bits
    au_fmt_ptr->encoded_ecc_au_meta_read_only_sz <<= 3;        // 64 bits -> bytes

    //au_fmt_ptr->encoded_page_meta_read_only_sz = 
        //au_fmt_ptr->encoded_ecc_au_meta_read_only_sz << ec_nvcfg_ptr->nr_ecc_au_per_page_shift;  // calculate final encoded page meta read only size
    au_fmt_ptr->encoded_page_meta_read_only_sz = 
        au_fmt_ptr->encoded_ecc_au_meta_read_only_sz * au_fmt_ptr->page_au_ratio;

    au_fmt_ptr->encoded_ecc_au_sz = 8 * (4 * (meta_mcrc_en + au_mcrc_en) + au_fmt_ptr->aux_size + 
                                    au_fmt_ptr->host_sector_size * au_fmt_ptr->ecu2host_ratio + au_fmt_ptr->meta_size);
    au_fmt_ptr->encoded_ecc_au_sz += (au_fmt_ptr->meta_size ? meta_ecc_en * au_fmt_ptr->meta_t * 15L : 0);
    au_fmt_ptr->encoded_ecc_au_sz += (((au_fmt_ptr->two_level_en) && (au_fmt_ptr->cw_per_au > 1)) ?
                                         (au_fmt_ptr->t_strong + (au_fmt_ptr->cw_per_au - 1) * au_fmt_ptr->t_weak) * 15 :
                                      au_fmt_ptr->cw_per_au * au_fmt_ptr->t_weak * 15);
    au_fmt_ptr->encoded_ecc_au_sz += 63;              // for 8 byte alignment
    au_fmt_ptr->encoded_ecc_au_sz >>= 6;                               
    au_fmt_ptr->encoded_ecc_au_sz <<= 3;
                                       
    //au_fmt_ptr->encoded_page_sz = au_fmt_ptr->encoded_ecc_au_sz << ec_nvcfg_ptr->nr_ecc_au_per_page_shift;  // calculate final encoded page size
    au_fmt_ptr->encoded_page_sz = au_fmt_ptr->encoded_ecc_au_sz * au_fmt_ptr->page_au_ratio;
}


int 
EC_Set_Flexible_Au(u8 au_format_no, ec_nvcfg_t* ec_nvcfg_ptr)
{
    flex_au_fmt* au_fmt_ptr = &(_supported_au_fmt[au_format_no]);
    u32 au_sz;
    
    au_fmt_ptr->phy_page_size = ec_nvcfg_ptr->page_sz;

    au_sz = ec_nvcfg_ptr->page_sz / au_fmt_ptr->page_au_ratio;

    //use 1-level cw if AU size is less than or equal to 2048 bytes. otherwise, use 2-level cw
    au_fmt_ptr->two_level_en = (au_sz > 2048) ? 1 : 0;

    au_fmt_ptr->ecu2host_ratio = au_sz / au_fmt_ptr->host_sector_size;

    // 1 codeword for 1-level. 2 codewords for au size = 4096 bytes, 3 codewords for au size >= 8K.
    if (au_fmt_ptr->two_level_en) 
    {
        au_fmt_ptr->cw_per_au = (au_sz > 4096) ? 3 : 2;
    }
    else 
    {
        au_fmt_ptr->cw_per_au = 1;
    }

	//au_fmt_ptr->two_level_en = 0;
	//au_fmt_ptr->cw_per_au = 1;

    /****************************/
    //to be added in future: check spi to see if there is any parameter user wants to set
    /****************************/

    if (EC_Calc_Ecc_Power(au_fmt_ptr, ec_nvcfg_ptr) != 0) 
    {
        //if au spare size is not enough for ecc, return failure
        return -1;
    }
    //set au format structure. 
    au_fmt_ptr->threshold_strong = au_fmt_ptr->t_strong / STRONG_THRESHOLD_T_RATIO;
    au_fmt_ptr->threshold_weak = au_fmt_ptr->t_weak / WEAK_THRESHOLD_T_RATIO + 1;
    au_fmt_ptr->erase_threshold_weak = au_fmt_ptr->t_weak;
    au_fmt_ptr->meta_threshold = au_fmt_ptr->meta_t > 3 ? au_fmt_ptr->meta_t - 3 : au_fmt_ptr->meta_t;

    //set flexible au format based on the obtained parameters
    EC_Set_Au_Format_Ptr(au_format_no);

    //update ecu ctrl cfg register based on au format structure
    EC_Set_Au_Format_Cfg(au_fmt_ptr);	

    //calculate other parameter
    EC_Calc_Au_Format_Cfg(au_fmt_ptr, ec_nvcfg_ptr);

    if (au_fmt_ptr->encoded_page_sz > ec_nvcfg_ptr->full_page_sz) 
    {
        //not enough space for encoded page
        return -1;
    }


    return 0;
}


int 
EC_Input_Flexible_Au(flex_au_fmt* au_fmt_ptr, ec_nvcfg_t* ec_nvcfg_ptr)
{

    //should not exceed the maximum allowed format number
    if (au_format_index > 31) 
    {
        return 0xFF;
    }

    //allocate memory for the new au format
    memory_copy(&(_supported_au_fmt[au_format_index]),au_fmt_ptr,sizeof(flex_au_fmt));

    if (EC_Set_Flexible_Au(au_format_index, ec_nvcfg_ptr) != 0) 
    {
        return 0xFF;
    }
    else 
    {
        return au_format_index++;
    }
}

void 
Init_ECU(u32 page_sz, u32 ecc_au_sz)
{
    int i;    

    flex_au_fmt _supported_au_fmt[] =
    {
    //flex_au_setting_0, flex_au_setting_1, host_sector_size, meta_size, aux_size, meta_data_only
    //t_strong, t_weak, meta_t, page_au_ratio, ecu_hlba_strip_mode, ecu_hlba_mode
  #ifdef AUXILIARY_SUPPORT
    { 0x6a, 0x20, 512,    0,      12,    0,
      0,    0,     0,    PARATIO,      0,    0},
  #else
    { 0xec, 0x00, 512,    metasize,      0,    0,
      0,    0,      metat,    PARATIO,      0,    0},
  #endif
    //{ 0xec, 0x00, 512,    metasize,      0,    0,
      //0,    0,      6,    PARATIO,      0,    0},
    { 0xec, 0x00, 512,    metasize,      0,    0,
      0,    0,      metat,    8,      0,    0},
    { 0xec, 0x00, 512,    12,      0,    0,
      0,    6,      6,    8,      0,    0},
    //{ 0x8f, 0x00, 512,    4,      0,    0,//ec
      //0,    0,      6,    1,      0,    0},
    //{ 0x8F, 0x00, 512,    4,      0,    0,
      //0,    0,      6,    2,      0,    0},
    //{ 0x8F, 0x00, 512,    4,      0,    0,
      //0,    0,      6,    4,      0,    0},
    { 0x8F, 0x00, 512,    4,      0,    0,
      0,    0,      1,    8,      0,    0},
    // The entry 4 ~ 7 are for META read only mode. Please notes that
    // (0, 4) (1, 5) (2, 6) (4,7) are used in pair.
    // For meta data read only mode, the host sector size and ecu2host_ratio must be 0.
    { 0xec, 0x00, 512,    12,      0,    1,
      0,    6,      6,    8,      0,    0},
    //{ 0x8F, 0x00, 512,    4,      0,    1,
      //0,    0,      6,    1,      0,    0},
    { 0x8F, 0x00, 512,    4,      0,    1,
      0,    0,      6,    2,      0,    0},
    { 0x8F, 0x00, 512,    4,      0,    1,
      0,    0,      6,    4,      0,    0},
    { 0x8F, 0x00, 512,    4,      0,    1,
      0,    0,      1,    8,      0,    0},

    { 0x68, 0x00, 512,    0,      4,    0,
      0,    0,     0,    PARATIO,      0,    0},
    { 0x0B, 0x00, 512,    0,      4,    0,
      0,    0,     12,    2,      0,    0},
    { 0x0B, 0x00, 512,    0,      4,    0,
      0,    0,     12,    4,      0,    0},
    { 0x0B, 0x00, 512,    0,      4,    0,
      0,    0,      1,    8,      0,    0},
    };

    //structure for input to ecu
    ec_nvcfg_t ec_nvcfg;

    EC_Reset();     

	//general settings
    REG16_WRITE(EC_REG_CNTL_CFG2, EC_REG_DEFAULT_CNTL_CFG2);    
    //REG16_WRITE(EC_REG_CNTL_CFG3, BIT_5|BIT_3);
    REG16_WRITE(EC_REG_CNTL_CFG5, EC_REG_DEFAULT_CNTL_CFG5);  
    
    ec_nvcfg.full_page_sz = nvcfg.full_page_sz;
    ec_nvcfg.page_sz = nvcfg.page_sz;
    ec_nvcfg.nr_ecc_au_per_page_shift = nvcfg.nr_ecc_au_per_page_shift;

    au_format_index = 0;	
    for (i = 0; i < AU_FORMAT_CNT; i ++) 
    {
        EC_Input_Flexible_Au(&_supported_au_fmt[i], &ec_nvcfg);
            

    }
}

void
FC_Seq_Wait(void)
{
    while (REG16_READ(SEQ_REG_CONTROL_1) & (SEQ_BUSY|SEQ_RESET)) 
    {
        DelayUS(100);   // wait for sequencer ready
    }
}

void
FC_Seq_Reset(void)
{
    u16 tmp;

    tmp = REG16_READ(SEQ_REG_CONTROL_1);
    tmp |= SEQ_RESET;
    REG16_WRITE(SEQ_REG_CONTROL_1, tmp);

    FC_Seq_Wait();
}

void
FC_Seq_Set_Pa_Ratio(u32 ratio)
{
    u16 tmp = REG16_READ(SEQ_REG_CONFIG_3);
 
    tmp &= ~(SEQ_PA_RATIO_MASK << SEQ_PA_RATIO_BIT_OFF);
    tmp |= ((((u16) ratio) & SEQ_PA_RATIO_MASK) << SEQ_PA_RATIO_BIT_OFF);
    
    REG16_WRITE(SEQ_REG_CONFIG_3, tmp);
}

void
FC_Seq_Set_Row_Increment(u32 row_increment)
{
    REG32_WRITE(SEQ_REG_ROW_INCREMENT, row_increment);
}

void
FC_Seq_Set_Active_Trks(u32 nr_max_trks)
{
    REG16_WRITE(SEQ_REG_CONFIG_4, nr_max_trks);
}

void
FC_Seq_Enable(int enable)
{
    u16 tmp;

    FC_Seq_Wait();

    tmp = REG16_READ(SEQ_REG_CONTROL_1);
    if (enable) 
    {
        tmp |= SEQ_ENABLE;
    }
    else 
    {
        tmp &= ~SEQ_ENABLE;
    }
    REG16_WRITE(SEQ_REG_CONTROL_1, tmp);

    FC_Seq_Wait();
}

void
FC_Seq_Set_Desc_Loop_Count(u32 desc_loop)
{
    REG16_WRITE(SEQ_REG_DES_LOOP_CNT, desc_loop);
}

#ifdef AUXILIARY_SUPPORT
void
FC_Seq_Aux_Enable(int enable, u32 aux_size)
{
    u16 tmp = REG16_READ(SEQ_REG_CONFIG_3);

    tmp &= ~(SEQ_AUX_SIZE_MASK << SEQ_AUX_SIZE_BIT_OFF);
    tmp &= ~SEQ_TWO_LBA_EN;
    if (enable) {
        tmp |= (SEQ_AUX_META_SEL | ((aux_size & SEQ_AUX_SIZE_MASK) << SEQ_AUX_SIZE_BIT_OFF));
    }
    else {
        tmp &= ~(SEQ_AUX_META_SEL);
    }
    
    REG16_WRITE(SEQ_REG_CONFIG_3, tmp);
}
#endif

void 
FC_Seq_Cfg(u32 page_sz)
{
//    dbg_assert(nvhwcfg.encoded_page_sz);    // run ecu_cfg first where encoded_page_sz is initialized.    
    FC_Set_Access_Mode(FC_ACCESS_MODE_SEQ);
    FC_Seq_Reset();//???????????
//  should set seq_aux_enable after assigning au_format_no   
#ifdef AUXILIARY_SUPPORT
	FC_Seq_Aux_Enable(1,3);// 12byte aux
#endif

    /*
     * It might be easier to under that PA_RATIO is the ratio between AU size
     * and descriptor transfer size. (from Hyunsuk Shin)
     */
    FC_Seq_Set_Pa_Ratio((page_sz >> nvcfg.ecc_au_sz_shift) >> 1);//no use

    FC_Seq_Set_Row_Increment(1);               // TBD

    FC_Seq_Set_Active_Trks(8);

    FC_Seq_Enable(1);
    //FC_Seq_Set_Desc_Loop_Count(0x8000); //no use       // set as a large value so I will never get OP_DONE interrupt
}

void
FC_Seq_Spm_Program_Des_Fifo_Dw(u32 des_fifo_data)
{
    //dbg_printf("Address %x DW: %x \n", des_fifo_pro_dw_ptr, des_fifo_data);    
    *des_fifo_pro_dw_ptr = des_fifo_data;
    //dbg_printf("Address %x DW: %x \n", des_fifo_pro_dw_ptr, *des_fifo_pro_dw_ptr);  
    
    des_fifo_pro_dw_ptr++;
    if (des_fifo_pro_dw_ptr > (u32 *)(DF_8BYTE_ALIGN_END)) 
    {
        des_fifo_pro_dw_ptr = (u32 *)DF_START;
    }
    return;
} /*End of spm_program_des_fifo_dw*/

void
FC_Seq_Set_Desc_Fifo_Count(u16 df_cnt)
{
    REG16_WRITE(SEQ_REG_DES_FIFO_CNT, df_cnt);
}

void
FC_Seq_Des_Program_Gen_Dummy(u32 trk_id, u32 fst_trk)
{
    u32 tmp_dw;

    /*Program 1st Dword of 1st parameter*/
    FC_Seq_Spm_Program_Des_Fifo_Dw(trk_id);

    tmp_dw =  (u32)((fst_trk) ? 1 : 0)  << CMD_DES_GEN_FD_BIT_OFF
            | (u32)((!fst_trk) ? 1 : 0)  << CMD_DES_GEN_LD_BIT_OFF
            | (u32)1L                   << CMD_DES_GEN_DV_BIT_OFF
            | (u32)CMD_DES_GEN_DES_TYPE << CMD_DES_GEN_DF_BIT_OFF
            | (u32)2L                   << CMD_DES_GEN_DES_TYPE_BIT_OFF
            | (u32)7L                   << CMD_DES_GEN_CH_BIT_OFF     //must be 0 or 1
            | (u32)7L                   << CMD_DES_GEN_DEV_BIT_OFF
            ;
    /*Program 2nd Dword of 1st parameter*/
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);

    /*Program 1st Dword of 2nd parameter*/
    /*We do not use the SET_PARAM not, so set zero*/
    FC_Seq_Spm_Program_Des_Fifo_Dw(0);

    /*Program 2nd Dword of 2nd parameter*/
    FC_Seq_Spm_Program_Des_Fifo_Dw(0);

    /*Program 1st Dword of 3th parameter*/
    FC_Seq_Spm_Program_Des_Fifo_Dw(0);

    tmp_dw =  (u32)1L << CMD_DES_GEN_OPT_2ND_CMD_CYC_OFF
            | (u32)1L << CMD_DES_GEN_OPT_1ST_CMD_CYC_OFF
            | (u32)3L << CMD_DES_GEN_OPT_ADR_TYP_BIT_OFF
            ;
    /*Program 2nd Dword of 3th parameter*/
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);

    /*Program 1st Dword of 4th parameter*/
    FC_Seq_Spm_Program_Des_Fifo_Dw(0);

    /*Program 2nd Dword of 4th parameter*/
    FC_Seq_Spm_Program_Des_Fifo_Dw(0);

    FC_Seq_Set_Desc_Fifo_Count(1);
} /*End of cmd_des_program_gen_dummy_des*/





void 
FC_Spm_Init_Pointers(void)
{
    /*Write pointer of programming command descriptor*/
    des_fifo_pro_dw_ptr = (u32 *)DF_START;
    /*INIT Descriptor FIFO pointer*/
    REG32_WRITE(SEQ_REG_DF_PTR, DF_START);

#ifdef AUXILIARY_SUPPORT
    /*Write pointer of inserting AUX insert data*/
    ai_fifo_ins_dw_ptr = (u32 *)AIF_START;
    /*Read pointer of extracting AUX data*/
    ae_fifo_rd_dw_ptr = (u32*)AEF_START;
    /*Read pointer of comparing AUX data*/
    ac_fifo_cmp_dw_ptr = (u32*)ACF_START;
    /*INIT AUX insert FIFO pointer*/
    REG32_WRITE(SEQ_REG_AUX_FIFO_INS_PTR, AIF_START);
    /*INIT AUX compare FIFO pointer*/
    REG32_WRITE(SEQ_REG_AUX_FIFO_CMP_PTR, ACF_START);
    /*INIT AUX extract FIFO pointer*/
    REG32_WRITE(SEQ_REG_AUX_FIFO_EXA_PTR, AEF_START);
#endif /*End of #ifdef AUXILIARY_SUPPORT*/

} /*End of spm_init_pointers*/

#ifdef AUXILIARY_SUPPORT
void
FC_Spm_Insert_Aux_Fifo_Dw(u32* aux_fifo_data_ptr, u32 aux_dw_nr)
{
    int i;

    for (i = 0; i < aux_dw_nr; i++) {
        *ai_fifo_ins_dw_ptr = aux_fifo_data_ptr[i];

        ai_fifo_ins_dw_ptr++;
        if (ai_fifo_ins_dw_ptr > (u32 *)AIF_END) {
            ai_fifo_ins_dw_ptr = (u32 *)AIF_START;
        }
    }
    return;
} /*End of spm_insert_aux_fifo_dw*/

void
FC_Spm_Insert_Aux_Fifo_Lw(u32 aux_fifo_data_0, u32 aux_fifo_data_1)
{
    FC_Spm_Insert_Aux_Fifo_Dw(&aux_fifo_data_0, 1);
    FC_Spm_Insert_Aux_Fifo_Dw(&aux_fifo_data_1, 1);
    return;
} /*End of spm_insert_aux_fifo_lw*/

void
FC_Spm_Insert_Aux_Fifo_3dw(
                       u32 aux_fifo_data_0,
                       u32 aux_fifo_data_1,
                       u32 aux_fifo_data_2
                       )
{
    FC_Spm_Insert_Aux_Fifo_Dw(&aux_fifo_data_0, 1);
    FC_Spm_Insert_Aux_Fifo_Dw(&aux_fifo_data_1, 1);
    FC_Spm_Insert_Aux_Fifo_Dw(&aux_fifo_data_2, 1);
    return;
} /*End of spm_insert_aux_fifo_3dw*/

u32
FC_Spm_Extract_Aux_Fifo_Dw(void)
{
    u32 aux_data;
	
    aux_data = REG32_READ(ae_fifo_rd_dw_ptr);

    ae_fifo_rd_dw_ptr ++;
    if (ae_fifo_rd_dw_ptr > (u32 *)AEF_END) {
        ae_fifo_rd_dw_ptr = (u32 *)AEF_START;
    }

    return aux_data;
} /*End of spm_extract_aux_fifo_dw*/

u64
FC_Spm_Extract_Aux_Fifo_Lw(void)
{
    u32 aux_lw_lo = FC_Spm_Extract_Aux_Fifo_Dw();
    return ((u64)FC_Spm_Extract_Aux_Fifo_Dw() << 32 | aux_lw_lo);
} /*End of spm_extract_aux_fifo_lw*/

void
FC_Spm_Extract_Aux_Fifo_3dw(
                        u32 *aux_fifo_data_0,
                        u32 *aux_fifo_data_1,
                        u32 *aux_fifo_data_2
                        )
{
    *aux_fifo_data_0 = FC_Spm_Extract_Aux_Fifo_Dw();
    *aux_fifo_data_1 = FC_Spm_Extract_Aux_Fifo_Dw();
    *aux_fifo_data_2 = FC_Spm_Extract_Aux_Fifo_Dw();
    return; 
} /*End of spm_extract_aux_fifo_3dw*/

void 
FC_Spm_Prepare_Cmp_Fifo(
                         u32 *aux_fifo_data_ptr,
                         u32 aux_dw_nr
                         )
{
    int i;

    for (i = 0; i < aux_dw_nr; i++) {
        *ac_fifo_cmp_dw_ptr = aux_fifo_data_ptr[i];

        ac_fifo_cmp_dw_ptr ++;
        if (ac_fifo_cmp_dw_ptr > (u32 *)ACF_END) {
            ac_fifo_cmp_dw_ptr = (u32 *)ACF_START;
        }
    }

    return;
} /*End of spm_prepare_cmp_fifo*/

#endif

void 
FC_Spm_Init(void)
{    
    /*INIT Descriptor FIFO*/
    REG32_WRITE(SEQ_REG_DF_START_ADDR, DF_START);
    REG32_WRITE(SEQ_REG_DF_END_ADDR, DF_END);

    /*INIT Track memory*/
    REG32_WRITE(SEQ_REG_TRKM_START, TRKM_START);

#ifdef AUXILIARY_SUPPORT
    /*INIT AUX insert FIFO*/
    REG32_WRITE(SEQ_REG_AUX_FIFO_INS_START, AIF_START);
    REG32_WRITE(SEQ_REG_AUX_FIFO_INS_END, AIF_END);

    /*INIT AUX compare FIFO*/
    REG32_WRITE(SEQ_REG_AUX_FIFO_CMP_START, ACF_START);
    REG32_WRITE(SEQ_REG_AUX_FIFO_CMP_END, ACF_END);

    /*INIT AUX extract FIFO*/
    REG32_WRITE(SEQ_REG_AUX_FIFO_EXA_START, AEF_START);
    REG32_WRITE(SEQ_REG_AUX_FIFO_EXA_END, AEF_END);
#endif /*End of #ifdef AUXILIARY_SUPPORT*/

    /*INIT AU Encode FIFO*/
    REG32_WRITE(SEQ_REG_AENC_START, AENC_START);
    REG16_WRITE(SEQ_REG_AENC_SIZE, AENC_SIZE);

    /*INIT AU Decode FIFO*/
    REG32_WRITE(SEQ_REG_ADEC_START, ADEC_START);
    REG16_WRITE(SEQ_REG_ADEC_SIZE, ADEC_SIZE);
    /*
     *Initializes pointers of descriptor, track, auxiliary
     *inst/comp/extr FIFOs.
     */
    FC_Spm_Init_Pointers();
} /*End of spm_init*/

void
FC_Seq_Set_Trk_Conf(u32 trk_conf_bits)
{
    u16 tmp = REG16_READ(SEQ_REG_CONFIG_1);
 
    tmp &= ~(SEQ_TRK_CONF_MASK << SEQ_TRK_CONF_BIT_OFF);
    tmp |= (((u16) trk_conf_bits) << SEQ_TRK_CONF_BIT_OFF);
    tmp |= (1 << 15);//int out of order
    
    REG16_WRITE(SEQ_REG_CONFIG_1, tmp);

}

void
FC_Seq_Write_Irq_Status(u16 v)
{
    REG16_WRITE(SEQ_REG_IRQ_STATUS, v);
}

void
FC_Seq_Write_Irq_Mask(u16 v)
{
    REG16_WRITE(SEQ_REG_IRQ_MASK, v);
}

void
FC_Fct_Write_Irq_Status(u16 status)
{
    REG16_WRITE(FCT_REG_IRQ_STATUS, status);
}

void
FC_Fct_Write_Irq_Enable(u16 mask)
{
    REG16_WRITE(FCT_REG_IRQ_EN, mask);
}

void 
Init_Track()
{	
    FC_Spm_Init();      

    /*B[14:12] of sequencer configuration 1*/
    FC_Seq_Set_Trk_Conf(TRK_CONF);//max tid = 31, max descriptor = 255
    /*
     * There are 3 levels control to the interrupt. The 1st level is of course
     * the CPU level control, which is handled by the system ISR framework. The
     * second level is the flash controller interrupt control (R5ba00) and the
     * third level is the sequencer interrupt control (R5b014).
     */
    FC_Seq_Write_Irq_Status(0xffff);
    // interrupt is enable when the bit is clear
    FC_Seq_Write_Irq_Mask(~SEQ_HANDLED_IRQS);

    FC_Fct_Write_Irq_Status(0xffff);
    // interrupt is enable when the bit is set
    FC_Fct_Write_Irq_Enable(FCT_INT_SEQ);

    //sys_isr_register(&fct_intr_cb,INT_MAP_FCT,trkmgr_isr);
    //MainIRQIntEn |= INT_MAP_FCT;
    //REG32_WRITE(CPUC_RW_MAINIRQMASK, MainIRQIntEn);
    //rCPU.cpuIntrEnable.bits.servoInt = 1;
}

void ECU_Set_Bypass()
{
	EC_Set_Au_Format_Ptr(0);
	
	REG16_SET_BITS(EC_REG_CNTL_CFG5, EC_ECC_DEC_BYPASS_EN);
	REG16_CLEAR_BITS(EC_REG_CNTL_CFG4, EC_META_READ_SKIP); 
	REG16_CLEAR_BITS(EC_REG_CNTL_CFG4, EC_META_AUX_RCVR); 
	REG16_CLEAR_BITS(EC_REG_CNTL_CFG4, EC_ERASE_PAGE_DET_ONLY); 
	REG16_CLEAR_BITS(EC_REG_CNTL_CFG5, EC_FIT_2_PHY_PAGE); 
}

u8 FC_Get_Tid(void)
{
	u8 tid;

	while(1)
	{
		for(tid=0;tid<32;tid++)
		{
			if(tid_sts[tid] == 0)
			{
				tid_sts[tid] = 1;
				tid_error[tid] = 0;
				return tid;
			}
		}
	}
	//if(tid == 32)
		//return 0xff;
}

u8 FC_Get_Fs(u8 tid)
{
	u8 no;

	while(1)
	{
		for(no=0;no<MAXSEG;no++)
		{
			if(fs_sts[no] == 0)
			{
				fs_sts[no] = 1;
				trk_seg[tid].id = tid;
				trk_seg[tid].rw = 1;//write cmd
				trk_seg[tid].fs_num = no;
				return no;
			}
		}
	}
	//if(tid == 32)
		//return 0xff;
}

u8 FC_Get_Es(u8 tid)
{
	u8 no;

	while(1)
	{
		for(no=0;no<MAXSEG;no++)
		{
			if(es_sts[no] == 0)
			{
				es_sts[no] = 1;
				trk_seg[tid].id = tid;
				trk_seg[tid].rw = 2;//read cmd
				trk_seg[tid].es_num = no;
				return no;
			}
		}
	}
	//if(tid == 32)
		//return 0xff;
}



void FC_Seq_Program_Desc_Gen_Dummy(u8 id)
{
	FC_Seq_Des_Program_Gen_Dummy(id, FIRST_DESCRIPTOR);
	FC_Seq_Des_Program_Gen_Dummy(id, LAST_DESCRIPTOR);
}

#if 0
void FC_Seq_Cmd_Des_Program_Gen_Des(cmd_des_gen_info_ctx_t *desc_info)
{
    u32 tmp_dw;

    /*Program 1st Dword of 1st parameter*/
    tmp_dw = (u32)(desc_info->au_cnt-1)<<CMD_DES_GEN_AU_NUM_BIT_OFF
			|(u32)desc_info->tid;
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);	
    /*Program 2nd Dword of 1st parameter*/
    tmp_dw =  (u32)((desc_info->fst_des) ? 1 : 0)  << CMD_DES_GEN_FD_BIT_OFF
            | (u32)((desc_info->lst_des) ? 1 : 0)  << CMD_DES_GEN_LD_BIT_OFF
            | (u32)(desc_info->rdy_bit)  << CMD_DES_GEN_READY_BIT_OFF
            | (u32)1L                   << CMD_DES_GEN_DV_BIT_OFF
            | (u32)0L                   << CMD_DES_GEN_PA_BIT_OFF     //from ecu       
            | (u32)CMD_DES_GEN_DES_TYPE << CMD_DES_GEN_DF_BIT_OFF
            | (u32)(desc_info->des_cmd)                   << CMD_DES_GEN_DES_TYPE_BIT_OFF
            | (u32)(desc_info->ch)                   << CMD_DES_GEN_CH_BIT_OFF
            | (u32)(desc_info->device)                   << 0
            ;    
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);

	

    /*Program 1st Dword of 2nd parameter*/
    /*We do not use the SET_PARAM not, so set zero*/
    FC_Seq_Spm_Program_Des_Fifo_Dw(0);
    /*Program 2nd Dword of 2nd parameter*/
    tmp_dw = (u32)(desc_info->au_format_no) << CMD_DES_GEN_AU_FORMAT_BIT_OFF;
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);

	

    /*Program 1st Dword of 3th parameter*/
    tmp_dw = (u32)(desc_info->col_add) << 0
    			|(u32)(desc_info->encoded_ecc_au_sz*desc_info->au_cnt) <<CMD_DES_GEN_XF_COUNT_BIT_OFF;
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);
    /*Program 2nd Dword of 3th parameter*/
    tmp_dw =  (u32)0L << 24
    	     |(u32)0L << 23
    	     |(u32)(desc_info->wait_bef_add) << 22
    	     |(u32)(desc_info->iss_enh) << 20
    	     |(u32)(desc_info->iss_add_enh) << 18
    	     |(u32)(desc_info->iss_00) << 17
    	     |(u32)(desc_info->iss_add) << 15
    	     |(u32)(desc_info->fnl_status) << 13
    	     |(u32)(desc_info->cmd_00) << 12
    	     |(u32)(desc_info->scd_cmd_off) << 11    	     
            | (u32)(desc_info->fst_cmd_off) << 10
            |(u32)(desc_info->status_add) << 9
            |(u32)(desc_info->status_poll_time) << 7
            |(u32)(desc_info->status_wait_time) << 3
            | (u32)(desc_info->add_type) << 0
            ;    
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);

	

    /*Program 1st Dword of 4th parameter*/
    tmp_dw = (u32)(desc_info->row_add);
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);
    /*Program 2nd Dword of 4th parameter*/
    tmp_dw = (u32)(desc_info->fail_bit)<<0
              |(u32)(desc_info->scmd)<<CMD_DES_GEN_SCMD_BIT_OFF
              |(u32)(desc_info->cmd2)<<CMD_DES_GEN_CMD2_BIT_OFF
              |(u32)(desc_info->cmd1)<<CMD_DES_GEN_CMD1_BIT_OFF;
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);

    FC_Seq_Set_Desc_Fifo_Count(1);
} /*End of cmd_des_program_gen_dummy_des*/


void FC_Seq_Program_Desc_Gen_Erase_Block()
{
    cmd_des_gen_info_ctx_t cmd_des_pro_info;
    
    memory_set(&cmd_des_pro_info, 0, sizeof(cmd_des_gen_info_ctx_t));

    FC_Seq_Des_Program_Gen_Dummy(0, FIRST_DESCRIPTOR);

	cmd_des_pro_info.au_cnt = 0;
	cmd_des_pro_info.tid=0;
	cmd_des_pro_info.fst_des=0;
	cmd_des_pro_info.lst_des=0;

	cmd_des_pro_info.rdy_bit=6;
	cmd_des_pro_info.des_cmd=2;//0 for read 1 for program 2 for erase
	cmd_des_pro_info.ch=0;
	cmd_des_pro_info.device=0;
	
	cmd_des_pro_info.col_add=0;
	cmd_des_pro_info.encoded_ecc_au_sz=_supported_au_fmt[0].encoded_ecc_au_sz;

	cmd_des_pro_info.au_format_no=0;
	
	cmd_des_pro_info.wait_bef_add=0;
	cmd_des_pro_info.iss_enh=0;
	cmd_des_pro_info.iss_add_enh=0;
	cmd_des_pro_info.iss_00=0;
	
	cmd_des_pro_info.fnl_status=0;
	cmd_des_pro_info.cmd_00=0;
	cmd_des_pro_info.scd_cmd_off=0;
	cmd_des_pro_info.fst_cmd_off=0;

	cmd_des_pro_info.status_add=0;
	cmd_des_pro_info.status_poll_time=1;
	cmd_des_pro_info.status_wait_time=1;
	cmd_des_pro_info.add_type=2;

	cmd_des_pro_info.row_add=0;

	cmd_des_pro_info.fail_bit=0;
	cmd_des_pro_info.scmd=0x70;
	cmd_des_pro_info.cmd2=0xd0;
	cmd_des_pro_info.cmd1=0x60;    
  
    FC_Seq_Cmd_Des_Program_Gen_Des(&cmd_des_pro_info);

    FC_Seq_Des_Program_Gen_Dummy(0, LAST_DESCRIPTOR);
} /* End of program_desc */

void FC_Seq_Program_Desc_Gen_Read_Page()
{
    cmd_des_gen_info_ctx_t cmd_des_pro_info;
    
    memory_set(&cmd_des_pro_info, 0, sizeof(cmd_des_gen_info_ctx_t));

    FC_Seq_Des_Program_Gen_Dummy(0, FIRST_DESCRIPTOR);

	cmd_des_pro_info.au_cnt = 2;
	cmd_des_pro_info.tid=0;
	cmd_des_pro_info.fst_des=0;
	cmd_des_pro_info.lst_des=0;

	cmd_des_pro_info.rdy_bit=6;
	cmd_des_pro_info.des_cmd=0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info.ch=0;
	cmd_des_pro_info.device=0;
	
	cmd_des_pro_info.col_add=0;
	cmd_des_pro_info.encoded_ecc_au_sz=_supported_au_fmt[0].encoded_ecc_au_sz;

	cmd_des_pro_info.au_format_no=0;
	
	cmd_des_pro_info.wait_bef_add=0;
	cmd_des_pro_info.iss_enh=0;
	cmd_des_pro_info.iss_add_enh=0;
	cmd_des_pro_info.iss_00=0;
	
	cmd_des_pro_info.fnl_status=0;
	cmd_des_pro_info.cmd_00=0;
	cmd_des_pro_info.scd_cmd_off=0;
	cmd_des_pro_info.fst_cmd_off=0;

	cmd_des_pro_info.status_add=0;
	cmd_des_pro_info.status_poll_time=1;
	cmd_des_pro_info.status_wait_time=1;
	cmd_des_pro_info.add_type=0;

	cmd_des_pro_info.row_add=0;

	cmd_des_pro_info.fail_bit=0;
	cmd_des_pro_info.scmd=0x70;
	cmd_des_pro_info.cmd2=0x30;
	cmd_des_pro_info.cmd1=0x00;    
  
    FC_Seq_Cmd_Des_Program_Gen_Des(&cmd_des_pro_info);

    FC_Seq_Des_Program_Gen_Dummy(0, LAST_DESCRIPTOR);
} /* End of program_desc */

void FC_Seq_Program_Desc_Gen_Program()
{
    cmd_des_gen_info_ctx_t cmd_des_pro_info;
    
    memory_set(&cmd_des_pro_info, 0, sizeof(cmd_des_gen_info_ctx_t));

    FC_Seq_Des_Program_Gen_Dummy(0, FIRST_DESCRIPTOR);	

	cmd_des_pro_info.au_cnt = 2;
	cmd_des_pro_info.tid=0;
	cmd_des_pro_info.fst_des=0;
	cmd_des_pro_info.lst_des=0;

	cmd_des_pro_info.rdy_bit=6;
	cmd_des_pro_info.des_cmd=1;//0 for read 1 for program 2 for erase
	cmd_des_pro_info.ch=0;
	cmd_des_pro_info.device=0;
	
	cmd_des_pro_info.col_add=0;
	cmd_des_pro_info.encoded_ecc_au_sz=_supported_au_fmt[0].encoded_ecc_au_sz;

	cmd_des_pro_info.au_format_no=0;
	
	cmd_des_pro_info.wait_bef_add=0;
	cmd_des_pro_info.iss_enh=0;
	cmd_des_pro_info.iss_add_enh=0;
	cmd_des_pro_info.iss_00=0;
	
	cmd_des_pro_info.fnl_status=0;
	cmd_des_pro_info.cmd_00=0;
	cmd_des_pro_info.scd_cmd_off=0;
	cmd_des_pro_info.fst_cmd_off=0;

	cmd_des_pro_info.status_add=0;
	cmd_des_pro_info.status_poll_time=1;
	cmd_des_pro_info.status_wait_time=0x01;
	cmd_des_pro_info.add_type=0;

	cmd_des_pro_info.row_add=0;

	cmd_des_pro_info.fail_bit=0;
	cmd_des_pro_info.scmd=0x70;
	cmd_des_pro_info.cmd2=0x10;
	cmd_des_pro_info.cmd1=0x80;    
  
    FC_Seq_Cmd_Des_Program_Gen_Des(&cmd_des_pro_info);

    FC_Seq_Des_Program_Gen_Dummy(0, LAST_DESCRIPTOR);
} /* End of program_desc */


void FC_Seq_Program_Desc_Gen_Program_Random_Data_In()
{
    cmd_des_gen_info_ctx_t cmd_des_pro_info;
    
    memory_set(&cmd_des_pro_info, 0, sizeof(cmd_des_gen_info_ctx_t));

    FC_Seq_Des_Program_Gen_Dummy(0, FIRST_DESCRIPTOR);

	cmd_des_pro_info.au_cnt = 0;
	cmd_des_pro_info.tid=0;
	cmd_des_pro_info.fst_des=0;
	cmd_des_pro_info.lst_des=0;

	cmd_des_pro_info.rdy_bit=6;
	cmd_des_pro_info.des_cmd=2;//0 for read 1 for program 2 for erase
	cmd_des_pro_info.ch=0;
	cmd_des_pro_info.device=0;
	
	cmd_des_pro_info.col_add=0;
	cmd_des_pro_info.encoded_ecc_au_sz=_supported_au_fmt[0].encoded_ecc_au_sz;

	cmd_des_pro_info.au_format_no=0;
	
	cmd_des_pro_info.wait_bef_add=0;
	cmd_des_pro_info.iss_enh=0;
	cmd_des_pro_info.iss_add_enh=0;
	cmd_des_pro_info.iss_00=0;
	
	cmd_des_pro_info.fnl_status=0;
	cmd_des_pro_info.cmd_00=0;
	cmd_des_pro_info.scd_cmd_off=1;
	cmd_des_pro_info.fst_cmd_off=0;

	cmd_des_pro_info.status_add=0;
	cmd_des_pro_info.status_poll_time=0;
	cmd_des_pro_info.status_wait_time=0;
	cmd_des_pro_info.add_type=0;

	cmd_des_pro_info.row_add=256;

	cmd_des_pro_info.fail_bit=0;
	cmd_des_pro_info.scmd=0x00;
	cmd_des_pro_info.cmd2=0x00;
	cmd_des_pro_info.cmd1=0x80;    
  
    FC_Seq_Cmd_Des_Program_Gen_Des(&cmd_des_pro_info);

	cmd_des_pro_info.au_cnt = 2;
	cmd_des_pro_info.tid=0;
	cmd_des_pro_info.fst_des=0;
	cmd_des_pro_info.lst_des=0;

	cmd_des_pro_info.rdy_bit=6;
	cmd_des_pro_info.des_cmd=1;//0 for read 1 for program 2 for erase
	cmd_des_pro_info.ch=0;
	cmd_des_pro_info.device=0;
	
	cmd_des_pro_info.col_add=0;
	cmd_des_pro_info.encoded_ecc_au_sz=_supported_au_fmt[0].encoded_ecc_au_sz;

	cmd_des_pro_info.au_format_no=0;
	
	cmd_des_pro_info.wait_bef_add=0;
	cmd_des_pro_info.iss_enh=0;
	cmd_des_pro_info.iss_add_enh=0;
	cmd_des_pro_info.iss_00=0;
	
	cmd_des_pro_info.fnl_status=0;
	cmd_des_pro_info.cmd_00=0;
	cmd_des_pro_info.scd_cmd_off=0;
	cmd_des_pro_info.fst_cmd_off=0;

	cmd_des_pro_info.status_add=0;
	cmd_des_pro_info.status_poll_time=1;
	cmd_des_pro_info.status_wait_time=1;
	cmd_des_pro_info.add_type=1;

	cmd_des_pro_info.row_add=256;

	cmd_des_pro_info.fail_bit=0;
	cmd_des_pro_info.scmd=0x70;
	cmd_des_pro_info.cmd2=0x10;
	cmd_des_pro_info.cmd1=0x85;    
  
    FC_Seq_Cmd_Des_Program_Gen_Des(&cmd_des_pro_info);

    FC_Seq_Des_Program_Gen_Dummy(0, LAST_DESCRIPTOR);
} /* End of program_desc */


void FC_Seq_Program_Desc_Gen_Copy()
{
    cmd_des_gen_info_ctx_t cmd_des_pro_info;
    
    memory_set(&cmd_des_pro_info, 0, sizeof(cmd_des_gen_info_ctx_t));

    FC_Seq_Des_Program_Gen_Dummy(0, FIRST_DESCRIPTOR);

	cmd_des_pro_info.au_cnt = 0;
	cmd_des_pro_info.tid=0;
	cmd_des_pro_info.fst_des=0;
	cmd_des_pro_info.lst_des=0;

	cmd_des_pro_info.rdy_bit=6;
	cmd_des_pro_info.des_cmd=0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info.ch=0;
	cmd_des_pro_info.device=0;
	
	cmd_des_pro_info.col_add=0;
	cmd_des_pro_info.encoded_ecc_au_sz=_supported_au_fmt[0].encoded_ecc_au_sz;

	cmd_des_pro_info.au_format_no=0;
	
	cmd_des_pro_info.wait_bef_add=0;
	cmd_des_pro_info.iss_enh=0;
	cmd_des_pro_info.iss_add_enh=0;
	cmd_des_pro_info.iss_00=0;
	
	cmd_des_pro_info.fnl_status=0;
	cmd_des_pro_info.cmd_00=0;
	cmd_des_pro_info.scd_cmd_off=0;
	cmd_des_pro_info.fst_cmd_off=0;

	cmd_des_pro_info.status_add=0;
	cmd_des_pro_info.status_poll_time=1;
	cmd_des_pro_info.status_wait_time=1;
	cmd_des_pro_info.add_type=0;

	cmd_des_pro_info.row_add=0;

	cmd_des_pro_info.fail_bit=0;
	cmd_des_pro_info.scmd=0x70;
	cmd_des_pro_info.cmd2=0x35;
	cmd_des_pro_info.cmd1=0x00;    
  
    FC_Seq_Cmd_Des_Program_Gen_Des(&cmd_des_pro_info);

	cmd_des_pro_info.au_cnt = 0;
	cmd_des_pro_info.tid=0;
	cmd_des_pro_info.fst_des=0;
	cmd_des_pro_info.lst_des=0;

	cmd_des_pro_info.rdy_bit=6;
	cmd_des_pro_info.des_cmd=1;//0 for read 1 for program 2 for erase
	cmd_des_pro_info.ch=0;
	cmd_des_pro_info.device=0;
	
	cmd_des_pro_info.col_add=0;
	cmd_des_pro_info.encoded_ecc_au_sz=_supported_au_fmt[0].encoded_ecc_au_sz;

	cmd_des_pro_info.au_format_no=0;
	
	cmd_des_pro_info.wait_bef_add=0;
	cmd_des_pro_info.iss_enh=0;
	cmd_des_pro_info.iss_add_enh=0;
	cmd_des_pro_info.iss_00=0;
	
	cmd_des_pro_info.fnl_status=0;
	cmd_des_pro_info.cmd_00=0;
	cmd_des_pro_info.scd_cmd_off=0;
	cmd_des_pro_info.fst_cmd_off=0;

	cmd_des_pro_info.status_add=0;
	cmd_des_pro_info.status_poll_time=1;
	cmd_des_pro_info.status_wait_time=1;
	cmd_des_pro_info.add_type=0;

	cmd_des_pro_info.row_add=256;

	cmd_des_pro_info.fail_bit=0;
	cmd_des_pro_info.scmd=0x70;
	cmd_des_pro_info.cmd2=0x10;
	cmd_des_pro_info.cmd1=0x85;    
  
    FC_Seq_Cmd_Des_Program_Gen_Des(&cmd_des_pro_info);

    FC_Seq_Des_Program_Gen_Dummy(0, LAST_DESCRIPTOR);
} /* End of program_desc */

void FC_Seq_Program_Desc_Gen_Copy_Random_Data_In()
{
    cmd_des_gen_info_ctx_t cmd_des_pro_info;
    
    memory_set(&cmd_des_pro_info, 0, sizeof(cmd_des_gen_info_ctx_t));

    FC_Seq_Des_Program_Gen_Dummy(0, FIRST_DESCRIPTOR);

	cmd_des_pro_info.au_cnt = 0;
	cmd_des_pro_info.tid=0;
	cmd_des_pro_info.fst_des=0;
	cmd_des_pro_info.lst_des=0;

	cmd_des_pro_info.rdy_bit=6;
	cmd_des_pro_info.des_cmd=0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info.ch=0;
	cmd_des_pro_info.device=0;
	
	cmd_des_pro_info.col_add=0;
	cmd_des_pro_info.encoded_ecc_au_sz=_supported_au_fmt[0].encoded_ecc_au_sz;

	cmd_des_pro_info.au_format_no=0;
	
	cmd_des_pro_info.wait_bef_add=0;
	cmd_des_pro_info.iss_enh=0;
	cmd_des_pro_info.iss_add_enh=0;
	cmd_des_pro_info.iss_00=0;
	
	cmd_des_pro_info.fnl_status=0;
	cmd_des_pro_info.cmd_00=0;
	cmd_des_pro_info.scd_cmd_off=0;
	cmd_des_pro_info.fst_cmd_off=0;

	cmd_des_pro_info.status_add=0;
	cmd_des_pro_info.status_poll_time=1;
	cmd_des_pro_info.status_wait_time=1;
	cmd_des_pro_info.add_type=0;

	cmd_des_pro_info.row_add=0;

	cmd_des_pro_info.fail_bit=0;
	cmd_des_pro_info.scmd=0x70;
	cmd_des_pro_info.cmd2=0x35;
	cmd_des_pro_info.cmd1=0x00;    
  
    FC_Seq_Cmd_Des_Program_Gen_Des(&cmd_des_pro_info);

	cmd_des_pro_info.au_cnt = 0;
	cmd_des_pro_info.tid=0;
	cmd_des_pro_info.fst_des=0;
	cmd_des_pro_info.lst_des=0;

	cmd_des_pro_info.rdy_bit=6;
	cmd_des_pro_info.des_cmd=2;//0 for read 1 for program 2 for erase
	cmd_des_pro_info.ch=0;
	cmd_des_pro_info.device=0;
	
	cmd_des_pro_info.col_add=0;
	cmd_des_pro_info.encoded_ecc_au_sz=_supported_au_fmt[0].encoded_ecc_au_sz;

	cmd_des_pro_info.au_format_no=0;
	
	cmd_des_pro_info.wait_bef_add=0;
	cmd_des_pro_info.iss_enh=0;
	cmd_des_pro_info.iss_add_enh=0;
	cmd_des_pro_info.iss_00=0;
	
	cmd_des_pro_info.fnl_status=0;
	cmd_des_pro_info.cmd_00=0;
	cmd_des_pro_info.scd_cmd_off=1;
	cmd_des_pro_info.fst_cmd_off=0;

	cmd_des_pro_info.status_add=0;
	cmd_des_pro_info.status_poll_time=0;
	cmd_des_pro_info.status_wait_time=0;
	cmd_des_pro_info.add_type=0;

	cmd_des_pro_info.row_add=256;

	cmd_des_pro_info.fail_bit=0;
	cmd_des_pro_info.scmd=0x00;
	cmd_des_pro_info.cmd2=0x00;
	cmd_des_pro_info.cmd1=0x85;    
  
    FC_Seq_Cmd_Des_Program_Gen_Des(&cmd_des_pro_info);

	cmd_des_pro_info.au_cnt = 1;
	cmd_des_pro_info.tid=0;
	cmd_des_pro_info.fst_des=0;
	cmd_des_pro_info.lst_des=0;

	cmd_des_pro_info.rdy_bit=6;
	cmd_des_pro_info.des_cmd=1;//0 for read 1 for program 2 for erase
	cmd_des_pro_info.ch=0;
	cmd_des_pro_info.device=0;
	
	cmd_des_pro_info.col_add=_supported_au_fmt[0].encoded_ecc_au_sz;
	cmd_des_pro_info.encoded_ecc_au_sz=_supported_au_fmt[0].encoded_ecc_au_sz;

	cmd_des_pro_info.au_format_no=0;
	
	cmd_des_pro_info.wait_bef_add=0;
	cmd_des_pro_info.iss_enh=0;
	cmd_des_pro_info.iss_add_enh=0;
	cmd_des_pro_info.iss_00=0;
	
	cmd_des_pro_info.fnl_status=0;
	cmd_des_pro_info.cmd_00=0;
	cmd_des_pro_info.scd_cmd_off=0;
	cmd_des_pro_info.fst_cmd_off=0;

	cmd_des_pro_info.status_add=0;
	cmd_des_pro_info.status_poll_time=1;
	cmd_des_pro_info.status_wait_time=1;
	cmd_des_pro_info.add_type=1;

	cmd_des_pro_info.row_add=256;

	cmd_des_pro_info.fail_bit=0;
	cmd_des_pro_info.scmd=0x70;
	cmd_des_pro_info.cmd2=0x10;
	cmd_des_pro_info.cmd1=0x85;    
  
    FC_Seq_Cmd_Des_Program_Gen_Des(&cmd_des_pro_info);

    FC_Seq_Des_Program_Gen_Dummy(0, LAST_DESCRIPTOR);
} /* End of program_desc */

void FC_Seq_Program_Desc_Gen_Random_Cache_Read()
{
    cmd_des_gen_info_ctx_t cmd_des_pro_info;
    
    memory_set(&cmd_des_pro_info, 0, sizeof(cmd_des_gen_info_ctx_t));

    FC_Seq_Des_Program_Gen_Dummy(0, FIRST_DESCRIPTOR);

	cmd_des_pro_info.au_cnt = 0;
	cmd_des_pro_info.tid=0;
	cmd_des_pro_info.fst_des=0;
	cmd_des_pro_info.lst_des=0;

	cmd_des_pro_info.rdy_bit=6;
	cmd_des_pro_info.des_cmd=0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info.ch=0;
	cmd_des_pro_info.device=0;
	
	cmd_des_pro_info.col_add=0;
	cmd_des_pro_info.encoded_ecc_au_sz=_supported_au_fmt[0].encoded_ecc_au_sz;

	cmd_des_pro_info.au_format_no=0;
	
	cmd_des_pro_info.wait_bef_add=0;
	cmd_des_pro_info.iss_enh=0;
	cmd_des_pro_info.iss_add_enh=0;
	cmd_des_pro_info.iss_00=0;
	
	cmd_des_pro_info.fnl_status=0;
	cmd_des_pro_info.cmd_00=0;
	cmd_des_pro_info.scd_cmd_off=0;
	cmd_des_pro_info.fst_cmd_off=0;

	cmd_des_pro_info.status_add=0;
	cmd_des_pro_info.status_poll_time=1;
	cmd_des_pro_info.status_wait_time=1;
	cmd_des_pro_info.add_type=0;

	cmd_des_pro_info.row_add=0;

	cmd_des_pro_info.fail_bit=0;
	cmd_des_pro_info.scmd=0x70;
	cmd_des_pro_info.cmd2=0x30;
	cmd_des_pro_info.cmd1=0x00;    
  
    FC_Seq_Cmd_Des_Program_Gen_Des(&cmd_des_pro_info);

	cmd_des_pro_info.au_cnt = 2;
	cmd_des_pro_info.tid=0;
	cmd_des_pro_info.fst_des=0;
	cmd_des_pro_info.lst_des=0;

	cmd_des_pro_info.rdy_bit=6;
	cmd_des_pro_info.des_cmd=0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info.ch=0;
	cmd_des_pro_info.device=0;
	
	cmd_des_pro_info.col_add=0;
	cmd_des_pro_info.encoded_ecc_au_sz=_supported_au_fmt[0].encoded_ecc_au_sz;

	cmd_des_pro_info.au_format_no=0;
	
	cmd_des_pro_info.wait_bef_add=0;
	cmd_des_pro_info.iss_enh=0;
	cmd_des_pro_info.iss_add_enh=0;
	cmd_des_pro_info.iss_00=0;
	
	cmd_des_pro_info.fnl_status=0;
	cmd_des_pro_info.cmd_00=0;
	cmd_des_pro_info.scd_cmd_off=0;
	cmd_des_pro_info.fst_cmd_off=0;

	cmd_des_pro_info.status_add=0;
	cmd_des_pro_info.status_poll_time=1;
	cmd_des_pro_info.status_wait_time=0;
	cmd_des_pro_info.add_type=0;

	cmd_des_pro_info.row_add=128;

	cmd_des_pro_info.fail_bit=0;
	cmd_des_pro_info.scmd=0x70;
	cmd_des_pro_info.cmd2=0x31;
	cmd_des_pro_info.cmd1=0x00;    
  
    FC_Seq_Cmd_Des_Program_Gen_Des(&cmd_des_pro_info);

	cmd_des_pro_info.au_cnt = 2;
	cmd_des_pro_info.tid=0;
	cmd_des_pro_info.fst_des=0;
	cmd_des_pro_info.lst_des=0;

	cmd_des_pro_info.rdy_bit=6;
	cmd_des_pro_info.des_cmd=0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info.ch=0;
	cmd_des_pro_info.device=0;
	
	cmd_des_pro_info.col_add=0;
	cmd_des_pro_info.encoded_ecc_au_sz=_supported_au_fmt[0].encoded_ecc_au_sz;

	cmd_des_pro_info.au_format_no=0;
	
	cmd_des_pro_info.wait_bef_add=0;
	cmd_des_pro_info.iss_enh=0;
	cmd_des_pro_info.iss_add_enh=0;
	cmd_des_pro_info.iss_00=0;
	
	cmd_des_pro_info.fnl_status=0;
	cmd_des_pro_info.cmd_00=0;
	cmd_des_pro_info.scd_cmd_off=1;
	cmd_des_pro_info.fst_cmd_off=0;

	cmd_des_pro_info.status_add=0;
	cmd_des_pro_info.status_poll_time=1;
	cmd_des_pro_info.status_wait_time=0;
	cmd_des_pro_info.add_type=3;

	cmd_des_pro_info.row_add=0;

	cmd_des_pro_info.fail_bit=0;
	cmd_des_pro_info.scmd=0x70;
	cmd_des_pro_info.cmd2=0x00;
	cmd_des_pro_info.cmd1=0x3f;    
  
    FC_Seq_Cmd_Des_Program_Gen_Des(&cmd_des_pro_info);

    FC_Seq_Des_Program_Gen_Dummy(0, LAST_DESCRIPTOR);
} /* End of program_desc */


void FC_Seq_Program_Desc_Gen_Two_Plane_Program()
{
    cmd_des_gen_info_ctx_t cmd_des_pro_info;
    
    memory_set(&cmd_des_pro_info, 0, sizeof(cmd_des_gen_info_ctx_t));

    FC_Seq_Des_Program_Gen_Dummy(0, FIRST_DESCRIPTOR);	

	cmd_des_pro_info.au_cnt = 2;
	cmd_des_pro_info.tid=0;
	cmd_des_pro_info.fst_des=0;
	cmd_des_pro_info.lst_des=0;

	cmd_des_pro_info.rdy_bit=6;
	cmd_des_pro_info.des_cmd=1;//0 for read 1 for program 2 for erase
	cmd_des_pro_info.ch=0;
	cmd_des_pro_info.device=0;
	
	cmd_des_pro_info.col_add=0;
	cmd_des_pro_info.encoded_ecc_au_sz=_supported_au_fmt[0].encoded_ecc_au_sz;

	cmd_des_pro_info.au_format_no=0;
	
	cmd_des_pro_info.wait_bef_add=0;
	cmd_des_pro_info.iss_enh=0;
	cmd_des_pro_info.iss_add_enh=0;
	cmd_des_pro_info.iss_00=0;
	
	cmd_des_pro_info.fnl_status=0;
	cmd_des_pro_info.cmd_00=0;
	cmd_des_pro_info.scd_cmd_off=0;
	cmd_des_pro_info.fst_cmd_off=0;

	cmd_des_pro_info.status_add=0;
	cmd_des_pro_info.status_poll_time=1;
	cmd_des_pro_info.status_wait_time=0;
	cmd_des_pro_info.add_type=0;

	cmd_des_pro_info.row_add=0;

	cmd_des_pro_info.fail_bit=0;
	cmd_des_pro_info.scmd=0x70;
	cmd_des_pro_info.cmd2=0x11;
	cmd_des_pro_info.cmd1=0x80;    
  
    FC_Seq_Cmd_Des_Program_Gen_Des(&cmd_des_pro_info);

	cmd_des_pro_info.au_cnt = 2;
	cmd_des_pro_info.tid=0;
	cmd_des_pro_info.fst_des=0;
	cmd_des_pro_info.lst_des=0;

	cmd_des_pro_info.rdy_bit=6;
	cmd_des_pro_info.des_cmd=1;//0 for read 1 for program 2 for erase
	cmd_des_pro_info.ch=0;
	cmd_des_pro_info.device=0;
	
	cmd_des_pro_info.col_add=0;
	cmd_des_pro_info.encoded_ecc_au_sz=_supported_au_fmt[0].encoded_ecc_au_sz;

	cmd_des_pro_info.au_format_no=0;
	
	cmd_des_pro_info.wait_bef_add=0;
	cmd_des_pro_info.iss_enh=0;
	cmd_des_pro_info.iss_add_enh=0;
	cmd_des_pro_info.iss_00=0;
	
	cmd_des_pro_info.fnl_status=0;
	cmd_des_pro_info.cmd_00=0;
	cmd_des_pro_info.scd_cmd_off=0;
	cmd_des_pro_info.fst_cmd_off=0;

	cmd_des_pro_info.status_add=0;
	cmd_des_pro_info.status_poll_time=1;
	cmd_des_pro_info.status_wait_time=1;
	cmd_des_pro_info.add_type=0;

	cmd_des_pro_info.row_add=128;

	cmd_des_pro_info.fail_bit=0;
	cmd_des_pro_info.scmd=0x71;
	cmd_des_pro_info.cmd2=0x10;
	cmd_des_pro_info.cmd1=0x81;    
  
    FC_Seq_Cmd_Des_Program_Gen_Des(&cmd_des_pro_info);


    FC_Seq_Des_Program_Gen_Dummy(0, LAST_DESCRIPTOR);
} /* End of program_desc */
#else

void FC_Seq_Des_Program_Gen(cmd_des_gen_info *desc_info)
{
    u32 tmp_dw;

    /*Program 1st Dword of 1st parameter*/
    if(desc_info->au_cnt > 0)
    	tmp_dw = (u32)(desc_info->au_cnt-1)<<CMD_DES_GEN_AU_NUM_BIT_OFF
    			|(u32)(desc_info->au_seg)<<CMD_DES_GEN_AU_SEG_BIT_OFF	
			|(u32)desc_info->tid;
    else
    	tmp_dw = (u32)(desc_info->au_seg)<<CMD_DES_GEN_AU_SEG_BIT_OFF	
			|(u32)desc_info->tid;
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);	
	
    /*Program 2nd Dword of 1st parameter*/
    tmp_dw =  (u32)(desc_info->rdy_bit)  << CMD_DES_GEN_READY_BIT_OFF
    		| (u32)(desc_info->readpad)  << CMD_DES_GEN_LE_BIT_OFF
            | (u32)1L                   << CMD_DES_GEN_DV_BIT_OFF
            | (u32)0L                   << CMD_DES_GEN_PA_BIT_OFF     //from ecu       
            | (u32)CMD_DES_GEN_DES_TYPE << CMD_DES_GEN_DF_BIT_OFF
            | (u32)(desc_info->des_cmd)                   << CMD_DES_GEN_DES_TYPE_BIT_OFF
            | (u32)(desc_info->ch)                   << CMD_DES_GEN_CH_BIT_OFF
            | (u32)(desc_info->device)                   << 0
            | (u32)(desc_info->fst_des)  << CMD_DES_GEN_FD_BIT_OFF
            | (u32)(desc_info->lst_des)  << CMD_DES_GEN_LD_BIT_OFF
            ;    
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);

	

    /*Program 1st Dword of 2nd parameter*/
    /*We do not use the SET_PARAM not, so set zero*/
    FC_Seq_Spm_Program_Des_Fifo_Dw(0);
    /*Program 2nd Dword of 2nd parameter*/
    tmp_dw = (u32)(desc_info->au_format_no) << CMD_DES_GEN_AU_FORMAT_BIT_OFF;
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);

	

    /*Program 1st Dword of 3th parameter*/
    tmp_dw = (u32)(desc_info->col_add) << 0
    			|(u32)(desc_info->encoded_ecc_au_sz*desc_info->au_cnt) <<CMD_DES_GEN_XF_COUNT_BIT_OFF;
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);
    /*Program 2nd Dword of 3th parameter*/
    if(desc_info->scmd == 0x78)
		tmp_dw = BIT_9;// 78 cmd should have row add
    else
		tmp_dw = 0;
    if((desc_info->cmd1 == 0)&&(desc_info->scd_cmd_off == 1))
		tmp_dw |= BIT_17;// do not issue 00 cmd, other read cmd should issue 00 cmd before data transfer
    if((desc_info->cmd1 == 0x78)&&(desc_info->scd_cmd_off == 1))
		tmp_dw |= BIT_17;
    if((desc_info->des_cmd == 0)&&(desc_info->au_cnt == 0))//read cmd, no data out
		tmp_dw |= BIT_17;
#if TOSHIBA>0
    if((desc_info->cmd1 == 0x05)&&(desc_info->cmd2 == 0xe0))//toshiba 2p data out 00+05+e0
		tmp_dw |= BIT_17;
#endif
   
    tmp_dw |= (u32)(desc_info->scd_cmd_off) << 11    	     
            | (u32)(desc_info->fst_cmd_off) << 10            
            |(u32)(desc_info->status_poll_time) << 7
            |(u32)(desc_info->status_wait_time) << 3
            | (u32)(desc_info->add_type) << 0
            ;    
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);

	

    /*Program 1st Dword of 4th parameter*/
    tmp_dw = (u32)(desc_info->row_add);
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);
    /*Program 2nd Dword of 4th parameter*/
    tmp_dw = (u32)(desc_info->fail_bit)<<0
              |(u32)(desc_info->scmd)<<CMD_DES_GEN_SCMD_BIT_OFF
              |(u32)(desc_info->cmd2)<<CMD_DES_GEN_CMD2_BIT_OFF
              |(u32)(desc_info->cmd1)<<CMD_DES_GEN_CMD1_BIT_OFF;
    FC_Seq_Spm_Program_Des_Fifo_Dw(tmp_dw);

    FC_Seq_Set_Desc_Fifo_Count(1);
} 
#endif


void Test_Nand_Indirect(void)
{
	u8 *data;
	u32 chan;
	u32 dev;
	u32 block;
	u32 page;
	u32 tmp1;
	int err;
	int i;
	u8 *rdata;

	chan = 0;
	dev = 0;
	block =100;
	page = 0;
	data = (u8 *)(0x54000000+0x00000);//256k
	rdata = (u8 *)(0x54000000+0x40000);//256k
	err = 0;

	//for(block = 0;block<20;block++)
	{
		memory_set((void*) data, 0, 8192);	
		FC_Direct_Enable_Write_Protection(0);
		
		err = FC_Indirect_Read_Page(chan, dev, block, page, (void*) data, 8192);
		//err = FC_Indirect_Read_Page(chan, dev, 1, page, (void*) data, 8192);
		//err = FC_Indirect_Erase_Block(chan,dev,0);
		//err = FC_Indirect_Erase_Block(chan,dev,1);
		//err = FC_Indirect_Erase_Block(chan,dev,2);
		//err = FC_Indirect_Erase_Block(chan,dev,5);
		err = FC_Indirect_Erase_Block(chan,dev,block);
		FC_Indirect_Get_Status(0, 0, &tmp1);
		memory_set((void*) data, 0x77, 8192);
		err = FC_Indirect_Write_Page(chan, dev, block, page, (void*) data, 8192);
		FC_Indirect_Get_Status(0, 0, &tmp1);
		memory_set((void*) data, 0, 8192);				
		err = FC_Indirect_Read_Page(chan, dev, block, page, (void*) data, 8192);
		err = FC_Indirect_Erase_Block(chan,dev,block);
		//err = FC_Indirect_Erase_Block(chan,dev,6);
		
	}	
}
void FC_Seq2Indirect()
{
	REG16_CLEAR_BITS(FC_REG_SEQ_CNTL1,  FC_FSEQ_EN);
	DelayUS(FC_DLY_US);
	FC_Set_Access_Mode(FC_ACCESS_MODE_INDIRECT);
	FC_Indirect_Fifo_Reset();
}

void FC_Indirect2Seq()
{
	FC_Indirect_Fifo_Reset();
	FC_Set_Access_Mode(FC_ACCESS_MODE_SEQ);
	REG16_SET_BITS(FC_REG_SEQ_CNTL1,  FC_FSEQ_EN);
	DelayUS(FC_DLY_US);
	
}
#if 0
void FC_Debug_FindBadBlock(cmd_fc_info cmd)//search 256 block once
{	
	u8 err;
	u8 *data;
	u32 block;

	data = (u8*)cmd.buf_add;
	
	FC_Seq2Indirect();

	for(block = cmd.phyblock; block < (cmd.phyblock + 128); block++)
	{
		err = FC_Indirect_Read_Page(cmd.ch, cmd.device, block, 0, data, 2);	//page 0
		data +=2;
		err = FC_Indirect_Read_Page(cmd.ch, cmd.device, block, 255, data, 2);	//page 255
		data +=2;
	}

	FC_Indirect2Seq();
}
#else

void FC_Debug_FindBadBlock(cmd_fc_info cmd, u8 FlashTag)//search 256 block once
{	
	u8 err;
	u8 *data; 
	u8*rdata;
	u8 *tmp;
	u32 block;
	u32 page0, page1;
	u8 stepsize, i;
	u8 tcnt=0;

	data = (u8*)cmd.buf_add;
	rdata = (u8*)(cmd.buf_add+1024);
	tmp = (u8*)(cmd.buf_add+1024);
	FC_Seq2Indirect();
	switch(FlashTag)
	{
		case FLASH_TYPE_TOSHIBA:
			page0 = 0;
			page1 = 255;
			stepsize = 2;
			break;
		case FLASH_TYPE_SANDISK:
			page0 = 0;
			page1 = 1;
			stepsize = 6;
			break;
		case FLASH_TYPE_SAMSUNG:
		default:
			break;

	}

	for(block = cmd.phyblock; block < (cmd.phyblock + 128); block++)
	{
		err = FC_Indirect_Read_Page(cmd.ch, cmd.device, block, page0, rdata, stepsize);	//page 0
		rdata +=stepsize;
		
		err = FC_Indirect_Read_Page(cmd.ch, cmd.device, block, page1, rdata, stepsize);	//page 255
		rdata +=stepsize;

		if(FlashTag==FLASH_TYPE_TOSHIBA)
		{
			for(i =0; i<2*stepsize; i++)// compare 2page rdata
			{
				
				if(tmp[i+tcnt*2*stepsize]!=0xff)
					data[i+tcnt*2*stepsize]=0x00;
				else
					data[i+tcnt*2*stepsize]=0xff;
				
				
			}	

		}
		else if(FlashTag == FLASH_TYPE_SANDISK)
		{
			for(i =0; i<2*stepsize; i+=3)// compare 2page rdata
			{
				
				if((tmp[i+tcnt*2*stepsize]==0x00)&&(tmp[i+1+tcnt*2*stepsize]==0x00)&&(tmp[i+2+tcnt*2*stepsize]==0x00))
				{
					data[(i/3)+tcnt*4]==0x00;
				}
					
				else
				{
					
					data[(i/3)+tcnt*4]=0xff;
				}
						
			}

		}
		tcnt++;
	}
	FC_Indirect2Seq();
}

#endif

void 
Init_Nand(void)
{	
	cmd_fc_info cmd;
	u8 FlashTag;
	//REG16_WRITE(0x1c00a89e, 0);
	//Init NAND flash interface
    	nvcfg.chdev = (8 << 4) | 4;
    	nvcfg.nr_ch = nvcfg.chdev >> 4;
    	nvcfg.nr_dev_per_ch = (nvcfg.chdev & 0xF);

	Nand_Find_All_Device(nvcfg.flash_id, &nvcfg.nr_ch, &nvcfg.nr_dev_per_ch, nvcfg.devs);
	
	//Test_Nand_Indirect();
	/*DBG_FillDDR(dbgDDRDataAddr, PAGE_SIZE, 0x25);
	cmd.ch =0;
	cmd.device =0;
	cmd.phyblock = 0;
	FlashTag = 2;
	cmd.buf_add   = dbgDDRDataAddr;
	FC_Debug_FindBadBlock(cmd, FlashTag);*/
	
	Nand_Set_Timing_Mode((u32)nvcfg.nand_device_class);
	//FC_Seq2Indirect();
	//Test_Nand_Indirect();
	Nand_Init_Nvcfg_Related();	
}



void InitBM(void)
{
	u32 i;
	//rECU.ctrlConfig5.bits.ddrMcPortConf = 0;//fs can be used for w,es can be used for r.
	rBM.extdSegSel.all = BIT_15|BIT_14;	
    	rBM.extdSecSize.all = (mAU_SIZE/2 + metasize/2);
	rBM.extdSeg0SectorCnt= 0;
	rBM.extdSeg0Size = 0x7ffe;
	rBM.extdSeg1SectorCnt= 0;
	rBM.extdSeg1Size = 0x7ffe;
	rBM.extdSeg2SectorCnt= 0;
	rBM.extdSeg2Size = 0x7ffe;
	rBM.extdSeg3SectorCnt= 0;
	rBM.extdSeg3Size = 0x7ffe;

	rBM.diskSegSelect.all = BIT_15|BIT_14;	
	rBM.diskSectorSize.all = (mAU_SIZE/2 + metasize/2);
	rBM.diskSeg0SectorCnt= 0;
	rBM.diskSeg0Size = 0x7ffe;
	rBM.diskSeg1SectorCnt= 0;
	rBM.diskSeg1Size = 0x7ffe;
	rBM.diskSeg2SectorCnt= 0;
	rBM.diskSeg2Size = 0x7ffe;
	rBM.diskSeg3SectorCnt= 0;
	rBM.diskSeg3Size = 0x7ffe;	
#if FTL == 0
	for(i=0;i<BFR_SSD_RDCNT-1;i++)
	{
		pmBfrSSD[i].nextSsdIndex = i+1;
	}
	pmBfrSSD[BFR_SSD_RDCNT-1].nextSsdIndex = 0;

	for(i=0;i<BFR_SSD_WDCNT-1;i++)
	{
		pmBfrSSD[i+BFR_SSD_RDCNT].nextSsdIndex = i+1+BFR_SSD_RDCNT;
	}
	pmBfrSSD[BFR_SSD_WDCNT-1+BFR_SSD_RDCNT].nextSsdIndex = BFR_SSD_RDCNT;
#endif
}

void InitSeqGlobal(void)
{
	u8 i;
	for(i=0;i<32;i++)
	{
		tid_sts[i] = 0;
		tid_error[i] = 0;
	}
	
	for(i=0;i<8;i++)
	{
		fs_sts[i] = 0;
		es_sts[i] = 0;
	}
#if TOSHIBA > 0 
	memory_set(&cmd_des_pro_info_r, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_r.rdy_bit = 6;
	cmd_des_pro_info_r.fail_bit = 0;	
	cmd_des_pro_info_r.scd_cmd_off = 0;
	cmd_des_pro_info_r.fst_cmd_off = 0;	
	cmd_des_pro_info_r.status_poll_time = 1;
	cmd_des_pro_info_r.status_wait_time = 1;
	cmd_des_pro_info_r.add_type = 0;	
	cmd_des_pro_info_r.des_cmd = 0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_r.scmd = FC_CMD_STS_70;
	cmd_des_pro_info_r.cmd2 = 0x30;
	cmd_des_pro_info_r.cmd1 = 0x00;

	memory_set(&cmd_des_pro_info_w, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_w.rdy_bit = 6;
	cmd_des_pro_info_w.fail_bit = 0;	
	cmd_des_pro_info_w.scd_cmd_off = 0;
	cmd_des_pro_info_w.fst_cmd_off = 0;	
	cmd_des_pro_info_w.status_poll_time = 1;
	cmd_des_pro_info_w.status_wait_time = 3;
	cmd_des_pro_info_w.add_type = 0;	
	cmd_des_pro_info_w.des_cmd = 1;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_w.scmd = FC_CMD_STS_70;
	cmd_des_pro_info_w.cmd2 = 0x10;
	cmd_des_pro_info_w.cmd1 = 0x80; 

	memory_set(&cmd_des_pro_info_e, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_e.rdy_bit = 6;
	cmd_des_pro_info_e.fail_bit = 0;	
	cmd_des_pro_info_e.scd_cmd_off = 0;
	cmd_des_pro_info_e.fst_cmd_off = 0;	
	cmd_des_pro_info_e.status_poll_time = 1;
	cmd_des_pro_info_e.status_wait_time = 5;
	cmd_des_pro_info_e.add_type = 2;	
	cmd_des_pro_info_e.des_cmd = 2;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_e.scmd = FC_CMD_STS_70;
	cmd_des_pro_info_e.cmd2 = 0xd0;
	cmd_des_pro_info_e.cmd1 = 0x60; 

	memory_set(&cmd_des_pro_info_2p_e, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_2p_e.rdy_bit = 6;
	cmd_des_pro_info_2p_e.fail_bit = 0;	
	cmd_des_pro_info_2p_e.scd_cmd_off = 1;
	cmd_des_pro_info_2p_e.fst_cmd_off = 0;	
	cmd_des_pro_info_2p_e.status_poll_time = 0;
	cmd_des_pro_info_2p_e.status_wait_time = 0;
	cmd_des_pro_info_2p_e.add_type = 2;	
	cmd_des_pro_info_2p_e.des_cmd = 2;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_2p_e.scmd = 0xff;//0x78
	cmd_des_pro_info_2p_e.cmd2 = 0xff;
	cmd_des_pro_info_2p_e.cmd1 = 0x60; 

	memory_set(&cmd_des_pro_info_dataout, 0, sizeof(cmd_des_gen_info));	
	cmd_des_pro_info_dataout.rdy_bit = 6;
	cmd_des_pro_info_dataout.fail_bit = 0;	
	cmd_des_pro_info_dataout.scd_cmd_off = 1;
	cmd_des_pro_info_dataout.fst_cmd_off = 0;	
	cmd_des_pro_info_dataout.status_poll_time = 0;
	cmd_des_pro_info_dataout.status_wait_time = 0;
	cmd_des_pro_info_dataout.add_type = 0;	
	cmd_des_pro_info_dataout.des_cmd = 0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_dataout.scmd = 0xff;
	cmd_des_pro_info_dataout.cmd2 = 0xff;
	cmd_des_pro_info_dataout.cmd1 = 0x00;

	memory_set(&cmd_des_pro_info_changeclm, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_changeclm.rdy_bit = 6;
	cmd_des_pro_info_changeclm.fail_bit = 0;	
	cmd_des_pro_info_changeclm.scd_cmd_off = 0;
	cmd_des_pro_info_changeclm.fst_cmd_off = 0;	
	cmd_des_pro_info_changeclm.status_poll_time = 0;
	cmd_des_pro_info_changeclm.status_wait_time = 0;
	cmd_des_pro_info_changeclm.add_type = 1;	
	cmd_des_pro_info_changeclm.des_cmd = 0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_changeclm.scmd = 0xff;
	cmd_des_pro_info_changeclm.cmd2 = 0xe0;
	cmd_des_pro_info_changeclm.cmd1 = 0x05;

	memory_set(&cmd_des_pro_info_2p_r, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_2p_r.rdy_bit = 6;
	cmd_des_pro_info_2p_r.fail_bit = 0;	
	cmd_des_pro_info_2p_r.scd_cmd_off = 0;
	cmd_des_pro_info_2p_r.fst_cmd_off = 0;	
	cmd_des_pro_info_2p_r.status_poll_time = 1;
	cmd_des_pro_info_2p_r.status_wait_time = 0;
	cmd_des_pro_info_2p_r.add_type = 0;	
	cmd_des_pro_info_2p_r.des_cmd = 0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_2p_r.scmd = FC_CMD_STS_70;//0x78
	cmd_des_pro_info_2p_r.cmd2 = 0x32;
	cmd_des_pro_info_2p_r.cmd1 = 0x00;

	memory_set(&cmd_des_pro_info_2p_datain, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_2p_datain.rdy_bit = 6;
	cmd_des_pro_info_2p_datain.fail_bit = 0;	
	cmd_des_pro_info_2p_datain.scd_cmd_off = 0;
	cmd_des_pro_info_2p_datain.fst_cmd_off = 0;	
	cmd_des_pro_info_2p_datain.status_poll_time = 1;
	cmd_des_pro_info_2p_datain.status_wait_time = 1;
	cmd_des_pro_info_2p_datain.add_type = 0;	
	cmd_des_pro_info_2p_datain.des_cmd = 1;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_2p_datain.scmd = FC_CMD_STS_70;//0x78
	cmd_des_pro_info_2p_datain.cmd2 = 0x11;
	cmd_des_pro_info_2p_datain.cmd1 = 0x85;

	memory_set(&cmd_des_pro_info_2p_prg, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_2p_prg.rdy_bit = 6;
	cmd_des_pro_info_2p_prg.fail_bit = 0;	
	cmd_des_pro_info_2p_prg.scd_cmd_off = 0;
	cmd_des_pro_info_2p_prg.fst_cmd_off = 0;	
	cmd_des_pro_info_2p_prg.status_poll_time = 1;
	cmd_des_pro_info_2p_prg.status_wait_time = 3;
	cmd_des_pro_info_2p_prg.add_type = 0;	
	cmd_des_pro_info_2p_prg.des_cmd = 1;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_2p_prg.scmd = FC_CMD_STS_71;
	cmd_des_pro_info_2p_prg.cmd2 = 0x10;
	cmd_des_pro_info_2p_prg.cmd1 = 0x85;
#else
	memory_set(&cmd_des_pro_info_r, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_r.rdy_bit = 6;
	cmd_des_pro_info_r.fail_bit = 0;	
	cmd_des_pro_info_r.scd_cmd_off = 0;
	cmd_des_pro_info_r.fst_cmd_off = 0;	
	cmd_des_pro_info_r.status_poll_time = 1;
	cmd_des_pro_info_r.status_wait_time = 1;
	cmd_des_pro_info_r.add_type = 0;	
	cmd_des_pro_info_r.des_cmd = 0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_r.scmd = FC_CMD_STS_70;
	cmd_des_pro_info_r.cmd2 = 0x30;
	cmd_des_pro_info_r.cmd1 = 0x00;

	memory_set(&cmd_des_pro_info_w, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_w.rdy_bit = 6;
	cmd_des_pro_info_w.fail_bit = 0;	
	cmd_des_pro_info_w.scd_cmd_off = 0;
	cmd_des_pro_info_w.fst_cmd_off = 0;	
	cmd_des_pro_info_w.status_poll_time = 1;
	cmd_des_pro_info_w.status_wait_time = 3;
	cmd_des_pro_info_w.add_type = 0;	
	cmd_des_pro_info_w.des_cmd = 1;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_w.scmd = FC_CMD_STS_70;
	cmd_des_pro_info_w.cmd2 = 0x10;
	cmd_des_pro_info_w.cmd1 = 0x80; 

	memory_set(&cmd_des_pro_info_e, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_e.rdy_bit = 6;
	cmd_des_pro_info_e.fail_bit = 0;	
	cmd_des_pro_info_e.scd_cmd_off = 0;
	cmd_des_pro_info_e.fst_cmd_off = 0;	
	cmd_des_pro_info_e.status_poll_time = 1;
	cmd_des_pro_info_e.status_wait_time = 5;
	cmd_des_pro_info_e.add_type = 2;	
	cmd_des_pro_info_e.des_cmd = 2;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_e.scmd = FC_CMD_STS_70;
	cmd_des_pro_info_e.cmd2 = 0xd0;
	cmd_des_pro_info_e.cmd1 = 0x60; 

	memory_set(&cmd_des_pro_info_2p_e, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_2p_e.rdy_bit = 6;
	cmd_des_pro_info_2p_e.fail_bit = 0;	
	cmd_des_pro_info_2p_e.scd_cmd_off = 0;
	cmd_des_pro_info_2p_e.fst_cmd_off = 0;	
	cmd_des_pro_info_2p_e.status_poll_time = 1;
	cmd_des_pro_info_2p_e.status_wait_time = 0;
	cmd_des_pro_info_2p_e.add_type = 2;	
	cmd_des_pro_info_2p_e.des_cmd = 2;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_2p_e.scmd = FC_CMD_STS_78;//0x78
	cmd_des_pro_info_2p_e.cmd2 = 0xd1;
	cmd_des_pro_info_2p_e.cmd1 = 0x60; 

	memory_set(&cmd_des_pro_info_2p_datain, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_2p_datain.rdy_bit = 6;
	cmd_des_pro_info_2p_datain.fail_bit = 0;	
	cmd_des_pro_info_2p_datain.scd_cmd_off = 0;
	cmd_des_pro_info_2p_datain.fst_cmd_off = 0;	
	cmd_des_pro_info_2p_datain.status_poll_time = 1;
	cmd_des_pro_info_2p_datain.status_wait_time = 1;
	cmd_des_pro_info_2p_datain.add_type = 0;	
	cmd_des_pro_info_2p_datain.des_cmd = 1;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_2p_datain.scmd = FC_CMD_STS_78;//0x78
	cmd_des_pro_info_2p_datain.cmd2 = 0x11;
	cmd_des_pro_info_2p_datain.cmd1 = 0x85;

	memory_set(&cmd_des_pro_info_2p_prg, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_2p_prg.rdy_bit = 6;
	cmd_des_pro_info_2p_prg.fail_bit = 0;	
	cmd_des_pro_info_2p_prg.scd_cmd_off = 0;
	cmd_des_pro_info_2p_prg.fst_cmd_off = 0;	
	cmd_des_pro_info_2p_prg.status_poll_time = 1;
	cmd_des_pro_info_2p_prg.status_wait_time = 3;
	cmd_des_pro_info_2p_prg.add_type = 0;	
	cmd_des_pro_info_2p_prg.des_cmd = 1;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_2p_prg.scmd = FC_CMD_STS_70;
	cmd_des_pro_info_2p_prg.cmd2 = 0x10;
	cmd_des_pro_info_2p_prg.cmd1 = 0x85;

	memory_set(&cmd_des_pro_info_changeclm, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_changeclm.rdy_bit = 6;
	cmd_des_pro_info_changeclm.fail_bit = 0;	
	cmd_des_pro_info_changeclm.scd_cmd_off = 0;
	cmd_des_pro_info_changeclm.fst_cmd_off = 0;	
	cmd_des_pro_info_changeclm.status_poll_time = 0;
	cmd_des_pro_info_changeclm.status_wait_time = 0;
	cmd_des_pro_info_changeclm.add_type = 1;	
	cmd_des_pro_info_changeclm.des_cmd = 0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_changeclm.scmd = FC_CMD_STS_70;
	cmd_des_pro_info_changeclm.cmd2 = 0xe0;
	cmd_des_pro_info_changeclm.cmd1 = 0x05;

	memory_set(&cmd_des_pro_info_2p_r, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_2p_r.rdy_bit = 6;
	cmd_des_pro_info_2p_r.fail_bit = 0;	
	cmd_des_pro_info_2p_r.scd_cmd_off = 0;
	cmd_des_pro_info_2p_r.fst_cmd_off = 0;	
	cmd_des_pro_info_2p_r.status_poll_time = 1;
	cmd_des_pro_info_2p_r.status_wait_time = 0;
	cmd_des_pro_info_2p_r.add_type = 0;	
	cmd_des_pro_info_2p_r.des_cmd = 0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_2p_r.scmd = FC_CMD_STS_78;//0x78
	cmd_des_pro_info_2p_r.cmd2 = 0x32;
	cmd_des_pro_info_2p_r.cmd1 = 0x00;

	memory_set(&cmd_des_pro_info_2p_changeclm, 0, sizeof(cmd_des_gen_info));
	cmd_des_pro_info_2p_changeclm.rdy_bit = 6;
	cmd_des_pro_info_2p_changeclm.fail_bit = 0;	
	cmd_des_pro_info_2p_changeclm.scd_cmd_off = 0;
	cmd_des_pro_info_2p_changeclm.fst_cmd_off = 0;	
	cmd_des_pro_info_2p_changeclm.status_poll_time = 0;
	cmd_des_pro_info_2p_changeclm.status_wait_time = 0;
	cmd_des_pro_info_2p_changeclm.add_type = 0;	
	cmd_des_pro_info_2p_changeclm.des_cmd = 0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_2p_changeclm.scmd = FC_CMD_STS_78;
	cmd_des_pro_info_2p_changeclm.cmd2 = 0xe0;
	cmd_des_pro_info_2p_changeclm.cmd1 = 0x06;

	memory_set(&cmd_des_pro_info_dataout, 0, sizeof(cmd_des_gen_info));	
	cmd_des_pro_info_dataout.rdy_bit = 6;
	cmd_des_pro_info_dataout.fail_bit = 0;	
	cmd_des_pro_info_dataout.scd_cmd_off = 1;
	cmd_des_pro_info_dataout.fst_cmd_off = 0;	
	cmd_des_pro_info_dataout.status_poll_time = 0;
	cmd_des_pro_info_dataout.status_wait_time = 0;
	cmd_des_pro_info_dataout.add_type = 0;	
	cmd_des_pro_info_dataout.des_cmd = 0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_dataout.scmd = FC_CMD_STS_70;
	cmd_des_pro_info_dataout.cmd2 = 0xe0;
	cmd_des_pro_info_dataout.cmd1 = 0x00;

	memory_set(&cmd_des_pro_info_r_sts, 0, sizeof(cmd_des_gen_info));	
	cmd_des_pro_info_r_sts.rdy_bit = 6;
	cmd_des_pro_info_r_sts.fail_bit = 0;	
	cmd_des_pro_info_r_sts.scd_cmd_off = 1;
	cmd_des_pro_info_r_sts.fst_cmd_off = 1;	
	cmd_des_pro_info_r_sts.status_poll_time = 1;
	cmd_des_pro_info_r_sts.status_wait_time = 0;
	cmd_des_pro_info_r_sts.add_type = 3;	
	cmd_des_pro_info_r_sts.des_cmd = 0;//0 for read 1 for program 2 for erase
	cmd_des_pro_info_r_sts.scmd = FC_CMD_STS_78;
	cmd_des_pro_info_r_sts.cmd2 = 0xe0;
	cmd_des_pro_info_r_sts.cmd1 = 0x00;
#endif

}

void  InitSeq(void)
{
	InitSeqGlobal();
	InitBM();	
	Init_Track();	
	Init_Nand();	
	Init_ECU(nvcfg.page_sz, nvcfg.ecc_au_sz);
	FC_Seq_Cfg(nvcfg.page_sz);	
    InitSPI();
	
}



void FC_Seq_Done(void)
{
	INT16U SeqIntSta;
	u32 isr_bit;
	u16 tid;
	u32  dec_sts;
	u32 trk_sts1;
	u32 trk_sts2;
	
	//isr_bit = (u32)REG16_READ(0x1C00BA00);
	//REG16_WRITE(0x1C00BA00, isr_bit);

	SeqIntSta = REG16_READ(SEQC_RW_INTSTA);
	//REG16_WRITE(SEQC_RW_INTSTA, SeqIntSta);
	
	
	tid = REG16_READ(SEQC_RW_TRACKSTAID);	

	if (SeqIntSta & (SEQ_IRQ_TRK_ERR | SEQ_IRQ_TRK_DONE))
	{
		tid = REG16_READ(SEQC_RW_TRACKSTAID);
		if (SeqIntSta & SEQ_IRQ_TRK_ERR) 
		{			
			trk_sts1 = REG32_READ(SEQ_REG_TRK_STATUS1);
			if(trk_sts1 & BIT_0)//nand flash error
			{
				tid_sts[tid] = 0;	
				tid_error[tid] = 1;
				if(trk_seg[tid].rw == 1)
					fs_sts[trk_seg[tid].fs_num] = 0;
				else if(trk_seg[tid].rw == 2)
					es_sts[trk_seg[tid].es_num] = 0;
				trk_seg[tid].rw = 0;//free cmd

#if FTL > 0 
				switch(TrackList[tid].Type)
				{
					case TRACK_RD:
						break;
					case TRACK_GC:			
						if(GcGroup[TrackList[tid].EsNo].TrackId == tid)
						{
							ftl_put_es_table(TrackList[tid].EsNo);
							ftl_gc_done(TrackList[tid].EsNo);					
						}
						break;		
					case TRACK_WR:
						FsBitmap.HwBitmap ^= (1<<TrackList[tid].FsNo);
						break;
					case TRACK_PE:
						RowState[TrackList[tid].RowNo].PeDone = 1;
						RowState[TrackList[tid].RowNo].PeErr = tid_error[tid];
						break;
					default: break;
				}
#endif
			}
			else if(trk_sts1 & BIT_1)//ecc error
			{
				
				trk_sts2 = REG32_READ(SEQ_REG_TRK_STATUS2);
				if(trk_sts2 & BIT_31)//encode error
				{
					dec_sts = REG16_READ(EC_REG_ENCODE_STATUS_0);
					REG16_CLEAR_BITS(EC_REG_ENCODE_STATUS_0, EC_ENC_STOP_RESUME);
				}
				else//decode error
				{
					dec_sts = REG16_READ(EC_REG_DECODE_STATUS_REPORT0);
					REG16_CLEAR_BITS(EC_REG_DECODE_STATUS_REPORT0, EC_DEC_STOP_RESUME);
					tid_error[tid] = 1;
					if (dec_sts & EC_DEC_CUR_AU_ERASE) 
					{
		                
		            		}
		            		if (dec_sts & EC_DEC_CUR_AU_UNCORR) 
					{
		                		//tid_sts[tid] = 0;
		                		tid_error[tid] = 1;
		            		}
				}
			}	
					
			REG16_WRITE(SEQC_RW_INTSTA, SEQ_IRQ_TRK_ERR);
		}
		if (SeqIntSta & SEQ_IRQ_TRK_DONE) 
		{
			REG16_WRITE(SEQC_RW_INTSTA, SEQ_IRQ_TRK_DONE);
			tid_sts[tid] = 0;
			if(trk_seg[tid].rw == 1)
				fs_sts[trk_seg[tid].fs_num] = 0;
			else if(trk_seg[tid].rw == 2)
				es_sts[trk_seg[tid].es_num] = 0;
			trk_seg[tid].rw = 0;//free cmd
			
#if FTL > 0 
			switch(TrackList[tid].Type)
			{
				case TRACK_RD:
					break;
				case TRACK_GC:			
					if(GcGroup[TrackList[tid].EsNo].TrackId == tid)
					{
						ftl_put_es_table(TrackList[tid].EsNo);
						ftl_gc_done(TrackList[tid].EsNo);					
					}
					break;		
				case TRACK_WR:
					FsBitmap.HwBitmap ^= (1<<TrackList[tid].FsNo);
					break;
				case TRACK_PE:
					RowState[TrackList[tid].RowNo].PeDone = 1;
					RowState[TrackList[tid].RowNo].PeErr = tid_error[tid];
					break;
				default: break;
			}
#endif
		}
	}
	if (SeqIntSta & (~(SEQ_IRQ_TRK_ERR | SEQ_IRQ_TRK_DONE)))
	{
		SeqIntSta = REG16_READ(SEQC_RW_INTSTA);
		//REG16_WRITE(SEQC_RW_INTSTA, SeqIntSta);
		REG16_WRITE(SEQC_RW_INTSTA, SeqIntSta &(~(SEQ_IRQ_TRK_ERR | SEQ_IRQ_TRK_DONE)));
	}
}

#if DEBUG > 0 
void FC_Debug_ResetFlash(cmd_fc_info cmd)
{
	u8 fcmd[] = { mFC_CMD_RESET_FLASH };
	u8 err;
	
	FC_Seq2Indirect();
	
	FC_Indirect_Set_Access_Device(cmd.ch, cmd.device);
       err = FC_Indirect_Execute_Cmd(fcmd, sizeof(fcmd), 0, 0, 1);            
       DelayUS(100);             // 100 delay for device reset ready
       err = FC_Indirect_Wait_Device_Ready(cmd.ch, cmd.device, FC_INDIRECT_RESET_TIME_OUT_US);

	FC_Indirect2Seq();
}

void FC_Debug_ReadId(cmd_fc_info cmd)
{	
	u8 err;
	u8 *id;

	id = (u8*)cmd.buf_add;
	
	FC_Seq2Indirect();
	//FC_Set_Sqra_Mode();
	
	err = FC_Indirect_Execute_Read_Id(cmd.ch, cmd.device, id, 6);

	FC_Indirect2Seq();
	//FC_Reset_Sqra_Mode();
}
/*
void FC_Debug_EraseBlock(cmd_fc_info cmd)
{	
	u8 err;
	
	FC_Seq2Indirect();
	
	err = FC_Indirect_Erase_Block(cmd.ch,cmd.device,cmd.phyblock);

	FC_Indirect2Seq();
	DelayMS(500);
}*/

void FC_Debug_ReadPage_Bp(cmd_fc_info cmd)
{	
	u8 err;
	u8 *data;

	data = (u8*)cmd.buf_add;
	
	FC_Seq2Indirect();
	
	err = FC_Indirect_Read_Page(cmd.ch, cmd.device, cmd.phyblock, cmd.phypage, data, cmd.data_len);

	FC_Indirect2Seq();
}
#endif

u32 Get_FSsd_Index(u32 ssdlen)
{
	u32 fs_num;
	if(FS_BUSY_PTR >= FS_FREE_PTR)
	{
		while((FS_BUSY_PTR + ssdlen) >= (BFR_SSD_WDCNT + FS_FREE_PTR));
		
	}
	else
	{
		while(1)
		{
			if(FS_BUSY_PTR < FS_FREE_PTR)
			{
				if((FS_BUSY_PTR + ssdlen) < FS_FREE_PTR) 
					break;
			}
			else if(FS_BUSY_PTR >= FS_FREE_PTR)// host change FS_FREE_PTR
			{
				if((FS_BUSY_PTR + ssdlen) < (BFR_SSD_WDCNT + FS_FREE_PTR)) 
					break;
			}
		}
	}

	fs_num = FS_BUSY_PTR;
	if((FS_BUSY_PTR + ssdlen) >= BFR_SSD_WDCNT)
	{
		FS_BUSY_PTR = FS_BUSY_PTR + ssdlen - BFR_SSD_WDCNT;
	}		
	else
	{
		FS_BUSY_PTR = FS_BUSY_PTR + ssdlen;
	}
		
	return (fs_num + BFR_SSD_RDCNT);
}

u32 Get_ESsd_Index(u32 ssdlen)
{
	u32 es_num;
	if(ES_BUSY_PTR >= ES_FREE_PTR)
	{
		while((ES_BUSY_PTR + ssdlen) >= (BFR_SSD_RDCNT + ES_FREE_PTR));
		
	}
	else
	{
		while(1)
		{
			if(ES_BUSY_PTR < ES_FREE_PTR)
			{
				if((ES_BUSY_PTR + ssdlen) < ES_FREE_PTR) 
					break;
			}
			else if(ES_BUSY_PTR >= ES_FREE_PTR)// host change ES_FREE_PTR
			{
				if((ES_BUSY_PTR + ssdlen) < (BFR_SSD_RDCNT + ES_FREE_PTR)) 
					break;
			}
		}
	}

	es_num = ES_BUSY_PTR;
	if((ES_BUSY_PTR + ssdlen) >= BFR_SSD_RDCNT)
	{
		ES_BUSY_PTR = ES_BUSY_PTR + ssdlen - BFR_SSD_RDCNT;
	}		
	else
	{
		ES_BUSY_PTR = ES_BUSY_PTR + ssdlen;
	}
		
	return (es_num);
}

u8 Ftl_Get_Chan(u32 lba)
{
	u32 value;
	value = REG32_READ(0 + (lba<<2));
	if(value == 0xffffffff)
		return 0xff;
	else
		return ((value>>(BLK_SHIFT+PLANE_SHIFT+DIE_SHIFT))&0x07);
}

u8 Ftl_Get_Dev(u32 lba)
{
	u32 value;
	value = REG32_READ(0 + (lba<<2));
	if(value == 0xffffffff)
		return 0xff;
	else
		return ((value>>(BLK_SHIFT+PLANE_SHIFT+DIE_SHIFT+CHN_SHIFT)));
}

u16 Ftl_Get_Phypage(u32 lba)
{
	u32 value;
	value = REG32_READ(0 + (lba<<2));
	if(value == 0xffffffff)
		return 0xffff;
	else
		return ((value>>(PAGE_SHIFT+PLANE_SHIFT))&PAGEMASK);
}

u16 Ftl_Get_Phyblock(u32 lba)
{
	u32 value;
	value = REG32_READ(0 + (lba<<2));
	if(value == 0xffffffff)
		return 0xffff;
	else
		return ((value>>(BLK_SHIFT+PLANE_SHIFT))&((1<<DIE_SHIFT)-1));
}

u8 Ftl_Get_AUoffset(u32 lba)
{
	u32 value;
	value = REG32_READ(0 + (lba<<2));
	if(value == 0xffffffff)
		return 0xff;
	else
		return ((value&((1<<PAGE_SHIFT)-1)));
}

void FC_Erase_Block(void)
{
	cmd_des_pro_info_e.au_cnt = 0;
	cmd_des_pro_info_e.ch = fc_cmd_all.ch;
	cmd_des_pro_info_e.device = fc_cmd_all.device;
	cmd_des_pro_info_e.row_add = fc_cmd_all.phyblk_add<<PAGEPBLOCK_SHIFT;
	cmd_des_pro_info_e.col_add = 0;
	cmd_des_pro_info_e.encoded_ecc_au_sz = 0;
	cmd_des_pro_info_e.au_format_no = 0;	
	cmd_des_pro_info_e.tid = cur_tid;
	cmd_des_pro_info_e.au_seg = 0;   
	cmd_des_pro_info_e.fst_des = fc_cmd_all.fst_des;
	cmd_des_pro_info_e.lst_des = fc_cmd_all.lst_des;
  
    	FC_Seq_Des_Program_Gen(&cmd_des_pro_info_e);
}

void FC_Read_Page(void)
{	
	cmd_des_pro_info_r.au_cnt = fc_cmd_all.au_cnt;
	cmd_des_pro_info_r.ch = fc_cmd_all.ch;
	cmd_des_pro_info_r.device = fc_cmd_all.device;
	cmd_des_pro_info_r.row_add = (fc_cmd_all.phyblk_add<<PAGEPBLOCK_SHIFT) + fc_cmd_all.phypage_add;
	cmd_des_pro_info_r.col_add = fc_cmd_all.au_offset * _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_r.encoded_ecc_au_sz = _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_r.au_format_no = fc_cmd_all.au_type;	
	cmd_des_pro_info_r.tid = cur_tid; 
	cmd_des_pro_info_r.fst_des = fc_cmd_all.fst_des;
	cmd_des_pro_info_r.lst_des = fc_cmd_all.lst_des;
	cmd_des_pro_info_r.au_seg = fc_cmd_all.seg_num;
	cmd_des_pro_info_r.readpad = fc_cmd_all.readpad;
  
    	FC_Seq_Des_Program_Gen(&cmd_des_pro_info_r);	
}

void FC_Read_Changeclm(void)
{	
	cmd_des_pro_info_changeclm.au_cnt = fc_cmd_all.au_cnt;
	cmd_des_pro_info_changeclm.ch = fc_cmd_all.ch;
	cmd_des_pro_info_changeclm.device = fc_cmd_all.device;
	cmd_des_pro_info_changeclm.row_add = (fc_cmd_all.phyblk_add<<PAGEPBLOCK_SHIFT) + fc_cmd_all.phypage_add;
	cmd_des_pro_info_changeclm.col_add = fc_cmd_all.au_offset * _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_changeclm.encoded_ecc_au_sz = _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_changeclm.au_format_no = fc_cmd_all.au_type;	
	cmd_des_pro_info_changeclm.tid = cur_tid; 
	cmd_des_pro_info_changeclm.fst_des = fc_cmd_all.fst_des;
	cmd_des_pro_info_changeclm.lst_des = fc_cmd_all.lst_des;
	cmd_des_pro_info_changeclm.au_seg = fc_cmd_all.seg_num;
  
    	FC_Seq_Des_Program_Gen(&cmd_des_pro_info_changeclm);	
}

void FC_Program_Page(void)
{
	cmd_des_pro_info_w.au_cnt = fc_cmd_all.au_cnt;
	cmd_des_pro_info_w.ch = fc_cmd_all.ch;
	cmd_des_pro_info_w.device = fc_cmd_all.device;
	cmd_des_pro_info_w.row_add = (fc_cmd_all.phyblk_add<<PAGEPBLOCK_SHIFT) + fc_cmd_all.phypage_add;
	cmd_des_pro_info_w.col_add = fc_cmd_all.au_offset * _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_w.encoded_ecc_au_sz = _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_w.au_format_no = fc_cmd_all.au_type;	
	cmd_des_pro_info_w.tid = cur_tid; 
	cmd_des_pro_info_w.fst_des = fc_cmd_all.fst_des;
	cmd_des_pro_info_w.lst_des = fc_cmd_all.lst_des;
	cmd_des_pro_info_w.au_seg = fc_cmd_all.seg_num;
  
    	FC_Seq_Des_Program_Gen(&cmd_des_pro_info_w);	
}

void FC_2plane_Erase_Block(void)
{
	cmd_des_pro_info_2p_e.au_cnt = 0;
	cmd_des_pro_info_2p_e.ch = fc_cmd_all.ch;
	cmd_des_pro_info_2p_e.device = fc_cmd_all.device;
	cmd_des_pro_info_2p_e.row_add = fc_cmd_all.phyblk_add<<PAGEPBLOCK_SHIFT;
	cmd_des_pro_info_2p_e.col_add = 0;
	cmd_des_pro_info_2p_e.encoded_ecc_au_sz = 0;
	cmd_des_pro_info_2p_e.au_format_no = 0;	
	cmd_des_pro_info_2p_e.tid = cur_tid;
	cmd_des_pro_info_2p_e.au_seg = 0;   
	cmd_des_pro_info_2p_e.fst_des = fc_cmd_all.fst_des;
	cmd_des_pro_info_2p_e.lst_des = fc_cmd_all.lst_des;
  
    	FC_Seq_Des_Program_Gen(&cmd_des_pro_info_2p_e);
}

void FC_2plane_Random_Data_In(void)
{
	cmd_des_pro_info_2p_datain.au_cnt = fc_cmd_all.au_cnt;
	cmd_des_pro_info_2p_datain.ch = fc_cmd_all.ch;
	cmd_des_pro_info_2p_datain.device = fc_cmd_all.device;
	cmd_des_pro_info_2p_datain.row_add = (fc_cmd_all.phyblk_add<<PAGEPBLOCK_SHIFT) + fc_cmd_all.phypage_add;
	cmd_des_pro_info_2p_datain.col_add = fc_cmd_all.au_offset * _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_2p_datain.encoded_ecc_au_sz = _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_2p_datain.au_format_no = fc_cmd_all.au_type;	
	cmd_des_pro_info_2p_datain.tid = cur_tid; 
	cmd_des_pro_info_2p_datain.fst_des = fc_cmd_all.fst_des;
	cmd_des_pro_info_2p_datain.lst_des = fc_cmd_all.lst_des;
	cmd_des_pro_info_2p_datain.au_seg = fc_cmd_all.seg_num;

	if(fc_cmd_all.au_offset == (AU_PLANE - 1))
	{
		cmd_des_pro_info_2p_datain.rdy_bit = 6;
		cmd_des_pro_info_2p_datain.fail_bit = 0;	
		cmd_des_pro_info_2p_datain.scd_cmd_off = 0;
		cmd_des_pro_info_2p_datain.fst_cmd_off = 0;	
		cmd_des_pro_info_2p_datain.status_poll_time = 1;
		cmd_des_pro_info_2p_datain.status_wait_time = 0;
		cmd_des_pro_info_2p_datain.add_type = 0;	
		cmd_des_pro_info_2p_datain.des_cmd = 1;//0 for read 1 for program 2 for erase
		cmd_des_pro_info_2p_datain.scmd = FC_CMD_STS_78;//0x78
		cmd_des_pro_info_2p_datain.cmd2 = 0x11;
		cmd_des_pro_info_2p_datain.cmd1 = 0x85;
	}
	else
	{
		cmd_des_pro_info_2p_datain.rdy_bit = 6;
		cmd_des_pro_info_2p_datain.fail_bit = 0;	
		cmd_des_pro_info_2p_datain.scd_cmd_off = 1;
		cmd_des_pro_info_2p_datain.fst_cmd_off = 0;	
		cmd_des_pro_info_2p_datain.status_poll_time = 0;
		cmd_des_pro_info_2p_datain.status_wait_time = 0;
		cmd_des_pro_info_2p_datain.add_type = 0;	
		cmd_des_pro_info_2p_datain.des_cmd = 1;//0 for read 1 for program 2 for erase
		cmd_des_pro_info_2p_datain.scmd = FC_CMD_STS_70;//0x78
		cmd_des_pro_info_2p_datain.cmd2 = 0x11;
		if(fc_cmd_all.au_offset == 0)
			cmd_des_pro_info_2p_datain.cmd1 = 0x80;
		else
			cmd_des_pro_info_2p_datain.cmd1 = 0x85;
	}  
    	FC_Seq_Des_Program_Gen(&cmd_des_pro_info_2p_datain);	
}

void FC_2plane_Program(void)
{
	cmd_des_pro_info_2p_prg.au_cnt = fc_cmd_all.au_cnt;
	cmd_des_pro_info_2p_prg.ch = fc_cmd_all.ch;
	cmd_des_pro_info_2p_prg.device = fc_cmd_all.device;
	cmd_des_pro_info_2p_prg.row_add = (fc_cmd_all.phyblk_add<<PAGEPBLOCK_SHIFT) + fc_cmd_all.phypage_add;
	cmd_des_pro_info_2p_prg.col_add = fc_cmd_all.au_offset * _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_2p_prg.encoded_ecc_au_sz = _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_2p_prg.au_format_no = fc_cmd_all.au_type;	
	cmd_des_pro_info_2p_prg.tid = cur_tid; 
	cmd_des_pro_info_2p_prg.fst_des = fc_cmd_all.fst_des;
	cmd_des_pro_info_2p_prg.lst_des = fc_cmd_all.lst_des;
	cmd_des_pro_info_2p_prg.au_seg = fc_cmd_all.seg_num;	
  
    	FC_Seq_Des_Program_Gen(&cmd_des_pro_info_2p_prg);	
}

void FC_2P_Read(void)
{	
	cmd_des_pro_info_2p_r.au_cnt = fc_cmd_all.au_cnt;
	cmd_des_pro_info_2p_r.ch = fc_cmd_all.ch;
	cmd_des_pro_info_2p_r.device = fc_cmd_all.device;
	cmd_des_pro_info_2p_r.row_add = (fc_cmd_all.phyblk_add<<PAGEPBLOCK_SHIFT) + fc_cmd_all.phypage_add;
	cmd_des_pro_info_2p_r.col_add = fc_cmd_all.au_offset * _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_2p_r.encoded_ecc_au_sz = _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_2p_r.au_format_no = fc_cmd_all.au_type;	
	cmd_des_pro_info_2p_r.tid = cur_tid; 
	cmd_des_pro_info_2p_r.fst_des = fc_cmd_all.fst_des;
	cmd_des_pro_info_2p_r.lst_des = fc_cmd_all.lst_des;
	cmd_des_pro_info_2p_r.au_seg = fc_cmd_all.seg_num;
  
    	FC_Seq_Des_Program_Gen(&cmd_des_pro_info_2p_r);	
}

void FC_2P_Changeclm(void)
{	
	cmd_des_pro_info_2p_changeclm.au_cnt = fc_cmd_all.au_cnt;
	cmd_des_pro_info_2p_changeclm.ch = fc_cmd_all.ch;
	cmd_des_pro_info_2p_changeclm.device = fc_cmd_all.device;
	cmd_des_pro_info_2p_changeclm.row_add = (fc_cmd_all.phyblk_add<<PAGEPBLOCK_SHIFT) + fc_cmd_all.phypage_add;
	cmd_des_pro_info_2p_changeclm.col_add = fc_cmd_all.au_offset * _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_2p_changeclm.encoded_ecc_au_sz = _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_2p_changeclm.au_format_no = fc_cmd_all.au_type;	
	cmd_des_pro_info_2p_changeclm.tid = cur_tid; 
	cmd_des_pro_info_2p_changeclm.fst_des = fc_cmd_all.fst_des;
	cmd_des_pro_info_2p_changeclm.lst_des = fc_cmd_all.lst_des;
	cmd_des_pro_info_2p_changeclm.au_seg = fc_cmd_all.seg_num;
  
    	FC_Seq_Des_Program_Gen(&cmd_des_pro_info_2p_changeclm);	
}

void FC_Dataout(void)
{	
	cmd_des_pro_info_dataout.au_cnt = fc_cmd_all.au_cnt;
	cmd_des_pro_info_dataout.ch = fc_cmd_all.ch;
	cmd_des_pro_info_dataout.device = fc_cmd_all.device;
	cmd_des_pro_info_dataout.row_add = (fc_cmd_all.phyblk_add<<PAGEPBLOCK_SHIFT) + fc_cmd_all.phypage_add;
	cmd_des_pro_info_dataout.col_add = fc_cmd_all.au_offset * _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_dataout.encoded_ecc_au_sz = _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_dataout.au_format_no = fc_cmd_all.au_type;	
	cmd_des_pro_info_dataout.tid = cur_tid; 
	cmd_des_pro_info_dataout.fst_des = fc_cmd_all.fst_des;
	cmd_des_pro_info_dataout.lst_des = fc_cmd_all.lst_des;
	cmd_des_pro_info_dataout.au_seg = fc_cmd_all.seg_num;
  
    	FC_Seq_Des_Program_Gen(&cmd_des_pro_info_dataout);	
}

void FC_Readsts(void)
{	
	cmd_des_pro_info_r_sts.au_cnt = fc_cmd_all.au_cnt;
	cmd_des_pro_info_r_sts.ch = fc_cmd_all.ch;
	cmd_des_pro_info_r_sts.device = fc_cmd_all.device;
	cmd_des_pro_info_r_sts.row_add = (fc_cmd_all.phyblk_add<<PAGEPBLOCK_SHIFT) + fc_cmd_all.phypage_add;
	cmd_des_pro_info_r_sts.col_add = fc_cmd_all.au_offset * _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_r_sts.encoded_ecc_au_sz = _supported_au_fmt[fc_cmd_all.au_type].encoded_ecc_au_sz;
	cmd_des_pro_info_r_sts.au_format_no = fc_cmd_all.au_type;	
	cmd_des_pro_info_r_sts.tid = cur_tid; 
	cmd_des_pro_info_r_sts.fst_des = fc_cmd_all.fst_des;
	cmd_des_pro_info_r_sts.lst_des = fc_cmd_all.lst_des;
	cmd_des_pro_info_r_sts.au_seg = fc_cmd_all.seg_num;
  
    	FC_Seq_Des_Program_Gen(&cmd_des_pro_info_r_sts);	
}

void FC_Set_FS_Page()
{
	u16 value;
	value = REG16_READ(0x1C002ECA);
	value &= ~(1<<9);
	value |= (fc_cmd_all.seg_num>>2)<<9;
	REG16_WRITE(0x1C002ECA, value);
}

void FC_Set_ES_Page()
{
	u16 value;
	value = REG16_READ(0x1C002ECA);
	value &= ~(1<<8);
	value |= (fc_cmd_all.seg_num>>2)<<8;
	REG16_WRITE(0x1C002ECA, value);
}

void FC_ES_Setup(void)
{
	if(tabledone == 1)
		return;
#if FTL > 0

#else
	fc_cmd_all.seg_num = FC_Get_Es(cur_tid);	
#endif
	rBM.extdSegSel.all = BIT_15|BIT_14;
	FC_Set_ES_Page();
	
	switch(fc_cmd_all.seg_num)
	{
		case 0:
		case 4:			
			rBM.extdSeg0SectorCnt= 0;
			rBM.extdSeg0LnkLstPtr.all = fc_cmd_all.ssd_index;
			rBM.extdSeg0XferPtrL = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr&0xffff;
			rBM.extdSeg0XferPtrH = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr>>16;			
			break;
		case 1:
		case 5:			
			rBM.extdSeg1SectorCnt= 0;
			rBM.extdSeg1LnkLstPtr.all = fc_cmd_all.ssd_index;
			rBM.extdSeg1XferPtrL = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr&0xffff;
			rBM.extdSeg1XferPtrH = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr>>16;				
			break;
		case 2:
		case 6:			
			rBM.extdSeg2SectorCnt= 0;
			rBM.extdSeg2LnkLstPtr.all = fc_cmd_all.ssd_index;
			rBM.extdSeg2XferPtrL = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr&0xffff;
			rBM.extdSeg2XferPtrH = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr>>16;			
			break;
		case 3:
		case 7:			
			rBM.extdSeg3SectorCnt= 0;
			rBM.extdSeg3LnkLstPtr.all = fc_cmd_all.ssd_index;
			rBM.extdSeg3XferPtrL = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr&0xffff;
			rBM.extdSeg3XferPtrH = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr>>16;			
			break;
		default:			
			rBM.extdSeg0SectorCnt= 0;
			rBM.extdSeg0LnkLstPtr.all = fc_cmd_all.ssd_index;
			rBM.extdSeg0XferPtrL = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr&0xffff;
			rBM.extdSeg0XferPtrH = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr>>16;	
			break;
	}
}

void FC_FS_Setup()
{
	if(tabledone == 1)
		return;
#if FTL > 0
#else
	fc_cmd_all.seg_num = FC_Get_Fs(cur_tid);	
#endif
	rBM.extdSegSel.all = BIT_15|BIT_14;
	FC_Set_FS_Page();
	
	switch(fc_cmd_all.seg_num)
	{
		case 0:			
			rBM.diskSeg0SectorCnt= 64;
			rBM.diskSeg0LnkLstPtr.all = fc_cmd_all.ssd_index;
			rBM.diskSeg0XferPtrL = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr&0xffff;
			rBM.diskSeg0XferPtrH = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr>>16;			
			break;
		case 1:			
			rBM.diskSeg1SectorCnt= 64;
			rBM.diskSeg1LnkLstPtr.all = fc_cmd_all.ssd_index;
			rBM.diskSeg1XferPtrL = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr&0xffff;
			rBM.diskSeg1XferPtrH = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr>>16;			
			break;
		case 2:			
			rBM.diskSeg2SectorCnt= 64;
			rBM.diskSeg2LnkLstPtr.all = fc_cmd_all.ssd_index;
			rBM.diskSeg2XferPtrL = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr&0xffff;
			rBM.diskSeg2XferPtrH = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr>>16;			
			break;
		case 3:			
			rBM.diskSeg3SectorCnt= 64;
			rBM.diskSeg3LnkLstPtr.all = fc_cmd_all.ssd_index;
			rBM.diskSeg3XferPtrL = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr&0xffff;
			rBM.diskSeg3XferPtrH = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr>>16;			
			break;
		default:			
			rBM.diskSeg0SectorCnt= 64;
			rBM.diskSeg0LnkLstPtr.all = fc_cmd_all.ssd_index;
			rBM.diskSeg0XferPtrL = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr&0xffff;
			rBM.diskSeg0XferPtrH = pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr>>16;	
			break;
	}
}


#if FTL >0
u16 ftl_get_ssd_index(void)
{
	u16 ssdindex;
	if(FcCmd.TableType == ES_TYPE)
	{
		ssdindex = ExtendSeg[FcCmd.TableId].StartIndex;
	}
	else if(FcCmd.TableType == FS_TYPE)
	{
		ssdindex = FlashSeg[FcCmd.TableId].StartIndex;
	}
	return ssdindex;
}

u32 fctl_operation(void) 
{
	fc_cmd_all.ch = FcCmd.Die & 0x07;
	fc_cmd_all.device = FcCmd.Die >> 3;
	fc_cmd_all.au_type = 0;
	fc_cmd_all.au_offset = 0;
	fc_cmd_all.au_cnt = 0;
	fc_cmd_all.seg_num = FcCmd.TableId;
	fc_cmd_all.fst_des = FcCmd.Start;
	fc_cmd_all.lst_des = FcCmd.End;
	fc_cmd_all.ssd_index = ftl_get_ssd_index();	
	fc_cmd_all.phypage_add = FcCmd.Page>>shift_4k_per_page;
	switch(FcCmd.Cmd)
	{
		case FC_PGRD:
			fc_cmd_all.cmd_type = FC_CMD_2P_READ;
			fc_cmd_all.phyblk_add = FcCmd.Blk0;
			fc_cmd_all.fst_des = FcCmd.Start;
			fc_cmd_all.lst_des = 0;
			FC_Operation();
			

			fc_cmd_all.cmd_type = FC_CMD_READ;
			fc_cmd_all.phyblk_add = FcCmd.Blk1;
			fc_cmd_all.fst_des = 0;
			fc_cmd_all.lst_des = FcCmd.End;
			FC_Operation();			
			break;
			
		case FC_DATO:
#if TOSHIBA > 0
			fc_cmd_all.cmd_type = FC_CMD_DATAOUT;
			fc_cmd_all.au_cnt = 0;
			fc_cmd_all.fst_des = FcCmd.Start;
			fc_cmd_all.lst_des = 0;
			FC_Operation();

			fc_cmd_all.cmd_type = FC_CMD_CHANGECLM;
			if((FcCmd.Page & mask_4k_per_page) < (1<<(shift_4k_per_page-1)))
				fc_cmd_all.phyblk_add = FcCmd.Blk0;
			else
				fc_cmd_all.phyblk_add = FcCmd.Blk1;
			fc_cmd_all.au_offset = FcCmd.Page & (mask_4k_per_page>>1);
			fc_cmd_all.au_cnt = 1;
			fc_cmd_all.fst_des = 0;
			fc_cmd_all.lst_des = FcCmd.End;
			FC_Operation();

#else
			fc_cmd_all.cmd_type = FC_CMD_2P_CHANGECLM;
			if((FcCmd.Page & mask_4k_per_page) < (1<<(shift_4k_per_page-1)))
				fc_cmd_all.phyblk_add = FcCmd.Blk0;
			else
				fc_cmd_all.phyblk_add = FcCmd.Blk1;
			
			fc_cmd_all.au_offset = FcCmd.Page & (mask_4k_per_page>>1);
			fc_cmd_all.fst_des = FcCmd.Start;
			fc_cmd_all.lst_des = 0;
			FC_Operation();

			
			fc_cmd_all.cmd_type = FC_CMD_DATAOUT;
			fc_cmd_all.au_cnt = 1;
			fc_cmd_all.fst_des = 0;
			fc_cmd_all.lst_des = FcCmd.End;
			FC_Operation();
#endif
			break;
			
		case FC_DATI:
			fc_cmd_all.cmd_type = FC_CMD_2P_DATAIN;
			if((FcCmd.Page & mask_4k_per_page) < (1<<(shift_4k_per_page-1)))
				fc_cmd_all.phyblk_add = FcCmd.Blk0;
			else
				fc_cmd_all.phyblk_add = FcCmd.Blk1;
			
			fc_cmd_all.au_offset = FcCmd.Page & (mask_4k_per_page>>1);
			fc_cmd_all.au_cnt = 1;
			FC_Operation();
			break;
			
		case FC_PROG:
			fc_cmd_all.cmd_type = FC_CMD_2P_PROGRAM;
			fc_cmd_all.phyblk_add = FcCmd.Blk1;
			FC_Operation();
			break;
			
		case FC_ERAS:
			fc_cmd_all.cmd_type = FC_CMD_2P_ERASE;
			fc_cmd_all.phyblk_add = FcCmd.Blk0;
			fc_cmd_all.fst_des = FcCmd.Start;
			fc_cmd_all.lst_des = 0;
			FC_Operation();

			fc_cmd_all.cmd_type = FC_CMD_ERASE;
			fc_cmd_all.phyblk_add = FcCmd.Blk1;
			fc_cmd_all.fst_des = 0;
			fc_cmd_all.lst_des = FcCmd.End;
			FC_Operation();
			break;
			
		default:
			break;
	}
	return cur_tid;
}
#else
u32 fctl_operation(void) 
{
	return cur_tid;
}
#endif

#if DEBUG > 0 
void FC_Debug_ReadPage(cmd_fc_info cmd)
{
	fc_cmd_all.ch = cmd.ch;
	fc_cmd_all.device = cmd.device;
	fc_cmd_all.au_type = 0;
	fc_cmd_all.au_offset = 0;
	fc_cmd_all.au_cnt = 4;
	fc_cmd_all.seg_num = 0;
	fc_cmd_all.fst_des = 1;
	fc_cmd_all.lst_des = 1;
	fc_cmd_all.ssd_index = 0;	
	fc_cmd_all.phypage_add = cmd.phypage;
	fc_cmd_all.phyblk_add = cmd.phyblock;	
	fc_cmd_all.cmd_type = FC_CMD_READ;	
	fc_cmd_all.readpad = 1;

	pmBfrSSD[fc_cmd_all.ssd_index].nextSsdIndex = fc_cmd_all.ssd_index;
    pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr = cmd.buf_add;
    pmBfrSSD[fc_cmd_all.ssd_index].ssdEndBufAddr  = cmd.buf_add+0x8000-2;
	
	FC_Operation();
	while(tid_sts[cur_tid]);
#ifdef AUXILIARY_SUPPORT
	IO_REG32(cmd.padbuf_add) = FC_Spm_Extract_Aux_Fifo_Dw();
	IO_REG32(cmd.padbuf_add+4) = FC_Spm_Extract_Aux_Fifo_Dw();
	IO_REG32(cmd.padbuf_add+8) = FC_Spm_Extract_Aux_Fifo_Dw();

	IO_REG32(cmd.padbuf_add+12) = FC_Spm_Extract_Aux_Fifo_Dw();
	IO_REG32(cmd.padbuf_add+16) = FC_Spm_Extract_Aux_Fifo_Dw();
	IO_REG32(cmd.padbuf_add+20) = FC_Spm_Extract_Aux_Fifo_Dw();

	IO_REG32(cmd.padbuf_add+24) = FC_Spm_Extract_Aux_Fifo_Dw();
	IO_REG32(cmd.padbuf_add+28) = FC_Spm_Extract_Aux_Fifo_Dw();
	IO_REG32(cmd.padbuf_add+32) = FC_Spm_Extract_Aux_Fifo_Dw();

	IO_REG32(cmd.padbuf_add+36) = FC_Spm_Extract_Aux_Fifo_Dw();
	IO_REG32(cmd.padbuf_add+40) = FC_Spm_Extract_Aux_Fifo_Dw();
	IO_REG32(cmd.padbuf_add+44) = FC_Spm_Extract_Aux_Fifo_Dw();
	fc_cmd_all.readpad = 0;
#endif
	
}

void FC_FS_Setup_SSD(void)
{			
	rBM.diskSeg0SectorCnt= 2048;
	rBM.diskSeg0LnkLstPtr.all = 0;
	rBM.diskSeg0XferPtrL = pmBfrSSD[0].ssdStartBufAddr&0xffff;
	rBM.diskSeg0XferPtrH = pmBfrSSD[0].ssdStartBufAddr>>16;
}

void FC_ES_Setup_SSD(void)
{		
	rBM.extdSeg0SectorCnt= 0;
	rBM.extdSeg0LnkLstPtr.all = 0;
	rBM.extdSeg0XferPtrL = pmBfrSSD[0].ssdStartBufAddr&0xffff;
	rBM.extdSeg0XferPtrH = pmBfrSSD[0].ssdStartBufAddr>>16;	
}

void FC_Debug_ReadPageEX(cmd_fc_info cmd)
{
	fc_cmd_all.ch = cmd.ch;
	fc_cmd_all.device = cmd.device;
	fc_cmd_all.au_type = 0;
	fc_cmd_all.au_offset = 0;
	fc_cmd_all.au_cnt = 4;
	fc_cmd_all.seg_num = 0;
	fc_cmd_all.fst_des = 1;
	fc_cmd_all.lst_des = 1;
	fc_cmd_all.ssd_index = 0;	
	fc_cmd_all.phypage_add = cmd.phypage;
	fc_cmd_all.phyblk_add = cmd.phyblock;	
	fc_cmd_all.cmd_type = FC_CMD_READ;	
	fc_cmd_all.readpad = 0;
	tabledone = 1;	

	pmBfrSSD[fc_cmd_all.ssd_index].nextSsdIndex = fc_cmd_all.ssd_index;
    pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr = DBG_DDR_RST_ADDR - 0x50000000 - 16*1024;
    pmBfrSSD[fc_cmd_all.ssd_index].ssdEndBufAddr  = DBG_DDR_RST_ADDR - 0x50000000 - 16*1024 + 0x4000-2;
	
	FC_Operation();
	tabledone = 0;

	
}

void FC_Debug_ProgramPage(cmd_fc_info cmd)
{
	fc_cmd_all.ch = cmd.ch;
	fc_cmd_all.device = cmd.device;
	fc_cmd_all.au_type = 0;
	fc_cmd_all.au_offset = 0;
	fc_cmd_all.au_cnt = 4;
	fc_cmd_all.seg_num = 0;
	fc_cmd_all.fst_des = 1;
	fc_cmd_all.lst_des = 1;
	fc_cmd_all.ssd_index = 0;	
	fc_cmd_all.phypage_add = cmd.phypage;
	fc_cmd_all.phyblk_add = cmd.phyblock;	
	fc_cmd_all.cmd_type = FC_CMD_PROGRAM;	

	pmBfrSSD[fc_cmd_all.ssd_index].nextSsdIndex = fc_cmd_all.ssd_index;
    pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr = cmd.buf_add;
    pmBfrSSD[fc_cmd_all.ssd_index].ssdEndBufAddr = cmd.buf_add+0x8000-2;
#ifdef AUXILIARY_SUPPORT
	FC_Spm_Insert_Aux_Fifo_Dw((u32*)cmd.padbuf_add,3);
	FC_Spm_Insert_Aux_Fifo_Dw((u32*)(cmd.padbuf_add+12),3);
	FC_Spm_Insert_Aux_Fifo_Dw((u32*)(cmd.padbuf_add+24),3);
	FC_Spm_Insert_Aux_Fifo_Dw((u32*)(cmd.padbuf_add+36),3);
#endif
    //FC_Spm_Insert_Aux_Fifo_3dw(REG32_READ(cmd.padbuf_add),REG32_READ(cmd.padbuf_add+4),REG32_READ(cmd.padbuf_add+8));
	
	FC_Operation();
	while(tid_sts[cur_tid]);
}

void FC_Debug_Program2PPage(cmd_fc_info cmd)
{
	fc_cmd_all.ch = cmd.ch;
	fc_cmd_all.device = cmd.device;
	fc_cmd_all.au_type = 0;
	fc_cmd_all.au_offset = 0;
	fc_cmd_all.au_cnt = 4;
	fc_cmd_all.seg_num = 0;
	fc_cmd_all.fst_des = 1;
	fc_cmd_all.lst_des = 0;
	fc_cmd_all.ssd_index = 0;
	fc_cmd_all.phyblk_add = cmd.phyblock;
	fc_cmd_all.phypage_add = cmd.phypage;
	fc_cmd_all.cmd_type = FC_CMD_2P_DATAIN;
	pmBfrSSD[fc_cmd_all.ssd_index].nextSsdIndex = fc_cmd_all.ssd_index;
	pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr = cmd.buf_add;
	pmBfrSSD[fc_cmd_all.ssd_index].ssdEndBufAddr = cmd.buf_add+0x8000-2;
	FC_Operation();
	
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 0;
	fc_cmd_all.phyblk_add =  cmd.data_len;
	fc_cmd_all.phypage_add = cmd.phypage;
	fc_cmd_all.cmd_type = FC_CMD_2P_DATAIN;
	FC_Operation();

	
	fc_cmd_all.au_offset = 0;
	fc_cmd_all.au_cnt = 0;
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 1;
	fc_cmd_all.phyblk_add = cmd.data_len;
	fc_cmd_all.phypage_add = cmd.phypage;
	fc_cmd_all.cmd_type = FC_CMD_2P_PROGRAM;
	FC_Operation();

	while(tid_sts[cur_tid])
    ;
 

}


void FC_Debug_ProgramPageEX(cmd_fc_info cmd)
{
	fc_cmd_all.ch = cmd.ch;
	fc_cmd_all.device = cmd.device;
	fc_cmd_all.au_type = 0;
	fc_cmd_all.au_offset = 0;
	fc_cmd_all.au_cnt = 4;
	fc_cmd_all.seg_num = 0;
	fc_cmd_all.fst_des = 1;
	fc_cmd_all.lst_des = 1;
	fc_cmd_all.ssd_index = 0;	
	fc_cmd_all.phypage_add = cmd.phypage;
	fc_cmd_all.phyblk_add = cmd.phyblock;	
	fc_cmd_all.cmd_type = FC_CMD_PROGRAM;	
	pmBfrSSD[fc_cmd_all.ssd_index].nextSsdIndex = fc_cmd_all.ssd_index;
    pmBfrSSD[fc_cmd_all.ssd_index].ssdStartBufAddr = DBG_DDR_RST_ADDR - 0x50000000 - 16*1024;
    pmBfrSSD[fc_cmd_all.ssd_index].ssdEndBufAddr  = DBG_DDR_RST_ADDR - 0x50000000 - 16*1024 + 0x4000-2;
	
#ifdef AUXILIARY_SUPPORT
	FC_Spm_Insert_Aux_Fifo_Dw((u32*)cmd.padbuf_add,3);
	FC_Spm_Insert_Aux_Fifo_Dw((u32*)(cmd.padbuf_add+12),3);
	FC_Spm_Insert_Aux_Fifo_Dw((u32*)(cmd.padbuf_add+24),3);
	FC_Spm_Insert_Aux_Fifo_Dw((u32*)(cmd.padbuf_add+36),3);
#endif
	tabledone = 1;
	FC_Operation();
	tabledone = 0;
}
void FC_Debug_EraseBlock(cmd_fc_info cmd)
{
	fc_cmd_all.ch = cmd.ch;
	fc_cmd_all.device = cmd.device;	
	fc_cmd_all.fst_des = 1;
	fc_cmd_all.lst_des = 1;		
	fc_cmd_all.phypage_add = cmd.phypage;
	fc_cmd_all.phyblk_add = cmd.phyblock;	
	fc_cmd_all.cmd_type = FC_CMD_ERASE;

	FC_Operation();
	while(tid_sts[cur_tid]);
}

void FC_Debug_EraseBlockEX(cmd_fc_info cmd)
{
	fc_cmd_all.ch = cmd.ch;
	fc_cmd_all.device = cmd.device;	
	fc_cmd_all.fst_des = 1;
	fc_cmd_all.lst_des = 1;		
	fc_cmd_all.phypage_add = cmd.phypage;
	fc_cmd_all.phyblk_add = cmd.phyblock;	
	fc_cmd_all.cmd_type = FC_CMD_ERASE;
	FC_Operation();
}
#endif

u8 FC_Operation(void)
{
	if(fc_cmd_all.fst_des == 1)
		cur_tid = FC_Get_Tid();

	switch(fc_cmd_all.cmd_type)
	{
		case FC_CMD_ERASE:
			FC_Erase_Block();
		break;
		
		case FC_CMD_READ:
			if(fc_cmd_all.fst_des == 1)
			{
				FC_ES_Setup();				
			}
			FC_Read_Page();
		break;

		case FC_CMD_PROGRAM:
			if(fc_cmd_all.fst_des == 1)
			{
				FC_FS_Setup();
			}
			FC_Program_Page();
		break;

		case FC_CMD_2P_ERASE:
			FC_2plane_Erase_Block();
		break;

		case FC_CMD_2P_DATAIN:
			if(fc_cmd_all.fst_des == 1)
			{
				FC_FS_Setup();
			}
			FC_2plane_Random_Data_In();
		break;

		case FC_CMD_2P_PROGRAM:
			FC_2plane_Program();
		break;

		case FC_CMD_CHANGECLM:
			FC_Read_Changeclm();
		break;

		case FC_CMD_2P_READ:
			if(fc_cmd_all.fst_des == 1)
			{
				FC_ES_Setup();
			}
			FC_2P_Read();
		break;

		case FC_CMD_2P_CHANGECLM:
			FC_2P_Changeclm();
		break;

		case FC_CMD_DATAOUT:
			FC_Dataout();
		break;

		case FC_CMD_R_STS:
			FC_Readsts();
		break;

		default:
			break;
	}
	
	
	return cur_tid;
}
   
void Test(void)
{
	u32 i,j;
	cmd_fc_info cmd;
#if 0
	pmBfrSSD[0].nextSsdIndex = 0;
    	pmBfrSSD[0].ssdStartBufAddr = 0x4000000;
    	pmBfrSSD[0].ssdEndBufAddr  = 0x4000000+0x8000-2;
	pmBfrSSD[1].nextSsdIndex = 1;
    	pmBfrSSD[1].ssdStartBufAddr = 0x4004000;
    	pmBfrSSD[1].ssdEndBufAddr  = 0x4000000+0x8000-2;
		pmBfrSSD[2].nextSsdIndex = 2;
    	pmBfrSSD[2].ssdStartBufAddr = 0x4008000;
    	pmBfrSSD[2].ssdEndBufAddr  = 0x4000000+0xa000-2;
		pmBfrSSD[3].nextSsdIndex = 3;
    	pmBfrSSD[3].ssdStartBufAddr = 0x400a000;
    	pmBfrSSD[3].ssdEndBufAddr  = 0x4000000+0xf000-2;
	for(i=0;i<64;i++)
    	{
    		for(j=0;j<512;j+=4)
    		{
    			REG32_WRITE(0x54000000+(i<<9)+j, i);
    		}
    	}
#endif
while (1)
{
	cmd.ch  = 0;
	cmd.device = 0;
	cmd.phyblock = 34;
	cmd.phypage = 0;
	cmd.buf_add = 0x4f000000;
	
	memory_set((void *)0x4f000000,0,16*1024);
	FC_Debug_ReadPage(cmd);

	FC_Debug_EraseBlock(cmd);
	memory_set((void *)0x4f100000,55,16*1024);
	cmd.buf_add = 0x4f100000;
	
	FC_Debug_ProgramPage(cmd);

	
	//memory_set((void *)0x4f100000,12,32*1024);
	//FC_Debug_Program2PPage( cmd);
	//read
	//cmd.buf_add = 0x4f000000;
	//memory_set((void *)0x4f000000,0,16*1024);
	//cmd.phyblock = 34;
	//FC_Debug_ReadPage(cmd);

	memory_set((void *)0x4f000000,0,16*1024);
	cmd.buf_add = 0x4f000000;
	FC_Debug_ReadPage(cmd);
}
#if 0	
	FC_Debug_ReadId(cmd);
	cmd.phyblock = 5;
	FC_Debug_EraseBlock(cmd);
	cmd.phypage = 0;
	cmd.data_len = 16384;
	cmd.buf_add = 0x5400a000;
	FC_Debug_ReadPage_Bp(cmd);
#endif
	
	
		
	
	
#if 0
/*	fc_cmd_all.ch = 0;
	fc_cmd_all.device = 0;
	fc_cmd_all.phyblk_add = 0;
	fc_cmd_all.phypage_add = 0;
	fc_cmd_all.au_offset = 0;
	fc_cmd_all.au_type = 0;

	fc_cmd_all.phyblk_add = 0;	
	fc_cmd_all.cmd_type = FC_CMD_2P_ERASE;
	fc_cmd_all.fst_des = 1;
	fc_cmd_all.lst_des = 0;	
	FC_Operation();
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 1;
	fc_cmd_all.phyblk_add = 1;
	fc_cmd_all.cmd_type = FC_CMD_ERASE;//erase
	FC_Operation();*/

	cmd.ch = 0;
	cmd.device = 0;
	cmd.phyblock = 5;
	cmd.phypage  = 0;
	cmd.buf_add = 0x54000000;
	cmd.padbuf_add = 0x54001000;
	FC_Debug_ProgramPage(cmd);

	cmd.buf_add = 0x5400A000;
	cmd.padbuf_add = 0x54008000;
	FC_Debug_ReadPage(cmd);

	
	fc_cmd_all.phyblk_add = 0;
	fc_cmd_all.phypage_add = 0;
	fc_cmd_all.au_cnt = 1;
	fc_cmd_all.au_offset = 0;	
	fc_cmd_all.cmd_type = FC_CMD_2P_DATAIN;
	fc_cmd_all.fst_des = 1;
	fc_cmd_all.lst_des = 0;
	fc_cmd_all.ssd_index = 0;
	FC_Operation();
	fc_cmd_all.au_cnt = 1;
	fc_cmd_all.au_offset = 1;	
	fc_cmd_all.cmd_type = FC_CMD_2P_DATAIN;
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 0;
	FC_Operation();
	fc_cmd_all.au_cnt = 1;
	fc_cmd_all.au_offset = 2;	
	fc_cmd_all.cmd_type = FC_CMD_2P_DATAIN;
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 0;
	FC_Operation();
	fc_cmd_all.au_cnt = 1;
	fc_cmd_all.au_offset = 3;	
	fc_cmd_all.cmd_type = FC_CMD_2P_DATAIN;
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 0;
	FC_Operation();
	fc_cmd_all.phyblk_add = 1;
	fc_cmd_all.phypage_add = 0;
	fc_cmd_all.au_cnt = 1;
	fc_cmd_all.au_offset = 0;	
	fc_cmd_all.cmd_type = FC_CMD_2P_DATAIN;
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 0;
	FC_Operation();
	fc_cmd_all.au_cnt = 1;
	fc_cmd_all.au_offset = 1;	
	fc_cmd_all.cmd_type = FC_CMD_2P_DATAIN;
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 0;
	FC_Operation();
	fc_cmd_all.au_cnt = 1;
	fc_cmd_all.au_offset = 2;	
	fc_cmd_all.cmd_type = FC_CMD_2P_DATAIN;
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 0;
	FC_Operation();
	fc_cmd_all.au_cnt = 1;
	fc_cmd_all.au_offset = 3;	
	fc_cmd_all.cmd_type = FC_CMD_2P_DATAIN;
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 0;
	FC_Operation();

	fc_cmd_all.phyblk_add = 1;
	fc_cmd_all.phypage_add = 0;
	fc_cmd_all.au_cnt = 0;
	fc_cmd_all.au_offset = 0;	
	fc_cmd_all.cmd_type = FC_CMD_2P_PROGRAM;
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 1;
	FC_Operation();
/*
	fc_cmd_all.phyblk_add = 0;
	fc_cmd_all.phypage_add = 0;
	fc_cmd_all.au_cnt = 4;
	fc_cmd_all.au_offset = 0;	
	fc_cmd_all.cmd_type = FC_CMD_READ;
	fc_cmd_all.fst_des = 1;
	fc_cmd_all.lst_des = 0;
	fc_cmd_all.ssd_index = 3;
	FC_Operation();

	fc_cmd_all.phyblk_add = 1;
	fc_cmd_all.phypage_add = 0;
	fc_cmd_all.au_cnt = 4;
	fc_cmd_all.au_offset = 0;	
	fc_cmd_all.cmd_type = FC_CMD_READ;
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 1;
	fc_cmd_all.ssd_index = 3;
	FC_Operation();*/

	fc_cmd_all.ch = 0;
	fc_cmd_all.phyblk_add = 0;
	fc_cmd_all.phypage_add = 0;
	fc_cmd_all.au_cnt = 0;
	fc_cmd_all.cmd_type = FC_CMD_2P_READ;//read
	fc_cmd_all.fst_des = 1;
	fc_cmd_all.lst_des = 0;
	fc_cmd_all.ssd_index = 3;
	//REG32_WRITE(0x54006000, 0xffffffff);
	fc_cmd_all.au_type = 0;
	FC_Operation();
	fc_cmd_all.phyblk_add = 1;
	fc_cmd_all.cmd_type = FC_CMD_READ;//read
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 0;
	FC_Operation();	
	fc_cmd_all.au_cnt = 0;
	fc_cmd_all.phyblk_add = 0;
	fc_cmd_all.cmd_type = FC_CMD_DATAOUT;	
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 0;
	FC_Operation();
	fc_cmd_all.au_cnt = 4;	
	fc_cmd_all.cmd_type = FC_CMD_CHANGECLM;
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 0;
	FC_Operation();
	fc_cmd_all.au_cnt = 0;
	fc_cmd_all.phyblk_add = 1;
	fc_cmd_all.cmd_type = FC_CMD_DATAOUT;	
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 0;
	FC_Operation();
	fc_cmd_all.au_cnt = 4;	
	fc_cmd_all.cmd_type = FC_CMD_CHANGECLM;
	fc_cmd_all.fst_des = 0;
	fc_cmd_all.lst_des = 1;
	FC_Operation();

	while(1);
#endif







}



