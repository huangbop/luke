#include "s3c24x0.h"





void s4_push()
{
	int i = 20;

	i = i * i;
}


void do_irq(void)
{
	int offset;

	offset = INTOFFSET;

	if (offset == 2) {
		s4_push();
	}

	ClearPending(1 << offset);
}
