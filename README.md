bfc
===
bfc is a multi-platform compiler that compiles Brainfuck to assembly.

Typical usage is as follows:
```
$ bfc hello.bf | cc -x assembler -
$ ./a.out
```

Why?
----
Read my
[blog post](https://briancallahan.net/blog/20210425.html)
about this codebase.

Building
--------
Run `./configure` to detect your native CPU.
Then run `make`.

Supported backends
------------------
* amd64 (x86_64)
* i386 (i486, i586, i686, i786)
* 8080/Z80 (8080, i80, z80)
* Generic C (for all other CPUs)

Please feel free to add additional CPU support.

License
-------
ISC License.
See `LICENSE` for details.
