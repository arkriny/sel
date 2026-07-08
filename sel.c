/*
 * sel - select interactively
 *
 * Written by Artem Krinitsyn. Public domain.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Opts {
	char **items;
	size_t len;
	size_t cap;
};

#define OPTS_CAP 16

int
main(void)
{
	FILE *in = fopen("/dev/tty", "r");
	FILE *out = fopen("/dev/tty", "w");
	if (!in || !out) return 1;

	struct Opts opts = {
		.items = malloc(OPTS_CAP * sizeof(char *)),
		.len = 0,
		.cap = OPTS_CAP,
	};

	char *lbuf = NULL;
	size_t lsize;
	ssize_t llen;
	while ((llen = getline(&lbuf, &lsize, stdin)) > 0) {
		if (opts.len == opts.cap) {
			opts.cap <<= 1;
			opts.items = realloc(opts.items,
			                     opts.cap * sizeof(char *));
		}
		opts.items[opts.len] = malloc(llen);
		memcpy(opts.items[opts.len], lbuf, llen-1);
		opts.items[opts.len][llen] = '\0';
		++opts.len;
		fprintf(out, "%s", lbuf);
	}

	size_t sel;
	if (fscanf(in, "%d", &sel) && 1 <= sel && sel <= opts.len) {
		printf("%s\n", opts.items[sel-1]);
	}

	fclose(in);
	fclose(out);
	return 0;
}
