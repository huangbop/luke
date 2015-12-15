#include "s3c24x0.h"



unsigned interrupt_switch_flag;
unsigned interrupt_switch_from;
unsigned interrupt_switch_to;


void s4_push()
{

}


void do_irq(void)
{
	int offset;

	offset = INTOFFSET;

	switch (offset) {
	case 2:			/* S4 pushed */
		s4_push();
		break;
	case 10:		/* timer0 */
		
		break;
	default:
		break;
	}

	

	ClearPending(1 << offset);
}
