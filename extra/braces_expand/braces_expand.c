#include "braces_expand.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_vec.h"
#include "utils.h"

/* Basic idea:
   Segregate the text into 3 sections: preamble (stuff before an open brace),
   postamble (stuff after the matching close brace) and amble (stuff after
   preamble, and before postamble).  Expand amble, and then tack on the
   expansions to preamble.  Expand postamble, and tack on the expansions to
   the result so far.
*/

/* String to abridge a sequence. */
static const char *kSeq = "..";
/* The character which is used to separate arguments. */
static const int kSep = ',';

/* Gets the amble's position index in text.
 *
 * @param text string
 * @param amble_start[out] amble's start index in text
 * @param amble_end[out] amble's end index in text
 * @param seq[out] it will be set to 1 if found a sequence
 *                 abbreviation amble, otherwise, set to 0.
 * @return 1 for a valid amble found
 *         0 for no valid amble found.
 */
static int GetAmbleIdx(char *text, int *amble_start,
                       int *amble_end, int *seq);

/* Expands the amble part, not including sequence abbr style
 *
 * @param amble amble part of text
 * @param len length of amble text
 * @return the array of string, each item is one part of the amble.
 */
static char **ExpandAmble(char *amble, int len);

/* Expands the sequence abbreviation string
 *
 * @param text string
 * @param len length of string
 * @return the array of string, include all items in expanded sequence;
 *         or original text if it is not an valid sequence abbreviation.
 */
static char **ExpandSeq(char *text, int len);

/* Finds next position of character satisfy in part of the text.
 * In particular, ignore the char in the nested {} structure,
 * except the char '{' itself.
 *
 * @param text string
 * @param begin search starting position in text
 * @param end search ending position in text
 * @param satisfy character for searching
 * @return the index of the char first occurs in [begin, end] part
 *         of text, it must be in [begin, end], or -1 for otherwise.
 */
static int FindNextItemIdx(char *text, int begin, int end, char satisfy);


/* Expands the content in braces {} and returns an array of strings */
char **ExpandBrace(char *text) {
  int amble_len = 0, text_len = 0, pre_len = 0;
  char *pre_amble = NULL, *post_amble = NULL, *amble = NULL;
  char **tack = NULL, **result = NULL;
  int seq = 0, amble_start = 0, amble_end = 0;

  text_len = strlen(text);
  result = StrVecCreate(2);

  if (!text_len) {
    result[0] = NULL;
    return result;
  }

  /* Gets an valid amble, if do not exist, return */
  if (!GetAmbleIdx(text, &amble_start, &amble_end, &seq)) {
    /* no valid amble found, just return. */
    result[0] = strdup(text);
    result[1] = NULL;
    return result;
  }

  pre_len = amble_start - 1;
  amble_len = amble_end - amble_start;
  post_amble = text + pre_len + amble_len + 2;

  if (seq) {
    --amble_start;
    ++amble_end;
    amble_len += 2;
  }

  pre_amble = SubStr(text, 0, pre_len);
  amble = SubStr(text, amble_start, amble_end);
  result[0] = strdup(pre_amble);
  result[1] = NULL;

  if (seq) {
    tack = ExpandSeq(amble, amble_len);
  } else {
    tack = ExpandAmble(amble, amble_len);
  }

  if (tack) {
    result = StrVecMerge(result, tack);
    /* Frees the content of tack. */
    StrVecDispose(tack);
  }

  if (tack = ExpandBrace(post_amble)) {
    result = StrVecMerge(result, tack);
    /* Frees the content of tack. */
    StrVecDispose(tack);
  }

  free(tack);
  free(amble);
  free(pre_amble);

  return result;
}

static int GetAmbleIdx(char *text, int *amble_start,
                       int *amble_end, int *seq) {
  char *p = NULL, *amble = NULL;
  int amble_len = 0;
  int text_len = strlen(text);
  *amble_start = 0;
  *amble_end = 0;

  /* finding the amble part of text. */
  while ((p = strchr(text + *amble_start, '{')) != NULL) {
    *amble_start = p - text + 1;

    /* finding the matching close brace. */
    *amble_end = FindNextItemIdx(text, *amble_start, text_len, '}');

    /* If we found a matching close brace then check it is valid or not */
    if (*amble_end > 0) {
      int idx = 0;
      amble_len = *amble_end - *amble_start;
      amble = text + *amble_start;
      idx = FindNextItemIdx(text, *amble_start, *amble_end, kSep);

      /* If found a separator in this amble, it is valid, return */
      if (idx > 0) {
        return 1;
      }
      /* If no sepearator found, but found a nested '{', then,
       * check the nested amble is valid or not. */
      idx = FindNextItemIdx(text, *amble_start, *amble_end, '{');
      if (idx > 0) {
        continue;
      }
      /* no separator, no nested '{', but found a sequence abbreviation */
      if ((p = strstr(text + *amble_start, kSeq)) && (p - amble) < amble_len) {
        /* It does not check if the sequence abbreviation is vaild or not */
        *seq = 1;
        return 1;
      }

      /* no separator, no neseted '{', no sequence abbr, not valid */
      return 0;
    }
  }
  /* Not return yet, not valid. */
  return 0;
}

static char **ExpandAmble(char *amble, int len) {
  char **result = NULL,  **partial = NULL;
  char *tem = NULL;
  char c;
  int  re_len = 0, tem_end = 0, level = 0, tem_start = 0, tem_len = 0;

  do {
    tem_end = FindNextItemIdx(amble, tem_start, len, kSep);
    /* No more seperator, it is the last item. */
    tem_end = tem_end < 0 ? len : tem_end;
    tem = SubStr(amble, tem_start, tem_end);

    partial = ExpandBrace(tem);

    if (result == NULL) {
      result = partial;
    } else {
      char **new_result;
      new_result = StrVecConcat(result, partial);

      if (!new_result) {
        printf("Error: memory overflow.");
        exit(1);
      }

      free(result);
      free(partial);
      result = new_result;
    }
    /* Next item start index*/
    tem_start = tem_end + 1;
  } while (tem_end != len);

  return result;
}

static const int kChar = 1;
static const int kInt = 2;

static char **MakeSeq(int begin, int end, int type, int width) {
  int n = 0, i = 0;
  char **result = NULL, *t = NULL ;
  int incr = 1;

  n = abs(end - begin) + 1;
  result = StrVecCreate(n + 1);

  if (begin > end) {
    incr = -incr;
  } else if (begin < end)
    incr = incr;

  /* Make sure we go through the loop at least once, so {3..3} prints `3' */
  i = 0;
  n = begin;
  do {
    if (type == kInt) {
      t = malloc((width + 1) * sizeof(*t));
      t = IntToStr(n, t);
      result[i++] = t;
    } else	{
      t = malloc(2 * sizeof(*t));
      t[0] = n;
      t[1] = '\0';
      result[i++] = t;
    }
    n += incr;
    if ((incr < 0 && n < end) || (incr > 0 && n > end)) {
      break;
    }
  } while (1);

  result[i] = NULL;

  return result;
}

static char **ExpandSeq(char *text, int len) {
  /* Note: text must be start with '{' and end with '} */

  char *t = NULL, *lhs = NULL, *rhs = NULL;
  char **result = NULL;
  int lhs_len = 0, rhs_len = 0, lhs_v = 0, rhs_v = 0;
  int type = 0, width = 0, seq_len = 0, break_return = 0;

  char *lhs_start = text + 1;
  seq_len = strlen(kSeq);

  /* Splits the text to lhs, kSeq, rhs three parts. */
  if ((t = strstr(text, kSeq)) == NULL) {
    break_return = 1;
    goto RETURN;
  }

  lhs_len = t - lhs_start;
  rhs_len = len - lhs_len - seq_len;
  lhs = SubStr(lhs_start, 0, lhs_len);
  rhs = SubStr(lhs_start, lhs_len + seq_len, len - 2);

  if (lhs[0] == '\0' || rhs[0] == '\0')  {
    break_return = 1;
    goto RETURN;
  }

  /* Now figure out whether lhs and rhs are integers or letters.
   * Both sides have to match. */
  if (isalpha(lhs[0]) && lhs[1] == '\0' && isalpha(rhs[0]) && rhs[1] == '\0') {
    lhs_v = lhs[0];
    rhs_v = rhs[0];
    type = kChar;
    width = 1;
  } else if (StrToInt(lhs, &lhs_v) && StrToInt(rhs, &rhs_v)) {
    type = kInt;
    width = lhs_len >= rhs_len ? lhs_len : rhs_len;
  } else {
    break_return = 1;
    goto RETURN;
  }

RETURN:
  free(lhs);
  free(rhs);

  if (break_return) {
    result = StrVecCreate(2);
    result[0] = strdup(text);
    result[1] = NULL;
  } else {
    /* Generate sequence and return */
    result = MakeSeq(lhs_v, rhs_v, type, width);
  }

  return result;
}

static int FindNextItemIdx(char *text, int begin, int end, char satisfy) {
  int c, i = 0, level = 0;

  i = begin;

  while ((c = text[i]) != '\0' && i < end) {
    switch (c) {
      case '{':
        if (c == satisfy) {
          return i;
        }
        ++level;
        break;
      case '}':
        if (c == satisfy && level == 0) {
          return i;
        }

        if (level > 0) {
          --level;
        }
        break;
      default:
        if (level == 0 && c == satisfy) {
          return i;
        }
        break;
    }
    ++i;
  }

  return -1;
}
