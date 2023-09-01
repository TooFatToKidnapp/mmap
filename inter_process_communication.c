#include<stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

#define SIZE 10

int *shared_memory_ptr;

void print(char * str) {
		puts(str);
		for(int i = 0; i < SIZE; i++) {
			printf(" [%d] ", shared_memory_ptr[i]);
		}
		printf("\n");
}

int main(void) {

	// the same region of memory is shared between processes
	shared_memory_ptr = mmap(NULL, SIZE * sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);

	if (MAP_FAILED == shared_memory_ptr) {
		puts(strerror(errno));
		return -1;
	}

	for (int i = 0; i < SIZE; i++) { // storing values in ascending order in the parent
		shared_memory_ptr[i] = i + 1;
	}

	pid_t chid_pid = fork();
	if (0 > chid_pid) {
		puts(strerror(errno));
		return -1;
	} else if (chid_pid == 0) {
		for(int i = 0; i < SIZE / 2; i++) { // reverce the array in the child process
			int tmp = shared_memory_ptr[i];
			shared_memory_ptr[i] = shared_memory_ptr[SIZE - i - 1];
			shared_memory_ptr[SIZE - i - 1] = tmp;
		}
		print("in child:");
	} else {
		waitpid(chid_pid, NULL, 0);
		print("in adult:"); // values are reverced in the parrent process
	}
	if (0 > munmap(shared_memory_ptr, SIZE * sizeof(int))) {
		puts(strerror(errno));
		return -1;
	}
	return 0;
}
