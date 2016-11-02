#include "allhead.h"
#include <signal.h>

void handler(int signo)
{
	printf("ouch\n");
}

int main(int argc, char *argv[])
{
	if (signal(SIGINT, handler) == SIG_ERR)
		err_exit("signal");

	while (1)
		sleep(3);

	return EXIT_SUCCESS;
}
