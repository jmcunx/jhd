/*
 * Copyright (c) 2006 2007 2008 ... 2021 2022
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
#include <j_lib2.h>
#include <j_lib2m.h>

#include "jhd.h"

#define MAX_PRINT_LINE  70
#define MAX_FMT_DEC 999999999L
#define SIZE_FMT_HEX 3

/*
 * show_hex_line() -- show 'normal' hex mode line
 *                    rmode 0: Initialize and exit
 *                          1: process
 *                          2: flush
 */
void show_hex_line(int rmode, 
                   FILE *fp, 
                   long int byte, 
                   int curr_pos, 
                   unsigned char *raw, 
                   unsigned char *string)

{

  int i;

  fprintf(fp, "%08lX  ", (unsigned long int) (byte - curr_pos ));

  /*** show hex chars ***/
  for (i = 0; i < curr_pos; i++)
    {
      fprintf(fp, "%02X ", (unsigned int) raw[i]);
      if ( (i == 3) || (i == 7) || (i == 11) )
	fprintf(fp, " ");
    }

  /*** show byte and data ***/
  if (rmode == 2)
    {
      if (curr_pos != MAX_HEX)
	{
	  for (i = curr_pos; i < MAX_HEX; i++)
	    {
	      fprintf(fp, "   ");
	      if ( (i == 3) || (i == 7) || (i == 11) )
		fprintf(fp, " ");
	    }
	}
      fprintf(fp, "|%-16s|\n", string);
      fprintf(fp, "%08lX\n", byte);
    }
  else
    fprintf(fp, "|%-16s|\n", string);

  /*** clear ***/
  memset(raw,    JLIB2_UCHAR_NULL, MAX_HEX);
  memset(string, JLIB2_UCHAR_NULL, MAX_HEX);

} /* show_hex_line() */

/*
 * show_hex() -- Show hex
 *               rmode 0: Initialize and exit
 *                     1: process
 *                     2: flush
 */
void show_hex(int rmode, long int byte, FILE *fp, unsigned char c)

{
  static int curr_pos = 0;
  static unsigned char raw[MAX_HEX];
  static unsigned char string[(MAX_HEX + 1)];

  switch (rmode)
    {
      case 0:   /*  initialize only */
	curr_pos = 0;
	memset(raw,    JLIB2_UCHAR_NULL, MAX_HEX);
	memset(string, JLIB2_UCHAR_NULL, MAX_HEX);
	return;
      case 1:
	/*** if (curr_pos == (MAX_HEX - 1))  ***/
	if (curr_pos == MAX_HEX)
	  {
	    show_hex_line(rmode, fp, byte, curr_pos, raw, string);
	    curr_pos = 0;
	  }
	raw[curr_pos] = c;
	string[curr_pos] = cnv_chr(c);
	curr_pos++;
	break;
      case 2:
	show_hex_line(rmode, fp, byte, curr_pos, raw, string);
	curr_pos = 0;
	return;
    }
  
} /* show_hex() */

/*
 * show_hex_vertical() -- Show in vertical
 *                        rmode 0: Initialize and exit
 *                              1: process
 *                              2: flush
 */
void show_hex_vertical(int rmode, long int byte, FILE *fp, unsigned char c)

{
  static char pline0[MAX_PRINT_LINE];
  static char pline1[MAX_PRINT_LINE];
  static char pline2[MAX_PRINT_LINE];
  static int curr = (int) 0;
  char fmt_hx[SIZE_FMT_HEX];

  if ( (rmode == 0) ||  (rmode == 4) )
    {
      curr = (int) 0;
      memset(pline0, JLIB2_CHAR_NULL, MAX_PRINT_LINE);
      memset(pline1, JLIB2_CHAR_NULL, MAX_PRINT_LINE);
      memset(pline2, JLIB2_CHAR_NULL, MAX_PRINT_LINE);
      return;
    }
  if (rmode == 2)
    {
      if ((*pline0) != JLIB2_CHAR_NULL)
        {
	  byte -= (long int) strlen(pline0); /* adjust for line size */
          if (byte > MAX_FMT_DEC)
            {
	      fprintf(fp, "_________ %s\n", pline0);
	      fprintf(fp, "_________ %s\n", pline1);
	    }
	  else
            {
	      fprintf(fp, "%9ld %s\n", byte, pline0);
	      fprintf(fp, "%09X %s\n", (unsigned int) byte, pline1);
	    }
	  fprintf(fp, "          %s\n", pline2);
	}
      show_hex_vertical(0, byte, fp, JLIB2_UCHAR_NULL);
      return;
    }
  
  if (curr >= (MAX_PRINT_LINE - 1))
    {
      byte -= (long int) strlen(pline0); /* adjust for line size */
      if (byte > MAX_FMT_DEC)
	{
	  fprintf(fp, "_________ %s\n", pline0);
	  fprintf(fp, "_________ %s\n", pline1);
	}
      else
	{
	  fprintf(fp, "%9ld %s\n", byte, pline0);
	  fprintf(fp, "%09X %s\n", (unsigned int) byte, pline1);
	}
      fprintf(fp, "          %s\n", pline2);
      fprintf(fp, "\n");
      show_hex_vertical(0, byte, fp, JLIB2_UCHAR_NULL);
    }

  snprintf(fmt_hx, SIZE_FMT_HEX, "%02X", c);

  pline0[curr] = cnv_chr(c);
  pline1[curr] = fmt_hx[0];
  pline2[curr] = fmt_hx[1];
  curr++;

} /* show_hex_vertical() */
