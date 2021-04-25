/*
 * Copyright (c) 2021 Brian Callahan <bcallah@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bfc.h"

/*
 * bfc -- brainfuck compiler
 */

int l, m, target = TARGET;
unsigned char label[256];

static void
mismatch(void)
{

	dputs("bfc: bracket mismatch\n", STDERR_FILENO);

	exit(1);
}

static void
prologue(int fd)
{

	cg_prologue(fd);
}

static void
epilogue(int fd)
{

	cg_epilogue(fd);
}

static void
left(int fd)
{

	cg_left(fd);
}

static void
right(int fd)
{

	cg_right(fd);
}

static void
inc(int fd)
{

	cg_inc(fd);
}

static void
dec(int fd)
{

	cg_dec(fd);
}

static void
_getchar(int fd)
{

	cg_getchar(fd);
}

static void
_putchar(int fd)
{

	cg_putchar(fd);
}

static void
open_loop(int fd)
{

	cg_open_loop(fd);
}

static void
close_loop(int fd)
{

	cg_close_loop(fd);
}

static int
cross(const char *s)
{

	if ((!strcmp("amd64", s)) || (!strcmp("x86_64", s))) {
		return TAMD64;
	} else if ((!strcmp("i386", s)) || (!strcmp("i486", s)) ||
		   (!strcmp("i586", s)) || (!strcmp("i686", s)) ||
		   (!strcmp("i786", s))) {
		return TI386;
	} else if ((!strcmp("8080", s)) || (!strcmp("i80", s)) ||
		   (!strcmp("z80", s))) {
		return TI80;
	} else if ((!strcmp("C", s)) || (!strcmp("c", s))) {
		return TC;
	}

	/* No match? Native compiler.  */
	return target;
}

static void __dead
usage(void)
{

	dputs("usage: bfc [-t target] file\n", STDERR_FILENO);

	exit(1);
}

int
main(int argc, char *argv[])
{
	char c;
	int ch, d = 0, fd;

	if (pledge("stdio rpath wpath cpath", NULL) == -1)
		usage();

	if ((ch = getopt(argc, argv, "t:")) != -1) {
		switch (ch) {
		case 't':
			target = cross(optarg);
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 1)
		usage();

	if ((fd = open(*argv++, O_RDONLY)) == -1) {
		dputs("bfc: could not open input file\n", STDERR_FILENO);
		return 1;
	}

	if (pledge("stdio", NULL) == -1)
		usage();

	prologue(STDOUT_FILENO);

	while (read(fd, &c, STDOUT_FILENO) == 1) {
		switch (c) {
		case '<':
			left(STDOUT_FILENO);
			break;
		case '>':
			right(STDOUT_FILENO);
			break;
		case '+':
			inc(STDOUT_FILENO);
			break;
		case '-':
			dec(STDOUT_FILENO);
			break;
		case ',':
			_getchar(STDOUT_FILENO);
			break;
		case '.':
			_putchar(STDOUT_FILENO);
			break;
		case '[':
			++d;
			open_loop(STDOUT_FILENO);
			break;
		case ']':
			if (--d < 0)
				mismatch();
			close_loop(STDOUT_FILENO);
		}
	}
	if (d != 0)
		mismatch();

	epilogue(STDOUT_FILENO);
	close(fd);

	return 0;
}
