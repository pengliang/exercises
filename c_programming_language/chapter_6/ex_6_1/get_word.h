#ifndef K_AND_R_ASSIGNMENTS_EX_6_1_GET_WORD_H
#define K_AND_R_ASSIGNMENTS_EX_6_1_GET_WORD_H

/* Gets next word or a single non-white space cahracter from input,
 * where a valid word is either a string of letters, digits and
 * underscores beginning with a letter or underscore.
 *
 * @param word[out] string buffer
 * @param max_word_len max length of the buffer
 * @return 1 for finding a valid word
 *         EOF(-1) for the end of file
 *         the character itself otherwise.*/
int GetWord(char *word, int max_word_len);

#endif // K_AND_R_ASSIGNMENTS_EX_6_1_GET_WORD_H
