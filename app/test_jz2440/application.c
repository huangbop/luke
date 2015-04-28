/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2007-11-20     Yi.Qiu		add rtgui application
 * 2008-6-28      Bernard		no rtgui init
 */

/**
 * @addtogroup mini2440
 */
 
/*@{*/

#include <rtthread.h>


void rt_init_thread_entry(void *parameter)
{
	while (1) {
		rt_kprintf("---\n");
	}
}

void rt_led_thread_entry(void *parameter)
{
	while (1)
	{
		rt_kprintf("***\n");
	}
}

int rt_application_init(void)
{
	rt_thread_t init_thread;
	rt_thread_t led_thread;

	init_thread = rt_thread_create("init",
				       rt_init_thread_entry, RT_NULL,
				       512, 8, 4);

	led_thread = rt_thread_create("led",
				      rt_led_thread_entry, RT_NULL,
				      512, 8, 4);

	if (init_thread != RT_NULL)
		rt_thread_startup(init_thread);

	if (led_thread != RT_NULL)
		rt_thread_startup(led_thread);

	return 0;
}

/*@}*/
