/*
** bithacks.h - bit hacks macros. v1.0
**
** Released under the MIT license.
*/

#ifndef BITHACKS_H
#define BITHACKS_H

#define HEXIFY(X) 0x##X##LU

#define B8IFY(Y) (((Y&0x0000000FLU)?1:0)  + \
                  ((Y&0x000000F0LU)?2:0)  + \
                  ((Y&0x00000F00LU)?4:0)  + \
                  ((Y&0x0000F000LU)?8:0)  + \
                  ((Y&0x000F0000LU)?16:0) + \
                  ((Y&0x00F00000LU)?32:0) + \
                  ((Y&0x0F000000LU)?64:0) + \
                  ((Y&0xF0000000LU)?128:0))

#define B8(Z) ((unsigned char)B8IFY(HEXIFY(Z)))

/* test if x is even */
#define B_EVEN(x)        (((x)&1)==0)

/* test if x is odd */
#define B_ODD(x)         (!B_EVEN((x)))

/* test if n-th bit in x is set */
#define B_IS_SET(x, n)   (((x) & (1<<(n)))?1:0)

/* set n-th bit in x */
#define B_SET(x, n)      ((x) |= (1<<(n)))

/* unset n-th bit in x */
#define B_UNSET(x, n)    ((x) &= ~(1<<(n)))

/* toggle n-th bit in x */
#define B_TOGGLE(x, n)   ((x) ^= (1<<(n)))

/* turn off right-most 1-bit in x */
#define B_TURNOFF_1(x)   ((x) &= ((x)-1))

/* isolate right-most 1-bit in x */
#define B_ISOLATE_1(x)   ((x) &= (-(x)))

/* right-propagate right-most 1-bit in x */
#define B_PROPAGATE_1(x) ((x) |= ((x)-1))

/* isolate right-most 0-bit in x */
#define B_ISOLATE_0(x)   ((x) = ~(x) & ((x)+1))

/* turn on right-most 0-bit in x */
#define B_TURNON_0(x)    ((x) |= ((x)+1))

/*
** more bit hacks coming as soon as I post
** an article on advanced bit hacks
*/

/*
 * find the position of the first 0 in a 8-bit array
 * Notice: only intel x86 serial cpu have 'bsfl' command
 *
 * Another algorithm
 *  1. Invert the number
 *  2. Compute the two's complement of the inverted number
 *  3. AND the results of (1) and (2)
 *  4. Find the position by computing the binary logarithm of (3)
   e.x.
   For the number 10110111

    01001000
    10111000
    01001000 AND 10111000 = 00001000
    log2(00001000) = 3
 */
inline unsigned short find_first_zero(uint8_t bit_array)
{
  unsigned pos = 0;

  __asm__("bsfl %1,%0\n\t"
      "jne 1f\n\t"
      "movl $32, %0\n"
      "1:"
      : "=r" (pos)
      : "r" (~(bit_array)));

  if (pos > 7)
    return 8;

  return (unsigned short) pos;
}

#endif
