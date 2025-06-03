#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


int main() {
	FILE *file = fopen("dice_rolls.txt", "w");
	if (file == NULL) {
		perror("Cannot open file");
		return 1;
	}

	srand(time(NULL));

	for (int i = 0; ; i++) {
		int roll = rand() % 6 + 1;

		char buffer[32];
		int len = snprintf(buffer, sizeof(buffer), "Roll %d: %d\n", i + 1, roll);

		if (fwrite(buffer, 1, len, file) != len) {
			if (ferror(file)) {
				fprintf(stderr, "Write error: %s\n", strerror(errno));
				if (errno == EDQUOT || errno == EFBIG) {
					fprintf(stderr, "File size limit exceeded. Stopping.\n");
				}
				break;
			}
		}

		fflush(file);
		usleep(100000);
	}

	fclose(file);
	return 0;
}