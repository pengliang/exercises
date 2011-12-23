#ifndef K_AND_R_ASSIGNMENTS_EX_8_8_LOCAL_ALLOCL_H
#define K_AND_R_ASSIGNMENTS_EX_8_8_LOCAL_ALLOCL_H
typedef long Align;

union header {
  struct {
    union header *ptr;
    unsigned size;
  } s;
  Align x;
};

typedef union header Header;

/* Allocates size bytes and returns a pointer to
 * the allocated memory. The memory is not cleared.
 *
 * @param nbytes size
 * @return a void pointer to the allocated memory or
 *         NULL for failure.
 */
void *malloc(unsigned nbytes);

/* Allocates memory for an array of n elements of
 * size bytes each, and returns a pointer to the
 * allocated memory. The memory is set to zero.
 *
 * @param n number of elements
 * @param size each element's size
 * @return a pointer to the allocated memory or
 *         NULL for failure.
 */
void *calloc(unsigned n, unsigned size);

/* Frees the memory space pointed to by ptr
 *
 * @param ptr memory space pointer
 */
void free(void *ptr);

/* Frees the memory block pointed to by p of n characters.
 *
 * @param p memory block pointer
 * @param n size
 */
void bfree(char *p, unsigned n);

#endif // K_AND_R_ASSIGNMENTS_EX_8_8_LOCAL_ALLOCL_H
