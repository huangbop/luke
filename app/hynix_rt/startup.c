
void show_version(void)
{
	rt_kprintf("Copyright (C) Memoright 2015\n");
	rt_kprintf("Hynix flash diagnostic tool, firmware version V1.0.0\n");
	rt_kprintf("\n");
}


int main()
{
	board_init();

	show_version();
	
	rt_system_timer_init();

	rt_system_scheduler_init();

	application_init();

	rt_thread_idle_init();

	rt_system_scheduler_start();

	return 0;
}
