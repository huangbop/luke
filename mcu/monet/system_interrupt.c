#include "mSFRS.h"
#include "mTimer.h"



void system_interrupt_init(void)
{
	rSFRS.cpuIntrCntl0.all = 0x00f0; /* A000, CPU0 irq for all */

	rCPU.cpuIntrEnable.all = 0; /* 1FFE_0002 */

	/* Set timer */
	rTimer.counterClkCtrl.bits.cntrTbgDivSel = 5; /* A230, From 500M to 100M */
	rTimer.counterClkCtrl.bits.cntrTbgSel = 1; /* From TBGB */
	rTimer.counterClkCtrl.bits.cntrClkSel = 1;

	/* scale 10, *invalid*, repeat */
	rTimer.counter0.all = (10 << 8) | (9 << 4) | (1 << 2); /* A202 */
	
	rCPU.periIntrEn.all = 1 << 8; /* 1FFE_0006, timer0 enable */
	rTimer.counter0_value_lo = 10*1000*10/100; /* A204 */
	rTimer.counter0_value_hi = (10*1000*1000/100)>>16; /* A206 */

	rTimer.counter0.all |= 1; /* timer0 enable */
		
}
