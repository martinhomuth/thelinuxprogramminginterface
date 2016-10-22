/**
 * @file copy.c
 */
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 128

/**
 * @brief Copies one file to another location by writing every byte to
 * the new file
 */
int main(int argc, char *argv[])
{
	int old_fd = 0, new_fd = 0;
	char *old_file_path, *new_file_path;
	char buf[BUFSIZE];
	if (argc < 3)
		printf("Usage: %s old_file new_file\n", argv[0]);
	old_file_path = argv[1];
	new_file_path = argv[2];

	old_fd = open(old_file_path, O_RDONLY);
	if (old_fd == -1) {
		perror("open old");
		return EXIT_FAILURE;
	}

	new_fd = open(new_file_path, O_RDWR | O_CREAT | O_TRUNC);
	if (new_fd == -1) {
		perror("open new");
		return EXIT_FAILURE;
	}

	ssize_t bytes_read, bytes_written;
	while ((bytes_read = read(old_fd, buf, sizeof(buf)))) {
		bytes_written = write(new_fd, buf, bytes_read);
		if (bytes_written != bytes_read) {
			fprintf(stderr, "bytes_read != bytes_written\n");
			return EXIT_FAILURE;
		}
	}

	if (close(old_fd))
		perror("close old");

	if (close(new_fd))
		perror("close new");

	return EXIT_SUCCESS;
}
