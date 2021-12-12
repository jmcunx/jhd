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

#ifndef HD_H

#define PROG_NAME  "jhd"
#define REV_JHD "$Id: jhd.h,v 3.3 2020/06/14 19:14:44 jmccue Exp $"

#define MAX_STR 20
#define MAX_HEX 16
#define MAX_OCT 8
#define JHD_MSG_SIZE 256
#define DEFAULT_MAX    0L
#define DEFAULT_START  0L

#ifdef MSDOSTYPE
#define HD_OMODE (O_BINARY | O_RDONLY)
#else
#define HD_OMODE O_RDONLY
#endif

/*** Types ***/
typedef struct f_file_info
  {
    FILE *fp;
    char *fname;
  } f_info;

typedef struct work_area_s
{
  char *prog_name;
  long int start_byte;         /* Start print at byte      */
  long int max_bytes;          /* print max byte count     */
  int mode_oct;                /* true or false            */
  int mode_decimal;            /* true or false            */
  int mode_hex;                /* true or false            */
  int mode_vertical;           /* true or false            */
  int processed;               /* Files Processed          */
  int num_files;               /* total number of files    */
  int force;                   /* TRUE or FALSE, defaults to FALSE */
  int verbose;                 /* TRUE or FALSE, defaults to FALSE */
  f_info out;
  f_info err;
} work_area;

/*** prototypes ***/
unsigned char cnv_chr(unsigned char);
void process_arg(int, char **, work_area *);
void init(int, char **, work_area *);
int  show_rev(FILE *, char *);
int  show_help(FILE *, char *);
void show_hex(int, long int, FILE *, unsigned char);
void show_decimal(int, FILE *, unsigned char);
void show_octal(int, FILE *, unsigned char);
void show_hex_vertical(int, long int, FILE *, unsigned char);
void show_dec_vertical(int, long int, FILE *, unsigned char);
void show_oct_vertical(int, long int, FILE *, unsigned char);
void exit_process(int, work_area *);

#endif  /* JHD_H */

/* jhd.h */
