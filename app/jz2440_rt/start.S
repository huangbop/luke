;;
;; Start for s3c2440 with rt-thread 
;; 

Mode_USR 	EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F

I_Bit           EQU     0x80            ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40            ; when F bit is set, FIQ is disabled
NOINT		EQU	0xc0
	
	;; Stack space for all modes
	AREA 	STACK, NOINIT, READWRITE, ALIGN=3
__und_stack		SPACE	16
__und_stack_end	
__svc_stack		SPACE	256
__svc_stack_end
__irq_stack		SPACE 	256
__irq_stack_end
__fiq_stack		SPACE	256
__fiq_stack_end
__usr_stack		SPACE	256
__usr_stack_end	

	;; Heap
	AREA	HEAP, NOINIT, READWRITE, ALIGN=3
__heap		SPACE 	0
__heap_end	


	;; RESET entry
        PRESERVE8
	REQUIRE8
	AREA 	RESET, CODE, READONLY
        ARM
	ENTRY
	B	reset_handler
	LDR	pc, _und_handler
	LDR	pc, _swi_handler
	LDR	pc, _pabt_handler
	LDR	pc, _dabt_handler
	NOP
	LDR	pc, _irq_handler
	LDR	pc, _fiq_handler


_und_handler	DCD	und_handler
_swi_handler	DCD	swi_handler
_pabt_handler	DCD	pabt_handler
_dabt_handler	DCD	dabt_handler
_irq_handler	DCD	irq_handler
_fiq_handler	DCD	fiq_handler	
	

und_handler
swi_handler
pabt_handler
dabt_handler	B	und_handler


fiq_handler
	B	fiq_handler


	IMPORT	do_irq

irq_handler
	STMFD	sp!, {r0-r12, lr}

	BL	do_irq


	LDMFD	sp!, {r0-r12, lr}
	SUBS	pc, lr, #4



reset_handler
	;; Set stack for every mode
	MSR	CPSR_c, #Mode_UND:OR:NOINT
	LDR	SP, =__und_stack_end

	MSR	CPSR_c, #Mode_ABT:OR:NOINT
	LDR	SP, =__und_stack_end
	
	MSR	CPSR_c, #Mode_FIQ:OR:NOINT
	LDR	SP, =__fiq_stack_end
	
	MSR	CPSR_c, #Mode_IRQ:OR:NOINT
	LDR	SP, =__irq_stack_end
	
	MSR	CPSR_c, #Mode_SVC:OR:NOINT
	;; MSR	CPSR_c, #Mode_SVC
	LDR	SP, =__svc_stack_end
	LDR	SL, =__svc_stack

	;; Goto c main
	IMPORT 	main
	LDR	R0, =main
	BX	R0


	EXPORT	__user_initial_stackheap
__user_initial_stackheap
	LDR	R0, =__heap
	LDR	R1, =__usr_stack_end
	LDR	R2, =__heap_end
	LDR	R3, =__usr_stack
	BX	LR

	END
	
