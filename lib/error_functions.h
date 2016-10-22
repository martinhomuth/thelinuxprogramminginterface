#ifndef __ERROR_FUNCTIONS_H
#define __ERROR_FUNCTIONS_H

/**
 * @brief Prints a message on standard error
 *
 * Automatically appends a newline character to the output string. The
 * message corresponds to the current errno value. The output contains
 * the errno value, the text returned by strerror and the formatted
 * output specified in the argument list.
 */
void err_msg(const char *format, ...);

#ifdef __GNUC__

#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

/**
 * @brief Operates like <err_msg>"()" and terminates the program
 *
 * The program is terminated by either calling exit() or by calling abort()
 */
void err_exit(const char *format, ...) NORETURN;

/**
 * @brief Operates like <err_exit>"()" but prints the errno instead of
 * a string
 */
void err_exit_en(int errnum, const char *format, ...) NORETURN;

/**
 * @brief Used to handle general errors that don't set errno
 */
void fatal(const char *format, ...) NORETURN;

/**
 * @brief Handles command line errors and prints "Usage: %s"
 */
void usage_err(const char *format, ...) NORETURN;

/**
 * @brief Similar to <usage_err>"()"
 */
void cmd_line_err(const char *format, ...) NORETURN;

#endif
