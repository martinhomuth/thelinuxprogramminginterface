#include "allhead.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TESTFILE "/tmp/testfile_ex06"

int main()
{
	int fd1, fd2, fd3;

	fd1 = open(TESTFILE, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	fd2 = dup(fd1);
	fd3 = open(TESTFILE, O_RDWR);
	write(fd1, "Hello,", 6);
	write(fd2, "world", 6);
	lseek(fd2, 0, SEEK_SET);
	write(fd1, "HELLO,", 6);
	write(fd3, "Gidday", 6);

	if (close(fd1) || close(fd2) || close(fd3))
		err_exit("close");

	char buf[128];
	int readfd = open(TESTFILE, O_RDONLY);
	if (readfd == -1)
		err_exit("open");
	ssize_t bytes_read;
	bytes_read = read(readfd, buf, sizeof(buf));
	if (bytes_read == -1)
		err_exit("read");
	buf[127] = '\0';
	printf("%s\n", buf);
	return EXIT_SUCCESS;
}
