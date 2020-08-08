# bfc Makefile

CC =		cc
CFLAGS =	-Oz -nostdinc -fomit-frame-pointer
CFLAGS +=	-fno-PIE -fno-PIC -fno-ret-protector
CFLAGS +=	-fno-stack-protector -mno-retpoline
CFLAGS +=	-fno-asynchronous-unwind-tables
CFLAGS +=	-fdata-sections -ffunction-sections
CFLAGS +=	-Wno-int-to-void-pointer-cast
LDFLAGS +=	-Wl,--gc-sections

PROG =	bfc
OBJS =	_start.o _syscall.o bfc.o crt.o

all: ${OBJS}
	/usr/bin/ld -nopie -o ${PROG} ${OBJS}
	/usr/bin/strip ${PROG}
	/usr/bin/strip -R .comment ${PROG}
	/usr/bin/gzexe ${PROG}

clean:
	rm -rf ${PROG} ${OBJS} ${PROG}.core ${PROG}~
