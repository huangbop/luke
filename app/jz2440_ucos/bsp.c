
#include <ucos_ii.h>

void App_TCBInitHook(OS_TCB *ptcb){}

void App_TaskCreateHook(OS_TCB *ptcb){}

void App_TaskDelHook(OS_TCB *ptcp){}

void App_TaskIdleHook(void){}

void App_TaskStatHook(void){}

void App_TaskSwHook(void) //
{		 
	
}

void App_TimeTickHook(void){}

void myInitHookBegin(void) //My Init Code Here
{
	OS_CPU_InitExceptVect(); //Init Exception Vector

	
}

void OS_CPU_ExceptHndlr(INT32U except_type)
{ 
   
		
}