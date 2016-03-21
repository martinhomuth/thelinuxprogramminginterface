#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TESTFILE "/tmp/testfile"

int main(int argc, char *argv[])
{
	int fd1, fd2;
	off_t offset;
	int flags1, flags2;

	printf("opening %s\n", TESTFILE);

	fd1 = open(TESTFILE, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd1 == -1) {
		perror("open");
		return EXIT_FAILURE;
	}

	flags1 = fcntl(fd1, F_GETFL);
	printf("flags1 %x\n", flags1);

	if (write(fd1, "test", 4) == -1) {
		perror("write");
		return EXIT_FAILURE;
	}

	fd2 = dup(fd1);

	flags2 = fcntl(fd2, F_GETFL);
	printf("flags2 %x\n", flags2);

	offset = lseek(fd2, 0, SEEK_CUR);
	printf("fd2 is at %lld\n", (long long)offset);

	if (lseek(fd1, 0, SEEK_SET) < 0) {
		perror("lseek");
		return EXIT_FAILURE;
	}

	offset = lseek(fd2, 0, SEEK_CUR);
	printf("fd2 is at %lld\n", (long long)offset);


	return EXIT_SUCCESS;
}
