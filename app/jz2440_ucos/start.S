;;
;; Start for s3c2440 with ucos_ii v2.91
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
	

	;; Reset entry
        PRESERVE8
	REQUIRE8
	AREA 	RESET, CODE, READONLY
        ARM
	ENTRY

	B	reset_handler
	B	und_handler
	B	swi_handler
	B	pabt_handler
	B	dabt_handler
	NOP
	B	irq_handler
	B	fiq_handler


und_handler
swi_handler
pabt_handler
dabt_handler
	B	und_handler


irq_handler
	B	irq_handler

fiq_handler
	B	fiq_handler

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
	LDR	SP, =__svc_stack_end
	LDR	SL, =__svc_stack

	;; Goto c main
	IMPORT	__main
	LDR	R0, =__main
	BX	R0


	END
	
