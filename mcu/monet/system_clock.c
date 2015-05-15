#include "mSFRS.h"
#include "mCLKPWR.h"
#include "mUART.h"
#include "types.h"

#define TBGA_CLOCK 800
#define TBGB_CLOCK 500

void set_cpu_timing_control_mode(void)
{
	/* 1FFE_00FE, wait status */
	rCPU.CPUTimingCntl = 0xa953;
}

void set_cpu_clock(u16 which_tbg, u16 div)
{
	rCLKPWR.pwrDownCnt.bits.cpuTbgSel = which_tbg; /* A800, CPU divided from _ */
	rCLKPWR.clkDiv0.cpuClk = div; /* A802, divided by _, 400M */
	rCLKPWR.clkDiv1.bits.cpuClk = 1; /* A804, output from CPU clock divider */

}

void set_uart_clock(u16 which_tbg, u16 div)
{
	rUART.baudRate.bits.uart_tbg_sel = which_tbg; /* A630, Divided from _ */
	rUART.baudRate.bits.uart_tbg_div_sel = div; /* Divided _ */
	rUART.baudRate.bits.uart_clk_sel = 1;
}

/*
 * Unit M, range (75M, 1200M), must mod 25,
 * formula: TBG = OSC * (N + 2) / (div * (M + 2)),
 * OSC fixed to 25.
 */
int set_tgb_clock(unsigned tbga, unsigned tbgb)
{
	int i, j;

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

	for (i = 0; i < 2000; i++)
		for (j = 0; j < 10; j++)
			;

	rCLKPWR.TBGBcontrol.TBGnF = (3 * tbgb / 25) - 2; /* N */
	rCLKPWR.TBGBcontrol.TBGnS = 1; /* A80E, M */
	rCLKPWR.TBGBcontrol1.sscEn = 0;
	rCLKPWR.TBGBcontrol1.puEn = 0;
	rCLKPWR.TBGBcontrol1.gain = 2;
	rCLKPWR.TBGBcontrol1.kvco = tbgb < 800 ? 3 : 7;
	rCLKPWR.TBGBcontrol1.vcoDivSel = 0; /* A814, div = 1 */

	for (i = 0; i < 2000; i++)
		for (j = 0; j < 10; j++)
			;

	/* TBGA & TBGB must both locked */
	if (!rCLKPWR.TBGAcontrol1.lock || !rCLKPWR.TBGBcontrol1.lock)
		return -1;

	return 0;
}

int system_clock_init(void)
{
	set_cpu_timing_control_mode();

	set_tgb_clock(TBGA_CLOCK, TBGB_CLOCK);

	/* From TBGA, 800M -> 400M */
	set_cpu_clock(0, 2);

	/* From TBGB, 500M -> 100M */
	set_uart_clock(1, 5);

	return 0;
}
