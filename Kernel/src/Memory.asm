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
global memset32
global memset16
global memset8

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

; p0 / rdi: void* destination
; p1 / rsi: uint32 value
; p2 / rdx: uint64 nBytes
memset32:
	mov rax, p1
	mov rcx, p2
	shr rcx, 2    ; divide by 4
	and p2, 0b11 ; the remainder
	rep stosd 	; store value into buffer

	test p2, p2
	.byteLoop:
	jz .end
		stosb
		ror rax, 8
		dec p2
	jmp .byteLoop
	.end:
ret

; p0 / rdi: void* destination
; p1 / rsi: uint16 value
; p2 / rdx: uint64 nBytes
memset16:
	mov rax, p1
	mov rcx, p2
	shr rcx, 1    ; divide by 2
	and p2, 0b1 ; the remainder
	rep stosw 	; store value into buffer

	test p2, p2
	jz .end
	stosb
	.end:
ret

; p0 / rdi: void* destination
; p1 / rsi: byte value
; p2 / rdx: uint64 nBytes
memset8:
	mov rax, p1 ; the value to be stored
	mov rcx, p2	; how many times to rep
	rep stosb 	; store value into buffer
ret
