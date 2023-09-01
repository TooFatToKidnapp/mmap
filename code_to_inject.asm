%define SYS_WRITE 1
%define STDOUT 1

global _start
segment .text
_start:
		;; write syscall
		mov rax, SYS_WRITE
		mov rdi, STDOUT
		lea rsi, [hello]
		mov rdx, hello_size
		syscall
		ret

segment .data
hello: db "Hello, World", 10
hello_size: equ $-hello
