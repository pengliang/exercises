#ifndef K_AND_R_ASSIGNMENTS_EX_5_17_SORT_H
#define K_AND_R_ASSIGNMENTS_EX_5_17_SORT_H

#define kNumeric 1
// sort in decreasing order
#define kDecrease 2
// fold upper and lower cases
#define kCase 4
// directory order
#define kDir 8
// specify field
#define kField  16

extern char option;
extern int field_begin;
extern int field_end;

/* Sorts nlines lines string whose pointer stored in the array.
 * The sorting rule is spicified by the global variable 'option'.
 * If option & 16 != 0, it will sort the string by the field
 * in the string specified by 'field_begin' and 'field_end' var.
 *
 * If option & 1 != 0, it will sort the string by numeric order.
 * If option & 2 != 0, it will sort the string asending.
 * If option & 4 != 0, it will sort the string case insensitively.
 * If option & 8 != 0, it will sort the string by directory order.
 *
 * @param line_ptr pointer array stroe the string's address.
 * @param nlines the size of line_ptr array
 */
void SortLines(char *line_ptr[], int nlines);

#endif // K_AND_R_ASSIGNMENTS_EX_5_17_SORT_H
