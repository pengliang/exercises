#ifndef K_AND_R_ASSIGNMENTS_EXTRA_STRING_VEC_H_
#define K_AND_R_ASSIGNMENTS_EXTRA_STRING_VEC_H_

/* Creates a nsize length string vector, array of char *.
 *
 * @param nsize length of vector
 * @return the pointer to string vector, non NULL terminated.
 */
char **StrVecCreate(int nsize);

/* Gets the length of a string vector array,
 * the last element of array must be NULL.
 *
 * @param array pointer to NULL terminated array of char *.
 * @return the length of array.
 */
int StrVecLen(char **array);

/* Allocates and returns a new copy of array and its contents.
 *
 * @param array pointer to NULL terminated array of char *.
 * @return the pointer to a new copy of array.
 */
char **StrVecCopy(char **array);

/* Gets a new array of strings which is the result of appending each string in
 * arr2 to each string in arr1. The resultant array is len(arr1) * len(arr2)
 * long. For convenience, arr1 (and their contents) are freed, arr2 are not,
 * arr1/arr2 can be NULL, in that case, a new version of arr2/arr1 is returned.
 *
 * @param arr1 pointer to NULL terminated array of char *.
 * @param arr2 pointer to NULL terminated array of char *.
 * @return the pointer to a resultant vector of arr1 and arr2.
 */
char **StrVecMerge(char **arr1, char **arr2);

/* Prints the string vector's content, one element each line.
 *
 * @param array pointer to the string vector
 */
void StrVecPrint(char **array);

/* Free the content of array of char *.
 *
 * @param array pointer to NULL terminated array of char *.
 */
void StrVecDispose(char **array);

/* Free the content and itself of array.
 *
 * @param array pointer to NULL terminated array of char *.
 */
void StrVecFree(char **array);

/* Appending arr2 array to arr1 array, and allocates a new
 * len(arr1) + len(arr2) long array to store the result.
 *
 * @param arr1 pointer to NULL terminated array of char *.
 * @param arr2 pointer to NULL terminated array of char *.
 * @return the pointer to a resultant vector of arr1 and arr2.
 */
char **StrVecConcat(char **arr1, char **arr2);

#endif // K_AND_R_ASSIGNMENTS_EXTRA_STRING_VEC_H_
