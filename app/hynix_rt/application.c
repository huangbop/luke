#include "rtthread.h"
#include "types.h"


static struct rt_thread print0;
static unsigned char print0_stack[512];

static struct rt_thread print1;
static unsigned char print1_stack[512];

extern struct rt_thread test_hynix;
extern void test_hynix_entry(void);
extern u8 test_hynix_stack[2048];



void print0_entry(void)
{
	while (1) {
		rt_kprintf("0 0 0 0 \n");

	}
}

void print1_entry(void)
{
	while (1) {
		rt_kprintf("1 1 1 1 \n");

	}
}

void application_init(void)
{
	int res;

	res = rt_thread_init(&print0, "print0", print0_entry, 0,
			     print0_stack, 512, 8, 1);

	res = rt_thread_init(&print1, "print1", print1_entry, 0,
			     print1_stack, 512, 8, 1);

	res = rt_thread_init(&test_hynix, "test hynix", test_hynix_entry, 0,
			     test_hynix_stack, 2048, 4, 10);

	rt_thread_startup(&print0);
	rt_thread_startup(&print1);
	rt_thread_startup(&test_hynix);

}
