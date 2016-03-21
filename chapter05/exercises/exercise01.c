//#define _FILE_OFFSET_BITS 64
//#define _LARGEFILE64_SOURCE
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;
	off_t off;

	if (argc != 3 || strcmp(argv[1], "--help") == 0) {
		fprintf(stderr, "%s pathname offset\n", argv[0]);
		return EXIT_FAILURE;
	}

	fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}

	off = atoll(argv[2]);
	if (lseek(fd, off, SEEK_SET) == -1) {
		perror("lseek");
		return EXIT_FAILURE;
	}

	if (write(fd, "test", 4) == -1) {
		fprintf(stderr, "unable to write to fd\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
