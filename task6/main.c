#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


int depth = 0;

void recurse() {
	char dummy[1024000];
	depth++;
	printf("Recursion depth: %d\n", depth);
	recurse();
}

int main() {
	printf("Starting deep recursion...\n");
	recurse();
	return 0;
}