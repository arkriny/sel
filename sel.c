/*
 * sel - select interactively
 *
 * Written by Artem Krinitsyn. Public domain.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *opts[1024];

int main(void)
{
	FILE *in = fopen("/dev/tty", "r");
	FILE *out = fopen("/dev/tty", "w");
	if (!in || !out) return 1;

	char *buf = NULL;
	size_t size;
	ssize_t len;
	int oi = 0;
	while ((len = getline(&buf, &size, stdin)) > 0) {
		opts[oi] = malloc(len);
		memcpy(opts[oi], buf, len-1);
		opts[oi][len] = '\0';
		++oi;
		fprintf(out, "%s", buf);
	}

	int sel;
	if (fscanf(in, "%d", &sel) && 1 <= sel && sel <= oi) {
		printf("%s\n", opts[sel-1]);
	}

	fclose(in);
	fclose(out);
	return 0;
}
