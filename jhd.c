/*
 * Copyright (c) 2006 2007 2008 ... 2022 2023
 *     John McCue <jmccue@jmcunx.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _MSDOS
#include <sys/param.h>
#endif
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef OpenBSD
#include <err.h>
#endif
#ifdef __FreeBSD_version
#include <err.h>
#endif
#ifdef __NetBSD_Version__
#include <err.h>
#endif

#include <j_lib2.h>
#include <j_lib2m.h>

#include "jhd.h"

#ifndef R_OK
#define R_OK 4        /* Test for read permission */
#endif

/*
 * show_file_heading() -- Show run stats
 */
void show_file_heading(work_area *w, char *fname)

{

  fprintf(w->out.fp, "%s\n", LIT_C80);

  if (fname == (char *) NULL)
    fprintf(w->out.fp, "%s\n", LIT_STDIN);
  else
    {
      if (strcmp(fname, FILE_NAME_STDIN) == 0)
	fprintf(w->out.fp, "%s\n", LIT_STDIN);
      else
	fprintf(w->out.fp, "%s\n", fname);
    }

  fprintf(w->out.fp, "%s\n", LIT_C80);

} /* show_file_heading() */

/*
 * open_in() -- open input
 */
int open_in(int *f, char *fname, FILE *fp)

{
  int errsave;

  if (fname == (char *) NULL)
    {
      (*f) = fileno(stdin);
      return((int) TRUE);
    }

  if (strcmp(fname, FILE_NAME_STDIN) == 0)
    {
      (*f) = fileno(stdin);
      return((int) TRUE);
    }

  if ( access(fname, R_OK) != (int) 0 )
    {
      fprintf(fp, MSG_ERR_E016, fname);
      return((int) FALSE);
    }

  (*f) = open(fname, ( HD_OMODE ) );
  errsave = errno;
  if ((*f) < 0)
    {
      fprintf(fp, MSG_WARN_W002, fname, strerror(errsave));
      return((int) FALSE);
    }

  return((int) TRUE);

} /* open_in() */

/*
 * process_file() -- Process one file
 */
void process_file(work_area *w, char *fname)

{

  int f;
  unsigned char buf[3];
  long int byte_read  = 0L;
  long int byte_write = 0L;

  memset(buf, JLIB2_UCHAR_NULL, 3);

  /*** force reset of static variables inside functions ***/
  if ( (w->mode_hex) == (int) TRUE )
    {
      if (w->mode_vertical == (int) TRUE)
        show_hex_vertical(0, byte_read, w->out.fp, buf[0], w->pause);
      else
	show_hex(0, byte_read, w->out.fp, buf[0], w->pause);
    }
  if ( (w->mode_decimal) == (int) TRUE )
    {
      if (w->mode_vertical == (int) TRUE)
        show_dec_vertical(0, byte_read, w->out.fp, buf[0], w->pause);
      else
	show_decimal(0, w->out.fp, (unsigned char) buf[0], w->pause);
    }
  if ( (w->mode_oct) == (int) TRUE )
    {
      if (w->mode_vertical == (int) TRUE)
        show_oct_vertical(0, byte_read, w->out.fp, buf[0], w->pause);
      else
	show_octal(0, w->out.fp, (unsigned char) buf[0], w->pause);
    }

  /*** Open File ***/
  if ( ! open_in(&f, fname, w->err.fp) )
    return;

  /*** show heading ***/
  if ((w->num_files > 1) && (w->verbose == (int) TRUE))
    show_file_heading(w, fname);

  /*** process file ***/
  byte_read  = 0L;
  byte_write = 0L;
  while ( (read(f, buf, 1)) > 0)
    {
      byte_read++;
      if ( byte_read >= w->start_byte )
	{
	  byte_write++;
	  if (w->max_bytes != 0L)
	    {
	      if (byte_write > w->max_bytes)
		break;
	    }
	  if ( (w->mode_hex) == (int) TRUE )
	    {
	      if (w->mode_vertical == (int) TRUE)
		show_hex_vertical(1, byte_read, w->out.fp, buf[0], w->pause);
	      else
		show_hex(1, byte_read, w->out.fp, buf[0], w->pause);
	    }
	  if ( (w->mode_decimal) == (int) TRUE )
	    {
	      if (w->mode_vertical == (int) TRUE)
		show_dec_vertical(1, byte_read, w->out.fp, buf[0], w->pause);
	      else
		show_decimal(1, w->out.fp, buf[0], w->pause);
	    }
	  if ( (w->mode_oct) == (int) TRUE )
	    {
	      if (w->mode_vertical == (int) TRUE)
		show_oct_vertical(1, byte_read, w->out.fp, buf[0], w->pause);
	      else
		show_octal(1, w->out.fp, buf[0], w->pause);
	    }
        }
      memset(buf, JLIB2_UCHAR_NULL, 3);
    }

  /*** close file ***/
  if ( (w->mode_hex) == (int) TRUE )
    {
      if (w->mode_vertical == (int) TRUE)
	show_hex_vertical(2, byte_read, w->out.fp, JLIB2_UCHAR_NULL, w->pause);
      else
	show_hex(2, byte_read, w->out.fp, JLIB2_UCHAR_NULL, w->pause);
    }
  if ( (w->mode_decimal) == (int) TRUE )
    {
      if (w->mode_vertical == (int) TRUE)
	show_dec_vertical(2, byte_read, w->out.fp, JLIB2_UCHAR_NULL, w->pause);
      else
	show_decimal(2, w->out.fp, JLIB2_UCHAR_NULL, w->pause);
    }
  if ( (w->mode_oct) == (int) TRUE )
    {
      if (w->mode_vertical == (int) TRUE)
	show_oct_vertical(2, byte_read, w->out.fp, JLIB2_UCHAR_NULL, w->pause);
      else
	show_octal(2, w->out.fp, JLIB2_UCHAR_NULL, w->pause);
    }

  fflush(w->out.fp);
  if (fname != (char *) NULL)
    close(f);

} /* process_file() */

/*
 * process_all_files()
 */
void process_all_files(int argc, char **argv, work_area *w)

{

  int i;

  w->num_files = 0;
  for (i = optind; i < argc; i++)
    (w->num_files)++;

  for (i = optind; i < argc; i++)
    process_file(w, argv[i]);

  if (i == optind)
    process_file(w, FILE_NAME_STDIN);

} /* process_all_files() */

/*
 * main()
 */
int main(int argc, char **argv)
{

  work_area w;

#ifdef OpenBSD
  if(pledge("stdio rpath wpath cpath",NULL) == -1)
    err(1,"pledge\n");
#endif

  init(argc, argv, &w);

  process_all_files(argc, argv, &w);

  exit_process(EXIT_SUCCESS, &w);
  return(EXIT_SUCCESS);

}  /* main() */
