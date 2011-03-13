#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Finds a string from a file and prints the matched line
 *
 * @param fp file pointer
 * @param file_name file name
 * @param str_pattern substring to be found
 */
void FindPattern(FILE *fp, char *file_name, char *str_pattern);

/* Finds a string from files.*/
int main(int argc, char *argv[]) {
  char *str_pattern;
  FILE *fp;

  if (--argc >= 1) {
    str_pattern = strdup(*++argv);
    if (!str_pattern) {
      printf("Error: memory overflow.\n");
      exit(1);
    }
  } else {
    printf("Usage: find pattern [file ...]\n");
    exit(1);
  }

  if (argc == 1) {
    FindPattern(stdin, "", str_pattern);
  } else {
    while (--argc > 0) {
      if ((fp = fopen(*++argv, "r")) == NULL) {
        printf("Error: can't open file %s\n", *argv);
        exit(1);
      } else {
        FindPattern(fp, *argv, str_pattern);
        fclose(fp);
      }
    }
  }
  free(str_pattern);
  return 0;
}

void FindPattern(FILE *fp, char *file_name, char *str_pattern) {
  char *line = NULL;
  int len = 0;
  int line_num = 0;

  while (getline(&line, &len, fp) != -1) {
    ++line_num;
    if (strstr(line, str_pattern) != NULL) {
      if (*file_name) {
        printf("%s, ", file_name);
      }
      printf("row %d: %s", line_num, line);
    }
  }
}
