#include <stdio.h>
#include <sys/mman.h>
#include <errno.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

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
	printf("%s file size: %ld\n", av[1], file_stats.st_size);

	char *ptr_to_file = mmap(NULL, file_stats.st_size, PROT_READ | PROT_WRITE , MAP_SHARED, fd, 0);

	close(fd);

	if (MAP_FAILED == ptr_to_file) {
		puts("mmap faild");
		puts(strerror(errno));
		return -1;
	}

	// char * elem_pos = strstr(ptr_to_file, "-");
	// while(elem_pos != NULL) {
	// 	elem_pos[0] = '+';
	// 	elem_pos = strstr(ptr_to_file, "+");
	// }
	for (int i = 0 ; i < file_stats.st_size / 2 ; ++i) {
		char tmp = ptr_to_file[i];
		ptr_to_file[i] = ptr_to_file[file_stats.st_size - i -1];
		ptr_to_file[file_stats.st_size - i -1] = tmp;
	}

	write(1, ptr_to_file, file_stats.st_size);
	if (0 > munmap(ptr_to_file, file_stats.st_size)) {
		puts(strerror(errno));
		return -1;
	}
	return 0;
}
