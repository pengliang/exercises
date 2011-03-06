#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

static const int kMaxLines = 100;

/* Output the program's usage to stdout. */
static void Usage();

/* Parses program's arguments,
 * setting the global var option, field_begin and field_end.
 *
 * @param argc number of arguments
 * @param argv pointer array of arguments
 */
static void ReadArgs(int argc, char *argv[]);

/* Writes output lines ascending if decr = 0, otherwise, decending.
 *
 * @param line_ptr storage buffer
 * @param nlines the number of lines will be output.
 * @param decr specify the output order
 * */
static void WriteLines(char *line_ptr[], int nlines, int decr);

char option;
int field_begin;
int field_end;

/* Sorts input lines.*/
int main(int argc, char *argv[]) {
  char *line_ptr[kMaxLines];
  int nlines = 0;

  ReadArgs(argc, argv);

  if ((nlines = GetLines(line_ptr, kMaxLines)) > 0) {
    SortLines(line_ptr, nlines);
    WriteLines(line_ptr, nlines, option & kDecrease);
    return 0;
  }
  if (nlines == -1) {
    printf("Error: too many input lines!");
    exit(1);
  }
  exit(2);
}

static void Usage() {
  printf("Usage: sort -cdfnr field_begin field_end\n");
  printf("field_begin should be less than field_end.");
  exit(0);
}

/* Parses program's arguments */
static void ReadArgs(int argc, char *argv[]) {
  char c;

  while (--argc > 0) {
    if ((*++argv)[0] == '-') {
      while (c = *++argv[0]) {
        switch (c) {
          case 'n':
            option |= kNumeric;
            break;
          case 'r':
            option |= kDecrease;
            break;
          case 'c':
            option |= kCase;
            break;
          case 'd':
            option |= kDir;
            break;
          case 'f':
            option |= kField;
            break;
          default:
            printf("Error: illeagal option %c\n", c);
            exit(3);
        }
      }
    } else if (option & kField) {
      field_begin = atoi(*argv);
      if (--argc > 0) {
        field_end = atoi(*++argv);
      } else {
        Usage();
      }
    }
  }

  if (argc || field_end < field_begin) {
    Usage();
  }
}


/* Writes output lines ascending if decr = 0, otherwise, decending. */
static void WriteLines(char *line_ptr[], int nlines, int decr) {
  int i = 0;
  if (decr) {
    // prints lines in decreasing order
    for (i = nlines - 1; i >= 0; --i) {
      printf("%s", line_ptr[i]);
    }
  } else {
    // prints lines in increasing order
    for (i = 0; i < nlines; ++i) {
      printf("%s", line_ptr[i]);
    }
  }
}
