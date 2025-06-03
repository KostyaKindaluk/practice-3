#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Program needs two arguments\n");
		return 1;
	}

	FILE *src = fopen(argv[1], "r");
	if (src == NULL) {
		fprintf(stderr, "Cannot open file %s for reading: %s\n", argv[1], strerror(errno));
		return 1;
	}

	FILE *dst = fopen(argv[2], "w");
	if (dst == NULL) {
		fprintf(stderr, "Cannot open file %s for writing: %s\n", argv[2], strerror(errno));
		fclose(src);
		return 1;
	}

	char buffer[1024];
	size_t bytesRead;

	while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
		size_t bytesWritten = fwrite(buffer, 1, bytesRead, dst);
		if (bytesWritten < bytesRead) {
			if (ferror(dst)) {
				fprintf(stderr, "Write error: %s\n", strerror(errno));
				if (errno == EDQUOT || errno == EFBIG) {
					fprintf(stderr, "File size limit exceeded while writing.\n");
				}
			}
			fclose(src);
			fclose(dst);
			return 1;
		}
	}

	fclose(src);
	fclose(dst);
	return 0;
}