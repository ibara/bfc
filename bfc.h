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

#define TAMD64	0
#define TI386	1
#define TC	255

extern int	l, m, target;
extern unsigned char label[256];

extern void	amd64_close_loop(int);
extern void	amd64_dec(int);
extern void	amd64_epilogue(int);
extern void	amd64_getchar(int);
extern void	amd64_inc(int);
extern void	amd64_left(int);
extern void	amd64_open_loop(int);
extern void	amd64_prologue(int);
extern void	amd64_putchar(int);
extern void	amd64_right(int);

extern void	c_close_loop(int);
extern void	c_dec(int);
extern void	c_epilogue(int);
extern void	c_getchar(int);
extern void	c_inc(int);
extern void	c_left(int);
extern void	c_open_loop(int);
extern void	c_prologue(int);
extern void	c_putchar(int);
extern void	c_right(int);

extern void	cg_close_loop(int);
extern void	cg_dec(int);
extern void	cg_epilogue(int);
extern void	cg_getchar(int);
extern void	cg_inc(int);
extern void	cg_left(int);
extern void	cg_open_loop(int);
extern void	cg_prologue(int);
extern void	cg_putchar(int);
extern void	cg_right(int);

extern void	dputs(const char *, int);
extern void	dputi(int, int);

extern void	i386_close_loop(int);
extern void	i386_dec(int);
extern void	i386_epilogue(int);
extern void	i386_getchar(int);
extern void	i386_inc(int);
extern void	i386_left(int);
extern void	i386_open_loop(int);
extern void	i386_prologue(int);
extern void	i386_putchar(int);
extern void	i386_right(int);
