#include <stdio.h>
#include <sys/mman.h>
#include <errno.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

// https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/

int main(int ac, char **av) {
	if (ac != 2){
		puts("invalid number of arguments");
		return -1;
	}

	int fd = open(av[1], O_RDWR);
	if (0 > fd){
		printf("failed to opne file [%s] [%s]\n", av[1], strerror(errno));
		return -1;
	}

	struct stat file_stats;
	if ( 0 > fstat(fd, &file_stats)){
		puts(strerror(errno));
		return -1;
	}
	printf("%s file size: %lld\n", av[1], file_stats.st_size);

	void *ptr_to_injected_code = mmap(NULL, file_stats.st_size, PROT_EXEC, MAP_PRIVATE, fd, 0);

	close(fd);

	if (MAP_FAILED == ptr_to_injected_code) {
		puts("mmap faild");
		puts(strerror(errno));
		return -1;
	}

	((void (*)(void))ptr_to_injected_code)();

}
