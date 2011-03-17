#include "string_vec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **StrVecCreate(int n) {
  return ((char **)malloc ((n) * sizeof (char *)));
}

/* Allocates and returns a new copy of ARRAY and its contents. */
char **StrVecCopy(char **array) {
  register int i;
  int len;
  char **ret;

  len = StrVecLen(array);

  ret = (char **)malloc((len + 1) * sizeof (char *));
  for (i = 0; array[i]; ++i) {
    ret[i] = strdup(array[i]);
  }

  ret[i] = (char *)NULL;

  return (ret);
}

/* Returns the length of ARRAY, a NULL terminated array of char *. */
int StrVecLen(char **array) {
  register int i;

  for (i = 0; array[i]; ++i) {}

  return (i);
}

/* Disposes the string vector's content, but not itself.*/
void StrVecDispose(char **array) {
  register int i;

  if (array == 0) {
    return;
  }

  for (i = 0; array[i]; i++) {
    free (array[i]);
  }
}

/* Frees the contents of array and itself. */
void StrVecFree(char **array) {
  if (array == 0) {
    return;
  }

  StrVecDispose(array);
  free (array);
}

void StrVecPrint(char **array) {
  register int i;

  for (i = 0; array[i]; ++i) {
    printf("%s ", array[i]);
  }
  putchar('\n');
}

char **StrVecConcat(char **arr1, char **arr2) {
  register int lr = 0, lp = 0, i, j;
  char **result = NULL;

  lr = StrVecLen(arr1);
  lp = StrVecLen(arr2);

  result = (char **)malloc((lp + lr + 1) * sizeof(char *));

  if (result == NULL) {
    return NULL;
  }

  for (i = 0; i < lr; ++i) {
    result[i] = arr1[i];
  }

  for (j = 0; j < lp; ++j) {
    result[lr + j] = arr2[j];
  }

  result[lr + j] = NULL;

  return result;
}

char **StrVecMerge(char **arr1, char **arr2) {
  register int i, j, len, len1, len2;
  register char **result;

  len1 = StrVecLen(arr1);
  len2 = StrVecLen(arr2);

  if (len1 == 0) {
    return (StrVecCopy(arr2));
  }

  if (len2 == 0) {
    return (StrVecCopy(arr1));
  }

  result = (char **)malloc((1 + (len1 * len2)) * sizeof (char *));

  len = 0;
  for (i = 0; i < len1; i++) {
    int strlen_1 = strlen (arr1[i]);
    for (j = 0; j < len2; j++)	{
      result[len] = (char *)malloc (1 + strlen_1 + strlen (arr2[j]));
      strcpy(result[len], arr1[i]);
      strcpy(result[len] + strlen_1, arr2[j]);
      len++;
    }
    free(arr1[i]);
  }
  free(arr1);
  result[len] = (char *)NULL;

  return (result);
}
