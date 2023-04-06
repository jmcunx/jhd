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

#ifdef HAVE_JLIB
#include <j_lib2.h>
#include <j_lib2m.h>
#endif

#include "jhd.h"

/*
 * clear_work()
 */
void clear_work(work_area *w, char *a)

{

  w->pause             = 0L;
  w->processed         = (int) 0;
  w->num_files         = (int) 0;
  w->force             = (int) FALSE;
  w->mode_oct          = (int) FALSE;
  w->mode_decimal      = (int) FALSE;
  w->mode_hex          = (int) TRUE;
  w->mode_vertical     = (int) FALSE;
  w->max_bytes         = DEFAULT_MAX;
  w->start_byte        = DEFAULT_START;
  w->verbose           = (int) TRUE;
  w->prog_name         = j2_get_prgname(a, PROG_NAME);

  memset(&(w->err), '\0', sizeof(f_info));
  memset(&(w->out), '\0', sizeof(f_info));

  w->out.fp = stdout;
  w->err.fp = stderr;

} /* clear_work() */

/*
 * init() -- setup for Run
 */
void init(int argc, char **argv, work_area *w)

{

  clear_work(w, argv[0]);

  /* process options */
  process_arg(argc, argv, w);

  if (w->max_bytes < 1L) /* if < 1, changed to default */
    w->max_bytes = DEFAULT_MAX;
  if (w->start_byte < 1L) /* if < 1, changed to default */
    w->start_byte = DEFAULT_START;

} /* process_arg() */
