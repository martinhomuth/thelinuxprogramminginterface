#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int mdup(int fd);
int mdup2(int oldfd, int newfd);

int main(int argc, char *argv[])
{
	int mynewfd = mdup(3);
	if (mynewfd < 0)
		perror("mdup");
	printf("mdup created fd %d\n", mynewfd);

	mynewfd = mdup2(3, 5);
	if (mynewfd < 0)
		perror("mdup2");
	printf("mdup2 created fd %d\n", mynewfd);

	return EXIT_SUCCESS;
}

int mdup(int fd)
{
	int newfd = fcntl(fd, F_DUPFD, 3);
	if (newfd < 0)
		return EBADF;
	return newfd;
}

int mdup2(int oldfd, int newfd)
{
	int mnewfd;
	if (oldfd == newfd && fcntl(oldfd, F_GETFL))
		return EBADF;
	mnewfd = fcntl(oldfd, F_DUPFD, newfd);
	if (newfd < 0)
		return -1;
	return mnewfd;
}
