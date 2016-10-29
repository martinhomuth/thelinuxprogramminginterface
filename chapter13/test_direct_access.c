#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define TESTFILETMP "/tmp/testfile"
#define TESTFILEHOME "/home/martin/testfile"

int main()
{
	printf("Checking for direct access on tmpfs...");
	fflush(stdout);
	int fd1 = open(TESTFILETMP, O_RDWR | O_CREAT | O_DIRECT, S_IRUSR | S_IWUSR);
	if (fd1 == -1)
		perror("failed");
	else
		printf("ok\n");
	printf("Checking for direct access on fs in $HOME...");
	fflush(stdout);
	char homefile[128];
	strcpy(homefile, getenv("HOME"));
	strcat(homefile, "/testfile");
	int fd2 = open(homefile, O_RDWR | O_CREAT | O_DIRECT, S_IRUSR | S_IWUSR);
	if (fd2 == -1)
		perror("open");
	else
		printf("ok\n");
	unlink(TESTFILETMP);
	unlink(homefile);
	close(fd1);
	close(fd2);
	return EXIT_SUCCESS;
}
