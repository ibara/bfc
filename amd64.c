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
amd64_prologue(int fd)
{

	dputs("\t.text\n", fd);
	dputs("\t.p2align 4, 0xcc\n", fd);
	dputs("\t.globl\tmain\n", fd);
	dputs("\t.type\tmain,@function\n", fd);
	dputs("main:\n", fd);
	dputs("\tpushq\t%rbp\n", fd);
	dputs("\tmovq\t%rsp, %rbp\n", fd);
	dputs("\tleaq\ttape(%rip), %r15\n", fd);
}

void
amd64_epilogue(int fd)
{

	dputs("\txorl\t%eax, %eax\n", fd);
	dputs("\tleaveq\n", fd);
	dputs("\tretq\n", fd);
	dputs("\t.size\tmain,.-main\n", fd);
	dputs("\t.local\ttape\n", fd);
	dputs("\t.comm\ttape,65536,1\n", fd);
	dputs("\t.end\n", fd);
}

void
amd64_left(int fd)
{

	dputs("\tdecq\t%r15\n", fd);
}

void
amd64_right(int fd)
{

	dputs("\tincq\t%r15\n", fd);
}

void
amd64_inc(int fd)
{

	dputs("\tmovsbl\t(%r15), %eax\n", fd);
	dputs("\tincl\t%eax\n", fd);
	dputs("\tmovb\t%al, (%r15)\n", fd);
}

void
amd64_dec(int fd)
{

	dputs("\tmovsbl\t(%r15), %eax\n", fd);
	dputs("\tdecl\t%eax\n", fd);
	dputs("\tmovb\t%al, (%r15)\n", fd);
}

void
amd64_getchar(int fd)
{

	dputs("\tmovl\t$0, %edi\n", fd);
	dputs("\tmovq\t%r15, %rsi\n", fd);
	dputs("\tmovl\t$1, %edx\n", fd);
	dputs("\tcall\tread@PLT\n", fd);
}

void
amd64_putchar(int fd)
{

	dputs("\tmovl\t$1, %edi\n", fd);
	dputs("\tmovq\t%r15, %rsi\n", fd);
	dputs("\tmovl\t$1, %edx\n", fd);
	dputs("\tcall\twrite@PLT\n", fd);
}

void
amd64_open_loop(int fd)
{

	dputs("\tmovsbl\t(%r15), %eax\n", fd);
	dputs("\tcmpl\t$0, %eax\n", fd);
	dputs("\tje\t.LE", fd);
}

void
amd64_close_loop(int fd)
{

	dputs("\tjmp\t.LB", fd);
}
