#include "rtthread.h"


static struct rt_thread print0;
static unsigned char print0_stack[512];

static struct rt_thread print1;
static unsigned char print1_stack[512];


void print0_entry(void)
{
	while (1) {
		rt_kprintf("0 0 0 0 \n");
		rt_thread_yield();
	}
}

void print1_entry(void)
{
	while (1) {
		rt_kprintf("1 1 1 1 \n");
		rt_thread_yield();
	}
}


void application_init(void)
{
	int res;

	res = rt_thread_init(&print0, "print0", print0_entry, 0,
			     print0_stack, 512, 7, 20);

	res = rt_thread_init(&print1, "print1", print1_entry, 0,
			     print1_stack, 512, 8, 20);

	rt_thread_startup(&print0);
	rt_thread_startup(&print1);
}
