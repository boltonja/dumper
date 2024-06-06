/* dumper.c - a multi-radix file dump program
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
#include "dumper.h"

#define COMPILATION     "Compiled"
#define DESCRIPTION     "dumper - a file dump program."
#define HEX_BLANK       "+-"
#define NON_PRINT_CHAR  '.'
#define OTHER_BLANK     "+--"
#define RESTRICTIONS    "\nSee documentation and source for distribution restrictions."
#define USAGE_MSG       "%s:  usage:\n\t%s [-c -n -r -v] [--help] [[-d -h -o] [file ...]]\n"
#define VERSION         "\nJillian Alana Bolton\nReleased Mar 02 1994 07:00:00"

/* constants for command line switches. */

#define COL             "-c"
#define DASH            "-"
#define DEC             "-d"
#define DEFAULT_MODE    hexadecimal
#define HELP            "--help"
#define HEX             "-h"
#define NAM             "-n"
#define OCT             "-o"
#define RST             "-r"
#define VER             "-v"

#define BUFLEN           16 * sizeof(char)

typedef struct {
    int            handle;
    FILE          *stream;
    modetype       mode;
    const char    *name;
} filetype;

static const char *stdinname = "stdin";

void dumper(char *s, size_t c, size_t *offset, modetype mode, int h)
{
    int loop;
    int column = 2;
    unsigned char *p = (void *)s;

    switch (mode) {
	case hexadecimal:
	    printf("%08lx: ", *offset);
	    break;
	case octal:
	    printf("%010lo: ", *offset);
	    break;
	case decimal:
	    printf("%010lu: ", *offset);
	    break;
    }

    /* offset is the index into the file of the first char in the buffer.
     * Ideally, it's a multiple of 16, but on VMS, read() and fread() may
     * stop early, i.e. at the end of each record. In such cases, ASCII
     * EOL characters are not present.
     */

    *offset += c;

    for (loop = 0; loop <= (c - 1); loop++) {

            /* separate every group of four numbers in hex mode, 8 otherwise. */

	if ((!(loop % 4) && loop && (mode == hexadecimal)) ||
	    (!(loop % 8) && loop && (mode != hexadecimal)))
	    printf(" ");

	if (h && (++column % 2)) {
	    printf("[7m");
        }

	switch (mode) {
	    case hexadecimal:
		printf("%02x", (unsigned int) p[loop]);
		break;
	    case decimal:
		printf("%03d", (unsigned int) p[loop]);
		break;
	    case octal:
		printf("%03o", (unsigned int) p[loop]);
		break;
	}

	if (h && (column % 2)) {
	    printf("[0m");
        }
            
            /* if it's not printable, print something else. */

	if (!(isalnum(s[loop]) || ispunct(s[loop])
	      || (s[loop] == ' ')))
	    s[loop] = NON_PRINT_CHAR;

    }

    for (; loop < 16; loop++) {

            /* separate every group of four numbers in hex mode, 8 otherwise */

	if ((!(loop % 4) && loop && (mode == hexadecimal)) ||
	    (!(loop % 8) && loop && (mode != hexadecimal)))
	    printf(" ");

            /* print blanks in  leftover positions to fill the number space. */

	printf(((mode == hexadecimal) ? HEX_BLANK : OTHER_BLANK));

    };

    s[c] = 0;

    printf(" %s\n", s);
};

int fileopen(char *fname, filetype *f)
{
    /* VAX C sequential files have associated trade-offs between UNIX I/O and
     * buffered C I/O.  To select UNIX I/O, define USE_LOW_LEVEL_IO
     */
#ifdef USE_LOW_LEVEL_IO
    f->handle = open(fname, O_RDONLY | O_BINARY | O_NDELAY, S_IFREG);
    return (f->handle >= 0);
#else
    f->stream = fopen(fname, "rb");
    return (f->stream != NULL);
#endif
}

void fileclose(filetype *f)
{
#ifdef USE_LOW_LEVEL_IO
    close(f->handle);
#else
    if (f->stream != stdin)
	fclose(f->stream);
#endif
}

int fileread(char *buf, size_t count, filetype *f)
{

#ifdef USE_LOW_LEVEL_IO
    return read(f->handle, buf, (unsigned) count);
#else
    return fread(buf, (size_t) 1, (size_t) count, f->stream);
#endif
}

void emitversion(char *exename)
{
    printf("%s\n", DESCRIPTION);
    printf("%s \n%s %s %s\n%s\n\n", VERSION, COMPILATION, __DATE__, __TIME__, RESTRICTIONS);
    printf(USAGE_MSG, exename, exename);
}

int main(int argc,char *argv[])
{
    int       nread;
    char      errmsg[1024];                 /* an arbitrary limit */
    modetype  mode = DEFAULT_MODE;	    /* What mode are we in? */

    char      inbuf[(BUFLEN + sizeof(char))]; /* and one for the javanisse */
    int       i;
    int       filecount = 0;                 /* how many args were pathnames */
    filetype *files;
    int       columnhighlight = 0;
    int       printnames = 0;
    int       resetoffset = 0;
    size_t    offset = 0;
    
    files = malloc(sizeof(filetype) * argc); /* always one or more due to argv[0] */

    if (!files) {
        perror("out of memory");
        return EXIT_FAILURE;
    }

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], VER) || !strcmp(argv[i], HELP)) {
            emitversion(argv[0]);
            return EXIT_SUCCESS;
        } else if (!strcmp(argv[i], DEC)) {
            mode = decimal;
        } else if (!strcmp(argv[i], OCT)) {
            mode = octal;
        } else if (!strcmp(argv[i], HEX)) {
            mode = hexadecimal;
        } else if (!strcmp(argv[i], RST)) {
            resetoffset = 1;
        } else if (!strcmp(argv[i], NAM)) {
            printnames = 1;
        } else if (!strcmp(argv[i], COL)) {
            columnhighlight = 1;
        } else if (!strcmp(argv[i], DASH)) {
            files[filecount].handle = 0;
            files[filecount].stream = stdin;
            files[filecount].mode = mode;
            files[filecount].name = stdinname;
            filecount++;
        } else {
            if (!fileopen(argv[i], &files[filecount])) {
                sprintf(errmsg, "%s: %s", argv[0], argv[i]);
                perror(errmsg);
                return EXIT_FAILURE;
            }
            files[filecount].mode = mode;
            files[filecount].name = argv[i];
            filecount++;
        }
    }

    if (filecount == 0) {
        files[filecount].handle = 0;
        files[filecount].stream = stdin;
        files[filecount].mode = mode;
        files[filecount].name = stdinname;
        filecount++;
    }

    for (i = 0; i < filecount; i++) {

        if (resetoffset) {
            offset = 0;
        }

        if (printnames) {
            printf("%s:\n",files[i].name);
        }

        while ((nread = fileread(inbuf, (size_t) BUFLEN, &files[i]))) {
            if (nread < 0) {
                    /* some serious error occurred. */
                sprintf(errmsg, "%s: %s", argv[0], files[i].name);
                perror(errmsg);
                fileclose(&files[i]);
                return EXIT_FAILURE;
            }
            inbuf[nread] = 0;
            dumper(inbuf, nread, &offset, files[i].mode, columnhighlight);
        }
        fileclose(&files[i]);
    }

    return EXIT_SUCCESS;
}
