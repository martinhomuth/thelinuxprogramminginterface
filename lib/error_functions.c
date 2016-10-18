#include "allhead.h"
#include "error_functions.h"
#include <stdarg.h>
#include "ename.c.inc"

#ifdef __GNUC__
__attribute__ ((__noreturn__))
#endif

static void terminate(Boolean useExit3)
{
	char *s;

	s = getenv("EF_DUMPCORE");
	if (s != NULL && *s != '\0')
		abort();
	else if (useExit3)
		exit(EXIT_FAILURE);
	else
		_exit(EXIT_FAILURE);
}

static void output_error(Boolean use_err, int err, Boolean flush_stdout,
			 const char *format, va_list ap)
{
#define BUF_SIZE 500
	char buf[BUF_SIZE], user_msg[BUF_SIZE], err_text[BUF_SIZE];

	vsnprintf(user_msg, BUF_SIZE, format, ap);

	if (use_err)
		snprintf(err_text, BUF_SIZE, " [%s %s]",
			 (err > 0 && err <= MAX_ENAME) ?
			 ename[err] : "?UNKNOWN?", strerror(err));
	else
		snprintf(err_text, BUF_SIZE, ":");

	snprintf(buf, BUF_SIZE, "ERROR%s %s\n", err_text, user_msg);

	if (flush_stdout)
		fflush(stdout);
	fputs(buf, stderr);
	fflush(stderr);
}

void err_msg(const char *format, ...)
{
	va_list arg_list;
	int saved_errno;

	saved_errno = errno; /* in case we change it here */

	va_start(arg_list, format);
	output_error(TRUE, errno, TRUE, format, arg_list);
	va_end(arg_list);

	errno = saved_errno;
}

void err_exit(const char *format, ...)
{
	va_list arg_list;

	va_start(arg_list, format);
	output_error(TRUE, errno, TRUE, format, arg_list);
	va_end(arg_list);

	terminate(TRUE);
}

void err_exit_en(int errnum, const char *format, ...)
{
	va_list arg_list;

	va_start(arg_list, format);
	output_error(TRUE, errnum, TRUE, format, arg_list);
	va_end(arg_list);

	terminate(TRUE);
}

void fatal(const char *format, ...)
{
	va_list arg_list;

	va_start(arg_list, format);
	output_error(FALSE, 0, TRUE, format, arg_list);
	va_end(arg_list);

	terminate(TRUE);
}

void usage_err(const char *format, ...)
{
	va_list arg_list;

	fflush(stdout);   /* flush any pending stdout */

	fprintf(stderr, "Usage: ");
	va_start(arg_list, format);
	vfprintf(stderr, format, arg_list);
	va_end(arg_list);

	fflush(stderr);
	exit(EXIT_FAILURE);
}

void cmd_line_err(const char *format, ...)
{
	va_list arg_list;

	fflush(stdout);   /* flush any pending stdout */

	fprintf(stderr, "Command-line usage error: ");
	va_start(arg_list, format);
	vfprintf(stderr, format, arg_list);
	va_end(arg_list);

	fflush(stderr);
	exit(EXIT_FAILURE);
}
