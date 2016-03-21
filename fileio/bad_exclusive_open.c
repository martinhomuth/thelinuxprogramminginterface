#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int fd = open(argv[1], O_WRONLY);
	if (fd != -1) { /* open succeeded */
		printf("[PID %ld] File \"%s\" already exists\n",
		       (long) getpid(), argv[1]);
		close(fd);
	} else {
		if (errno != ENOENT) { /* Failed for unexpected reason */
			perror("open");
			return EXIT_FAILURE;
		} else {
			/* WINDOW FOR FAILURE */
			fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
			if (fd == -1) {
				perror("open");
				return EXIT_FAILURE;
			}

			printf("[PID %ld] Created file \"%s\" exclusively\n",
			       (long) getpid(), argv[1]);
		}
	}
	return EXIT_SUCCESS;
}
