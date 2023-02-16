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
#include <stdlib.h>
#include <j_lib2.h>
#include <j_lib2m.h>

#include "jhd.h"

#define MSG_HELP_11 "hex/octal dump of one or more files."

/*
 * show_rev()
 */
int show_rev(FILE *fp, char *progname)


{
  fprintf(fp,"%s %s:\n", progname, LIT_REV);
  fprintf(fp,"\t%s %s\n", LIT_INFO_02, j2_get_build());

#ifdef OSTYPE
  fprintf(fp,"\t%s\n",OSTYPE);
#endif  /* OSTYPE  */
#ifdef PRETTY_NAME
  fprintf(fp,"\t%s\n",PRETTY_NAME);
#endif  /* PRETTY_NAME  */
  fprintf(fp, LIT_INFO_01, __DATE__, __TIME__);

  return(EXIT_FAILURE);

} /* show_rev() */

/*
 * show_help()
 */
int show_help(FILE *fp, char *progname)

{

  fprintf(fp, USG_MSG_USAGE, progname);
  fprintf(fp, "\t%s\n", MSG_HELP_11);
  fprintf(fp, USG_MSG_OPTIONS);

  fprintf(fp, USG_MSG_ARG_DECIMAL,   SWITCH_CHAR, ARG_DECIMAL);
  fprintf(fp, USG_MSG_ARG_ERR,   SWITCH_CHAR, ARG_ERR);
  fprintf(fp, USG_MSG_ARG_FORCE, SWITCH_CHAR, ARG_FORCE);
  fprintf(fp, USG_MSG_ARG_HELP,  SWITCH_CHAR, ARG_HELP);

  fprintf(fp, USG_MSG_ARG_MAX_BYTES, SWITCH_CHAR, ARG_MAX_BYTES);
  fprintf(fp, USG_MSG_ARG_OCT,       SWITCH_CHAR, ARG_OCT);
  fprintf(fp, USG_MSG_ARG_OUT,       SWITCH_CHAR, ARG_OUT);
  fprintf(fp, USG_MSG_ARG_QUIET_2,   SWITCH_CHAR, ARG_QUIET);
  fprintf(fp, USG_MSG_ARG_START,     SWITCH_CHAR, ARG_START);
  fprintf(fp, USG_MSG_ARG_PAUSE,     SWITCH_CHAR, ARG_PAUSE);
  fprintf(fp, USG_MSG_ARG_VERSION,   SWITCH_CHAR, ARG_VERSION);
  fprintf(fp, USG_MSG_ARG_VERTICAL,  SWITCH_CHAR, ARG_VERTICAL);
  fprintf(fp, USG_MSG_ARG_HEX,       SWITCH_CHAR, ARG_HEX);

  return(EXIT_FAILURE);

} /* show_help() */
