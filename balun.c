/* balun.c - impedance matching for a multi-radix file dump program
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

#include "balun.h"

#ifdef NO_PERROR
/* implementation for perror() and friends */
#  ifdef NO_STRERROR
int strerror_r(int error, char *buf, size_t buflen)
{
#    ifndef NO_SYS_ERRLIST
    if (error < sys_nerr) {
        strncpy(buf, sys_errlist[error], buflen);
    } else
#    else
     snprintf(buf, buflen, "Unknown error %u", (unsigned) error);
#    endif
    buf[buflen - 1] = (char) 0
    return 0;
}
#  endif
void perror(const char *s)
{
    char *errbuf[128];
    fprintf(stderr, "%s: %s\n", s, strerror_r(errno, errbuf, sizeof(errbuf)));
}
#endif
