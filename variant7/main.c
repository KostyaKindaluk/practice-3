#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BLOCK_SIZE 1024 * 1024 * 4


int main() {
	printf("Starting memory allocation...\n");

	size_t total = 0;
	while (1) {
		void *block = malloc(BLOCK_SIZE);
		if (block == NULL) {
			fprintf(stderr, "Memory allocation failed at %.2f MB: %s\n",
				total / 1024.0, strerror(errno));
			break;
		}
		memset(block, 0, BLOCK_SIZE);
		total += BLOCK_SIZE / 1024;
		printf("Allocated: %zu KB\n", total);
		usleep(100000);
	}

	printf("Total allocated memory: %zu KB\n", total);
	return 0;
}