



int main()
{
	rt_hw_interrupt_disable();
	
	board_init();

	rt_show_version();

	rt_system_timer_init();

	rt_system_scheduler_init();

	application_init();

	rt_thread_idle_init();

	rt_system_scheduler_start();

	return 0;
}
