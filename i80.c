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

#include "bfc.h"

void
i80_prologue(int fd)
{

	dputs("\torg\t100h\n", fd);
	dputs("\tlxi\tsp, 0dbffh\n", fd);
	dputs("\tlxi\td, 5bffh\n", fd);
	dputs("\tlxi\th, 8000h\n", fd);
	dputs("loop:\tmov\ta, d\n", fd);
	dputs("\tcpi\t0\n", fd);
	dputs("\tjz\tendl\n", fd);
	dputs("\tmvi\tm, 0\n", fd);
	dputs("\tinx\th\n", fd);
	dputs("\tdcr\td\n", fd);
	dputs("\tjmp\tloop\n", fd);
	dputs("endl:\tlxi\th, 8000h\n", fd);
	dputs("main:\n", fd);
}

void
i80_epilogue(int fd)
{

	dputs("\trst\t0\n", fd);
	dputs("\tend\n", fd);
}

void
i80_left(int fd)
{

	dputs("\tdcx\th\n", fd);
}

void
i80_right(int fd)
{

	dputs("\tinx\th\n", fd);
}

void
i80_inc(int fd)
{

	dputs("\tmov\tb, m\n", fd);
	dputs("\tinr\tb\n", fd);
	dputs("\tmov\tm, b\n", fd);
}

void
i80_dec(int fd)
{

	dputs("\tmov\tb, m\n", fd);
	dputs("\tdcr\tb\n", fd);
	dputs("\tmov\tm, b\n", fd);
}

void
i80_getchar(int fd)
{

	dputs("\tpush\th\n", fd);
	dputs("\tmvi\tc, 1\n", fd);
	dputs("\tcall\t5\n", fd);
	dputs("\tpop\th\n", fd);
	dputs("\tmov\tm, a\n", fd);
}

void
i80_putchar(int fd)
{

	dputs("\tpush\th\n", fd);
	dputs("\tmov\te, m\n", fd);
	dputs("\tmvi\tc, 2\n", fd);
	dputs("\tcall\t5\n", fd);
	dputs("\tpop\th\n", fd);
}

void
i80_open_loop(int fd)
{

	dputs("\tmov\ta, m\n", fd);
	dputs("\tcpi\t0\n", fd);
	dputs("\tjz\t.LE", fd);
}

void
i80_close_loop(int fd)
{

	dputs("\tjmp\t.LB",fd);
}
