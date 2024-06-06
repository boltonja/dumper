% dumper(1) | General Commands Manual
NAME
====

dumper - a multi-radix file dump program

SYNOPSIS
========
`dumper [-c -n -r -v] [--help] [[-d -h -o] [file ...]]`

DESCRIPTION
===========

For each operand that refers to a regular file, or a symbolic or hard link to a regular file, dumper displays a numeric and printable character representation of the bytes in the file, sequentially. This format is often referred to as a radix dump. If no operands are given, dumper accepts input from <ins>stdin</ins>. When the special name "<ins>-</ins>" is given as an argument, dumper reads from stdin until end of file. All of the files named on the command line are processed in the order specified. The last **-d**, **-h**, or **-o** that precedes a file name controls the radix for the dump of that file.

The following options are available:

`-c`
: columns alternate with highlights using VT/ANSI escape codes

`-d`
: dump using decimal numbers

`-h`
: dump using hexadecimal numbers; this is the default

`--help`
: a synonym for -v

`-n`
: emit the name of a file on a separate line immediately before the start of its content dump

`-o`
: dump using octal numbers

`-r`
: reset the offset counter for each file when dumping multiple files; the default is to keep a running offset as if all files were concatenated

`-v`
: display version information and usage synopsis

ENVIRONMENT
===========

The C Library may be locale-aware, in which case the standard locale environment variables may affect the processing of bytes for ASCII output. The behavior with collating sequences other than US ASCII is not specified.

EXIT STATUS
===========

The dumper utility exits 0 on success, and >0 if an error occurs.

EXAMPLES
========

Dump the contents of the file /bin/ls in hexadecimal mode, without column highlighting:

    $ dumper /bin/ls

Dump the contents of stdin, /bin/ls, and /etc/motd with different radices:

    $ dumper -d - -o /bin/ls -h /etc/motd

Dump the contents of stdin, /bin/ls, and /etc/motd with different radices, resetting the offset for each file, emitting the name of each file, and highlighting alternating columns in the radix dump:

    $ dumper -d - -o /bin/ls -h /etc/motd -c -r -n

SEE ALSO
========
hexdump(1), od(1), xxd(1)

HISTORY
=======

A dumper command appeared on select SunOS 4.1, NeXTStep 2.0, and MS-DOS 3.x-6.x systems at Rose-Hulman Institute of Technology in 1991.

BUGS
====

The behavior on very large files is not known.

LICENSE
=======

Copyright 1991-2024 Jillian Alana Bolton

The BSD 2-Clause License

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the following
    disclaimer in the documentation and/or other materials provided
    with the distribution.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
