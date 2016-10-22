#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "allhead.h"

int main(int argc, char *argv[])
{
	if (argc < 3 || strcmp(argv[1], "--help") == 0)
		usage_err("%s file {r<length>|R<length|w<string>|s<offset>}...\n",
			  argv[0]);

	int fd = open(argv[1], O_RDWR | O_CREAT,
		      S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1)
		err_exit("open");

	size_t len;
	char *buf;
	ssize_t num_read, num_written;
	long offset;
	for (int ap = 2; ap < argc; ap++) {
		switch (argv[ap][0]) {
		case 'r': /* Display bytes at current offset, as text */
		case 'R':
			len = get_long(&argv[ap][1], GN_ANY_BASE, argv[ap]);
			buf = malloc(len);
			if (buf == NULL)
				err_exit("malloc");

			num_read = read(fd, buf, len);
			if (num_read == -1)
				err_exit("read");

			if (num_read == 0) {
				printf("%s: end-of-file\n", argv[ap]);
			} else {
				printf("%s: ", argv[ap]);
				for (int j = 0; j < num_read; j++) {
					if (argv[ap][0] == 'r')
						printf("%c", isprint((unsigned char) buf[j]) ?
						       buf[j] : '?');
					else
						printf("%02x ", (unsigned int) buf[j]);
				}
				printf("\n");
			}

			free(buf);
			break;
		case 'w':  /* Write string at current offset */
			num_written = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
			if (num_written == -1)
				err_exit("write");
			printf("%s: write %ld bytes\n", argv[ap], (long) num_written);
			break;
		case 's':  /* Change file offset */
			offset = get_long(&argv[ap][1], GN_ANY_BASE, argv[ap]);
			if (lseek(fd, offset, SEEK_SET) == -1)
				err_exit("lseek");
			printf("%s: seek succeeded\n", argv[ap]);
			break;
		default:
			cmd_line_err("Argument must start with [rRws]: %s\n", argv[ap]);
		}
	}
	exit(EXIT_SUCCESS);
}
