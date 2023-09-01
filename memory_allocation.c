#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#include <assert.h>

#define SIZE 10

void s() {
	system("leaks memory_allocation");
}

int main (void) {
	// atexit(s);
	int * ptr = mmap(NULL, SIZE * sizeof(int) , PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

	if (MAP_FAILED == ptr) {
		puts(strerror(errno));
		return -1;
	}

	assert(SIZE >= 2);
	ptr[0] = 0;
	ptr[1] = 1;

	for(int i = 2; i < SIZE; i++) {
		ptr [i] = ptr[i - 1] + ptr[i-2];
	}

	for( int i = 0; i < SIZE; i++) {
			printf("%d\n", ptr[i]);
		}

	if (0 > munmap(ptr, SIZE * sizeof(int))) {
		puts(strerror(errno));
		return -1;
	}
	return 0;
}
