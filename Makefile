alloc: memory_allocation.c
	cc -Wall -Wextra -o memory_allocation memory_allocation.c

read: file_manipulation.c
	cc -Wall -Wextra -o file_manipulation file_manipulation.c

ipc: inter_process_communication.c
	cc -Wall -Wextra -o IPC inter_process_communication.c

exec: code_injection.c
	cc -Wall -Wextra -fsanitize=address -g -o code_injection code_injection.c

