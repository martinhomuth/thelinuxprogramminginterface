#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define TEMPFILE "/tmp/peter.txt"

int main(int argc, char *argv[])
{
	int fd;
	fd = open(TEMPFILE, O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("fd");
		return EXIT_FAILURE;
	}

	if (lseek(fd, 0, SEEK_SET) == -1) {
		perror("lseek");
		return EXIT_FAILURE;
	}

	/* because of the O_APPEND every write atomically
	   sets the offset to SEEK_END */
	if (write(fd, "test", 4) == -1) {
		fprintf(stderr, "error writing stuff\n");
		return EXIT_FAILURE;
	}
	close(fd);
	return EXIT_SUCCESS;
}
