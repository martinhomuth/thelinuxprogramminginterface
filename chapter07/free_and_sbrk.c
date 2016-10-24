#define _GNU_SOUCES
#include "../lib/allhead.h"

#define MAX_ALLOCS 100000

int main(int argc, char *argv[])
{
	char *ptr[MAX_ALLOCS];
	int free_step, free_min, free_max, block_size, num_allocs, i;

	printf("\n");

	if (argc < 3 || strcmp(argv[1], "--help") == 0)
		usage_err("%s num-allocs block-size [step [min [max]]]\n", argv[0]);

	num_allocs = get_int(argv[1], GN_GT_0, "num-allocs");
	if (num_allocs > MAX_ALLOCS)
		cmd_line_err("num-allocs > %d\n", MAX_ALLOCS);

	block_size = get_int(argv[2], GN_GT_0 | GN_ANY_BASE, "block-size");

	free_step = (argc > 3) ? get_int(argv[3], GN_GT_0, "step") : 1;
	free_min = (argc > 4) ? get_int(argv[4], GN_GT_0, "min") : 1;
	free_max = (argc > 5) ? get_int(argv[5], GN_GT_0, "max") : num_allocs;

	if (free_max > num_allocs)
		cmd_line_err("free-max > num-allocs\n");

	printf("Initial program break: %10p\n", sbrk(0));

	printf("Allocating %d*%d bytes\n", num_allocs, block_size);

	for (i = 0; i < num_allocs; i++) {
		ptr[i] = malloc(block_size);
		if (ptr[i] == NULL)
			err_exit("malloc");
	}

	printf("Program break is now: %10p\n", sbrk(0));

	printf("Freeing blocks from %d to %d in steps of %d\n",
	       free_min, free_max, free_step);

	for (i = free_min - 1; i < free_max; i += free_step)
		free(ptr[i]);

	printf("After free(), program break is %10p\n", sbrk(0));
	return EXIT_SUCCESS;
}
