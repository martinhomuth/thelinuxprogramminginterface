#ifndef __ALLHEAD_H
#define __ALLHEAD_H

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

#include "get_num.h" /* handling of numeric arguments */

#include "error_functions.h" /* error-handling functions */

typedef enum { FALSE, TRUE } Boolean;

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#endif
