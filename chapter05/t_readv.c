#include "allhead.h"
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;
	struct iovec iov[3];
	struct stat my_struct; /* first buffer */
	int x;                 /* second buffer */
#define STR_SIZE 100
	char str[STR_SIZE];    /* third buffer */

	ssize_t num_read, tot_required;

	if (argc != 2 || strcmp(argv[1], "--help") == 0)
		usage_err("%s file\n", argv[0]);

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		err_exit("open");

	tot_required = 0;

	iov[0].iov_base = &my_struct;
	iov[0].iov_len = sizeof(struct stat);
	tot_required += iov[0].iov_len;

	iov[1].iov_base = &x;
	iov[1].iov_len = sizeof(int);
	tot_required += iov[1].iov_len;

	iov[2].iov_base = &str;
	iov[2].iov_len = STR_SIZE;
	tot_required += iov[2].iov_len;

	num_read = readv(fd, iov, 3);
	if (num_read == -1)
		err_exit("readv");

	if (num_read < tot_required)
		printf("Fewer bytes read than requested\n");
	printf("Total bytes requested: %ld, bytes read: %ld\n",
	       tot_required, num_read);
	return EXIT_SUCCESS;
}
