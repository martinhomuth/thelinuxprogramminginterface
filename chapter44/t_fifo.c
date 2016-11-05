#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <poll.h>
#include "../lib/allhead.h"

int main(int argc, char *argv[])
{
	if (argc != 2 || strcmp(argv[1], "--help") == 0)
		usage_err("%s fifo-path", argv[0]);

	pid_t child1, child2;

	if ((child1 = fork()) < 0)
		err_exit("fork()");

	if (child1 == 0) {
		if ((child2 = fork()) < 0)
			err_exit("fork()");
	}

	int fd;
	if (child1 == 0 && child2 == 0) {
		umask(0);
		if (mkfifo("/tmp/fifo", S_IRGRP|S_IRUSR|S_IWOTH|S_IROTH))
			err_exit("mkfifo");
		while (1)
			;
	} else {
		sleep(2);
		char buf[128];
		if ((fd = open("/tmp/fifo", O_RDONLY)) < 0)
			err_exit("(%d) open", getpid());

		struct pollfd fds;
		fds.fd = fd;
		fds.events = POLLIN;
		int ret = poll(&fds, 1, 0);
		if (ret < 0)
			err_exit("poll");
		else
			printf("(%d) fifo available\n", getpid());
		if (read(fd, buf, 128) < 0)
			err_exit("read");

		printf("read: %s\n", buf);
	}

	return EXIT_SUCCESS;
}
