BITS 64
%define SYS_WRITE 1
%define STDOUT 1
%define SYS_EXIT 60

_start:
		;; write syscall
		mov rax, SYS_WRITE
		mov rdi, STDOUT
		lea rsi, [rel hello]
		mov rdx, hello_size
		syscall

		;; exit
		mov rax, SYS_EXIT
		mov rdi, 0
		syscall
		ret

hello: db "Hello, World", 10
hello_size: equ $-hello
