#include "allhead.h"
#include <sys/time.h>
#include <time.h>

int main()
{
	struct timeval tv;
	char *timestring;
	if (gettimeofday(&tv, NULL) == -1)
		perror("gettimeofday");

	timestring = ctime(&(tv.tv_sec));
	printf("time is %s\n", timestring);
	return 0;
}
