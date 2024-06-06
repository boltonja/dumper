Changelog for a multi-radix file dump program
=============================================

License
-------

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

Changes Summary for 5 June 2024 by Jillian Alana Bolton
-------------------------------------------------------

- Added support for multiple files, each with different radices
- Added support for stdin when using UNIX I/O
- Added -c switch for column highlights
- Added -r switch for resetting the offset between files
- Added --help switch as a synonym for -v
- Updated usage message
- Cleaned up default UNIX makefile and removed "install" target
- Print filenames as given (no backslash conversion and strlwr)
- General cleanup of various cruft, comments, and documentation
- Moved VMS and Turbo C specific files to the attic
- Changed function definitions to ANSI style
- Patterned inbuilt strerror() after POSIX strerror_r(3)
- Moved the old README to attic
- created balun.h, dumper.h, and moved stuff necessary to compile
  as a library into there (left as an exercise for the reader)
- Created new README from the ashes of the old
- Added Visual Studio project files

Changes Summary for unknown date in 1995 by Mark P. Fister
----------------------------------------------------------

- Added alternting VT / ANSI highlights in the hex, dec, oct columns

Changes Summary for 25 January 1994 by Jillian Alana Bolton
------------------------------------------------------------

-  Converted error messages to standard UNIX-style messages
-  Added code to convert upper case paths in MS-DOS to lower case
-  Altered error messages to include strerror output
-  Added open,read,close for better VMS compatibility
-  Added makefile for Turbo C with the following targets:

`dumper`
: just the executable file.

`clean`
: remove the executable, object files, and backups.

`install`
: builds dumper and copies it to BINDIR

Changes Summary for 28 February 1994 by Jillian Alana Bolton
------------------------------------------------------------

- Changed command line format and usage message:  switches now go before
  the filename
  Thanks to Ade Barkah (mbarkah@barkah.golden.co.us) for the suggestion
- stdin is still not supported.     
- Changed UNIX Makefile for compatibility with make tools requiring tabs
- Changed UNIX Makefile so default target is dumper rather than clean
  Thanks again, Ade. :)
- Fixed bugs in the preprocessor spaghetti
  -DNO_STRERROR, -DNO_ERRNO, -DNO_SYS_ERRLIST now work as intended

Changes Summary for 1 March 1994 by Jillian Alana Bolton
--------------------------------------------------------

- Now using perror for errors, and conditional identifier -DNO_PERROR
- Added -DBSD identifier to include either <string.h> or <strings.h>
  (Thanks again, Ade, for the suggestions)
- Fixed a bug in the local strerror() code that used errno explicitly
- Fixed an out of range index into sys_errlist in strerror

Changes Summary for 2 March 1994 by Jillian Alana Bolton
--------------------------------------------------------

- Fixed VMS port so that it works as described
- UNIX I/O routines are selected at build time with -DUSE_LOW_LEVEL_IO
- The default build uses stream I/O from stdio.h
- Redefined EXIT_FAILURE for VMS versions so that you don't get a
  system message anymore since dumper prints its own error messages
- stdin is supported when USE_LOW_LEVEL_IO is not defined.

Changes Summary for 17 February 1995 by Jillian Alana Bolton
------------------------------------------------------------
- Changed function definitions from ANSI style to K & R style
  for better portability.
- Updated README file with more systems.
