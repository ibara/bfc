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

void
cg_prologue(int fd)
{

	switch (target) {
	case TAMD64:
		amd64_prologue(fd);
		break;
	case TI386:
		i386_prologue(fd);
	}
}

void
cg_epilogue(int fd)
{

	switch (target) {
	case TAMD64:
		amd64_epilogue(fd);
		break;
	case TI386:
		i386_epilogue(fd);
	}
}

void
cg_left(int fd)
{

	switch (target) {
	case TAMD64:
		amd64_left(fd);
		break;
	case TI386:
		i386_left(fd);
	}
}

void
cg_right(int fd)
{

	switch (target) {
	case TAMD64:
		amd64_right(fd);
		break;
	case TI386:
		i386_right(fd);
	}
}

void
cg_inc(int fd)
{

	switch (target) {
	case TAMD64:
		amd64_inc(fd);
		break;
	case TI386:
		i386_inc(fd);
	}
}

void
cg_dec(int fd)
{

	switch (target) {
	case TAMD64:
		amd64_dec(fd);
		break;
	case TI386:
		i386_dec(fd);
	}
}

void
cg_getchar(int fd)
{

	switch (target) {
	case TAMD64:
		amd64_getchar(fd);
		break;
	case TI386:
		i386_getchar(fd);
	}
}

void
cg_putchar(int fd)
{

	switch (target) {
	case TAMD64:
		amd64_putchar(fd);
		break;
	case TI386:
		i386_putchar(fd);
	}
}

void
cg_open_loop(int fd)
{

	label[l] = m++;
	dputs(".LB", fd);
	dputi(label[l], fd);
	dputs(":\n", fd);

	switch (target) {
	case TAMD64:
		amd64_open_loop(fd);
		break;
	case TI386:
		i386_open_loop(fd);
	}

	dputi(label[l++], fd);
	dputs("\n", fd);
}

void
cg_close_loop(int fd)
{

	switch (target) {
	case TAMD64:
		amd64_close_loop(fd);
		break;
	case TI386:
		i386_close_loop(fd);
	}

	dputi(label[--l], fd);
	dputs("\n", fd);
	dputs(".LE", fd);
	dputi(label[l], fd);
	dputs(":\n", fd);
}
