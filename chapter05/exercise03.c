
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd;
	int atomic = 0;
	long num_bytes;

	if (argc < 3 || strcmp(argv[1], "--help") == 0) {
		fprintf(stderr, "%s filename num-bytes [x]", argv[0]);
		return EXIT_FAILURE;
	}

	if (argc == 4 && strcmp(argv[3], "x") == 0)
		atomic = 1;

	num_bytes = atoll(argv[2]);

	if (atomic)
		fd = open(argv[1], O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	else
		fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}

	if (!atomic && lseek(fd, 0, SEEK_END) == -1) {
		perror("lseek");
		return EXIT_FAILURE;
	}

	while (num_bytes--) {
		write(fd, "a", 1);
	}

	return EXIT_SUCCESS;
}
