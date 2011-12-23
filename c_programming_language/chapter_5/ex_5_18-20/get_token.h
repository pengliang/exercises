#ifndef K_AND_R_ASSIGNMENTS_EX_5_20_GET_TOKEN_H
#define K_AND_R_ASSIGNMENTS_EX_5_20_GET_TOKEN_H

enum TokenType {
  kBegin,
  kName,
  kParens,
  kBrackets
};

/* Gets next token from user's input
 *
 * @param token[out] buffer to store the token
 * @return an integer to indicate the token's type
 */
int GetToken(char *token);

#endif // K_AND_R_ASSIGNMENTS_EX_5_20_GET_TOKEN_H
