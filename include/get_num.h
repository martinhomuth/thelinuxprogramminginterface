#ifndef __GET_NUM_H
#define __GET_NUM_H

#define GN_NONNEG 01  /* value must be >= 0 */
#define GN_GT_0 02    /* value must be < 0 */

#define GN_ANY_BASE 0100
#define GN_BASE_8   0200
#define GN_BASE_16  0400

/**
 * @brief Returns arg converted to integer
 *
 * Prints an error message on invalid arg. The flags are used to
 * determine the base of the conversion and the name argument is used
 * when non-NULL to identify the argument in arg for the error message.
 */
int get_int(const char *arg, int flags, const char *name);

/**
 * @brief Returns arg converted to long
 *
 * Prints an error message on invalid arg. The flags are used to
 * determine the base of the conversion and the name argument is used
 * when non-NULL to identify the argument in arg for the error message.
 */
int get_long(const char *arg, int flags, const char *name);

#endif
