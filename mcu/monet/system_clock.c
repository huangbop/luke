#include "mSFRS.h"
#include "mCLKPWR.h"
#include "mUART.h"


#define hal_delay_us(us)    do{int _us=us;int delay; while(_us--){ delay = 100; while(delay--);}}while(0)


/*
 * Unit M, range (75M, 1200M), must mod 25,
 * formula: TBG = OSC * (N + 2) / (div * (M + 2)),
 * OSC fixed to 25.
 */
int set_tgb_clock(unsigned tbga, unsigned tbgb)
{
	if (tbga % 25 || tbgb % 25)
		return -1;

	/* TBGA */
	rCLKPWR.TBGAcontrol.TBGnF = (3 * tbga / 25) - 2; /* N */
	rCLKPWR.TBGAcontrol.TBGnS = 1;	/* A80C, M */
	rCLKPWR.TBGAcontrol1.sscEn = 0;
	rCLKPWR.TBGAcontrol1.puEn = 0;
	rCLKPWR.TBGAcontrol1.gain = 2;
	rCLKPWR.TBGAcontrol1.kvco = tbga < 800 ? 3 : 7;
	rCLKPWR.TBGAcontrol1.vcoDivSel = 0; /* A812, div = 1 */

	hal_delay_us(200);

	rCLKPWR.TBGBcontrol.TBGnF = (3 * tbgb / 25) - 2; /* N */
	rCLKPWR.TBGBcontrol.TBGnS = 1; /* A80E, M */
	rCLKPWR.TBGBcontrol1.sscEn = 0;
	rCLKPWR.TBGBcontrol1.puEn = 0;
	rCLKPWR.TBGBcontrol1.gain = 2;
	rCLKPWR.TBGBcontrol1.kvco = tbgb < 800 ? 3 : 7;
	rCLKPWR.TBGBcontrol1.vcoDivSel = 0; /* A814, div = 1 */

	hal_delay_us(200);

	/* TBGA & TBGB must both locked */
	if (!rCLKPWR.TBGAcontrol1.lock || !rCLKPWR.TBGBcontrol1.lock)
		return -1;

	return 0;
}

int system_clock_init(void)
{
	/* 1FFE_00FE */
	rCPU.CPUTimingCntl = (2 << 14) | (2 << 12) | (2 << 10) |
		(1 << 8) | (1 << 6) | (1 << 4) | 3;

	rCLKPWR.clkDiv1.bits.oscClk = 0; /* A804, Osc divided by 1 */
	rCLKPWR.clkDiv1.bits.hdcClk = 0;
	rCLKPWR.clkDiv1.bits.cpuClk = 0; /* BM & CPU output from osc clock divider */

	set_tgb_clock(800, 500);

	/* Set CPU clock */
	rCLKPWR.pwrDownCnt.bits.cpuTbgSel = 0 ; /* A800, CPU divided from TBGA */
	rCLKPWR.clkDiv0.cpuClk = 2; /* A802, divided by 2, 400M */
	rCLKPWR.clkDiv1.bits.cpuClk = 1; /* A804, output from CPU clock divider */

	/* Set UART clock */
	rUART.baudRate.bits.uart_tbg_sel = 1; /* A630, Divided from TBGB */
	rUART.baudRate.bits.uart_tbg_div_sel = 5; /* Divided from 500M to 100M */
	rUART.baudRate.bits.uart_clk_sel = 1;

	return 0;
}
