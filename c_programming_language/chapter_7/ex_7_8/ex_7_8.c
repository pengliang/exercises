#include <stdio.h>
#include <stdlib.h>

/* maximum length of one line */
static const int kMaxLine = 80;
/* maximum number of lines on one page */
static const int kMaxPage = 22;
/* maximum number of lines at bottom of pages*/
static const int kMaxBottom = 3;
/* maximum number of lines at head of pages*/
static const int kMaxHead = 3;

/* Prints the header info on each page.
 *
 * @param file_name current file's name
 * @param page_num page number of current file
 * @return the number of lines used by page header
 */
int PrintPageHeader(char *file_name, int page_num);

/* Prints a file with limited lines on one page. 
 *
 * @param fp file pointer
 * @param file_name file name
 */
void PrintFile(FILE *fp, char *file_name);

/* Prints files on stdout, echo new one on a new page. */
int main(int argc, char *argv[]) {
  FILE *fp;

  if (argc == 1) {
    PrintFiles(stdin, "");
  } else {
    while (--argc > 0) {
      if ((fp = fopen(*++argv, "r")) == NULL) {
        printf("Error: can't open file %s\n", *argv);
        exit(1);
      } else {
        PrintFiles(fp, *argv);
        fclose(fp);
      }
    }
  }
  return 0;
}

void PrintFiles(FILE *fp, char *file_name) {
  int line_num = 0, page_num = 0, len = 0;
  char *line = NULL;

  line_num = PrintPageHeader(file_name, ++page_num);

  while (getline(&line, &len, fp) != -1) {
    if (line_num == 1) {
      putchar('\f');
      line_num = PrintPageHeader(file_name, ++page_num);
    }

    puts(line);

    if (++line_num > kMaxPage - kMaxBottom) {
      line_num = 1;
    }
  }
  putchar('\f');
}

int PrintPageHeader(char *file_name, int page_num) {
  int ln = 1;
  printf("\n\n%s  page %d\n", file_name, page_num);
  while (++ln < kMaxHead) {
    putchar('\n');
  }
  return ln;
}
