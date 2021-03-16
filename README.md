bfc
===
bfc is a compiler that compiles Brainfuck to amd64 assembly.
It is a static binary under 2 KB (1791 bytes).

![bfc QR code](bfc.png)

The typical usage is as follows:
```
$ bfc hello.bf hello.s
$ as -o hello.o hello.o
$ ld -nopie -o hello hello.o bfrt.o
$ ./hello
```

Why?
----
Read my
[blog post]()
about this codebase.
(Blog post forthcoming)

Building
--------
Just run `make`.
This will probably only run on
[OpenBSD](https://www.openbsd.org)/amd64
as is.
Feel free to port to your Unix of choice.

License
-------
ISC License.
See `LICENSE` for details.
