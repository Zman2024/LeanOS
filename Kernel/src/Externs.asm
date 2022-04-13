[bits 64]

; notes:
; parameter passing:
;	rdi 1st
;	rsi 2nd
;	rdx 3rd
;	rcx 4th
;	r8 5th
;	r9 6th
; temp regs:
;	r10
;	r11
; all other regs need to be saved if they are used

%define p0 rdi
%define p1 rsi
%define p2 rdx
%define p3 rdx

global memset64


; p0 / rdi: void* destination
; p1 / rsi: uint64 value
; p2 / rdx: uint64 nBytes
memset64:
	mov rax, p1
	mov rcx, p2
	shr rcx, 3    ; divide by 8
	and p2, 0b111 ; the remainder
	rep stosq 	; store value into buffer

	test p2, p2
	.byteLoop:
	jz .end
		stosb
		ror rax, 8
		dec p2
	jmp .byteLoop
	.end:
ret
