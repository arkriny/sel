/*
 * sel - select interactively
 *
 * Written by Artem Krinitsyn. Public domain.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	FILE *in = fopen("/dev/tty", "r");
	FILE *out = fopen("/dev/tty", "w");
	if (!in || !out) return 1;

	size_t ocap = 16;
	size_t olen = 0;
	char **opts = malloc(ocap * sizeof(char*));

	char *buf = NULL;
	size_t size;
	ssize_t len;
	while ((len = getline(&buf, &size, stdin)) > 0) {
		if (olen == ocap) {
			ocap <<= 1;
			opts = realloc(opts, ocap * sizeof(char*));
		}
		opts[olen] = malloc(len);
		memcpy(opts[olen], buf, len-1);
		opts[olen][len] = '\0';
		++olen;
		fprintf(out, "%s", buf);
	}

	int sel;
	if (fscanf(in, "%d", &sel) && 1 <= sel && sel <= olen) {
		printf("%s\n", opts[sel-1]);
	}

	fclose(in);
	fclose(out);
	return 0;
}
