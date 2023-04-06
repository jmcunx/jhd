/*
 * Copyright (c) 2006 2007 2008 ... 2023 2024
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
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>

#ifdef HAVE_JLIB
#include <j_lib2.h>
#include <j_lib2m.h>
#endif

#include "jhd.h"

#define SCKARG 80

/*
 * open_out() -- save the file anem and check status
 */
int open_out(FILE *wfp, f_info *f, char *fname, int force)

{
  int errsave;

  if (fname == (char *) NULL)
    return((int) TRUE);

  if (force == (int) FALSE)
    {
      if ( j2_f_exist(fname) )
	{
	  fprintf(wfp, MSG_ERR_E025, fname);
	  return((int) FALSE);
	}
    }


  f->fp = fopen(fname, "w");
  errsave = errno;
  if (f->fp == (FILE *) NULL)
    {
      f->fp = stderr;  /* needs to be something */
      fprintf(wfp, MSG_ERR_E002, fname);
      fprintf(wfp, "\t%s\n", strerror(errsave));
      return((int) FALSE);
    }

  /*** success, save file name ***/
  f->fname = strdup(fname);
  return((int) TRUE);

} /* open_out() */

/*
 * close_out() -- Close an output file and release memory
 */
void close_out(f_info *f)

{

  if (f->fname == (char *) NULL)
    return;

  free(f->fname);
  f->fname = (char *)  NULL;

  if (f->fp == (FILE *) NULL)
    return;

  fclose(f->fp);
  f->fp = (FILE *) NULL;

} /* close_out() */

/*
 * process_arg() -- process arguments
 */
void process_arg(int argc, char **argv, work_area *w)

{
  char ckarg[SCKARG];
  int opt;
  int ok;
  char *out_file   = (char *) NULL;
  char *err_file   = (char *) NULL;
  int show_help_brief = (int) FALSE;
  int show_rev_info = (int) FALSE;

  snprintf(ckarg, SCKARG, "%c%c%c%c%c%c%c%c%c:%c:%c:%c:%c:", 
           ARG_FORCE, ARG_HELP, ARG_VERSION, ARG_OCT, ARG_DECIMAL,
           ARG_HEX, ARG_QUIET, ARG_VERTICAL,
           ARG_MAX_BYTES, ARG_START, ARG_OUT, ARG_ERR, ARG_PAUSE);

  while ((opt = getopt(argc, argv, ckarg)) != -1)
    {
      switch (opt)
	{
	  case ARG_HELP:
	    show_help_brief = (int) TRUE;
	    break;
	  case ARG_FORCE:
	    w->force = (int) TRUE;
	    break;
	  case ARG_VERSION:
	    show_rev_info = (int) TRUE;
	    break;
	  case ARG_OCT:
	    w->mode_oct     = (int) TRUE;
	    w->mode_decimal = (int) FALSE;
	    w->mode_hex     = (int) FALSE;
	    break;
	  case ARG_DECIMAL:
	    w->mode_oct     = (int) FALSE;
	    w->mode_decimal = (int) TRUE;
	    w->mode_hex     = (int) FALSE;
	    break;
	  case ARG_HEX:
	    w->mode_oct     = (int) FALSE;
	    w->mode_decimal = (int) FALSE;
	    w->mode_hex     = (int) TRUE;
	    break;
	  case ARG_PAUSE:
	    if (j2_is_numr(optarg) == (int) TRUE)
	      w->pause = atol(optarg);
	    else
	      {
		fprintf(stderr, MSG_ERR_E008, optarg, SWITCH_CHAR, ARG_PAUSE);
		exit_process(EXIT_FAILURE, w);
	      }
	    break;
	  case ARG_QUIET:
	    w->verbose = (int) FALSE;
	    break;
	  case ARG_VERTICAL:
	    w->mode_vertical = (int) TRUE;
	    break;
	  case ARG_MAX_BYTES:
	    if (j2_is_numr(optarg) == (int) TRUE)
	      w->max_bytes = atol(optarg);
	    else
	      {
		fprintf(stderr, MSG_ERR_E008, optarg, SWITCH_CHAR, ARG_MAX_BYTES);
		exit_process(EXIT_FAILURE, w);
	      }
	    break;
	  case ARG_START:
	    if (j2_is_numr(optarg) == (int) TRUE)
	      w->start_byte = atol(optarg);
	    else
	      {
		fprintf(stderr, MSG_ERR_E008, optarg, SWITCH_CHAR, ARG_START);
		exit_process(EXIT_FAILURE, w);
	      }
	    break;
	  case ARG_OUT:
	    out_file = optarg;
	    break;
	  case ARG_ERR:
	    err_file = optarg;
	    break;
	  default:
	    fprintf(stderr, MSG_ERR_E000, w->prog_name, SWITCH_CHAR, ARG_HELP);
	    exit_process(EXIT_FAILURE, w);
	    break;
	}
    }

  /*** if necessary - save stdout/err files and open ***/
  ok = open_out(stderr, &(w->err), err_file, w->force);
  if ( ok )
    ok = open_out(w->err.fp, &(w->out), out_file, w->force);
  if ( ! ok )
    {
      fprintf(w->err.fp, MSG_ERR_E000, w->prog_name, SWITCH_CHAR, ARG_HELP);
      exit(EXIT_FAILURE);
    }

  /*** show_help / rev ***/
  ok = EXIT_SUCCESS;
  if (show_help_brief == (int) TRUE)
    ok = show_help(w->out.fp, w->prog_name);
  if (show_rev_info == (int) TRUE)
    ok = show_rev(w->out.fp, w->prog_name);

  if (ok != EXIT_SUCCESS)
    exit_process(EXIT_FAILURE, w);

} /* process_arg() */

/*
 * exit_process() -- exit processing
 *                   release memory then exit
 */
void exit_process(int err_code, work_area *w)

{

  close_out(&(w->out));
  close_out(&(w->err));

  if (w->prog_name != (char *) NULL)
    free(w->prog_name);

  exit(err_code);

} /* exit_process() */
