.section .text
	.global _start
_start:
	lui sp, %hi(_fstack)
	add sp, sp, %lo(_fstack)
	jal main

loopf:
	j loopf
