/*
 * Hynix flash tester with rt-thread OS,
 * hardware use t0003(t0004) board.
 */

extern int Image$$ER_ZI$$ZI$$Base;
extern int Image$$ER_ZI$$ZI$$Length;
extern int Image$$ER_ZI$$ZI$$Limit;

int main(void)
{
	/* disable interrupt first */
	rt_hw_interrupt_disable();
	
	/* enable cpu cache */
	rt_hw_cpu_icache_enable();
	rt_hw_cpu_dcache_enable();

	/* init hardware interrupt */
	rt_hw_interrupt_init();

	/* init board */
	rt_hw_board_init();

	/* show version */
	rt_show_version();

	/* init timer system */
	rt_system_timer_init();
	
	rt_system_heap_init((void*)&Image$$ER_ZI$$ZI$$Limit, (void*)0x33F00000);

	/* init scheduler system */
	rt_system_scheduler_init();
	
	/* init application */
	rt_application_init();
	
	rt_system_timer_thread_init();

	/* init idle thread */
	rt_thread_idle_init();

	/* start scheduler */
	rt_system_scheduler_start();
	
	
	return 0;
}
