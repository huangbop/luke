#include "mCONDS.h"
#include "mSFRS.h"
#include "mSFRS2.h"
#include "mCLKPWR.h"
#include "mTimer.h"
#include "mHDC.h"
#include "mBM.h"
#include "types.h"

#define DDR_CACHED_BASE		0x80000000
#define DDR_BASE                0x40000000
#define DDR_SSD_TAB_BASE	0x40200000
#define DDR_HEAP_START		0x40300000
#define DDR_HEAP_END		0x43000000
#define DDR_BUF_BASE            0x43000000 //2M
#define DDR_RANDOM_BASE         0x43210000 //64k
#define DDR_VENDOR_BASE         0x43220000 //128k
#define DDR_RAMDISK_BASE	0x43240000
#define DDR_RAMDISK_END		0x50000000

struct bm_buf {
	u16 size;		/* How many sects can be stored */
	u16 sect;		/* stored count */
	u16 link_list_ptr;
	u16 expect_link_list_ptr;
	u32 transfer_ptr;
	u8 host_seg;
	u8 disk_seg;
	u8 flag;
};

struct bm_ssd {
	u32 next;
	u32 base;
	u32 end;
	u32 flag;
};


struct bm_buf buf_table[8];
struct bm_ssd *ssd_table;


void init_ssd_table(void)
{
	int buf_idx = 0;
	int ssd_idx = 0;
	int ssd_index_end = 64;
	ssd_table = (bm_ssd *)DDR_SSD_TAB_BASE;
	u32 buf_addr = DDR_BUF_BASE;

	for (; buf_idx < 8; buf_idx++) {
		buf_table[buf_idx].size = 512;
		buf_table[buf_idx].sect = 0;
		buf_table[buf_idx].link_list_ptr = 0;
		buf_table[buf_idx].transfer_ptr = buf_addr;

		for (j = 0; j < ssd_index_end; j++) {
			ssd_table[j].next = j + 1;
			ssd_table[j].base = buf_addr;
			buf_addr += 4096;
			ssd_table[j].end = buf_addr - 2;
			ssd_table[j].flag = 0;
		}
		ssd_table[j - 1].next = j - 64;
		ssd_index_end += 64;
	}

}


void segment_init(void)
{
	/* Ratio 1:8:8, 512:4096:4096 */
	rBM.sectorSizeRatio = (1 << 8) | (8 << 4) | 8;
	rBM.hostSectorSize.bits.size = 512 / 2;
	rBM.diskSectorSize.bits.size = 4096 / 2;
	rBM.extdSecSize.bits.size = 4096 / 2;

	/* Burst len 64, 128, 128 */
	rBM.cntrlReg1.bits.hostBurstLenSel = 3;
	rBM.cntrlReg1.bits.diskBurstLenSel = 5;
	rBM.cntrlReg0.bits.extBurstLenSel = 5;

	/* Segment sel */
	rBM.diskSegSelect.all = 0xc000;
	rBM.extdSegSel.all = 0xc000;

	init_ssd_table();

}
