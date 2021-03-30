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

static size_t il;

static void
indent(size_t l, int fd)
{

	do {
		dputs("\t", fd);
	} while (l--);
}

void
c_prologue(int fd)
{

	dputs("#include <stdio.h>\n\n", fd);
	dputs("unsigned char array[65536];\n\n", fd);
	dputs("int\n", fd);
	dputs("main(int argc, char *argv[])\n", fd);
	dputs("{\n", fd);
	dputs("\tint q;\n", fd);
	dputs("\tunsigned char *p = array;\n\n", fd);
}

void
c_epilogue(int fd)
{

	dputs("\treturn 0;\n", fd);
	dputs("}\n", fd);
}

void
c_left(int fd)
{

	indent(il, fd);
	dputs("--p;\n", fd);
}

void
c_right(int fd)
{

	indent(il, fd);
	dputs("++p;\n", fd);
}

void
c_inc(int fd)
{

	indent(il, fd);
	dputs("++*p;\n", fd);
}

void
c_dec(int fd)
{

	indent(il, fd);
	dputs("--*p;\n", fd);
}

void
c_getchar(int fd)
{

	indent(il, fd);
	dputs("if ((q = getchar()) != -1)\n", fd);
	indent(il, fd);
	dputs("\t*p = q;\n", fd);
}

void
c_putchar(int fd)
{

	indent(il, fd);
	dputs("putchar(*p);\n", fd);
}

void
c_open_loop(int fd)
{

	indent(il++, fd);
	dputs("while (*p) {\n", fd);
}

void
c_close_loop(int fd)
{

	indent(--il, fd);
	dputs("}\n", fd);
}
