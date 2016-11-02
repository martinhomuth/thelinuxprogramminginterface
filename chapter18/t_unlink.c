#include <stdio.h>
#include "allhead.h"

#define CMD_SIZE 100
#define BUF_SIZE 1000

int main(int argc, char *argv[])
{
	if (argc < 2 || strcmp(argv[1], "--help") == 0)
		usage_err("%s temp-file [num-1kb-blocks]\n", argv[0]);

	char shell_cmd[CMD_SIZE];
	char buf[BUF_SIZE];

	int num_blocks = argc > 2 ? get_int(argv[2], GN_GT_0, "num_blocks") : 10000;

	int fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, S_IWUSR);
	if (fd < 0)
		err_exit("open");

	if (unlink(argv[1]) < 0)
		err_exit("unlink");

	for (int i = 0; i < num_blocks; i++)
		if(write(fd, buf, BUF_SIZE) != BUF_SIZE)
			fatal("partial/failed write");

	snprintf(shell_cmd, CMD_SIZE, "df -k $(dirname %s)", argv[1]);
	system(shell_cmd);

	if (close(fd) < 0)
		err_exit("close");
	printf("******** Closed file descriptor\n");

	system(shell_cmd);

	return EXIT_SUCCESS;
}
