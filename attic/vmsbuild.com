$! Copyright 1991-2024 Jillian Alana Bolton
$! Copyright 1995 Mark P. Fister
$! 
$! The BSD 2-Clause License
$! 
$! Redistribution and use in source and binary forms, with or without
$! modification, are permitted provided that the following conditions are
$! met:
$! 
$!     1. Redistributions of source code must retain the above copyright
$!     notice, this list of conditions and the following disclaimer.
$! 
$!     2. Redistributions in binary form must reproduce the above
$!     copyright notice, this list of conditions and the following
$!     disclaimer in the documentation and/or other materials provided
$!     with the distribution.
$! 
$! THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
$! ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
$! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
$! PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
$! BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
$! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
$! SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
$! BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
$! WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
$! OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
$! IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
$!
$! Command procedure to make the program executable spec'd in P1
$! (e.g. to make dumper, type @make DUMPER)
$!
$! Place your BINDIR and EXTENSION here, in quotes.
$ EXTENSION == ".EXE"
$ BINDIR == "[-]"
$
$ filebase == P1
$ executable == filebase + EXTENSION
$ dest == BINDIR + executable
$ commandobject == filebase + "_CMD"
$ commandfile == filebase + ".cld"
$ sourcefile == filebase
$!
$! Compile it.
$!
$ cc 'sourcefile
$!
$! Create DCL command language definition object.
$!
$ set command/obj='commandobject 'commandfile
$!
$! Link it all together.
$!
$ link 'sourcefile,'commandobject
$!
$! Now we do a "make clean" for you.
$!
$ purge
$ delete *.obj;*
$!
$! Now copy the executable to the proper directory and delete it from here.
$!
$ copy 'executable 'dest
$ executable == executable + ";*"
