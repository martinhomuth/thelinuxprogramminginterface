#include "allhead.h"

int main(int argc, char *argv[])
{
	int opt;
	Boolean append;

	if (argc != 2)
		usage_err("%s [-a] outfile\n", argv[0]);

	while ((opt = getopt(argc, argv, ":a")) != -1) {
		switch (opt) {
		case 'a':
			append = TRUE;
			break;
		case ':':
			usage_err("missing argument");
		case '?':
			usage_err("unknown option");
		default:
			fatal("Unexpected case in switch()");
		}
	}
	char *outfile = argv[optind];

	int fd;
	if (append == TRUE)
		fd = open(outfile, O_RDWR | O_CREAT | O_APPEND,
			  S_IRUSR | S_IWUSR);
	else
		fd = open(outfile, O_RDWR | O_CREAT | O_TRUNC,
			  S_IRUSR | S_IWUSR);
	if (fd == -1)
		err_exit("open");

	int bytes_read, bytes_written;
	char buf[128];
	while ((bytes_read = read(STDIN_FILENO, buf, sizeof(buf)))) {
		bytes_written = write(STDOUT_FILENO, buf, bytes_read);
		if (bytes_written != bytes_read)
			err_exit("bytes_written != bytes_read stdout");
		bytes_written = write(fd, buf, bytes_read);
		if (bytes_written != bytes_read)
			err_exit("bytes_written != bytes_read fd");
	}

	if (close(fd))
		err_exit("close");

	return EXIT_SUCCESS;
}
