/*
 * sel - select interactively
 *
 * Written by Artem Krinitsyn. Public domain.
 */

#include <stdio.h>

char opts[4096][1024];

int main(void)
{
	FILE *in = fopen("/dev/tty", "r");
	FILE *out = fopen("/dev/tty", "w");
	if (!in || !out) return 1;

	int c, oi, ci;
	oi = ci = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			opts[oi][ci] = '\0';
			++oi;
			ci = 0;
		} else {
			opts[oi][ci++] = c;
		}
		fputc(c, out);
	}

	int sel;
	if (fscanf(in, "%d", &sel) && 1 <= sel && sel <= oi) {
		printf("%s\n", opts[sel-1]);
	}

	fclose(in);
	fclose(out);
	return 0;
}
