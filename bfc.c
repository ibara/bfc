/*
 * Copyright (c) 2020 Brian Callahan <bcallah@openbsd.org>
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

/*
 * bfc -- tiny brainfuck compiler
 */

extern void *_syscall(void *n, void *a, void *b, void *c, void *d, void *e);

static unsigned char label[256];
static int l, m;

static void
_exit(int status)
{

	_syscall((void *) 1, (void *) status, (void *) 0, (void *) 0, (void *) 0, (void *) 0);
}

static long
read(int d, void *buf, unsigned long nbytes)
{

	return (long) _syscall((void *) 3, (void *) d, (void *) buf, (void *) nbytes, (void *) 0, (void *) 0);
}

static void
write(int d, const void *buf, unsigned long nbytes)
{

	_syscall((void *) 4, (void *) d, (void *) buf, (void *) nbytes, (void *) 0, (void *) 0);
}

static long
open(const char *path, int flags, unsigned int mode)
{

	return (long) _syscall((void *) 5, (void *) path, (void *) flags, (void *) mode, (void *) 0, (void *) 0);
}

static void
close(int d)
{

	_syscall((void *) 6, (void *) d, (void *) 0, (void *) 0, (void *) 0, (void *) 0);
}

static long
strlen(const char *s)
{
	char *t;

	t = (char *) s;
	while (*t != '\0')
		t++;

	return t - s;
}

static void
dputs(const char *s, int fd)
{

	write(fd, s, strlen(s));
}

static void
dputi(int n, int fd)
{
	char num[10];
	int i, neg = 0;

	if (n < 0)
		neg = 1;

	i = 0;
	do {
		num[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);

	if (neg == 1)
		write(fd, "-", 1);

	for (i--; i >= 0; i--)
		write(fd, &num[i], 1);
}

static void
prologue(int fd)
{

	dputs("\t.text\n", fd);
	dputs("\t.p2align 2\n", fd);
	dputs("\t.globl\tmain\n", fd);
	dputs("\t.type\tmain,@function\n", fd);
	dputs("main:\n", fd);
	dputs("\tpushq\t%rbp\n", fd);
	dputs("\tmovq\t%rsp, %rbp\n", fd);
	dputs("\tsubq\t$16, %rsp\n", fd);
	dputs("\tleaq\ttape(%rip), %r15\n", fd);
}

static void
epilogue(int fd)
{

	dputs("\txorl\t%eax, %eax\n", fd);
	dputs("\tleaveq\n", fd);
	dputs("\tretq\n", fd);
	dputs("\t.size\tmain,.-main\n", fd);
	dputs("\n", fd);
	dputs("\t.local\ttape\n", fd);
	dputs("\t.comm\ttape,65536,1\n", fd);
	dputs("\t.end\n", fd);
}

static void
left(int fd)
{

	dputs("\tdecq\t%r15\n", fd);
}

static void
right(int fd)
{

	dputs("\tincq\t%r15\n", fd);
}

static void
inc(int fd)
{

	dputs("\tmovsbl\t(%r15), %eax\n", fd);
	dputs("\tincl\t%eax\n", fd);
	dputs("\tmovb\t%al, (%r15)\n", fd);
}

static void
dec(int fd)
{

	dputs("\tmovsbl\t(%r15), %eax\n", fd);
	dputs("\tdecl\t%eax\n", fd);
	dputs("\tmovb\t%al, (%r15)\n", fd);
}

static void
getchar(int fd)
{

	dputs("\tmovl\t$3, %eax\n", fd);
	dputs("\tmovl\t$0, %edi\n", fd);
	dputs("\tmovq\t%r15, %rsi\n", fd);
	dputs("\tmovl\t$1, %edx\n", fd);
	dputs("\tmovq\t$0, %rcx\n", fd);
	dputs("\tmovq\t$0, %r8\n", fd);
	dputs("\tmovq\t$0, %r9\n", fd);
	dputs("\tsyscall\n", fd);
	dputs("\txorl\t%eax, %eax\n", fd);
}

static void
putchar(int fd)
{

	dputs("\tmovl\t$4, %eax\n", fd);
	dputs("\tmovl\t$1, %edi\n", fd);
	dputs("\tmovq\t%r15, %rsi\n", fd);
	dputs("\tmovl\t$1, %edx\n", fd);
	dputs("\tmovq\t$0, %rcx\n", fd);
	dputs("\tmovq\t$0, %r8\n", fd);
	dputs("\tmovq\t$0, %r9\n", fd);
	dputs("\tsyscall\n", fd);
	dputs("\txorl\t%eax, %eax\n", fd);
}

static void
open_loop(int fd)
{

	label[l] = m++;
	dputs(".LS", fd);
	dputi(label[l], fd);
	dputs(":\n", fd);
	dputs("\tmovsbl\t(%r15), %eax\n", fd);
	dputs("\tcmpl\t$0, %eax\n", fd);
	dputs("\tje\t.LE", fd);
	dputi(label[l++], fd);
	dputs("\n", fd);
}

static void
close_loop(int fd)
{

	dputs("\tjmp\t.LS", fd);
	dputi(label[--l], fd);
	dputs("\n", fd);
	dputs(".LE", fd);
	dputi(label[l], fd);
	dputs(":\n", fd);
}

int
main(int argc, char *argv[])
{
	int c, fd1, fd2;

	if (argc != 3) {
		dputs("usage: bfc infile outfile\n", 1);
		return 1;
	}

	if ((fd1 = open(argv[1], 0x0000, 0)) == -1) {
		dputs("bfc: could not open input file\n", 1);
		return 1;
	}

	if ((fd2 = open(argv[2], 0x0002 | 0x0200 | 0x0400, 000644)) == -1) {
		dputs("bfc: could not open output file\n", 1);
		close(fd1);
		return 1;
	}

	prologue(fd2);

loop:
	if (read(fd1, &c, 1) < 1) {
		epilogue(fd2);

		close(fd2);
		close(fd1);

		return 0;
	}

	switch (c) {
	case '<':
		left(fd2);
		break;
	case '>':
		right(fd2);
		break;
	case '+':
		inc(fd2);
		break;
	case '-':
		dec(fd2);
		break;
	case ',':
		getchar(fd2);
		break;
	case '.':
		putchar(fd2);
		break;
	case '[':
		open_loop(fd2);
		break;
	case ']':
		close_loop(fd2);
	}

	goto loop;
}
