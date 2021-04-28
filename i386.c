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
i386_prologue(int fd)
{

	dputs("\t.text\n", fd);
	dputs("\t.p2align 4, 0xcc\n", fd);
	dputs("\t.globl\tmain\n", fd);
	dputs("\t.type\tmain,@function\n", fd);
	dputs("main:\n", fd);
	dputs("\tpushl\t%ebp\n", fd);
	dputs("\tmovl\t%esp, %ebp\n", fd);
	dputs("\tpushl\t%ebx\n", fd);
	dputs("\tleal\ttape@GOTOFF(%eax), %ecx\n", fd);
}

void
i386_epilogue(int fd)
{

	dputs("\txorl\t%eax, %eax\n", fd);
	dputs("\tpopl\t%ebx\n", fd);
	dputs("\tpopl\t%ebp\n", fd);
	dputs("\tretl\n", fd);
	dputs("\t.size\tmain,.-main\n", fd);
	dputs("\t.local\ttape\n", fd);
	dputs("\t.comm\ttape,65536,1\n", fd);
	dputs("\t.end\n", fd);
}

void
i386_left(int fd)
{

	dputs("\tdecl\t%ecx\n", fd);
}

void
i386_right(int fd)
{

	dputs("\tincl\t%ecx\n", fd);
}

void
i386_inc(int fd)
{

	dputs("\tmovsbl\t(%ecx), %eax\n", fd);
	dputs("\tincl\t%eax\n", fd);
	dputs("\tmovb\t%al, (%ecx)\n", fd);
}

void
i386_dec(int fd)
{

	dputs("\tmovsbl\t(%ecx), %eax\n", fd);
	dputs("\tdecl\t%eax\n", fd);
	dputs("\tmovb\t%al, (%ecx)\n", fd);
}

void
i386_getchar(int fd)
{

	dputs("\tpushl\t$1\n", fd);
	dputs("\tpushl\t%ecx\n", fd);
	dputs("\tpushl\t$0\n", fd);
	dputs("\tcall\tread@PLT\n", fd);
	dputs("\tpopl\t%eax\n", fd);
	dputs("\tpopl\t%eax\n", fd);
	dputs("\tpopl\t%eax\n", fd);
}

void
i386_putchar(int fd)
{

	dputs("\tpushl\t$1\n", fd);
	dputs("\tpushl\t%ecx\n", fd);
	dputs("\tpushl\t$1\n", fd);
	dputs("\tcall\twrite@PLT\n", fd);
	dputs("\tpopl\t%eax\n", fd);
	dputs("\tpopl\t%eax\n", fd);
	dputs("\tpopl\t%eax\n", fd);
}

void
i386_open_loop(int fd)
{

	dputs("\tmovsbl\t(%ecx), %eax\n", fd);
	dputs("\tcmpl\t$0, %eax\n", fd);
	dputs("\tje\t.LE", fd);
}

void
i386_close_loop(int fd)
{

	dputs("\tjmp\t.LB",fd);
}
