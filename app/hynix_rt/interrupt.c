#include "mSFRS.h"


unsigned interrupt_switch_flag;
unsigned interrupt_switch_from;
unsigned interrupt_switch_to;


void do_irq(void)
{
	unsigned short peri_int_sts;


	peri_int_sts = rCPU.periIntrStatus.all;

	if (peri_int_sts & 0x0100) { /* timer0 interrupt */
		rt_tick_increase();
	}

}
