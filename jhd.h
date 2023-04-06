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

#ifndef HD_H

#define PROG_NAME  "jhd"
#define REV_JHD "INCLUDE"

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

#ifndef JLIB2_CHAR_NULL
#define NO_JLIB 1
#define JLIB2_INT_NULL   ((int) '\0')
#define JLIB2_CHAR_NULL  ((char) '\0')
#define JLIB2_UCHAR_NULL ((unsigned char) '\0' )
#endif

#ifndef NULL
#define NULL '\0'
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef SSIZE_T
#define SSIZE_T ssize_t
#endif
#ifndef TAB_CHAR
#define TAB_CHAR 0x09
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
  long int start_byte;         /* Start print at byte                 */
  long int max_bytes;          /* print max byte count                */
  int mode_oct;                /* true or false                       */
  int mode_decimal;            /* true or false                       */
  int mode_hex;                /* true or false                       */
  int mode_vertical;           /* true or false                       */
  int processed;               /* Files Processed                     */
  int num_files;               /* total number of files               */
  int force;                   /* TRUE or FALSE, defaults to FALSE    */
  int verbose;                 /* TRUE or FALSE, defaults to FALSE    */
  long int pause;              /* microsecinds to paus between prints */
  f_info out;
  f_info err;
} work_area;

/*** messages ***/
#ifdef NO_JLIB
#define ARG_DECIMAL       'D'  /* Decimal Mode                       */
#define ARG_ERR           'e'  /* Output Error File                  */
#define ARG_FORCE         'f'  /* force create files                 */
#define ARG_HELP          'h'  /* Show Help                          */
#define ARG_HEX           'x'  /* Hex   Mode                         */
#define ARG_MAX_BYTES     'm'  /* Show Char Count                    */
#define ARG_OCT           'O'  /* Octal Mode                         */
#define ARG_OUT           'o'  /* Output File                        */
#define ARG_PAUSE         's'  /* Pause for for microseconds         */
#define ARG_QUIET         'q'  /* Quiet Mode                         */
#define ARG_START         'S'  /* start print at line #              */
#define ARG_VERSION       'V'  /* Show Version Information           */
#define ARG_VERTICAL      'v'  /* Vertical Display                   */
#define FILE_NAME_STDIN   "-"
#define LIT_C80           "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
#define LIT_INFO_01       "\tBuild: %s %s\n"
#define LIT_REV           "Revision"
#define LIT_STDIN         "(standard input)"
#define MSG_ERR_E000      "Try '%s %c%c' for more information\n"
#define MSG_ERR_E002      "ERROR E002: Cannot open '%s' for write, processing aborted\n"
#define MSG_ERR_E008      "ERROR E008: '%s' is an invalid value for %c%c, must be numeric\n"
#define MSG_ERR_E016      "ERROR E016: File %s cannot be found or no access\n"
#define MSG_ERR_E025      "ERROR E025: File %s cannot be created, already exists\n"
#define MSG_WARN_W002     "W002: Open Error Bypass File '%s' : %s\n"
#define SWITCH_CHAR       '-'
#define USG_MSG_ARG_DECIMAL    "\t%c%c\t\t: Decimal Dump\n"
#define USG_MSG_ARG_ERR        "\t%c%c file\t\t: Write errors to file 'file', default stderr\n"
#define USG_MSG_ARG_FORCE      "\t%c%c\t\t: force create of files when found\n"
#define USG_MSG_ARG_HELP       "\t%c%c\t\t: Show brief help and exit\n"
#define USG_MSG_ARG_HEX        "\t%c%c\t\t: Hexadecimal Dump (default)\n"
#define USG_MSG_ARG_MAX_BYTES  "\t%c%c n\t\t: Stop dump after showing 'n' bytes\n"
#define USG_MSG_ARG_OCT        "\t%c%c\t\t: Octal Dump\n"
#define USG_MSG_ARG_OUT        "\t%c%c file\t\t: Write output to file 'file', default stdout\n"
#define USG_MSG_ARG_PAUSE      "\t%c%c n\t\t: Sleep for 'n' microseconds after each output line\n"
#define USG_MSG_ARG_QUIET_2    "\t%c%c\t\t: do not show file headings.\n"
#define USG_MSG_ARG_START      "\t%c%c b\t\t: Start dump at byte 'b'\n"
#define USG_MSG_ARG_VERSION    "\t%c%c\t\t: Show revision information and exit\n"
#define USG_MSG_ARG_VERTICAL   "\t%c%c\t\t: Vertical display\n"
#define USG_MSG_OPTIONS        "Options\n"
#define USG_MSG_USAGE          "usage:\t%s [OPTIONS] [FILES ...]\n"
#endif /* NO_JLIB */

/*** prototypes ***/
unsigned char cnv_chr(unsigned char);
void process_arg(int, char **, work_area *);
void init(int, char **, work_area *);
int  show_rev(FILE *, char *);
int  show_help(FILE *, char *);
void show_hex(int, long int, FILE *, unsigned char, long int);
void show_decimal(int, FILE *, unsigned char, long int);
void show_octal(int, FILE *, unsigned char, long int);
void show_hex_vertical(int, long int, FILE *, unsigned char, long int);
void show_dec_vertical(int, long int, FILE *, unsigned char, long int);
void show_oct_vertical(int, long int, FILE *, unsigned char, long int);
void exit_process(int, work_area *);

#ifdef NO_JLIB
char *j2_get_prgname(char *argv_0, char *default_name);
int j2_f_exist(char *file_name);
int j2_is_numr(char *s);
void j2_sleepm(long int micro);
#endif /* NO_JLIB */

#endif  /* JHD_H */
