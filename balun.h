/* balun.h - impedance matching for a multi-radix file dump program
 * 
 * Copyright 1991-2024 Jillian Alana Bolton
 * Copyright 1995 Mark P. Fister
 *
 * The BSD 2-Clause License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef VAXC
/*
 * Some incompatibilities with dumper and VMS:
 * - Text files are often written with one record per line and no ASCII EOL
 * - Record-oriented (RMS) files contain metadata that is abstracted away
 *   by system services and the C APIs cannot directly read this metadata
 *
 * Otherwise, dumper works reasonably well on VMS. 
 *
 * The VMS "DUMP" command in the DCL command reference can show the structure
 * metadata in an easy to read form, while dumping the record contents in
 * hex, decimal, or octal.
 */
#  define VMS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef BSD
#  include <string.h>
#else
#  include <strings.h>
#endif

#ifdef NO_PERROR
#  include <errno.h>
#if (defined NO_ERRNO)
#  define errno 0
#endif
#endif

#ifdef VMS
#  include <unixio.h>
#  include <file.h>			    /* no O_BINARY :( */
#  include <stat.h>
#  include <types.h>
#  undef EXIT_SUCCESS
#  define EXIT_SUCCESS 0x10000001	    /* success, suppress message */
#  undef EXIT_FAILURE
#  define EXIT_FAILURE 0x10000000	    /* failure, suppress message*/
#else
#  include <fcntl.h>
#  include <sys/types.h>
#  include <sys/stat.h>
#endif

#ifndef O_NDELAY
#  define O_NDELAY 0
#endif

#ifndef O_BINARY
#  define O_BINARY      0
#endif

#ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS  1
#endif
#ifndef EXIT_FAILURE
#  define EXIT_FAILURE  0
#endif
