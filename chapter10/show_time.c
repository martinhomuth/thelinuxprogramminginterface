#include <time.h>
#include <locale.h>
#include "allhead.h"

#define BUF_SIZE 200

int main(int argc, char *argv[])
{
	time_t t;
	struct tm *loc;
	char buf[BUF_SIZE];

	if (setlocale(LC_ALL, "") == NULL)
		err_exit("setlocale"); /* use locale settings in
					  conversions */

	t = time(NULL);

	printf("ctime() of time() value is: %s", ctime(&t));

	loc = localtime(&t);
	if (loc == NULL)
		err_exit("localtime");

	printf("asctime() of local time is: %s", asctime(loc));

	if(strftime(buf, BUF_SIZE, "%A, %d %B %Y, %H:%M:%S %Z", loc) == 0)
		fatal("strftime returned 0");

	printf("strftime() of local time is: %s\n", buf);
	return 0;
}
