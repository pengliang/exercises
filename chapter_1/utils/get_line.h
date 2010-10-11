#ifndef K_AND_R_ASSIGNMENTS_CHAPTER_1_UTILS_GET_LINE_H_
#define K_AND_R_ASSIGNMENTS_CHAPTER_1_UTILS_GET_LINE_H_
// Reads a line from the standard input. If the user's input is ended with
// line-feed '\n', the line feed character is also included in the output.
//
// @param line_buf[] the buffer to store the user's input
// @param line_buf_length the maximum length of the buffer
// @return the length of the user's input
int GetLine(char line_buf[], int line_buf_length);


// Reads all line from the standard input. If the length of user's input is
// > line_buf_length, the buffer will be realloced with
// 2 * line_buf_length auto. All the line will be ended with '\0'. Since the
// address of buffer may be changed after calling realloc, the address of the
// pointer to the buffer should be gaven.
//
// @param line_buf, the buffer to store the user's input.
// @param line_buf_length, the maximum length of the buffer.
// @return the length of the user's input.
int GetAllLine(char **line_buf, int line_buf_length);

#endif  // K_AND_R_ASSIGNMENTS_CHAPTER_1_UTILS_GET_LINE_H_
