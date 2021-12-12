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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <j_lib2.h>
#include <j_lib2m.h>

#include "jhd.h"

char *rev_jhd_u = "$Id: jhd_u.c,v 3.4 2021/02/21 19:56:51 jmccue Exp $";

/*
 * cnv_chr() -- return a prinitable character
 */
unsigned char cnv_chr(unsigned char c)

{

  if ( c < (unsigned char) 31)
    return((unsigned char) '.');
  if ( c > (unsigned char) 254)
    return((unsigned char) '.');

  if ( isprint(c) )
    return(c);
  else
    return((unsigned char) '.');

} /* cnv_chr() */

/* jhd_u.c */
