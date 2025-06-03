#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


volatile sig_atomic_t time_exceeded = 0;

void handle_cpu_limit(int signum) {
	time_exceeded = 1;
}


int is_unique(int *arr, int size, int value) {
	for (int i = 0; i < size; i++) {
		if (arr[i] == value) return 0;
	}
	return 1;
}

void generate_unique_numbers(int *arr, int count, int max) {
	int i = 0;
	while (i < count) {
		int num = rand() % max + 1;
		if (is_unique(arr, i, num)) {
			arr[i++] = num;
		}
	}
}

int main() {
	signal(SIGXCPU, handle_cpu_limit);

	FILE *file = fopen("lottery_results.txt", "w");
	if (file == NULL) {
		perror("Cannot open file");
		return 1;
	}

	srand(time(NULL));
	int rounds = 0;

	while (!time_exceeded) {
		int main1[7], main2[6];
		generate_unique_numbers(main1, 7, 49);
		generate_unique_numbers(main2, 6, 36);

		char buffer[256];
		int len = snprintf(buffer, sizeof(buffer),
			"Round %d:\n  7 of 49: ", rounds + 1);
		for (int i = 0; i < 7; i++) {
			len += snprintf(buffer + len, sizeof(buffer) - len, "%d ", main1[i]);
		}
		len += snprintf(buffer + len, sizeof(buffer) - len, "\n  6 of 36: ");
		for (int i = 0; i < 6; i++) {
			len += snprintf(buffer + len, sizeof(buffer) - len, "%d ", main2[i]);
		}
		len += snprintf(buffer + len, sizeof(buffer) - len, "\n\n");

		if (fwrite(buffer, 1, len, file) != len) {
			if (ferror(file)) {
				fprintf(stderr, "Write error: %s\n", strerror(errno));
				break;
			}
		}

		fflush(file);
		rounds++;
	}

	if (time_exceeded) {
		fprintf(stderr, "CPU time limit exceeded. Stopping.\n");
	}

	fclose(file);
	return 0;
}