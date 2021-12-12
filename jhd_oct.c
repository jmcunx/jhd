/*
 * Copyright (c) 2006 2007 2008 ... 2020 2021
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

#include <sys/param.h>
#include <stdio.h>
#include <string.h>
#include <j_lib2.h>
#include <j_lib2m.h>

#include "jhd.h"

#define MAX_PRINT_LINE  70
#define MAX_FMT_OCT 134217727L
#define MAX_FMT_DEC 999999999L
#define SIZE_FMT_OCT 4

char *rev_jhd_oct = "$Id: jhd_oct.c,v 3.5 2021/02/21 19:56:51 jmccue Exp $";

/*
 * show_octal()
 */
void show_octal(int rmode, FILE *fp, unsigned char c)

{
  static long line = 0L;
  static int str_idx = 0;
  int max = 7;

  static unsigned char string[MAX_STR];

  /*** reset and exit ***/
  if (rmode == 0)
    {
      line = 0L;
      str_idx = 0;
      memset(string, JLIB2_UCHAR_NULL, MAX_STR);
      return;
    }

  /*** show ascii file area for last record ***/
  if (rmode == 2)
    {
      if (str_idx > 0)
	{
	  for ( ; str_idx <= max; str_idx++)
	    fprintf(fp, "    ");
	  fprintf(fp, "|%-8s|\n", string);
	}
      fprintf(fp, "%08lo\n", line);
      return;
    }

  /*** initialize ***/
  if (str_idx == 0)
    {
      memset(string, JLIB2_UCHAR_NULL, MAX_STR);
      fprintf(fp, "%08lo  ", line);
    }

  /*** save string ***/
  string[str_idx] = cnv_chr(c);
  str_idx++;

  /*** show byte ***/
  fprintf(fp, "%03o ", c);
  line++;

  /*** do we need a newline ***/
  if (str_idx > max)
    {
      str_idx = 0;
      fprintf(fp, "|%-8s|\n", string);
    }

} /* show_octal() */

/*
 * show_oct_vertical() -- Show in vertical
 *                        rmode 0: Initialize and exit
 *                              1: process
 *                              2: flush
 *                              4: Initialize, but keep byte count
 */
void show_oct_vertical(int rmode, long int byte, FILE *fp, unsigned char c)

{
  static char pline0[MAX_PRINT_LINE];
  static char pline1[MAX_PRINT_LINE];
  static char pline2[MAX_PRINT_LINE];
  static char pline3[MAX_PRINT_LINE];
  static int curr = (int) 0;
  char fmt_oct[SIZE_FMT_OCT];

  if ( (rmode == 0) || (rmode == 4) )
    {
      curr = (int) 0;
      memset(pline0, JLIB2_CHAR_NULL, MAX_PRINT_LINE);
      memset(pline1, JLIB2_CHAR_NULL, MAX_PRINT_LINE);
      memset(pline2, JLIB2_CHAR_NULL, MAX_PRINT_LINE);
      memset(pline3, JLIB2_CHAR_NULL, MAX_PRINT_LINE);
      return;
    }
  if (rmode == 2)
    {
      if ((*pline0) != JLIB2_CHAR_NULL)
        {
	  byte -= (long int) strlen(pline0); /* adjust for line size */
	  if (byte > MAX_FMT_DEC)
	    fprintf(fp, "_________ %s\n", pline0);
	  else
	    fprintf(fp, "%9ld %s\n", byte, pline0);
	  if (byte > MAX_FMT_OCT)
	    fprintf(fp, "_________ %s\n", pline1);
	  else
	    fprintf(fp, "%09o %s\n", (unsigned int) byte, pline1);
	  fprintf(fp, "          %s\n", pline2);
	  fprintf(fp, "          %s\n", pline3);
	  byte += (long int) MAX_PRINT_LINE;
	}
      show_oct_vertical(0, byte, fp, JLIB2_UCHAR_NULL);
      return;
    }
  
  if (curr >= (MAX_PRINT_LINE - 1))
    {
      byte -= (long int) strlen(pline0); /* adjust for line size */
      if (byte > MAX_FMT_DEC)
	fprintf(fp, "_________ %s\n", pline0);
      else
	fprintf(fp, "%9ld %s\n", byte, pline0);
      if (byte > MAX_FMT_OCT)
	fprintf(fp, "_________ %s\n", pline1);
      else
	fprintf(fp, "%09o %s\n", (unsigned int) byte, pline1);
      fprintf(fp, "          %s\n", pline2);
      fprintf(fp, "          %s\n", pline3);
      fprintf(fp, "\n");
      byte += (long int) MAX_PRINT_LINE;
      show_oct_vertical(0, byte, fp, JLIB2_UCHAR_NULL);
    }

  snprintf(fmt_oct, SIZE_FMT_OCT, "%03o", c);

  pline0[curr] = cnv_chr(c);
  pline1[curr] = fmt_oct[0];
  pline2[curr] = fmt_oct[1];
  pline3[curr] = fmt_oct[2];
  curr++;

} /* show_oct_vertical() */

/* END: jhd_oct.c */
