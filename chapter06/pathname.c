#include <stdio.h>
#include <stdlib.h>

#define __USE_GNU
#define _GNU_SOURCE
#include <errno.h>
#include <unistd.h>



int main(int argc, char *argv[])
{
	printf("%s\n", program_invocation_name);
	printf("%s\n", program_invocation_short_name);
	printf("I have pid %d\n", getpid());
	return EXIT_SUCCESS;
}
