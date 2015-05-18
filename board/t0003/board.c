#include "mCONDS.h"
#include "mSFRS.h"
#include "mSFRS2.h"
#include "mCLKPWR.h"
#include "mTimer.h"
#include "mHDC.h"
#include "mBM.h"
#include "types.h"


void ddr_init(void)
{
	rHDC.reset.bits.bm = 0;	/* 2806, reset off */

	/* 2EC0, Synchronize DDRPHY BM clock */
	rBM.dramDebug.bits.ddrSyncEn = 1;
	rBM.dramDebug.bits.ddrSyncRst = 0;
	udelay(10);
	rBM.dramDebug.bits.ddrSyncRst = 1;
	rBM.dramDebug.bits.ddrSyncEn = 0;

	/* 2EA0, Reset DLL */
	rBM.dramPhyDll0Cntl.bits.dll0Reset = 1;
	rBM.dramPhyDll1Cntl.bits.dll1Reset = 1;
	udelay(10);
	rBM.dramPhyDll0Cntl.bits.dll0Reset = 0;
	rBM.dramPhyDll1Cntl.bits.dll1Reset = 0;

	/* Configure */
	rBM.dramPhyDqPadCtl0.all = 0x01FF; /* R2EB0h */
	rBM.dramPhyDqPadCtl1.all = 0xF977;
	rBM.dramPhyDqPadCtl2.all = 0x332C;
	rBM.dramPhyClockPad.all  = 0xA077;
	rBM.dramPhyAdcmPadCtl0.all = 0x10C0;
	rBM.dramPhyAdcmPadCtl1.all = 0x1277;
	rBM.dramPhyAdcmPadCtl2.all = 0x3300;

	/* Read DLL control */
	rBM.dramPhyDll0Cntl.all = 0x1010; /* 2EA0 */
	rBM.dramPhyDll1Cntl.all = 0x1010; /* 2EA0 */

	udelay(200);

	/* Release DRAM_RESET */
	rBM.dramCntl0.bits.dramReset = 0; /* 2E22 */

	udelay(500);

	/* DDR size, timing */
	rBM.dramCntl1.bits.memSize = 6;	/* 2E20, 2Gb */
	rBM.dramCntl1.bits.tRPSel = 3;
	rBM.dramCntl1.bits.tWrSel = 4; /* 10T */

	rBM.dramCntl0.bits.tRasSel = 3;			/* 2EA2 */
	rBM.dramCntl0.bits.tWtrSel = 1;
	rBM.dramCntl0.bits.tRFC = 0x2b;

	/* Enable DDR3 */
	rBM.dramCntl1.bits.ddr3En = 1; /* 2E20, 2Gb */

	/* CAS, burst length */
	rBM.dramModeCntl.bits.ddrWrRecovery = 5; /* 2E2C */
	rBM.dramModeCntl.bits.cas_ltncy = 2;

	/* 2EA0, Initiaize DLL */
	rBM.dramPhyDll0Cntl.bits.dll0UpdateEn = 0;
	rBM.dramPhyDll1Cntl.bits.dll1UpdateEn = 0;
	udelay(10);
	rBM.dramPhyDll0Cntl.bits.dll0UpdateEn = 1;
	rBM.dramPhyDll1Cntl.bits.dll1UpdateEn = 1;
	udelay(10);
	rBM.dramPhyDll0Cntl.bits.dll0UpdateEn = 0;
	rBM.dramPhyDll1Cntl.bits.dll1UpdateEn = 0;

	/* 2E26, refresh period, BM 400M */
	rBM.refPeriod.bits.value = 3120; /* 7.8 * Freq */

	/* DRAM reset */
	rBM.dramCntl0.bits.dramReset = 1; /* 2E22 */

	udelay(100);
	
	/* 2E00, DRAM start */
	rBM.cntrlReg1.bits.DRAMstart = 1;

	/* Wait until the BM initialization sequence is complete */
	while (!rBM.stat2.bits.dramRdy)
		;

}

void board_init(void)
{
	system_clock_init();

	uart_init();

	system_timer_init();

	ddr_init();
	
}
