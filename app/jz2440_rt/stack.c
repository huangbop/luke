

#define SVCMODE 0x13 



/* rt_uint8_t *rt_hw_stack_init(void       *entry, */
/*                              void       *parameter, */
/*                              rt_uint8_t *stack_addr, */
/*                              void       *exit); */
unsigned char *rt_hw_stack_init(void *entry, void *param,
				unsigned char *stack_addr, void *exit)
{
	unsigned *stk;

	stk = (unsigned *)stack_addr;
	*stk = (unsigned)entry;	  /* entry */
	*--stk = (unsigned)exit;  /* lr */
	*--stk = 0;		  /* r12 */
	*--stk = 0;		  /* r11 */
	*--stk = 0;		  /* r10 */
	*--stk = 0;		  /* r9 */
	*--stk = 0;		  /* r8 */
	*--stk = 0;		  /* r7 */
	*--stk = 0;		  /* r6 */
	*--stk = 0;		  /* r5 */
	*--stk = 0;		  /* r4 */
	*--stk = 0;		  /* r3 */
	*--stk = 0;		  /* r2 */
	*--stk = 0;		  /* r1 */
	*--stk = (unsigned)param; /* r0 */
	*--stk = SVCMODE;	  /* cpsr */
	*--stk = SVCMODE;	  /* spsr */

	return (unsigned char *)stk;
}
