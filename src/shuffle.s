.intel_syntax noprefix

.global shuffle

.text
shuffle:
	# POINTER TO DECK IN RDI
	CALL rand
	# LARGE RANDOM NUMBER IN RAX

	XOR EDX, EDX
	DIV 52
	# RDX NOW HAS REMAINDER
	INT3
	RET
