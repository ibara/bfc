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
[blog post]()
about this codebase.
(Blog post forthcoming)

Building
--------
Run `./configure` to detect your native CPU.
Then run `make`.

Supported CPUs
--------------
* amd64 (x86_64)
* i386 (i486, i586, i686, i786)

Please feel free to add additional CPU support.

License
-------
ISC License.
See `LICENSE` for details.
