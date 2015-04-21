/*
 * Hynix flash tester with rt-thread OS,
 * hardware use t0003(t0004) board.
 */



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

	return 0;
}
