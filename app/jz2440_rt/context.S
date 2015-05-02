


NOINT	EQU	0xc0	


	PRESERVE8
	REQUIRE8
	AREA |.text|, CODE, READONLY, ALIGN=2

;; void rt_hw_interrupt_enable(int level)
rt_hw_interrupt_enable	PROC
	EXPORT	rt_hw_interrupt_enable
	MSR	cpsr_c, r0
	BX	lr
	ENDP

;; int rt_hw_interrupt_disable(void)
rt_hw_interrupt_disable	PROC
	EXPORT	rt_hw_interrupt_disable
	MRS	r0, cpsr
	ORR	r1, r0, #NOINT
	MSR	cpsr_c, r1
	BX	lr
	ENDP


;; void rt_hw_context_switch_to(unsigned to)
rt_hw_context_switch_to PROC
	EXPORT	rt_hw_context_switch_to
	LDR	sp, [r0]

	LDMFD	sp!, {r4}
	MSR	spsr_cxsf, r4
	LDMFD	sp!, {r4}
	MSR	cpsr_cxsf, r4

	LDM	sp!, {r0-r12, lr, pc}
	ENDP
	
;; rt_hw_context_switch(unsigned from, unsigned to)
rt_hw_context_switch	PROC
	EXPORT	rt_hw_context_switch
	STMFD	sp!, {lr}
	STMFD	sp!, {r0-r12, lr}

	MRS	r4, cpsr
	STMFD	sp!, {r4}
	MRS	r4, spsr
	STMFD	sp!, {r4}

	STR	sp, [r0]
	LDR	sp, [r1]

	LDMFD	sp!, {r4}
	MSR	spsr_cxsf, r4
	LDMFD	sp!, {r4}
	MSR	spsr_cxsf, r4

	LDMFD	sp!, {r0-r12, lr, pc}^
	ENDP

;; void rt_hw_context_switch_interrupt(unsigned from, unsigned to)
rt_hw_context_switch_interrupt	PROC
	EXPORT	rt_hw_context_switch_interrupt

	ENDP
	

	END

	
