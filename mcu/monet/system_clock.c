#include "mSFRS.h"
#include "mCLKPWR.h"


#define hal_delay_us(us)    do{int _us=us;int delay; while(_us--){ delay = 100; while(delay--);}}while(0)


int system_clock_init(void)
{
	/* 1FFE_00FE */
	rCPU.CPUTimingCntl = (2 << 14) | (2 << 12) | (2 << 10) |
		(1 << 8) | (1 << 6) | (1 << 4) | 3;


	rCLKPWR.clkDiv1.bits.oscClk = 0; /* A804, Osc divided by 1 */
	rCLKPWR.clkDiv1.bits.hdcClk = 0; 
	rCLKPWR.clkDiv1.bits.cpuClk = 0; /* BM & CPU output from osc clock divider */

	/* TBGA - 800M, TBGB - 500M */
	rCLKPWR.TBGAcontrol.TBGnF = 0x60 - 2; 
	rCLKPWR.TBGAcontrol.TBGnS = 0x3 - 2;	/* A80C */
	rCLKPWR.TBGAcontrol1.sscEn = 0;
	rCLKPWR.TBGAcontrol1.puEn = 0;
	rCLKPWR.TBGAcontrol1.gain = 2;
	rCLKPWR.TBGAcontrol1.kvco = 7;
	rCLKPWR.TBGAcontrol1.vcoDivSel = 0; /* A812 */

	hal_delay_us(200);

	rCLKPWR.TBGBcontrol.TBGnF = 0x78 - 2; 
	rCLKPWR.TBGBcontrol.TBGnS = 0x3 - 2; /* A80E */
	rCLKPWR.TBGBcontrol1.sscEn = 0;
	rCLKPWR.TBGBcontrol1.puEn = 0;
	rCLKPWR.TBGBcontrol1.gain = 2;
	rCLKPWR.TBGBcontrol1.kvco = 7;
	rCLKPWR.TBGBcontrol1.vcoDivSel = 1; /* A814 */


	hal_delay_us(200);

	/* TBGA & TBGB must both locked */
	if (!rCLKPWR.TBGAcontrol1.lock || !rCLKPWR.TBGBcontrol1.lock)
		return -1;
	
	/* Set CPU clock */
	rCLKPWR.clkDiv0.cpuClk = 2; /* A802, divided by 2, 400M */
	rCLKPWR.pwrDownCnt.bits.cpuTbgSel = 0 ; /* A800, CPU divided from TBGA */
	rCLKPWR.clkDiv1.bits.cpuClk = 1; /* A804, output from CPU clock divider */

	/* Set UART clock */
	
	return 0;
}
