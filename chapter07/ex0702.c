#include "allhead.h"

struct free_block {
	size_t length_of_block;
	struct free_block *previous;
	struct free_block *next;
};

static struct free_block mem = {
	.length_of_block = 0,
	.previous = NULL,
	.next = NULL
};

static struct free_block *head = &mem;

void find_required_block(struct free_block **cur, size_t size)
{

}

/*
 * void *sbrk(intptr_t increment)
 * previous program break on success
 * (void *) -1 on error
 */
void *my_malloc(size_t size)
{

	struct free_block *ptr = NULL;
	/*
	 * Searches for a fitting free block >= size. If larger the
	 * block is split and the right one returned. If none is
	 * found, *ptr is still NULL
	 */
	find_required_block(&ptr, size);

	if (!ptr) {
		/* "allocate" the required space for the application */
		
	}

	if (ptr->length_of_block == size) {
		if (ptr->next != NULL)
			head = ptr->next;
	}
	return NULL;
}

void my_free(void *ptr)
{

}

int main(int argc, char *argv[])
{
#define SIZE 128
	printf("allocating %d bytes of memory\n", SIZE);
	char *ptr = my_malloc(SIZE);
	my_free(ptr);
	return 0;
}
