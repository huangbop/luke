
Mode_USR 	EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F
	
I_Bit           EQU     0x80            ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40            ; when F bit is set, FIQ is disabled
NOINT		EQU 	0xc0
	

	PRESERVE8
	REQUIRE8
	AREA 	RESET, CODE, READONLY
	ARM
	ENTRY

	B	reset_handler
	

	
