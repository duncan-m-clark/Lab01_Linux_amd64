.intel_syntax noprefix

.global shuffle

.text
shuffle:
	PUSH RBX

	# INITIALIZE COUNTER
	MOV ECX, 51
	# POINTER TO DECK IN RDI

.loop:

	PUSH RCX
	PUSH RDI
	CALL rand
	POP RDI
	POP RCX
	# LARGE RANDOM NUMBER IN RAX

	XOR EDX, EDX
	LEA EBX, [ECX+1]
	DIV EBX
	# RDX NOW HAS REMAINDER

	MOV R8D, dword ptr [RDI+4*RDX]
	MOV R9D, dword ptr [RDI+4*RCX]
	MOV dword ptr [RDI+4*RCX], R8D
	MOV dword ptr [RDI+4*RDX], R9D

	SUB RCX, 1
	JNZ .loop

	POP RBX
	RET
