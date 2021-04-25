# bfc Makefile

CC =		cc
CFLAGS =	-g -O2 -DTARGET=0

PROG =	bfc
OBJS =	amd64.o bfc.o c.o cg.o dput.o i386.o i80.o

all: ${OBJS}
	${CC} ${LDFLAGS} -o ${PROG} ${OBJS}

install:
	install -m 755 ${PROG} /usr/local/bin

clean:
	rm -f ${PROG} ${OBJS}

distclean: clean
	rm -f Makefile
