#define _GNU_SOURCE
#include "../lib/allhead.h"
#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>

#define BUFSIZE 4096

int main(int argc, char *argv[])
{
	if (argc < 2 || strcmp(argv[1], "--help") == 0)
		usage_err("%s [-n num] file", argv[0]);

	int opt, lines = 10;
	char *filename;
	while ((opt = getopt(argc, argv, ":n:")) != -1) {
		switch (opt) {
		case 'n':
			lines = get_int(optarg, GN_ANY_BASE, "lines");
			break;
		case ':':
			usage_err(argv[0], "Missing argument", optopt);
		default:
			fatal("unexpected case in switch()");
		}
	}

	int fd = open(argv[optind], O_RDONLY | O_DIRECT);
	if (fd == -1)
		err_exit("open");

	struct stat file_stats;
	if (fstat(fd, &file_stats) == -1)
		err_exit("fstat");
	off_t file_length = file_stats.st_size;
	printf("file length: %ld\n", (long)file_length);

	void *buf = (char *) memalign(512, BUFSIZE);
	if (buf == NULL)
		err_exit("malloc");

	if (lseek(fd, -BUFSIZE, SEEK_END) == -1)
		err_exit("lseek");

	ssize_t num_read = read(fd, buf, (size_t)BUFSIZE);
	if (num_read == -1)
		err_exit("read");

	printf("%s\n", (char *)buf);

	free(buf);
	return EXIT_SUCCESS;
}
