#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define TESTFILE "/tmp/testfile_ex07"

struct iovec {
	void *iov_base;
	int iov_len;
};

ssize_t mreadv(int fd, const struct iovec *iov, int iovcnt);

int main(int argc, char *argv[])
{
	int fd;
	struct iovec iov[2];
	int x;
#define STRLEN 30
	char buf[STRLEN];
	ssize_t total_required, num_read;

	fd = open(TESTFILE, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}

	total_required = 0;

	iov[0].iov_base = &x;
	iov[0].iov_len = sizeof(x);
	total_required += iov[0].iov_len;

	iov[1].iov_base = buf;
	iov[1].iov_len = STRLEN;
	total_required += iov[1].iov_len;

	num_read = mreadv(fd, iov, 2);
	if (num_read == -1) {
		perror("mreadv");
		return EXIT_FAILURE;
	}

	printf("read %ld, should have read %ld\n", num_read, total_required);

	printf("number read: %d\nstring read: %s\n",
	       *(int *)iov[0].iov_base,
	       (char *)iov[1].iov_base);

	return EXIT_SUCCESS;
}

ssize_t mreadv(int fd, const struct iovec *iov, int iovcnt)
{
	int i;
	ssize_t num_read, total_read = 0;
	for (i = 0; i < iovcnt; i++) {
		if ((num_read = read(fd, iov[i].iov_base, iov[i].iov_len)) < 0) {
			perror("read");
			return -1;
		} else {
			total_read += num_read;
		}
	}

	return total_read;
}
