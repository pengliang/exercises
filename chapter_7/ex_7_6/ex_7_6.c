#include <stdio.h>
#include <stdlib.h>

/* Compares two files and prints the first different line.
 *
 * @param fp1 first file pointer
 * @param fp2 second file pointer*/
void CompFiles(FILE *fp1, FILE *fp2);

/* Compares two files and prints the first different line.*/
int main(int argc, char *argv[]) {
  FILE *fp1, *fp2;

  if (argc != 3) {
    printf("Error: need two file names\n");
    exit(1);
  } else {
    if ((fp1 = fopen(*++argv, "r")) == NULL) {
      printf("Error: can't open file %s\n", *argv);
      exit(1);
    } else if ((fp2 = fopen(*++argv, "r")) == NULL) {
      printf("Error: can't open file %s\n", *argv);
      exit(1);
    } else {
      CompFiles(fp1, fp2);
      fclose(fp1);
      fclose(fp2);
      exit(0);
    }
  }
  return 0;
}

void CompFiles(FILE *fp1, FILE *fp2) {
  char *line1 = NULL, *line2 = NULL;
  size_t len = 0;
  ssize_t len1, len2;
  int line = 0;

  do {
    len1 = getline(&line1, &len, fp1);
    len2 = getline(&line2, &len, fp2);
    ++line;
    if (len1 != -1 && len2 != -1) {
      if (strcmp(line1, line2) != 0) {
        printf("first different line is line %d:\n", line);
        printf("first file: %s\n", line1);
        printf("second file: %s\n", line2);
        break;
      }
    } else if (len2 == -1 && len1 != -1) {
      printf("first different line is line %d:\n", line);
      printf("first file: %s\n", line1);
      printf("end of second file.");
      break;
    } else if (len1 == -1 && len2 != -1) {
      printf("first different line is line %d:\n", line);
      printf("end of first file");
      printf("second file: %s\n", line2);
      break;
    }
  } while (len1 != -1 && len2 != -1);

  if (len1 == -1 && len2 == -1) {
    printf("no different lines in two files.\n");
  }

  free(line1);
  free(line2);
}
